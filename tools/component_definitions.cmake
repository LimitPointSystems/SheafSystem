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
function(SheafSystem_set_cumulative_tools_variables)

   # Set the cumulative include path for this component.

   if(SHEAFSYSTEM_BUILD_BINDINGS)

      set(TOOLS_IPATHS ${FIELDS_IPATHS} ${TOOLS_IPATH} ${VTK_INCLUDE_DIRS}
         ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} 
         CACHE
         STRING " Cumulative include paths for tools component"
         FORCE)

   else()

      set(TOOLS_IPATHS ${FIELDS_IPATHS} ${TOOLS_IPATH} 
         CACHE
         STRING " Cumulative include paths for tools component"
         FORCE)

   endif()
   mark_as_advanced(FORCE TOOLS_IPATHS)

endfunction(SheafSystem_set_cumulative_tools_variables)

#
# Establish an aggregate list of files used to build the SHeafScope.
#
function(SheafSystem_set_scope_sources)

   # clear the scope srcs var so consecutive cmake runs don't
   # list the same sources n times.

   set(TOOLS_SHEAFSCOPE_SRCS CACHE STRING "SheafScope java sources." FORCE)
   mark_as_advanced(FORCE TOOLS_SHEAFSCOPE_SRCS)

   foreach(cluster ${clusters})

      file(GLOB scopesrcs . ${cluster}/*.java)
      set(TOOLS_SHEAFSCOPE_SRCS ${TOOLS_SHEAFSCOPE_SRCS} ${scopesrcs}
         CACHE STRING "SheafScope java sources." FORCE)

   endforeach()

   string(REPLACE "\\" "/" TOOLS_SHEAFSCOPE_SRCS "${TOOLS_SHEAFSCOPE_SRCS}")

   # Write the contents of TOOLS_SHEAFSCOPE_SRCS to a file on disk.
   # We have to do this to overcome the Windows 8K character
   # command line limit in Windows.

   string(REGEX REPLACE ";" "\r" TOOLS_SHEAFSCOPE_SRCS "${TOOLS_SHEAFSCOPE_SRCS}")
   file(WRITE ${CMAKE_BINARY_DIR}/scopesrcs "${TOOLS_SHEAFSCOPE_SRCS}")
   
endfunction(SheafSystem_set_scope_sources)

#
# Create the library targets for this component.
#
function(SheafSystem_add_tools_library_targets)

   # message("Entering tools/component_defintions::add_library_target")

   # Link libraries below assume we're building bindings.

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   # Shouldn't need this anymore
   # link_directories(${VTK_LIBRARY_DIRS})

   # We'll need to use generator expression to configure include directories differently
   # for build and installation. Have to escape ";" in BUILD_INTERFACE 
   # generator expression, otherwise it inserts the current source directory 
   # just before the expression. Go figure.

   string(REPLACE ";" "\;" _lps_escaped_paths "${TOOLS_IPATH}" )
   # message("_lps_escaped_paths=${_lps_escaped_paths}")

   # Target to create copies of header files with path ${SHEAFSYSTEM_HEADER_SCOPE}/*.h,
   # so uniquely scoped paths in include directives with work.

   add_custom_target(sheaves_scoped_headers
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TOOLS_INCS} ${SHEAFSYSTEM_HEADER_SCOPE})
   
   if(SHEAFSYSTEM_WINDOWS)

      # Windows

      # Tell the linker where to look for this project's libraries. 
      # $$ISSUE: shouldn't be necessary.
      # link_directories(${TOOLS_OUTPUT_DIR})
      
      # Create the DLL.

      add_library(${TOOLS_DYNAMIC_LIB} SHARED ${TOOLS_SRCS})
      add_dependencies(${TOOLS_DYNAMIC_LIB} ${FIELDS_IMPORT_LIB})
      add_dependencies(${TOOLS_DYNAMIC_LIB} tools_scoped_headers)
      target_include_directories(${TOOLS_DYNAMIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )           
      target_link_libraries(${TOOLS_DYNAMIC_LIB} ${FIELDS_IMPORT_LIB} 
         ${JNI_LIBRARIES} ${JAVA_AWT_LIBRARY} ${JAVA_JVM_LIBRARY} ${VTK_LIBS} ) 
      set_target_properties(${TOOLS_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")        
      
      # Override cmake's placing of "${TOOLS_DYNAMIC_LIB}_EXPORTS 
      # into the preproc symbol table.

      set_target_properties(${TOOLS_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")
      
   else()

      # Linux
      
      # Static library

      add_library(${TOOLS_STATIC_LIB} STATIC ${TOOLS_SRCS})
      add_dependencies(${TOOLS_STATIC_LIB} ${FIELDS_STATIC_LIB})
      add_dependencies(${TOOLS_STATIC_LIB} tools_scoped_headers)
      target_include_directories(${TOOLS_STATIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${TOOLS_STATIC_LIB} ${FIELDS_STATIC_LIB} 
         ${JAVA_AWT_LIBRARY} ${JAVA_MAWT_LIBRARY} ${JAVA_JVM_LIBRARY} ${VTK_LIBS})
      set_target_properties(${TOOLS_STATIC_LIB} PROPERTIES OUTPUT_NAME tools)
      
      # Shared library

      add_library(${TOOLS_SHARED_LIB} SHARED ${TOOLS_SRCS})
      add_dependencies(${TOOLS_SHARED_LIB} ${FIELDS_SHARED_LIB})
      add_dependencies(${TOOLS_SHARED_LIB} tools_scoped_headers)
      target_include_directories(${TOOLS_SHARED_LIB} PUBLIC
         $<BUILD_INTERFACE:${_lps_escaped_paths}> $<INSTALL_INTERFACE:include> )   
      target_link_libraries(${TOOLS_SHARED_LIB} ${FIELDS_SHARED_LIB} 
         ${JAVA_AWT_LIBRARY} ${JAVA_MAWT_LIBRARY} ${JAVA_JVM_LIBRARY} ${VTK_LIBS})
      set_target_properties(${TOOLS_SHARED_LIB} PROPERTIES OUTPUT_NAME tools)
      set_target_properties(${TOOLS_SHARED_LIB} PROPERTIES LINKER_LANGUAGE CXX)
      set_target_properties(${TOOLS_SHARED_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION}) 
      
      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
      # CMake apparently detects the presence of cdecl_dllspec in the source and places
      # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.

      set_target_properties(${TOOLS_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")      
      
      # Library alias definitions

      add_custom_target(tools-static-lib)
      add_dependencies(tools-static-lib ${TOOLS_STATIC_LIB})      

      add_custom_target(tools-shared-lib)
      add_dependencies(tools-shared-lib ${TOOLS_SHARED_LIB})

   endif()

   # message("Leaving tools/component_defintions::add_library_target")

endfunction(SheafSystem_add_tools_library_targets)

#
# Create the bindings targets for this component.
#
function(SheafSystem_add_tools_java_bindings_targets)

   # Preconditions:

   # Requires swig and java to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_JAVA)
   dbc_require(SHEAFSYSTEM_FOUND_JNI)

   # Also requires fields java bindings, not sure how to require that.

   dbc_unexecutable_require("fields java bindings")

   include_directories(${VTK_INCLUDE_DIRS})
   link_directories(${VTK_LIB_DIR}) 

   include_directories(${TOOLS_IPATHS})
   include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
   include_directories(${SHEAVES_JAVA_BINDING_SRC_DIR})
   include_directories(${SHEAVES_COMMON_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR})
   include_directories(${FIBER_BUNDLES_COMMON_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_JAVA_BINDING_SRC_DIR})
   include_directories(${GEOMETRY_COMMON_BINDING_SRC_DIR})
   include_directories(${FIELDS_JAVA_BINDING_SRC_DIR})
   include_directories(${FIELDS_COMMON_BINDING_SRC_DIR})
   include_directories(${TOOLS_JAVA_BINDING_SRC_DIR})
   include_directories(${TOOLS_COMMON_BINDING_SRC_DIR})
   
   set_source_files_properties(${TOOLS_JAVA_BINDING_SRC_DIR}/${TOOLS_SWIG_JAVA_INTERFACE}
      PROPERTIES CPLUSPLUS ON)
   
   set(SWIG_CXX_EXTENSION "cxx")
   set(CMAKE_SWIG_FLAGS -package bindings.java)

   # Add the java binding library target

   swig_add_module(${TOOLS_JAVA_BINDING_LIB} java
      ${TOOLS_JAVA_BINDING_SRC_DIR}/${TOOLS_SWIG_JAVA_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${TOOLS_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_LIB} ${TOOLS_IMPORT_LIB})
      swig_link_libraries(${TOOLS_JAVA_BINDING_LIB}
         PUBLIC ${FIELDS_JAVA_BINDING_LIB} ${TOOLS_IMPORT_LIB}
         PRIVATE hdf5-static)   
      set_target_properties(${TOOLS_JAVA_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Java")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${TOOLS_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_LIB} ${TOOLS_SHARED_LIB})
      target_link_libraries(${TOOLS_JAVA_BINDING_LIB} 
         ${TOOLS_SHARED_LIB} ${FIELDS_JAVA_BINDING_LIB} ${VTK_LIBS})   

   endif(SHEAFSYSTEM_WINDOWS)
   
   set_target_properties(${TOOLS_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
   
   # Define the library version.

   set_target_properties(${TOOLS_JAVA_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})
   
   # Create the bindings jar file 

   if(SHEAFSYSTEM_WINDOWS)

      # Windows.

      set(TOOLS_CLASSPATH
         ${FIELDS_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${TOOLS_JAVA_BINDING_JAR} 
         ${VTK_JAR}
         CACHE STRING "Cumulative classpath for tools" FORCE)
      mark_as_advanced(FORCE TOOLS_CLASSPATH) 

      add_custom_target(tools_java_binding.jar 
         ALL 
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE}
            -classpath "${FIELDS_CLASSPATH} ${VTK_JAR} ${JMF_JAR}"
            -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${TOOLS_JAVA_BINDING_JAR} bindings/java/*.class
         )

      add_dependencies(tools_java_binding.jar ${TOOLS_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_JAR})

      set_target_properties(tools_java_binding.jar PROPERTIES FOLDER "Component Binding Jars")                           
      
      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)
         add_custom_target(tools-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle "tools documentation" 
               -classpath "${FIELDS_CLASSPATH}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/tools  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(tools-java-docs ${TOOLS_JAVA_BINDING_JAR})
         set_target_properties(tools-java-docs PROPERTIES FOLDER "Documentation Targets")

      endif(SHEAFSYSTEM_DOC_TARGETS)

   elseif(SHEAFSYSTEM_LINUX)

      # Linux  

      set(TOOLS_CLASSPATH
         ${FIELDS_CLASSPATH} 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${TOOLS_JAVA_BINDING_JAR} 
         ${JMF_JAR}
         ${VTK_JAR}
         CACHE STRING "Cumulative classpath for tools" FORCE)
      mark_as_advanced(FORCE TOOLS_CLASSPATH) 

      # The default list item separator in cmake is ";". If Linux, then exchange ";" for  the UNIX style ":"
      # and store the result in parent_classpath.

      string(REGEX REPLACE ";" ":" parent_classpath "${FIELDS_CLASSPATH}")
      string(REGEX REPLACE ";" ":" this_classpath "${TOOLS_CLASSPATH}")

      add_custom_target(tools_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${parent_classpath}" -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${TOOLS_JAVA_BINDING_JAR} bindings/java/*.class
         )
      
      add_dependencies(tools_java_binding.jar ${TOOLS_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_JAR})

      set_target_properties(tools_java_binding.jar PROPERTIES FOLDER "Library Jars") 

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(tools-java-binding)
      add_dependencies(tools-java-binding tools_java_binding.jar)

      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(tools-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} -windowtitle "tools documentation" 
               -classpath "${this_classpath}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/tools  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(tools-java-docs ${TOOLS_JAVA_BINDING_JAR})

      endif(SHEAFSYSTEM_DOC_TARGETS)                                      

   endif(SHEAFSYSTEM_WINDOWS)

   if(SHEAFSYSTEM_BUILD_SHEAFSCOPE)   
      
      # Establish the SheafScope jar dir

      set(LIB_JAR_DIR ${CMAKE_BINARY_DIR}/SheafScope)

      # Build the SheafScope jar

      if(SHEAFSYSTEM_WINDOWS)

         # Windows

         add_custom_target(SheafScope.jar 
            ALL 
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}
            COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
            COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${TOOLS_CLASSPATH}" 
               -g -d ${LIB_JAR_DIR} @${CMAKE_BINARY_DIR}/scopesrcs
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/common/gui/resources
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/viewer/resources/docs
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/SheafScope/resources/docs

	    COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/common/gui/resources
               ${LIB_JAR_DIR}/tools/common/gui/resources
	    COMMAND ${CMAKE_COMMAND} -E copy_directory 
	       ${CMAKE_SOURCE_DIR}/tools/viewer/resources
	       ${LIB_JAR_DIR}/tools/viewer/resources
	    COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/viewer/resources/docs
	       ${LIB_JAR_DIR}/tools/viewer/resources/docs
	    COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/resources      
	       ${LIB_JAR_DIR}/tools/SheafScope/resources
	    COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/resources/docs 
               ${LIB_JAR_DIR}/tools/SheafScope/resources/docs 

            COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
            COMMAND ${Java_JAR_EXECUTABLE} cvmf 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/manifest.txt 
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/SheafScope.jar  
               -C ${LIB_JAR_DIR} .
            )

         add_dependencies(SheafScope.jar tools_java_binding.jar)

      elseif(SHEAFSYSTEM_LINUX)

         # Linux

         # Build the SheafScope jar

         add_custom_target(SheafScope.jar 
            ALL 
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}
            COMMAND ${CMAKE_COMMAND} -E echo "Compiling SheafScope.jar Java files..."
            COMMAND ${Java_JAVAC_EXECUTABLE} -classpath "${this_classpath}" 
               -g -d ${LIB_JAR_DIR} @${CMAKE_BINARY_DIR}/scopesrcs
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/common/gui/resources
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/viewer/resources/docs
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAR_DIR}/tools/SheafScope/resources/docs
            
            COMMAND ${CMAKE_COMMAND} -E copy_directory
               ${CMAKE_SOURCE_DIR}/tools/common/gui/resources 
               ${LIB_JAR_DIR}/tools/common/gui/resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/viewer/resources 
               ${LIB_JAR_DIR}/tools/viewer/resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/viewer/resources/docs 
               ${LIB_JAR_DIR}/tools/viewer/resources/docs
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/resources 
               ${LIB_JAR_DIR}/tools/SheafScope/resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/resources/docs
               ${LIB_JAR_DIR}/tools/SheafScope/resources/docs 
            
            COMMAND ${CMAKE_COMMAND} -E echo "Creating SheafScope jar file..."
            COMMAND ${Java_JAR_EXECUTABLE} cvmf 
               ${CMAKE_SOURCE_DIR}/tools/SheafScope/manifest.txt 
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SheafScope.jar 
               -C ${LIB_JAR_DIR} .
            )

         add_dependencies(SheafScope.jar tools_java_binding.jar)

      endif(SHEAFSYSTEM_WINDOWS)
      
      set_target_properties(SheafScope.jar PROPERTIES FOLDER "Executable Jars") 

   endif(SHEAFSYSTEM_BUILD_SHEAFSCOPE)
   
endfunction(SheafSystem_add_tools_java_bindings_targets)


#
# Create the bindings targets for this component.
#
function(SheafSystem_add_tools_bindings_targets)

   # Can't add the bindings targets unless bindings are enabled.
   # Note that SHEAFSYSTEM_BUILD_BINDINGS implies Java, VTK, Swig, etc found, 
   # see SheafSystem_find_prerequisites

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseSWIG.cmake)
#   include(UseSWIG)

   SheafSystem_add_tools_java_bindings_targets()

   # Apparently there are no Csharp or python bindings for tools.

   # SheafSystem_add_tools_csharp_bindings_targets()

   # SheafSystem_add_tools_python_bindings_targets()

   # Add aggregate bindings target for this component.

   add_custom_target(tools-bindings)
   add_dependencies(tools-bindings tools_java_binding.jar)

endfunction(SheafSystem_add_tools_bindings_targets)



# 
# Set the commands for the install target
#
function(SheafSystem_add_tools_install_target)

   if(SHEAFSYSTEM_LINUX)

      if(SHEAFSYSTEM_BUILD_BINDINGS)

         install(TARGETS ${TOOLS_SHARED_LIB}  ${TOOLS_STATIC_LIB}
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)


         install(TARGETS ${TOOLS_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${TOOLS_JAVA_BINDING_JAR}
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)  

         install(PROGRAMS ${JMF_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(PROGRAMS ${VTK_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(PROGRAMS ${JAVA_JDK_LIBS} DESTINATION ${CMAKE_BUILD_TYPE}/lib)

      endif(SHEAFSYSTEM_BUILD_BINDINGS)

      if(SHEAFSYSTEM_BUILD_SHEAFSCOPE)

         # Install the SheafScope.

         install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SheafScope.jar 
            DESTINATION ${CMAKE_BUILD_TYPE}/lib)

         install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sheafscope 
            DESTINATION ${CMAKE_BUILD_TYPE}/bin)

      endif(SHEAFSYSTEM_BUILD_SHEAFSCOPE)

      install(TARGETS dumpsheaf DESTINATION ${CMAKE_BUILD_TYPE}/bin)   
      
   elseif(SHEAFSYSTEM_WINDOWS)

      if(SHEAFSYSTEM_BUILD_BINDINGS)

         # Install tools libs.
         
         install(TARGETS ${TOOLS_IMPORT_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION lib/$<CONFIG>)

         # The dynmaic library is not directly referred to by clients,
         # so it is not an exported target.
      
         install(TARGETS ${TOOLS_DYNAMIC_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${TOOLS_DYNAMIC_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${TOOLS_DYNAMIC_LIB}.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL)

         # Install tools java binding libs.
         
         install(TARGETS ${TOOLS_JAVA_BINDING_LIB} 
            EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
            ARCHIVE
            DESTINATION LIB/$<CONFIG>)
         
         install(TARGETS ${TOOLS_JAVA_BINDING_LIB} 
            RUNTIME
            DESTINATION bin/$<CONFIG>)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${TOOLS_JAVA_BINDING_LIB}_d.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL)

         install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${TOOLS_JAVA_BINDING_LIB}.pdb 
            DESTINATION bin/$<CONFIG> OPTIONAL)

         # Install the tools java binding jar files.

         install(PROGRAMS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/$<CONFIG>/${TOOLS_JAVA_BINDING_JAR} 
            DESTINATION lib/$<CONFIG> OPTIONAL)  

         install(PROGRAMS ${JMF_JAR} DESTINATION lib/$<CONFIG> OPTIONAL)
         install(PROGRAMS ${VTK_JAR} DESTINATION lib/$<CONFIG> OPTIONAL)
         install(PROGRAMS ${JAVA_JDK_LIBS} DESTINATION lib/$<CONFIG> OPTIONAL)

      endif(SHEAFSYSTEM_BUILD_BINDINGS)

      if(SHEAFSYSTEM_BUILD_SHEAFSCOPE)

         install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/SheafScope.jar 
            DESTINATION bin/$<CONFIG> OPTIONAL)

         install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/sheafscope 
            DESTINATION bin/$<CONFIG> OPTIONAL)

      endif(SHEAFSYSTEM_BUILD_SHEAFSCOPE)
      
      install(TARGETS dumpsheaf 
         EXPORT ${SHEAFSYSTEM_EXPORT_NAME}
         DESTINATION bin/$<CONFIG>
         OPTIONAL)

   endif(SHEAFSYSTEM_LINUX)

   install(FILES ${TOOLS_INCS} DESTINATION include) 
   
endfunction(SheafSystem_add_tools_install_target)

function(SheafSystem_add_dumpsheaf_target)

   add_executable(dumpsheaf ${CMAKE_SOURCE_DIR}/tools/util/dumpsheaf.cc)
   target_include_directories(dumpsheaf PUBLIC ${HDF5_INCLUDE_DIR} )
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(dumpsheaf ${FIBER_BUNDLES_IMPORT_LIB})
      target_link_libraries(dumpsheaf ${FIBER_BUNDLES_IMPORT_LIB})

   else()

      add_dependencies(dumpsheaf ${FIBER_BUNDLES_SHARED_LIB})
      target_link_libraries(dumpsheaf ${FIBER_BUNDLES_SHARED_LIB})

   endif()

   # Supply the *_DLL_IMPORTS directive to preprocessor

   set_target_properties(dumpsheaf PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")

   # Put the target in the Utilities VS folder.

   set_target_properties(dumpsheaf PROPERTIES FOLDER "Utilities")
   
endfunction(SheafSystem_add_dumpsheaf_target)

function(SheafSystem_add_sheafscope_wrapper_target)

   add_executable(sheafscope ${CMAKE_SOURCE_DIR}/tools/util/SheafScope.cc)
   
   # Make sure the library is up to date

   if(SHEAFSYSTEM_WINDOWS)
      add_dependencies(sheafscope ${TOOLS_IMPORT_LIB})
      target_link_libraries(sheafscope ${TOOLS_IMPORT_LIB})
   elseif(SHEAFSYSTEM_LINUX)
      add_dependencies(sheafscope ${TOOLS_SHARED_LIB})
      target_link_libraries(sheafscope ${TOOLS_SHARED_LIB})
   endif()

   # Supply the *_DLL_IMPORTS directive to preprocessor

   set_target_properties(sheafscope PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")

   # Put the target in the Utilities VS folder.

   set_target_properties(sheafscope PROPERTIES FOLDER "Utilities")
   
endfunction(SheafSystem_add_sheafscope_wrapper_target)
