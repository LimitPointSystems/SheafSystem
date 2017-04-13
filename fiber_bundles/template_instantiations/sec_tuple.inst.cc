
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

// Explicit instantiations for class sec_tuple.

#include "SheafSystem/sec_tuple.impl.h"

#include "SheafSystem/at0.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/at2.h"
#include "SheafSystem/at2_e2.h"
#include "SheafSystem/at2_e3.h"
#include "SheafSystem/at3.h"
#include "SheafSystem/at3_e3.h"
#include "SheafSystem/atp.h"
#include "SheafSystem/atp_space.h"
#include "SheafSystem/e1.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/e4.h"
#include "SheafSystem/ed.h"
#include "SheafSystem/jcb.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_e23.h"
#include "SheafSystem/jcb_e33.h"
#include "SheafSystem/jcb_ed.h"
#include "SheafSystem/jcb_space.h"
#include "SheafSystem/met.h"
#include "SheafSystem/met_e1.h"
#include "SheafSystem/met_e2.h"
#include "SheafSystem/met_e3.h"
#include "SheafSystem/met_ed.h"
#include "SheafSystem/st2.h"
#include "SheafSystem/st2_e2.h"
#include "SheafSystem/st2_e3.h"
#include "SheafSystem/st3.h"
#include "SheafSystem/st3_e3.h"
#include "SheafSystem/st4.h"
#include "SheafSystem/st4_e2.h"
#include "SheafSystem/st4_e3.h"
#include "SheafSystem/stp.h"
#include "SheafSystem/stp_space.h"
#include "SheafSystem/t2.h"
#include "SheafSystem/t2_e2.h"
#include "SheafSystem/t2_e3.h"
#include "SheafSystem/t3.h"
#include "SheafSystem/t3_e3.h"
#include "SheafSystem/t4.h"
#include "SheafSystem/t4_e2.h"
#include "SheafSystem/t4_e3.h"
#include "SheafSystem/tp.h"
#include "SheafSystem/tp_space.h"
#include "SheafSystem/tuple.h"
#include "SheafSystem/tuple_space.h"
#include "SheafSystem/vd.h"
#include "SheafSystem/vd_space.h"

#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_at1.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/sec_at2.h"
#include "SheafSystem/sec_at2_e2.h"
#include "SheafSystem/sec_at2_e3.h"
#include "SheafSystem/sec_at3.h"
#include "SheafSystem/sec_at3_e3.h"
#include "SheafSystem/sec_atp.h"
#include "SheafSystem/sec_atp_space.h"
#include "SheafSystem/sec_e1.h"
#include "SheafSystem/sec_e1_uniform.h"
#include "SheafSystem/sec_e2.h"
#include "SheafSystem/sec_e2_uniform.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_e3_uniform.h"
#include "SheafSystem/sec_e4.h"
#include "SheafSystem/sec_ed.h"
#include "SheafSystem/sec_jcb.h"
#include "SheafSystem/sec_jcb_e13.h"
#include "SheafSystem/sec_jcb_e23.h"
#include "SheafSystem/sec_jcb_e33.h"
#include "SheafSystem/sec_jcb_ed.h"
#include "SheafSystem/sec_jcb_space.h"
#include "SheafSystem/sec_met.h"
#include "SheafSystem/sec_met_e1.h"
#include "SheafSystem/sec_met_e2.h"
#include "SheafSystem/sec_met_e3.h"
#include "SheafSystem/sec_met_ed.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/sec_rep_descriptor_poset.h"
#include "SheafSystem/sec_rep_descriptor_table_dofs_type.h"
#include "SheafSystem/sec_rep_space.h"
#include "SheafSystem/sec_rep_space_member.h"
#include "SheafSystem/sec_st2.h"
#include "SheafSystem/sec_st2_e2.h"
#include "SheafSystem/sec_st2_e3.h"
#include "SheafSystem/sec_st3.h"
#include "SheafSystem/sec_st3_e3.h"
#include "SheafSystem/sec_st4.h"
#include "SheafSystem/sec_st4_e2.h"
#include "SheafSystem/sec_st4_e3.h"
#include "SheafSystem/sec_stp.h"
#include "SheafSystem/sec_stp_space.h"
#include "SheafSystem/sec_t2.h"
#include "SheafSystem/sec_t2_e2.h"
#include "SheafSystem/sec_t2_e3.h"
#include "SheafSystem/sec_t3.h"
#include "SheafSystem/sec_t3_e3.h"
#include "SheafSystem/sec_t4.h"
#include "SheafSystem/sec_t4_e2.h"
#include "SheafSystem/sec_t4_e3.h"
#include "SheafSystem/sec_tp.h"
#include "SheafSystem/sec_tp_space.h"
#include "SheafSystem/sec_tuple.h"
#include "SheafSystem/sec_tuple_space.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/sec_vd_space.h"

using namespace std;


//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//
// sec_at0
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_at0>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_at0>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_at2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_at2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_at2_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_at2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_at2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_at2_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_at3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_at3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_at3_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e1
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e1>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e1>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e1_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e1_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e1_uniform>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e2_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e2_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e2_uniform>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e3_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e3_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e3_uniform>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_e4
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_e4>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_e4>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_jcb_e13
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_jcb_e13>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_jcb_e13>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_jcb_e23
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_jcb_e23>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_jcb_e23>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_jcb_e33
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_jcb_e33>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_jcb_e33>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_met_e1
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_met_e1>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_met_e1>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_met_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_met_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_met_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_met_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_met_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_met_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_st2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_st2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_st2_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_st2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_st2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_st2_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_st3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_st3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_st3_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_st4_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_st4_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_st4_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_st4_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_st4_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_st4_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_t2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_t2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_t2_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_t2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_t2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_t2_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_t3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_t3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_t3_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_t4_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_t4_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_t4_e2>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//
// sec_t4_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::sec_tuple::
standard_host_path<fiber_bundle::sec_t4_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

template
SHEAF_DLL_SPEC
bool
fiber_bundle::sec_tuple::
standard_host_is_available<fiber_bundle::sec_t4_e3>(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

