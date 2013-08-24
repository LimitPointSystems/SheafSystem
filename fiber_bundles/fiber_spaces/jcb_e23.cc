

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class jcb_e23.

#include "jcb_e23.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at1_space.h"
#include "e2.h"
#include "e3.h"
#include "jcb_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "st2_e2.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS JCB_E23_LITE
//==============================================================================


//============================================================================
// JCB_E23 FACET OF CLASS JCB_E23_LITE
//============================================================================

fiber_bundle::jcb_e23_lite::
jcb_e23_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_e23_lite::
jcb_e23_lite(const jcb_e23_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_e23_lite&
fiber_bundle::jcb_e23_lite::
operator=(const jcb_e23_lite& xother)
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

fiber_bundle::jcb_e23_lite::
~jcb_e23_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::jcb_e23_lite::
jcb_e23_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_e23_lite::
jcb_e23_lite(const matrix_type& xmatrix)
{
  // Preconditions:

  // Body:

  *this = xmatrix;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_e23_lite&
fiber_bundle::jcb_e23_lite::
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

fiber_bundle::jcb_e23_lite& 
fiber_bundle::jcb_e23_lite::
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

fiber_bundle::jcb_e23_lite::
operator jcb_e23_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::jcb_e23_lite::
operator const jcb_e23_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::jcb_e23_lite::
operator jcb_e23_lite::matrix_type& ()
{
  // Preconditions:

  // Body:

  matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;

}

fiber_bundle::jcb_e23_lite::
operator const jcb_e23_lite::matrix_type& () const
{
  // Preconditions:

  // Body:

  const matrix_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::jcb_e23_lite::
jcb_e23_lite(const value_type& dxdu, const value_type& dxdv,
             const value_type& dydu, const value_type& dydv,
             const value_type& dzdu, const value_type& dzdv)
{
  // Preconditions:

  // Body:

  put_components(dxdu, dxdv, dydu, dydv, dzdu, dzdv);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), dxdu));
  ensure(isunordered_or_equals(component(1), dxdv));
  ensure(isunordered_or_equals(component(2), dydu));
  ensure(isunordered_or_equals(component(3), dydv));
  ensure(isunordered_or_equals(component(4), dzdu));
  ensure(isunordered_or_equals(component(5), dzdv));

  // Exit:
}

void
fiber_bundle::jcb_e23_lite::
put_components(const value_type& dxdu, const value_type& dxdv,
               const value_type& dydu, const value_type& dydv,
               const value_type& dzdu, const value_type& dzdv)
{
  // Preconditions:

  // Body:

  put_component(0, dxdu);
  put_component(1, dxdv);
  put_component(2, dydu);
  put_component(3, dydv);
  put_component(4, dzdu);
  put_component(5, dzdv);

  // Postconditions:

  ensure(invariant());

  ensure(isunordered_or_equals(component(0), dxdu));
  ensure(isunordered_or_equals(component(1), dxdv));
  ensure(isunordered_or_equals(component(2), dydu));
  ensure(isunordered_or_equals(component(3), dydv));
  ensure(isunordered_or_equals(component(4), dzdu));
  ensure(isunordered_or_equals(component(5), dzdv));

  // Exit:
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// JCB_ED FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// JACOBIAN (JCB) FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::jcb_e23_lite::
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

int
fiber_bundle::jcb_e23_lite::
dr() const
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


//============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::jcb_e23_lite::
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
fiber_bundle::jcb_e23_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("jcb_e23_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::jcb_e23_lite*
fiber_bundle::jcb_e23_lite::
clone() const
{
  jcb_e23_lite* result = 0;

  // Preconditions:

  // Body:

  result = new jcb_e23_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ANY FACET OF CLASS JCB_E23_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::jcb_e23_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const jcb_e23_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::jcb_e23_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(jcb_ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::jcb_e23_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::jcb_e23_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS JCB_E23
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::jcb_e23::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "jcb_e23_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::jcb_e23::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  string lmember_names = "dxdu DOUBLE false ";
  lmember_names       += "dxdv DOUBLE false ";
  lmember_names       += "dydu DOUBLE false ";
  lmember_names       += "dydv DOUBLE false ";
  lmember_names       += "dzdu DOUBLE false ";
  lmember_names       += "dzdv DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              jcb_ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::jcb_e23::host_type&
fiber_bundle::jcb_e23::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
	 const poset_path& xdomain_path,
	 const poset_path& xrange_path,
         bool xauto_access)
{
  // cout << endl << "Entering jcb_e23::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 6);

  require(xns.path_is_auto_read_accessible(xdomain_path, xauto_access));
  require(xns.contains_poset<domain_type::host_type>(xdomain_path, xauto_access));
  require(xns.member_poset(xdomain_path, xauto_access).schema(xauto_access).conforms_to(domain_type::standard_schema_path()));
  require(xns.member_poset<domain_type::host_type>(xdomain_path, xauto_access).d(xauto_access) == 2);

  require(xns.path_is_auto_read_accessible(xrange_path, xauto_access));
  require(xns.contains_poset<range_type::host_type>(xrange_path, xauto_access));
  require(xns.member_poset(xrange_path, xauto_access).schema(xauto_access).conforms_to(range_type::standard_schema_path()));
  require(xns.member_poset<range_type::host_type>(xrange_path, xauto_access).d(xauto_access) == 3);

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, xdomain_path, xrange_path, xauto_access));

  require(xns.member_poset<domain_type::host_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access) ==
	  xns.member_poset<range_type::host_type>(xrange_path, xauto_access).scalar_space_path(xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xdomain_path, xrange_path, xauto_access); 

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.dd(true) == 2);
  ensure(result.dr(true) == 3);
  ensure(result.domain_path(true) == xdomain_path);
  ensure(result.range_path(true) == xrange_path);

  ensure(result.scalar_space_path(true) ==
	 xns.member_poset<domain_type::host_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.scalar_space_path(true) ==
	 xns.member_poset<range_type::host_type>(xrange_path, xauto_access).scalar_space_path(xauto_access) );
  
  // Exit:

  // cout << "Leaving jcb_e23::new_host." << endl;
  return result;
}

fiber_bundle::jcb_e23::host_type&
fiber_bundle::jcb_e23::
standard_host(namespace_type& xns, const string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering jcb_e23::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(standard_host_is_available<jcb_e23>(xns, xsuffix, xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xns.path_is_auto_read_available(standard_host_path<domain_type>(xsuffix), xauto_access));
  require(xns.path_is_auto_read_available(standard_host_path<range_type>(xsuffix), xauto_access));

  // Body:

  // Create the domain space if necessary.

  poset_path ldomain_space_path = domain_type::standard_host(xns, xsuffix, xauto_access).path(true);

  // Create the range space if necessary.

  poset_path lrange_space_path = range_type::standard_host(xns, xsuffix, xauto_access).path(true);

  poset_path lpath(standard_host_path<jcb_e23>(xsuffix));

  host_type* result_ptr;
  if(xns.contains_path(lpath, xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(lpath, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, lpath, standard_schema_path(), ldomain_space_path, lrange_space_path, xauto_access);
  }

  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<jcb_e23>(xsuffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.factor_ct(true) == 6);
  ensure(result.d(true) == 6);
  ensure(result.dd(true) == 2);
  ensure(result.dr(true) == 3);
  ensure(result.domain_path(true) == standard_host_path<domain_type>(xsuffix));
  ensure(result.range_path(true) == standard_host_path<range_type>(xsuffix));

  ensure(result.scalar_space_path(true) == standard_host_path<domain_type::scalar_type>(xsuffix));
  ensure(result.scalar_space_path(true) == standard_host_path<domain_type::scalar_type>(xsuffix));

  // Exit:

  // cout << "Leaving jcb_e23::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//============================================================================
// JCB_E23 FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::jcb_e23::
jcb_e23()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::jcb_e23::
jcb_e23(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::jcb_e23::
jcb_e23(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::jcb_e23::
jcb_e23(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::jcb_e23::
jcb_e23(abstract_poset_member* xother)
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

fiber_bundle::jcb_e23::
jcb_e23(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::jcb_e23::
jcb_e23(poset_state_handle& xhost,
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

fiber_bundle::jcb_e23&
fiber_bundle::jcb_e23::
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
fiber_bundle::jcb_e23&
fiber_bundle::jcb_e23::
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
fiber_bundle::jcb_e23&
fiber_bundle::jcb_e23::
operator=(const jcb_e23& xother)
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

fiber_bundle::jcb_e23::
~jcb_e23()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::jcb_e23::volatile_type&
fiber_bundle::jcb_e23::
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
fiber_bundle::jcb_e23::volatile_type*
fiber_bundle::jcb_e23::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


//============================================================================
// ROW DOF RELATED MEMBER FUNCTIONS
//============================================================================

fiber_bundle::jcb_e23::
operator jcb_e23::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::jcb_e23::
operator const jcb_e23::row_dofs_type& () const
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


//============================================================================
// JCB_ED FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// JCB FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// VD FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// TUPLE FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::jcb_e23::
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
fiber_bundle::jcb_e23::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("jcb_e23");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::jcb_e23*
fiber_bundle::jcb_e23::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  jcb_e23* result = new jcb_e23();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ANY FACET OF CLASS JCB_E23
//============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::jcb_e23::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const jcb_e23*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::jcb_e23::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(jcb_ed::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(is_attached() ? (dr() == 3) : true);
    invariance(is_attached() ? (dd() == 2) : true);

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
fiber_bundle::jcb_algebra::
push(const jcb_e23& xjcb, const e2& xvector, e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xvector.d(xauto_access) == xjcb.dd(xauto_access));
  require(xresult.d(xauto_access) == xjcb.dr(xauto_access));

  ///@issue What do we want here?

  require(xvector.is_contravariant(0, xauto_access)); // !is_dual

  // Body:

  if(xauto_access)
  {
    xjcb.get_read_access();
    xvector.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Left matrix multiply vector with jacobian.

  int num_rows = xjcb.dr();
  int num_cols = xjcb.dd();

  for(int i=0; i<num_rows; ++i)
  {
    vd_value_type sumi = 0.0;
    for(int j=0; j<num_cols; ++j)
    {
      vd_value_type vj = xvector.component(j);
      vd_value_type cij = xjcb.component(i, j);
      sumi += cij*vj;
    }
    xresult.put_component(i, sumi);
  }
 
  // Make sure the result is contravariant/p_vector.

  xresult.put_is_p_vector(false);

  if(xauto_access)
  {
    xjcb.release_access();
    xvector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::jcb_algebra::
push(const jcb_e23_lite& xjcb, const e2_lite& xvector, e3_lite& xresult)
{
  // Preconditions:

  require(xvector.d() == xjcb.dd());
  require(xresult.d() == xjcb.dr());

  ///@issue What do we want here?

  require(unexecutable("xvector.is_contravariant())")); // !is_dual

  // Body:

  // Left matrix multiply vector with jacobian.

  int num_rows = xjcb.dr();
  int num_cols = xjcb.dd();

  for(int i=0; i<num_rows; ++i)
  {
    vd_value_type sumi = 0.0;
    for(int j=0; j<num_cols; ++j)
    {
      vd_value_type vj = xvector.component(j);
      vd_value_type cij = xjcb.component(i, j);
      sumi += cij*vj;
    }
    xresult.put_component(i, sumi);
  }    

  // Postconditions:

  ensure(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Exit:

  return;
}

///
fiber_bundle::e3_lite*
fiber_bundle::jcb_algebra::
push(const jcb_e23_lite& xjcb, const e2_lite& xvector)
{
  // Preconditions:

  require(precondition_of(push(xjcb, xvector, *result)));

  // Body:

  e3_lite* result = new e3_lite();

  push(xjcb, xvector, *result);

  // Postconditions:

  ensure(postcondition_of(push(xjcb, xvector, *result)));

  // Exit:

  return result;

}

///
void
fiber_bundle::jcb_algebra::
pull(const jcb_e23& xjcb, const e3& xcovector, e2& xresult, bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.d(xauto_access) == xjcb.dr(xauto_access));
  require(xresult.d(xauto_access) == xjcb.dd(xauto_access));

  ///@issue What do we want here?

  require(xcovector.is_covariant(0, xauto_access)); // is_dual

  // Body:

  if(xauto_access)
  {
    xjcb.get_read_access();
    xcovector.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Right matrix multiply covector with jacobian.

  int num_rows = xjcb.dd();
  int num_cols = xjcb.dr();

  for(int i=0; i<num_rows; ++i)
  {
    vd_value_type sumi = 0.0;
    for(int j=0; j<num_cols; ++j)
    {
      vd_value_type vj = xcovector.component(j);
      vd_value_type cji = xjcb.component(j, i);
      sumi += vj*cji;
    }
    xresult.put_component(i, sumi);
  }    

  // Make sure the result is covariant/p_form.

  xresult.put_is_p_form(false);

  if(xauto_access)
  {
    xjcb.release_access();
    xcovector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));   // is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::jcb_algebra::
pull(const jcb_e23_lite& xjcb, const e3_lite& xcovector, e2_lite& xresult)
{
  // Preconditions:

  require(xcovector.d() == xjcb.dr());
  require(xresult.d() == xjcb.dd());
  require(unexecutable("xcovector.is_covariant())")); // is_dual

  // Body:

  // Right matrix multiply covector with jacobian.

  int num_rows = xjcb.dd();
  int num_cols = xjcb.dr();

  for(int i=0; i<num_rows; ++i)
  {
    vd_value_type sumi = 0.0;
    for(int j=0; j<num_cols; ++j)
    {
      vd_value_type vj = xcovector.component(j);
      vd_value_type cji = xjcb.component(j, i);
      sumi += vj*cji;
    }
    xresult.put_component(i, sumi);
  }    

  // Postconditions:

  ensure(unexecutable("xresult.is_covariant())"));   // is_dual

  // Exit:

  return;
}

///
fiber_bundle::e2_lite*
fiber_bundle::jcb_algebra::
pull(const jcb_e23_lite& xjcb, const e3_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(pull(xjcb, xcovector, *result)));

  // Body:

  e2_lite* result = new e2_lite();

  pull(xjcb, xcovector, *result);

  // Postconditions:

  ensure(postcondition_of(pull(xjcb, xcovector, *result)));

  // Exit:

  return result;

}

//==============================================================================

//@todo Decide what to with the following functions.
 
///
void
fiber_bundle::jcb_algebra::
metric(const jcb_e23_lite& xjcb, st2_e2_lite& xresult)
{

  // Preconditions:

  // Body:

  xresult[0] = xjcb[0]*xjcb[0] + xjcb[2]*xjcb[2] + xjcb[4]*xjcb[4];
  xresult[1] = xjcb[0]*xjcb[1] + xjcb[2]*xjcb[3] + xjcb[4]*xjcb[5];
  xresult[2] = xjcb[1]*xjcb[1] + xjcb[3]*xjcb[3] + xjcb[5]*xjcb[5];

  // Postconditions:

  // Exit:
}

///
void
fiber_bundle::jcb_algebra::
symmetric_dot_push(const jcb_e23_lite& xjcb,
				 const jcb_e23_lite& xother_jcb,
				 st2_e2_lite&  xresult)
{
  // Preconditions:

  // Body:

  xresult[0] = xjcb[0]*xother_jcb[0]+xjcb[2]*xother_jcb[2]+xjcb[4]*xother_jcb[4];

  xresult[1] =
    (  xjcb[0]*xother_jcb[1] + xjcb[2]*xother_jcb[3] + xjcb[4]*xother_jcb[5]
     + xjcb[1]*xother_jcb[0] + xjcb[3]*xother_jcb[2] + xjcb[5]*xother_jcb[4] )/2;

  xresult[2] = xjcb[1]*xother_jcb[1]+xjcb[3]*xother_jcb[3]+xjcb[5]*xother_jcb[5];

  // Postconditions:

  // Exit:
}

