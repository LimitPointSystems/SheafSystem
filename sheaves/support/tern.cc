
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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

