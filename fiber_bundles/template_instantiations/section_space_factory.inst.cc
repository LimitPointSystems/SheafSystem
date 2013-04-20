
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class section_space_factory.

#include "section_space_factory.impl.h"

#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3_e3.h"
#include "sec_atp_space.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st3_e3.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_stp_space.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t3_e3.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_tp_space.h"

//#include "sec_jcb_e13.h"
//#include "sec_jcb_e23.h"
//#include "sec_jcb_e33.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATION FOR "CONCRETE" FIBER TYPES
//==============================================================================

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_at0>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_at2_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_at2_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_at3_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e1>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e1_uniform>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e2_uniform>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_e3_uniform>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_met_e1>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_met_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_met_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_st2_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_st2_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_st3_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_st4_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_st4_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_t2_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_t2_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_t3_e3>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_t4_e2>;

template class
SHEAF_DLL_SPEC
fiber_bundle::section_space_factory<fiber_bundle::sec_t4_e3>;

// template class
// SHEAF_DLL_SPEC
// fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e13>;

// template class
// SHEAF_DLL_SPEC
// fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e23>;

// template class
// SHEAF_DLL_SPEC
// fiber_bundle::section_space_factory<fiber_bundle::sec_jcb_e33>;

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS


