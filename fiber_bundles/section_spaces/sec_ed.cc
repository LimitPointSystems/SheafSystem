
// $RCSfile: sec_ed.cc,v $ $Revision: 1.29 $ $Date: 2013/03/13 00:58:50 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_ed.

#include "sec_ed.h"

#include "assert_contract.h"
#include "namespace_poset.h"

#include "sec_at0.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_ED
//==============================================================================

//==============================================================================
// ED FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_ed::
sec_ed()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_ed::
sec_ed(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_ed::
sec_ed(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_ed::
sec_ed(const sec_rep_space* xhost, const string& xname)
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

fiber_bundle::sec_ed::
sec_ed(const namespace_poset* xnamespace,
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


fiber_bundle::sec_ed::
sec_ed(const sec_rep_space_member* xother)
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

fiber_bundle::sec_ed::
sec_ed(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_ed::
sec_ed(sec_rep_space* xhost,
       abstract_poset_member& xbase_mbr,
       int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(\
    new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::sec_ed&
fiber_bundle::sec_ed::
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

fiber_bundle::sec_ed&
fiber_bundle::sec_ed::
operator=(const sec_ed& xother)
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

fiber_bundle::sec_ed&
fiber_bundle::sec_ed::
operator=(const ed& xfiber)
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

fiber_bundle::sec_ed&
fiber_bundle::sec_ed::
operator=(const ed_lite& xfiber)
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

fiber_bundle::sec_ed::
~sec_ed()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_ed::fiber_type&
fiber_bundle::sec_ed::
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
// AT1 FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ATP FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_ed::
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
fiber_bundle::sec_ed::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_ed");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_ed*
fiber_bundle::sec_ed::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  sec_ed* result = new sec_ed();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_ED
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_ed::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const ed*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_ed::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_ed*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_ed::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_at1::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

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

namespace
{
using namespace fiber_bundle::ed_algebra;

class dot_functor
{
public:
  void operator()(const ed_lite& xl0, const ed_lite& xl1,
                  at0_lite& xlresult) const
  {
    xlresult = dot(xl0, xl1);
  }
};

class length_functor
{
public:
  void operator()(const ed_lite& x0, at0_lite& xresult)
  {
    xresult = length(x0);
  }
};

class put_length_functor
{
public:
  void operator()(ed_lite& x0, const vd_value_type& xlength)
  {
    put_length(x0, xlength);
  }

  void operator()(ed_lite& x0, const at0_lite& xlength)
  {
    put_length(x0, xlength);
  }
};

class normalize_functor
{
public:
  void operator()(const ed_lite& x0, ed_lite& xresult)
  {
    normalize(x0, xresult);
  }
};

} //end unnamed namespace 

//==============================================================================
//==============================================================================

#include "sec_vd.impl.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_ed_algebra::
dot(const sec_ed& x0, const sec_ed& x1, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.is_same_type(&x1));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, dot_functor(), xauto_access);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sec_ed_algebra::
length(const sec_ed& x0, sec_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, length_functor(), xauto_access);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sec_ed_algebra::
put_length(sec_ed& x0, const vd_value_type& xlength, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xlength >= 0.0);

  // Body:

  unary_op(x0, xlength, put_length_functor(), xauto_access);

  // Postconditions:

  ensure(unexecutable("length(x0, xauto_access) == xlength"));

  // Exit:

  return;
}

/// @todo: Implement. Need a new unary_op?
// void
// fiber_bundle::
// put_length(sec_ed& x0, const sec_at0& xlength, bool xauto_access)
// {
//   // Preconditions:

//   require(x0.state_is_auto_read_accessible(xauto_access));
//   require(xlength >= 0.0);

//   // Body:

//   unary_op(x0, xlength, put_length_functor(), xauto_access);

//   // Postconditions:

//   ensure(unexecutable("length(x0, xauto_access) == xlength"));

//   // Exit:

//   return;
// }

void
fiber_bundle::sec_ed_algebra::
normalize(const sec_ed& x0, sec_ed& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.is_same_type(&xresult));
  require(x0.is_p_form(xauto_access) == xresult.is_p_form(xauto_access));

  // Body:

  unary_op(x0, xresult, normalize_functor(), xauto_access);

  // Postconditions:

  ensure(xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access));
  ensure(unexecutable("length(xresult, xauto_access) == 1.0"));

  // Exit:

  return;
}

void
fiber_bundle::sec_ed_algebra::
normalize(sec_ed& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(normalize(x0, x0, xauto_access)));

  // Body:

  normalize(x0, x0, xauto_access);

  // Postconditions:

  ensure(postcondition_of(normalize(x0, x0, xauto_access)));

  // Exit:
}


