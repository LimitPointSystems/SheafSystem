// $RCSfile: any.cc,v $ $Revision: 1.21 $ $Date: 2013/01/12 17:17:45 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class any

#include "any.h"
#include "assert_contract.h"


// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

///
sheaf::any::
any()
{

  // Preconditions:


  // Body:

  // Invariant checking enabled unless specifcally disabled

  _disable_invariance_check_request_depth = 0;

  // Postconditions:

  ensure(invariant_check());

  // Exit:

  return;
}

// GENERIC OBJECT INTERFACE

///
bool
sheaf::any::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const any*>(other) != 0;

  // Postconditions:

  return result;

}


///
bool
sheaf::any::
is_same_type(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other is same type as this

  bool result = this->is_ancestor_of(other) && other->is_ancestor_of(this);

  // Note: could use typeid, but this implementation
  // doesn't require <typeinfo>

  // Postconditions:

  return result;

}

///
sheaf::any*
sheaf::any::
clone() const
{
  any* result = 0;

  // Preconditions:

  // Body:

  // Does nothing here, since any is abstract,
  // just establishes the postcondition.

  // Should never be called, but just in case,
  // make it fail an assertion

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit

  return result;
}

///

sheaf::any::
~any()
{
  // Preconditions:

  // Body:

  // Nothing to do in this class.
  // Destructor defined just to make it virtual in all descendants.

  // Postconditions:


  // Exit:

  return;
}


bool
sheaf::any::
invariant() const
{
  // Body:

  invariance(disable_invariance_check_request_depth() >= 0);

  // Exit

  return true;
}
