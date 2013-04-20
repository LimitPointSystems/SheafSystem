

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for sec_jcb facet function templates.

#ifndef SEC_JCB_IMPL_H
#define SEC_JCB_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SEC_JCB_H
#include "sec_jcb.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

///
template <typename VJCB, typename VCOVECTOR, typename VR>
void
pull_functor<VJCB, VCOVECTOR, VR>::
operator()(const VJCB& xjcb, const VCOVECTOR& xcovector, VR& xresult)
{
  // Preconditions:

  require(precondition_of(pull(xjcb, xcovector, xresult)));

  // Body:

  pull(xjcb, xcovector, xresult);

  // Postconditions:

  ensure(postcondition_of(pull(xjcb, xcovector, xresult)));

  // Exit:

  return;
}

///
template <typename VJCB, typename VVECTOR, typename VR>
void
push_functor<VJCB, VVECTOR,  VR>::
operator()(const VJCB& xjcb, const VVECTOR& xvector, VR& xresult)
{
  // Preconditions:

  require(precondition_of( push(xjcb, xvector, xresult)));

  // Body:

   push(xjcb, xvector, xresult);

  // Postconditions:

  ensure(postcondition_of( push(xjcb, xvector, xresult)));

  // Exit:

  return;
}


//==============================================================================

///
template <typename SJCB, typename SCOVECTOR, typename SR>
void pull(const SJCB& xjcb, const SCOVECTOR& xcovector, SR& xresult,
          bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    xjcb.get_read_access();
    xcovector.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename SJCB::fiber_type::volatile_type VJCB;
  typedef typename SCOVECTOR::fiber_type::volatile_type VCOVECTOR;
  typedef typename SR::fiber_type::volatile_type VR;
  pull_functor<VJCB, VCOVECTOR, VR> f;
  binary_op(xjcb, xcovector, xresult, f, xauto_access);

  // Make sure the result is covariant/p_form.

  xresult.put_is_p_form(false);


  if(xauto_access)
  {
    xjcb.release_access();
    xcovector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access));

  // Exit:

  return;
}

///
template <typename SJCB, typename SVECTOR, typename SR>
void push(const SJCB& xjcb, const SVECTOR& xvector, SR& xresult,
          bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xvector.is_p_vector(xauto_access));

  // Body:

  if(xauto_access)
  {
    xjcb.get_read_access();
    xvector.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename SJCB::fiber_type::volatile_type VJCB;
  typedef typename SVECTOR::fiber_type::volatile_type VVECTOR;
  typedef typename SR::fiber_type::volatile_type VR;
  push_functor<VJCB, VVECTOR, VR> f;
  binary_op(xjcb, xvector, xresult, f, xauto_access);

 // Make sure the result is p_vector.

  xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    xjcb.release_access();
    xvector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_vector(xauto_access));

  // Exit:

  return;
}

} // namespace fiber_bundle

#endif // ifndef SEC_JCB_IMPL_H
