
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

/// @file
/// Implementation for class primitives_index_space_iterator

#include "ComLimitPoint/sheaf/primitives_index_space_iterator.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/explicit_index_space_handle.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/primitives_index_space_state.h"
#include "ComLimitPoint/sheaf/primitives_schema_member_index.h"

namespace
{
  const sheaf::size_type CT = 
    sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_END - sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN;

  typedef sheaf::primitives_index_space_state::pod_type pod_type;

  const pod_type BEGIN = 0;
  const pod_type END   = CT;

  const pod_type HUB_BEGIN = sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN;
  const pod_type HUB_END   = sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_END;
}

// ===========================================================
// PRIMITIVES_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitives_index_space_iterator::
primitives_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::primitives_index_space_iterator::
primitives_index_space_iterator(const primitives_index_space_iterator& xother)
  : explicit_index_space_iterator(xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

sheaf::primitives_index_space_iterator::
primitives_index_space_iterator(const index_space_family& xid_spaces,
			    pod_type xindex)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  attach_to(xid_spaces, xindex);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

sheaf::primitives_index_space_iterator::
primitives_index_space_iterator(const index_space_family& xid_spaces,
			    const std::string& xname)
{
  // Preconditions:

  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xname);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

sheaf::primitives_index_space_iterator&
sheaf::primitives_index_space_iterator::
operator=(const primitives_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    (void) explicit_index_space_iterator::operator=(xother);
  }
  else
  {
    detach();
  }

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

sheaf::primitives_index_space_iterator::
~primitives_index_space_iterator()
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// EXPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::primitives_index_space_iterator&
sheaf::primitives_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const primitives_index_space_iterator& lother =
    dynamic_cast<const primitives_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

sheaf::primitives_index_space_iterator*
sheaf::primitives_index_space_iterator::
clone() const
{
  primitives_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new primitives_index_space_iterator(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::primitives_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Increment to the next entry.

  ++_pod;
  if(_pod == CT)
  {
    // The iteration is done.

    invalidate_ids();
  }
  else
  {
    ++_hub_pod;
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() == (old_pod + 1));
  ensure(is_done() || hub_pod() == (old_hub_pod + 1));

  // Exit:

  return;
}

void
sheaf::primitives_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  _pod = BEGIN;
  _hub_pod = HUB_BEGIN;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::primitives_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  _state  = xstate;

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == xstate);

  // Exit:

  return;
}

bool
sheaf::primitives_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<primitives_index_space_state*>(xstate) != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::primitives_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const primitives_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::primitives_index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(explicit_index_space_iterator::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
