
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
/// Implementation for class reserved_primary_index_space_iterator

#include "reserved_primary_index_space_iterator.h"

#include "assert_contract.h"
#include "explicit_index_space_handle.h"
#include "index_space_family.h"
#include "reserved_primary_index_space_state.h"

// ===========================================================
// RESERVED_PRIMARY_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::reserved_primary_index_space_iterator::
reserved_primary_index_space_iterator()
  : _is_active_only(true)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::reserved_primary_index_space_iterator::
reserved_primary_index_space_iterator(const reserved_primary_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

sheaf::reserved_primary_index_space_iterator::
reserved_primary_index_space_iterator(const index_space_family& xid_spaces,
				      pod_type xindex)
  : _is_active_only(true)
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

sheaf::reserved_primary_index_space_iterator::
reserved_primary_index_space_iterator(const index_space_family& xid_spaces,
				      const std::string& xname)
  : _is_active_only(true)
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

sheaf::reserved_primary_index_space_iterator&
sheaf::reserved_primary_index_space_iterator::
operator=(const reserved_primary_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _offset = xother._offset;
    _end = xother._end;
    _is_active_only = xother._is_active_only;

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

sheaf::reserved_primary_index_space_iterator::
~reserved_primary_index_space_iterator()
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  // Exit:

  return;
}

sheaf::reserved_primary_index_space_iterator::pod_type
sheaf::reserved_primary_index_space_iterator::
offset() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _offset;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_iterator::
is_active_only() const
{
  // Preconditions:

  // Body:

  bool result = _is_active_only;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::reserved_primary_index_space_iterator::
put_is_active_only(bool xis_active_only)
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_active_only = xis_active_only;

  reserved_primary_index_space_state* lstate =
    reinterpret_cast<reserved_primary_index_space_state*>(_state);

  _end = _is_active_only ? lstate->next_hub_id() - _offset : lstate->ct();

  // Postconditions:

  ensure(is_active_only() == xis_active_only);

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

sheaf::reserved_primary_index_space_iterator&
sheaf::reserved_primary_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const reserved_primary_index_space_iterator& lother =
    dynamic_cast<const reserved_primary_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::reserved_primary_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = explicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const reserved_primary_index_space_iterator& lother =
      dynamic_cast<const reserved_primary_index_space_iterator&>(xother);

    result = result && (_offset == lother._offset);
    result = result && (_end == lother._end);
    result = result && (_is_active_only == lother._is_active_only);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

sheaf::reserved_primary_index_space_iterator*
sheaf::reserved_primary_index_space_iterator::
clone() const
{
  reserved_primary_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new reserved_primary_index_space_iterator(*this);

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
sheaf::reserved_primary_index_space_iterator::
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
  if(_pod == _end)
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
sheaf::reserved_primary_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  if(_end == 0 || !is_valid(_end))
  {
    // The map is empty, the iteration is done.

    invalidate_ids();
  }
  else
  {
    // There's at least one entry, the iteration is not done.

    _is_done = false;

    _pod = 0;
    _hub_pod = _offset;
  }

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
sheaf::reserved_primary_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  reserved_primary_index_space_state* lstate =
    reinterpret_cast<reserved_primary_index_space_state*>(xstate);

  _state  = xstate;
  _offset = lstate->offset();
  _end = _is_active_only ? lstate->next_hub_id() - _offset : lstate->ct();

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
sheaf::reserved_primary_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<reserved_primary_index_space_state*>(xstate) != 0);

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
sheaf::reserved_primary_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const reserved_primary_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::reserved_primary_index_space_iterator::
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
