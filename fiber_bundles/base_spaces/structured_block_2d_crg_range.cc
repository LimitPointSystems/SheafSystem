// $RCSfile: structured_block_2d_crg_range.cc,v $ $Revision: 1.24 $ $Date: 2013/01/12 17:16:52 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class structured_block_2d_crg_range

#include "structured_block_2d_crg_range.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "factory.h"
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
// STRUCTURED_BLOCK_2D_CRG_RANGE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block_2d_crg_range::
structured_block_2d_crg_range()
{
  _i_size = 0;
  _j_size = 0;

  _i_vertex_size = 0;
  _j_vertex_size = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::structured_block_2d_crg_range::
~structured_block_2d_crg_range()
{
  // Nothing to do.
}

sheaf::size_type
fiber_bundle::structured_block_2d_crg_range::
i_size() const
{
  return _i_size;
}

sheaf::size_type
fiber_bundle::structured_block_2d_crg_range::
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
// ZONE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::ij_product_structure&
fiber_bundle::structured_block_2d_crg_range::
zone_product_structure() const
{
  // Preconditions:

  require(zones_initialized());
  require(zone_id_space().has_product_structure());
  require(zone_id_space().product_structure_conforms_to<ij_product_structure>());

  // Body:

  const ij_product_structure& result =
    _zone_id_space.product_structure<ij_product_structure>();

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

const sheaf::ij_product_structure&
fiber_bundle::structured_block_2d_crg_range::
vertex_product_structure() const
{
  // Preconditions:

  require(vertices_initialized());
  require(vertex_id_space().has_product_structure());
  require(vertex_id_space().product_structure_conforms_to<ij_product_structure>());

  // Body:

  const ij_product_structure& result =
    _vertex_id_space.product_structure<ij_product_structure>();

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

// sheaf::cover_set_iterator
// fiber_bundle::structured_block_2d_crg_range::
// block_vertices() const
// {
//   // Preconditions:


//   // Body:

//   /// @todo replace with specialized iterator, when available

//   list_cover_set* lcover = new list_cover_set(0);
//   lcover->put_is_implicit(true);

//   int I = i_size();
//   int J = j_size();

//   pod_index_type lvertex_begin = _vertex_id_space.offset();

//   lcover->push_back(lvertex_begin);
//   lcover->push_back(lvertex_begin + (J+1)*I);
//   lcover->push_back(lvertex_begin + (J+1)*I + J);
//   lcover->push_back(lvertex_begin + J);

//   cover_set_iterator result(*lcover);

//   // Postconditions:


//   // Exit:

//   return result;
// }

int
fiber_bundle::structured_block_2d_crg_range::
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

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BLOCK VERTICES FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
fiber_bundle::structured_block_2d_crg_range::
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
  _block_vertices_id_space.push_back(lvertex_begin);
  _block_vertices_id_space.push_back(lvertex_begin + (J+1)*I);
  _block_vertices_id_space.push_back(lvertex_begin + (J+1)*I + J);
  _block_vertices_id_space.push_back(lvertex_begin + J);

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
fiber_bundle::structured_block_2d_crg_range::
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

const sheaf::index_space_handle&
sheaf::structured_block_2d_crg_range::
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
sheaf::structured_block_2d_crg_range::
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

// PRIVATE DATA MEMBERS


// ===========================================================
// DOF_TUPLE_ID FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::structured_block_2d_crg_range::
get_dof_tuple_ids(poset_state_handle& xhost,
                  size_type xi_size,
                  size_type xj_size,
                  block<scoped_index>& result)
{
  // Preconditions:


  // Body:

  result.reserve(MEMBER_CLASS_END);
  result.set_ct(MEMBER_CLASS_END);


  result[BLOCK]  = structured_block_2d::new_row_dof_map(xhost, xi_size, xj_size, true);
  result[ZONE]   = base_space_member::new_row_dof_map(xhost, "quad_nodes", true);
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
fiber_bundle::structured_block_2d_crg_range::
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
fiber_bundle::structured_block_2d_crg_range::
implicit_private_data_size() const
{
  return 2;
}

void
fiber_bundle::structured_block_2d_crg_range::
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
fiber_bundle::structured_block_2d_crg_range::
put_implicit_private_data(const block<pod_index_type>& xdata)
{
  // Preconditions:

  require(xdata.ct() >= implicit_private_data_size());

  // Body:

  _i_size = xdata[0];
  _j_size = xdata[1];

  _i_vertex_size = _i_size + 1;
  _j_vertex_size = _j_size + 1;

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
fiber_bundle::structured_block_2d_crg_range::
finalize(poset_state_handle& xhost)
{
  // Preconditions:

  require(dynamic_cast<base_space_poset*>(&xhost) != 0);
  require(xhost.state_is_read_accessible());

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(xhost);

  // Compute the top ids for the cell ranges.

  size_type lzone_ct = (_i_size*_j_size);
  size_type lvertex_ct   = (_i_vertex_size*_j_vertex_size);

  pod_index_type lblock_id     = range_member();
  pod_index_type lzone_begin   = lblock_id + 1;
  pod_index_type lvertex_begin = lzone_begin + lzone_ct;

  // Construct the id space and product structure for the zones.

  const string& lzone_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(2),
							    lblock_id);

  initialize_zone_id_space(lzone_id_space_name, lzone_begin, lzone_ct);

  ij_product_structure lzone_structure(_i_size, _j_size);
  _zone_id_space.new_product_structure(lzone_structure);

  // Construct the id space and product structure for the vertices.

  const string& lvertex_id_space_name =
    section_space_schema_member::intersection_id_space_name(lhost.d_cells(0),
							    lblock_id);

  initialize_vertex_id_space(lvertex_id_space_name, lvertex_begin, lvertex_ct);

  ij_product_structure lvertex_structure(_i_vertex_size, _j_vertex_size);
  _vertex_id_space.new_product_structure(lvertex_structure);

  // Construct the id space for the block vertices.

  initialize_block_vertices_id_space();

  // Construct the connectivity id space interval.

  arg_list largs =
    ij_connectivity_index_space_interval::make_arg_list(lvertex_begin, _j_size);

  initialize_connectivity_id_spaces("ij_connectivity_index_space_interval",
				    largs, lzone_ct);

  // Construct the adjacency id space interval.

  largs = ij_adjacency_index_space_interval::make_arg_list(lzone_begin,
							   _i_size, _j_size);
  initialize_adjacency_id_spaces("ij_adjacency_index_space_interval",
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
fiber_bundle::structured_block_2d_crg_range::
class_name() const
{
  static const string result("structured_block_2d_crg_range");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
fiber_bundle::structured_block_2d_crg_range::
_has_prototype = make_prototype();

bool
fiber_bundle::structured_block_2d_crg_range::
make_prototype()
{
  // Preconditions:


  // Body:

  structured_block_2d_crg_range* lproto = new structured_block_2d_crg_range();

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
fiber_bundle::structured_block_2d_crg_range::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const structured_block_2d_crg_range*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::structured_block_2d_crg_range*
fiber_bundle::structured_block_2d_crg_range::
clone() const
{
  // Preconditions:

  // Body:

  structured_block_2d_crg_range* result = new structured_block_2d_crg_range();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::structured_block_2d_crg_range::
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
	       zone_id_space().ct() == i_size()*j_size() : true);
    invariance(vertices_initialized() ?
	       vertex_id_space().ct() == (i_size()+1)*(j_size()+1) : true);

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
deep_size(const structured_block_2d_crg_range& xr, bool xinclude_shallow)
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

