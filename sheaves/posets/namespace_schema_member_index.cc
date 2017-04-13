
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Definitions for namespace_schema_member_index facet of namespace sheaf.


#include "SheafSystem/namespace_schema_member_index.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_string.h"

using namespace std;

namespace
{
const int NAMESPACE_SCHEMA_MEMBER_INDEX_CT =
  sheaf::NAMESPACE_SCHEMA_MEMBER_INDEX_END - sheaf::NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN;
}

///
sheaf::namespace_schema_member_index&
sheaf::
operator++(namespace_schema_member_index& x)
{
  return x =
           (x == NAMESPACE_SCHEMA_MEMBER_INDEX_END) ?
           NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN :
           namespace_schema_member_index(x+1);
};

///
const std::string&
sheaf::
namespace_schema_member_index_to_name(namespace_schema_member_index xpt)
{
  // Preconditions:

  // Body:

  static const string names[NAMESPACE_SCHEMA_MEMBER_INDEX_CT+1] =
    {
      "POINTER_INDEX",
      "TYPE_ID_INDEX",
      "CLASS_INDEX",
      "PREREQ_ID_0_INDEX",
      "PREREQ_ID_1_INDEX",
      "PREREQ_ID_2_INDEX",
      "PREREQ_ID_3_INDEX",
      "PREREQ_ID_4_INDEX",
      "IO_INDEX",
      "NOT_A_NAMESPACE_SCHEMA_MEMBER_INDEX"
    };

  const string* lresult_ptr = &names[NAMESPACE_SCHEMA_MEMBER_INDEX_CT];

  pod_index_type lpt = xpt;
  if(is_namespace_schema_member_index(lpt))
  {
    lresult_ptr = &names[lpt - NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN];
  }

  const string& result = *lresult_ptr;

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::namespace_schema_member_index
sheaf::
namespace_schema_member_index_from_name(const std::string& xname)
{
  namespace_schema_member_index result = NOT_A_NAMESPACE_SCHEMA_MEMBER_INDEX;
  for(namespace_schema_member_index i=NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN;
      i< NAMESPACE_SCHEMA_MEMBER_INDEX_END;
      ++i)
  {
    if(namespace_schema_member_index_to_name(i) == xname)
    {
      result = i;
      break;
    }
  }

  return result;
}

///
sheaf::namespace_schema_member_index
sheaf::
namespace_schema_member_index_from_index(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  static const namespace_schema_member_index prims[NAMESPACE_SCHEMA_MEMBER_INDEX_CT+1] =
    {
      POINTER_INDEX,
      TYPE_ID_INDEX,
      CLASS_INDEX,
      PREREQ_ID_0_INDEX,
      PREREQ_ID_1_INDEX,
      PREREQ_ID_2_INDEX,
      PREREQ_ID_3_INDEX,
      PREREQ_ID_4_INDEX,
      IO_INDEX,
      NOT_A_NAMESPACE_SCHEMA_MEMBER_INDEX
    };

  namespace_schema_member_index result = prims[NAMESPACE_SCHEMA_MEMBER_INDEX_CT];
  if(is_namespace_schema_member_index(xindex))
  {
    result = prims[xindex - NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN];
  }

  // Postconditions:

  // Exit:

  return result;
}

///
bool
sheaf::
is_namespace_schema_member_index(pod_index_type xindex)
{
  bool result;

  // Preconditions:

  // Body:

  result =
    (NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN <= xindex) && (xindex < NAMESPACE_SCHEMA_MEMBER_INDEX_END);

  // Postconditions:

  // Exit

  return result;
}

