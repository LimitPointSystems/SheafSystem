
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
/// Implementation for class property_disc_iterator_1_2


#include "property_disc_iterator_1_2.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_member.h"
#include "ComLimitPoint/fiber_bundle/eval_family.h"
#include "ComLimitPoint/fiber_bundle/sec_rep_descriptor.h"
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_member.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#include "std_limits.h"
#include "ComLimitPoint/fiber_bundle/structured_block_1d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_2d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_3d.h"
#include "ComLimitPoint/sheaf/subposet_member_iterator.h"
#include "ComLimitPoint/fiber_bundle/uniform_eval_family.h"
#include "field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PROPERTY_DISC_ITERATOR_1_2 FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::property_disc_iterator_1_2::
property_disc_iterator_1_2(const field_vd& xfield)
{

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xfield.property().schema().base_space().le(&xfield.coordinates().schema().base_space()));
  require(xfield.property().schema().evaluation().is_same_state(&xfield.coordinates().schema().evaluation()));
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


fields::property_disc_iterator_1_2::
property_disc_iterator_1_2(
  const section_space_schema_member& xcoordinates_schema,
  const section_space_schema_member& xproperty_schema)
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.base_space().le(&xcoordinates_schema.base_space()));
  require(xproperty_schema.evaluation().is_same_state(&xcoordinates_schema.evaluation()));
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


fields::property_disc_iterator_1_2::
~property_disc_iterator_1_2()
{
  // Preconditions:

  // Body:

  // Postconditions:

}



void
fields::property_disc_iterator_1_2::
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

  // Body:

  _coord_state.gather_dofs(xsec);

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
    if(_coord_state.disc_sp.contains_member(ldisc_mbr.disc_id))
    {
      // Don't need to evaluate, just get the coord disc.

      size_type ldof_id_begin = lcoord_local_id*ldf;
      for(size_type c=0; c<ldf; ++c)
      {
        ldisc_mbr.values[c] = lcoord_dofs[ldof_id_begin+c];
      }
      ++lcoord_local_id;
    }
    else
    {
      // Have to evaluate the coords at the prop disc point.
      // Get the local coordinates of the disc point.

      const int MAX_DB = 3;
      chart_point_coord_type local_coords[MAX_DB];

      lprop_eval->local_coordinates(ldisc_mbr.local_id, local_coords, MAX_DB);

      // Evaluate the global coordinate section.

      lcoord_eval->value_at_coord(lcoord_dofs.base(),
                                  lcoord_dofs.ct(),
                                  local_coords,
                                  MAX_DB,
                                  ldisc_mbr.values,
                                  ldf);
    }
  }

  // Postconditions:


  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

void
fields::property_disc_iterator_1_2::
coord_eval_previsit_action()
{
  // Preconditions:

  require(_at.coord_eval);

  // Body:

  _above.coord_eval = false;

  _coord_state.set_evaluation_member(_index);
  _coord_state.initialize_order_correction();
  _coord_state.discretization_members.set_ct(0);
  _coord_state.down_set.set_ct(0);

  _prop_state.set_evaluation_member(_index);
  _prop_state.initialize_order_correction();
  _prop_state.discretization_members.set_ct(0);

  // Postconditions:


  // Exit:

  return;
}

void
fields::property_disc_iterator_1_2::
prop_disc_previsit_action()
{
  // Preconditions:

  require(_at.prop_disc);

  // Body:

  _above.prop_disc = false;

  // We only gather prop disc members we haven't gathered before.

  if(!_prop_state.visited[_index.pod()])
  {
    // This member has not been visited before; gather it and mark it.

    _prop_state.gather_discretization_member(_index, greater_index());

    _prop_state.visited.put(_index.pod(), true);
  }

  // Increment the local id every time, but after we've gathered.

  _prop_state.local_id++;

  // Postconditions:


  // Exit:

  return;
}

void
fields::property_disc_iterator_1_2::
coord_disc_previsit_action()
{
  // Preconditions:

  require(_at.coord_disc);

  // Body:

  _above.coord_disc = false;

  _coord_state.gather_discretization_member(_index, greater_index());
  _coord_state.local_id++;

  // Postconditions:


  // Exit:

  return;
}


void
fields::property_disc_iterator_1_2::
coord_eval_postvisit_action()
{
  // Preconditions:

  require(_at.coord_eval);

  // Body:

  block<scoped_index>& ldown_set = _coord_state.down_set;
  size_type lct = ldown_set.ct();
  for(size_type i=0; i<lct; ++i)
  {
    put_has_visited(ldown_set[i], false);
  }
  ldown_set.set_ct(0);

  _above.coord_eval  = true;

  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::property_disc_iterator_1_2::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Never want to see a prop disc member more than once,
  // so always clear the buffer before we start.

  _prop_state.discretization_members.set_ct(0);

  // Traverse the graph gathering coord and prop disc members until
  // we have enough context to evaluate the coordinates at the
  // the property disc points or until the trversal is done.

  property_disc_iterator::next(ltruncate);

  while(!is_done())
  {
    if(action() == PREVISIT_ACTION)
    {
      if(!_above.coord_eval)
      {
        _coord_state.down_set.push_back(_index);
      }

      // The coord and prop eval are both the element subposet and
      // the coord disc is the vertices. The prop disc is strictly below
      // the elements, but not necessarily equal to the vertices.

      _at.coord_eval = _coord_state.eval_sp.contains_member(_index);
      _at.coord_disc = _coord_state.disc_sp.contains_member(_index);
      _at.prop_disc  = _prop_state.disc_sp.contains_member(_index);

      if(_at.coord_eval)
      {
        coord_eval_previsit_action();
      }

      if(_at.prop_disc)
      {
        prop_disc_previsit_action();
      }

      if(_at.coord_disc)
      {
        coord_disc_previsit_action();
        ltruncate = true;
      }
    }
    else if(action() == POSTVISIT_ACTION)
    {
      _at.coord_eval = _coord_state.eval_sp.contains_member(_index);

      if(_at.coord_eval)
      {
        coord_eval_postvisit_action();
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
fields::property_disc_iterator_1_2::
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
fields::property_disc_iterator_1_2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const property_disc_iterator_1_2*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fields::property_disc_iterator_1_2*
fields::property_disc_iterator_1_2::
clone() const
{
  // Preconditions:

  // Body:

  property_disc_iterator_1_2* result =
    new property_disc_iterator_1_2(coordinates_schema(), property_schema());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
fields::property_disc_iterator_1_2::
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
    invariance(property_schema().evaluation().is_same_state(&coordinates_schema().evaluation()));
    invariance(property_schema().rep().eval_is_above_disc());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


