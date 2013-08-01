//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Common SWIG interface to fields cluster
//

//=============================================================================

//$$SCRIBBLE: This file contains only the part of the Swig interface which
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

%include "fields.h"

%include "field_refinement_buffer.h"
%include "field_refinement_policy.h"
%include       "depth_bound_refinement_policy.h"
%include       "variance_bound_refinement_policy.h"
%include       "zone_centered_error_bound_refinement_policy.h"
%include "field_refiner.h"
%include "field_refiner_family.h"
%include       "barycentric_refiner_family.h"
%include       "edge_centered_refiner_family.h"
%include       "zone_centered_refiner_family.h"
%include "local_field_refiner.h"
%include       "edge_centered_polygon_refiner.h"
%include             "barycentric_quad_refiner.h"
%include             "barycentric_triangle_refiner.h"
%include             "edge_centered_triangle_refiner.h"
%include       "zone_centered_segment_refiner.h"
%include       "zone_centered_tet_refiner.h"
%include       "zone_centered_triangle_refiner.h"
%include "refining_section_pusher.h"


// The following 5 classes are commented out because they currently unused and there is no working test driver.
//%include "base_space_map.h"
//%include "base_space_map_push_action.h"
//%include       "average_base_space_map_push_action.h"
//%include       "constant_base_space_map_push_action.h"
//%include       "copy_base_space_map_push_action.h"

%include "body_builder.h"
%include "body_factory.h"
%include "body_pusher.h"
 //%include "d_bin_coordinates.h"
 //%include "d_bounding_box.h"
 //%include "d_tree_point_locator_node.h"
%include "discretization_push_action.h"
%include       "body_pusher_pullback_action.h"
%include       "print_property_dofs_action.h"
%include       "put_property_dofs_action.h"
%include             "put_property_dofs_fcn_action.h"
%include       "section_pusher_pullback_action.h"
%include "discretization_pusher.h"
%include "field_eval_iterator.h"
%include "field_factory.h"
%include "field_factory_2.h"

 //%include "point_locator.h"
 //%include       "cylindrical_point_locator.h"
 //%include             "array_cylindrical_point_locator.h"
 //%include       "d_bin_point_locator.h"
 //%include             "d_array_point_locator.h"
 //%include             "d_tree_point_locator.h"
 //%include       "d_uniform_point_locator.h"
 //%include       "db0_point_locator.h"

%include "property_disc_iterator.h"
%include       "property_disc_iterator_1_1.h"
%include       "property_disc_iterator_1_2.h"
%include       "property_disc_iterator_1_3.h"
%include       "property_disc_iterator_4_2.h"
%include       "property_disc_iterator_4_3.h"
%include "pullback_map.h"

%include "section_pusher.h"
%include       "avg_section_pusher.h"
%include "section_pusher_push_action.h"
%include       "average_push_action.h"
%include       "constant_push_action.h"
%include       "copy_push_action.h"

//%include "vd_field.h"

%include "field_vd.h"
%include       "field_jcb.h"
%include             "field_jcb_ed.h"
%include                   "field_jcb_e13.h"
%include                   "field_jcb_e23.h"
%include                   "field_jcb_e33.h"
%include       "field_tp.h"
%include             "field_atp.h"
%include                   "field_at0.h"
%include                   "field_at1.h"
%include                         "field_ed.h"
%include                               "field_e1.h"
%include                                     "field_e1_uniform.h"
%include                               "field_e2.h"
%include                                     "field_e2_uniform.h"
%include                               "field_e3.h"
%include                                     "field_e3_uniform.h"
%include                   "field_at2.h"
%include                         "field_at2_e2.h"
%include                         "field_at2_e3.h"
%include                   "field_at3.h"
%include                         "field_at3_e3.h"
%include             "field_stp.h"
%include                   "field_st2.h"
%include                         "field_met.h"
%include                               "field_met_ed.h"
%include                                     "field_met_e1.h"
%include                                     "field_met_e2.h"
%include                                     "field_met_e3.h"
%include                         "field_st2_e2.h"
%include                         "field_st2_e3.h"
%include                   "field_st3.h"
%include                         "field_st3_e3.h"
%include                   "field_st4.h"
%include                         "field_st4_e2.h"
%include                         "field_st4_e3.h"
%include             "field_t2.h"
%include                   "field_t2_e2.h"
%include                   "field_t2_e3.h"
%include             "field_t3.h"
%include                   "field_t3_e3.h"
%include             "field_t4.h"
%include                   "field_t4_e2.h"
%include                   "field_t4_e3.h"

//=============================================================================

