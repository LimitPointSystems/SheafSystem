
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
/// Interface for class d_tree_point_locator

#ifndef COM_LIMITPOINT_GEOMETRY_D_TREE_POINT_LOCATOR_H
#define COM_LIMITPOINT_GEOMETRY_D_TREE_POINT_LOCATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_D_BIN_POINT_LOCATOR_H
#include "ComLimitPoint/geometry/d_bin_point_locator.h"
#endif

#ifndef COM_LIMITPOINT_GEOMETRY_D_TREE_POINT_LOCATOR_NODE_H
#include "ComLimitPoint/geometry/d_tree_point_locator_node.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_PTR_LINKED_POOL_H
#include "ComLimitPoint/sheaf/ptr_linked_pool.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace geometry
{

///
/// A point location query in domains with
/// global coordinate dimension dc and local coordinate dimension db.
/// implemented using a 2^DC tree search structure. Efficient for
/// non-compact domains.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_tree_point_locator : public d_bin_point_locator<DC, DB>
{
  friend class d_tree_point_locator_node<DC, DB>;

  // ===========================================================
  /// @name D_TREE_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for coordinate section xcoords with depth xdepth.
  ///
  d_tree_point_locator(sec_ed& xcoords, size_type xdepth);

  ///
  /// Creates an instance for coordinate section xcoords with depth
  /// computed from the size of the mesh.
  ///
  d_tree_point_locator(sec_ed& xcoords);

  ///
  /// Destructor.
  ///
  virtual ~d_tree_point_locator();

  ///
  ///  The root node.
  ///
  const d_tree_point_locator_node<DC, DB>& root() const;

  ///
  /// The number of levels; the length of the
  /// longest path from root() to a leaf.
  ///
  size_type depth() const;

  ///
  /// The maximum representable number of levels.
  ///
  static size_type max_depth();

  ///
  /// The number of nodes in the tree.
  ///
  size_type size();

  ///
  /// The nodes allocated for use by the tree.
  ///
  size_type capacity();

  ///
  /// The default depth; the depth of a instance
  /// created with the default constructor.
  ///
  static size_type& default_depth();

protected:

  ///
  /// Default constructor; disabled.
  ///
  d_tree_point_locator() {};

  ///
  /// Copy constructor; disabled
  ///
  d_tree_point_locator(const d_tree_point_locator<DC, DB>& xother) {};

  ///
  /// Assignment operator; disabled.
  ///
    virtual d_tree_point_locator& operator=(const point_locator& xother) {return *this;};

  ///
  /// Assignment operator; disabled.
  ///
      d_tree_point_locator& operator=(const d_tree_point_locator<DC, DB>& xother) {return *this;};

  ///
  /// Updates the tree bin parameters.
  ///
  void update_bins();

  ///
  /// Pool for efficiently allocating and deallocating nodes.
  ///
  ptr_linked_pool< d_tree_point_locator_node<DC, DB> >& node_pool();

  ///
  /// Pool for efficiently allocating and deallocating nodes.
  ///
  ptr_linked_pool< d_tree_point_locator_node<DC, DB> > _node_pool;

  ///
  ///  The root node of the tree.
  ///
  d_tree_point_locator_node<DC, DB> _root;

  ///
  /// The number of levels in the tree;
  /// the length of the longest path from the root to a leaf.
  ///
  size_type _depth;

  //@}


  // ===========================================================
  /// @name D_BIN_POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of box list.
  ///
  typedef singly_linked_list<const d_bounding_box<DC, DB>*> box_list_type;

  ///
  /// Insert xbox into the tree.
  ///
  virtual void insert_box(d_bounding_box<DC, DB>* xbox);

  ///
  ///  Remove xbox from the tree.
  ///
  virtual void remove_box(d_bounding_box<DC, DB>* xbox);

  ///
  /// The list of bounding boxes which may contain xpt.
  ///
  virtual const box_list_type& box_list(sec_vd_value_type* xpt,
                                        size_type xpt_ub) const;

  ///
  /// True if xbox is in the box list of some bin.
  ///
  virtual bool contains_box(d_bounding_box<DC, DB>* xbox) const;

  ///
  ///  Clear the tree of all bounding boxes and all nodes except the root.
  ///
  virtual void clear();

  //@}


  // ===========================================================
  /// @name POINT_LOCATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}


};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts d_tree_point_locator& xtree into stream xos.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const d_tree_point_locator<DC, DB>& xtree);
 
} // namespace geometry

#endif // COM_LIMITPOINT_GEOMETRY_D_TREE_POINT_LOCATOR_H
