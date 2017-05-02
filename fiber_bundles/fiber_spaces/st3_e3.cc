
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

// Implementation for class st3_e3.

#include "SheafSystem/st3_e3.impl.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/wsv_block.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ST3_E3_LITE
//==============================================================================

//==============================================================================
// ST3_E3 FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st3_e3_lite::
st3_e3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_e3_lite::
st3_e3_lite(const st3_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_e3_lite&
fiber_bundle::st3_e3_lite::
operator=(const st3_e3_lite& xother)
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

fiber_bundle::st3_e3_lite::
~st3_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::st3_e3_lite::
st3_e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st3_e3_lite&
fiber_bundle::st3_e3_lite::
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

fiber_bundle::st3_e3_lite::
operator st3_e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st3_e3_lite::
operator const st3_e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}


// fiber_bundle::st3_e3_lite::
// st3_e3_lite(const value_type& xcomp)
// {
//   // Preconditions:

//   // Body:

//   put_components(xcomp);

//   // Postconditions:

//   // Exit:
// }

// void
// fiber_bundle::st3_e3_lite::
// put_components(const value_type& xcomp)
// {
//   // Preconditions:

//   // Body:

//   put_component(0, xcomp);

//   // Postconditions:

//   ensure(invariant());
//   ensure(isunordered_or_equals(component(0), xcomp));

//   // Exit:
// }

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (ST3) FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st3_e3_lite::
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
// VECTOR ALGEBRA (VD) FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::st3_e3_lite::
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
fiber_bundle::st3_e3_lite::
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
fiber_bundle::st3_e3_lite::
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
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st3_e3_lite::
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
fiber_bundle::st3_e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st3_e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st3_e3_lite*
fiber_bundle::st3_e3_lite::
clone() const
{
  st3_e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st3_e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st3_e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st3_e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::st3_e3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st3_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::st3_e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::st3_e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS ST3_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS ST3_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st3_e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st3_e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st3_e3::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  string lmember_names = "xxx DOUBLE false ";
  lmember_names       += "xxy DOUBLE false ";
  lmember_names       += "xxz DOUBLE false ";
  lmember_names       += "xyy DOUBLE false ";
  lmember_names       += "xyz DOUBLE false ";
  lmember_names       += "xzz DOUBLE false ";
  lmember_names       += "yyy DOUBLE false ";
  lmember_names       += "yyz DOUBLE false ";
  lmember_names       += "yzz DOUBLE false ";
  lmember_names       += "zzz DOUBLE false ";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              st3::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::st3_e3::host_type&
fiber_bundle::st3_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st3_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 10);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 3);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 3, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 10);
  ensure(result.d(true) == 10);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 3);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving st3_e3::new_host." << endl;
  return result;
}

fiber_bundle::st3_e3::host_type&
fiber_bundle::st3_e3::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering st3_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<st3_e3>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<st3_e3>(xsuffix));

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
  ensure(result.path(true) == standard_host_path<st3_e3>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 10);
  ensure(result.d(true) == 10);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 3);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving st3_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// ST3_E3 FACET OF CLASS ST3_E3
//==============================================================================

fiber_bundle::st3_e3::
st3_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st3_e3::
st3_e3(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::st3_e3::
st3_e3(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::st3_e3::
st3_e3(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::st3_e3::
st3_e3(abstract_poset_member* xother)
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

fiber_bundle::st3_e3::
st3_e3(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::st3_e3::
st3_e3(poset_state_handle& xhost,
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


fiber_bundle::st3_e3&
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3&
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3&
fiber_bundle::st3_e3::
operator=(const st3_e3& xother)
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

fiber_bundle::st3_e3::
~st3_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

}


const fiber_bundle::st3_e3::volatile_type&
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3::volatile_type*
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3::
put_components(dof_type xcomp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));

  // Exit:

  return;
}

fiber_bundle::st3_e3::
operator st3_e3::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st3_e3::
operator const st3_e3::row_dofs_type& () const
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
// ST3 FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3::
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


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st3_e3::
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
fiber_bundle::st3_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st3_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st3_e3*
fiber_bundle::st3_e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st3_e3* result = new st3_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st3_e3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const st3_e3*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;

}


bool
fiber_bundle::st3_e3::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st3::invariant());

    // Invariances for this class:

    invariance((state_is_read_accessible() ? dd()  == 3 : true));
    invariance((state_is_read_accessible() ? d()  == 10 : true));

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


