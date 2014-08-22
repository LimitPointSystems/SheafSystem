
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

// Implementation for class factory.

#include "ComLimitPoint/sheaf/factory.impl.h"

#include "field_refinement_policy.h"
#include "field_refiner_family.h"

//#include "barycentric_refiner_family.h"
//#include "edge_centered_refiner_family.h"
//#include "zone_centered_refiner_family.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================


template class
SHEAF_DLL_SPEC
sheaf::factory<fields::field_refinement_policy>;


template class
SHEAF_DLL_SPEC
sheaf::factory<fields::field_refiner_family>;

// template class
// SHEAF_DLL_SPEC
// sheaf::block<fields::barycentric_refiner_family*>;

///@issue The following instantiation does not compile because there is
///         no method:
///             barycentric_refiner_family::initialize(namespace_poset&).
///template class sheaf::factory<fields::barycentric_refiner_family>;

// template class sheaf::block<fields::edge_centered_refiner_family*>;

///@todo Add comment for why the following instantiation does not work.

//template class sheaf::factory<fields::edge_centered_refiner_family>;

// template class sheaf::block<fields::zone_centered_refiner_family*>;

///@issue The following instantiation does not compile because there is
///         no method:
///             zone_centered_refiner_family::initialize(namespace_poset&).
///template class sheaf::factory<fields::zone_centered_refiner_family>;

