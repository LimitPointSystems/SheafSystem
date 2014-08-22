
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

// Implementation for sec_vd facet function templates.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_IMPL_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_IMPL_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ASSERT_CONTRACT_H
#include "ComLimitPoint/sheaf/assert_contract.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_H
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_SECTION_EVALUATOR_H
#include "ComLimitPoint/fiber_bundle/section_evaluator.h"
#endif

namespace fiber_bundle
{

namespace sec_vd_algebra
{

///
template <typename S0, typename S1, typename SR, typename F>
void
binary_op(const S0& x0, const S1& x1, SR& xresult, F xfunctor,
          bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require((const_cast<S0&>(x0)).discretization_ct(xauto_access) == \
          (const_cast<S1&>(x1)).discretization_ct(xauto_access));
  require((const_cast<S0&>(x0)).discretization_ct(xauto_access) == \
           xresult.discretization_ct(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Create temporary volatile fiber type instances.

  typedef typename S0::fiber_type::volatile_type volatile_type_0;
  typedef typename S1::fiber_type::volatile_type volatile_type_1;
  typedef typename SR::fiber_type::volatile_type volatile_type_r;

  volatile_type_0* lx0_fiber = x0.fiber_prototype().lite_prototype().clone();
  volatile_type_1* lx1_fiber = x1.fiber_prototype().lite_prototype().clone();
  volatile_type_r* lxresult_fiber =
    xresult.fiber_prototype().lite_prototype().clone();

  // Get pointers to the volatile fiber row_dofs.

  //$$SCRIBBLE:
  //  It would be nice if we didn't have to explicitly create these
  //  pointers.  We could create additional get/put_discretization_dofs
  //  functions to simplify things; but, at the cost of some efficiency.

  ///@issue How do we ensure that this dof type is the same as that
  ///       of the fibers?

  typedef sec_vd::dof_type dof_type;

  // Iterate over the discretization performing the specified operation
  // (via the functor argument) on the dofs.

  ///$$SCRIBBLE: Changes to the get/put dofs interface are planned and we will
  ///            have to modify the following when the changes are in place.

  S0& lx0 = const_cast<S0&>(x0);
  S1& lx1 = const_cast<S1&>(x1);

  size_type ldisc_ct = lx0.discretization_ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Gather all the fiber dofs of this at the same base point as result.

    lx0.get_fiber(i, *lx0_fiber);
    lx1.get_fiber(i, *lx1_fiber);

    // Compute the result.

    xfunctor(*lx0_fiber, *lx1_fiber, *lxresult_fiber);

    // Store the dofs in the result field.

    xresult.put_fiber(i, *lxresult_fiber);
  }

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  delete lx0_fiber;
  delete lx1_fiber;
  delete lxresult_fiber;

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S0, typename SR, typename F>
void
binary_op(const S0& x0, const vd_value_type& xvalue, SR& xresult, F xfunctor,
          bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require((const_cast<S0&>(x0)).discretization_ct(xauto_access) == \
           xresult.discretization_ct(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Create temporary volatile fiber type instances.

  typedef typename S0::fiber_type::volatile_type volatile_type_0;
  typedef typename SR::fiber_type::volatile_type volatile_type_r;

  volatile_type_0* lx0_fiber = x0.fiber_prototype().lite_prototype().clone();
  volatile_type_r* lxresult_fiber =
    xresult.fiber_prototype().lite_prototype().clone();

  // Get pointers to the volatile fiber row_dofs.

  //$$SCRIBBLE:
  //  It would be nice if we didn't have to explicitly create these
  //  pointers.  We could create additional get/put_discretization_dofs
  //  functions to simplify things; but, at the cost of some efficiency.

  ///@issue How do we ensure that this dof type is the same as that
  ///       of the fibers?

  typedef sec_vd::dof_type dof_type;

  // Iterate over the discretization performing the specified operation
  // (via the functor argument) on the dofs.

  ///$$SCRIBBLE: Changes to the get/put dofs interface are planned and we will
  ///            have to modify the following when the changes are in place.

  S0& lx0 = const_cast<S0&>(x0);

  size_type ldisc_ct = lx0.discretization_ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Gather all the fiber dofs of this at the same base point as result.

    lx0.get_fiber(i, *lx0_fiber);

    // Compute the result.

    xfunctor(*lx0_fiber, xvalue, *lxresult_fiber);

    // Store the dofs in the result field.

    xresult.put_fiber(i, *lxresult_fiber);
  }

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  delete lx0_fiber;
  delete lxresult_fiber;

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S0, typename SR, typename F>
void
unary_op(const S0& x0, SR& xresult, F xfunctor, bool xauto_access)

{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require((const_cast<S0&>(x0)).discretization_ct(xauto_access) == \
           xresult.discretization_ct(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Create temporary volatile fiber type instances.

  typedef typename S0::fiber_type::volatile_type volatile_type_0;
  typedef typename SR::fiber_type::volatile_type volatile_type_r;

  volatile_type_0* lx0_fiber = x0.fiber_prototype().lite_prototype().clone();
  volatile_type_r* lxresult_fiber =
    xresult.fiber_prototype().lite_prototype().clone();

  // Get pointers to the volatile fiber row_dofs.

  typedef sec_vd::dof_type dof_type;

  // Iterate over the discretization performing the specified
  // (via the functor argument) on the dofs.

  S0& lx0 = const_cast<S0&>(x0);
  size_type ldisc_ct = lx0.discretization_ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Gather all the fiber dofs of this at the same base point as result.

    lx0.get_fiber(i, *lx0_fiber);

    // Compute the result.

    xfunctor(*lx0_fiber, *lxresult_fiber);

    // Store the dofs in the result field.

    xresult.put_fiber(i, *lxresult_fiber);
  }

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  delete lx0_fiber;
  delete lxresult_fiber;

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S0, typename F>
void
unary_op(S0& x0, const vd_value_type& x1, F xfunctor, bool xauto_access)

{
  // Preconditions:

  require(x0.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_write_access(true);
  }

  // Create a temporary volatile fiber type instance.

  typedef typename S0::fiber_type::volatile_type volatile_type_0;

  volatile_type_0* lx0_fiber = x0.fiber_prototype().lite_prototype().clone();

  // Get ap pointer to the volatile fiber row_dofs.

  typedef sec_vd::dof_type dof_type;

  // Iterate over the discretization performing the specified
  // (via the functor argument) on the dofs.

  S0& lx0 = const_cast<S0&>(x0);
  size_type ldisc_ct = lx0.discretization_ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Gather all the fiber dofs of this at the same base point as result.

    lx0.get_fiber(i, *lx0_fiber);

    // Compute the result.

    xfunctor(*lx0_fiber, x1);

    // Store the dofs in the result field.

    x0.put_fiber(i, *lx0_fiber);
  }

  if(xauto_access)
  {
    x0.release_access();
  }

  delete lx0_fiber;

  // Postconditions:

  // Exit:

  return;
}

///
template <typename S0, typename SR, typename F>
void
unary_op(const S0& x0, SR& xresult1, SR& xresult2, F xfunctor,
         bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult1.state_is_auto_read_write_accessible(xauto_access));
  require(xresult2.state_is_auto_read_write_accessible(xauto_access));
  require((const_cast<S0&>(x0)).discretization_ct(xauto_access) == \
           xresult1.discretization_ct(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult1.get_read_write_access(true);
    xresult2.get_read_write_access(true);
  }

  // Create temporary volatile fiber type instances.

  typedef typename S0::fiber_type::volatile_type volatile_type_0;
  typedef typename SR::fiber_type::volatile_type volatile_type_r;

  volatile_type_0 lx0_fiber;
  volatile_type_r lxresult1_fiber;
  volatile_type_r lxresult2_fiber;

  // Get pointers to the volatile fiber row_dofs.

  typedef sec_vd::dof_type dof_type;

  S0& lx0 = const_cast<S0&>(x0);
  size_type ldisc_ct = lx0.discretization_ct();

  // Iterate over the discretization performing the specified
  // (via the functor argument) on the dofs.

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    // Gather all the fiber dofs of this at the same base point as result.

    lx0.get_fiber(i, lx0_fiber);

    // Compute the result.

    xfunctor(lx0_fiber, lxresult1_fiber, lxresult2_fiber);

    // Store the dofs in the result fields.

    xresult1.put_fiber(i, lxresult1_fiber);
    xresult2.put_fiber(i, lxresult2_fiber);
  }

  if(xauto_access)
  {
    x0.release_access();
    xresult1.release_access();
    xresult2.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}
  
} // namespace sec_vd_algebra

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_IMPL_H
