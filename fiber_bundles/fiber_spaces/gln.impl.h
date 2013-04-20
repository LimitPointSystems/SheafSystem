

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for gln facet function templates.


#ifndef GLN_IMPL_H
#define GLN_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef GLN_H
#include "gln.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS GLN_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
gln_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("gln_row_dofs_type");

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