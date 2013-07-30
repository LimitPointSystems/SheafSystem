

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

// Explicit instantiations for class base_space_factory.

#include "base_space_factory.impl.h"

#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"
#include "zone_nodes_block.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::structured_block_1d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::structured_block_2d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::structured_block_3d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::point_block_1d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::point_block_2d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::point_block_3d>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::zone_nodes_block>;

template class 
SHEAF_DLL_SPEC 
fiber_bundle::base_space_factory<fiber_bundle::unstructured_block>;

//==============================================================================
//==============================================================================




