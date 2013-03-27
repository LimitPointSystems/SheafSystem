
// $RCSfile: atp.impl.h,v $ $Revision: 1.13 $ $Date: 2013/03/13 00:58:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for atp facet function templates.

#ifndef ATP_IMPL_H
#define ATP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATP_H
#include "atp.h"
#endif

namespace fiber_bundle 
{

namespace atp_algebra
{

//==============================================================================
// ATP FACET:
//==============================================================================

template <typename T0, typename T1> 
typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
hook(const T0& x0, const T1& x1)
{
  // Preconditions:

  require(precondition_of(hook(x0, x1, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), VST>::atp_type return_type;

  // Can not cast to the return type here because the compile uses the
  // at0_lite conversion operator to double to find a conversion path
  // for hook(T0&, T1&, bool).

  atp_lite* result = x0.atp_prototype(x0.p() - x1.p()).clone();

  hook(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(hook(x0, x1, *result)));

  // Exit:

  return reinterpret_cast<return_type*>(result);
}


template <typename T0, typename T1> 
typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
wedge(const T0& x0, const T1& x1)
{
  // Preconditions:

  require(precondition_of(wedge(x0, x1, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), VST>::atp_type return_type;

  // Can not cast to the return type here because the compile uses the
  // at0_lite conversion operator to double to find a conversion path
  // for wedge(T0&, T1&, bool).

  atp_lite* result = x0.atp_prototype(x0.p() + x1.p()).clone();

  wedge(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(wedge(x0, x1, *result)));

  // Exit:

  return reinterpret_cast<return_type*>(result);
}

template <typename T0, typename T1> 
typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
hook(const T0& x0, const T1& x1, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(hook(x0, x1, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<static_cast<int>(T0::P) - static_cast<int>(T1::P), VST>::atp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_atp(x0.p(xauto_access) - x1.p(xauto_access),
                                              xauto_access));

  hook(x0, x1, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(hook(x0, x1, *result, xauto_access)));

  // Exit:

  return result;
}

template <typename T0, typename T1> 
typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), typename T0::vector_space_type>::atp_type*
wedge(const T0& x0, const T1& x1, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(wedge(x0, x1, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<static_cast<int>(T0::P) + static_cast<int>(T1::P), VST>::atp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_atp(x0.p(xauto_access) + x1.p(xauto_access), xauto_access));

  wedge(x0, x1, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(wedge(x0, x1, *result, xauto_access)));

  // Exit:

  return result;
}
  
} // namespace atp_algebra
  
} // namespace fiber_bundle

#endif // ifndef ATP_IMPL_H
