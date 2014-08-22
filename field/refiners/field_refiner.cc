
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

//
/// @file
/// Implementation for class field_refiner
// A map from one sec_rep_space to another.
//

#include "field_refiner.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "depth_bound_refinement_policy.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/sheaf/factory.h"
#include "field_eval_iterator.h"
#include "field_refinement_buffer.h"
#include "field_refinement_policy.h"
#include "local_field_refiner.h"
#include "field_refiner_family.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#include "variance_bound_refinement_policy.h"
#include "field_vd.h"
#include "zone_centered_error_bound_refinement_policy.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_refiner::
field_refiner()
    : _refiners(0)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}

fields::field_refiner::
field_refiner(const field_refiner& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fields::field_refiner::
~field_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}


bool
fields::field_refiner::
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
// FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_refiner::
field_refiner(const poset& xbase_space,
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
fields::field_refiner::
refiners()
{
  return *_refiners;
}

fields::field_refinement_policy&
fields::field_refiner::
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
fields::field_refiner::
refine(field_vd& xtarget, bool xauto_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering refine(field_vd&, bool)");
#endif

  // Preconditions:

  require(xauto_access || xtarget.base_space().state_is_read_write_accessible());
  require(xauto_access || xtarget.state_is_read_write_accessible());

  define_old_variable(int old_xtarget_access_request_depth =
                        xtarget.access_request_depth());


  if(xauto_access)
  {
    xtarget.get_read_write_access(true, true);
  }

  require(xtarget.same_evaluation());

  // Body:

  // Put target base space in jim edit mode.

  xtarget.base_space().host()->begin_jim_edit_mode(false);

  // Create an evaluation iterator for the target.

  field_eval_iterator litr(xtarget);

  // Initialize the buffer shared by this, the refiner and the refinement policy;
  // uses discretization buffers from iterator.

  field_refinement_buffer lbuffer(xtarget,
                                  litr.coordinate_discretization_members(),
                                  litr.property_discretization_members(),
                                  policy().refinement_depth_ub());

  // Traverse the target; refining as needed.

  while(!litr.is_done())
  {
    // Get the refiner to match the cell type.

    local_field_refiner* lrefiner = _refiners->member(litr.type_id());

    assertion(lrefiner != 0);

    int ldepth = litr.refinement_depth();

    // Initialize some members in the refinement buffer.

    lbuffer.zone_id = litr.index();
    lbuffer.coord_evaluator = &litr.coordinate_evaluator();
    lbuffer.prop_evaluator  = &litr.property_evaluator();
    lbuffer.depth = ldepth;

    // Gather the coordinate dofs for this zone.

    lbuffer.gather_coordinate_dofs();

    if(ldepth > 0)
    {
      // Evaluate any property dofs for this zone
      // that have not been previously evaluated.

      lbuffer.refine_prop_dofs(lrefiner);
    }

    // Gather the property dofs for this zone.

    lbuffer.gather_property_dofs();

    // Test the refinement policy.

    if(lrefiner->policy().should_refine(lbuffer, ldepth))
    {
      // Policy says refine; do it.

      lrefiner->refine(lbuffer);

      // Save the current zone in the parent buffers.

      lbuffer.save_parent();

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
  }

  // Postconditions:

  ensure(xtarget.access_request_depth() == old_xtarget_access_request_depth);

  // Exit

  return;
}

void
fields::field_refiner::
refine(const sec_ed& xcoordinates, const sec_vd& xproperty, bool xauto_access)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("Entering refine(sec_ed&, sec_vd&, bool");
#endif

  // Preconditions:

  require(precondition_of(refine(field_vd(xcoordinates, xproperty, xauto_access), xauto_access)));

  // Body:

  field_vd ltarget(xcoordinates, xproperty, xauto_access);

  refine(ltarget, xauto_access);

  // Postconditions:

  ensure(postcondition_of(refine(field_vd(xcoordinates, xproperty, xauto_access), xauto_access)));

  // Exit

  return;
}

// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

