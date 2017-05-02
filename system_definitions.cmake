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

##
# This file is the system level counterpart to the component_definitions file
# found in the top level of any component. Functions and variables
# that need to have system scope should be declared and/or defined here.
##


#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Make sure system level variables are defined and initialize to default values.
#
function(SheafSystem_set_system_variable_defaults)

   # Make sure SHEAFSYSTEM_BUILD_SHEAFSCOPE is defined; won't overwrite value if it already exists.

   set(SHEAFSYSTEM_BUILD_SHEAFSCOPE OFF CACHE BOOL "Toggle build of the SheafScope.")

   # Make sure SHEAFSYSTEM_BUILD_BINDINGS is defined; won't overwrite value if it already exists.

   set(SHEAFSYSTEM_BUILD_BINDINGS OFF CACHE BOOL "Toggle build of language bindings.")
   if(${SHEAFSYSTEM_BUILD_SHEAFSCOPE})

      # SHEAFSYSTEM_BUILD_SHEAFSCOPE implies SHEAFSYSTEM_BUILD_BINDINGS.
      # Invocation with FROCE will overwrite current value.

      set(SHEAFSYSTEM_BUILD_BINDINGS ON CACHE BOOL "Toggle build of language bindings." FORCE)

   endif()

   # Make sure SHEAFSYSTEM_INSTALL_DOCS is defined; won't overwrite value if it already exists.

   set(SHEAFSYSTEM_INSTALL_DOCS ON CACHE BOOL "Toggle install state of Documentation.")

   #
   # Make sure SHEAFSYSTEM_LIB_VERSION is defined; won't overwrite value if it already exists.
   #
   set(SHEAFSYSTEM_LIB_VERSION 0.0.0.0 CACHE STRING "Library version number for release purposes")
   mark_as_advanced(SHEAFSYSTEM_LIB_VERSION)

   #
   # Define the tag for the exported target set
   #
   set(SHEAFSYSTEM_EXPORT_NAME SheafSystemTargets
      CACHE STRING "As used in install(EXPORT <export-name> ...)")
   mark_as_advanced(SHEAFSYSTEM_EXPORT_NAME)

   #
   # Define path to include dir for build and installed configurations.
   #
   set(SHEAFSYSTEM_BUILD_INC_DIR ${CMAKE_BINARY_DIR}/include
      CACHE PATH "Path to build include directory.")
   mark_as_advanced(SHEAFSYSTEM_BUILD_INC_DIR)  

   set(SHEAFSYSTEM_INSTALL_INC_DIR include
      CACHE PATH "Relative path to install include directory.")
   mark_as_advanced(SHEAFSYSTEM_INSTALL_INC_DIR)  

   #
   # Define the unique header file scope qualifier and directory path.
   #
   set(SHEAFSYSTEM_HEADER_SCOPE SheafSystem
      CACHE STRING "Used to give header files unique scope in include directives.")
   mark_as_advanced(SHEAFSYSTEM_HEADER_SCOPE)  

   set(SHEAFSYSTEM_HEADER_DIR ${SHEAFSYSTEM_BUILD_INC_DIR}/${SHEAFSYSTEM_HEADER_SCOPE}
      CACHE PATH "Path to scoped header file directory.")
   mark_as_advanced(SHEAFSYSTEM_HEADER_DIR)  

   #   
   #  Type of system documentation to build: Dev or User
   #  User docs do not contain source code listing. Otherwise,
   #  Dev and User are identical.
   #
   set(SHEAFSYSTEM_DOC_STATE Dev CACHE STRING "Type of documentation to build: [Dev|User]")

   # Set STRINGS property so GUI displays cycle-through or drop-down list.
   
   set(ldoc_state_values Dev User)
   set_property(CACHE SHEAFSYSTEM_DOC_STATE PROPERTY STRINGS ${ldoc_state_values})

   dbc_ensure_implies(SHEAFSYSTEM_BUILD_SHEAFSCOPE SHEAFSYSTEM_BUILD_BINDINGS)

endfunction(SheafSystem_set_system_variable_defaults)


#
# Set platform definitions
#
function(SheafSystem_set_platform_variables)

   # Make sure platform variables are defined.

   set(SHEAFSYSTEM_WINDOWS OFF
      CACHE BOOL "True if platform is Windows" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_WINDOWS)

   set(SHEAFSYSTEM_LINUX OFF
      CACHE BOOL "True if platform is Linux" FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_LINUX)

   set(SHEAFSYSTEM_WIN64MSVC OFF
      CACHE BOOL "True if platform is Windows and MS compiler in use." FORCE)
   mark_as_advanced(FORCE SHEAFSYSTEM_WIN64MSVC)

   set(SHEAFSYSTEM_WIN64INTEL OFF
      CACHE BOOL "True if platorm is Windows and Intel compiler in use." FORCE)
   mark_as_advanced(SHEAFSYSTEM_WIN64INTEL)

   set(SHEAFSYSTEM_LINUX64GNU OFF
      CACHE BOOL "True if platform is Linux and GNU CXX compiler in use." FORCE)
   mark_as_advanced(SHEAFSYSTEM_LINUX64GNU)

   set(SHEAFSYSTEM_LINUX64INTEL OFF
      CACHE BOOL "True if platform is Linux and Intel compiler in use." FORCE)
   mark_as_advanced(SHEAFSYSTEM_LINUX64INTEL)   

   if(CMAKE_SIZEOF_VOID_P MATCHES "8")

      if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")

         # OS is 64 bit Windows 

         set(SHEAFSYSTEM_WINDOWS ON CACHE BOOL "True if platform is Windows" FORCE)

         # Toggle multi-process compilation in win32.

         set(SHEAFSYSTEM_ENABLE_WIN32_MP ON
            CACHE BOOL "Toggle win32 compiler MP directive. Works for MS and Intel. Default is ON.")

         # Turn on project folders for Visual Studio.

         set_property(GLOBAL PROPERTY USE_FOLDERS ON)

         if(MSVC)

            # OS is 64 bit Windows, compiler is cl 

            set(SHEAFSYSTEM_WIN64MSVC ON
               CACHE BOOL "True if platform is Windows and MS compiler in use." FORCE)

         elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")

            # OS is 64 bit Windows, compiler is icl

            set(SHEAFSYSTEM_WIN64INTEL ON
               CACHE BOOL "True if platorm is Windows and Intel compiler in use." FORCE)

            set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")
            mark_as_advanced(FORCE INTELWARN)

         else()

            message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} not supported.")

         endif()

      elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

         # OS is 64 bit Linux 

         set(SHEAFSYSTEM_LINUX ON CACHE BOOL "True if platform is Linux" FORCE)

         if(CMAKE_COMPILER_IS_GNUCXX)

            # OS is 64 bit linux, compiler is g++

            if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.3)
               message(FATAL "g++ ${CMAKE_CXX_COMPILER_VERSION} is unsupported. Version must be >= 4.9.3")                
            endif()

            set(SHEAFSYSTEM_LINUX64GNU ON CACHE BOOL "True if platform is Linux and GNU CXX compiler in use." FORCE)

         elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")

            # OS is 64 bit linux, compiler is icpc

            set(SHEAFSYSTEM_LINUX64INTEL ON CACHE BOOL "True if platform is Linux and Intel compiler in use." FORCE)

            set(INTELWARN CACHE BOOL "Toggle Intel compiler warnings")
            mark_as_advanced(FORCE INTELWARN)

         else()

            message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} not supported.")

         endif(CMAKE_COMPILER_IS_GNUCXX)

         # The compiler library path; used to set LD_LIBRARY_PATH in env scripts.

         string(REPLACE ";" ":" lshfsys_lib_dirs "${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES}")
         set(SHEAFSYSTEM_CXX_IMPLICIT_LINK_DIRECTORIES "${lshfsys_lib_dirs}" 
            CACHE STRING "C++ compiler library directories." FORCE)
         mark_as_advanced(FORCE SHEAFSYSTEM_CXX_IMPLICIT_LINK_DIRECTORIES)

      else()

         # Neither Windows or Linux

         message(FATAL_ERROR "Operating system ${CMAKE_HOST_SYSTEM_NAME} not supported")

      endif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")

   else(CMAKE_SIZEOF_VOID_P MATCHES "8")

         message(FATAL_ERROR "Only 64 bit platform supported.")

   endif(CMAKE_SIZEOF_VOID_P MATCHES "8")

   dbc_ensure_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

endfunction(SheafSystem_set_platform_variables)

#
# Set the default value for install location
#
function(SheafSystem_set_system_install_location_default)
   
   if(NOT DEFINED SHEAFSYSTEM_INSTALL_PREFIX_SET)

      # CMAKE_INSTALL_PREFIX is set to cmake default, which is not usually writable.
      # Set it to something reasonable that should be writable.
      
      set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "System install location" FORCE)

      set(SHEAFSYSTEM_INSTALL_PREFIX_SET "TRUE" CACHE INTERNAL "True if CMAKE_INSTALL_PREFIX has been initialized")
      
   else()

      # CMAKE_INSTALL_PREFIX is either not set or has been set by user.
      # Set it to something writable if it has not been set, won't
      # overwrite value if user has already set it.

      set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "System install location")

   endif()

   dbc_ensure_defined(CMAKE_INSTALL_PREFIX)

endfunction(SheafSystem_set_system_install_location_default)


#
# Set debug configuration properties.
#
function(SheafSystem_set_debug_configuration)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   # Tell CMake which configurations are "debug"

   set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug_contracts" "Debug_no_contracts") 

   # Establish the file name suffix for debug type compiler output

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_d"
         CACHE STRING "Debug libs suffix for Debug_contracts configuration")
      mark_as_advanced(FORCE CMAKE_DEBUG_CONTRACTS_POSTFIX)

      set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_d"
         CACHE STRING "Debug libs suffix for Debug_no_contracts configuration")
      mark_as_advanced(FORCE CMAKE_DEBUG_NO_CONTRACTS_POSTFIX)

   elseif(SHEAFSYSTEM_LINUX)

      set(CMAKE_DEBUG_CONTRACTS_POSTFIX "_debug"
         CACHE STRING "Debug libs suffix for Debug_contracts configuration")
      mark_as_advanced(FORCE CMAKE_DEBUG_CONTRACTS_POSTFIX)

      set(CMAKE_DEBUG_NO_CONTRACTS_POSTFIX "_debug"
         CACHE STRING "Debug libs suffix for Debug_no_contracts configuration")
      mark_as_advanced(FORCE CMAKE_DEBUG_NO_CONTRACTS_POSTFIX)

   endif()

endfunction(SheafSystem_set_debug_configuration)

#
# Set the default build type.
#
function(SheafSystem_set_default_build_type)

   if(NOT CMAKE_BUILD_TYPE)      
      set(CMAKE_BUILD_TYPE "Debug_contracts" 
         CACHE 
         STRING 
         "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}."
         FORCE)
   elseif(NOT (CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES))
      message(FATAL_ERROR "CMAKE_BUILD_TYPE must be one of ${CMAKE_CONFIGURATION_TYPES}")
   endif()

   if(SHEAFSYSTEM_WINDOWS)

      # On Windows the client  doesn't set the build type at configure time,
      # so mark it advanced so it doesn't clutter up the interface.

      mark_as_advanced(FORCE CMAKE_BUILD_TYPE)
      
   endif()

   # Set STRINGS property so GUI displays cycle-through or drop-down list.
   
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

endfunction(SheafSystem_set_default_build_type)

function(SheafSystem_set_coverage_defaults)

   # Disable coverage results by default; won't overwrit existing value.

   set(SHEAFSYSTEM_ENABLE_COVERAGE OFF
      CACHE BOOL "Set to ON to compile with coverage support. Default is OFF.")
   mark_as_advanced(FORCE SHEAFSYSTEM_ENABLE_COVERAGE)

   # Set the location of the coverage folder and then create it.

   if(SHEAFSYSTEM_ENABLE_COVERAGE)

      set(SHEAFSYSTEM_COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage CACHE STRING "Directory for coverage files")
      mark_as_advanced(FORCE SHEAFSYSTEM_COVERAGE_DIR)
      
      execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${SHEAFSYSTEM_COVERAGE_DIR})

      #
      # Set some variables for the Intel coverage utilities.
      # $$TODO: Linux only for now -- hook up for Windows as well if we pursue 
      # support for Intel.
      #
      if(SHEAFSYSTEM_LINUX64INTEL)

         set(UNCOVERED_COLOR DE0829 CACHE STRING "Color for uncovered code.")
         set(COVERED_COLOR 319A44 CACHE STRING "Color for covered code.")
         set(PARTIAL_COLOR E1EA43 CACHE STRING "Color for partially covered code.")

         # Lop the compiler name off the end of the CXX string

         string(REPLACE "/icpc" "" INTELPATH ${CMAKE_CXX_COMPILER})

         # The codecov executable

         set(CODECOV "${INTELPATH}/bin/codecov" CACHE STRING "Intel Code coverage utility.")

         # The profmerge executable

         set(PROFMERGE "${INTELPATH}/bin/profmerge" CACHE STRING "Intel dynamic profile merge utility." )

         # The compiler library path.

         set(INTEL_LIBPATH "${INTELPATH}/lib/intel64" CACHE STRING "Intel C++ compiler library path." )

      elseif(SHEAFSYSTEM_LINUX64GNU)

         # Lop the compiler name off the end of the CXX string to get the gnu root.

         string(REPLACE "bin/g++" "" GNUPATH ${CMAKE_CXX_COMPILER})

         # The compiler library path.

         set(GNU_LIBPATH "${GNUPATH}lib64" CACHE STRING "GNU C++ compiler library path." )

      endif(SHEAFSYSTEM_LINUX64INTEL)

   endif(SHEAFSYSTEM_ENABLE_COVERAGE)

endfunction(SheafSystem_set_coverage_defaults)


#
# Create the build output directories.
#
function(SheafSystem_create_output_dirs)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   # Create directory for scoped header files.

   file(MAKE_DIRECTORY ${SHEAFSYSTEM_HEADER_DIR})

   # Create directory for documentation files.

   file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/documentation)
   
   # Visual Studio will generate cmake_build_dir folders for the current build type.
   # Linux needs to be told.

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin PARENT_SCOPE)

      # Create build/lib for libraries.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

      # Create build/bin for executables.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)        

   elseif(SHEAFSYSTEM_LINUX)

      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin PARENT_SCOPE)
      
      # Create build/lib for libraries.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
      
      # Create build/bin for executables.

      file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)        

   endif(SHEAFSYSTEM_WINDOWS)

endfunction(SheafSystem_create_output_dirs)

#
# Adds components to the system.
#
function(SheafSystem_add_components)

   set(lcomponents sheaves fiber_bundles geometry fields tools)

   foreach(comp ${lcomponents})
      add_subdirectory(${comp})
   endforeach()

endfunction(SheafSystem_add_components)

#
# Set /MP option in CMAKE_CXX_FLAGS_<xconfig>
#
function(SheafSystem_set_mp_option xconfig)

   # Make a copy of CMAKE_CXX_FLAGS_<xconfig> variable without /MP

   string(TOUPPER ${xconfig} LCONFIG_UC)
   string(REPLACE "/MP " " " tmp "${CMAKE_CXX_FLAGS_${LCONFIG_UC}}")

   if(SHEAFSYSTEM_ENABLE_WIN32_MP)

      # Add the /MP option

      set(tmp "/MP ${tmp}")
         
   endif()

   # Store the result in CMAKE_CXX_FLAGS_<xconfig>.   
   
   set(CMAKE_CXX_FLAGS_${LCONFIG_UC} ${tmp}
      CACHE STRING "Flags used by the C++ compiler for ${xconfig} builds"  FORCE)

endfunction(SheafSystem_set_mp_option xconfig)

#
# Set the compiler flags per build configuration
#
function(SheafSystem_set_compiler_flags)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:
   
   # Toggle multi-process compilation in Windows

   if(SHEAFSYSTEM_ENABLE_WIN32_MP)
      set(MP "/MP")
   else()
      set(MP "")
   endif()
   
   if(SHEAFSYSTEM_WIN64MSVC)

      # Windows with MS Visual C++ compiler.

      set(SHEAFSYSTEM_CXX_FLAGS "${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /EHsc" 
         CACHE STRING "C++ Compiler Flags")

      set(SHEAFSYSTEM_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /MACHINE:X64"
         CACHE STRING "Linker Flags for Shared Libs")

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /SUBSYSTEM:CONSOLE /MACHINE:X64" 
         CACHE STRING "Linker Flags for Executables")

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG "/DEBUG" CACHE STRING "Debug Linker Flags" FORCE)

   elseif(SHEAFSYSTEM_WIN64INTEL)

      # Windows with Intel compiler.

      set(SHEAFSYSTEM_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /wd2651 /EHsc /Qprof-gen:srcpos /D_HDF5USEDLL_" 
         CACHE STRING "C++ Compiler Flags")

      set(SHEAFSYSTEM_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /NXCOMPAT /MACHINE:X64" 
         CACHE STRING "Linker Flags") 

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )

   elseif(SHEAFSYSTEM_LINUX64INTEL)

      # Linux with Intel compiler.

      if(SHEAFSYSTEM_ENABLE_COVERAGE)
         if(INTELWARN)
            set(SHEAFSYSTEM_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated -prof-gen=srcpos")
         else()
            set(SHEAFSYSTEM_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated  -prof-gen=srcpos")
         endif()
      else()
         if(INTELWARN)
            set(SHEAFSYSTEM_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ")
         else()
            set(SHEAFSYSTEM_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ")
         endif()
      endif(SHEAFSYSTEM_ENABLE_COVERAGE)

      set(SHEAFSYSTEM_SHARED_LINKER_FLAGS CACHE STRING "Linker Flags") 

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )
        
   elseif(SHEAFSYSTEM_LINUX64GNU)

      # Linux with g++ compiler.

      # 12/20/13 -- added "-Wno-abi to suppress the following:
      #"SheafSystem/sheaves/support/primitive_attributes.h:115: 
      #note: The ABI of passing union with long double has changed in GCC 4.4"
      # The probrem is still there; we have only suppressed the warning.

      set(SHEAFSYSTEM_CXX_FLAGS "-std=c++11 -m64 -Wno-deprecated -Wno-abi") 

      set(SHEAFSYSTEM_SHARED_LINKER_FLAGS CACHE STRING "Linker Flags") 

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS CACHE STRING "Linker Flags for Executables")

      set(SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG CACHE STRING "Debug Linker Flags" )

   endif()

   mark_as_advanced(FORCE SHEAFSYSTEM_CXX_FLAGS SHEAFSYSTEM_SHARED_LINKER_FLAGS SHEAFSYSTEM_EXE_LINKER_FLAGS SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG)

   
   # Configuration specific flags 

   #                 
   # DEBUG_CONTRACTS section
   #

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} /Zi /D\"_ITERATOR_DEBUG_LEVEL=2\" /MDd /LDd /Od " 
         CACHE STRING "Flags used by the C++ compiler for Debug_contracts builds" )
      SheafSystem_set_mp_option(Debug_contracts)

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRT" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_contracts linker flags - binding libs" )

   elseif(SHEAFSYSTEM_LINUX) 

      set(CMAKE_CXX_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} -g " 
         CACHE STRING "Flags used by the C++ compiler for Debug_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} " 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS ${CMAKE_EXE_LINKER_FLAGS}  
         CACHE STRING "Flags used by the linker for executables for Debug_contracts builds")

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_contracts linker flags - binding libs" )

   endif(SHEAFSYSTEM_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_DEBUG_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_DEBUG_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_DEBUG_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_DEBUG_CONTRACTS)

   #                 
   # DEBUG_NO_CONTRACTS section
   #      

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} /Zi /D\"_ITERATOR_DEBUG_LEVEL=2\" /MDd /LDd /Od /DNDEBUG " 
         CACHE STRING "Flags used by the C++ compiler for Debug_no_contracts builds" )
      SheafSystem_set_mp_option(Debug_no_contracts)

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRT" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_no_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_no_contracts linker flags - binding libs" )

   elseif(SHEAFSYSTEM_LINUX)

      set(CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} -g -DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Debug_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Debug_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for Debug_no_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Debug_no_contracts linker flags - binding libs" )

   endif(SHEAFSYSTEM_WINDOWS)

   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_DEBUG_NO_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_DEBUG_NO_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_DEBUG_NO_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_DEBUG_NO_CONTRACTS)
   
   #                 
   # RELEASE_CONTRACTS section
   #

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS}  /MD /LD /O2 " 
         CACHE STRING "Flags used by the C++ compiler for Release_contracts builds" )
      SheafSystem_set_mp_option(Release_contracts)

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" 
         CACHE STRING "Flags used by the linker for executables for Release_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_contracts linker flags - binding libs" )

   elseif(SHEAFSYSTEM_LINUX)

      set(CMAKE_CXX_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} " 
         CACHE STRING "Flags used by the C++ compiler for Release_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_EXE_LINKER_FLAGS}"  
         CACHE STRING "Flags used by the linker for executables for Release_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_contracts linker flags - binding libs" )

   endif(SHEAFSYSTEM_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_RELEASE_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_RELEASE_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_RELEASE_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_RELEASE_CONTRACTS)
   
   #                 
   # RELEASE_NO_CONTRACTS section
   #

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS}  /MD /LD /O2 /DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Release_no_contracts builds" )
      SheafSystem_set_mp_option(Release_no_contracts)

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD  /NXCOMPAT" 
         CACHE STRING "Flags used by the linker for executables for Release_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_no_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_no_contracts linker flags - binding libs" )

   elseif(SHEAFSYSTEM_LINUX)

      set(CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS}  -DNDEBUG" 
         CACHE STRING "Flags used by the C++ compiler for Release_no_contracts builds" )

      set(CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for executables for Release_no_contracts builds" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Flags used by the linker for shared libraries for Release_no_contracts builds" )

      set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS}" 
         CACHE STRING "Release_no_contracts linker flags - binding libs" )

   endif(SHEAFSYSTEM_WINDOWS)
   
   mark_as_advanced(FORCE 
      CMAKE_CXX_FLAGS_RELEASE_NO_CONTRACTS
      CMAKE_EXE_LINKER_FLAGS_RELEASE_NO_CONTRACTS 
      CMAKE_SHARED_LINKER_FLAGS_RELEASE_NO_CONTRACTS
      CMAKE_MODULE_LINKER_FLAGS_RELEASE_NO_CONTRACTS)

   #                 
   # RelWithDebInfo_contracts section; Windows only.
   #

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} /MD /LD /O2 " 
         CACHE STRING "RelWithDebInfo_contracts compiler flags" )
      SheafSystem_set_mp_option(Relwithdebinfo_contracts)

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHEAFSYSTEM_EXE_LINKER_FLAGS} /DEBUG /NODEFAULTLIB:MSVCRTD  /NXCOMPAT"
         CACHE STRING "RelWithDebInfo_contracts linker flags - executables" )

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS  "${CMAKE_EXE_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for RelWithDebInfo_contracts builds" FORCE)

      set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - binding libs" )

      set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - shared libs" ) 
      
      mark_as_advanced(FORCE 
         CMAKE_CXX_FLAGS_RELWITHDEBINFO_CONTRACTS
         CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS 
         CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS
         CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_CONTRACTS)

   endif(SHEAFSYSTEM_WINDOWS)
   
   #                 
   # RelWithDebInfo_no_contracts section; Windows only.
   #

   if(SHEAFSYSTEM_WINDOWS)

      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHEAFSYSTEM_CXX_FLAGS} /MD /LD /O2 /DNDEBUG" CACHE
         STRING "RelWithDebInfo_no_contracts compiler flags" )
      SheafSystem_set_mp_option(Relwithdebinfo_no_contracts)

      set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "Flags used by the linker for executables for RelWithDebInfo_no_contracts builds" FORCE)

      set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - shared libs" ) 

      set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS "${SHEAFSYSTEM_SHARED_LINKER_FLAGS} ${SHEAFSYSTEM_EXE_LINKER_FLAGS_DEBUG}" 
         CACHE STRING "RelWithDebInfo_contracts linker flags - binding libs" )
      
      mark_as_advanced(FORCE 
         CMAKE_CXX_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
         CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS 
         CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS
         CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO_NO_CONTRACTS)

   endif(SHEAFSYSTEM_WINDOWS)
   
endfunction(SheafSystem_set_compiler_flags)

#
# Generate and install the CMake standard configuration files. 
#
function(SheafSystem_generate_install_config_files)

   # message("Entering system_definition.cmake:generate_install_config_files")

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   #
   # Generate and install the build tree config file.
   #
   include (CMakePackageConfigHelpers)

   set(SHEAFSYSTEM_CONFIG_NAME "SheafSystemConfig.cmake")
   set(SHEAFSYSTEM_VERSION_NAME "SheafSystemVersion.cmake")
   set(SHEAFSYSTEM_CONFIG_INSTALL_DIR "cmake")

   if(SHEAFSYSTEM_WINDOWS)

      # SHEAFSYSTEM_LIB_INSTALL_DIR exported for use in set_env_var scripts.
      
      set(SHEAFSYSTEM_LIB_INSTALL_DIR "lib")      
      set(SHEAFSYSTEM_BIN_INSTALL_DIR "bin")

      configure_package_config_file (
         ${SHEAFSYSTEM_CMAKE_MODULE_PATH}/Windows.${SHEAFSYSTEM_CONFIG_NAME}.in
         "${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_CONFIG_NAME}"
         INSTALL_DESTINATION "${SHEAFSYSTEM_CONFIG_INSTALL_DIR}"
         PATH_VARS SHEAFSYSTEM_CONFIG_INSTALL_DIR SHEAFSYSTEM_LIB_INSTALL_DIR SHEAFSYSTEM_BIN_INSTALL_DIR)

   elseif(SHEAFSYSTEM_LINUX)

      # SHEAFSYSTEM_LIB_INSTALL_DIR exported for use in set_env_var scripts.
      
      set(SHEAFSYSTEM_LIB_INSTALL_DIR "${CMAKE_BUILD_TYPE}/lib")

      configure_package_config_file (
         ${SHEAFSYSTEM_CMAKE_MODULE_PATH}/Linux.${SHEAFSYSTEM_CONFIG_NAME}.in
         "${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_CONFIG_NAME}"
         INSTALL_DESTINATION "${SHEAFSYSTEM_CONFIG_INSTALL_DIR}"
         PATH_VARS SHEAFSYSTEM_CONFIG_INSTALL_DIR SHEAFSYSTEM_LIB_INSTALL_DIR)

   endif()

   write_basic_package_version_file(
      "${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_VERSION_NAME}"
      VERSION ${SHEAFSYSTEM_LIB_VERSION}
      COMPATIBILITY AnyNewerVersion)

   #
   # Generate and install the build tree targets file.
   #

   export(EXPORT ${SHEAFSYSTEM_EXPORT_NAME} FILE ${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_EXPORT_NAME}.cmake)

   #
   # Generate and install the installation tree config and targets files.
   #
   install(FILES 
      "${CMAKE_BINARY_DIR}/${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_CONFIG_NAME}"
      "${CMAKE_BINARY_DIR}/${SHEAFSYSTEM_CONFIG_INSTALL_DIR}/${SHEAFSYSTEM_VERSION_NAME}"
      DESTINATION ${SHEAFSYSTEM_CONFIG_INSTALL_DIR})
   install(EXPORT ${SHEAFSYSTEM_EXPORT_NAME} DESTINATION ${SHEAFSYSTEM_CONFIG_INSTALL_DIR})

   # message("Leaving system_definition.cmake:generate_install_config_files")

endfunction(SheafSystem_generate_install_config_files)

# 
# Install documentation
#
function(SheafSystem_install_documentation)

   install(DIRECTORY ${CMAKE_BINARY_DIR}/documentation/ DESTINATION documentation)
   install(DIRECTORY ${SHEAFSYSTEM_CMAKE_MODULE_PATH}/css DESTINATION documentation)
   install(DIRECTORY ${SHEAFSYSTEM_CMAKE_MODULE_PATH}/images DESTINATION documentation)
   
endfunction(SheafSystem_install_documentation)


# 
# Install any prerequisites that need to ship with our libs
#
function(SheafSystem_install_prereqs)
   # Prerequisite components install
   # Install only the HDF includes we use 
   foreach(inc ${HDF5_INCS})
      install(FILES ${HDF5_INCLUDE_DIR}/${inc}
         DESTINATION include/${SHEAFSYSTEM_HEADER_SCOPE}
         PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
   endforeach()
   
endfunction(SheafSystem_install_prereqs)

# 
# Get the current system date and store it in RESULT
#
macro(get_date RESULT)
   if(WIN32)
      execute_process(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE ${RESULT})
      string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}})
   elseif(UNIX)
      execute_process(COMMAND "date" "+%m/%d/%Y" OUTPUT_VARIABLE ${RESULT})
      string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}})
   else(WIN32)
      message(WARNING "date not implemented")
      set(${RESULT} 000000)
   endif(WIN32)
endmacro(get_date)

function(SheafSystem_install_release_notes)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   #
   # Markup the RELEASE_NOTES file. 
   #
   set(RELEASE_DATE)
   get_date(RELEASE_DATE)

   #
   # Generate some info about the release
   #
   file(WRITE ${CMAKE_BINARY_DIR}/VERSION "SheafSystem version ${SHEAFSYSTEM_LIB_VERSION} ${RELEASE_DATE}  \n")
   install(FILES ${CMAKE_BINARY_DIR}/VERSION DESTINATION ${CMAKE_INSTALL_PREFIX})

   configure_file(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/RELEASE_NOTES.cmake.in ${CMAKE_BINARY_DIR}/RELEASE_NOTES)

   if(SHEAFSYSTEM_WINDOWS)
      install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX} RENAME RELEASE_NOTES.txt)
   elseif(SHEAFSYSTEM_LINUX)
      install(FILES ${CMAKE_BINARY_DIR}/RELEASE_NOTES DESTINATION ${CMAKE_INSTALL_PREFIX})
   endif()

endfunction(SheafSystem_install_release_notes)

function(SheafSystem_make_system_definitions)

   SheafSystem_set_system_variable_defaults()
   SheafSystem_set_platform_variables()
   SheafSystem_set_compiler_flags()
   SheafSystem_set_system_install_location_default()
   SheafSystem_set_debug_configuration()
   SheafSystem_set_default_build_type()
   SheafSystem_set_coverage_defaults()

   if(SHEAFSYSTEM_WINDOWS)
      #
      # Install the Windows Runtime libs
      #
      # $$ISSUE: This call was previously the first thing in this file.
      # It combines find functions with install functions, not clear where to put it.
      #
      include(InstallRequiredSystemLibraries)
   endif()

   include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/find_prerequisites.cmake)
   SheafSystem_find_prerequisites()

endfunction(SheafSystem_make_system_definitions)

# 
# Convenience wrapper for the message function.
# The Eclipse Cmakeed plugin renders this pretty much obsolete
# from a pregramming viewpoint, but the syntax is prettier
# than what it wraps.
#
function(SheafSystem_status_message txt)

   # Let the user know what's being configured
   message(STATUS " ")
   message(STATUS "${txt} - ")
   message(STATUS " ")

endfunction(SheafSystem_status_message)
