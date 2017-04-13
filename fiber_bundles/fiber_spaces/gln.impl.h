
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
/// Implementation for gln facet function templates.


#ifndef GLN_IMPL_H
#define GLN_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef GLN_H
#include "SheafSystem/gln.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS GLN_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const std::string&
gln_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const std::string result("gln_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
T&
gln_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex >= 0);

  // Body:

  T& result = reinterpret_cast<T*>(this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
gln_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex >= 0);

  // Body:

  const T& result = reinterpret_cast<const T*>(this)[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
gln_row_dofs_type<T>* 
gln_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  gln_row_dofs_type<T>* result = new gln_row_dofs_type<T>();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


} // namespace fiber_bundle

#endif // ifndef GLN_IMPL_H
