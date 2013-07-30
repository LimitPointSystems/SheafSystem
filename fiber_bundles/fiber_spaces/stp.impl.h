

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
