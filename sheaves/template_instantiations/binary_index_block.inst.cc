
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class template binary_index_block.

#include "binary_index_block.impl.h"

using namespace sheaf; // workaround for MS C++ bug.

// =============================================================================
// EXPLICIT INSTANTIATIONS
// =============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::binary_index_block<int>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::
operator << <int>(ostream& xos, const sheaf::binary_index_block<int>& xblk);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::binary_index_block<double>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::
operator << <double>(ostream& xos, const sheaf::binary_index_block<double>& xblk);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
