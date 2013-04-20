

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for sec_stp facet function templates.

#ifndef SEC_STP_IMPL_H
#define SEC_STP_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SEC_STP_H
#include "sec_stp.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

template <typename V0, typename V1, typename VR>
void
symmetric_product_functor<V0, V1, VR>::
operator()(const V0& x0, const V1& x1, VR& xresult)
{
   symmetric_product(x0, x1, xresult);
}

//==============================================================================

///
template <typename S0, typename S1, typename SR>
void symmetric_product(const S0& x0, const S1& x1, SR& xresult,
                       bool xauto_access)
{
  typedef typename S0::fiber_type::volatile_type V0;
  typedef typename S1::fiber_type::volatile_type V1;
  typedef typename SR::fiber_type::volatile_type VR;
  symmetric_product_functor<V0, V1, VR> f;
  binary_op(x0, x1, xresult, f, xauto_access);
}


} // namespace fiber_bundle

#endif // ifndef SEC_STP_IMPL_H
