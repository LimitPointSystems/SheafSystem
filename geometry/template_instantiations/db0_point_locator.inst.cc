
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Instantiations for class db0_point_locator.

#include "db0_point_locator.impl.h"

#include "block.impl.h"

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


