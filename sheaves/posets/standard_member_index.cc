// $RCSfile: standard_member_index.cc,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for standard_member_index facet of namespace sheaf.


#include "standard_member_index.h"

#include "assert_contract.h"
#include "std_string.h"

namespace
{
const int STANDARD_MEMBER_INDEX_CT =
  sheaf::STANDARD_MEMBER_INDEX_END - sheaf::STANDARD_MEMBER_INDEX_BEGIN;
}

///
sheaf::standard_member_index&
sheaf::
operator++(standard_member_index& x)
{
  return x =
           (x == STANDARD_MEMBER_INDEX_END) ?
           STANDARD_MEMBER_INDEX_BEGIN :
           standard_member_index(x+1);
};

///
const string&
sheaf::
standard_member_index_to_name(standard_member_index xpt)
{
  // Preconditions:

  // Body:

  static const string names[STANDARD_MEMBER_INDEX_CT+1] =
    {
      "BOTTOM_INDEX",
      "TOP_INDEX",
      "NOT_A_STANDARD_MEMBER_INDEX" // Must be one more than last std id.
    };

  const string* lresult_ptr = &names[STANDARD_MEMBER_INDEX_CT];

  pod_index_type lpt = xpt;
  if(is_standard_member_index(lpt))
  {
    lresult_ptr = &names[lpt - STANDARD_MEMBER_INDEX_BEGIN];
  }

  const string& result = *lresult_ptr;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::standard_member_index
sheaf::
standard_member_index_from_name(const string& xname)
{
  standard_member_index result = NOT_A_STANDARD_MEMBER_INDEX;
  for(standard_member_index i=STANDARD_MEMBER_INDEX_BEGIN;
      i< STANDARD_MEMBER_INDEX_END;
      ++i)
  {
    if(standard_member_index_to_name(i) == xname)
    {
      result = i;
      break;
    }
  }

  return result;
}

///
sheaf::standard_member_index
sheaf::
standard_member_index_from_index(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  static const standard_member_index prims[STANDARD_MEMBER_INDEX_CT+1] =
    {
      BOTTOM_INDEX,
      TOP_INDEX, // 1
      NOT_A_STANDARD_MEMBER_INDEX
    };

  standard_member_index result = prims[STANDARD_MEMBER_INDEX_CT];
  if(is_standard_member_index(xindex))
  {
    result = prims[xindex];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::
is_standard_member_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (STANDARD_MEMBER_INDEX_BEGIN <= xindex) && (xindex < STANDARD_MEMBER_INDEX_END);

  // Postconditions:

  // Exit

  return result;
}

