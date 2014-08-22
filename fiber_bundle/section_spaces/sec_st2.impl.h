
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

// Implementation for sec_st2 facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ST2_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_ST2_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ST2_H
#include "ComLimitPoint/fiber_bundle/sec_st2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

template <typename V0, typename VR>
void
trace_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(xresult = trace(x0)));

  // Body:

  //trace(x0, xresult);
  xresult = trace(x0);

  // Postconditions:

  ensure(postcondition_of(xresult = trace(x0)));

  // Exit:

  return;
}


template <typename V0, typename VR>
void
determinant_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(xresult = determinant(x0)));

  // Body:

  vd_value_type lcomp;
  determinant(x0, lcomp);
  xresult.put_component(0, lcomp);
  
  //xresult = determinant(x0);

  // Postconditions:

  ensure(postcondition_of(xresult = determinant(x0)));

  // Exit:

  return;
}


//==============================================================================

///
template <typename S0, typename SR>
void trace(const S0& x0, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename SR::fiber_type::volatile_type VR;
  trace_functor<V0, VR> f;
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
template <typename S0, typename SR>
void determinant(const S0& x0, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename SR::fiber_type::volatile_type VR;
  determinant_functor<V0, VR> f;
  unary_op(x0, xresult, f, xauto_access);

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ST2_IMPL_H
