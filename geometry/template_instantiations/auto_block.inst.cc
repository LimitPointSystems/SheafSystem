// $RCSfile: auto_block.inst.cc,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:31 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class auto_block.


#include "auto_block.impl.h"

#include "d_bounding_box.impl.h"
#include "d_tree_point_locator_node.impl.h"
#include "geometry.h"
#include "kd_bounding_box.h"
#include "kd_plane.h"
#include "std_slist.h"
#include "std_utility.h"


using namespace geometry; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// auto_block<kd_plane>
//==============================================================================

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::kd_plane>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::kd_plane,
                  sheaf::un_block_initialization_policy<geometry::kd_plane> >;

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >(const sheaf::auto_block<geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >& xblk1,
									     const sheaf::auto_block<geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >(ostream& xos,
										 const sheaf::auto_block<geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >(const sheaf::auto_block<geometry::kd_plane, sheaf::un_block_initialization_policy<geometry::kd_plane> >& xblk,
									    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<kd_bounding_box>
//==============================================================================

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::kd_bounding_box>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::kd_bounding_box,
                  sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >;


#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >(const sheaf::auto_block<geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >& xblk1,
									     const sheaf::auto_block<geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >(ostream& xos,
										 const sheaf::auto_block<geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >& xblk);

template 
SHEAF_DLL_SPEC 
size_t sheaf::deep_size<geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >(const sheaf::auto_block<geometry::kd_bounding_box, sheaf::un_block_initialization_policy<geometry::kd_bounding_box> >& xblk,
									    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<d_bounding_box<M, N>,
//            un_block_initialization_policy<d_bounding_box<M, N> > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<1, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<1, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<2, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<2, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 0>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<1, 1>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >(const sheaf::auto_block<geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >(const sheaf::auto_block<geometry::d_bounding_box<1, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<2, 2>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >(const sheaf::auto_block<geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >(const sheaf::auto_block<geometry::d_bounding_box<2, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 1>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 1>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 2>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 2>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 3>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >(const sheaf::auto_block<geometry::d_bounding_box<3, 3>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<4, 4>,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >(const sheaf::auto_block<geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >(const sheaf::auto_block<geometry::d_bounding_box<4, 4>, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<d_bounding_box<M, N> const*,
//            un_block_initialization_policy<d_bounding_box<M, N> const* > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<1, 0> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<1, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 0> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<2, 0> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<2, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 0> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 0> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 0> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 0> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<1, 1> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >(const sheaf::auto_block<geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >(const sheaf::auto_block<geometry::d_bounding_box<1, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<1, 1> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<2, 2> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >(const sheaf::auto_block<geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >(const sheaf::auto_block<geometry::d_bounding_box<2, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<2, 2> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 1> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 1> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 1> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 2> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 2> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 2> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<3, 3> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >(const sheaf::auto_block<geometry::d_bounding_box<3, 3> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<3, 3> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_bounding_box<4, 4> const*,
                  sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >(const sheaf::auto_block<geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >& xblk1,
									     const sheaf::auto_block<geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >(ostream& xos,
										 const sheaf::auto_block<geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >(const sheaf::auto_block<geometry::d_bounding_box<4, 4> const*, sheaf::un_block_initialization_policy<geometry::d_bounding_box<4, 4> const* > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// auto_block<block<d_bounding_box<M, N> >,
//            un_block_initialization_policy<block<d_bounding_box<M, N> > > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 0> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 0> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 0> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 0> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 0> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 0> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 0> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 1> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<1, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<1, 1> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 2> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<2, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<2, 2> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 1> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 1> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 1> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 2> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 2> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 2> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 3> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<3, 3> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<3, 3> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<sheaf::block<geometry::d_bounding_box<4, 4> >,
                  sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >& xblk1,
									     const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >(ostream& xos,
										 const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >(const sheaf::auto_block<sheaf::block<geometry::d_bounding_box<4, 4> >, sheaf::un_block_initialization_policy<sheaf::block<geometry::d_bounding_box<4, 4> > > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// auto_block<slist<d_bounding_box<M, N>* >,
//            un_block_initialization_policy<slist<d_bounding_box<M, N>*> > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<1, 0>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 1>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<1, 1>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 1>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<2, 0>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 2>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<2, 2>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 2>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 0>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 1>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 1>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 1>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 2>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 2>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 2>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 3>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 3>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 3>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<4, 4>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<4, 4>* > ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<4, 4>* > > >;



//==============================================================================
// auto_block<slist<d_bounding_box<M, N> const* >,
//            un_block_initialization_policy<slist<d_bounding_box<M, N> const*> > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<1, 0> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 1> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<1, 1> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<1, 1> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<2, 0> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 2> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<2, 2> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<2, 2> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 0> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 1> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 1> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 1> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 2> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 2> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 2> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 3> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<3, 3> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<3, 3> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<4, 4> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<slist< geometry::d_bounding_box<4, 4> const*> ,
                         sheaf::un_block_initialization_policy<slist< geometry::d_bounding_box<4, 4> const*> > >;


//==============================================================================
// auto_block<d_tree_point_locator_node<DC, DB> >
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<1, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<1, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<1, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<1, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<2, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<2, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<2, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<2, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 0> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<3, 0>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 0> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 0>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 0> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<1, 1> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<1, 1>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<1, 1> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >(const sheaf::auto_block<d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >(const sheaf::auto_block<d_tree_point_locator_node<1, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<1, 1> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 1> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<3, 1>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 1> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 1>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 1> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<2, 2> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<2, 2>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<2, 2> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >(const sheaf::auto_block<d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >(const sheaf::auto_block<d_tree_point_locator_node<2, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<2, 2> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 2> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<3, 2>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 2> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 2>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 2> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 3> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<3, 3>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<3, 3> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >(const sheaf::auto_block<d_tree_point_locator_node<3, 3>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<3, 3> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<4, 4> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<geometry::d_tree_point_locator_node<4, 4>,
                  sheaf::un_block_initialization_policy<geometry::d_tree_point_locator_node<4, 4> > >;


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC 
bool sheaf::operator == <d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >(const sheaf::auto_block<d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >& xblk1,
									     const sheaf::auto_block<d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >& xblk2);

template 
SHEAF_DLL_SPEC 
ostream& sheaf::operator << <d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >(ostream& xos,
										 const sheaf::auto_block<d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >& xblk);

// template 
// SHEAF_DLL_SPEC 
// size_t sheaf::deep_size<d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >(const sheaf::auto_block<d_tree_point_locator_node<4, 4>, sheaf::un_block_initialization_policy<d_tree_point_locator_node<4, 4> > >& xblk,
									    // bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
//==============================================================================
