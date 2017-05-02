
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
/// Implementation for class e4.

#include "SheafSystem/e4.impl.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/stp.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS E4_LITE
//==============================================================================


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E4) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e4_lite::
e4_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e4_lite::
e4_lite(const e4_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e4_lite&
fiber_bundle::e4_lite::
operator=(const e4_lite& xother)
{

  // Preconditions:

  // Body:

  if(this == &xother)
    return *this;

  _row_dofs = xother._row_dofs;
  
  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(*this == xother));

  // Exit:

  return *this;
}

fiber_bundle::e4_lite::
~e4_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

fiber_bundle::e4_lite::
e4_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  // Exit:
}

fiber_bundle::e4_lite&
fiber_bundle::e4_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  _row_dofs = xrow_dofs;

  // Postconditions:

  ensure(invariant());
  ensure(unexecutable(row_dofs() == xrow_dofs));
  //ensure_for_all(i, 0, d(), component(i) == xrow_dofs[i]);

  // Exit:

  return *this;

}

fiber_bundle::e4_lite::
e4_lite(const value_type& x0,
        const value_type& x1,
        const value_type& x2,
        const value_type& x3)
{
  // Preconditions:

  // Body:

  put_components(x0, x1, x2, x3);

  // Postconditions:

   ensure(invariant());
   ensure(isunordered_or_equals(component(0), x0)); 
   ensure(isunordered_or_equals(component(1), x1));
   ensure(isunordered_or_equals(component(2), x2));
   ensure(isunordered_or_equals(component(3), x3));

  // Exit:
}

fiber_bundle::e4_lite::
operator e4_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

fiber_bundle::e4_lite::
operator const e4_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::e4_lite::
put_components(const value_type& x0,
               const value_type& x1,
               const value_type& x2,
               const value_type& x3)
{
  // Preconditions:

  // Body:

  put_component(0, x0);
  put_component(1, x1);
  put_component(2, x2);
  put_component(3, x3);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), x0));
  ensure(isunordered_or_equals(component(1), x1));
  ensure(isunordered_or_equals(component(2), x2));
  ensure(isunordered_or_equals(component(3), x3));


  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::e4_lite::
dd() const
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

bool
fiber_bundle::e4_lite::
operator==(const e4_lite& xother) const
{
  // cout << endl << "Entering e4_lite::operator==." << endl;

  // Preconditions:
  
  // Body:

  bool result = 
    (_row_dofs.components[0] == xother._row_dofs.components[0]) &&
    (_row_dofs.components[1] == xother._row_dofs.components[1]) &&
    (_row_dofs.components[2] == xother._row_dofs.components[2]) &&
    (_row_dofs.components[3] == xother._row_dofs.components[3]);

  // Postconditions:


  // Exit:

  // cout << "Leaving e4_lite::operator==." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::e4_lite::
static_tp_prototype(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp <= 1));

  // Body:

  switch(xp)
  {
    case 0:
      {
        static const at0_lite lat0_lite;
        return lat0_lite;
      }
    case 1:
      {
        static const e4_lite le4_lite;
        return le4_lite;
      }
    default:
      {
        // Can't get here because of the precondition.
        static const tp_lite ltp_lite;
        return ltp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::tp_lite&
fiber_bundle::e4_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::e4_lite::
static_atp_prototype(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp <= 1));

  // Body:

  switch(xp)
  {
    case 0:
      {
        static const at0_lite lat0_lite;
        return lat0_lite;
      }
    case 1:
      {
        static const e4_lite le4_lite;
        return le4_lite;
      }
    default:
      {
        // Can't get here because of the precondition.
        static const atp_lite latp_lite;
        return latp_lite;
      }
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::atp_lite&
fiber_bundle::e4_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::e4_lite::
static_stp_prototype(int xp)
{
  // Preconditions:

  require((2 <= xp) && (xp <= 4));

  // Body:

  static const stp_lite lstp_lite;
  return lstp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::stp_lite&
fiber_bundle::e4_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::e4_lite::
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
fiber_bundle::e4_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e4_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e4_lite*
fiber_bundle::e4_lite::
clone() const
{
  e4_lite* result = 0;

  // Preconditions:

  // Body:

  result = new e4_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E4_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e4_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const e4_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::e4_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::e4_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::e4_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS E4
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS E4
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::e4::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "e4_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::e4::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "x DOUBLE false ";
  lmember_names       += "y DOUBLE false ";
  lmember_names       += "z DOUBLE false";
  lmember_names       += "t DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::e4::host_type&
fiber_bundle::e4::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xscalar_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering e4::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 4);
  
  require(xns.path_is_auto_read_accessible(xscalar_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xscalar_space_path, xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xscalar_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 4);
  ensure(result.d(true) == 4);
  ensure(result.scalar_space_path(true) == xscalar_space_path );
  ensure(result.p(true) == 1);
  ensure(result.dd(true) == 4);
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving e4::new_host." << endl;
  return result;
}

fiber_bundle::e4::host_type&
fiber_bundle::e4::
standard_host(namespace_type& xns, const std::string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering e4::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<e4>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<scalar_type>(xsuffix), xauto_access));

  // Body:

  // Create the scalar space if necessary.

  poset_path lscalar_space_path = scalar_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<e4>(xsuffix));

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, lpath, standard_schema_path(), lscalar_space_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<e4>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 4);
  ensure(result.d(true) == 4);
  ensure(result.scalar_space_path(true) == 
         standard_host_path<scalar_type>(xsuffix) );
  ensure(result.p(true) == 1);
  ensure(result.dd(true) == 4);
  ensure(result.vector_space_path(true) == result.path(true) );

  // Exit:

  // cout << "Leaving e4::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN VECTOR ALGEBRA (E4) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::e4::
e4()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::e4::
e4(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::e4::
e4(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::e4::
e4(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::e4::
e4(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

  // Exit:

}

fiber_bundle::e4::
e4(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::e4::
e4(poset_state_handle& xhost,
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

fiber_bundle::e4&
fiber_bundle::e4::
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
fiber_bundle::e4&
fiber_bundle::e4::
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
fiber_bundle::e4&
fiber_bundle::e4::
operator=(const e4& xother)
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

fiber_bundle::e4::
~e4()
{
  // Preconditions:

  // Body:

  // Postconditions:
}

const fiber_bundle::e4::volatile_type&
fiber_bundle::e4::
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
fiber_bundle::e4::volatile_type*
fiber_bundle::e4::
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
// EUCLIDEAN VECTOR ALGEBRA (ED) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (AT1) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::e4::
put_components(dof_type x0, dof_type x1, dof_type x2, dof_type x3)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, x0);
  put_component(1, x1);
  put_component(2, x2);
  put_component(3, x3);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), x0));
  ensure(isunordered_or_equals(component(1), x1));
  ensure(isunordered_or_equals(component(2), x2));
  ensure(isunordered_or_equals(component(3), x3));

  // Exit:

  return;
}

fiber_bundle::e4::
operator e4::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::e4::
operator const e4::row_dofs_type& () const
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
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tp*
fiber_bundle::e4::
new_tp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((0 <= xp) && (xp <= 1));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	tp_space& lhost = lns->member_poset<tp_space>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e4");
	tp_space& lhost = lns->member_poset<tp_space>(lname, false);
        e4* result = new e4(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:

}


fiber_bundle::atp*
fiber_bundle::e4::
new_atp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require((0 <= xp) && (xp <= 1));

  // Body:

  namespace_poset* lns = xvector_space.name_space();
  const string& lvector_space_name = xvector_space.name();

  switch(xp)
  {
    case 0:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "at0");
	tp_space& lhost = lns->member_poset<tp_space>(lname, false);
        at0* result = new at0(&lhost);
        return result;
      }

    case 1:
      {
        const string lname =
          create_tensor_space_name(lvector_space_name, "e4");
	tp_space& lhost = lns->member_poset<tp_space>(lname, false);
        e4* result = new e4(&lhost);
        return result;
      }

    default:
      // Can't get here because of the precondition.
      return 0;
  }

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}


fiber_bundle::stp*
fiber_bundle::e4::
new_stp(tp_space& xvector_space, int xp)
{
  // Preconditions:

  require(xvector_space.state_is_read_accessible());
  require( xp == 0 );

  // Body:

  return 0;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:

}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

fiber_bundle::tp*
fiber_bundle::e4::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e4::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e4::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e4::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::e4::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e4::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e4::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e4::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::e4::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e4::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e4::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e4::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::e4::
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
fiber_bundle::e4::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("e4");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::e4*
fiber_bundle::e4::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  e4* result = new e4();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS E4
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::e4::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const e4*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::e4::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(ed::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance((is_attached() ? d() == 4 : true));

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


