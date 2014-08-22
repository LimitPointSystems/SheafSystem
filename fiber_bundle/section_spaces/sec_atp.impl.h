
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
// Implementation for sec_atp facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_H
#include "ComLimitPoint/fiber_bundle/sec_atp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

///
template <typename V0, typename V1, typename VR>
void
hook_functor<V0, V1, VR>::
operator()(const V0& x0, const V1& x1, VR& xresult)
{
  // Preconditions:

  require(precondition_of(hook(x0, x1, xresult)));

  // Body:

  hook(x0, x1, xresult);

  // Postconditions:

  ensure(postcondition_of(hook(x0, x1, xresult)));

  // Exit:

  return;
}

///
template <typename V0, typename VR>
void
star_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(star(x0, xresult)));

  // Body:

  star(x0, xresult);

  // Postconditions:

  ensure(postcondition_of(star(x0, xresult)));

  // Exit:

  return;
}

///
template <typename V0, typename V1, typename VR>
void
wedge_functor<V0, V1, VR>::
operator()(const V0& x0, const V1& x1, VR& xresult)
{
  // Preconditions:

  require(precondition_of(wedge(x0, x1, xresult)));

  // Body:

  wedge(x0, x1, xresult);

  // Postconditions:

  ensure(postcondition_of(wedge(x0, x1, xresult)));

  // Exit:

  return;
}

//==============================================================================

///
template <typename S0, typename S1, typename SR>
void hook(const S0& x0, const S1& x1, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 1);

 // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename S1::fiber_type::volatile_type V1;
  typedef typename SR::fiber_type::volatile_type VR;
  hook_functor<V0, V1, VR> f;
  binary_op(x0, x1, xresult, f, false);

  // Set the variance of the result.

  //x0.is_p_form(false) ? xresult.put_is_p_form(false)
  //                    : xresult.put_is_p_vector(false);
  xresult.put_variance(hook(x0.variance(false)), false);


  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  //ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));
  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));


  // Exit:

  return;
}

///
template <typename S0, typename SR>
void star(const S0& x0, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename SR::fiber_type::volatile_type VR;
  star_functor<V0, VR> f;
  unary_op(x0, xresult, f, false);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do no need to set the variance
  // of the result because it does not change.

  define_old_variable(bool old_xresult_is_p_form = xresult.is_p_form(false));

  if(x0.p() > 0)
  {
    xresult.put_variance( star(x0.variance(false), x0.dd()), false );
  }

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

///
template <typename S0, typename S1, typename SR>
void wedge(const S0& x0, const S1& x1, SR& xresult, bool xauto_access)
{
 // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) >= xresult.dd(xauto_access));
  require(x1.dd(xauto_access) >= xresult.dd(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) + x1.p(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename S1::fiber_type::volatile_type V1;
  typedef typename SR::fiber_type::volatile_type VR;
  wedge_functor<V0, V1, VR> f;
  binary_op(x0, x1, xresult, f, false);

  // Set the variance of the result.

  xresult.put_variance(wedge(x0.variance(false), x1.variance(false)), false);

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    wedge(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}


} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_ATP_IMPL_H
