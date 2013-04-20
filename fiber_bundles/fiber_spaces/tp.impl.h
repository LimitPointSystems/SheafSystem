

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for tp facet function templates.

#ifndef TP_IMPL_H
#define TP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{

namespace tp_algebra
{

//==============================================================================
// TP FACET
//==============================================================================

template <typename T0> 
typename tensor_traits<T0::P, typename T0::vector_space_type>::atp_type*
alt(const T0& x0)
{
  // Preconditions:

  require(precondition_of(alt(x0, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P, VST>::atp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.atp_prototype(x0.p()).clone());


  alt(x0, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(alt(x0, *result)));

  // Exit:

  return result;
}

template <typename T0> 
typename tensor_traits<T0::P, typename T0::vector_space_type>::stp_type*
sym(const T0& x0)
{
  // Preconditions:

  require(precondition_of(sym(x0, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P, VST>::stp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.stp_prototype(x0.p()).clone());

  sym(x0, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(sym(x0, *result)));

  // Exit:

  return result;
}


template <typename T0> 
typename tensor_traits<T0::P, typename T0::vector_space_type>::atp_type*
alt(const T0& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(alt(x0, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P, VST>::atp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_atp(x0.p(xauto_access), xauto_access));
  
  alt(x0, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(alt(x0, *result, xauto_access)));

  // Exit:

  return result;
}


template <typename T0> 
typename tensor_traits<T0::P, typename T0::vector_space_type>::stp_type*
sym(const T0& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(sym(x0, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P, VST>::stp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_stp(x0.p(xauto_access), xauto_access));
  
  sym(x0, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(sym(x0, *result, xauto_access)));

  // Exit:

  return result;
}

template <typename T0, typename T1> 
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
tensor(const T0& x0, const T1& x1)
{
  // Preconditions:

  require(precondition_of(tensor(x0, x1, *result)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P + T1::P, VST>::tp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.tp_prototype(x0.p() + x1.p()).clone());

  tensor(x0, x1, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(tensor(x0, x1, *result)));

  // Exit:

  return result;
}

template <typename T0, typename T1> 
typename tensor_traits<T0::P + T1::P, typename T0::vector_space_type>::tp_type*
tensor(const T0& x0, const T1& x1, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(tensor(x0, x1, *result, xauto_access)));

  // Body:

  typedef typename T0::vector_space_type VST;
  typedef typename tensor_traits<T0::P + T1::P, VST>::tp_type return_type;

  return_type* result =
    reinterpret_cast<return_type*>(x0.new_tp(x0.p(xauto_access) + x1.p(xauto_access),
                                             xauto_access));

  tensor(x0, x1, *result, xauto_access);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(tensor(x0, x1, *result, xauto_access)));

  // Exit:

  return result;
}
  
} // end namespace tp_algebra

} // end namespace fiber_bundle

#endif // ifndef TP_IMPL_H
