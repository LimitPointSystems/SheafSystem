
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

// Implementation for class factory_2.

#include "ComLimitPoint/sheaf/factory_2.impl.h"

#include "ComLimitPoint/sheaf/crg_interval.h"
#include "ComLimitPoint/sheaf/explicit_index_space_state.h"
#include "ComLimitPoint/sheaf/index_space_interval.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

template class 
SHEAF_DLL_SPEC
sheaf::factory_2<sheaf::explicit_index_space_state>;

template class 
SHEAF_DLL_SPEC
sheaf::factory_2<sheaf::index_space_interval>;
