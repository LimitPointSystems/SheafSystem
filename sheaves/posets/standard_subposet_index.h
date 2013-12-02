
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

// Declarations for standard_subposet_index facet of namespace sheaf.

#ifndef STANDARD_SUBPOSET_INDEX_H
#define STANDARD_SUBPOSET_INDEX_H

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
/// Ids for standard subposets.
///
enum standard_subposet_index
{
  STANDARD_SUBPOSET_INDEX_BEGIN = -2, // Must be first
  TOC_INDEX = -2,
  STANDARD_SUBPOSET_INDEX_PLACEHOLDER_MINUS_1, // -1
  JIMS_INDEX, // 0

  /// @issue 1 is in fact the index of the coarsest common refinement whole.
  /// It is whole().index() only for posets which are not descendants of
  /// refinable_poset. See poset_state_handle::initialize_standard_subposets
  /// and refinable_poset::initialize_standard_subposets.

  WHOLE_INDEX, // 1
  RESIDENT_INDEX, //2
  STANDARD_SUBPOSET_INDEX_END, // Must be one more than last std id.
  NOT_A_STANDARD_SUBPOSET_INDEX = INT_MAX
};

///
/// Prefix increment operator for standard_subposet_index.
///
SHEAF_DLL_SPEC standard_subposet_index& operator++(standard_subposet_index& x);

///
/// The name of the enumerator xpt.
///
SHEAF_DLL_SPEC const std::string& standard_subposet_index_to_name(standard_subposet_index xpt);

///
/// The enumerator with name xname.
///
SHEAF_DLL_SPEC standard_subposet_index standard_subposet_index_from_name(const std::string& xname);

///
/// The enumerator corresponding to primitive index xindex.
///
SHEAF_DLL_SPEC standard_subposet_index standard_subposet_index_from_index(pod_index_type xindex);

///
/// True if xindex is a valid primitive index.
///
SHEAF_DLL_SPEC bool is_standard_subposet_index(pod_index_type xindex);

} // namespace sheaf

#endif // ifndef STANDARD_SUBPOSET_INDEX_H






