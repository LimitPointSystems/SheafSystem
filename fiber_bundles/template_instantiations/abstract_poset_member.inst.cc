// $RCSfile: abstract_poset_member.inst.cc,v $ $Revision: 1.3 $ $Date: 2013/01/12 17:17:17 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class abstract_poset_member.

#include "abstract_poset_member.impl.h"

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
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "ed.h"
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
#include "vd.h"

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

