
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
/// Explicit instantiations for class d_bounding_box.

#include "d_bounding_box.impl.h"

//#include "ComLimitPoint/sheaf/block.impl.h"
#include "geometry.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/singly_linked_list.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

// ============================================================================
// EXPLICIT INSTANTIATIONS
// ============================================================================

// Bounding boxes

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<1, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<2, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<3, 0>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<1, 1>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<2, 2>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<3, 1>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<3, 2>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<3, 3>;

template class 
SHEAF_DLL_SPEC
geometry::d_bounding_box<4, 4>;

// Stream insertion operators for bounding boxes.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <1, 0>(ostream& xos, const geometry::d_bounding_box<1, 0>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <1, 1>(ostream& xos, const geometry::d_bounding_box<1, 1>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <2, 0>(ostream& xos, const geometry::d_bounding_box<2, 0>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <2, 2>(ostream& xos, const geometry::d_bounding_box<2, 2>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 0>(ostream& xos, const geometry::d_bounding_box<3, 0>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 1>(ostream& xos, const geometry::d_bounding_box<3, 1>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 2>(ostream& xos, const geometry::d_bounding_box<3, 2>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <3, 3>(ostream& xos, const geometry::d_bounding_box<3, 3>& xbox);

template 
SHEAF_DLL_SPEC
ostream& geometry::operator<< <4, 4>(ostream& xos, const geometry::d_bounding_box<4, 4>& xbox);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


// Singly_linked_lists of bounding boxes.

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<1, 0>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<1, 1>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<2, 0>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<2, 2>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 0>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 1>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 2>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 3>* >;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<4, 4>* >;

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS


// Singly_linked_lists of bounding boxes const.

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<1, 0> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<1, 1> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<2, 0> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<2, 2> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 0> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 1> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 2> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<3, 3> const*>;

template class 
SHEAF_DLL_SPEC
sheaf::singly_linked_list< geometry::d_bounding_box<4, 4> const*>;

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS
