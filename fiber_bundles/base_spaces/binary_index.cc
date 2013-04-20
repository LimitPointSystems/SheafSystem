
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Implementation for class binary_index

#include "binary_index.h"
#include "assert_contract.h"
#include "std_iostream.h"


// Member functions all inlined in header file.

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
fiber_bundle::
operator<<(ostream& xos, const fiber_bundle::binary_index& xbi)
{
  xos << xbi.i << "," << xbi.j;
  return xos;
}

