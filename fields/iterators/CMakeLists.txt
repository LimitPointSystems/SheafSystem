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
    field_eval_iterator.cc
    property_disc_iterator.cc
    property_disc_iterator_1_1.cc
    property_disc_iterator_1_2.cc
    property_disc_iterator_1_3.cc
    property_disc_iterator_4_2.cc
    property_disc_iterator_4_3.cc
   )

SheafSystem_collect_sources(fields "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
   )

SheafSystem_collect_includes(fields "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

SheafSystem_collect_unit_test_sources(fields "${UNIT_TEST_SRCS}")

#
# Source for example executables.
#
set(EXAMPLE_SRCS
   )

SheafSystem_collect_example_sources(fields "${EXAMPLE_SRCS}")