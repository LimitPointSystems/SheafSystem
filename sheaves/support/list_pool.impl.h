

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for template class list_pool.

#ifndef LIST_POOL_IMPL_H
#define LIST_POOL_IMPL_H

#ifndef LIST_POOL_H
#include "list_pool.h"
#endif

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

namespace sheaf
{
  
// ===========================================================
// LIST_POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

template <typename T>
list_pool<T>::
list_pool()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
};

template <typename T>
list_pool<T>::
~list_pool()
{
  // Preconditions:

  // Body:

  typename allocated_type::iterator itr = _allocated.begin();

  while(itr != _allocated.end())
  {
    // Get the object to delete.

    T* obj = *itr;

    // Delete the object.

    delete obj;

    // Move to the next object.

    ++itr;
  }

  // Postconditions:

  ensure(unexecutable("All allocated objects have been deleted."));

  // Exit:

  return;
};

template <typename T>
T&
list_pool<T>::
get()
{
  // Preconditions:

  // Body:

  T* result;

  if(_free_list.empty())
  {
    // No available free list objects, allocate a new object.

    result = new T();

    // Add new object to the set of allocated objects.

    _allocated.insert(result);
  }
  else
  {
    // Get the top object in the list.

    result = _free_list.front();
    _free_list.pop_front();
  }

  // Postconditions:

  ensure(allocated(*result));

  // Exit:

  return *result;
};

template <typename T>
void
list_pool<T>::
release(T& xobj)
{
  // Preconditions:

  require(allocated(xobj));

  // Body:

  _free_list.push_front(&xobj);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
};

template <typename T>
bool
list_pool<T>::
allocated(const T& xobj) const
{
  // Preconditions:

  // Body:

  T& lobj = const_cast<T&>(xobj);

  bool result = (_allocated.find(&lobj) != _allocated.end());  

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
};

template <typename T>
typename list_pool<T>::size_type
list_pool<T>::
ct() const
{
  // Preconditions:

  // Body:

  size_type result = _allocated.size();

  // Postconditions:

  ensure(result >= 0);
  
  // Exit:

  return result;
};

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

template <typename T>
size_t
deep_size(const list_pool<T>& xpool, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xpool) : 0;

  typename list_pool<T>::allocated_type::const_iterator itr;
  for(itr = xpool._allocated.begin(); itr != xpool._allocated.end(); ++itr)
  {
    result += deep_size(**itr, true);
  }

  // Postconditions:

  // Exit:

  return result;
};

} // namespace sheaf

#endif // ifndef LIST_POOL_IMPL_H
