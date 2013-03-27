
// $RCSfile: field_met_ed.cc,v $ $Revision: 1.12 $ $Date: 2013/03/13 00:58:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class field_met_ed.
///
/// CAUTION: Normally this file should NOT be edited.  It is machine
///          generated.  If you need to make permanent changes,
///          edit the code template and rerun the generator instead.

#include "field_met_ed.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "sec_ed_invertible.h"
#include "sec_met_ed.h"

using namespace fields; // Workaround for MS C++ bug.

//=============================================================================
// FIELD_VD FACET OF CLASS FIELD_MET_ED
//=============================================================================

///
fields::field_met_ed::
field_met_ed()
  : field_met(new sec_met_ed, new sec_ed_invertible, new base_space_member)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

///
fields::field_met_ed::
field_met_ed(const field_met_ed& xother, bool xauto_access)
  : field_met(new sec_met_ed, new sec_ed_invertible, new base_space_member)
{
  // Preconditions:

  require(xauto_access || !xother.is_attached() || \
          xother.state_is_read_accessible());

  // Body:

  _coordinates->attach_to_state(xother._coordinates, xauto_access);
  _property->attach_to_state(xother._property, xauto_access);
  _base_space->attach_to_state(xother._base_space, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().is_same_state(&xother.coordinates()));
  ensure(property().is_same_state(&xother.property()));
  ensure(base_space().is_same_state(&xother.base_space()));

  // Exit:

  return;
}

///
fields::field_met_ed::
field_met_ed(const sec_ed& xcoordinates, const sec_met_ed& xproperty, bool xauto_access)
  : field_met(new sec_met_ed, new sec_ed_invertible, new base_space_member)
{
  // Preconditions:

  require(xcoordinates.is_attached());
  require(xproperty.is_attached());
  require(xauto_access || xcoordinates.state_is_read_accessible());
  require(xauto_access || xproperty.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xcoordinates.get_read_access();
    xproperty.get_read_access();
  }

  _coordinates->attach_to_state(&xcoordinates);
  _property->attach_to_state(&xproperty);
  _base_space->attach_to_state(&(xproperty.schema().base_space()));

  if(xauto_access)
  {
    xcoordinates.release_access();
    xproperty.release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().is_same_state(&xcoordinates));
  ensure(property().is_same_state(&xproperty));

  // Exit:

  return;
}

///
fields::field_met_ed::
field_met_ed(namespace_poset& xns,
         const poset_path& xcoordinates_path,
         const poset_path& xproperty_path,
         bool xauto_access)
  : field_met(new sec_met_ed, new sec_ed_invertible, new base_space_member)
{
  // Preconditions:

  require(xauto_access || xns.state_is_read_accessible());
  require(xns.contains_poset_member(xcoordinates_path));
  require(xauto_access ||
          xns.member_poset(xcoordinates_path).state_is_read_accessible());
  require(xns.contains_poset_member(xproperty_path));
  require(xauto_access ||
          xns.member_poset(xproperty_path).state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xns.get_read_access();
  }

  _coordinates->attach_to_state(&xns, xcoordinates_path, xauto_access);
  _property->attach_to_state(&xns, xproperty_path, xauto_access);

  if(xauto_access)
  {
    _coordinates->get_read_access();
    _property->get_read_access();
  }
 
  _base_space->attach_to_state(&(_property->schema().base_space()));

  if(xauto_access)
  {
    xns.release_access();
    _coordinates->release_access();
    _property->release_access();
  }

  // Postconditions:

  ensure(invariant());
  ensure(coordinates().path(true) == xcoordinates_path);
  ensure(property().path(true) == xproperty_path);

  // Exit:

  return;
}

///
fields::field_met_ed::
field_met_ed(sec_met_ed* xproperty,
         sec_ed_invertible* xcoordinates,
         base_space_member* xbase_space)
  : field_met(xproperty, xcoordinates, xbase_space)
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

///
fields::field_met_ed&
fields::field_met_ed::
operator=(const field_vd& xother)
{
  // Preconditions:

  require(precondition_of(field_vd::operator=(xother)));

  // Body:

  field_vd::operator=(xother);

  // Postconditions:

  ensure(postcondition_of(field_vd::operator=(xother)));

  // Exit:

  return *this;
}

///
fields::field_met_ed&
fields::field_met_ed::
operator=(const field_met_ed& xother)
{
  // Preconditions:

  require(precondition_of(field_vd::operator=(xother)));

  // Body:

  field_vd::operator=(xother);

  // Postconditions:

  ensure(postcondition_of(field_vd::operator=(xother)));

  // Exit:

  return *this;
}

///
fields::field_met_ed&
fields::field_met_ed::
operator=(const sec_met_ed& xsection)
{
  // Preconditions:

  require(precondition_of(field_vd::operator=(xsection)));

  // Body:

  field_vd::operator=(xsection);

  // Postconditions:

  ensure(postcondition_of(field_vd::operator=(xsection)));

  // Exit

  return *this;

}

///
fields::field_met_ed&
fields::field_met_ed::
operator=(const met_ed& xfiber)
{
  // Preconditions:

  require(precondition_of(field_vd::operator=(xfiber)));

  // Body:

  field_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(field_vd::operator=(xfiber)));

  // Exit

  return *this;

}

///
fields::field_met_ed&
fields::field_met_ed::
operator=(const met_ed_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(field_vd::operator=(xfiber)));

  // Body:

  field_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(field_vd::operator=(xfiber)));

  // Exit

  return *this;

}

///
fields::field_met_ed::
~field_met_ed()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

///
fiber_bundle::sec_met_ed&
fields::field_met_ed::
property() const
{
  // Preconditions:

  // Body:

  sec_met_ed& result = dynamic_cast<sec_met_ed&>(*_property);

  // Postconditions:

  // Exit:

  return result;
}


///
bool
fields::field_met_ed::
same_property_fiber_schema(const field_met_ed& xother, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
    xother.get_read_access();
  }

  result = property().schema().fiber_schema().
             is_same_state(&xother.property().schema().fiber_schema());

  if(xauto_access)
  {
    release_access();
    xother.release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

//=============================================================================
// ANY FACET OF CLASS FIELD_MET_ED
//=============================================================================

///
const string&
fields::field_met_ed::
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

///
const string&
fields::field_met_ed::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("field_met_ed");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
bool
fields::field_met_ed::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if xother conforms to this.

  bool result = dynamic_cast<const field_met_ed*>(xother) != 0;

  // Postconditions:

  return result;
}

///
fields::field_met_ed*
fields::field_met_ed::
clone() const
{
  field_met_ed* result;

  // Preconditions:

  // Body:

  result = new field_met_ed();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
bool
fields::field_met_ed::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(field_met::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ?
               base_space().is_same_state(&property().schema().base_space()) :
               true);

    invariance(state_is_read_accessible() ?
               property().schema().base_space().le(&coordinates().
                 schema().base_space()) :
               true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

//=============================================================================
// NON-MEMBER FUNCTIONS OF CLASS FIELD_MET_ED
//=============================================================================

///
fields::field_met_ed&
fields::
operator>>(const field_met_ed& xsrc, field_met_ed& xdst)
{
  // Preconditions:

  require(xsrc.is_attached());
  require(xdst.is_attached());
  require(xsrc.same_property_fiber_schema(xdst, true));

  // Body:

  not_implemented();

  // Postconditions:

  //Exit:

  return xdst;
}

///
ostream&
fields::
operator<<(ostream& xos, const field_met_ed& xfield)
{
  // Preconditions:

  require(xfield.state_is_read_accessible());

  // Body:

  xfield.print_property_dofs(xos, 0, "", false, false);

  // Postconditions:

  // Exit:

  return xos;
}

//==============================================================================

/// Include field_vd algebra function definitions.

//...

