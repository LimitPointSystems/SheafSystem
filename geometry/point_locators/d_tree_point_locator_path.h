
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
/// Interface for class d_tree_point_locator_path

#ifndef D_TREE_POINT_LOCATOR_PATH_H
#define D_TREE_POINT_LOCATOR_PATH_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef D_BIN_COORDINATES_H
#include "d_bin_coordinates.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

template <int DC, int DB>
class d_bounding_box;
template <int DC, int DB>
class d_tree_point_locator;

///
/// A path in an d_tree_point_locator search structure.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_tree_point_locator_path
{

  // ===========================================================
  /// @name D_TREE_POINT_LOCATOR_PATH FACET
  // ===========================================================
  //@{

public:

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef sheaf::size_type size_type;

  ///
  /// The maximum number of branches at each node.
  ///
  static const size_type DEGREE = 1<<DC;

  ///
  /// Assignment operator
  ///
  d_tree_point_locator_path<DC, DB>& operator=
    (const d_tree_point_locator_path<DC, DB>& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Copy constructor
  ///
  d_tree_point_locator_path(const d_tree_point_locator_path<DC, DB>& xother);

  ///
  /// Destructor
  ///
  virtual ~d_tree_point_locator_path();

  ///
  /// Creates a path for point xpt in tree xtree.
  ///
  d_tree_point_locator_path(const d_bin_coordinates<DC, DB>& xpt,
                            const d_tree_point_locator<DC, DB>* xtree);

  ///
  /// Creates an empty path for tree xtree.
  ///
  d_tree_point_locator_path(const d_tree_point_locator<DC, DB>* xtree);

  ///
  /// The current depth.
  ///
  size_type depth() const;

  ///
  /// The current height.
  ///
  size_type height() const;

  ///
  /// The height of the root of the longest representable path.
  ///
  static size_type max_height();

  ///
  /// The depth of the head of the longest representable path.
  ///
  static size_type max_depth();

  ///
  /// The tree this is a path in.
  ///
  d_tree_point_locator<DC, DB>* tree() const;

  ///
  /// The branch index of the head of the path.
  ///
  size_type head() const;

  ///
  /// Ascend one level in the path.
  ///
  void ascend();

  ///
  /// Descend one level in the path.
  ///
  void descend();

  ///
  /// Set the current head to xhead.
  ///
  void put_head(size_type xhead);

  ///
  /// Sets depth to 0.
  ///
  void reset();

  ///
  /// True if the tree box represented by the current head
  /// intersects the box with lower bound xlb and upper bound xub.
  ///
  bool intersects(const d_bounding_box<DC, DB>* xbox) const;

  ///
  /// The representation of the path.
  ///
  const d_bin_coordinates<DC, DB>& path() const;

  ///
  /// The degree of the tree this is a path for.
  ///
  static size_type degree();

private:

  ///
  /// Default constructor; disabled
  ///
  d_tree_point_locator_path();

  ///
  /// The height of the head.
  ///
  size_type _height;

  // Tree is included as feature in this class
  // only because it is a convenient and efficient
  // place to put it for use by various clients.
  // It is not used in this class.

  ///
  /// The tree this is a path in.
  ///
  const d_tree_point_locator<DC, DB>* _tree;

  ///
  /// The representation of the path.
  ///
  d_bin_coordinates<DC, DB> _path;

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Insert d_tree_point_locator_path<DC, DB> xp into ostream os.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
ostream&
operator<<(ostream &os, const d_tree_point_locator_path<DC, DB>& xpath);
 
} // namespace geometry

#endif // ifndef D_TREE_POINT_LOCATOR_PATH_H
