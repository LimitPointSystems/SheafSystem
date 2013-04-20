
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class factory.

#include "factory.impl.h"

#include "eval_family.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

template class 
SHEAF_DLL_SPEC
sheaf::factory<fiber_bundle::eval_family>;
