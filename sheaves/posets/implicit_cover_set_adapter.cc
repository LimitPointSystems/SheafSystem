// $RCSfile: implicit_cover_set_adapter.cc,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class implicit_cover_set_adapter

#include "implicit_cover_set_adapter.h"
#include "assert_contract.h"

// ===========================================================
// IMPLICIT_COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::implicit_cover_set_adapter::
implicit_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());
  ensure(!member_index().is_valid());

  // Exit:

  return;
}

sheaf::implicit_cover_set_adapter::
implicit_cover_set_adapter(const implicit_cover_set_adapter& xother)
{
  // Preconditions:

  // Body:

  _member_index = xother._member_index;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::implicit_cover_set_adapter::
~implicit_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::implicit_cover_set_adapter::
member_index() const
{
  return _member_index;
}

void
sheaf::implicit_cover_set_adapter::
put_member_index(const scoped_index& xindex)
{
  // Preconditions:

  require(can_emulate(xindex));

  // Body:

  _member_index = xindex;

  // Postconditions:

  ensure(member_index() == xindex);

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::implicit_cover_set_adapter::
range_begin() const
{
  return _range_begin;
}

const sheaf::scoped_index&
sheaf::implicit_cover_set_adapter::
range_end() const
{
  return _range_end;
}

sheaf::size_type
sheaf::implicit_cover_set_adapter::
range_size() const
{
  return _range_size;
}

bool
sheaf::implicit_cover_set_adapter::
can_emulate(const scoped_index& xindex) const
{
  return xindex.in_range(_range_begin, _range_end);
}

void
sheaf::implicit_cover_set_adapter::
put_range_begin(const scoped_index& xbegin)
{
  _range_begin = xbegin;
  _range_end = _range_begin + _range_size;

  // Postconditions:

  ensure(range_begin() == xbegin);
  ensure(range_end() == range_begin() + range_size());

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::implicit_cover_set_adapter::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const implicit_cover_set_adapter*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::implicit_cover_set_adapter*
sheaf::implicit_cover_set_adapter::
clone() const
{
  implicit_cover_set_adapter* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::implicit_cover_set_adapter::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(cover_set_adapter::invariant());

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

