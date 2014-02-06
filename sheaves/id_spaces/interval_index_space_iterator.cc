
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
/// Implementation for class interval_index_space_iterator

#include "interval_index_space_iterator.h"

#include "assert_contract.h"
#include "explicit_index_space_handle.h"
#include "index_space_family.h"
#include "interval_index_space_state.h"

// ===========================================================
// INTERVAL_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_index_space_iterator::
interval_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::interval_index_space_iterator::
interval_index_space_iterator(const interval_index_space_iterator& xother)
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

sheaf::interval_index_space_iterator::
interval_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::interval_index_space_iterator::
interval_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::interval_index_space_iterator::
~interval_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

sheaf::interval_index_space_iterator&
sheaf::interval_index_space_iterator::
operator=(const interval_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _to_hub         = xother._to_hub;
    _itr            = xother._itr;
    _interval_begin = xother._interval_begin;
    _interval_end   = xother._interval_end;

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

void
sheaf::interval_index_space_iterator::
next_interval()
{
  // Preconditions:

  require(!is_done());
  
  // Body:

  pod_type linterval_begin = _itr->first + 1;
  ++_itr;
  _is_done = (_itr == _to_hub->end());

  if(!_is_done)
  {
    // Found the next interval.

    if(!is_valid(_itr->second))
    {
      // The current interval is not mapped; 
      // we're going to skip it, but first
      // set the beginning of the next interval.

      linterval_begin = _itr->first + 1;

      // Now skip the current intreval.

      ++_itr;
	
      // Last interval can not be unmapped,
      // so there must be another one and
      // there can not be two unmapped intervals in a row.

      assertion(_itr != _to_hub->end());
      assertion(is_valid(_itr->second));
    }

    // Update the interval ids.

    update_interval_ids(linterval_begin);
  }
  else
  {
    // There is no next interval, we're done.

    invalidate_interval_ids();
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::interval_index_space_iterator::pod_type
sheaf::interval_index_space_iterator::
interval_begin() const
{
  return _interval_begin;
}

sheaf::interval_index_space_iterator::pod_type
sheaf::interval_index_space_iterator::
interval_end() const
{
  return _interval_end;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::interval_index_space_iterator::
update_interval_ids(pod_type xinterval_begin)
{
  // Preconditions:

  require(!is_done());
  require(is_valid(xinterval_begin));

  // Body:

  // Assign the interval extrema.
  
  _interval_begin = xinterval_begin;
  _interval_end   =  _itr->first;

  // Set the current ids.

  _pod = _interval_begin;
  _hub_pod = _itr->second - (_interval_end - _interval_begin);

  // Postconditions:

  ensure(is_valid(pod()));
  ensure(is_valid(hub_pod()));
  ensure(is_valid(interval_begin()));
  ensure(is_valid(interval_end()));

  // Exit:

  return;
}

void
sheaf::interval_index_space_iterator::
invalidate_interval_ids()
{
  // Preconditions:

  // Body:

  _interval_begin = invalid_pod_index();
  _interval_end = invalid_pod_index();

  invalidate_ids();

  // Postconditions:

  // Exit:

  return;
}

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

sheaf::interval_index_space_iterator&
sheaf::interval_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const interval_index_space_iterator& lother =
    dynamic_cast<const interval_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::interval_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = explicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const interval_index_space_iterator& lother =
      dynamic_cast<const interval_index_space_iterator&>(xother);

    result = result && (_to_hub == lother._to_hub);
    result = result && (_itr == lother._itr);
    result = result && (_interval_begin == lother._interval_begin);
    result = result && (_interval_end == lother._interval_end);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

sheaf::interval_index_space_iterator*
sheaf::interval_index_space_iterator::
clone() const
{
  interval_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new interval_index_space_iterator(*this);

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
sheaf::interval_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Iterate to the next id.

  ++_pod;

  if(_pod > _interval_end)
  {
    // At the end of the current interval;
    // advance to the next interval.

    next_interval();
  }
  else
  {
    // Still in the same interval;
    // increment hub id.

    ++_hub_pod;
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

void
sheaf::interval_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _itr = _to_hub->begin();

  if(_itr != _to_hub->end())
  {
    // There's at least one entry, we're not done.

    _is_done = false;

    // Found end of implicit 0-th interval;
    // mapped value must be invalid.

    assertion(!is_valid(_itr->second));

    // The beginning of the first interval is the next id.

    pod_type linterval_begin = _itr->first + 1;

    // Find the end of the first interval.

    ++_itr;

    // There can not be just a single entry.
    // and there can not be two unmapped intervals in a row.

    assertion(_itr != _to_hub->end());
    assertion(is_valid(_itr->second));

    // Update the interval ids.

    update_interval_ids(linterval_begin);
  }
  else
  {
    // The map is empty, we're done.

    invalidate_ids();
  }
    
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::interval_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  _state  = xstate;
  _to_hub = &reinterpret_cast<interval_index_space_state*>(_state)->_to_range;

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == xstate);
  ensure(!is_done() ? pod() >= 0 : true);
  ensure(!is_done() ? is_valid(hub_pod()) : true);

  // Exit:

  return;
}

bool
sheaf::interval_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<interval_index_space_state*>(xstate) != 0);

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
sheaf::interval_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::interval_index_space_iterator::
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

