
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Instantiations for class template d_bin_coordinates

#include "d_bin_coordinates.impl.h"

#include "std_iostream.h"

using namespace geometry; // Workaround for MS C++ bug.


//=============================================================================
// EXPLICIT INSTANTIATIONS FOR D_BIN_COORDINATES
//=============================================================================

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<1, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<2, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<3, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<4, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<1, 1>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<3, 1>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<2, 2>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<3, 2>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<3, 3>;

template class 
SHEAF_DLL_SPEC
geometry::d_bin_coordinates<4, 4>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <1, 0>(ostream& xos, const geometry::d_bin_coordinates<1, 0>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <2, 0>(ostream& xos, const  geometry::d_bin_coordinates<2, 0>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 0>(ostream& xos, const  geometry::d_bin_coordinates<3, 0>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <4, 0>(ostream& xos, const  geometry::d_bin_coordinates<4, 0>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <1, 1>(ostream& xos, const  geometry::d_bin_coordinates<1, 1>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <2, 2>(ostream& xos, const  geometry::d_bin_coordinates<2, 2>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 1>(ostream& xos, const  geometry::d_bin_coordinates<3, 1>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 2>(ostream& xos, const  geometry::d_bin_coordinates<3, 2>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 3>(ostream& xos, const  geometry::d_bin_coordinates<3, 3>& xcoords);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <4, 4>(ostream& xos, const  geometry::d_bin_coordinates<4, 4>& xcoords);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
