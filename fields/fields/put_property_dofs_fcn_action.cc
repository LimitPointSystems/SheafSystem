
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class put_property_dofs_fcn_action

#include "put_property_dofs_fcn_action.h"

#include "assert_contract.h"
#include "block.h"
#include "error_message.h"
#include "sec_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1


// ===========================================================
// PUT_PROPERTY_DOFS_FCN_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::put_property_dofs_fcn_action::
put_property_dofs_fcn_action(sec_vd& xproperty,
                             property_dof_function_type xfcn,
                             bool xauto_access)
    : put_property_dofs_action(xproperty, xauto_access)
{
  // Preconditions:

  require(xauto_access || xproperty.state_is_read_accessible());

  // Body:

  _dof_function = xfcn;

  // Postconditions:

  // Exit:

  return;
}

fields::put_property_dofs_fcn_action::
~put_property_dofs_fcn_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::put_property_dofs_fcn_action::
operator()(const scoped_index& xdisc_id, block<sec_vd_value_type>& xcoords)
{
  // Preconditions:

  require(property().state_is_read_write_accessible());

  // Body:

  // Evaluate the property dof function at
  // the global coordinates of the discretization member.

  _dof_function(xcoords, _dofs);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "in put_property_dofs_fcn_action: coords: " << xcoords
  <<  "dofs: " << _dofs
  << endl;
#endif

  // Scatter the dofs into the property section.

  property().put_fiber(xdisc_id.pod(), _dofs.base(), _dofs.ct()*sizeof(sec_vd_dof_type));

  // Postconditions:


  // Exit:

  return;
}

fields::property_dof_function_type
fields::put_property_dofs_fcn_action::
dof_function()
{
  property_dof_function_type result;

  // Preconditions:

  // Body:

  result = _dof_function;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
