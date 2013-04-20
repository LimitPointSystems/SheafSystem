

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class t2.

#include "t2.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "tp_space.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS T2_LITE
//==============================================================================

//==============================================================================
// T2 FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t2_lite::
t2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_lite::
t2_lite(const t2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_lite&
fiber_bundle::t2_lite::
operator=(const t2_lite& xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t2_lite::
~t2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::t2_lite::
t2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_lite&
fiber_bundle::t2_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  vd_lite::operator=(xrow_dofs);
  
  // Postconditions:

  postcondition_of(vd_lite::operator=(xrow_dofs));

  // Exit:

  return *this;

}

fiber_bundle::t2_lite::value_type
fiber_bundle::t2_lite::
component(int xrow, int xcolumn) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < dd());
  require(xcolumn >= 0 && xcolumn < dd());

  // Body:

  value_type result = component(index_for_row_column(xrow, xcolumn));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::t2_lite::
put_component(int xrow, int xcolumn, value_type xcomp)
{
  // Preconditions:

  require(xrow >= 0 && xrow < dd());
  require(xcolumn >= 0 && xcolumn < dd());

  // Body:

  put_component(index_for_row_column(xrow, xcolumn), xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(index_for_row_column(xrow, xcolumn)), xcomp));

  // Exit:

  return;
}

int
fiber_bundle::t2_lite::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(0 <= xrow && xrow < dd());
  require(0 <= xcolumn && xcolumn < dd());

  // Body:

  int result = xrow*dd() + xcolumn;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);
  ensure(result < dd()*dd());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t2_lite::
p() const
{
  // Preconditions:

  // Body:

  int result = 2;

  // Postconditions:

  ensure(invariant());
  ensure(result == 2);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t2_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = static_cast<int>(dd()*dd());

  // Postconditions:

  ensure(invariant());
  ensure(result == static_cast<int>(dd()*dd()));

  // Exit:

  return result;
}

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t2_lite::
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
fiber_bundle::t2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t2_lite*
fiber_bundle::t2_lite::
clone() const
{
  t2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new t2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::t2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(tp_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS T2
//==============================================================================

//==============================================================================
// TO2 FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t2::
t2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::t2::
t2(const t2& xother)
{

  // Preconditions:


  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::t2&
fiber_bundle::t2::
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
fiber_bundle::t2&
fiber_bundle::t2::
operator=(const t2& xother)
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

fiber_bundle::t2::
~t2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

const fiber_bundle::t2::volatile_type&
fiber_bundle::t2::
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
fiber_bundle::t2::volatile_type*
fiber_bundle::t2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::t2::
t2(poset* xhost, bool xauto_access)
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

fiber_bundle::t2::
t2(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
}

fiber_bundle::t2::
t2(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
}

fiber_bundle::t2::
t2(const poset* xhost, const string& xname)
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
  ensure(is_attached());
  // ensure(host() == xhost);
  ensure(name() == xname);

}

int
fiber_bundle::t2::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(0 <= xrow && xrow < dd());
  require(0 <= xcolumn && xcolumn < dd());

  // Body:

  // Convert (xrow, xcolumn) into an index into linear component storage.

  int result = xrow*dd() + xcolumn;

  // Postconditions:

  //ensure(invariant());
  ensure(result >= 0);
  ensure(result < dd()*dd());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t2::value_type
fiber_bundle::t2::
component(int xrow, int xcolumn) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xrow) && (xrow < dd()));
  require((0 <= xcolumn) && (xcolumn < dd()));

  // Body:

  value_type result = component(index_for_row_column(xrow, xcolumn));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::t2::value_type
fiber_bundle::t2::
component(int xrow, int xcolumn, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xrow) && (xrow < dd(xauto_access)));
  require((0 <= xcolumn) && (xcolumn < dd(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  value_type result = component(xrow, xcolumn);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::t2::
put_component(int xrow, int xcolumn, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xrow) && (xrow < dd()));
  require((0 <= xcolumn) && (xcolumn < dd()));

  // Body:

  put_component(index_for_row_column(xrow, xcolumn), xvalue);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xrow, xcolumn), xvalue));

  // Exit:

  return;
}

void
fiber_bundle::t2::
put_component(int xrow, int xcolumn, value_type xvalue, bool xauto_access)
{

  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xrow) && (xrow < dd(xauto_access)));
  require((0 <= xcolumn) && (xcolumn < dd(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  put_component(index_for_row_column(xrow, xcolumn), xvalue);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xrow, xcolumn), xvalue));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::t2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "t2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::t2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              tp::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t2::
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
fiber_bundle::t2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t2*
fiber_bundle::t2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  t2* result = new t2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t2::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(tp::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? p() == 2 : true);
    invariance(state_is_read_accessible() ? d() == dd()*dd() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

bool
fiber_bundle::t2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this.

  bool result = dynamic_cast<const t2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#include "at0.h"
#include "at1.h"
#include "at2.h"
#include "st2.h"
#include "t2.h"

void
fiber_bundle::tp_algebra::
contract(const t2_lite& x0, int xp, int xq, at0_lite& xresult)
{
  // Preconditions:

  require(xp != xq);
  require(xp >= 0 && xp < x0.p());
  require(xq >= 0 && xq < x0.p());
  require(xresult.p() == x0.p() - 2);

  // Body:

  // For t2 the result of the contraction is a scalar (the trace).

  vd_value_type lscalar = 0;

  int ldd = x0.dd();
  for(int i=0; i<ldd; ++i)
  { 
    lscalar += x0.component(i, i);
  }

  xresult.put_component(0, lscalar);

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
contract(const t2& x0, int xp, int xq, at0& xresult, bool xauto_access)
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

  // For t2 the result of the contraction is a scalar (the trace).

  vd_value_type lscalar = 0;

  int ldd = x0.dd();
  for(int i=0; i<ldd; ++i)
  { 
    lscalar += x0.component(i, i);
  }

  xresult.put_component(0, lscalar);


  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  //ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
alt(const t2_lite& x0, at2_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  // Postconditions:

  int ldd = x0.dd();

  for(int i=0; i<ldd-1; ++i)
  {
    for(int j=i+1; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) - x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const t2& x0, at2& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // $$SCRIBBLE: error
  // the variance of the output is the same as the variance of the input.
  // Since the output variance can't be mixed, neither can the input.
  // require(!x0.variance(xauto_access).is_mixed());
  // $$SCRIBBLE END

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  int ldd = x0.dd();

  for(int i=0; i<ldd-1; ++i)
  {
    for(int j=i+1; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) - x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Set the variance of the result.

  //
  // Variance of result is same as variance of x0.
  //

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
void
fiber_bundle::tp_algebra::
alt(const t2_lite& x0, t2_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  // Postconditions:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) - x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
sym(const t2_lite& x0, st2_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  // Postconditions:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=i; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) + x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
sym(const t2& x0, st2& xresult, bool xauto_access)
{ 
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // $$SCRIBBLE: error
  // the variance of the output is the same as the variance of the input.
  // Since the output variance can't be mixed, neither can the input.
  // require(!x0.variance(xauto_access).is_mixed());
  // $$SCRIBBLE END

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=i; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) + x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Set the variance of the result.

  //
  // Variance of result is same as variance of x0.
  //

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
void
fiber_bundle::tp_algebra::
sym(const t2_lite& x0, t2_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  // Postconditions:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) + x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
sym(const t2& x0, t2& xresult, bool xauto_access)
{ 
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(x0.dd() == xresult.dd());
  require(!x0.variance(xauto_access).is_mixed());

  // $$SCRIBBLE
  // sym part is multiple of identity if variance is mixed; should we allow mixed variance input?
  // require(!x0.variance(xauto_access).is_mixed());
  //
  // $$SCRIBBLE END

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lvalue = 0.5*(x0.component(i, j) + x0.component(j, i));
      xresult.put_component(i, j, lvalue);
    }
  }

  // Set the variance of the result.

  //
  // Variance of result is same as variance of x0.
  //
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
void
fiber_bundle::tp_algebra::
tensor(const at1_lite& x0, const at1_lite& x1, t2_lite& xresult)
{
  // Preconditions:

  require(x1.dd() == x0.dd());
  require(xresult.dd() == x0.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    vd_value_type lcomp_i = x0.component(i);

    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_j = x1.component(j);
      vd_value_type lcomp_ij = lcomp_i * lcomp_j;
      xresult.put_component(i, j, lcomp_ij);
    }
  }

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
tensor(const at1& x0, const at1& x1, t2& xresult, bool xauto_access)
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

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    vd_value_type lcomp_i = x0.component(i);

    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_j = x1.component(j);
      vd_value_type lcomp_ij = lcomp_i * lcomp_j;
      xresult.put_component(i, j, lcomp_ij);
    }
  }

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

  ensure(xresult.variance(xauto_access) ==
	 tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

