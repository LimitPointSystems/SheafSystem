// $RCSfile: record.cc,v $ $Revision: 1.18 $ $Date: 2013/01/12 17:17:36 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class record

#include "record.h"
#include "assert_contract.h"

// PUBLIC MEMBER FUNCTIONS

// CANONICAL MEMBERS

// No default constructor

// Copy constructor
///
sheaf::record::
record(const record& xother)
    : _index(xother._index), _scaffold(xother._scaffold)
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}



// Virtual constructor
///
sheaf::record*
sheaf::record::
clone() const
{
  record* result;

  // Preconditions:

  // Body:

  result = new record(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


// Destructor
///
sheaf::record::
~record()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


// Class invariant
///
bool
sheaf::record::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// Conformance test
///
bool
sheaf::record::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const record*>(other) != 0;

  // Postconditions:

  return result;

}



// RECORD INTERFACE



///
sheaf::record::
record(const poset_scaffold& xscaffold)
      : _scaffold(const_cast<poset_scaffold&>(xscaffold))
{
  // Preconditions:

  // Body:

  _index.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(!external_index().is_valid());
  ensure(&(scaffold()) == &xscaffold);

  // Exit

  return;
}



