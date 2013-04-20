


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_st4_e2.

#include "sec_st4_e2.h"

#include "assert_contract.h"
#include "namespace_poset.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_ST4_E2
//==============================================================================

//==============================================================================
// ST4_E2 FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_st4_e2::
sec_st4_e2()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_st4_e2::
sec_st4_e2(const sec_rep_space* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_st4_e2::
sec_st4_e2(const sec_rep_space* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_st4_e2::
sec_st4_e2(const sec_rep_space* xhost, const string& xname)
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
  //ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
  ensure(!is_restricted());

}


fiber_bundle::sec_st4_e2::
sec_st4_e2(const namespace_poset* xnamespace,
           const poset_path& xpath,
           bool xauto_access)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}


fiber_bundle::sec_st4_e2::
sec_st4_e2(const sec_rep_space_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(is_same_restriction(xother));

}

fiber_bundle::sec_st4_e2::
sec_st4_e2(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Body:

  new_jim_state(xhost, xdof_map, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_st4_e2::
sec_st4_e2(sec_rep_space* xhost,
           abstract_poset_member& xbase_mbr,
           int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_st4_e2&
fiber_bundle::sec_st4_e2::
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

fiber_bundle::sec_st4_e2&
fiber_bundle::sec_st4_e2::
operator=(const sec_st4_e2& xother)
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

fiber_bundle::sec_st4_e2&
fiber_bundle::sec_st4_e2::
operator=(const st4_e2& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_st4_e2&
fiber_bundle::sec_st4_e2::
operator=(const st4_e2_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_st4_e2::
~sec_st4_e2()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_st4_e2::fiber_type&
fiber_bundle::sec_st4_e2::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST4 FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_st4_e2::
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
fiber_bundle::sec_st4_e2::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_st4_e2");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_st4_e2*
fiber_bundle::sec_st4_e2::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_st4_e2 *result = new sec_st4_e2();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_ST4_E2
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_st4_e2::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const st4_e2*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_st4_e2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_st4_e2*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_st4_e2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_st4::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(is_attached() ? dd() == 2 : true);

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


