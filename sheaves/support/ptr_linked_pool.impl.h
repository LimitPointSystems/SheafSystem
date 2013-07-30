
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

// Implementations for class ptr_linked_pool.

#ifndef PTR_LINKED_POOL_IMPL_H
#define PTR_LINKED_POOL_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PTR_LINKED_POOL_H
#include "ptr_linked_pool.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef BLOCK_IMPL_H
#include "block.impl.h"
#endif

#ifndef STD_IOMANIP_H
#include "std_iomanip.h"
#endif

namespace sheaf
{

///
template <typename T>
size_t
ptr_linked_pool<T>::
capacity() const
{

  return _capacity;
}

///
template <typename T>
size_t
ptr_linked_pool<T>::
allocated_size() const
{
  return _capacity - _free_size;
}

///
template <typename T>
size_t
ptr_linked_pool<T>::
free_size() const
{
  return _free_size;
}

///
template <typename T>
T*
ptr_linked_pool<T>::
allocate()
{
  T* result = 0;

  define_old_variable(size_t old_allocated_size = allocated_size());

  if (_free_list == 0 )
  {
    // Free list is empty, extend the ptr_linked_pool

    reserve(2*_capacity);
  }

  result = _free_list;
  if (result != 0 )
  {
    // Have valid result, remove it from the free list

    _free_list = result->next();
    --_free_size;

    // Make sure no interaction between use of next
    // by free list and other uses of next.

    result->put_next(0);
  }

  // Postconditions:

  ensure(result !=0);
  ensure(allocated_size() == old_allocated_size + 1);

  return result;
}


///
template <typename T>
void
ptr_linked_pool<T>::
deallocate(T* xobject)
{

  // Preconditions:

  require(xobject != 0);
  require(unexecutable("xobject is allocated"));

  // Body:

  define_old_variable(size_t old_free_size = _free_size);
  define_old_variable(size_t old_allocated_size = allocated_size());

  xobject->put_next(_free_list);
  _free_list = xobject;
  ++_free_size;

  // Postconditions:

  ensure(free_size() == old_free_size + 1);
  ensure(allocated_size() == old_allocated_size - 1);

  // Exit:
}

template <typename T>
void
ptr_linked_pool<T>::
print() const
{   
  print(cout);
}


template <typename T>
void
ptr_linked_pool<T>::
print(ostream& xos) const
{
  // Preconditions:

  // Body:

  xos << " capacity: " << capacity()
      << " free_size: " << free_size()
      << " allocated_size: " << allocated_size()
      << endl;

  int lcol_pos = 0;
  xos << "pool contents: " << endl;
  typename slist<block<T>*>::const_iterator citr;
  for(citr = _chunk_list.begin(); citr != _chunk_list.end(); ++citr)
  {
    for(size_t i=0; i<(*citr)->ct(); ++i)
    {
      xos << "  " << (*citr)->item(i);
      lcol_pos++;
      if(lcol_pos == 9)
      {
        xos << endl;
        lcol_pos = 0;
      }
    }
  }
  xos << endl;

  // Postconditions:

  // Exit:

}

///
template <typename T>
ptr_linked_pool<T>::
ptr_linked_pool(size_t xcapacity)
{

  // Preconditions:

  // Body:

  _capacity = 0;
  _free_size = 0;
  _free_list = 0;

  reserve(xcapacity);

  // Postconditions:

  ensure(free_size() == xcapacity);
  ensure(allocated_size() == 0);

  // Exit:

}

///
template <typename T>
ptr_linked_pool<T>::
~ptr_linked_pool()
{
  clear();
}

template <typename T>
void
ptr_linked_pool<T>::
reserve(size_t xcapacity)
{

  // Preconditions:

  require(xcapacity > 0);

  // Body:

  define_old_variable(size_t old_free_size = _free_size);

  size_t old_capacity = _capacity;

  if(xcapacity > _capacity)
  {
    // Allocate a new chunk of storage.

    size_t lchunk_size = xcapacity - old_capacity;
    block<T>* lchunk = new block<T>(lchunk_size);
    lchunk->set_ct(lchunk_size);
    _chunk_list.push_front(lchunk);

    // String the chunk together into a list.

    T* lptr = lchunk->base();
    for(size_t i=0; i<(lchunk_size-1); ++i)
    {
      T* lnext_ptr = lptr+1;
      lptr->put_next(lnext_ptr);
      lptr = lnext_ptr;
    }
    lptr->put_next(0);

    // Put the new chunk on the free list.

    if(_free_list == 0)
    {
      // The free list is empty;
      // make it point to the new chunk.

      _free_list = lchunk->base();
    }
    else
    {
      // The free list is not empty;
      // find its end.

      lptr = _free_list;

      while(lptr->next() != 0)
      {
        lptr = lptr->next();
      }

      assertion((lptr != 0) && (lptr->next() == 0));

      // Append the new chunk to the end of the list.

      lptr->put_next(lchunk->base());
    }

    // Update size and capacity.

    _free_size += lchunk_size;
    _capacity += lchunk_size;
  }

  // Postconditions:

  ensure(capacity() >= xcapacity);
  ensure(free_size() >= old_free_size);

  // Exit:

  return;
}

///
template <typename T>
void
ptr_linked_pool<T>::
clear()
{
  // Preconditions:


  // Body:

  // Clear the chunk list and delete all the chunks.

  while(!_chunk_list.empty())
  {
    block<T>* lchunk = _chunk_list.front();
    delete lchunk;
    _chunk_list.pop_front();
  }

  _capacity = 0;
  _free_size = 0;
  _free_list = 0;

  // Postconditions:

  ensure(capacity() == 0);
  ensure(free_size() == 0);
  ensure(allocated_size() == 0);

  // Exit:

  return;
}

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

template <typename T>
ostream&
operator<< (ostream& xos, const ptr_linked_pool<T>& xp)
{
  // Preconditions:

  // Body:

  xp.print(xos);

  // Postconditions:

  // Exit:

  return xos;
}

} // namespace sheaf

#endif // ifndef PTR_LINKED_POOL_IMPL_H
