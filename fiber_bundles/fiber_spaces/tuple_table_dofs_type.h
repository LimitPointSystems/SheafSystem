
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

/// @file
/// Interface for class tuple_table_dofs_type.

#ifndef TUPLE_TABLE_DOFS_TYPE_H
#define TUPLE_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

namespace fiber_bundle
{

using namespace sheaf;

//==============================================================================
// CLASS TUPLE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class tuple_table_dofs_type.
///
class SHEAF_DLL_SPEC tuple_table_dofs_type
{
public:

  ///
  /// Number of factors (components) in tuple.
  ///
  int factor_ct;

};

} // namespace fiber_bundle

#endif // ifndef TUPLE_TABLE_DOFS_TYPE_H
