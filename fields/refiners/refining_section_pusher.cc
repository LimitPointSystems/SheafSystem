
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for class refining_section_pusher
/// A map from one sec_rep_space to another.

#include "refining_section_pusher.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "depth_bound_refinement_policy.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/sheaf/factory.h"
#include "ComLimitPoint/fields/field_eval_iterator.h"
#include "field_refinement_buffer.h"
#include "field_refinement_policy.h"
#include "local_field_refiner.h"
#include "field_refiner_family.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#include "variance_bound_refinement_policy.h"
#include "ComLimitPoint/fields/field_vd.h"
#include "zone_centered_error_bound_refinement_policy.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

// =============================================================================
// REFINING_SECTION_PUSHER FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::refining_section_pusher::
refining_section_pusher(const poset& xbase_space,
                        const std::string& xrefiner_family_name,
                        const std::string& xrefinement_policy_name,
                        bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xbase_space.state_is_read_accessible());
  require(field_refiner_family::family_factory().contains_prototype(xrefiner_family_name));
  require(field_refinement_policy::policy_factory().contains_prototype(xrefinement_policy_name));

  // Body:

  if(xauto_access)
  {
    xbase_space.get_read_access();
  }


  _refiners = field_refiner_family::new_family(xrefiner_family_name);

  field_refinement_policy* lpolicy =
    field_refinement_policy::new_policy(xrefinement_policy_name);

  /// @todo Remove dynamic cast when base_space_member returns base_space_poset
  ///       as its host.

  _refiners->initialize(dynamic_cast<const base_space_poset&>(xbase_space),
			*lpolicy);

  if(xauto_access)
  {
    xbase_space.release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(refiners().is_initialized());
  ensure(refiners().class_name() == xrefiner_family_name);

  // Exit:

  return;
}

fields::field_refiner_family&
fields::refining_section_pusher::
refiners()
{
  return *_refiners;
}

fields::field_refinement_policy&
fields::refining_section_pusher::
policy() const
{

  // Preconditions:


  // Body:

  field_refinement_policy& result = _refiners->policy();

  // Postconditions:


  // Exit:

  return result;
}

void
fields::refining_section_pusher::
push(const field_vd& xsource, field_vd& xtarget, bool xauto_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering push_pa:");
#endif

  // Preconditions:

  require(xauto_access || xsource.state_is_read_accessible());
  require(xauto_access || xtarget.base_space().state_is_read_write_accessible());
  require(xauto_access || xtarget.state_is_read_write_accessible());

  define_old_variable(int old_xsource_access_request_depth =
                        xsource.access_request_depth());
  define_old_variable(int old_xtarget_access_request_depth =
                        xtarget.access_request_depth());


  if(xauto_access)
  {
    xsource.get_read_access();
    xtarget.get_read_write_access(true, true);
  }

  require(xtarget.same_evaluation());

  // Body:

  // Initialize inversion for the source coordinates.

  if(!xsource.coordinates().is_invertible())
  {
    xsource.coordinates().initialize_point_locator(false);
  }

  // Put target base space in jim edit mode.

  /// @hack have to create separate handle because base_space_member::host()
  /// is type poset.
  /// @todo remove when sheaves/fiber_bundles refactored and host type is fixed.

  xtarget.base_space().host()->begin_jim_edit_mode(false);

  // Create an evaluation iterator for the target.

  field_eval_iterator litr(xtarget);

  // Initialize the buffer shared by this, the refiner and the refinement policy;
  // uses discretization buffers from iterator.

  field_refinement_buffer lbuffer(xsource,
                                  xtarget,
                                  litr.coordinate_discretization_members(),
                                  litr.property_discretization_members(),
                                  policy().refinement_depth_ub());

  // Traverse the target; pushing and refining as needed.

  while(!litr.is_done())
  {
    lbuffer.zone_id = litr.index();
    lbuffer.coord_evaluator = &litr.coordinate_evaluator();
    lbuffer.prop_evaluator  = &litr.property_evaluator();

    // Gather the coordinate dofs for this zone.

    lbuffer.gather_coordinate_dofs();

    // Push any property dofs that have not been pushed.

    lbuffer.push_prop_dofs();

    // Gather the property dofs for this zone.
    /// @todo integrate the gather with the push; more efficient.

    lbuffer.gather_property_dofs();

    // Get the refiner to match the cell type.

    local_field_refiner* lrefiner = _refiners->member(litr.type_id());

    assertion(lrefiner != 0);

    // Test the refinement policy.

    if(lrefiner->policy().should_refine(lbuffer, litr.refinement_depth()))
    {
      // Policy says refine; do it.

      lrefiner->refine(lbuffer);

      // Repeat the traversal of the down set of the current
      // zone in case we need to further refine the zones we
      // just added. Arg == true tells iterator we've just
      // refined this zone.

      litr.repeat(true);
    }
    else
    {
      // Just continue to the next zone.

      litr.next();
    }
  }

  // Finished with jim edit mode.

  xtarget.base_space().host()->end_jim_edit_mode(true, false);

  xtarget.coordinates().schema().force_cache_update();
  xtarget.property().schema().force_cache_update();

  if(xauto_access)
  {
    xtarget.release_access();
    xsource.release_access();
  }

  // Postconditions:

  ensure(xsource.access_request_depth() == old_xsource_access_request_depth);
  ensure(xtarget.access_request_depth() == old_xtarget_access_request_depth);

  // Exit

  return;
}


bool
fields::refining_section_pusher::
same_fiber(const sec_vd& x1, const sec_vd& x2) const
{
  bool result;

  // Preconditions:

  require(x1.state_is_read_accessible());
  require(x2.state_is_read_accessible());

  // Body:

  result =
    x1.schema().fiber_schema().is_same_state(&x2.schema().fiber_schema()) &&
    (x1.schema().df() == x2.schema().df());

  // Postconditions:

  ensure(result ==
         (x1.schema().fiber_schema().is_same_state(&x2.schema().fiber_schema()) &&
          (x1.schema().df() == x2.schema().df())));

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

fields::refining_section_pusher::
refining_section_pusher()
    : _refiners(0)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

fields::refining_section_pusher::
refining_section_pusher(const refining_section_pusher& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::refining_section_pusher::
~refining_section_pusher()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

bool
fields::refining_section_pusher::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  invariance(any::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

