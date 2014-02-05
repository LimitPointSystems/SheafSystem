
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
/// Implementation for class t3_e3

#include "t3_e3.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "tp_space.h"
#include "wsv_block.h"

#include "at3_e3.h"
#include "st3_e3.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS T3_E3_LITE
//==============================================================================

//==============================================================================
// T3_E3 FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t3_e3_lite::
t3_e3_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_e3_lite::
t3_e3_lite(const t3_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_e3_lite&
fiber_bundle::t3_e3_lite::
operator=(const t3_e3_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;

  // Postconditions:

  ensure(invariant());
  ensure_for_all(i, 0, d(), component(i) == xother[i]); 

  // Exit:

  return *this;
}

fiber_bundle::t3_e3_lite::
~t3_e3_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::t3_e3_lite::
t3_e3_lite(const at3_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_e3_lite&
fiber_bundle::t3_e3_lite::
operator=(const at3_e3_lite& xother)
{

  // Preconditions:

  // Body:

  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
      {
        value_type lcomp = xother.component(i, j, k);
        put_component(i, j, k, lcomp);
      }
    }
  }
 
  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t3_e3_lite::
t3_e3_lite(const st3_e3_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_e3_lite&
fiber_bundle::t3_e3_lite::
operator=(const st3_e3_lite& xother)
{

  // Preconditions:

  // Body:

  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
      {
        value_type lcomp = xother.component(i, j, k);
        put_component(i, j, k, lcomp);
      }
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t3_e3_lite::
t3_e3_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t3_e3_lite&
fiber_bundle::t3_e3_lite::
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

fiber_bundle::t3_e3_lite::
operator t3_e3_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t3_e3_lite::
operator const t3_e3_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// T3 FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t3_e3_lite::
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
// VECTOR ALGEBRA (VD) FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::t3_e3_lite::
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
fiber_bundle::t3_e3_lite::
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
fiber_bundle::t3_e3_lite::
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

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::t3_e3_lite::
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
fiber_bundle::t3_e3_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t3_e3_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t3_e3_lite*
fiber_bundle::t3_e3_lite::
clone() const
{
  t3_e3_lite* result = 0;

  // Preconditions:

  // Body:

  result = new t3_e3_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T3_E3_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t3_e3_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t3_e3_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::t3_e3_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(t3_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::t3_e3_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::t3_e3_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS T3_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS T3_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::t3_e3::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "t3_e3_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::t3_e3::
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
  lmember_names       += "xyx DOUBLE false ";
  lmember_names       += "xyy DOUBLE false ";
  lmember_names       += "xyz DOUBLE false ";
  lmember_names       += "xzx DOUBLE false ";
  lmember_names       += "xzy DOUBLE false ";
  lmember_names       += "xzz DOUBLE false ";
  lmember_names       += "yxx DOUBLE false ";
  lmember_names       += "yxy DOUBLE false ";
  lmember_names       += "yxz DOUBLE false ";
  lmember_names       += "yyx DOUBLE false ";
  lmember_names       += "yyy DOUBLE false ";
  lmember_names       += "yyz DOUBLE false ";
  lmember_names       += "yzx DOUBLE false ";
  lmember_names       += "yzy DOUBLE false ";
  lmember_names       += "yzz DOUBLE false ";
  lmember_names       += "zxx DOUBLE false ";
  lmember_names       += "zxy DOUBLE false ";
  lmember_names       += "zxz DOUBLE false ";
  lmember_names       += "zyx DOUBLE false ";
  lmember_names       += "zyy DOUBLE false ";
  lmember_names       += "zyz DOUBLE false ";
  lmember_names       += "zzx DOUBLE false ";
  lmember_names       += "zzy DOUBLE false ";
  lmember_names       += "zzz DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              t3::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::t3_e3::host_type&
fiber_bundle::t3_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering t3_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 27);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 3);

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, 3, xvector_space_path, xauto_access));   

  // Body:

  host_type& result = 
    host_type::new_table(xns, xhost_path, xschema_path, 3, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 27);
  ensure(result.d(true) == 27);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 3);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving t3_e3::new_host." << endl;
  return result;
}

fiber_bundle::t3_e3::host_type&
fiber_bundle::t3_e3::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering t3_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<t3_e3>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<t3_e3>(xsuffix));

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
  ensure(result.path(true) == standard_host_path<t3_e3>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 27);
  ensure(result.d(true) == 27);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 3);
  ensure(result.dd(true) == 3);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving t3_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// T3_E3 FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t3_e3::
t3_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::t3_e3::
t3_e3(const t3_e3& xother)
{

  // Preconditions:


  // Body:

  attach_to_state(const_cast<t3_e3*>(&xother));

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::t3_e3&
fiber_bundle::t3_e3::
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
fiber_bundle::t3_e3&
fiber_bundle::t3_e3::
operator=(const t3_e3& xother)
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

fiber_bundle::t3_e3::
~t3_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

const fiber_bundle::t3_e3::volatile_type&
fiber_bundle::t3_e3::
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
fiber_bundle::t3_e3::volatile_type*
fiber_bundle::t3_e3::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::t3_e3::
t3_e3(poset* xhost, bool xauto_access)
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

fiber_bundle::t3_e3::
t3_e3(poset_state_handle& xhost,
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

fiber_bundle::t3_e3&
fiber_bundle::t3_e3::
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

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::t3_e3::
t3_e3(const poset* xhost, pod_index_type xhub_id)
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

fiber_bundle::t3_e3::
t3_e3(const poset* xhost, const scoped_index& xid)
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

fiber_bundle::t3_e3::
t3_e3(const poset* xhost, const std::string& xname)
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

fiber_bundle::t3_e3::
operator t3_e3::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t3_e3::
operator const t3_e3::row_dofs_type& () const
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
// T3 FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::t3_e3::
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
fiber_bundle::t3_e3::
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
fiber_bundle::t3_e3::
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
// ABSTRACT POSET MEMBER FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::t3_e3::
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
fiber_bundle::t3_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t3_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t3_e3*
fiber_bundle::t3_e3::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  t3_e3 *result = new t3_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T3_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t3_e3::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(t3::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? dd() == 3 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

bool
fiber_bundle::t3_e3::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this.

  bool result = dynamic_cast<const t3_e3*>(xother) != 0;

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

#include "at3_e3.h"
#include "st3_e3.h"

void
fiber_bundle::tp_algebra::
alt(const t3_e3_lite& x0, at3_e3_lite& xresult)
{
  // Preconditions:

  //require(x0.dd() == xresult.dd());

  // Body:

  // Postconditions:

  //$$SCRIBBLE: For at3_e3 we know that d=1 for the antisymmetric tensor;
  //            so we just need to calculate lvalue for (0,1,2)

  vd_value_type lvalue = x0.component(0,1,2)
                       + x0.component(1,2,0)
                       + x0.component(2,0,1)
                       - x0.component(1,0,2)
                       - x0.component(2,1,0)
                       - x0.component(0,2,1);

  lvalue /= 6.0; // 3!

  xresult.put_component(0, lvalue);

  // Postconditions:

  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
alt(const t3_e3& x0, at3_e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
  require(!x0.variance(xauto_access).is_mixed());

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
    xresult.get_read_write_access(true);
  }

  //$$SCRIBBLE: For at3_e3 we know that d=1 for the antisymmetric tensor;
  //            so we just need to calculate lvalue for (0,1,2)

  vd_value_type lvalue = x0.component(0,1,2)
                       + x0.component(1,2,0)
                       + x0.component(2,0,1)
                       - x0.component(1,0,2)
                       - x0.component(2,1,0)
                       - x0.component(0,2,1);

  lvalue /= 6.0; // 3!

  xresult.put_component(0, lvalue);

  // Set the variance of the result.

  xresult.put_variance(x0.variance(false), false);


  // Postconditions:

  ensure(xresult.variance(xauto_access) == x0.variance(xauto_access));
  ensure(unexecutable("xresult is equal to the symmetric part of x0"));

  // Exit:

  return;
}

void
fiber_bundle::tp_algebra::
sym(const t3_e3_lite& x0, st3_e3_lite& xresult)
{
  // Preconditions:

  // Body:

  int ldd = x0.dd();

  for(int i=0; i<ldd; ++i)
  {
    for(int j=i; j<ldd; ++j)
    {
      for(int k=j; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i,j,k)
                             + x0.component(j,k,i)
                             + x0.component(k,i,j)
                             + x0.component(j,i,k)
                             + x0.component(k,j,i)
                             + x0.component(i,k,j);

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
sym(const t3_e3& x0, st3_e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_accessible(xauto_access));
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
    for(int j=i; j<ldd; ++j)
    {
      for(int k=j; k<ldd; ++k)
      {
        vd_value_type lvalue = x0.component(i,j,k)
                             + x0.component(j,k,i)
                             + x0.component(k,i,j)
                             + x0.component(j,i,k)
                             + x0.component(k,j,i)
                             + x0.component(i,k,j);

        lvalue /= 6.0; // 3!
        xresult.put_component(i, j, k, lvalue);
      }
    }
  }

  // Set the variance of the result.

  //
  // Variance of result is same as variance of x0.
  //

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

