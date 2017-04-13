
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
/// Instantiations for class template record_map.

#include "SheafSystem/record_map.impl.h"

using namespace std;
using namespace sheaf; // workaround for MS C++ bug.

// =============================================================================
// EXPLICIT INSTANTIATIONS
// =============================================================================

// Instantiation for pod_index_type.

template class 
SHEAF_DLL_SPEC
sheaf::record_map<sheaf::pod_index_type, sheaf::pod_index_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <sheaf::pod_index_type, sheaf::pod_index_type>(ostream& xos, const sheaf::record_map<sheaf::pod_index_type, sheaf::pod_index_type>& xp);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
