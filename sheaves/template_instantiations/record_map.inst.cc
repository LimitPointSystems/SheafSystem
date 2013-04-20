

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Instantiations for class template record_map.

#include "record_map.impl.h"

using namespace sheaf; // workaround for MS C++ bug.

// =============================================================================
// EXPLICIT INSTANTIATIONS
// =============================================================================

// Instantiation for pod_index_type.

template class 
SHEAF_DLL_SPEC
sheaf::record_map<sheaf::pod_index_type, sheaf::pod_index_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <sheaf::pod_index_type, sheaf::pod_index_type>(ostream& xos, const sheaf::record_map<sheaf::pod_index_type, sheaf::pod_index_type>& xp);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
