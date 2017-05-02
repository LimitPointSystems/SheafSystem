
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Explicit instantiations for class d_tree_point_locator_node.

#include "SheafSystem/d_tree_point_locator_node.impl.h"

using namespace std;
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
