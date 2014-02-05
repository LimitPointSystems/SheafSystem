
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

// Implementation for class uniform_eval_family


#include "base_space_member.h"
#include "factory.h"
#include "fiber_bundles_namespace.h"
#include "int_set.h"
#include "namespace_poset.h"
#include "sheaf.h"
#include "assert_contract.h"
#include "uniform_1d.h"
#include "uniform_2d.h"
#include "uniform_3d.h"
#include "uniform_eval_family.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS



///
fiber_bundle::uniform_eval_family::
uniform_eval_family(const uniform_eval_family& xother)
    : eval_family(xother)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}



///
fiber_bundle::uniform_eval_family*
fiber_bundle::uniform_eval_family::
clone() const
{
  uniform_eval_family* result;

  // Preconditions:

  // Body:

  result = new uniform_eval_family(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::uniform_eval_family::
~uniform_eval_family()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


///
bool
fiber_bundle::uniform_eval_family::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && eval_family::invariant();

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

///
bool
fiber_bundle::uniform_eval_family::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const uniform_eval_family*>(xother) != 0;

  // Postconditions:

  return result;

}



// DLINEAR_FAMILY FACET


///
fiber_bundle::uniform_eval_family::
uniform_eval_family(const namespace_poset& xname_space)
{

  // Preconditions:

  require(xname_space.state_is_read_accessible());
  require(xname_space.contains_poset(base_space_member::prototypes_poset_name()));

  // Body:

  initialize(xname_space);

  // Postconditions:

  ensure(invariant());
}


///
const std::string&
fiber_bundle::uniform_eval_family::
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
fiber_bundle::uniform_eval_family::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("uniform");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
void
fiber_bundle::uniform_eval_family::
initialize(const namespace_poset& xname_space)
{

  // Preconditions:

  require(!is_initialized());
  require(xname_space.state_is_read_accessible());
  require(xname_space.contains_poset(base_space_member::prototypes_poset_name()));

  // Body:

  eval_family::initialize(xname_space);

  // The type codes used here must be the same as those used
  // in fiber_bundles_namespace::make_base_space_member_prototypes().

  poset* lhost = &xname_space.member_poset<poset>(base_space_member::prototypes_poset_name(), false);
  lhost->get_read_access();

  // Allocate enough storage for the members.

  initialize_members(lhost->member_index_ub().pod());

  // Get the type id of each member of the family and
  // and create the appropriate entry in _members.

  base_space_member lmbr;
  lmbr.attach_to_state(lhost, "structured_block_1d");
  _members.force_item(lmbr.type_id(), new uniform_1d);

  lmbr.attach_to_state(lhost, "structured_block_2d");
  _members.force_item(lmbr.type_id(), new uniform_2d);

  lmbr.attach_to_state(lhost, "structured_block_3d");
  _members.force_item(lmbr.type_id(), new uniform_3d);

  lmbr.detach_from_state();
  lhost->release_access();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());

  // Exit:

  return;
}

///
bool
fiber_bundle::uniform_eval_family::
dofs_are_values() const
{
  return true;
}

///
bool
fiber_bundle::uniform_eval_family::
extrema_are_dofs() const
{
  return true;
}


// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

///
fiber_bundle::uniform_eval_family::
uniform_eval_family()
    : eval_family()
{

  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

