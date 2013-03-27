
// $RCSfile: jcb_e13.impl.h,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:01 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class jcb_e13.

#ifndef JCB_E13_IMPL_H
#define JCB_E13_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef JCB_E13_H
#include "jcb_e13.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS JCB_E13_ROW_DOFS_TYPE
//==============================================================================

template <typename T>
const string&
jcb_e13_row_dofs_type<T>::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("jcb_e13_row_dofs_type");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

template <typename T>
int
jcb_e13_row_dofs_type<T>::
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
jcb_e13_row_dofs_type<T>::
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
jcb_e13_row_dofs_type<T>::
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
jcb_e13_row_dofs_type<T>::
operator typename jcb_e13_row_dofs_type<T>::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = reinterpret_cast<matrix_type&>(*this);

  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
jcb_e13_row_dofs_type<T>::
operator const typename jcb_e13_row_dofs_type<T>::matrix_type& () const
{
  // Preconditions:

  // Body:

  jcb_e13_row_dofs_type<T>& lthis = const_cast<jcb_e13_row_dofs_type<T>&>(*this);
  const matrix_type& result = reinterpret_cast<matrix_type&>(lthis);
 
  // Postconditions:

  // Exit:

  return result;
}

template <typename T>
jcb_e13_row_dofs_type<T>* 
jcb_e13_row_dofs_type<T>::clone() const
{
  // Preconditions:

  // Body:

  jcb_e13_row_dofs_type<T>* result = new jcb_e13_row_dofs_type<T>();

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
ostream& operator<<(ostream& xos, const jcb_e13_row_dofs_type<T>& xrdt)
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

#endif // ifndef JCB_E13_IMPL_H
