
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Implementation for class zone_nodes_block_crg_interval

#include "zone_nodes_block_crg_interval.h"

#include "arg_list.h"
#include "array_implicit_index_space_iterator.h"
#include "array_index_space_interval.h"
#include "assert_contract.h"
#include "block_connectivity.h"
#include "constant_index_space_interval.h"
#include "error_message.h"
#include "explicit_index_space_interval.h"
#include "factory.h"
#include "offset_index_space_handle.h"
#include "offset_index_space_state.h"
#include "list_index_space_handle.h"
#include "list_index_space_state.h"
#include "hash_index_space_handle.h"
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
// ZONE_NODES_BLOCK_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::zone_nodes_block_crg_interval::
zone_nodes_block_crg_interval()
{
  // Preconditions:

  // Body:

  _nodes_per_zone = 0;
  _zone_db = -1;
  _vertex_client_id_space_initialized = false;
  _vertex_client_space_id = invalid_pod_index();

  _zone_begin = 0;
  _zone_size = 0;

  _vertex_begin = 0;
  _vertex_size = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}


fiber_bundle::zone_nodes_block_crg_interval::
~zone_nodes_block_crg_interval()
{
  // Preconditions:

  // Body:

  if(is_valid(_lower_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_secondary_interval(_lower_covers_begin);

    // Delete the zones interval.

    _id_spaces->delete_secondary_interval(_lower_covers_begin + 1);

    // Delete the vertices interval.

    _id_spaces->delete_secondary_interval(_lower_covers_begin + 1 + _zone_size);
  }

  if(is_valid(_upper_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_secondary_interval(_upper_covers_begin);

    // Delete the zones interval.

    _id_spaces->delete_secondary_interval(_upper_covers_begin + 1);

    // Delete the vertices interval.

    _id_spaces->delete_secondary_interval(_upper_covers_begin + 1 + _zone_size);
  }

  if(is_valid(_vertex_client_space_id))
  {
    _id_spaces->delete_secondary_state(_vertex_client_space_id);
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

const string&
fiber_bundle::zone_nodes_block_crg_interval::
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
fiber_bundle::zone_nodes_block_crg_interval::
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

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTEX CLIENT ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::zone_nodes_block_crg_interval::
vertex_client_id_space_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _vertex_client_id_space_initialized;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::zone_nodes_block_crg_interval::
vertex_client_space_id() const
{
  // Preconditions:

  require(vertex_client_id_space_initialized());

  // Body:

  pod_index_type result = _vertex_client_space_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

string
fiber_bundle::zone_nodes_block_crg_interval::
vertex_client_id_space_name()
{
  // Preconditions:

  // Body:

  string result(poset_path::make_reserved_name("", interval_member(), "_vertex_client_ids"));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

void
fiber_bundle::zone_nodes_block_crg_interval::
initialize_vertex_client_id_space(block_adjacency& xadjacency)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());

  // Body:

  pod_index_type lzone_begin = implicit_begin();

  string lname = vertex_client_id_space_name();

  // Create the id space.

  mutable_index_space_handle lclient_id_space =
    hash_index_space_state::new_space(*_id_spaces,
				      lname,
				      false,
				      xadjacency.node_ct());

  // Populate the id space.

  pod_index_type lhub_vertex_id = lzone_begin + xadjacency.zone_ct();
  typedef block_adjacency::const_node_iterator_type node_itr_type;

  for(node_itr_type v = xadjacency.begin(); v != xadjacency.end(); ++v)
  {
    lclient_id_space.insert(v->first, lhub_vertex_id);
    ++lhub_vertex_id;
  }

  assertion(lhub_vertex_id == lzone_begin + xadjacency.zone_ct() + xadjacency.node_ct());

  _vertex_client_id_space_initialized = true;

  // Postconditions:

  ensure(vertex_client_id_space_initialized());
  ensure(id_spaces().ct(vertex_client_space_id()) == _vertex_size);

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ZONES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_interval::
initialize_zones(base_space_poset& xhost)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!zones_initialized());

  // Body:

  // Construct the zone id space.

  const string& lzone_id_space_name =
    section_space_schema_member::intersection_id_space_name(xhost.d_cells(_zone_db), interval_member());

  _zones_space_id =
    offset_index_space_state::new_space(*_id_spaces,
					lzone_id_space_name,
					_zone_begin,
					_zone_size).index();

  _zones_initialized = true;

  // Postconditions:

  ensure(zones_initialized());

  // Exit:

  return;
}  

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTICES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_interval::
initialize_vertices(base_space_poset& xhost)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!vertices_initialized());

  // Body:

  // Construct the vertex id space.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(xhost.d_cells(0),
							    interval_member());

  _vertices_space_id =
    offset_index_space_state::new_space(*_id_spaces,
					lvertex_id_space_name,
					_vertex_begin,
					_vertex_size).index();

  _vertices_initialized = true;

  // Postconditions:

  ensure(vertices_initialized());

  // Exit:

  return;
}  

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_CRG_INTERVAL FACET
// ===========================================================

int
fiber_bundle::zone_nodes_block_crg_interval::
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

sheaf::pod_index_type
fiber_bundle::zone_nodes_block_crg_interval::
d_cells_space_id(int xd) const
{
  // Preconditions:

  // Body:

  pod_index_type result;

  if(xd == 0)
  {
    result = _vertices_space_id;
  }
  else if(xd == _zone_db)
  {
    result = _zones_space_id;
  }
  else
  {
    result = invalid_pod_index();
  }

  // Postconditions:

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
fiber_bundle::zone_nodes_block_crg_interval::
initialize_block_vertices()
{
  // Preconditions:

  require(!block_vertices_initialized());
  require(vertices_initialized());

  // Body:

  _block_vertices_space_id =
     list_index_space_state::new_space(*_id_spaces,
				       block_vertices_name(),
				       false).index();

  // Block vertices id space is empty.

  _block_vertices_initialized = true;

  // Postconditions:

  ensure(block_vertices_initialized());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_interval::
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

void
fiber_bundle::zone_nodes_block_crg_interval::
initialize_lower_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(LOWER));

  // Body:

  // Construct the lower cover of the block.
  //
  // The lower cover of the block is initialized to an id space that contains
  // all the zones.  The initial value is the same as the zone id.

  _lower_covers_begin =
    _id_spaces->new_secondary_interval("explicit_index_space_interval",
				       explicit_index_space_interval::make_arg_list(),
				       1);

  offset_index_space_state::new_space(*_id_spaces,
				      implicit_cover_name(LOWER, interval_member()),
				      _zone_begin,
				      _zone_size);

  // Construct the lower cover of the zones.
  //
  // The lower cover of the zones is initialized to the nodal connectivity.
  // The user may change the lower cover of the zones by using the explicit
  // overrides in crg_range.  However, the underlineing connectivity id space
  // interval will remain in the id space family.  For that reason, we can
  // set use the interval created below as the connectivity id space interval.

  arg_list largs = array_index_space_interval::make_arg_list(_connectivity,
							     _nodes_per_zone,
							     false);

  _connectivity_begin =
    _id_spaces->new_secondary_interval("array_index_space_interval",
				       largs, _zone_size);
				     

  // Construct the lower cover of the vertices.
  //
  // The lower cover of the vertices is initialized to bottom.

  largs = constant_index_space_interval::make_arg_list(BOTTOM_INDEX);

  _id_spaces->new_secondary_interval("constant_index_space_interval",
				     largs, _vertex_size);

  // The lower cover is initialized.

  _lower_covers_initialized = true;

  // Posconditions:

  ensure(covers_initialized(LOWER));

  // Exit:

  return;
}

void
fiber_bundle::zone_nodes_block_crg_interval::
initialize_upper_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(UPPER));

  // Body:

  // Construct the upper cover of the block
  //
  // The upper cover of block is initialized to an empty explicit id space.

  _upper_covers_begin =
    _id_spaces->new_secondary_interval("explicit_index_space_interval",
				       explicit_index_space_interval::make_arg_list(),
				       1);  

  list_index_space_state::new_space(*_id_spaces,
				    explicit_cover_name(UPPER, interval_member()),
				    false);

  // Construct the upper cover of the zones.
  //
  // The upper cover of the zones is initialized to the block.

  arg_list largs = constant_index_space_interval::make_arg_list(interval_member());

  _id_spaces->new_secondary_interval("constant_index_space_interval",
				     largs, _zone_size);

  // Construct the upper cover of the vertices.
  //
  // The upper cover of the vertices is initialized to the zonal adjacency.
  // The user may change the upper cover of the vertices by using the explicit
  // overrides in crg_range.  However, the underlineing adjacency id space
  // interval will remain in the id space family.  For that reason, we can
  // the interval created below as the adjacency interval.

  largs = ragged_array_index_space_interval::make_arg_list(_adjacency, false);

  _adjacency_begin =
    _id_spaces->new_secondary_interval("ragged_array_index_space_interval",
				       largs, _vertex_size);

  // The upper cover is initialized.

  _upper_covers_initialized = true;

  // Posconditions:

  ensure(covers_initialized(UPPER));

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::zone_nodes_block_crg_interval::
get_dof_tuple_ids(poset_state_handle& xhost,
                  const block_connectivity& xconn,
                  block<pod_index_type>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);

  string lname = zone_prototype_name(xconn);
  size_type lzone_ct = xconn.element_ct();

  result[BLOCK]  =
    homogeneous_block::new_row_dof_map(xhost, "unstructured_block", lname, lzone_ct, true).hub_pod();
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, lname, true).hub_pod();
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();

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
fiber_bundle::zone_nodes_block_crg_interval::
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
fiber_bundle::zone_nodes_block_crg_interval::
implicit_private_data_size() const
{
  return _zone_size*_nodes_per_zone + NODE_IDS_BEGIN;
}

void
fiber_bundle::zone_nodes_block_crg_interval::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  size_type lconn_size = _zone_size*_nodes_per_zone;

  size_type lpd_size = lconn_size + NODE_IDS_BEGIN;
  xdata.set_ct(lpd_size);

  size_type j=0;
  xdata[j++] = _zone_db; // xdata[0]
  xdata[j++] = _zone_size; // xdata[1]
  xdata[j++] = _nodes_per_zone; // xdata[2]
  xdata[j++] = lconn_size; // xdata[3]

  mutable_index_space_handle& lclient_id_space =
    _id_spaces->get_id_space<mutable_index_space_handle>(_vertex_client_space_id);  

  for(pod_index_type i = 0; i < lconn_size; ++i)
  {
    xdata[j++] = lclient_id_space.pod(_connectivity[i]);
  }

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());
  ensure(unexecutable("node ids are clients ids"));

  // Exit:

  return;
}

void
fiber_bundle::zone_nodes_block_crg_interval::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata[3] == xdata[1]*xdata[2]);
  require(xdata.ct() > NODE_IDS_BEGIN);
  require(xdata.ct() >= xdata[3] + NODE_IDS_BEGIN);

  // Body:

  pod_index_type j=0;

  _zone_db = xdata[j++];
  _zone_size = xdata[j++];
  _nodes_per_zone = xdata[j++];

  size_type lconn_ct = xdata[j++];

  // Initialize the zone and vertex offsets into the hub id space.

  _zone_begin = implicit_begin();
  _vertex_begin = _zone_begin + _zone_size;

  // Construct a block adjacency object.

  block_adjacency ladjacency(_zone_size, _nodes_per_zone,
			     lconn_ct, &xdata[j]);

  // Initialize the number of vertices.

  _vertex_size = ladjacency.node_ct();

  // Initialize the vertex client id space.

  initialize_vertex_client_id_space(ladjacency);

  // Initialize the connectivity array.  This array is passed to
  // the array interval when constructing the lower cover of the
  // zones.

  mutable_index_space_handle& lclient_id_space =
    _id_spaces->get_id_space<mutable_index_space_handle>(_vertex_client_space_id);

  _connectivity.reserve(lconn_ct);
  _connectivity.set_ct(lconn_ct);

  for(pod_index_type i = 0; i < lconn_ct; i++)
  {
    _connectivity[i] = lclient_id_space.hub_pod(xdata[j++]);
  }

  _id_spaces->release_id_space(lclient_id_space);

  // Initialize the adjacency array.  This array is passed to
  // the ragged array interval when constructing the upper cover
  // of the vertices.

  typedef block_adjacency::const_node_iterator_type node_itr_type;
  typedef block_adjacency::const_zone_iterator_type zone_itr_type;

  node_itr_type v = ladjacency.begin();

  while(v != ladjacency.end())
  {
    for(zone_itr_type z = v->second.begin(); z != v->second.end(); ++z)
    {
      _adjacency.push_back((*z) + _zone_begin);
    }

    // Increment to the next vertex

    ++v;

    if(v != ladjacency.end())
    {
      _adjacency.new_back_row();
    }
  }

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
fiber_bundle::zone_nodes_block_crg_interval::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Initialize the zone id space.

  initialize_zones(lhost);

  // Initialize the vertex id space.

  initialize_vertices(lhost);

  // Initialize the block vertices id space.

  initialize_block_vertices();

  // Initialize the cover id spaces.

  initialize_covers();

  // Now this can be inserted in the standard subposets (d-cells, etc).

  lhost.insert_interval_in_standard_subposets(*this);

  // Insert the vertices into the upper cover of bottom.

  xhost.append_upper_cover_of_bottom(_vertex_begin,
				     _vertex_begin + _vertex_size);

  homogeneous_block_crg_interval::finalize(xhost);

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
fiber_bundle::zone_nodes_block_crg_interval::
class_name() const
{
  static const string result("zone_nodes_block_crg_interval");
  return result;
}

bool
fiber_bundle::zone_nodes_block_crg_interval::
is_initialized() const
{
  bool result =
    homogeneous_block_crg_interval::is_initialized() &&
    _vertex_client_id_space_initialized;

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::zone_nodes_block_crg_interval::
make_prototype()
{
  // Preconditions:


  // Body:

  zone_nodes_block_crg_interval* lproto = new zone_nodes_block_crg_interval();

  interval_factory().insert_prototype(lproto);

  // Postconditions:


  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::zone_nodes_block_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const zone_nodes_block_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::zone_nodes_block_crg_interval*
fiber_bundle::zone_nodes_block_crg_interval::
clone() const
{
  // Preconditions:

  // Body:

  zone_nodes_block_crg_interval* result = new zone_nodes_block_crg_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::zone_nodes_block_crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(homogeneous_block_crg_interval::invariant());

    // Invariances for this class:

    invariance(dof_tuple_ids_initialized() ? is_valid(block_dof_tuple_id()) : true);
    invariance(dof_tuple_ids_initialized() ? is_valid(zone_dof_tuple_id()) : true);
    invariance(dof_tuple_ids_initialized() ? is_valid(vertex_dof_tuple_id()) : true);

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

