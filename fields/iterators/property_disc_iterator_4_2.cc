
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
/// Implementation for class property_disc_iterator_4_2


#include "SheafSystem/property_disc_iterator_4_2.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/binary_section_space_schema_member.h"
#include "SheafSystem/eval_family.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/section_space_schema_member.h"
#include "SheafSystem/sec_ed_invertible.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/std_limits.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/structured_block_2d.h"
#include "SheafSystem/structured_block_3d.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/uniform_eval_family.h"
#include "SheafSystem/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PROPERTY_DISC_ITERATOR_4_2 FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::property_disc_iterator_4_2::
property_disc_iterator_4_2(const field_vd& xfield)
{

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().schema().conforms_to(base_space_member::standard_schema_path()));

  require(xfield.coordinates().schema().evaluator_family_name() == "uniform");

  /// @issue We can't support prop base < coord base in this implementation
  /// because we traverse from the prop down and we won't find the coord eval.

  require(xfield.property().schema().base_space().is_same_state(&xfield.coordinates().schema().base_space()));
  require(xfield.property().schema().rep().eval_is_above_disc());

  // Body:

  initialize_iteration(xfield, BIORDER);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xfield.coordinates().schema()));
  ensure(coordinates_schema().is_same_type(&xfield.coordinates().schema()));
  ensure(coordinates_schema().version() == xfield.coordinates().schema().version());
  ensure(property_schema().is_same_state(&xfield.property().schema()));
  ensure(property_schema().is_same_type(&xfield.property().schema()));
  ensure(property_schema().version() == xfield.property().schema().version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


fields::property_disc_iterator_4_2::
property_disc_iterator_4_2(
  const section_space_schema_member& xcoordinates_schema,
  const section_space_schema_member& xproperty_schema)
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));

  require(xcoordinates_schema.evaluator_family_name() == "uniform");

  require(xproperty_schema.state_is_read_accessible());

  /// @issue We can't support prop base < coord base in this implementation
  /// because we traverse from the prop down and we won't find the coord eval.

  require(xproperty_schema.base_space().is_same_state(&xcoordinates_schema.base_space()));
  require(xproperty_schema.rep().eval_is_above_disc());

  // Body:

  initialize_iteration(xcoordinates_schema, xproperty_schema, BIORDER);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xcoordinates_schema));
  ensure(coordinates_schema().is_same_type(&xcoordinates_schema));
  ensure(coordinates_schema().version() == xcoordinates_schema.version());
  ensure(property_schema().is_same_state(&xproperty_schema));
  ensure(property_schema().is_same_type(&xproperty_schema));
  ensure(property_schema().version() == xproperty_schema.version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


fields::property_disc_iterator_4_2::
~property_disc_iterator_4_2()
{
  // Preconditions:

  // Body:

  // Postconditions:

}



void
fields::property_disc_iterator_4_2::
get_prop_disc_values(const sec_vd& xsec)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());
  require(xsec.schema().is_same_state(&coordinates_schema()));

  // Implementation of evaluate below only correct for binary schema.
  /// @todo revise when ternary schema are supported.

  require(dynamic_cast<const binary_section_space_schema_member*>
    (&xsec.schema()) != 0);

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(xsec.schema().df() <= 3);

  // Since the prop disc at or above the prop eval, there should only
  // be a single disc member.

  require(coordinate_discretization_members().ct() == 1);

  // Body:

  if(_coord_state.dofs.ct() == 0)
  {
    // The dofs have not been gathered for thiscoord eval member.

    _coord_state.gather_dofs(xsec);
  }

  int ldf = _coord_state.df;
  block<sec_vd_dof_type>& lcoord_dofs = _coord_state.dofs;
  section_evaluator* lcoord_eval = _coord_state.eval;
  size_type lcoord_local_id = 0;

  section_evaluator* lprop_eval = _prop_state.eval;
  block<discretization_context>& ldisc_mbrs = _prop_state.discretization_members;
  size_type ldisc_ct = ldisc_mbrs.ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    discretization_context& ldisc_mbr = ldisc_mbrs[i];

    // Get the local coordinates of the disc point.

    chart_point_3d ldisc_pt;
    ldisc_pt.put_chart_id(ldisc_mbr.eval_id);

    lprop_eval->local_coordinates(ldisc_mbr.local_id, ldisc_pt.local_coords(), 3);

    // Unrefine from the prop eval to the coord eval.

    /// @error we assume the unrefine operator unrefines to the prop eval,
    /// but there is no way to ensure this condition.

    _coord_state.eval_mbr->unrefine_point_pa(ldisc_pt, ldisc_pt);

    // Evaluate the global coordinate section.

    lcoord_eval->value_at_coord(lcoord_dofs.base(),
                                lcoord_dofs.ct(),
                                ldisc_pt.local_coords(),
                                3,
                                ldisc_mbr.values,
                                ldf);
  }

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::property_disc_iterator_4_2::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Traverse the graph gathering coord and prop disc members until
  // we have enough context to evaluate the coordinates at the
  // the property disc points or until the traversal is done.

  property_disc_iterator::next(ltruncate);

  while(!is_done())
  {
    if(action() == PREVISIT_ACTION)
    {
      // The coord eval and disc are both __blocks.
      // The prop eval is strictly above the prop disc.

      if(_coord_state.eval_sp.contains_member(_index))
      {
        _coord_state.set_and_attach_evaluation_member(_index);
        _coord_state.discretization_members.set_ct(0);
        _coord_state.gather_discretization_member(_index, greater_index());
        _coord_state.local_id++;
        _coord_state.dofs.set_ct(0);
      }

      if(_prop_state.eval_sp.contains_member(_index))
      {
        _above.prop_eval = false;
        put_visit_once(false);

        _prop_state.set_evaluation_member(_index);
        _prop_state.initialize_order_correction();
        _prop_state.discretization_members.set_ct(0);
      }

      if(_prop_state.disc_sp.contains_member(_index))
      {
        // We only gather a prop disc member when we're below a
        // prop eval member and we haven't gathered it before.

        if(!(_above.prop_eval || _prop_state.visited[_index.pod()]))
        {
          _prop_state.gather_discretization_member(_index);

          _prop_state.visited.put(_index.pod(), true);
        }
        _prop_state.local_id++;
        ltruncate = true;
      }

    }
    else if(action() == POSTVISIT_ACTION)
    {
      if(_prop_state.eval_sp.contains_member(_index))
      {
        put_visit_once(true);
        _above.prop_eval  = true;

        break;
      }

      // If we invoke property_disc_iterator::next() from the postvisit action,
      // the truncation flag will be ignored, since you can only truncate
      // in the previsit action. But just to be specific, we'll set it false no
      // matter what we've done here.

      ltruncate = false;
    }
    else
    {
      post_fatal_error_message("unrecognized action");
    }

    property_disc_iterator::next(ltruncate);
  } // end while(!is_done())

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() ? action() == POSTVISIT_ACTION : true);

  // Exit

  return;
}

void
fields::property_disc_iterator_4_2::
reset(bool xreset_markers)
{
  // Preconditions:


  // Body:

  if(xreset_markers)
  {
    _prop_state.visited.make_false();
  }

  // Gather buffers and control flags reset in force_is_done
  // called from property_disc_iterator::reset

  property_disc_iterator::reset(xreset_markers);

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::property_disc_iterator_4_2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const property_disc_iterator_4_2*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fields::property_disc_iterator_4_2*
fields::property_disc_iterator_4_2::
clone() const
{
  // Preconditions:

  // Body:

  property_disc_iterator_4_2* result =
    new property_disc_iterator_4_2(coordinates_schema(), property_schema());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
fields::property_disc_iterator_4_2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(property_disc_iterator::invariant());

    disable_invariant_check();

    invariance(order() == BIORDER);

    invariance(coordinates_schema().evaluator_family_name() == "uniform");

    /// @issue We can't support prop base < coord base in this implementation
    /// because we traverse from the prop down and we won't find the coord eval.

    invariance(property_schema().base_space().is_same_state(&coordinates_schema().base_space()));

    invariance(property_schema().rep().eval_is_above_disc());

    // Since the coord disc is the same as the coord eval, there should
    // be at most a single disc member.

    require(!is_done() ? coordinate_discretization_members().ct() <= 1 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}
