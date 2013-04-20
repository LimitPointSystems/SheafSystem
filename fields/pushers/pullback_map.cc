
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class discretization_point

#include "pullback_map.h"

#include "std_iomanip.h"
#include "std_iostream.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream&
fields::operator<<(ostream& xos, const pullback_map_entry& xentry)
{

  // Preconditions:

  // Body:

  xos << "disc_id: " << setw(6) << xentry.disc_id << " domain_pt: " << xentry.domain_pt;

  // Postconditions:

  // Exit:

  return xos;
}
