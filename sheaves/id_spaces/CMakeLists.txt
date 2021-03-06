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
    abstract_product_structure.cc
    array_implicit_index_space_iterator.cc
    array_index_space_handle.cc
    array_index_space_interval.cc
    array_index_space_iterator.cc
    array_index_space_state.cc
    constant_implicit_index_space_iterator.cc
    constant_index_space_interval.cc
    explicit_index_space_collection.cc
    explicit_index_space_handle.cc
    explicit_index_space_interval.cc
    explicit_index_space_iterator.cc
    explicit_index_space_state.cc
    forwarding_index_space_handle.cc
    gathered_insertion_index_space_handle.cc
    gathered_insertion_index_space_state.cc
    hash_index_space_handle.cc
    hash_index_space_iterator.cc
    hash_index_space_state.cc
    hub_index_space_handle.cc
    hub_index_space_iterator.cc
    ij_product_structure.cc
    ijk_product_structure.cc
    implicit_index_space_iterator.cc
    index_space_collection.cc
    index_equivalence_class.cc
    index_equivalence_iterator.cc
    index_space_family.cc
    index_space_family_iterator.cc
    index_space_handle.cc
    index_space_interval.cc
    index_space_interval_iterator.cc
    index_space_iterator.cc
    interval_index_space_handle.cc
    interval_index_space_iterator.cc
    interval_index_space_state.cc
    list_index_space_handle.cc
    list_index_space_iterator.cc
    list_index_space_state.cc
    offset_index_space_handle.cc
    offset_index_space_iterator.cc
    offset_index_space_state.cc
    primary_index_space_handle.cc
    primary_index_space_iterator.cc
    primary_index_space_state.cc
    primary_sum_index_space_state.cc
    primitives_index_space_handle.cc
    primitives_index_space_iterator.cc
    primitives_index_space_state.cc
    ragged_array_implicit_index_space_iterator.cc
    ragged_array_index_space_interval.cc
    reserved_primary_index_space_handle.cc
    reserved_primary_index_space_iterator.cc
    reserved_primary_index_space_state.cc
    scattered_insertion_index_space_handle.cc
    scattered_insertion_index_space_state.cc
    singleton_implicit_index_space_iterator.cc
    singleton_index_space_handle.cc
    singleton_index_space_interval.cc
    singleton_index_space_iterator.cc
    singleton_index_space_state.cc
    sum_index_space_handle.cc
    sum_index_space_state.cc
   )


SheafSystem_collect_sources(sheaves "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    index_space_family.impl.h
    index_space_handle.impl.h
   )
  
SheafSystem_collect_includes(sheaves "${SRCS}" "${ADDITIONAL_INCS}")

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

SheafSystem_collect_unit_test_sources(sheaves "${UNIT_TEST_SRCS}")

#
# Source for example executables.
#
set(EXAMPLE_SRCS
   )

SheafSystem_collect_example_sources(sheaves "${EXAMPLE_SRCS}")
