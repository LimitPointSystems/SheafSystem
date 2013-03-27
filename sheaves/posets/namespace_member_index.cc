// $RCSfile: namespace_member_index.cc,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:41 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Definitions for namespace_member_index facet of namespace sheaf.


#include "namespace_member_index.h"

#include "assert_contract.h"
#include "std_string.h"

namespace
{
const int NAMESPACE_MEMBER_INDEX_CT =
  sheaf::NAMESPACE_MEMBER_INDEX_END - sheaf::NAMESPACE_MEMBER_INDEX_BEGIN;
}

///
sheaf::namespace_member_index&
sheaf::
operator++(namespace_member_index& x)
{
  return x =
           (x == NAMESPACE_MEMBER_INDEX_END) ?
           NAMESPACE_MEMBER_INDEX_BEGIN :
           namespace_member_index(x+1);
};

///
const string&
sheaf::
namespace_member_index_to_name(namespace_member_index xpt)
{
  // Preconditions:

  // Body:

  static const string names[NAMESPACE_MEMBER_INDEX_CT+1] =
    {
      "PRIMITIVES_SCHEMA_INDEX",
      "NAMESPACE_SCHEMA_INDEX",
      "PRIMITIVES_INDEX",
      "SCHEMA_DEFINITIONS_INDEX",
      "NOT_A_NAMESPACE_MEMBER_INDEX" // Must be one more than last std id.
    };

  const string* lresult_ptr = &names[NAMESPACE_MEMBER_INDEX_CT];

  pod_index_type lpt = xpt;
  if(is_namespace_member_index(lpt))
  {
    lresult_ptr = &names[lpt - NAMESPACE_MEMBER_INDEX_BEGIN];
  }

  const string& result = *lresult_ptr;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::namespace_member_index
sheaf::
namespace_member_index_from_name(const string& xname)
{
  namespace_member_index result = NOT_A_NAMESPACE_MEMBER_INDEX;
  for(namespace_member_index i=NAMESPACE_MEMBER_INDEX_BEGIN;
      i< NAMESPACE_MEMBER_INDEX_END;
      ++i)
  {
    if(namespace_member_index_to_name(i) == xname)
    {
      result = i;
      break;
    }
  }

  return result;
}

///
sheaf::namespace_member_index
sheaf::
namespace_member_index_from_index(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  static const namespace_member_index prims[NAMESPACE_MEMBER_INDEX_CT+1] =
    {
      PRIMITIVES_SCHEMA_INDEX, // 2
      NAMESPACE_SCHEMA_INDEX, // 3
      PRIMITIVES_INDEX, // 4
      SCHEMA_DEFINITIONS_INDEX,//5
      NOT_A_NAMESPACE_MEMBER_INDEX
    };

  namespace_member_index result = prims[NAMESPACE_MEMBER_INDEX_CT];
  if(is_namespace_member_index(xindex))
  {
    result = prims[xindex - NAMESPACE_MEMBER_INDEX_BEGIN];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::
is_namespace_member_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (NAMESPACE_MEMBER_INDEX_BEGIN <= xindex) && (xindex < NAMESPACE_MEMBER_INDEX_END);

  // Postconditions:

  // Exit

  return result;
}

