
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class array_cylindrical_point_locator

#include "array_cylindrical_point_locator.h"

#include "sec_ed.h"
#include "section_space_schema_poset.h"
#include "structured_block_2d.h"
#include "unstructured_block.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// ARRAY_CYLINDRICAL_POINT_LOCATOR FACET
// ===========================================================

geometry::array_cylindrical_point_locator::
array_cylindrical_point_locator(sec_ed& xcoords,
                                const block<size_type>& xbin_ub)
    : cylindrical_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);
  require(xcoords.schema().db() == DB);
  require(is_dlinear_quads(xcoords) || is_dlinear_triangles(xcoords));
  require(xbin_ub.ct() >= DB);
  require_for_all(i, 0, DB, xbin_ub[i] > 0);

  // Body:

  for(int i=0; i<DB; i++)
  {
    _bin_ub[i] = xbin_ub[i];
  }

  _bin_0_max = static_cast<sec_vd_value_type>(_bin_ub[0]) - 0.99;

  update();

  // Postconditions:


  // Exit:

  return;
}

geometry::array_cylindrical_point_locator::
array_cylindrical_point_locator(sec_ed& xcoords)
    : cylindrical_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);
  require(is_dlinear_quads(xcoords) || is_dlinear_triangles(xcoords));

  // Body:

  // Set _bin_ub to the db()-th root of the number of evaluation members.

  double leval_ct = static_cast<double>(xcoords.schema().evaluation_ct());
  size_type lbin_ub =
    static_cast<size_type>(exp(log(leval_ct)/static_cast<double>(DB)));

  // Make sure ub is at least 1.

  lbin_ub = (lbin_ub > 1) ? lbin_ub : 1;


  for(int i=0; i<DB; i++)
  {
    _bin_ub[i] = lbin_ub;
  }

  _bin_0_max = _bin_ub[0] - 1;

  update();

  // Postconditions:


  // Exit:

  return;
}

geometry::array_cylindrical_point_locator::
~array_cylindrical_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

sheaf::size_type
geometry::array_cylindrical_point_locator::
size() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _bins.ct();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

sheaf::size_type
geometry::array_cylindrical_point_locator::
capacity() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _bins.ub();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

bool
geometry::array_cylindrical_point_locator::
is_dlinear_quads(const sec_ed& xcoords) const
{
  bool result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());

  // Body:

  result = (xcoords.schema().evaluator_family_name() == "dlinear");
  if(result)
  {
    pod_index_type lbase_id = xcoords.schema().base_space_id();
    string ltype_name =
      xcoords.schema().host()->base_space().type_name(lbase_id);

    // The following is stricter than necessary; all we need is quads.
    // but there's no other easy way to find out.

    result = (ltype_name == "structured_block_2d");
    if(result)
    {
      structured_block_2d lblock(xcoords.schema().base_space());
      ltype_name = lblock.local_cell_type_name();
      result = (ltype_name.find("quad") != string::npos);
      lblock.detach_from_state();
    }
  }

  // Postconditions:


  // Exit:

  return result;
}

bool
geometry::array_cylindrical_point_locator::
is_dlinear_triangles(const sec_ed& xcoords) const
{
  bool result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());

  // Body:

  result = (xcoords.schema().evaluator_family_name() == "dlinear");
  if(result)
  {
    pod_index_type lbase_id = xcoords.schema().base_space_id();
    string ltype_name =
      xcoords.schema().host()->base_space().type_name(lbase_id);

    // The following is stricter than necessary; all we need is quads.
    // but there's no other easy way to find out.

    result = (ltype_name == "unstructured_block");
    if(result)
    {
      unstructured_block lblock(xcoords.schema().base_space());
      ltype_name = lblock.local_cell_type_name();
      result = (ltype_name.find("triangle") != string::npos);
      lblock.detach_from_state();
    }
  }

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

void
geometry::array_cylindrical_point_locator::
update_bins()
{
  // Preconditions:

  require(is_empty());

  // Body:

  // Compute the bin size.

  _bin_size[0] = 360.0/_bin_ub[0];
  _bin_size[1] = 180.0/_bin_ub[1];


  // Compute the reciprocal of the smallest bin size.
  // Used for efficiency in relative_position_pa().

  sec_vd_value_type lcoord_ub = d_bin_coordinates<2, 2>::ub();
  for(int i=0; i<DB; i++)
  {
    _one_over_min_bin_size[i] = 1.0/_bin_size[i];
  }

  // Reset the size of the bin array.

  size_type lbin_ct = 1;
  for(int i=0; i<DB; i++)
  {
    lbin_ct *= _bin_ub[i];
  }

  _bins.reserve(lbin_ct);
  _bins.set_ct(lbin_ct);

  /// @issue block.reserve doesn't reallocate if capacity is already large enough;
  /// so storage will never shrink.

  /// @todo provide mechanism in block for reclaiming storage.

  // Postconditions:

  // Exit:

  return;
}

sheaf::size_type
geometry::array_cylindrical_point_locator::
bin_id(const d_bin_coordinates<2, 2>& xcoord) const
{
  return (xcoord[0]*_bin_ub[1] + xcoord[1]);
};

sheaf::size_type
geometry::array_cylindrical_point_locator::
bin_id(const block<size_type>& xid) const
{
  return (xid[0]*_bin_ub[1] + xid[1]);
};

sheaf::size_type
geometry::array_cylindrical_point_locator::
bin_id(size_type xi, size_type xj) const
{
  return (xi*_bin_ub[1] + xj);
};


// ===========================================================
// CYLINDRICAL_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
geometry::array_cylindrical_point_locator::
insert_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      _bins[bin_id(i, j)].push_front(xbox);
    }
  }

  _box_ct++;


  // Postconditions:

  ensure(contains_box(xbox));
  ensure(box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

void
geometry::array_cylindrical_point_locator::
remove_box(d_bounding_box<2, 2>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = _box_ct);

  size_type ilb = xbox->lb()[0];
  size_type jlb = xbox->lb()[1];
  size_type iub = xbox->ub()[0];
  size_type jub = xbox->ub()[1];

  for(size_type i=ilb; i<=iub; ++i)
  {
    for(size_type j=jlb; j<=jub; ++j)
    {
      _bins[bin_id(i, j)].remove(xbox);
    }
  }

  _box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

const geometry::array_cylindrical_point_locator::box_list_type&
geometry::array_cylindrical_point_locator::
box_list(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= db());

  // Body:

  d_bin_coordinates<DB, DB> lcoord;
  relative_position_pa(xpt, xpt_ub, lcoord);

  const box_list_type& result = _bins[bin_id(lcoord)];

  // Postconditions:

  // Exit:

  return result;
}

bool
geometry::array_cylindrical_point_locator::
contains_box(d_bounding_box<2, 2>* xbox) const
{
  bool result = true;

  // Preconditions:

  require(xbox != 0);

  // Body:

  // Xbox has been inserted in this if and only if it has bin inserted in
  // every bin that it overlaps. So all we have to check is one bin;
  // the one containg the lower bound is convenient.

  box_list_type& llist = _bins[bin_id(xbox->lb())];
  box_list_type::const_iterator itr = llist.begin();
  while((itr != llist.end()) && (*itr != xbox))
  {
    ++itr;
  }

  result = (itr != llist.end());

  // Postconditions:


  // Exit:

  return result;
}

void
geometry::array_cylindrical_point_locator::
clear()
{
  // Preconditions:

  // Body:

  for(size_type i=0; i<_bins.ct(); i++)
  {
    _bins[i].clear();
  }

  _box_ct = 0;

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

///
geometry::array_cylindrical_point_locator&
geometry::array_cylindrical_point_locator::
operator=(const point_locator& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

///
geometry::array_cylindrical_point_locator&
geometry::array_cylindrical_point_locator::
operator=(const array_cylindrical_point_locator& xother)
{

  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

bool
geometry::array_cylindrical_point_locator::
invariant() const
{
  bool result = true;

  invariance(size() > 0);
  invariance(capacity() > 0);


  return result;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
geometry::operator<<(ostream& xos, const array_cylindrical_point_locator& xpl)
{
  // Preconditions:

  // Body:

  cout << "lb =";
  for(int i=0; i< xpl.db(); i++)
  {
    cout << " " << xpl.lb()[i];
  }
  cout << endl;

  cout << "ub =";
  for(int i=0; i< xpl.db(); i++)
  {
    cout << " " << xpl.ub()[i];
  }
  cout << endl;

  // Postconditions:

  // Exit:

  return xos;
}

