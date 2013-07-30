
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Explicit instantiations for class block.


#include "auto_block.impl.h"
#include "block.impl.h"

#include "barycentric_refiner_family.h"
#include "edge_centered_polygon_refiner.h"
#include "edge_centered_refiner_family.h"
#include "pullback_map.h"
#include "zone_centered_refiner_family.h"
#include "zone_centered_segment_refiner.h"
#include "zone_centered_tet_refiner.h"
#include "zone_centered_triangle_refiner.h"
#include "local_field_refiner.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// local_field_refiner*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::local_field_refiner*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::local_field_refiner*>(const sheaf::block<fields::local_field_refiner*>& xblk1, const sheaf::block<fields::local_field_refiner*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::local_field_refiner*>(ostream& xos, const sheaf::block<fields::local_field_refiner*>& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<fields::local_field_refiner*>(const sheaf::block<fields::local_field_refiner*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// barycentric_refiner_family*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::barycentric_refiner_family*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::barycentric_refiner_family*>(const sheaf::block<fields::barycentric_refiner_family*>& xblk1, const sheaf::block<fields::barycentric_refiner_family*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::barycentric_refiner_family*>(ostream& xos, const sheaf::block<fields::barycentric_refiner_family*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::barycentric_refiner_family*>(const sheaf::block<fields::barycentric_refiner_family*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// edge_centered_polygon_refiner*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::edge_centered_polygon_refiner*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::edge_centered_polygon_refiner*>(const sheaf::block<fields::edge_centered_polygon_refiner*>& xblk1, const sheaf::block<fields::edge_centered_polygon_refiner*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::edge_centered_polygon_refiner*>(ostream& xos, const sheaf::block<fields::edge_centered_polygon_refiner*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::edge_centered_polygon_refiner*>(const sheaf::block<fields::edge_centered_polygon_refiner*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// edge_centered_refiner_family*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::edge_centered_refiner_family*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::edge_centered_refiner_family*>(const sheaf::block<fields::edge_centered_refiner_family*>& xblk1, const sheaf::block<fields::edge_centered_refiner_family*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::edge_centered_refiner_family*>(ostream& xos, const sheaf::block<fields::edge_centered_refiner_family*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::edge_centered_refiner_family*>(const sheaf::block<fields::edge_centered_refiner_family*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// zone_centered_refiner_family*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::zone_centered_refiner_family*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::zone_centered_refiner_family*>(const sheaf::block<fields::zone_centered_refiner_family*>& xblk1, const sheaf::block<fields::zone_centered_refiner_family*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::zone_centered_refiner_family*>(ostream& xos, const sheaf::block<fields::zone_centered_refiner_family*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::zone_centered_refiner_family*>(const sheaf::block<fields::zone_centered_refiner_family*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// zone_centered_segment_refiner*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::zone_centered_segment_refiner*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::zone_centered_segment_refiner*>(const sheaf::block<fields::zone_centered_segment_refiner*>& xblk1, const sheaf::block<fields::zone_centered_segment_refiner*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::zone_centered_segment_refiner*>(ostream& xos, const sheaf::block<fields::zone_centered_segment_refiner*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::zone_centered_segment_refiner*>(const sheaf::block<fields::zone_centered_segment_refiner*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// zone_centered_tet_refiner*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::zone_centered_tet_refiner*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::zone_centered_tet_refiner*>(const sheaf::block<fields::zone_centered_tet_refiner*>& xblk1, const sheaf::block<fields::zone_centered_tet_refiner*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::zone_centered_tet_refiner*>(ostream& xos, const sheaf::block<fields::zone_centered_tet_refiner*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::zone_centered_tet_refiner*>(const sheaf::block<fields::zone_centered_tet_refiner*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// zone_centered_triangle_refiner*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::zone_centered_triangle_refiner*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::zone_centered_triangle_refiner*>(const sheaf::block<fields::zone_centered_triangle_refiner*>& xblk1, const sheaf::block<fields::zone_centered_triangle_refiner*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::zone_centered_triangle_refiner*>(ostream& xos, const sheaf::block<fields::zone_centered_triangle_refiner*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::zone_centered_triangle_refiner*>(const sheaf::block<fields::zone_centered_triangle_refiner*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
// pullback_map*
//==============================================================================

template class
SHEAF_DLL_SPEC 
sheaf::block<fields::pullback_map*>;

#ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS
template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <fields::pullback_map*>(const sheaf::block<fields::pullback_map*>& xblk1, const sheaf::block<fields::pullback_map*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <fields::pullback_map*>(ostream& xos, const sheaf::block<fields::pullback_map*>& xblk);

//template 
//SHEAF_DLL_SPEC 
//size_t sheaf::deep_size<fields::pullback_map*>(const sheaf::block<fields::pullback_map*>& xblk, bool xinclude_shallow);
#endif // #ifndef DOXYGEN_SKIP_PRIMITIVE_INSTANTIATIONS

//==============================================================================
//==============================================================================

