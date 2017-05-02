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
    abstract_poset_member.cc
    crg_interval.cc
    explicit_crg_interval.cc
    implicit_crg_interval.cc
    namespace_member_index.cc
    namespace_poset.cc
    namespace_poset_member.cc
    namespace_poset_schema.cc
    namespace_relative_member_index.cc
    namespace_relative_subposet_index.cc
    namespace_schema_member_index.cc
    partial_poset_member.cc
    poset.cc
    poset_component.cc
    poset_crg_state.cc
    poset_handle_factory.cc
    poset_joiner.cc
    poset_member.cc
    poset_path.cc
    poset_powerset_state.cc
    poset_state.cc
    poset_state_handle.cc
    poset_table_state.cc
    poset_type.cc
    primitives_poset.cc
    primitives_poset_schema.cc
    primitives_schema_member_index.cc
    refinable_poset.cc
    schema_descriptor.cc
    schema_poset_member.cc
    standard_dof_tuple_index.cc
    standard_member_hack_crg_interval.cc
    standard_member_index.cc
    standard_subposet_index.cc
    standard_version_index.cc
    subposet.cc
    subposet_state.cc
    total_poset_member.cc
   )

SheafSystem_collect_sources(sheaves "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    abstract_poset_member.impl.h 
    namespace_poset.impl.h 
    poset_crg_state.impl.h 
    poset_state_handle.impl.h
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

