
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

#include "auto_block.impl.h"
#include "auto_block.impl.h"
#include "block.impl.h"
#include "deep_size.h"
#include "chart_point_1d.h"
#include "chart_point_2d.h"
#include "chart_point_3d.h"
#include "discretization_context.h"
#include "e3.h"
#include "sec_vd.h"
#include "sec_tuple.h"
#include "std_utility.h"
#include "structured_block.h"
#include "section_evaluator.h"
#include "differentiable_section_evaluator.h"
#include "integrable_section_evaluator.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//=============================================================================
//  auto_block<fiber_bundle::chart_point_1d>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >(const sheaf::auto_block<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >(const sheaf::auto_block<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
//  auto_block<fiber_bundle::chart_point_1d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >(const sheaf::auto_block<fiber_bundle::chart_point_1d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_1d*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
//  auto_block<chart_point_2d>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >(const sheaf::auto_block<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >(const sheaf::auto_block<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
//  auto_block<chart_point_2d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >(const sheaf::auto_block<fiber_bundle::chart_point_2d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_2d*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// auto_block<chart_point_3d>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >(const sheaf::auto_block<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >(const sheaf::auto_block<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// auto_block<chart_point_3d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::un_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::invalid_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >(const sheaf::auto_block<fiber_bundle::chart_point_3d*, sheaf::zero_block_initialization_policy<fiber_bundle::chart_point_3d*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// auto_block<discretization_context>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::discretization_context>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >(const sheaf::auto_block<fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// auto_block<discretization_context*>
//=============================================================================
template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::discretization_context, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::discretization_context, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::invalid_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::discretization_context, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >(const sheaf::auto_block<fiber_bundle::discretization_context*, sheaf::zero_block_initialization_policy<fiber_bundle::discretization_context*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// auto_block<sec_tuple*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_tuple, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_tuple, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_tuple, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >(const sheaf::auto_block<fiber_bundle::sec_tuple*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_tuple*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=========================================================================
// auto_block<sec_vd*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_vd, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::un_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_vd, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::invalid_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk2);

//template
//SHEAF_DLL_SPEC
//ostream& sheaf::operator << <fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >(ostream& xos,
//												 const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_vd, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >(const sheaf::auto_block<fiber_bundle::sec_vd*, sheaf::zero_block_initialization_policy<fiber_bundle::sec_vd*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// auto_block<structured_block*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::structured_block*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::structured_block, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::un_block_initialization_policy<fiber_bundle::structured_block*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::structured_block, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::invalid_block_initialization_policy<fiber_bundle::structured_block*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::structured_block, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >(const sheaf::auto_block<fiber_bundle::structured_block*, sheaf::zero_block_initialization_policy<fiber_bundle::structured_block*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// auto_block<section_evaluator*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::section_evaluator, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::section_evaluator, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::section_evaluator, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >(const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// auto_block<differentiable_section_evaluator*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::differentiable_section_evaluator, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::differentiable_section_evaluator, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::differentiable_section_evaluator, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// auto_block<integrable_section_evaluator*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::integrable_section_evaluator, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk1,
												const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::integrable_section_evaluator, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::invalid_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::integrable_section_evaluator, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(const sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// auto_block<e3_lite>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::e3_lite>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >& xblk1,
											   const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >(ostream& xos,
											       const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >& xblk,
											  bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >& xblk1,
												const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >(ostream& xos,
												    const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::invalid_block_initialization_policy<fiber_bundle::e3_lite> >& xblk,
											       bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >& xblk1,
											     const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >& xblk2);

template
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >(ostream& xos,
												 const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >(const sheaf::auto_block<fiber_bundle::e3_lite, sheaf::zero_block_initialization_policy<fiber_bundle::e3_lite> >& xblk,
											    bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS



