
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

//           This file contains only the part of the Swig interface which
//            is to be inserted directly into the generated code.
//            We have to break the interface into two parts because
//            of the way Swig handles "%import" versus "%include".
//            If you change this file make sure you also change
//            "fields_common_binding.i" as well.

//=============================================================================

%{

#include "ComLimitPoint/fields/fields.h"

#include "ComLimitPoint/fields/field_refinement_buffer.h"
#include "ComLimitPoint/fields/field_refinement_policy.h"
#include       "ComLimitPoint/fields/depth_bound_refinement_policy.h"
#include       "ComLimitPoint/fields/variance_bound_refinement_policy.h"
#include       "ComLimitPoint/fields/zone_centered_error_bound_refinement_policy.h"
#include "ComLimitPoint/fields/field_refiner.h"
#include "ComLimitPoint/fields/field_refiner_family.h"
#include       "ComLimitPoint/fields/barycentric_refiner_family.h"
#include       "ComLimitPoint/fields/edge_centered_refiner_family.h"
#include       "ComLimitPoint/fields/zone_centered_refiner_family.h"
#include "ComLimitPoint/fields/local_field_refiner.h"
#include       "ComLimitPoint/fields/edge_centered_polygon_refiner.h"
#include             "ComLimitPoint/fields/barycentric_quad_refiner.h"
#include             "ComLimitPoint/fields/barycentric_triangle_refiner.h"
#include             "ComLimitPoint/fields/edge_centered_triangle_refiner.h"
#include       "ComLimitPoint/fields/zone_centered_segment_refiner.h"
#include       "ComLimitPoint/fields/zone_centered_tet_refiner.h"
#include       "ComLimitPoint/fields/zone_centered_triangle_refiner.h"
#include "ComLimitPoint/fields/refining_section_pusher.h"

// The following 5 classes are commented out because they currently unused and there is no working test driver.
//#include "ComLimitPoint/fields/base_space_map.h"
//#include "ComLimitPoint/fields/base_space_map_push_action.h"
//#include       "ComLimitPoint/fields/average_base_space_map_push_action.h"
//#include       "ComLimitPoint/fields/constant_base_space_map_push_action.h"
//#include       "ComLimitPoint/fields/copy_base_space_map_push_action.h"
#include "ComLimitPoint/fields/body_builder.h"
#include "ComLimitPoint/fields/body_factory.h"
#include "ComLimitPoint/fields/body_pusher.h"

#include "ComLimitPoint/fields/discretization_push_action.h"
#include       "ComLimitPoint/fields/body_pusher_pullback_action.h"
#include       "ComLimitPoint/fields/print_property_dofs_action.h"
#include       "ComLimitPoint/fields/put_property_dofs_action.h"
#include             "ComLimitPoint/fields/put_property_dofs_fcn_action.h"
#include       "ComLimitPoint/fields/section_pusher_pullback_action.h"
#include "ComLimitPoint/fields/discretization_pusher.h"
#include "ComLimitPoint/fields/field_eval_iterator.h"
#include "ComLimitPoint/fields/field_factory.h"
#include "ComLimitPoint/fields/field_factory_2.h"

#include "ComLimitPoint/fields/property_disc_iterator.h"
#include       "ComLimitPoint/fields/property_disc_iterator_1_1.h"
#include       "ComLimitPoint/fields/property_disc_iterator_1_2.h"
#include       "ComLimitPoint/fields/property_disc_iterator_1_3.h"
#include       "ComLimitPoint/fields/property_disc_iterator_4_2.h"
#include       "ComLimitPoint/fields/property_disc_iterator_4_3.h"
#include "ComLimitPoint/fields/pullback_map.h"
#include "ComLimitPoint/fields/section_pusher.h"
#include       "ComLimitPoint/fields/avg_section_pusher.h"
#include "ComLimitPoint/fields/section_pusher_push_action.h"
#include       "ComLimitPoint/fields/average_push_action.h"
#include       "ComLimitPoint/fields/constant_push_action.h"
#include       "ComLimitPoint/fields/copy_push_action.h"

#include "ComLimitPoint/fields/field_vd.h"
#include       "ComLimitPoint/fields/field_jcb.h"
#include             "ComLimitPoint/fields/field_jcb_ed.h"
#include                   "ComLimitPoint/fields/field_jcb_e13.h"
#include                   "ComLimitPoint/fields/field_jcb_e23.h"
#include                   "ComLimitPoint/fields/field_jcb_e33.h"
#include       "ComLimitPoint/fields/field_tp.h"
#include             "ComLimitPoint/fields/field_atp.h"
#include                   "ComLimitPoint/fields/field_at0.h"
#include                   "ComLimitPoint/fields/field_at1.h"
#include                         "ComLimitPoint/fields/field_ed.h"
#include                               "ComLimitPoint/fields/field_e1.h"
#include                                     "ComLimitPoint/fields/field_e1_uniform.h"
#include                               "ComLimitPoint/fields/field_e2.h"
#include                                     "ComLimitPoint/fields/field_e2_uniform.h"
#include                               "ComLimitPoint/fields/field_e3.h"
#include                                     "ComLimitPoint/fields/field_e3_uniform.h"
#include                   "ComLimitPoint/fields/field_at2.h"
#include                         "ComLimitPoint/fields/field_at2_e2.h"
#include                         "ComLimitPoint/fields/field_at2_e3.h"
#include                   "ComLimitPoint/fields/field_at3.h"
#include                         "ComLimitPoint/fields/field_at3_e3.h"
#include             "ComLimitPoint/fields/field_stp.h"
#include                   "ComLimitPoint/fields/field_st2.h"
#include                         "ComLimitPoint/fields/field_met.h"
#include                               "ComLimitPoint/fields/field_met_ed.h"
#include                                     "ComLimitPoint/fields/field_met_e1.h"
#include                                     "ComLimitPoint/fields/field_met_e2.h"
#include                                     "ComLimitPoint/fields/field_met_e3.h"
#include                         "ComLimitPoint/fields/field_st2_e2.h"
#include                         "ComLimitPoint/fields/field_st2_e3.h"
#include                   "ComLimitPoint/fields/field_st3.h"
#include                         "ComLimitPoint/fields/field_st3_e3.h"
#include                   "ComLimitPoint/fields/field_st4.h"
#include                         "ComLimitPoint/fields/field_st4_e2.h"
#include                         "ComLimitPoint/fields/field_st4_e3.h"
#include             "ComLimitPoint/fields/field_t2.h"
#include                   "ComLimitPoint/fields/field_t2_e2.h"
#include                   "ComLimitPoint/fields/field_t2_e3.h"
#include             "ComLimitPoint/fields/field_t3.h"
#include                   "ComLimitPoint/fields/field_t3_e3.h"
#include             "ComLimitPoint/fields/field_t4.h"
#include                   "ComLimitPoint/fields/field_t4_e2.h"
#include                   "ComLimitPoint/fields/field_t4_e3.h"

using namespace std;
using namespace fields;
using namespace geometry;
%}
