
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
/// Interface for class gln_table_dofs_type

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_GLN_TABLE_DOFS_TYPE_H
#define COM_LIMITPOINT_FIBER_BUNDLE_GLN_TABLE_DOFS_TYPE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle.h"
#endif
  
namespace fiber_bundle
{  
  
//==============================================================================
// CLASS GLN_TABLE_DOFS_TYPE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs of gln.
///
class SHEAF_DLL_SPEC gln_table_dofs_type
{
public:

  ///
  /// The path of the underlying scalar space.
  ///
  c_string scalar_space_path;

  ///
  /// The path of the underlying vector space.
  ///
  c_string vector_space_path;

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n;

};



} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_GLN_TABLE_DOFS_TYPE_H






