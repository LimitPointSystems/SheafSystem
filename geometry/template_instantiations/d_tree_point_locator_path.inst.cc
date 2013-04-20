
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_tree_point_locator_path.

#include "d_tree_point_locator_path.impl.h"

//#include "std_iostream.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_path<1, 1>;

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_path<2, 2>;

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_path<3, 3>;

// template class 
// SHEAF_DLL_SPEC 
// geometry::d_tree_point_locator_path<4, 4>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <1, 1>(ostream &os,
				   const geometry::d_tree_point_locator_path<1, 1>& xpath);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <2, 2>(ostream &os,
				   const geometry::d_tree_point_locator_path<2, 2>& xpath);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <3, 3>(ostream &os,
				   const geometry::d_tree_point_locator_path<3, 3>& xpath);
// template 
// SHEAF_DLL_SPEC 
// ostream& geometry::operator<< <4, 4>(ostream &os,
// 				   const geometry::d_tree_point_locator_path<4, 4>& xpath);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
