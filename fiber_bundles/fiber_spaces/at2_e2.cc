
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
/// Implementation for class at2_e2

#include "SheafSystem/at2_e2.impl.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS AT2_E2_LITE
//==============================================================================


//==============================================================================
// AT2_E2 FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at2_e2_lite::
at2_e2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_e2_lite::
at2_e2_lite(const at2_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_e2_lite&
fiber_bundle::at2_e2_lite::
operator=(const at2_e2_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xother[0]));

  // Exit:

  return *this;
}

fiber_bundle::at2_e2_lite::
~at2_e2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::at2_e2_lite::
at2_e2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_e2_lite&
fiber_bundle::at2_e2_lite::
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

fiber_bundle::at2_e2_lite::
at2_e2_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at2_e2_lite& 
fiber_bundle::at2_e2_lite::
operator=(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  _row_dofs = reinterpret_cast<const row_dofs_type&>(xmatrix);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::at2_e2_lite::
operator at2_e2_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2_e2_lite::
operator const at2_e2_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2_e2_lite::
operator at2_e2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2_e2_lite::
operator const at2_e2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2_e2_lite::
at2_e2_lite(const value_type& xy)
{
  // Preconditions:

  // Body:

  put_component(xy);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xy));

  // Exit:
}

void
fiber_bundle::at2_e2_lite::
put_component(value_type xy)
{
  // Preconditions:

  // Body:

  put_component(0, xy);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xy));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at2_e2_lite::
dd() const
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
// VECTOR ALGEBRA (VD) FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::at2_e2_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e2_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::at2_e2_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e2_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::at2_e2_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e2_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e2_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e2_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::at2_e2_lite::
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
fiber_bundle::at2_e2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at2_e2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at2_e2_lite*
fiber_bundle::at2_e2_lite::
clone() const
{
  at2_e2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new at2_e2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at2_e2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const at2_e2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::at2_e2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(at2_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::at2_e2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::at2_e2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS AT2_E2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS AT2_E2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::at2_e2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "at2_e2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at2_e2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  string lmember_names = "xy DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              at2::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::at2_e2::host_type&
fiber_bundle::at2_e2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering at2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 1);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 2);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 1);
  ensure(result.d(true) == 1);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving at2_e2::new_host." << endl;
  return result;
}

fiber_bundle::at2_e2::host_type&
fiber_bundle::at2_e2::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering at2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<at2_e2>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<at2_e2>(xsuffix));

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, lpath, standard_schema_path(), lvector_space_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<at2_e2>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 1);
  ensure(result.d(true) == 1);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving at2_e2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// AT2_E2 FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at2_e2::
at2_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::at2_e2::
at2_e2(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::at2_e2::
at2_e2(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::at2_e2::
at2_e2(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::at2_e2::
at2_e2(abstract_poset_member* xother)
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

fiber_bundle::at2_e2::
at2_e2(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::at2_e2::
at2_e2(poset_state_handle& xhost,
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

fiber_bundle::at2_e2&
fiber_bundle::at2_e2::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  sheaf::row_dofs(*this) = xrdt;
  
  // Postconditions:

  ensure(isunordered_or_equals(component(0), xrdt.components[0]));

  // Exit:

  return *this;
}

///
fiber_bundle::at2_e2&
fiber_bundle::at2_e2::
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
fiber_bundle::at2_e2&
fiber_bundle::at2_e2::
operator=(const at2_e2& xother)
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

fiber_bundle::at2_e2::
~at2_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

const fiber_bundle::at2_e2::volatile_type&
fiber_bundle::at2_e2::
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
fiber_bundle::at2_e2::volatile_type*
fiber_bundle::at2_e2::
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
fiber_bundle::at2_e2::
put_components(dof_type xy_comp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xy_comp);


  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xy_comp));

  // Exit:

  return;
}

fiber_bundle::at2_e2::
operator at2_e2::row_dofs_type& ()
//operator row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at2_e2::
operator const at2_e2::row_dofs_type& () const
//operator const row_dofs_type& () const
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
// AT2 FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ATP FACET OF CLASS AT2_E2
//==============================================================================
  
// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS AT2_E2
//==============================================================================
  
// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::at2_e2::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e2::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::at2_e2::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e2::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::at2_e2::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e2::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e2::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e2::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::at2_e2::
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
fiber_bundle::at2_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at2_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at2_e2*
fiber_bundle::at2_e2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  at2_e2* result = new at2_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at2_e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const at2_e2*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;

}

bool
fiber_bundle::at2_e2::
invariant() const
{
  bool result = true;

  // Body:

  // Must satisfy base class invariant.

  invariance(at2::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(at2::invariant());

    // Invariances for this class:

    invariance((state_is_read_accessible() ? dd() == 2 : true));

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

#include "SheafSystem/at0.h"

void
fiber_bundle::atp_algebra::
hook(const e2& x0, const e2& x1, at0& xresult,  bool xauto_access)
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

  // The hook operation is essentially a contract, so here we
  // could call the vd facet contract function here, but we'll
  // reimplement it for efficiency.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  vd_value_type lcomp = a0*b0 + a1*b1;

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
hook(const e2_lite& x0, const e2_lite& x1, at0_lite& xresult)
{

  // Preconditions:

  // Body:

  // The hook operation is essentially a contract, so we
  // could call the vd facet contract function here, but we'll
  // reimplement it for efficiency.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  vd_value_type lcomp = a0*b0 + a1*b1;

  xresult.put_component(0, lcomp);

  // Postconditions:



  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
hook(const at2_e2& x0, const e2& x1, e2& xresult, bool xauto_access)
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
  // on the first index.  In 2d this is pretty simple,
  // so we implement it explicitly for efficiency.
  
  // at2_e2 has just 1 component.

  vd_value_type a = x0.component(0);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  int lrank = 2;

  vd_value_type lcomp0 = lrank*(-a*b1);
  vd_value_type lcomp1 = lrank*( a*b0);

  xresult.put_component(0, lcomp0);
  xresult.put_component(1, lcomp1);

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
hook(const at2_e2_lite& x0, const e2_lite& x1, e2_lite& xresult)
{

  // Preconditions:

  // Body:

  // The hook operation is essentially a contract operation
  // on the first index.  In 2d this is pretty simple,
  // so we implement it explicitly for efficiency.
  
  // at2_e2 has just 1 component.

  vd_value_type a = x0.component(0);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  int lrank = 2;

  vd_value_type lcomp0 = lrank*(-a*b1);
  vd_value_type lcomp1 = lrank*( a*b0);

  xresult.put_component(0, lcomp0);
  xresult.put_component(1, lcomp1);

  // Postconditions:


  // Exit:

  return;

}

void
fiber_bundle::atp_algebra::
star(const at2_e2& x0, at0& xresult, bool xauto_access)
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
star(const at2_e2_lite& x0, at0_lite& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type a123 = x0.component(0);

  xresult.put_component(0, a123);
 
  // Postconditions:

  ensure(xresult.component(0) == x0.component(0));

  // Exit:

  return;
}

fiber_bundle::at0_lite*
fiber_bundle::atp_algebra::
star(const at2_e2_lite& x0)
{
  // Preconditions:

  require(precondition_of(star(x0, *result)));

  // Body:

  at0_lite* result = new at0_lite();

  star(x0, *result);
 
  // Postconditions:

  ///@todo Postconditions.

  ensure(result != 0);
  ensure(postcondition_of(star(x0, *result)));

  // Exit:

  return result;
}


void
fiber_bundle::atp_algebra::
star(const at0& x0, at2_e2& xresult, bool xauto_access)
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
star(const at0_lite& x0, at2_e2_lite& xresult)
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

fiber_bundle::at2_e2_lite*
fiber_bundle::atp_algebra::
star(const at0_lite& x0)
{
  // Preconditions:

  require(precondition_of(star(x0, *result)));

  // Body:

  at2_e2_lite* result = new at2_e2_lite();

  star(x0, *result);
 
  // Postconditions:

  ///@todo Postconditions.

  ensure(result != 0);
  ensure(postcondition_of(star(x0, *result)));

  // Exit:

  return result;
}


void
fiber_bundle::atp_algebra::
star(const e2& x0, e2& xresult, bool xauto_access)
{
  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  // In 2d the Hodge star operator maps a one-form to a new one-form represented
  // by orthogonal lines.  So here we need to exchange the components and and
  // change the sign of one of them.  We arbitrarily (?) change the sign on
  // the second component.

  vd_value_type lcomp0 =  x0.component(1);
  vd_value_type lcomp1 = -x0.component(0);

  xresult.put_component(0, lcomp0);
  xresult.put_component(1, lcomp1);

  // Set the variance of the result.

  x0.is_p_form(false) ? xresult.put_is_p_form(false)
                      : xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    x0.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));

  // Exit:

  return;
}

void
fiber_bundle::atp_algebra::
star(const e2_lite& x0, e2_lite& xresult)
{
  // Preconditions:

  // Body:

  // In 2d the Hodge star operator maps a one-form to a new one-form represented by
  // orthogonal lines.  So here we need to exchange the components and and change
  // the sign of one of them.  We arbitrarily (?) change the sign on the second
  // component.

  vd_value_type lcomp0 =  x0.component(1);
  vd_value_type lcomp1 = -x0.component(0);

  xresult.put_component(0, lcomp0);
  xresult.put_component(1, lcomp1);

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;
}

fiber_bundle::e2_lite*
fiber_bundle::atp_algebra::
star(const e2_lite& x0)
{
  // Preconditions:

  // Body:

  e2_lite* result = new e2_lite();

  star(x0, *result);
 
  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

void
fiber_bundle::atp_algebra::
wedge(const e2& x0, const e2& x1, at2_e2& xresult, bool xauto_access)
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

  // Access via virtual component required since 
  // some descendants may not store components.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  vd_value_type lcomp = a0*b1 - a1*b0;

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
wedge(const e2_lite& x0, const e2_lite& x1, at2_e2_lite& xresult)
{
  // Preconditions:

  require(x0.is_same_type(x1));
  require(x0.dd() == xresult.dd());

  // Body:

  // Access via virtual component required since 
  // some descendants may not store components.

  vd_value_type a0 = x0.component(0);
  vd_value_type a1 = x0.component(1);

  vd_value_type b0 = x1.component(0);
  vd_value_type b1 = x1.component(1);

  vd_value_type lcomp = a0*b1 - a1*b0;

  xresult.put_component(0, lcomp);

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;
}

