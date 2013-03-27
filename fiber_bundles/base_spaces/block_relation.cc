// $RCSfile: block_relation.cc,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:16:51 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//




// Implementation for class block_relation

#include "assert_contract.h"
#include "block_relation.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BLOCK_RELATION FACET
// ===========================================================

///
fiber_bundle::block_relation::
block_relation()
{
  // Nothing to do.
}

///
fiber_bundle::block_relation::
~block_relation()
{
  // Nothing to do.
}


// ===========================================================
// ANY FACET
// ===========================================================

///
bool
fiber_bundle::block_relation::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    invariance(any::invariant());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

///
bool
fiber_bundle::block_relation::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const block_relation*>(other) != 0;

  // Postconditions:

  return result;
}



