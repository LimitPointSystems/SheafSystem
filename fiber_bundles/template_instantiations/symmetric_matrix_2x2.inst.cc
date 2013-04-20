

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class symmetric_matrix_2x2.

#include "symmetric_matrix_2x2.impl.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// symmetric_matrix_2x2
//==============================================================================

template class 
SHEAF_DLL_SPEC
fiber_bundle::symmetric_matrix_2x2<double>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& fiber_bundle::operator<< <double>(ostream&,
    const fiber_bundle::symmetric_matrix_2x2<double>&);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

