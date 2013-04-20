
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_bounding_box.

#include "d_bounding_box.impl.h"

//#include "block.impl.h"
#include "geometry.h"
#include "std_iostream.h"
#include "std_slist.h"

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


// Slists of bounding boxes.

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<1, 0>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<1, 1>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<2, 0>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<2, 2>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 0>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 1>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 2>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 3>* >;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<4, 4>* >;

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS


// Slists of bounding boxes const.

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<1, 0> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<1, 1> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<2, 0> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<2, 2> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 0> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 1> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 2> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<3, 3> const*>;

template class 
SHEAF_DLL_SPEC
slist< geometry::d_bounding_box<4, 4> const*>;

#endif // ifndef DOXYGEN_SHOULD_SKIP_THIS