
// $RCSfile: e3.impl.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:00 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class e3.

#ifndef E3_IMPL_H
#define E3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef E3_H
#include "e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 3;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}

template <typename T>
T&
e3_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  T& result = components[xindex];

  // Postconditions:

  //ensure(result == components[xindex]);

  // Exit:

  return result;
}

template <typename T>
const T&
e3_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  const T& result = components[xindex];

  // Postconditions:

  //ensure(result == components[xindex]);

  // Exit:

  return result;
}

template <typename T>
e3_row_dofs_type<T>* 
e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  e3_row_dofs_type<T>* result = new e3_row_dofs_type<T>();

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#ifndef DOXYGEN_SKIP_IMPLEMENTATIONS
template <typename T>
ostream& operator<<(ostream& xos, const e3_row_dofs_type<T>& xrdt)
{
  int ld = xrdt.d();
  for(int i=0; i<ld; ++i)
  {
    xos << " " << xrdt.components[i];
  }

  return xos;
}
#endif // ifndef DOXYGEN_SKIP_IMPLEMENTATIONS

} // namespace fiber_bundle

#endif // ifndef E3_IMPL_H
