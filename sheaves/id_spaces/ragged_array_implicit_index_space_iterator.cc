
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
/// Implementation for class ragged_array_implicit_index_space_iterator

#include "SheafSystem/ragged_array_implicit_index_space_iterator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/ragged_array_index_space_interval.h"
#include "SheafSystem/index_space_family.h"

// ===========================================================
// RAGGED_ARRAY_IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::ragged_array_implicit_index_space_iterator::
ragged_array_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::ragged_array_implicit_index_space_iterator::
ragged_array_implicit_index_space_iterator(const ragged_array_implicit_index_space_iterator& xother)
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

sheaf::ragged_array_implicit_index_space_iterator::
ragged_array_implicit_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::ragged_array_implicit_index_space_iterator::
ragged_array_implicit_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::ragged_array_implicit_index_space_iterator&
sheaf::ragged_array_implicit_index_space_iterator::
operator=(const ragged_array_implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _to_hub = xother._to_hub;
    _end    = xother._end;

    (void) implicit_index_space_iterator::operator=(xother);
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

sheaf::ragged_array_implicit_index_space_iterator::
~ragged_array_implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MAMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::ragged_array_implicit_index_space_iterator&
sheaf::ragged_array_implicit_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const ragged_array_implicit_index_space_iterator& lother =
    dynamic_cast<const ragged_array_implicit_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::ragged_array_implicit_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = implicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const ragged_array_implicit_index_space_iterator& lother =
      dynamic_cast<const ragged_array_implicit_index_space_iterator&>(xother);

    result = result && (_to_hub == lother._to_hub);
    result = result && (_end == lother._end);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

sheaf::ragged_array_implicit_index_space_iterator*
sheaf::ragged_array_implicit_index_space_iterator::
clone() const
{
  ragged_array_implicit_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new ragged_array_implicit_index_space_iterator(*this);

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
sheaf::ragged_array_implicit_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Skip forward until we're done or we find a valid hub id.

  do
  {
    ++_pod;

    if(_pod == _end)
    {
      // Done with the iteration.

      invalidate_ids();
      break;
    }
  }
  while(!is_valid(_hub_pod = _to_hub[_pod]));
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

void
sheaf::ragged_array_implicit_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _is_done = false;

  // Start at begin.

  _pod = 0;

  while(!is_valid(_hub_pod = _to_hub[_pod]))
  {
    _pod++;

    if(_pod == _end)
    {
      // Reached the end entry before finding a valid hub id;
      // invalidate the ids and quit.
      
      invalidate_ids();
      break;
    }
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
sheaf::ragged_array_implicit_index_space_iterator::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));
  require(reinterpret_cast<const ragged_array_index_space_interval&>(xhost).ct(xlocal_id) > 0);

  // Body:

  // Assign the state information.

  _host     = &xhost;
  _local_id = xlocal_id;

  // Find the section of the ragged_array that represents this id space.

  const ragged_array_index_space_interval* lhost =
    reinterpret_cast<const ragged_array_index_space_interval*>(_host);

  _to_hub   = lhost->hub_ids()[_local_id];
  _end      = lhost->end(_local_id);

  // Reset the iterator.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

bool
sheaf::ragged_array_implicit_index_space_iterator::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<const ragged_array_index_space_interval*>(&xhost) != 0);

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
sheaf::ragged_array_implicit_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ragged_array_implicit_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::ragged_array_implicit_index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(implicit_index_space_iterator::invariant());

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


