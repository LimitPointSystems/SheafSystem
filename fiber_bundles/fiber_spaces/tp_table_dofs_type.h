
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
/// Interface for class tp_table_dofs_type

#ifndef TP_TABLE_DOFS_TYPE_H
#define TP_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "SheafSystem/fiber_bundle.h"
#endif

namespace fiber_bundle
{
  
//==============================================================================
// CLASS TP_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class tp.
///
class SHEAF_DLL_SPEC tp_table_dofs_type
{
public:

  ///
  ///  Number of factors (components) in tuple.
  ///
  int factor_ct;

  ///
  /// Dimension of this as a vector space.
  ///
  int d;

  ///
  /// The path of the underlying scalar space.
  ///
  c_string scalar_space_path;

  ///
  /// The degree of the tensor; 
  /// the sum of the contravariant and covariant degrees.
  int p;

  ///
  /// Dimension of the underlying vector space.
  ///
  int dd;

  ///
  /// The path of the underlying vector space.
  ///
  c_string vector_space_path;

};


} // namespace fiber_bundle


#endif // ifndef TP_TABLE_DOFS_TYPE_H
