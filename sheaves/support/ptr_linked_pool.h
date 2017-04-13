
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

// Interface for class PTR_LINKED_POOL

#ifndef PTR_LINKED_POOL_H
#define PTR_LINKED_POOL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "SheafSystem/block.h"
#endif

#ifndef STD_IOSTREAM_H
#include "SheafSystem/std_iostream.h"
#endif

#ifndef SINGLY_LINKED_LIST_H
#include "SheafSystem/singly_linked_list.h"
#endif

namespace sheaf
{

///
/// A reallocatable pool of objects of type T.
/// Objects in the pool are either "allocated" or linked
/// together via pointers into a "free" list. Intended to support efficient
/// allocation and deallocation of nodes in a graph or other
/// dynamic data structure. There is an implicit constraint
/// on T: it must have a next() feature.
///
template <typename T>
class SHEAF_DLL_SPEC ptr_linked_pool
{
public:


  ///
  /// The number of objects, either free or allocated,
  /// currently in the pool.
  ///
  size_t capacity() const;

  ///
  /// The size of free list.
  ///
  size_t free_size() const;

  ///
  /// The size of allocated list.
  ///
  size_t allocated_size() const;

  ///
  /// Makes capacity at least xcapacity.
  ///
  void reserve(size_t xcapacity);

  ///
  /// Deletes all the objects in the pool.
  ///
  void clear();

  ///
  /// Allocate next available object from the free list.
  ///
  T* allocate();

  ///
  /// Deallocate xobject.
  ///
  void deallocate(T* xobject);
  
  ///
  /// Prints the data members of this on cout.
  /// Intended for use debugging.
  ///
  void print() const;

  ///
  /// Prints the data members of this on output stream xos.
  /// Intended for use debugging.
  ///
  void print(std::ostream& xos) const;
        
  ///
  /// Creates an instance with capacity xcapacity.
  ///
  ptr_linked_pool(size_t xcapacity = 1024);

  ///
  /// Destructor
  ///
  ~ptr_linked_pool();


private:

  ///
  /// The capacity.
  ///
  size_t _capacity;

  ///
  /// The size of free list
  ///
  size_t _free_size;

  ///
  /// The head of the free list.
  ///
  T* _free_list;

  ///
  /// List of contiguously allocated chunks of members.
  ///
  singly_linked_list<block<T>*> _chunk_list;

};
 

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Insert ptr_linked_pool<T>& xp into ostream& xos.
///
template <typename T>
std::ostream& operator<< (std::ostream& xos, const ptr_linked_pool<T>& xp);


} // namespace sheaf

#endif // ifndef PTR_LINKED_POOL_H
