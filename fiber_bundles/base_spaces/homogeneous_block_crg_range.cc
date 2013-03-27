// $RCSfile: homogeneous_block_crg_range.cc,v $ $Revision: 1.23 $ $Date: 2013/03/13 00:58:40 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class homogeneous_block_crg_range

#include "homogeneous_block_crg_range.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "offset_index_space_state.h"
#include "index_space_iterator.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"
#include "homogeneous_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// ===========================================================
// HOMOGENEOUS_BLOCK_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::homogeneous_block_crg_range::
homogeneous_block_crg_range()
  : _conn_begin(invalid_pod_index()),
    _adj_begin(invalid_pod_index()),
    _conn_id_space_interval(0),
    _adj_id_space_interval(0)
{
  // Body:

  // Initialize dof tuple ids.

  _dof_tuple_ids.reserve(MEMBER_CLASS_END);
  _dof_tuple_ids.set_ct(MEMBER_CLASS_END);
  _dof_tuple_ids.assign(scoped_index::INVALID());

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::homogeneous_block_crg_range::
~homogeneous_block_crg_range()
{
  // Preconditions:

  // Body:

  // nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_range::
initialize_zone_vertex_id_space(const string& xname,
				pod_index_type xoffset,
				size_type xct)
{
  // Preconditions:

  require(!zones_initialized());
  require(!vertices_initialized());

  // Body:

  arg_list largs =
    offset_index_space_state::make_arg_list(xoffset, xct);

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(xname, "offset_index_space_state",
				    largs, false);

  _zone_id_space.attach_to(id_spaces(), lspace_id);
  _vertex_id_space.attach_to(id_spaces(), lspace_id);

  // Postconditions:

  ensure(zones_initialized());
  ensure(vertices_initialized());

  // Exit:

  return;
}

void
fiber_bundle::homogeneous_block_crg_range::
initialize_conn_adj_id_spaces(const string& xclass_name,
			      const arg_list& xargs,
			      size_type xub)
{
  // Preconditions:

  require(!connectivity_initialized());
  require(!adjacency_initialized());

  // Body:

  _conn_begin = _id_spaces->new_secondary_interval(xclass_name, xargs, xub);
  _adj_begin = _conn_begin;

  _conn_id_space_interval = collection(_conn_begin);
  _adj_id_space_interval = _conn_id_space_interval;

  // Postconditions:

  ensure(connectivity_initialized());
  ensure(adjacency_initialized());
  ensure(_conn_begin == _adj_begin);
  ensure_for_range(pod_index_type i = 0, i < xub, ++i, id_spaces().contains(_adj_begin+i));

  // Exit:

  return;
}

fiber_bundle::homogeneous_block_crg_range::member_class_type
fiber_bundle::homogeneous_block_crg_range::
member_class(pod_index_type xmbr_index) const
{

  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  member_class_type result;

  if(_vertex_id_space.contains_hub(xmbr_index))
  {
    result = VERTEX;
  }
  else if(_zone_id_space.contains_hub(xmbr_index))
  {
    result = ZONE;
  }
  else
  {
    result = BLOCK;
  }

  // Postconditions:


  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ZONE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
zones_initialized() const
{
  return _zone_id_space.is_attached();
}

const sheaf::offset_index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
zone_id_space() const
{
  // Preconditions:

  require(zones_initialized());

  // Body:

  const offset_index_space_handle& result = _zone_id_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_zone_id_space_iterator() const
{
  // Preconditions:

  require(zones_initialized());

  // Body:

  index_space_iterator& result = _zone_id_space.get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_zone_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(zones_initialized());
  require(allocated_zone_id_space_iterator(xitr));

  // Body:

  _zone_id_space.release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_zone_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(zones_initialized());

  // Body:

  bool result = _zone_id_space.allocated_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_range::
initialize_zone_id_space(const string& xname,
			 pod_index_type xoffset,
			 size_type xct)
{
  // Preconditions:

  require(!zones_initialized());

  // Body:

  arg_list largs =
    offset_index_space_state::make_arg_list(xoffset, xct);

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(xname, "offset_index_space_state",
				    largs, false);

  _zone_id_space.attach_to(id_spaces(), lspace_id);

  // Postconditions:

  ensure(zones_initialized());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// VERTEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
vertices_initialized() const
{
  return _vertex_id_space.is_attached();
}

const sheaf::offset_index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
vertex_id_space() const
{
  // Preconditions:

  require(vertices_initialized());

  // Body:

  const offset_index_space_handle& result = _vertex_id_space;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_vertex_id_space_iterator() const
{
  // Preconditions:

  require(vertices_initialized());

  // Body:

  index_space_iterator& result = _vertex_id_space.get_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_vertex_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(vertices_initialized());
  require(allocated_vertex_id_space_iterator(xitr));

  // Body:

  _vertex_id_space.release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_vertex_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(vertices_initialized());

  // Body:

  bool result = _vertex_id_space.allocated_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_range::
initialize_vertex_id_space(const string& xname,
			   pod_index_type xoffset,
			   size_type xct)
{
  // Preconditions:

  require(!vertices_initialized());

  // Body:

  arg_list largs =
    offset_index_space_state::make_arg_list(xoffset, xct);

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(xname, "offset_index_space_state",
				    largs, false);

  _vertex_id_space.attach_to(id_spaces(), lspace_id);

  // Postconditions:

  ensure(vertices_initialized());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// CONNECTIVITY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
connectivity_initialized() const
{
  return (_conn_id_space_interval != 0);
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
get_connectivity_id_space(pod_index_type xzone_id) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(zone_id_space().contains_hub(xzone_id));

  // Body:

  index_space_handle& result =
    _conn_id_space_interval->get_id_space(_zone_id_space.pod(xzone_id));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}
  
sheaf::index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
get_connectivity_id_space(const scoped_index& xzone_id) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(zone_id_space().contains_hub(xzone_id));

  // Body:

  pod_index_type lzone_id = xzone_id.same_scope(zone_id_space()) ?
    xzone_id.pod() : zone_id_space().pod(xzone_id);

  index_space_handle& result = _conn_id_space_interval->get_id_space(lzone_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_connectivity_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(allocated_connectivity_handle(xid_space));

  // Body:

  _conn_id_space_interval->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_connectivity_handle(index_space_handle& xid_space) const
{
  // Preconditions:

  require(connectivity_initialized());

  // Body:

  bool result = _conn_id_space_interval->allocated_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_connectivity_id_space_iterator(pod_index_type xzone_id) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(zone_id_space().contains_hub(xzone_id));

  // Body:

  index_space_iterator& result =
    _conn_id_space_interval->get_iterator(_zone_id_space.pod(xzone_id));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}
  
sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_connectivity_id_space_iterator(const scoped_index& xzone_id) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(zone_id_space().contains_hub(xzone_id));

  // Body:

  pod_index_type lzone_id = xzone_id.same_scope(zone_id_space()) ?
    xzone_id.pod() : zone_id_space().pod(xzone_id);

  index_space_iterator& result =
    _conn_id_space_interval->get_iterator(lzone_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_connectivity_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(connectivity_initialized());
  require(allocated_connectivity_iterator(xitr));

  // Body:

  _conn_id_space_interval->release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_connectivity_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(connectivity_initialized());

  // Body:

  bool result = _conn_id_space_interval->allocated_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_range::
initialize_connectivity_id_spaces(const string& xclass_name,
				  const arg_list& xargs,
				  size_type xub)
{
  // Preconditions:

  require(!connectivity_initialized());

  // Body:

  _conn_begin = _id_spaces->new_secondary_interval(xclass_name, xargs, xub);
  _conn_id_space_interval = collection(_conn_begin);

  // Postconditions:

  ensure(connectivity_initialized());
  ensure_for_range(pod_index_type i = 0, i < xub, ++i, id_spaces().contains(_conn_begin+i));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ADJACENCY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
adjacency_initialized() const
{
  return (_adj_id_space_interval != 0);
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
get_adjacency_id_space(pod_index_type xvertex_id) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(vertex_id_space().contains_hub(xvertex_id));

  // Body:

  index_space_handle& result =
    _adj_id_space_interval->get_id_space(_vertex_id_space.pod(xvertex_id));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}
  
sheaf::index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
get_adjacency_id_space(const scoped_index& xvertex_id) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(vertex_id_space().contains_hub(xvertex_id));

  // Body:

  pod_index_type lvertex_id = xvertex_id.same_scope(vertex_id_space()) ?
    xvertex_id.pod() : vertex_id_space().pod(xvertex_id);

  index_space_handle& result =
    _adj_id_space_interval->get_id_space(lvertex_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_adjacency_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(allocated_adjacency_handle(xid_space));

  // Body:

  _adj_id_space_interval->release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_adjacency_handle(index_space_handle& xid_space) const
{
  // Preconditions:

  require(adjacency_initialized());

  // Body:

  bool result = _adj_id_space_interval->allocated_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_adjacency_id_space_iterator(pod_index_type xvertex_id) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(vertex_id_space().contains_hub(xvertex_id));

  // Body:

  index_space_iterator& result =
    _adj_id_space_interval->get_iterator(_vertex_id_space.pod(xvertex_id));

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}
  
sheaf::index_space_iterator&
fiber_bundle::homogeneous_block_crg_range::
get_adjacency_id_space_iterator(const scoped_index& xvertex_id) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(vertex_id_space().contains_hub(xvertex_id));

  // Body:

  pod_index_type lvertex_id = xvertex_id.same_scope(vertex_id_space()) ?
    xvertex_id.pod() : vertex_id_space().pod(xvertex_id);

  index_space_iterator& result =
    _adj_id_space_interval->get_iterator(lvertex_id);

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block_crg_range::
release_adjacency_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(adjacency_initialized());
  require(allocated_adjacency_iterator(xitr));

  // Body:

  _adj_id_space_interval->release_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_range::
allocated_adjacency_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(adjacency_initialized());

  // Body:

  bool result = _adj_id_space_interval->allocated_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_range::
initialize_adjacency_id_spaces(const string& xclass_name,
			       const arg_list& xargs,
			       size_type xub)
{
  // Preconditions:

  require(!adjacency_initialized());

  // Body:

  _adj_begin = _id_spaces->new_secondary_interval(xclass_name, xargs, xub);
  _adj_id_space_interval = collection(_adj_begin);

  // Postconditions:

  ensure(adjacency_initialized());
  ensure_for_range(pod_index_type i = 0, i < xub, ++i, id_spaces().contains(_adj_begin+i));

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BASE_SPACE_CRG_RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_range::
cells_begin() const
{
  return implicit_begin();
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_range::
cells_end() const
{
  return end();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// RANGE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_handle&
fiber_bundle::homogeneous_block_crg_range::
atoms() const
{
  // Preconditions:

  // Body:

  return _vertex_id_space;
}

/// @todo Remove.

// sheaf::cover_set_iterator
// fiber_bundle::homogeneous_block_crg_range::
// atoms() const
// {
//   // Preconditions:


//   // Body:

//   /// @todo replace with specialized iterator, when available

//   list_cover_set* lcover = new list_cover_set(0);
//   lcover->put_is_implicit(true);

//   index_space_iterator& litr = _vertex_id_space.get_iterator();
//   while(!litr.is_done())
//   {
//     lcover->push_back(litr.hub_pod());

//     litr.next();
//   }
//   _vertex_id_space.release_iterator(litr);

//   cover_set_iterator result(*lcover);

//   // Postconditions:


//   // Exit:

//   return result;
// }

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
is_jim(pod_index_type xmbr_index) const
{
  // Every member except the block itself is a jim.

  return !is_range_member(xmbr_index);
}

const sheaf::scoped_index&
fiber_bundle::homogeneous_block_crg_range::
dof_tuple_id(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // Map xmbr_index to the id space of this.

  const scoped_index& result =
    _dof_tuple_ids[member_class(xmbr_index)];

  // Postconditions:

  ensure(result.is_valid());

  // Exit:

  return result;
}

const sheaf::scoped_index&
fiber_bundle::homogeneous_block_crg_range::
block_dof_tuple_id() const
{
  return _dof_tuple_ids[BLOCK];
}

const sheaf::scoped_index&
fiber_bundle::homogeneous_block_crg_range::
zone_dof_tuple_id() const
{
  return _dof_tuple_ids[ZONE];
}

const sheaf::scoped_index&
fiber_bundle::homogeneous_block_crg_range::
vertex_dof_tuple_id() const
{
  return _dof_tuple_ids[VERTEX];
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
is_initialized() const
{
  bool result =
    base_space_crg_range::is_initialized() &&
    zones_initialized() &&
    vertices_initialized() &&
    connectivity_initialized() &&
    adjacency_initialized();

  return result;
}


const string&
fiber_bundle::homogeneous_block_crg_range::
class_name() const
{
  static const string result("homogeneous_block_crg_range");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const homogeneous_block_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::homogeneous_block_crg_range*
fiber_bundle::homogeneous_block_crg_range::
clone() const
{
  // Preconditions:

  // Body:

  homogeneous_block_crg_range* result = 0;

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::homogeneous_block_crg_range::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(base_space_crg_range::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const homogeneous_block_crg_range& xr, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

