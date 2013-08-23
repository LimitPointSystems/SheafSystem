
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

/// @file
/// Implementation for class sec_at2_e2.


#include "sec_at2_e2.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "sec_atp_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_AT2_E2
//==============================================================================

//==============================================================================
// AT2_E2 FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at2_e2::
sec_at2_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_at2_e2::
sec_at2_e2(const sec_rep_space_member& xother)
{

  // Preconditions:

  require(xother.is_attached() ? xother.state_is_read_accessible() : true);

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached());
  ensure(is_same_state(&xother));
  ensure(is_same_restriction(&xother));

}

fiber_bundle::sec_at2_e2::
sec_at2_e2(sec_rep_space* xhost,
           abstract_poset_member& xbase_mbr,
           int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_at2_e2::
sec_at2_e2(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Body:

  new_jim_state(xhost, xdof_map, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_at2_e2::
sec_at2_e2(const sec_rep_space* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_at2_e2::
sec_at2_e2(const sec_rep_space* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_at2_e2::
sec_at2_e2(const sec_rep_space* xhost, const string& xname)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
  ensure(!is_restricted());

}


fiber_bundle::sec_at2_e2::
sec_at2_e2(const namespace_poset* xnamespace,
           const poset_path& xpath,
           bool xauto_access)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_at2_e2&
fiber_bundle::sec_at2_e2::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::sec_at2_e2&
fiber_bundle::sec_at2_e2::
operator=(const sec_at2_e2& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::sec_at2_e2&
fiber_bundle::sec_at2_e2::
operator=(const at2_e2& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_at2_e2&
fiber_bundle::sec_at2_e2::
operator=(const at2_e2_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_at2_e2::
~sec_at2_e2()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_at2_e2::fiber_type&
fiber_bundle::sec_at2_e2::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// AT2 FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_at2_e2::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::sec_at2_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_at2_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_at2_e2*
fiber_bundle::sec_at2_e2::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_at2_e2 *result = new sec_at2_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_at2_e2::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const at2_e2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_at2_e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const sec_at2_e2*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_at2_e2::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(sec_atp::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? dd() == 2 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

namespace
{
  using namespace fiber_bundle::atp_algebra;

  class hook_functor
  {
  public:
    void operator()(const e2_lite& x0, const e2_lite& x1,
                    at0_lite& xresult) const
    {
      hook(x0, x1, xresult);
    }

    void operator()(const at2_e2_lite& x0, const e2_lite& x1,
                    e2_lite& xresult) const
    {
      hook(x0, x1, xresult);
    }
  };

  class star_functor
  {
  public:
    void operator()(const at2_e2_lite& x0, at0_lite& xresult) const
    {
      star(x0, xresult);
    }

    void operator()(const at0_lite& x0, at2_e2_lite& xresult) const
    {
      star(x0, xresult);
    }

    void operator()(const e2_lite& x0, e2_lite& xresult) const
    {
      star(x0, xresult);
    }
  };

  class wedge_functor
  {
  public:
    void operator()(const e2_lite& x0, const e2_lite& x1,
                    at2_e2_lite& xresult) const
    {
      wedge(x0, x1, xresult);
    }
  };

} //end unnamed namespace

//==============================================================================

#include "sec_vd.impl.h"
#include "sec_e2.h"
#include "sec_at0.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_atp_algebra::
hook(const sec_e2& x0, const sec_e2& x1, sec_at0& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 1);

  // Body:

  binary_op(x0, x1, xresult, hook_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(hook(x0.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
hook(const sec_at2_e2& x0, const sec_e2& x1, sec_e2& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 1);

  // Body:

  binary_op(x0, x1, xresult, hook_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(hook(x0.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));

  // Exit:

  return;
}


void
fiber_bundle::sec_atp_algebra::
star(const sec_at2_e2& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, star_functor(), xauto_access);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do not need to set the variance
  // of the result because it does not change.

  define_old_variable(\
    bool old_xresult_is_p_form = xresult.is_p_form(xauto_access));

  if(x0.p(xauto_access) > 0)
  {
    xresult.put_variance(star(x0.variance(xauto_access), x0.dd(xauto_access)),
                         xauto_access);
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
star(const sec_at0& x0, sec_at2_e2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, star_functor(), xauto_access);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do not need to set the variance
  // of the result because it does not change.

  define_old_variable(\
    bool old_xresult_is_p_form = xresult.is_p_form(xauto_access));

  if(x0.p(xauto_access) > 0)
  {
    xresult.put_variance(star(x0.variance(xauto_access), x0.dd(xauto_access)),
                         xauto_access);
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
star(const sec_e2& x0, sec_e2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, star_functor(), xauto_access);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do no need to set the variance
  // of the result because it does not change.

  define_old_variable(\
    bool old_xresult_is_p_form = xresult.is_p_form(xauto_access));

  if(x0.p(xauto_access) > 0)
  {
    xresult.put_variance(star(x0.variance(xauto_access), x0.dd(xauto_access)),
                         xauto_access);
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
wedge(const sec_e2& x0, const sec_e2& x1, sec_at2_e2& xresult,
      bool xauto_access)
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

  binary_op(x0, x1, xresult, wedge_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(wedge(x0.variance(xauto_access), 
                             x1.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    wedge(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

