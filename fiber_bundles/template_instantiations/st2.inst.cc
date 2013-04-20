
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class st2.

#include "st2.impl.h"

#include "st2_e2.h"
#include "gl2.h"

#include "st2_e3.h"
#include "gl3.h"


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

