// $RCSfile: interval_set_iterator.cc,v $ $Revision: 1.11 $ $Date: 2013/01/14 23:29:39 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class interval_set_iterator

#include "interval_set_iterator.h"

#include "assert_contract.h"

// ===========================================================
// INTERVAL_SET_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::interval_set_iterator::
interval_set_iterator(const interval_set& xset, bool xis_member_iterator)
{
  // Preconditions:

  // Body:

  _set = &xset;
  _map = &xset._interval_map;
  _is_member_iterator = xis_member_iterator;

  reset();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::interval_set_iterator::
~interval_set_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

const sheaf::interval_set&
sheaf::interval_set_iterator::
set() const
{
  return *_set;
}

bool
sheaf::interval_set_iterator::
is_member_iterator() const
{
  return _is_member_iterator;
}

sheaf::interval_set_iterator::pod_type
sheaf::interval_set_iterator::
item() const
{
  // Preconditions:

  require(!is_done());

  // Body:

  // Postconditions:

  // Exit:

  return _item;
}

void
sheaf::interval_set_iterator::
next()
{
  // Preconditions:

  require(!is_done());

  // Body:

  ++_item;

  if(_item > _ub)
  {
    ++_map_itr;

    if(_map_itr != _map->end())
    {
      next_interval();
    }
    else
    {
      _item = invalid_pod_index();
      _ub = invalid_pod_index();
    }
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

bool
sheaf::interval_set_iterator::
is_done() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_map_itr == _map->end());

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::interval_set_iterator::
reset()
{
  // Preconditions:

  // Body:

  _map_itr = _map->begin();
  
  if(_map_itr != _map->end())
  {
    if(!_is_member_iterator)
    {
      ++_map_itr;
    }
    
    next_interval();
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::interval_set_iterator::
interval_set_iterator(const interval_set_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

void
sheaf::interval_set_iterator::
next_interval()
{
  // Preconditions:

  require(!is_done());

  // Body:

  _item = _map_itr->first+1;
  ++_map_itr;

  if(_map_itr != _map->end())
  {
    _ub = _map_itr->first;
  }
  else
  {
    _item = invalid_pod_index();
    _ub = invalid_pod_index();
  }
  
  // Postconditions:

  ensure(is_done() || is_member_iterator() == is_member_interval());

  // Exit:

  return;
}

bool
sheaf::interval_set_iterator::
is_member_interval() const
{
  return (_map_itr->second);
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::interval_set_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const interval_set_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::interval_set_iterator*
sheaf::interval_set_iterator::
clone() const
{
  interval_set_iterator* result = 0;

  // Preconditions:

  // Body:

  result = new interval_set_iterator(*_set, _is_member_iterator);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(set() == result->set());
  ensure(is_member_iterator() == result->is_member_iterator());

  // Exit:

  return result;
}

sheaf::interval_set_iterator&
sheaf::interval_set_iterator::
operator=(const interval_set_iterator& xother)
{
  // Preconditions:

  // Body:

  _set = xother._set;
  _is_member_iterator = xother._is_member_iterator;
  _item = xother._item;
  _ub = xother._ub;
  _map = xother._map;
  _map_itr = xother._map_itr;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
sheaf::interval_set_iterator::
operator==(const interval_set_iterator& xother) const
{
  // Preconditions:

  // Body:

  bool result = (_set == xother._set);
  result = result && (_is_member_iterator == xother._is_member_iterator);
  result = result && (_item == xother._item);
  result = result && (_ub == xother._ub);
  result = result && (_map == xother._map);
  result = result && (_map_itr == xother._map_itr);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::interval_set_iterator::
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

    invariance(is_done() || (is_member_iterator() == is_member_interval()));

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

