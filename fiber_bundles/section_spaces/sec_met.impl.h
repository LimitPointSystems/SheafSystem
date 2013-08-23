
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Implementation for sec_met facet function templates.

#ifndef SEC_MET_IMPL_H
#define SEC_MET_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef SEC_MET_H
#include "sec_met.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

//==============================================================================

///
template <typename VMET, typename VVECTOR, typename VR>
void
lower_functor<VMET, VVECTOR, VR>::
operator()(const VMET& xmet, const VVECTOR& xvector, VR& xresult)
{
  // Preconditions:

  require(precondition_of(lower(xmet, xvector, xresult)));

  // Body:

  lower(xmet, xvector, xresult);

  // Postconditions:

  ensure(postcondition_of(lower(xmet, xvector, xresult)));

  // Exit:

  return;
}

///
template <typename VMET, typename VCOVECTOR, typename VR>
void
raise_functor<VMET, VCOVECTOR, VR>::
operator()(const VMET& xmet, const VCOVECTOR& xcovector, VR& xresult)
{
  // Preconditions:

  require(precondition_of( raise(xmet, xcovector, xresult)));

  // Body:

   raise(xmet, xcovector, xresult);

  // Postconditions:

  ensure(postcondition_of( raise(xmet, xcovector, xresult)));

  // Exit:

  return;
}


//==============================================================================

///
template <typename SMET, typename SVECTOR, typename SR>
void lower(const SMET& xmetric, const SVECTOR& xvector, SR& xresult,
           bool xauto_access)
{
 // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_covariant(0, xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual;

  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xvector.get_read_access();
    xresult.get_read_write_access(true);
  }
 
  typedef typename SMET::fiber_type::volatile_type VMET;
  typedef typename SVECTOR::fiber_type::volatile_type VVECTOR;
  typedef typename SR::fiber_type::volatile_type VR;
  lower_functor<VMET, VVECTOR, VR> f;
  binary_op(xmetric, xvector, xresult, f, xauto_access);


  // Make sure the result is covariant/p_form.

  xresult.put_is_p_form(false);

  if(xauto_access)
  {
    xmetric.release_access();
    xvector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));     //  is_dual

  // Exit:

  return;

}

///
template <typename SMET, typename SCOVECTOR, typename SR>
void raise(const SMET& xmetric, const SCOVECTOR& xcovector, SR& xresult,
           bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_contravariant(0, xauto_access));
  require(xcovector.is_covariant(0, xauto_access));   //  is_dual;

  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xcovector.get_read_access();
    xresult.get_read_write_access(true);
  }

  typedef typename SMET::fiber_type::volatile_type VMET;
  typedef typename SCOVECTOR::fiber_type::volatile_type VCOVECTOR;
  typedef typename SR::fiber_type::volatile_type VR;
  raise_functor<VMET, VCOVECTOR, VR> f;
  binary_op(xmetric, xcovector, xresult, f, xauto_access);

  // Make sure the result is contravariant/p_vector.

  xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    xmetric.release_access();
    xcovector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

} // namespace fiber_bundle


#endif // ifndef SEC_MET_IMPL_H
