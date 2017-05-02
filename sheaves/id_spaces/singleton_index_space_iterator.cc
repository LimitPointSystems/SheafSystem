
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
/// Implementation for class singleton_index_space_iterator

#include "SheafSystem/singleton_index_space_iterator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/explicit_index_space_handle.h"
#include "SheafSystem/index_space_family.h"
#include "SheafSystem/singleton_index_space_state.h"

// ===========================================================
// SINGLETON_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::singleton_index_space_iterator::
singleton_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::singleton_index_space_iterator::
singleton_index_space_iterator(const singleton_index_space_iterator& xother)
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

sheaf::singleton_index_space_iterator::
singleton_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::singleton_index_space_iterator::
singleton_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::singleton_index_space_iterator&
sheaf::singleton_index_space_iterator::
operator=(const singleton_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _hub_begin = xother._hub_begin;

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

sheaf::singleton_index_space_iterator::
~singleton_index_space_iterator()
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  // Exit:

  return;
}

sheaf::singleton_index_space_iterator::pod_type
sheaf::singleton_index_space_iterator::
hub_begin() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _hub_begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
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

sheaf::singleton_index_space_iterator&
sheaf::singleton_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const singleton_index_space_iterator& lother =
    dynamic_cast<const singleton_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::singleton_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = explicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const singleton_index_space_iterator& lother =
      dynamic_cast<const singleton_index_space_iterator&>(xother);

    result = result && (_hub_begin == lother._hub_begin);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

sheaf::singleton_index_space_iterator*
sheaf::singleton_index_space_iterator::
clone() const
{
  singleton_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new singleton_index_space_iterator(*this);

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
sheaf::singleton_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Only one id, the iteration is done.

  invalidate_ids();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit:

  return;
}

void
sheaf::singleton_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  _pod = 0;
  _hub_pod = _hub_begin;

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
sheaf::singleton_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  _state  = xstate;
  _hub_begin = reinterpret_cast<singleton_index_space_state*>(_state)->hub_id();

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
sheaf::singleton_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<singleton_index_space_state*>(xstate) != 0);

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
sheaf::singleton_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const singleton_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::singleton_index_space_iterator::
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
