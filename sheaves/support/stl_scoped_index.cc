

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class stl_scoped_index.

#include "stl_scoped_index.h"
#include "assert_contract.h"

using namespace sheaf;

// ===========================================================
// LEXOGRAPHICAL_COMPARE_POLICY
// ===========================================================

bool
sheaf::lexographical_compare_policy::
less_than(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result;

  if(xindex1.scope_id() == xindex2.scope_id())
    result = (xindex1.pod() < xindex2.pod());
  else
    result = (xindex1.scope_id() < xindex2.scope_id());

  // Postconditions:

  ensure((xindex1.scope_id() == xindex2.scope_id()) ?
	 result == xindex1.pod() < xindex2.pod() :
	 (xindex1.scope_id() < xindex2.scope_id()));

  // Exit:

  return result;
}

bool
sheaf::lexographical_compare_policy::
equal(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  // Body:

  bool result = (xindex1 == xindex2);
  
  // Postconditions:

  ensure(result == (xindex1 == xindex2));

  // Exit:

  return result;
}

// ===========================================================
// EQUIVALENCE_COMPARE_POLICY
// ===========================================================

bool
sheaf::equivalence_compare_policy::
less_than(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result = (xindex1 <~ xindex2);

  // Postconditions:

  ensure(result == (xindex1 <~ xindex2));

  // Exit:

  return result;
}

bool
sheaf::equivalence_compare_policy::
equal(const scoped_index& xindex1, const scoped_index& xindex2)
{
  // Preconditions:

  require(xindex1.is_scoped());
  require(xindex2.is_scoped());

  // Body:

  bool result = (xindex1 ==~ xindex2);
  
  // Postconditions:

  ensure(result == (xindex1 ==~ xindex2));

  // Exit:

  return result;
}
