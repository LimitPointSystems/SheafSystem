
// $RCSfile: gln.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:17 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class gln.

#include "gln.impl.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// gln
//==============================================================================

template class
SHEAF_DLL_SPEC
fiber_bundle::gln_row_dofs_type<double>;

// template class
// SHEAF_DLL_SPEC
// fiber_bundle::gln_row_dofs_type<float>;

