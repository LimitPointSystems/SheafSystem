
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class d_tree_point_locator_path

#ifndef D_TREE_POINT_LOCATOR_PATH_IMPL_H
#define D_TREE_POINT_LOCATOR_PATH_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_TREE_POINT_LOCATOR_PATH_H
#include "d_tree_point_locator_path.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef D_BOUNDING_BOX_H
#include "d_bounding_box.h"
#endif

#ifndef STD_BITSET_H
#include "std_bitset.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

// ============================================================================
// D_TREE_POINT_LOCATOR_PATH FACET
// ============================================================================

// PUBLIC MEMBER FUNCTIONS

template <int DC, int DB>
d_tree_point_locator_path<DC, DB>&
d_tree_point_locator_path<DC, DB>::
operator=(const d_tree_point_locator_path<DC, DB>& xother)
{
  if(&xother != this)
  {
    _height = xother._height;
    _path = xother._path;
  }
  return *this;
}

template <int DC, int DB>
bool
d_tree_point_locator_path<DC, DB>::
invariant() const
{
  invariance(height() <= max_height());
  invariance(depth() == max_height() - height());
  invariance(max_depth() == max_height());

  return true;
}

template <int DC, int DB>
d_tree_point_locator_path<DC, DB>::
d_tree_point_locator_path(const d_tree_point_locator_path<DC, DB>& xother)
{
  *this = xother;
}


template <int DC, int DB>
d_tree_point_locator_path<DC, DB>::
~d_tree_point_locator_path()
{}


template <int DC, int DB>
d_tree_point_locator_path<DC, DB>::
d_tree_point_locator_path(const d_bin_coordinates<DC, DB>& xpt,
                          const d_tree_point_locator<DC, DB>* xtree)
{
  // Preconditions:

  // Body:

  _path = xpt;
  _tree = xtree;

  reset();

  // Postconditions:

  ensure(depth() == 0);
  ensure(tree() == xtree);

  // Exit:

  return;
}

template <int DC, int DB>
d_tree_point_locator_path<DC, DB>::
d_tree_point_locator_path(const d_tree_point_locator<DC, DB>* xtree)
{
  // Preconditions:

  // Body:

  // _path initialized by default.

  _tree = xtree;

  reset();

  // Postconditions:

  ensure(depth() == 0);
  ensure(tree() == xtree);

  // Exit:

  return;
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
depth() const
{
  size_type result = max_height() - _height;

  // Postconditions:

  ensure(result <= max_depth());

  return result;
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
height() const
{
  size_type result = _height;

  // Postconditions:

  ensure(result <= max_height());

  return result;
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
max_height()
{
  static const size_type result = d_bin_coordinates<DC, DB>::leftmost_bit_id();
  return result;
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
max_depth()
{
  return max_height();
}

template <int DC, int DB>
d_tree_point_locator<DC, DB>*
d_tree_point_locator_path<DC, DB>::
tree() const
{
  return const_cast<d_tree_point_locator<DC, DB>*>(_tree);
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
head() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = _path.branch(_height);

  // Postconditions:

  ensure(result < DEGREE);

  // Exit:

  return result;
}

template <int DC, int DB>
void
d_tree_point_locator_path<DC, DB>::
ascend()
{
  // Preconditions:

  require(depth() > 0);

  // Body:

  define_old_variable(size_type old_depth = depth());

  _height++;

  // Postconditions:

  ensure(depth() == old_depth - 1);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_tree_point_locator_path<DC, DB>::
descend()
{
  // Preconditions:

  require(depth() < max_depth());

  // Body:

  define_old_variable(size_type old_depth = depth());

  _height--;

  // Postocnditions:

  ensure(depth() == old_depth + 1);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_tree_point_locator_path<DC, DB>::
put_head(size_type xhead)
{
  // Preconditions:

  require(xhead < DEGREE);

  // Body:

  _path.put_branch(_height, xhead);

  // Postconditions:

  ensure(head() == xhead);

  // Exit:

  return;
}

template <int DC, int DB>
void
d_tree_point_locator_path<DC, DB>::
reset()
{
  // Preconditions:

  // Body:

  _height = max_height();

  // Postconditions:

  ensure(depth() == 0);

  // Exit:

  return;
}

template <int DC, int DB>
bool
d_tree_point_locator_path<DC, DB>::
intersects(const d_bounding_box<DC, DB>* xbox) const
{
  bool result;

  // Preconditions:

  require(xbox != 0);

  // This intersects xbox iff for i in [0, DC):
  // (xbox->lb() <= _path) && (xbox->ub() >= _path),
  // where the comparisons are done using only the bits in the
  // current path, that is, the bits at height >= the current height.
  // This is implemented by right shifting the tree coordinates by _height
  // and then doing the usual numerical comparisons.

  // The path to the root should intersect all boxes, but this comparison
  // will only return true if the leftmost bit of all box bounds is 0.
  // So using this comparison relies on the invariant that the tree coordinates
  // in _path and in the box lb and ub are always < d_bin_coordinates::ub().

  d_bin_coordinates<DC, DB> lbox_lb(xbox->lb());
  lbox_lb >>= _height;

  d_bin_coordinates<DC, DB> lbox_ub(xbox->ub());
  lbox_ub >>= _height;

  d_bin_coordinates<DC, DB> lpath(_path);
  lpath >>= _height;

  result = (lbox_lb <= lpath) && (lpath <= lbox_ub);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "height= " << _height << endl;
  cout << "unshifted:" << endl;
  cout << xbox->lb() << endl;
  cout << _path      << endl;
  cout << xbox->ub() << endl;
  cout << "shifted:" << endl;
  cout << lbox_lb << endl;
  cout << lpath   << endl;
  cout << lbox_ub << endl;
  cout << "result= " << boolalpha << result << noboolalpha << endl;
  cout << endl;
#endif

  // Postconditions:

  // Exit:

  return result;
}

template <int DC, int DB>
const d_bin_coordinates<DC, DB>&
d_tree_point_locator_path<DC, DB>::
path() const
{
  return _path;
}

template <int DC, int DB>
sheaf::size_type
d_tree_point_locator_path<DC, DB>::
degree()
{
  return DEGREE;
}

template <int DC, int DB>
d_tree_point_locator_path<DC, DB>::
d_tree_point_locator_path()
{}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

template <int DC, int DB>
ostream&
operator<<(ostream &os, const d_tree_point_locator_path<DC, DB>& xpath)
{
  os << "height = " << xpath.height()
  << ", max_height = " << xpath.max_height()
  << ", head = " << xpath.head()
  << ", path = " << xpath.path()
  << endl;

  return os;
}
 
} // namespace geometry

#endif // ifndef D_TREE_POINT_LOCATOR_PATH_IMPL_H
