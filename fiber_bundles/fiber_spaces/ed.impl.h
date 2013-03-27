
// $RCSfile: ed.impl.h,v $ $Revision: 1.10 $ $Date: 2013/03/13 00:58:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for ed facet function templates.

#ifndef ED_IMPL_H
#define ED_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ED_H
#include "ed.h"
#endif

namespace fiber_bundle
{

namespace ed_algebra
{

template <typename T>
vd_value_type operator*(const T& x0, const T& x1)
{
  // Preconditions:

  require(precondition_of(dot(x0, x1)));

  // Body:
 
  vd_value_type result = dot(x0, x1);

  // Postconditions:

  ensure(postcondition_of(dot(x0, x1)));

  // Exit:

  return result;
}

template <typename T>
void normalize(T& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(normalize(x0, x0, xauto_access)));

  // Body:

  normalize(x0, x0, xauto_access);

  // Postconditions:

  ensure(postcondition_of(normalize(x0, x0, xauto_access)));

  // Exit:
}

template <typename T>
void normalize(T& x0)
{
  // Preconditions:

  require(precondition_of(normalize(x0, x0)));

  // Body:

  normalize(x0, x0);

  // Postconditions:

  ensure(postcondition_of(normalize(x0, x0)));

  // Exit:
}
  
} // namespace ed_algebra

} // namespace fiber_bundle

#endif // ifndef ED_IMPL_H
