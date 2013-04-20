
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_array_point_locator.


#include "d_array_point_locator.impl.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<1, 1>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<2, 2>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 1>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 2>;

template class
SHEAF_DLL_SPEC
geometry::d_array_point_locator<3, 3>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <1, 1>(ostream& xos,
                            const geometry::d_array_point_locator<1, 1>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <2, 2>(ostream& xos,
                            const geometry::d_array_point_locator<2, 2>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 1>(ostream& xos,
                            const geometry::d_array_point_locator<3, 1>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 2>(ostream& xos,
                            const geometry::d_array_point_locator<3, 2>& xpl);

template
SHEAF_DLL_SPEC
ostream&
geometry::operator<< <3, 3>(ostream& xos,
                            const geometry::d_array_point_locator<3, 3>& xpl);


#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
