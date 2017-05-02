
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

/// @file
/// Implementation for class st3.

#include "SheafSystem/st3.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/wsv_block.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ST3_LITE
//==============================================================================

//==============================================================================
// ST3 FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st3_lite::
st3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_lite::
st3_lite(const st3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_lite&
fiber_bundle::st3_lite::
operator=(const st3_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::st3_lite::
~st3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::st3_lite::
st3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_lite&
fiber_bundle::st3_lite::
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
// STP FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st3_lite::
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
// VD FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st3_lite::value_type
fiber_bundle::st3_lite::
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
fiber_bundle::st3_lite::
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
fiber_bundle::st3_lite::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int ldd = dd();

  // Bubble sort the indices.

  int ltmp;

  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }

  //$$SCRIBBLE: This works for ldd = 3 (only?).

  int result = (xi*ldd + xj)*ldd + xk;
  result -= (xi*(5 + xi) + (xj*(xj+1))/2);

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st3_lite::
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

const std::string&
fiber_bundle::st3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st3_lite*
fiber_bundle::st3_lite::
clone() const
{
  st3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}


bool
fiber_bundle::st3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(stp_lite::invariant());

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
// CLASS ST3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ST2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              stp::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::st3::host_type&
fiber_bundle::st3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xvector_space_path, xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 3, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path );
  ensure(result.p(true) == 3);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving st3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST3 FACET OF CLASS ST3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st3::
st3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st3::
st3(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::st3::
st3(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::st3::
st3(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::st3::
st3(abstract_poset_member* xother)
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

fiber_bundle::st3::
st3(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::st3&
fiber_bundle::st3::
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
fiber_bundle::st3&
fiber_bundle::st3::
operator=(const st3& xother)
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

fiber_bundle::st3::
~st3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}


const fiber_bundle::st3::volatile_type&
fiber_bundle::st3::
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
fiber_bundle::st3::volatile_type*
fiber_bundle::st3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS ST3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st3::value_type
fiber_bundle::st3::
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

fiber_bundle::st3::value_type
fiber_bundle::st3::
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
fiber_bundle::st3::
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
fiber_bundle::st3::
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
fiber_bundle::st3::
index_for_ijk(int xi, int xj, int xk) const
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));

  // Body:

  int ldd = dd();

  // Bubble sort the indices.

  int ltmp;

  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }

  //$$SCRIBBLE: This works for ldd = 3 (only?).

  int result = (xi*ldd + xj)*ldd + xk;
  result -= (xi*(5 + xi) + (xj*(xj+1))/2);

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st3::
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

const std::string&
fiber_bundle::st3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st3*
fiber_bundle::st3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st3* result = new st3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const st3*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());
  //ensure(other->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::st3::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(stp::invariant());

    // Invariances for this class:

    invariance((state_is_read_accessible() ? p() == 3 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



