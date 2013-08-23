
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

// Declarations for namespace_schema_member_index facet of namespace sheaf.

#ifndef NAMESPACE_SCHEMA_MEMBER_INDEX_H
#define NAMESPACE_SCHEMA_MEMBER_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_CLIMITS_H
#include "std_climits.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

///
/// Number of prerequisites ids.
/// Must be consistent with PREREQ_ID_*_INDEX below.
///
const int PREREQ_IDS_UB = 5;

///
/// Ids for namespace poset schema members.
///
enum namespace_schema_member_index
{
  NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN = 2, // Must be same as first std id.
  POINTER_INDEX = 2,
  TYPE_ID_INDEX, // 3
  CLASS_INDEX,  // 4
  PREREQ_ID_0_INDEX, // 5
  PREREQ_ID_1_INDEX, // 6
  PREREQ_ID_2_INDEX, // 7
  PREREQ_ID_3_INDEX, // 8
  PREREQ_ID_4_INDEX, // 9
  IO_INDEX, // 10
  NAMESPACE_SCHEMA_MEMBER_INDEX_END, // Must be one more than last std id.
  NOT_A_NAMESPACE_SCHEMA_MEMBER_INDEX = INT_MAX
};

///
/// The number of dofs defined by the namespace schema.
///
const int NAMESPACE_SCHEMA_DOF_CT =
  NAMESPACE_SCHEMA_MEMBER_INDEX_END - NAMESPACE_SCHEMA_MEMBER_INDEX_BEGIN - 1; // IO_INDEX not a dof.

///
/// Prefix increment operator for namespace_schema_member_index.
///
SHEAF_DLL_SPEC namespace_schema_member_index& operator++(namespace_schema_member_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const string& namespace_schema_member_index_to_name(namespace_schema_member_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC namespace_schema_member_index namespace_schema_member_index_from_name(const string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC namespace_schema_member_index namespace_schema_member_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_namespace_schema_member_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef NAMESPACE_SCHEMA_MEMBER_INDEX_H






