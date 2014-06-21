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

project(sheaves)

#
# Include the functions and variable definitions unique to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Announce current status.
#
status_message("Processing ${PROJECT_NAME}")

#
# Set compiler flags for all build configurations
#
set_compiler_flags() 
#
# Set up output directories
#
create_output_dirs()

#
# Add the library targets
#
add_library_targets()

#
# Add Bindings targets
#
add_bindings_targets()

#
# Installation target
#
add_install_target()

#
# Write this component's lib targets and include paths to an export file.
#
write_exports_file()

#
# Prepare this component's lib targets and include paths for export to an install config file.
# This data only gets used by clients when the SheafSystem has been installed.
#
export_install_config_file_vars()

#
# Sheaves is responsible for the std headers;
# append their location to the exports file.
#
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(STD_HEADERS ${STD_HEADERS} CACHE STRING \"STD headers\")\n")
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(STD_IPATH ${CMAKE_BINARY_DIR}/include CACHE STRING \"STD header include path\")\n")


