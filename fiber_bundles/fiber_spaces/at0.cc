

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class at0.

#include "at0.impl.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "stp.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS AT0_LITE
//==============================================================================


//==============================================================================
// AT0 FACET OF CLASS AT0_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at0_lite::
at0_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at0_lite::
at0_lite(const at0_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at0_lite&
fiber_bundle::at0_lite::
operator=(const at0_lite& xother)
{

  // Preconditions:

  // Body:

  if(this != &xother)
  {
    put_component(0, xother[0]);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::at0_lite::
~at0_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::at0_lite::
at0_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::at0_lite&
fiber_bundle::at0_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  put_component(xrow_dofs.components[0]);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;

}

fiber_bundle::at0_lite::
at0_lite(const value_type& x0)
{
  // Preconditions:

  // Body:

  put_component(x0);

  // Postconditions:

  ensure(invariant());

  // Exit:
}


fiber_bundle::at0_lite&
fiber_bundle::at0_lite::
operator=(const value_type& xcomp)
{
  // Preconditions:

  // Body:

  put_component(xcomp);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

bool
fiber_bundle::at0_lite::
operator==(const vd_value_type& xother) const
{
  // Preconditions:

  // Body:

  bool result = (component() == xother); 

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;  
}

fiber_bundle::at0_lite::
operator at0_lite::value_type ()
{
  // Preconditions:

  // Body:

  value_type result = component();

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at0_lite::
operator at0_lite::value_type () const
{
  // Preconditions:

  // Body:

  const value_type result = component();

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at0_lite::
operator at0_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at0_lite::
operator const at0_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at0_lite::
put_component(value_type xcomp)
{
  // Preconditions:

  // Body:

  put_component(0, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(0), xcomp));

  // Exit:
}

fiber_bundle::at0_lite::value_type
fiber_bundle::at0_lite::
component() const
{
  // Preconditions:

  // Body:

  value_type result = sheaf::row_dofs(*this)[0];

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
const fiber_bundle::tp_lite&
fiber_bundle::at0_lite::
static_tp_prototype(int xp)
{
  // Preconditions:

  require(0 <= xp);

  // Body:

    static const tp_lite ltp_lite;
    return ltp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

///
const fiber_bundle::tp_lite& 
fiber_bundle::at0_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  // Body:
  // Preconditions:

  require(precondition_of(static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

///
const fiber_bundle::atp_lite&
fiber_bundle::at0_lite::
static_atp_prototype(int xp)
{
  // Preconditions:

  require(0 <= xp);

  // Body:

  static const atp_lite latp_lite;
  return latp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

///
const fiber_bundle::atp_lite&
fiber_bundle::at0_lite::
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

///
const fiber_bundle::stp_lite&
fiber_bundle::at0_lite::
static_stp_prototype(int xp)
{
  // Preconditions:

  require(0 <= xp);

  // Body:

  static const stp_lite lstp_lite;
  return lstp_lite;

  // Postconditions:

  ensure(unexecutable("result.p() == xp"));

  // Exit:
}

const fiber_bundle::stp_lite&
fiber_bundle::at0_lite::
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
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT0_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at0_lite::
p() const
{
  // Preconditions:

  // Body:

  int result = 0;

  // Postconditions:

  ensure(invariant());
  ensure(result == 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS AT0_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at0_lite::
dd() const
{
  // Preconditions:

  // Body:

  int result = 1;

  // Postconditions:

  ensure(invariant());
  ensure(result == 1);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//===========================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS AT0_LITE
//===========================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//===========================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT0_LITE
//===========================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT0_LITE
//============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at0_lite::
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
fiber_bundle::at0_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at0_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::at0_lite*
fiber_bundle::at0_lite::
clone() const
{
  at0_lite* result = 0;

  // Preconditions:

  // Body:

  result = new at0_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT0_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at0_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const at0_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::at0_lite::
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

void*
fiber_bundle::at0_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::at0_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS AT0
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS AT0
// ===========================================================

// PUBLIC MEMBER FUNCTIONS


const sheaf::poset_path&
fiber_bundle::at0::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "at0_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::at0::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));


  // Body:

  string lmember_names = "value DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              atp::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}


void
fiber_bundle::at0::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering at0::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 1);

  // Body:

  host_type::new_table(xns, xhost_path, xschema_path, xauto_access);

  // Postconditions:

  ensure(xns.contains_path(xhost_path, xauto_access));
  ensure(xns.member_poset(xhost_path, xauto_access).state_is_not_read_accessible());
  ensure(xns.member_poset(xhost_path, xauto_access).schema(true).path(true) == xschema_path);

  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).factor_ct(true) == 1);
  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).d(true) == 1);
  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).p(true) == 0);
  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).vector_space_path(true) == xhost_path );
  ensure(xns.member_poset<host_type>(xhost_path, xauto_access).scalar_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving at0::new_host." << endl;
  return;
}

sheaf::poset_path
fiber_bundle::at0::
new_host(namespace_type& xns, const string& xsuffix, bool xauto_access)
{
  // cout << endl << "Entering at0::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xsuffix.empty() || poset_path::is_valid_name(xsuffix));
  require(!xns.contains_path(standard_host_path(static_class_name(), xsuffix), xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));

  // Body:

  poset_path result(standard_host_path(static_class_name(), xsuffix));

  host_type::new_table(xns, result, standard_schema_path(), xauto_access);

  // Postconditions:

  ensure(result == standard_host_path(static_class_name(), xsuffix));
  ensure(xns.contains_path(result, xauto_access));
  ensure(xns.member_poset(result, xauto_access).state_is_not_read_accessible());
  ensure(xns.member_poset(result, xauto_access).schema(true).path(true) == standard_schema_path());

  ensure(xns.member_poset<host_type>(result, xauto_access).factor_ct(true) == 1);
  ensure(xns.member_poset<host_type>(result, xauto_access).d(true) == 1);
  ensure(xns.member_poset<host_type>(result, xauto_access).p(true) == 0);
  ensure(xns.member_poset<host_type>(result, xauto_access).vector_space_path(true) == result );
  ensure(xns.member_poset<host_type>(result, xauto_access).scalar_space_path(true) == result );

  // Exit:

  // cout << "Leaving at0::new_host." << endl;
  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// AT0 FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at0::
at0()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::at0::
at0(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::at0::
at0(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::at0::
at0(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::at0::
at0(abstract_poset_member* xother)
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

fiber_bundle::at0::
at0(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::at0::
at0(poset_state_handle& xhost,
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

fiber_bundle::at0&
fiber_bundle::at0::
operator=(const row_dofs_type& xrdt)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xrdt.components[0]);

  // Postconditions:

  ensure(isunordered_or_equals(component(0), xrdt.components[0]));

  // Exit:

  return *this;

}

///
fiber_bundle::at0&
fiber_bundle::at0::
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
fiber_bundle::at0&
fiber_bundle::at0::
operator=(const at0& xother)
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

fiber_bundle::at0::
~at0()
{

  // Preconditions:

  // Body:

  // Postconditions:
}

const fiber_bundle::at0::volatile_type&
fiber_bundle::at0::
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
fiber_bundle::at0::volatile_type*
fiber_bundle::at0::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


fiber_bundle::at0::value_type
fiber_bundle::at0::
value() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  value_type result = component(0);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::at0::
put_value(value_type xvalue)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  put_component(0, xvalue);

  // Postconditions:

  ensure(value() == xvalue);
  ensure(invariant());
}

fiber_bundle::at0::
operator at0::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::at0::
operator const at0::row_dofs_type& () const
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
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::at0::
factor_ct() const
{
  // Preconditions:

  // Body:

  int result = 1;

  // Postconditions:

  ensure(invariant());
  ensure(result == 1);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::at0::
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
fiber_bundle::at0::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("at0");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::at0::host_type*
fiber_bundle::at0::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::at0::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS AT0
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::at0::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const at0*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());
  //ensure(xother->invariant());

  // Exit:

  return result;

}

fiber_bundle::at0*
fiber_bundle::at0::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  at0* result = new at0();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::at0::
invariant() const
{
  bool result = true;

  // Body:

  // Must satisfy base class invariant.

  invariance(atp::invariant());

  /// @hack Guard invariants on p, d, dof_ct
  ///       until poset member restriction implemented.

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance((is_attached() ? p() == 0 : true));
    invariance((is_attached() ? d() == 1 : true));
    invariance((is_attached() ? dof_ct() == 1 : true));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

