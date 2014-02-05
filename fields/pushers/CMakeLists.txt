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
    average_push_action.cc
    avg_section_pusher.cc
    body_builder.cc
    body_factory.cc
    body_pusher.cc
    body_pusher_pullback_action.cc
    constant_push_action.cc
    copy_push_action.cc
    pullback_map.cc
    section_pusher.cc
    section_pusher_pullback_action.cc
    section_pusher_push_action.cc

   )

## @hack: The following 5 classes are excluded from the SRCS list because they 
## are currently unused and there is no working test driver. -- JEB 01/03/13

##    average_base_space_map_push_action.cc
##    base_space_map.cc
##    base_space_map_push_action.cc
##    constant_base_space_map_push_action.cc
##    copy_base_space_map_push_action.cc

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

