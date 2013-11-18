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

cmake_policy(SET CMP0022 NEW)

##
# This file is the system level counterpart to the component_definitions file
# found in the top level of any component. Functions and variables
# that need to have system scope should be declared and/or defined here.
##

set(BUILD_TOOLS OFF CACHE BOOL "Toggle build of tools component. If no, then no need to look for JDK or VTK unless BUILD_BINDINGS is on.")
set(INSTALL_DOCS ON CACHE BOOL "Documentation is installed by default.")

#
# Establish the version number for this build.
# This is only relevant for releases. 0.0.0.0 is chosen here
# simply as a stub.
#
set(LIB_VERSION 0.0.0.0 CACHE STRING "Library version number for release purposes")
mark_as_advanced(LIB_VERSION)

#
# Establish the list of components in this system
#
if(BUILD_TOOLS)
    set(COMPONENTS sheaves fiber_bundles geometry fields tools CACHE STRING "List of components in this system" FORCE)
else()
    set(COMPONENTS sheaves fiber_bundles geometry fields CACHE STRING "List of components in this system" FORCE)
endif()

#
# Set the default value for install location
#
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND LIB_VERSION MATCHES "0.0.0.0" )
    if(LINUX64GNU OR LINUX64INTEL)
      set(CMAKE_INSTALL_PREFIX
        "$ENV{HOME}/SheafSystem" CACHE PATH "SheafSystem install prefix" FORCE
        )
    else()
      set(CMAKE_INSTALL_PREFIX
        "$ENV{USERPROFILE}/SheafSystem" CACHE PATH "SheafSystem install prefix" FORCE
        )
    endif()
endif()

#
# Now fix the install path.
#
file(TO_CMAKE_PATH ${CMAKE_INSTALL_PREFIX} CMAKE_INSTALL_PREFIX)

#
# Platform definitions
#
# OS is 64 bit Windows, compiler is cl 
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND MSVC AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(WIN64MSVC ON CACHE BOOL "MS compiler in use.")
# OS is 64 bit Windows, compiler is icl
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND CMAKE_CXX_COMPILER_ID MATCHES "Intel" AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(WIN64INTEL ON CACHE BOOL "Intel compiler in use.")
# OS is 64 bit linux, compiler is g++
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux" AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(LINUX64GNU ON CACHE BOOL "GNU compiler in use.")
# OS is 64 bit linux, compiler is icpc
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux" AND CMAKE_CXX_COMPILER_ID MATCHES "Intel" AND CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(LINUX64INTEL ON CACHE BOOL "Intel compiler in use.")
else()
    message(FATAL_ERROR "A 64 bit Windows or Linux environment was not detected; exiting")
endif()

#
# Define the exports files
#
set(EXPORTS_FILE ${PROJECT_NAME}-exports.cmake CACHE STRING "System exports file name")
set(INSTALL_CONFIG_FILE ${PROJECT_NAME}-install.cmake CACHE STRING "Install config file name")

#
# Delete the exports file at the start of each cmake run
#
execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE})

#
# Set the default build type.
#
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug_contracts" CACHE STRING
      "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}."      
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#
# Tell CMake which configurations are "debug"
#
set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug_contracts" "Debug_no_contracts") 

#
# Establish the file name suffix for debug type compuiler output
#
if(WIN64MSVC OR WIN64INTEL)
    set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_d" CACHE STRING "Debug libs suffix")
    set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_d" CACHE STRING "Debug libs suffix")
else()
    set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_debug" CACHE STRING "Debug libs suffix")
    set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_debug" CACHE STRING "Debug libs suffix")
endif()

#   
#  Type of system documentation to build: Dev or User
#
set(BUILD_BINDINGS NO CACHE BOOL "Toggle build of language bindings.")

#
# Toggle multi-process compilation in win32.
#
set(ENABLE_WIN32_MP ON CACHE BOOL "Toggle win32 compiler MP directive. Works for MS and Intel. Default is ON.")

#
# Toggle intel compiler warnings.
#
set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")

#   
#  Type of system documentation to build: Dev or User
#  User docs do not contain source code listing. Otherwise,
#  Dev and User are identical.
#
set(DOC_STATE Dev CACHE STRING "Type of documentation to build: [Dev|User]")

#
# Enable coverage results
#
if(LINUX64GNU OR LINUX64INTEL)
    set(ENABLE_COVERAGE OFF CACHE BOOL "Set to ON to compile with coverage support. Default is OFF.")
endif()

#
# Set the location of the coverage foilder and create it.
#
if(ENABLE_COVERAGE)
    set(COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage CACHE STRING "Directory for coverage files")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_DIR})
endif()

#
# Default linux installation location is /usr/local
# Set a default where the user has write permission ; in this
# case, the top of the components source tree.
# "lib", "include", and "bin" will be appended to this location.
# See "add_install_target" in cmake_modules/LPSCommon.cmake for source.
#
if(LINUX64GNU OR LINUX64INTEL)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE STRING "System install location")
elseif(WIN64MSVC OR WIN64INTEL)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE STRING "System install location")
endif()

#
# Set the cmake module path.
#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" CACHE STRING "Location of Cmake modules")

#
# Targets with global scope are declared and optionally defined in 
# target_declarations.cmake; otherwise defined at first use.
#
include(${CMAKE_MODULE_PATH}/target_declarations.cmake)

#
# Prerequisite discovery
#
include(${CMAKE_MODULE_PATH}/find_prerequisites.cmake)

#
# Detect C++11 features
#
message(STATUS " ")
message(STATUS "Checking for C++11 Compliance - ")
message(STATUS " ")

include(${CMAKE_MODULE_PATH}/CheckCXX11Features.cmake)

#
# Utility function to add components to a system.
#
function(add_components)

    foreach(comp ${COMPONENTS})
        clear_component_variables(${comp})
        add_subdirectory(${comp})
    endforeach()

endfunction(add_components)

#
# Clear cached variables at the start of each cmake run.
# This prevents the variables from containing diplicate entries.
#
function(clear_component_variables comp)

    string(TOUPPER ${comp} COMP)

    # clear the srcs vars so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_SRCS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_UNIT_TEST_SRCS CACHE)

    # clear the example binaries var so consecutive cmake runs don't
    # list the same sources n times.
    unset(${COMP}_EXAMPLE_SRCS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same unit tests n times.
    unset(${COMP}_UNIT_TESTS CACHE)
    
    # clear the unit tests var so consecutive cmake runs don't
    # list the same includes n times.
    unset(${COMP}_INCS CACHE)
    
    # clear the ipath var so consecutive cmake runs don't
    # list the same include paths n times.
    unset(${COMP}_IPATH CACHE)

    # clear the ipath var so consecutive cmake runs don't
    # list the same include paths n times.
    unset(${COMP}_CLASSPATH CACHE)
    
endfunction(clear_component_variables)

# 
#  Make emacs tags
#
function(add_tags_target)

    if(LINUX64GNU OR LINUX64INTEL)
        add_custom_target(tags
            COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -name build -prune -o -name "*.cc" -print -o -name "*.h" -print -o -name "*.t.cc" -print | etags --c++ --members -
        )
    endif()

endfunction(add_tags_target) 
