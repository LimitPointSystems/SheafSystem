// $RCSfile: zone_nodes_block_crg_range.cc,v $ $Revision: 1.28 $ $Date: 2013/03/13 00:58:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class zone_nodes_block_crg_range

#include "zone_nodes_block_crg_range.h"

#include "arg_list.h"
#include "array_implicit_index_space_iterator.h"
#include "array_index_space_interval.h"
#include "assert_contract.h"
#include "block_adjacency.h"
#include "block_connectivity.h"
#include "error_message.h"
#include "factory.h"
#include "hash_index_space_state.h"
#include "homogeneous_block.h"
#include "index_space_iterator.h"
#include "ragged_array_index_space_interval.h"
#include "section_space_schema_member.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT
// #undef DIAGNOSTIC_OUTPUT

namespace
{
  const sheaf::size_type NODE_IDS_BEGIN = 4;
  const sheaf::size_type EXPLICIT_PRIVATE_DATA_SIZE = 2;
}


// ===========================================================
// ZONE_NODES_BLOCK_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::zone_nodes_block_crg_range::
zone_nodes_block_crg_range()
{
  // Preconditions:

  // Body:

  _nodes_per_zone = 0;
  _zone_db = -1;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}


fiber_bundle::zone_nodes_block_crg_range::
~zone_nodes_block_crg_range()
{}

string
fiber_bundle::zone_nodes_block_crg_range::
vertex_client_id_space_name(pod_index_type xhub_id)
{
  // Preconditions:


  // Body:

  string result(poset_path::make_reserved_name("", xhub_id, "_vertex_client_ids"));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::zone_nodes_block_crg_range::
vertex_client_id_space() const
{
  require(vertex_client_id_space_initialized());

  return _vertex_client_id_space;
}

bool
fiber_bundle::zone_nodes_block_crg_range::
vertex_client_id_space_initialized() const
{
  return _vertex_client_id_space.is_attached();
}

void
fiber_bundle::zone_nodes_block_crg_range::
initialize_vertex_client_id_space(const adj_type& xadj)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());

  // Body:

  pod_index_type lblock_id = range_member();

  string lname(vertex_client_id_space_name(lblock_id));

  // Create the id space.

  arg_list largs = hash_index_space_state::make_arg_list(xadj.node_ct());

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(lname,
				    "hash_index_space_state",
				    largs,
				    false);
  _vertex_client_id_space.attach_to(*_id_spaces, lspace_id);

  // Populate the id space.

  pod_index_type llocal_vertex_id = lblock_id + xadj.zone_ct();
  typedef adj_type::const_node_iterator_type node_itr_type;

  for(node_itr_type v = xadj.begin(); v != xadj.end(); ++v)
  {
    _vertex_client_id_space.insert(v->first, llocal_vertex_id);
    ++llocal_vertex_id;
  }

  assertion(llocal_vertex_id == lblock_id + xadj.zone_ct() + xadj.node_ct());

  // Postconditions:

  ensure(vertex_client_id_space_initialized());
  ensure(vertex_client_id_space().ct() == xadj.node_ct());

  // Exit:

  return;
}

void
fiber_bundle::zone_nodes_block_crg_range::
initialize_connectivity_id_spaces(size_type xzone_ct,
				  size_type xnodes_per_zone,
				  size_type xconn_ct,
				  const pod_index_type* xconn)
{
  // Preconditions:

  // Body:

  // Construct the connectivity data.

  block<pod_index_type> lconn(xconn_ct);

  pod_index_type k = 0;

  for(size_type i=0; i<xzone_ct; ++i)
  {
    // Move to the next row before body of loop,
    // this leaves an unused 0-th row and avoids
    // creating an unused last row, which is what we want.

    for(size_type j=0; j<xnodes_per_zone; ++j)
    {
      assertion(k < xconn_ct);

      // Store the local id.

      lconn.push_back(_vertex_client_id_space.hub_pod(xconn[k++]));
    }
  }

  // Construct the id space interval.

  arg_list largs = 
    array_index_space_interval::make_arg_list(lconn, xnodes_per_zone);

  homogeneous_block_crg_range::
    initialize_connectivity_id_spaces("array_index_space_interval",
				      largs, xzone_ct);

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::zone_nodes_block_crg_range::
initialize_adjacency_id_spaces(const adj_type& xadj)
{
  // Preconditions:

  // Body:

  // Construct adjacency ragged array.

  ragged_array<pod_index_type> ladj;

  typedef adj_type::const_node_iterator_type node_itr_type;
  typedef adj_type::const_zone_iterator_type zone_itr_type;

  pod_index_type lzone_offset = range_member() + 1;

  node_itr_type v = xadj.begin();

  while(v != xadj.end())
  {
    for(zone_itr_type z = v->second.begin(); z != v->second.end(); ++z)
    {
      ladj.push_back((*z) + lzone_offset);
    }

    // Increment to the next vertex

    ++v;

    if(v != xadj.end())
    {
      ladj.new_back_row();
    }
  }

  // Construct the id space interval.

  arg_list largs = ragged_array_index_space_interval::make_arg_list(ladj);

  homogeneous_block_crg_range::
    initialize_adjacency_id_spaces("ragged_array_index_space_interval",
				   largs, xadj.node_ct());

  // Postconditions:

  // Exit:

  return;
}

const string&
fiber_bundle::zone_nodes_block_crg_range::
zone_prototype_name(const block_connectivity& xconn)
{
  // Preconditions:


  // Body:

  static const string prototype_names[block_connectivity::CELL_TYPE_END] =
    {
      "point",
      "segment_complex",
      "quad_nodes",
      "triangle_nodes",
      "hex_nodes",
      "tetra_nodes"
    };

  const string& result = prototype_names[xconn.element_type()];

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}


int
fiber_bundle::zone_nodes_block_crg_range::
zone_db(const block_connectivity& xconn)
{
  // Preconditions:


  // Body:

  static const int ldb[block_connectivity::CELL_TYPE_END] =
    {
      0, 1, 2, 2, 3, 3
    };

  int result = ldb[xconn.element_type()];

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_CRG_RANGE FACET
// ===========================================================

/// @todo Remove.

// sheaf::cover_set_iterator
// fiber_bundle::zone_nodes_block_crg_range::
// block_vertices() const
// {
//   // Preconditions:


//   // Body:

//   // Thee are no block_vertices.

//   cover_set_iterator result;

//   // Postconditions:

//   ensure(result.is_done());

//   // Exit:

//   return result;
// }

int
fiber_bundle::zone_nodes_block_crg_range::
db(pod_index_type xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  int result = (member_class(xmbr_id) == VERTEX) ? 0 : _zone_db;

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BLOCK VERTICES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
fiber_bundle::structured_block_3d_crg_range::
initialize_block_vertices() const
{
  // Preconditions:

  require(!block_vertices_initialized());
  require(vertices_initialized());

  // Body:

  arg_list largs = list_index_space_state::make_arg_list();

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(block_vertices_name(),
				    "list_index_space_state",
				    largs, false);

  _block_vertices_id_space.attach_to(id_spaces(), lspace_id);

  // Block vertices id space is empty.

  // Postconditions:

  ensure(block_vertices_initialized());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_range::
get_size(const block_connectivity& xconn, size_type& result)
{
  // Preconditions:


  // Body:

  // Size is number of zones + number of nodes + 1.

  result = xconn.element_ct() + xconn.node_ct() + 1;

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

const sheaf::index_space_handle&
sheaf::zone_nodes_block_crg_range::
implicit_cover_id_space(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  /// @todo Implement.

  index_space_handle* result = 0; // Silence the compiler.

  not_implemented();

  // Postconditions:

  // Exit:

  return *result;
}

void
sheaf::zone_nodes_block_crg_range::
initialize_explicit_cover(bool xlower,
			  pod_index_type xmbr_index,
			  interval_index_space_handle& xcover) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(!cover_is_explicit(xlower, xmbr_index));

  // Body:

  define_old_variable(size_type old_cover_ct = cover_id_space(xlower, xmbr_index).ct());

  /// @todo Implement.

  not_implemented();

  // Postconditions:

  ensure(cover_id_space(xlower, xmbr_index).ct() == old_cover_ct);

  // Exit:

  return;
}

/// @todo Remove.

// sheaf::cover_set_iterator
// fiber_bundle::zone_nodes_block_crg_range::
// implicit_cover_iterator(bool xlower, pod_index_type xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

//   // Map xmbr_index to the id space of this.

//   list_cover_set* lcover = new list_cover_set(0);
//   lcover->put_is_implicit(true);

//   if(xlower)
//   {
//     // Lower cover

//     switch(member_class(xmbr_index))
//     {
//     case VERTEX:
//       {  
// 	lcover->push_back(BOTTOM_INDEX);
// 	break;
//       }

//     case ZONE:
//       {  
// 	index_space_iterator& litr = get_connectivity_id_space_iterator(xmbr_index);

// 	while(!litr.is_done())
// 	{
// 	  lcover->push_back(litr.hub_pod());

// 	  litr.next();
// 	}
// 	release_connectivity_id_space_iterator(litr);
// 	break;
//       }

//     case BLOCK:
//       {  
// 	index_space_iterator& litr = _zone_id_space.get_iterator();
// 	while(!litr.is_done())
// 	{
// 	  lcover->push_back(litr.hub_pod());
	 
// 	  litr.next();
// 	}
// 	_zone_id_space.release_iterator(litr);
// 	break;
//       }
//     }
//   }
//   else
//   {
//     // Upper cover

//     switch(member_class(xmbr_index))
//     {
//     case VERTEX:
//       {
// 	index_space_iterator& litr = get_adjacency_id_space_iterator(xmbr_index);
	
// 	while(!litr.is_done())
// 	{
// 	  lcover->push_back(litr.hub_pod());

// 	  litr.next();
// 	}
// 	release_adjacency_id_space_iterator(litr);
// 	break;
//       }
      
//     case ZONE:
//       {
//         lcover->push_back(range_member());
// 	break;
//       }
      
//     case BLOCK:

//       // Upper cover is empty;
//       // will be overridden by explicit cover set.

//       break;
//     }
//   }

//   cover_set_iterator result(lcover);

//   return result;
// }

// PRIVATE DATA MEMBERS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_range::
get_dof_tuple_ids(poset_state_handle& xhost,
                  const block_connectivity& xconn,
                  block<scoped_index>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);

  string lname = zone_prototype_name(xconn);
  size_type lzone_ct = xconn.element_ct();

  result[BLOCK]  =
    homogeneous_block::new_row_dof_map(xhost, "unstructured_block", lname, lzone_ct, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, lname, true);
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true);

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// PRIVATE_DATA FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_range::
get_private_data(const block_connectivity& xconn,
                 block<pod_index_type>& xdata)
{
  // Preconditions:

  // Body:

  size_type lnode_ids_ct = xconn.node_id_ct();

  size_type lpd_size = lnode_ids_ct + NODE_IDS_BEGIN + EXPLICIT_PRIVATE_DATA_SIZE;
  xdata.reserve(lpd_size);
  xdata.set_ct(lpd_size);

  size_type j=0;
  xdata[j++] = zone_db(xconn); // xdata[0]
  xdata[j++] = xconn.element_ct(); // xdata[1]
  xdata[j++] = xconn.nodes_per_element(); // xdata[2]
  xdata[j++] = lnode_ids_ct; // xdata[3]

  const pod_index_type* lnode_ids = xconn.node_ids();

  for(size_type i = 0; i < lnode_ids_ct; ++i)
  {
    xdata[j++] = lnode_ids[i];
  }

  // No explicit covers.

  xdata[j++] = 0;
  xdata[j++] = 0;

  // Since xconn values are client ids,
  // above call puts client ids in xdata.

  // Postconditions:

  ensure(unexecutable("node ids are clients ids"));

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
fiber_bundle::zone_nodes_block_crg_range::
implicit_private_data_size() const
{
  return _zone_id_space.ct()*_nodes_per_zone + NODE_IDS_BEGIN;
}

void
fiber_bundle::zone_nodes_block_crg_range::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  size_type lzone_ct = _zone_id_space.ct();

  size_type lpd_size = lzone_ct*_nodes_per_zone + NODE_IDS_BEGIN;
  xdata.set_ct(lpd_size);

  size_type j=0;
  xdata[j++] = _zone_db; // xdata[0]
  xdata[j++] = lzone_ct; // xdata[1]
  xdata[j++] = _nodes_per_zone; // xdata[2]
  xdata[j++] = lzone_ct*_nodes_per_zone; // xdata[3]

  index_space_iterator& lzone_itr = _zone_id_space.get_iterator();
  array_implicit_index_space_iterator lconn_itr(*_id_spaces, _conn_begin);

  while(!lzone_itr.is_done())
  {
    lconn_itr.attach_to(*_conn_id_space_interval, lzone_itr.pod());

    while(!lconn_itr.is_done())
    {
      xdata[j++] = lconn_itr.hub_pod();

      lconn_itr.next();
    }

    lzone_itr.next();
  }
  _zone_id_space.release_iterator(lzone_itr);

  // Postconditions:

  ensure(xdata.ct() == private_data_size());
  ensure(unexecutable("node ids are clients ids"));

  // Exit:

  return;
}

void
fiber_bundle::zone_nodes_block_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  /// @hack The following precondition can not be implemented because
  ///       it relies on the this size of zone id space and nodes per zone
  ///       which have not been set yet.
  ///require(xdata.ct() >= implicit_private_data_size());  

  // Body:

  _zone_db = xdata[0];
  _zone_ct = xdata[1];
  _nodes_per_zone = xdata[2];

  size_type lconn_ct = xdata[3];
  pod_index_type* lconn = &(xdata[4]);

  // Find the distict vertices by constructing the vertex to zone
  // adjacency relation from the zone to vertex connectivity relation.
  //
  // Use of map as the temporary adjacency storage sorts the vertices
  // in ascending order and ensures that vertex_client_id_space
  // constructed below is order-preserving (vertices appear
  // in local id space in the same order as in client id space).

  adj_type ladj(_zone_ct, _nodes_per_zone, lconn_ct, lconn);

  // Create the vertex client id space and
  // get an index in its scope.

  initialize_vertex_client_id_space(ladj);

  // Initialize the connectivity id spaces.

  initialize_connectivity_id_spaces(_zone_ct, _nodes_per_zone,
				    lconn_ct, lconn);

  // Initialize the adjacency id spaces.

  initialize_adjacency_id_spaces(ladj);

  // Done.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// FINIALIZE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Compute the top ids for the cell ranges.

  size_type lvertex_ct = _vertex_client_id_space.ct();

  pod_index_type lblock_id     = range_member();
  pod_index_type lzone_begin   = lblock_id + 1;
  pod_index_type lvertex_begin = lzone_begin + _zone_ct;

  // Construct the id space for the zones.

  /// @todo Give product structure when zone nodes block has enough information.

  const string& lzone_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(_zone_db), lblock_id);

  initialize_zone_id_space(lzone_id_space_name, lzone_begin, _zone_ct);

  // Construct the id space for the vertices.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(0), lblock_id);

  initialize_vertex_id_space(lvertex_id_space_name, lvertex_begin, lvertex_ct);

  // Construct the id space for the block vertices.

  initialize_block_vertices_id_space();

  // Now this can be inserted in the standard subposets (d-cells, etc).

  lhost.insert_range_in_standard_subposets(*this);

  // Put atoms in upper cover of bottom.

  /// @hack this same call is made in poset_crg_state::new_member_range,
  /// where it fails silectly because the vertex range is empty.
  /// This protocol is way too arcane and we need to find some better way.

  xhost.append_cover(atoms(), UPPER, BOTTOM_INDEX);

  implicit_crg_range::finalize(xhost);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const string&
fiber_bundle::zone_nodes_block_crg_range::
class_name() const
{
  static const string result("zone_nodes_block_crg_range");
  return result;
}

bool
fiber_bundle::zone_nodes_block_crg_range::
is_initialized() const
{
  bool result =
    homogeneous_block_crg_range::is_initialized() &&
    vertex_client_id_space_initialized();

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::zone_nodes_block_crg_range::
_has_prototype = make_prototype();

bool
fiber_bundle::zone_nodes_block_crg_range::
make_prototype()
{
  // Preconditions:


  // Body:

  zone_nodes_block_crg_range* lproto = new zone_nodes_block_crg_range();

  range_factory().insert_prototype(lproto);

  // Postconditions:


  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::zone_nodes_block_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const zone_nodes_block_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::zone_nodes_block_crg_range*
fiber_bundle::zone_nodes_block_crg_range::
clone() const
{
  // Preconditions:

  // Body:

  zone_nodes_block_crg_range* result = new zone_nodes_block_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::zone_nodes_block_crg_range::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(homogeneous_block_crg_range::invariant());

    // Invariances for this class:

    invariance(dof_tuple_ids_initialized() ? block_dof_tuple_id().is_valid() : true);
    invariance(dof_tuple_ids_initialized() ? zone_dof_tuple_id().is_valid() : true);
    invariance(dof_tuple_ids_initialized() ? vertex_dof_tuple_id().is_valid() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const zone_nodes_block_crg_range& xr, bool xinclude_shallow)
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
