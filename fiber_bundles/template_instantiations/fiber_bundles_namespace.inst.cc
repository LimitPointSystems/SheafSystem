
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
#include "sec_rep_space.h"
#include "sec_stp_space.h"
#include "sec_tp_space.h"
#include "sec_tuple_space.h"
#include "sec_vd_space.h"

#include "fiber_bundles_namespace.impl.h"
//#include "fiber_bundles_namespace.h"
//#include "fiber_bundle.h"
#include "namespace_poset.impl.h"
#include "abstract_poset_member.h"
#include "assert_contract.h"
#include "poset_path.h"
#include "scoped_index.h"
#include "arg_list.h"

#include "point_block_1d.h"
#include "point_block_2d.h"
#include "point_block_3d.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "unstructured_block.h"
#include "zone_nodes_block.h"

#include "base_space_member_prototype.h"


#ifndef DOXYGEN_SKIP_INSTANTIATIONS

//==============================================================================
// EXPLICIT INSTANTIATIONS FOR FIBER_BUNDLES_NAMESPACE FACET:
//==============================================================================

//==============================================================================
// CLASS AT0:
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at0::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at0::host_type>::
// new_space<fiber_bundle::at0>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at0::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at0>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at0::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_space<fiber_bundle::at0>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at0>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at0>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at0>(const poset_path& xfiber_space_path, 
						     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at0>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at0>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS AT1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at1::host_type>::
// new_space<fiber_bundle::at1>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at1>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::at1>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::at1>(const poset_path& xfiber_space_path, 
					       const poset_path& xscalar_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at1>(const poset_path& xfiber_space_path, 
		bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::at1>(const poset_path& xfiber_space_path, 
							    const poset_path& xscalar_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at1>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at1>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS AT2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at2::host_type>::
// new_space<fiber_bundle::at2>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::at2>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::at2>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::at2>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::at2>(const poset_path& xfiber_space_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at2>(const poset_path& xfiber_space_path, 
						     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::at2>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::at2>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at2>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS AT2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at2_e2::host_type>::
// new_space<fiber_bundle::at2_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::at2_e2>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at2_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at2_e2>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;

//==============================================================================
// CLASS AT2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at2_e3::host_type>::
// new_space<fiber_bundle::at2_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::at2_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at2_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at2_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS AT3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at3::host_type>::
// new_space<fiber_bundle::at3>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::at3>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::at3>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::at3>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::at3>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at3>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::at3>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::at3>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at3>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS AT3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::at3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::at3_e3::host_type>::
// new_space<fiber_bundle::at3_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::at3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::at3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::at3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::at3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::at3_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::at3_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::at3_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS ATP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::atp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::atp::host_type>::
// new_space<fiber_bundle::atp>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::atp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::atp>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::atp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::atp>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::atp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::atp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::atp>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::atp>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::atp>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::atp>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::atp>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::atp>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::atp>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::atp>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;

//==============================================================================
// CLASS E1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::e1::host_type>::
// new_space<fiber_bundle::e1>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::e1>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::e1>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::e1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::e1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::e1>(const poset_path& xfiber_space_path, 
					      const poset_path& xscalar_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::e1>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::e1>(const poset_path& xfiber_space_path, 
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::e1>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::e1>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;

//==============================================================================
// CLASS E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::e2::host_type>::
// new_space<fiber_bundle::e2>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::e2>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::e2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::e2>(const poset_path& xfiber_space_path, 
					      const poset_path& xscalar_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::e2>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::e2>(const poset_path& xfiber_space_path, 
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::e2>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;

//==============================================================================
// CLASS E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::e3::host_type>::
// new_space<fiber_bundle::e3>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::e3>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::e3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::e3>(const poset_path& xfiber_space_path, 
					      const poset_path& xscalar_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::e3>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::e3>(const poset_path& xfiber_space_path, 
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::e3>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS E4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::e4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::e4::host_type>::
// new_space<fiber_bundle::e4>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::e4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::e4>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::e4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::e4>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::e4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::e4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::e4>(const poset_path& xfiber_space_path, 
					      const poset_path& xscalar_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::e4>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::e4>(const poset_path& xfiber_space_path, 
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::e4>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::e4>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS ED
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::ed::host_type>::
// new_space<fiber_bundle::ed>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::ed>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::ed>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::ed>(const poset_path& xfiber_space_path, 
					      const poset_path& xscalar_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::ed>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::ed>(const poset_path& xfiber_space_path, 
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::ed>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::ed>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS GL2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::gl2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::gl2::host_type>::
// new_space<fiber_bundle::gl2>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::gl2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::gl2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::gl2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_group_space<fiber_bundle::gl2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::gl2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::gl2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::gl2>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::gl2>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::gl2>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::gl2>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::gl2>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::gl2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::gl2>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;

//==============================================================================
// CLASS GL3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::gl3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::gl3::host_type>::
// new_space<fiber_bundle::gl3>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::gl3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::gl3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::gl3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_group_space<fiber_bundle::gl3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::gl3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::gl3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::gl3>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::gl3>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::gl3>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::gl3>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::gl3>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::gl3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::gl3>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS GLN
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::gln::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::gln::host_type>::
// new_space<fiber_bundle::gln>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::gln::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::gln>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::gln::host_type&
fiber_bundle::fiber_bundles_namespace::
new_group_space<fiber_bundle::gln>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::gln>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::gln>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::gln>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::gln>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::gln>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::gln>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::gln>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::gln>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::gln>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS JCB
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::jcb::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::jcb::host_type>::
// new_space<fiber_bundle::jcb>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::jcb>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::jcb::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space<fiber_bundle::jcb>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xdomain_space_path,
				      const arg_list& xdomain_space_args,
				      const poset_path& xdomain_space_schema_path,
				      const poset_path& xrange_space_path,
				      const arg_list& xrange_space_args,
				      const poset_path& xrange_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::jcb>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::jcb>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
					       const poset_path& xdomain_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
					      const poset_path& xrange_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
							      const poset_path& xdomain_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xdomain_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
									   const poset_path& xdomain_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xdomain_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
							    const poset_path& xdomain_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available<fiber_bundle::jcb>(const poset_path& xfiber_space_path, 
							   const poset_path& xrange_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::jcb>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::jcb>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS JCB_E13
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::jcb_e13::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::jcb_e13::host_type>::
// new_space<fiber_bundle::jcb_e13>(fiber_bundles_namespace& xns,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e13::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path,
					  const arg_list& xfiber_space_args,
					  const poset_path& xfiber_space_schema_path,
					  const poset_path& xdomain_space_path,
					  const arg_list& xdomain_space_args,
					  const poset_path& xdomain_space_schema_path,
					  const poset_path& xrange_space_path,
					  const arg_list& xrange_space_args,
					  const poset_path& xrange_space_schema_path,
					  const poset_path& xscalar_space_path,
					  const arg_list& xscalar_space_args,
					  const poset_path& xscalar_space_schema_path,
					  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::jcb_e13>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::jcb_e13>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
						   const poset_path& xdomain_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
						  const poset_path& xrange_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
								  const poset_path& xdomain_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xdomain_space_args,
								  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
									       const poset_path& xdomain_space_path, 
									       const arg_list& xfiber_space_args,
									       const poset_path& xscalar_space_path, 
									       const arg_list& xdomain_space_args,
									       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
								const poset_path& xdomain_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available<fiber_bundle::jcb_e13>(const poset_path& xfiber_space_path, 
							       const poset_path& xrange_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::jcb_e13>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::jcb_e13>(const arg_list& xargs,
							     const poset_path& xpath, 
							     bool xauto_access) const;


//==============================================================================
// CLASS JCB_E23
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::jcb_e23::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::jcb_e23::host_type>::
// new_space<fiber_bundle::jcb_e23>(fiber_bundles_namespace& xns,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e23::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path,
					  const arg_list& xfiber_space_args,
					  const poset_path& xfiber_space_schema_path,
					  const poset_path& xdomain_space_path,
					  const arg_list& xdomain_space_args,
					  const poset_path& xdomain_space_schema_path,
					  const poset_path& xrange_space_path,
					  const arg_list& xrange_space_args,
					  const poset_path& xrange_space_schema_path,
					  const poset_path& xscalar_space_path,
					  const arg_list& xscalar_space_args,
					  const poset_path& xscalar_space_schema_path,
					  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::jcb_e23>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::jcb_e23>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
						   const poset_path& xdomain_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
						  const poset_path& xrange_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
								  const poset_path& xdomain_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xdomain_space_args,
								  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
									       const poset_path& xdomain_space_path, 
									       const arg_list& xfiber_space_args,
									       const poset_path& xscalar_space_path, 
									       const arg_list& xdomain_space_args,
									       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
								const poset_path& xdomain_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available<fiber_bundle::jcb_e23>(const poset_path& xfiber_space_path, 
							       const poset_path& xrange_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::jcb_e23>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::jcb_e23>(const arg_list& xargs,
							     const poset_path& xpath, 
							     bool xauto_access) const;


//==============================================================================
// CLASS JCB_E33
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::jcb_e33::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::jcb_e33::host_type>::
// new_space<fiber_bundle::jcb_e33>(fiber_bundles_namespace& xns,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::jcb_e33::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path,
					  const arg_list& xfiber_space_args,
					  const poset_path& xfiber_space_schema_path,
					  const poset_path& xdomain_space_path,
					  const arg_list& xdomain_space_args,
					  const poset_path& xdomain_space_schema_path,
					  const poset_path& xrange_space_path,
					  const arg_list& xrange_space_args,
					  const poset_path& xrange_space_schema_path,
					  const poset_path& xscalar_space_path,
					  const arg_list& xscalar_space_args,
					  const poset_path& xscalar_space_schema_path,
					  bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::jcb_e33>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::jcb_e33>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
						   const poset_path& xdomain_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
						  const poset_path& xrange_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
								  const poset_path& xdomain_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xdomain_space_args,
								  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
									       const poset_path& xdomain_space_path, 
									       const arg_list& xfiber_space_args,
									       const poset_path& xscalar_space_path, 
									       const arg_list& xdomain_space_args,
									       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
								const poset_path& xdomain_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available<fiber_bundle::jcb_e33>(const poset_path& xfiber_space_path, 
							       const poset_path& xrange_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::jcb_e33>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::jcb_e33>(const arg_list& xargs,
							     const poset_path& xpath, 
							     bool xauto_access) const;


//==============================================================================
// CLASS JCB_ED
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::jcb_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::jcb_ed::host_type>::
// new_space<fiber_bundle::jcb_ed>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::jcb_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::jcb_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_jacobian_space<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path,
					 const arg_list& xfiber_space_args,
					 const poset_path& xfiber_space_schema_path,
					 const poset_path& xdomain_space_path,
					 const arg_list& xdomain_space_args,
					 const poset_path& xdomain_space_schema_path,
					 const poset_path& xrange_space_path,
					 const arg_list& xrange_space_args,
					 const poset_path& xrange_space_schema_path,
					 const poset_path& xscalar_space_path,
					 const arg_list& xscalar_space_args,
					 const poset_path& xscalar_space_schema_path,
					 bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::jcb_ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::jcb_ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
						  const poset_path& xdomain_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
						 const poset_path& xrange_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
								 const poset_path& xdomain_space_path, 
								 const arg_list& xfiber_space_args,
								 const poset_path& xscalar_space_path, 
								 const arg_list& xdomain_space_args,
								 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_jacobian_scalar_space_path_is_available<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
									      const poset_path& xdomain_space_path, 
									      const arg_list& xfiber_space_args,
									      const poset_path& xscalar_space_path, 
									      const arg_list& xdomain_space_args,
									      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_domain_space_path_is_available<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
							       const poset_path& xdomain_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_range_space_path_is_available<fiber_bundle::jcb_ed>(const poset_path& xfiber_space_path, 
							      const poset_path& xrange_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::jcb_ed>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::jcb_ed>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;



//==============================================================================
// CLASS MET
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::met::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::met::host_type>::
// new_space<fiber_bundle::met>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::met::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::met>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::met::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::met>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::met>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::met>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::met>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::met>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::met>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::met>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::met>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::met>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::met>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::met>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS MET_E1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::met_e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::met_e1::host_type>::
// new_space<fiber_bundle::met_e1>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::met_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::met_e1>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::met_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::met_e1>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::met_e1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::met_e1>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::met_e1>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::met_e1>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::met_e1>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::met_e1>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::met_e1>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::met_e1>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::met_e1>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::met_e1>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS MET_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::met_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::met_e2::host_type>::
// new_space<fiber_bundle::met_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::met_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::met_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::met_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::met_e2>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::met_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::met_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::met_e2>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::met_e2>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::met_e2>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::met_e2>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::met_e2>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::met_e2>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::met_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::met_e2>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS MET_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::met_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::met_e3::host_type>::
// new_space<fiber_bundle::met_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::met_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::met_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::met_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::met_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::met_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::met_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::met_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::met_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::met_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::met_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::met_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::met_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::met_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::met_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS MET_ED
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::met_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::met_ed::host_type>::
// new_space<fiber_bundle::met_ed>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::met_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::met_ed>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::met_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::met_ed>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::met_ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::met_ed>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::met_ed>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::met_ed>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::met_ed>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::met_ed>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::met_ed>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::met_ed>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::met_ed>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::met_ed>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;

//==============================================================================
// CLASS ST2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st2::host_type>::
// new_space<fiber_bundle::st2>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st2>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st2>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st2>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st2>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st2>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st2>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st2>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st2>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS ST2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st2_e2::host_type>::
// new_space<fiber_bundle::st2_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st2_e2>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st2_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st2_e2>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS ST2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st2_e3::host_type>::
// new_space<fiber_bundle::st2_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st2_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st2_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st2_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS ST3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st3::host_type>::
// new_space<fiber_bundle::st3>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st3>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st3>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st3>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st3>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st3>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st3>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st3>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st3>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS ST3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st3_e3::host_type>::
// new_space<fiber_bundle::st3_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st3_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st3_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st3_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS ST4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st4::host_type>::
// new_space<fiber_bundle::st4>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st4>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st4>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st4>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st4>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st4>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st4>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st4>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st4>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st4>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st4>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS ST4_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st4_e2::host_type>::
// new_space<fiber_bundle::st4_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st4_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st4_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st4_e2>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st4_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st4_e2>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS ST4_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::st4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::st4_e3::host_type>::
// new_space<fiber_bundle::st4_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::st4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::st4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path,
				       const arg_list& xfiber_space_args,
				       const poset_path& xfiber_space_schema_path,
				       const poset_path& xvector_space_path,
				       const arg_list& xvector_space_args,
				       const poset_path& xvector_space_schema_path,
				       const poset_path& xscalar_space_path,
				       const arg_list& xscalar_space_args,
				       const poset_path& xscalar_space_schema_path,
				       bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::st4_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::st4_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path, 
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path, 
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::st4_e3>(const poset_path& xfiber_space_path, 
									    const poset_path& xvector_space_path, 
									    const arg_list& xfiber_space_args,
									    const poset_path& xscalar_space_path, 
									    const arg_list& xvector_space_args,
									    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::st4_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::st4_e3>(const arg_list& xargs,
							    const poset_path& xpath, 
							    bool xauto_access) const;


//==============================================================================
// CLASS STP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::stp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::stp::host_type>::
// new_space<fiber_bundle::stp>(fiber_bundles_namespace& xns,
// 			     const poset_path& xfiber_space_path,
// 			     const arg_list& xfiber_space_args,
// 			     const poset_path& xfiber_space_schema_path,
// 			     bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::stp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::stp>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::stp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::stp>(const poset_path& xfiber_space_path,
				    const arg_list& xfiber_space_args,
				    const poset_path& xfiber_space_schema_path,
				    const poset_path& xvector_space_path,
				    const arg_list& xvector_space_args,
				    const poset_path& xvector_space_schema_path,
				    const poset_path& xscalar_space_path,
				    const arg_list& xscalar_space_args,
				    const poset_path& xscalar_space_schema_path,
				    bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::stp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::stp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::stp>(const poset_path& xfiber_space_path, 
			       const arg_list& xfiber_space_args,
			       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::stp>(const poset_path& xfiber_space_path, 
					       const poset_path& xvector_space_path, 
					       const arg_list& xfiber_space_args,
					       bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::stp>(const poset_path& xfiber_space_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::stp>(const poset_path& xfiber_space_path, 
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::stp>(const poset_path& xfiber_space_path,
							    const poset_path& xvector_space_path, 
							    const arg_list& xfiber_space_args,
							    bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::stp>(const poset_path& xfiber_space_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xfiber_space_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::stp>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::stp>(const arg_list& xargs,
							 const poset_path& xpath, 
							 bool xauto_access) const;


//==============================================================================
// CLASS T2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t2::host_type>::
// new_space<fiber_bundle::t2>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t2>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t2>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t2>(const poset_path& xfiber_space_path, 
			      const arg_list& xfiber_space_args,
			      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t2>(const poset_path& xfiber_space_path, 
					      const poset_path& xvector_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t2>(const poset_path& xfiber_space_path, 
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xvector_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t2>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t2>(const poset_path& xfiber_space_path,
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t2>(const poset_path& xfiber_space_path, 
									const poset_path& xvector_space_path, 
									const arg_list& xfiber_space_args,
									const poset_path& xscalar_space_path, 
									const arg_list& xvector_space_args,
									bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t2>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS T2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t2_e2::host_type>::
// new_space<fiber_bundle::t2_e2>(fiber_bundles_namespace& xns,
// 			       const poset_path& xfiber_space_path,
// 			       const arg_list& xfiber_space_args,
// 			       const poset_path& xfiber_space_schema_path,
// 			       bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xvector_space_path,
				      const arg_list& xvector_space_args,
				      const poset_path& xvector_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t2_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path, 
				 const arg_list& xfiber_space_args,
				 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path, 
						 const poset_path& xvector_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path, 
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xvector_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path, 
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path,
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t2_e2>(const poset_path& xfiber_space_path, 
									   const poset_path& xvector_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xvector_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t2_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t2_e2>(const arg_list& xargs,
							   const poset_path& xpath, 
							   bool xauto_access) const;


//==============================================================================
// CLASS T2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t2_e3::host_type>::
// new_space<fiber_bundle::t2_e3>(fiber_bundles_namespace& xns,
// 			       const poset_path& xfiber_space_path,
// 			       const arg_list& xfiber_space_args,
// 			       const poset_path& xfiber_space_schema_path,
// 			       bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xvector_space_path,
				      const arg_list& xvector_space_args,
				      const poset_path& xvector_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t2_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path, 
				 const arg_list& xfiber_space_args,
				 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path, 
						 const poset_path& xvector_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path, 
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xvector_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path, 
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path,
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t2_e3>(const poset_path& xfiber_space_path, 
									   const poset_path& xvector_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xvector_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t2_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t2_e3>(const arg_list& xargs,
							   const poset_path& xpath, 
							   bool xauto_access) const;


//==============================================================================
// CLASS T3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t3::host_type>::
// new_space<fiber_bundle::t3>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t3>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t3>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t3>(const poset_path& xfiber_space_path, 
			      const arg_list& xfiber_space_args,
			      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t3>(const poset_path& xfiber_space_path, 
					      const poset_path& xvector_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t3>(const poset_path& xfiber_space_path, 
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xvector_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t3>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t3>(const poset_path& xfiber_space_path,
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t3>(const poset_path& xfiber_space_path, 
									const poset_path& xvector_space_path, 
									const arg_list& xfiber_space_args,
									const poset_path& xscalar_space_path, 
									const arg_list& xvector_space_args,
									bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t3>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS T3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t3_e3::host_type>::
// new_space<fiber_bundle::t3_e3>(fiber_bundles_namespace& xns,
// 			       const poset_path& xfiber_space_path,
// 			       const arg_list& xfiber_space_args,
// 			       const poset_path& xfiber_space_schema_path,
// 			       bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xvector_space_path,
				      const arg_list& xvector_space_args,
				      const poset_path& xvector_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t3_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path, 
				 const arg_list& xfiber_space_args,
				 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path, 
						 const poset_path& xvector_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path, 
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xvector_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path, 
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path,
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t3_e3>(const poset_path& xfiber_space_path, 
									   const poset_path& xvector_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xvector_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t3_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t3_e3>(const arg_list& xargs,
							   const poset_path& xpath, 
							   bool xauto_access) const;


//==============================================================================
// CLASS T4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t4::host_type>::
// new_space<fiber_bundle::t4>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t4>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t4>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t4>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t4>(const poset_path& xfiber_space_path, 
			      const arg_list& xfiber_space_args,
			      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t4>(const poset_path& xfiber_space_path, 
					      const poset_path& xvector_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t4>(const poset_path& xfiber_space_path, 
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xvector_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t4>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t4>(const poset_path& xfiber_space_path,
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t4>(const poset_path& xfiber_space_path, 
									const poset_path& xvector_space_path, 
									const arg_list& xfiber_space_args,
									const poset_path& xscalar_space_path, 
									const arg_list& xvector_space_args,
									bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t4>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t4>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS T4_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t4_e2::host_type>::
// new_space<fiber_bundle::t4_e2>(fiber_bundles_namespace& xns,
// 			       const poset_path& xfiber_space_path,
// 			       const arg_list& xfiber_space_args,
// 			       const poset_path& xfiber_space_schema_path,
// 			       bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xvector_space_path,
				      const arg_list& xvector_space_args,
				      const poset_path& xvector_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t4_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t4_e2>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path, 
				 const arg_list& xfiber_space_args,
				 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path, 
						 const poset_path& xvector_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path, 
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xvector_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path, 
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path,
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t4_e2>(const poset_path& xfiber_space_path, 
									   const poset_path& xvector_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xvector_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t4_e2>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t4_e2>(const arg_list& xargs,
							   const poset_path& xpath, 
							   bool xauto_access) const;


//==============================================================================
// CLASS T4_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::t4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::t4_e3::host_type>::
// new_space<fiber_bundle::t4_e3>(fiber_bundles_namespace& xns,
// 			       const poset_path& xfiber_space_path,
// 			       const arg_list& xfiber_space_args,
// 			       const poset_path& xfiber_space_schema_path,
// 			       bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::t4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::t4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path,
				      const arg_list& xfiber_space_args,
				      const poset_path& xfiber_space_schema_path,
				      const poset_path& xvector_space_path,
				      const arg_list& xvector_space_args,
				      const poset_path& xvector_space_schema_path,
				      const poset_path& xscalar_space_path,
				      const arg_list& xscalar_space_args,
				      const poset_path& xscalar_space_schema_path,
				      bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::t4_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::t4_e3>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path, 
				 const arg_list& xfiber_space_args,
				 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path, 
						 const poset_path& xvector_space_path, 
						 const arg_list& xfiber_space_args,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path, 
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xvector_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path, 
							     bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path,
							      const poset_path& xvector_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::t4_e3>(const poset_path& xfiber_space_path, 
									   const poset_path& xvector_space_path, 
									   const arg_list& xfiber_space_args,
									   const poset_path& xscalar_space_path, 
									   const arg_list& xvector_space_args,
									   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::t4_e3>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::t4_e3>(const arg_list& xargs,
							   const poset_path& xpath, 
							   bool xauto_access) const;


//==============================================================================
// CLASS TP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::tp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::tp::host_type>::
// new_space<fiber_bundle::tp>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
// 
template
SHEAF_DLL_SPEC
fiber_bundle::tp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::tp>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::tp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_space<fiber_bundle::tp>(const poset_path& xfiber_space_path,
				   const arg_list& xfiber_space_args,
				   const poset_path& xfiber_space_schema_path,
				   const poset_path& xvector_space_path,
				   const arg_list& xvector_space_args,
				   const poset_path& xvector_space_schema_path,
				   const poset_path& xscalar_space_path,
				   const arg_list& xscalar_space_args,
				   const poset_path& xscalar_space_schema_path,
				   bool xauto_access);

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_schema_path<fiber_bundle::tp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::tp>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::tp>(const poset_path& xfiber_space_path, 
			      const arg_list& xfiber_space_args,
			      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::tp>(const poset_path& xfiber_space_path, 
					      const poset_path& xvector_space_path, 
					      const arg_list& xfiber_space_args,
					      bool xauto_access) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::tp>(const poset_path& xfiber_space_path, 
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xvector_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::tp>(const poset_path& xfiber_space_path, 
							  bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::tp>(const poset_path& xfiber_space_path,
							   const poset_path& xvector_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::tp>(const poset_path& xfiber_space_path, 
									const poset_path& xvector_space_path, 
									const arg_list& xfiber_space_args,
									const poset_path& xscalar_space_path, 
									const arg_list& xvector_space_args,
									bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_schema_path_conforms_to<fiber_bundle::tp>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
args_conform_to_completed_schema_path<fiber_bundle::tp>(const arg_list& xargs,
							const poset_path& xpath, 
							bool xauto_access) const;


//==============================================================================
// CLASS TUPLE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::tuple::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::tuple>(const poset_path& xfiber_space_path,
				     const arg_list& xfiber_space_args,
				     const poset_path& xfiber_space_schema_path,
				     bool xauto_access);


//==============================================================================
// CLASS VD
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::vd::host_type&
// fiber_bundle::fiber_bundles_namespace::new_fiber_space_impl<fiber_bundle::vd::host_type>::
// new_space<fiber_bundle::vd>(fiber_bundles_namespace& xns,
// 			    const poset_path& xfiber_space_path,
// 			    const arg_list& xfiber_space_args,
// 			    const poset_path& xfiber_space_schema_path,
// 			    bool xauto_access);
 
template
SHEAF_DLL_SPEC
fiber_bundle::vd::host_type&
fiber_bundle::fiber_bundles_namespace::
new_fiber_space<fiber_bundle::vd>(const poset_path& xfiber_space_path,
				  const arg_list& xfiber_space_args,
				  const poset_path& xfiber_space_schema_path,
				  bool xauto_access);

 
//==============================================================================
// CLASS SEC_AT0
//==============================================================================

// 
//template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at0::host_type>::
// new_space<fiber_bundle::sec_at0>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);

// 
//template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at0::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at0::host_type>::
// new_space<fiber_bundle::sec_at0>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 	              bool xauto_access);


// 
//template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at0::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at0::host_type>::
// new_space<fiber_bundle::sec_at0>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at0::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at0>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at0::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at0>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);




template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space_schema<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at0::host_type&
fiber_bundle::fiber_bundles_namespace::
new_scalar_section_space<fiber_bundle::sec_at0>(const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at0>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at0>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at0>(const poset_path& xfiber_space_path, 
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at0>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at0>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at1::host_type>::
// new_space<fiber_bundle::sec_at1>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at1::host_type>::
// new_space<fiber_bundle::sec_at1>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at1::host_type>::
// new_space<fiber_bundle::sec_at1>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
//

//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at1::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_at1::fiber_type>(const poset_path& xfiber_space_path,
// 						    const arg_list& xfiber_space_args,
// 						    const poset_path& xfiber_space_schema_path,
// 						    const poset_path& xscalar_space_path,
// 						    const arg_list& xscalar_space_args,	
// 						    const poset_path& xscalar_space_schema_path,
// 						    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at1>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at1>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_at1>(const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at1>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at1>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at1>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at1>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at1>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at1>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at1>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at2::host_type>::
// new_space<fiber_bundle::sec_at2>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2::host_type>::
// new_space<fiber_bundle::sec_at2>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2::host_type>::
// new_space<fiber_bundle::sec_at2>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_at2>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at2>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at2>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;



//==============================================================================
// CLASS SEC_AT2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at2_e2::host_type>::
// new_space<fiber_bundle::sec_at2_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2_e2::host_type>::
// new_space<fiber_bundle::sec_at2_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2_e2::host_type>::
// new_space<fiber_bundle::sec_at2_e2>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_at2_e2>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at2_e2>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at2_e3::host_type>::
// new_space<fiber_bundle::sec_at2_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2_e3::host_type>::
// new_space<fiber_bundle::sec_at2_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at2_e3::host_type>::
// new_space<fiber_bundle::sec_at2_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_at2_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at2_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;




//==============================================================================
// CLASS SEC_AT3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at3::host_type>::
// new_space<fiber_bundle::sec_at3>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at3::host_type>::
// new_space<fiber_bundle::sec_at3>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at3::host_type>::
// new_space<fiber_bundle::sec_at3>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at3>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at3>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_at3>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at3>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at3>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_AT3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at3_e3::host_type>::
// new_space<fiber_bundle::sec_at3_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at3_e3::host_type>::
// new_space<fiber_bundle::sec_at3_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_at3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_at3_e3::host_type>::
// new_space<fiber_bundle::sec_at3_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_at3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_at3_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_at3_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_at3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ATP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_atp::host_type>::
// new_space<fiber_bundle::sec_atp>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_atp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_atp::host_type>::
// new_space<fiber_bundle::sec_atp>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_atp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_atp::host_type>::
// new_space<fiber_bundle::sec_atp>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_atp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_atp>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_atp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_atp>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_atp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_atp>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_atp>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_atp>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_atp>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_atp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;



//==============================================================================
// CLASS SEC_E1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e1::host_type>::
// new_space<fiber_bundle::sec_e1>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e1::host_type>::
// new_space<fiber_bundle::sec_e1>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e1::host_type>::
// new_space<fiber_bundle::sec_e1>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
//

//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e1::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e1>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e1>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e1>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e1>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e1>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e1>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e1>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e1>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e1>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e1>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_E1_UNIFORM
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e1_uniform::host_type>::
// new_space<fiber_bundle::sec_e1_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e1_uniform::host_type>::
// new_space<fiber_bundle::sec_e1_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e1_uniform::host_type>::
// new_space<fiber_bundle::sec_e1_uniform>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
//

//$$SCRIBBLE: Commented out because sec_e1_uniform::fiber_type::host_type is same as sec_e1
//            resulting in multiple instantiations. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e1_uniform::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e1_uniform::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e1_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e1_uniform>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e1_uniform>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e1_uniform>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e1_uniform>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e1_uniform>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e1_uniform>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e1_uniform>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e1_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;



//==============================================================================
// CLASS SEC_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e2::host_type>::
// new_space<fiber_bundle::sec_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e2::host_type>::
// new_space<fiber_bundle::sec_e2>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e2::host_type>::
// new_space<fiber_bundle::sec_e2>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 

//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e2::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e2>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e2>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e2>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e2>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e2>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e2>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e2>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e2>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;



//==============================================================================
// CLASS SEC_E2_UNIFORM
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e2_uniform::host_type>::
// new_space<fiber_bundle::sec_e2_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e2_uniform::host_type>::
// new_space<fiber_bundle::sec_e2_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e2_uniform::host_type>::
// new_space<fiber_bundle::sec_e2_uniform>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
//
//$$SCRIBBLE: Commented out because sec_e2_uniform::fiber_type::host_type is same as sec_e2
//            resulting in multiple instantiations.
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e2_uniform::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e2_uniform::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e2_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e2_uniform>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e2_uniform>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e2_uniform>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e2_uniform>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e2_uniform>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e2_uniform>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e2_uniform>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e2_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_E3
//==============================================================================

// 
//template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// //fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e3::host_type>::
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_at1_space>::
// new_space<fiber_bundle::sec_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);

// 
//template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e3::host_type>::
// new_space<fiber_bundle::sec_e3>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);

// 
//template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e3::host_type>::
// new_space<fiber_bundle::sec_e3>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);


//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e3::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e3>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e3>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e3>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e3>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e3>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e3>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e3>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e3>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_E3_UNIFORM
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e3_uniform::host_type>::
// new_space<fiber_bundle::sec_e3_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e3_uniform::host_type>::
// new_space<fiber_bundle::sec_e3_uniform>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3_uniform::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e3_uniform::host_type>::
// new_space<fiber_bundle::sec_e3_uniform>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
//
//$$SCRIBBLE: Commented out because sec_e3_uniform::fiber_type::host_type is same as sec_e3
//            resulting in multiple instantiations.
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e3_uniform::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e3_uniform::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e3_uniform::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e3_uniform>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e3_uniform>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e3_uniform>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e3_uniform>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e3_uniform>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e3_uniform>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e3_uniform>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e3_uniform>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_E4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_e4::host_type>::
// new_space<fiber_bundle::sec_e4>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e4::host_type>::
// new_space<fiber_bundle::sec_e4>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_e4::host_type>::
// new_space<fiber_bundle::sec_e4>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
//

//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_e4::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_e4::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e4>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_e4>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_e4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_e4>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_e4>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_e4>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_e4>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_e4>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_e4>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_e4>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_e4>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;



//==============================================================================
// CLASS SEC_ED
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_ed::host_type>::
// new_space<fiber_bundle::sec_ed>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_ed::host_type>::
// new_space<fiber_bundle::sec_ed>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_ed::host_type>::
// new_space<fiber_bundle::sec_ed>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
//$$SCRIBBLE: Already instantiated above. 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_ed::fiber_type::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_vector_space<fiber_bundle::sec_ed::fiber_type>(const poset_path& xfiber_space_path,
// 						   const arg_list& xfiber_space_args,
// 						   const poset_path& xfiber_space_schema_path,
// 						   const poset_path& xscalar_space_path,
// 						   const arg_list& xscalar_space_args,	
// 						   const poset_path& xscalar_space_schema_path,
// 						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_ed>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_ed>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_ed>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_ed>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_ed>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_ed>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_ed>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_ed>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_ed>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_ed>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;



//==============================================================================
// CLASS SEC_JCB_E13
//==============================================================================

// $$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_jcb_e13::host_type>::
// new_space<fiber_bundle::sec_jcb_e13>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_schema_path,
// 				     const arg_list& xsection_space_schema_args,
// 				     const poset_path& xsection_space_schema_schema_path,
// 				     const poset_path& xrep_path,
// 				     const poset_path& xbase_space_path,
// 				     const poset_path& xfiber_space_path,
// 				     const arg_list& xfiber_space_args,
// 				     const poset_path& xfiber_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e13::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e13::host_type>::
// new_space<fiber_bundle::sec_jcb_e13>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_path,
// 				     const arg_list& xsection_space_args,
// 				     const poset_path& xsection_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e13::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e13::host_type>::
// new_space<fiber_bundle::sec_jcb_e13>(fiber_bundles_namespace& xns,
// 				     const string& xname,
// 				     const poset_path& xbase_path,
// 				     const poset_path& xrep_path);

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::
// new_section_space_schema<fiber_bundle::sec_jcb_e13>(const poset_path& xsection_space_schema_path,
// 						    const arg_list& xsection_space_schema_args,
// 						    const poset_path& xsection_space_schema_schema_path,
// 						    const poset_path& xrep_path,
// 						    const poset_path& xbase_space_path,
// 						    const poset_path& xfiber_space_path,
// 						    const arg_list& xfiber_space_args,
// 						    const poset_path& xfiber_space_schema_path,
// 						    bool xauto_access);


// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_jcb_e13::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e13>(const poset_path& xsection_space_path,
// 					     const poset_path& xbase_space_path,
// 					     const poset_path& xrep_path,
// 					     bool xauto_access);


// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_jcb_e13::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e13>(const poset_path& xsection_space_path,
// 					     const arg_list& xsection_space_args,
// 					     const poset_path& xsection_space_schema_path,
// 					     bool xauto_access);


//==============================================================================
// CLASS SEC_JCB_23
//==============================================================================

// $$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_jcb_e23::host_type>::
// new_space<fiber_bundle::sec_jcb_e23>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_schema_path,
// 				     const arg_list& xsection_space_schema_args,
// 				     const poset_path& xsection_space_schema_schema_path,
// 				     const poset_path& xrep_path,
// 				     const poset_path& xbase_space_path,
// 				     const poset_path& xfiber_space_path,
// 				     const arg_list& xfiber_space_args,
// 				     const poset_path& xfiber_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e23::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e23::host_type>::
// new_space<fiber_bundle::sec_jcb_e23>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_path,
// 				     const arg_list& xsection_space_args,
// 				     const poset_path& xsection_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e23::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e23::host_type>::
// new_space<fiber_bundle::sec_jcb_e23>(fiber_bundles_namespace& xns,
// 				     const string& xname,
// 				     const poset_path& xbase_path,
// 				     const poset_path& xrep_path);

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::
// new_section_space_schema<fiber_bundle::sec_jcb_e23>(const poset_path& xsection_space_schema_path,
// 						    const arg_list& xsection_space_schema_args,
// 						    const poset_path& xsection_space_schema_schema_path,
// 						    const poset_path& xrep_path,
// 						    const poset_path& xbase_space_path,
// 						    const poset_path& xfiber_space_path,
// 						    const arg_list& xfiber_space_args,
// 						    const poset_path& xfiber_space_schema_path,
// 						    bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e23::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e23>(const poset_path& xsection_space_path,
// 					     const poset_path& xbase_space_path,
// 					     const poset_path& xrep_path,
// 					     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e23::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e23>(const poset_path& xsection_space_path,
// 					     const arg_list& xsection_space_args,
// 					     const poset_path& xsection_space_schema_path,
// 					     bool xauto_access);

//==============================================================================
// CLASS SEC_JCB_33
//==============================================================================

// $$SCRIBBLE: Jacobian not complete in fiber_bundles_namespace

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_jcb_e33::host_type>::
// new_space<fiber_bundle::sec_jcb_e33>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_schema_path,
// 				     const arg_list& xsection_space_schema_args,
// 				     const poset_path& xsection_space_schema_schema_path,
// 				     const poset_path& xrep_path,
// 				     const poset_path& xbase_space_path,
// 				     const poset_path& xfiber_space_path,
// 				     const arg_list& xfiber_space_args,
// 				     const poset_path& xfiber_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e33::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e33::host_type>::
// new_space<fiber_bundle::sec_jcb_e33>(fiber_bundles_namespace& xns,
// 				     const poset_path& xsection_space_path,
// 				     const arg_list& xsection_space_args,
// 				     const poset_path& xsection_space_schema_path,
// 				     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e33::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_jcb_e33::host_type>::
// new_space<fiber_bundle::sec_jcb_e33>(fiber_bundles_namespace& xns,
// 				     const string& xname,
// 				     const poset_path& xbase_path,
// 				     const poset_path& xrep_path);

// 
//template
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::
// new_section_space_schema<fiber_bundle::sec_jcb_e33>(const poset_path& xsection_space_schema_path,
// 						    const arg_list& xsection_space_schema_args,
// 						    const poset_path& xsection_space_schema_schema_path,
// 						    const poset_path& xrep_path,
// 						    const poset_path& xbase_space_path,
// 						    const poset_path& xfiber_space_path,
// 						    const arg_list& xfiber_space_args,
// 						    const poset_path& xfiber_space_schema_path,
// 						    bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e33::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e33>(const poset_path& xsection_space_path,
// 					     const poset_path& xbase_space_path,
// 					     const poset_path& xrep_path,
// 					     bool xauto_access);

// 
//template
// fiber_bundle::sec_jcb_e33::host_type&
// fiber_bundle::fiber_bundles_namespace::
// new_section_space<fiber_bundle::sec_jcb_e33>(const poset_path& xsection_space_path,
// 					     const arg_list& xsection_space_args,
// 					     const poset_path& xsection_space_schema_path,
// 					     bool xauto_access);

//==============================================================================
// CLASS SEC_JCB_ED
//==============================================================================

// ...


//==============================================================================
// CLASS SEC_MET
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_met::host_type>::
// new_space<fiber_bundle::sec_met>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met::host_type>::
// new_space<fiber_bundle::sec_met>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met::host_type>::
// new_space<fiber_bundle::sec_met>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_met::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_met>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_met>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_met>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_met>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_met>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_MET_E1
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_met_e1::host_type>::
// new_space<fiber_bundle::sec_met_e1>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e1::host_type>::
// new_space<fiber_bundle::sec_met_e1>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e1::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e1::host_type>::
// new_space<fiber_bundle::sec_met_e1>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e1::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_met_e1>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_met_e1>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_met_e1>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e1>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;



//==============================================================================
// CLASS SEC_MET_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_met_e2::host_type>::
// new_space<fiber_bundle::sec_met_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e2::host_type>::
// new_space<fiber_bundle::sec_met_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e2::host_type>::
// new_space<fiber_bundle::sec_met_e2>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_met_e2>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_met_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_met_e2>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_MET_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_met_e3::host_type>::
// new_space<fiber_bundle::sec_met_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e3::host_type>::
// new_space<fiber_bundle::sec_met_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_e3::host_type>::
// new_space<fiber_bundle::sec_met_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_met_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_met_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_met_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_MET_ED
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_met_ed::host_type>::
// new_space<fiber_bundle::sec_met_ed>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_ed::host_type>::
// new_space<fiber_bundle::sec_met_ed>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_met_ed::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_met_ed::host_type>::
// new_space<fiber_bundle::sec_met_ed>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_met_ed::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_met_ed>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_met_ed>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_met_ed>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_met_ed>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st2::host_type>::
// new_space<fiber_bundle::sec_st2>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2::host_type>::
// new_space<fiber_bundle::sec_st2>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2::host_type>::
// new_space<fiber_bundle::sec_st2>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st2>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st2>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st2>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st2_e2::host_type>::
// new_space<fiber_bundle::sec_st2_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2_e2::host_type>::
// new_space<fiber_bundle::sec_st2_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2_e2::host_type>::
// new_space<fiber_bundle::sec_st2_e2>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st2_e2>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st2_e2>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st2_e3::host_type>::
// new_space<fiber_bundle::sec_st2_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2_e3::host_type>::
// new_space<fiber_bundle::sec_st2_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st2_e3::host_type>::
// new_space<fiber_bundle::sec_st2_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st2_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st2_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st2_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st3::host_type>::
// new_space<fiber_bundle::sec_st3>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st3::host_type>::
// new_space<fiber_bundle::sec_st3>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st3::host_type>::
// new_space<fiber_bundle::sec_st3>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st3>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st3>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st3>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st3>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st3>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st3_e3::host_type>::
// new_space<fiber_bundle::sec_st3_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st3_e3::host_type>::
// new_space<fiber_bundle::sec_st3_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st3_e3::host_type>::
// new_space<fiber_bundle::sec_st3_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st3_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st3_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st3_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st4::host_type>::
// new_space<fiber_bundle::sec_st4>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4::host_type>::
// new_space<fiber_bundle::sec_st4>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4::host_type>::
// new_space<fiber_bundle::sec_st4>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st4>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st4>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st4>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st4>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST4_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st4_e2::host_type>::
// new_space<fiber_bundle::sec_st4_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4_e2::host_type>::
// new_space<fiber_bundle::sec_st4_e2>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4_e2::host_type>::
// new_space<fiber_bundle::sec_st4_e2>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st4_e2>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st4_e2>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e2>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_ST4_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_st4_e3::host_type>::
// new_space<fiber_bundle::sec_st4_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_schema_path,
// 				    const arg_list& xsection_space_schema_args,
// 				    const poset_path& xsection_space_schema_schema_path,
// 				    const poset_path& xrep_path,
// 				    const poset_path& xbase_space_path,
// 				    const poset_path& xfiber_space_path,
// 				    const arg_list& xfiber_space_args,
// 				    const poset_path& xfiber_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4_e3::host_type>::
// new_space<fiber_bundle::sec_st4_e3>(fiber_bundles_namespace& xns,
// 				    const poset_path& xsection_space_path,
// 				    const arg_list& xsection_space_args,
// 				    const poset_path& xsection_space_schema_path,
// 				    bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_st4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_st4_e3::host_type>::
// new_space<fiber_bundle::sec_st4_e3>(fiber_bundles_namespace& xns,
// 				    const string& xname,
// 				    const poset_path& xbase_path,
// 				    const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path,
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xsection_space_schema_schema_path,
						   const poset_path& xrep_path,
						   const poset_path& xbase_space_path,
						   const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_path,
					    const poset_path& xbase_space_path,
					    const poset_path& xrep_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_path,
					    const arg_list& xsection_space_args,
					    const poset_path& xsection_space_schema_path,
					    bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path,
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xsection_space_schema_schema_path,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xfiber_space_args,
							  const poset_path& xfiber_space_schema_path,
							  const poset_path& xvector_space_path,
							  const arg_list& xvector_space_args,
							  const poset_path& xvector_space_schema_path,
							  const poset_path& xscalar_space_path,
							  const arg_list& xscalar_space_args,
							  const poset_path& xscalar_space_schema_path,
							  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_st4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_st4_e3>(const poset_path& xtensor_space_path,
						   const arg_list& xtensor_space_args,
						   const poset_path& xtensor_space_schema_path,
						   const poset_path& xvector_space_path,
						   const arg_list& xvector_space_args,
						   const poset_path& xvector_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
						      const poset_path& xvector_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
						      const poset_path& xscalar_space_path, 
						      const arg_list& xspace_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
							     const poset_path& xvector_space_path, 
							     const arg_list& xspace_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xvector_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_st4_e3>(const poset_path& xpath,
							      const poset_path& xrep_path,
							      const poset_path& xbase_space_path,
							      const poset_path& xfiber_space_path,
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
					     const poset_path& xrep_path, 
					     const arg_list& xargs,
					     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xargs,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
				      const poset_path& xfiber_space_path, 
				      const arg_list& xsection_space_schema_args,
				      const arg_list& xfiber_space_args,
				      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      const poset_path& xscalar_space_path, 
							      const arg_list& xfiber_space_args,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
						      const poset_path& xfiber_space_path, 
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xvector_space_path, 
						      const arg_list& xfiber_space_args,
						      const poset_path& xscalar_space_path, 
						      const arg_list& xvector_space_args,
						      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
								   const poset_path& xvector_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
								   const poset_path& xscalar_space_path, 
								   const arg_list& xspace_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xspace_path, 
									  const poset_path& xvector_space_path, 
									  const arg_list& xspace_args,
									  const poset_path& xscalar_space_path, 
									  const arg_list& xvector_space_args,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xpath,
									   const poset_path& xrep_path,
									   const poset_path& xbase_space_path,
									   const poset_path& xfiber_space_path,
									   const arg_list& xargs,
									   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xrep_path, 
							   const poset_path& xbase_space_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xargs,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xfiber_space_args,
								   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_st4_e3>(const poset_path& xsection_space_schema_path, 
								   const poset_path& xrep_path, 
								   const poset_path& xbase_space_path, 
								   const poset_path& xfiber_space_path, 
								   const arg_list& xsection_space_schema_args,
								   const poset_path& xvector_space_path, 
								   const arg_list& xfiber_space_args,
								   const poset_path& xscalar_space_path, 
								   const arg_list& xvector_space_args,
								   bool xauto_access) const;


//==============================================================================
// CLASS SEC_STP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_stp::host_type>::
// new_space<fiber_bundle::sec_stp>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_schema_path,
// 				 const arg_list& xsection_space_schema_args,
// 				 const poset_path& xsection_space_schema_schema_path,
// 				 const poset_path& xrep_path,
// 				 const poset_path& xbase_space_path,
// 				 const poset_path& xfiber_space_path,
// 				 const arg_list& xfiber_space_args,
// 				 const poset_path& xfiber_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_stp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_stp::host_type>::
// new_space<fiber_bundle::sec_stp>(fiber_bundles_namespace& xns,
// 				 const poset_path& xsection_space_path,
// 				 const arg_list& xsection_space_args,
// 				 const poset_path& xsection_space_schema_path,
// 				 bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_stp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_stp::host_type>::
// new_space<fiber_bundle::sec_stp>(fiber_bundles_namespace& xns,
// 				 const string& xname,
// 				 const poset_path& xbase_path,
// 				 const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path,
						const arg_list& xsection_space_schema_args,
						const poset_path& xsection_space_schema_schema_path,
						const poset_path& xrep_path,
						const poset_path& xbase_space_path,
						const poset_path& xfiber_space_path,
						const arg_list& xfiber_space_args,
						const poset_path& xfiber_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_stp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_stp>(const poset_path& xsection_space_path,
					 const poset_path& xbase_space_path,
					 const poset_path& xrep_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_stp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_stp>(const poset_path& xsection_space_path,
					 const arg_list& xsection_space_args,
					 const poset_path& xsection_space_schema_path,
					 bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path,
						       const arg_list& xsection_space_schema_args,
						       const poset_path& xsection_space_schema_schema_path,
						       const poset_path& xrep_path,
						       const poset_path& xbase_space_path,
						       const poset_path& xfiber_space_path,
						       const arg_list& xfiber_space_args,
						       const poset_path& xfiber_space_schema_path,
						       const poset_path& xvector_space_path,
						       const arg_list& xvector_space_args,
						       const poset_path& xvector_space_schema_path,
						       const poset_path& xscalar_space_path,
						       const arg_list& xscalar_space_args,
						       const poset_path& xscalar_space_schema_path,
						       bool xauto_access);

template
SHEAF_DLL_SPEC
fiber_bundle::sec_stp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_stp>(const poset_path& xtensor_space_path,
						const arg_list& xtensor_space_args,
						const poset_path& xtensor_space_schema_path,
						const poset_path& xvector_space_path,
						const arg_list& xvector_space_args,
						const poset_path& xvector_space_schema_path,
						const poset_path& xscalar_space_path,
						const arg_list& xscalar_space_args,
						const poset_path& xscalar_space_schema_path,
						bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_stp>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
						   const poset_path& xvector_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
						   const poset_path& xscalar_space_path, 
						   const arg_list& xspace_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
							  const poset_path& xvector_space_path, 
							  const arg_list& xspace_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xvector_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_stp>(const poset_path& xpath,
							   const poset_path& xrep_path,
							   const poset_path& xbase_space_path,
							   const poset_path& xfiber_space_path,
							   const arg_list& xargs,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
					  const poset_path& xrep_path, 
					  const arg_list& xargs,
					  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xargs,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
				   const poset_path& xfiber_space_path, 
				   const arg_list& xsection_space_schema_args,
				   const arg_list& xfiber_space_args,
				   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
							   const poset_path& xfiber_space_path, 
							   const arg_list& xsection_space_schema_args,
							   const poset_path& xscalar_space_path, 
							   const arg_list& xfiber_space_args,
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
						   const poset_path& xfiber_space_path, 
						   const arg_list& xsection_space_schema_args,
						   const poset_path& xvector_space_path, 
						   const arg_list& xfiber_space_args,
						   const poset_path& xscalar_space_path, 
						   const arg_list& xvector_space_args,
						   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
								const poset_path& xvector_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
								const poset_path& xscalar_space_path, 
								const arg_list& xspace_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xspace_path, 
								       const poset_path& xvector_space_path, 
								       const arg_list& xspace_args,
								       const poset_path& xscalar_space_path, 
								       const arg_list& xvector_space_args,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_stp>(const poset_path& xpath,
									const poset_path& xrep_path,
									const poset_path& xbase_space_path,
									const poset_path& xfiber_space_path,
									const arg_list& xargs,
									bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
							const poset_path& xrep_path, 
							const poset_path& xbase_space_path, 
							const poset_path& xfiber_space_path, 
							const arg_list& xargs,
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xargs,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xfiber_space_args,
								bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_stp>(const poset_path& xsection_space_schema_path, 
								const poset_path& xrep_path, 
								const poset_path& xbase_space_path, 
								const poset_path& xfiber_space_path, 
								const arg_list& xsection_space_schema_args,
								const poset_path& xvector_space_path, 
								const arg_list& xfiber_space_args,
								const poset_path& xscalar_space_path, 
								const arg_list& xvector_space_args,
								bool xauto_access) const;


//==============================================================================
// CLASS SEC_T2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t2::host_type>::
// new_space<fiber_bundle::sec_t2>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2::host_type>::
// new_space<fiber_bundle::sec_t2>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2::host_type>::
// new_space<fiber_bundle::sec_t2>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xvector_space_path,
						      const arg_list& xvector_space_args,
						      const poset_path& xvector_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t2>(const poset_path& xtensor_space_path,
					       const arg_list& xtensor_space_args,
					       const poset_path& xtensor_space_schema_path,
					       const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
							 const poset_path& xvector_space_path, 
							 const arg_list& xspace_args,
							 const poset_path& xscalar_space_path, 
							 const arg_list& xvector_space_args,
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t2>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
				  const poset_path& xfiber_space_path, 
				  const arg_list& xsection_space_schema_args,
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xvector_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xspace_path, 
								      const poset_path& xvector_space_path, 
								      const arg_list& xspace_args,
								      const poset_path& xscalar_space_path, 
								      const arg_list& xvector_space_args,
								      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t2>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t2>(	const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;


//==============================================================================
// CLASS SEC_T2_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t2_e2::host_type>::
// new_space<fiber_bundle::sec_t2_e2>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_schema_path,
// 				   const arg_list& xsection_space_schema_args,
// 				   const poset_path& xsection_space_schema_schema_path,
// 				   const poset_path& xrep_path,
// 				   const poset_path& xbase_space_path,
// 				   const poset_path& xfiber_space_path,
// 				   const arg_list& xfiber_space_args,
// 				   const poset_path& xfiber_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2_e2::host_type>::
// new_space<fiber_bundle::sec_t2_e2>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_path,
// 				   const arg_list& xsection_space_args,
// 				   const poset_path& xsection_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2_e2::host_type>::
// new_space<fiber_bundle::sec_t2_e2>(fiber_bundles_namespace& xns,
// 				   const string& xname,
// 				   const poset_path& xbase_path,
// 				   const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path,
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xsection_space_schema_schema_path,
						  const poset_path& xrep_path,
						  const poset_path& xbase_space_path,
						  const poset_path& xfiber_space_path,
						  const arg_list& xfiber_space_args,
						  const poset_path& xfiber_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_path,
					   const poset_path& xbase_space_path,
					   const poset_path& xrep_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_path,
					   const arg_list& xsection_space_args,
					   const poset_path& xsection_space_schema_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path,
							 const arg_list& xsection_space_schema_args,
							 const poset_path& xsection_space_schema_schema_path,
							 const poset_path& xrep_path,
							 const poset_path& xbase_space_path,
							 const poset_path& xfiber_space_path,
							 const arg_list& xfiber_space_args,
							 const poset_path& xfiber_space_schema_path,
							 const poset_path& xvector_space_path,
							 const arg_list& xvector_space_args,
							 const poset_path& xvector_space_schema_path,
							 const poset_path& xscalar_space_path,
							 const arg_list& xscalar_space_args,
							 const poset_path& xscalar_space_schema_path,
							 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t2_e2>(const poset_path& xtensor_space_path,
						  const arg_list& xtensor_space_args,
						  const poset_path& xtensor_space_schema_path,
						  const poset_path& xvector_space_path,
						  const arg_list& xvector_space_args,
						  const poset_path& xvector_space_schema_path,
						  const poset_path& xscalar_space_path,
						  const arg_list& xscalar_space_args,
						  const poset_path& xscalar_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
						     const poset_path& xvector_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
						     const poset_path& xscalar_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xspace_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t2_e2>(const poset_path& xpath,
							     const poset_path& xrep_path,
							     const poset_path& xbase_space_path,
							     const poset_path& xfiber_space_path,
							     const arg_list& xargs,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
					    const poset_path& xrep_path, 
					    const arg_list& xargs,
					    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
						    const poset_path& xfiber_space_path, 
						    const arg_list& xargs,
						    bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
				     const poset_path& xfiber_space_path, 
				     const arg_list& xsection_space_schema_args,
				     const arg_list& xfiber_space_args,
				     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
							     const poset_path& xfiber_space_path, 
							     const arg_list& xsection_space_schema_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xfiber_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     const poset_path& xscalar_space_path, 
						     const arg_list& xvector_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
								  const poset_path& xvector_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
								  const poset_path& xscalar_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xspace_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xspace_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xpath,
									  const poset_path& xrep_path,
									  const poset_path& xbase_space_path,
									  const poset_path& xfiber_space_path,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xrep_path, 
							  const poset_path& xbase_space_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xsection_space_schema_args,
								 bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xvector_space_args,
								  bool xauto_access) const;


//==============================================================================
// CLASS SEC_T2_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t2_e3::host_type>::
// new_space<fiber_bundle::sec_t2_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_schema_path,
// 				   const arg_list& xsection_space_schema_args,
// 				   const poset_path& xsection_space_schema_schema_path,
// 				   const poset_path& xrep_path,
// 				   const poset_path& xbase_space_path,
// 				   const poset_path& xfiber_space_path,
// 				   const arg_list& xfiber_space_args,
// 				   const poset_path& xfiber_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2_e3::host_type>::
// new_space<fiber_bundle::sec_t2_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_path,
// 				   const arg_list& xsection_space_args,
// 				   const poset_path& xsection_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t2_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t2_e3::host_type>::
// new_space<fiber_bundle::sec_t2_e3>(fiber_bundles_namespace& xns,
// 				   const string& xname,
// 				   const poset_path& xbase_path,
// 				   const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path,
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xsection_space_schema_schema_path,
						  const poset_path& xrep_path,
						  const poset_path& xbase_space_path,
						  const poset_path& xfiber_space_path,
						  const arg_list& xfiber_space_args,
						  const poset_path& xfiber_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_path,
					   const poset_path& xbase_space_path,
					   const poset_path& xrep_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_path,
					   const arg_list& xsection_space_args,
					   const poset_path& xsection_space_schema_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path,
							 const arg_list& xsection_space_schema_args,
							 const poset_path& xsection_space_schema_schema_path,
							 const poset_path& xrep_path,
							 const poset_path& xbase_space_path,
							 const poset_path& xfiber_space_path,
							 const arg_list& xfiber_space_args,
							 const poset_path& xfiber_space_schema_path,
							 const poset_path& xvector_space_path,
							 const arg_list& xvector_space_args,
							 const poset_path& xvector_space_schema_path,
							 const poset_path& xscalar_space_path,
							 const arg_list& xscalar_space_args,
							 const poset_path& xscalar_space_schema_path,
							 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t2_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t2_e3>(const poset_path& xtensor_space_path,
						  const arg_list& xtensor_space_args,
						  const poset_path& xtensor_space_schema_path,
						  const poset_path& xvector_space_path,
						  const arg_list& xvector_space_args,
						  const poset_path& xvector_space_schema_path,
						  const poset_path& xscalar_space_path,
						  const arg_list& xscalar_space_args,
						  const poset_path& xscalar_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
						     const poset_path& xvector_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
						     const poset_path& xscalar_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xspace_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t2_e3>(const poset_path& xpath,
							     const poset_path& xrep_path,
							     const poset_path& xbase_space_path,
							     const poset_path& xfiber_space_path,
							     const arg_list& xargs,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
					    const poset_path& xrep_path, 
					    const arg_list& xargs,
					    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
						    const poset_path& xfiber_space_path, 
						    const arg_list& xargs,
						    bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
				     const poset_path& xfiber_space_path, 
				     const arg_list& xsection_space_schema_args,
				     const arg_list& xfiber_space_args,
				     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
							     const poset_path& xfiber_space_path, 
							     const arg_list& xsection_space_schema_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xfiber_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     const poset_path& xscalar_space_path, 
						     const arg_list& xvector_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
								  const poset_path& xvector_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
								  const poset_path& xscalar_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xspace_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xspace_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xpath,
									  const poset_path& xrep_path,
									  const poset_path& xbase_space_path,
									  const poset_path& xfiber_space_path,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xrep_path, 
							  const poset_path& xbase_space_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xsection_space_schema_args,
								 bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t2_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xvector_space_args,
								  bool xauto_access) const;


//==============================================================================
// CLASS SEC_T3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t3::host_type>::
// new_space<fiber_bundle::sec_t3>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t3::host_type>::
// new_space<fiber_bundle::sec_t3>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t3::host_type>::
// new_space<fiber_bundle::sec_t3>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t3>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t3>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xvector_space_path,
						      const arg_list& xvector_space_args,
						      const poset_path& xvector_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t3>(const poset_path& xtensor_space_path,
					       const arg_list& xtensor_space_args,
					       const poset_path& xtensor_space_schema_path,
					       const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
							 const poset_path& xvector_space_path, 
							 const arg_list& xspace_args,
							 const poset_path& xscalar_space_path, 
							 const arg_list& xvector_space_args,
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t3>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
				  const poset_path& xfiber_space_path, 
				  const arg_list& xsection_space_schema_args,
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xvector_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xspace_path, 
								      const poset_path& xvector_space_path, 
								      const arg_list& xspace_args,
								      const poset_path& xscalar_space_path, 
								      const arg_list& xvector_space_args,
								      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t3>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t3>(	const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t3>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;


//==============================================================================
// CLASS SEC_T3_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t3_e3::host_type>::
// new_space<fiber_bundle::sec_t3_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_schema_path,
// 				   const arg_list& xsection_space_schema_args,
// 				   const poset_path& xsection_space_schema_schema_path,
// 				   const poset_path& xrep_path,
// 				   const poset_path& xbase_space_path,
// 				   const poset_path& xfiber_space_path,
// 				   const arg_list& xfiber_space_args,
// 				   const poset_path& xfiber_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t3_e3::host_type>::
// new_space<fiber_bundle::sec_t3_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_path,
// 				   const arg_list& xsection_space_args,
// 				   const poset_path& xsection_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t3_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t3_e3::host_type>::
// new_space<fiber_bundle::sec_t3_e3>(fiber_bundles_namespace& xns,
// 				   const string& xname,
// 				   const poset_path& xbase_path,
// 				   const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path,
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xsection_space_schema_schema_path,
						  const poset_path& xrep_path,
						  const poset_path& xbase_space_path,
						  const poset_path& xfiber_space_path,
						  const arg_list& xfiber_space_args,
						  const poset_path& xfiber_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_path,
					   const poset_path& xbase_space_path,
					   const poset_path& xrep_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_path,
					   const arg_list& xsection_space_args,
					   const poset_path& xsection_space_schema_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path,
							 const arg_list& xsection_space_schema_args,
							 const poset_path& xsection_space_schema_schema_path,
							 const poset_path& xrep_path,
							 const poset_path& xbase_space_path,
							 const poset_path& xfiber_space_path,
							 const arg_list& xfiber_space_args,
							 const poset_path& xfiber_space_schema_path,
							 const poset_path& xvector_space_path,
							 const arg_list& xvector_space_args,
							 const poset_path& xvector_space_schema_path,
							 const poset_path& xscalar_space_path,
							 const arg_list& xscalar_space_args,
							 const poset_path& xscalar_space_schema_path,
							 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t3_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t3_e3>(const poset_path& xtensor_space_path,
						  const arg_list& xtensor_space_args,
						  const poset_path& xtensor_space_schema_path,
						  const poset_path& xvector_space_path,
						  const arg_list& xvector_space_args,
						  const poset_path& xvector_space_schema_path,
						  const poset_path& xscalar_space_path,
						  const arg_list& xscalar_space_args,
						  const poset_path& xscalar_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
						     const poset_path& xvector_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
						     const poset_path& xscalar_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xspace_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t3_e3>(const poset_path& xpath,
							     const poset_path& xrep_path,
							     const poset_path& xbase_space_path,
							     const poset_path& xfiber_space_path,
							     const arg_list& xargs,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
					    const poset_path& xrep_path, 
					    const arg_list& xargs,
					    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
						    const poset_path& xfiber_space_path, 
						    const arg_list& xargs,
						    bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
				     const poset_path& xfiber_space_path, 
				     const arg_list& xsection_space_schema_args,
				     const arg_list& xfiber_space_args,
				     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
							     const poset_path& xfiber_space_path, 
							     const arg_list& xsection_space_schema_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xfiber_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     const poset_path& xscalar_space_path, 
						     const arg_list& xvector_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
								  const poset_path& xvector_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
								  const poset_path& xscalar_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xspace_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xspace_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xpath,
									  const poset_path& xrep_path,
									  const poset_path& xbase_space_path,
									  const poset_path& xfiber_space_path,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xrep_path, 
							  const poset_path& xbase_space_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xsection_space_schema_args,
								 bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t3_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xvector_space_args,
								  bool xauto_access) const;


//==============================================================================
// CLASS SEC_T4
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t4::host_type>::
// new_space<fiber_bundle::sec_t4>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4::host_type>::
// new_space<fiber_bundle::sec_t4>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4::host_type>::
// new_space<fiber_bundle::sec_t4>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xvector_space_path,
						      const arg_list& xvector_space_args,
						      const poset_path& xvector_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t4>(const poset_path& xtensor_space_path,
					       const arg_list& xtensor_space_args,
					       const poset_path& xtensor_space_schema_path,
					       const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t4>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
							 const poset_path& xvector_space_path, 
							 const arg_list& xspace_args,
							 const poset_path& xscalar_space_path, 
							 const arg_list& xvector_space_args,
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t4>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
				  const poset_path& xfiber_space_path, 
				  const arg_list& xsection_space_schema_args,
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xvector_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xspace_path, 
								      const poset_path& xvector_space_path, 
								      const arg_list& xspace_args,
								      const poset_path& xscalar_space_path, 
								      const arg_list& xvector_space_args,
								      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t4>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t4>(	const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;


//==============================================================================
// CLASS SEC_T4_E2
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t4_e2::host_type>::
// new_space<fiber_bundle::sec_t4_e2>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_schema_path,
// 				   const arg_list& xsection_space_schema_args,
// 				   const poset_path& xsection_space_schema_schema_path,
// 				   const poset_path& xrep_path,
// 				   const poset_path& xbase_space_path,
// 				   const poset_path& xfiber_space_path,
// 				   const arg_list& xfiber_space_args,
// 				   const poset_path& xfiber_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4_e2::host_type>::
// new_space<fiber_bundle::sec_t4_e2>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_path,
// 				   const arg_list& xsection_space_args,
// 				   const poset_path& xsection_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4_e2::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4_e2::host_type>::
// new_space<fiber_bundle::sec_t4_e2>(fiber_bundles_namespace& xns,
// 				   const string& xname,
// 				   const poset_path& xbase_path,
// 				   const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path,
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xsection_space_schema_schema_path,
						  const poset_path& xrep_path,
						  const poset_path& xbase_space_path,
						  const poset_path& xfiber_space_path,
						  const arg_list& xfiber_space_args,
						  const poset_path& xfiber_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_path,
					   const poset_path& xbase_space_path,
					   const poset_path& xrep_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_path,
					   const arg_list& xsection_space_args,
					   const poset_path& xsection_space_schema_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path,
							 const arg_list& xsection_space_schema_args,
							 const poset_path& xsection_space_schema_schema_path,
							 const poset_path& xrep_path,
							 const poset_path& xbase_space_path,
							 const poset_path& xfiber_space_path,
							 const arg_list& xfiber_space_args,
							 const poset_path& xfiber_space_schema_path,
							 const poset_path& xvector_space_path,
							 const arg_list& xvector_space_args,
							 const poset_path& xvector_space_schema_path,
							 const poset_path& xscalar_space_path,
							 const arg_list& xscalar_space_args,
							 const poset_path& xscalar_space_schema_path,
							 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e2::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t4_e2>(const poset_path& xtensor_space_path,
						  const arg_list& xtensor_space_args,
						  const poset_path& xtensor_space_schema_path,
						  const poset_path& xvector_space_path,
						  const arg_list& xvector_space_args,
						  const poset_path& xvector_space_schema_path,
						  const poset_path& xscalar_space_path,
						  const arg_list& xscalar_space_args,
						  const poset_path& xscalar_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
						     const poset_path& xvector_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
						     const poset_path& xscalar_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xspace_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t4_e2>(const poset_path& xpath,
							     const poset_path& xrep_path,
							     const poset_path& xbase_space_path,
							     const poset_path& xfiber_space_path,
							     const arg_list& xargs,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
					    const poset_path& xrep_path, 
					    const arg_list& xargs,
					    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
						    const poset_path& xfiber_space_path, 
						    const arg_list& xargs,
						    bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
				     const poset_path& xfiber_space_path, 
				     const arg_list& xsection_space_schema_args,
				     const arg_list& xfiber_space_args,
				     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
							     const poset_path& xfiber_space_path, 
							     const arg_list& xsection_space_schema_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xfiber_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     const poset_path& xscalar_space_path, 
						     const arg_list& xvector_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
								  const poset_path& xvector_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
								  const poset_path& xscalar_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xspace_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xspace_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xpath,
									  const poset_path& xrep_path,
									  const poset_path& xbase_space_path,
									  const poset_path& xfiber_space_path,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xrep_path, 
							  const poset_path& xbase_space_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xsection_space_schema_args,
								 bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e2>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xvector_space_args,
								  bool xauto_access) const;


//==============================================================================
// CLASS SEC_T4_E3
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_t4_e3::host_type>::
// new_space<fiber_bundle::sec_t4_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_schema_path,
// 				   const arg_list& xsection_space_schema_args,
// 				   const poset_path& xsection_space_schema_schema_path,
// 				   const poset_path& xrep_path,
// 				   const poset_path& xbase_space_path,
// 				   const poset_path& xfiber_space_path,
// 				   const arg_list& xfiber_space_args,
// 				   const poset_path& xfiber_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4_e3::host_type>::
// new_space<fiber_bundle::sec_t4_e3>(fiber_bundles_namespace& xns,
// 				   const poset_path& xsection_space_path,
// 				   const arg_list& xsection_space_args,
// 				   const poset_path& xsection_space_schema_path,
// 				   bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_t4_e3::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_t4_e3::host_type>::
// new_space<fiber_bundle::sec_t4_e3>(fiber_bundles_namespace& xns,
// 				   const string& xname,
// 				   const poset_path& xbase_path,
// 				   const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path,
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xsection_space_schema_schema_path,
						  const poset_path& xrep_path,
						  const poset_path& xbase_space_path,
						  const poset_path& xfiber_space_path,
						  const arg_list& xfiber_space_args,
						  const poset_path& xfiber_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_path,
					   const poset_path& xbase_space_path,
					   const poset_path& xrep_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_path,
					   const arg_list& xsection_space_args,
					   const poset_path& xsection_space_schema_path,
					   bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path,
							 const arg_list& xsection_space_schema_args,
							 const poset_path& xsection_space_schema_schema_path,
							 const poset_path& xrep_path,
							 const poset_path& xbase_space_path,
							 const poset_path& xfiber_space_path,
							 const arg_list& xfiber_space_args,
							 const poset_path& xfiber_space_schema_path,
							 const poset_path& xvector_space_path,
							 const arg_list& xvector_space_args,
							 const poset_path& xvector_space_schema_path,
							 const poset_path& xscalar_space_path,
							 const arg_list& xscalar_space_args,
							 const poset_path& xscalar_space_schema_path,
							 bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_t4_e3::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_t4_e3>(const poset_path& xtensor_space_path,
						  const arg_list& xtensor_space_args,
						  const poset_path& xtensor_space_schema_path,
						  const poset_path& xvector_space_path,
						  const arg_list& xvector_space_args,
						  const poset_path& xvector_space_schema_path,
						  const poset_path& xscalar_space_path,
						  const arg_list& xscalar_space_args,
						  const poset_path& xscalar_space_schema_path,
						  bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
						     const poset_path& xvector_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
						     const poset_path& xscalar_space_path, 
						     const arg_list& xspace_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
							    const poset_path& xvector_space_path, 
							    const arg_list& xspace_args,
							    const poset_path& xscalar_space_path, 
							    const arg_list& xvector_space_args,
							    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_t4_e3>(const poset_path& xpath,
							     const poset_path& xrep_path,
							     const poset_path& xbase_space_path,
							     const poset_path& xfiber_space_path,
							     const arg_list& xargs,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
					    const poset_path& xrep_path, 
					    const arg_list& xargs,
					    bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
						    const poset_path& xfiber_space_path, 
						    const arg_list& xargs,
						    bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
				     const poset_path& xfiber_space_path, 
				     const arg_list& xsection_space_schema_args,
				     const arg_list& xfiber_space_args,
				     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
							     const poset_path& xfiber_space_path, 
							     const arg_list& xsection_space_schema_args,
							     const poset_path& xscalar_space_path, 
							     const arg_list& xfiber_space_args,
							     bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
						     const poset_path& xfiber_space_path, 
						     const arg_list& xsection_space_schema_args,
						     const poset_path& xvector_space_path, 
						     const arg_list& xfiber_space_args,
						     const poset_path& xscalar_space_path, 
						     const arg_list& xvector_space_args,
						     bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
							   bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
								  const poset_path& xvector_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
								  const poset_path& xscalar_space_path, 
								  const arg_list& xspace_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xspace_path, 
									 const poset_path& xvector_space_path, 
									 const arg_list& xspace_args,
									 const poset_path& xscalar_space_path, 
									 const arg_list& xvector_space_args,
									 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xpath,
									  const poset_path& xrep_path,
									  const poset_path& xbase_space_path,
									  const poset_path& xfiber_space_path,
									  const arg_list& xargs,
									  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xrep_path, 
							  const poset_path& xbase_space_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xargs,
								 bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
								 const poset_path& xrep_path, 
								 const poset_path& xbase_space_path, 
								 const poset_path& xfiber_space_path, 
								 const arg_list& xsection_space_schema_args,
								 bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xfiber_space_args,
								  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_t4_e3>(const poset_path& xsection_space_schema_path, 
								  const poset_path& xrep_path, 
								  const poset_path& xbase_space_path, 
								  const poset_path& xfiber_space_path, 
								  const arg_list& xsection_space_schema_args,
								  const poset_path& xvector_space_path, 
								  const arg_list& xfiber_space_args,
								  const poset_path& xscalar_space_path, 
								  const arg_list& xvector_space_args,
								  bool xauto_access) const;


//==============================================================================
// CLASS SEC_TP
//==============================================================================

// template
// SHEAF_DLL_SPEC
// sheaf::poset_path
// fiber_bundle::fiber_bundles_namespace::new_section_space_schema_impl<fiber_bundle::sec_tp::host_type>::
// new_space<fiber_bundle::sec_tp>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_schema_path,
// 				const arg_list& xsection_space_schema_args,
// 				const poset_path& xsection_space_schema_schema_path,
// 				const poset_path& xrep_path,
// 				const poset_path& xbase_space_path,
// 				const poset_path& xfiber_space_path,
// 				const arg_list& xfiber_space_args,
// 				const poset_path& xfiber_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_tp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_tp::host_type>::
// new_space<fiber_bundle::sec_tp>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_tp::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_tp::host_type>::
// new_space<fiber_bundle::sec_tp>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_section_space_schema<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path,
					       const arg_list& xsection_space_schema_args,
					       const poset_path& xsection_space_schema_schema_path,
					       const poset_path& xrep_path,
					       const poset_path& xbase_space_path,
					       const poset_path& xfiber_space_path,
					       const arg_list& xfiber_space_args,
					       const poset_path& xfiber_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_tp>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_tp>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space_schema<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xvector_space_path,
						      const arg_list& xvector_space_args,
						      const poset_path& xvector_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tp::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tensor_section_space<fiber_bundle::sec_tp>(const poset_path& xtensor_space_path,
					       const arg_list& xtensor_space_args,
					       const poset_path& xtensor_space_schema_path,
					       const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_tp>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
						  const poset_path& xvector_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
							 const poset_path& xvector_space_path, 
							 const arg_list& xspace_args,
							 const poset_path& xscalar_space_path, 
							 const arg_list& xvector_space_args,
							 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_tp>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
int
fiber_bundle::fiber_bundles_namespace::
completed_p<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
				  const poset_path& xfiber_space_path, 
				  const arg_list& xsection_space_schema_args,
				  const arg_list& xfiber_space_args,
				  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
						  const poset_path& xfiber_space_path, 
						  const arg_list& xsection_space_schema_args,
						  const poset_path& xvector_space_path, 
						  const arg_list& xfiber_space_args,
						  const poset_path& xscalar_space_path, 
						  const arg_list& xvector_space_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_vector_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
							       const poset_path& xvector_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_tensor_scalar_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xspace_path, 
								      const poset_path& xvector_space_path, 
								      const arg_list& xspace_args,
								      const poset_path& xscalar_space_path, 
								      const arg_list& xvector_space_args,
								      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_tp>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_vector_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template	
bool	
fiber_bundle::fiber_bundles_namespace::	
completed_scalar_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xfiber_space_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_tp>(const poset_path& xsection_space_schema_path, 
							       const poset_path& xrep_path, 
							       const poset_path& xbase_space_path, 
							       const poset_path& xfiber_space_path, 
							       const arg_list& xsection_space_schema_args,
							       const poset_path& xvector_space_path, 
							       const arg_list& xfiber_space_args,
							       const poset_path& xscalar_space_path, 
							       const arg_list& xvector_space_args,
							       bool xauto_access) const;



//==============================================================================
// CLASS SEC_TUPLE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::sec_tuple::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_tuple>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tuple::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_tuple>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_tuple_section_space_schema<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_tuple::host_type&
fiber_bundle::fiber_bundles_namespace::
new_tuple_section_space<fiber_bundle::sec_tuple>(const poset_path& xtuple_space_path,
					       const arg_list& xtuple_space_args,
					       const poset_path& xtuple_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_tuple>(const poset_path& xpath) const;

template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_tuple>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_tuple>(const poset_path& xspace_path, 
							bool xauto_access) const;

template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_tuple>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_tuple>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS SEC_VD
//==============================================================================

// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_vd::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_vd::host_type>::
// new_space<fiber_bundle::sec_vd>(fiber_bundles_namespace& xns,
// 				const poset_path& xsection_space_path,
// 				const arg_list& xsection_space_args,
// 				const poset_path& xsection_space_schema_path,
// 				bool xauto_access);
// 
// 
// template
// SHEAF_DLL_SPEC
// fiber_bundle::sec_vd::host_type&
// fiber_bundle::fiber_bundles_namespace::new_section_space_impl<fiber_bundle::sec_vd::host_type>::
// new_space<fiber_bundle::sec_vd>(fiber_bundles_namespace& xns,
// 				const string& xname,
// 				const poset_path& xbase_path,
// 				const poset_path& xrep_path);
// 
// 
template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd::fiber_type::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_space<fiber_bundle::sec_vd::fiber_type>(const poset_path& xfiber_space_path,
						   const arg_list& xfiber_space_args,
						   const poset_path& xfiber_space_schema_path,
						   const poset_path& xscalar_space_path,
						   const arg_list& xscalar_space_args,	
						   const poset_path& xscalar_space_schema_path,
						   bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_vd>(const poset_path& xsection_space_path,
					const poset_path& xbase_space_path,
					const poset_path& xrep_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd::host_type&
fiber_bundle::fiber_bundles_namespace::
new_section_space<fiber_bundle::sec_vd>(const poset_path& xsection_space_path,
					const arg_list& xsection_space_args,
					const poset_path& xsection_space_schema_path,
					bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space_schema<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path,
						      const arg_list& xsection_space_schema_args,
						      const poset_path& xsection_space_schema_schema_path,
						      const poset_path& xrep_path,
						      const poset_path& xbase_space_path,
						      const poset_path& xfiber_space_path,
						      const arg_list& xfiber_space_args,
						      const poset_path& xfiber_space_schema_path,
						      const poset_path& xscalar_space_path,
						      const arg_list& xscalar_space_args,
						      const poset_path& xscalar_space_schema_path,
						      bool xauto_access);


template
SHEAF_DLL_SPEC
fiber_bundle::sec_vd::host_type&
fiber_bundle::fiber_bundles_namespace::
new_vector_section_space<fiber_bundle::sec_vd>(const poset_path& xvector_space_path,
					       const arg_list& xvector_space_args,
					       const poset_path& xvector_space_schema_path,
					       const poset_path& xscalar_space_path,
					       const arg_list& xscalar_space_args,
					       const poset_path& xscalar_space_schema_path,
					       bool xauto_access);


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_space_path<fiber_bundle::sec_vd>(const poset_path& xpath) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path<fiber_bundle::sec_vd>(const poset_path& xspace_path, 
						  const poset_path& xscalar_space_path, 
						  const arg_list& xspace_args,
						  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path<fiber_bundle::sec_vd>(const poset_path& xpath,
							  const poset_path& xrep_path,
							  const poset_path& xbase_space_path,
							  const poset_path& xfiber_space_path,
							  const arg_list& xargs,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_rep_path<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
					 const poset_path& xrep_path, 
					 const arg_list& xargs,
					 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
						 const poset_path& xfiber_space_path, 
						 const arg_list& xargs,
						 bool xauto_access) const;


template
SHEAF_DLL_SPEC
sheaf::poset_path
fiber_bundle::fiber_bundles_namespace::
completed_section_scalar_space_path<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
							  const poset_path& xfiber_space_path, 
							  const arg_list& xsection_space_schema_args,
							  const poset_path& xscalar_space_path, 
							  const arg_list& xfiber_space_args,
							  bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_space_path_is_available<fiber_bundle::sec_vd>(const poset_path& xspace_path, 
							bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_scalar_space_path_is_available<fiber_bundle::sec_vd>(const poset_path& xspace_path, 
							       const poset_path& xscalar_space_path, 
							       const arg_list& xspace_args,
							       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_section_space_schema_path_is_available<fiber_bundle::sec_vd>(const poset_path& xpath,
								       const poset_path& xrep_path,
								       const poset_path& xbase_space_path,
								       const poset_path& xfiber_space_path,
								       const arg_list& xargs,
								       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_rep_path_is_accessible<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
						       const poset_path& xrep_path, 
						       const poset_path& xbase_space_path, 
						       const poset_path& xfiber_space_path, 
						       const arg_list& xargs,
						       bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_base_space_path_is_accessible<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xargs,
							      bool xauto_access) const;


template
SHEAF_DLL_SPEC
bool
fiber_bundle::fiber_bundles_namespace::
completed_fiber_space_path_is_available<fiber_bundle::sec_vd>(const poset_path& xsection_space_schema_path, 
							      const poset_path& xrep_path, 
							      const poset_path& xbase_space_path, 
							      const poset_path& xfiber_space_path, 
							      const arg_list& xsection_space_schema_args,
							      bool xauto_access) const;


//==============================================================================
// CLASS POINT_BLOCK_1D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::point_block_1d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS POINT_BLOCK_2D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::point_block_2d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS POINT_BLOCK_3D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::point_block_3d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);


//==============================================================================
// CLASS STRUCTURED_BLOCK_1D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::structured_block_1d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS STRUCTURED_BLOCK_2D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::structured_block_2d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS STRUCTURED_BLOCK_3D
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::structured_block_3d>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS ZONE_NODES_BLOCK
//==============================================================================

template
SHEAF_DLL_SPEC 
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::zone_nodes_block>(
                          const poset_path& xbase_space_path,
						  const arg_list& xargs,
						  const poset_path& xschema_path,
						  int xmax_db,
						  bool xauto_access);

//==============================================================================
// CLASS UNSTRUCTURED_BLOCK
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::unstructured_block>(
                         const poset_path& xbase_space_path,
						 const arg_list& xargs,
						 const poset_path& xschema_path,
						 int xmax_db,
						 bool xauto_access);

//==============================================================================
// CLASS BASE_SPACE_MEMBER_PROTOTYPE
//==============================================================================

template
SHEAF_DLL_SPEC
fiber_bundle::base_space_poset&
fiber_bundle::fiber_bundles_namespace::
new_base_space<fiber_bundle::base_space_member_prototype>(
                         const poset_path& xbase_space_path,
						 const arg_list& xargs,
						 const poset_path& xschema_path,
						 int xmax_db,
						 bool xauto_access);

//==============================================================================
//==============================================================================

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
