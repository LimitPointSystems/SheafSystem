
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

// Explicit instantiations for class abstract_poset_member.

#include "SheafSystem/abstract_poset_member.impl.h"

#include "SheafSystem/fiber_bundles_namespace.h"
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
#include "SheafSystem/e1.h"
#include "SheafSystem/e2.h"
#include "SheafSystem/e3.h"
#include "SheafSystem/e4.h"
#include "SheafSystem/ed.h"
#include "SheafSystem/gl2.h"
#include "SheafSystem/gl3.h"
#include "SheafSystem/gln.h"
#include "SheafSystem/gln_space.h"
#include "SheafSystem/jcb.h"
#include "SheafSystem/jcb_e13.h"
#include "SheafSystem/jcb_e23.h"
#include "SheafSystem/jcb_e33.h"
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
#include "SheafSystem/vd.h"

#ifndef DOXYGEN_SKIP_INSTANTIATIONS


//==============================================================================
// EXPLICIT INSTANTIATIONS FOR FIBER CLASSES
//==============================================================================

//==============================================================================
// CLASS AT0_LITE
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::at0_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0_lite>(fiber_bundle::at0_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at0_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0_lite>(const fiber_bundle::at0_lite& x0);


//==============================================================================
// CLASS AT0
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::at0::table_dofs_type&
sheaf::table_dofs<fiber_bundle::at0>(fiber_bundle::at0& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at0::table_dofs_type&
sheaf::table_dofs<fiber_bundle::at0>(const fiber_bundle::at0& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::at0::table_dofs_type&
sheaf::table_dofs<fiber_bundle::at0>(fiber_bundle::at0& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at0::table_dofs_type&
sheaf::table_dofs<fiber_bundle::at0>(const fiber_bundle::at0& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
fiber_bundle::at0::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0>(fiber_bundle::at0& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at0::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0>(const fiber_bundle::at0& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::at0::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0>(fiber_bundle::at0& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at0::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at0>(const fiber_bundle::at0& x0, bool xauto_access);


//==============================================================================
// CLASS AT1_LITE
//==============================================================================

// template 
// SHEAF_DLL_SPEC
// fiber_bundle::at1_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at1_lite>(fiber_bundle::at1_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::at1_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at1_lite>(const fiber_bundle::at1_lite& x0);

//==============================================================================
// CLASS AT1
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS AT2_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::at2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at2_lite>(fiber_bundle::at2_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::at2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at2_lite>(const fiber_bundle::at2_lite& x0);

//==============================================================================
// CLASS AT2
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS AT2_E2_LITE
//==============================================================================

template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2_lite>(fiber_bundle::at2_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2_lite>(const fiber_bundle::at2_e2_lite& x0);

//==============================================================================
// CLASS AT2_E2
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2>(fiber_bundle::at2_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2>(const fiber_bundle::at2_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2>(fiber_bundle::at2_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e2>(const fiber_bundle::at2_e2& x0, bool xauto_access);


//==============================================================================
// CLASS AT2_E3_LITE
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3_lite>(fiber_bundle::at2_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3_lite>(const fiber_bundle::at2_e3_lite& x0);


//==============================================================================
// CLASS AT2_E3
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3>(fiber_bundle::at2_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3>(const fiber_bundle::at2_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::at2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3>(fiber_bundle::at2_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at2_e3>(const fiber_bundle::at2_e3& x0, bool xauto_access);


//==============================================================================
// CLASS AT3_LITE
//==============================================================================

// template 
// SHEAF_DLL_SPEC
// fiber_bundle::at3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at3_lite>(fiber_bundle::at3_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::at3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::at3_lite>(const fiber_bundle::at3_lite& x0);

//==============================================================================
// CLASS AT3
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS AT3_E3_LITE
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::at3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3_lite>(fiber_bundle::at3_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3_lite>(const fiber_bundle::at3_e3_lite& x0);


//==============================================================================
// CLASS AT3_E3
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::at3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3>(fiber_bundle::at3_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3>(const fiber_bundle::at3_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::at3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3>(fiber_bundle::at3_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::at3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::at3_e3>(const fiber_bundle::at3_e3& x0, bool xauto_access);


//==============================================================================
// CLASS ATP_LITE
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS ATP
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::atp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::atp>(fiber_bundle::atp& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::atp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::atp>(const fiber_bundle::atp& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::atp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::atp>(fiber_bundle::atp& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::atp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::atp>(const fiber_bundle::atp& x0, bool xauto_access);


//==============================================================================
// CLASS E1_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::e1_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1_lite>(fiber_bundle::e1_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e1_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1_lite>(const fiber_bundle::e1_lite& x0);


//==============================================================================
// CLASS E1
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1>(fiber_bundle::e1& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1>(const fiber_bundle::e1& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1>(fiber_bundle::e1& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e1>(const fiber_bundle::e1& x0, bool xauto_access);


//==============================================================================
// CLASS E2_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2_lite>(fiber_bundle::e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2_lite>(const fiber_bundle::e2_lite& x0);


//==============================================================================
// CLASS E2
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2>(fiber_bundle::e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2>(const fiber_bundle::e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2>(fiber_bundle::e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e2>(const fiber_bundle::e2& x0, bool xauto_access);


//==============================================================================
// CLASS E3_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3_lite>(fiber_bundle::e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3_lite>(const fiber_bundle::e3_lite& x0);


//==============================================================================
// CLASS E3
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3>(fiber_bundle::e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3>(const fiber_bundle::e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3>(fiber_bundle::e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e3>(const fiber_bundle::e3& x0, bool xauto_access);


//==============================================================================
// CLASS E4_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::e4_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4_lite>(fiber_bundle::e4_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e4_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4_lite>(const fiber_bundle::e4_lite& x0);


//==============================================================================
// CLASS E4
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::e4::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4>(fiber_bundle::e4& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e4::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4>(const fiber_bundle::e4& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::e4::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4>(fiber_bundle::e4& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::e4::row_dofs_type&
sheaf::row_dofs<fiber_bundle::e4>(const fiber_bundle::e4& x0, bool xauto_access);


//==============================================================================
// CLASS ED_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::ed_lite>(fiber_bundle::ed_lite& x0);

// template
// SHEAF_DLL_SPEC 
// const fiber_bundle::ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::ed_lite>(const fiber_bundle::ed_lite& x0);

//==============================================================================
// CLASS ED_LITE
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS GL2_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::gl2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2_lite>(fiber_bundle::gl2_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2_lite>(const fiber_bundle::gl2_lite& x0);


//==============================================================================
// CLASS GL2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::gl2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2>(fiber_bundle::gl2& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2>(const fiber_bundle::gl2& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::gl2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2>(fiber_bundle::gl2& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl2>(const fiber_bundle::gl2& x0, bool xauto_access);


//==============================================================================
// CLASS GL3_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::gl3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3_lite>(fiber_bundle::gl3_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3_lite>(const fiber_bundle::gl3_lite& x0);


//==============================================================================
// CLASS GL3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::gl3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3>(fiber_bundle::gl3& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3>(const fiber_bundle::gl3& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::gl3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3>(fiber_bundle::gl3& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gl3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gl3>(const fiber_bundle::gl3& x0, bool xauto_access);


//==============================================================================
// CLASS GLN_LITE
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::gln_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln_lite>(fiber_bundle::gln_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gln_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln_lite>(const fiber_bundle::gln_lite& x0);


//==============================================================================
// CLASS GLN
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::gln::table_dofs_type&
sheaf::table_dofs<fiber_bundle::gln>(fiber_bundle::gln& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gln::table_dofs_type&
sheaf::table_dofs<fiber_bundle::gln>(const fiber_bundle::gln& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::gln::table_dofs_type&
sheaf::table_dofs<fiber_bundle::gln>(fiber_bundle::gln& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gln::table_dofs_type&
sheaf::table_dofs<fiber_bundle::gln>(const fiber_bundle::gln& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
fiber_bundle::gln::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln>(fiber_bundle::gln& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gln::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln>(const fiber_bundle::gln& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::gln::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln>(fiber_bundle::gln& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::gln::row_dofs_type&
sheaf::row_dofs<fiber_bundle::gln>(const fiber_bundle::gln& x0, bool xauto_access);



//==============================================================================
// CLASS JCB_LITE
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS JCB
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::jcb::table_dofs_type&
sheaf::table_dofs<fiber_bundle::jcb>(fiber_bundle::jcb& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb::table_dofs_type&
sheaf::table_dofs<fiber_bundle::jcb>(const fiber_bundle::jcb& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::jcb::table_dofs_type&
sheaf::table_dofs<fiber_bundle::jcb>(fiber_bundle::jcb& x0, bool xauto_access);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb::table_dofs_type&
sheaf::table_dofs<fiber_bundle::jcb>(const fiber_bundle::jcb& x0, bool xauto_access);


//==============================================================================
// CLASS JCB_E13_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e13_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13_lite>(fiber_bundle::jcb_e13_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e13_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13_lite>(const fiber_bundle::jcb_e13_lite& x0);


//==============================================================================
// CLASS JCB_E13
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e13::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13>(fiber_bundle::jcb_e13& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e13::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13>(const fiber_bundle::jcb_e13& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e13::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13>(fiber_bundle::jcb_e13& x0, bool xauto_access);

template
SHEAF_DLL_SPEC  
const fiber_bundle::jcb_e13::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e13>(const fiber_bundle::jcb_e13& x0, bool xauto_access);


//==============================================================================
// CLASS JCB_E23_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e23_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23_lite>(fiber_bundle::jcb_e23_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e23_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23_lite>(const fiber_bundle::jcb_e23_lite& x0);


//==============================================================================
// CLASS JCB_E23
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e23::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23>(fiber_bundle::jcb_e23& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e23::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23>(const fiber_bundle::jcb_e23& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e23::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23>(fiber_bundle::jcb_e23& x0, bool xauto_access);

template
SHEAF_DLL_SPEC  
const fiber_bundle::jcb_e23::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e23>(const fiber_bundle::jcb_e23& x0, bool xauto_access);



//==============================================================================
// CLASS JCB_E33_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e33_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33_lite>(fiber_bundle::jcb_e33_lite& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e33_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33_lite>(const fiber_bundle::jcb_e33_lite& x0);


//==============================================================================
// CLASS JCB_E33
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e33::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33>(fiber_bundle::jcb_e33& x0);

template
SHEAF_DLL_SPEC 
const fiber_bundle::jcb_e33::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33>(const fiber_bundle::jcb_e33& x0);

template
SHEAF_DLL_SPEC 
fiber_bundle::jcb_e33::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33>(fiber_bundle::jcb_e33& x0, bool xauto_access);

template
SHEAF_DLL_SPEC  
const fiber_bundle::jcb_e33::row_dofs_type&
sheaf::row_dofs<fiber_bundle::jcb_e33>(const fiber_bundle::jcb_e33& x0, bool xauto_access);


//==============================================================================
// CLASS JCB_ED_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::jcb_ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::jcb_ed_lite>(fiber_bundle::jcb_ed_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::jcb_ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::jcb_ed_lite>(const fiber_bundle::jcb_ed_lite& x0);

//==============================================================================
// CLASS JCB_ED
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS MET_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::met_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::met_lite>(fiber_bundle::met_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::met_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::met_lite>(const fiber_bundle::met_lite& x0);

//==============================================================================
// CLASS MET
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS MET_E1_LITE
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e1_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1_lite>(fiber_bundle::met_e1_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e1_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1_lite>(const fiber_bundle::met_e1_lite& x0);


//==============================================================================
// CLASS MET_E1
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1>(fiber_bundle::met_e1& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1>(const fiber_bundle::met_e1& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1>(fiber_bundle::met_e1& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e1::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e1>(const fiber_bundle::met_e1& x0, bool xauto_access);



//==============================================================================
// CLASS MET_E2_LITE
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2_lite>(fiber_bundle::met_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2_lite>(const fiber_bundle::met_e2_lite& x0);


//==============================================================================
// CLASS MET_E2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2>(fiber_bundle::met_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2>(const fiber_bundle::met_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2>(fiber_bundle::met_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e2>(const fiber_bundle::met_e2& x0, bool xauto_access);



//==============================================================================
// CLASS MET_E3_LITE
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3_lite>(fiber_bundle::met_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3_lite>(const fiber_bundle::met_e3_lite& x0);


//==============================================================================
// CLASS MET_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::met_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3>(fiber_bundle::met_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3>(const fiber_bundle::met_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::met_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3>(fiber_bundle::met_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::met_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::met_e3>(const fiber_bundle::met_e3& x0, bool xauto_access);


//==============================================================================
// CLASS MET_ED_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::met_ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::met_ed_lite>(fiber_bundle::met_ed_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::met_ed_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::met_ed_lite>(const fiber_bundle::met_ed_lite& x0);

//==============================================================================
// CLASS MET_ED
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS ST2_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::st2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st2_lite>(fiber_bundle::st2_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::st2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st2_lite>(const fiber_bundle::st2_lite& x0);

//==============================================================================
// CLASS ST2
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS ST2_E2_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2_lite>(fiber_bundle::st2_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2_lite>(const fiber_bundle::st2_e2_lite& x0);



//==============================================================================
// CLASS ST2_E2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::st2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2>(fiber_bundle::st2_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2>(const fiber_bundle::st2_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2>(fiber_bundle::st2_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e2>(const fiber_bundle::st2_e2& x0, bool xauto_access);


//==============================================================================
// CLASS ST2_E3_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3_lite>(fiber_bundle::st2_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3_lite>(const fiber_bundle::st2_e3_lite& x0);



//==============================================================================
// CLASS ST2_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::st2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3>(fiber_bundle::st2_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3>(const fiber_bundle::st2_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::st2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3>(fiber_bundle::st2_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st2_e3>(const fiber_bundle::st2_e3& x0, bool xauto_access);


//==============================================================================
// CLASS ST3_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::st3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st3_lite>(fiber_bundle::st3_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::st3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st3_lite>(const fiber_bundle::st3_lite& x0);

//==============================================================================
// CLASS ST3
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS ST3_E3_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3_lite>(fiber_bundle::st3_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3_lite>(const fiber_bundle::st3_e3_lite& x0);



//==============================================================================
// CLASS ST3_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::st3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3>(fiber_bundle::st3_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3>(const fiber_bundle::st3_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::st3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3>(fiber_bundle::st3_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st3_e3>(const fiber_bundle::st3_e3& x0, bool xauto_access);



//==============================================================================
// CLASS ST4_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::st4_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st4_lite>(fiber_bundle::st4_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::st4_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::st4_lite>(const fiber_bundle::st4_lite& x0);

//==============================================================================
// CLASS ST4
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS ST4_E2_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2_lite>(fiber_bundle::st4_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2_lite>(const fiber_bundle::st4_e2_lite& x0);



//==============================================================================
// CLASS ST4_E2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::st4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2>(fiber_bundle::st4_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2>(const fiber_bundle::st4_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2>(fiber_bundle::st4_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e2>(const fiber_bundle::st4_e2& x0, bool xauto_access);


//==============================================================================
// CLASS ST4_E3_LITE
//==============================================================================

 
template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3_lite>(fiber_bundle::st4_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3_lite>(const fiber_bundle::st4_e3_lite& x0);



//==============================================================================
// CLASS ST4_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::st4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3>(fiber_bundle::st4_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3>(const fiber_bundle::st4_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::st4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3>(fiber_bundle::st4_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::st4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::st4_e3>(const fiber_bundle::st4_e3& x0, bool xauto_access);



//==============================================================================
// FOR CLASS STP_LITE
//==============================================================================

// No instantiations.

//==============================================================================
// FOR CLASS STP
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::stp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::stp>(fiber_bundle::stp& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::stp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::stp>(const fiber_bundle::stp& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::stp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::stp>(fiber_bundle::stp& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::stp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::stp>(const fiber_bundle::stp& x0, bool xauto_access);


//==============================================================================
// CLASS T2_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::t2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t2_lite>(fiber_bundle::t2_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::t2_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t2_lite>(const fiber_bundle::t2_lite& x0);

//==============================================================================
// CLASS T2
//==============================================================================

// No instantiations.

//==============================================================================
// CLASS T2_E2_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::t2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2_lite>(fiber_bundle::t2_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2_lite>(const fiber_bundle::t2_e2_lite& x0);


//==============================================================================
// CLASS T2_E2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::t2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2>(fiber_bundle::t2_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2>(const fiber_bundle::t2_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2>(fiber_bundle::t2_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e2>(const fiber_bundle::t2_e2& x0, bool xauto_access);


//==============================================================================
// CLASS T2_E3_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::t2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3_lite>(fiber_bundle::t2_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3_lite>(const fiber_bundle::t2_e3_lite& x0);


//==============================================================================
// CLASS T2_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::t2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3>(fiber_bundle::t2_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3>(const fiber_bundle::t2_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::t2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3>(fiber_bundle::t2_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t2_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t2_e3>(const fiber_bundle::t2_e3& x0, bool xauto_access);


//==============================================================================
// CLASS T3_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::t3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t3_lite>(fiber_bundle::t3_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::t3_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t3_lite>(const fiber_bundle::t3_lite& x0);

//==============================================================================
// CLASS T3
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS T3_E3_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::t3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3_lite>(fiber_bundle::t3_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t3_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3_lite>(const fiber_bundle::t3_e3_lite& x0);


//==============================================================================
// CLASS T3_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::t3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3>(fiber_bundle::t3_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3>(const fiber_bundle::t3_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::t3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3>(fiber_bundle::t3_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t3_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t3_e3>(const fiber_bundle::t3_e3& x0, bool xauto_access);


//==============================================================================
// CLASS T4_LITE
//==============================================================================

// template
// SHEAF_DLL_SPEC 
// fiber_bundle::t4_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t4_lite>(fiber_bundle::t4_lite& x0);

// template 
// SHEAF_DLL_SPEC
// const fiber_bundle::t4_lite::row_dofs_type&
// sheaf::row_dofs<fiber_bundle::t4_lite>(const fiber_bundle::t4_lite& x0);

//==============================================================================
// CLASS T4
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS T4_E2_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::t4_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2_lite>(fiber_bundle::t4_e2_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e2_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2_lite>(const fiber_bundle::t4_e2_lite& x0);


//==============================================================================
// CLASS T4_E2
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::t4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2>(fiber_bundle::t4_e2& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2>(const fiber_bundle::t4_e2& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2>(fiber_bundle::t4_e2& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e2::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e2>(const fiber_bundle::t4_e2& x0, bool xauto_access);


//==============================================================================
// CLASS T4_E3_LITE
//==============================================================================

 
template
SHEAF_DLL_SPEC 
fiber_bundle::t4_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3_lite>(fiber_bundle::t4_e3_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e3_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3_lite>(const fiber_bundle::t4_e3_lite& x0);


//==============================================================================
// CLASS T4_E3
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::t4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3>(fiber_bundle::t4_e3& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3>(const fiber_bundle::t4_e3& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::t4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3>(fiber_bundle::t4_e3& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::t4_e3::row_dofs_type&
sheaf::row_dofs<fiber_bundle::t4_e3>(const fiber_bundle::t4_e3& x0, bool xauto_access);


//==============================================================================
// CLASS TP_LITE
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS TP
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::tp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tp>(fiber_bundle::tp& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::tp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tp>(const fiber_bundle::tp& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::tp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tp>(fiber_bundle::tp& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::tp::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tp>(const fiber_bundle::tp& x0, bool xauto_access);


//==============================================================================
// CLASS TUPLE_LITE
//==============================================================================

// No instantiations.


//==============================================================================
// CLASS TUPLE
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::tuple::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tuple>(fiber_bundle::tuple& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::tuple::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tuple>(const fiber_bundle::tuple& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::tuple::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tuple>(fiber_bundle::tuple& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::tuple::table_dofs_type&
sheaf::table_dofs<fiber_bundle::tuple>(const fiber_bundle::tuple& x0, bool xauto_access);

//==============================================================================
// CLASS VD_LITE
//==============================================================================


template 
SHEAF_DLL_SPEC
fiber_bundle::vd_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd_lite>(fiber_bundle::vd_lite& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::vd_lite::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd_lite>(const fiber_bundle::vd_lite& x0);


//==============================================================================
// EXPLICIT INSTANTIATIONS FOR CLASS VD
//==============================================================================


template
SHEAF_DLL_SPEC 
fiber_bundle::vd::table_dofs_type&
sheaf::table_dofs<fiber_bundle::vd>(fiber_bundle::vd& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::vd::table_dofs_type&
sheaf::table_dofs<fiber_bundle::vd>(const fiber_bundle::vd& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::vd::table_dofs_type&
sheaf::table_dofs<fiber_bundle::vd>(fiber_bundle::vd& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::vd::table_dofs_type&
sheaf::table_dofs<fiber_bundle::vd>(const fiber_bundle::vd& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
fiber_bundle::vd::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd>(fiber_bundle::vd& x0);

template 
SHEAF_DLL_SPEC
const fiber_bundle::vd::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd>(const fiber_bundle::vd& x0);

template 
SHEAF_DLL_SPEC
fiber_bundle::vd::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd>(fiber_bundle::vd& x0, bool xauto_access);

template 
SHEAF_DLL_SPEC
const fiber_bundle::vd::row_dofs_type&
sheaf::row_dofs<fiber_bundle::vd>(const fiber_bundle::vd& x0, bool xauto_access);

//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS

