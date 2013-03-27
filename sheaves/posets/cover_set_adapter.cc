// $RCSfile: cover_set_adapter.cc,v $ $Revision: 1.18 $ $Date: 2013/01/12 17:17:41 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class cover_set_adapter.

#include "cover_set_adapter.h"

#include "assert_contract.h"
#include "cover_set_iterator.h"
#include "std_set.h"
#include "scoped_index.h"

// ===========================================================
// COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::cover_set_adapter::
cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::cover_set_adapter::
cover_set_adapter(const cover_set_adapter& xother)
{

  // Preconditions:


  // Body:

  // Nothing to do

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

sheaf::cover_set_adapter::
~cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

sheaf::cover_set_iterator
sheaf::cover_set_adapter::
iterator() const
{
  cover_set_iterator result; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::cover_set_adapter::
is_empty() const
{
  bool result = false; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::cover_set_adapter::
is_singleton() const
{
  bool result = false; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

sheaf::size_type
sheaf::cover_set_adapter::
size() const
{
  size_type result = false; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::cover_set_adapter::
contains_member(pod_index_type xindex) const
{
  bool result = false; // Just to silence compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::cover_set_adapter::
contains_member(const scoped_index& xindex) const
{
  return contains_member(xindex.hub_pod());
}

bool
sheaf::cover_set_adapter::
operator==(const cover_set_adapter& xother) const
{
  // Preconditions:

  // Body:

  cover_set_iterator litr = xother.iterator();
  bool result = operator==(litr);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::cover_set_adapter::
operator==(cover_set_iterator xitr) const
{
  // Preconditions:

  // Body:

  // Note: argument is pass-by-value rather than
  // pass-by-reference so const references can be passed.
  // This allows client to pass list_cover_set arguments
  // with implicit conversion.

  set<pod_index_type> lother_set;
  xitr.reset();
  while(!xitr.is_done())
  {
    lother_set.insert(xitr.item());
    xitr.next();
  }

  set<pod_index_type> lthis_set;
  cover_set_iterator litr(iterator());

  while(!litr.is_done())
  {
    lthis_set.insert(litr.item());
    litr.next();
  }

  bool result = (lthis_set == lother_set);

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::cover_set_adapter::
first_member() const
{
  pod_index_type result = false; // Just to silence compiler warnings.

  // Preconditions:

  require(!is_empty());

  // Body:

  is_abstract();

  // Postconditions:

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
sheaf::cover_set_adapter::
is_ancestor_of(const any* other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const cover_set_adapter*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::cover_set_adapter*
sheaf::cover_set_adapter::
clone() const
{
  cover_set_adapter* result = 0; // Just to silence compiler warnings.

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
sheaf::cover_set_adapter::
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

ostream & sheaf::operator << (ostream &os, const cover_set_adapter& p)
{
  // Preconditions:

  // Body:

  cover_set_iterator litr(p.iterator());
  while(!litr.is_done())
  {
    os << " " << litr.item();
    litr.next();
  }

  // Postconditions:

  // Exit

  return os;
}

size_t
sheaf::deep_size(const cover_set_adapter& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
