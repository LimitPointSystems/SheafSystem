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

configure_file(singly_linked_list.h.in ${CMAKE_BINARY_DIR}/include/singly_linked_list.h)
install(FILES ${CMAKE_BINARY_DIR}/include/singly_linked_list.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

#
# Library sources.
#
set(SRCS
    any.cc
    arg_list.cc
    assert_contract.cc
    auto_block.cc
    binary_index_block.cc
    block.cc
    deep_size.cc
    error_message.cc
    id_block.cc
    int_set.cc
    interval_set.cc
    interval_set_iterator.cc
    list_pool.cc
    plot.cc
    pod_types.cc
    primitive_attributes.cc
    primitive_traits.cc
    primitive_type.cc
    primitive_value.cc
    ragged_array.cc
    rc_any.cc
    rc_ptr.cc
    report.cc
    scoped_index.cc
    stl_scoped_index.cc
    stop_watch.cc
    tern.cc
    tolerance_comparison.cc
    zn_to_bool.cc
    wsv_block.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    auto_block.impl.h 
    binary_index_block.impl.h 
    block.impl.h
    deep_size.impl.h 
    factory.h 
    factory.impl.h 
    index_traits.h 
    list_pool.impl.h
    pool.h 
    pool.impl.h 
    ptr_linked_pool.h 
    ptr_linked_pool.impl.h 
    ragged_array.impl.h 
    rc_ptr.impl.h 
    set_filter.h 
    sheaf_dll_spec.h
    stl_scoped_index.impl.h 
    unordered_set_filter.h 
    wsv_block.impl.h 
    zn_to_bool_filter.h
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


