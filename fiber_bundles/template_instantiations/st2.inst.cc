
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

// Explicit_instantiations for class st2.

#include "SheafSystem/st2.impl.h"

#include "SheafSystem/st2_e2.h"
#include "SheafSystem/gl2.h"

#include "SheafSystem/st2_e3.h"
#include "SheafSystem/gl3.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


#ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================


//==============================================================================
// st2_e2_lite
//==============================================================================

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite*
fiber_bundle::st2_algebra::to_principal_axes<fiber_bundle::st2_e2_lite>(const st2_e2_lite& xlite,
									const gl2_lite& xtransform);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::st2_algebra::to_principal_axes<fiber_bundle::st2_e2_lite>(const st2_e2_lite& xlite,
									const gl2_lite& xtransform,
									st2_e2_lite& xresult);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::st2_algebra::to_principal_axes<fiber_bundle::st2_e2_lite>(const st2_e2_lite& xlite,
									const st2_e2_lite& xpd_lite,
									const gl2_lite& xtransform,
									st2_e2_lite& xresult);


//==============================================================================
// st2_e3_lite
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::st2_algebra::to_principal_axes<fiber_bundle::st2_e3_lite>(const st2_e3_lite& xlite,
									const gl3_lite& xtransform);

template 
SHEAF_DLL_SPEC
void 
fiber_bundle::st2_algebra::to_principal_axes<fiber_bundle::st2_e3_lite>(const st2_e3_lite& xlite,
									const gl3_lite& xtransform,
									st2_e3_lite& xresult);

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

