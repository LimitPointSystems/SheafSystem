
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

/// @file
/// Implementation for class any_lite.

#include "any_lite.h"
#include "assert_contract.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS ANY_LITE
//==============================================================================

//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::any_lite::
~any_lite()
{
  // Preconditions:

  // Body:

  // Nothing to do in this class.
  // Destructor defined just to make it virtual in all descendants.

  // Postconditions:

  // Exit:

  return;
}

const string&
fiber_bundle::any_lite::
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
fiber_bundle::any_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("any_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::any_lite*
fiber_bundle::any_lite::
clone() const
{
  any_lite* result = 0;

  // Preconditions:

  // Body:

  // Does nothing here, since any_lite is abstract,
  // just establishes the postcondition.

  // Should never be called, but just in case,
  // make it fail an assertion.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit

  return result;
}

bool
fiber_bundle::any_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const any_lite*>(&xother) != 0;

  // Postconditions:

  return result;

}

bool
fiber_bundle::any_lite::
is_same_type(const any_lite& xother) const
{

  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if xother is same type as this.

  bool result = this->is_ancestor_of(xother) && xother.is_ancestor_of(*this);

  // Note: Could use typeid, but this implementation
  //       doesn't require <typeinfo>.

  // Postconditions:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::any_lite::
any_lite()
{
  // Preconditions:

  // Body:

  // Invariant checking enabled unless specifically disabled.

  _disable_invariance_check_request_depth = 0;

  // Postconditions:

  ensure(invariant_check());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CONTROLLABLE INVARIANT INTERFACE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::any_lite::
invariant() const
{
  // Preconditions:

  // Body:

  invariance(disable_invariance_check_request_depth() >= 0);

  // Postconditions:

  // Exit

  return true;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// DOF ACCESS FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

void*
fiber_bundle::any_lite::
row_dofs()
{
  void* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  
  // Exit:

  return result;
}

const void*
fiber_bundle::any_lite::
row_dofs() const
{
  void* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  
  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

