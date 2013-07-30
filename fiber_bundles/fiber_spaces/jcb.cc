

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class jcb.

#include "jcb.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "jcb_space.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS JCB_LITE
//==============================================================================

//==============================================================================
// JACOBIAN (JCB) FACET OF CLASS JCB_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::jcb_lite::
jcb_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_lite::
jcb_lite(const jcb_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_lite&
fiber_bundle::jcb_lite::
operator=(const jcb_lite& xother)
{
  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::jcb_lite::
~jcb_lite()
{
  // Preconditions:


  // Body:


  // Postconditions:

  // Exit:

}

fiber_bundle::jcb_lite::
jcb_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_lite&
fiber_bundle::jcb_lite::
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

int
fiber_bundle::jcb_lite::
dd() const
{
  // Preconditions:

  // Body:

  int result = 0; // Just to silence compiler.

  // Postconditions:

  ensure(invariant());
  ensure(result == 0);

  // Exit:

  return result;
}

int
fiber_bundle::jcb_lite::
dr() const
{
  // Preconditions:

  // Body:

  int result = 0; // Just to silence compiler.

  // Postconditions:

  ensure(invariant());
  ensure(result == 0);

  // Exit:

  return result;
}


fiber_bundle::jcb_lite::table_dofs_type
fiber_bundle::jcb_lite::
table_dofs() const
{
  // Preconditions:

  // Body:

  int lfactor_ct = factor_ct();
  int ld = d();

  /// @issue: where do these strings get deleted?

  char* lscalar_space_path = new char[1];
  lscalar_space_path[0] = 0;

  int ldd = dd();

  char* ldomain_path = new char[1];
  ldomain_path[0] = 0;

  char* lrange_path = new char[1];
  lrange_path[0] = 0;
  
  int ldr = dr();
  
  table_dofs_type result;

  result.factor_ct = lfactor_ct;
  result.d = ld;
  result.scalar_space_path = lscalar_space_path;
  result.dd = ldd;
  result.domain_path = ldomain_path;
  result.range_path = lrange_path;
  result.dr = ldr;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::jcb_lite::value_type
fiber_bundle::jcb_lite::
component(int xrow, int xcolumn) const
{
  // Preconditions:

  require(xrow >= 0 && xrow < dr());
  require(xcolumn >= 0 && xcolumn < dd());

  // Body:

  value_type result = component(index_for_row_column(xrow, xcolumn));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::jcb_lite::
put_component(int xrow, int xcolumn, value_type xcomp)
{
  // Preconditions:

  require(xrow >= 0 && xrow < dr());
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
fiber_bundle::jcb_lite::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(0 <= xrow && xrow < dr());
  require(0 <= xcolumn && xcolumn < dd());

  // Body:

  // Convert (xrow, xcolumn) into an index into linear component storage.

  int result = xrow*dd() + xcolumn;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);
  ensure(result < dr()*dd());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS JCB_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::jcb_lite::
d() const
{
  // Preconditions:

  // Body:

  int result = dd()*dr();

  // Postconditions:

  ensure(invariant());
  ensure(result==dd()*dr());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS JCB_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::jcb_lite::
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
fiber_bundle::jcb_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("jcb_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::jcb_lite*
fiber_bundle::jcb_lite::
clone() const
{
  jcb_lite* result = 0;

  // Preconditions:

  // Body:

  result = new jcb_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS JCB_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::jcb_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const vd_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::jcb_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(vd_lite::invariant());

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
// CLASS JCB
//==============================================================================


//==============================================================================
// JCB FACET OF CLASS JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::jcb::
jcb()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::jcb::
jcb(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::jcb::
jcb(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::jcb::
jcb(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::jcb::
jcb(abstract_poset_member* xother)
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

fiber_bundle::jcb::
jcb(poset_state_handle* xhost, bool xauto_access)
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

///
fiber_bundle::jcb&
fiber_bundle::jcb::
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
fiber_bundle::jcb&
fiber_bundle::jcb::
operator=(const jcb& xother)
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

fiber_bundle::jcb::
~jcb()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::jcb::volatile_type&
fiber_bundle::jcb::
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
fiber_bundle::jcb::volatile_type*
fiber_bundle::jcb::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::jcb::
dd() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->dd();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::jcb::
dd(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->dd(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb::
domain_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->domain_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb::
domain_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->domain_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::jcb::
dr() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->dr();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::jcb::
dr(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->dr(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb::
range_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->range_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::jcb::
range_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->range_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::jcb::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(0 <= xrow && xrow < dr());
  require(0 <= xcolumn && xcolumn < dd());

  // Body:

  // Convert (xrow, xcolumn) into an index into linear component storage.

  int result = xrow*dd() + xcolumn;

  // Postconditions:

  //ensure(invariant());
  ensure(result >= 0);
  ensure(result < dr()*dd());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::jcb::value_type
fiber_bundle::jcb::
component(int xrow, int xcolumn) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xrow) && (xrow < dr()));
  require((0 <= xcolumn) && (xcolumn < dd()));

  // Body:

  value_type result = component(index_for_row_column(xrow, xcolumn));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::jcb::value_type
fiber_bundle::jcb::
component(int xrow, int xcolumn, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xrow) && (xrow < dr(xauto_access)));
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
fiber_bundle::jcb::
put_component(int xrow, int xcolumn, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xrow) && (xrow < dr()));
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
fiber_bundle::jcb::
put_component(int xrow, int xcolumn, value_type xvalue, bool xauto_access)
{

  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xrow) && (xrow < dr(xauto_access)));
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
// TUPLE FACET OF CLASS JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::jcb::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "jcb_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::jcb::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  // Order has conform to order in dof id space of top.

  string lmember_names;
  lmember_names += "dd INT true";
  lmember_names += " domain_path C_STRING true";
  lmember_names += " range_path C_STRING true";
  lmember_names += " dr INT true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              vd::standard_schema_path(),
                              lmember_names,
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
// ABSTRACT POSET MEMBER FACET OF CLASS JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::jcb::
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
fiber_bundle::jcb::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("jcb");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::jcb::host_type*
fiber_bundle::jcb::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::jcb::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



//==============================================================================
// ANY FACET OF CLASS JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::jcb::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const jcb*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

fiber_bundle::jcb*
fiber_bundle::jcb::
clone() const
{

  // Preconditions:

  jcb* result = 0;

  // Body:

  result = new jcb();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::jcb::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(vd::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance((is_attached() ? (d() == dd() * dr()) : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
ostream&
fiber_bundle::
operator<<(ostream& xos, jcb_lite::table_dofs_type& xt)
{
  xos << " " << xt.factor_ct
      << " " << xt.d
      << " " << xt.dd
      << " " << xt.domain_path
      << " " << xt.dr
      << " " << xt.range_path;

  return xos;
}

//==============================================================================
// JCB FACET:
//==============================================================================

#include "error_message.h"
#include "at1.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"

///
void
fiber_bundle::jcb_algebra::
push(const jcb& xjcb, const at1& xvector, at1& xresult, bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xvector.d(xauto_access) == xjcb.dd(xauto_access));
  require(xresult.d(xauto_access) == xjcb.dr(xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual
  require(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Body:

  // jcb_e13:
  //   xvector == e1
  //   xresult == e3

  // jcb_e23:
  //   xvector == e2
  //   xresult == e3

  // jcb_e33:
  //   xvector == e3
  //   xresult == e3

  const jcb_e13* jcb_e13_xjcb = dynamic_cast<const jcb_e13*>(&xjcb);
  const jcb_e23* jcb_e23_xjcb = dynamic_cast<const jcb_e23*>(&xjcb);
  const jcb_e33* jcb_e33_xjcb = dynamic_cast<const jcb_e33*>(&xjcb);

  const e1* e1_xvector = dynamic_cast<const e1*>(&xvector);
  const e2* e2_xvector = dynamic_cast<const e2*>(&xvector);
  const e3* e3_xvector = dynamic_cast<const e3*>(&xvector);

  e3* e3_xresult = dynamic_cast<e3*>(&xresult);

  if(jcb_e13_xjcb && e1_xvector && e3_xresult)
  {
    push(*jcb_e13_xjcb, *e1_xvector, *e3_xresult, xauto_access);
  }
  else if(jcb_e23_xjcb && e2_xvector && e3_xresult)
  {
    push(*jcb_e23_xjcb, *e2_xvector, *e3_xresult, xauto_access);
  }
  else if(jcb_e33_xjcb && e3_xvector && e3_xresult)
  {
    push(*jcb_e33_xjcb, *e3_xvector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to push(...)");
  } 

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::jcb_algebra::
pull(const jcb& xjcb, const at1& xcovector, at1& xresult, bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.d(xauto_access) == xjcb.dr(xauto_access));
  require(xresult.d(xauto_access) == xjcb.dd(xauto_access));
  require(xcovector.is_covariant(0, xauto_access)); // is_dual
  require(xresult.is_covariant(0, xauto_access));   // is_dual

  // Body:

  // jcb_e13:
  //   xcovector == e3
  //   xresult   == e1

  // jcb_e23:
  //   xcovector == e3
  //   xresult   == e2

  // jcb_e33:
  //   xcovector == e3
  //   xresult   == e3

  const jcb_e13* jcb_e13_xjcb = dynamic_cast<const jcb_e13*>(&xjcb);
  const jcb_e23* jcb_e23_xjcb = dynamic_cast<const jcb_e23*>(&xjcb);
  const jcb_e33* jcb_e33_xjcb = dynamic_cast<const jcb_e33*>(&xjcb);

  const e3* e3_xcovector = dynamic_cast<const e3*>(&xcovector);

  e1* e1_xresult = dynamic_cast<e1*>(&xresult);
  e2* e2_xresult = dynamic_cast<e2*>(&xresult);
  e3* e3_xresult = dynamic_cast<e3*>(&xresult);

  if(jcb_e13_xjcb && e3_xcovector && e1_xresult)
  {
    pull(*jcb_e13_xjcb, *e3_xcovector, *e1_xresult, xauto_access);
  }
  else if(jcb_e23_xjcb && e3_xcovector && e2_xresult)
  {
    pull(*jcb_e23_xjcb, *e3_xcovector, *e2_xresult, xauto_access);
  }
  else if(jcb_e33_xjcb && e3_xcovector && e3_xresult)
  {
    pull(*jcb_e33_xjcb, *e3_xcovector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to pull(...)");
  } 

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));   // is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::jcb_algebra::
push(const jcb_lite& xjcb, const at1_lite& xvector, at1_lite& xresult)
{
  // Preconditions:

  require(xvector.d() == xjcb.dd());
  require(xresult.d() == xjcb.dr());
  require(unexecutable("xvector.is_contravariant())")); // !is_dual
  require(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Body:

  const jcb_e13_lite* jcb_e13_xjcb = dynamic_cast<const jcb_e13_lite*>(&xjcb);
  const jcb_e23_lite* jcb_e23_xjcb = dynamic_cast<const jcb_e23_lite*>(&xjcb);
  const jcb_e33_lite* jcb_e33_xjcb = dynamic_cast<const jcb_e33_lite*>(&xjcb);

  const e1_lite* e1_xvector = dynamic_cast<const e1_lite*>(&xvector);
  const e2_lite* e2_xvector = dynamic_cast<const e2_lite*>(&xvector);
  const e3_lite* e3_xvector = dynamic_cast<const e3_lite*>(&xvector);

  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);

  if(jcb_e13_xjcb && e1_xvector && e3_xresult)
  {
    push(*jcb_e13_xjcb, *e1_xvector, *e3_xresult);
  }
  else if(jcb_e23_xjcb && e2_xvector && e3_xresult)
  {
    push(*jcb_e23_xjcb, *e2_xvector, *e3_xresult);
  }
  else if(jcb_e33_xjcb && e3_xvector && e3_xresult)
  {
    push(*jcb_e33_xjcb, *e3_xvector, *e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to push(...)");
  } 

  // Postconditions:

  //ensure(xresult.is_contravariant(0)); // !is_dual

  // Exit:

  return;
}

///
fiber_bundle::at1_lite*
fiber_bundle::jcb_algebra::
push(const jcb_lite& xjcb, const at1_lite& xvector)
{
  // Preconditions:

  require(precondition_of(push(xjcb, xvector, *result)));

  // Body:

  at1_lite* result = new at1_lite();
  push(xjcb, xvector, *result);

  // Postconditions:

  ensure(postcondition_of(push(xjcb, xvector, *result)));

  // Exit:

  return result;

}

///
void
fiber_bundle::jcb_algebra::
pull(const jcb_lite& xjcb, const at1_lite& xcovector, at1_lite& xresult)
{
  // Preconditions:

  require(xcovector.d() == xjcb.dr());
  require(xresult.d() == xjcb.dd());
  require(unexecutable("xcovector.is_covariant())")); // is_dual
  require(unexecutable("xresult.is_covariant())"));   // is_dual

  // Body:

  const jcb_e13_lite* jcb_e13_xjcb = dynamic_cast<const jcb_e13_lite*>(&xjcb);
  const jcb_e23_lite* jcb_e23_xjcb = dynamic_cast<const jcb_e23_lite*>(&xjcb);
  const jcb_e33_lite* jcb_e33_xjcb = dynamic_cast<const jcb_e33_lite*>(&xjcb);

  const e3_lite* e3_xcovector = dynamic_cast<const e3_lite*>(&xcovector);

  e1_lite* e1_xresult = dynamic_cast<e1_lite*>(&xresult);
  e2_lite* e2_xresult = dynamic_cast<e2_lite*>(&xresult);
  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);

  if(jcb_e13_xjcb && e3_xcovector && e1_xresult)
  {
    pull(*jcb_e13_xjcb, *e3_xcovector, *e1_xresult);
  }
  else if(jcb_e23_xjcb && e3_xcovector && e2_xresult)
  {
    pull(*jcb_e23_xjcb, *e3_xcovector, *e2_xresult);
  }
  else if(jcb_e33_xjcb && e3_xcovector && e3_xresult)
  {
    pull(*jcb_e33_xjcb, *e3_xcovector, *e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to pull(...)");
  } 

  // Postconditions:

  //ensure(xresult.is_covariant(0, xauto_access));   // is_dual

  // Exit:

  return;
}

///
fiber_bundle::at1_lite*
fiber_bundle::jcb_algebra::
pull(const jcb_lite& xjcb, const at1_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(pull(xjcb, xcovector, *result)));

  // Body:

  at1_lite* result = new at1_lite();
  pull(xjcb, xcovector, *result);

  // Postconditions:

  ensure(postcondition_of(pull(xjcb, xcovector, *result)));

  // Exit:

  return result;

}

