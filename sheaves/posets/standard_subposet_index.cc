// $RCSfile: standard_subposet_index.cc,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for standard_subposet_index facet of namespace sheaf.

#include "standard_subposet_index.h"

#include "assert_contract.h"
#include "std_string.h"

namespace
{
const int STANDARD_SUBPOSET_INDEX_CT =
  sheaf::STANDARD_SUBPOSET_INDEX_END - sheaf::STANDARD_SUBPOSET_INDEX_BEGIN;
}


///
sheaf::standard_subposet_index&
sheaf::
operator++(standard_subposet_index& x)
{
  return x =
           (x == STANDARD_SUBPOSET_INDEX_END) ?
           STANDARD_SUBPOSET_INDEX_BEGIN :
           standard_subposet_index(x+1);
};

///
const string&
sheaf::
standard_subposet_index_to_name(standard_subposet_index xindex)
{
  // Preconditions:

  // Body:

  static const string names[STANDARD_SUBPOSET_INDEX_CT+1] =
    {
      "TOC_INDEX",
      "STANDARD_SUBPOSET_INDEX_PLACEHOLDER_MINUS_1",
      "JIMS_INDEX",
      "WHOLE_INDEX",
      "RESIDENT_INDEX",
      "NOT_A_STANDARD_SUBPOSET_INDEX"
    };

  const string* lresult_ptr = &names[STANDARD_SUBPOSET_INDEX_CT];

  pod_index_type lindex = xindex;
  if(is_standard_subposet_index(lindex))
  {
    lresult_ptr = &names[lindex - STANDARD_SUBPOSET_INDEX_BEGIN];
  }

  const string& result = *lresult_ptr;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::standard_subposet_index
sheaf::
standard_subposet_index_from_name(const string& xname)
{
  standard_subposet_index result = NOT_A_STANDARD_SUBPOSET_INDEX;
  for(standard_subposet_index i=STANDARD_SUBPOSET_INDEX_BEGIN;
      i< STANDARD_SUBPOSET_INDEX_END;
      ++i)
  {
    if(standard_subposet_index_to_name(i) == xname)
    {
      result = i;
      break;
    }
  }

  return result;
}

///
sheaf::standard_subposet_index
sheaf::
standard_subposet_index_from_index(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  static const standard_subposet_index prims[STANDARD_SUBPOSET_INDEX_CT+1] =
    {
      TOC_INDEX,
      STANDARD_SUBPOSET_INDEX_PLACEHOLDER_MINUS_1,
      JIMS_INDEX,
      WHOLE_INDEX,
      RESIDENT_INDEX,
      NOT_A_STANDARD_SUBPOSET_INDEX
    };

  standard_subposet_index result = prims[STANDARD_SUBPOSET_INDEX_CT];
  if(is_standard_subposet_index(xindex))
  {
    result = prims[xindex - STANDARD_SUBPOSET_INDEX_BEGIN];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::
is_standard_subposet_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (STANDARD_SUBPOSET_INDEX_BEGIN <= xindex) &&
    (xindex < STANDARD_SUBPOSET_INDEX_END);

  // Postconditions:

  // Exit

  return result;
}
