
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

// Implementation for class field_dof_map

#include "field_dof_map.h"
#include "assert_contract.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

///
const std::string&
fiber_bundle::field_dof_map::
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
const std::string&
fiber_bundle::field_dof_map::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("field_dof_map");

  // Postconditions:

  ensure(!result.empty());
  ensure(result == "field_dof_map");

  // Exit:

  return result;
}

// CANONICAL MEMBERS


///
fiber_bundle::field_dof_map&
fiber_bundle::field_dof_map::
operator=(const field_dof_map& xother)
{

  // Preconditions:

  require(xother.is_initialized());

  // Body:

  section_dof_map::operator=(xother);

  // Postconditions:

  // Exit

  return *this;
}


///
fiber_bundle::field_dof_map::
~field_dof_map()
{

  // Preconditions:


  // Body:

  // Postconditions:

  // Exit

  return;
}


///
bool
fiber_bundle::field_dof_map::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && section_dof_map::invariant();

  // Postconditions:

  // Exit

  return result;
}


// MAP INTERFACE



// PROTECTED MEMBER FUNCTIONS

// CANONICAL MEMBERS

fiber_bundle::field_dof_map::
field_dof_map()
{

  // Preconditions:


  // Body:

  // No action required

  // Postconditions:

  // Exit

  return;
}


fiber_bundle::field_dof_map::
field_dof_map(const field_dof_map& xother)
    : section_dof_map(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}


// OTHER CONSTRUCTORS

fiber_bundle::field_dof_map::
field_dof_map(const sec_rep_space* xhost)
    : section_dof_map(xhost, xhost->base().index(), xhost->base().version())
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}
