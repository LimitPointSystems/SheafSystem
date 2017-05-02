
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
// Common SWIG interface to fields cluster
//

//=============================================================================

//	          This file contains only the part of the Swig interface which
//            is to be lists the classes, etc. to be wrapped.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "fields_common_binding_includes.i" as well.

//=============================================================================
// Include the list of files to be inserted into the generated code.

%include "fields_common_binding_includes.i"

//=============================================================================

//$$ISSUE: Ignoring this obsolete method.

//%ignore fields::vd_field::put_property_dofs(put_property_dofs_action&, bool);

//=============================================================================

//$$ISSUE: Ingoring the shift operators because it causes errors when
//         building the python bindings.  These errors appeared when
//         the namespaces were introduced.

%ignore *::operator<<;
%ignore *::operator>>;

//=============================================================================

// The list of classes, etc for which wrappers will be generated.

//$$SCRIBBLE: Note that order is important in the following list.  It must
//            follow the class hierarchies.

//=============================================================================

%include "SheafSystem/fields.h"

%include "SheafSystem/field_refinement_buffer.h"
%include "SheafSystem/field_refinement_policy.h"
%include       "SheafSystem/depth_bound_refinement_policy.h"
%include       "SheafSystem/variance_bound_refinement_policy.h"
%include       "SheafSystem/zone_centered_error_bound_refinement_policy.h"
%include "SheafSystem/field_refiner.h"
%include "SheafSystem/field_refiner_family.h"
%include       "SheafSystem/barycentric_refiner_family.h"
%include       "SheafSystem/edge_centered_refiner_family.h"
%include       "SheafSystem/zone_centered_refiner_family.h"
%include "SheafSystem/local_field_refiner.h"
%include       "SheafSystem/edge_centered_polygon_refiner.h"
%include             "SheafSystem/barycentric_quad_refiner.h"
%include             "SheafSystem/barycentric_triangle_refiner.h"
%include             "SheafSystem/edge_centered_triangle_refiner.h"
%include       "SheafSystem/zone_centered_segment_refiner.h"
%include       "SheafSystem/zone_centered_tet_refiner.h"
%include       "SheafSystem/zone_centered_triangle_refiner.h"
%include "SheafSystem/refining_section_pusher.h"


// The following 5 classes are commented out because they currently unused and there is no working test driver.
//%include "SheafSystem/base_space_map.h"
//%include "SheafSystem/base_space_map_push_action.h"
//%include       "SheafSystem/average_base_space_map_push_action.h"
//%include       "SheafSystem/constant_base_space_map_push_action.h"
//%include       "SheafSystem/copy_base_space_map_push_action.h"

%include "SheafSystem/body_builder.h"
%include "SheafSystem/body_factory.h"
%include "SheafSystem/body_pusher.h"
 //%include "SheafSystem/d_bin_coordinates.h"
 //%include "SheafSystem/d_bounding_box.h"
 //%include "SheafSystem/d_tree_point_locator_node.h"
%include "SheafSystem/discretization_push_action.h"
%include       "SheafSystem/body_pusher_pullback_action.h"
%include       "SheafSystem/print_property_dofs_action.h"
%include       "SheafSystem/put_property_dofs_action.h"
%include             "SheafSystem/put_property_dofs_fcn_action.h"
%include       "SheafSystem/section_pusher_pullback_action.h"
%include "SheafSystem/discretization_pusher.h"
%include "SheafSystem/field_eval_iterator.h"
%include "SheafSystem/field_factory.h"
%include "SheafSystem/field_factory_2.h"

 //%include "SheafSystem/point_locator.h"
 //%include       "SheafSystem/cylindrical_point_locator.h"
 //%include             "SheafSystem/array_cylindrical_point_locator.h"
 //%include       "SheafSystem/d_bin_point_locator.h"
 //%include             "SheafSystem/d_array_point_locator.h"
 //%include             "SheafSystem/d_tree_point_locator.h"
 //%include       "SheafSystem/d_uniform_point_locator.h"
 //%include       "SheafSystem/db0_point_locator.h"

%include "SheafSystem/property_disc_iterator.h"
%include       "SheafSystem/property_disc_iterator_1_1.h"
%include       "SheafSystem/property_disc_iterator_1_2.h"
%include       "SheafSystem/property_disc_iterator_1_3.h"
%include       "SheafSystem/property_disc_iterator_4_2.h"
%include       "SheafSystem/property_disc_iterator_4_3.h"
%include "SheafSystem/pullback_map.h"

%include "SheafSystem/section_pusher.h"
%include       "SheafSystem/avg_section_pusher.h"
%include "SheafSystem/section_pusher_push_action.h"
%include       "SheafSystem/average_push_action.h"
%include       "SheafSystem/constant_push_action.h"
%include       "SheafSystem/copy_push_action.h"

//%include "SheafSystem/vd_field.h"

%include "SheafSystem/field_vd.h"
%include       "SheafSystem/field_jcb.h"
%include             "SheafSystem/field_jcb_ed.h"
%include                   "SheafSystem/field_jcb_e13.h"
%include                   "SheafSystem/field_jcb_e23.h"
%include                   "SheafSystem/field_jcb_e33.h"
%include       "SheafSystem/field_tp.h"
%include             "SheafSystem/field_atp.h"
%include                   "SheafSystem/field_at0.h"
%include                   "SheafSystem/field_at1.h"
%include                         "SheafSystem/field_ed.h"
%include                               "SheafSystem/field_e1.h"
%include                                     "SheafSystem/field_e1_uniform.h"
%include                               "SheafSystem/field_e2.h"
%include                                     "SheafSystem/field_e2_uniform.h"
%include                               "SheafSystem/field_e3.h"
%include                                     "SheafSystem/field_e3_uniform.h"
%include                   "SheafSystem/field_at2.h"
%include                         "SheafSystem/field_at2_e2.h"
%include                         "SheafSystem/field_at2_e3.h"
%include                   "SheafSystem/field_at3.h"
%include                         "SheafSystem/field_at3_e3.h"
%include             "SheafSystem/field_stp.h"
%include                   "SheafSystem/field_st2.h"
%include                         "SheafSystem/field_met.h"
%include                               "SheafSystem/field_met_ed.h"
%include                                     "SheafSystem/field_met_e1.h"
%include                                     "SheafSystem/field_met_e2.h"
%include                                     "SheafSystem/field_met_e3.h"
%include                         "SheafSystem/field_st2_e2.h"
%include                         "SheafSystem/field_st2_e3.h"
%include                   "SheafSystem/field_st3.h"
%include                         "SheafSystem/field_st3_e3.h"
%include                   "SheafSystem/field_st4.h"
%include                         "SheafSystem/field_st4_e2.h"
%include                         "SheafSystem/field_st4_e3.h"
%include             "SheafSystem/field_t2.h"
%include                   "SheafSystem/field_t2_e2.h"
%include                   "SheafSystem/field_t2_e3.h"
%include             "SheafSystem/field_t3.h"
%include                   "SheafSystem/field_t3_e3.h"
%include             "SheafSystem/field_t4.h"
%include                   "SheafSystem/field_t4_e2.h"
%include                   "SheafSystem/field_t4_e3.h"

//=============================================================================

