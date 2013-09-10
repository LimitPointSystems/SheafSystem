//
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
%ignore fiber_bundle::base_space_member_prototype::row_dof_tuple;

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
%rename (new_row_DOF_map) new_row_dof_map(poset_state_handle& xhost,const string& xprototype_name,const string& xlocal_cell_name,size_type xsize,bool xauto_access);


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

%include "fiber_bundle.h"

%include "base_space_factory.h"
%include "base_space_member.h"
%include       "homogeneous_block.h"
%include             "point_block_1d.h"
%include             "point_block_2d.h"
%include             "point_block_3d.h"
%include             "structured_block.h"
%include                   "structured_block_1d.h"
%include                   "structured_block_2d.h"
%include                   "structured_block_3d.h"
%include             "unstructured_block.h"
%include       "local_base_space_member.h"
%include "base_space_member_prototype.h"
%include "base_space_poset.h"
%include "binary_index.h"
%include "binary_index_space.h"
%include "block_connectivity.h"
%include       "hex_connectivity.h"
%include       "line_connectivity.h"
%include       "point_connectivity.h"
%include       "quad_connectivity.h"
%include       "tetra_connectivity.h"
%include       "triangle_connectivity.h"
%include "chart_point.h"
%include       "chart_point_1d.h"
%include       "chart_point_2d.h"
%include       "chart_point_3d.h"
%include "discretization_context.h"
%include "discretization_iterator.h"
%include "eval_family.h"
%include       "constant_eval_family.h"
%include       "dlinear_eval_family.h"
%include       "uniform_eval_family.h"
%include "eval_iterator.h"
%include "fiber_bundles_namespace.h"
%include "group.h"
%include       "gln.h"
%include             "gl2.h"
%include             "gl3.h"
%include "gln_space.h"
%include "i_adjacency_implicit_index_space_iterator.h"
%include "i_adjacency_index_space_interval.h"
%include "i_connectivity_implicit_index_space_iterator.h"
%include "i_connectivity_index_space_interval.h"
%include "ij_adjacency_implicit_index_space_iterator.h"
%include "ij_adjacency_index_space_interval.h"
%include "ij_connectivity_implicit_index_space_iterator.h"
%include "ij_connectivity_index_space_interval.h"
%include "ijk_adjacency_implicit_index_space_iterator.h"
%include "ijk_adjacency_index_space_interval.h"
%include "ijk_connectivity_implicit_index_space_iterator.h"
%include "ijk_connectivity_index_space_interval.h"
%include "sec_rep_descriptor.h"
%include "sec_rep_space.h"
%include       "sec_tuple_space.h"
%include             "sec_vd_space.h"
%include                   "sec_jcb_space.h"
%include                   "sec_tp_space.h"
%include                         "sec_atp_space.h"
%include                              "sec_at0_space.h"
%include                              "sec_at1_space.h"
%include                         "sec_stp_space.h"
%include "sec_rep_space_member.h"
%include       "sec_tuple.h"
%include       "sec_vd.h"
%include             "sec_jcb.h"
%include                   "sec_jcb_ed.h"
%include                         "sec_jcb_e13.h"
%include                         "sec_jcb_e23.h"
%include                         "sec_jcb_e33.h"
%include             "sec_tp.h"
%include                   "sec_atp.h"
%include                         "sec_at0.h"
%include                         "sec_at1.h"
%include                               "sec_ed.h"
%include                                     "sec_e1.h"
%include                                           "sec_e1_uniform.h"
%include                                     "sec_e2.h"
%include                                           "sec_e2_uniform.h"
%include                                     "sec_e3.h"
%include                                           "sec_e3_uniform.h"
%include                                     "sec_e4.h"
%include                         "sec_at2.h"
%include                               "sec_at2_e2.h"
%include                               "sec_at2_e3.h"
%include                         "sec_at3.h"
%include                               "sec_at3_e3.h"
%include                   "sec_stp.h"
%include                         "sec_st2.h"
%include                               "sec_met.h"
%include                                     "sec_met_ed.h"
%include                                           "sec_met_e1.h"
%include                                           "sec_met_e2.h"
%include                                           "sec_met_e3.h"
%include                               "sec_st2_e2.h"
%include                               "sec_st2_e3.h"
%include                         "sec_st3.h"
%include                               "sec_st3_e3.h"
%include                         "sec_st4.h"
%include                               "sec_st4_e2.h"
%include                               "sec_st4_e3.h"
%include                   "sec_t2.h"
%include                         "sec_t2_e2.h"
%include                         "sec_t2_e3.h"
%include                   "sec_t3.h"
%include                         "sec_t3_e3.h"
%include                   "sec_t4.h"
%include                         "sec_t4_e2.h"
%include                         "sec_t4_e3.h"
%include "section_component_iterator.h"
%include       "binary_section_component_iterator.h"
%include "section_dof_iterator.h"
%include  	"binary_section_dof_iterator.h"
%include "section_dof_map.h"
%include       "array_section_dof_map.h"
%include       "sparse_section_dof_map.h"
%include "section_eval_iterator.h"
%include "section_evaluator.h"
%include       "differentiable_section_evaluator.h"
%include       "integrable_section_evaluator.h"
%include       "linear_fcn_space.h"
%include             "bilinear_2d.h"
%include             "constant_fcn_space.h"
%include                   "constant_hex.h"
%include                   "constant_point.h"
%include                   "constant_quad.h"
%include                   "constant_segment.h"
%include                   "constant_tet.h"
%include                   "constant_triangle.h"
%include             "linear_1d.h"
%include             "linear_2d.h"
%include             "linear_3d.h"
%include             "quadratic_1d.h"
%include             "quadratic_2d.h"
%include             "quadratic_3d.h"
%include             "trilinear_3d.h"
%include             "uniform_1d.h"
%include             "uniform_2d.h"
%include             "uniform_3d.h"
%include "section_iteration_state.h"
%include "section_space_schema_jims_index_space_handle.h"
%include "section_space_schema_jims_index_space_iterator.h"
%include "section_space_schema_jims_index_space_state.h"
%include "section_space_schema_member.h"
%include       "binary_section_space_schema_member.h"
%include "section_space_schema_poset.h"
%include       "binary_section_space_schema_poset.h"
%include "ternary_index.h"
%include "ternary_index_space.h"
%include "tuple.h"
%include       "vd.h"
%include             "jcb.h"
%include                   "jcb_ed.h"
%include                         "jcb_e13.h"
%include                         "jcb_e23.h"
%include                         "jcb_e33.h"
%include             "tp.h"
%include                   "atp.h"
%include                         "at0.h"
%include                         "at1.h"
%include                               "ed.h"
%include                                     "e1.h"
%include                                     "e2.h"
%include                                     "e3.h"
%include                                     "e4.h"
%include                         "at2.h"
%include                               "at2_e2.h"
%include                               "at2_e3.h"
%include                         "at3.h"
%include                               "at3_e3.h"
%include                   "stp.h"
%include                         "st2.h"
%include                               "met.h"
%include                                     "met_ed.h"
%include                                           "met_e1.h"
%include                                           "met_e2.h"
%include                                           "met_e3.h"
%include                               "st2_e2.h"
%include                               "st2_e3.h"
%include                         "st3.h"
%include                               "st3_e3.h"
%include                         "st4.h"
%include                               "st4_e2.h"
%include                               "st4_e3.h"
%include                   "t2.h"
%include                         "t2_e2.h"
%include                         "t2_e3.h"
%include                   "t3.h"
%include                         "t3_e3.h"
%include                   "t4.h"
%include                         "t4_e2.h"
%include                         "t4_e3.h"
%include "tuple_space.h"
%include       "vd_space.h"
%include             "jcb_space.h"
%include             "tp_space.h"
%include                   "atp_space.h"
%include                         "at0_space.h"
%include                         "at1_space.h"
%include                   "stp_space.h"
%include "unary_index_space.h"
%include "unstructured_block_builder.h"

//=============================================================================

//=============================================================================
