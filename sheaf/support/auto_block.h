
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

// Interface for class auto_block.

#ifndef COM_LIMITPOINT_SHEAF_AUTO_BLOCK_H
#define COM_LIMITPOINT_SHEAF_AUTO_BLOCK_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POD_TYPES_H
#include "ComLimitPoint/sheaf/pod_types.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{
  
///
/// An auto_block value initialization policy that leaves the values uninitialized.
///
template <typename T>
class un_block_initialization_policy
{
public:

  ///
  /// Initializes the range [xbegin, xend).
  ///
  static void initialize(T* xbegin, T* xend);

  ///
  /// Initializes xvalue.
  ///
  static void initialize(T& xvalue);
};

///
/// A auto_block initialization policy that initializes the values to invalid.
///
template <typename T>
class invalid_block_initialization_policy
{
public:
  ///
  /// Initializes the range [xbegin, xend) to invalid().
  ///
  static void initialize(T* xbegin, T* xend);

  ///
  /// Initializes xvalue to invalid().
  ///
  static void initialize(T& xvalue);
};

// Specialization for float

template <>
class invalid_block_initialization_policy<float>
{
public:
  static float invalid();
  static void initialize(float* xbegin, float* xend);
  static void initialize(float& xvalue);
};

// Specialization for double

template <>
class invalid_block_initialization_policy<double>
{
public:
  static double invalid();
  static void initialize(double* xbegin, double* xend);
  static void initialize(double& xvalue);
};


///
/// A auto_block initialization policy that initializes the values to zero.
///
template <typename T>
class zero_block_initialization_policy
{
public:
  ///
  /// Initializes the range [xbegin, xend) to invalid().
  ///
  static void initialize(T* xbegin, T* xend);

  ///
  /// Initializes xvalue to invalid().
  ///
  static void initialize(T& xvalue);
};


///
/// A contiguously allocated array of items of type T
/// with size information and automatic resizing.
///
template <typename T, typename S = un_block_initialization_policy<T> >
class SHEAF_DLL_SPEC auto_block
{

public:

  ///
  /// The type of value stored in the container.
  ///
  typedef T value_type;

  ///
  /// The value initialization policy.
  ///
  typedef S initialization_policy;

  ///
  /// A type that behaves as a reference to the container's value type.
  ///
  typedef T& reference_type;

  ///
  /// A type that behaves as a const reference to the container's value type.
  ///
  typedef const T& const_reference_type;

  ///
  /// A type that behaves as a pointer to the container's value type.
  ///
  typedef T* pointer_type;

  ///
  /// A type that behaves as a const pointer to the container's value type.
  ///
  typedef const T* const_pointer_type;

  ///
  /// The containers index type.
  ///
  typedef typename sheaf::pod_index_type index_type;

  ///
  /// A signed integral type used to represent the difference of
  /// two indices or iterators.
  ///
  typedef signed long int  difference_type;

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef unsigned long int size_type;

  ///
  /// The underlying storage array.
  ///
  pointer_type base() const;

  ///
  /// The number of items currently in use.
  ///
  size_type ct() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  ///
  /// The item at index xindex.
  ///
  reference_type item(index_type xindex) const;

  ///
  /// The item at index xindex.
  ///
  reference_type operator [] (index_type xindex) const;

  ///
  /// The upper bound on the storage array.
  /// The number of items current allocated in the storage array.
  ///
  index_type ub() const;

  ///
  /// Creates an instance with ub() == xub;
  /// storage is uninitialized.
  ///
  auto_block(index_type xub = 0);

  ///
  /// Creates an instance with ub() == xub; storage is
  /// initialized with xct items copied from xitems
  ///
  auto_block(index_type xub, size_type xct, const T *xitems);

  ///
  /// Copy constructor.
  ///
  auto_block(const auto_block& xother);

  ///
  /// Assignment operator.
  ///
  auto_block& operator=(const auto_block& xother);

  ///
  /// Destructor
  ///
  virtual ~auto_block();

  ///
  /// Puts the item xitem at index xindex, resizing if necessary;
  /// any other new storage allocated is uninitialized.
  ///
  void force_item(index_type xindex, const_reference_type xitem);

  ///
  /// Makes ub() at least xub;
  /// if new storage is allocated, it is uninitialized.
  ///
  void reserve(index_type xub);

  ///
  /// Sets ct() == xct.
  ///
  void set_ct(size_type xct);

  ///
  /// Puts the item xitem at index xindex,
  /// but will not resize.
  ///
  void set_item(index_type xindex, const_reference_type xitem);

  ///
  /// Sets the values of all items to xitem.
  ///
  void assign(const_reference_type xitem);

  ///
  /// Sets the values of items with xbegin <= index < xend to xitem.
  ///
  void assign(index_type xbegin, index_type xend, const_reference_type xitem);

  ///
  /// The last item in the auto_block
  ///
  reference_type back() const;

  ///
  /// Insert item at the end of the items in the auto_block
  ///
  void push_back(const_reference_type item);

  ///
  /// Appends xother to the back of this.
  ///
  void push_back(const auto_block& xother);

  ///
  /// Remove item at the back.
  ///
  void pop_back();

  ///
  /// Remove all items.
  ///
  void clear();

  ///
  /// Invokes the initialization policy on the item at xindex.
  ///
  void initialize(index_type xindex);

  ///
  /// Invokes the initialization policy on the range [xbegin, xend).
  ///
  void initialize(index_type xbegin, index_type xend);



protected:

  ///
  /// Start of storage for this.
  ///
  pointer_type _base;     // start of auto_block storage

  ///
  /// The index upper bound.
  ///
  index_type  _ub;

  ///
  /// The number of items currently stored.
  ///
  size_type  _ct;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Equality operator; true if xblk1 equals xblk2
///
template <typename T, typename S>
bool operator==(const auto_block<T, S>& xblk1, const auto_block<T, S>& xblk2);

///
/// Inserts auto_block xblk into ostream xos.
///
template <typename T, typename S>
std::ostream& operator << (std::ostream& xos, const auto_block<T, S>& xblk);

///
/// The deep size of the referenced object of type auto_block@<T, S@>;
/// if xinclude_shallow, add the sizeof xp to the result.
///
template <typename T, typename S>
size_t deep_size(const auto_block<T, S>& xp, bool xinclude_shallow = true);

///
/// The deep size of the referenced object of type auto_block@<T* S@>.
/// if xinclude_shallow, add the sizeof xp to the result.
/// Note that the first argument is auto_block<T*, S> but the
/// template parameter is T, not T*.
///
template <typename T, typename S>
size_t deep_size(const auto_block<T*, S>& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // COM_LIMITPOINT_SHEAF_AUTO_BLOCK_H
