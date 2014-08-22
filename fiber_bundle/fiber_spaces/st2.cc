
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
/// Implementation for class st2

#include "ComLimitPoint/fiber_bundle/st2.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/stp_space.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "ComLimitPoint/sheaf/wsv_block.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

 
//==============================================================================
// CLASS ST2_LITE
//==============================================================================

//==============================================================================
// ST2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st2_lite::
st2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_lite::
st2_lite(const st2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_lite&
fiber_bundle::st2_lite::
operator=(const st2_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::st2_lite::
~st2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::st2_lite::
st2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_lite&
fiber_bundle::st2_lite::
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

fiber_bundle::st2_lite::value_type
fiber_bundle::st2_lite::
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
fiber_bundle::st2_lite::
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
fiber_bundle::st2_lite::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(0 <= xrow && xrow < dd());
  require(0 <= xcolumn && xcolumn < dd());

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

  int result = j + (i*(2*dd()-1-i))/2;

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
// INTERIOR ALGEBRA (STP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st2_lite::
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

const std::string&
fiber_bundle::st2_lite::
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
fiber_bundle::st2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2_lite*
fiber_bundle::st2_lite::
clone() const
{
  st2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st2_lite();

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
fiber_bundle::st2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::st2_lite::
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
// CLASS ST2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ST2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st2::
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

fiber_bundle::st2::host_type&
fiber_bundle::st2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st2::new_host." << endl;

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
    host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving st2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st2::
st2()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st2::
st2(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::st2::
st2(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::st2::
st2(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::st2::
st2(abstract_poset_member* xother)
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

fiber_bundle::st2::
st2(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::st2&
fiber_bundle::st2::
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
fiber_bundle::st2&
fiber_bundle::st2::
operator=(const st2& xother)
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

fiber_bundle::st2::
~st2()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

const fiber_bundle::st2::volatile_type&
fiber_bundle::st2::
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
fiber_bundle::st2::volatile_type*
fiber_bundle::st2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::st2::value_type
fiber_bundle::st2::
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

fiber_bundle::st2::value_type
fiber_bundle::st2::
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
fiber_bundle::st2::
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
fiber_bundle::st2::
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

int
fiber_bundle::st2::
index_for_row_column(int xrow, int xcolumn) const
{
  // Preconditions:

  require(0 <= xrow && xrow < dd());
  require(0 <= xcolumn && xcolumn < dd());

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

  int result = j + (i*(2*dd()-1-i))/2;

  // Postconditions:

  //  ensure(invariant());
  ensure(result >= 0);
  ensure(result < dd()*dd());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

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

const std::string&
fiber_bundle::st2::
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
fiber_bundle::st2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2*
fiber_bundle::st2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st2 *result = new st2();

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
fiber_bundle::st2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const st2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::st2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(stp::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_attached() ? (p() == 2) : true);

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

//==============================================================================
// ST2 FACET
//==============================================================================

#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/st2_e2.h"
#include "ComLimitPoint/fiber_bundle/st2_e3.h"

///
void
fiber_bundle::st2_algebra::
trace(const st2& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  xresult = 0;

  int ldd = x0.dd();
  for(int i=0; i<ldd; ++i)
  { 
    xresult += x0.component(i, i);
  }

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult == trace(x0)"));

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
trace(const st2& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(trace(x0, result, xauto_access)));

  // Body:

  vd_value_type result;

  trace(x0, result, xauto_access);

  // Postconditions:

  ensure(postcondition_of(trace(x0, result, xauto_access)));

  // Exit:

  return result;
}

///
void
fiber_bundle::st2_algebra::
trace(const st2_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  xresult = 0;

  int ldd = x0.dd();
  for(int i=0; i<ldd; ++i)
  { 
    xresult += x0.component(i, i);
  }

  // Postconditions:

  ensure(unexecutable("xresult == trace(x0)"));

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
trace(const st2_lite& x0)
{
  // Preconditions:

  require(precondition_of(trace(x0, result)));

  // Body:

  vd_value_type result;

  trace(x0, result);

  // Postconditions:

  ensure(postcondition_of(trace(x0, result)));

  // Exit:

  return result;
}

///
void
fiber_bundle::st2_algebra::
determinant(const st2& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  const st2_e2* st2_e2_x0 = dynamic_cast<const st2_e2*>(&x0);
  const st2_e3* st2_e3_x0 = dynamic_cast<const st2_e3*>(&x0);

  if(st2_e2_x0)
  {
    determinant(*st2_e2_x0, xresult, xauto_access);
  }
  else if(st2_e3_x0)
  {
    determinant(*st2_e3_x0, xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to determinant(...)");
  } 

  // Postconditions:

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
determinant(const st2& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(determinant(x0, result, xauto_access)));

  // Body:

  vd_value_type result;

  determinant(x0, result, xauto_access);

  // Postconditions:

  ensure(postcondition_of(determinant(x0, result, xauto_access)));

  // Exit:

  return result;
}

void
fiber_bundle::st2_algebra::
determinant(const st2_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  const st2_e2_lite* st2_e2_x0 = dynamic_cast<const st2_e2_lite*>(&x0);
  const st2_e3_lite* st2_e3_x0 = dynamic_cast<const st2_e3_lite*>(&x0);

  if(st2_e2_x0)
  {
    determinant(*st2_e2_x0, xresult);
  }
  else if(st2_e3_x0)
  {
    determinant(*st2_e3_x0, xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to determinant(...)");
  } 

  // Postconditions:

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
determinant(const st2_lite& x0)
{
  // Preconditions:

  require(precondition_of(determinant(x0, result)));

  // Body:

  vd_value_type result;

  determinant(x0, result);

  // Postconditions:

  ensure(postcondition_of(determinant(x0, result)));

  // Exit:

  return result;
}

