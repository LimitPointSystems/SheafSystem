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
cmake_minimum_required(VERSION 3.0.0)

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
# Install the documentation
#
if(INSTALL_DOCS)
    install_docs()
endif()    

#
# Write the system's lib and binary paths to an export file.
#
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
    "set(SHEAFSYSTEM_LIB_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
# Mark the variable as advanced           
#file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "mark_as_advanced(FORCE SHEAFSYSTEM_LIB_DIR)\n")         
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")

file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
    "set(SHEAFSYSTEM_BIN_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} binary output directory\")\n")
# Mark the variable as advanced           
#file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "mark_as_advanced(FORCE ${COMPONENT}_BIN_OUTPUT_DIR)\n") 
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
    "set(SHEAFSYSTEM_INC_DIR ${CMAKE_BINARY_DIR}/include CACHE STRING \"${PROJECT_NAME} binary output directory\")\n")


#
# Export this component's library targets and list of includes for install
# The file locations on an install (includes, libs, etc) are different
# than they are in a build tree. The install config produces
# a .cmake.in file that is configured by the client.
#
function(export_libs)
    if(WIN64MSVC OR WIN64INTEL)
        # The BUILD_TYPE variable will be set while CMake is processing the install files. It is not set at configure time
        # for this project. We pass it literally here.
        foreach(comp ${COMPONENTS})
            string(TOUPPER ${comp} COMP)        
            message(STATUS "Current lib is: ${comp}")
            install(EXPORT ${${COMP}_IMPORT_LIB} DESTINATION lib)
            install(EXPORT ${${COMP}_IMPORT_LIB} DESTINATION bin)
        endforeach()         
    endif()
endfunction(export_libs)

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
#generate_install_config_file()

 #       install(TARGETS sheaf fiber_bundle geometry fields EXPORT sheafsystem RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
#        install(EXPORT sheafsystem DESTINATION  ${CMAKE_INSTALL_PREFIX} FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)
        
#        install(TARGETS fiber_bundle EXPORT fiber_bundle RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
#        install(EXPORT fiber_bundle DESTINATION  ${CMAKE_INSTALL_PREFIX} FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)
        
#        install(TARGETS geometry EXPORT geometry RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
#        install(EXPORT geometry DESTINATION  ${CMAKE_INSTALL_PREFIX} FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)
        
#        install(TARGETS fields EXPORT fields RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
#        install(EXPORT fields DESTINATION  ${CMAKE_INSTALL_PREFIX} FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)





#
# Install HDF5 headers to <include> dir
#
install_prereqs()

#
# Install the exports file
#
#if(LINUX64INTEL OR LINUX64GNU)
#    install(FILES ${PROJECT_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION ${CMAKE_BUILD_TYPE}/config)
#else()
#    install(FILES ${PROJECT_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION config/\${BUILD_TYPE})#
#endif()    

#
# Markup the RELEASE_NOTES file. 
#
set(RELEASE_DATE)
get_date(RELEASE_DATE)

#
# Generate some info about the release
#
file(WRITE ${CMAKE_BINARY_DIR}/VERSION "${PROJECT_NAME} version ${LIB_VERSION} ${RELEASE_DATE}  \n")
install(FILES ${PROJECT_BINARY_DIR}/VERSION DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/RELEASE_NOTES.in ${CMAKE_BINARY_DIR}/RELEASE_NOTES)

#if(TARGET install)
    if(LINUX64GNU OR LINUX64INTEL)
        install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX})
    else()
        install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX} RENAME RELEASE_NOTES.txt)
    endif()
#endif()

#    if(WIN64MSVC OR WIN64INTEL)
#        install(TARGETS ${COMPONENTS} EXPORT 
#            ${PROJECT_NAME} ARCHIVE DESTINATION lib/\${BUILD_TYPE} 
#            RUNTIME DESTINATION bin/\${BUILD_TYPE} INCLUDES DESTINATION include/ComLimitPoint/SheafSystem)
#    endif()

 #       install(TARGETS sheaf/sheaf fiber_bundle  EXPORT sheafsystem  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
 #      install(TARGETS sheaf fiber_bundle  EXPORT sheafsystem ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
 #       install(EXPORT ${${COMPONENT}_IMPORT_LIB}  DESTINATION  ${CMAKE_INSTALL_PREFIX}/cmake FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)
 #       install(EXPORT ${${COMPONENT}_IMPORT_LIB}_implib DESTINATION  ${CMAKE_INSTALL_PREFIX}/cmake FILE ${INSTALL_CONFIG_FILE} EXPORT_LINK_INTERFACE_LIBRARIES)