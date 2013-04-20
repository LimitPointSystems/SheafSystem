

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class discretization_context

#include "discretization_context.h"

#include "assert_contract.h"
#include "error_message.h"

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

ostream&
fiber_bundle::
operator<<(ostream& xos, const fiber_bundle::discretization_context& xc)
{
  // Preconditions:

  // Body:

  xos << "eval_id  = " << xc.eval_id << endl;
  xos << "local_id = " << xc.local_id << endl;
  xos << "disc_id =  " << xc.disc_id << endl;
  xos << "values =";
  for(int i=0; i<xc.values_ub; ++i)
  {
    xos << "  " << xc.values[i]; 
  }
  xos << endl;

  // Postconditions:

  // Exit:

  return xos;
}

size_t
fiber_bundle::
deep_size(const discretization_context& xc, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}
