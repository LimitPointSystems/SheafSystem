
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

// Explicit_instantiations for class atp.

#include "atp.impl.h"

#include "at2_e2.h"
#include "e2.h"

#include "at2_e3.h"
#include "e3.h"

#include "at3_e3.h"

#include "at0.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
#ifndef _WIN32

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// at2_e2_lite
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::e2_lite*
fiber_bundle::atp_algebra::hook<fiber_bundle::at2_e2_lite>(const at2_e2_lite& x0,
							   const e2_lite& x1);


//==============================================================================
// at2_e3_lite
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::e3_lite*
fiber_bundle::atp_algebra::hook<fiber_bundle::at2_e3_lite>(const at2_e3_lite& x0, const e3_lite& x1);

// template
// fiber_bundle::tensor_traits<fiber_bundle::at2_e3_lite::P, fiber_bundle::e3_lite::vector_space_type>::atp_type*
// fiber_bundle::star(const at2_e3_lite& x0);

template
SHEAF_DLL_SPEC
fiber_bundle::at3_e3_lite*
fiber_bundle::atp_algebra::wedge<fiber_bundle::at2_e3_lite>(const at2_e3_lite& x0, const e3_lite& x1);


//==============================================================================
// at3_e3_lite
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::at2_e3_lite*
fiber_bundle::atp_algebra::hook<fiber_bundle::at3_e3_lite>(const at3_e3_lite& x0, const e3_lite& x1);

//==============================================================================
// e2_lite
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at0_lite*
fiber_bundle::atp_algebra::hook<fiber_bundle::e2_lite>(const e2_lite& x0, const e2_lite& x1);

// template
// fiber_bundle::tensor_traits<fiber_bundle::e2_lite::P, fiber_bundle::e2_lite::vector_space_type>::atp_type*
// fiber_bundle::star(const e2_lite& x0);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::atp_algebra::wedge<fiber_bundle::e2_lite>(const e2_lite& x0, const e2_lite& x1);


//==============================================================================
// e3_lite
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::at0_lite*
fiber_bundle::atp_algebra::hook<fiber_bundle::e3_lite>(const e3_lite& x0, const e3_lite& x1);

// template
// fiber_bundle::tensor_traits<fiber_bundle::e3_lite::P, fiber_bundle::e3_lite::vector_space_type>::atp_type*
// fiber_bundle::star(const e3_lite& x0);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e3_lite*
fiber_bundle::atp_algebra::wedge<fiber_bundle::e3_lite>(const e3_lite& x0, const e3_lite& x1);


//==============================================================================
// e4_lite
//==============================================================================

// template
// fiber_bundle::tensor_traits<fiber_bundle::e4_lite::P - fiber_bundle::e4_lite::P, fiber_bundle::e4_lite::vector_space_type>::atp_type*
// fiber_bundle::hook(const e4_lite& x0, const e4_lite& x1);

// template
// fiber_bundle::tensor_traits<fiber_bundle::e4_lite::P, fiber_bundle::e4_lite::vector_space_type>::atp_type*
// fiber_bundle::star(const e4_lite& x0);

// template
// fiber*_bundle::tensor_traits<fiber_bundle::e4_lite::P + fiber_bundle::e4_lite::P, fiber_bundle::e4_lite::vector_space_type>::atp_type*
// fiber_bundle::wedge(const e4_lite& x0, const e4_lite& x1);

//==============================================================================
//==============================================================================

#endif // ifndef _WIN32
#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

