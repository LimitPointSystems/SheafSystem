

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class tern

#include "tern.h"
#include "assert_contract.h"
#include "error_message.h"

///@hack Something in the AIX xlC environment
/// is defining TRUE and FALSE. Until we find a
/// workaround, undefine them.

 

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

// =============================================================================
// TERN FACET
// =============================================================================

///
sheaf::tern::
tern()
{

  // Preconditions:


  // Body:

  _state = NEITHER;

  // Postconditions:

  // Exit:

  return;
}


///
sheaf::tern::
tern(const tern& xother)
{

  // Preconditions:


  // Body:

  _state = xother._state;

  // Postconditions:

  // Exit:

  return;
}


// ///
// sheaf::tern::
// tern(const bool& xother)
// {

//   // Preconditions:


//   // Body:

//   _state = xother ? TRUE : FALSE;

//   // Postconditions:

//   // Exit:

//   return;
// }


///
sheaf::tern::
~tern()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


///
sheaf::tern&
sheaf::tern::
operator=(const tern& xother)
{

  // Preconditions:


  // Body:

  _state = xother._state;

  // Postconditions:

  // Exit

  return *this;
}

// ///
// tern&
// sheaf::tern::
// operator=(const bool& xother)
// {

//   // Preconditions:


//   // Body:

//   _state = xother ? TRUE : FALSE;

//   // Postconditions:

//   // Exit

//   return *this;
// }

///
sheaf::tern::
operator bool() const
{
  // Preconditions:


  // Body:

  bool result = is_true();


  // Postconditions:

  ensure(result == is_true());

  // Exit:

  return result;
}


///
bool
sheaf::tern::
is_true() const
{
  return _state == TRUE;
}

///
bool
sheaf::tern::
is_false() const
{
  return _state == FALSE;
}

///
bool
sheaf::tern::
is_neither() const
{
  return _state == NEITHER;
}

///
sheaf::tern::
tern(state_type xstate)
{
  // Preconditions:


  // Body:

  _state = xstate;

  // Postconditions:


  // Exit:

  return;
}


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

