
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

// Definitions for primitives_schema_member_index facet of namespace sheaf.


#include "SheafSystem/primitives_schema_member_index.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_string.h"

using namespace std;

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
const std::string&
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
primitives_schema_member_index_from_name(const std::string& xname)
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

