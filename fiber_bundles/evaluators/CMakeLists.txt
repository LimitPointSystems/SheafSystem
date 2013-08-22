#
# Copyright (c) 2013 Limit Point Systems, Inc. 
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
    dlinear_eval_family.cc
    differentiable_section_evaluator.cc
    constant_eval_family.cc
    constant_fcn_space.cc
    constant_hex.cc
    constant_point.cc
    constant_quad.cc
    constant_segment.cc
    constant_tet.cc
    constant_triangle.cc
    eval_family.cc
    integrable_section_evaluator.cc
    uniform_eval_family.cc
    section_evaluator.cc
    linear_fcn_space.cc
    bilinear_2d.cc
    linear_1d.cc
    linear_2d.cc
    linear_3d.cc
    quadratic_1d.cc
    quadratic_2d.cc
    quadratic_3d.cc
    trilinear_3d.cc
    uniform_1d.cc
    uniform_2d.cc
    uniform_3d.cc
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
# Source for non-test executables.
#
set(EXAMPLE_SRCS
   )

collect_example_sources()

