
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for tp facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TP_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_TP_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TP_H
#include "ComLimitPoint/fiber_bundle/tp.h"
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

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_TP_IMPL_H
