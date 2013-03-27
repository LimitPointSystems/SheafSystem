
// $RCSfile: st2.impl.h,v $ $Revision: 1.10 $ $Date: 2013/03/13 00:58:44 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for st2 facet function templates.


#ifndef ST2_IMPL_H
#define ST2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ST2_H
#include "st2.h"
#endif

namespace fiber_bundle
{

namespace st2_algebra
{

template <typename T, typename GLN>
T* to_principal_axes(const T& xlite, GLN& xtransform)
{
  // Preconditions:

  // Body:

  T* result = xlite.clone();

  to_principal_axes(xlite, xtransform, *result);

  // Postconditions:

  return result;

  // Exit:
}

template <typename T, typename GLN>
void to_principal_axes(const T& xlite, GLN& xtransform, T& xresult)
{
  // Preconditions:

  // Body:

  not_implemented(); //Specialized for some cases (See st2_e2 & st2_e3). 

  // Postconditions:

  // Exit:
}

template <typename T, typename GLN>
void to_principal_axes(const T& xlite, const T& xpd_lite,
                       GLN& xtransform, T& xresult)
{
  // Preconditions:

  // Body:

  not_implemented(); //Specialized for some cases (See st2_e2 & st2_e3). 

  // Postconditions:

  // Exit:
}
  
} // namespace st2_algebra

} // namespace fiber_bundle

#endif // ifndef ST2_IMPL_H
