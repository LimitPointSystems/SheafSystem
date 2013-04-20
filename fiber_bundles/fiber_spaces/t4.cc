

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class t4.

#include "t4.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "tp_space.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS T4_LITE
//==============================================================================

//==============================================================================
// T4 FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t4_lite::
t4_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t4_lite::
t4_lite(const t4_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t4_lite&
fiber_bundle::t4_lite::
operator=(const t4_lite& xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t4_lite::
~t4_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::t4_lite::
t4_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t4_lite&
fiber_bundle::t4_lite::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t4_lite::
p() const
{
  // Preconditions:

  // Body:

  int result = 4;

  // Postconditions:

  ensure(invariant());
  ensure(result == 4);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t4_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = static_cast<int>(dd()*dd()*dd()*dd());

  // Postconditions:

  ensure(invariant());
  ensure(result == static_cast<int>(dd()*dd()*dd()*dd()));

  // Exit:

  return result;
}

fiber_bundle::t4_lite::value_type
fiber_bundle::t4_lite::
component(int xi, int xj, int xk, int xl) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  value_type result = component(index_for_ijkl(xi, xj, xk, xl));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::t4_lite::
put_component(int xi, int xj, int xk, int xl, value_type xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  put_component(index_for_ijkl(xi, xj, xk, xl), xvalue);

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk, xl), xvalue));

  // Exit:

  return;
}


int
fiber_bundle::t4_lite::
index_for_ijkl(int xi, int xj, int xk, int xl) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  int ldd = dd();
  int result = ((xi*ldd + xj)*ldd + xk)*ldd + xl;

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t4_lite::
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
fiber_bundle::t4_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t4_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t4_lite*
fiber_bundle::t4_lite::
clone() const
{
  t4_lite* result = 0;

  // Preconditions:

  // Body:

  result = new t4_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t4_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t4_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::t4_lite::
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
// CLASS T4
//==============================================================================

//==============================================================================
// T4 FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t4::
t4()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::t4::
t4(const t4& xother)
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
fiber_bundle::t4&
fiber_bundle::t4::
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
fiber_bundle::t4&
fiber_bundle::t4::
operator=(const t4& xother)
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

fiber_bundle::t4::
~t4()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

const fiber_bundle::t4::volatile_type&
fiber_bundle::t4::
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
fiber_bundle::t4::volatile_type*
fiber_bundle::t4::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::t4::
t4(poset* xhost, bool xauto_access)
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

fiber_bundle::t4::
t4(const poset* xhost, pod_index_type xhub_id)
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

fiber_bundle::t4::
t4(const poset* xhost, const scoped_index& xid)
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

fiber_bundle::t4::
t4(const poset* xhost, const string& xname)
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


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t4::value_type
fiber_bundle::t4::
component(int xi, int xj, int xk, int xl) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  value_type result = component(index_for_ijkl(xi, xj, xk, xl));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::t4::value_type
fiber_bundle::t4::
component(int xi, int xj, int xk, int xl, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < dd(xauto_access)));
  require((0 <= xj) && (xj < dd(xauto_access)));
  require((0 <= xk) && (xk < dd(xauto_access)));
  require((0 <= xl) && (xl < dd(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  value_type result = component(index_for_ijkl(xi, xj, xk, xl));

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
fiber_bundle::t4::
put_component(int xi, int xj, int xk, int xl, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  put_component(index_for_ijkl(xi, xj, xk, xl), xvalue);

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk, xl), xvalue));

  // Exit:

  return;
}

void
fiber_bundle::t4::
put_component(int xi, int xj, int xk, int xl, value_type xvalue,
              bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  put_component(index_for_ijkl(xi, xj, xk, xl), xvalue);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk, xl, xauto_access), xvalue));

  // Exit:

  return;
}

int
fiber_bundle::t4::
index_for_ijkl(int xi, int xj, int xk, int xl) const
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  int ldd = dd();
  int result = ((xi*ldd + xj)*ldd + xk)*ldd + xl;

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::t4::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "t4_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::t4::
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
// ABSTRACT POSET MEMBER FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t4::
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
fiber_bundle::t4::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t4");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t4*
fiber_bundle::t4::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  t4* result = new t4();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t4::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(tp::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? p() == 4 : true);
    invariance(state_is_read_accessible() ? d() == dd()*dd()*dd()*dd() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

bool
fiber_bundle::t4::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const t4*>(xother) != 0;

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

