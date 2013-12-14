
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

// Istantiations for class linkorder_itr<T>.

 
#include "linkorder_itr.impl.h"

#include "zn_to_bool.h"
#include "std_set.h"
#include "std_unordered_set.h"

using namespace std;
using namespace sheaf; // workaround for MS C++ bug.

//==============================================================================
// zn_to_bool
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::
linkorder_itr<sheaf::zn_to_bool>;

//==============================================================================
// set<pod_index_type>
//==============================================================================

template class
SHEAF_DLL_SPEC
sheaf::
linkorder_itr< set<sheaf::pod_index_type> >;

//==============================================================================
// unordered_set<pod_index_type>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::
linkorder_itr< unordered_set<sheaf::pod_index_type> >;
