

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class implicit_index_space_iterator

#include "implicit_index_space_iterator.h"

#include "assert_contract.h"
#include "index_space_family.h"

// ===========================================================
// IMPLICIT_INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::implicit_index_space_iterator::
~implicit_index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::implicit_index_space_iterator::
implicit_index_space_iterator()
  : _host(0),
    _local_id(invalid_pod_index())
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::implicit_index_space_iterator::
implicit_index_space_iterator(const implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(host() == xother.host());
  ensure(index() == xother.index());

  // Exit:

  return;
}

sheaf::implicit_index_space_iterator&
sheaf::implicit_index_space_iterator::
operator=(const implicit_index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  _host = xother._host;
  _local_id = xother._local_id;

  (void) index_space_iterator::operator=(xother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::implicit_index_space_iterator&
sheaf::implicit_index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const implicit_index_space_iterator& lother =
    dynamic_cast<const implicit_index_space_iterator&>(xother);

  (void) this->operator=(lother);

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::implicit_index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  bool result = index_space_iterator::operator==(xother);
  if(result && is_attached())
  {
    const implicit_index_space_iterator& lother =
      dynamic_cast<const implicit_index_space_iterator&>(xother);

    result = result && (_host == lother._host);
    result = result && (_local_id == lother._local_id);
  }
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::implicit_index_space_iterator*
sheaf::implicit_index_space_iterator::
clone() const
{
  implicit_index_space_iterator* result;

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
sheaf::implicit_index_space_iterator::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_collection& result = *_host;

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return result;
}

sheaf::index_space_iterator::pod_type
sheaf::implicit_index_space_iterator::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = _host->family_scope(_local_id);

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

bool
sheaf::implicit_index_space_iterator::
is_attached() const
{
  // Preconditions:

  // Body:

  bool result = is_valid(_local_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::implicit_index_space_iterator::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  const index_space_collection* lhost =
    _host->contains(xindex) ? _host : id_spaces().collection(xindex);

  attach_to(*lhost, lhost->local_scope(xindex));
  
  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::implicit_index_space_iterator::
detach()
{
  // Preconditions:

  // Body:

  _local_id = invalid_pod_index();

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

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
sheaf::implicit_index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const implicit_index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::implicit_index_space_iterator::
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

