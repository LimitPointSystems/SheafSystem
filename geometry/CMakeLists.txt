#
#
# Copyright (c) 2013 Limit Point Systems, Inc. 

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#   http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project(geometry)

cmake_minimum_required(VERSION 2.8.3)

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
export_targets()

#
# Prepare this component's lib targets and include paths for export to an install config file.
#
export_install_config_file_vars()

