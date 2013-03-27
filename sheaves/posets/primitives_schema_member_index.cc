// $RCSfile: primitives_schema_member_index.cc,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:43 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for primitives_schema_member_index facet of namespace sheaf.


#include "primitives_schema_member_index.h"

#include "assert_contract.h"
#include "std_string.h"

namespace
{
const int PRIMITIVES_SCHEMA_MEMBER_INDEX_CT =
  sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_END - sheaf::PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN;
}

///
sheaf::primitives_schema_member_index&
sheaf::
operator++(primitives_schema_member_index& x)
{
  return x =
           (x == PRIMITIVES_SCHEMA_MEMBER_INDEX_END) ?
           PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN :
           primitives_schema_member_index(x+1);
};

///
const string&
sheaf::
primitives_schema_member_index_to_name(primitives_schema_member_index xpt)
{
  // Preconditions:

  // Body:

  static const string names[PRIMITIVES_SCHEMA_MEMBER_INDEX_CT+1] =
    {
      "SIZE_INDEX",
      "ALIGNMENT_INDEX",
      "INDEX_INDEX",
      "NOT_A_PRIMITIVES_SCHEMA_MEMBER_INDEX" // Must be one more than last std id.
    };

  const string* lresult_ptr = &names[PRIMITIVES_SCHEMA_MEMBER_INDEX_CT];

  pod_index_type lpt = xpt;
  if(is_primitives_schema_member_index(lpt))
  {
    lresult_ptr = &names[lpt - PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN];
  }

  const string& result = *lresult_ptr;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::primitives_schema_member_index
sheaf::
primitives_schema_member_index_from_name(const string& xname)
{
  primitives_schema_member_index result = NOT_A_PRIMITIVES_SCHEMA_MEMBER_INDEX;
  for(primitives_schema_member_index i=PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN;
      i< PRIMITIVES_SCHEMA_MEMBER_INDEX_END;
      ++i)
  {
    if(primitives_schema_member_index_to_name(i) == xname)
    {
      result = i;
      break;
    }
  }

  return result;
}

///
sheaf::primitives_schema_member_index
sheaf::
primitives_schema_member_index_from_index(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  static const primitives_schema_member_index prims[PRIMITIVES_SCHEMA_MEMBER_INDEX_CT+1] =
    {
      SIZE_INDEX,
      ALIGNMENT_INDEX,
      INDEX_INDEX,
      NOT_A_PRIMITIVES_SCHEMA_MEMBER_INDEX
    };

  primitives_schema_member_index result = prims[PRIMITIVES_SCHEMA_MEMBER_INDEX_CT];
  if(is_primitives_schema_member_index(xindex))
  {
    result = prims[xindex - PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::
is_primitives_schema_member_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (PRIMITIVES_SCHEMA_MEMBER_INDEX_BEGIN <= xindex) && (xindex < PRIMITIVES_SCHEMA_MEMBER_INDEX_END);

  // Postconditions:

  // Exit

  return result;
}

