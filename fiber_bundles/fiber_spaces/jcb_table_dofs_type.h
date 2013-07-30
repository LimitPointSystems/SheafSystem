

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class jcb_table_dofs_type.

#ifndef JCB_TABLE_DOFS_TYPE_H
#define JCB_TABLE_DOFS_TYPE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

namespace fiber_bundle
{
  using namespace sheaf;
  
//==============================================================================
// CLASS JCB_TABLE_DOFS_TYPE_TABLE_DOFS_TYPE
//==============================================================================

///
/// Table dofs type for class jcb.
///
class SHEAF_DLL_SPEC jcb_table_dofs_type
{
public:

  // Order has to conform to order in schema,
  // which has to conform to order in dof id space of top.

  ///
  /// Number of factors (components) in tuple.
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
  /// Dimension of the domain.
  ///
  int dd;

  ///
  /// The path of the domain vector space.
  ///
  c_string domain_path;

  ///
  /// The path of the range vector space.
  ///
  c_string range_path;

  ///
  /// Dimension of the range.
  ///
  int dr;

};


} // namespace fiber_bundle


#endif // ifndef JCB_TABLE_DOFS_TYPE_H
