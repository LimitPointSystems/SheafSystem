
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
/// Implementation for class index_space_family_iterator

#include "SheafSystem/index_space_family_iterator.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_space_interval.h"
#include "SheafSystem/index_space_iterator.h"

// ===========================================================
// INDEX_SPACE_FAMILY_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_family_iterator::
index_space_family_iterator(const index_space_family& xid_spaces,
			    bool xonly_persistent)
  : _id_spaces(&xid_spaces),
    _id_space_itr(xonly_persistent)
{
  // Preconditions:

  // Body:

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(&id_spaces() == &xid_spaces);
  ensure(only_persistent() == xonly_persistent);

  // Exit:

  return;
}

sheaf::index_space_family_iterator::
~index_space_family_iterator()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_space_family_iterator&
sheaf::index_space_family_iterator::
operator=(const index_space_family_iterator& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  _id_spaces = xother._id_spaces;
  _interval_itr = xother._interval_itr;
  _id_space_itr = xother._id_space_itr;
  
  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

bool
sheaf::index_space_family_iterator::
operator==(const index_space_family_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = (_id_spaces == xother._id_spaces);
  result = result && (_interval_itr == xother._interval_itr);
  result = result && (_id_space_itr == xother._id_space_itr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit

  return result;
}

sheaf::index_space_family_iterator*
sheaf::index_space_family_iterator::
clone() const
{
  // Preconditions:

  // Body:
  
  index_space_family_iterator* result =
    new index_space_family_iterator(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result; 
}

bool
sheaf::index_space_family_iterator::
only_persistent() const
{
  // Preconditions:

  // Body:

  bool result = _id_space_itr.only_persistent();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_family_iterator::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  define_old_variable(pod_type old_index = index());

  // Increment to the next id space.

  _id_space_itr.next();
  next_id_space();

  while(_id_space_itr.is_done())
  {
    // Done with the current id space interval, move to the next one.

    ++_interval_itr;
    if(_interval_itr == _id_spaces->_intervals.end())
    {
      // The iteration is done.

      _id_space_itr.detach();
      break;
    }
    else if((_interval_itr->second != 0) &&
	    (!only_persistent() ||
	     _interval_itr->second->supports_persistent_id_spaces()))
    {
      // Attach the interval iterator to the current interval.

      _id_space_itr.attach_to(*_interval_itr->second);

      // Increment to the next id space.

      next_id_space();
    }
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_done() || index() != old_index);

  // Exit:

  return;
}

bool
sheaf::index_space_family_iterator::
is_done() const
{
  // Preconditions:

  // Body:

  bool result = !_id_space_itr.is_attached() || _id_space_itr.is_done();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_family_iterator::
reset()
{
  // Preconditions:

  // Body:

  _interval_itr = _id_spaces->_intervals.begin();
  _id_space_itr.detach();

  // The first entry should always be null.

  assertion(_interval_itr != _id_spaces->_intervals.end());
  assertion(_interval_itr->second == 0);

  // Increment to the first interval.

  do
  {
    ++_interval_itr;

    if(_interval_itr == _id_spaces->_intervals.end())
    {
      // The iteration is done.

      break;
    }
    else if((_interval_itr->second != 0) &&
	    (!only_persistent() ||
	     _interval_itr->second->supports_persistent_id_spaces()))
    {
      // Attach the interval iterator to the current interval.

      _id_space_itr.attach_to(*_interval_itr->second);

      // Increment to the next id space.

      next_id_space();

      if(!_id_space_itr.is_done())
      {
	// An id space was found, done searching.

	break;
      }
    }
  }
  while(_interval_itr != _id_spaces->_intervals.end());

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

const sheaf::index_space_interval&
sheaf::index_space_family_iterator::
host() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  const index_space_interval& result = _id_space_itr.host();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family_iterator::pod_type
sheaf::index_space_family_iterator::
index() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.index();

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

std::string
sheaf::index_space_family_iterator::
name() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  std::string result = _id_spaces->name(index());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_family_iterator::
index_space_family_iterator(const index_space_family_iterator& xother)
{
  // Preconditions:
    
  // Body:

  (*this) = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return; 
}

void
sheaf::index_space_family_iterator::
next_id_space()
{
  // Preconditions:

  require(_id_space_itr.is_attached());

  // Body:

  if(only_persistent())
  {
    // Find the first persistent id space.

    while(!_id_space_itr.is_done())
    {
      if(is_persistent())
      {
	// Found persistent id space, search is done.

	break;
      }

      _id_space_itr.next();
    }
  }
  
  // Postconditions:

  ensure(_id_space_itr.is_done() || !only_persistent() || is_persistent());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::index_space_family_iterator::
id_spaces() const
{
  // Preconditions:

  // Body:

  const index_space_family& result = *_id_spaces;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_family_iterator::
hub_id_space() const
{
  // Preconditions:

  // Body:

  const hub_index_space_handle& result = _id_spaces->hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::index_space_family_iterator::
ct() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  size_type result = _id_space_itr.ct();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
begin() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.begin();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
end() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.end();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
contains(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.contains(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
contains_hub(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.contains_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
contains_unglued_hub(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.contains_unglued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
contains_glued_hub(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.contains_glued_hub(xid);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
contains(pod_type xid, pod_type xhub_id) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.contains(xid, xhub_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
pod(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
hub_pod(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
unglued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.unglued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_unglued_hub(result));

  // Exit:

  return result;
}

sheaf::index_space_handle::pod_type
sheaf::index_space_family_iterator::
glued_hub_pod(pod_type xid) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id_space_itr.glued_hub_pod(xid);

  // Postconditions:

  ensure(!is_valid(result) || contains_glued_hub(result));

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
is_persistent() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.is_persistent();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_handle&
sheaf::index_space_family_iterator::
get_id_space() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  index_space_handle& result = _id_space_itr.get_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_family_iterator::
release_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(!is_done());
  require(allocated_id_space(xid_space));

  // Body:

  _id_space_itr.release_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_family_iterator::
allocated_id_space(index_space_handle& xid_space) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result =_id_space_itr.allocated_id_space(xid_space);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR POOL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator&
sheaf::index_space_family_iterator::
get_id_space_iterator() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  index_space_iterator& result = _id_space_itr.get_id_space_iterator();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

void
sheaf::index_space_family_iterator::
release_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(!is_done());
  require(allocated_id_space_iterator(xitr));

  // Body:

  _id_space_itr.release_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return;
}

bool
sheaf::index_space_family_iterator::
allocated_id_space_iterator(index_space_iterator& xitr) const
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool result = _id_space_itr.allocated_id_space_iterator(xitr);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::index_space_family_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_family_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_family_iterator::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(is_done() || is_valid(index()));
      
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

