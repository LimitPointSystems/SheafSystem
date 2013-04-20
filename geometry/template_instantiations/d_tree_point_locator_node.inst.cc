
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_tree_point_locator_node.

#include "d_tree_point_locator_node.impl.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_node<1, 1>;

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_node<2, 2>;

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator_node<3, 3>;

// template class 
// SHEAF_DLL_SPEC 
// geometry::d_tree_point_locator_node<4, 4>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <1, 1>(ostream& xos,
                   const geometry::d_tree_point_locator_node<1, 1>& xnode);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <2, 2>(ostream& xos,
				   const geometry::d_tree_point_locator_node<2, 2>& xnode);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <3, 3>(ostream& xos,
				   const geometry::d_tree_point_locator_node<3, 3>& xnode);
// template 
// SHEAF_DLL_SPEC 
// ostream& geometry::operator<< <4, 4>(ostream& xos,
// 				   const geometry::d_tree_point_locator_node<4, 4>& xnode);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
