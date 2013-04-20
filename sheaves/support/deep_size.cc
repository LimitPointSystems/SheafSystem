
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for deep_size functions

#include "deep_size.impl.h"

size_t
sheaf::deep_size(const string& xp, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  //
  // @hack This calculation is a guess and should be revisited.
  //

  result += xp.size() * sizeof(char);

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

