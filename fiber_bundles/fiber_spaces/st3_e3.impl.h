

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class st3_e3.

#ifndef ST3_E3_IMPL_H
#define ST3_E3_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ST3_E3_H
#include "st3_e3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST3_E3_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
st3_e3_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st3_e3_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
st3_e3_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 10;

  // Postconditions:

  ensure(result == 10);

  // Exit:

  return result;
}

template <typename T>
T&
st3_e3_row_dofs_type<T>::
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
st3_e3_row_dofs_type<T>::
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
st3_e3_row_dofs_type<T>* 
st3_e3_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  st3_e3_row_dofs_type<T>* result = new st3_e3_row_dofs_type<T>();

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
ostream& operator<<(ostream& xos, const st3_e3_row_dofs_type<T>& xrdt)
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

#endif // ifndef ST3_E3_IMPL_H