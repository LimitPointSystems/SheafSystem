// $RCSfile: discretization_push_action.cc,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:20 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class discretization_push_action

#include "discretization_push_action.h"

#include "assert_contract.h"
#include "block.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// DISCRETIZATION_PUSH_ACTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::discretization_push_action::
~discretization_push_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


void
fields::discretization_push_action::
operator()(const scoped_index& xmbr_id, block<sec_vd_value_type>& xglobal_coords)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fields::discretization_push_action::
discretization_push_action()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

