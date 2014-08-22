
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//

// Explicit_instantiations for class tuple.

#include "ComLimitPoint/fiber_bundle/tuple.impl.h"

#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/at2_e2.h"
#include "ComLimitPoint/fiber_bundle/at2_e3.h"
#include "ComLimitPoint/fiber_bundle/at3_e3.h"
#include "ComLimitPoint/fiber_bundle/e1.h"
#include "ComLimitPoint/fiber_bundle/e2.h"
#include "ComLimitPoint/fiber_bundle/e3.h"
#include "ComLimitPoint/fiber_bundle/e4.h"
#include "ComLimitPoint/fiber_bundle/jcb_e13.h"
#include "ComLimitPoint/fiber_bundle/jcb_e23.h"
#include "ComLimitPoint/fiber_bundle/jcb_e33.h"
#include "ComLimitPoint/fiber_bundle/met_e1.h"
#include "ComLimitPoint/fiber_bundle/met_e2.h"
#include "ComLimitPoint/fiber_bundle/met_e3.h"
#include "ComLimitPoint/fiber_bundle/st2_e2.h"
#include "ComLimitPoint/fiber_bundle/st2_e3.h"
#include "ComLimitPoint/fiber_bundle/st3_e3.h"
#include "ComLimitPoint/fiber_bundle/st4_e2.h"
#include "ComLimitPoint/fiber_bundle/st4_e3.h"
#include "ComLimitPoint/fiber_bundle/t2_e2.h"
#include "ComLimitPoint/fiber_bundle/t2_e3.h"
#include "ComLimitPoint/fiber_bundle/t3_e3.h"
#include "ComLimitPoint/fiber_bundle/t4_e2.h"
#include "ComLimitPoint/fiber_bundle/t4_e3.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR HOST FACTORY FACET
//==============================================================================

// at0

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::at0>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::at0>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// at2_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::at2_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::at2_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// at2_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::at2_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::at2_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// at3_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::at3_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::at3_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// e1

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::e1>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::e1>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// e4

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::e4>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::e4>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// jcb_e13

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::jcb_e13>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::jcb_e13>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// jcb_e23

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::jcb_e23>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::jcb_e23>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// jcb_e33

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::jcb_e33>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::jcb_e33>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// met_e1

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::met_e1>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::met_e1>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// met_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::met_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::met_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// met_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::met_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::met_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// st2_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::st2_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::st2_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// st2_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::st2_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::st2_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// st3_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::st3_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::st3_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// st4_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::st4_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::st4_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// st4_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::st4_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::st4_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// t2_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::t2_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::t2_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// t2_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::t2_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::t2_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// t3_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::t3_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::t3_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// t4_e2

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::t4_e2>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::t4_e2>(namespace_type& xns, const string& xsuffix, bool xauto_access);

// t4_e3

template 
SHEAF_DLL_SPEC 
sheaf::poset_path
fiber_bundle::tuple::
standard_host_path<fiber_bundle::t4_e3>(const string& xsuffix);

template 
SHEAF_DLL_SPEC 
bool
fiber_bundle::tuple::
standard_host_is_available<fiber_bundle::t4_e3>(namespace_type& xns, const string& xsuffix, bool xauto_access);

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
