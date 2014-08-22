
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

/// @file
/// Implementation for class field_factory.

#include "field_factory.h"

#include "ComLimitPoint/sheaf/arg_list.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/block.impl.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/namespace_poset_member.h"
#include "ComLimitPoint/fiber_bundle/sec_at0.h"
#include "ComLimitPoint/fiber_bundle/sec_at0_space.h"
#include "ComLimitPoint/fiber_bundle/sec_at1_space.h"
#include "ComLimitPoint/fiber_bundle/sec_e1.h"
#include "ComLimitPoint/fiber_bundle/sec_e2.h"
#include "ComLimitPoint/fiber_bundle/sec_e3.h"
#include "ComLimitPoint/geometry/sec_ed_invertible.h"
#include "ComLimitPoint/fiber_bundle/sec_vd_space.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"
#include "std_iostream.h"
#include "std_set.h"
#include "std_string.h"
#include "ComLimitPoint/fiber_bundle/structured_block_1d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_2d.h"
#include "ComLimitPoint/fiber_bundle/structured_block_3d.h"
#include "ComLimitPoint/fiber_bundle/unstructured_block.h"
#include "field_vd.h"

#ifdef HAVE_VTK

#include "vtkConnectivityFilter.h"
#include "vtkDelaunay2D.h"
#include "vtkDelaunay3D.h"
#include "vtkMath.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkUnstructuredGrid.h"

#endif

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT


fields::field_vd*
fields::field_factory::
new_scalar_field_1d_points(fiber_bundles_namespace& xns,
                           const std::string& xname,
                           size_type xi_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           property_dof_function_type xfcn,
                           const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_1d_points:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  unstructured_block* lbase_space =
    new_0d_point_base_space(xns, xname, xi_size);

  // Create the coordinates ection.

  sec_e1* lcoords =
    new_1d_unstructured_coordinates(xns,
                                    xname,
                                    xi_size,
                                    xlower,
                                    xupper,
                                    *lbase_space,
                                    "sec_rep_descriptors/vertex_vertex_constant");

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 property_dof_function_type xfcn,
                                 const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_1d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.
  post_information_message("")
  unstructured_block* lbase_space =
    new_1d_unstructured_base_space(xns, xname+"_base_space", xi_size);

  // Create the coordinates section.

  sec_e1* lcoords =
    new_1d_unstructured_coordinates(xns, xname, xi_size, xlower, xupper,
                                    *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);
  post_information_message("")
  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;
  post_information_message("")
  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_1d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            property_dof_function_type xfcn,
                            const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_1d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  structured_block_1d* lbase_space =
    new_1d_structured_base_space(xns, xname+"_base_space", xi_size);

  // Create the coordinates section.

  sec_e1* lcoords =
    new_1d_uniform_coordinates(xns, xname, xi_size, xlower, xupper,
                               *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_2d_points(fiber_bundles_namespace& xns,
                           const std::string& xname,
                           size_type xi_size,
                           size_type xj_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           property_dof_function_type xfcn,
                           const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  unstructured_block* lbase_space =
    new_0d_point_base_space(xns, xname, xi_size, xj_size);

  // Create the coordinates ection.

  sec_e2* lcoords =
    new_2d_unstructured_coordinates(xns,
                                    xname,
                                    xi_size,
                                    xj_size,
                                    xlower,
                                    xupper,
                                    *lbase_space,
                                    "sec_rep_descriptors/vertex_vertex_constant");

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 bool xuse_quads,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 property_dof_function_type xfcn,
                                 const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  unstructured_block* lbase_space =
    new_2d_unstructured_base_space(xns, xname, xi_size, xj_size, xuse_quads);

  // Create the coordinates ection.
  
  sec_e2* lcoords =
    new_2d_unstructured_coordinates(xns, xname, xi_size, xj_size,
                                    xlower, xupper, *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


#ifdef HAVE_VTK
fields::field_vd*
fields::field_factory::
new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 property_dof_function_type xfcn,
                                 const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  block<sec_vd_value_type> lpt_coords;

  unstructured_block* lbase_space =
    new_2d_unstructured_base_space(xns, xname, xpt_ct, lpt_coords);

  // Create the coordinates ection.

  sec_e2* lcoords =
    new_2d_unstructured_coordinates(xns,
                                    xname,
                                    xpt_ct,
                                    xlower,
                                    xupper,
                                    *lbase_space,
                                    lpt_coords);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#endif


fields::field_vd*
fields::field_factory::
new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            size_type xj_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            property_dof_function_type xfcn,
                            const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  structured_block_2d* lbase_space =
    new_2d_structured_base_space(xns, xname+"_base_space", xi_size, xj_size);

  // Create the coordinates section.

  sec_e2* lcoords =
    new_2d_uniform_coordinates(xns, xname, xi_size, xj_size,
                               xlower, xupper, *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_points(fiber_bundles_namespace& xns,
                           const std::string& xname,
                           size_type xi_size,
                           size_type xj_size,
                           size_type xk_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           property_dof_function_type xfcn,
                           const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  unstructured_block* lbase_space =
    new_0d_point_base_space(xns, xname, xi_size, xj_size, xk_size);

  // Create the coordinates ection.

  sec_e3* lcoords =
    new_3d_unstructured_coordinates(xns,
                                    xname,
                                    xi_size,
                                    xj_size,
                                    xk_size,
                                    xlower,
                                    xupper,
                                    *lbase_space,
                                    "sec_rep_descriptors/vertex_vertex_constant");

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 size_type xk_size,
                                 bool xuse_hexs,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 property_dof_function_type xfcn,
                                 const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_3d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  unstructured_block* lbase_space =
    new_3d_unstructured_base_space(xns, xname, xi_size, xj_size, xk_size, xuse_hexs);

  // Create the coordinates ection.

  sec_e3* lcoords =
    new_3d_unstructured_coordinates(xns, xname, xi_size, xj_size, xk_size,
                                    xlower, xupper, *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#ifdef HAVE_VTK

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 property_dof_function_type xfcn,
                                 const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  block<sec_vd_value_type> lpt_coords;

  unstructured_block* lbase_space =
    new_3d_unstructured_base_space(xns, xname, xpt_ct, lpt_coords);

  // Create the coordinates ection.

  sec_e3* lcoords =
    new_3d_unstructured_coordinates(xns,
                                    xname,
                                    xpt_ct,
                                    xlower,
                                    xupper,
                                    *lbase_space,
                                    lpt_coords);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#endif

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            size_type xj_size,
                            size_type xk_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            property_dof_function_type xfcn,
                            const poset_path& xproperty_rep_path)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_3d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xproperty_rep_path));
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);

  // Body:

  // Create the mesh.

  structured_block_3d* lbase_space =
    new_3d_structured_base_space(xns, xname, xi_size, xj_size, xk_size);

  // Create the coordinates ection.

  sec_e3* lcoords =
    new_3d_uniform_coordinates(xns, xname, xi_size, xj_size, xk_size,
                               xlower, xupper, *lbase_space);

  // Create the property section.

  sec_at0* lprop = new_property(xns, xname, *lbase_space, xproperty_rep_path);

  // Create the field.

  field_vd* result = new field_vd(*lcoords, *lprop, true);

  // Set the property values.

  if(xfcn == 0)
  {
    xfcn = field_vd::property_dof_function_example;
  }

  result->put_property_dofs(xfcn, true);

  // Clean up.

  lbase_space->detach_from_state();
  delete lbase_space;

  lcoords->detach_from_state();
  delete lcoords;

  lprop->detach_from_state();
  delete lprop;

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}



// ===========================================================
// JAVA WRAPPER SUPPORT FACET
// ===========================================================

fields::field_vd*
fields::field_factory::
new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_1d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_1d_unstructured(xns,
                                     xname,
                                     xi_size,
                                     xlower,
                                     xupper,
                                     property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_1d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_1d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_1d_uniform(xns,
                                xname,
                                xi_size,
                                xlower,
                                xupper,
                                property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 bool xuse_quads,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_2d_unstructured(xns,
                                     xname,
                                     xi_size,
                                     xj_size,
                                     xuse_quads,
                                     xlower,
                                     xupper,
                                     property_dof_function(xfcn));


  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#ifdef HAVE_VTK

fields::field_vd*
fields::field_factory::
new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_2d_unstructured(xns,
                                     xname,
                                     xpt_ct,
                                     xlower,
                                     xupper,
                                     property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#endif

fields::field_vd*
fields::field_factory::
new_scalar_field_2d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            size_type xj_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_2d_uniform(xns,
                                xname,
                                xi_size,
                                xj_size,
                                xlower,
                                xupper,
                                property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fields::field_vd*
fields::field_factory::
new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xi_size,
                                 size_type xj_size,
                                 size_type xk_size,
                                 bool xuse_hexs,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_3d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_3d_unstructured(xns,
                                     xname,
                                     xi_size,
                                     xj_size,
                                     xk_size,
                                     xuse_hexs,
                                     xlower,
                                     xupper,
                                     property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#ifdef HAVE_VTK

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns,
                                 const std::string& xname,
                                 size_type xpt_ct,
                                 block<sec_vd_value_type>& xlower,
                                 block<sec_vd_value_type>& xupper,
                                 const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_2d_unstructured:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_3d_unstructured(xns,
                                     xname,
                                     xpt_ct,
                                     xlower,
                                     xupper,
                                     property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#endif

fields::field_vd*
fields::field_factory::
new_scalar_field_3d_uniform(fiber_bundles_namespace& xns,
                            const std::string& xname,
                            size_type xi_size,
                            size_type xj_size,
                            size_type xk_size,
                            block<sec_vd_value_type>& xlower,
                            block<sec_vd_value_type>& xupper,
                            const std::string& xfcn)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("new_scalar_field_3d_uniform:");
#endif

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);
  require((xfcn == "linear_scalar_fcn") || (xfcn == "zero") || (xfcn == "property_dof_function_example") || (xfcn == "step_fcn"));

  // Body:

  field_vd* result =
    new_scalar_field_3d_uniform(xns,
                                xname,
                                xi_size,
                                xj_size,
                                xk_size,
                                xlower,
                                xupper,
                                property_dof_function(xfcn));

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


void
fields::field_factory::
delete_field_spaces(field_vd* xfield,
                    bool xdelete_coord_fiber,
                    bool xdelete_prop_fiber)
{
  // Preconditions:


  // Body:

  namespace_poset& lns = xfield->name_space();
  lns.begin_jim_edit_mode(true);

  // The prereq_id dofs define the outgoing adjacency links of the
  // member dependency graph. Build the incoming adjacency links.

  block< set<pod_index_type> > lin_links(lns.member_index_ub().pod());

  namespace_poset_member lmbr(lns.top());

  index_iterator lmbr_itr = lns.member_iterator();
  while(!lmbr_itr.is_done())
  {
    lmbr.attach_to_state(lmbr_itr.index());

    if(lmbr.is_jim(false))
    {
      for(int i=0; i<sheaf::PREREQ_IDS_UB; ++i)
      {
        pod_index_type lprereq_id = lmbr.poset_prereq_id(i);

        if(is_valid(lprereq_id))
        {
          lin_links[lprereq_id].insert(lmbr.index().pod());
        }
      }
    }

    lmbr_itr.next();
  }
  lmbr.detach_from_state();

  // Get the property and coordinate host indices, then delete the field.

  xfield->get_read_access();

  scoped_index lprop_host_index  = xfield->property().host()->index();
  scoped_index lprop_schema_host_index = xfield->property().host()->schema().host()->index();
  scoped_index lprop_fiber_space_index = xfield->property().host()->schema().host()->fiber_space().index();

  scoped_index lcoord_host_index = xfield->coordinates().host()->index();
  scoped_index lcoord_schema_host_index = xfield->coordinates().host()->schema().host()->index();
  scoped_index lcoord_fiber_space_index = xfield->coordinates().host()->schema().host()->fiber_space().index();

  scoped_index lbase_host_index  = xfield->base_space().host()->index();

  xfield->release_access();

  delete xfield;

  // Get the property schema host, remove the in link from the property
  // host to the property schema host, then delete the property host.

  lin_links[lprop_schema_host_index.hub_pod()].erase(lprop_host_index.hub_pod());

  lns.delete_poset(lprop_host_index, true);

  if(lin_links[lprop_schema_host_index.hub_pod()].empty())
  {
    // The prop schema host is no longer being used.
    // Get the fiber space, remove the proerty schema host
    // from the in links of the fiber space,
    // then delete the property schema host.

    lin_links[lprop_fiber_space_index.hub_pod()].erase(lprop_schema_host_index.hub_pod());
    lin_links[lbase_host_index.hub_pod()].erase(lprop_schema_host_index.hub_pod());

    lns.delete_poset(lprop_schema_host_index, true);

    if(lin_links[lprop_fiber_space_index.hub_pod()].empty() && xdelete_prop_fiber)
    {
      // The prop fiber space is no longer being used; delete it..

      lns.delete_poset(lprop_fiber_space_index, true);
    }
  }

  // Get the coord schema host, then delete the coord host.

  lin_links[lcoord_schema_host_index.hub_pod()].erase(lcoord_host_index.hub_pod());

  lns.delete_poset(lcoord_host_index, true);

  if(lin_links[lcoord_schema_host_index.hub_pod()].empty())
  {
    // The coord schema host is no longer being used,
    // delete it, but first get the fiber space.

    lin_links[lcoord_fiber_space_index.hub_pod()].erase(lcoord_schema_host_index.hub_pod());
    lin_links[lbase_host_index.hub_pod()].erase(lcoord_schema_host_index.hub_pod());

    lns.delete_poset(lcoord_schema_host_index, true);

    if(lin_links[lcoord_fiber_space_index.hub_pod()].empty() && xdelete_coord_fiber)
    {
      // The coord fiber space is no longer being used; delete it..

      lns.delete_poset(lcoord_fiber_space_index, true);
    }
  }

  if(lin_links[lbase_host_index.hub_pod()].empty())
  {
    // The base space is no longer being used; delete it.

    lns.delete_poset(lbase_host_index, true);
  }

  // The fiber space group in the namespace may now be empty.
  // If so, it must be deleted because it is incorrectly connected to top.

  pod_index_type lfiber_spaces_id = lns.member_id("fiber_spaces", false);

  if(is_valid(lfiber_spaces_id) && lns.cover_is_empty(LOWER, lfiber_spaces_id))
  {
    lns.delete_link(TOP_INDEX, lfiber_spaces_id);
    lns.delete_member(lfiber_spaces_id);
  }


  // The section space group in the namespace may now be empty.
  // If so, it must be deleted because it is incorrectly connected to top.

  pod_index_type lsection_spaces_id = lns.member_id("section_spaces", false);

  if(is_valid(lsection_spaces_id) && lns.cover_is_empty(LOWER, lsection_spaces_id))
  {
    lns.delete_link(TOP_INDEX, lsection_spaces_id);
    lns.delete_member(lsection_spaces_id);
  }


  lns.end_jim_edit_mode(true, true);


  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// PROTECTED MEMBER FUNCTIONS FACET
// ===========================================================


fiber_bundle::unstructured_block*
fields::field_factory::
new_0d_point_base_space(namespace_poset& xns, const std::string& xname, size_type xi_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 0, false);
  
  lhost.get_read_write_access();

  string proto_member_name("point");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  // Compute the number of points;
  // xi_size is edge count for compatibility with other members.

  size_type lpt_ct = xi_size+1;

  // Construct an array of "client" ids.

  block<int> lclient_ids(lpt_ct);
  for(size_type i=0; i<lpt_ct; ++i)
  {
    lclient_ids.push_back(i);
  }

  // Create a block of points.

  unstructured_block* result =
    new unstructured_block(&lhost,
                           lproto_path,
                           lclient_ids.base(),
                           lclient_ids.ct(),
                           true);

  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::unstructured_block*
fields::field_factory::
new_0d_point_base_space(namespace_poset& xns,
                        const std::string& xname,
                        size_type xi_size,
                        size_type xj_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 0, false);
  
  lhost.get_read_write_access();

  string proto_member_name("point");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  // Compute the number of points;
  // xi_size, xj_size are edge counts for compatibility with other members.

  size_type lpt_ct = (xi_size+1)*(xj_size+1);

  // Construct an array of "client" ids.

  block<int> lclient_ids(lpt_ct);  
  for(size_type i=0; i<lpt_ct; ++i)
  {
    lclient_ids.push_back(i);
  }

  // Create a block of points.

  unstructured_block* result =
    new unstructured_block(&lhost,
                           lproto_path,
                           lclient_ids.base(),
                           lclient_ids.ct(),
                           true);

  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::unstructured_block*
fields::field_factory::
new_0d_point_base_space(namespace_poset& xns,
                        const std::string& xname,
                        size_type xi_size,
                        size_type xj_size,
                        size_type xk_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
//   base_space_poset* lhost = &lns.new_base_space<unstructured_block>(xname+"_base_space",
// 								    "",
// 								    "",
// 								    0,
// 								    true);
  string lbase_name(xname+"_base_space");
  unstructured_block::standard_host(lns, lbase_name, 0, false);
  base_space_poset& lhost = lns.member_poset<base_space_poset>(lbase_name, false);
  
  lhost.get_read_write_access();

  string proto_member_name("point");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  // Compute the number of points;
  // xi_size, xj_size are edge counts for compatibility with other members.

  size_type lpt_ct = (xi_size+1)*(xj_size+1)*(xk_size+1);

  // Construct an array of "client" ids.

  block<int> lclient_ids(lpt_ct);  
  for(size_type i=0; i<lpt_ct; ++i)
  {
    lclient_ids.push_back(i);
  }

  // Create a block of points.

  unstructured_block* result =
    new unstructured_block(&lhost,
                           lproto_path,
                           lclient_ids.base(),
                           lclient_ids.ct(),
                           true);

  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::unstructured_block*
fields::field_factory::
new_1d_unstructured_base_space(namespace_poset& xns,
                               const std::string& xname,
                               size_type xi_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
  base_space_poset& lhost = unstructured_block::standard_host(lns, xname, 1, false);
  
  lhost.get_read_write_access();

  string proto_member_name("segment_complex");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  unstructured_block* result =
    new unstructured_block(&lhost, lproto_path, xi_size);
  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::sec_e1*
fields::field_factory::
new_1d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                const std::string& xname,
                                size_type xi_size,
                                block<sec_vd_value_type>& xlower,
                                block<sec_vd_value_type>& xupper,
                                unstructured_block& xbase_space,
                                const poset_path& xrep_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);
  require(xns.contains_poset_member(xrep_path));

  // Body:

  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";

  sec_rep_space& lhost =
    sec_e1::standard_host(xns, xbase_space.path(true), xrep_path, "", "", false);

  lhost.get_read_write_access(); 
  
  // Make the coordinates section.

  sec_e1* result = new sec_e1(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs.

  size_type i_ub = xi_size + 1;

  sec_vd_value_type ldelta0 = (xupper[0] - xlower[0])/xi_size;

  sec_e1::fiber_type::volatile_type lfiber;

  for(size_type i=0; i<i_ub; ++i)
  {
    lfiber[0] = xlower[0] + i*ldelta0;

    // Connectivity called from unstructured_block assigns vertex
    // client ids using standard array index calculation.

    result->put_fiber(i, lfiber);
  }

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fiber_bundle::structured_block_1d*
fields::field_factory::
new_1d_structured_base_space(namespace_poset& xns,
                             const std::string& xname,
                             size_type xi_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);

  base_space_poset& lhost = structured_block_1d::standard_host(lns, xname, false);
  
  lhost.get_read_write_access();

  structured_block_1d* result =
    new structured_block_1d(&lhost, xi_size, true);
  result->put_name(xname + "_structured_block_1d", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::sec_e1*
fields::field_factory::
new_1d_uniform_coordinates(fiber_bundles_namespace& xns,
                           const std::string& xname,
                           size_type xi_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           structured_block_1d& xbase_space)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xlower.ct() >= 1);
  require(xupper.ct() >= 1);
  require_for_all(i, 0, 1, xlower[i] < xupper[i]);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xlower: ";
  for(int c=0; c<xlower.ub(); ++c)
  {
    cout << "  " << xlower[c];
  }
  cout << endl;

  cout << "xupper: ";
  for(int c=0; c<xupper.ub(); ++c)
  {
    cout << "  " << xupper[c];
  }
  cout << endl;
#endif


  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_block_uniform");

  sec_rep_space& lhost =
    sec_e1::standard_host(xns, xbase_space.path(true), lpath, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e1* result = new sec_e1(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs;

  put_1d_uniform_coord_dofs(xlower, xupper, result);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::unstructured_block*
fields::field_factory::
new_2d_unstructured_base_space(namespace_poset& xns,
                               const std::string& xname,
                               size_type xi_size,
                               size_type xj_size,
                               bool xuse_quads)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);

  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 2, false);
  
  lhost.get_read_write_access();

  string proto_member_name(xuse_quads ? "quad_nodes" : "triangle_nodes");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  unstructured_block* result =
    new unstructured_block(&lhost, lproto_path, xi_size, xj_size);
  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::sec_e2*
fields::field_factory::
new_2d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                const std::string& xname,
                                size_type xi_size,
                                size_type xj_size,
                                block<sec_vd_value_type>& xlower,
                                block<sec_vd_value_type>& xupper,
                                unstructured_block& xbase_space,
                                const poset_path& xrep_path)
{
  // Preconditions:
  
  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);
  require(xns.contains_poset_member(xrep_path));

  // Body:

  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";

  sec_rep_space& lhost =
    sec_e2::standard_host(xns, xbase_space.path(true), xrep_path, "", "", false);

  lhost.get_read_write_access(); 

  // Make the coordinates section.

  sec_e2* result = new sec_e2(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs.

  size_type i_ub = xi_size + 1;
  size_type j_ub = xj_size + 1;

  sec_vd_value_type ldelta0 = (xupper[0] - xlower[0])/xi_size;
  sec_vd_value_type ldelta1 = (xupper[1] - xlower[1])/xj_size;

  sec_e2::fiber_type::volatile_type lfiber;

  pod_index_type lclient_id;

  for(size_type i=0; i<i_ub; ++i)
  {
    lfiber[0] = xlower[0] + i*ldelta0;
    for(size_type j=0; j<j_ub; ++j)
    {
      lfiber[1] = xlower[1] + j*ldelta1;

      // Connectivity called from unstructured_block assigns vertex
      // client ids using standard array index calculation.

      lclient_id = i*j_ub + j;

      result->put_fiber(lclient_id, lfiber);
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#ifdef HAVE_VTK

fiber_bundle::unstructured_block*
fields::field_factory::
new_2d_unstructured_base_space(namespace_poset& xns,
                               const std::string& xname,
                               size_type xpt_ct,
                               block<sec_vd_value_type>& xpt_coords)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);

  // Body:

  // Create xpt_ct random points within the unit circle centered at (0,0).

  vtkPoints* points = vtkPoints::New();

  int count = 0;
  while(count < xpt_ct)
  {
    double x = vtkMath::Random(-1.0, 1.0);
    double y = vtkMath::Random(-1.0, 1.0);
    double z = 0.0;

    double r2 = x*x + y*y;
    if(r2 <= 1.0)
    {
      points->InsertPoint(count, x, y, z);
      count++;
    }
  }

  // Triangulate the points by creating a VTK mesh object.

  vtkPolyData* profile = vtkPolyData::New();
  profile->SetPoints(points);

  vtkDelaunay2D* del = vtkDelaunay2D::New();
  del->SetInput(profile);
  del->SetTolerance(0.001);

  vtkConnectivityFilter* cf = vtkConnectivityFilter::New();
  cf->SetInput(del->GetOutput());
  cf->Update();

  vtkUnstructuredGrid* ugrid = cf->GetOutput();

  // Extract the point coordinates from the VTK mesh object.

  xpt_coords.reserve(2*xpt_ct);
  xpt_coords.set_ct(0);
  double lpt_coords[3];
  for(size_type i=0; i<xpt_ct; ++i)
  {
    ugrid->GetPoint(i, lpt_coords);
    xpt_coords.push_back(lpt_coords[0]);
    xpt_coords.push_back(lpt_coords[1]);
  }

  // Extract the triangle connectivity data from the VTK mesh object.

  size_type ltri_ct = ugrid->GetNumberOfCells();
  block<int> lconn(3*ltri_ct);
  lconn.set_ct(0);

  vtkIdType npts;
  vtkIdType* pts;
  for(size_type i=0; i<ltri_ct; ++i)
  {
    ugrid->GetCellPoints(i, npts, pts);
    lconn.push_back(pts[0]);
    lconn.push_back(pts[1]);
    lconn.push_back(pts[2]);
  }

  // Make the base space using the connectivy from the triangulation.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);

  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 2, false);
  
  lhost.get_read_write_access();

  poset_path lproto_path(base_space_member::prototypes_poset_name(), "triangle_nodes");

  unstructured_block* result =
    new unstructured_block(&lhost, lproto_path, lconn.base(), lconn.ct(), true);
  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

#endif

fiber_bundle::sec_e2*
fields::field_factory::
new_2d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                const std::string& xname,
                                size_type xpt_ct,
                                block<sec_vd_value_type>& xlower,
                                block<sec_vd_value_type>& xupper,
                                unstructured_block& xbase_space,
                                const block<sec_vd_value_type>& xpt_coords)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);
  require(xpt_coords.ct() >= 2*xpt_ct);

  // Body:

  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space& lhost =
    sec_e2::standard_host(xns, xbase_space.path(true), lpath, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e2* result = new sec_e2(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs.

  sec_e2::fiber_type::volatile_type lfiber;

  sec_vd_value_type ldel0 = (xupper[0] - xlower[0])/2.0;
  sec_vd_value_type ldel1 = (xupper[1] - xlower[1])/2.0;

  for(size_type i=0; i<xpt_ct; ++i)
  {
    lfiber[0] = (xpt_coords[2*i  ] + 1.0)*ldel0 + xlower[0];
    lfiber[1] = (xpt_coords[2*i+1] + 1.0)*ldel1 + xlower[1];
    result->put_fiber(i, lfiber);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}


fiber_bundle::structured_block_2d*
fields::field_factory::
new_2d_structured_base_space(namespace_poset& xns,
                             const std::string& xname,
                             size_type xi_size,
                             size_type xj_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));
  require(!xns.contains_poset(xname, false));
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
  
  base_space_poset& lhost = structured_block_2d::standard_host(lns, xname, false);

  lhost.get_read_write_access();

  structured_block_2d* result =
    new structured_block_2d(&lhost, xi_size, xj_size, true);
  result->put_name(xname + "_structured_block_2d", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::sec_e2*
fields::field_factory::
new_2d_uniform_coordinates(fiber_bundles_namespace& xns,
                           const string& xname,
                           size_type xi_size,
                           size_type xj_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           structured_block_2d& xbase_space)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xlower.ct() >= 2);
  require(xupper.ct() >= 2);
  require_for_all(i, 0, 2, xlower[i] < xupper[i]);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xlower: ";
  for(int c=0; c<xlower.ub(); ++c)
  {
    cout << "  " << xlower[c];
  }
  cout << endl;

  cout << "xupper: ";
  for(int c=0; c<xupper.ub(); ++c)
  {
    cout << "  " << xupper[c];
  }
  cout << endl;
#endif


  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_block_uniform");

  sec_rep_space& lhost =
    sec_e2::standard_host(xns, xbase_space.path(true), lpath, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e2* result = new sec_e2(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs;

  put_2d_uniform_coord_dofs(xlower, xupper, result);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::unstructured_block*
fields::field_factory::
new_3d_unstructured_base_space(namespace_poset& xns,
                               const std::string& xname,
                               size_type xi_size,
                               size_type xj_size,
                               size_type xk_size,
                               bool xuse_hexs)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);

  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 3, false);

  lhost.get_read_write_access();

  string proto_member_name(xuse_hexs ? "hex_nodes" : "tetra_nodes");

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  unstructured_block* result =
    new unstructured_block(&lhost, lproto_path, xi_size, xj_size, xk_size);
  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

fiber_bundle::sec_e3*
fields::field_factory::
new_3d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                const std::string& xname,
                                size_type xi_size,
                                size_type xj_size,
                                size_type xk_size,
                                block<sec_vd_value_type>& xlower,
                                block<sec_vd_value_type>& xupper,
                                unstructured_block& xbase_space,
                                const poset_path& xrep_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);
  require(xns.contains_poset_member(xrep_path));

  // Body:

  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";

  sec_rep_space& lhost =
    sec_e3::standard_host(xns, xbase_space.path(true), xrep_path, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e3* result = new sec_e3(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs.

  size_type i_ub = xi_size + 1;
  size_type j_ub = xj_size + 1;
  size_type k_ub = xk_size + 1;

  sec_vd_value_type ldelta0 = (xupper[0] - xlower[0])/xi_size;
  sec_vd_value_type ldelta1 = (xupper[1] - xlower[1])/xj_size;
  sec_vd_value_type ldelta2 = (xupper[2] - xlower[2])/xk_size;

  sec_e3::fiber_type::volatile_type lfiber;

  pod_index_type lclient_id;

  for(size_type i=0; i<i_ub; ++i)
  {
    lfiber[0] = xlower[0] + i*ldelta0;
    for(size_type j=0; j<j_ub; ++j)
    {
      lfiber[1] = xlower[1] + j*ldelta1;

      for(size_type k=0; k<k_ub; ++k)
      {
        lfiber[2] = xlower[2] + k*ldelta2;

        // Connectivity called from unstructured_block assigns vertex
        // client ids using standard array index calculation.

        lclient_id = (i*j_ub + j)*k_ub + k;

	result->put_fiber(lclient_id, lfiber);
      }
    }
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

#ifdef HAVE_VTK

fiber_bundle::unstructured_block*
fields::field_factory::
new_3d_unstructured_base_space(namespace_poset& xns,
                               const std::string& xname,
                               size_type xpt_ct,
                               block<sec_vd_value_type>& xpt_coords)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);

  // Body:

  // Create xpt_ct random points within the unit circle centered at (0,0).

  vtkPoints* points = vtkPoints::New();

  int count = 0;
  while(count < xpt_ct)
  {
    double x = vtkMath::Random(-1.0, 1.0);
    double y = vtkMath::Random(-1.0, 1.0);
    double z = vtkMath::Random(-1.0, 1.0);

    double r2 = x*x + y*y + z*z;
    if(r2 <= 1.0)
    {
      points->InsertPoint(count, x, y, z);
      count++;
    }
  }

  // Triangulate the points by creating a VTK mesh object.

  vtkPolyData* profile = vtkPolyData::New();
  profile->SetPoints(points);

  vtkDelaunay3D* del = vtkDelaunay3D::New();
  del->SetInput(profile);
  del->SetTolerance(0.001);
  del->Update();

  vtkUnstructuredGrid* ugrid = del->GetOutput();

  // Extract the point coordinates from the VTK mesh object.

  xpt_coords.reserve(3*xpt_ct);
  xpt_coords.set_ct(0);
  double lpt_coords[3];
  for(size_type i=0; i<xpt_ct; ++i)
  {
    ugrid->GetPoint(i, lpt_coords);
    xpt_coords.push_back(lpt_coords[0]);
    xpt_coords.push_back(lpt_coords[1]);
    xpt_coords.push_back(lpt_coords[2]);
  }

  // Extract the tet connectivity data from the VTK mesh object.

  size_type ltet_ct = ugrid->GetNumberOfCells();
  block<int> lconn(4*ltet_ct);
  lconn.set_ct(0);

  vtkIdType npts;
  vtkIdType* pts;
  for(size_type i=0; i<ltet_ct; ++i)
  {
    ugrid->GetCellPoints(i, npts, pts);
    lconn.push_back(pts[0]);
    lconn.push_back(pts[1]);
    lconn.push_back(pts[2]);
    lconn.push_back(pts[3]);
  }

  // Make the base space using the connectivy from the triangulation.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);

  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = unstructured_block::standard_host(lns, lbase_name, 3, false);

  lhost.get_read_write_access();

  poset_path lproto_path(base_space_member::prototypes_poset_name(), "tetra_nodes");

  unstructured_block* result =
    new unstructured_block(&lhost, lproto_path, lconn.base(), lconn.ct(), true);

  result->put_name(xname + "_unstructured_block", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());


  // Exit:

  return result;
}

#endif

fiber_bundle::sec_e3*
fields::field_factory::
new_3d_unstructured_coordinates(fiber_bundles_namespace& xns,
                                const std::string& xname,
                                size_type xpt_ct,
                                block<sec_vd_value_type>& xlower,
                                block<sec_vd_value_type>& xupper,
                                unstructured_block& xbase_space,
                                const block<sec_vd_value_type>& xpt_coords)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xpt_ct > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);
  require(xpt_coords.ct() >= 3*xpt_ct);

  // Body:

  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  sec_rep_space& lhost =
    sec_e3::standard_host(xns, xbase_space.path(true), lpath, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e3* result = new sec_e3(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs.

  sec_e3::fiber_type::volatile_type lfiber;

  sec_vd_value_type ldel0 = (xupper[0] - xlower[0])/2.0;
  sec_vd_value_type ldel1 = (xupper[1] - xlower[1])/2.0;
  sec_vd_value_type ldel2 = (xupper[2] - xlower[2])/2.0;

  for(size_type i=0; i<xpt_ct; ++i)
  {
    lfiber[0] = (xpt_coords[3*i  ] + 1.0)*ldel0 + xlower[0];
    lfiber[1] = (xpt_coords[3*i+1] + 1.0)*ldel1 + xlower[1];
    lfiber[2] = (xpt_coords[3*i+2] + 1.0)*ldel2 + xlower[2];
    result->put_fiber(i, lfiber);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::structured_block_3d*
fields::field_factory::
new_3d_structured_base_space(namespace_poset& xns,
                             const std::string& xname,
                             size_type xi_size,
                             size_type xj_size,
                             size_type xk_size)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  // Make the base space.

  fiber_bundles_namespace& lns = dynamic_cast<fiber_bundles_namespace&>(xns);
  
  string lbase_name(xname+"_base_space");
  base_space_poset& lhost = structured_block_3d::standard_host(lns, lbase_name, false);
  
  lhost.get_read_write_access();

  structured_block_3d* result =
    new structured_block_3d(&lhost, xi_size, xj_size, xk_size, true);
  result->put_name(xname + "_structured_block_3d", true, false);

#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::sec_e3*
fields::field_factory::
new_3d_uniform_coordinates(fiber_bundles_namespace& xns,
                           const std::string& xname,
                           size_type xi_size,
                           size_type xj_size,
                           size_type xk_size,
                           block<sec_vd_value_type>& xlower,
                           block<sec_vd_value_type>& xupper,
                           structured_block_3d& xbase_space)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(!xname.empty());
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);
  require(xlower.ct() >= 3);
  require(xupper.ct() >= 3);
  require_for_all(i, 0, 3, xlower[i] < xupper[i]);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "xlower: ";
  for(int c=0; c<xlower.ub(); ++c)
  {
    cout << "  " << xlower[c];
  }
  cout << endl;

  cout << "xupper: ";
  for(int c=0; c<xupper.ub(); ++c)
  {
    cout << "  " << xupper[c];
  }
  cout << endl;
#endif


  // Make coordinate sec_rep_space.

  string lname = xname + "_coordinates_section_space";
  poset_path lpath("sec_rep_descriptors", "vertex_block_uniform");

  sec_rep_space& lhost =
    sec_e3::standard_host(xns, xbase_space.path(true), lpath, "", "", false);

  lhost.get_read_write_access();

  // Make the coordinates section.

  sec_e3* result = new sec_e3(&lhost);
  result->put_name(xname + "_coordinate_field", true, false);

  // Set the coordinates dofs;

  put_3d_uniform_coord_dofs(xlower, xupper, result);


#ifdef DIAGNOSTIC_OUTPUT
  cout << lhost << endl;
#endif

  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

fiber_bundle::sec_at0*
fields::field_factory::
new_property(fiber_bundles_namespace& xns,
             const std::string& xname,
             base_space_member& xbase_space,
             const poset_path& xrep_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(xrep_path));
  require(!xname.empty());

  // Body:

  // Create the property sec_rep_space.

  string lname = xname + "_property_section_space";

  sec_rep_space& lhost =
    sec_at0::standard_host(xns, xbase_space.path(true), xrep_path, "", "", false);

  lhost.get_read_write_access();

  // Create the property section;
  // dofs will be set in main.

  sec_at0* result = new sec_at0(&lhost);
  result->put_name(xname+"_scalar_property", true, false);


  // Clean up.

  lhost.release_access();

  // Postconditions:

  ensure(result != 0);
  ensure(result->state_is_not_read_accessible());

  // Exit:

  return result;
}

void
fields::field_factory::
step_fcn(block<sec_vd_value_type>& xglobal_coords,
         block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  require(xglobal_coords.ct() >= 1);
  require(xproperty_dofs.ct() == 1);

  // Body:

  // Not exactly a step, really a ramp.
  // Test case centers coarse mesh zone on
  // origin of coordinates, so make sure
  // test function not symmetric (or antisymmetric).
  // Otherwise, the error at the center may
  // be unexpectedly small.

  sec_vd_value_type x = xglobal_coords[0];

  if(x < -0.5)
  {
    xproperty_dofs[0] = -1.0;
  }
  else if(x > 0.0)
  {
    xproperty_dofs[0] = 1.0;
  }
  else
  {
    xproperty_dofs[0] = 4.0*x + 1.0;
  }


  // Postconditions:

  // Exit:

  return;
}

void
fields::field_factory::
linear_scalar_fcn(block<sec_vd_value_type>& xglobal_coords,
                  block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  require(xglobal_coords.ct() > 0);
  require(xproperty_dofs.ct() == 1);

  // Body:

  sec_vd_dof_type lprop_dof = 20.0;

  int ldc = xglobal_coords.ct();
  for(int i=0; i<ldc; ++i)
  {
    lprop_dof += (i+1)*xglobal_coords[i];
  }

  xproperty_dofs[0] = lprop_dof;


  // Postconditions:

  // Exit:

  return;
}

void
fields::field_factory::
zero(block<sec_vd_value_type>& xglobal_coords, block<sec_vd_dof_type>& xproperty_dofs)
{
  // Preconditions:

  // Body:

  xproperty_dofs.assign(0.0);

  // Postconditions:

  ensure_for_all(i, 0, xproperty_dofs.ct(), xproperty_dofs[i] == 0.0);

  // Exit:

  return;
}


fiber_bundle::base_space_member*
fields::field_factory::
new_structured_base_space(namespace_poset& xns,
                          const std::string& xbase_space_name,
                          const block<int>& xindex_ubs)
{
  base_space_member* result;

  // Preconditions:


  // Body:

  switch(xindex_ubs.ct())
  {
  case 1:
    result = field_factory::new_1d_structured_base_space(xns,
             xbase_space_name,
             xindex_ubs[0]);
    break;
  case 2:
    result = field_factory::new_2d_structured_base_space(xns,
             xbase_space_name,
             xindex_ubs[0],
             xindex_ubs[1]);
    break;
  case 3:
    result = field_factory::new_3d_structured_base_space(xns,
             xbase_space_name,
             xindex_ubs[0],
             xindex_ubs[1],
             xindex_ubs[2]);
    break;
  }

  // Postconditions:


  // Exit:

  return result;
}


fiber_bundle::sec_ed*
fields::field_factory::
new_coord_section_handle(int xdc)
{
  sec_ed* result;

  // Preconditions:

  require( (1 <= xdc) && (xdc <= 3) );

  // Body:

  switch(xdc)
  {
  case 1:
    result = new sec_e1();
    break;
  case 2:
    result = new sec_e2();
    break;
  case 3:
    result = new sec_e3();
    break;
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}


void
fields::field_factory::
put_1d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                          const block<sec_vd_dof_type>& xupper,
                          sec_ed* xcoords)
{
  // Preconditions:


  // Body:

  sec_e1::fiber_type::volatile_type lfiber;

  // Structured_block_1d ctor sets client ids to match the order
  // for a normal seqment.

  // xmin; client id 0.

  lfiber[0] = xlower[0];
  xcoords->put_fiber(0, lfiber);

  // xmax; client id 1:

  lfiber[0] = xupper[0];
  xcoords->put_fiber(1, lfiber);

  // Postconditions:


  // Exit:

  return;
}


void
fields::field_factory::
put_2d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                          const block<sec_vd_dof_type>& xupper,
                          sec_ed* xcoords)
{
  // Preconditions:


  // Body:

  // Set the coordinates dofs;
  // uniform coordinates have only 8 dofs in 2d,
  // the x,y coordinates at the corners of the domain.
  // (Even these aren't all independent).

  sec_e2::fiber_type::volatile_type lfiber;

  // Structured_block_2d ctor sets client ids to match the order
  // for a normal quad.

  // xmin, ymin; client id 0.

  lfiber[0] = xlower[0];
  lfiber[1] = xlower[1];
  xcoords->put_fiber(0, lfiber);

  // xmax, ymin; client id 1:

  lfiber[0] = xupper[0];
  lfiber[1] = xlower[1];
  xcoords->put_fiber(1, lfiber);

  // xmax, ymax; client id 2.

  lfiber[0] = xupper[0];
  lfiber[1] = xupper[1];
  xcoords->put_fiber(2, lfiber);

  // xmin, ymax; client id 3.

  lfiber[0] = xlower[0];
  lfiber[1] = xupper[1];
  xcoords->put_fiber(3, lfiber);

  // Postconditions:


  // Exit:

  return;
}


void
fields::field_factory::
put_3d_uniform_coord_dofs(const block<sec_vd_dof_type>& xlower,
                          const block<sec_vd_dof_type>& xupper,
                          sec_ed* xcoords)
{
  // Preconditions:


  // Body:

  // Set the coordinates dofs;
  // uniform coordinates have only 8 dofs in 2d,
  // the x,y coordinates at the corners of the domain.
  // (Even these aren't all independent).

  sec_e3::fiber_type::volatile_type lfiber;

  // Structured _block_3d ctor sets client ids to match the order
  // for a normal hex.

  // xmin, ymin, zmin; client id 0.

  lfiber[0] = xlower[0];
  lfiber[1] = xlower[1];
  lfiber[2] = xlower[2];
  xcoords->put_fiber(0, lfiber);

  // xmax, ymin, zmin; client id 1:

  lfiber[0] = xupper[0];
  lfiber[1] = xlower[1];
  lfiber[2] = xlower[2];
  xcoords->put_fiber(1, lfiber);

  // xmax, ymax, zmin; client id 2.

  lfiber[0] = xupper[0];
  lfiber[1] = xupper[1];
  lfiber[2] = xlower[2];
  xcoords->put_fiber(2, lfiber);

  // xmin, ymax, zmin; client id 3.

  lfiber[0] = xlower[0];
  lfiber[1] = xupper[1];
  lfiber[2] = xlower[2];
  xcoords->put_fiber(3, lfiber);

  // xmin, ymin, zmax; client id 4.

  lfiber[0] = xlower[0];
  lfiber[1] = xlower[1];
  lfiber[2] = xupper[2];
  xcoords->put_fiber(4, lfiber);

  // xmax, ymin, zmax; client id 5:

  lfiber[0] = xupper[0];
  lfiber[1] = xlower[1];
  lfiber[2] = xupper[2];
  xcoords->put_fiber(5, lfiber);

  // xmax, ymax, zmax; client id 6.

  lfiber[0] = xupper[0];
  lfiber[1] = xupper[1];
  lfiber[2] = xupper[2];
  xcoords->put_fiber(6, lfiber);

  // xmin, ymax, zmax; client id 7.

  lfiber[0] = xlower[0];
  lfiber[1] = xupper[1];
  lfiber[2] = xupper[2];
  xcoords->put_fiber(7, lfiber);

  // Postconditions:


  // Exit:

  return;
}

void
fields::field_factory::
put_uniform_coord_dofs(int xdc,
                       const block<sec_vd_dof_type>& xlower,
                       const block<sec_vd_dof_type>& xupper,
                       sec_ed* xcoords)
{
  // Preconditions:


  // Body:

  xcoords->get_read_write_access();

  switch(xdc)
  {
  case 1:
    put_1d_uniform_coord_dofs(xlower, xupper, xcoords);
    break;
  case 2:
    put_2d_uniform_coord_dofs(xlower, xupper, xcoords);
    break;
  case 3:
    put_3d_uniform_coord_dofs(xlower, xupper, xcoords);
    break;
  }

  xcoords->release_access();

  // Postconditions:


  // Exit:

  return;
}


fields::property_dof_function_type
fields::field_factory::
property_dof_function(const std::string& xname)
{
  property_dof_function_type result;

  // Preconditions:

  require((xname == "linear_scalar_fcn") || (xname == "zero") || (xname == "property_dof_function_example") || (xname == "step_fcn"));

  // Body:

  if(xname == "linear_scalar_fcn")
  {
    result = linear_scalar_fcn;
  }
  else if (xname == "step_fcn")
  {
    result = step_fcn;
  }
  else if (xname == "zero")
  {
    result = zero;
  }
  else if(xname == "property_dof_function_example")
  {
    result = field_vd::property_dof_function_example;
  }

  else
  {
    post_fatal_error_message("Unsuppported property dof function name.");
  }

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

