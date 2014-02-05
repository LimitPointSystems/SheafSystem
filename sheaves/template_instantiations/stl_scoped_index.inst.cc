
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
/// Expliicit instantiations for class stl_scoped_index.

#include "stl_scoped_index.impl.h"

using namespace sheaf; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::stl_scoped_index<sheaf::lexographical_compare_policy>;


template class 
SHEAF_DLL_SPEC
sheaf::stl_scoped_index<sheaf::equivalence_compare_policy>;
