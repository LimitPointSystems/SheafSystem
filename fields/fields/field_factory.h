
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Prototype for field_factory.

#ifndef FIELD_FACTORY_H
#define FIELD_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

#ifndef FIELDS_H
#include "fields.h"
#endif

#ifndef POSET_PATH_H
#include "poset_path.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

namespace sheaf
{
class arg_list;
template <class T>
class block;
class namespace_poset;
}

namespace fiber_bundle
{
class sec_at0;
class sec_e1;
class sec_e2;
class sec_e3;
class sec_ed;
class sec_vd;

class base_space_member;
class structured_block_1d;
class structured_block_2d;
class structured_block_3d;
class unstructured_block;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 
class field_vd;

///
/// Test case generator for fields cluster.
/// @deprecated Use field_factory_2.
///
class SHEAF_DLL_SPEC field_factory
{

  // =============================================================================
  /// @name FIELD_FACTORY FACET
  // =============================================================================
  //@{

public:

  ///
  /// Creates a field with property the same type as xprop
  /// and its associated structured base space, section spaces,
  /// and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber__name and xprop_fiber_name, respectively.
  /// The section spaces are named with the standard form
  /// fiber_space_name+"_on_"+xbase_space_name.
  ///
  template <typename T>
  static field_vd*
  new_structured_field(fiber_bundles_namespace& xns,
                       const string& xbase_space_name,
                       const block<int>& xindex_ubs,
                       const string& xcoord_name,
                       const string& xprop_name,
                       T& xprop,
                       const string& xcoord_fiber_schema_name = "",
                       const string& xcoord_fiber_name = "",
                       const string& xcoord_section_space_name = "",
                       const string& xprop_fiber_schema_name = "",
                       const string& xprop_fiber_name = "",
                       const string& xprop_section_space_name = "",
                       const string& xprop_rep_name = "");

  ///
  /// Creates a field with property the same type as xprop
  /// and its associated structured base space, section spaces,
  /// and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber_name and xprop_fiber_name, respectively.
  /// The section spaces are named with the standard form
  /// fiber_space_name+"_on_"+xbase_space_name.
  ///
  static field_vd*
  new_structured_field(fiber_bundles_namespace& xns,
                       const string& xbase_space_name,
                       const block<int>& xindex_ubs,
                       const string& xcoord_fiber_name,
                       const string& xcoord_name,
                       const string& xprop_fiber_name,
                       const string& xprop_name,
                       const poset_path& xprop_rep_path,
                       sec_vd& xprop);

  ///
  /// Creates a field with property the same type as xprop
  /// and its associated structured base space, section spaces,
  /// and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber_name and xprop_fiber_name, respectively.
  ///
  static field_vd*
  new_structured_field(fiber_bundles_namespace& xns,
                       const string& xbase_space_name,
                       const block<int>& xindex_ubs,
                       const string& xcoord_fiber_name,
                       const string& xcoord_section_space_name,
                       const string& xcoord_name,
                       const string& xprop_fiber_name,
                       const string& xprop_section_space_name,
                       const string& xprop_name,
                       const poset_path& xprop_rep_path,
                       sec_vd& xprop);


  ///
  /// Creates a field with uniform coordinates and with
  /// property the same type as xprop
  /// and its associated structured base space, section spaces,
  /// and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber__name and xprop_fiber_name, respectively.
  /// The section spaces are named with the standard form
  /// fiber_space_name+"_on_"+xbase_space_name.
  ///
  static field_vd*
  new_uniform_field(fiber_bundles_namespace& xns,
                    const string& xbase_space_name,
                    const block<int>& xindex_ubs,
                    block<sec_vd_value_type>& xlower,
                    block<sec_vd_value_type>& xupper,
                    const string& xcoord_fiber_name,
                    const string& xcoord_name,
                    const string& xprop_fiber_name,
                    const string& xprop_name,
                    const poset_path& xprop_rep_path,
                    sec_vd& xprop);


  ///
  /// Creates a field with uniform coordinates and with
  /// property the same type as xprop
  /// and its associated structured base space, section spaces,
  /// and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber_name and xprop_fiber_name, respectively.
  ///
  static field_vd*
  new_uniform_field(fiber_bundles_namespace& xns,
                    const string& xbase_space_name,
                    const block<int>& xindex_ubs,
                    block<sec_vd_value_type>& xlower,
                    block<sec_vd_value_type>& xupper,
                    const string& xcoord_fiber_name,
                    const string& xcoord_section_space_name,
                    const string& xcoord_name,
                    const string& xprop_fiber_name,
                    const string& xprop_section_space_name,
                    const string& xprop_name,
                    const poset_path& xprop_rep_path,
                    sec_vd& xprop);

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a point mesh
  /// with coordinates which locate the points in xi_size
  /// array, with cooordinate bounds xlower and xupper, and with property values
  /// given by xfcn. If xfcn == 0, then field_vd::property_value_function_example
  /// is used.
  ///
  static field_vd*
  new_scalar_field_1d_points(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             property_dof_function_type xfcn = 0,
                             const poset_path& xproperty_rep_path =
                               "sec_rep_descriptors/vertex_vertex_constant");


  ///
  /// Creates a scalar field and its associated 1D unstructured base space,
  /// fiber spaces, section spaces, and sections, with coordinates and
  /// property fiber schema specified by xcoord_fiber_schema_path and
  /// xprop_fiber_schema_path, respectively.
  ///
  static field_vd*
  new_scalar_field_1d(fiber_bundles_namespace& xns,
                      const string& xbase_space_name,
                      size_type xi_size,
                      const poset_path& xcoord_fiber_schema_path,
                      const string& xcoord_fiber_name,
                      const string& xcoord_section_space_name,
                      const arg_list& xcoord_section_space_table_dofs,
                      const string& xcoord_name,
                      const poset_path& xprop_fiber_schema_path,
                      const string& xprop_fiber_name,
                      const string& xprop_section_space_name,
                      const arg_list& xprop_section_space_table_dofs,
                      const string& xprop_name,
                      const poset_path& xprop_rep_path);



  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 1D mesh
  /// of size xi_size, with cooordinate bounds xlower and xupper,
  /// and with property values given by xfcn. If xfcn == 0,
  /// then field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   property_dof_function_type xfcn = 0,
                                   const poset_path& xproperty_rep_path =
                                     "sec_rep_descriptors/vertex_element_dlinear");


  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 1D uniform mesh
  /// of size xi_size with cooordinate bounds xlower and xupper and
  /// with property values given by xfcn. If xfcn == 0, then
  /// field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_1d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              property_dof_function_type xfcn = 0,
                              const poset_path& xproperty_rep_path =
                                "sec_rep_descriptors/vertex_element_dlinear");

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a point mesh
  /// with coordinates which locate the points in an xi_size by xj_size rectangular
  /// array, with cooordinate bounds xlower and xupper, and with property values
  /// given by xfcn. If xfcn == 0, then field_vd::property_value_function_example
  /// is used.
  ///
  static field_vd*
  new_scalar_field_2d_points(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             size_type xj_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             property_dof_function_type xfcn = 0,
                             const poset_path& xproperty_rep_path =
                               "sec_rep_descriptors/vertex_vertex_constant");


  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D mesh with
  /// general connectivity, but arranged in an xi_size by xj_size rectangular array of
  /// quads (xuse_quads true) or triangles(xuse_quads false), with cooordinate
  /// bounds xlower and xupper, and with property values given by xfcn.
  /// If xfcn == 0, then field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   size_type xj_size,
                                   bool xuse_quads,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   property_dof_function_type xfcn = 0,
                                   const poset_path& xproperty_rep_path =
                                     "sec_rep_descriptors/vertex_element_dlinear");


#ifdef HAVE_VTK

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D mesh
  /// which is a Delaunay triangulation of xpt_ct points randomly generated
  /// within the cooordinate bounds xlower and xupper, and with property values
  /// given by xfcn. If xfcn == 0, then field_vd::property_value_function_example
  /// is used.
  ///
  static field_vd*
  new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xpt_ct,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   property_dof_function_type xfcn = 0,
                                   const poset_path& xproperty_rep_path =
                                     "sec_rep_descriptors/vertex_element_dlinear");

#endif

  ///
  /// Creates a scalar field on a 2D structured base space, with
  /// associated fibers, section spaces, and sections,
  /// as specified by the arguments.
  ///
  static field_vd*
  new_scalar_field_2d_structured(fiber_bundles_namespace& xns,
                                 const string& xbase_space_name,
                                 size_type xi_size,
                                 size_type xj_size,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const poset_path& xcoord_fiber_schema_path,
                                 const string& xcoord_fiber_name,
                                 const string& xcoord_section_space_name,
                                 const arg_list& xcoord_section_space_table_dofs,
                                 const string& xcoord_name,
                                 const poset_path& xprop_fiber_schema_path,
                                 const string& xprop_fiber_name,
                                 const string& xprop_section_space_name,
                                 const arg_list& xprop_section_space_table_dofs,
                                 const string& xprop_name,
                                 const poset_path& xprop_rep_path);
  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D uniform mesh
  /// xi_size by xj_size with cooordinate bounds xlower and xupper and
  /// with property values given by xfcn.
  /// If xfcn == 0, then field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              size_type xj_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              property_dof_function_type xfcn = 0,
                              const poset_path& xproperty_rep_path =
                                "sec_rep_descriptors/vertex_element_dlinear");
                              //"sec_rep_descriptors/vertex_cells_dlinear");

  ///
  /// Creates a scalar field and its associated 2D structured base space,
  /// section spaces, and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber__name and xprop_fiber_name, respectively.
  /// The section spaces are named with the standard form
  /// fiber_space_name+"_on_"+xbase_space_name.
  ///
  static field_vd*
  new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                              const string& xbase_space_name,
                              size_type xi_size,
                              size_type xj_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const string& xcoord_fiber_name,
                              const string& xcoord_name,
                              const string& xprop_fiber_name,
                              const string& xprop_name,
                              const poset_path& xprop_rep_path);

  ///
  /// Creates a scalar field and its associated 2D structured base space,
  /// section spaces, and sections, with coordinate and property fiber spaces
  /// specified by xcoord_fiber__name and xprop_fiber_name, respectively.
  ///
  static field_vd*
  new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                              const string& xbase_space_name,
                              size_type xi_size,
                              size_type xj_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const string& xcoord_fiber_name,
                              const string& xcoord_section_space_name,
                              const string& xcoord_name,
                              const string& xprop_fiber_name,
                              const string& xprop_section_space_name,
                              const string& xprop_name,
                              const poset_path& xprop_rep_path);




  ///
  /// Creates a scalar field on a 2D uniform base space, with
  /// associated fibers, section spaces, and sections,
  /// as specified by the arguments.
  ///
  static field_vd*
  new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                              const string& xbase_space_name,
                              size_type xi_size,
                              size_type xj_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const poset_path& xcoord_fiber_schema_path,
                              const string& xcoord_fiber_name,
                              const string& xcoord_section_space_name,
                              const arg_list& xcoord_section_space_table_dofs,
                              const string& xcoord_name,
                              const poset_path& xprop_fiber_schema_path,
                              const string& xprop_fiber_name,
                              const string& xprop_section_space_name,
                              const arg_list& xprop_section_space_table_dofs,
                              const string& xprop_name,
                              const poset_path& xprop_rep_path);

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a point mesh
  /// with coordinates which locate the points in an xi_size by xj_size rectangular
  /// array, with cooordinate bounds xlower and xupper, and with property values
  /// given by xfcn. If xfcn == 0, then field_vd::property_value_function_example
  /// is used.
  ///
  static field_vd*
  new_scalar_field_3d_points(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             size_type xj_size,
                             size_type xk_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             property_dof_function_type xfcn = 0,
                             const poset_path& xproperty_rep_path =
                               "sec_rep_descriptors/vertex_vertex_constant");


  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D mesh with
  /// general connectivity, but arranged in an xi_size by xj_size by xk_size
  /// cubic array of hexs (xuse_hexs true) or tet(xuse_hexs false), with cooordinate
  /// bounds xlower and xupper, and with property values given by xfcn.
  /// If xfcn == 0, then field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   size_type xj_size,
                                   size_type xk_size,
                                   bool xuse_hexs,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   property_dof_function_type xfcn = 0,
                                   const poset_path& xproperty_rep_path =
                                     "sec_rep_descriptors/vertex_element_dlinear");


#ifdef HAVE_VTK

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D mesh
  /// which is a Delaunay tessalation of xpt_ct points randomly generated
  /// within the cooordinate bounds xlower and xupper, and with property values
  /// given by xfcn. If xfcn == 0, then field_vd::property_value_function_example
  /// is used.
  ///
  static field_vd*
  new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xpt_ct,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   property_dof_function_type xfcn = 0,
                                   const poset_path& xproperty_rep_path =
                                     "sec_rep_descriptors/vertex_element_dlinear");

#endif

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D uniform mesh
  /// xi_size by xj_size by xk_size with cooordinate bounds xlower and xupper and
  /// with property values given by xfcn.
  /// If xfcn == 0, then field_vd::property_value_function_example is used.
  ///
  static field_vd*
  new_scalar_field_3d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              size_type xj_size,
                              size_type xk_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              property_dof_function_type xfcn = 0,
                              const poset_path& xproperty_rep_path =
                                "sec_rep_descriptors/vertex_element_dlinear");
                              //"sec_rep_descriptors/vertex_cells_dlinear");

  //@}


  // ===========================================================
  /// @name JAVA WRAPPER SUPPORT FACET
  // ===========================================================
  //@{

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 1D
  //  uniform mesh of size xi_size with cooordinate bounds xlower and xupper and
  /// with property values given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_1d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const string& xfcn);

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 1D mesh
  /// of size xi_size, with cooordinate bounds xlower and xupper,
  /// and with property values given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   const string& xfcn);

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D mesh with
  /// general connectivity, but arranged in an xi_size by xj_size rectangular
  /// array of quads (xuse_quads true) or triangles(xuse_quads false), with
  /// cooordinate bounds xlower and xupper, and with property values given by
  //  function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   size_type xj_size,
                                   bool xuse_quads,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   const string& xfcn);

#ifdef HAVE_VTK

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D mesh
  /// which is a Delaunay triangulation of xpt_ct points randomly generated
  /// within the cooordinate bounds xlower and xupper, and with property values
  /// given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xpt_ct,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   const string& xfcn);

#endif

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 2D
  /// uniform mesh xi_size by xj_size with cooordinate bounds xlower and
  /// xupper and with property values given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              size_type xj_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const string& xfcn);

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D mesh with
  /// general connectivity, but arranged in an xi_size by xj_size by xk_size
  /// cubic array of hexs (xuse_hexs true) or tet(xuse_hexs false), with cooordinate
  /// bounds xlower and xupper, and with property values given by function
  /// with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xi_size,
                                   size_type xj_size,
                                   size_type xk_size,
                                   bool xuse_hexs,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   const string& xfcn);


#ifdef HAVE_VTK

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D mesh
  /// which is a Delaunay tessalation of xpt_ct points randomly generated
  /// within the cooordinate bounds xlower and xupper, and with property values
  /// given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                   const string& xname,
                                   size_type xpt_ct,
                                   block<sec_vd_value_type>& xlower,
                                   block<sec_vd_value_type>& xupper,
                                   const string& xfcn);

#endif

  ///
  /// Creates a scalar field with name xname+"_scalar_property" on a 3D uniform mesh
  /// xi_size by xj_size by xk_size with cooordinate bounds xlower and xupper and
  /// with property values given by function with name xfcn.
  /// Intended mostly for use from Java wrappers.
  ///
  static field_vd*
  new_scalar_field_3d_uniform(fiber_bundles_namespace& xns,
                              const string& xname,
                              size_type xi_size,
                              size_type xj_size,
                              size_type xk_size,
                              block<sec_vd_value_type>& xlower,
                              block<sec_vd_value_type>& xupper,
                              const string& xfcn);




  ///
  /// Scalar property dof function, linear so it can be fit
  /// exactly by both linear and multilinear elements.
  /// Intended to be easy to check field dofs for correctness.
  ///
  static void linear_scalar_fcn(block<sec_vd_value_type>& xglobal_coords,
                                block<sec_vd_dof_type>& xproperty_dofs);

  ///
  /// Step property dof function. Not exactly a step, really a ramp.
  /// Test case centers coarse mesh zone on origin of coordinates,
  /// so make sure test function not symmetric (or antisymmetric).
  /// Otherwise, the error at the center may be unexpectedly small.
  ///
  static void step_fcn(block<sec_vd_value_type>& xglobal_coords,
                       block<sec_vd_dof_type>& xproperty_dofs);

  ///
  /// Property dof function with value 0.0.
  ///
  static void zero(block<sec_vd_value_type>& xglobal_coords,
                   block<sec_vd_dof_type>& xproperty_dofs);


  ///
  /// The property dof function with name xname. Intended to enable
  /// passing property_dof_function pointers from Java.
  ///
  static property_dof_function_type property_dof_function(const string& xname);

  ///
  /// Deletes field xfield and all associated section spaces, section schema spaces,
  /// and base space, if they are no longer being used. If xdelete_coord_fiber
  /// delete the coordinate fiber space, if it is no longer beinbg used, and
  /// similarly for xdelete_prop_fiber.
  ///
  static void delete_field_spaces(field_vd* xfield,
                                  bool xdelete_coord_fiber,
                                  bool xdelete_prop_fiber);


protected:

  ///
  /// Creates a 0D mesh of (xi_size+1) points, without
  /// any higher dimensional cells. Intended to be given coordinates
  /// that locate the points in a (xi_size+1) rectangular array.
  ///
  static unstructured_block*
  new_0d_point_base_space(namespace_poset& xns,
                          const string& xname,
                          size_type xi_size);

  ///
  /// Creates a 0D mesh of (xi_size+1)*(xj_size+1) points, without
  /// any higher dimensional cells. Intended to be given coordinates
  /// that locate the points in a (xi_size+1)x(xj_size+1) rectangular array.
  ///
  static unstructured_block*
  new_0d_point_base_space(namespace_poset& xns,
                          const string& xname,
                          size_type xi_size,
                          size_type xj_size);

  ///
  /// Creates a 0D mesh of (xi_size+1)*(xj_size+1)*(xk_size+1) points, without
  /// any higher dimensional cells. Intended to be given coordinates
  /// that locate the points in a (xi_size+1)x(xj_size+1)x(xk_size+1) rectangular array.
  ///
  static unstructured_block*
  new_0d_point_base_space(namespace_poset& xns,
                          const string& xname,
                          size_type xi_size,
                          size_type xj_size,
                          size_type xk_size);

  ///
  /// Creates a 1D mesh of size xi_size.
  ///
  static unstructured_block*
  new_1d_unstructured_base_space(namespace_poset& xns,
                                 const string& xname,
                                 size_type xi_size);

  ///
  /// Creates 1D cooordinates with bounds xlower and xupper.
  ///
  static sec_e1*
  new_1d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                  const string& xname,
                                  size_type xi_size,
                                  block<sec_vd_value_type>& xlower,
                                  block<sec_vd_value_type>& xupper,
                                  unstructured_block& xbase_space,
                                  const poset_path& xrep_path =
                                    "sec_rep_descriptors/vertex_element_dlinear");

  ///
  /// Creates a 1D structured mesh with xi_size.
  ///
  static structured_block_1d*
  new_1d_structured_base_space(namespace_poset& xns,
                               const string& xname,
                               size_type xi_size);

  ///
  /// Creates 1D uniform coordinates with bounds xlower and xupper.
  ///
  static sec_e1*
  new_1d_uniform_coordinates(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             structured_block_1d& xbase_space);

  ///
  /// Creates a 2D mesh with general connectivity,
  /// but arranged in an xi_size by xj_size rectangular array of
  /// quads (xuse_quads true) or triangles(xuse_quads false).
  ///
  static unstructured_block*
  new_2d_unstructured_base_space(namespace_poset& xns,
                                 const string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 bool xuse_quads);

  ///
  /// Creates 2D cooordinates with bounds xlower and xupper.
  ///
  static sec_e2*
  new_2d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                  const string& xname,
                                  size_type xi_size,
                                  size_type xj_size,
                                  block<sec_vd_value_type>& xlower,
                                  block<sec_vd_value_type>& xupper,
                                  unstructured_block& xbase_space,
                                  const poset_path& xrep_path =
                                    "sec_rep_descriptors/vertex_element_dlinear");

#ifdef HAVE_VTK
  ///
  /// Creates a 2D mesh with general connectivity which is a Delaunay
  /// triangulation of xpt_ct points randomly generated in the unit circle.
  ///
  static unstructured_block*
  new_2d_unstructured_base_space(namespace_poset& xns,
                                 const string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xpt_coords);

#endif

  ///
  /// Creates 2D cooordinates with bounds xlower and xupper for a mesh
  /// with general connectivity which is a Delaunay triangulation of
  /// xpt_ct points randomly generated in the unit circle.
  ///
  static sec_e2*
  new_2d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                  const string& xname,
                                  size_type xpt_ct,
                                  block<sec_vd_value_type>& xlower,
                                  block<sec_vd_value_type>& xupper,
                                  unstructured_block& xbase_space,
                                  const block<sec_vd_value_type>& xpt_coords);

  ///
  /// Creates a 2D structured mesh with xi_size by xj_size.
  ///
  static structured_block_2d*
  new_2d_structured_base_space(namespace_poset& xns,
                               const string& xname,
                               size_type xi_size,
                               size_type xj_size);

  ///
  /// Creates 2D uniform coordinates with bounds xlower and xupper.
  ///
  static sec_e2*
  new_2d_uniform_coordinates(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             size_type xj_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             structured_block_2d& xbase_space);

  ///
  /// Creates a 3D mesh with general connectivity,
  /// but arranged in an xi_size by xj_size by xk_size cubic array of
  /// hexs (xuse_hexs true) or tet(xuse_hexs false).
  ///
  static unstructured_block*
  new_3d_unstructured_base_space(namespace_poset& xns,
                                 const string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 size_type xk_size,
                                 bool xuse_hexs);


  ///
  /// Creates 3D cooordinates with bounds xlower and xupper.
  ///
  static sec_e3*
  new_3d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                  const string& xname,
                                  size_type xi_size,
                                  size_type xj_size,
                                  size_type xk_size,
                                  block<sec_vd_value_type>& xlower,
                                  block<sec_vd_value_type>& xupper,
                                  unstructured_block& xbase_space,
                                  const poset_path& xrep_path =
                                    "sec_rep_descriptors/vertex_element_dlinear");

#ifdef HAVE_VTK

  ///
  /// Creates a 3D mesh with general connectivity which is a Delaunay
  /// tesselation of xpt_ct points randomly generated in the unit circle.
  ///
  static unstructured_block*
  new_3d_unstructured_base_space(namespace_poset& xns,
                                 const string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xpt_coords);

#endif

  ///
  /// Creates 3D cooordinates with bounds xlower and xupper for a mesh
  /// with general connectivity which is a Delaunay tesselation of
  /// xpt_ct points randomly generated in the unit circle.
  ///
  static sec_e3*
  new_3d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                  const string& xname,
                                  size_type xpt_ct,
                                  block<sec_vd_value_type>& xlower,
                                  block<sec_vd_value_type>& xupper,
                                  unstructured_block& xbase_space,
                                  const block<sec_vd_value_type>& xpt_coords);

  ///
  /// Creates a 3D structured mesh with xi_size by xj_size by xk_size.
  ///
  static structured_block_3d*
  new_3d_structured_base_space(namespace_poset& xns,
                               const string& xname,
                               size_type xi_size,
                               size_type xj_size,
                               size_type xk_size);

  ///
  /// Creates 3D uniform coordinates with bounds xlower and xupper.
  ///
  static sec_e3*
  new_3d_uniform_coordinates(fiber_bundles_namespace& xns,
                             const string& xname,
                             size_type xi_size,
                             size_type xj_size,
                             size_type xk_size,
                             block<sec_vd_value_type>& xlower,
                             block<sec_vd_value_type>& xupper,
                             structured_block_3d& xbase_space);

  ///
  /// Constructs a structured base space in namespace xns, with name
  /// xbase_space_name, and index bounds xindex_ubs.
  ///
  static base_space_member*
  new_structured_base_space(namespace_poset& xns,
                            const string& xbase_space_name,
                            const block<int>& xindex_ubs);


  ///
  /// Creates a new unattached instance of sec_e<xdc>.
  ///
  static sec_ed*
  new_coord_section_handle(int xdc);

  ///
  /// Sets the dofs for 1D uniform coordinate section xcoords
  /// to the bounds specified by xlower and xupper.
  ///
  static void
  put_1d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                            const block<sec_vd_dof_type>& xupper,
                            sec_ed* xcoords);

  ///
  /// Sets the dofs for 2D uniform coordinate section xcoords
  /// to the bounds specified by xlower and xupper.
  ///
  static void
  put_2d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                            const block<sec_vd_dof_type>& xupper,
                            sec_ed* xcoords);

  ///
  /// Sets the dofs for 3D uniform coordinate section xcoords
  /// to the bounds specified by xlower and xupper.
  ///
  static void
  put_3d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                            const block<sec_vd_dof_type>& xupper,
                            sec_ed* xcoords);


  ///
  /// Sets the dofs for dimension xdc uniform coordinate section xcoords
  /// to the bounds specified by xlower and xupper.
  ///
  static void
  put_uniform_coord_dofs(int xdc,
                         const block<sec_vd_dof_type>& xlower,
                         const block<sec_vd_dof_type>& xupper,
                         sec_ed* xcoords);

  ///
  /// Creates a property section with values given by xfcn.
  /// If xfcn == 0, then field_vd::property_value_function_example is used.
  ///
  static sec_at0*
  new_property(fiber_bundles_namespace& xns,
               const string& xname,
               base_space_member& xbase_space,
               const poset_path& xrep_path);

  //@}

};
 
} // namespace fields

#endif // ifndef FIELD_FACTORY_H
