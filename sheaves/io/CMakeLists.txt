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
    attributes_record.cc
    attributes_record_set.cc
    data_converter.cc
    data_type_map.cc
    dof_tuple_class_names_record.cc
    dof_tuple_col_bounds_record.cc
    dof_tuple_domain_offsets_record.cc
    dof_tuple_record_set.cc
    dof_tuple_schema_ids_record.cc
    dof_tuple_schema_versions_record.cc
    dof_tuple_types_record.cc
    file_data_type_map.cc
    id_space_names_record.cc
    interval_index_space_record.cc
    member_class_names_record.cc
    member_names_record.cc
    member_record.cc
    member_record_set.cc
    poset_bounds.cc
    poset_bounds_descriptor.cc
    poset_data_type_map.cc
    poset_general_record.cc
    poset_scaffold.cc
    record.cc
    record_queue.cc
    record_set.cc
    sheaf_file.cc
    storage_agent.cc
    subposet_names_record.cc
    table_dof_tuple_record.cc
    variable_length_record.cc
   )

SheafSystem_collect_sources(sheaves "${SRCS}")

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    record_index.h
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

