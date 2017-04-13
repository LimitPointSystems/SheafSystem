
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

// Explicit_instantiations for class tp.

#include "SheafSystem/tp.impl.h"

#include "SheafSystem/t2_e2.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/st2_e2.h"

#include "SheafSystem/t2_e3.h"
#include "SheafSystem/at2_e3.h"
#include "SheafSystem/st2_e3.h"

#include "SheafSystem/t3_e3.h"
#include "SheafSystem/at3_e3.h"
#include "SheafSystem/st3_e3.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR TP FACET
//==============================================================================


//==============================================================================
// t2_e2_lite
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite*
fiber_bundle::tp_algebra::alt<fiber_bundle::t2_e2_lite>(const t2_e2_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite*
fiber_bundle::tp_algebra::sym<fiber_bundle::t2_e2_lite>(const t2_e2_lite&);

//==============================================================================
// t2_e3_lite
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e3_lite*
fiber_bundle::tp_algebra::alt<fiber_bundle::t2_e3_lite>(const t2_e3_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite*
fiber_bundle::tp_algebra::sym<fiber_bundle::t2_e3_lite>(const t2_e3_lite&);


//==============================================================================
// t3_e3_lite
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at3_e3_lite*
fiber_bundle::tp_algebra::alt<fiber_bundle::t3_e3_lite>(const t3_e3_lite&);

template
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite*
fiber_bundle::tp_algebra::sym<fiber_bundle::t3_e3_lite>(const t3_e3_lite&);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
