

//
// Copyright (c) 2013 Limit Point Systems, Inc.
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




