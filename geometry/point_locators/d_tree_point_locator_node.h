
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
/// Interface for class d_tree_point_locator_node

#ifndef D_TREE_POINT_LOCATOR_NODE_H
#define D_TREE_POINT_LOCATOR_NODE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_H
#include "ComLimitPoint/sheaf/sheaf.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SINGLY_LINKED_LIST_H
#include "ComLimitPoint/sheaf/singly_linked_list.h"
#endif

//#undef DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

namespace sheaf
{
template <class T>
class ptr_linked_pool;

}

namespace geometry
{

using namespace sheaf;
  
template <int DC, int DB>
class d_bounding_box;
template <int DC, int DB>
class d_tree_point_locator_path;

///
///  A node in a d_tree_point_locator search structure.
///
template <int DC, int DB>
class SHEAF_DLL_SPEC d_tree_point_locator_node
{
  friend class ptr_linked_pool< d_tree_point_locator_node<DC, DB> >;

  // ===========================================================
  /// @name D_TREE_POINT_LOCATOR_NODE FACET
  // ===========================================================
  //@{

public:

  ///
  ///  An unsigned integral type used to represent sizes and capacities.
  ///
  typedef sheaf::size_type size_type;

  ///
  /// Default constructor.
  ///
  d_tree_point_locator_node();

  ///
  /// Copy constructor.
  ///
  d_tree_point_locator_node(const d_tree_point_locator_node<DC, DB>& xother);

  ///
  /// Assignment operator.
  ///
  d_tree_point_locator_node<DC, DB>& operator=
    (const d_tree_point_locator_node<DC, DB>& xother);

  ///
  /// Equality operator.
  ///
  bool operator==(const d_tree_point_locator_node<DC, DB>& xother);

  ///
  /// Destructor.
  ///
  ~d_tree_point_locator_node();

  ///
  /// Class invariant.
  ///
  bool invariant() const;

  ///
  /// The xindex-th branch.
  ///
  d_tree_point_locator_node<DC, DB>* branch(int xindex) const;

  ///
  ///  True if this node is a leaf node.
  ///
  bool is_leaf() const;

  ///
  /// True if box_list() is empty.
  ///
  bool is_empty() const;

  ///
  /// Inserts xbox in this or somewhere on one of its branches.
  ///
  void insert_box(const d_bounding_box<DC, DB>* xbox,
                  d_tree_point_locator_path<DC, DB>& xpath);

  ///
  /// Removes xbox from this and its branches, recursively.
  ///
  void remove_box(const d_bounding_box<DC, DB>* xbox,
                  d_tree_point_locator_path<DC, DB>& xpath);

  ///
  /// True if xbox is in the box list of this or its branches, recursively.
  ///
  bool contains_box(const d_bounding_box<DC, DB>* xbox,
                    d_tree_point_locator_path<DC, DB>& xpath) const;

  ///
  /// Clears all branches and all boxes from this.
  /// Warning: this function does not deallocate the branches
  /// and hence can leave allocated but unreachable branches.
  ///
  void clear();

  ///
  /// The type of box list.
  ///
  typedef singly_linked_list<const d_bounding_box<DC, DB>*> box_list_type;

  ///
  /// The bounding boxes which intersect xpath.
  ///
  const box_list_type& box_list(d_tree_point_locator_path<DC, DB>& xpath) const;

  ///
  /// The bounding boxes which intersect this.
  ///
  const box_list_type& box_list() const;

  ///
  /// Get instance information as a string.
  ///
  std::string* to_string() const;

  ///
  /// The maximum number of branches a node may have.
  ///
  static size_type degree();

  ///
  /// The number of non-null branches.
  ///
  size_type branch_ct() const;

protected:

  ///
  /// The list of bounding boxes associated with this.
  ///
  box_list_type _box_list;

  ///
  /// The number of elements in the branches array.
  ///
  static const size_type DEGREE = 1<<DC;

  ///
  /// The branches of this node.
  ///
  d_tree_point_locator_node<DC, DB>* _branches[DEGREE];

  ///
  /// The number of non-null branches.
  ///
  size_type _branch_ct;

  ///
  /// The next node in the free list;
  /// intended for use only by class ptr_linked_pool.
  ///
  d_tree_point_locator_node<DC, DB>* next() const;

  ///
  /// Sets the next node in the free list to xnode;
  /// intended for use only by class ptr_linked_pool.
  ///
  void put_next(d_tree_point_locator_node<DC, DB>* xnode);

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts d_tree_point_locator_node<DC, DB> xnode into ostream xos.
///
template <int DC, int DB>
SHEAF_DLL_SPEC 
std::ostream&
operator<<(std::ostream& xos, const d_tree_point_locator_node<DC, DB>& xnode);
 
} // namespace geometry

#endif // D_TREE_POINT_LOCATOR_NODE_H
