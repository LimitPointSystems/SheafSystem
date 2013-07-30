
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Definitions for poset type id facet of namespace sheaf.

#include "poset_type.h"

#include "assert_contract.h"
#include "error_message.h"

// =============================================================================
// POSET TYPE FACET
// =============================================================================

///
sheaf::poset_type
sheaf::
poset_type_id(int xi)
{
  poset_type result;

  // Preconditions:

  // Body:

  // Array needed only to convert type
  // from int to enum.

  static const poset_type ltype_ids[] =
    {
      NAMESPACE_POSET_ID,
      PRIMITIVES_POSET_ID,
      PRIMITIVES_POSET_SCHEMA_ID,
      NAMESPACE_POSET_SCHEMA_ID,
      POSET_ID,
      REFINABLE_POSET_ID,
      SHEAVES_NAMESPACE_ID,
      FIBER_BUNDLES_NAMESPACE_ID,
      BASE_SPACE_POSET_ID,
      TUPLE_SPACE_ID,
      VD_SPACE_ID,
      TP_SPACE_ID,
      STP_SPACE_ID,
      ATP_SPACE_ID,
      AT1_SPACE_ID,
      AT0_SPACE_ID,
      GLN_SPACE_ID,
      JCB_SPACE_ID,
      SEC_REP_DESCRIPTOR_POSET_ID,
      SEC_REP_SPACE_ID,
      SEC_TUPLE_SPACE_ID,
      SEC_VD_SPACE_ID,
      SEC_TP_SPACE_ID,
      SEC_STP_SPACE_ID,
      SEC_ATP_SPACE_ID,
      SEC_AT1_SPACE_ID,
      SEC_AT0_SPACE_ID,
      SEC_JCB_SPACE_ID,
      SECTION_SPACE_SCHEMA_POSET_ID,
      BINARY_SECTION_SPACE_SCHEMA_POSET_ID,
      PRODUCT_SECTION_SPACE_SCHEMA_POSET_ID,
      NOT_A_POSET_TYPE // must be last
    }
  ;

  if((0 <= xi) && (xi < NOT_A_POSET_TYPE))
  {
    result = ltype_ids[xi];
  }
  else
  {
    result = NOT_A_POSET_TYPE;
  }

  // Postconditions:

  // Exit

  return result;
}

