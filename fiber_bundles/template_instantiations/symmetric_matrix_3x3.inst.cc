
// $RCSfile: symmetric_matrix_3x3.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:18 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class symmetric_matrix_3x3.

#include "symmetric_matrix_3x3.impl.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// symmetric_matrix_3x3
//==============================================================================

template class 
SHEAF_DLL_SPEC
fiber_bundle::symmetric_matrix_3x3<double>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& fiber_bundle::operator<< <double>(ostream&,
    const fiber_bundle::symmetric_matrix_3x3<double>&);

template
SHEAF_DLL_SPEC
void fiber_bundle::jacobi_transformation<double>(
  const fiber_bundle::symmetric_matrix_3x3<double>& xm,
  fiber_bundle::general_matrix_3x3<double>& xeigenvectors,
  double xeigenvalues[3]);

template 
SHEAF_DLL_SPEC
void fiber_bundle::jacobi_transformation<double>(
    const fiber_bundle::symmetric_matrix_3x3<double>& xm,
	fiber_bundle::general_matrix_3x3<double>& xeigenvectors,
	fiber_bundle::symmetric_matrix_3x3<double>& xdiagonal);

template 
SHEAF_DLL_SPEC
void fiber_bundle::sort_eigenvalues<double>(
    fiber_bundle::general_matrix_3x3<double>& xeigenvectors,
	double xeigenvalues[3]);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

