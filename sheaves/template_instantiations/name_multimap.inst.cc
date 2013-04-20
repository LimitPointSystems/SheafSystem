
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class name_multimap<index_type> is in name_multimap_impl.h

#include "name_multimap.impl.h"
#include "scoped_index.h"

using namespace sheaf; // workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

// Instantiations for pod_index_type

template class 
SHEAF_DLL_SPEC
sheaf::name_multimap<sheaf::pod_index_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <sheaf::pod_index_type>(ostream& xos,
                                           const sheaf::name_multimap<sheaf::pod_index_type>& xmap);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::pod_index_type>(const sheaf::name_multimap<sheaf::pod_index_type>& xp,
                                        bool xinclude_shallow);

