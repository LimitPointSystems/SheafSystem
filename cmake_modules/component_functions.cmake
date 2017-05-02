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


#------------------------------------------------------------------------------
# Functions called from <component>/CMakeLists.txt.
#------------------------------------------------------------------------------

#
# Add the list of clusters to this component.
#
function(SheafSystem_add_clusters clusters)

   foreach(cluster ${clusters})

      #Add each cluster subdir to the project. 

      add_subdirectory(${cluster})

   endforeach()

endfunction(SheafSystem_add_clusters)

#
# Construct the list of include paths for xclusters.
#
function(SheafSystem_set_component_ipath_variable xcomponent_name xclusters)

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   set(lipath)
   foreach(cluster ${xclusters})

      # Add the fully-qualified cluster names to this component's ipath var

      set(lipath ${lipath} ${CMAKE_CURRENT_SOURCE_DIR}/${cluster})

   endforeach()

   set(${LCOMP_NAME_UC}_IPATH ${lipath} CACHE STRING "Include paths for ${xcomponent_name}" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_IPATH)

endfunction(SheafSystem_set_component_ipath_variable)

# 
# Declare and initialize all variables that are component-specific.
#
function(SheafSystem_set_component_variables xcomponent_name)

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   # Source collection variables.

   set(${LCOMP_NAME_UC}_SRCS CACHE STRING "${lcomp_name_lc} sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SRCS)

   set(${LCOMP_NAME_UC}_INCS CACHE STRING "${lcomp_name_lc} includes" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_INCS)

   set(${LCOMP_NAME_UC}_UNIT_TEST_SRCS CACHE STRING "${lcomp_name_lc} unit test sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_UNIT_TEST_SRCS)

   set(${LCOMP_NAME_UC}_EXAMPLE_SRCS CACHE STRING "${lcomp_name_lc} example sources" FORCE)
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_EXAMPLE_SRCS)

   # Library variables.

   if(SHEAFSYSTEM_WINDOWS)

      set(${LCOMP_NAME_UC}_DYNAMIC_LIB ${lcomp_name_lc} 
         CACHE STRING "${lcomp_name_lc} dynamic link library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_DYNAMIC_LIB)

      set(${LCOMP_NAME_UC}_IMPORT_LIB ${lcomp_name_lc}
         CACHE STRING "${lcomp_name_lc} import library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_IMPORT_LIB)

      set(${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY ${lcomp_name_lc}_csharp_assembly.dll 
         CACHE STRING "${lcomp_name_lc} csharp binding assembly name")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY)   

   elseif(SHEAFSYSTEM_LINUX)

      set(${LCOMP_NAME_UC}_SHARED_LIB lib${lcomp_name_lc}.so 
         CACHE STRING "${lcomp_name_lc} shared library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SHARED_LIB)

      set(${LCOMP_NAME_UC}_STATIC_LIB lib${lcomp_name_lc}.a 
         CACHE STRING "${lcomp_name_lc} static library")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_STATIC_LIB)

      set(${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY ${lcomp_name_lc}_csharp_assembly.so 
         CACHE STRING "${lcomp_name_lc} csharp binding assembly name")
      mark_as_advanced(FORCE ${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY)   

   endif(SHEAFSYSTEM_WINDOWS)
   
   set(${LCOMP_NAME_UC}_COMMON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/src 
      CACHE STRING "${lcomp_name_lc} common binding source directory")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_COMMON_BINDING_SRC_DIR)

   # Swig variables

   set(${LCOMP_NAME_UC}_SWIG_COMMON_INTERFACE ${lcomp_name_lc}_common_binding.i 
      CACHE STRING "${lcomp_name_lc} common interface filename")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SWIG_COMMON_INTERFACE)

   set(${LCOMP_NAME_UC}_SWIG_COMMON_INCLUDES_INTERFACE ${lcomp_name_lc}_common_binding_includes.i 
      CACHE STRING "${lcomp_name_lc} common includes interface filename" )
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SWIG_COMMON_INCLUDES_INTERFACE)

   # Java binding variables.
   
   set(${LCOMP_NAME_UC}_JAVA_BINDING_LIB ${lcomp_name_lc}_java_binding 
      CACHE STRING "${lcomp_name_lc} java binding library basename")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_JAVA_BINDING_LIB)

   set(${LCOMP_NAME_UC}_JAVA_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/java/src 
      CACHE STRING "${lcomp_name_lc} java binding source directory")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_JAVA_BINDING_SRC_DIR)

   set(${LCOMP_NAME_UC}_SWIG_JAVA_INTERFACE ${lcomp_name_lc}_java_binding.i 
      CACHE STRING "${lcomp_name_lc} java binding interface file")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SWIG_JAVA_INTERFACE)

   set(${LCOMP_NAME_UC}_JAVA_BINDING_JAR ${lcomp_name_lc}_java_binding.jar 
      CACHE STRING "${lcomp_name_lc} java binding jar name")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_JAVA_BINDING_JAR)

   # Python binding variables.

   set(${LCOMP_NAME_UC}_PYTHON_BINDING_LIB ${lcomp_name_lc}_python_binding 
      CACHE STRING "${lcomp_name_lc} python binding library name")    
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_PYTHON_BINDING_LIB)

   set(${LCOMP_NAME_UC}_PYTHON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/python/src 
      CACHE STRING "${lcomp_name_lc} python source directory")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_PYTHON_BINDING_SRC_DIR)

   set(${LCOMP_NAME_UC}_SWIG_PYTHON_INTERFACE ${lcomp_name_lc}_python_binding.i 
      CACHE STRING "${lcomp_name_lc} python binding interface file")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SWIG_PYTHON_INTERFACE)

   # CSharp binding variables.
  
   set(${LCOMP_NAME_UC}_CSHARP_BINDING_LIB ${lcomp_name_lc}_csharp_binding 
      CACHE STRING "${lcomp_name_lc} csharp binding library name")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_CSHARP_BINDING_LIB)

   set(${LCOMP_NAME_UC}_CSHARP_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/csharp/src 
      CACHE STRING "${lcomp_name_lc} csharp source directory")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_CSHARP_BINDING_SRC_DIR)

   set(${LCOMP_NAME_UC}_SWIG_CSHARP_INTERFACE ${lcomp_name_lc}_csharp_binding.i 
      CACHE STRING "${lcomp_name_lc} csharp binding interface file")
   mark_as_advanced(FORCE ${LCOMP_NAME_UC}_SWIG_CSHARP_INTERFACE)   
   
endfunction(SheafSystem_set_component_variables)

#------------------------------------------------------------------------------
# Functions called from <cluster>/CMakeLists.txt.
#------------------------------------------------------------------------------

#
# Append the sources in xsrcs to <xcomponent_name>_SRCS
# Used in cluster level CMakeLists.txt
#
function(SheafSystem_collect_sources xcomponent_name xsrcs)

   # Prepend the cluster name to each member of the srcs list

   set(lsrcs)
   foreach(src ${xsrcs})
      list(APPEND lsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()
   
   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_SRCS ${${LCOMP_NAME_UC}_SRCS} ${lsrcs} 
      CACHE STRING "${xcomponent_name} sources." FORCE)

endfunction(SheafSystem_collect_sources)

#
# Append incs to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(SheafSystem_collect_includes xcomponent_name xsrcs xadditional_incs)

   get_filename_component(CLUSTERNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

   # Prepend the cluster name to each member of the srcs list

   set(lincs)
   if(NOT ${CLUSTERNAME} STREQUAL "template_instantiations")
      foreach(src ${xsrcs})
         string(REGEX REPLACE ".cc$" ".h"  inc ${src})
         list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
      endforeach()
   endif()
   
   # Prepend the cluster name to each member of the additional_incs list

   foreach(inc ${xadditional_incs})
      list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
   endforeach()

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_INCS ${${LCOMP_NAME_UC}_INCS} ${lincs} 
      CACHE STRING "${xcomponent_name} includes." FORCE)

endfunction(SheafSystem_collect_includes)

#
# Append unit test executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(SheafSystem_collect_unit_test_sources xcomponent_name xunit_test_srcs)

   # Prepend the path to each member of the unit test srcs list

   set(chksrcs)
   foreach(src ${xunit_test_srcs})
      list(APPEND chksrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()
   
   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_UNIT_TEST_SRCS ${${LCOMP_NAME_UC}_UNIT_TEST_SRCS} ${chksrcs} 
      CACHE STRING "Unit test sources." FORCE)
   
endfunction(SheafSystem_collect_unit_test_sources)

#
# Append standalone executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(SheafSystem_collect_example_sources xcomponent_name xexample_srcs)

   # Prepend the path to each member of the execs list

   set(execsrcs)
   foreach(src ${xexample_srcs})
      list(APPEND execsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
   endforeach()

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)

   set(${LCOMP_NAME_UC}_EXAMPLE_SRCS ${${LCOMP_NAME_UC}_EXAMPLE_SRCS} ${execsrcs} 
      CACHE STRING "EXEC sources." FORCE)

endfunction(SheafSystem_collect_example_sources)

#------------------------------------------------------------------------------
# Functions called from <component>/component_definitions.cmake.
#------------------------------------------------------------------------------

function(SheafSystem_add_component_install_target xcomponent_name)

   # message("Entering SheafSystem_add_component_install_target")

   # Preconditions:

   dbc_require_or(SHEAFSYSTEM_WINDOWS SHEAFSYSTEM_LINUX)

   # Body:

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} lcomp_name_lc)

   if(SHEAFSYSTEM_LINUX)

      install(TARGETS ${${LCOMP_NAME_UC}_SHARED_LIB} ${${LCOMP_NAME_UC}_STATIC_LIB}
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
         ARCHIVE DESTINATION ${CMAKE_BUILD_TYPE}/lib
         LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      if(SHEAFSYSTEM_BUILD_BINDINGS)

         install(TARGETS ${${LCOMP_NAME_UC}_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${LCOMP_NAME_UC}_JAVA_BINDING_JAR} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)  

         install(TARGETS ${${LCOMP_NAME_UC}_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(TARGETS ${${LCOMP_NAME_UC}_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib) 

      endif()
      
   elseif(SHEAFSYSTEM_WINDOWS)

      # Install the component libs.
      
      install(TARGETS ${${LCOMP_NAME_UC}_IMPORT_LIB}
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
         ARCHIVE
         DESTINATION lib/$<CONFIG>)

      # The dynmaic library is not directly referred to by clients,
      # so it is not an exported target.
      
      install(TARGETS ${${LCOMP_NAME_UC}_DYNAMIC_LIB}
         RUNTIME
         DESTINATION bin/$<CONFIG>)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_DYNAMIC_LIB}_d.pdb 
         DESTINATION bin/$<CONFIG> 
         OPTIONAL)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_DYNAMIC_LIB}.pdb 
         DESTINATION bin/$<CONFIG> 
         OPTIONAL)
      
      if(SHEAFSYSTEM_BUILD_BINDINGS)

         # Install the component java bindings libs.
         
         install(TARGETS ${${LCOMP_NAME_UC}_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)
         
         install(TARGETS ${${LCOMP_NAME_UC}_JAVA_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_JAVA_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_JAVA_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_JAVA_BINDING_JAR} 
            DESTINATION lib/$<CONFIG>)  

         # Install the component csharp bindings libs
         
         install(TARGETS ${${LCOMP_NAME_UC}_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${${LCOMP_NAME_UC}_CSHARP_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_CSHARP_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_CSHARP_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_CSHARP_BINDING_ASSY} 
            DESTINATION bin/$<CONFIG>) 

         # Install component python bindings libs.
         
         install(TARGETS ${${LCOMP_NAME_UC}_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${${LCOMP_NAME_UC}_PYTHON_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         
         
         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_PYTHON_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${${LCOMP_NAME_UC}_PYTHON_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 
         
      endif()
   endif()

   install(FILES ${${LCOMP_NAME_UC}_INCS} DESTINATION include/${SHEAFSYSTEM_HEADER_SCOPE}) 

   # message("Leaving SheafSystem_add_component_install_target")
   
endfunction(SheafSystem_add_component_install_target)


# Function to create target to create copies of header files with path ${SHEAFSYSTEM_HEADER_SCOPE}/*.h,
# so uniquely scoped paths in include directives will work.
# Note: can't use copy_if_different command with multiple input files
# directly in add_custom_target because fails on Windows, apparently
# due to error in copy_if_different dealing with long lists

function(SheafSystem_add_component_scoped_headers_target xcomponent_name)

   string(TOUPPER ${xcomponent_name} LCOMP_NAME_UC)
   string(TOLOWER ${xcomponent_name} LCOMP_NAME_LC)

   set(all_scoped_hdrs)
   foreach(hdr_path ${${LCOMP_NAME_UC}_INCS})

      get_filename_component(hdr_file ${hdr_path} NAME)

      add_custom_command(OUTPUT ${SHEAFSYSTEM_HEADER_DIR}/${hdr_file}
         COMMAND ${CMAKE_COMMAND} -E copy_if_different ${hdr_path} ${SHEAFSYSTEM_HEADER_DIR}
         DEPENDS ${hdr_path}
         )

      list(APPEND all_scoped_hdrs ${SHEAFSYSTEM_HEADER_DIR}/${hdr_file})

   endforeach()

   add_custom_target(${LCOMP_NAME_LC}_scoped_headers DEPENDS ${all_scoped_hdrs} )

endfunction(SheafSystem_add_component_scoped_headers_target)


#------------------------------------------------------------------------------
# Misc functions
#------------------------------------------------------------------------------

#
# Return string with backslash path separators escaped
# e.g., "c:\my\files" is returned "c:\\my\\files"
# Usage :
#    set(VAR "c:\my\files" )
#    esc_backslash(VAR)
#
macro(esc_backslash RESULT)
   if(WIN32)
      string(REPLACE "\\" "\\\\" RESULT "${RESULT}")
   endif()
endmacro(esc_backslash RESULT)

#
# Query git for the info regarding this repository.
#
function(SheafSystem_get_repository_info)

   #
   # Get the current branch tag from git
   #
   execute_process(
      COMMAND git rev-parse --abbrev-ref HEAD 
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE TAG
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   set(GIT_TAG ${TAG} CACHE STRING "Name of this git branch" FORCE)
   
   #
   # Get the hash associated with this branch
   #
   execute_process(
      COMMAND git rev-parse ${GIT_TAG}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   set(GIT_HASH ${HASH} CACHE STRING "Hash for this git branch" FORCE)

endfunction(SheafSystem_get_repository_info)
