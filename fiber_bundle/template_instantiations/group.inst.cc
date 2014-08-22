
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//

// Explicit_instantiations for class group.

#include "group.impl.h"

#include "ComLimitPoint/fiber_bundle/gl2.h"
#include "ComLimitPoint/fiber_bundle/gl3.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR HOST FACTORY FACET
//==============================================================================

// gl2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::group::
standard_host_path<fiber_bundle::gl2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::group::
standard_host_is_available<fiber_bundle::gl2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// gl3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::group::
standard_host_path<fiber_bundle::gl3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::group::
standard_host_is_available<fiber_bundle::gl3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
