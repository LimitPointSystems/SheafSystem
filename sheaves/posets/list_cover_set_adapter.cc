// $RCSfile: list_cover_set_adapter.cc,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:41 $
//
// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Implementation for class list_cover_set_adapter

#include "list_cover_set_adapter.h"

#include "assert_contract.h"
#include "cover_set_iterator.h"

// ===========================================================
// LIST_COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::list_cover_set_adapter::
list_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // This has a reference to _cover, let _cover know about it.
  // Prevents cover from deleting itself when this is the only reference,
  // e.g. when an iterator lets go.

  _cover.add_reference();

  assertion(!_cover.is_implicit());

  // Postconditions:

  ensure(invariant());
  ensure(is_empty());

  // Exit:

  return;
}

sheaf::list_cover_set_adapter::
list_cover_set_adapter(const list_cover_set_adapter& xother)
{
  // Preconditions:

  // Body:

  // This has a reference to _cover, let _cover know about it.
  // Prevents cover from deleting itself when this is the only reference,
  // e.g. when an iterator lets go.

  _cover.add_reference();

  // The following call does not invoke 
  // explicit_cover_set_adapter::operator=(const cover_set_adapter&)
  // as intended; it invokes a memberwise assignment created by the compiler.
  //  (*this) = xother;

  // Call desired functions explicitly.

  explicit_cover_set_adapter::operator=(xother);  

  // Postconditions:

  ensure(postcondition_of(operator=(xother)));

  // Exit:

  return;
}

sheaf::list_cover_set_adapter::
list_cover_set_adapter(const cover_set_iterator& xitr)
{

  // Preconditions:

  // Body:

  // This has a reference to _cover, let _cover know about it.
  // Prevents cover from deleting itself when this is the only reference,
  // e.g. when an iterator lets go.

  _cover.add_reference();

  // The following call does not invoke 
  // explicit_cover_set_adapter::opr=(const cover_set_iterator&),
  // it attempts to covert xitr to list_cover_set_adapter using this
  // constructor recursively.
  //  (*this) = xitr;

  // Call opr= directly instead.

  explicit_cover_set_adapter::operator=(xitr);

  // Postconditions:

  ensure((*this) == xitr);

  // Exit:

  return;
}

sheaf::list_cover_set_adapter::
~list_cover_set_adapter()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // In particular, do not remove the reference to _cover;
  // _cover will be deleted automatically because it is a data member,
  // don't want it deleting itself before that.

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::list_cover_set_adapter::
insert_member(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  _cover.insert_member(xindex);

  // Postconditions:

  ensure(contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::list_cover_set_adapter::
remove_member(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  _cover.remove_member(xindex);

  // Postconditions:

  ensure(!contains_member(xindex));

  // Exit:

  return;
}

void
sheaf::list_cover_set_adapter::
remove_member(const cover_set_iterator& xitr)
{
  // Preconditions:

  // Body:

  if(contains_iterator(xitr))
  {
    _cover.erase(xitr._itr);
  }
  else
  {
    remove_member(xitr.item());
  }

  // Postconditions:

  // Exit:

  return;
}

void
sheaf::list_cover_set_adapter::
replace_member(pod_index_type xold_mbr_index,
	       pod_index_type xnew_mbr_index)
{
  // Preconditions:

  // Body:

  _cover.replace_member(xold_mbr_index, xnew_mbr_index);

  // Postconditions:

  ensure(!contains_member(xold_mbr_index));
  ensure(contains_member(xnew_mbr_index));

  // Exit:

  return;
}


void
sheaf::list_cover_set_adapter::
clear()
{
  // Preconditions:


  // Body:

  _cover.clear();

  // Postconditions:

  ensure(is_empty());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER_SET_ADAPTER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::cover_set_iterator
sheaf::list_cover_set_adapter::
iterator() const
{
  return cover_set_iterator(_cover);
}

bool
sheaf::list_cover_set_adapter::
contains_iterator(const cover_set_iterator& xitr) const
{
  return (xitr._cover == &_cover);
}

bool
sheaf::list_cover_set_adapter::
is_empty() const
{
  return _cover.empty();
}

sheaf::size_type
sheaf::list_cover_set_adapter::
size() const
{
  return _cover.size();
}

bool
sheaf::list_cover_set_adapter::
is_singleton() const
{
  return _cover.is_singleton();
}

bool
sheaf::list_cover_set_adapter::
contains_member(pod_index_type xindex) const
{
  return _cover.contains_member(xindex);
}

sheaf::pod_index_type
sheaf::list_cover_set_adapter::
first_member() const
{
  // Preconditions:

  require(!is_empty());

  // Body:

  return _cover.front();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::list_cover_set_adapter::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const list_cover_set_adapter*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::list_cover_set_adapter*
sheaf::list_cover_set_adapter::
clone() const
{
  // Preconditions:

  // Body:

  list_cover_set_adapter* result = new list_cover_set_adapter();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::list_cover_set_adapter::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(explicit_cover_set_adapter::invariant());

    // Invariances for this class:

    invariance(_cover.ref_ct() >= 1);

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

