
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

// Declarations for standard_version_index facet of namespace sheaf.

#ifndef STANDARD_VERSION_INDEX_H
#define STANDARD_VERSION_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef STD_CLIMITS_H
#include "SheafSystem/std_climits.h"
#endif

#ifndef POD_TYPES_H
#include "SheafSystem/pod_types.h"
#endif

namespace sheaf
{

///
/// Ids for standard poset versions.
///
enum standard_version_index
{
  STANDARD_VERSION_INDEX_BEGIN = -4, // Must be same a first std id.
  CURRENT_MEMBER_VERSION = -4,
  CURRENT_HOST_VERSION, // -3
  COARSEST_COMMON_REFINEMENT_VERSION, // -2
  STANDARD_VERSION_INDEX_END, // Must be one more than last std id.
  NOT_A_STANDARD_VERSION_INDEX = INT_MAX
};

///
/// Prefix increment operator for standard_version_index.
///
SHEAF_DLL_SPEC standard_version_index& operator++(standard_version_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const std::string& standard_version_index_to_name(standard_version_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC standard_version_index standard_version_index_from_name(const std::string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC standard_version_index standard_version_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_standard_version_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef STANDARD_VERSION_INDEX_H






