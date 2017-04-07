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

# Logic below depends on SHEAFSYSTEM_BUILD_BINDINGS being on if SHEAFSYSTEM_BUILD_SHEAFSCOPE is.

dbc_require_implies(SHEAFSYSTEM_BUILD_SHEAFSCOPE SHEAFSYSTEM_BUILD_BINDINGS)

#
# Announce current status.
#
SheafSystem_status_message("Processing tools component")

#
# Define the clusters for this component.
#
if(SHEAFSYSTEM_BUILD_BINDINGS)
   set(clusters SheafScope common/client_server common/event common/gui common/util 
      util viewer/animation viewer/common viewer/event viewer/render viewer/table 
      viewer/user viewer/application)
else()
   set(clusters util)
endif()


#
# Include functions and definitions common to all components.
# 
include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/component_functions.cmake)

#
# Initialize standard variables for this component.
#
SheafSystem_set_component_variables(tools)

#
# Add the clusters to the project
#
SheafSystem_add_clusters("${clusters}")

#
# Set the ipath variable.
#
SheafSystem_set_component_ipath_variable(tools "${clusters}")

#
# Include the functions and variable definitions unique to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Set some cumulative tools-specific variables
#
SheafSystem_set_cumulative_tools_variables()

#
# examples will corrupt the scope sources. Include it after.
#
add_subdirectory(examples)

#
# Intialize the SheafScope sources var
#
SheafSystem_set_scope_sources()

if(SHEAFSYSTEM_BUILD_BINDINGS)
   #
   # Add the library targets
   #
   SheafSystem_add_tools_library_targets()
   #
   # Add Bindings targets
   #
   SheafSystem_add_tools_bindings_targets()
endif()

#
# Add a target for the dumpsheaf utility
#
SheafSystem_add_dumpsheaf_target()

#
# Add a target for the sheafscope exe wrapper
#
if(SHEAFSYSTEM_BUILD_SHEAFSCOPE)
    SheafSystem_add_sheafscope_wrapper_target()
endif()

#
# Installation target
#
SheafSystem_add_tools_install_target()
