
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
/// Implementation for class t2_e2.

#include "t2_e2.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "tp_space.h"
#include "wsv_block.h"

#include "at2_e2.h"
#include "st2_e2.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS T2_E2_LITE
//==============================================================================

//==============================================================================
// T2_E2 FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t2_e2_lite::
t2_e2_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_e2_lite::
t2_e2_lite(const t2_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_e2_lite&
fiber_bundle::t2_e2_lite::
operator=(const t2_e2_lite& xother)
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

fiber_bundle::t2_e2_lite::
~t2_e2_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::t2_e2_lite::
t2_e2_lite(const at2_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_e2_lite&
fiber_bundle::t2_e2_lite::
operator=(const at2_e2_lite& xother)
{

  // Preconditions:

  // Body:

  for(int i=0; i<2; i++)
  {
    for(int j=0; j<2; j++)
    {
      value_type lcomp = xother.component(i, j);
      put_component(i, j, lcomp);
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t2_e2_lite::
t2_e2_lite(const st2_e2_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_e2_lite&
fiber_bundle::t2_e2_lite::
operator=(const st2_e2_lite& xother)
{

  // Preconditions:

  // Body:

  for(int i=0; i<2; i++)
  {
    for(int j=0; j<2; j++)
    {
      value_type lcomp = xother.component(i, j);
      put_component(i, j, lcomp);
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::t2_e2_lite::
t2_e2_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::t2_e2_lite&
fiber_bundle::t2_e2_lite::
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

fiber_bundle::t2_e2_lite::
t2_e2_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::t2_e2_lite& 
fiber_bundle::t2_e2_lite::
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

fiber_bundle::t2_e2_lite::
operator t2_e2_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t2_e2_lite::
operator const t2_e2_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t2_e2_lite::
operator t2_e2_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t2_e2_lite::
operator const t2_e2_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t2_e2_lite::
t2_e2_lite(const value_type& xx_comp,
            const value_type& xy_comp,
            const value_type& yx_comp,
            const value_type& yy_comp)
{
  // Preconditions:

  // Body:

  put_components(xx_comp, xy_comp, yx_comp, yy_comp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yx_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));

  // Exit:
}

void
fiber_bundle::t2_e2_lite::
put_components(value_type xx_comp,
               value_type xy_comp,
               value_type yx_comp,
               value_type yy_comp)
{
  // Preconditions:

  // Body:

  put_component(0, xx_comp);
  put_component(1, xy_comp);
  put_component(2, yx_comp);
  put_component(3, yy_comp);

  // Postconditions:

  ensure(invariant());

  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yx_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));

  // Exit:
}

//==============================================================================
// T2 FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::t2_e2_lite::
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
// VECTOR ALGEBRA (VD) FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::t2_e2_lite::
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
fiber_bundle::t2_e2_lite::
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
fiber_bundle::t2_e2_lite::
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

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::t2_e2_lite::
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
fiber_bundle::t2_e2_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t2_e2_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t2_e2_lite*
fiber_bundle::t2_e2_lite::
clone() const
{
  t2_e2_lite* result = 0;

  // Preconditions:

  // Body:

  result = new t2_e2_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T2_E2_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t2_e2_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t2_e2_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::t2_e2_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(t2_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::t2_e2_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::t2_e2_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS T2_E2
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS T2_E2
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::t2_e2::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "t2_e2_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::t2_e2::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "xx DOUBLE false ";
  lmember_names       += "xy DOUBLE false ";
  lmember_names       += "yx DOUBLE false ";
  lmember_names       += "yy DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              t2::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::t2_e2::host_type&
fiber_bundle::t2_e2::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering t2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 4);
  
  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));
  require(xns.member_poset(xvector_space_path, xauto_access).schema(xauto_access).conforms_to(vector_space_type::standard_schema_path()));
  require(xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d(xauto_access) == 2);

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, 2, xvector_space_path, xauto_access));   

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 4);
  ensure(result.d(true) == 4);
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path());
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving t2_e2::new_host." << endl;
  return result;
}

fiber_bundle::t2_e2::host_type&
fiber_bundle::t2_e2::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering t2_e2::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<t2_e2>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<vector_space_type>(xsuffix), xauto_access));

  // Body:

  // Create the vector space if necessary.

  poset_path lvector_space_path = vector_space_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<t2_e2>(xsuffix));

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
  ensure(result.path(true) == standard_host_path<t2_e2>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 4);
  ensure(result.d(true) == 4);
  ensure(result.scalar_space_path(true) == standard_host_path<vector_space_type::scalar_type>(xsuffix) );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == 2);
  ensure(result.vector_space_path(true) == standard_host_path<vector_space_type>(xsuffix) );

  // Exit:

  // cout << "Leaving t2_e2::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// T2_E2 FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::t2_e2::
t2_e2()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::t2_e2::
t2_e2(const t2_e2& xother)
{

  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::t2_e2&
fiber_bundle::t2_e2::
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
fiber_bundle::t2_e2&
fiber_bundle::t2_e2::
operator=(const t2_e2& xother)
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

fiber_bundle::t2_e2::
~t2_e2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

const fiber_bundle::t2_e2::volatile_type&
fiber_bundle::t2_e2::
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
fiber_bundle::t2_e2::volatile_type*
fiber_bundle::t2_e2::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::t2_e2::
t2_e2(poset* xhost, bool xauto_access)
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

fiber_bundle::t2_e2::
t2_e2(poset_state_handle& xhost,
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

fiber_bundle::t2_e2&
fiber_bundle::t2_e2::
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

fiber_bundle::t2_e2::
t2_e2(const poset* xhost, pod_index_type xhub_id)
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

fiber_bundle::t2_e2::
t2_e2(const poset* xhost, const scoped_index& xid)
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

fiber_bundle::t2_e2::
t2_e2(const poset* xhost, const std::string& xname)
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

void
fiber_bundle::t2_e2::
put_components(dof_type xx_comp, dof_type xy_comp,
               dof_type yx_comp, dof_type yy_comp)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  (*this)[0] = xx_comp;
  (*this)[1] = xy_comp;
  (*this)[2] = yx_comp;
  (*this)[3] = yy_comp;

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xx_comp));
  ensure(isunordered_or_equals(component(1), xy_comp));
  ensure(isunordered_or_equals(component(2), yx_comp));
  ensure(isunordered_or_equals(component(3), yy_comp));

  // Exit:

  return;
}

fiber_bundle::t2_e2::
operator t2_e2::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::t2_e2::
operator const t2_e2::row_dofs_type& () const
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
// T2 FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::t2_e2::
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
fiber_bundle::t2_e2::
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
fiber_bundle::t2_e2::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::t2_e2::
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
fiber_bundle::t2_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("t2_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::t2_e2*
fiber_bundle::t2_e2::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  t2_e2* result = new t2_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS T2_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::t2_e2::
invariant() const
{
  bool result = true;

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(t2::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? dd() == 2 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

bool
fiber_bundle::t2_e2::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const t2_e2*>(xother) != 0;

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

