
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
/// Instantiations for class db0_point_locator.

#include "db0_point_locator.impl.h"

#include "ComLimitPoint/sheaf/block.impl.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

template class 
SHEAF_DLL_SPEC 
geometry::db0_point_locator<1>;

template class 
SHEAF_DLL_SPEC 
geometry::db0_point_locator<2>;

template class 
SHEAF_DLL_SPEC 
geometry::db0_point_locator<3>;



