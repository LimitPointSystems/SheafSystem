
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
/// Implementation for class explicit_index_space_iterator

#include "explicit_index_space_iterator.h"

#include "assert_contract.h"
#include "explicit_index_space_state.h"
#include "index_space_family.h"

// ===========================================================
// EXPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_iterator::
~explicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::explicit_index_space_iterator::
explicit_index_space_iterator()
  : _state(0)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::explicit_index_space_iterator::
explicit_index_space_iterator(const explicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
//  ensure((*this) == xother);

  // Exit:

  return;
}

sheaf::explicit_index_space_iterator&
sheaf::explicit_index_space_iterator::
operator=(const explicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _state = xother._state;

    (void) index_space_iterator::operator=(xother);
  }
  
  // Postconditions:

  ensure(invariant());
//  ensure((*this) == xother);

  // Exit

  return *this;
}

sheaf::explicit_index_space_state&
sheaf::explicit_index_space_iterator::
state()
{
  // Preconditions:

  require(is_attached());

  // Body:

  explicit_index_space_state& result = *_state;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::explicit_index_space_state&
sheaf::explicit_index_space_iterator::
state() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const explicit_index_space_state& result = *_state;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_index_space_iterator&
sheaf::explicit_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const explicit_index_space_iterator& lother =
    dynamic_cast<const explicit_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
//  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::explicit_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const explicit_index_space_iterator& lother =
      dynamic_cast<const explicit_index_space_iterator&>(xother);

    result = result && (_state == lother._state);
  }
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_iterator*
sheaf::explicit_index_space_iterator::
clone() const
{
  explicit_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_collection&
sheaf::explicit_index_space_iterator::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_collection& result = _state->host();

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return result;
}

sheaf::index_space_iterator::pod_type
sheaf::explicit_index_space_iterator::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _state->index();

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_iterator::
is_attached() const
{
  // Preconditions:

  // Body:

  bool result = (_state != 0);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::explicit_index_space_iterator::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  attach_to(state(xindex));
  
  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::explicit_index_space_iterator::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  attach_to(xhost.explicit_state(xlocal_id));
  
  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

void
sheaf::explicit_index_space_iterator::
detach()
{
  // Preconditions:

  // Body:

  _state = 0;

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_iterator::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result = (xhost.explicit_state(xlocal_id) != 0);
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::explicit_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == xstate);

  // Exit:

  return;
}

bool
sheaf::explicit_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_iterator::
state(pod_type xindex) const
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));

  // Body:

  const index_space_collection& lhost =
    host().contains(xindex) ? host() : *id_spaces().collection(xindex);

  explicit_index_space_state* result =
    lhost.explicit_state(lhost.local_scope(xindex));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::explicit_index_space_state*
sheaf::explicit_index_space_iterator::
state(const index_space_collection& xhost, pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  explicit_index_space_state* result = xhost.explicit_state(xlocal_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::explicit_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::explicit_index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(index_space_iterator::invariant());

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

