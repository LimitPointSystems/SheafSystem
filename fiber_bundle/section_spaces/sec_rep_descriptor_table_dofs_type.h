
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

// Interface for class SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE

#ifndef SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
#define SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_RELATIVE_MEMBER_INDEX_H
#include "ComLimitPoint/sheaf/namespace_relative_member_index.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

///
/// Table dofs type for class sec_rep_descriptor_poset.
///
class SHEAF_DLL_SPEC sec_rep_descriptor_table_dofs_type
{
public:

  ///
  /// The base space prototypes path.
  ///
  c_string prototypes_path;

};

} // namespace fiber_bundle

#endif // SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
