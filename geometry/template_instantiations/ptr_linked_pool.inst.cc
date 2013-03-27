// $RCSfile: ptr_linked_pool.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:32 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Explicit instantiations for class ptr_linked_pool.

#include "ptr_linked_pool.impl.h"

#include "geometry.h"
#include "d_tree_point_locator_node.impl.h"

using namespace geometry; // Workaround for MS C++ bug.

//=============================================================================
// EXPLICIT INSTANTIATIONS
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<1, 1> >;

template class 
SHEAF_DLL_SPEC 
sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<2, 2> >;

template class 
SHEAF_DLL_SPEC 
sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<3, 3> >;

// template class 
// SHEAF_DLL_SPEC 
// sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<4, 4> >;

template
SHEAF_DLL_SPEC 
ostream&
sheaf::operator<< <geometry::d_tree_point_locator_node<1, 1> >(ostream& xos,
    const sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<1, 1> >& xp);

template
SHEAF_DLL_SPEC 
ostream&
sheaf::operator<< <geometry::d_tree_point_locator_node<2, 2> >(ostream& xos,
    const sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<2, 2> >& xp);

template
SHEAF_DLL_SPEC 
ostream&
sheaf::operator<< <geometry::d_tree_point_locator_node<3, 3> >(ostream& xos,
    const sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<3, 3> >& xp);

// template
// SHEAF_DLL_SPEC 
// ostream&
// sheaf::operator<< <geometry::d_tree_point_locator_node<4, 4> >(ostream& xos,
//     const sheaf::ptr_linked_pool<geometry::d_tree_point_locator_node<4, 4> >& xp);
