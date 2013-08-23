
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
/// Implementation for class at3.

#include "at3.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS AT3_LITE
//==============================================================================

//==============================================================================
// AT3 FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at3_lite::
at3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_lite::
at3_lite(const at3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_lite&
fiber_bundle::at3_lite::
operator=(const at3_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::at3_lite::
~at3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::at3_lite::
at3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at3_lite&
fiber_bundle::at3_lite::
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
// ATP FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at3_lite::
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
// VD FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at3_lite::value_type
fiber_bundle::at3_lite::
component(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  //$$SCRIBBLE: For at3_e3 we know that d=1 meaning we have only
  //            one component. So we use the Levi-Civita (permutation)
  //            symbol for accessing the "components".

  ///@issue This really belongs in at3_e3.  Should we put it there?

  static const int levi_civita[27] =
   {0, 0, 0, 0, 0, 1, 0, -1, 0,
    0, 0, -1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, -1, 0, 0, 0, 0, 0};

  int ldd = dd();
  int lindex = (xi*ldd + xj)*ldd + xk;
  int lindex_value  = levi_civita[lindex];

  value_type result = (lindex_value != 0)
                    ? (lindex_value*component(0)) : 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::at3_lite::
put_component(int xi, int xj, int xk, value_type xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  //@hack  We have only ONE component (for at3_e3).
  //       This function is only here to allow things
  //       to work generically.

  //@issue Decide what we want to do here and fix it.

  static const int levi_civita[27] =
   {0, 0, 0, 0, 0, 1, 0, -1, 0,
    0, 0, -1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, -1, 0, 0, 0, 0, 0};

  int ldd = dd();
  int lindex = (xi*ldd + xj)*ldd + xk;
  int lindex_value = levi_civita[lindex];

  if(lindex_value != 0)
  {
    put_component(0, xvalue);
  }

  cout << "+++++++++++++++++ component(xi, xj, xk) = "\
       << component(xi, xj, xk) << endl;

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk), xvalue*lindex_value));

  // Exit:

  return;
}

int
fiber_bundle::at3_lite::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int result = 0;
  
  // Postconditions:

  ensure(result == 0);

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at3_lite::
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
fiber_bundle::at3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at3_lite*
fiber_bundle::at3_lite::
clone() const
{
  at3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new at3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const at3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::at3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(atp_lite::invariant());

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
// CLASS AT3
//==============================================================================

//==============================================================================
// AT3 FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at3::
at3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::at3::
at3(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::at3::
at3(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::at3::
at3(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::at3::
at3(abstract_poset_member* xother)
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

fiber_bundle::at3::
at3(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::at3&
fiber_bundle::at3::
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
fiber_bundle::at3&
fiber_bundle::at3::
operator=(const at3& xother)
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

fiber_bundle::at3::
~at3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::at3::volatile_type&
fiber_bundle::at3::
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
fiber_bundle::at3::volatile_type*
fiber_bundle::at3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at3::value_type
fiber_bundle::at3::
component(int xi, int xj, int xk) const
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  //$$SCRIBBLE: For at3_e3 we know that d=1 meaning we have only
  //            one component. So we use the Levi-Civita (permutation)
  //            symbol for accessing the "components".

  ///@issue This really belongs in at3_e3.  Should we put it there?

  static const int levi_civita[27] =
   {0, 0, 0, 0, 0, 1, 0, -1, 0,
    0, 0, -1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, -1, 0, 0, 0, 0, 0};

  int ldd = dd();
  int lindex = (xi*ldd + xj)*ldd + xk;
  int lindex_value  = levi_civita[lindex];

  value_type result = (lindex_value != 0)
                    ? (lindex_value*component(0)) : 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::at3::value_type
fiber_bundle::at3::
component(int xi, int xj, int xk, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(precondition_of(component(xi, xj, xk)));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  value_type result = component(xi, xj, xk);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(postcondition_of(component(xi, xj, xk)));

  // Exit:

  return result;
}

void
fiber_bundle::at3::
put_component(int xi, int xj, int xk, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  //@hack  We have only ONE component (for at3_e3).
  //       This function is only here to allow things
  //       to work generically.

  //@issue Decide what we want to do here and fix it.

  static const int levi_civita[27] =
   {0, 0, 0, 0, 0, 1, 0, -1, 0,
    0, 0, -1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, -1, 0, 0, 0, 0, 0};

  int ldd = dd();
  int lindex = (xi*ldd + xj)*ldd + xk;
  int lindex_value = levi_civita[lindex];

  if(lindex_value != 0)
  {
    value_type lvalue = xvalue*lindex_value;
    put_component(0, lvalue);
  }

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk), xvalue));

  // Exit:

  return;
}

void
fiber_bundle::at3::
put_component(int xi, int xj, int xk, value_type xvalue,
               bool xauto_access)
{

  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(precondition_of(put_component(xi, xj, xk, xvalue)));

  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  put_component(xi, xj, xk, xvalue);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(postcondition_of(put_component(xi, xj, xk, xvalue)));

  // Exit:

  return;
}

int
fiber_bundle::at3::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int result = 0;
  
  // Postconditions:

  ensure(result == 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ATP FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::at3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "at3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              atp::standard_schema_path(),
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
// ABSTRACT POSET MEMBER FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at3::
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
fiber_bundle::at3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at3*
fiber_bundle::at3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  at3* result = new at3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const at3*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::at3::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(atp::invariant());

    // Invariances for this class:

    invariance((state_is_read_accessible() ? p() == 3 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}


