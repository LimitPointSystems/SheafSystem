

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for member function templates in class index_space_handle.

#ifndef INDEX_SPACE_HANDLE_IMPL_H
#define INDEX_SPACE_HANDLE_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef INDEX_SPACE_HANDLE_H
#include "index_space_handle.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
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
