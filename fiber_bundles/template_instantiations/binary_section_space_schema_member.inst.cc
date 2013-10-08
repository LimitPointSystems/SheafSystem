
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

// Explicit instantiations for class binary_section_space_schema_member.

#include "binary_section_space_schema_member.impl.h"

#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "at2.h"
#include "at2_e2.h"
#include "at2_e3.h"
#include "at3.h"
#include "at3_e3.h"
#include "atp.h"
#include "atp_space.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "ed.h"
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
#include "jcb_space.h"
#include "met.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"
#include "met_ed.h"
#include "st2.h"
#include "st2_e2.h"
#include "st2_e3.h"
#include "st3.h"
#include "st3_e3.h"
#include "st4.h"
#include "st4_e2.h"
#include "st4_e3.h"
#include "stp.h"
#include "stp_space.h"
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "t4.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "tp.h"
#include "tp_space.h"
#include "tuple.h"
#include "tuple_space.h"
#include "vd.h"
#include "vd_space.h"

#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_at2.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3.h"
#include "sec_at3_e3.h"
#include "sec_atp.h"
#include "sec_atp_space.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "sec_e4.h"
#include "sec_ed.h"
#include "sec_jcb.h"
#include "sec_jcb_e13.h"
#include "sec_jcb_e23.h"
#include "sec_jcb_e33.h"
#include "sec_jcb_ed.h"
#include "sec_jcb_space.h"
#include "sec_met.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_met_ed.h"
#include "sec_rep_descriptor.h"
#include "sec_rep_descriptor_poset.h"
#include "sec_rep_descriptor_table_dofs_type.h"
#include "sec_rep_space.h"
#include "sec_rep_space_member.h"
#include "sec_st2.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st3.h"
#include "sec_st3_e3.h"
#include "sec_st4.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_stp.h"
#include "sec_stp_space.h"
#include "sec_t2.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t3.h"
#include "sec_t3_e3.h"
#include "sec_t4.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_tp.h"
#include "sec_tp_space.h"
#include "sec_tuple.h"
#include "sec_tuple_space.h"
#include "sec_vd.h"
#include "sec_vd_space.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================

//
// sec_at0
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_at0>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_at0>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_at0>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_at0>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_at0>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_at0_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_at0_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_at0_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_at0_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_at0_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_at0_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_at1
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_at1>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_at1>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_at1>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_at1>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_at1>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_at1_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_at1_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_at1_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_at1_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_at1_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_at1_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_at2
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_at2>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_at2>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_at2>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_at2>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_at2>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_at2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_at2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_at2_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_at2_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_at2_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_at2_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_at2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_at2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_at2_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_at2_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_at2_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_at2_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_at3
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_at3>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_at3>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_at3>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_at3>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_at3>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_at3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_at3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_at3_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_at3_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_at3_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_at3_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_atp
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_atp>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_atp>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_atp>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_atp>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_atp>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_atp_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_atp_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_atp_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_atp_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_atp_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_atp_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_e1
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e1>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e1>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e1>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e1>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e1>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e1_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e1_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e1_uniform>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e1_uniform>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e1_uniform>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e1_uniform>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e2_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e2_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e2_uniform>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e2_uniform>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e2_uniform>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e2_uniform>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e3_uniform
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e3_uniform>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e3_uniform>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e3_uniform>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e3_uniform>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e3_uniform>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_e4
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_e4>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_e4>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_e4>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_e4>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_e4>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_ed
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_ed>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_ed>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_ed>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_ed>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_ed>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_jcb
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_jcb>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_jcb>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_jcb>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_jcb>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_jcb>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_jcb_e13
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_jcb_e13>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_jcb_e13>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_jcb_e13>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_jcb_e13>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_jcb_e13>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_jcb_e23
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_jcb_e23>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_jcb_e23>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_jcb_e23>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_jcb_e23>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_jcb_e23>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_jcb_e33
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_jcb_e33>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_jcb_e33>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_jcb_e33>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_jcb_e33>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_jcb_e33>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_jcb_ed
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_jcb_ed>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_jcb_ed>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_jcb_ed>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_jcb_ed>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_jcb_ed>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_jcb_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_jcb_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_jcb_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_jcb_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_jcb_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_jcb_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_met
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_met>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_met>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_met>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_met>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_met>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_met_e1
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_met_e1>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_met_e1>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_met_e1>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_met_e1>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_met_e1>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
//  sec_met_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_met_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_met_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_met_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_met_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_met_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
//  sec_met_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_met_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_met_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_met_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_met_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_met_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_met_ed
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_met_ed>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_met_ed>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_met_ed>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_met_ed>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_met_ed>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);
//
////
//// nonleaf sec_rep_descriptor
////
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_rep_descriptor>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_rep_descriptor>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_rep_descriptor>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_rep_descriptor>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_rep_descriptor>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);
//
////
//// nonleaf sec_rep_descriptor_poset
////
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_rep_descriptor_poset>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_rep_descriptor_poset>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_rep_descriptor_poset>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);
//
////
//// nonleaf sec_rep_descriptor_table_dofs_type
////
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_rep_descriptor_table_dofs_type>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_rep_descriptor_table_dofs_type>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_rep_descriptor_table_dofs_type>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_rep_descriptor_table_dofs_type>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_rep_descriptor_table_dofs_type>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_rep_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_rep_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_rep_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_rep_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_rep_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_rep_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);
//
////
//// nonleaf sec_rep_space_member
////
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_rep_space_member>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_rep_space_member>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_rep_space_member>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_rep_space_member>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_rep_space_member>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);
//
////
//// nonleaf sec_st2
////
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_st2>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_st2>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_st2>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_st2>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_st2>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_st2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_st2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_st2_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_st2_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_st2_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_st2_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_st2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_st2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_st2_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_st2_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_st2_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_st2_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_st3
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_st3>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_st3>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_st3>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_st3>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_st3>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_st3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_st3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_st3_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_st3_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_st3_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_st3_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_st4
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_st4>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_st4>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_st4>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_st4>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_st4>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_st4_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_st4_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_st4_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_st4_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_st4_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_st4_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_st4_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_st4_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_st4_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_st4_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_st4_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_st4_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_stp
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_stp>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_stp>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_stp>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_stp>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_stp>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_stp_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_stp_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_stp_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_stp_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_stp_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_stp_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_t2
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_t2>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_t2>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_t2>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_t2>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_t2>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_t2_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_t2_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_t2_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_t2_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_t2_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_t2_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// sec_t2_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_t2_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_t2_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_t2_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_t2_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_t2_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_t3
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_t3>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_t3>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_t3>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_t3>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_t3>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_t3_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_t3_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_t3_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_t3_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_t3_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_t3_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_t4
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_t4>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_t4>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_t4>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_t4>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_t4>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_t4_e2
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_t4_e2>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_t4_e2>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_t4_e2>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_t4_e2>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_t4_e2>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
//  sec_t4_e3
//

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_host_path<fiber_bundle::sec_t4_e3>(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member_path<fiber_bundle::sec_t4_e3>(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
bool
fiber_bundle::binary_section_space_schema_member::
standard_host_is_available<fiber_bundle::sec_t4_e3>(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::binary_section_space_schema_member::host_type&
fiber_bundle::binary_section_space_schema_member::
standard_host<fiber_bundle::sec_t4_e3>(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::binary_section_space_schema_member::
standard_member<fiber_bundle::sec_t4_e3>(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);

//
// nonleaf sec_tp
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_tp>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_tp>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_tp>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_tp>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_tp>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_tp_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_tp_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_tp_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_tp_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_tp_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_tp_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// nonleaf sec_tuple
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_tuple>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_tuple>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_tuple>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_tuple>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_tuple>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_tuple_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_tuple_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_tuple_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_tuple_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_tuple_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_tuple_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_vd
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_vd>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_vd>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_vd>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_vd>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_vd>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

//
// sec_vd_space
//

//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_host_path<fiber_bundle::sec_vd_space>(const poset_path& xbase_path,
//                                       const poset_path& xrep_path,
//                                       const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member_path<fiber_bundle::sec_vd_space>(const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix);
//
//
//template
//SHEAF_DLL_SPEC
//bool
//fiber_bundle::binary_section_space_schema_member::
//standard_host_is_available<fiber_bundle::sec_vd_space>(namespace_poset& xns,
//                                         const poset_path& xbase_path,
//                                         const poset_path& xrep_path,
//                                         const string& xfiber_suffix,
//                                         bool xauto_access);
//
//
//template
//SHEAF_DLL_SPEC
//fiber_bundle::binary_section_space_schema_member::host_type&
//fiber_bundle::binary_section_space_schema_member::
//standard_host<fiber_bundle::sec_vd_space>(namespace_type& xns,
//                                  const poset_path& xbase_path,
//                                  const poset_path& xrep_path,
//                                  const string& xfiber_suffix,
//                                  bool xauto_access);
//
//template
//SHEAF_DLL_SPEC
//sheaf::poset_path
//fiber_bundle::binary_section_space_schema_member::
//standard_member<fiber_bundle::sec_vd_space>(namespace_type& xns,
//                                    const poset_path& xbase_path,
//                                    const poset_path& xrep_path,
//                                    const string& xfiber_suffix,
//                                    bool xauto_access);

