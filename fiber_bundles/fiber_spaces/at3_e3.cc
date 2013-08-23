
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

// Implementation for class at3_e3.

#include "at3_e3.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS AT3_E3_LITE
//==============================================================================

//==============================================================================
// AT3_E3 FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at3_e3_lite::
at3_e3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_e3_lite::
at3_e3_lite(const at3_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_e3_lite&
fiber_bundle::at3_e3_lite::
operator=(const at3_e3_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::at3_e3_lite::
~at3_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::at3_e3_lite::
at3_e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_e3_lite&
fiber_bundle::at3_e3_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::at3_e3_lite::
operator at3_e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at3_e3_lite::
operator const at3_e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::at3_e3_lite::
at3_e3_lite(const value_type& xcomp)
{
  // Preconditions:

  // Body:

  put_components(xcomp);

  // Postconditions:

  // Exit:
}

void
fiber_bundle::at3_e3_lite::
put_components(const value_type& xcomp)
{
  // Preconditions:

  // Body:

  put_component(0, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (AT3) FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at3_e3_lite::
dd() const
{
  // Preconditions:

  // Body:

  int result = 3;

  // Postconditions:

  ensure(invariant());
  ensure(result == 3);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::at3_e3_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e3_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::at3_e3_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e3_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::at3_e3_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e3_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at3_e3_lite::
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
fiber_bundle::at3_e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at3_e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at3_e3_lite*
fiber_bundle::at3_e3_lite::
clone() const
{
  at3_e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new at3_e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at3_e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const at3_e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::at3_e3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(at3_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::at3_e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::at3_e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS AT3_E3
//==============================================================================

//==============================================================================
// AT3_E3 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at3_e3::
at3_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::at3_e3::
at3_e3(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::at3_e3::
at3_e3(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::at3_e3::
at3_e3(const poset_state_handle* xhost, const string& xname)
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
  // ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());

}

fiber_bundle::at3_e3::
at3_e3(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

}

fiber_bundle::at3_e3::
at3_e3(poset_state_handle* xhost, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(xhost, 0, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::at3_e3::
at3_e3(poset_state_handle& xhost,
       const row_dofs_type& xrdt,
       bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(&xhost, 0, false, xauto_access);

  if(xauto_access)
  {
    xhost.get_read_write_access();
  }

  *this = xrdt;

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(postcondition_of(new_jim_state(&xhost, 0, false, xauto_access)));

  // Exit:

  return;
}


fiber_bundle::at3_e3&
fiber_bundle::at3_e3::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  sheaf::row_dofs(*this) = xrdt;
  
  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

///
fiber_bundle::at3_e3&
fiber_bundle::at3_e3::
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

///
fiber_bundle::at3_e3&
fiber_bundle::at3_e3::
operator=(const at3_e3& xother)
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

fiber_bundle::at3_e3::
~at3_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::at3_e3::volatile_type&
fiber_bundle::at3_e3::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

///
fiber_bundle::at3_e3::volatile_type*
fiber_bundle::at3_e3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


void
fiber_bundle::at3_e3::
put_components(dof_type xcomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));

  // Exit:

  return;
}

fiber_bundle::at3_e3::
operator at3_e3::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at3_e3::
operator const at3_e3::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// AT3 FACET OF CLASS AT3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ATP FACET OF CLASS AT3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

//==============================================================================
// TP FACET OF CLASS AT3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS AT3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::at3_e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "at3_e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at3_e3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  string lmember_names = "component DOUBLE false ";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              at3::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp*
fiber_bundle::at3_e3::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e3::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::at3_e3::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e3::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::at3_e3::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e3::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at3_e3::
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
fiber_bundle::at3_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at3_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at3_e3*
fiber_bundle::at3_e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  at3_e3* result = new at3_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::at3_e3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const at3_e3*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;

}


bool
fiber_bundle::at3_e3::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(at3::invariant());

    // Invariances for this class:

    invariance((state_is_read_accessible() ? dd() == 3 : true));

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

#include "at0.h"
#include "at2_e3.h"

void
fiber_bundle::atp_algebra::
hook(const at3_e3& x0, const e3& x1, at2_e3& xresult,  bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // The hook operation is essentially a contract operation
  // on the first index.  In 3d this is pretty simple,
  // so we implement it explicitly for efficiency.
  
  // at3_e3 has just 1 component.

  vd_value_type a = x0.component(0);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  int lrank = 3;

  vd_value_type lcomp01 = lrank*( a*b2);
  vd_value_type lcomp02 = lrank*(-a*b1);
  vd_value_type lcomp12 = lrank*(-a*b0);

  xresult.put_component(0, lcomp01);
  xresult.put_component(1, lcomp02);
  xresult.put_component(2, lcomp12);


  // Set the variance of the result.

  x0.is_p_form(false) ? xresult.put_is_p_form(false)
                      : xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;

}

void
fiber_bundle::atp_algebra::
hook(const at3_e3_lite& x0, const e3_lite& x1, at2_e3_lite& xresult)
{
  // Preconditions:

  // Body:

  // The hook operation is essentially a contract operation
  // on the first index.  In 3d this is pretty simple,
  // so we implement it explicitly for efficiency.
  
  // at3_e3 has just 1 component.

  vd_value_type a = x0.component(0);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  int lrank = 3;

  vd_value_type lcomp01 = lrank*( a*b2);
  vd_value_type lcomp02 = lrank*(-a*b1);
  vd_value_type lcomp12 = lrank*(-a*b0);

  xresult.put_component(0, lcomp01);
  xresult.put_component(1, lcomp02);
  xresult.put_component(2, lcomp12);

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;

}

void
fiber_bundle::atp_algebra::
star(const at3_e3& x0, at0& xresult, bool xauto_access)
{
  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  vd_value_type a123 = x0.component(0);

  xresult.put_component(0, a123);

  // Set the variance of the result.

  // Nothing to do for at0. It's both a p_form and a p_vector.


  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
star(const at3_e3_lite& x0, at0_lite& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type a123 = x0.component(0);

  xresult.put_component(0, a123);
 
  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;
}

fiber_bundle::at0_lite*
fiber_bundle::atp_algebra::
star(const at3_e3_lite& x0)
{
  // Preconditions:

  // Body:

  at0_lite* result = new at0_lite();

  star(x0, *result);
 
  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

void
fiber_bundle::atp_algebra::
star(const at0& x0, at3_e3& xresult, bool xauto_access)
{
  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  vd_value_type lcomp123 = x0.component(0);

  xresult.put_component(0, lcomp123);

  // Set the variance of the result.

  define_old_variable(bool old_xresult_is_p_form = xresult.is_p_form(false));

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == old_xresult_is_p_form);

  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
star(const at0_lite& x0, at3_e3_lite& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type lcomp123 = x0.component(0);

  xresult.put_component(0, lcomp123);

  // Postconditions:

  ensure(xresult.component(0) == x0.component(0));

  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
wedge(const at2_e3& x0, const e3& x1, at3_e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    x1.get_read_access();
    xresult.get_read_write_access(true);
  }

  // The basis order we assume here is "e1^e2, e1^e3, e2^e3"
  // Don't confuse "e1, e2, e3" here with fibers with the same name.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);
  vd_value_type a2 = x0.component(2);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  vd_value_type lcomp = a0*b0 +a1*b1 + a2*b2;

  xresult.put_component(0, lcomp);


  // Set the variance of the result.

  x0.is_p_form(false) ? xresult.put_is_p_form(false)
                      : xresult.put_is_p_vector(false);


  if(xauto_access)
  {
    x0.release_access();
    x1.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
wedge(const at2_e3_lite& x0, const e3_lite& x1, at3_e3_lite& xresult)
{
  // Preconditions:

  // Body:

  // The basis order we assume here is "e1^e2, e1^e3, e2^e3"
  // Don't confuse "e1, e2, e3" here with fibers with the same name.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);
  vd_value_type a2 = x0.component(2);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);
  vd_value_type b2 = x1.component(2);

  vd_value_type lcomp = a0*b0 + a1*b1 *a2*b2;

  xresult.put_component(0, lcomp);

  // Postconditions:

  // Exit:

  return;
}

