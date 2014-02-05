
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

// Interface for class SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE

#ifndef SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H
#define SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "namespace_relative_member_index.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// Table dofs type for class section_space_schema_poset.
///
class SHEAF_DLL_SPEC section_space_schema_table_dofs_type
{
public:

  ///
  /// The section representation path.
  ///
  c_string rep_path;

  ///
  /// The base space path.
  ///
  c_string base_space_path;

  ///
  /// The fiber schema space path.
  ///
  c_string fiber_space_path;

};

} // namespace fiber_bundle

#endif // SECTION_SPACE_SCHEMA_TABLE_DOFS_TYPE_H
