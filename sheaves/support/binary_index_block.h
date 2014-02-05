
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

// Interface for class binary_index_block

#ifndef BINARY_INDEX_BLOCK_H
#define BINARY_INDEX_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

namespace sheaf
{
  
///
/// A block which can be accessed using two indices,
/// similarly to a two index array.
///
template <typename T>
class binary_index_block : public block<T>
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Sets the contents of this to the contents of xother.
  ///
  binary_index_block& operator=(const binary_index_block& xother);

  /**
   * The class invariant.
   */
  bool invariant() const;

  // ===========================================================
  // BLOCK FACET
  // ===========================================================

  using block<T>::push_back;

  ///
  /// Appends xother to the back of this.
  ///
  void push_back(const binary_index_block& xother);

  // ===========================================================
  // BINARY_INDEX_BLOCK FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  ///
  binary_index_block(int xi_ub = 0, int xj_ub = 0);

  ///
  /// Copy constructor
  ///
  ///
  binary_index_block(const binary_index_block& xother);


  ///
  /// Creates an instance with i_ub() == xi_ub and j_ub() == xj_ub
  /// containing xi_ct*xj_ct items copied from xitems
  ///
  binary_index_block(int xi_ub, int xi_ct, int xj_ub, int xj_ct, const T *xitems);

  ///
  /// Destructor
  ///
  ~binary_index_block();

  ///
  /// The upper bound for the first index.
  ///
  int i_ub() const;

  ///
  /// The upper bound for the second index.
  ///
  int j_ub() const;

  ///
  /// The number of i index values currently in use.
  ///
  int i_ct() const;

  ///
  /// The number of j index values currently in use.
  ///
  int j_ct() const;

  using block<T>::item;

  ///
  /// The item at index xi, xj (mutable version).
  ///
  T& item(int xi, int xj);

  ///
  /// The item at index xi, xj (const version).
  ///
  const T& item(int xi, int xj) const;

  ///
  /// The address of the first item in row xi.
  //// @issue with this operator, the expression b[i][j],
  //// where b is a block should evaluate to the value of the item at i,j.
  //// But what we really want is a reference to the item.
  //// To do this we'll probably need some sort of intermediate type that
  //// this operator can return, but then there may be efficiency issues.
  ////
  T* operator [] (int xi) const;

  using block<T>::force_item;

  ///
  /// Puts the item xitem at index xi,xj,
  /// resizing if necessary.
  ///
  void force_item(int xi, int xj, const T& xitem);

  using block<T>::reserve;

  ///
  /// Makes i_ub() at least xi_ub and j_ub() at least xj_ub.
  ///
  void reserve(int xi_ub, int xj_ub);

  using block<T>::set_ct;

  ///
  /// Sets i_ct() == xi_ct and j_ct() == xj_ct.
  ///
  void set_ct(int xi_ct, int xj_ct);

  ///
  /// Sets the item xitem at index xi, xj
  /// to xitem, but will not resize.
  ///
  void put_item(int xi, int xj, const T& xitem);

  ///
  /// Sets the values of all items to xitem.
  ///
  void assign(const T& xitem);

protected:

  ///
  /// The upper bound for the first index.
  ///
  int _i_ub;

  ///
  /// The upper bound for the second index.
  ///
  int _j_ub;

  ///
  /// The number of i index values currently in use.
  ///
  int _i_ct;

  ///
  /// The number of j index values currently in use.
  ///
  int _j_ct;


};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts block xblk into ostream xos.
///
template <class T>
std::ostream&
operator << (std::ostream& xos, const binary_index_block<T>& xblk);
 
} // namespace sheaf


#endif // ifndef BINARY_INDEX_BLOCK_H
