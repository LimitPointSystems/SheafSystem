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
# This file contains declarations and functions unique to this component.
#

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------
 
#
# Set some cumulative variables; not entirely clear these are necessary.
#
function(SheafSystem_set_cumulative_fields_variables)

   #
   # Set the cumulative include path for this component.
   #
   set(FIELDS_IPATHS ${GEOMETRY_IPATHS} ${FIELDS_IPATH} 
      CACHE STRING " Cumulative include paths for fields component")
   mark_as_advanced(FORCE FIELDS_IPATHS)

endfunction(SheafSystem_set_cumulative_fields_variables)


#
# Create the library targets for this component.
#
function(SheafSystem_add_fields_library_targets)

   # message("Entering fields/component_defintions::SheafSystem_add_fields_library_target")

   # We'll need to use generator expression to configure include directories differently
   # for build and installation. Have to escape ";" in BUILD_INTERFACE 
   # generator expression, otherwise it inserts the current source directory 
   # just before the expression. Go figure.

   string(REPLACE ";" "\;" _lps_escaped_paths "${FIELDS_IPATH}" )
   # message("_lps_escaped_paths=${_lps_escaped_paths}")

   # Target to create copies of header files with path ${SHEAFSYSTEM_HEADER_SCOPE}/*.h,
   # so uniquely scoped paths in include directives with work.

   add_custom_target(fields_scoped_headers
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FIELDS_INCS} ${SHEAFSYSTEM_HEADER_DIR})

   if(SHEAFSYSTEM_WINDOWS)

      # Windwos.

      # Tell the linker where to look for this project's libraries.
      # $$ISSUE: shouldn't be necessary.
      #link_directories(${FIELDS_OUTPUT_DIR})
      
      add_library(${FIELDS_DYNAMIC_LIB} SHARED ${FIELDS_SRCS})
      add_dependencies(${FIELDS_DYNAMIC_LIB} ${GEOMETRY_IMPORT_LIB})
      add_dependencies(${FIELDS_DYNAMIC_LIB} fields_scoped_headers)
      target_include_directories(${FIELDS_DYNAMIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIELDS_DYNAMIC_LIB} ${GEOMETRY_IMPORT_LIB} )        
      set_target_properties(${FIELDS_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")   

      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.

      set_target_properties(${FIELDS_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

      # Add a Win32 "lib" target
      # Doing it here makes it a synonym for "Fields", but abstracts away
      # the component hierarchy.
      add_custom_target(lib)
      add_dependencies(lib ${FIELDS_IMPORT_LIB})
      set_target_properties(lib PROPERTIES FOLDER "Library Targets")    

   else() 

      # Linux
      
      # Static library

      add_library(${FIELDS_STATIC_LIB} STATIC ${FIELDS_SRCS})
      add_dependencies(${FIELDS_STATIC_LIB} ${GEOMETRY_STATIC_LIB})
      add_dependencies(${FIELDS_STATIC_LIB} fields_scoped_headers)
      target_include_directories(${FIELDS_STATIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIELDS_STATIC_LIB} ${GEOMETRY_STATIC_LIB}) 
      set_target_properties(${FIELDS_STATIC_LIB} PROPERTIES OUTPUT_NAME fields)
      
      # Shared library

      add_library(${FIELDS_SHARED_LIB} SHARED ${FIELDS_SRCS})
      add_dependencies(${FIELDS_SHARED_LIB} ${GEOMETRY_SHARED_LIB})
      add_dependencies(${FIELDS_SHARED_LIB} fields_scoped_headers)
      target_include_directories(${FIELDS_SHARED_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIELDS_SHARED_LIB} ${GEOMETRY_SHARED_LIB}) 
      set_target_properties(${FIELDS_SHARED_LIB} PROPERTIES OUTPUT_NAME fields)
      set_target_properties(${FIELDS_SHARED_LIB} PROPERTIES LINKER_LANGUAGE CXX)
      set_target_properties(${FIELDS_SHARED_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION}) 
      
      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
      # CMake apparently detects the presence of cdecl_dllspec in the source and places
      # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.

      set_target_properties(${FIELDS_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
      
      # Library alias definitions

      add_custom_target(fields-static-lib)
      add_dependencies(fields-static-lib ${FIELDS_STATIC_LIB})      

      add_custom_target(fields-shared-lib)
      add_dependencies(fields-shared-lib ${FIELDS_SHARED_LIB})

   endif()

   # message("Leaving fields/component_defintions::SheafSystem_add_fields_library_target")

endfunction(SheafSystem_add_fields_library_targets)

#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fields_java_bindings_targets)

   # Preconditions:

   # Requires swig and java to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_JAVA)
   dbc_require(SHEAFSYSTEM_FOUND_JNI)

   # Also requires geometry java bindings, not sure how to require that.

   dbc_unexecutable_require("geometry java bindings")

   include_directories(${FIELDS_IPATHS})
   include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
   include_directories(${SHEAVES_JAVA_BINDING_SRC_DIR})
   include_directories(${SHEAVES_COMMON_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_COMMON_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_JAVA_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_COMMON_BINDING_SRC_DIR})
   include_directories(${FIELDS_JAVA_BINDING_SRC_DIR})
   include_directories(${FIELDS_COMMON_BINDING_SRC_DIR})

   
   set_source_files_properties(${FIELDS_JAVA_BINDING_SRC_DIR}/${FIELDS_SWIG_JAVA_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)
   
   set(SWIG_CXX_EXTENSION "cxx")
   set(CMAKE_SWIG_FLAGS -package bindings.java)

   # Add the java binding library target

   swig_add_module(${FIELDS_JAVA_BINDING_LIB} java 
      ${FIELDS_JAVA_BINDING_SRC_DIR}/${FIELDS_SWIG_JAVA_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${FIELDS_JAVA_BINDING_LIB} ${GEOMETRY_JAVA_BINDING_LIB} ${FIELDS_IMPORT_LIB})

      swig_link_libraries(${FIELDS_JAVA_BINDING_LIB}
         PUBLIC ${GEOMETRY_JAVA_BINDING_LIB} ${FIELDS_IMPORT_LIB}
         PRIVATE hdf5-static)

      set_target_properties(${FIELDS_JAVA_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Java")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIELDS_JAVA_BINDING_LIB} ${GEOMETRY_JAVA_BINDING_LIB} ${FIELDS_SHARED_LIB})

      target_link_libraries(${FIELDS_JAVA_BINDING_LIB}
         ${GEOMETRY_JAVA_BINDING_LIB} ${FIELDS_SHARED_LIB})

   endif()
   
   set_target_properties(${FIELDS_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
   
   # Define the library version.

   set_target_properties(${FIELDS_JAVA_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})     

   # Create the bindings jar file 

   if(SHEAFSYSTEM_WINDOWS)

      # Windows.

      set(FIELDS_CLASSPATH 
         ${GEOMETRY_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIELDS_JAVA_BINDING_JAR} 
         CACHE STRING "Cumulative classpath for fields" FORCE)
      mark_as_advanced(FORCE FIELDS_CLASSPATH) 

      add_custom_target(fields_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${GEOMETRY_CLASSPATH}" -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIELDS_JAVA_BINDING_JAR}  
            bindings/java/*.class
         )
      
      add_dependencies(fields_java_binding.jar ${FIELDS_JAVA_BINDING_LIB} ${GEOMETRY_JAVA_BINDING_JAR})

      set_target_properties(fields_java_binding.jar PROPERTIES FOLDER "Component Binding Jars")

      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(fields-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle "fields documentation" 
               -classpath "${GEOMETRY_CLASSPATH}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/fields  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(fields-java-docs ${FIELDS_JAVA_BINDING_JAR})

         set_target_properties(fields-java-docs PROPERTIES FOLDER "Documentation Targets")

      endif(SHEAFSYSTEM_DOC_TARGETS)            

   else(SHEAFSYSTEM_WINDOWS)
      
      # Linux

      set(FIELDS_CLASSPATH 
         ${GEOMETRY_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIELDS_JAVA_BINDING_JAR} 
         CACHE STRING "Cumulative classpath for fields" FORCE)
      mark_as_advanced(FORCE FIELDS_CLASSPATH) 

      # The default list item separator in cmake is ";". If Linux, then exchange ";" for  the UNIX style ":"
      # and store the result in parent_classpath.

      string(REGEX REPLACE ";" ":" parent_classpath "${GEOMETRY_CLASSPATH}")
      string(REGEX REPLACE ";" ":" this_classpath "${FIELDS_CLASSPATH}")

      add_custom_target(fields_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${parent_classpath}" -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIELDS_JAVA_BINDING_JAR}  
            bindings/java/*.class
         )

      add_dependencies(fields_java_binding.jar ${FIELDS_JAVA_BINDING_LIB} ${GEOMETRY_JAVA_BINDING_JAR})

      set_target_properties(fields_java_binding.jar PROPERTIES FOLDER "Library Jars") 
 
      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(fields-java-binding)
      add_dependencies(fields-java-binding fields_java_binding.jar)
     
      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(fields-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle "fields documentation" 
               -classpath "${this_classpath}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/fields  
               *.java 
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(fields-java-docs ${FIELDS_JAVA_BINDING_JAR})

      endif(SHEAFSYSTEM_DOC_TARGETS)

   endif()      

endfunction(SheafSystem_add_fields_java_bindings_targets)



#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fields_csharp_bindings_targets)

   # Preconditions:

   # Requires swig and csharp to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_CSHARP)

   # Also requires geometry CSharp bindings, not sure how to require that.

   dbc_unexecutable_require("geometry CSharp bindings")
   
   set(CMAKE_SWIG_FLAGS -c++ -w842 -namespace fields)
   
   include_directories(${SHEAVES_CSHARP_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_CSHARP_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_CSHARP_BINDING_SRC_DIR})
   
   # Add the csharp binding library target

   set_source_files_properties(${FIELDS_CSHARP_BINDING_SRC_DIR}/${FIELDS_SWIG_CSHARP_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${FIELDS_CSHARP_BINDING_LIB} csharp 
      ${FIELDS_CSHARP_BINDING_SRC_DIR}/${FIELDS_SWIG_CSHARP_INTERFACE})

   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${FIELDS_CSHARP_BINDING_LIB}
         ${GEOMETRY_CSHARP_BINDING_LIB} ${FIELDS_IMPORT_LIB})

      target_link_libraries(${FIELDS_CSHARP_BINDING_LIB}
         PUBLIC ${GEOMETRY_CSHARP_BINDING_LIB} ${FIELDS_IMPORT_LIB}
         PRIVATE hdf5-static)

      set_target_properties(${FIELDS_CSHARP_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - CSharp")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIELDS_CSHARP_BINDING_LIB}
         ${GEOMETRY_CSHARP_BINDING_LIB} ${FIELDS_SHARED_LIB})

      target_link_libraries(${FIELDS_CSHARP_BINDING_LIB}
         ${GEOMETRY_CSHARP_BINDING_LIB} ${FIELDS_SHARED_LIB})

   endif()    

   set_target_properties(${FIELDS_CSHARP_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
   
   # Define the library version.

   set_target_properties(${FIELDS_CSHARP_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})

   # Create the csharp assembly

   if(SHEAFSYSTEM_WINDOWS)

      add_custom_target(${FIELDS_CSHARP_BINDING_ASSY} 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo ""
         COMMAND ${CMAKE_COMMAND} -E echo "Creating Csharp Binding for fields ..."
         COMMAND ${CMAKE_COMMAND} -E echo ""                 
         COMMAND ${CSHARP_COMPILER} /nologo /noconfig /warn:1 /errorreport:prompt 
            /target:library 
            /out:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIELDS_CSHARP_BINDING_ASSY}  
            ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )

      add_dependencies(${FIELDS_CSHARP_BINDING_ASSY} ${FIELDS_CSHARP_BINDING_LIB})          

      set_target_properties(${FIELDS_CSHARP_BINDING_ASSY} PROPERTIES FOLDER "CSharp Assembly Targets")

   else()

      add_custom_target(${FIELDS_CSHARP_BINDING_ASSY}
         ALL
         COMMAND ${CSHARP_COMPILER} -nowarn:0114,0108 
            -target:library
            -out:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIELDS_CSHARP_BINDING_ASSY}  
            ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )

      add_dependencies(${FIELDS_CSHARP_BINDING_ASSY} ${FIELDS_CSHARP_BINDING_LIB})          
 
      # Add library alias; only in Linux because clutters up Solution Explorer too much

      add_custom_target(fields-csharp-binding)
      add_dependencies(fields-csharp-binding ${FIELDS_CSHARP_BINDING_ASSY})
     
   endif(SHEAFSYSTEM_WINDOWS)

endfunction(SheafSystem_add_fields_csharp_bindings_targets)


#
# Create the python bindings targets for this component.
#
function(SheafSystem_add_fields_python_bindings_targets)

   # Preconditions:

   # Requires swig and python to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_PYTHONLIBS)

   # Also requires geometry python bindings, not sure how to require that.

   dbc_unexecutable_require("geometry python bindings")
   
   set(CMAKE_SWIG_FLAGS -c++ )
   
   include_directories(${SHEAFSYSTEM_PYTHON_INCLUDE_DIRS})
   include_directories(${SHEAVES_PYTHON_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_PYTHON_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_PYTHON_BINDING_SRC_DIR})
   
   set_source_files_properties(${FIELDS_PYTHON_BINDING_SRC_DIR}/${FIELDS_SWIG_PYTHON_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${FIELDS_PYTHON_BINDING_LIB} python 
      ${FIELDS_PYTHON_BINDING_SRC_DIR}/${FIELDS_SWIG_PYTHON_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${FIELDS_PYTHON_BINDING_LIB} 
         ${GEOMETRY_PYTHON_BINDING_LIB} ${FIELDS_IMPORT_LIB})

      # Including both release and debug libs here. Linker is smart enough to know 
      # which one to use, and since the build type is a run-time decision in VS
      # we have no way to choose when generating the make file.

      target_link_libraries(${FIELDS_PYTHON_BINDING_LIB}
         PUBLIC ${GEOMETRY_PYTHON_BINDING_LIB} ${FIELDS_IMPORT_LIB}
         PRIVATE hdf5-static)
      set_target_properties(${FIELDS_PYTHON_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Python")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIELDS_PYTHON_BINDING_LIB}
         ${GEOMETRY_PYTHON_BINDING_LIB} ${FIELDS_SHARED_LIB})
      
      target_link_libraries(${FIELDS_PYTHON_BINDING_LIB}
         ${GEOMETRY_PYTHON_BINDING_LIB} ${FIELDS_SHARED_LIB})

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(fields-python-binding)
      add_dependencies(fields-python-binding ${FIELDS_PYTHON_BINDING_LIB})

   endif()
   
   set_target_properties(${FIELDS_PYTHON_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${FIELDS_PYTHON_BINDING_LIB}
      PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})  

endfunction(SheafSystem_add_fields_python_bindings_targets)



#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fields_bindings_targets)

   # Can't add the bindings targets unless bindings are enabled.
   # Note that SHEAFSYSTEM_BUILD_BINDINGS implies Java, VTK, Swig, etc found, 
   # see SheafSystem_find_prerequisites

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseSWIG.cmake)

   SheafSystem_add_fields_java_bindings_targets()

   SheafSystem_add_fields_csharp_bindings_targets()

   SheafSystem_add_fields_python_bindings_targets()

   # Add aggregate bindings target for this component.

   add_custom_target(fields-bindings)
   add_dependencies(fields-bindings fields_java_binding.jar
      ${FIELDS_CSHARP_BINDING_LIB} ${FIELDS_PYTHON_BINDING_LIB})

endfunction(SheafSystem_add_fields_bindings_targets)


# 
# Set the commands for the install target
#
function(SheafSystem_add_fields_install_target)

   if(SHEAFSYSTEM_LINUX)

      install(TARGETS ${FIELDS_SHARED_LIB} ${FIELDS_STATIC_LIB} 
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
         DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      if(SHEAFSYSTEM_BUILD_BINDINGS)

         install(TARGETS ${FIELDS_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIELDS_JAVA_BINDING_JAR} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(TARGETS ${FIELDS_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(TARGETS ${FIELDS_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${FIELDS_CSHARP_BINDING_ASSY} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      endif()
      
   elseif(SHEAFSYSTEM_WINDOWS)

      install(TARGETS ${FIELDS_IMPORT_LIB}
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME} 
         ARCHIVE
         DESTINATION lib/$<CONFIG>)

      # The dynmaic library is not directly referred to by clients,
      # so it is not an exported target.
      
      install(TARGETS ${FIELDS_DYNAMIC_LIB} 
         RUNTIME
         DESTINATION bin/$<CONFIG>)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_DYNAMIC_LIB}_d.pdb 
         DESTINATION bin/$<CONFIG> OPTIONAL)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_DYNAMIC_LIB}.pdb 
         DESTINATION bin/$<CONFIG> OPTIONAL)
      
      if(SHEAFSYSTEM_BUILD_BINDINGS)

         # Install the fields java bindings libs.
         
         install(TARGETS ${FIELDS_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)
         
         install(TARGETS ${FIELDS_JAVA_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_JAVA_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_JAVA_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_JAVA_BINDING_JAR} 
            DESTINATION lib/$<CONFIG>)  

         # Install the fields csharp bindings libs
         
         install(TARGETS ${FIELDS_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${FIELDS_CSHARP_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_CSHARP_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_CSHARP_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_CSHARP_BINDING_ASSY} 
            DESTINATION bin/$<CONFIG>) 

         # Install fields python bindings libs.
         
         install(TARGETS ${FIELDS_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${FIELDS_PYTHON_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         
         
         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_PYTHON_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIELDS_PYTHON_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> 
            OPTIONAL) 
         
      endif(SHEAFSYSTEM_BUILD_BINDINGS)

   endif()

   install(FILES ${FIELDS_INCS} DESTINATION include) 
   
endfunction(SheafSystem_add_fields_install_target)
