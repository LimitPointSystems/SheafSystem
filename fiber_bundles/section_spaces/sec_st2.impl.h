
// $RCSfile: sec_st2.impl.h,v $ $Revision: 1.11 $ $Date: 2013/01/12 17:17:12 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for sec_st2 facet function templates.

#ifndef SEC_ST2_IMPL_H
#define SEC_ST2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SEC_ST2_H
#include "sec_st2.h"
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

#endif // ifndef SEC_ST2_IMPL_H
