

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class t3.

#include "t3.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at1.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "tp_space.h"
#include "wsv_block.h"

// #include "abstract_poset_member.impl.h"
// #include "assert_contract.h"
// #include "at0.h"
// #include "at0_space.h"
// #include "at1.h"
// #include "at1_space.h"
// #include "tp_space.h"
// #include "fiber_bundles_namespace.impl.h"
// #include "namespace_poset.impl.h"
// #include "poset.h"
// #include "schema_descriptor.h"
// #include "tp_space.h"
// #include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS T3_LITE
//==============================================================================

//==============================================================================
// T3 FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t3_lite::
t3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_lite::
t3_lite(const t3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_lite&
fiber_bundle::t3_lite::
operator=(const t3_lite& xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t3_lite::
~t3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::t3_lite::
t3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_lite&
fiber_bundle::t3_lite::
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
// TENSOR ALGEBRA (TP) FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t3_lite::
p() const
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
// VECTOR ALGEBRA (VD) FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t3_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = static_cast<int>(dd()*dd()*dd());

  // Postconditions:

  ensure(invariant());
  ensure(result == static_cast<int>(dd()*dd()*dd()));

  // Exit:

  return result;
}

fiber_bundle::t3_lite::value_type
fiber_bundle::t3_lite::
component(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  value_type result = component(index_for_ijk(xi, xj, xk));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::t3_lite::
put_component(int xi, int xj, int xk, value_type xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  put_component(index_for_ijk(xi, xj, xk), xvalue);

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk), xvalue));

  // Exit:

  return;
}


int
fiber_bundle::t3_lite::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int ldd = dd();
  int result = (xi*ldd + xj)*ldd + xk;

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t3_lite::
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
fiber_bundle::t3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t3_lite*
fiber_bundle::t3_lite::
clone() const
{
  t3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new t3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::t3_lite::
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
// CLASS T3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS T3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::t3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "t3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::t3::
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

void
fiber_bundle::t3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering t3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, 3, xvector_space_path, xauto_access));   

  // Body:

  host_type::new_table(xns, xhost_path, xschema_path, 3, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.contains_path(xhost_path, xauto_access));
  ensure(xns.member_poset(xhost_path, xauto_access).state_is_not_read_accessible());
  ensure(xns.member_poset(xhost_path, xauto_access).schema(true).path(true) == xschema_path);

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).factor_ct(true) == 
         xns.member_poset<host_type>(xhost_path, xauto_access).d(true));

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).d(true) == 
         schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).scalar_space_path(true) == 
         xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).p(true) == 3);

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).dd(true) == 
         xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d());

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).vector_space_path(true) == 
         xvector_space_path );
  
  // Exit:

  // cout << "Leaving t3::new_host." << endl;
  return;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// T3 FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t3::
t3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::t3::
t3(const t3& xother)
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
fiber_bundle::t3&
fiber_bundle::t3::
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
fiber_bundle::t3&
fiber_bundle::t3::
operator=(const t3& xother)
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

fiber_bundle::t3::
~t3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

const fiber_bundle::t3::volatile_type&
fiber_bundle::t3::
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
fiber_bundle::t3::volatile_type*
fiber_bundle::t3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::t3::
t3(poset* xhost, bool xauto_access)
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

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::t3::
t3(const poset* xhost, pod_index_type xhub_id)
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

fiber_bundle::t3::
t3(const poset* xhost, const scoped_index& xid)
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

fiber_bundle::t3::
t3(const poset* xhost, const string& xname)
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
// TP FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t3::value_type
fiber_bundle::t3::
component(int xi, int xj, int xk) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  value_type result = component(index_for_ijk(xi, xj, xk));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::t3::value_type
fiber_bundle::t3::
component(int xi, int xj, int xk, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < dd(xauto_access)));
  require((0 <= xj) && (xj < dd(xauto_access)));
  require((0 <= xk) && (xk < dd(xauto_access)));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  value_type result = component(index_for_ijk(xi, xj, xk));

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
fiber_bundle::t3::
put_component(int xi, int xj, int xk, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  put_component(index_for_ijk(xi, xj, xk), xvalue);

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk), xvalue));

  // Exit:

  return;
}

void
fiber_bundle::t3::
put_component(int xi, int xj, int xk, value_type xvalue, bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  put_component(index_for_ijk(xi, xj, xk), xvalue);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk), xvalue));

  // Exit:

  return;
}

int
fiber_bundle::t3::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int ldd = dd();
  int result = (xi*ldd + xj)*ldd + xk;

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::t3::
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
fiber_bundle::t3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t3*
fiber_bundle::t3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  t3 *result = new t3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t3::
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

    invariance(state_is_read_accessible() ? p() == 3 : true);
    invariance(state_is_read_accessible() ? d() == dd()*dd()*dd() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

bool
fiber_bundle::t3::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const t3*>(xother) != 0;

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

#include "at1.h"
#include "at2.h"
#include "at3.h"
#include "st2.h"
#include "st3.h"
#include "t2.h"

//==============================================================================
// TP FACET:
//==============================================================================

void
fiber_bundle::tp_algebra::
contract(const t3_lite& x0, int xp, int xq, at1_lite& xresult)
{
  // Preconditions:

  require(xp != xq);
  require(xp >= 0 && xp < x0.p());
  require(xq >= 0 && xq < x0.p());
  require(xresult.p() == x0.p() - 2);

  // Body:

  // For t3 the result of the contracton is an at1.
  // Well not really; but we use at1 in place of t1.

  int ldd = x0.dd();
  
  for(int n=0; n<ldd; ++n)
  {
    vd_value_type lsum = 0;
    for(int i=0; i<ldd; ++i)
    { 
      int lindex;
      if(xp+xq == 1)      // xp==0 and xq==1 or xp==1 and xq==0
      {
        lindex = x0.index_for_ijk(i, i, n);
      }
      else if(xp+xq == 2) // xp==0 and xq==2 or xp==2 and xq==0
      {
        lindex = x0.index_for_ijk(i, n, i);
      }
      else if(xp+xq == 3) // xp==1 and xq==2 or xp==2 and xq==1
      {
        lindex = x0.index_for_ijk(n, i, i);
      }

      lsum += x0.component(lindex);
    }
    xresult.put_component(n, lsum);
  }

  // Postconditions:

  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
contract(const t3& x0, int xp, int xq, at1& xresult, bool xauto_access)
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

  // For t3 the result of the contraction is an at1.

  int ldd = x0.dd();
  int lsum_pq = xp+xq;
  
  for(int n=0; n<ldd; ++n)
  {
    vd_value_type lsum = 0;
    for(int i=0; i<ldd; ++i)
    { 
      int lindex;
      if(lsum_pq == 1)      // xp==0 and xq==1 or xp==1 and xq==0
      {
        lindex = x0.index_for_ijk(i, i, n);
      }
      else if(lsum_pq == 2) // xp==0 and xq==2 or xp==2 and xq==0
      {
        lindex = x0.index_for_ijk(i, n, i);
      }
      else if(lsum_pq == 3) // xp==1 and xq==2 or xp==2 and xq==1
      {
        lindex = x0.index_for_ijk(n, i, i);
      }

      lsum += x0.component(lindex);
    }
    xresult.put_component(n, lsum);
  }

  // Set the variance of the result.

  xresult.put_variance(contract(x0.variance(false), xp, xq), false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult is the contraction of x0 on indices xp and xq"));
  ensure(xresult.variance(xauto_access) == contract(x0.variance(false), xp, xq));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const t3_lite& x0, t3_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             - x0.component(j, i, k)
                             - x0.component(k, j, i)
                             - x0.component(i, k, j);

        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const t3_lite& x0, at3_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             - x0.component(j, i, k)
                             - x0.component(k, j, i)
                             - x0.component(i, k, j);

        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the antisymmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const t3& x0, at3& xresult, bool xauto_access)
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

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             - x0.component(j, i, k)
                             - x0.component(k, j, i)
                             - x0.component(i, k, j);

        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

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

void
fiber_bundle::tp_algebra::
sym(const t3_lite& x0, t3_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             + x0.component(j, i, k)
                             + x0.component(k, j, i)
                             + x0.component(i, k, j);
        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
sym(const t3_lite& x0, st3_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == xresult.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             + x0.component(j, i, k)
                             + x0.component(k, j, i)
                             + x0.component(i, k, j);
        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

  // Postconditions:

  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
sym(const t3& x0, st3& xresult, bool xauto_access)
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

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i, j, k)
                             + x0.component(j, k, i)
                             + x0.component(k, i, j)
                             + x0.component(j, i, k)
                             + x0.component(k, j, i)
                             + x0.component(i, k, j);

        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

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

void
fiber_bundle::tp_algebra::
tensor(const t2_lite& x0, const at1_lite& x1, t3_lite& xresult)
{
  // Preconditions:

  require(x1.dd() == x0.dd());
  require(xresult.dd() == x0.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
    }
  }

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
tensor(const t2& x0, const at1& x1, t3& xresult, bool xauto_access)
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
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
tensor(const at1_lite& x0, const t2_lite& x1, t3_lite& xresult)
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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);
        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
    }
  }

  // Postconditions:

  //ensure();

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
tensor(const at1& x0, const t2& x1, t3& xresult, bool xauto_access)
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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);
        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

//==============================================================================
// atp versions of tensor:
//==============================================================================

///
void
fiber_bundle::tp_algebra::
tensor(const at2_lite& x0, const at1_lite& x1, t3_lite& xresult)
{
  // Preconditions:

  require(x1.dd() == x0.dd());
  require(xresult.dd() == x0.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
tensor(const at2& x0, const at1& x1, t3& xresult, bool xauto_access)
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
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
tensor(const at1_lite& x0, const at2_lite& x1, t3_lite& xresult)
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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);

        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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
tensor(const at1& x0, const at2& x1, t3& xresult, bool xauto_access)
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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);

        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

//==============================================================================
// stp versions of tensor:
//==============================================================================

///
void
fiber_bundle::tp_algebra::
tensor(const st2_lite& x0, const at1_lite& x1, t3_lite& xresult)
{
  // Preconditions:

  require(x1.dd() == x0.dd());
  require(xresult.dd() == x0.dd());

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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
tensor(const st2& x0, const at1& x1, t3& xresult, bool xauto_access)
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
    for(int j=0; j<ldd; ++j)
    {
      vd_value_type lcomp_ij = x0.component(i, j);

      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_k = x1.component(k);
        vd_value_type lcomp_ijk = lcomp_ij * lcomp_k;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

///
void
fiber_bundle::tp_algebra::
tensor(const at1_lite& x0, const st2_lite& x1, t3_lite& xresult)
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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);
        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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
tensor(const at1& x0, const st2& x1, t3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));

  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(xresult.dd(xauto_access) == x0.dd(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) + x1.p(xauto_access));

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
      for(int k=0; k<ldd; ++k)
      {
        vd_value_type lcomp_jk = x1.component(j, k);
        vd_value_type lcomp_ijk = lcomp_i * lcomp_jk;
        xresult.put_component(i, j, k, lcomp_ijk);
      }
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

  ensure(xresult.variance(xauto_access) == \
    tensor_product(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

