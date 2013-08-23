
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


// Implementation for class record

#include "record.h"
#include "assert_contract.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// No default constructor

// Copy constructor
///
sheaf::record::
record(const record& xother)
    : _index(xother._index), _scaffold(xother._scaffold)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::record*
sheaf::record::
clone() const
{
  record* result;

  // Preconditions:

  // Body:

  result = new record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::record::
~record()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


// Class invariant
///
bool
sheaf::record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// Conformance test
///
bool
sheaf::record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const record*>(other) != 0;

  // Postconditions:

  return result;

}



// RECORD INTERFACE



///
sheaf::record::
record(const poset_scaffold& xscaffold)
      : _scaffold(const_cast<poset_scaffold&>(xscaffold))
{
  // Preconditions:

  // Body:

  _index.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(!external_index().is_valid());
  ensure(&(scaffold()) == &xscaffold);

  // Exit

  return;
}



