#
# Copyright (c) 2014 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER ${CMAKE_CURRENT_BINARY_DIR})

#
# Library sources.
#
set(SRCS
    barycentric_refiner_family.cc
    barycentric_quad_refiner.cc
    barycentric_triangle_refiner.cc
    depth_bound_refinement_policy.cc
    edge_centered_polygon_refiner.cc
    edge_centered_refiner_family.cc
    edge_centered_triangle_refiner.cc
    field_refinement_buffer.cc
    field_refinement_policy.cc
    field_refiner.cc
    field_refiner_family.cc
    local_field_refiner.cc
    refining_section_pusher.cc
    variance_bound_refinement_policy.cc
    zone_centered_error_bound_refinement_policy.cc
    zone_centered_refiner_family.cc
    zone_centered_segment_refiner.cc
    zone_centered_tet_refiner.cc
    zone_centered_triangle_refiner.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
   )

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS
   )

collect_example_sources()
