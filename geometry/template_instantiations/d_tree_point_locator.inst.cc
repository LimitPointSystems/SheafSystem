// $RCSfile: d_tree_point_locator.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:31 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_tree_point_locator

#include "d_tree_point_locator.impl.h"

#include "std_iostream.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator<1, 1>;

template class
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator<2, 2>;

template class 
SHEAF_DLL_SPEC 
geometry::d_tree_point_locator<3, 3>;

// template class 
// SHEAF_DLL_SPEC 
// geometry::d_tree_point_locator<4, 4>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <1, 1>(ostream& xos,
				   const geometry::d_tree_point_locator<1, 1>& xtree);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <2, 2>(ostream& xos,
				   const geometry::d_tree_point_locator<2, 2>& xtree);
template 
SHEAF_DLL_SPEC 
ostream& geometry::operator<< <3, 3>(ostream& xos,
				   const geometry::d_tree_point_locator<3, 3>& xtree);
// template 
// SHEAF_DLL_SPEC
// ostream& geometry::operator<< <4, 4>(ostream& xos,
// 				   const geometry::d_tree_point_locator<4, 4>& xtree);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
