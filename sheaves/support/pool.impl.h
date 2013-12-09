
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

// Interface for class POOL

#ifndef POOL_IMPL_H
#define POOL_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POOL_H
#include "pool.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef STD_IOMANIP_H
#include "std_iomanip.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "zn_to_bool.h"
#endif

namespace sheaf
{

template <typename T, int EXTENSION_FACTOR>
bool
pool<T, EXTENSION_FACTOR>::
invariant() const
{
  bool result = true;

  // _pool and _is_allocated same size

  invariance(_pool.ub() == _is_allocated->ub());

  /// @todo elaborate pool::invariant()

  return result;
}

template <typename T, int EXTENSION_FACTOR>
pod_index_type
pool<T, EXTENSION_FACTOR>::
index_ub() const
{
  // Preconditions:

  // Body:

  index_type result(_pool.ub());

  // Postconditions:

  ensure(result >= 0);

  // return:

  return result;
}

template <typename T, int EXTENSION_FACTOR>
bool
pool<T, EXTENSION_FACTOR>::
index_in_bounds(pod_index_type xitem) const
{
  return (0 <= xitem) && (xitem < _pool.ub());
}

template <typename T, int EXTENSION_FACTOR>
int
pool<T, EXTENSION_FACTOR>::
free_ct() const
{
  return _free_ct;
}

template <typename T, int EXTENSION_FACTOR>
pod_index_type
pool<T, EXTENSION_FACTOR>::
free_list() const
{
  return _free_list;
}

template <typename T, int EXTENSION_FACTOR>
int
pool<T, EXTENSION_FACTOR>::
allocated_ct() const
{
  return _allocated_ct;
}

template <typename T, int EXTENSION_FACTOR>
bool
pool<T, EXTENSION_FACTOR>::
is_allocated(pod_index_type xindex) const
{
  bool result;

  // Preconditions:

  require(index_in_bounds(xindex));

  // Body:

  result = (*_is_allocated)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T, int EXTENSION_FACTOR>
index_iterator
pool<T, EXTENSION_FACTOR>::
allocated_iterator() const
{
  // Preconditions:

  // Body:

  index_iterator result(_is_allocated);

  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

template <typename T, int EXTENSION_FACTOR>
pod_index_type
pool<T, EXTENSION_FACTOR>::
allocate()
{
  if(!is_valid(_free_list))
  {
    // Free list is empty, extend the pool.

    pod_index_type new_index_ub(EXTENSION_FACTOR*_pool.ub());

    extend_to(new_index_ub);
  }

  pod_index_type result = _free_list;

  if(is_valid(result))
  {
    // Have valid result, remove it from the free list.

    _free_list = _pool[result]->next();
    --_free_ct;
    ++_allocated_ct;
    _is_allocated->put(result, true);

    // Make sure no interaction between use of next
    // by free list and other uses of next..

    _pool[result]->put_next(invalid_pod_index());

  }

  // postconditions:

  ensure(is_allocated(result));
  ensure(unexecutable(free_ct() == old free_ct() - 1));
  ensure(unexecutable(allocated_ct() == old allocated_ct() + 1));

  return result;
}

template <typename T, int EXTENSION_FACTOR>
void
pool<T, EXTENSION_FACTOR>::
deallocate(pod_index_type xindex)
{
  // Preconditions

  require(is_allocated(xindex));

  // Body:

  T* item = _pool.item(xindex);

  item->put_next(_free_list);
  _free_list = xindex;
  ++_free_ct;
  _is_allocated->put(xindex, false);
  --_allocated_ct;

  // Postconditions:

  ensure(!is_allocated(xindex));
  ensure(unexecutable(free_ct() == old free_ct() + 1));
  ensure(unexecutable(allocated_ct() == old allocated_ct() - 1));

  // Exit:

  return;
}

template <typename T, int EXTENSION_FACTOR>
pool<T, EXTENSION_FACTOR>::
pool(pod_index_type xub)
{
  // Preconditions:

  require(xub >= 0);

  // Body:

  _free_ct = 0;
  _free_list = invalid_pod_index();
  _allocated_ct = 0;
  _is_allocated = new zn_to_bool(xub);

  extend_to(xub);

  // Postconditions:

  ensure(index_ub() == xub);
  ensure(free_ct() == xub);
  ensure(free_list() == 0);
  ensure(allocated_ct() == 0);

  // Exit:

  return;
}

template <typename T, int EXTENSION_FACTOR>
pool<T, EXTENSION_FACTOR>::
~pool()
{
  // Clear the chunk list and delete all the chunks.

  while(!_chunk_list.empty())
  {
    T* lchunk = _chunk_list.front();
    delete [] lchunk;
    _chunk_list.pop_front();
  }

  // Delete the is_allocated bit vector

  delete _is_allocated;

}

template <typename T, int EXTENSION_FACTOR>
T &
pool<T, EXTENSION_FACTOR>::
item(pod_index_type xindex)
{

  // preconditions:

  require(index_in_bounds(xindex));

  // body:

  T& result = *(_pool.item(xindex));

  // postconditions:

  return result;
}

template <typename T, int EXTENSION_FACTOR>
T &
pool<T, EXTENSION_FACTOR>::
operator[](pod_index_type xindex)
{

  // preconditions:

  require(index_in_bounds(xindex));

  // body:

  T& result = *(_pool[xindex]);

  // postconditions:

  return result;
}

template <typename T, int EXTENSION_FACTOR>
void
pool<T, EXTENSION_FACTOR>::
extend_to(pod_index_type xub)
{
  // Preconditions:

  require(xub > 0);
  require(xub > index_ub());

  // Body:

  pod_index_type old_index_ub = index_ub();

  pod_index_type old_pool_ub = _pool.ub();
  pod_index_type new_pool_ub = xub;

  // Allocate a new chunk of storage.

  size_type lchunk_size = new_pool_ub - old_pool_ub;
  T* lchunk = new T[lchunk_size];
  _chunk_list.push_front(lchunk);

  // Extend the pool.

  _pool.reserve(new_pool_ub);

  // Initialize the new members of the pool
  // to point into the new chunk.

  T* lmbr_ptr = lchunk;
  for(int i=0; i<lchunk_size; i++)
  {
    _pool.push_back(lmbr_ptr++);
  }

  // Extend _is_allocated

  _is_allocated->extend_to(new_pool_ub);

  // Tie the new members together into a list;
  // each the new member is linked to the next one,
  // except the last, which is terminated.

  pod_index_type last_new_mbr_id(xub);
  --last_new_mbr_id;

  assertion(last_new_mbr_id >= old_index_ub);

  for(pod_index_type i = old_index_ub; i < last_new_mbr_id;)
  {
    pod_index_type old_i = i;
    _pool.item(old_i)->put_next(++i);
  }
  _pool.item(last_new_mbr_id)->put_next(invalid_pod_index());

  // Append the new member list to the free list.

  if (!is_valid(_free_list))
  {
    // Free list is empty;
    // make it point to the new member list.

    _free_list = old_index_ub;
  }
  else
  {
    // Free list is not empty;
    // find the end of it.

    pod_index_type last_free_mbr = _free_list;
    while(is_valid(_pool.item(last_free_mbr)->next()))
    {
      last_free_mbr = _pool.item(last_free_mbr)->next();
    }

    // Append the new member list.

    _pool.item(last_free_mbr)->put_next(old_index_ub);
  }

  // Update the free count.

  _free_ct += (new_pool_ub - old_pool_ub);

  // Postconditions:

  // Exit:

  return;
}


template <typename T, int EXTENSION_FACTOR>
void
pool<T, EXTENSION_FACTOR>::
print() const
{   
  print(std::cout);
}

template <typename T, int EXTENSION_FACTOR>
void
pool<T, EXTENSION_FACTOR>::
print(std::ostream &os) const
{

  os << std::endl;

  os << "pool "
     << std::hex
     << (void *)this
     << std::dec
     << " free_ct = "
     << _free_ct
     << " allocated_ct = "
     << _allocated_ct
     << " free_list = "
     << _free_list
     << std::endl
     << std::endl;

  for (pod_index_type i = 0; i < _pool.ub(); ++i)
  {
    os << "member: " << std::setw(5) << i << "   ";
    os << *(_pool[i]);
    os << std::endl;
  }


  return;
}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T, int EXTENSION_FACTOR>
size_t
deep_size(const pool<T, EXTENSION_FACTOR>& xpool, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  //require(T is not a pointer);

  // Body:

  result = xinclude_shallow ? sizeof(xpool) : 0;

  // Cast away the constness so we can access the methods of class pool.

  pool<T, EXTENSION_FACTOR>& lpool = const_cast<pool<T, EXTENSION_FACTOR>&>(xpool);

  // Add the sizeof size of both the allocated and free items.

  pod_index_type lindex_ub = lpool.index_ub();
  result += lindex_ub*sizeof(T);

  // Add the "deep_size"s of all of the allocsted items.

  for(pod_index_type i=0; i<lindex_ub; ++i)
  {
    if(lpool.is_allocated(i))
    {
      result += deep_size(lpool.item(i), false);
    }
  }

  // Class pool has no public access to the slist and zn_to_bool type data
  // members, so we are unable to add any additional contributions from them.

  // Calculate the total memory used by data member _chunk_list
  // of type slist<T*> not including that already counted above.

  // Best guess for singly linked list deep size.

  result += lpool._chunk_list.size()*(sizeof(T*) + sizeof(void*));

  // Calculate the total memory used by data member _is_allocated
  // of type zn_to_bool*.

  if(lpool._is_allocated != 0)
  {
    result += deep_size(*(lpool._is_allocated), true);
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

} // namespace sheaf

#endif // ifndef POOL_IMPL_H
