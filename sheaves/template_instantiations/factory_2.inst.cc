
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class factory_2.

#include "factory_2.impl.h"

#include "crg_interval.h"
#include "explicit_index_space_state.h"
#include "index_space_interval.h"

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
