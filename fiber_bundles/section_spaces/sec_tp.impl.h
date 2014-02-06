
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

// Implementation for sec_tp facet function templates.

#ifndef SEC_TP_IMPL_H
#define SEC_TP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SEC_TP_H
#include "sec_tp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

///
template <typename V0, typename VR>
void
alt_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(alt(x0, xresult)));

  // Body:

  alt(x0, xresult);

  // Postconditions:

  ensure(postcondition_of(alt(x0, xresult)));

  // Exit:

  return;
}

///
template <typename V0, typename VR>
void
sym_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(sym(x0, xresult)));

  // Body:

  sym(x0, xresult);

  // Postconditions:

  ensure(postcondition_of(sym(x0, xresult)));

  // Exit:

  return;
}

///
template <typename V0, typename V1, typename VR>
void
tensor_functor<V0, V1, VR>::
operator()(const V0& x0, const V1& x1, VR& xresult)
{
  // Preconditions:

  require(precondition_of(tensor(x0, x1, xresult)));

  // Body:

  tensor(x0, x1, xresult);

  // Postconditions:

  ensure(postcondition_of( tensor(x0, x1, xresult)));

  // Exit:

  return;
}

///
template <typename V0, typename VR>
void
contract_functor<V0, VR>::
operator()(const V0& x0, VR& xresult)
{
  // Preconditions:

  require(precondition_of(contract(x0, _p, _q, xresult)));

  // Body:

  contract(x0, _p, _q, xresult);

  // Postconditions:

  ensure(postcondition_of(contract(x0, _p, _q, xresult)));

  // Exit:

  return;
}

//==============================================================================

///
template <typename GT, typename AT>
void alt(const GT& x0, AT& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename GT::fiber_type::volatile_type V0;
  typedef typename AT::fiber_type::volatile_type VR;
  alt_functor<V0, VR> f;
  unary_op(x0, xresult, f, false);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(false), false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

///
template <typename GT, typename ST>
void sym(const GT& x0, ST& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename GT::fiber_type::volatile_type V0;
  typedef typename ST::fiber_type::volatile_type VR;
  sym_functor<V0, VR> f;
  unary_op(x0, xresult, f, false);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(false), false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

///
template <typename S0, typename S1, typename SR>
void tensor(const S0& x0, const S1& x1, SR& xresult, bool xauto_access)
{

  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(xresult.dd(xauto_access) == x0.dd(xauto_access));

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
  tensor_functor<V0, V1, VR> f;
  binary_op(x0, x1, xresult, f, xauto_access);

  // Set the variance of the result.

  xresult.put_variance(
    tensor_product(x0.variance(false), x1.variance(false)), false);


  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

///
template <typename S0, typename SR>
void contract(const S0& x0, int xp, int xq, SR& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(xp != xq);
  require(xp >= 0 && xp < x0.p(xauto_access));
  require(xq >= 0 && xq < x0.p(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 2);
  require(x0.is_contravariant(xp, xauto_access) != \
    x0.is_contravariant(xq, xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename SR::fiber_type::volatile_type VR;
  contract_functor<V0, VR> f(xp, xq);
  unary_op(x0, xresult, f, xauto_access);

  // Set the variance of the result.

  xresult.put_variance(contract(x0.variance(false), xp, xq), false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    contract(x0.variance(xauto_access), xp, xq));
  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));

  // Exit:

  return;
}

template<>
void contract(const sec_t2_e2& x0, int xp, int xq, sec_at0& xresult,
              bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(xp != xq);
  require(xp >= 0 && xp < x0.p(xauto_access));
  require(xq >= 0 && xq < x0.p(xauto_access));
  require(x0.is_contravariant(xp, xauto_access) != \
    x0.is_contravariant(xq, xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef sec_t2_e2::fiber_type::volatile_type V0;
  typedef sec_at0::fiber_type::volatile_type VR;
  contract_functor<V0, VR> f(xp, xq);
  unary_op(x0, xresult, f, xauto_access);


  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));
  //ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

template<>
void contract(const sec_t2_e3& x0, int xp, int xq, sec_at0& xresult,
              bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(xp != xq);
  require(xp >= 0 && xp < x0.p(xauto_access));
  require(xq >= 0 && xq < x0.p(xauto_access));
  require(x0.is_contravariant(xp, xauto_access) != \
    x0.is_contravariant(xq, xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef sec_t2_e3::fiber_type::volatile_type V0;
  typedef sec_at0::fiber_type::volatile_type VR;
  contract_functor<V0, VR> f(xp, xq);
  unary_op(x0, xresult, f, xauto_access);


  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));
  //ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

} // namespace fiber_bundle

#endif // ifndef SEC_TP_IMPL_H
