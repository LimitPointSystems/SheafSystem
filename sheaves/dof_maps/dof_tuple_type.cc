
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

// Definitions for class dof_tuple_type

#include "dof_tuple_type.h"

#include "assert_contract.h"
#include "error_message.h"

using namespace std;

// =============================================================================
// DOF TUPLE TYPES FACET
// =============================================================================

///
const std::string&
sheaf::
dof_tuple_type_to_name(dof_tuple_type xdt)
{
  // Preconditions:

  // Body:

  static const string names[NOT_A_DOF_TUPLE_TYPE+1] =
    {
      "NAMESPACE_POSET_DOF_TUPLE_ID",
      "PRIMITIVES_POSET_DOF_TUPLE_ID",
      "ARRAY_POSET_DOF_TUPLE_ID",
      "ARRAY_SECTION_DOF_TUPLE_ID",
      "SPARSE_SECTOPM_DOF_TUPLE_ID",
      "NOT_A_DOF_TUPLE_TYPE"
    };

  const string& result = names[xdt];

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
sheaf::dof_tuple_type
sheaf::dof_tuple_type_from_name(const std::string& xname)
{
  dof_tuple_type result;

  // Preconditions:


  // Body:

  /// @hack The following if block is crude, but there doesn't seem to be
  /// any substantially better way to do it. The language doesn't support
  /// iteration over enums and integral values, except compile-time constants,
  /// can not be converted to enums, so searching an array of names is as
  /// at least as clumsy as this construction. STL maps would be clumsy to initialize.

  if(xname == "NAMESPACE_POSET_DOF_TUPLE_ID")
  {
    result = NAMESPACE_POSET_DOF_TUPLE_ID;
  }
  else if(xname == "PRIMITIVES_POSET_DOF_TUPLE_ID")
  {
    result = PRIMITIVES_POSET_DOF_TUPLE_ID;
  }
  else if( xname == "ARRAY_POSET_DOF_TUPLE_ID")
  {
    result = ARRAY_POSET_DOF_TUPLE_ID;
  }
  else if( xname == "ARRAY_SECTION_DOF_TUPLE_ID")
  {
    result = ARRAY_SECTION_DOF_TUPLE_ID;
  }
  else if( xname == "SPARSE_SECTION_DOF_TUPLE_ID")
  {
    result = SPARSE_SECTION_DOF_TUPLE_ID;
  }
  else
  {
    result = NOT_A_DOF_TUPLE_TYPE;
  }

  // Postconditions:


  // Exit:

  return result;
}

///
sheaf::dof_tuple_type
sheaf::
dof_tuple_type_id(int xi)
{
  dof_tuple_type result;

  // Preconditions:

  // Body:

  static const dof_tuple_type ltype_ids[] =
    {
      NAMESPACE_POSET_DOF_TUPLE_ID,
      PRIMITIVES_POSET_DOF_TUPLE_ID,
      ARRAY_POSET_DOF_TUPLE_ID,
      ARRAY_SECTION_DOF_TUPLE_ID,
      SPARSE_SECTION_DOF_TUPLE_ID,
      NOT_A_DOF_TUPLE_TYPE // must be last
    }
    ;

  if((0 <= xi) && (xi < NOT_A_DOF_TUPLE_TYPE))
  {
    result = ltype_ids[xi];
  }
  else
  {
    result = NOT_A_DOF_TUPLE_TYPE;
  }

  // Postconditions:

  // Exit

  return result;
}



///
std::ostream&
sheaf::
operator<<(std::ostream& os, dof_tuple_type xdt)
{
  // Preconditions:


  // Body:

  os << dof_tuple_type_to_name(xdt);

  // Postconditions:


  // Exit:

  return os;
}

///
std::istream&
sheaf::
operator>>(std::istream& is, dof_tuple_type& xdt)
{
  // Preconditions:


  // Body:

  string ltmp;
  is >> ltmp;
  xdt = dof_tuple_type_from_name(ltmp);

  // Postconditions:


  // Exit:

  return is;
}

