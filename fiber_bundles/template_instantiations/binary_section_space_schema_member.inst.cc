
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

#include "fiber_bundles_namespace.h"
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
#include "dtypeh"
#include "e3.h"
#include "e4.h"
#include "ed.h"
#include "gl1.h"
#include "gl2.h"
#include "gl3.h"
#include "gln.h"
#include "gln_space.h"
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
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
#include "st4_e2.h"
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
#include "vd.h"

//==============================================================================
// EXPLICIT INSTANTIATIONS
//==============================================================================


  //
  // at0
  //

template
SHEAF_DLL_SPEC
<fiber_bundle::at0>
static poset_path standard_host_path(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0>
static poset_path standard_member_path(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0>
static bool standard_host_is_available(namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix,
                                         bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0>
static host_type& standard_host(namespace_type& xns,
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xfiber_suffix,
                                  bool xauto_access);

template
SHEAF_DLL_SPEC
<fiber_bundle::at0>
static poset_path standard_member(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);


  //
  // at0_space
  //

 template
 SHEAF_DLL_SPEC
 <fiber_bundle::at0_space>
 static poset_path standard_host_path(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                           const poset_path& xrep_path,
                                           const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0_space>
static bool standard_host_is_available(namespace_poset& xns,
                                           const poset_path& xbase_path,
                                           const poset_path& xrep_path,
                                           const string& xfiber_suffix,
                                           bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0_space>
static host_type& standard_host(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at0_space>
static poset_path standard_member(namespace_type& xns,
                                      const poset_path& xbase_path,
                                      const poset_path& xrep_path,
                                      const string& xfiber_suffix,
                                      bool xauto_access);

 //
 // at1
 //

template
SHEAF_DLL_SPEC
<fiber_bundle::at1>
 static poset_path standard_host_path(const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1>
static poset_path standard_member_path(const poset_path& xbase_path,
                                           const poset_path& xrep_path,
                                           const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1>
static bool standard_host_is_available(namespace_poset& xns,
                                           const poset_path& xbase_path,
                                           const poset_path& xrep_path,
                                           const string& xfiber_suffix,
                                           bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1>
static host_type& standard_host(namespace_type& xns,
                                    const poset_path& xbase_path,
                                    const poset_path& xrep_path,
                                    const string& xfiber_suffix,
                                    bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1>
static poset_path standard_member(namespace_type& xns,
                                      const poset_path& xbase_path,
                                      const poset_path& xrep_path,
                                      const string& xfiber_suffix,
                                      bool xauto_access);

//
// at1_space
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at1_space>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1_space>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1_space>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at1_space>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// at2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// at2_e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// at2_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at2_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// at3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);


//
// at3_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::at3_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::at3_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);


//
// atp
//

template
SHEAF_DLL_SPEC
<fiber_bundle::atp>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::atp>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::atp>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::atp>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::atp>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// e1
//

template
SHEAF_DLL_SPEC
<fiber_bundle::e1>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e1>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e1>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e1>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e1>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// e4
//

template
SHEAF_DLL_SPEC
<fiber_bundle::e4>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e4>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::e4>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e4>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::e4>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// ed
//

template
SHEAF_DLL_SPEC
<fiber_bundle::ed>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::ed>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::ed>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::ed>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::ed>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);


//
// gl2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::gl2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// gl3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::gl3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gl3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// gln
//

template
SHEAF_DLL_SPEC
<fiber_bundle::gln>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// gln_space
//

template
SHEAF_DLL_SPEC
<fiber_bundle::gln_space>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln_space>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln_space>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::gln_space>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// jcb
//

template
SHEAF_DLL_SPEC
<fiber_bundle::jcb>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// jcb_e13
//

template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e13>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e13>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e13>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e13>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e13>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// jcb_e23
//

template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e23>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e23>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e23>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e23>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e23>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// jcb_e33
//

template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e33>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e33>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e33>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e33>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_e33>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// jcb_space
//

template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_space>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_space>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_space>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::jcb_space>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// met
//

template
SHEAF_DLL_SPEC
<fiber_bundle::met>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// met_e1
//

template
SHEAF_DLL_SPEC
<fiber_bundle::met_e1>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e1>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e1>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e1>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e1>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// met_e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::met_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// met_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::met_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// met_ed
//

template
SHEAF_DLL_SPEC
<fiber_bundle::met_ed>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_ed>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_ed>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_ed>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::met_ed>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st2_e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st2_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st2_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st3_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st3_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st3_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st4
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st4>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st4_e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// st4_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::st4_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// stp
//

template
SHEAF_DLL_SPEC
<fiber_bundle::stp>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// stp_space
//

template
SHEAF_DLL_SPEC
<fiber_bundle::stp_space>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp_space>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp_space>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::stp_space>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t2_e2
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t2_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t2_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t3_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t3_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t3_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t4
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t4>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// dtype
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e2>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e2>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e2>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e2>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e2>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// t4_e3
//

template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e3>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e3>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e3>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e3>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::t4_e3>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// tp
//

template
SHEAF_DLL_SPEC
<fiber_bundle::tp>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// tp_space
//

template
SHEAF_DLL_SPEC
<fiber_bundle::tp_space>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp_space>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp_space>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp_space>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::tp_space>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

//
// vd
//

template
SHEAF_DLL_SPEC
<fiber_bundle::vd>
static poset_path standard_host_path(const poset_path& xbase_path,
                                        const poset_path& xrep_path,
                                        const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::vd>
static poset_path standard_member_path(const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix);


template
SHEAF_DLL_SPEC
<fiber_bundle::vd>
static bool standard_host_is_available(namespace_poset& xns,
                                          const poset_path& xbase_path,
                                          const poset_path& xrep_path,
                                          const string& xfiber_suffix,
                                          bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::vd>
static host_type& standard_host(namespace_type& xns,
                                   const poset_path& xbase_path,
                                   const poset_path& xrep_path,
                                   const string& xfiber_suffix,
                                   bool xauto_access);


template
SHEAF_DLL_SPEC
<fiber_bundle::vd>
static poset_path standard_member(namespace_type& xns,
                                     const poset_path& xbase_path,
                                     const poset_path& xrep_path,
                                     const string& xfiber_suffix,
                                     bool xauto_access);

