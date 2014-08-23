
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
/// Explicit instantiations for class field_factory_2.

#include "ComLimitPoint/fields/field_factory_2.impl.h"

#include "ComLimitPoint/fiber_bundle/sec_at0.h"
#include "ComLimitPoint/fiber_bundle/sec_e1.h"
#include "ComLimitPoint/fiber_bundle/sec_e2.h"
#include "ComLimitPoint/fiber_bundle/sec_e3.h"
#include "ComLimitPoint/fiber_bundle/sec_e1_uniform.h"
#include "ComLimitPoint/fiber_bundle/sec_e2_uniform.h"
#include "ComLimitPoint/fiber_bundle/sec_e3_uniform.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/point_block_1d.h"
#include "ComLimitPoint/fiber_bundle/point_block_2d.h"
#include "ComLimitPoint/fiber_bundle/point_block_3d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_1d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_2d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_3d.h"
#include "ComLimitPoint/fiber_bundle/unstructured_block.h"

#include "ComLimitPoint/fiber_bundle/homogeneous_block.h"

#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/poset_path.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

#include "ComLimitPoint/fiber_bundle/sec_tuple.impl.h"
#include "ComLimitPoint/fiber_bundle/sec_tuple_space.impl.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.


//==============================================================================
// EXPLICIT_INSTANTIATIONS
//==============================================================================

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_at0,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_at0,
                        fiber_bundle::point_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1_uniform,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_at0,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_at0,
                        fiber_bundle::point_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2_uniform,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_at0,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_3d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_at0,
                        fiber_bundle::point_block_3d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3_uniform,
                        fiber_bundle::sec_at0,
                        fiber_bundle::structured_block_3d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_e1,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1,
                        fiber_bundle::sec_e1,
                        fiber_bundle::point_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e1_uniform,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_1d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_e1,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2,
                        fiber_bundle::sec_e1,
                        fiber_bundle::point_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e2_uniform,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_2d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_e1,
                        fiber_bundle::unstructured_block>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_3d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3,
                        fiber_bundle::sec_e1,
                        fiber_bundle::point_block_3d>;

template class
SHEAF_DLL_SPEC 
fields::field_factory_2<fiber_bundle::sec_e3_uniform,
                        fiber_bundle::sec_e1,
                        fiber_bundle::structured_block_3d>;

template
SHEAF_DLL_SPEC 
void
fields::make_base_space<fiber_bundle::base_space_member>(
    fiber_bundle::fiber_bundles_namespace& xns,
    const sheaf::poset_path& xbase_path,
    const sheaf::wsv_block<int>& xbase_index_ubs,
    sheaf::poset_path& xlocal_cell_prototype_path,
    fiber_bundle::base_space_member& xresult);

template
SHEAF_DLL_SPEC 
void
fields::make_base_space<fiber_bundle::homogeneous_block>(
    fiber_bundle::fiber_bundles_namespace& xns,
    const sheaf::poset_path& xbase_path,
    const sheaf::wsv_block<int>& xbase_index_ubs,
    sheaf::poset_path& xlocal_cell_prototype_path,
    fiber_bundle::homogeneous_block& xresult);
