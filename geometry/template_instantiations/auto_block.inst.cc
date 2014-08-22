
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

// Explicit instantiations for class auto_block.


#include "ComLimitPoint/sheaf/auto_block.impl.h"

#include "ComLimitPoint/geometry/d_bounding_box.impl.h"
#include "ComLimitPoint/geometry/d_tree_point_locator_node.impl.h"
#include "ComLimitPoint/geometry/geometry.h"
#include "ComLimitPoint/sheaf/singly_linked_list.h"
#include "std_utility.h"


using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

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
// auto_block<singly_linked_list<d_bounding_box<M, N>* >,
//            un_block_initialization_policy<singly_linked_list<d_bounding_box<M, N>*> > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<1, 0>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 1>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<1, 1>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 1>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<2, 0>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 2>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<2, 2>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 2>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 0>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 0>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 0>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 1>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 1>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 1>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 2>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 2>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 2>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 3>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 3>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 3>* > > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<4, 4>* > >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<4, 4>* > ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<4, 4>* > > >;



//==============================================================================
// auto_block<singly_linked_list<d_bounding_box<M, N> const* >,
//            un_block_initialization_policy<singly_linked_list<d_bounding_box<M, N> const*> > >;
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<1, 0> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 1> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<1, 1> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<1, 1> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<2, 0> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 2> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<2, 2> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<2, 2> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 0> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 0> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 0> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 1> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 1> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 1> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 2> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 2> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 2> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 3> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<3, 3> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<3, 3> const*> > >;

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<4, 4> const*> >;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<singly_linked_list< geometry::d_bounding_box<4, 4> const*> ,
                         sheaf::un_block_initialization_policy<singly_linked_list< geometry::d_bounding_box<4, 4> const*> > >;


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
