
// $RCSfile: antisymmetric_matrix_3x3.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:17 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class antisymmetric_matrix_3x3.

#include "antisymmetric_matrix_3x3.impl.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// antisymmetric_matrix_3x3
//==============================================================================

template class 
SHEAF_DLL_SPEC
fiber_bundle::antisymmetric_matrix_3x3<double>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& fiber_bundle::operator<< <double>(ostream&,
    const fiber_bundle::antisymmetric_matrix_3x3<double>&);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

