
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

/// @file
/// Implementation for class stl_scoped_index.

#ifndef STL_SCOPED_INDEX_IMPL_H
#define STL_SCOPED_INDEX_IMPL_H

#ifndef STL_SCOPED_INDEX_H
#include "SheafSystem/stl_scoped_index.h"
#endif

#ifndef  ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
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
