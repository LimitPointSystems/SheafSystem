// $RCSfile: put_property_dofs_action.cc,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:22 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class put_property_dofs_action

#include "put_property_dofs_action.h"

#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "sec_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PUT_PROPERTY_DOFS_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::put_property_dofs_action::
put_property_dofs_action(sec_vd& xproperty, bool xauto_access)
    : _property(xproperty)
{
  // Preconditions:

  require(xauto_access || xproperty.state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    xproperty.get_read_access();
  }


  /// @issue assuming binary schema, one dof per component.

  int ldf = xproperty.schema().df();
  _dofs.reserve(ldf);
  _dofs.set_ct(ldf);

  if(xauto_access)
  {
    xproperty.release_access();
  }

  // Postconditions:

  // Exit:

  return;
}

fields::put_property_dofs_action::
~put_property_dofs_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::sec_vd&
fields::put_property_dofs_action::
property()
{
  // Preconditions:


  // Body:

  sec_vd& result = _property;

  // Postconditions:


  // Exit:

  return result;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
