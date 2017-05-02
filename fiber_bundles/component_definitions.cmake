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
function(SheafSystem_set_cumulative_fiber_bundles_variables)

   #
   # Set the cumulative include path for this component.
   #
   set(FIBER_BUNDLES_IPATHS ${SHEAVES_IPATHS} ${FIBER_BUNDLES_IPATH} 
      CACHE STRING " Cumulative include paths for fiber_bundles" FORCE)
   mark_as_advanced(FORCE FIBER_BUNDLES_IPATHS)

endfunction(SheafSystem_set_cumulative_fiber_bundles_variables)

#
# Create the library targets for this component.
#
function(SheafSystem_add_fiber_bundles_library_targets)

   # message("Entering fiber_bundles/component_defintions::add_library_target")

   # We'll need to use generator expression to configure include directories differently
   # for build and installation. Have to escape ";" in BUILD_INTERFACE 
   # generator expression, otherwise it inserts the current source directory 
   # just before the expression. Go figure.

   string(REPLACE ";" "\;" _lps_escaped_paths "${FIBER_BUNDLES_IPATH}" )
   # message("_lps_escaped_paths=${_lps_escaped_paths}")

   # Create target to create copies of header files with path ${SHEAFSYSTEM_HEADER_SCOPE}/*.h,
   # so uniquely scoped paths in include directives will work.

   SheafSystem_add_component_scoped_headers_target(fiber_bundles)

   if(SHEAFSYSTEM_WINDOWS)

      # Windows.

      # Tell the linker where to look for this project's libraries.
      # $$ISSUE: shouldn't be necessary.
      #link_directories(${FIBER_BUNDLES_OUTPUT_DIR})

      # Create the DLL.

      add_library(${FIBER_BUNDLES_DYNAMIC_LIB} SHARED ${FIBER_BUNDLES_SRCS})
      add_dependencies(${FIBER_BUNDLES_DYNAMIC_LIB} ${SHEAVES_IMPORT_LIB})
      add_dependencies(${FIBER_BUNDLES_DYNAMIC_LIB} fiber_bundles_scoped_headers)
      target_include_directories(${FIBER_BUNDLES_DYNAMIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIBER_BUNDLES_DYNAMIC_LIB} ${SHEAVES_IMPORT_LIB})
      set_target_properties(${FIBER_BUNDLES_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")

      # Override cmake's placing of "${FIBER_BUNDLES_DYNAMIC_LIB}_EXPORTS 
      # into the preproc symbol table.

      set_target_properties(${FIBER_BUNDLES_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

   else() 

      # Linux
      
      # Static library

      add_library(${FIBER_BUNDLES_STATIC_LIB} STATIC ${FIBER_BUNDLES_SRCS})
      add_dependencies(${FIBER_BUNDLES_STATIC_LIB} ${SHEAVES_STATIC_LIB})
      add_dependencies(${FIBER_BUNDLES_STATIC_LIB} fiber_bundles_scoped_headers)
      target_include_directories(${FIBER_BUNDLES_STATIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIBER_BUNDLES_STATIC_LIB} ${SHEAVES_STATIC_LIB})
      set_target_properties(${FIBER_BUNDLES_STATIC_LIB} PROPERTIES OUTPUT_NAME fiber_bundles )

      # Shared library

      add_library(${FIBER_BUNDLES_SHARED_LIB} SHARED ${FIBER_BUNDLES_SRCS})
      add_dependencies(${FIBER_BUNDLES_SHARED_LIB} ${SHEAVES_SHARED_LIB})
      add_dependencies(${FIBER_BUNDLES_SHARED_LIB} fiber_bundles_scoped_headers)
      target_include_directories(${FIBER_BUNDLES_SHARED_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${FIBER_BUNDLES_SHARED_LIB} ${SHEAVES_SHARED_LIB})
      set_target_properties(${FIBER_BUNDLES_SHARED_LIB} PROPERTIES OUTPUT_NAME fiber_bundles)
      set_target_properties(${FIBER_BUNDLES_SHARED_LIB} PROPERTIES LINKER_LANGUAGE CXX)
      
      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc 
      # symbol table. CMake apparently detects the presence of cdecl_dllspec in 
      # the source and places -D<LIBRARY>_EXPORTS into the preproc symbol 
      # table no matter the platform.

      set_target_properties(${FIBER_BUNDLES_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
      
      # Define the library version.

      set_target_properties(${FIBER_BUNDLES_SHARED_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION}) 
      
      # Library alias definitions

      add_custom_target(fiber_bundles-static-lib)
      add_dependencies(fiber_bundles-static-lib ${FIBER_BUNDLES_STATIC_LIB})

      add_custom_target(fiber_bundles-shared-lib)
      add_dependencies(fiber_bundles-shared-lib ${FIBER_BUNDLES_SHARED_LIB})

   endif()

   # message("Leaving fiber_bundles/component_defintions::add_library_target")

endfunction(SheafSystem_add_fiber_bundles_library_targets)

#
# Create the java bindings targets for this component.
#
function(SheafSystem_add_fiber_bundles_java_bindings_targets)

   # Preconditions:

   # Requires swig and java to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_JAVA)
   dbc_require(SHEAFSYSTEM_FOUND_JNI)

   # Also requires sheaves java bindings, not sure how to require that.

   dbc_unexecutable_require("sheaves java bindings")

   # Body:

#   include_directories(${FIBER_BUNDLES_IPATHS})
   include_directories(${SHEAFSYSTEM_BUILD_INC_DIR})
   include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
   include_directories(${SHEAVES_JAVA_BINDING_SRC_DIR})
   include_directories(${SHEAVES_COMMON_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_COMMON_BINDING_SRC_DIR})        
   include_directories(${HDF5_INCLUDE_DIR})
   
   set_source_files_properties(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_JAVA_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)
   
   set(SWIG_CXX_EXTENSION "cxx")
   set(CMAKE_SWIG_FLAGS -package bindings.java)
   
   # Add the java binding library target

   swig_add_module(${FIBER_BUNDLES_JAVA_BINDING_LIB} java 
      ${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_JAVA_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${FIBER_BUNDLES_JAVA_BINDING_LIB}
         ${SHEAVES_JAVA_BINDING_LIB} ${FIBER_BUNDLES_IMPORT_LIB})
      swig_link_libraries(${FIBER_BUNDLES_JAVA_BINDING_LIB}
         PUBLIC ${SHEAVES_JAVA_BINDING_LIB} ${FIBER_BUNDLES_IMPORT_LIB}
         PRIVATE hdf5-static)
      set_target_properties(${FIBER_BUNDLES_JAVA_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Java")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIBER_BUNDLES_JAVA_BINDING_LIB} ${SHEAVES_JAVA_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})
      target_link_libraries(${FIBER_BUNDLES_JAVA_BINDING_LIB} ${SHEAVES_JAVA_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})   

   endif()
   
   set_target_properties(${FIBER_BUNDLES_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${FIBER_BUNDLES_JAVA_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})

   # Create the bindings jar file 

   if(SHEAFSYSTEM_WINDOWS)

      # Windows.

      set(FIBER_BUNDLES_CLASSPATH  
         ${SHEAVES_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIBER_BUNDLES_JAVA_BINDING_JAR} 
         CACHE STRING "Cumulative classpath for fiber_bundles" FORCE)
      mark_as_advanced(FORCE FIBER_BUNDLES_CLASSPATH) 

      add_custom_target(fiber_bundles_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${SHEAVES_CLASSPATH}" -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIBER_BUNDLES_JAVA_BINDING_JAR} 
            bindings/java/*.class
         )
      
      add_dependencies(fiber_bundles_java_binding.jar
         ${FIBER_BUNDLES_JAVA_BINDING_LIB} ${SHEAVES_JAVA_BINDING_JAR})

      set_target_properties(fiber_bundles_java_binding.jar
         PROPERTIES FOLDER "Component Binding Jars")
      
      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(fiber_bundles-java-docs ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle "fiber_bundles documentation" 
               -classpath "${SHEAVES_CLASSPATH}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/fiber_bundles  
                *.java WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${FIBER_BUNDLES_JAVA_BINDING_JAR}
            )
         set_target_properties(fiber_bundles-java-docs PROPERTIES FOLDER "Documentation Targets") 

      endif(SHEAFSYSTEM_DOC_TARGETS)                              

   else()

      # Linux.
      
      set(FIBER_BUNDLES_CLASSPATH 
         ${SHEAVES_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIBER_BUNDLES_JAVA_BINDING_JAR} 
         CACHE STRING "Cumulative classpath for fiber_bundles" FORCE)
      mark_as_advanced(FORCE FIBER_BUNDLES_CLASSPATH) 

      # The default list item separator in cmake is ";". If Linux, then exchange 
      # ";" for  the UNIX style ":" and store the result in parent_classpath.

      string(REGEX REPLACE ";" ":" parent_classpath "${SHEAVES_CLASSPATH}")
      string(REGEX REPLACE ";" ":" this_classpath "${FIBER_BUNDLES_CLASSPATH}")            

      add_custom_target(fiber_bundles_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${parent_classpath}" -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIBER_BUNDLES_JAVA_BINDING_JAR} bindings/java/*.class
         )
       
      add_dependencies(fiber_bundles_java_binding.jar ${FIBER_BUNDLES_JAVA_BINDING_LIB} ${SHEAVES_JAVA_BINDING_JAR})
   
      set_target_properties(fiber_bundles_java_binding.jar PROPERTIES FOLDER "Library Jars") 

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(fiber_bundles-java-binding)
      add_dependencies(fiber_bundles-java-binding fiber_bundles_java_binding.jar)

      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(fiber_bundles-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle 
               "fiber_bundles documentation" -classpath "${this_classpath}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/fiber_bundles  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(fiber_bundles-java-docs ${FIBER_BUNDLES_JAVA_BINDING_JAR})

      endif(SHEAFSYSTEM_DOC_TARGETS)

   endif(SHEAFSYSTEM_WINDOWS)

endfunction(SheafSystem_add_fiber_bundles_java_bindings_targets)


#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fiber_bundles_csharp_bindings_targets)

   # Preconditions:

   # Requires swig and csharp to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_CSHARP)

   # Also requires sheaves CSharp bindings, not sure how to require that.

   dbc_unexecutable_require("sheaves CSharp bindings")

   # Body:
   
   set(CMAKE_SWIG_FLAGS -c++ -w842 -namespace fiber_bundle)
   
   include_directories(${SHEAVES_CSHARP_BINDING_SRC_DIR})
   include_directories(${HDF5_INCLUDE_DIR})
   
   # Add the csharp binding library target

   set_source_files_properties(${FIBER_BUNDLES_CSHARP_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_CSHARP_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${FIBER_BUNDLES_CSHARP_BINDING_LIB} csharp 
      ${FIBER_BUNDLES_CSHARP_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_CSHARP_INTERFACE})

   if(SHEAFSYSTEM_WINDOWS)

      swig_link_libraries(${FIBER_BUNDLES_CSHARP_BINDING_LIB}
         PUBLIC ${SHEAVES_CSHARP_BINDING_LIB} ${FIBER_BUNDLES_IMPORT_LIB}
         PRIVATE hdf5-static)

      set_target_properties(${FIBER_BUNDLES_CSHARP_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - CSharp")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIBER_BUNDLES_CSHARP_BINDING_LIB}
         ${SHEAVES_CSHARP_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})

      target_link_libraries(${FIBER_BUNDLES_CSHARP_BINDING_LIB} 
         ${SHEAVES_CSHARP_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})

   endif()    

   set_target_properties(${FIBER_BUNDLES_CSHARP_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${FIBER_BUNDLES_CSHARP_BINDING_LIB}
      PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})
   
   # Create the csharp assembly

   if(SHEAFSYSTEM_WINDOWS)

      add_custom_target(${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo ""
         COMMAND ${CMAKE_COMMAND} -E echo "Creating Csharp Binding for fiber_bundles ..."
         COMMAND ${CMAKE_COMMAND} -E echo ""                 
         COMMAND ${CSHARP_COMPILER} /nologo /noconfig /warn:1 
            /errorreport:prompt /target:library 
            /out:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
            ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )

      add_dependencies(${FIBER_BUNDLES_CSHARP_BINDING_ASSY} ${FIBER_BUNDLES_CSHARP_BINDING_LIB})        
      set_target_properties(${FIBER_BUNDLES_CSHARP_BINDING_ASSY}
         PROPERTIES FOLDER "CSharp Assembly Targets")

   else()

      add_custom_target(${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
         ALL
         COMMAND ${CSHARP_COMPILER} -target:library 
            -nowarn:0114,0108 
            -out:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
            ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )

      add_dependencies(${FIBER_BUNDLES_CSHARP_BINDING_ASSY} ${FIBER_BUNDLES_CSHARP_BINDING_LIB})        

      # Add library alias; only in Linux because clutters up Solution Explorer too much

      add_custom_target(fiber_bundles-csharp-binding)
      add_dependencies(fiber_bundles-csharp-binding ${FIBER_BUNDLES_CSHARP_BINDING_ASSY})

   endif()

endfunction(SheafSystem_add_fiber_bundles_csharp_bindings_targets)


#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fiber_bundles_python_bindings_targets)

   # Preconditions:

   # Requires swig and python to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_PYTHONLIBS)

   # Also requires sheaves python bindings, not sure how to require that.

   dbc_unexecutable_require("sheaves python bindings")

   # Body:
   
   set(CMAKE_SWIG_FLAGS -c++ )
   
   include_directories(${SHEAFSYSTEM_PYTHON_INCLUDE_DIRS})
   include_directories(${SHEAVES_PYTHON_BINDING_SRC_DIR})
   
   set_source_files_properties(${FIBER_BUNDLES_PYTHON_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_PYTHON_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${FIBER_BUNDLES_PYTHON_BINDING_LIB} python 
      ${FIBER_BUNDLES_PYTHON_BINDING_SRC_DIR}/${FIBER_BUNDLES_SWIG_PYTHON_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${FIBER_BUNDLES_PYTHON_BINDING_LIB}
         ${SHEAVES_PYTHON_BINDING_LIB} ${FIBER_BUNDLES_IMPORT_LIB})

      swig_link_libraries(${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
         PUBLIC ${SHEAVES_PYTHON_BINDING_LIB} ${FIBER_BUNDLES_IMPORT_LIB} ${PYTHON_LIBRARY}
         PRIVATE hdf5-static)

      set_target_properties(${FIBER_BUNDLES_PYTHON_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Python")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
         ${SHEAVES_PYTHON_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})

      swig_link_libraries(${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
         ${SHEAVES_PYTHON_BINDING_LIB} ${FIBER_BUNDLES_SHARED_LIB})

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(fiber_bundles-python-binding)
      add_dependencies(fiber_bundles-python-binding ${FIBER_BUNDLES_PYTHON_BINDING_LIB})

   endif()
   
   set_target_properties(${FIBER_BUNDLES_PYTHON_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${FIBER_BUNDLES_PYTHON_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})  

endfunction(SheafSystem_add_fiber_bundles_python_bindings_targets)


#
# Create the bindings targets for this component.
#
function(SheafSystem_add_fiber_bundles_bindings_targets)

   # Can't add the bindings targets unless bindings are enabled.
   # Note that SHEAFSYSTEM_BUILD_BINDINGS implies Java, VTK, Swig, etc found, 
   # see SheafSystem_find_prerequisites

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseSWIG.cmake)
#   include(UseSWIG)

   SheafSystem_add_fiber_bundles_java_bindings_targets()

   SheafSystem_add_fiber_bundles_csharp_bindings_targets()

   SheafSystem_add_fiber_bundles_python_bindings_targets()

   # Add aggregate bindings target for this component.

   add_custom_target(fiber_bundles-bindings)
   add_dependencies(fiber_bundles-bindings fiber_bundles_java_binding.jar 
      ${FIBER_BUNDLES_CSHARP_BINDING_LIB} ${FIBER_BUNDLES_PYTHON_BINDING_LIB})

endfunction(SheafSystem_add_fiber_bundles_bindings_targets)



function(SheafSystem_add_fiber_bundles_install_target)

   if(SHEAFSYSTEM_LINUX)

      install(TARGETS ${FIBER_BUNDLES_SHARED_LIB} ${FIBER_BUNDLES_STATIC_LIB}
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
         DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      if(SHEAFSYSTEM_BUILD_BINDINGS)

         install(TARGETS ${FIBER_BUNDLES_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME} 
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FIBER_BUNDLES_JAVA_BINDING_JAR} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)  

         install(TARGETS ${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME} 
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(TARGETS ${FIBER_BUNDLES_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME} 
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      endif(SHEAFSYSTEM_BUILD_BINDINGS)
      
   elseif(SHEAFSYSTEM_WINDOWS)

      # Install the fiber_bundles libs.
      
      install(TARGETS ${FIBER_BUNDLES_IMPORT_LIB} 
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME} 
         ARCHIVE DESTINATION lib/$<CONFIG>)

      # The dynmaic library is not directly referred to by clients,
      # so it is not an exported target.
      
      install(TARGETS ${FIBER_BUNDLES_DYNAMIC_LIB} 
         RUNTIME DESTINATION bin/$<CONFIG>)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_DYNAMIC_LIB}_d.pdb 
         DESTINATION bin/$<CONFIG> OPTIONAL)

      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_DYNAMIC_LIB}.pdb 
         DESTINATION bin/$<CONFIG> OPTIONAL)
      
      if(SHEAFSYSTEM_BUILD_BINDINGS)

         # Install fiber_bundles java bindings libs.
         
         install(TARGETS ${FIBER_BUNDLES_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)
         
         install(TARGETS ${FIBER_BUNDLES_JAVA_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)
         
         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_JAVA_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG>
            OPTIONAL) 

         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_JAVA_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG>
            OPTIONAL)

         install(FILES
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_JAVA_BINDING_JAR} 
            DESTINATION lib/$<CONFIG>)  

         # Install fiber_bundles csharp bindings libs.
         
         install(TARGETS ${FIBER_BUNDLES_CSHARP_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${FIBER_BUNDLES_CSHARP_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         
               
         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_CSHARP_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG>
            OPTIONAL) 

         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_CSHARP_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL) 

         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_CSHARP_BINDING_ASSY} 
            DESTINATION bin/$<CONFIG>)              

         # Install fiber_bundles python bindings libs.
         
         install(TARGETS ${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)         
         
         install(TARGETS ${FIBER_BUNDLES_PYTHON_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)         
         
         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_PYTHON_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL) 

         install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${FIBER_BUNDLES_PYTHON_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL) 

      endif(SHEAFSYSTEM_BUILD_BINDINGS)

   endif(SHEAFSYSTEM_LINUX)

   install(FILES ${FIBER_BUNDLES_INCS} DESTINATION include) 
   
endfunction(SheafSystem_add_fiber_bundles_install_target)

