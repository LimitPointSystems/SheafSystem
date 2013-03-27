// $RCSfile: point_block_crg_range.cc,v $ $Revision: 1.23 $ $Date: 2013/03/13 00:58:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class point_block_crg_range

#include "point_block_crg_range.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_index_space.h"
#include "cover_set_iterator.h"
#include "error_message.h"
#include "factory.h"
#include "list_index_space_state.h"
#include "index_space_iterator.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "section_space_schema_member.h"
#include "singleton_index_space_interval.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"
#include "ternary_index_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

namespace
{
const sheaf::size_type BLOCK_VERTICES_BEGIN = 2;
const sheaf::size_type EXPLICIT_PRIVATE_DATA_SIZE = 2;
}


// ===========================================================
// POINT_BLOCK_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::point_block_crg_range::
point_block_crg_range()
{
  /// @todo Remove.

//   // Add a reference to _block_vertices
//   // so it won't delete itself.

//   _block_vertices.add_reference();

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::point_block_crg_range::
~point_block_crg_range()
{
  // Nothing to do.
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

// PUBLIC DATA MEMBERS

/// @todo Remove.

// sheaf::cover_set_iterator
// fiber_bundle::point_block_crg_range::
// block_vertices() const
// {
//   // Preconditions:


//   // Body:

//   // Thee are no block_vertices.

//   cover_set_iterator result(_block_vertices);

//   // Postconditions:

//   // Postconditions:


//   // Exit:

//   return result;
// }

int
fiber_bundle::point_block_crg_range::
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

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


void
fiber_bundle::point_block_crg_range::
initialize_block_vertices_id_space(pod_index_type* xdata)
{
  // Preconditions:

  require(!block_vertices_initialized());

  // Body:

  arg_list largs = list_index_space_state::make_arg_list();

  pod_index_type lspace_id =
    _id_spaces->new_secondary_state(block_vertices_name(),
				    "list_index_space_state",
				    largs, false);

  _block_vertices_id_space.attach_to(id_spaces(), lspace_id);

  pod_index_type v = 0;
  size_type lbv_size = xdata[v++];
  for(size_type lbv=0; lbv<lbv_size; ++lbv)
  {
    _block_vertices_id_space.push_back(_local_id_space.hub_pod(xdata[v++]));
  }

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
fiber_bundle::point_block_crg_range::
get_size(size_type xi_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_ranges(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_range::
get_size(size_type xi_size, size_type xj_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size*xj_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_ranges(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_range::
get_size(size_type xi_size, size_type xj_size, size_type xk_size, size_type& result)
{
  // Preconditions:


  // Body:

  // xi_size, xj_size, and xk_size are number of "vertices"
  // in the array that points are arranged in.

  size_type lvertex_ct = xi_size*xj_size*xk_size;

  // Must be consistent with homogeneous_block::
  // initialize_cell_ranges(poset_state_handle&, size_type).

  result = 1 + lvertex_ct;

  // Postconditions:


  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER_SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

const sheaf::index_space_handle&
fiber_bundle::point_block_crg_range::
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
sheaf::implicit_crg_range::
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

// sheaf::index_space_handle&
// fiber_bundle::point_block_crg_range::
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

//     if(is_range_member(xmbr_index))
//     {
//       // xmbr_index is the block;
//       // lower cover is all the zones/vertices.

//       index_space_iterator& litr = _vertex_id_space.get_iterator();
//       while(!litr.is_done())
//       {
// 	lcover->push_back(litr.hub_pod());

// 	litr.next();
//       }
//       _vertex_id_space.release_iterator(litr);
//     }
//     else
//     {
//       // xmbr_index is a zone/vertex;
//       // lower cover is bottom.

//       lcover->push_back(BOTTOM_INDEX); // Unscoped.
//     }
//   }
//   else
//   {
//     // Upper cover

//     if(is_range_member(xmbr_index))
//     {
//       // xmbr_index is the block;
//       // upper cover is empty.
//       // Do nothing.
//     }
//     else
//     {
//       // xmbr_index is a zone/vertex;
//       // upper cover is block.

//       lcover->push_back(range_member());
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
fiber_bundle::point_block_crg_range::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  block<scoped_index>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_1d::new_row_dof_map(xhost, xi_size, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true);
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_range::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  block<scoped_index>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_2d::new_row_dof_map(xhost, xi_size, xj_size, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true);
  result[VERTEX] = base_space_member::new_row_dof_map(xhost, "point", true);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_range::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  size_type xk_size,
                  block<scoped_index>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = point_block_3d::new_row_dof_map(xhost, xi_size, xj_size, xk_size, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "point", true);
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
fiber_bundle::point_block_crg_range::
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
  // local vertex ids are in range [1, #vertices);
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
fiber_bundle::point_block_crg_range::
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
  // local vertex ids are in range [1, #vertices);
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
fiber_bundle::point_block_crg_range::
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
  // local vertex ids are in range [1, #vertices);
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

/// @todo Remove.

// sheaf::size_type
// fiber_bundle::point_block_crg_range::
// implicit_private_data_size() const
// {
//   return BLOCK_VERTICES_BEGIN + _block_vertices.size();
// }

sheaf::size_type
fiber_bundle::point_block_crg_range::
implicit_private_data_size() const
{
  return BLOCK_VERTICES_BEGIN + _block_vertices_id_space.ct();
}

/// @todo Remove.

// void
// fiber_bundle::point_block_crg_range::
// get_implicit_private_data(block<pod_index_type>& xdata) const
// {
//   // Preconditions:

//   // Body:

//   size_type lpd_size = _block_vertices.size() + BLOCK_VERTICES_BEGIN;

//   xdata.set_ct(lpd_size);

//   size_type v = 0;
//   xdata[v++] = _vertex_id_space.ct();
//   xdata[v++] = _block_vertices.size();

//   for(list_cover_set::const_iterator litr = _block_vertices.begin();
//       litr != _block_vertices.end();
//       ++litr)
//   {
//     xdata[v++] = _local_id_space.pod(*litr);
//   }


//   // Postconditions:

//   ensure(xdata.ct() == implicit_private_data_size());

//   // Exit:

//   return;
// }

void
fiber_bundle::point_block_crg_range::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  size_type lpd_size = _block_vertices_id_space.ct() + BLOCK_VERTICES_BEGIN;

  xdata.set_ct(lpd_size);

  size_type v = 0;
  xdata[v++] = _vertex_id_space.ct();
  xdata[v++] = _block_vertices_id_space.ct();

  index_space_iterator& litr = get_block_vertices_id_space_iterator();
  while(!litr.is_done())
  {
    xdata[v++] = _local_id_space.pod(litr.hub_pod());
    
    litr.next();
  }

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
fiber_bundle::point_block_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= implicit_private_data_size());
  require(!block_vertices_initialized());

  // Body:

  // Initialize private data.

  size_type v = 0;
  _vertex_ct = xdata[v++];

  initialize_block_vertices(&xdata[v]);

//   _block_vertices.clear();
//   size_type lbv_size = xdata[v++];
//   for(size_type lbv=0; lbv<lbv_size; ++lbv)
//   {
//     _block_vertices.push_back(_local_id_space.hub_pod(xdata[v++]));
//   }

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
fiber_bundle::point_block_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Compute the top ids for the cell ranges.

  pod_index_type lblock_id     = range_member();
  pod_index_type lvertex_begin = lblock_id + 1;

  // Construct the id space for the vertices.

  /// @todo Add product structure when point blocks private data provides
  /// enough information.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(0),
							    lblock_id);

  initialize_zone_vertex_id_space(lvertex_id_space_name, lvertex_begin, _vertex_ct);

  // Initialize the connectivity/adjacency id space interval.  Since the
  // zones are vertices the connectivity and adjacency are the same thing.

  arg_list largs = singleton_index_space_interval::make_arg_list(lvertex_begin);

  initialize_conn_adj_id_spaces("singleton_index_space_interval",
				largs, _vertex_ct);

  // Now this can be inserted in the standard subposets (d-cells, etc).

  lhost.insert_range_in_standard_subposets(*this);

  // Put atoms in upper cover of bottom.

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
fiber_bundle::point_block_crg_range::
class_name() const
{
  static const string result("point_block_crg_range");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::point_block_crg_range::
_has_prototype = make_prototype();

bool
fiber_bundle::point_block_crg_range::
make_prototype()
{
  // Preconditions:


  // Body:

  point_block_crg_range* lproto = new point_block_crg_range();

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
fiber_bundle::point_block_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const point_block_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::point_block_crg_range*
fiber_bundle::point_block_crg_range::
clone() const
{
  // Preconditions:

  // Body:

  point_block_crg_range* result = new point_block_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::point_block_crg_range::
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
deep_size(const point_block_crg_range& xr, bool xinclude_shallow)
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

