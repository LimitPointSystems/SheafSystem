
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
/// Implementation for class point_block_crg_interval

#include "SheafSystem/point_block_crg_interval.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/binary_index_space.h"
#include "SheafSystem/constant_index_space_interval.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/explicit_index_space_interval.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/list_index_space_handle.h"
#include "SheafSystem/list_index_space_state.h"
#include "SheafSystem/offset_index_space_handle.h"
#include "SheafSystem/offset_index_space_state.h"
#include "SheafSystem/point_block_1d.h"
#include "SheafSystem/point_block_2d.h"
#include "SheafSystem/point_block_3d.h"
#include "SheafSystem/section_space_schema_member.h"
#include "SheafSystem/singleton_index_space_interval.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/std_string.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/ternary_index_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

namespace
{
const sheaf::size_type BLOCK_VERTICES_BEGIN = 2;
const sheaf::size_type EXPLICIT_PRIVATE_DATA_SIZE = 2;
}


// ===========================================================
// POINT_BLOCK_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::point_block_crg_interval::
point_block_crg_interval()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  // Exit:

  return;
}

fiber_bundle::point_block_crg_interval::
~point_block_crg_interval()
{
  // Preconditions:

  // Body:

  if(is_valid(_lower_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_space(_lower_covers_begin);

    // Delete the vertices interval.

    _id_spaces->delete_space(_lower_covers_begin + 1);
  }

  if(is_valid(_upper_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_space(_upper_covers_begin);

    // Delete the vertices interval.

    _id_spaces->delete_space(_upper_covers_begin + 1);
  }

  if(is_valid(_connectivity_begin))
  {
    // Delete the connectivity interval.

    _id_spaces->delete_space(_connectivity_begin);
  }

  // For efficiency, the connectivity and adjacency id space interval
  // are the same interval.  Deleting the connectivity interval also
  // deletes the adjacency interval.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

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

// PRIVATE DATA MEMBERS


// ===========================================================
// ZONES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTICES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
fiber_bundle::point_block_crg_interval::
initialize_vertices(base_space_poset& xhost)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!vertices_initialized());
  require(!zones_initialized());

  // Body:

  // Construct the vertex id space.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(xhost.d_cells(0),
							    interval_member());

  _vertices_space_id =
    offset_index_space_state::new_space(*_id_spaces,
					lvertex_id_space_name,
					implicit_begin(),
					_vertex_size).index();

  _vertices_initialized = true;
  
  // Zones and vertices are the same id space.

  _zones_space_id = _vertices_space_id;

  _zones_initialized = true;

  // Postconditions:

  ensure(vertices_initialized());
  ensure(zones_initialized());

  // Exit:

  return;
}  

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

int
fiber_bundle::point_block_crg_interval::
db(pod_index_type xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  int result = 0;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::point_block_crg_interval::
d_cells_space_id(int xd) const
{
  // Preconditions:

  // Body:

  pod_index_type result;

  switch(xd)
  {
  case 0:
    result = _vertices_space_id;
    break;

  default:
    result = invalid_pod_index();
    break;
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
fiber_bundle::point_block_crg_interval::
initialize_block_vertices(pod_index_type* xdata)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(!block_vertices_initialized());

  // Body:

  // Construct the block vertices id space.

  list_index_space_handle lblock_vertices_id_space =
     list_index_space_state::new_space(*_id_spaces,
				       block_vertices_name(),
				       false);

  _block_vertices_space_id = lblock_vertices_id_space.index();

  // Insert the private data into the id space.

  pod_index_type v = 0;
  size_type lbv_size = xdata[v++];
  for(size_type lbv=0; lbv<lbv_size; ++lbv)
  {
    lblock_vertices_id_space.push_back(_local_id_space.hub_pod(xdata[v++]));
  }

  // The block vertices is initialized.

  _block_vertices_initialized = true;

  // Postconditions:

  ensure(block_vertices_initialized());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// IMPLICIT_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::point_block_crg_interval::
get_size(size_type xi_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_intervals(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_size(size_type xi_size, size_type xj_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size*xj_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_intervals(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_size(size_type xi_size, size_type xj_size, size_type xk_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size*xj_size*xk_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_intervals(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

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
fiber_bundle::point_block_crg_interval::
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
  // all the points.

  _lower_covers_begin =
    explicit_index_space_interval::new_space(*_id_spaces, 1).begin();

  offset_index_space_state::new_space(*_id_spaces,
				      _lower_covers_begin,
				      implicit_cover_name(LOWER, interval_member()),
				      implicit_begin(),
				      _vertex_size);

  // Construct the lower cover of the vertices.
  //
  // The lower cover of the vertices is initialized to bottom.

  constant_index_space_interval::new_space(*_id_spaces, _vertex_size, BOTTOM_INDEX);

  // Construct the connectivity and adjacency id spaces.  The connectivity
  // and adjacency id spaces are identical.  Since a point is both a zone
  // and vertex.  The connectivity and adjacency id spaces are id spaces
  // with a single member that maps to itself.  For efficiency, only one
  // id space interval will be created for both the connectivity and
  // adjacency id spaces.

  _connectivity_begin =
    singleton_index_space_interval::new_space(*_id_spaces, _vertex_size, implicit_begin()).begin();

  _adjacency_begin = _connectivity_begin;

  // The lower cover is initialized.

  _lower_covers_initialized = true;

  // Posconditions:

  ensure(covers_initialized(LOWER));

  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
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
    explicit_index_space_interval::new_space(*_id_spaces, 1).begin();

  list_index_space_state::new_space(*_id_spaces,
				    _upper_covers_begin,
				    explicit_cover_name(UPPER, interval_member()),
				    false);

  // Construct the upper cover of the points.
  //
  // The upper cover of the points is initialized to the block.

  constant_index_space_interval::new_space(*_id_spaces, _vertex_size, interval_member());

  // The adjacency id spaces are contructed in initialize_lower_covers.

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
fiber_bundle::point_block_crg_interval::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  block<pod_index_type>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_1d::new_row_dof_map(xhost, xi_size, true).hub_pod();
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  block<pod_index_type>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_2d::new_row_dof_map(xhost, xi_size, xj_size, true).hub_pod();
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  size_type xk_size,
                  block<pod_index_type>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_3d::new_row_dof_map(xhost, xi_size, xj_size, xk_size, true).hub_pod();
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true).hub_pod();
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
fiber_bundle::point_block_crg_interval::
get_private_data(size_type xi_size, block<pod_index_type>& result)
{
  // Preconditions:

  require(xi_size > 0);

  // Body:

  size_type lblock_vertices_size = 2;
  size_type lpd_size = lblock_vertices_size + BLOCK_VERTICES_BEGIN + EXPLICIT_PRIVATE_DATA_SIZE;

  result.reserve(lpd_size);
  result.set_ct(lpd_size);

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_i_size = xi_size;

  size_type v = 0;
  result[v++] = lvertex_i_size;
  result[v++] = lblock_vertices_size;

  // Add block vertex ids.

  // block vertices are local ids;
  // local vertex ids are in interval [1, #vertices);
  // so calculate ids using usual array indexing, then add 1.

  result[v++] = 1;
  result[v++] = xi_size;

  // There are no explicit covers.

  result[v++] = 0;
  result[v++] = 0;

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_private_data(size_type xi_size,
                 size_type xj_size,
                 block<pod_index_type>& result)
{
  // Preconditions:

  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  size_type lblock_vertices_size = 4;
  size_type lpd_size = lblock_vertices_size + BLOCK_VERTICES_BEGIN + EXPLICIT_PRIVATE_DATA_SIZE;

  result.reserve(lpd_size);
  result.set_ct(lpd_size);

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_i_size = xi_size;
  size_type lvertex_j_size = xj_size;

  size_type v = 0;
  result[v++] = lvertex_i_size*lvertex_j_size;
  result[v++] = lblock_vertices_size;

  binary_index_space lid_space(lvertex_i_size, lvertex_j_size);

  // block vertices are local ids;
  // local vertex ids are in interval [1, #vertices);
  // so calculate ids using usual array indexing, then add 1.

  result[v++] = lid_space.to_row_major_offset(0,         0) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, 0) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, xj_size-1) + 1;
  result[v++] = lid_space.to_row_major_offset(0,         xj_size-1) + 1;

  // There are no explicit covers.

  result[v++] = 0;
  result[v++] = 0;

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
get_private_data(size_type xi_size,
                 size_type xj_size,
                 size_type xk_size,
                 block<pod_index_type>& result)
{
  // Preconditions:

  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  size_type lblock_vertices_size = 8;
  size_type lpd_size = lblock_vertices_size + BLOCK_VERTICES_BEGIN + EXPLICIT_PRIVATE_DATA_SIZE;

  result.reserve(lpd_size);
  result.set_ct(lpd_size);

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_i_size = xi_size;
  size_type lvertex_j_size = xj_size;
  size_type lvertex_k_size = xk_size;

  size_type v = 0;
  result[v++] = lvertex_i_size*lvertex_j_size*lvertex_k_size;
  result[v++] = lblock_vertices_size;

  ternary_index_space lid_space(lvertex_i_size, lvertex_j_size, lvertex_k_size);

  // block vertices are local ids;
  // local vertex ids are in interval [1, #vertices);
  // so calculate ids using usual array indexing, then add 1.

  result[v++] = lid_space.to_row_major_offset(0,         0,         0) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, 0,         0) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, xj_size-1, 0) + 1;
  result[v++] = lid_space.to_row_major_offset(0,         xj_size-1, 0) + 1;

  result[v++] = lid_space.to_row_major_offset(0,         0,         xk_size-1) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, 0,         xk_size-1) + 1;
  result[v++] = lid_space.to_row_major_offset(xi_size-1, xj_size-1, xk_size-1) + 1;
  result[v++] = lid_space.to_row_major_offset(0,         xj_size-1, xk_size-1) + 1;

  // There are no explicit covers.

  result[v++] = 0;
  result[v++] = 0;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
fiber_bundle::point_block_crg_interval::
implicit_private_data_size() const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  size_type result =
    BLOCK_VERTICES_BEGIN + _id_spaces->ct(_block_vertices_space_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::point_block_crg_interval::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  size_type lbv_size = _id_spaces->ct(_block_vertices_space_id);

  size_type lpd_size = lbv_size + BLOCK_VERTICES_BEGIN;

  xdata.set_ct(lpd_size);

  size_type v = 0;
  xdata[v++] = _vertex_size;
  xdata[v++] = lbv_size;

  index_space_iterator& litr = _id_spaces->get_id_space_iterator(_block_vertices_space_id);
  while(!litr.is_done())
  {
    xdata[v++] = _local_id_space.pod(litr.hub_pod());
    
    litr.next();
  }
  _id_spaces->release_id_space_iterator(litr);

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_interval::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(!block_vertices_initialized());

  // Body:

  // Initialize private data.

  size_type v = 0;
  _vertex_size = xdata[v++];

  initialize_block_vertices(&xdata[v]);

  // Postconditions:

  ensure(invariant());
  ensure(block_vertices_initialized());

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// FINIALIZE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::point_block_crg_interval::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Compute the top ids for the cell intervals.

  pod_index_type lvertex_begin = interval_member() + 1;
  pod_index_type lvertex_end   = lvertex_begin + _vertex_size;

  // Initialize zones and vertex id spaces.

  initialize_vertices(lhost);

  // Initialize the cover id spaces.

  initialize_covers();

  // Now this can be inserted in the standard subposets (d-cells, etc).

  lhost.insert_interval_in_standard_subposets(*this);

  // Insert the vertices into the upper cover of bottom.

  xhost.append_upper_cover_of_bottom(lvertex_begin, lvertex_end);

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

const std::string&
fiber_bundle::point_block_crg_interval::
class_name() const
{
  static const string result("point_block_crg_interval");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::point_block_crg_interval::
make_prototype()
{
  // Preconditions:


  // Body:

  point_block_crg_interval* lproto = new point_block_crg_interval();

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
fiber_bundle::point_block_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const point_block_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::point_block_crg_interval*
fiber_bundle::point_block_crg_interval::
clone() const
{
  // Preconditions:

  // Body:

  point_block_crg_interval* result = new point_block_crg_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::point_block_crg_interval::
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



