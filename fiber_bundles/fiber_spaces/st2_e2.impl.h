
// $RCSfile: st2_e2.impl.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:02 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for st2_e2 facet function templates.


#ifndef ST2_E2_IMPL_H
#define ST2_E2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ST2_E2_H
#include "st2_e2.h"
#endif

#ifndef GL2_H
#include "gl2.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS ST2_E2_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
st2_e2_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_e2_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
st2_e2_row_dofs_type<T>::
d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return 3;
}

template <typename T>
T&
st2_e2_row_dofs_type<T>::
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
st2_e2_row_dofs_type<T>::
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
st2_e2_row_dofs_type<T>::
operator typename st2_e2_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return reinterpret_cast<matrix_type&>(*this);
}

template <typename T>
st2_e2_row_dofs_type<T>::
operator const typename st2_e2_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  st2_e2_row_dofs_type<T>& me = const_cast<st2_e2_row_dofs_type<T>&>(*this);

  return reinterpret_cast<matrix_type&>(me);
}

template <typename T>
st2_e2_row_dofs_type<T>* 
st2_e2_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  st2_e2_row_dofs_type<T>* result = new st2_e2_row_dofs_type<T>();

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
ostream& operator<<(ostream& xos, const st2_e2_row_dofs_type<T>& xrdt)
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

#endif // ifndef ST2_E2_IMPL_H
