

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Expliicit instantiations for class stl_scoped_index.

#include "stl_scoped_index.impl.h"

using namespace sheaf; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::stl_scoped_index<sheaf::lexographical_compare_policy>;


template class 
SHEAF_DLL_SPEC
sheaf::stl_scoped_index<sheaf::equivalence_compare_policy>;
