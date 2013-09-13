
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
/// Implementation for class at2.

#include "at2.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS AT2_LITE
//==============================================================================


//==============================================================================
// AT2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at2_lite::
at2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_lite::
at2_lite(const at2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_lite&
fiber_bundle::at2_lite::
operator=(const at2_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::at2_lite::
~at2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::at2_lite::
at2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_lite&
fiber_bundle::at2_lite::
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

fiber_bundle::at2_lite::value_type
fiber_bundle::at2_lite::
component(int xrow, int xcolumn) const
{
  // Preconditions:

//   // We only allow values for xrow and xcolumn which are above
//   // (not including) the diagonal.

//   require(0 <= xrow && xrow < dd()-1);
//   require(xrow < xcolumn && xcolumn < dd());

  require(xrow >= 0 && xrow < dd());
  require(xcolumn >= 0 && xcolumn < dd());

  // Body:

  //value_type result = component(index_for_row_column(xrow, xcolumn));

  value_type result = 0;
  if(xrow < xcolumn)
  {
    result = component(index_for_row_column(xrow, xcolumn));
  }
  else if(xrow > xcolumn)
  {
    result = -component(index_for_row_column(xcolumn, xrow));
  }


  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::at2_lite::
put_component(int xrow, int xcolumn, value_type xcomp)
{
  // Preconditions:

  // We only allow values for xrow and xcolumn which are above
  // (not including) the diagonal.

  require(0 <= xrow && xrow < dd()-1);
  require(xrow < xcolumn && xcolumn < dd());

  // Body:

  int lindex = index_for_row_column(xrow, xcolumn);
  put_component(lindex, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(index_for_row_column(xrow, xcolumn)), xcomp));

  // Exit:

  return;
}


int
fiber_bundle::at2_lite::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  // We only allow values for xrow and xcolumn which are above
  // (not including) the diagonal.

  require(0 <= xrow && xrow < dd()-1);
  require(xrow < xcolumn && xcolumn < dd());

  //require(0 <= xrow && xrow < dd());
  //require(0 <= xcolumn && xcolumn < dd());

  // Body:

  // Convert (xrow, xcolumn) into an index into linear component storage
  // (upper triangular stored by rows).

  int i = xrow;
  int j = xcolumn;

  // Swap i and j if i > j.

  if(i > j)
  {
    int isave = i;
    i = j;
    j = isave;
  }

  int result = j + (i*(2*dd()-3-i))/2 - 1;

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at2_lite::
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
// TENSOR ALGEBRA (TP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at2_lite::
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
fiber_bundle::at2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at2_lite*
fiber_bundle::at2_lite::
clone() const
{
  at2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new at2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const at2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::at2_lite::
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
// CLASS AT2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS AT2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::at2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "at2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at2::
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

fiber_bundle::at2::host_type&
fiber_bundle::at2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering at2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xscalar_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xscalar_space_path, xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 2, xscalar_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xscalar_space_path );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving at2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// AT2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at2::
at2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::at2::
at2(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::at2::
at2(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::at2::
at2(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::at2::
at2(abstract_poset_member* xother)
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

fiber_bundle::at2::
at2(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::at2&
fiber_bundle::at2::
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
fiber_bundle::at2&
fiber_bundle::at2::
operator=(const at2& xother)
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

fiber_bundle::at2::
~at2()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::at2::volatile_type&
fiber_bundle::at2::
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
fiber_bundle::at2::volatile_type*
fiber_bundle::at2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2::value_type
fiber_bundle::at2::
component(int xrow, int xcolumn) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xrow >= 0 && xrow < dd());
  require(xcolumn >= 0 && xcolumn < dd());

  // Body:

  value_type result = 0;
  if(xrow < xcolumn)
  {
    result = component(index_for_row_column(xrow, xcolumn));
  }
  else if(xrow > xcolumn)
  {
    result = -component(index_for_row_column(xcolumn, xrow));
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::at2::value_type
fiber_bundle::at2::
component(int xrow, int xcolumn, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(xrow >= 0 && xrow < dd());
  require(xcolumn >= 0 && xcolumn < dd());

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
fiber_bundle::at2::
put_component(int xrow, int xcolumn, value_type xvalue)
{

  // Preconditions:

  require(state_is_read_write_accessible());

  // We only allow values for xrow and xcolumn which are above
  // (not including) the diagonal.

  require((0 <= xrow) && (xrow < dd()-1));
  require((xrow < xcolumn) && (xcolumn < dd()));

  // Body:

  put_component(index_for_row_column(xrow, xcolumn), xvalue);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(xrow, xcolumn), xvalue));

  // Exit:

  return;
}

void
fiber_bundle::at2::
put_component(int xrow, int xcolumn, value_type xvalue, bool xauto_access)
{

  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require((0 <= xrow) && (xrow < dd(xauto_access)-1));
  require((xrow < xcolumn) && (xcolumn < dd(xauto_access)));

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

int
fiber_bundle::at2::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  // We only allow values for xrow and xcolumn which are above
  // (not including) the diagonal.

  require(0 <= xrow && xrow < dd()-1);
  require(xrow < xcolumn && xcolumn < dd());

  // Body:

  // Convert (xrow, xcolumn) into an index into linear component storage.

  int i = xrow;
  int j = xcolumn;

  int result = j + (i*(2*dd()-3-i))/2 - 1;

  // Postconditions:

  //ensure(invariant());
  ensure(result >= 0);
  ensure(result < d());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ATP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at2::
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
fiber_bundle::at2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at2*
fiber_bundle::at2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  at2* result = new at2();

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

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const at2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::at2::
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

    invariance((state_is_read_accessible() ? p() == 2 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



