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
    binary_section_component_iterator.cc
    discretization_context.cc
    discretization_iterator.cc
    eval_iterator.cc
    section_component_iterator.cc
    section_eval_iterator.cc
    section_iteration_state.cc
   )

SheafSystem_collect_sources(fiber_bundles "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
   )

SheafSystem_collect_includes(fiber_bundles "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

SheafSystem_collect_unit_test_sources(fiber_bundles "${UNIT_TEST_SRCS}")

#
# Source for non-test executables.
#
set(EXAMPLE_SRCS
   )

SheafSystem_collect_example_sources(fiber_bundles "${EXAMPLE_SRCS}")
