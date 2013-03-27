// $RCSfile: explicit_cover_set_adapter.cc,v $ $Revision: 1.14 $ $Date: 2013/01/12 17:17:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class explicit_cover_set_adapter

#include "explicit_cover_set_adapter.h"

#include "assert_contract.h"
#include "cover_set_iterator.h"

// ===========================================================
// EXPLICIT_COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::explicit_cover_set_adapter::
explicit_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::explicit_cover_set_adapter::
explicit_cover_set_adapter(const explicit_cover_set_adapter& xother)
{
  // Preconditions:

  // Body:

  // Nothing to do

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::explicit_cover_set_adapter::
~explicit_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
insert_member(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
insert_member(const scoped_index& xindex)
{
  // Preconditions:

  // Body:

  insert_member(xindex.hub_pod());

  // Postconditions:

  ensure(contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
remove_member(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
remove_member(const scoped_index& xindex)
{
  // Preconditions:

  // Body:

  remove_member(xindex.hub_pod());

  // Postconditions:

  ensure(!contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
remove_member(const cover_set_iterator& xitr)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
replace_member(pod_index_type xold_mbr_index,
	       pod_index_type xnew_mbr_index)
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!contains_member(xold_mbr_index));
  ensure(contains_member(xnew_mbr_index));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
replace_member(const scoped_index& xold_mbr_index,
	       const scoped_index& xnew_mbr_index)
{
  // Preconditions:

  // Body:

  replace_member(xold_mbr_index.hub_pod(), xnew_mbr_index.hub_pod());

  // Postconditions:

  ensure(!contains_member(xold_mbr_index));
  ensure(contains_member(xnew_mbr_index));

  // Exit:

  return;
}

void
sheaf::explicit_cover_set_adapter::
clear()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}

sheaf::explicit_cover_set_adapter&
sheaf::explicit_cover_set_adapter::
operator=(const cover_set_adapter& xother)
{
  // Preconditions:

  // Body:

  cover_set_iterator litr = xother.iterator();
  operator=(litr);

  // Postconditions:

  ensure( (*this) == xother );

  // Exit:

  return *this;
}

sheaf::explicit_cover_set_adapter&
sheaf::explicit_cover_set_adapter::
operator=(const cover_set_iterator& xitr)
{
  // Preconditions:

  // Body:

  clear();
  (*this) += xitr;

  // Postconditions:

  ensure( (*this) == xitr );

  // Exit:

  return *this;
}

sheaf::explicit_cover_set_adapter&
sheaf::explicit_cover_set_adapter::
operator+=(cover_set_iterator xitr)
{
  // Preconditions:

  // Body:

  // Note: argument is pass-by-value rather than
  // pass-by-reference so const references can be passed.
  // This allows client to pass list_cover_set arguments
  // with implicit conversion.

  xitr.reset();
  while(!xitr.is_done())
  {
    insert_member(xitr.item());
    xitr.next();
  }

  // Postconditions:

  // Exit:

  return *this;
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
sheaf::explicit_cover_set_adapter::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const explicit_cover_set_adapter*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::explicit_cover_set_adapter*
sheaf::explicit_cover_set_adapter::
clone() const
{
  explicit_cover_set_adapter* result = 0;

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
sheaf::explicit_cover_set_adapter::
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

size_t
sheaf::deep_size(const explicit_cover_set_adapter& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Since does not contain any data members, there is no need to call
  // deep_size() on the parent class.  In fact, the compiler will not
  // allow us to cast to a cover_set_adapter because it has abstract
  // virual functions.

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
