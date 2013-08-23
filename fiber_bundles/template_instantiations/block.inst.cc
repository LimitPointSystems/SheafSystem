
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

// Explicit instantiations for class block.

#include "auto_block.h"
#include "auto_block.impl.h"
#include "block.impl.h"
#include "deep_size.h"
#include "chart_point_1d.h"
#include "chart_point_2d.h"
#include "chart_point_3d.h"
#include "discretization_context.h"
#include "e3.h"
#include "sec_at0.h"
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
//  block<chart_point_1d>
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<fiber_bundle::chart_point_1d>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d>(const sheaf::block<fiber_bundle::chart_point_1d>& xblk1, const sheaf::block<fiber_bundle::chart_point_1d>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_1d>
              (ostream& xos, const block<fiber_bundle::chart_point_1d>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d>(const sheaf::block<fiber_bundle::chart_point_1d>& xblk, bool xinclude_shallow);

//=============================================================================
//  block<chart_point_1d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::chart_point_1d*>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_1d*>(const sheaf::block<fiber_bundle::chart_point_1d*>& xblk1, const sheaf::block<fiber_bundle::chart_point_1d*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_1d*>
              (ostream& xos, const block<fiber_bundle::chart_point_1d*>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_1d>(const sheaf::block<fiber_bundle::chart_point_1d*>& xblk, bool xinclude_shallow);

//=============================================================================
//  block<chart_point_2d>
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<fiber_bundle::chart_point_2d>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d>(const sheaf::block<fiber_bundle::chart_point_2d>& xblk1, const sheaf::block<fiber_bundle::chart_point_2d>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_2d>
              (ostream& xos, const block<fiber_bundle::chart_point_2d>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d>(const sheaf::block<fiber_bundle::chart_point_2d>& xblk, bool xinclude_shallow);

//=============================================================================
//  block<chart_point_2d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::chart_point_2d*>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_2d*>(const sheaf::block<fiber_bundle::chart_point_2d*>& xblk1, const sheaf::block<fiber_bundle::chart_point_2d*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_2d*>
              (ostream& xos, const block<fiber_bundle::chart_point_2d*>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_2d>(const sheaf::block<fiber_bundle::chart_point_2d*>& xblk, bool xinclude_shallow);

//=============================================================================
//  block<chart_point_3d>
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<fiber_bundle::chart_point_3d>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d>(const sheaf::block<fiber_bundle::chart_point_3d>& xblk1, const sheaf::block<fiber_bundle::chart_point_3d>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_3d>
              (ostream& xos, const block<fiber_bundle::chart_point_3d>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d>(const sheaf::block<fiber_bundle::chart_point_3d>& xblk, bool xinclude_shallow);

//=============================================================================
//  block<chart_point_3d*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::chart_point_3d*>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::chart_point_3d*>(const sheaf::block<fiber_bundle::chart_point_3d*>& xblk1, const sheaf::block<fiber_bundle::chart_point_3d*>& xblk2);

template 
SHEAF_DLL_SPEC 
ostream&
sheaf::
operator<< <fiber_bundle::chart_point_3d*>
              (ostream& xos, const block<fiber_bundle::chart_point_3d*>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::chart_point_3d>(const sheaf::block<fiber_bundle::chart_point_3d*>& xblk, bool xinclude_shallow);

//=============================================================================
// block<discretization_context>
//=============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::discretization_context>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context,
                  sheaf::un_block_initialization_policy<fiber_bundle::discretization_context> >;

template class
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::discretization_context>;

 template
 SHEAF_DLL_SPEC
 ostream&
 sheaf::operator << <fiber_bundle::discretization_context>(ostream& xos, const sheaf::block<fiber_bundle::discretization_context>& xblk);

 template
 SHEAF_DLL_SPEC
 size_t sheaf::deep_size<fiber_bundle::discretization_context>(const sheaf::block<fiber_bundle::discretization_context>& xblk, bool xinclude_shallow);

//template
//SHEAF_DLL_SPEC
//bool sheaf::operator == <fiber_bundle::discretization_context>(const sheaf::block<fiber_bundle::discretization_context>& xblk1, const sheaf::block<fiber_bundle::discretization_context>& xblk2);

//=============================================================================
// block<discretization_context*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*>;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::discretization_context*,
                  sheaf::un_block_initialization_policy<fiber_bundle::discretization_context*> >;

template class
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::discretization_context*>;

template
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <fiber_bundle::discretization_context*>(ostream& xos, const sheaf::block<fiber_bundle::discretization_context*>& xblk);

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::discretization_context*>(const sheaf::block<fiber_bundle::discretization_context*>& xblk1, const sheaf::block<fiber_bundle::discretization_context*>& xblk2);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::discretization_context>(const sheaf::block<fiber_bundle::discretization_context*>& xblk, bool xinclude_shallow);

//=============================================================================
// block<sec_tuple*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*>;


template class
SHEAF_DLL_SPEC 
sheaf::auto_block<fiber_bundle::sec_tuple*,
		  sheaf::un_block_initialization_policy<fiber_bundle::sec_tuple*> >;


template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::sec_tuple*>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_tuple*>(const sheaf::block<fiber_bundle::sec_tuple*>& xblk1, const sheaf::block<fiber_bundle::sec_tuple*>& xblk2);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_tuple>(const sheaf::block<fiber_bundle::sec_tuple*>& xblk, bool xinclude_shallow);

// #ifndef DOXYGEN_SKIP_INSTANTIATIONS
// template 
// SHEAF_DLL_SPEC 
// ostream&
// sheaf::operator << <fiber_bundle::sec_tuple*>(ostream& xos, const sheaf::block<fiber_bundle::sec_tuple*>& xblk);
// #endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<sec_vd*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block< fiber_bundle::sec_vd* >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::auto_block< fiber_bundle::sec_vd* >;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_vd*>(const sheaf::block<fiber_bundle::sec_vd*>& xblk1, const sheaf::block<fiber_bundle::sec_vd*>& xblk2);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::sec_vd>(const sheaf::block<fiber_bundle::sec_vd*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<sec_at0*>
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block< fiber_bundle::sec_at0* >;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class
SHEAF_DLL_SPEC
sheaf::auto_block< fiber_bundle::sec_at0* >;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::sec_at0*>(const sheaf::block<fiber_bundle::sec_at0*>& xblk1, const sheaf::block<fiber_bundle::sec_at0*>& xblk2);

// Instantiation references undefined deep_size(const sec_at0&, bool)
// template
// SHEAF_DLL_SPEC
// size_t sheaf::deep_size<fiber_bundle::sec_at0>(const sheaf::block<fiber_bundle::sec_at0*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<sec_vd_value_type>
//=============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::sec_vd_value_type>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template 
SHEAF_DLL_SPEC
ostream&
sheaf::operator << <fiber_bundle::sec_vd_value_type>(
    ostream& xos, const sheaf::block<fiber_bundle::sec_vd_value_type>& xblk);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<structured_block*>
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block<fiber_bundle::structured_block*>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::structured_block*>(const sheaf::block<fiber_bundle::structured_block*>& xblk1, const sheaf::block<fiber_bundle::structured_block*>& xblk2);


template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::structured_block>(const sheaf::block<fiber_bundle::structured_block*>& xblk, bool xinclude_shallow);

// #ifndef DOXYGEN_SKIP_INSTANTIATIONS

// template 
// SHEAF_DLL_SPEC 
// ostream& sheaf::operator << <fiber_bundle::structured_block*>(ostream& xos, const block<fiber_bundle::structured_block*>& xblk);

// #endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<section_evaluator*>
//=============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::section_evaluator*> >;

template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::section_evaluator*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::section_evaluator*>(const sheaf::block<fiber_bundle::section_evaluator*>& xblk1, const sheaf::block<fiber_bundle::section_evaluator*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::section_evaluator*>(ostream& xos, const sheaf::block<fiber_bundle::section_evaluator*>& xblk);
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
ostream& sheaf::operator << <fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >(ostream& xos, const sheaf::auto_block<fiber_bundle::section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::section_evaluator>(const sheaf::block<fiber_bundle::section_evaluator*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// block<differentiable_section_evaluator*>
//=============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >;

template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::differentiable_section_evaluator*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::differentiable_section_evaluator*>(const sheaf::block<fiber_bundle::differentiable_section_evaluator*>& xblk1, const sheaf::block<fiber_bundle::differentiable_section_evaluator*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::differentiable_section_evaluator*>(ostream& xos, const sheaf::block<fiber_bundle::differentiable_section_evaluator*>& xblk);
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
ostream& sheaf::operator << <fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >(ostream& xos, const auto_block<fiber_bundle::differentiable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::differentiable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::differentiable_section_evaluator>(const sheaf::block<fiber_bundle::differentiable_section_evaluator*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


//=============================================================================
// block<integrable_section_evaluator*>
//=============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::un_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >;

template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::integrable_section_evaluator*>;

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::integrable_section_evaluator*>(const sheaf::block<fiber_bundle::integrable_section_evaluator*>& xblk1, const sheaf::block<fiber_bundle::integrable_section_evaluator*>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::integrable_section_evaluator*>(ostream& xos, const block<fiber_bundle::integrable_section_evaluator*>& xblk);

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
ostream& sheaf::operator << <fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >(ostream& xos, const auto_block<fiber_bundle::integrable_section_evaluator*, sheaf::zero_block_initialization_policy<fiber_bundle::integrable_section_evaluator*> >& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::integrable_section_evaluator>(const sheaf::block<fiber_bundle::integrable_section_evaluator*>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

//=============================================================================
// block<e3_lite>
//=============================================================================

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

template class 
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<fiber_bundle::e3_lite>;

template class 
SHEAF_DLL_SPEC
sheaf::auto_block<fiber_bundle::e3_lite,
                  sheaf::un_block_initialization_policy<fiber_bundle::e3_lite> >;

template class 
SHEAF_DLL_SPEC
sheaf::block<fiber_bundle::e3_lite>;

template
SHEAF_DLL_SPEC
bool sheaf::operator == <fiber_bundle::e3_lite>(const sheaf::block<fiber_bundle::e3_lite>& xblk1, const sheaf::block<fiber_bundle::e3_lite>& xblk2);

template 
SHEAF_DLL_SPEC
ostream& sheaf::operator << <fiber_bundle::e3_lite>(
    ostream& xos, const sheaf::block<fiber_bundle::e3_lite>& xblk);

template
SHEAF_DLL_SPEC
size_t sheaf::deep_size<fiber_bundle::e3_lite>(const sheaf::block<fiber_bundle::e3_lite>& xblk, bool xinclude_shallow);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
 

//==============================================================================
// block<pair<sheaf::scoped_index, fiber_bundle::chart_point_3d> >
//==============================================================================

template class 
SHEAF_DLL_SPEC
sheaf::block<pair<sheaf::scoped_index, fiber_bundle::chart_point_3d> >;

template class
SHEAF_DLL_SPEC
sheaf::un_block_initialization_policy<pair<sheaf::scoped_index,
                                           fiber_bundle::chart_point_3d> >;

template class
SHEAF_DLL_SPEC
sheaf::auto_block<pair<sheaf::scoped_index, fiber_bundle::chart_point_3d>,
		  sheaf::un_block_initialization_policy<
              pair<sheaf::scoped_index, fiber_bundle::chart_point_3d> > >;

//=============================================================================
// block< sheaf::block<fiber_bundle::sec_vd_dof_type> >
//=============================================================================

template class
SHEAF_DLL_SPEC
sheaf::block< sheaf::block<fiber_bundle::sec_vd_dof_type> >;

//=============================================================================
// block< sheaf::block<fiber_bundle::sec_vd_dof_type>* >
//=============================================================================

template class 
SHEAF_DLL_SPEC 
sheaf::block< sheaf::block<fiber_bundle::sec_vd_dof_type>* >;

//=============================================================================
//=============================================================================
