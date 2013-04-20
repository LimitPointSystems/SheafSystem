

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class stl_scoped_index.

#ifndef STL_SCOPED_INDEX_IMPL_H
#define STL_SCOPED_INDEX_IMPL_H

#ifndef STL_SCOPED_INDEX_H
#include "stl_scoped_index.h"
#endif

#ifndef  ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

using namespace sheaf;

// ===========================================================
// STL_SCOPED_INDEX
// ===========================================================

template<typename T>
sheaf::stl_scoped_index<T>::
stl_scoped_index(const scoped_index& xindex)
{
  // Preconditions:

  // Body:

  _index = xindex;

  // Postconditions:

  ensure(invariant());
  ensure(index() == xindex);

  // Exit:

  return;
}

template<typename T>
sheaf::stl_scoped_index<T>::
~stl_scoped_index()
{
  // Nothing to do.
}

template<typename T>
sheaf::stl_scoped_index<T>::
operator scoped_index () const
{
  return _index;
}

template<typename T>
bool
sheaf::stl_scoped_index<T>::
operator<(const stl_scoped_index<T>& xother) const
{
  // Preconditions:

  // Body:

  bool result = compare_policy::less_than(_index, xother.index());

  // Postconditions:

  ensure(result == (compare_policy::less_than(index(), xother.index())));

  // Exit:

  return result;
}

template<typename T>
bool
sheaf::stl_scoped_index<T>::
operator==(const stl_scoped_index<T>& xother) const
{
  // Preconditions:

  // Body:

  bool result = compare_policy::equal(_index, xother.index());
  
  // Postconditions:

  ensure(result == (compare_policy::equal(index(), xother.index())));

  // Exit:

  return result;
}

#endif // ifndef STL_SCOPED_INDEX_IMPL_H
