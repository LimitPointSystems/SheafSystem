
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
/// Implementation for member function templates in class index_space_handle.

#ifndef INDEX_SPACE_HANDLE_IMPL_H
#define INDEX_SPACE_HANDLE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_HANDLE_H
#include "SheafSystem/index_space_handle.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

// ===========================================================
// PRODUCT STRUCTURE FACET
// ===========================================================

template<typename T>
const T&
sheaf::index_space_handle::
product_structure() const
{
  // Preconditions:

  require(has_product_structure());
  require(product_structure_conforms_to<T>());

  // Body:

  const T& result = reinterpret_cast<const T&>(product_structure());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
T&
sheaf::index_space_handle::
product_structure()
{
  // Preconditions:

  require(has_product_structure());
  require(product_structure_conforms_to<T>());

  // Body:

  T& result = reinterpret_cast<T&>(product_structure());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

template<typename T>
bool
sheaf::index_space_handle::
product_structure_conforms_to() const
{
  // Preconditions:

  require(has_product_structure());

  // Body:

  bool result = (dynamic_cast<const T*>(&product_structure()) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

#endif // ifndef INDEX_SPACE_HANDLE_IMPL_H
