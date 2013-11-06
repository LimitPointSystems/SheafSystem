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
    abstract_poset_member.inst.cc
    auto_block.inst.cc
    binary_index_block.inst.cc
    biorder_itr.inst.cc
    block.inst.cc
    deep_size.inst.cc
    depth_first_itr.inst.cc
    factory.inst.cc
    filtered_depth_first_itr.inst.cc
    index_space_family.inst.cc
    index_space_handle.inst.cc
    linkorder_itr.inst.cc
    list_pool.inst.cc
    namespace_poset.inst.cc
    pool.inst.cc
    poset_crg_state.inst.cc
    poset_state_handle.inst.cc
    postorder_itr.inst.cc
    preorder_itr.inst.cc
    ragged_array.inst.cc
    rc_ptr.inst.cc
    record_map.inst.cc
    stl_scoped_index.inst.cc
    triorder_itr.inst.cc
    wsv_block.inst.cc
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
