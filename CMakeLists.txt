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
# Specify the minimum cmake version.
#
cmake_minimum_required(VERSION 3.5.0)

#
# Make sure if() treats constants like TRUE as constants 
# rather than implicitly treating them as variables and trying to dereference them.

cmake_policy(SET CMP0012 NEW)

#
# Set the cmake module path.
#
set(SHEAFSYSTEM_CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" 
   CACHE STRING "Location of Sheaf System Cmake modules")
mark_as_advanced(FORCE SHEAFSYSTEM_CMAKE_MODULE_PATH)

# Make the requires and ensures functions available.

include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/design_by_contract.cmake)

# Setting CMAKE_CONFIGURATION_TYPES prior to the project function call
# will eliminate the default configuration types (debug,release,RelWithDebugInfo, et al.) --
# or at least stop them from appearing in the VS configuration list.
# It does NOT stop cmake from setting all the cache variables associated with those same
# configurations however.

if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES Debug_contracts Debug_no_contracts Release_contracts Release_no_contracts 
       RelWithDebInfo_contracts RelWithDebInfo_no_contracts 
       CACHE STRING "Supported configuration types" FORCE)
    mark_as_advanced(FORCE CMAKE_CONFIGURATION_TYPES)
else()
    set(CMAKE_CONFIGURATION_TYPES Debug_contracts Debug_no_contracts Release_contracts Release_no_contracts 
       CACHE STRING "Supported configuration types" FORCE)
    mark_as_advanced(FORCE CMAKE_CONFIGURATION_TYPES)
endif()

#
# Establish the project name
#    
project(SheafSystem)

#
# Include variable definitions and functions
# unique to and/or required at the system level.
#
include(system_definitions.cmake)
SheafSystem_make_system_definitions()

#
# Set up output directories
#
SheafSystem_create_output_dirs()

#
# Add components to the system
#
SheafSystem_add_components()

#
# Add all the system level targets.
#
include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/target_declarations.cmake)
SheafSystem_add_system_targets()

#
# Configure the environment variable scripts. 
#
if(SHEAFSYSTEM_LINUX)
    configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
    configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)
endif()

#
# Generate the install configuration file.
#
SheafSystem_generate_install_config_files()

#
# Install HDF5 headers to <include> dir
#
SheafSystem_install_prereqs()

#
# Install the documentation.
#
if(SHEAFSYSTEM_INSTALL_DOCS)
    SheafSystem_install_documentation()
endif()    

#
# Install the release notes.
#
SheafSystem_install_release_notes()
