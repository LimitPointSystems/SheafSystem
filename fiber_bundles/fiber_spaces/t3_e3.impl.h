
// $RCSfile: t3_e3.impl.h,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:03 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class t3_e3

#ifndef T3_E3_IMPL_H
#define T3_E3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef T3_E3_H
#include "t3_e3.h"
#endif

//==============================================================================
// CLASS T3_E3_ROW_DOFS_TYPE
//==============================================================================

namespace fiber_bundle
{

template <typename T>
const string&
t3_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t3_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
t3_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 27;

  // Postconditions:

  ensure(result == 27);

  // Exit:

  return result;
}

template <typename T>
T&
t3_e3_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  ensure(xindex>=0 && xindex<d());

  // Body:

  T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
t3_e3_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  ensure(xindex>=0 && xindex<d());

  // Body:

  const T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
t3_e3_row_dofs_type<T>* 
t3_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  t3_e3_row_dofs_type<T>* result = new t3_e3_row_dofs_type<T>();

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
ostream& operator<<(ostream& xos, const t3_e3_row_dofs_type<T>& xrdt)
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

#endif // ifndef T3_E3_IMPL_H
