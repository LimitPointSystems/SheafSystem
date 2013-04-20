
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class d_tree_point_locator_node

#ifndef D_TREE_POINT_LOCATOR_NODE_H
#define D_TREE_POINT_LOCATOR_NODE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
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
  typedef slist<const d_bounding_box<DC, DB>*> box_list_type;

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
  string* to_string() const;

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
ostream&
operator<<(ostream& xos, const d_tree_point_locator_node<DC, DB>& xnode);
 
} // namespace geometry

#endif // D_TREE_POINT_LOCATOR_NODE_H