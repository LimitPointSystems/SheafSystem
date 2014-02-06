
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

// Declarations for standard_dof_tuple_index facet of namespace sheaf.

#ifndef STANDARD_DOF_TUPLE_INDEX_H
#define STANDARD_DOF_TUPLE_INDEX_H

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

//
// EMPTY_DOF_TUPLE_INDEX is the index of the (unique) empty dof map,
// i.e. the dof map with dof_ct() == 0.
//
// Note on restriction to BOTTOM:
// If the schema is restricted to BOTTOM, then the
// dof tuple is empty. As with the empty set and the null
// vector, we treat the empty dof tuple as unique. So all
// members of a poset on the BOTTOM schema share the same
// dof tuple, which contains no dofs. The dof tuple id for
// the empty dof tuple is 0. This structure is the same for
// both internal and external posets.
//

///
/// Ids for standard dof tuples.
///
enum standard_dof_tuple_index
{
  STANDARD_DOF_TUPLE_INDEX_BEGIN = 0, // Must be same a first std id.
  EMPTY_DOF_TUPLE_INDEX = 0,
  STANDARD_DOF_TUPLE_INDEX_END, // Must be one more than last std id.
  NOT_A_STANDARD_DOF_TUPLE_INDEX = INT_MAX
};

///
/// Prefix increment operator for standard_dof_tuple_index.
///
SHEAF_DLL_SPEC standard_dof_tuple_index& operator++(standard_dof_tuple_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const std::string& standard_dof_tuple_index_to_name(standard_dof_tuple_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC standard_dof_tuple_index standard_dof_tuple_index_from_name(const std::string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC standard_dof_tuple_index standard_dof_tuple_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_standard_dof_tuple_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef STANDARD_DOF_TUPLE_INDEX_H






