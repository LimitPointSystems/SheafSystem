
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class template implicit_entry_map_iterator.

#ifndef IMPLICIT_ENTRY_MAP_ITERATOR_IMPL_H
#define IMPLICIT_ENTRY_MAP_ITERATOR_IMPL_H

#ifndef IMPLICIT_ENTRY_MAP_ITERATOR_H
#include "implicit_entry_map_iterator.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef IMPLICIT_ENTRY_MAP_H
#include "implicit_entry_map.h"
#endif

#ifndef RC_PTR_H
#include "rc_ptr.h"
#endif

namespace sheaf
{
  
// =============================================================================
// IMPLICIT_ENTRY_MAP_ITERATOR FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename E, typename I>
implicit_entry_map_iterator<E, I>::
implicit_entry_map_iterator(const implicit_entry_map<E, I>& xmap)
{
  // Preconditions:

  // Body:

  _map = &xmap;
  reset();

  // Postconditions:

  // Exit:

  return;
}; 

template <typename E, typename I>
implicit_entry_map_iterator<E, I>::
~implicit_entry_map_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
};

template <typename E, typename I>
E&
implicit_entry_map_iterator<E, I>::
item()
{
  // Preconditions:

  require(!is_done());

  // Body:

  if(_item == 0)
  {
    // The first time the implicit value was requested, use the
    // map to construct it.

    _item = &_map->value(_id);
  }

  E& result = *_item;

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
const E&
implicit_entry_map_iterator<E, I>::
item() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  if(_item == 0)
  {
    // The first time the implicit value was requested, use the
    // map to construct it.

    _item = &_map->value(_id);
  }

  const E& result = *_item;

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
typename implicit_entry_map_iterator<E, I>::pod_type
implicit_entry_map_iterator<E, I>::
id() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  pod_type result = _id;

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
void
implicit_entry_map_iterator<E, I>::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  if(_explicit_value_itr != _map->_explicit_value_map.end())
  {
    // Still iterating over the explicit values.

    _id = _explicit_value_itr->first;
    _item = &**_explicit_value_itr->second;

    _explicit_value_itr++;
  }
  else if(_interval_itr != _map->_interval_map.end())
  {
    // Find the next implicit value that is not an explicit value.
    // Explicit values trumps implicit values.

    do
    {
      if(is_valid(_end))
      {
	// Already in an interval, increment to the next id.

	++_id;

	// Check if the interval has been deleted.

	/// @issue This is not very efficient.  Maybe this should be
	///        a mode or we should have a const iterator and a mutable
	///        iterator.

	if(!_map->contains_implicit_entry(_id))
	{
	  // The interval has been deleted, move to the end and continue.

	  _id = _end;
	}
      }
      else
      {
	// Starting with the first interval.

	assertion(_interval_itr->second == 0);

	_id = _interval_itr->first;
	_interval_itr++;

	// $$SCRIBBLE: There should not be a hole at the end or
	// back-to-back holes.  This should be enforced by the delete
	// operation in implicit_entry_map.

	assertion(_interval_itr != _map->_interval_map.end());
	assertion(_interval_itr->second != 0);

	_end = _interval_itr->first;
      }

      if(_id == _end)
      {
	// Move to the next interval.

	_interval_itr++;

	if(_interval_itr != _map->_interval_map.end())
	{
	  if(_interval_itr->second == 0)
	  {
	    // There is a hole in the interval map, start iterating
	    // from the end of the hole.

	    _id = _interval_itr->first;
	    _interval_itr++;

	    // $$SCRIBBLE: There should not be a hole at the end or
	    // back-to-back holes.  This should be enforced by the delete
	    // operation in implicit_entry_map.

	    assertion(_interval_itr != _map->_interval_map.end());
	    assertion(_interval_itr->second != 0);
	  }

	  // Set the end of the current interval.

	  _end = _interval_itr->first;
	}
	else
	{
	  // No more intervals to iterate over, the iteration is done.

	  _id = invalid_pod_index();
	}
      }
    }
    while(is_valid(_id) && _map->contains_explicit_entry(_id));

    // Void out the item.

    _item = 0;
  }
  else
  {
    // Reached the end of the explicit values and there are no implicit
    // values, the iteration is done.

    _id = invalid_pod_index();
  }

  // Postconditions:

  // Exit:

  return;
};

template <typename E, typename I>
bool
implicit_entry_map_iterator<E, I>::
is_done() const
{
  // Preconditions:

  // Body:

  bool result = !is_valid(_id);

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
void
implicit_entry_map_iterator<E, I>::
reset()
{
  // Preconditions:

  // Body:

  _id = 0; // Needs to be some valid value so the precondition of next() passes.
  _end = invalid_pod_index();

  _explicit_value_itr = _map->_explicit_value_map.begin();
  _interval_itr = _map->_interval_map.begin();

  next();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
};

// PROTECTED MEMBER FUNCTIONS

template <typename E, typename I>
implicit_entry_map_iterator<E, I>::
implicit_entry_map_iterator(const implicit_entry_map_iterator<E, I>& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  // Exit:

  return;
}; 

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

template <typename E, typename I>
bool
implicit_entry_map_iterator<E, I>::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  bool result = dynamic_cast< const implicit_entry_map_iterator<E, I>* >(other) != 0;

  // Postconditions:

  // Exit:

  return result;
};

template <typename E, typename I>
implicit_entry_map_iterator<E, I>*
implicit_entry_map_iterator<E, I>::
clone() const
{
  // Preconditions:

  // Body:

  implicit_entry_map_iterator<E, I>* result = new implicit_entry_map_iterator<E, I>(*_map);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
};

template <typename E, typename I>
implicit_entry_map_iterator<E, I>&
implicit_entry_map_iterator<E, I>::
operator=(const implicit_entry_map_iterator<E, I>& xother)
{
  // Preconditions:

  // Body:

  _map = xother._map;
  _id = xother._id;
  _item = xother._item;
  _explicit_value_itr = xother._explicit_value_itr;
  _interval_itr = xother._interval_itr;
  _end = xother._end;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
};

template <typename E, typename I>
bool
implicit_entry_map_iterator<E, I>::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(any::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariances for this class:

    /// @todo Implement invariant.
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
};

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

} // namespace sheaf

#endif // ifndef IMPLICIT_ENTRY_MAP_IMPL_H






