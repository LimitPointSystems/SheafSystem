
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

//
// Common Swig interface for fiber_bundles cluster
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "fiber_bundles_common_binding_includes.i" as well.

//=============================================================================
// Ignore directives:
//=============================================================================

//$$ISSUE: Due to problems with using a nested class as a return type or
//         argument the following functions need to be ignored.

%ignore fiber_bundle::base_space_member::row_dof_tuple;
%ignore fiber_bundle::base_space_poset::member_dof_tuple;
%ignore fiber_bundle::base_space_poset::table_dof_tuple;
%ignore fiber_bundle::base_space_poset::row_dof_tuple;

%ignore fiber_bundle::block_connectivity::element_type;
%ignore fiber_bundle::hex_connectivity::element_type;
%ignore fiber_bundle::line_connectivity::element_type;
%ignore fiber_bundle::point_connectivity::element_type;
%ignore fiber_bundle::quad_connectivity::element_type;
%ignore fiber_bundle::tetra_connectivity::element_type;
%ignore fiber_bundle::triangle_connectivity::element_type;
%ignore fiber_bundle::hex_connectivity::element_type;

// The follwing 2 functions will cause a "multiple definition error" if not ignored.
// oddly enough, the conflict is with functions of the saqme name, but differing sig in sec_vd.
%ignore add_equal(vd& xresult, const vd& xother, bool xauto_access);
%ignore subtract_equal(vd& xresult, const vd& xother, bool xauto_access);

// Overcome the naming conflict in homogenous_block, lines 218 and 229 respectively.
// Comments say that the version on line 218 is obsoleted. Perhaps we should do away with it to avoid this swig hack.
%rename (new_row_DOF_map) new_row_dof_map(poset_state_handle& xhost,const std::string& xprototype_name,const std::string& xlocal_cell_name,size_type xsize,bool xauto_access);


%ignore fiber_bundle::state::comp(int);

// $$ISSUE: 'sec_rep_space_member_schema' is multiply defined in the generated target language module in scope fiber_bundles_java_bindingJNI
%ignore fiber_bundle::sec_rep_space_member::schema;

// $$ISSUE: sec_rep_space::member_dof_map causes a name clash with
//          sec_rep_space_member::dof_map in generated code.
%ignore fiber_bundle::sec_rep_space::member_dof_map;

//$$ISSUE: Linker sees the following 4 as unresolved.
%ignore fiber_bundle::operator^;
%ignore fiber_bundle::operator^=;
%ignore fiber_bundle::operator<<;
%ignore fiber_bundle::cross;

//$$ISSUE: The following member functions are ignored to keep
//         SWIG from getting confused by the redefinitions of these
//         functions in section_dof_map.h (see the comments there).
//         Ignoring them creates no problems in the generated code.

%ignore fiber_bundle::section_dof_map::get_dofs(scoped_index*, int, void*, size_t);
%ignore fiber_bundle::section_dof_map::put_dofs(scoped_index*, int, void*, size_t);

//$$ISSUE: The following member functions are (temporarily) ignored
//         to prevent SWIG from failing because java does not allow
//         member functions of the same name in a derived class to
//         have different return types than the base class (except
//         when the return type in the derived class is a subtype
//         of the return type in the base class).

%ignore fiber_bundle::vd::table_dofs();
%ignore fiber_bundle::tuple::table_dofs();

%ignore fiber_bundle::vd_lite::table_dofs() const;

//$$ISSUE: The following member functions have the same problem as the 
//         functions above, however, the problem only occured after
//         all functions were moved to namespaces.

%ignore fiber_bundle::structured_block::refine_point;
%ignore fiber_bundle::structured_block::unrefine_point;
%ignore fiber_bundle::section_space_schema_member::host;

//$$ISSUE: The following functions are (temporarily) ignored to prevent
//         SWIG from failing because they are declared in the .h file
//         without template parameters but defined in the .impl.h file
//         with template parameters.

%ignore fiber_bundle::standard_fiber_path;
%ignore fiber_bundle::standard_vector_space_path;

//=============================================================================

//=============================================================================

// This functions have the same name in different namespaces.  Swig does
// not handle this.  Rename each function to have a namespace qualifier
// in the function name.

// fiber_bundles::vd_algebra

%rename (vd_algebra_add) fiber_bundle::vd_algebra::add;
%rename (vd_algebra_add_equal) fiber_bundle::vd_algebra::add_equal;
%rename (vd_algebra_subtract) fiber_bundle::vd_algebra::subtract;
%rename (vd_algebra_subtract_equal) fiber_bundle::vd_algebra::subtract_equal;
%rename (vd_algebra_multiply) fiber_bundle::vd_algebra::multiply;
%rename (vd_algebra_multiply_equal) fiber_bundle::vd_algebra::multiply_equal;
%rename (vd_algebra_divide) fiber_bundle::vd_algebra::divide;
%rename (vd_algebra_divide_equal) fiber_bundle::vd_algebra::divide_equal;
%rename (vd_algebra_max) fiber_bundle::vd_algebra::max;
%rename (vd_algebra_min) fiber_bundle::vd_algebra::min;
%rename (vd_algebra_contract) fiber_bundle::vd_algebra::contract;
%rename (vd_algebra_contract_equal) fiber_bundle::vd_algebra::contract_equal;
%rename (vd_algebra_a_eql) fiber_bundle::vd_algebra::a_eql;
%rename (vd_algebra_r_eql) fiber_bundle::vd_algebra::r_eql;
%rename (vd_algebra_c_eql) fiber_bundle::vd_algebra::c_eql;
%rename (vd_algebra_factorial) fiber_bundle::vd_algebra::factorial;
%rename (vd_algebra_binomial_coefficient) fiber_bundle::vd_algebra::binomial_coefficient;

// fiber_bundles::tp_algebra

%rename (tp_algebra_contract) fiber_bundle::tp_algebra::contract;
%rename (tp_algebra_alt) fiber_bundle::tp_algebra::alt;
%rename (tp_algebra_sym) fiber_bundle::tp_algebra::sym;
%rename (tp_algebra_tensor) fiber_bundle::tp_algebra::tensor;

// fiber_bundle::atp_algebra

%rename (atp_algebra_hook) fiber_bundle::atp_algebra::hook;
%rename (atp_algebra_star) fiber_bundle::atp_algebra::star;
%rename (atp_algebra_wedge) fiber_bundle::atp_algebra::wedge;

// fiber_bundle::ed_algebra

%rename (ed_algebra_dot) fiber_bundle::ed_algebra::dot;
%rename (ed_algebra_length) fiber_bundle::ed_algebra::length;
%rename (ed_algebra_put_length) fiber_bundle::ed_algebra::put_length;
%rename (ed_algebra_normalize) fiber_bundle::ed_algebra::normalize;

// fiber_bundle::e2_algebra

%rename (e2_algebra_perp_dot) fiber_bundle::e2_algebra::perp_dot;

// fiber_bundle::e3_algebra

%rename (e3_algebra_cross) fiber_bundle::e3_algebra::cross;
%rename (e3_algebra_cross_equal) fiber_bundle::e3_algebra::cross_equal;

// fiber_bundle::jcb_algebra

%rename (jcb_algebra_push) fiber_bundle::jcb_algebra::push;
%rename (jcb_algebra_pull) fiber_bundle::jcb_algebra::pull;

// fiber_bundle::met_algebra

%rename (met_algebra_raise) fiber_bundle::met_algebra::raise;
%rename (met_algebra_lower) fiber_bundle::met_algebra::lower;

// fiber_bundle::stp_algebra

%rename (stp_algebra_symmetric_product) fiber_bundle::stp_algebra::symmetric_product;

// fiber_bundle::st2_algebra

%rename (st2_algebra_trace) fiber_bundle::st2_algebra::trace;
%rename (st2_algebra_determinant) fiber_bundle::st2_algebra::determinant;
%rename (st2_algebra_to_principal_axes) fiber_bundle::st2_algebra::to_principal_axes;

// fiber_bundle::sec_at0_algebra

%rename (sec_at0_algebra_acos) fiber_bundle::sec_at0_algebra::acos;
%rename (sec_at0_algebra_asin) fiber_bundle::sec_at0_algebra::asin;
%rename (sec_at0_algebra_atan) fiber_bundle::sec_at0_algebra::atan;
%rename (sec_at0_algebra_atan2) fiber_bundle::sec_at0_algebra::atan2;
%rename (sec_at0_algebra_ceil) fiber_bundle::sec_at0_algebra::ceil;
%rename (sec_at0_algebra_cos) fiber_bundle::sec_at0_algebra::cos;
%rename (sec_at0_algebra_cosh) fiber_bundle::sec_at0_algebra::cosh;
%rename (sec_at0_algebra_exp) fiber_bundle::sec_at0_algebra::exp;
%rename (sec_at0_algebra_fabs) fiber_bundle::sec_at0_algebra::fabs;
%rename (sec_at0_algebra_floor) fiber_bundle::sec_at0_algebra::floor;
%rename (sec_at0_algebra_fmod) fiber_bundle::sec_at0_algebra::fmod;
%rename (sec_at0_algebra_frexp) fiber_bundle::sec_at0_algebra::frexp;
%rename (sec_at0_algebra_ldexp) fiber_bundle::sec_at0_algebra::ldexp;
%rename (sec_at0_algebra_log) fiber_bundle::sec_at0_algebra::log;
%rename (sec_at0_algebra_log10) fiber_bundle::sec_at0_algebra::log10;
%rename (sec_at0_algebra_modf) fiber_bundle::sec_at0_algebra::modf;
%rename (sec_at0_algebra_pow) fiber_bundle::sec_at0_algebra::pow;
%rename (sec_at0_algebra_sin) fiber_bundle::sec_at0_algebra::sin;
%rename (sec_at0_algebra_sinh) fiber_bundle::sec_at0_algebra::sinh;
%rename (sec_at0_algebra_sqrt) fiber_bundle::sec_at0_algebra::sqrt;
%rename (sec_at0_algebra_tan) fiber_bundle::sec_at0_algebra::tan;
%rename (sec_at0_algebra_tanh) fiber_bundle::sec_at0_algebra::tanh;

// fiber_bundles::sec_vd_algebra

%rename (sec_vd_algebra_add) fiber_bundle::sec_vd_algebra::add;
%rename (sec_vd_algebra_add_equal) fiber_bundle::sec_vd_algebra::add_equal;
%rename (sec_vd_algebra_subtract) fiber_bundle::sec_vd_algebra::subtract;
%rename (sec_vd_algebra_subtract_equal) fiber_bundle::sec_vd_algebra::subtract_equal;
%rename (sec_vd_algebra_multiply) fiber_bundle::sec_vd_algebra::multiply;
%rename (sec_vd_algebra_multiply_equal) fiber_bundle::sec_vd_algebra::multiply_equal;
%rename (sec_vd_algebra_divide) fiber_bundle::sec_vd_algebra::divide;
%rename (sec_vd_algebra_divide_equal) fiber_bundle::sec_vd_algebra::divide_equal;
%rename (sec_vd_algebra_max) fiber_bundle::sec_vd_algebra::max;
%rename (sec_vd_algebra_min) fiber_bundle::sec_vd_algebra::min;
%rename (sec_vd_algebra_contract) fiber_bundle::sec_vd_algebra::contract;
%rename (sec_vd_algebra_extrema) fiber_bundle::sec_vd_algebra::extrema;
%rename (sec_vd_algebra_assign) fiber_bundle::sec_vd_algebra::assign;
%rename (sec_vd_algebra_binary_op) fiber_bundle::sec_vd_algebra::binary_op;
%rename (sec_vd_algebra_unary_op) fiber_bundle::sec_vd_algebra::unary_op;

// fiber_bundles::sec_tp_algebra

%rename (sec_tp_algebra_contract) fiber_bundle::sec_tp_algebra::contract;
%rename (sec_tp_algebra_alt) fiber_bundle::sec_tp_algebra::alt;
%rename (sec_tp_algebra_sym) fiber_bundle::sec_tp_algebra::sym;
%rename (sec_tp_algebra_tensor) fiber_bundle::sec_tp_algebra::tensor;

// fiber_bundle::sec_atp_algebra

%rename (sec_atp_algebra_hook) fiber_bundle::sec_atp_algebra::hook;
%rename (sec_atp_algebra_star) fiber_bundle::sec_atp_algebra::star;
%rename (sec_atp_algebra_wedge) fiber_bundle::sec_atp_algebra::wedge;

// fiber_bundle::sec_ed_algebra

%rename (sec_ed_algebra_dot) fiber_bundle::sec_ed_algebra::dot;
%rename (sec_ed_algebra_length) fiber_bundle::sec_ed_algebra::length;
%rename (sec_ed_algebra_put_length) fiber_bundle::sec_ed_algebra::put_length;
%rename (sec_ed_algebra_normalize) fiber_bundle::sec_ed_algebra::normalize;

// fiber_bundle::sec_e3_algebra

%rename (sec_e3_algebra_cross) fiber_bundle::sec_e3_algebra::cross;
%rename (sec_e3_algebra_cross_equal) fiber_bundle::sec_e3_algebra::cross_equal;

// fiber_bundle::sec_jcb_algebra

%rename (sec_jcb_algebra_push) fiber_bundle::sec_jcb_algebra::push;
%rename (sec_jcb_algebra_pull) fiber_bundle::sec_jcb_algebra::pull;

// fiber_bundle::sec_met_algebra

%rename (sec_met_algebra_raise) fiber_bundle::sec_met_algebra::raise;
%rename (sec_met_algebra_lower) fiber_bundle::sec_met_algebra::lower;

// fiber_bundle::sec_stp_algebra

%rename (sec_stp_algebra_symmetric_product) fiber_bundle::sec_stp_algebra::symmetric_product;

// fiber_bundle::sec_st2_algebra

%rename (sec_st2_algebra_trace) fiber_bundle::sec_st2_algebra::trace;
%rename (sec_st2_algebra_determinant) fiber_bundle::sec_st2_algebra::determinant;

//=============================================================================

// Include the list of files to be inserted into the generated code.

%include "fiber_bundles_common_binding_includes.i"

//=============================================================================

// The list of classes, etc for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================

%include "SheafSystem/fiber_bundle.h"

%include "SheafSystem/base_space_factory.h"
%include "SheafSystem/base_space_member.h"
%include       "SheafSystem/homogeneous_block.h"
%include             "SheafSystem/point_block_1d.h"
%include             "SheafSystem/point_block_2d.h"
%include             "SheafSystem/point_block_3d.h"
%include             "SheafSystem/structured_block.h"
%include                   "SheafSystem/structured_block_1d.h"
%include                   "SheafSystem/structured_block_2d.h"
%include                   "SheafSystem/structured_block_3d.h"
%include             "SheafSystem/unstructured_block.h"
%include       "SheafSystem/local_base_space_member.h"
%include "SheafSystem/base_space_poset.h"
%include "SheafSystem/binary_index.h"
%include "SheafSystem/binary_index_space.h"
%include "SheafSystem/block_connectivity.h"
%include       "SheafSystem/hex_connectivity.h"
%include       "SheafSystem/line_connectivity.h"
%include       "SheafSystem/point_connectivity.h"
%include       "SheafSystem/quad_connectivity.h"
%include       "SheafSystem/tetra_connectivity.h"
%include       "SheafSystem/triangle_connectivity.h"
%include "SheafSystem/chart_point.h"
%include       "SheafSystem/chart_point_1d.h"
%include       "SheafSystem/chart_point_2d.h"
%include       "SheafSystem/chart_point_3d.h"
%include "SheafSystem/discretization_context.h"
%include "SheafSystem/discretization_iterator.h"
%include "SheafSystem/eval_family.h"
%include       "SheafSystem/constant_eval_family.h"
%include       "SheafSystem/dlinear_eval_family.h"
%include       "SheafSystem/uniform_eval_family.h"
%include "SheafSystem/eval_iterator.h"
%include "SheafSystem/fiber_bundles_namespace.h"
%include "SheafSystem/group.h"
%include       "SheafSystem/gln.h"
%include             "SheafSystem/gl2.h"
%include             "SheafSystem/gl3.h"
%include "SheafSystem/gln_space.h"
%include "SheafSystem/i_adjacency_implicit_index_space_iterator.h"
%include "SheafSystem/i_adjacency_index_space_interval.h"
%include "SheafSystem/i_connectivity_implicit_index_space_iterator.h"
%include "SheafSystem/i_connectivity_index_space_interval.h"
%include "SheafSystem/ij_adjacency_implicit_index_space_iterator.h"
%include "SheafSystem/ij_adjacency_index_space_interval.h"
%include "SheafSystem/ij_connectivity_implicit_index_space_iterator.h"
%include "SheafSystem/ij_connectivity_index_space_interval.h"
%include "SheafSystem/ijk_adjacency_implicit_index_space_iterator.h"
%include "SheafSystem/ijk_adjacency_index_space_interval.h"
%include "SheafSystem/ijk_connectivity_implicit_index_space_iterator.h"
%include "SheafSystem/ijk_connectivity_index_space_interval.h"
%include "SheafSystem/sec_rep_descriptor.h"
%include "SheafSystem/sec_rep_space.h"
%include       "SheafSystem/sec_tuple_space.h"
%include             "SheafSystem/sec_vd_space.h"
%include                   "SheafSystem/sec_jcb_space.h"
%include                   "SheafSystem/sec_tp_space.h"
%include                         "SheafSystem/sec_atp_space.h"
%include                              "SheafSystem/sec_at0_space.h"
%include                              "SheafSystem/sec_at1_space.h"
%include                         "SheafSystem/sec_stp_space.h"
%include "SheafSystem/sec_rep_space_member.h"
%include       "SheafSystem/sec_tuple.h"
%include       "SheafSystem/sec_vd.h"
%include             "SheafSystem/sec_jcb.h"
%include                   "SheafSystem/sec_jcb_ed.h"
%include                         "SheafSystem/sec_jcb_e13.h"
%include                         "SheafSystem/sec_jcb_e23.h"
%include                         "SheafSystem/sec_jcb_e33.h"
%include             "SheafSystem/sec_tp.h"
%include                   "SheafSystem/sec_atp.h"
%include                         "SheafSystem/sec_at0.h"
%include                         "SheafSystem/sec_at1.h"
%include                               "SheafSystem/sec_ed.h"
%include                                     "SheafSystem/sec_e1.h"
%include                                           "SheafSystem/sec_e1_uniform.h"
%include                                     "SheafSystem/sec_e2.h"
%include                                           "SheafSystem/sec_e2_uniform.h"
%include                                     "SheafSystem/sec_e3.h"
%include                                           "SheafSystem/sec_e3_uniform.h"
%include                                     "SheafSystem/sec_e4.h"
%include                         "SheafSystem/sec_at2.h"
%include                               "SheafSystem/sec_at2_e2.h"
%include                               "SheafSystem/sec_at2_e3.h"
%include                         "SheafSystem/sec_at3.h"
%include                               "SheafSystem/sec_at3_e3.h"
%include                   "SheafSystem/sec_stp.h"
%include                         "SheafSystem/sec_st2.h"
%include                               "SheafSystem/sec_met.h"
%include                                     "SheafSystem/sec_met_ed.h"
%include                                           "SheafSystem/sec_met_e1.h"
%include                                           "SheafSystem/sec_met_e2.h"
%include                                           "SheafSystem/sec_met_e3.h"
%include                               "SheafSystem/sec_st2_e2.h"
%include                               "SheafSystem/sec_st2_e3.h"
%include                         "SheafSystem/sec_st3.h"
%include                               "SheafSystem/sec_st3_e3.h"
%include                         "SheafSystem/sec_st4.h"
%include                               "SheafSystem/sec_st4_e2.h"
%include                               "SheafSystem/sec_st4_e3.h"
%include                   "SheafSystem/sec_t2.h"
%include                         "SheafSystem/sec_t2_e2.h"
%include                         "SheafSystem/sec_t2_e3.h"
%include                   "SheafSystem/sec_t3.h"
%include                         "SheafSystem/sec_t3_e3.h"
%include                   "SheafSystem/sec_t4.h"
%include                         "SheafSystem/sec_t4_e2.h"
%include                         "SheafSystem/sec_t4_e3.h"
%include "SheafSystem/section_component_iterator.h"
%include       "SheafSystem/binary_section_component_iterator.h"
%include "SheafSystem/section_dof_iterator.h"
%include       "SheafSystem/binary_section_dof_iterator.h"
%include "SheafSystem/section_dof_map.h"
%include       "SheafSystem/array_section_dof_map.h"
%include       "SheafSystem/sparse_section_dof_map.h"
%include "SheafSystem/section_eval_iterator.h"
%include "SheafSystem/section_evaluator.h"
%include       "SheafSystem/differentiable_section_evaluator.h"
%include       "SheafSystem/integrable_section_evaluator.h"
%include       "SheafSystem/linear_fcn_space.h"
%include             "SheafSystem/bilinear_2d.h"
%include             "SheafSystem/constant_fcn_space.h"
%include                   "SheafSystem/constant_hex.h"
%include                   "SheafSystem/constant_point.h"
%include                   "SheafSystem/constant_quad.h"
%include                   "SheafSystem/constant_segment.h"
%include                   "SheafSystem/constant_tet.h"
%include                   "SheafSystem/constant_triangle.h"
%include             "SheafSystem/linear_1d.h"
%include             "SheafSystem/linear_2d.h"
%include             "SheafSystem/linear_3d.h"
%include             "SheafSystem/quadratic_1d.h"
%include             "SheafSystem/quadratic_2d.h"
%include             "SheafSystem/quadratic_3d.h"
%include             "SheafSystem/trilinear_3d.h"
%include             "SheafSystem/uniform_1d.h"
%include             "SheafSystem/uniform_2d.h"
%include             "SheafSystem/uniform_3d.h"
%include "SheafSystem/section_iteration_state.h"
%include "SheafSystem/section_space_schema_jims_index_space_handle.h"
%include "SheafSystem/section_space_schema_jims_index_space_iterator.h"
%include "SheafSystem/section_space_schema_jims_index_space_state.h"
%include "SheafSystem/section_space_schema_member.h"
%include       "SheafSystem/binary_section_space_schema_member.h"
%include "SheafSystem/section_space_schema_poset.h"
%include       "SheafSystem/binary_section_space_schema_poset.h"
%include "SheafSystem/ternary_index.h"
%include "SheafSystem/ternary_index_space.h"
%include "SheafSystem/tuple.h"
%include       "SheafSystem/vd.h"
%include             "SheafSystem/jcb.h"
%include                   "SheafSystem/jcb_ed.h"
%include                         "SheafSystem/jcb_e13.h"
%include                         "SheafSystem/jcb_e23.h"
%include                         "SheafSystem/jcb_e33.h"
%include             "SheafSystem/tp.h"
%include                   "SheafSystem/atp.h"
%include                         "SheafSystem/at0.h"
%include                         "SheafSystem/at1.h"
%include                               "SheafSystem/ed.h"
%include                                     "SheafSystem/e1.h"
%include                                     "SheafSystem/e2.h"
%include                                     "SheafSystem/e3.h"
%include                                     "SheafSystem/e4.h"
%include                         "SheafSystem/at2.h"
%include                               "SheafSystem/at2_e2.h"
%include                               "SheafSystem/at2_e3.h"
%include                         "SheafSystem/at3.h"
%include                               "SheafSystem/at3_e3.h"
%include                   "SheafSystem/stp.h"
%include                         "SheafSystem/st2.h"
%include                               "SheafSystem/met.h"
%include                                     "SheafSystem/met_ed.h"
%include                                           "SheafSystem/met_e1.h"
%include                                           "SheafSystem/met_e2.h"
%include                                           "SheafSystem/met_e3.h"
%include                               "SheafSystem/st2_e2.h"
%include                               "SheafSystem/st2_e3.h"
%include                         "SheafSystem/st3.h"
%include                               "SheafSystem/st3_e3.h"
%include                         "SheafSystem/st4.h"
%include                               "SheafSystem/st4_e2.h"
%include                               "SheafSystem/st4_e3.h"
%include                   "SheafSystem/t2.h"
%include                         "SheafSystem/t2_e2.h"
%include                         "SheafSystem/t2_e3.h"
%include                   "SheafSystem/t3.h"
%include                         "SheafSystem/t3_e3.h"
%include                   "SheafSystem/t4.h"
%include                         "SheafSystem/t4_e2.h"
%include                         "SheafSystem/t4_e3.h"
%include "SheafSystem/tuple_space.h"
%include       "SheafSystem/vd_space.h"
%include             "SheafSystem/jcb_space.h"
%include             "SheafSystem/tp_space.h"
%include                   "SheafSystem/atp_space.h"
%include                         "SheafSystem/at0_space.h"
%include                         "SheafSystem/at1_space.h"
%include                   "SheafSystem/stp_space.h"
%include "SheafSystem/unary_index_space.h"
%include "SheafSystem/unstructured_block_builder.h"

//=============================================================================

//=============================================================================
