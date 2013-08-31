
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class namespace_poset.

#include "at0.h"
#include "at1.h"
#include "at2.h"
#include "at2_e2.h"
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
#include "jcb.h"
#include "jcb_e13.h"
#include "jcb_e23.h"
#include "jcb_e33.h"
#include "jcb_ed.h"
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
#include "t2.h"
#include "t2_e2.h"
#include "t2_e3.h"
#include "t3.h"
#include "t3_e3.h"
#include "t4.h"
#include "t4_e2.h"
#include "t4_e3.h"
#include "tp.h"
#include "tuple.h"
#include "vd.h"

#include "at0_space.h"
#include "at1_space.h"
#include "atp_space.h"
#include "gln_space.h"
#include "jcb_space.h"
#include "stp_space.h"
#include "tp_space.h"
#include "tuple_space.h"
#include "vd_space.h"

#include "sec_at0.h"
#include "sec_at1.h"
#include "sec_at2.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3.h"
#include "sec_at3_e3.h"
#include "sec_atp.h"
#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "sec_e4.h"
#include "sec_ed.h"
#include "sec_met.h"
#include "sec_met_e1.h"
#include "sec_met_e2.h"
#include "sec_met_e3.h"
#include "sec_met_ed.h"
#include "sec_st2.h"
#include "sec_st2_e2.h"
#include "sec_st2_e3.h"
#include "sec_st3.h"
#include "sec_st3_e3.h"
#include "sec_st4.h"
#include "sec_st4_e2.h"
#include "sec_st4_e3.h"
#include "sec_stp.h"
#include "sec_t2.h"
#include "sec_t2_e2.h"
#include "sec_t2_e3.h"
#include "sec_t3.h"
#include "sec_t3_e3.h"
#include "sec_t4.h"
#include "sec_t4_e2.h"
#include "sec_t4_e3.h"
#include "sec_tp.h"
#include "sec_tuple.h"
#include "sec_vd.h"

#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_atp_space.h"
#include "sec_jcb_space.h"
#include "sec_rep_space.h"
#include "sec_stp_space.h"
#include "sec_tp_space.h"
#include "sec_tuple_space.h"
#include "sec_vd_space.h"

#include "namespace_poset.impl.h"

#include "abstract_poset_member.h"
#include "schema_poset_member.h"
#include "assert_contract.h"
#include "poset_path.h"
#include "scoped_index.h"
#include "arg_list.h"

#include "base_space_poset.h"
#include "binary_section_space_schema_poset.h"
#include "binary_section_space_schema_member.h"
#include "section_space_schema_poset.h"
#include "sec_rep_descriptor_poset.h"


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR NAMESPACE_POSET FACET
//==============================================================================

//==============================================================================
// CLASS AT0_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at0_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::at0_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::at0_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::at0_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::at0_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::at0_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::at0_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::at0_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;


//==============================================================================
// CLASS AT1_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::at1_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::at1_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::at1_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::at1_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::at1_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::at1_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::at1_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::at1_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;


//==============================================================================
// CLASS ATP_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::atp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::atp_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::atp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::atp_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::atp_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::atp_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::atp_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::atp_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;

//==============================================================================
// CLASS GLN_SPACE
//============================================================================== 

template
SHEAF_DLL_SPEC
fiber_bundle::gln_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::gln_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::gln_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::gln_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::gln_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::gln_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::gln_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::gln_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::gln_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;


//==============================================================================
// CLASS JCB_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::jcb_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::jcb_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::jcb_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::jcb_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::jcb_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::jcb_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::jcb_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::jcb_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;

 
//==============================================================================
// CLASS STP_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::stp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::stp_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::stp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::stp_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::stp_space>(const string& xname,
						     const arg_list& xargs,
						     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::stp_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::stp_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::stp_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;


//==============================================================================
// FOR CLASS TP_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::tp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::tp_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::tp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::tp_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::tp_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::tp_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::tp_space>(const string& xname,
						   const arg_list& xargs,
						   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::tp_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;

 
//==============================================================================
// CLASS TUPLE_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::tuple_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::tuple_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::tuple_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::tuple_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::tuple_space>(const string& xname,
						       const arg_list& xargs,
						       bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::tuple_space>(const string& xname,
							     const arg_list& xargs,
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::tuple_space>(const string& xname,
						      const arg_list& xargs,
						      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::tuple_space>(const string& xname,
							    const arg_list& xargs,
							    bool xauto_access) const;

 
//==============================================================================
// CLASS VD_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::vd_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::vd_space>(const scoped_index& xindex, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
fiber_bundle::vd_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::vd_space>(const scoped_index& index, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::vd_space>(const string& xname,
						    const arg_list& xargs,
						    bool xauto_access) const;
 
template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::vd_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::vd_space>(const string& xname,
						   const arg_list& xargs,
						   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::vd_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT0_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at0_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_at0_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at0_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_at0_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_at0_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_at0_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_at0_space>(const string& xname,
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_at0_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_at0_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT1_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at1_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_at1_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at1_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_at1_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_at1_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_at1_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_at1_space>(const string& xname,
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_at1_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_at1_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;

//==============================================================================
// CLASS SEC_ATP_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_atp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_atp_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_atp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_atp_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_atp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_atp_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_atp_space>(const string& xname,
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_atp_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_atp_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_JCB_SPACE
//==============================================================================

// $$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace


// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_jcb_space&
// sheaf::namespace_poset::
// member_poset<fiber_bundle::sec_jcb_space>(const scoped_index& xindex, bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_jcb_space&
// sheaf::namespace_poset::
// member_poset<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// contains_poset<fiber_bundle::sec_jcb_space>(const scoped_index& index, bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// contains_poset<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// contains_path<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;


// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// path_is_auto_read_accessible<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// path_is_auto_read_write_accessible<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// path_is_available<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// path_is_auto_read_available<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;


// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// path_is_auto_read_write_available<fiber_bundle::sec_jcb_space>(const poset_path& xpath, bool xauto_access) const;


// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// arg_is_auto_read_accessible<fiber_bundle::sec_jcb_space>(const string& xname,
// 							 const arg_list& xargs,
// 							 bool xauto_access) const;
 

// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// arg_is_auto_read_write_accessible<fiber_bundle::sec_jcb_space>(const string& xname,
// 							       const arg_list& xargs,
// 							       bool xauto_access) const;


// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// arg_is_auto_read_available<fiber_bundle::sec_jcb_space>(const string& xname,
// 							const arg_list& xargs,
// 							bool xauto_access) const;


// template
// SHEAF_DLL_SPEC
// bool
// sheaf::namespace_poset::
// arg_is_auto_read_write_available<fiber_bundle::sec_jcb_space>(const string& xname,
// 							      const arg_list& xargs,
// 							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_REP_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_space&
sheaf::namespace_poset::
new_member_poset<fiber_bundle::sec_rep_space>(const string& xname,
					      const poset_path& xschema_path,
					      const arg_list& xargs,
					      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_rep_space>(const scoped_index& xindex,
					  bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_rep_space>(const poset_path& xpath,
					  bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_rep_space>(const scoped_index& index,
					    bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_rep_space>(const poset_path& xpath,
					    bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_rep_space>(const poset_path& xpath,
					   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_rep_space>(const poset_path& xpath,
							  bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_rep_space>(const poset_path& xpath,
								bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_rep_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_rep_space>(const poset_path& xpath,
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_rep_space>(const poset_path& xpath,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_rep_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_rep_space>(const string& xname,
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_rep_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_rep_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_STP_SPACE
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::sec_stp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_stp_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_stp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_stp_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_stp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_stp_space>(const string& xname,
							 const arg_list& xargs,
							 bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_stp_space>(const string& xname,
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_stp_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_stp_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_TP_SPACE
//==============================================================================


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_tp_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_tp_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_tp_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_tp_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_tp_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_tp_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_tp_space>(const string& xname,
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_tp_space>(const string& xname,
							     const arg_list& xargs,
							     bool xauto_access) const;


//==============================================================================
// CLASS SEC_TUPLE_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_tuple_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_tuple_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_tuple_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_tuple_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_tuple_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_tuple_space>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_tuple_space>(const string& xname,
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_tuple_space>(const string& xname,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_tuple_space>(const string& xname,
								const arg_list& xargs,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_VD_SPACE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_vd_space>(const scoped_index& xindex, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd_space&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_vd_space>(const scoped_index& index, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_vd_space>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_vd_space>(const string& xname,
							const arg_list& xargs,
							bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_vd_space>(const string& xname,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_vd_space>(const string& xname,
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_vd_space>(const string& xname,
							     const arg_list& xargs,
							     bool xauto_access) const;


//==============================================================================
// CLASS BASE_SPACE_POSET
//==============================================================================
 
template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
sheaf::namespace_poset::
new_member_poset<fiber_bundle::base_space_poset>(const string& xname,
						 const poset_path& xschema_path,
						 const arg_list& xargs,
						 bool xauto_access);

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::base_space_poset>(const scoped_index& xindex,
					     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::base_space_poset>(const poset_path& xpath,
					     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::base_space_poset>(const scoped_index& index,
					       bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::base_space_poset>(const poset_path& xpath,
					       bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::base_space_poset>(const poset_path& xpath,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::base_space_poset>(const poset_path& xpath,
							     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::base_space_poset>(const poset_path& xpath,
								   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::base_space_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::base_space_poset>(const poset_path& xpath,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::base_space_poset>(const poset_path& xpath,
								  bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::base_space_poset>(const string& xname,
							    const arg_list& xargs,
							    bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::base_space_poset>(const string& xname,
								  const arg_list& xargs,
								  bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::base_space_poset>(const string& xname,
							   const arg_list& xargs,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::base_space_poset>(const string& xname,
								 const arg_list& xargs,
								 bool xauto_access) const;


//==============================================================================
// CLASS BINARY_SECTION_SPACE_SCHEMA_POSET
//==============================================================================
 
template
SHEAF_DLL_SPEC 
fiber_bundle::binary_section_space_schema_poset&
sheaf::namespace_poset::
new_member_poset<fiber_bundle::binary_section_space_schema_poset>(const string& xname,
								  const poset_path& xschema_path,
								  const arg_list& xargs,
								  bool xauto_access);

template
SHEAF_DLL_SPEC 
fiber_bundle::binary_section_space_schema_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::binary_section_space_schema_poset>(const scoped_index& xindex,
							      bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
fiber_bundle::binary_section_space_schema_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
							      bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::binary_section_space_schema_poset>(const scoped_index& index,
								bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
								bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
									      bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
										    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
									     bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::binary_section_space_schema_poset>(const poset_path& xpath,
										   bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::binary_section_space_schema_poset>(const string& xname,
									     const arg_list& xargs,
									     bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::binary_section_space_schema_poset>(const string& xname,
										   const arg_list& xargs,
										   bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::binary_section_space_schema_poset>(const string& xname,
									    const arg_list& xargs,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::binary_section_space_schema_poset>(const string& xname,
										  const arg_list& xargs,
										  bool xauto_access) const;


//==============================================================================
// CLASS SECTION_SPACE_SCHEMA_POSET
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::section_space_schema_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::section_space_schema_poset>(
    const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::section_space_schema_poset>(
    const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::section_space_schema_poset>(
    const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::section_space_schema_poset>(
    const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::section_space_schema_poset>(
    const poset_path& xpath, bool xauto_access) const;


//==============================================================================
// CLASS SEC_REP_DESCRIPTOR_POSET
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_descriptor_poset&
sheaf::namespace_poset::
new_member_poset<fiber_bundle::sec_rep_descriptor_poset>(const string& xname,
		                                         const poset_path& xschema_path,
		                                         const arg_list& xargs,
		                                         bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_descriptor_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_rep_descriptor_poset>(const scoped_index& xindex,
						     bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
fiber_bundle::sec_rep_descriptor_poset&
sheaf::namespace_poset::
member_poset<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
						     bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_rep_descriptor_poset>(const scoped_index& index,
						       bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
						       bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
								     bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_accessible<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_available<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath, bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
								    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
path_is_auto_read_write_available<fiber_bundle::sec_rep_descriptor_poset>(const poset_path& xpath,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_accessible<fiber_bundle::sec_rep_descriptor_poset>(const string& xname,
								    const arg_list& xargs,
								    bool xauto_access) const;
 

template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_accessible<fiber_bundle::sec_rep_descriptor_poset>(const string& xname,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_available<fiber_bundle::sec_rep_descriptor_poset>(const string& xname,
								   const arg_list& xargs,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
sheaf::namespace_poset::
arg_is_auto_read_write_available<fiber_bundle::sec_rep_descriptor_poset>(const string& xname,
									 const arg_list& xargs,
									 bool xauto_access) const;

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
