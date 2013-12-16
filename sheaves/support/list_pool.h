
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
/// Interface for class list_pool.

#ifndef LIST_POOL_H
#define LIST_POOL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_FORWARD_LIST_H
#include "std_forward_list.h"
#endif

#ifndef STD_UNORDERED_SET_H
#include "std_unordered_set.h"
#endif

namespace sheaf
{

// Forward declarations to enable friend declaration.

template <typename T>
class list_pool;
template <typename T>
size_t deep_size(const list_pool<T>& xpool, bool xinclude_shallow);

///
/// Hash function for pointers.
///
template <typename T>
struct ptr_hash
{
public:
  size_t operator()(const T& t) const
  {
    return (size_t) t;
  }
};

///
/// Hash set key test for a pointer to type T.
///
template <typename T>
struct ptr_key_test
{
public:
  bool operator()(const T& t1, const T& t2) const
  {
    return (t1 == t2);
  }
};

///
/// A reallocated pool of objects of type T.
/// Objects in the pool are either allocated or stored in a free list.
/// The object allocated by the pool are tracked.  Intended to support
/// efficient allocation and deallocation for small numbers of objects.
///
template <typename T>
class list_pool
{

  friend size_t deep_size<T>(const list_pool<T>& xpool, bool xinclude_shallow);

  // ===========================================================
  /// @name LIST_POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// An unsigned integral type used to represent sizes and capacities.
  ///
  typedef unsigned long int  size_type;

  ///
  /// Default constructor.
  ///
  list_pool();

  ///
  /// Destructor
  ///
  virtual ~list_pool();

  ///
  /// Allocates an object of type T from this pool.
  ///
  T& get();

  ///
  /// Return the object xobj to the free list of this pool.
  ///
  void release(T& xobj);

  ///
  /// True if and only if this pool allocated object xobj.
  ///
  bool allocated(const T& xobj) const;

  ///
  // The number of allocated objects.
  ///
  size_type ct() const;

protected:

private:

  ///
  /// The free list type.
  ///
  typedef std::forward_list<T*> free_list_type;

  ///
  /// The type of allocation set.
  ///
  typedef std::unordered_set<T*, ptr_hash<T*>, ptr_key_test<T*> > allocated_type;

  ///
  /// Copy constructor; disabled.
  ///
  list_pool(const list_pool& xother) { };

  ///
  /// The list of free objects.
  ///
  free_list_type _free_list;

  ///
  /// The set of objects allocated by this pool.
  ///
  allocated_type _allocated;

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// The deep size of the referenced object of type list_pool.
///
template <typename T>
size_t deep_size(const list_pool<T>& xpool, bool xinclude_shallow);

} // namespace sheaf

#endif // ifndef LIST_POOL_H
