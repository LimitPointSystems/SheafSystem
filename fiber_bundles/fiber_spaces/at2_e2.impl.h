
// $RCSfile: at2_e2.impl.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:00 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class at2_e2

#ifndef AT2_E2_IMPL_H
#define AT2_E2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef AT2_E2_H
#include "at2_e2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS AT2_E2_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
at2_e2_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at2_e2_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
at2_e2_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  int result = 1;

  // Postconditions:

  ensure(result == 1);

  // Exit:

  return result;
}

template <typename T>
T&
at2_e2_row_dofs_type<T>::
operator[] (int xindex)
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
const T&
at2_e2_row_dofs_type<T>::
operator[] (int xindex) const
{
  // Preconditions:

  require(xindex>=0 && xindex<d());

  // Body:

  const T& result = components[xindex];

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
at2_e2_row_dofs_type<T>::
operator typename at2_e2_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return reinterpret_cast<matrix_type&>(*this);
}

template <typename T>
at2_e2_row_dofs_type<T>::
operator const typename at2_e2_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  at2_e2_row_dofs_type<T>& lthis = const_cast<at2_e2_row_dofs_type<T>&>(*this);
  const matrix_type& result = reinterpret_cast<matrix_type&>(lthis);
  
  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
at2_e2_row_dofs_type<T>* 
at2_e2_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  at2_e2_row_dofs_type<T>* result = new at2_e2_row_dofs_type<T>();

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
ostream& operator<<(ostream& xos, const at2_e2_row_dofs_type<T>& xrdt)
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

#endif // ifndef AT2_E2_IMPL_H
