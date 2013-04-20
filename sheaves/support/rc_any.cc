

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class rc_any

#include "rc_any.h"

#include "assert_contract.h"

// ===========================================================
// RC_ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::rc_any::
rc_any()
{
  // Preconditions:

  // Body:

  _ref_ct=0;

  // Postconditions:

  // Exit:

  return;
}

sheaf::rc_any::
rc_any(const rc_any & xother)
{
  // Preconditions:

  // Body:

  _ref_ct=0;

  // Postconditions:

  // Exit:

  return;
}

sheaf::rc_any&
sheaf::rc_any::
operator=(const rc_any& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return *this;
}

sheaf::rc_any::
~rc_any()
{
  // Preconditions:

  require(ref_ct()==0);

  // Body:

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::rc_any::
add_reference()
{

  // Preconditions:

  // Body:

  ++_ref_ct;

  // Postconditions:

  ensure(ref_ct() > 0);

  // Exit:

  return;
}

void
sheaf::rc_any::
remove_reference()
{
  // Preconditions:

  // Body:

  if(--_ref_ct == 0)
    delete this;

  // Postconditions:

  // Exit:

  return;
}

bool
sheaf::rc_any::
is_shared() const
{
  // Preconditions:

  // Body:

  bool result = _ref_ct > 1;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::rc_any::
ref_ct() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return _ref_ct;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream & sheaf::operator << (ostream& xos, const rc_any& xrc)
{
  // Preconditions:

  // Body:

  xos << "rc_any: " << endl;
  xos << "  ref_ct = " << xrc.ref_ct() << endl;
  xos << "  shared = " << xrc.is_shared() << endl;
  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}
