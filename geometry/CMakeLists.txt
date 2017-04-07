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

#
# Announce current status.
#
SheafSystem_status_message("Processing geometry component")

#
# Define the clusters for this component.
#
set(clusters coordinates general point_locators template_instantiations)

#
# Include functions and definitions common to all components.
# 
include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/component_functions.cmake)

#
# Initialize all variables for this component.
#
SheafSystem_set_component_variables(geometry)

#
# Add the clusters to the project
#
SheafSystem_add_clusters("${clusters}")

#
# Set the ipath variable.
#
SheafSystem_set_component_ipath_variable(geometry "${clusters}")

#
# Include the functions and variable definitions unique to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Set some cumulative geometry-specific variables
#
SheafSystem_set_cumulative_geometry_variables()

#
# Add the library targets
#
SheafSystem_add_geometry_library_targets()

#
# Add Bindings targets
#
if(SHEAFSYSTEM_BUILD_BINDINGS)
   SheafSystem_add_geometry_bindings_targets()
endif()

#
# Installation target
#
#SheafSystem_add_geometry_install_target()
SheafSystem_add_component_install_target(geometry)

