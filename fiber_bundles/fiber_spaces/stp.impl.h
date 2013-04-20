

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for stp facet function templates.


#ifndef STP_IMPL_H
#define STP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STP_H
#include "stp.h"
#endif

namespace fiber_bundle
{

namespace stp_algebra
{

template <typename T0, typename T1> 
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
symmetric_product(const T0& x0, const T1& x1)
{
  // Preconditions:

  require(precondition_of(symmetric_product(x0, x1, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P + T1::P, VST>::tp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.tp_prototype(x0.p() + x1.p()).clone());

  symmetric_product(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(symmetric_product(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T0, typename T1> 
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
symmetric_product(const T0& x0, const T1& x1, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(symmetric_product(x0, x1, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P + T1::P, VST>::tp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_tp(x0.p(xauto_access) + x1.p(xauto_access),
                                             xauto_access));

  symmetric_product(x0, x1, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(symmetric_product(x0, x1, *result, xauto_access)));

  // Exit:

  return result;
}
  
} // namespace stp_algebra

} // namespace fiber_bundle

#endif // ifndef STP_IMPL_H
