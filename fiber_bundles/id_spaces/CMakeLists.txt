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
    i_adjacency_implicit_index_space_iterator.cc
    i_adjacency_index_space_interval.cc
    i_connectivity_implicit_index_space_iterator.cc
    i_connectivity_index_space_interval.cc
    ij_adjacency_implicit_index_space_iterator.cc
    ij_adjacency_index_space_interval.cc
    ij_connectivity_implicit_index_space_iterator.cc
    ij_connectivity_index_space_interval.cc
    ijk_adjacency_implicit_index_space_iterator.cc
    ijk_adjacency_index_space_interval.cc
    ijk_connectivity_implicit_index_space_iterator.cc
    ijk_connectivity_index_space_interval.cc
    section_space_schema_jims_index_space_handle.cc
    section_space_schema_jims_index_space_iterator.cc
    section_space_schema_jims_index_space_state.cc
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

