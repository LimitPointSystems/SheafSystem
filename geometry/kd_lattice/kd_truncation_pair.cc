

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_truncation_pair

#include "kd_truncation_pair.h"
#include "assert_contract.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
// KD_TRUNCATION_PAIR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_truncation_pair::
kd_truncation_pair()
{
  
  // Preconditions:

    
  // Body:
  
  // Nothinf to do.

  // Postconditions:

  ensure(!truncated.is_valid());
  ensure(!truncating.is_valid());

  // Exit:

  return; 
}

geometry::kd_truncation_pair::
kd_truncation_pair(const sheaf::scoped_index& xfirst, const sheaf::scoped_index& xsecond)
  : truncated(xfirst), truncating(xsecond)
{
  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  ensure(truncated == xfirst);
  ensure(truncating == xsecond);

  // Exit:

  return; 
}

geometry::kd_truncation_pair::
~kd_truncation_pair()
{  
  // Preconditions:

    
  // Body:
  
  // Nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

bool
geometry::kd_truncation_pair::
operator<(const kd_truncation_pair& xother) const
{
  // cout << endl << "Entering kd_truncation_pair::operator<." << endl;

  // Preconditions:


  // Body:

  bool result =
    ((truncated < xother.truncated)) || 
    ((truncated == xother.truncated) && (truncating < xother.truncating));

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation_pair::operator<." << endl;
  return result;
}

bool
geometry::kd_truncation_pair::
operator==(const kd_truncation_pair& xother) const
{
  // cout << endl << "Entering kd_truncation_pair::operator==." << endl;

  // Preconditions:


  // Body:

  bool result = (truncated == xother.truncated) && (truncating == xother.truncating);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation_pair::operator==." << endl;
  return result;
}

kd_truncation_pair
geometry::kd_truncation_pair::
transpose() const
{
  // cout << endl << "Entering kd_truncation_pair::transpose." << endl;

  // Preconditions:


  // Body:

  kd_truncation_pair result(truncating, truncated);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation_pair::transpose." << endl;
  return result;
}

bool
geometry::kd_truncation_pair::
is_reflexive() const
{
  // cout << endl << "Entering kd_truncation_pair::is_reflexive." << endl;

  // Preconditions:


  // Body:

  bool result = (truncated == truncating);

  // Postconditions:


  // Exit:

  // cout << "Leaving kd_truncation_pair::is_reflexive." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS




// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
 
ostream& 
geometry::
operator << (ostream& xos, const kd_truncation_pair& xn)
{
  // Preconditions:

  // Body:

  xos << xn.truncated << "  " << xn.truncating;

  // Postconditions:

  // Exit:

  return xos;
}
 
