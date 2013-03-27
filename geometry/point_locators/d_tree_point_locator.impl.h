// $RCSfile: d_tree_point_locator.impl.h,v $ $Revision: 1.5 $ $Date: 2013/01/12 17:17:30 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class d_tree_point_locator

#ifndef D_TREE_POINT_LOCATOR_IMPL_H
#define D_TREE_POINT_LOCATOR_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_TREE_POINT_LOCATOR_H
#include "d_tree_point_locator.h"
#endif

#ifndef D_BIN_POINT_LOCATOR_IMPL_H
#include "d_bin_point_locator.impl.h"
#endif

#ifndef D_TREE_POINT_LOCATOR_PATH_H
#include "d_tree_point_locator_path.h"
#endif

#ifndef STD_UTILITY_H
#include "std_utility.h"
#endif

#ifndef STD_ALGORITHM_H
#include "std_algorithm.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{
  
// ===========================================================
// D_TREE_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_tree_point_locator<DC, DB>::
d_tree_point_locator(sec_ed& xcoords, size_type xdepth)
    : d_bin_point_locator<DC, DB>::d_bin_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);
  require(xdepth <= max_depth());

  // Body:

  _depth = xdepth;

  this->update();

  // Postconditions:


  // Exit:

  return;
}

template <int DC, int DB>
d_tree_point_locator<DC, DB>::
d_tree_point_locator(sec_ed& xcoords)
    : d_bin_point_locator<DC, DB>::d_bin_point_locator(xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().df() == DC);

  // Body:

  // Set the depth to log base 2^DC of number of evaluation members.

  double leval_ct = static_cast<double>(xcoords.schema().evaluation_ct());
  size_type ldepth =
    static_cast<size_type>((log(leval_ct)/log(static_cast<double>(1<<DC))));

  // Make depth is at least 1.

  _depth = ldepth > 1 ? ldepth : 1;

  this->update();

  // Postconditions:


  // Exit:

  return;
}

template <int DC, int DB>
d_tree_point_locator<DC, DB>::
~d_tree_point_locator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
const d_tree_point_locator_node<DC, DB>&
d_tree_point_locator<DC, DB>::
root() const
{
  // Preconditions:

  // Body:

  const d_tree_point_locator_node<DC, DB>& result = _root;

  // Postconditions:

  ensure(invariant());

  return result;
}

template <int DC, int DB>
size_type
d_tree_point_locator<DC, DB>::
depth() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = _depth;

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

template <int DC, int DB>
size_type
d_tree_point_locator<DC, DB>::
max_depth()
{
  // Preconditions:


  // Body:

  static const size_type result = d_bin_coordinates<DC, DB>::leftmost_bit_id();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

template <int DC, int DB>
size_type
d_tree_point_locator<DC, DB>::
size()
{
  size_type result;

  // Preconditions:


  // Body:

  // Root is not in the pool, so size is pool size + 1.

  result = node_pool().allocated_size() + 1;

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
size_type
d_tree_point_locator<DC, DB>::
capacity()
{
  size_type result;

  // Preconditions:


  // Body:

  // Root is not in the pool, so capacity is pool capacity + 1.

  result = node_pool().capacity();

  // Postconditions:


  // Exit:

  return result;
}



template <int DC, int DB>
size_type&
d_tree_point_locator<DC, DB>::
default_depth()
{

  // Preconditions:


  // Body:

  static size_type result = 5;

  // Postconditions:


  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

template <int DC, int DB>
void
d_tree_point_locator<DC, DB>::
update_bins()
{
  // Preconditions:

  require(this->is_empty());

  // Body:

  // Choose a reasonable initial capacity for the node pool.

  node_pool().clear();
  node_pool().reserve(1024);

  // Compute the bin size of the smallest leaves in the tree.
  // All paths have leading bit == 0, so number of bins in
  // each dimension is pow(2, depth-1) rather than pow(2, depth).

  sec_vd_value_type bin_ct = pow(2.0, static_cast<sec_vd_value_type>(_depth-1));
  for(int i=0; i<DC; i++)
  {
    this->_bin_ub[i]   = static_cast<size_type>(bin_ct);
    this->_bin_size[i] = (this->_ub[i] - this->_lb[i])/bin_ct;
  }

  // Compute the reciprocal of the bin size of the smallest representable leaves.
  // Used for efficiency in relative_position_pa().

  sec_vd_value_type lcoord_ub = d_bin_coordinates<DC, DB>::ub();
  for(int i=0; i<DC; i++)
  {
    this->_one_over_min_bin_size[i] = lcoord_ub/(this->_ub[i] - this->_lb[i]);
  }

  // Postconditions:

  // Exit:

  return;
}

template <int DC, int DB>
ptr_linked_pool< d_tree_point_locator_node<DC, DB> >&
d_tree_point_locator<DC, DB>::
node_pool()
{
  // Preconditions:

  // Body:

  ptr_linked_pool< d_tree_point_locator_node<DC, DB> >& result = _node_pool;

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// D_BIN_POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
void
d_tree_point_locator<DC, DB>::
insert_box(d_bounding_box<DC, DB>* xbox)
{
  // Preconditions:

  require(xbox != 0);

  // Body:

  define_old_variable(size_type old_box_ct = this->_box_ct);

  d_tree_point_locator_path<DC, DB> lpath(this);
  _root.insert_box(xbox, lpath);
  this->_box_ct++;

  // Postconditions:

  ensure(contains_box(xbox));
  ensure(this->box_ct() == old_box_ct + 1);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_tree_point_locator<DC, DB>::
remove_box(d_bounding_box<DC, DB>* xbox)
{
  // Preconditions:

  require(xbox != 0);
  require(contains_box(xbox));

  // Body:

  define_old_variable(size_type old_box_ct = this->_box_ct);

  d_tree_point_locator_path<DC, DB> lpath(this);
  _root.remove_box(xbox, lpath);
  this->_box_ct--;

  // Postconditions:

  ensure(!contains_box(xbox));
  ensure(this->box_ct() == old_box_ct - 1);

  // Exit:

  return;
}

template <int DC, int DB>
const typename d_tree_point_locator<DC, DB>::box_list_type&
d_tree_point_locator<DC, DB>::
box_list(sec_vd_value_type* xpt, size_type xpt_ub) const
{
  // Preconditions:

  require(xpt != 0);
  require(xpt_ub >= this->dc());
  require(this->domain_contains(xpt, xpt_ub));

  // Body:

  d_bin_coordinates<DC, DB> rel_pt;
  relative_position_pa(xpt, xpt_ub, rel_pt);

  d_tree_point_locator_path<DC, DB> lpath(rel_pt, this);
  const box_list_type& result = _root.box_list(lpath);

  // Postconditions:


  // Exit:

  return result;
}


template <int DC, int DB>
bool
d_tree_point_locator<DC, DB>::
contains_box(d_bounding_box<DC, DB>* xbox) const
{
  bool result = true;

  // Preconditions:

  require(xbox != 0);

  // Body:

  d_tree_point_locator_path<DC, DB> lpath(this);
  result = _root.contains_box(xbox, lpath);

  // Postconditions:


  // Exit:

  return result;
}

template <int DC, int DB>
void
d_tree_point_locator<DC, DB>::
clear()
{
  // Preconditions:

  // Body:

  _root.clear();
  node_pool().clear();
  this->_box_ct = 0;

  // Postconditions:

  ensure(this->is_empty());

  // Exit:

  return;
}


// ===========================================================
// POINT_LOCATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
bool
d_tree_point_locator<DC, DB>::
invariant() const
{
  bool result = true;

  invariance(depth() > 0);
  invariance(this->coordinates().schema().df() == DC);


  return result;
}


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

template <int DC, int DB>
ostream& operator<<(ostream& xos, const d_tree_point_locator<DC, DB>& xtree)
{
  // Preconditions:

  // Body:

  cout << "lb =";
  for(int i=0; i< xtree.dc(); i++)
  {
    cout << " " << xtree.lb()[i];
  }
  cout << endl;

  cout << "ub =";
  for(int i=0; i< xtree.dc(); i++)
  {
    cout << " " << xtree.ub()[i];
  }
  cout << endl;

  cout << "depth = " << xtree.depth() << endl;
  cout << "root = " << xtree.root() << endl;

  // Postconditions:

  // Exit:

  return xos;
}
 
} // namespace geometry

#endif // D_TREE_POINT_LOCATOR_IMPL_H
