
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Instantiations for class template name_map.

#include "name_map.impl.h"
#include "pod_types.h"

using namespace sheaf; // workaround for MS C++ bug.

template class 
SHEAF_DLL_SPEC
sheaf::name_map<sheaf::pod_index_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
template 
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <sheaf::pod_index_type>(ostream& xos,
                                           const sheaf::name_map<sheaf::pod_index_type>& xmap);
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
size_t
sheaf::deep_size<sheaf::pod_index_type>(const sheaf::name_map<sheaf::pod_index_type>& xp,
                                        bool xinclude_shallow);
