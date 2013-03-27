// $RCSfile: hub_index_space_iterator.cc,v $ $Revision: 1.5 $ $Date: 2013/03/13 00:59:02 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class hub_index_space_iterator

#include "hub_index_space_iterator.h"

#include "assert_contract.h"
#include "explicit_index_space_handle.h"
#include "index_space_family.h"
#include "interval_set_iterator.h"
#include "primary_sum_index_space_state.h"

// ===========================================================
// HUB_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::hub_index_space_iterator::
hub_index_space_iterator()
{
  // Preconditions:

  // Body:

  _mbr_itr = 0;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::hub_index_space_iterator::
hub_index_space_iterator(const hub_index_space_iterator& xother)
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

sheaf::hub_index_space_iterator::
hub_index_space_iterator(const index_space_family& xid_spaces,
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

sheaf::hub_index_space_iterator::
hub_index_space_iterator(const index_space_family& xid_spaces,
			 const string& xname)
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

sheaf::hub_index_space_iterator&
sheaf::hub_index_space_iterator::
operator=(const hub_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  _mbr_itr = new interval_set_iterator(*xother._mbr_itr);
  _rem     = xother._rem;

  (void) explicit_index_space_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

sheaf::hub_index_space_iterator::
~hub_index_space_iterator()
{
  // Preconditions:

  // Body:

  if(_mbr_itr != 0)
  {
    delete _mbr_itr;
  }
  
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

sheaf::hub_index_space_iterator&
sheaf::hub_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const hub_index_space_iterator& lother =
    dynamic_cast<const hub_index_space_iterator&>(xother);


  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::hub_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = explicit_index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const hub_index_space_iterator& lother =
      dynamic_cast<const hub_index_space_iterator&>(xother);

    result = result && (*_mbr_itr == *lother._mbr_itr);
    result = result && (_rem == lother._rem);
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit

  return result;
}

sheaf::hub_index_space_iterator*
sheaf::hub_index_space_iterator::
clone() const
{
  hub_index_space_iterator* result;

  // Preconditions:

  // Body:

  result = new hub_index_space_iterator(*this);

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
sheaf::hub_index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  // Iterate to the next member.
    
  _mbr_itr->next();

  if(_mbr_itr->is_done())
  {
    // The iteration is done.

    invalidate_ids();
  }
  else
  {
    // Still iterating over member ids;
    // set the ids.

    _pod = _mbr_itr->item();
    _hub_pod = _pod;
  }
  
  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() > old_pod);
  ensure(is_done() || hub_pod() > old_hub_pod);

  // Exit:

  return;
}

void
sheaf::hub_index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  _mbr_itr->reset();
  
  if(_mbr_itr->is_done())
  {
    // The member set is empty, the iteration is done.

    invalidate_ids();
  }
  else
  {
    // There's at least one entry, the iteration is not done.

    _is_done = false;
    _pod = _mbr_itr->item();
    _hub_pod = _pod;
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
sheaf::hub_index_space_iterator::
attach_to(explicit_index_space_state* xstate)
{
  // Preconditions:

  require(xstate != 0);
  require(conforms_to_state(xstate));

  // Body:

  // Assign the state information.

  primary_sum_index_space_state* lstate =
    reinterpret_cast<primary_sum_index_space_state*>(xstate);

  _state   = xstate;
  _mbr_itr = lstate->_members.iterator(true);
  _rem     = &lstate->_rem;

  // Start at the first id.

  reset();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&state() == xstate);

  // Exit:

  return;
}

bool
sheaf::hub_index_space_iterator::
conforms_to_state(explicit_index_space_state* xstate) const
{
  // Preconditions:

  // Body:

  bool result = (dynamic_cast<primary_sum_index_space_state*>(xstate) != 0);

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
sheaf::hub_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result =
    dynamic_cast<const hub_index_space_iterator*>(other) != 0;

  // Postconditions:

  return result;
}

bool
sheaf::hub_index_space_iterator::
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

    invariance(is_done() || pod() == hub_pod());

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


