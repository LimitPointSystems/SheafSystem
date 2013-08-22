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
    biorder_iterator.cc
    biorder_itr.cc
    depth_first_iterator.cc
    depth_first_itr.cc
    filtered_depth_first_itr.cc
    filtered_depth_first_iterator.cc
    filtered_depth_first_member_iterator.cc
    index_iterator.cc
    linkorder_iterator.cc
    linkorder_itr.cc
    postorder_iterator.cc
    postorder_itr.cc
    postorder_member_iterator.cc
    preorder_iterator.cc
    preorder_itr.cc
    preorder_member_iterator.cc
    subposet_member_iterator.cc
    triorder_iterator.cc
    triorder_itr.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    poset_member_iterator.h 
	biorder_itr.impl.h 
	depth_first_itr.impl.h 
	filtered_depth_first_itr.impl.h 
	linkorder_itr.impl.h 
	postorder_itr.impl.h 
	preorder_itr.impl.h 
	triorder_itr.impl.h
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
