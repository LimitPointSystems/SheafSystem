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

# Setting CMAKE_CONFIGURATION_TYPES prior to the project function call
# will eliminate the default configuration types (debug,release,RelWithDebugInfo, et al.) --
# or at least stop them from appearing in the VS configuration list.
# It does NOT stop cmake from setting all the cache variables associated with those same
# configurations however.

if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES Debug_contracts Debug_no_contracts Release_contracts Release_no_contracts 
         RelWithDebInfo_contracts RelWithDebInfo_no_contracts CACHE STRING "Supported configuration types"
        FORCE)
else()
    set(CMAKE_CONFIGURATION_TYPES Debug_contracts Debug_no_contracts Release_contracts Release_no_contracts 
         CACHE STRING "Supported configuration types"
        FORCE)
endif()

#
# Establish the project name
#    
project(SheafSystem)

#
# Specify the minimum cmake version.
#
cmake_minimum_required(VERSION 2.8.12)

#
# Include variable definitions and functions
# unique to and/or required at the system level.
#
include(system_definitions.cmake)

#
# Add components to the system
#
add_components()

#
# Set up output directories
#
create_output_dirs()

#
# Add the documentation targets (doc, docclean)
# Doc targets are system level and system scope.
# currently there is no notion of building a single
# component's documentation.
#
add_doc_targets()

#
# Target to generate emacs tags
#
add_tags_target()

#
# Configure the environment scripts. 
#
if(LINUX64GNU OR LINUX64INTEL)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)
endif()
 
#
# System level is responsible for installing the documentation. The component list (see system_definitions.cmake)
# determines what components are included in the docs.
# NOTE: Prepending of ${CMAKE_INSTALL_PREFIX}/ to the value of DESTINATION is implicit in the install command.
# You need only specify the sub-directory within ${CMAKE_INSTALL_PREFIX}, cmake will create the dir.
# With no value specified for DESTINATION, all files are placed in ${CMAKE_INSTALL_PREFIX}.
#
if(INSTALL_DOCS)
    install(DIRECTORY ${CMAKE_BINARY_DIR}/documentation/ DESTINATION documentation)
endif()

#
# Generate the install configuration file.
#
generate_install_config_file()

#
# Install HDF5 headers to <include> dir
#
install_prereqs()

#
# Install the exports file
#
if(LINUX64INTEL OR LINUX64GNU)
    install(FILES ${PROJECT_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION ${CMAKE_BUILD_TYPE}/config)
else()
    install(FILES ${PROJECT_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION config/\${BUILD_TYPE})
endif()    

#
# Markup the RELEASE_NOTES file. 
#
set(RELEASE_DATE)
get_date(RELEASE_DATE)
configure_file(${CMAKE_SOURCE_DIR}/RELEASE_NOTES.in ${CMAKE_BINARY_DIR}/RELEASE_NOTES)

#if(TARGET install)
    if(LINUX64GNU OR LINUX64INTEL)
        install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX})
    else()
        install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX} RENAME RELEASE_NOTES.txt)
    endif()
#endif()