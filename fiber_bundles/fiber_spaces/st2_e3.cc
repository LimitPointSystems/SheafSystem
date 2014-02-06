
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
/// Implementation for class st2_e3.

#include "st2_e3.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "stp_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "stp_space.h"
#include "wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ST2_E3_LITE
//==============================================================================

//==============================================================================
// ST2_E3 FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st2_e3_lite::
st2_e3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_e3_lite::
st2_e3_lite(const st2_e3_lite& xother)
{
  // Preconditions:

  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_e3_lite&
fiber_bundle::st2_e3_lite::
operator=(const st2_e3_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::st2_e3_lite::
~st2_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e3_lite::
st2_e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  (*this) = xrow_dofs;
  
  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e3_lite&
fiber_bundle::st2_e3_lite::
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

fiber_bundle::st2_e3_lite::
st2_e3_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  (*this) = xmatrix;

  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e3_lite& 
fiber_bundle::st2_e3_lite::
operator=(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  //_row_dofs = xmatrix;
  _row_dofs = reinterpret_cast<const row_dofs_type&>(xmatrix);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::st2_e3_lite::
operator st2_e3_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e3_lite::
operator const st2_e3_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e3_lite::
operator st2_e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e3_lite::
operator const st2_e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e3_lite::
st2_e3_lite(const value_type& xx, const value_type& xy, const value_type& xz,
            const value_type& yy, const value_type& yz, const value_type& zz)
{
  // Preconditions:

  // Body:

  put_components(xx, xy, xz, yy, yz, zz);

  // Postconditions:

  // Exit:
}

void
fiber_bundle::st2_e3_lite::
put_components(const value_type& xx_comp,
               const value_type& xy_comp,
               const value_type& xz_comp,
               const value_type& yy_comp,
               const value_type& yz_comp,
               const value_type& zz_comp)

{
  // Preconditions:

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, xz_comp);
  put_component(3, yy_comp);
  put_component(4, yz_comp);
  put_component(5, zz_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), xz_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));
  ensure(isunordered_or_equals(component(4), yz_comp));
  ensure(isunordered_or_equals(component(5), zz_comp));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (ST2) FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st2_e3_lite::
dd() const
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
// VECTOR ALGEBRA (VD) FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::st2_e3_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e3_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::st2_e3_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e3_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::st2_e3_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e3_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e3_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st2_e3_lite::
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
fiber_bundle::st2_e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2_e3_lite*
fiber_bundle::st2_e3_lite::
clone() const
{
  st2_e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st2_e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST2_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st2_e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st2_e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::st2_e3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st2_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::st2_e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::st2_e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS ST2_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ST2_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st2_e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st2_e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st2_e3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "xx DOUBLE false ";
  lmember_names       += "xy DOUBLE false ";
  lmember_names       += "xz DOUBLE false ";
  lmember_names       += "yy DOUBLE false ";
  lmember_names       += "yz DOUBLE false ";
  lmember_names       += "zz DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              st2::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::st2_e3::host_type&
fiber_bundle::st2_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st2_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 6);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 3);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving st2_e3::new_host." << endl;
  return result;
}

fiber_bundle::st2_e3::host_type&
fiber_bundle::st2_e3::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering st2_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<st2_e3>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<st2_e3>(xsuffix));

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
  ensure(result.path(true) == standard_host_path<st2_e3>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving st2_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// ST2_E3 FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st2_e3::
st2_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st2_e3::
st2_e3(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::st2_e3::
st2_e3(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::st2_e3::
st2_e3(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::st2_e3::
st2_e3(abstract_poset_member* xother)
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

fiber_bundle::st2_e3::
st2_e3(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::st2_e3::
st2_e3(poset_state_handle& xhost,
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

fiber_bundle::st2_e3&
fiber_bundle::st2_e3::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  sheaf::row_dofs(*this) = xrdt;

  // Postconditions:

  ensure_for_all(i, 0, d(), component(i) == xrdt.components[i]);

  // Exit:

  return *this;

}

///
fiber_bundle::st2_e3&
fiber_bundle::st2_e3::
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
fiber_bundle::st2_e3&
fiber_bundle::st2_e3::
operator=(const st2_e3& xother)
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

fiber_bundle::st2_e3::
~st2_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}


const fiber_bundle::st2_e3::volatile_type&
fiber_bundle::st2_e3::
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
fiber_bundle::st2_e3::volatile_type*
fiber_bundle::st2_e3::
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
fiber_bundle::st2_e3::
put_components(dof_type xx_comp, dof_type xy_comp, dof_type xz_comp,
               dof_type yy_comp, dof_type yz_comp, dof_type zz_comp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, xz_comp);
  put_component(3, yy_comp);
  put_component(4, yz_comp);
  put_component(5, zz_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), xz_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));
  ensure(isunordered_or_equals(component(4), yz_comp));
  ensure(isunordered_or_equals(component(5), zz_comp));

  // Exit:

  return;
}

fiber_bundle::st2_e3::
operator st2_e3::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e3::
operator const st2_e3::row_dofs_type& () const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::st2_e3::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e3::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::st2_e3::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e3::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::st2_e3::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e3::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e3::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//=============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST2_E3
//=============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st2_e3::
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
fiber_bundle::st2_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2_e3*
fiber_bundle::st2_e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st2_e3* result = new st2_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//=============================================================================
// ANY FACET OF CLASS ST2_E3
//=============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st2_e3::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const st2_e3*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::st2_e3::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st2::invariant());

    // Invariants for this class:

    invariance(state_is_read_accessible() ? (dd() == 3) : true);
    invariance(state_is_read_accessible() ? (d()  == 6) : true);

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

void
fiber_bundle::vd_algebra::
transform_basis_by(st2_e3_lite& xv, const gl3_lite& xtransform, bool is_contravariant)
{
  // Preconditions:

  // Body:

  // Notation:
  //
  // Let the current basis be f-hat, considered as a row of vectors
  // with f-hat[i] the i-th basis vector. Similary, let e-hat be the
  // new basis. Let B be the matrix of the transform xtransform,
  // defined such that the i-th column, B[*][i] contains
  // the components of e-hat[i] with respect to f-hat.
  //
  // Given a twice covariant tensor T, let the components w.r.t.
  // f-hat be denoted Tf[k][l], where k is a row index and l is a
  // column index. Then the components w.r.t. e-hat are given by:
  //
  // Te[m][n] = sum k{ sum l{ B[k][m]*B[l][n]*Tf[k][l] }}
  //
  // For a twice contravariant tensor, the transform is:
  //
  // Te[m][n] = sum k{ sum l{ C[m][k]*C[n][l]*Tf[k][l] }}
  //
  // where C is the inverse of B.

  // Transfer the tensor components into a full matrix
  // Note that the schema currently stores the matrix
  // elements in upper triangular row order.

  typedef st2_e3_lite::value_type value_type;

  value_type xx = xv[0];
  value_type xy = xv[1];
  value_type xz = xv[2];
  value_type yy = xv[3];
  value_type yz = xv[4];
  value_type zz = xv[5];

  general_matrix_3x3<value_type> Tf;

  Tf[0][0] = xx;
  Tf[0][1] = xy;
  Tf[0][2] = xz;

  Tf[1][0] = xy;
  Tf[1][1] = yy;
  Tf[1][2] = yz;

  Tf[2][0] = xz;
  Tf[2][1] = yz;
  Tf[2][2] = zz;

  // Make Te the matrix of xv (we have copied it so we can now overwrite it).

  st2_e3_lite::matrix_type& Te = xv;

  ///@issue What do we want to do here?

  if(!is_contravariant)
  {
    // Covariant case.

    // Get the basis transform matrix.

    const gl3_lite::matrix_type& B = xtransform.basis_matrix();

    // Transform the components;
    // only need to compute upper triangular part.

    for(int m=0; m<3; ++m)
    {
      for(int n=m; n<3; ++n)
      {
        value_type Te_mn = 0.0;
        for(int k=0; k<3; ++k)
        {
          for(int l=0; l<3; ++l)
          {
            Te_mn += B[k][m]*B[l][n]*Tf[k][l];
          } 
        }
        Te[m][n] = Te_mn;
      }
    }
  }
  else
  {
    // Contravariant case.

    // Get the component transform matrix.

    const gl3_lite::matrix_type& C = xtransform.component_matrix();

    // Transform the components;
    // only need to compute upper triangular part.

    for(int m=0; m<3; ++m)
    {
      for(int n=m; n<3; ++n)
      {
        value_type Te_mn = 0.0;
        for(int k=0; k<3; ++k)
        {
          for(int l=0; l<3; ++l)
          {
            Te_mn += C[m][k]*C[n][l]*Tf[k][l];
          }
        }
        Te[m][n] = Te_mn;
      }
    }
  }

  // Postconditions:

  // Exit:

}


//==============================================================================
// TEMPLATE SPECIALIZATIONS
//==============================================================================

///
void
fiber_bundle::st2_algebra::
determinant(const st2_e3& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  vd_value_type a00 = x0.component(0, 0);
  vd_value_type a01 = x0.component(0, 1);
  vd_value_type a02 = x0.component(0, 2);
  vd_value_type a10 = a01;
  vd_value_type a11 = x0.component(1, 1);
  vd_value_type a12 = x0.component(1, 2);
  vd_value_type a20 = a02;
  vd_value_type a21 = a12;
  vd_value_type a22 = x0.component(2, 2);

  vd_value_type c00 = a11*a22 - a12*a21;
  vd_value_type c01 = a12*a20 - a10*a22;
  vd_value_type c02 = a10*a21 - a11*a20;

  xresult = a00*c00 + a01*c01 + a02*c02;

  if(xauto_access)
  {
    x0.release_access();
  }

  // Postconditions:

  ensure(unexecutable("xresult == determinant of x0"));

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
determinant(const st2_e3& x0, bool xauto_access)
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

///
void
fiber_bundle::st2_algebra::
determinant(const st2_e3_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type a00 = x0.component(0, 0);
  vd_value_type a01 = x0.component(0, 1);
  vd_value_type a02 = x0.component(0, 2);
  vd_value_type a10 = a01;
  vd_value_type a11 = x0.component(1, 1);
  vd_value_type a12 = x0.component(1, 2);
  vd_value_type a20 = a02;
  vd_value_type a21 = a12;
  vd_value_type a22 = x0.component(2, 2);

  vd_value_type c00 = a11*a22 - a12*a21;
  vd_value_type c01 = a12*a20 - a10*a22;
  vd_value_type c02 = a10*a21 - a11*a20;

  xresult = a00*c00 + a01*c01 + a02*c02;

  // Postconditions:

  ensure(unexecutable("xresult == determinant of x0"));

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
determinant(const st2_e3_lite& x0)
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

// ===========================================================
// TEMPLATE SPECIALIZATIONS
// ===========================================================

template <>
void
fiber_bundle::st2_algebra::
to_principal_axes(const st2_e3_lite& xlite, gl3_lite& xtransform, st2_e3_lite& xresult)
{
  // Preconditions:

  // Body:

  // Calculate the eigenvalues and eigenvectors using the
  // Jacobi transformation (iterative) method.

  const st2_e3_lite::matrix_type& mlite = xlite;
  st2_e3_lite::matrix_type& mresult = xresult;

  jacobi_transformation(mlite, xtransform.basis_matrix(), mresult);

  // The component part of xtransform is the inverse of the basis part
  // (but in the symmetric case; the transform and the inverse are
  // identical and the transform is quicker to calculate).

  xtransform.basis_matrix().transpose(xtransform.component_matrix());

  // Postconditions:

  // Exit:
}
