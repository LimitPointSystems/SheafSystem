// $RCSfile: field_factory_2.inst.cc,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:29 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class field_factory_2.

#include "field_factory_2.impl.h"

#include "sec_at0.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_e1_uniform.h"
#include "sec_e2_uniform.h"
#include "sec_e3_uniform.h"
#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"

#include "homogeneous_block.h"

#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "wsv_block.h"

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
