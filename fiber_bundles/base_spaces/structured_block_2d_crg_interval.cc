
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
/// Implementation for class structured_block_2d_crg_interval

#include "structured_block_2d_crg_interval.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "constant_index_space_interval.h"
#include "error_message.h"
#include "explicit_index_space_interval.h"
#include "factory.h"
#include "offset_index_space_handle.h"
#include "offset_index_space_state.h"
#include "list_index_space_handle.h"
#include "list_index_space_state.h"
#include "ij_adjacency_index_space_interval.h"
#include "ij_connectivity_index_space_interval.h"
#include "ij_product_structure.h"
#include "index_space_iterator.h"
#include "section_space_schema_member.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"
#include "structured_block_2d.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// STRUCTURED_BLOCK_2D_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block_2d_crg_interval::
structured_block_2d_crg_interval()
{
  _i_size = 0;
  _j_size = 0;

  _i_vertex_size = 0;
  _j_vertex_size = 0;

  _zone_begin = 0;
  _zone_size = 0;

  _vertex_begin = 0;
  _vertex_size = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::structured_block_2d_crg_interval::
~structured_block_2d_crg_interval()
{
  // Preconditions:

  // Body:

  if(is_valid(_lower_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_space(_lower_covers_begin);

    // Delete the zones interval.

    _id_spaces->delete_space(_lower_covers_begin + 1);

    // Delete the vertices interval.

    _id_spaces->delete_space(_lower_covers_begin + 1 + _zone_size);
  }

  if(is_valid(_upper_covers_begin))
  {
    // Delete the block interval.

    _id_spaces->delete_space(_upper_covers_begin);

    // Delete the zones interval.

    _id_spaces->delete_space(_upper_covers_begin + 1);

    // Delete the vertices interval.

    _id_spaces->delete_space(_upper_covers_begin + 1 + _zone_size);
  }

  // Postconditions:

  // Exit:

  return;
}

sheaf::size_type
fiber_bundle::structured_block_2d_crg_interval::
i_size() const
{
  return _i_size;
}

sheaf::size_type
fiber_bundle::structured_block_2d_crg_interval::
j_size() const
{
  return _j_size;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
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
fiber_bundle::structured_block_2d_crg_interval::
initialize_zones(base_space_poset& xhost)
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!zones_initialized());

  // Body:

  // Construct the zone id space.

  const string& lzone_id_space_name =
    section_space_schema_member::intersection_id_space_name(xhost.d_cells(2),
							    interval_member());

  _zones_space_id =
    offset_index_space_state::new_space(*_id_spaces,
					lzone_id_space_name,
					_zone_begin,
					_zone_size).index();

  _zones_initialized = true;

  // Construct the product structure for the zone id space.

  ij_product_structure lzone_structure(_i_size, _j_size);
  _id_spaces->new_product_structure(_zones_space_id, lzone_structure);

  // Postconditions:

  ensure(zones_initialized());
  ensure(id_spaces().has_product_structure(zones_space_id()));
  ensure(id_spaces().product_structure_conforms_to<ij_product_structure>(_zones_space_id));

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
fiber_bundle::structured_block_2d_crg_interval::
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

  // Construct the product structure for the vertex id space.

  ij_product_structure lvertex_structure(_i_vertex_size, _j_vertex_size);
  _id_spaces->new_product_structure(_vertices_space_id, lvertex_structure);

  // Postconditions:

  ensure(vertices_initialized());
  ensure(id_spaces().has_product_structure(vertices_space_id()));
  ensure(id_spaces().product_structure_conforms_to<ij_product_structure>(_vertices_space_id));

  // Exit:

  return;
}  

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

int
fiber_bundle::structured_block_2d_crg_interval::
db(pod_index_type xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  static const int ldb[MEMBER_CLASS_END] =
    {
      2, 2, 0
    };

  int result = ldb[member_class(xmbr_id)];

  // Postconditions:


  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::structured_block_2d_crg_interval::
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

  case 2:
    result = _zones_space_id;
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
fiber_bundle::structured_block_2d_crg_interval::
initialize_block_vertices()
{
  // Preconditions:

  require(!block_vertices_initialized());
  require(vertices_initialized());

  // Body:

  // Construct the block vertices id space.

  list_index_space_handle lblock_vertices_id_space =
     list_index_space_state::new_space(*_id_spaces,
				       block_vertices_name(),
				       false);

  _block_vertices_space_id = lblock_vertices_id_space.index();

  // Insert the private data into the id space.

  int I = i_size();
  int J = j_size();
  lblock_vertices_id_space.push_back(_vertex_begin);
  lblock_vertices_id_space.push_back(_vertex_begin + (J+1)*I);
  lblock_vertices_id_space.push_back(_vertex_begin + (J+1)*I + J);
  lblock_vertices_id_space.push_back(_vertex_begin + J);

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
fiber_bundle::structured_block_2d_crg_interval::
get_size(size_type xi_size, size_type xj_size, size_type& result)
{
  // Preconditions:


  // Body:

  size_type lzone_size   = xi_size*xj_size;
  size_type lvertex_size = (xi_size + 1)*(xj_size + 1);

  result = 1 + lzone_size + lvertex_size;

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
fiber_bundle::structured_block_2d_crg_interval::
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
  // all the zones.

  _lower_covers_begin =
    explicit_index_space_interval::new_space(*_id_spaces, 1).begin();

  offset_index_space_state::new_space(*_id_spaces,
				      _lower_covers_begin,
				      implicit_cover_name(LOWER, interval_member()),
				      _zone_begin,
				      _zone_size);

  // Construct the lower cover of the zones.
  //
  // The lower cover of the zones is initialized to the nodal connectivity.
  // The user may change the lower cover of the zones by using the explicit
  // overrides in crg_range.  However, the underlineing connectivity id space
  // interval will remain in the id space family.  For that reason, we can
  // set the connectivity begin to beginning of the connectivity id space
  // interval created below.

  _connectivity_begin =
    ij_connectivity_index_space_interval::new_space(*_id_spaces,
						    _zone_size,
						    _vertex_begin,
						    _j_size).begin();

  // Construct the lower cover of the vertices.
  //
  // The lower cover of the vertices is initialized to bottom.

  constant_index_space_interval::new_space(*_id_spaces,
					   _vertex_size,
					   BOTTOM_INDEX);

  // The lower cover is initialized.

  _lower_covers_initialized = true;

  // Posconditions:

  ensure(covers_initialized(LOWER));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_2d_crg_interval::
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

  // Construct the upper cover of the zones.
  //
  // The upper cover of the zones is initialized to the block.

  constant_index_space_interval::new_space(*_id_spaces,
					   _zone_size,
					   interval_member());

  // Construct the upper cover of the vertices.
  //
  // The upper cover of the vertices is initialized to the zonal adjacency.
  // The user may change the upper cover of the vertices by using the explicit
  // overrides in crg_range.  However, the underlineing adjacency id space
  // interval will remain in the id space family.  For that reason, we can
  // set the adjacency begin to the beginning of the adjacency id space
  // interval created below.

  _adjacency_begin =
    ij_adjacency_index_space_interval::new_space(*_id_spaces,
						 _vertex_size,
						 _zone_begin,
						 _i_size,
						 _j_size).begin();

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
fiber_bundle::structured_block_2d_crg_interval::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  block<pod_index_type>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = structured_block_2d::new_row_dof_map(xhost, xi_size, xj_size, true).hub_pod();
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "quad_nodes", true).hub_pod();
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
fiber_bundle::structured_block_2d_crg_interval::
get_private_data(size_type xi_size, size_type xj_size, block<pod_index_type>& result)
{
  // Preconditions:

  // Body:

  // There is no explicit private data.

  result.reserve(4);
  result.set_ct(4);

  result[0] = xi_size;
  result[1] = xj_size;
  result[2] = 0;
  result[3] = 0;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
fiber_bundle::structured_block_2d_crg_interval::
implicit_private_data_size() const
{
  return 2;
}

void
fiber_bundle::structured_block_2d_crg_interval::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  xdata.push_back(_i_size);
  xdata.push_back(_j_size);

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
fiber_bundle::structured_block_2d_crg_interval::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  // Body:

  _i_size = xdata[0];
  _j_size = xdata[1];

  _i_vertex_size = _i_size + 1;
  _j_vertex_size = _j_size + 1;

  _zone_begin = implicit_begin();
  _zone_size = _i_size*_j_size;

  _vertex_begin = _zone_begin + _zone_size;
  _vertex_size = _i_vertex_size*_j_vertex_size;

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
fiber_bundle::structured_block_2d_crg_interval::
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
fiber_bundle::structured_block_2d_crg_interval::
class_name() const
{
  static const string result("structured_block_2d_crg_interval");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::structured_block_2d_crg_interval::
make_prototype()
{
  // Preconditions:


  // Body:

  structured_block_2d_crg_interval* lproto = new structured_block_2d_crg_interval();

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
fiber_bundle::structured_block_2d_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const structured_block_2d_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::structured_block_2d_crg_interval*
fiber_bundle::structured_block_2d_crg_interval::
clone() const
{
  // Preconditions:

  // Body:

  structured_block_2d_crg_interval* result = new structured_block_2d_crg_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::structured_block_2d_crg_interval::
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
