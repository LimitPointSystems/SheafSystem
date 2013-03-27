// $RCSfile: local_field_refiner.cc,v $ $Revision: 1.12 $ $Date: 2013/03/13 00:58:59 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class local_field_refiner

#include "local_field_refiner.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "block.impl.h"
#include "depth_bound_refinement_policy.h"
#include "field_refinement_buffer.h"
#include "field_refinement_policy.h"
#include "section_evaluator.h"
#include "sec_vd.h"
#include "field_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// LOCAL_FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::local_field_refiner::
~local_field_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

int
fields::local_field_refiner::
db() const
{
  int result = -1;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= -1);

  // Exit:

  return result;
}

const string&
fields::local_field_refiner::
zone_type_name() const
{
  // Preconditions:


  // Body:

  is_abstract();

  static const string result("NOT_A_TYPE_NAME"); // Just to keep compiler happy

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}


const string&
fields::local_field_refiner::
vertex_type_name() const
{
  // Preconditions:


  // Body:

  static const string result("point");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}


const fields::field_refinement_policy&
fields::local_field_refiner::
policy() const
{
  return _policy;
}


void
fields::local_field_refiner::
refine(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(unexecutable("coordinate dofs have been gathered"));
  require(unexecutable("property dofs have been gathered"));

  // Body:

  refine_base_space(xbuffer);
  refine_coordinates(xbuffer);

  // Postconditions:

  // Exit:

  return;
}

sheaf::size_type
fields::local_field_refiner::
refined_zone_ct() const
{
  size_type result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result > 1);

  // Exit:

  return result;
}

const sheaf::block<sheaf::scoped_index>&
fields::local_field_refiner::
refined_zone_ids() const
{
  return _refined_zone_ids;
}

const fiber_bundle::chart_point_coord_type*
fields::local_field_refiner::
local_coordinates_map(size_type xi) const
{
  // Preconditions:

  require(xi < refined_zone_ids().ct());

  // Body:

  is_abstract();

  // Just to keep compiler happy:

  chart_point_coord_type* result = 0;

  // Postconditions:

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

fields::local_field_refiner::
local_field_refiner()
    :  _policy(*(new depth_bound_refinement_policy(0))) // Just to keep compiler happy.
{
  // Preconditions:

  // Body:

  not_implemented();

  initialize_buffers();

  // Postconditions:

  ensure(invariant());

  return;
}

fields::local_field_refiner::
local_field_refiner(const local_field_refiner& xother)
    :  _policy(xother._policy),
    _point_dof_tuple_ids(xother._point_dof_tuple_ids),
    _zone_dof_tuple_ids(xother._zone_dof_tuple_ids),
    _refined_zone_ids(xother._refined_zone_ids)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

fields::local_field_refiner::
local_field_refiner(const field_refinement_policy& xpolicy)
    : _policy(xpolicy)
{
  // Preconditions:

  // Body:

  initialize_buffers();

  // Postconditions:

  ensure(invariant());
  ensure(&policy() == &xpolicy);

  return;
}

void
fields::local_field_refiner::
initialize_buffers()
{
  // Preconditions:


  // Body:

  // Reserve some arbitrary amount of space
  // to avoid many small auto-allocations.

  _point_dof_tuple_ids.reserve(16);
  _zone_dof_tuple_ids.reserve(16);
  _refined_zone_ids.reserve(16);

  // Initialize the dof tuple ids to invalid;
  // they will be created as needed.

  _point_dof_tuple_ids.set_ct(_point_dof_tuple_ids.ub());

  _point_dof_tuple_ids.assign(scoped_index::INVALID());

  _zone_dof_tuple_ids.set_ct(_zone_dof_tuple_ids.ub());

  _zone_dof_tuple_ids.assign(scoped_index::INVALID());

  // Postconditions:


  // Exit:

  return;
}

sheaf::pod_index_type
fields::local_field_refiner::
create_vertex(base_space_poset& xbase, int xdepth)
{
  // Preconditions:

  require(xbase.in_jim_edit_mode());
  require(xdepth >= 0);

  // Body:

  // Find or create the right dof tuple.

  scoped_index ltuple_id;

  if(xdepth < _point_dof_tuple_ids.ub())
  {
    ltuple_id = _point_dof_tuple_ids[xdepth];
  }

  if(!ltuple_id.is_valid())
  {
    ltuple_id = xbase.prototype_dof_tuple_id(vertex_type_name(), xdepth, true, false);
    _point_dof_tuple_ids.force_item(xdepth, ltuple_id);
  }

  // Create the vertex and link it to the bottom.

  pod_index_type result = xbase.new_member(true, ltuple_id.hub_pod());

  xbase.new_link(result, BOTTOM_INDEX);

  // Postconditions:

  ensure(xbase.contains_member(result));
  ensure(xbase.type_name(result) == "point");
  ensure(xbase.refinement_depth(result) == xdepth);

  // The following is made unexecutable because it is expensive,
  // have to search the upper cover of bottom, which is O(#vertices).

  ensure(unexecutable(xbase.contains_cover_link(result, BOTTOM_INDEX)));

  // Exit:

  return result;
}

sheaf::pod_index_type
fields::local_field_refiner::
create_zone(base_space_poset& xbase, int xdepth)
{
  // Preconditions:

  require(xbase.in_jim_edit_mode());

  // Body:

  // Find or create the right dof tuple.

  scoped_index ltuple_id;

  if(xdepth < _zone_dof_tuple_ids.ub())
  {
    ltuple_id = _zone_dof_tuple_ids[xdepth];
  }

  if(!ltuple_id.is_valid())
  {
    ltuple_id = xbase.prototype_dof_tuple_id(zone_type_name(), xdepth, true, false);
    _zone_dof_tuple_ids.force_item(xdepth, ltuple_id);
  }

  // Create the triangle.

  pod_index_type result = xbase.new_member(true, ltuple_id.hub_pod());

  // Postconditions:

  ensure(xbase.contains_member(result));

  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::local_field_refiner*
fields::local_field_refiner::
clone() const
{
  local_field_refiner* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

fields::local_field_refiner&
fields::local_field_refiner::
operator=(const local_field_refiner& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::local_field_refiner::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

bool
fields::local_field_refiner::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const local_field_refiner*>(xother) != 0;

  // Postconditions:

  return result;

}

