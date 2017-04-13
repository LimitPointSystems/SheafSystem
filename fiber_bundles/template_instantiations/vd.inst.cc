
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

// Explicit_instantiations for class vd.

#include "SheafSystem/vd.impl.h"

#include "SheafSystem/at0.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/at2_e3.h"
#include "SheafSystem/at3_e3.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/e4.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_e23.h"
#include "SheafSystem/jcb_e33.h"
#include "SheafSystem/met_e1.h"
#include "SheafSystem/met_e2.h"
#include "SheafSystem/met_e3.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/st2_e3.h"
#include "SheafSystem/st3_e3.h"
#include "SheafSystem/st4_e2.h"
#include "SheafSystem/st4_e3.h"
#include "SheafSystem/t2_e2.h"
#include "SheafSystem/t2_e3.h"
#include "SheafSystem/t3_e3.h"
#include "SheafSystem/t4_e2.h"
#include "SheafSystem/t4_e3.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR VD FACET
//==============================================================================

//==============================================================================
// at0_lite
//==============================================================================

template 
SHEAF_DLL_SPEC 
void
fiber_bundle::vd_algebra::add_equal<fiber_bundle::at0_lite>(at0_lite&,
							    const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::add<fiber_bundle::at0_lite>(const at0_lite&,
						      const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::operator+<fiber_bundle::at0_lite>(const at0_lite&,
							    const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite&
fiber_bundle::vd_algebra::operator+=<fiber_bundle::at0_lite>(at0_lite&,
							     const at0_lite&);

template 
SHEAF_DLL_SPEC 
void
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::at0_lite>(at0_lite&,
								 const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::subtract<fiber_bundle::at0_lite>(const at0_lite&,
							   const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::operator-<fiber_bundle::at0_lite>(const at0_lite&,
							    const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite&
fiber_bundle::vd_algebra::operator-=<fiber_bundle::at0_lite>(at0_lite&,
							     const at0_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::multiply<fiber_bundle::at0_lite>(const at0_lite&,
							   const at0_lite::value_type&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at0_lite*
fiber_bundle::vd_algebra::divide<fiber_bundle::at0_lite>(const at0_lite&,
							 const at0_lite::value_type&);

//==============================================================================
// at2_e2_lite
//==============================================================================


template
SHEAF_DLL_SPEC
void
fiber_bundle::vd_algebra::add_equal<fiber_bundle::at2_e2_lite>(at2_e2_lite&,
							       const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::add<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							 const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::operator+<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							       const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite&
fiber_bundle::vd_algebra::operator+=<fiber_bundle::at2_e2_lite>(at2_e2_lite&,
								const at2_e2_lite&);

template
SHEAF_DLL_SPEC
void
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::at2_e2_lite>(at2_e2_lite&,
								    const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::subtract<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							      const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::operator-<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							       const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite&
fiber_bundle::vd_algebra::operator-=<fiber_bundle::at2_e2_lite>(at2_e2_lite&,
								const at2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::multiply<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							      const at2_e2_lite::value_type&);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::vd_algebra::divide<fiber_bundle::at2_e2_lite>(const at2_e2_lite&,
							    const at2_e2_lite::value_type&);

//==============================================================================
// at2_e3_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::at2_e3_lite>(at2_e3_lite&,
							       const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::add<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							 const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::operator+<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							       const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite&
fiber_bundle::vd_algebra::operator+=<fiber_bundle::at2_e3_lite>(at2_e3_lite&,
								const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
void
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::at2_e3_lite>(at2_e3_lite&,
								    const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::subtract<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							      const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::operator-<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							       const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite&
fiber_bundle::vd_algebra::operator-=<fiber_bundle::at2_e3_lite>(at2_e3_lite&,
								const at2_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::multiply<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							      const at2_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at2_e3_lite*
fiber_bundle::vd_algebra::divide<fiber_bundle::at2_e3_lite>(const at2_e3_lite&,
							    const at2_e3_lite::value_type&);

//==============================================================================
// at3_e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::at3_e3_lite>(at3_e3_lite&,
							       const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							 const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							       const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::at3_e3_lite>(at3_e3_lite&,
								const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::at3_e3_lite>(at3_e3_lite&,
								    const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							      const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							       const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::at3_e3_lite>(at3_e3_lite&,
								const at3_e3_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							      const at3_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::at3_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::at3_e3_lite>(const at3_e3_lite&,
							    const at3_e3_lite::value_type&);

//==============================================================================
// e1_lite
//==============================================================================

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::e1_lite>(e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::e1_lite>(const e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::e1_lite>(const e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::e1_lite>(e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::e1_lite>(e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::e1_lite>(const e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::e1_lite>(const e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::e1_lite>(e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::e1_lite>(const e1_lite&,
							  const e1_lite::value_type&);

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::e1_lite>(const e1_lite&,
							const e1_lite::value_type&);

//==============================================================================
// e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::e2_lite>(e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::e2_lite>(const e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::e2_lite>(const e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::e2_lite>(e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::e2_lite>(e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::e2_lite>(const e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::e2_lite>(const e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::e2_lite>(e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::e2_lite>(const e2_lite&,
							  const e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite*
fiber_bundle::vd_algebra::operator*(const e2_lite&, const e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite& 
fiber_bundle::vd_algebra::operator*=<fiber_bundle::e2_lite>(e2_lite&, const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::e2_lite>(const e2_lite&,
							const e2_lite::value_type&);

//==============================================================================
// e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::e3_lite>(e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::e3_lite>(const e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::e3_lite>(const e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::e3_lite>(e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::e3_lite>(e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::e3_lite>(const e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::e3_lite>(const e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::e3_lite>(e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::e3_lite>(const e3_lite&,
							  const vd_value_type&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::multiply_equal<fiber_bundle::e3_lite>(e3_lite&,
								const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::operator*<fiber_bundle::e3_lite>(const e3_lite&,
							   const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite& 
fiber_bundle::vd_algebra::operator*=<fiber_bundle::e3_lite>(e3_lite&,
							    const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::e3_lite>(const e3_lite&,
							const vd_value_type&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::divide_equal<fiber_bundle::e3_lite>(e3_lite&,
							      const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite* 
fiber_bundle::vd_algebra::operator/<fiber_bundle::e3_lite>(const e3_lite&,
							   const vd_value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite& 
fiber_bundle::vd_algebra::operator/=<fiber_bundle::e3_lite>(e3_lite&,
							    const vd_value_type&);


//==============================================================================
// e4_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::e4_lite>(e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::e4_lite>(const e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::e4_lite>(const e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::e4_lite>(e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::e4_lite>(e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::e4_lite>(const e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::e4_lite>(const e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::e4_lite>(e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::e4_lite>(const e4_lite&,
							  const e4_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::e4_lite>(const e4_lite&,
							const e4_lite::value_type&);

//==============================================================================
// jcb_e13_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::jcb_e13_lite>(jcb_e13_lite&,
								const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
							  const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
								const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::jcb_e13_lite>(jcb_e13_lite&,
								 const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::jcb_e13_lite>(jcb_e13_lite&,
								     const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
							       const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
								const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::jcb_e13_lite>(jcb_e13_lite&,
								 const jcb_e13_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
							       const jcb_e13_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::jcb_e13_lite>(const jcb_e13_lite&,
							     const jcb_e13_lite::value_type&);

//==============================================================================
// jcb_e23_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::jcb_e23_lite>(jcb_e23_lite&,
								const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
							  const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
								const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::jcb_e23_lite>(jcb_e23_lite&,
								 const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::jcb_e23_lite>(jcb_e23_lite&,
								     const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
							       const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
								const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::jcb_e23_lite>(jcb_e23_lite&,
								 const jcb_e23_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
							       const jcb_e23_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::jcb_e23_lite>(const jcb_e23_lite&,
							     const jcb_e23_lite::value_type&);

//==============================================================================
// jcb_e33_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::jcb_e33_lite>(jcb_e33_lite&,
								const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
							  const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
								const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::jcb_e33_lite>(jcb_e33_lite&,
								 const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::jcb_e33_lite>(jcb_e33_lite&,
								     const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
							       const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
								const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::jcb_e33_lite>(jcb_e33_lite&,
								 const jcb_e33_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
							       const jcb_e33_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::jcb_e33_lite>(const jcb_e33_lite&,
							     const jcb_e33_lite::value_type&);

//==============================================================================
// met_e1_lite_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::met_e1_lite>(met_e1_lite&,
							       const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							 const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							       const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::met_e1_lite>(met_e1_lite&,
								const met_e1_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::met_e1_lite>(met_e1_lite&,
								    const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							      const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							       const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::met_e1_lite>(met_e1_lite&,
								const met_e1_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							      const met_e1_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::met_e1_lite>(const met_e1_lite&,
							    const met_e1_lite::value_type&);

//==============================================================================
// met_e2_lite_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::met_e2_lite>(met_e2_lite&,
							       const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							 const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							       const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::met_e2_lite>(met_e2_lite&,
								const met_e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::met_e2_lite>(met_e2_lite&,
								    const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							      const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							       const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::met_e2_lite>(met_e2_lite&,
								const met_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							      const met_e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::met_e2_lite>(const met_e2_lite&,
							    const met_e2_lite::value_type&);

//==============================================================================
// met_e3_lite_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::met_e3_lite>(met_e3_lite&,
							       const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							 const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							       const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::met_e3_lite>(met_e3_lite&,
								const met_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::met_e3_lite>(met_e3_lite&,
								    const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							      const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							       const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::met_e3_lite>(met_e3_lite&,
								const met_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							      const met_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::met_e3_lite>(const met_e3_lite&,
							    const met_e3_lite::value_type&);

//==============================================================================
// st2_e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::st2_e2_lite>(st2_e2_lite&,
							       const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							 const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							       const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::st2_e2_lite>(st2_e2_lite&,
								const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::st2_e2_lite>(st2_e2_lite&,
								    const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							      const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							       const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::st2_e2_lite>(st2_e2_lite&,
								const st2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							      const st2_e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::st2_e2_lite>(const st2_e2_lite&,
							    const st2_e2_lite::value_type&);

//==============================================================================
// st2_e3_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::st2_e3_lite>(st2_e3_lite&,
							       const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::vd_algebra::add<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							 const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::vd_algebra::operator+<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							       const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite&
fiber_bundle::vd_algebra::operator+=<fiber_bundle::st2_e3_lite>(st2_e3_lite&,
								const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::st2_e3_lite>(st2_e3_lite&,
								    const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::vd_algebra::subtract<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							      const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::vd_algebra::operator-<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							       const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite&
fiber_bundle::vd_algebra::operator-=<fiber_bundle::st2_e3_lite>(st2_e3_lite&,
								const st2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::vd_algebra::multiply<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							      const st2_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::st2_e3_lite>(const st2_e3_lite&,
							    const st2_e3_lite::value_type&);

//==============================================================================
// st3_e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::st3_e3_lite>(st3_e3_lite&,
							       const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							 const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							       const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::st3_e3_lite>(st3_e3_lite&,
								const st3_e3_lite&);

template
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::st3_e3_lite>(st3_e3_lite&,
								    const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							      const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							       const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::st3_e3_lite>(st3_e3_lite&,
								const st3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							      const st3_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::st3_e3_lite>(const st3_e3_lite&,
							    const st3_e3_lite::value_type&);

//==============================================================================
// st4_e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::st4_e2_lite>(st4_e2_lite&,
							       const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							 const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							       const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::st4_e2_lite>(st4_e2_lite&,
								const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::st4_e2_lite>(st4_e2_lite&,
								    const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							      const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							       const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::st4_e2_lite>(st4_e2_lite&,
								const st4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							      const st4_e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::st4_e2_lite>(const st4_e2_lite&,
							    const st4_e2_lite::value_type&);

//==============================================================================
// st4_e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::st4_e3_lite>(st4_e3_lite&,
							       const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							 const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							       const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::st4_e3_lite>(st4_e3_lite&,
								const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::st4_e3_lite>(st4_e3_lite&,
								    const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							      const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							       const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::st4_e3_lite>(st4_e3_lite&,
								const st4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							      const st4_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::st4_e3_lite>(const st4_e3_lite&,
							    const st4_e3_lite::value_type&);

//==============================================================================
// t2_e2_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::t2_e2_lite>(t2_e2_lite&,
							      const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							      const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::t2_e2_lite>(t2_e2_lite&,
							       const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::t2_e2_lite>(t2_e2_lite&,
								   const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							     const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							      const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::t2_e2_lite>(t2_e2_lite&,
							       const t2_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							     const t2_e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::t2_e2_lite>(const t2_e2_lite&,
							   const t2_e2_lite::value_type&);

//==============================================================================
// t2_e3_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::t2_e3_lite>(t2_e3_lite&,
							      const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							      const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::t2_e3_lite>(t2_e3_lite&,
							       const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::t2_e3_lite>(t2_e3_lite&,
								   const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							     const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							      const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::t2_e3_lite>(t2_e3_lite&,
							       const t2_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							     const t2_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::t2_e3_lite>(const t2_e3_lite&,
							   const t2_e3_lite::value_type&);

//==============================================================================
// t3_e3_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::t3_e3_lite>(t3_e3_lite&,
							      const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							      const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::t3_e3_lite>(t3_e3_lite&,
							       const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::t3_e3_lite>(t3_e3_lite&,
								   const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							     const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							      const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::t3_e3_lite>(t3_e3_lite&,
							       const t3_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite*
fiber_bundle::vd_algebra::multiply<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							     const t3_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3_lite*
fiber_bundle::vd_algebra::divide<fiber_bundle::t3_e3_lite>(const t3_e3_lite&,
							   const t3_e3_lite::value_type&);

//==============================================================================
// t4_e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::t4_e2_lite>(t4_e2_lite&,
							      const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							      const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::t4_e2_lite>(t4_e2_lite&,
							       const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::t4_e2_lite>(t4_e2_lite&,
								   const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							     const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							      const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::t4_e2_lite>(t4_e2_lite&,
							       const t4_e2_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							     const t4_e2_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::t4_e2_lite>(const t4_e2_lite&,
							   const t4_e2_lite::value_type&);

//==============================================================================
// t4_e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::add_equal<fiber_bundle::t4_e3_lite>(t4_e3_lite&,
							      const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::add<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::operator+<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							      const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite& 
fiber_bundle::vd_algebra::operator+=<fiber_bundle::t4_e3_lite>(t4_e3_lite&,
							       const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::vd_algebra::subtract_equal<fiber_bundle::t4_e3_lite>(t4_e3_lite&,
								   const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::subtract<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							     const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::operator-<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							      const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite& 
fiber_bundle::vd_algebra::operator-=<fiber_bundle::t4_e3_lite>(t4_e3_lite&,
							       const t4_e3_lite&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::multiply<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							     const t4_e3_lite::value_type&);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3_lite* 
fiber_bundle::vd_algebra::divide<fiber_bundle::t4_e3_lite>(const t4_e3_lite&,
							   const t4_e3_lite::value_type&);

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
