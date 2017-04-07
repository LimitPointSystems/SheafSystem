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
    array_cylindrical_point_locator.cc
    cylindrical_point_locator.cc
    db0_point_locator.cc
    d_array_point_locator.cc
    d_bin_point_locator.cc
    d_bin_coordinates.cc
    d_bounding_box.cc
    d_tree_point_locator.cc
    d_tree_point_locator_node.cc
    d_tree_point_locator_path.cc
    d_uniform_point_locator.cc
    line_surface_intersecter.cc
    point_locator.cc 
   )

SheafSystem_collect_sources(geometry "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    db0_point_locator.impl.h 
    d_array_point_locator.impl.h 
    d_bin_coordinates.impl.h 
    d_bin_point_locator.impl.h 
    d_bounding_box.impl.h 
    d_tree_point_locator.impl.h 
    d_tree_point_locator_node.impl.h 
    d_tree_point_locator_path.impl.h 
    d_uniform_point_locator.impl.h
   )

SheafSystem_collect_includes(geometry "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

SheafSystem_collect_unit_test_sources(geometry "${UNIT_TEST_SRCS}")

#
# Source for example executables.
#
set(EXAMPLE_SRCS
   )

SheafSystem_collect_example_sources(geometry "${EXAMPLE_SRCS}")
