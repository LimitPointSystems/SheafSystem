
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
/// Implementation for class st2_e2

#include "ComLimitPoint/fiber_bundle/st2_e2.impl.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/at1_space.h"
#include "ComLimitPoint/fiber_bundle/stp_space.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "ComLimitPoint/fiber_bundle/stp_space.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS ST2_E2_LITE
//==============================================================================

//==============================================================================
// COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2 FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::st2_e2_lite::
st2_e2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_e2_lite::
st2_e2_lite(const st2_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::st2_e2_lite&
fiber_bundle::st2_e2_lite::
operator=(const st2_e2_lite& xother)
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

fiber_bundle::st2_e2_lite::
~st2_e2_lite()
{
  // Preconditions:

  // Body:


  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e2_lite::
st2_e2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e2_lite&
fiber_bundle::st2_e2_lite::
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

fiber_bundle::st2_e2_lite::
st2_e2_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  // Exit:
}

fiber_bundle::st2_e2_lite& 
fiber_bundle::st2_e2_lite::
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

fiber_bundle::st2_e2_lite::
operator st2_e2_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e2_lite::
operator const st2_e2_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e2_lite::
operator st2_e2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e2_lite::
operator const st2_e2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e2_lite::
st2_e2_lite(const value_type& xx,
            const value_type& xy,
            const value_type& yy)
{
  // Preconditions:

  // Body:

  put_components(xx, xy, yy);

  // Postconditions:

  // Exit:
}

void
fiber_bundle::st2_e2_lite::
put_components(const value_type& xx_comp,
               const value_type& xy_comp,
               const value_type& yy_comp)
{
  // Preconditions:

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, yy_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yy_comp));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (ST2) FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::st2_e2_lite::
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
// VECTOR ALGEBRA (VD) FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::st2_e2_lite::
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
fiber_bundle::st2_e2_lite::
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
fiber_bundle::st2_e2_lite::
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
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st2_e2_lite::
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
fiber_bundle::st2_e2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_e2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2_e2_lite*
fiber_bundle::st2_e2_lite::
clone() const
{
  st2_e2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new st2_e2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ST2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st2_e2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const st2_e2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::st2_e2_lite::
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
fiber_bundle::st2_e2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::st2_e2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::st2_e2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "st2_e2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::st2_e2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "xx DOUBLE false ";
  lmember_names       += "xy DOUBLE false ";
  lmember_names       += "yy DOUBLE false";

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

fiber_bundle::st2_e2::host_type&
fiber_bundle::st2_e2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering st2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 3);
  
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

  ensure(result.factor_ct(true) == 3);
  ensure(result.d(true) == 3);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving st2_e2::new_host." << endl;
  return result;
}

fiber_bundle::st2_e2::host_type&
fiber_bundle::st2_e2::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering st2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<st2_e2>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<st2_e2>(xsuffix));

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
  ensure(result.path(true) == standard_host_path<st2_e2>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 3);
  ensure(result.d(true) == 3);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving st2_e2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2 FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2::
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

fiber_bundle::st2_e2::
st2_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::st2_e2::
st2_e2(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::st2_e2::
st2_e2(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::st2_e2::
st2_e2(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::st2_e2::
st2_e2(abstract_poset_member* xother)
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

fiber_bundle::st2_e2::
st2_e2(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::st2_e2::
st2_e2(poset_state_handle& xhost,
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

fiber_bundle::st2_e2&
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2&
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2&
fiber_bundle::st2_e2::
operator=(const st2_e2& xother)
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

fiber_bundle::st2_e2::
~st2_e2()
{

  // Preconditions:

  // Body:


  // Postconditions:

  // Exit:

}

const fiber_bundle::st2_e2::volatile_type&
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2::volatile_type*
fiber_bundle::st2_e2::
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
// ST2 FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::st2_e2::
put_components(dof_type xx_comp, dof_type xy_comp, dof_type yy_comp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, yy_comp);


  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yy_comp));

  // Exit:

  return;
}

fiber_bundle::st2_e2::
operator st2_e2::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::st2_e2::
operator const st2_e2::row_dofs_type& () const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  const row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::st2_e2::
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
fiber_bundle::st2_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("st2_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::st2_e2*
fiber_bundle::st2_e2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  st2_e2* result = new st2_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS COM_LIMITPOINT_FIBER_BUNDLE_ST2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::st2_e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const st2_e2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::st2_e2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st2::invariant());

    // Invariants for this class:

    invariance(state_is_read_accessible() ? (dd() == 2) : true);
    invariance(state_is_read_accessible() ? (d()  == 3) : true);

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
void
fiber_bundle::st2_algebra::
determinant(const st2_e2& x0, vd_value_type& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    x0.get_read_access();
  }

  vd_value_type a00 = x0.component(0);
  vd_value_type a01 = x0.component(1);
  vd_value_type a11 = x0.component(2);

  xresult = a00*a11 - a01*a01;

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
determinant(const st2_e2& x0, bool xauto_access)
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
determinant(const st2_e2_lite& x0, vd_value_type& xresult)
{
  // Preconditions:

  // Body:

  vd_value_type a00 = x0.component(0);
  vd_value_type a01 = x0.component(1);
  vd_value_type a11 = x0.component(2);

  xresult = a00*a11 - a01*a01;

  // Postconditions:

  ensure(unexecutable("xresult == determinant of x0"));

  // Exit:

  return;
}

///
fiber_bundle::vd_value_type
fiber_bundle::st2_algebra::
determinant(const st2_e2_lite& x0)
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
to_principal_axes(const st2_e2_lite& xlite, gl2_lite& xtransform, st2_e2_lite& xresult)
{
  // Preconditions:

  // Body:

  // The principal axis transformation is known in closed form for the 2d case,
  // and is described in various introductory continuum mechanics texts. 
  // See, for example, Fung, Y. C., "Foundations of Solid Mechanics", pg. 71.

  // Use the matrix diagonalization function to compute xresult.

  const st2_e2_lite::matrix_type& mlite = xlite;
  mlite.diagonalization(xresult);

  // Compute the transformation. 

  typedef st2_e2_lite::value_type value_type;

  value_type sxx = xlite[0];
  value_type sxy = xlite[1];
  value_type syy = xlite[2];

  value_type theta = 0.5*atan2(2.0*sxy, sxx-syy);

  value_type cos_theta = cos(theta);
  value_type sin_theta = sin(theta);

  // Basis transformation:

  xtransform[0] =  cos_theta; // bxx
  xtransform[1] =  sin_theta; // bxy
  xtransform[2] = -sin_theta; // byx
  xtransform[3] =  cos_theta; // byy

  // Component transformation (the inverse of the basis transformation):

  xtransform[4] =  cos_theta; // cxx
  xtransform[5] = -sin_theta; // cxy
  xtransform[6] =  sin_theta; // cyx
  xtransform[7] =  cos_theta; // cyy

  // Postconditions:

  // Exit:
}

template <>
void
fiber_bundle::st2_algebra::
to_principal_axes(const st2_e2_lite& xlite, const st2_e2_lite& xpd_lite, gl2_lite& xtransform, st2_e2_lite& xresult)
{
  // Preconditions:

  const st2_e2_lite::matrix_type& mlite = xpd_lite;
  bool xpd_lite_is_positive_definite = mlite.is_positive_definite();

  require(xpd_lite_is_positive_definite == true);

  // Body:

  ///@todo Optimimize the following code.

  // This feature solves the problem
  //    [[xdofs] - lambda * [xpd_dofs]] * v = lambda * v
  // where [xdofs] and [xpd_dofs] are 2x2 symmetric matrices and
  // [xpd_dofs] is positive definite.

  // The principal axis algorithm is clumsy to express in terms of
  // row dof tuple member names.  It's much easier to express in terms
  // of more traditional array expressions.

  const st2_e2_lite::row_dofs_type& lrdt    = xlite;
  const st2_e2_lite::row_dofs_type& lpd_rdt = xpd_lite;

  gl2_lite::row_dofs_type& ltransform_rdt   = xtransform;
  st2_e2_lite::row_dofs_type& lresult_rdt   = xresult;

  typedef st2_e2_lite::row_dofs_type::dof_type dof_type;

  const dof_type* lxdofs    =
    reinterpret_cast<const dof_type*>(lrdt.components);

  const dof_type* lxpd_dofs =
    reinterpret_cast<const dof_type*>(lpd_rdt.components);

  dof_type* ltransform_dofs =
    reinterpret_cast<dof_type*>(ltransform_rdt.components);

  dof_type* lresult_dofs    =
    reinterpret_cast<dof_type*>(lresult_rdt.components);

  // Form the quadratic expression ax^2+bx+c from
  // det(xdofs-lambda*xpd_dofs) = 0.

  dof_type a = lxpd_dofs[0]*lxpd_dofs[2] - lxpd_dofs[1]*lxpd_dofs[1];

  dof_type b = 2*lxdofs[1]*lxpd_dofs[1]-lxdofs[0]*lxpd_dofs[2]
               -lxdofs[2]*lxpd_dofs[0];

  dof_type c = lxdofs[0]*lxdofs[2] - lxdofs[1]*lxdofs[1];

  // In exact arithmetic, the discriminant is guaranteed to be > 0,
  // since the eigenvalues are guaranteed to be real.
  // Use the absolute value to ensure this in finite precision.

  dof_type sqrt_discr = sqrt(abs(b*b-4*a*c));
  
  // The eigenvalues.

  lresult_dofs[0] = (-b+sqrt_discr)/2/a;
  lresult_dofs[1] = 0;
  lresult_dofs[2] = (-b-sqrt_discr)/2/a;

  // `ss' is the matrix [xdofs]-lambda*[xpd_dofs].

  dof_type ss[3];

  // For each eigenvalue, compute the eigenvector.

  // The following discussion is based on exact
  // arithmetic.

  // `ss' represents a singular symmetric matrix.
  // We are seeking a solution to
  //        [ss]{v} = {0}.
  //
  // We want to distinguish several cases for constructing
  // eigenvectors, and in preparation we observe:
  //   det(ss) == 0 == ss(0,0)*ss(1,1)-ss(0,1)^2
  // Therefore
  //   ss(0,0)*ss(1,1) == ss(0,1)^2
  // Notice that when the off diagonal elements
  // of ss are 0, then at least one of the diagonals
  // is 0.  When the off diagonal elements of ss
  // are nonzero, then neither of the diagonal
  // elements can be zero.
  //
  // All of the possible forms of ss are enumerated
  // in the following cases:
  //
  // Case 1:
  //
  // The offdiagonals are zero and so are the
  // diagonals.  Any vector is an eigenvector.
  // We choose (1,0) for the 1st
  // eigenvector and (0,1) for the 2nd.
  //
  // Case 2:
  //
  // The offdiagonals are zero and the diagonal is
  // (not zero, zero).  Then (0,1) is an
  // eigenvector.
  //
  // Case 3:
  //
  // The offdiagonals are zero and the diagonal is
  // (zero, not zero).  Then (1, 0) is an
  // eigenvector.
  //
  // Case 4:
  //
  // The offdiagonals are not zero and the diagonals
  // are not zero.  In this case, one can prove that
  // the 2nd row of ss is a scalar multiple of the

  // 1st row.  Then (-ss(0,1), ss(0,0)) is normal
  // to both the 1st and 2nd rows of ss and is
  // an eigenvector.

  for(int i=0; i<2; ++i)
  {
    // Compute [xdofs]-lambda[i]*[xpd_dofs].

    dof_type lambda = (i == 0) ? lresult_dofs[0] : lresult_dofs[2];

    ss[0] = lxdofs[0]-lambda*lxpd_dofs[0];
    ss[1] = lxdofs[1]-lambda*lxpd_dofs[1];
    ss[2] = lxdofs[2]-lambda*lxpd_dofs[2];

    if(ss[1] == 0)
    {
      if(ss[2] == 0)
      {
        if(ss[0] == 0)
        {
          // Case 1:

          if(i == 0)
          {
            // 1st eigenvector

            ltransform_dofs[0] = 1;
            ltransform_dofs[2] = 0;
          }
          else
          {
            // 2nd eigenvector

            ltransform_dofs[1] = 0;
            ltransform_dofs[3] = 1;
          }
        }
        else
        {
          // Case 2:

          ltransform_dofs[i]   = 0;
          ltransform_dofs[2+i] = 1;
        }
      }
      else
      {
        // Case 3:

        ltransform_dofs[i]   = 1;
        ltransform_dofs[2+i] = 0;
      }
    }
    else
    {
      // Case 4:

      ltransform_dofs[i]   = -ss[1];
      ltransform_dofs[2+i] =  ss[0];
    }

    // Normalize the eigenvector.  The normalization we use is
    // (v) * [xpd_dofs] * {v} = 1
    // One can show that this normalization produces the following
    // results:
    // [xtransform_dofs] transpose * [xpd_dofs] * [xtransform_dofs]
    //    = diagonal(1, 1)
    // [xtransform_dofs] transpose * [xdofs   ] * [xtransform_dofs]
    //    = diagonal(lambda[0], lambda[1])

    // d  = {v} transpose * [g] * {v} > 0 since [xpd_dofs] is positive definite.

    dof_type d =
      ltransform_dofs[i]*
        (ltransform_dofs[i]*lxpd_dofs[0]+ltransform_dofs[2+i]*lxpd_dofs[1])
     +ltransform_dofs[2+i]*
        (ltransform_dofs[i]*lxpd_dofs[1]+ltransform_dofs[2+i]*lxpd_dofs[2]);

    d = sqrt(d);

    ltransform_dofs[i]   /= d;
    ltransform_dofs[2+i] /= d;
  }

  // Assign the inverse transform.

  dof_type det = ltransform_dofs[0]*ltransform_dofs[3]
               - ltransform_dofs[1]*ltransform_dofs[2];

  ltransform_dofs[4] =  ltransform_dofs[3]/det; 
  ltransform_dofs[5] = -ltransform_dofs[1]/det; 
  ltransform_dofs[6] = -ltransform_dofs[2]/det; 
  ltransform_dofs[7] =  ltransform_dofs[0]/det; 
  
  // Postconditions:

  // Exit:

}
