// $RCSfile: structured_block_3d_crg_range.cc,v $ $Revision: 1.25 $ $Date: 2013/03/13 00:58:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class structured_block_3d_crg_range.

#include "structured_block_3d_crg_range.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "factory.h"
#include "ijk_adjacency_index_space_interval.h"
#include "ijk_connectivity_index_space_interval.h"
#include "ijk_product_structure.h"
#include "index_space_iterator.h"
#include "section_space_schema_member.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"
#include "structured_block_3d.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// STRUCTURED_BLOCK_3D_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block_3d_crg_range::
structured_block_3d_crg_range()
{
  _i_size = 0;
  _j_size = 0;
  _k_size = 0;
  _jk_size = 0;

  _i_vertex_size = 0;
  _j_vertex_size = 0;
  _k_vertex_size = 0;
  _jk_vertex_size = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::structured_block_3d_crg_range::
~structured_block_3d_crg_range()
{
  // Nothing to do.
}

sheaf::size_type
fiber_bundle::structured_block_3d_crg_range::
i_size() const
{
  return _i_size;
}

sheaf::size_type
fiber_bundle::structured_block_3d_crg_range::
j_size() const
{
  return _j_size;
}

sheaf::size_type
fiber_bundle::structured_block_3d_crg_range::
k_size() const
{
  return _k_size;
}


// PROTECTED DATA MEMBERS

sheaf::pod_index_type 
fiber_bundle::structured_block_3d_crg_range::
vertex_id(pod_index_type xi, pod_index_type xj, pod_index_type xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi <= i_size()));
  require((0 <= xj) && (xj <= j_size()));
  require((0 <= xk) && (xk <= k_size()));

  // Body:

  pod_index_type result =
    (xi*_j_vertex_size + xj)*_k_vertex_size + xk + _vertex_id_space.offset();

  // Postconditions:

  ensure(vertex_id_space().contains_hub(result));

  // Exit:

  return result;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ZONE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::ijk_product_structure&
fiber_bundle::structured_block_3d_crg_range::
zone_product_structure() const
{
  // Preconditions:

  require(zones_initialized());
  require(zone_id_space().has_product_structure());
  require(zone_id_space().product_structure_conforms_to<ijk_product_structure>());

  // Body:

  const ijk_product_structure& result =
    _zone_id_space.product_structure<ijk_product_structure>();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTEX FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::ijk_product_structure&
fiber_bundle::structured_block_3d_crg_range::
vertex_product_structure() const
{
  // Preconditions:

  require(vertices_initialized());
  require(vertex_id_space().has_product_structure());
  require(vertex_id_space().product_structure_conforms_to<ijk_product_structure>());

  // Body:

  const ijk_product_structure& result =
    _vertex_id_space.product_structure<ijk_product_structure>();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

/// @todo Remove.

// // cover_set_iterator
// structured_block_3d_crg_range::
// block_vertices()
// {
//   // Preconditions:


//   // Body:

///   /// @todo replace with specialized iterator, when available

//   list_cover_set* lcover = new list_cover_set;

//   int I = i_size();
//   int J = j_size();
//   int K = k_size();

//   scoped_index::pod_type lvertex_begin = _vertex_begin.pod();
//   scoped_index lv_id(_local_index); // In local id space.

///   /// @error this order does not result
///   /// in proper client ids for block vertices;
///   /// see base_space_poset::insert_range_in_stard_subposets
///   /// and compare with old implementation of structured_block_3d.

//   // (0,0,0)

//   lv_id = lvertex_begin;
//   lcover->push_back(lv_id);

//   // (I,0,0)

//   lv_id = lvertex_begin + K;
//   lcover->push_back(lv_id);

//   // (I,J,0)

//   lv_id = lvertex_begin + (K+1)*J;
//   lcover->push_back(lv_id);

//   // (0,J,0)

//   lv_id = lvertex_begin + (K+1)*J + K;
//   lcover->push_back(lv_id);

//   lv_id = lvertex_begin + (K+1)*((J+1)*I);
//   lcover->push_back(lv_id);

//   lv_id = lvertex_begin + (K+1)*((J+1)*I) + K;
//   lcover->push_back(lv_id);

//   lv_id = lvertex_begin + (K+1)*((J+1)*I + J);
//   lcover->push_back(lv_id);

//   lv_id = lvertex_begin + (K+1)*((J+1)*I + J) + K;
//   lcover->push_back(lv_id);

//   cover_set_iterator result(*lcover);

//   // Postconditions:


//   // Exit:

//   return result;
// }

// sheaf::cover_set_iterator
// fiber_bundle::structured_block_3d_crg_range::
// block_vertices() const
// {
//   // Preconditions:


//   // Body:

//   /// @todo replace with specialized iterator, when available

//   list_cover_set* lcover = new list_cover_set(0);
//   lcover->put_is_implicit(true);

//   // Max values for i,j,k, respectively.

//   int I = i_size();
//   int J = j_size();
//   int K = k_size();

//   pod_index_type lvertex_begin = _vertex_id_space.offset();

//   // (0,0,0); client id 0

//   lcover->push_back(lvertex_begin);

//   // (I,0,0); client id 1.

//   lcover->push_back(vertex_id(I, 0, 0));

//   // (I,J,0); client id 2.

//   lcover->push_back(vertex_id(I, J, 0));

//   // (0,J,0); client id 3;

//   lcover->push_back(vertex_id(0, J, 0));

//   // (0,0,K); client id 4

//   lcover->push_back(vertex_id(0, 0, K));

//   // (I,0,K); client id 5.

//   lcover->push_back(vertex_id(I, 0, K));

//   // (I,J,K); client id 6.

//   lcover->push_back(vertex_id(I, J, K));

//   // (0,J,K); client id 7;

//   lcover->push_back(vertex_id(0, J, K));

//   cover_set_iterator result(*lcover);

//   // Postconditions:


//   // Exit:

//   return result;
// }

// int
// fiber_bundle::structured_block_3d_crg_range::
// db(pod_index_type xmbr_id) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_id));

//   // Body:

//   static const int ldb[MEMBER_CLASS_END] =
//     {
//       3, 3, 0
//     };

//   int result = ldb[member_class(xmbr_id)];

//   // Postconditions:


//   // Exit:

//   return result;
// }

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

  pod_index_type lvertex_begin = _vertex_id_space.offset();

  int I = i_size();
  int J = j_size();
  int K = k_size();

  pod_index_type lvertex_begin = _vertex_id_space.offset();

  // (0,0,0); client id 0

  _block_vertices_id_space.push_back(lvertex_begin);

  // (I,0,0); client id 1.

  _block_vertices_id_space.push_back(vertex_id(I, 0, 0));

  // (I,J,0); client id 2.

  _block_vertices_id_space.push_back(vertex_id(I, J, 0));

  // (0,J,0); client id 3;

  _block_vertices_id_space.push_back(vertex_id(0, J, 0));

  // (0,0,K); client id 4

  _block_vertices_id_space.push_back(vertex_id(0, 0, K));

  // (I,0,K); client id 5.

  _block_vertices_id_space.push_back(vertex_id(I, 0, K));

  // (I,J,K); client id 6.

  _block_vertices_id_space.push_back(vertex_id(I, J, K));

  // (0,J,K); client id 7;

  _block_vertices_id_space.push_back(vertex_id(0, J, K));

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
fiber_bundle::structured_block_3d_crg_range::
get_size(size_type xi_size, size_type xj_size, size_type xk_size, size_type& result)
{
  // Preconditions:


  // Body:

  size_type lzone_size   = xi_size*xj_size*xk_size;
  size_type lvertex_size = (xi_size + 1)*(xj_size + 1)*(xk_size + 1);

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

const sheaf::index_space_handle&
sheaf::structured_block_3d_crg_range::
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
sheaf::structured_block_3d_crg_range::
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
// fiber_bundle::structured_block_3d_crg_range::
// implicit_cover_iterator(bool xlower, pod_index_type xmbr_index) const
// {
//   // Preconditions:

//   require(contains_member(xmbr_index));

//   // Body:

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
//       }
//       break;

//     case ZONE:
//       {
//         lcover->push_back(range_member());
//       }
//       break;

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
fiber_bundle::structured_block_3d_crg_range::
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


  result[BLOCK]  = structured_block_3d::new_row_dof_map(xhost, xi_size, xj_size, xk_size, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "hex_nodes", true);
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
fiber_bundle::structured_block_3d_crg_range::
get_private_data(size_type xi_size,
                 size_type xj_size,
                 size_type xk_size,
                 block<pod_index_type>& result)
{
  // Preconditions:

  // Body:

  result.reserve(5);
  result.set_ct(5);

  result[0] = xi_size;
  result[1] = xj_size;
  result[2] = xk_size;
  result[3] = 0;
  result[4] = 0;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

sheaf::size_type
fiber_bundle::structured_block_3d_crg_range::
implicit_private_data_size() const
{
  return 3;
}

void
fiber_bundle::structured_block_3d_crg_range::
get_implicit_private_data(block<pod_index_type>& xdata) const
{
  // Preconditions:

  // Body:

  xdata.push_back(_i_size);
  xdata.push_back(_j_size);
  xdata.push_back(_k_size);

  // Postconditions:

  ensure(xdata.ct() == implicit_private_data_size());

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= implicit_private_data_size());

  // Body:

  _i_size = xdata[0];
  _j_size = xdata[1];
  _k_size = xdata[2];

  _jk_size = _j_size*_k_size;

  _i_vertex_size = _i_size + 1;
  _j_vertex_size = _j_size + 1;
  _k_vertex_size = _k_size + 1;
  _jk_vertex_size = _j_vertex_size*_k_vertex_size;

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
fiber_bundle::structured_block_3d_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Compute the top ids for the cell ranges.

  size_type lzone_ct = _i_size*_j_size*_k_size;
  size_type lvertex_ct = _i_vertex_size*_j_vertex_size*_k_vertex_size;

  pod_index_type lblock_id     =  range_member();
  pod_index_type lzone_begin   = lblock_id + 1;
  pod_index_type lvertex_begin = lzone_begin + lzone_ct;
 
  // Construct the id space and product structure for the zones.

  const string& lzone_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(3), lblock_id);

  initialize_zone_id_space(lzone_id_space_name, lzone_begin, lzone_ct);

  ijk_product_structure lzone_structure(_i_size, _j_size, _k_size);
  _zone_id_space.new_product_structure(lzone_structure);

  // Construct the id space and product structure for the vertices.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(0), lblock_id);

  initialize_vertex_id_space(lvertex_id_space_name, lvertex_begin, lvertex_ct);

  ijk_product_structure lvertex_structure(_i_vertex_size,
					  _j_vertex_size,
					  _k_vertex_size);
  _vertex_id_space.new_product_structure(lvertex_structure);

  // Construct the id space for the block vertices.

  initialize_block_vertices_id_space();

  // Construct the connectivity id space interval.

  arg_list largs =
    ijk_connectivity_index_space_interval::make_arg_list(lvertex_begin,
							 _j_size, _k_size);

  initialize_connectivity_id_spaces("ijk_connectivity_index_space_interval",
				    largs, lzone_ct);

  // Construct the adjacency id space interval.

  largs = ijk_adjacency_index_space_interval::make_arg_list(lzone_begin,
							    _i_size,
							    _j_size,
							    _k_size);
  initialize_adjacency_id_spaces("ijk_adjacency_index_space_interval",
				 largs, lvertex_ct);

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
fiber_bundle::structured_block_3d_crg_range::
class_name() const
{
  static const string result("structured_block_3d_crg_range");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::structured_block_3d_crg_range::
_has_prototype = make_prototype();

bool
fiber_bundle::structured_block_3d_crg_range::
make_prototype()
{
  // Preconditions:


  // Body:

  structured_block_3d_crg_range* lproto = new structured_block_3d_crg_range();

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
fiber_bundle::structured_block_3d_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const structured_block_3d_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::structured_block_3d_crg_range*
fiber_bundle::structured_block_3d_crg_range::
clone() const
{
  // Preconditions:

  // Body:

  structured_block_3d_crg_range* result = new structured_block_3d_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::structured_block_3d_crg_range::
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

    invariance(zones_initialized() ?
	       zone_id_space().ct() == i_size()*j_size()*k_size() : true);
    invariance(vertices_initialized() ?
	       vertex_id_space().ct() == (i_size()+1)*(j_size()+1)*(k_size()+1) : true);

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
deep_size(const structured_block_3d_crg_range& xr, bool xinclude_shallow)
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

