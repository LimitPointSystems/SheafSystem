
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

// Implementation for sec_ed facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ED_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_ED_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ED_H
#include "ComLimitPoint/fiber_bundle/sec_ed.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

// template <typename T, typename R>
// void
// dot_functor<T, R>::
// operator()(const T& x0, const T& x1, R& xresult)
// {
//   // Preconditions:

//   require(precondition_of(xresult = dot(x0, x1)));

//   // Body:

//   //@issue Do we want to add a new preallocated "dot" function to ed
//   //       which takes an at0 return type?

//   xresult = dot(x0, x1);

//   // Postconditions:

//   ensure(postcondition_of(xresult = dot(x0, x1)));

//   // Exit:

//   return;
// }


// template <typename T, typename R>
// void
// length_functor<T, R>::
// operator()(const T& x0, R& xresult)
// {
//   // Preconditions:

//   require(precondition_of(xresult = length(x0)));

//   // Body:

//    //@issue Do we want to add a new preallocated "length" function to ed
//    //       which takes an at0 return type?

//   xresult = length(x0);

//   // Postconditions:

//   ensure(postcondition_of(xresult = length(x0)));

//   // Exit:

//   return;
// }


// template <typename T>
// void
// put_length_functor<T>::
// operator()(T& x0, const vd_value_type& xlength)
// {
//   // Preconditions:

//   require(precondition_of(put_length(x0, xlength)));

//   // Body:

//   put_length(x0, xlength);

//   // Postconditions:

//   ensure(postcondition_of(put_length(x0, xlength)));

//   // Exit:

//   return;
// }

// template <typename T>
// void
// normalize_functor<T>::
// operator()(const T& x0, T& xresult)
// {
//   // Preconditions:

//   require(precondition_of(normalize(x0, xresult)));

//   // Body:

//   normalize(x0, xresult);

//   // Postconditions:

//   ensure(postcondition_of(normalize(x0, xresult)));

//   // Exit:

//   return;
// }

//==============================================================================

///
template <typename S, typename SR>
void dot(const S& x0, const S& x1, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(x0.is_same_type(&x1));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
  }

  typedef typename S::fiber_type::volatile_type V;
  typedef typename SR::fiber_type::volatile_type VR;
  dot_functor<V, VR> f;
  binary_op(x0, x1, xresult, f, xauto_access);

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S, typename SR>
void length(const S& x0, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  typedef typename S::fiber_type::volatile_type V;
  typedef typename SR::fiber_type::volatile_type VR;
  length_functor<V, VR> f;
  unary_op(x0, xresult, f, xauto_access);

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S>
void put_length(S& x0, const vd_value_type& xlength, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));
  ensure(xlength >= 0.0);

  // Body:

  if(xauto_access)
  {
    x0.get_read_write_access(true);
  }

  put_length_functor<typename S::fiber_type::volatile_type> f;
  unary_op(x0, xlength, f, xauto_access);

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("length(x0, xauto_access) == xlength"));

  // Exit:

  return;
}

///
template <typename S, typename SR>
void normalize(const S& x0, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.is_same_type(&xresult));
  require(x0.is_p_form(xauto_access) == xresult.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  normalize_functor<typename S::fiber_type::volatile_type> f;
  unary_op(x0, xresult, f, xauto_access);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));
  ensure(unexecutable("length(xresult, xauto_access) == 1.0"));

  // Exit:

  return;
}

///
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

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ED_IMPL_H
