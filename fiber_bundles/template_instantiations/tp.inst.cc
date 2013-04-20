
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit_instantiations for class tp.

#include "tp.impl.h"

#include "t2_e2.h"
#include "at2_e2.h"
#include "st2_e2.h"

#include "t2_e3.h"
#include "at2_e3.h"
#include "st2_e3.h"

#include "t3_e3.h"
#include "at3_e3.h"
#include "st3_e3.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR TP FACET
//==============================================================================


//==============================================================================
// t2_e2_lite
//==============================================================================


// template
// SHEAF_DLL_SPEC
// fiber_bundle::tensor_traits<fiber_bundle::t2_e2_lite::P,
//                             fiber_bundle::t2_e2_lite::vector_space_type>::atp_type*
// fiber_bundle::alt(const t2_e2_lite& x0);

// template
// SHEAF_DLL_SPEC
// fiber_bundle::tensor_traits<fiber_bundle::t2_e2_lite::P,
//                             fiber_bundle::t2_e2_lite::vector_space_type>::stp_type*
// fiber_bundle::sym(const t2_e2_lite& x0);

// template
// SHEAF_DLL_SPEC
// fiber_bundle::tensor_traits<fiber_bundle::t2_e2::P,
//                             fiber_bundle::t2_e2::vector_space_type>::atp_type*
// fiber_bundle::alt(const t2_e2& x0, bool xauto_access);

// template
// SHEAF_DLL_SPEC
// fiber_bundle::tensor_traits<fiber_bundle::t2_e2::P,
//                             fiber_bundle::t2_e2::vector_space_type>::stp_type*
// fiber_bundle::sym(const t2_e2& x0, bool xauto_access);

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

//==============================================================================
// t4_e2_lite
//==============================================================================


// template fiber_bundle::t4_e2_lite* fiber_bundle::alt(const t4_e2_lite&);
// template fiber_bundle::t4_e2_lite* fiber_bundle::sym(const t4_e2_lite&);

//==============================================================================
// t4_e3_lite
//==============================================================================

// template fiber_bundle::t4_e3_lite* fiber_bundle::alt(const t4_e3_lite&);
// template fiber_bundle::t4_e3_lite* fiber_bundle::sym(const t4_e3_lite&);

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
