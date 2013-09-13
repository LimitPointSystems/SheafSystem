
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
/// Implementation for class st4.

#include "st4.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "stp_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ST4_LITE
//==============================================================================

//==============================================================================
// ST4 FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st4_lite::
st4_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st4_lite::
st4_lite(const st4_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st4_lite&
fiber_bundle::st4_lite::
operator=(const st4_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::st4_lite::
~st4_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::st4_lite::
st4_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st4_lite&
fiber_bundle::st4_lite::
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
// STP FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st4_lite::
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
// VD FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st4_lite::value_type
fiber_bundle::st4_lite::
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
fiber_bundle::st4_lite::
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
fiber_bundle::st4_lite::
index_for_ijkl(int xi, int xj, int xk, int xl) const
{
  // Preconditions:

  require((0 <= xi) && (xi < dd()));
  require((0 <= xj) && (xj < dd()));
  require((0 <= xk) && (xk < dd()));
  require((0 <= xl) && (xl < dd()));

  // Body:

  int ldd = dd();

  // Bubble sort the indices into ascending order (brute force).

  int ltmp;

  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xk > xl) { ltmp = xk; xk = xl; xl = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xk > xl) { ltmp = xk; xk = xl; xl = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }

  //@todo Implement in st4_e2 and st4_e3.

  //int result = (xi*ldd + xj)*ldd + xk;
  int result = ((xi*ldd + xj)*ldd + xk)*ldd + xl;

  static const int iskip2[2] = {0, 7};
  static const int jskip2[2] = {0, 3};
  static const int kskip2[2] = {0, 1};

  static const int iskip3[3] = {0, 23, 49};
  static const int jskip3[3] = {0, 6, 14};
  static const int kskip3[3] = {0, 1, 3};

  if(ldd == 2)
  {
    result -= (iskip2[xi] + jskip2[xj] + kskip2[xk]);
  }
  else if(ldd == 3)
  {
    result -= (iskip3[xi] + jskip3[xj] + kskip3[xk]);
  }
  else
  {
    // error.
  }

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::st4_lite::
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
fiber_bundle::st4_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st4_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st4_lite*
fiber_bundle::st4_lite::
clone() const
{
  st4_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st4_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st4_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st4_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}


bool
fiber_bundle::st4_lite::
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
// CLASS ST4
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ST2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st4::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st4_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st4::
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

fiber_bundle::st4::host_type&
fiber_bundle::st4::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st4::new_host." << endl;

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
    host_type::new_table(xns, xhost_path, xschema_path, 4, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path );
  ensure(result.p(true) == 4);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving st4::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST4 FACET OF CLASS ST4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st4::
st4()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st4::
st4(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::st4::
st4(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::st4::
st4(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::st4::
st4(abstract_poset_member* xother)
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

fiber_bundle::st4::
st4(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::st4&
fiber_bundle::st4::
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
fiber_bundle::st4&
fiber_bundle::st4::
operator=(const st4& xother)
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

fiber_bundle::st4::
~st4()
{

  // Preconditions:

  // Body:

  // Postconditions:

}


const fiber_bundle::st4::volatile_type&
fiber_bundle::st4::
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
fiber_bundle::st4::volatile_type*
fiber_bundle::st4::
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
// VD FACET OF CLASS ST4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st4::value_type
fiber_bundle::st4::
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

fiber_bundle::st4::value_type
fiber_bundle::st4::
component(int xi, int xj, int xk, int xl, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require((0 <= xi) && (xi < dd(xauto_access)));
  require((0 <= xj) && (xj < dd(xauto_access)));
  require((0 <= xk) && (xk < dd(xauto_access)));
  require((0 <= xl) && (xl < dd()));

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
fiber_bundle::st4::
put_component(int xi, int xj, int xk, int xl, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());
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

void
fiber_bundle::st4::
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

  put_component(index_for_ijkl(xi, xj, xk, xk), xvalue);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(isunordered_or_equals(component(xi, xj, xk, xl), xvalue));

  // Exit:

  return;
}


int
fiber_bundle::st4::
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

  // Bubble sort the indices into ascending order (brute force).

  int ltmp;

  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xk > xl) { ltmp = xk; xk = xl; xl = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }
  if(xj > xk) { ltmp = xj; xj = xk; xk = ltmp; }
  if(xk > xl) { ltmp = xk; xk = xl; xl = ltmp; }
  if(xi > xj) { ltmp = xi; xi = xj; xj = ltmp; }

  //int result = (xi*ldd + xj)*ldd + xk;
  int result = ((xi*ldd + xj)*ldd + xk)*ldd + xl;

  //@todo Implement in st4_e2 and st4_e3.

  static const int iskip2[2] = {0, 7};
  static const int jskip2[2] = {0, 3};
  static const int kskip2[2] = {0, 1};

  static const int iskip3[3] = {0, 23, 49};
  static const int jskip3[3] = {0, 6, 14};
  static const int kskip3[3] = {0, 1, 3};

  if(ldd == 2)
  {
    result -= (iskip2[xi] + jskip2[xj] + kskip2[xk]);
  }
  else if(ldd == 3)
  {
    result -= (iskip3[xi] + jskip3[xj] + kskip3[xk]);
  }
  else
  {
    // error.
  }

  // Postconditions:

  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::st4::
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
fiber_bundle::st4::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st4");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st4*
fiber_bundle::st4::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st4* result = new st4();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st4::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const st4*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());
  //ensure(other->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::st4::
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

    invariance((state_is_read_accessible() ? p() == 4 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

