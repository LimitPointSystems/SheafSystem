
// $RCSfile: met_e1.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:17 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class met_e1.

#include "met_e1.impl.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// met_e1
//==============================================================================

template class
SHEAF_DLL_SPEC
fiber_bundle::met_e1_row_dofs_type<double>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
ostream& fiber_bundle::operator<< <double>(
    ostream&, const fiber_bundle::met_e1_row_dofs_type<double>&);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//template class
//SHEAF_DLL_SPEC
//fiber_bundle::met_e1_row_dofs_type<float>;

//template
//SHEAF_DLL_SPEC
//ostream& fiber_bundle::operator<<(
//    ostream&, const fiber_bundle::met_e1_row_dofs_type<float>&);

