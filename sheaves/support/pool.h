
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

// Interface for class POOL

#ifndef POOL_H
#define POOL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef INDEX_ITERATOR_H
#include "index_iterator.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_SLIST_H
#include "std_slist.h"
#endif

namespace sheaf
{
  
class zn_to_bool;

// Forward declarations to enable friend declaration.

template <class T, int EXTENSION_FACTOR>
class pool;
template <class T, int EXTENSION_FACTOR>
  size_t deep_size(const pool<T, EXTENSION_FACTOR>& xpool, bool xinclude_shallow);


///
/// A reallocatable pool of objects of type T.
/// Objects in the pool are either "allocated" or linked
/// together into a "free" list. Intended to support efficient
/// allocation and deallocation of nodes in a graph or other
/// dynamic data structure. There is an implicit constraint
/// on T: it must have a next() feature.
///
template <typename T, int EXTENSION_FACTOR=2>
class pool
{
  friend size_t deep_size<T, EXTENSION_FACTOR>
  (const pool<T,EXTENSION_FACTOR>& xpool, bool xinclude_shallow);

public:

  ///
  /// The container's value type.
  ///*
  typedef T value_type;

  ///
  /// A type that behaves as a reference to the container's value type.
  ///*
  typedef T& reference_type;

  ///
  /// A type that behaves as a const reference to the container's value type.
  ///*
  typedef const T& const_reference_type;

  ///
  /// A type that behaves as a pointer to the container's value type.
  ///*
  typedef T* pointer_type;

  ///
  /// A type that behaves as a const pointer to the container's value type.
  ///*
  typedef const T* const_pointer_type;

  ///
  /// The containers index type.
  ///
  typedef pod_index_type index_type;

  ///
  /// A signed integral type used to represent the difference of
  /// two indices or iterators.
  ///
  typedef pod_index_type difference_type;

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef unsigned long int  size_type;

  ///
  /// Class invariant
  ///
  bool invariant() const;

  ///
  /// The upper bound on the index for
  /// members of the pool.
  ///
  pod_index_type index_ub() const;

  ///
  /// True if xindex is in bounds
  ///
  bool index_in_bounds(pod_index_type xindex) const;

  ///
  /// The size of free list
  ///
  int free_ct() const;

  ///
  /// The head of the free list.
  ///
  pod_index_type free_list() const;

  ///
  /// The size of allocated list
  ///
  int allocated_ct() const;

  ///
  /// True if xindex is allocated
  ///
  bool is_allocated(pod_index_type xindex) const;

  ///
  /// A pointer to the pool item at xindex
  ///
  T& item(pod_index_type xindex);

  ///
  /// A reference to the pool item at xindex
  ///
  T & operator[](pod_index_type xindex);

  ///
  /// An iterator over allocated items in the pool.
  ///
  index_iterator allocated_iterator() const;

  ///
  /// Allocate next available index from free list
  ///
  pod_index_type allocate();

  ///
  /// Deallocate item at xindex
  ///
  void deallocate(pod_index_type xindex);

  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void  print() const;

  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void  print(ostream &out) const;

  ///
  /// Creates an instance with xub upper bound.
  ///
  pool(pod_index_type xub);

  ///
  /// Destructor
  ///
  ~pool();


private:

  ///
  /// The size of allocated list
  ///
  int _allocated_ct;

  ///
  /// The size of free list
  ///
  int _free_ct;

  ///
  /// The head of the free list.
  ///
  pod_index_type _free_list;

  ///
  /// Type of storage for pool.
  ///
  typedef block<T*> pool_type;

  ///
  /// Contiguously allocated pointers to members.
  ///
  pool_type _pool;

  ///
  /// List of contiguously allocated chunks of members.
  ///
  slist<T*> _chunk_list;

  ///
  /// Bit vector to tag allocated members.
  ///
  zn_to_bool* _is_allocated;

  ///
  /// Extends pool size to xub.
  ///
  void extend_to(pod_index_type xub);

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// The deep size of the referenced object of type pool@<T, int@>.
///
template <typename T, int EXTENSION_FACTOR>
size_t
deep_size(const pool<T, EXTENSION_FACTOR>& xpool, bool xinclude_shallow);
 
} // namespace sheaf

#endif // ifndef POOL_H
