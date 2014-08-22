
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

// Explicit_instantiations for class ed.

#include "ed.impl.h"

#include "ComLimitPoint/fiber_bundle/e1.h"
#include "ComLimitPoint/fiber_bundle/e2.h"
#include "ComLimitPoint/fiber_bundle/e3.h"
#include "ComLimitPoint/fiber_bundle/e4.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//==============================================================================
// e1
//==============================================================================

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e1>(e1&, bool);

//==============================================================================
// e1_lite
//==============================================================================

template 
SHEAF_DLL_SPEC 
fiber_bundle::e1_lite::value_type 
fiber_bundle::ed_algebra::operator*<fiber_bundle::e1_lite>(const e1_lite&, const e1_lite&);

template 
SHEAF_DLL_SPEC 
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e1_lite>(e1_lite&);

//==============================================================================
// e2
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e2>(e2&, bool);

//==============================================================================
// e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite::value_type 
fiber_bundle::ed_algebra::operator*<fiber_bundle::e2_lite>(const e2_lite&, const e2_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e2_lite>(e2_lite&);

//==============================================================================
// e3
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e3>(e3&, bool);

//==============================================================================
// e3_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite::value_type 
fiber_bundle::ed_algebra::operator*<fiber_bundle::e3_lite>(const e3_lite&, const e3_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e3_lite>(e3_lite&);

//==============================================================================
// e4
//==============================================================================

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e4>(e4&, bool);

//==============================================================================
// e4_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite::value_type
fiber_bundle::ed_algebra::operator*<fiber_bundle::e4_lite>(const e4_lite&, const e4_lite&);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::ed_algebra::normalize<fiber_bundle::e4_lite>(e4_lite&);

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
