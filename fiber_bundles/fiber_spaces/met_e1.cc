

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class met_e1.

#include "met_e1.impl.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS MET_E1_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN METRIC 1D (MET_E1) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e1_lite::
met_e1_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e1_lite::
met_e1_lite(const met_e1_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_e1_lite&
fiber_bundle::met_e1_lite::
operator=(const met_e1_lite& xother)
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

fiber_bundle::met_e1_lite::
~met_e1_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::met_e1_lite::
met_e1_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  // Exit:
}

fiber_bundle::met_e1_lite&
fiber_bundle::met_e1_lite::
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

fiber_bundle::met_e1_lite::
operator met_e1_lite::row_dofs_type& ()
{
  // Preconditions:

  // Body:

  row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e1_lite::
operator const met_e1_lite::row_dofs_type& () const
{
  // Preconditions:

  // Body:

  const row_dofs_type& result = _row_dofs;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e1_lite::
met_e1_lite(const value_type& xx)
{
  // Preconditions:

  // Body:

  put_component(xx);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(), xx));

  // Exit:
}

fiber_bundle::met_e1_lite::value_type
fiber_bundle::met_e1_lite::
component() const
{
  // Preconditions:

  // Body:

  value_type result = component(0);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

void
fiber_bundle::met_e1_lite::
put_component(const value_type& xcomp)
{
  // Preconditions:

  // Body:

  put_component(0, xcomp);

  // Postconditions:

  ensure(invariant());
  ensure(isunordered_or_equals(component(), xcomp));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// EUCLIDEAN METRIC (MET_ED) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// METRIC TENSOR (MET) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const fiber_bundle::tp_lite&
fiber_bundle::met_e1_lite::
tp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e1_lite::static_tp_prototype(xp)));
  
  // Body:

  const tp_lite& result = e1_lite::static_tp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e1_lite::static_tp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::atp_lite&
fiber_bundle::met_e1_lite::
atp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e1_lite::static_atp_prototype(xp)));
  
  // Body:

  const atp_lite& result = e1_lite::static_atp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e1_lite::static_atp_prototype(xp)));
  
  // Exit:

  return result;
}

const fiber_bundle::stp_lite&
fiber_bundle::met_e1_lite::
stp_prototype(int xp) const
{
  // Preconditions:

  require(precondition_of(e1_lite::static_stp_prototype(xp)));
  
  // Body:

  const stp_lite& result = e1_lite::static_stp_prototype(xp);

  // Postconditions:

  ensure(postcondition_of(e1_lite::static_stp_prototype(xp)));
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::met_e1_lite::
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


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e1_lite::
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
fiber_bundle::met_e1_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e1_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e1_lite*
fiber_bundle::met_e1_lite::
clone() const
{
  met_e1_lite* result = 0;

  // Preconditions:

  // Body:

  result = new met_e1_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E1_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e1_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const met_e1_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::met_e1_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(met_ed_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

void*
fiber_bundle::met_e1_lite::
row_dofs()
{
  return &_row_dofs;
}

const void*
fiber_bundle::met_e1_lite::
row_dofs() const
{
  return &_row_dofs;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS MET_E1
//==============================================================================

//==============================================================================
// MET_E1 FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_e1::
met_e1()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::met_e1::
met_e1(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::met_e1::
met_e1(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::met_e1::
met_e1(const poset_state_handle* xhost, const string& xname)
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

fiber_bundle::met_e1::
met_e1(abstract_poset_member* xother)
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

fiber_bundle::met_e1::
met_e1(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::met_e1::
met_e1(poset_state_handle& xhost,
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

fiber_bundle::met_e1&
fiber_bundle::met_e1::
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
fiber_bundle::met_e1&
fiber_bundle::met_e1::
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
fiber_bundle::met_e1&
fiber_bundle::met_e1::
operator=(const met_e1& xother)
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

fiber_bundle::met_e1::
~met_e1()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::met_e1::volatile_type&
fiber_bundle::met_e1::
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
fiber_bundle::met_e1::volatile_type*
fiber_bundle::met_e1::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e1::
operator met_e1::row_dofs_type& ()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  row_dofs_type& result = sheaf::row_dofs(*this);

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::met_e1::
operator const met_e1::row_dofs_type& () const
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
// MET_ED FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::met_e1::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "met_e1_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::met_e1::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  //  string lmember_names = "met_e1_xx_component DOUBLE false";
  string lmember_names = "xx DOUBLE false";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              met_ed::standard_schema_path(),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tp*
fiber_bundle::met_e1::
new_tp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e1::new_tp(vector_space(xauto_access), xp)));

  // Body:

  tp* result = e1::new_tp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e1::new_tp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::atp*
fiber_bundle::met_e1::
new_atp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e1::new_atp(vector_space(xauto_access), xp)));

  // Body:

  atp* result = e1::new_atp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e1::new_atp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

fiber_bundle::stp*
fiber_bundle::met_e1::
new_stp(int xp, bool xauto_access) const
{
  // Preconditions:

  require(precondition_of(e1::new_stp(vector_space(xauto_access), xp)));

  // Body:

  stp* result = e1::new_stp(vector_space(xauto_access), xp);

  // Postconditions:

  ensure(postcondition_of(e1::new_stp(vector_space(xauto_access), xp)));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::met_e1::
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
fiber_bundle::met_e1::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_e1");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_e1*
fiber_bundle::met_e1::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class..

  met_e1* result = new met_e1();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS MET_E1
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_e1::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const met_e1*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::met_e1::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(met_ed::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

    invariance(is_attached() ? (d() == 1) : true);

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
// MET FACET:
//==============================================================================

void
fiber_bundle::met_algebra::
raise(const met_e1_lite& xmetric, const e1_lite& xcovector, e1_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_contravariant())"));
  require(unexecutable("xcovector.is_covariant())"));   //  is_dual;

  // Body:
 
  // Left matrix multiply xcovector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e1_lite::value_type value_type;

  value_type m00 = xmetric.component(0);

  value_type comp0 = xcovector.component(0);

  value_type result_comp = m00*comp0;
  xresult.put_component(0, result_comp);

  // Postconditions:

  //ensure(unexecutable(""));
  ensure(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Exit:

}

fiber_bundle::e1_lite*
fiber_bundle::met_algebra::
raise(const met_e1_lite& xmetric, const e1_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(raise(xmetric, xcovector, *result)));

  // Body:

  e1_lite* result = new e1_lite();

  raise(xmetric, xcovector, *result);
  
  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(raise(xmetric, xcovector, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::met_algebra::
lower(const met_e1_lite& xmetric, const e1_lite& xvector, e1_lite& xresult)
{
  // Preconditions:

  require(unexecutable("xmetric.is_covariant())"));
  require(unexecutable("xcovector.is_contravariant())")); // !is_dual

  // Body:

  // Right matrix multiply xvector with xmetric.

  //
  // This class is a 2x2 matrix and we may therefore make optimizations
  // in light of this fact.

  typedef met_e1_lite::value_type value_type;

  value_type m00 = xmetric.component(0);

  value_type comp0 = xvector.component(0);

  value_type result_comp = m00*comp0;
  xresult.put_component(0, result_comp);

  // Postconditions:

  //ensure(unexecutable(""));
  ensure(unexecutable("xresult.is_covariant())"));       //  is_dual

  // Exit:
}

fiber_bundle::e1_lite*
fiber_bundle::met_algebra::
lower(const met_e1_lite& xmetric, const e1_lite& xvector)
{
  // Preconditions:

  require(precondition_of(lower(xmetric, xvector, *result)));

  // Body:

  e1_lite* result = new e1_lite();

  lower(xmetric, xvector, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(lower(xmetric, xvector, *result)));

  // Exit:

  return result;
}

void
fiber_bundle::met_algebra::
raise(const met_e1& xmetric, const e1& xcovector, e1& xresult, bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_contravariant(0, xauto_access));
  require(xcovector.is_covariant(0, xauto_access));   //  is_dual;

  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xcovector.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Left matrix multiply xcovector with xmetric.


  typedef met_e1::value_type value_type;

  value_type m00 = xmetric.component(0);

  value_type comp0 = xcovector.component(0);

  value_type result_comp = m00*comp0;
  xresult.put_component(0, result_comp);

  // Make sure the result is contravariant/p_vector.

  if(!xresult.is_p_vector(false))
  {
    xresult.put_is_p_vector(false);
  }


  if(xauto_access)
  {
    xmetric.release_access();
    xcovector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

}

void
fiber_bundle::met_algebra::
lower(const met_e1& xmetric, const e1& xvector, e1& xresult, bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xmetric.is_covariant(0, xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual;

  // Body:

  if(xauto_access)
  {
    xmetric.get_read_access();
    xvector.get_read_access();
    xresult.get_read_write_access(true);
  }

  // Right matrix multiply xvector with xmetric.

  typedef met_e1::value_type value_type;

  value_type m00 = xmetric.component(0);

  value_type comp0 = xvector.component(0);

  value_type result_comp = m00*comp0;
  xresult.put_component(0, result_comp);

  // Make sure the result is covariant/p_form.

  if(!xresult.is_p_form(false))
  {
    xresult.put_is_p_form(false);
  }

  if(xauto_access)
  {
    xmetric.release_access();
    xvector.release_access();
    xresult.release_access();
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));     //  is_dual

  // Exit:

}

//==============================================================================
// TEMPLATE SPECIALIZATIONS
//==============================================================================

