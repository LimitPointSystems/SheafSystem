
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

// Implementation for class template block

#include "ComLimitPoint/geometry/geometry.h"

#include "ComLimitPoint/sheaf/auto_block.impl.h"
#include "ComLimitPoint/sheaf/block.impl.h"

#include "ComLimitPoint/geometry/d_bounding_box.impl.h"
#include "ComLimitPoint/geometry/d_tree_point_locator_node.impl.h"
#include "ComLimitPoint/geometry/db0_point_locator.impl.h"

//#include "kd_plane.h"
//#include "kd_bounding_box.h"

#include "ComLimitPoint/sheaf/singly_linked_list.h"
#include "std_utility.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================



//==============================================================================
// block<d_tree_point_locator_node<DC, DB> >
//==============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block< geometry::d_tree_point_locator_node<1, 1> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_tree_point_locator_node<1, 1> >(const sheaf::block< geometry::d_tree_point_locator_node<1, 1> >& xblk1, const sheaf::block< geometry::d_tree_point_locator_node<1, 1> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_tree_point_locator_node<1, 1> >(ostream& xos, const sheaf::block< geometry::d_tree_point_locator_node<1, 1> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_tree_point_locator_node<1, 1> >(const sheaf::block< geometry::d_tree_point_locator_node<1, 1> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::block< geometry::d_tree_point_locator_node<2, 2> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_tree_point_locator_node<2, 2> >(const sheaf::block< geometry::d_tree_point_locator_node<2, 2> >& xblk1, const sheaf::block< geometry::d_tree_point_locator_node<2, 2> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_tree_point_locator_node<2, 2> >(ostream& xos, const sheaf::block< geometry::d_tree_point_locator_node<2, 2> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_tree_point_locator_node<2, 2> >(const sheaf::block< geometry::d_tree_point_locator_node<2, 2> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC 
sheaf::block< geometry::d_tree_point_locator_node<3, 3> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_tree_point_locator_node<3, 3> >(const sheaf::block< geometry::d_tree_point_locator_node<3, 3> >& xblk1, const sheaf::block< geometry::d_tree_point_locator_node<3, 3> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_tree_point_locator_node<3, 3> >(ostream& xos, const sheaf::block< geometry::d_tree_point_locator_node<3, 3> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_tree_point_locator_node<3, 3> >(const sheaf::block< geometry::d_tree_point_locator_node<3, 3> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

// template class 
// SHEAF_DLL_SPEC 
// sheaf::block< geometry::d_tree_point_locator_node<4, 4> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < geometry::d_tree_point_locator_node<4, 4> >(const sheaf::block< geometry::d_tree_point_locator_node<4, 4> >& xblk1, const sheaf::block< geometry::d_tree_point_locator_node<4, 4> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < geometry::d_tree_point_locator_node<4, 4> >(ostream& xos, const sheaf::block< geometry::d_tree_point_locator_node<4, 4> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_tree_point_locator_node<4, 4> >(const sheaf::block< geometry::d_tree_point_locator_node<4, 4> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<geometry::d_bounding_box<DC, DB> >
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<1, 0> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<1, 0> >(const sheaf::block< geometry::d_bounding_box<1, 0> >& xblk1, const sheaf::block< geometry::d_bounding_box<1, 0> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<1, 0> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<1, 0> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<1, 0> >(const sheaf::block< geometry::d_bounding_box<1, 0> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<1, 1> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<1, 1> >(const sheaf::block< geometry::d_bounding_box<1, 1> >& xblk1, const sheaf::block< geometry::d_bounding_box<1, 1> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<1, 1> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<1, 1> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<1, 1> >(const sheaf::block< geometry::d_bounding_box<1, 1> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<2, 0> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<2, 0> >(const sheaf::block< geometry::d_bounding_box<2, 0> >& xblk1, const sheaf::block< geometry::d_bounding_box<2, 0> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<2, 0> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<2, 0> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<2, 0> >(const sheaf::block< geometry::d_bounding_box<2, 0> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<2, 2> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<2, 2> >(const sheaf::block< geometry::d_bounding_box<2, 2> >& xblk1, const sheaf::block< geometry::d_bounding_box<2, 2> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<2, 2> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<2, 2> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<2, 2> >(const sheaf::block< geometry::d_bounding_box<2, 2> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 0> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 0> >(const sheaf::block< geometry::d_bounding_box<3, 0> >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 0> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 0> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 0> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 0> >(const sheaf::block< geometry::d_bounding_box<3, 0> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 1> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 1> >(const sheaf::block< geometry::d_bounding_box<3, 1> >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 1> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 1> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 1> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 1> >(const sheaf::block< geometry::d_bounding_box<3, 1> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 2> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 2> >(const sheaf::block< geometry::d_bounding_box<3, 2> >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 2> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 2> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 2> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 2> >(const sheaf::block< geometry::d_bounding_box<3, 2> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 3> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 3> >(const sheaf::block< geometry::d_bounding_box<3, 3> >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 3> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 3> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 3> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 3> >(const sheaf::block< geometry::d_bounding_box<3, 3> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<4, 4> >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<4, 4> >(const sheaf::block< geometry::d_bounding_box<4, 4> >& xblk1, const sheaf::block< geometry::d_bounding_box<4, 4> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<4, 4> >(ostream& xos, const sheaf::block< geometry::d_bounding_box<4, 4> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<4, 4> >(const sheaf::block< geometry::d_bounding_box<4, 4> >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<geometry::d_bounding_box<DC, DB> const*>
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<1, 0> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<1, 0> const* >(const sheaf::block< geometry::d_bounding_box<1, 0> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<1, 0> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<1, 0> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<1, 0> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<1, 0> const* >(const sheaf::block< geometry::d_bounding_box<1, 0> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<1, 1> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<1, 1> const* >(const sheaf::block< geometry::d_bounding_box<1, 1> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<1, 1> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<1, 1> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<1, 1> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<1, 1> const* >(const sheaf::block< geometry::d_bounding_box<1, 1> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<2, 0> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<2, 0> const* >(const sheaf::block< geometry::d_bounding_box<2, 0> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<2, 0> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<2, 0> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<2, 0> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<2, 0> const* >(const sheaf::block< geometry::d_bounding_box<2, 0> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<2, 2> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<2, 2> const* >(const sheaf::block< geometry::d_bounding_box<2, 2> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<2, 2> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<2, 2> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<2, 2> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<2, 2> const* >(const sheaf::block< geometry::d_bounding_box<2, 2> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 0> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 0> const* >(const sheaf::block< geometry::d_bounding_box<3, 0> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 0> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 0> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 0> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 0> const* >(const sheaf::block< geometry::d_bounding_box<3, 0> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 1> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 1> const* >(const sheaf::block< geometry::d_bounding_box<3, 1> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 1> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 1> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 1> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 1> const* >(const sheaf::block< geometry::d_bounding_box<3, 1> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 2> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 2> const* >(const sheaf::block< geometry::d_bounding_box<3, 2> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 2> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 2> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 2> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 2> const* >(const sheaf::block< geometry::d_bounding_box<3, 2> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<3, 3> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<3, 3> const* >(const sheaf::block< geometry::d_bounding_box<3, 3> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<3, 3> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<3, 3> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<3, 3> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<3, 3> const* >(const sheaf::block< geometry::d_bounding_box<3, 3> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< geometry::d_bounding_box<4, 4> const* >;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == < geometry::d_bounding_box<4, 4> const* >(const sheaf::block< geometry::d_bounding_box<4, 4> const* >& xblk1, const sheaf::block< geometry::d_bounding_box<4, 4> const* >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << < geometry::d_bounding_box<4, 4> const* >(ostream& xos, const sheaf::block< geometry::d_bounding_box<4, 4> const* >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< geometry::d_bounding_box<4, 4> const* >(const sheaf::block< geometry::d_bounding_box<4, 4> const* >& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// Blocks of singly_linked_lists of bounding boxes.
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<1, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<1, 0> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 0> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<1, 1> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<1, 1> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<1, 1> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<2, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<2, 0> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 0> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<2, 2> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<2, 2> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<2, 2> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<3, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<3, 0> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 0> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<3, 1> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<3, 1> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 1> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<3, 2> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<3, 2> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 2> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<3, 3> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<3, 3> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<3, 3> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// bool sheaf::operator == < singly_linked_list<geometry::d_bounding_box<4, 4> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >& xblk1, const sheaf::block< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::d_bounding_box<4, 4> const *> >(ostream& xos, const sheaf::block< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >(const sheaf::block< singly_linked_list<geometry::d_bounding_box<4, 4> const *> >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS


//==============================================================================
// block<singly_linked_list<db0_point_locator<M>::vertex_type
//==============================================================================

//$$SCRIBBLE: db0_point_locator<DC>::vertex_type is protected.

template class 
SHEAF_DLL_SPEC
sheaf::block<singly_linked_list<geometry::db0_point_locator<1>::vertex_type,
                   std::allocator<geometry::db0_point_locator<1>::vertex_type> > >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> >
// sheaf::operator == < singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >& xblk1,
//  const sheaf::block< singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >
// (ostream& xos, const sheaf::block< singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<1>::vertex_type, std::allocator<geometry::db0_point_locator<1>::vertex_type> > >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block<singly_linked_list<geometry::db0_point_locator<2>::vertex_type,
                   std::allocator<geometry::db0_point_locator<2>::vertex_type> > >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> >
// sheaf::operator == < singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >& xblk1,
 // const sheaf::block< singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >
// (ostream& xos, const sheaf::block< singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<2>::vertex_type, std::allocator<geometry::db0_point_locator<2>::vertex_type> > >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::block<singly_linked_list<geometry::db0_point_locator<3>::vertex_type,
                   std::allocator<geometry::db0_point_locator<3>::vertex_type> > >;

// #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> >
// sheaf::operator == < singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >& xblk1,
 // const sheaf::block< singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >& xblk2);

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << < singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >
// (ostream& xos, const sheaf::block< singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size< singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >
// (const sheaf::block< singly_linked_list<geometry::db0_point_locator<3>::vertex_type, std::allocator<geometry::db0_point_locator<3>::vertex_type> > >& xblk, bool xinclude_shallow);
// #endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
//==============================================================================
