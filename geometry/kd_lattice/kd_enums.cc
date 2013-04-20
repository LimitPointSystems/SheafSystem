

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for declarations in kd_enums.h

#include "kd_enums.h"
#include "assert_contract.h"

using namespace geometry; // Workaround for MS C++ bug.

// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
geometry::kd_alignment
geometry::
alignment(int xi)
{
  // cout << endl << "Entering geometry::alignment." << endl;

  // Preconditions:


  // Body:

  static const kd_alignment lalignment[NOT_AXIS_ALIGNED] =
    {
      X_AXIS_ALIGNED,
      Y_AXIS_ALIGNED,
      Z_AXIS_ALIGNED
    };
  
  kd_alignment result = ((0<=xi) && (xi < NOT_AXIS_ALIGNED)) ? lalignment[xi] : NOT_AXIS_ALIGNED;

  // Postconditions:


  // Exit:

  // cout << "Leaving geometry::alignment." << endl;
  return result;
}
 
geometry::kd_alignment
geometry::
other_alignment(kd_alignment xa0, kd_alignment xa1)
{
  // cout << endl << "Entering geometry::other_alignment." << endl;

  // Preconditions:

  require(xa0 != NOT_AXIS_ALIGNED);
  require(xa1 != NOT_AXIS_ALIGNED);
  require(xa0 != xa1);
  
  // Body:

  kd_alignment result = alignment(other_int_alignment(xa0, xa1));

  // Postconditions:

  ensure(result != NOT_AXIS_ALIGNED);
  
  // Exit:

  // cout << "Leaving geometry::other_alignment." << endl;
  return result;
}


ostream& 
geometry::
operator << (ostream& xos, const kd_alignment& xn)
{
  // Preconditions:

  // Body:

  switch(xn)
  {
    case X_AXIS_ALIGNED:
      xos << "X_AXIS_ALIGNED";
      break;
    case Y_AXIS_ALIGNED:
      xos << "Y_AXIS_ALIGNED";
      break;
    case Z_AXIS_ALIGNED:
      xos << "Z_AXIS_ALIGNED";
      break;
    case NOT_AXIS_ALIGNED:
      xos << "NOT_AXIS_ALIGNED";
      break;
    default:
      xos << "NOT_AXIS_ALIGNED";
      break;
  }
  
      
  // Postconditions:

  // Exit:

  return xos;
}


  
