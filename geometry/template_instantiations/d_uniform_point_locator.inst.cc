
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiations for class d_uniform_point_locator.


#include "d_uniform_point_locator.impl.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class 
SHEAF_DLL_SPEC 
geometry::d_uniform_point_locator<1, 1>;

template class 
SHEAF_DLL_SPEC 
geometry::d_uniform_point_locator<2, 2>;

template class 
SHEAF_DLL_SPEC 
geometry::d_uniform_point_locator<3, 3>;

// Stream insertion operators not yet implemented.

// template ostream& geometry::operator<<(ostream& xos,
//                                      const d_uniform_point_locator<1, 1>& xpl);
// template ostream& geometry::operator<<(ostream& xos,
//                                      const d_uniform_point_locator<2, 2>& xpl);
// template ostream& geometry::operator<<(ostream& xos,
//                                      const d_uniform_point_locator<3, 3>& xpl);
