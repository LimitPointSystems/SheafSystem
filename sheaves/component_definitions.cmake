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

 
#
# Set some cumulative variables; not entirely clear these are necessary.
#
function(SheafSystem_set_cumulative_sheaves_variables)

   #
   # Set the cumulative include path for this component.
   #
   set(SHEAVES_IPATHS ${SHEAVES_IPATH} ${CMAKE_BINARY_DIR}/include 
      CACHE 
      STRING " Cumulative include paths for sheaves" 
      FORCE)
   mark_as_advanced(FORCE SHEAVES_IPATHS)

endfunction(SheafSystem_set_cumulative_sheaves_variables)

#
# Check for and configure system cxx includes.
#
function(SheafSystem_check_cxx_includes)

   include(CheckIncludeFileCXX)

   # C++ Headers for C Library Facilities

   if(NOT HAVE_CASSERT)
      SheafSystem_status_message("Looking for C++ Headers For C Library Functions")   
   endif()

   check_include_file_cxx(cassert HAVE_CASSERT)
   check_include_file_cxx(cctype HAVE_CCTYPE)
   check_include_file_cxx(cerrno HAVE_CERRNO)
   check_include_file_cxx(cfloat HAVE_CFLOAT)
   check_include_file_cxx(ciso646 HAVE_CISO646)
   check_include_file_cxx(climits HAVE_CLIMITS)
   check_include_file_cxx(clocale HAVE_CLOCALE)
   check_include_file_cxx(cmath HAVE_CMATH)
   check_include_file_cxx(csetjmp HAVE_CSETJMP)
   check_include_file_cxx(csignal HAVE_CSIGNAL)
   check_include_file_cxx(cstdarg HAVE_CSTDARG)
   check_include_file_cxx(cstddef HAVE_CSTDDEF)
   check_include_file_cxx(cstdio HAVE_CSTDIO)
   check_include_file_cxx(cstdlib HAVE_CSTDLIB)
   check_include_file_cxx(cstring HAVE_CSTRING)
   check_include_file_cxx(ctime HAVE_CTIME)
   check_include_file_cxx(cwchar HAVE_CWCHAR)
   check_include_file_cxx(cwctype HAVE_CWCTYPE)                        


   # C++ Library Headers

   if(NOT HAVE_ALGORITHM)
      SheafSystem_status_message("Looking for C++ Standard Library Headers")    
   endif()

   check_include_file_cxx(algorithm HAVE_ALGORITHM)
   check_include_file_cxx(bitset HAVE_BITSET)
   check_include_file_cxx(complex HAVE_COMPLEX)    
   check_include_file_cxx(deque HAVE_DEQUE)
   check_include_file_cxx(exception HAVE_EXCEPTION)    
   check_include_file_cxx(forward_list HAVE_FORWARD_LIST)
   if(NOT HAVE_FORWARD_LIST)
      check_include_file_cxx(ext/slist HAVE_EXT_SLIST) 
      if(NOT HAVE_EXT_SLIST)
         message(FATAL_ERROR "ERROR: ${CMAKE_CXX_COMPILER} does not appear to support forward_list or slist. Configure phase aborted")
      endif()
   endif()
   check_include_file_cxx(fstream HAVE_FSTREAM)
   check_include_file_cxx(functional HAVE_FUNCTIONAL)
   check_include_file_cxx(iomanip HAVE_IOMANIP)
   check_include_file_cxx(ios HAVE_IOS)
   check_include_file_cxx(iosfwd HAVE_IOSFWD)
   check_include_file_cxx(iostream HAVE_IOSTREAM)
   check_include_file_cxx(iterator HAVE_ITERATOR)
   check_include_file_cxx(limits HAVE_LIMITS)
   check_include_file_cxx(list HAVE_LIST)
   check_include_file_cxx(locale HAVE_LOCALE)
   check_include_file_cxx(map HAVE_MAP)
   check_include_file_cxx(memory HAVE_MEMORY)
   check_include_file_cxx(new HAVE_NEW)
   check_include_file_cxx(numeric HAVE_NUMERIC)
   check_include_file_cxx(ostream HAVE_OSTREAM)
   check_include_file_cxx(queue HAVE_QUEUE)
   check_include_file_cxx(set HAVE_SET)
   check_include_file_cxx(sstream HAVE_SSTREAM)
   check_include_file_cxx(stack HAVE_STACK)
   check_include_file_cxx(stdexcept HAVE_STDEXCEPT)
   check_include_file_cxx(strtream HAVE_STRSTREAM)
   check_include_file_cxx(streambuf HAVE_STREAMBUF)
   check_include_file_cxx(string HAVE_STRING)
   check_include_file_cxx(unordered_map HAVE_UNORDERED_MAP)
   if(NOT HAVE_UNORDERED_MAP)
      check_include_file_cxx(tr1/unordered_map HAVE_TR1_UNORDERED_MAP) 
      if(NOT HAVE_TR1_UNORDERED_MAP)
         message(FATAL_ERROR "ERROR: ${CMAKE_CXX_COMPILER} does not appear to support unordered_map. Configure phase aborted")
      endif()
   endif()
   check_include_file_cxx(unordered_set HAVE_UNORDERED_SET)
   if(NOT HAVE_UNORDERED_SET)
      check_include_file_cxx(tr1/unordered_set HAVE_TR1_UNORDERED_SET)

      if(NOT HAVE_TR1_UNORDERED_SET)
         message(FATAL_ERROR "ERROR: ${CMAKE_CXX_COMPILER} does not appear to support unordered_set. Configure phase aborted")
      endif()
   endif()
   check_include_file_cxx(typeinfo HAVE_TYPEINFO)
   check_include_file_cxx(utility HAVE_UTILITY)
   check_include_file_cxx(valarray HAVE_VALARRAY)
   check_include_file_cxx(vector HAVE_VECTOR)

endfunction(SheafSystem_check_cxx_includes)

#
# Check for C++ headers and configure the STD wrappers 
# for the current platform.
#
function(SheafSystem_configure_std_headers)

   SheafSystem_status_message("Configuring STD include files")

   # Glob all the .h.cmake.in files in std

   file(GLOB STD_INC_INS
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/std ${CMAKE_CURRENT_SOURCE_DIR}/std/*.h.in)

   # Configure the .h file from each .h.cmake.in

   foreach(input_file ${STD_INC_INS})

      # Strip .in from globbed filenames for output filenames

      string(REGEX REPLACE ".in$" ""  std_h ${input_file})
      message(STATUS "Creating ${CMAKE_BINARY_DIR}/include/${std_h} from std/${input_file}")
      list(APPEND std_incs ${SHEAFSYSTEM_HEADER_DIR}/${std_h})

      # Configure the .h files

      configure_file(std/${input_file} ${SHEAFSYSTEM_HEADER_DIR}/${std_h})

   endforeach()

   set(SHEAVES_STD_HEADERS ${std_incs} CACHE STRING "STD Includes" FORCE)          
   mark_as_advanced(FORCE SHEAVES_STD_HEADERS)
   
endfunction(SheafSystem_configure_std_headers)

#
# Create the library targets for this component.
#
function(SheafSystem_add_sheaves_library_targets)

   # message("Entering sheaves/component_defintions::SheafSystem_add_sheaves_library_target")

   # We will need to use generator expression to configure include directories differently
   # for build and installation. Have to escape ";" in BUILD_INTERFACE 
   # generator expression, otherwise it inserts the current source directory 
   # just before the expression. Go figure.

   string(REPLACE ";" "\;" _lps_escaped_paths "${SHEAVES_IPATHS}" )
   #message("static _lps_escaped_paths= ${_lps_escaped_paths}")

   # Target to create copies of header files with path ${SHEAFSYSTEM_HEADER_SCOPE}/*.h,
   # so uniquely scoped paths in include directives with work.

   add_custom_target(sheaves_scoped_headers
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHEAVES_INCS} ${SHEAFSYSTEM_HEADER_DIR})

   if(SHEAFSYSTEM_WINDOWS)

      # Tell the linker where to look for this project's libraries.
      # $$ISSUE: shouldn't be necessary.
      #link_directories(${SHEAVES_OUTPUT_DIR})

      # Create the DLL.

      add_library(${SHEAVES_DYNAMIC_LIB} SHARED ${SHEAVES_SRCS})
      add_dependencies(${SHEAVES_DYNAMIC_LIB} sheaves_scoped_headers)
      target_include_directories(${SHEAVES_DYNAMIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )
      target_link_libraries(${SHEAVES_DYNAMIC_LIB} PRIVATE hdf5-static)
      set_target_properties(${SHEAVES_DYNAMIC_LIB} PROPERTIES FOLDER "Library Targets")

      # Override cmake's placing of "${SHEAVES_DYNAMIC_LIB}_EXPORTS 
      # into the preproc symbol table.

      set_target_properties(${SHEAVES_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

   elseif(SHEAFSYSTEM_LINUX)
      
      # Static library

      # Statically "linking" a library is really just putting the .o files into a .a file
      # and perhapd creating an index for the .a file. There is no actual linking involved.
      # However, the link_target_libraries command distinguishes between the link dependencies,
      # those libraries needed to "link" the target, and the link interface, those libraries
      # needed by clients linking to the target library. The list of link dependencies for the 
      # static library is empty, but the link interface includes hdf5 and the libraries listed
      # as "Extra libraries" in lhdf5.settings, that is:  hdf5 m dl rt z szip. Detailed
      # examination of libhdf5.a using nm seems to show that librt (asynchronuous i/o, see man
      # for instance aio_cancel and aio.h) is not actually called, at least not directly.
      # In any case, the link and include interface should propagate from the hdf5-static target.

      add_library(${SHEAVES_STATIC_LIB} STATIC ${SHEAVES_SRCS})
      add_dependencies(${SHEAVES_STATIC_LIB} sheaves_scoped_headers)
      target_include_directories(${SHEAVES_STATIC_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )
      target_link_libraries(${SHEAVES_STATIC_LIB} PUBLIC hdf5-static)
      set_target_properties(${SHEAVES_STATIC_LIB} PROPERTIES OUTPUT_NAME sheaves)
      set_target_properties(${SHEAVES_STATIC_LIB} PROPERTIES LINKER_LANGUAGE CXX)

      # Shared library

      # A shared library is really linked, so hdf5 and the "Extra libraries", (see comment for
      # static library above) must be in its link dependencies. We want to statically link these
      # into the shared library, so in principle they should not be in the link interface.
      # However, linking a static library into a shared library requires the static library
      # to be compiled with -fPIC. Unfortunately, libdl.a as distributed with 
      # glibc-static-2.12-1.149.el6.x86_64.rpm isn't compiled -fPIC and can't be linked statically.
      # The others apparently can be linked statically, although libstdc++ requires libm.so,
      # so the sheaf shard library ends up requiring libm.so anyway, even if linked statically here.

      add_library(${SHEAVES_SHARED_LIB} SHARED ${SHEAVES_SRCS})

      add_dependencies(${SHEAVES_SHARED_LIB} sheaves_scoped_headers)

      # Dependence on HDF5 library is private so include directories don't
      # propagate in link interface. But clients will need HDF5 include files,
      # so we have to explicitly put them into the interface.
      # See ../cmake_modules/find_prerequisites.cmake for defintion of HDF5_INCLUDE_DIR.

      string(APPEND _lps_escaped_paths "\;${HDF5_INCLUDE_DIR}")
      # message("shared _lps_escaped_paths= ${_lps_escaped_paths}")

      target_include_directories(${SHEAVES_SHARED_LIB} PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> $<INSTALL_INTERFACE:include> )   

      #target_link_libraries(${SHEAVES_SHARED_LIB} 
      #   PRIVATE -Wl,-Bstatic hdf5 m rt z szip -Wl,-Bdynamic 
      #   PUBLIC dl)  

      target_link_libraries(${SHEAVES_SHARED_LIB} PRIVATE -Wl,-Bstatic hdf5-static -Wl,-Bdynamic PUBLIC dl)  
      set_target_properties(${SHEAVES_SHARED_LIB} PROPERTIES OUTPUT_NAME sheaves)
      set_target_properties(${SHEAVES_SHARED_LIB} PROPERTIES LINKER_LANGUAGE CXX)
      set_target_properties(${SHEAVES_SHARED_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})  

      # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc 
      # symbol table. CMake apparently detects the presence of cdecl_dllspec in 
      # the source and places -D<LIBRARY>_EXPORTS into the preproc symbol 
      # table no matter the platform.

      set_target_properties(${SHEAVES_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
      
      # Library alias definitions

      add_custom_target(sheaves-static-lib)
      add_dependencies(sheaves-static-lib ${SHEAVES_STATIC_LIB})

      add_custom_target(sheaves-shared-lib)
      add_dependencies(sheaves-shared-lib ${SHEAVES_SHARED_LIB})

   endif()

   # message("Leaving sheaves/component_defintions::SheafSystem_add_sheaves_library_target")

endfunction(SheafSystem_add_sheaves_library_targets)



#
# Create the bindings targets for this component.
#
function(SheafSystem_add_sheaves_java_bindings_targets)

   # Requires swig and java to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_JAVA)
   dbc_require(SHEAFSYSTEM_FOUND_JNI)

   include_directories(${SHEAVES_IPATHS})
   include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
   include_directories(${SHEAVES_JAVA_BINDING_SRC_DIR})
   include_directories(${SHEAVES_COMMON_BINDING_SRC_DIR})
   
   set_source_files_properties(${SHEAVES_JAVA_BINDING_SRC_DIR}/${SHEAVES_SWIG_JAVA_INTERFACE}
      PROPERTIES CPLUSPLUS ON)

   # $$ISSUE: why should c++ extension be cxx?
   
   set(SWIG_CXX_EXTENSION "cxx")
   set(CMAKE_SWIG_FLAGS -package bindings.java)
   
   # Add the java binding library target

   swig_add_module(${SHEAVES_JAVA_BINDING_LIB} java
      ${SHEAVES_JAVA_BINDING_SRC_DIR}/${SHEAVES_SWIG_JAVA_INTERFACE})
   
   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${SHEAVES_JAVA_BINDING_LIB} ${SHEAVES_IMPORT_LIB})
      swig_link_libraries(${SHEAVES_JAVA_BINDING_LIB}
         PUBLIC ${JAVA_JDK_LIBS} ${SHEAVES_IMPORT_LIB}
         PRIVATE hdf5-static)
      set_target_properties(${SHEAVES_JAVA_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Java")   
      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${SHEAVES_JAVA_BINDING_LIB} ${SHEAVES_SHARED_LIB})
      target_link_libraries(${SHEAVES_JAVA_BINDING_LIB} ${JAVA_JDK_LIBS} ${SHEAVES_SHARED_LIB})

   endif()      
   
   # Establish CXX as the linker language for this library

   set_target_properties(${SHEAVES_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${SHEAVES_JAVA_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})
   
   # Create the bindings jar file
   # Output path in windows differs slightly from Linux. CMake wont allow a 
   # conditional inside add_custom_target, so we have to do it outside.

   if(SHEAFSYSTEM_WINDOWS)

      # Windows

      # Set the cumulative classpath variable for this component

      set(SHEAVES_CLASSPATH 
         ${JMF_JAR}
        "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${SHEAVES_JAVA_BINDING_JAR}" 
         CACHE STRING "Cumulative classpath for sheaves" FORCE)
      mark_as_advanced(FORCE SHEAVES_CLASSPATH) 
      
      add_custom_target(sheaves_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E copy
            ${SHEAVES_JAVA_BINDING_SRC_DIR}/base_client.java
            ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy
            ${SHEAVES_JAVA_BINDING_SRC_DIR}/base_server.java
            ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath . -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${SHEAVES_JAVA_BINDING_JAR}  
            bindings/java/*.class
         )

      add_dependencies(sheaves_java_binding.jar ${SHEAVES_JAVA_BINDING_LIB})

      set_target_properties(sheaves_java_binding.jar PROPERTIES FOLDER "Component Binding Jars")
      
      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(sheaves-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} 
               -windowtitle "sheaves documentation" 
               -classpath "${SHEAVES_CLASSPATH}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/sheaves  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(sheaves-java-docs ${SHEAVES_JAVA_BINDING_JAR})

         set_target_properties(sheaves-java-docs PROPERTIES FOLDER "Documentation Targets")

      endif(SHEAFSYSTEM_DOC_TARGETS)

   elseif(SHEAFSYSTEM_LINUX)

      # Linux

      # Set the cumulative classpath variable for this component

      set(SHEAVES_CLASSPATH 
         ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${SHEAVES_JAVA_BINDING_JAR} 
         CACHE STRING "Cumulative classpath for sheaves" FORCE)
      mark_as_advanced(FORCE SHEAVES_CLASSPATH) 

      add_custom_target(sheaves_java_binding.jar 
         ALL
         COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SHEAVES_JAVA_BINDING_SRC_DIR}/base_client.java 
            ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            ${SHEAVES_JAVA_BINDING_SRC_DIR}/base_server.java 
            ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${CMAKE_COMMAND} -E echo "Compiling Java files..."
         COMMAND ${Java_JAVAC_EXECUTABLE} -classpath . -d . *.java
         COMMAND ${CMAKE_COMMAND} -E echo "Creating jar file..."
         COMMAND ${Java_JAR_EXECUTABLE} cvf 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${SHEAVES_JAVA_BINDING_JAR}  
            bindings/java/*.class
         )        

      add_dependencies(sheaves_java_binding.jar ${SHEAVES_JAVA_BINDING_LIB})

      set_target_properties(sheaves_java_binding.jar PROPERTIES FOLDER "Library Jars") 

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(sheaves-java-binding)
      add_dependencies(sheaves-java-binding sheaves_java_binding.jar)

      # Java documentation

      if(SHEAFSYSTEM_DOC_TARGETS)

         add_custom_target(sheaves-java-docs 
            ALL
            COMMAND ${Java_JAVADOC_EXECUTABLE} 
               -windowtitle "sheaves Java binding documentation" 
               -classpath "${SHEAVES_CLASSPATH}" 
               -d  ${CMAKE_BINARY_DIR}/documentation/java/sheaves  
               *.java 
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )

         add_dependencies(sheaves-java-docs ${SHEAVES_JAVA_BINDING_JAR})
 
      endif(SHEAFSYSTEM_DOC_TARGETS)

   endif(SHEAFSYSTEM_WINDOWS)

endfunction(SheafSystem_add_sheaves_java_bindings_targets)

#
# Create the bindings targets for this component.
#
function(SheafSystem_add_sheaves_csharp_bindings_targets)

   # Requires swig and csharp to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_CSHARP)
   
   set(CMAKE_SWIG_FLAGS -c++ -namespace sheaf)        

   # Add the csharp binding library target

   set_source_files_properties(${SHEAVES_CSHARP_BINDING_SRC_DIR}/${SHEAVES_SWIG_CSHARP_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${SHEAVES_CSHARP_BINDING_LIB} csharp 
      ${SHEAVES_CSHARP_BINDING_SRC_DIR}/${SHEAVES_SWIG_CSHARP_INTERFACE})

   if(SHEAFSYSTEM_WINDOWS)

      swig_link_libraries(${SHEAVES_CSHARP_BINDING_LIB}
         PUBLIC ${SHEAVES_IMPORT_LIB} ${CSHARP_LIBRARY}
         PRIVATE hdf5-static)
      set_target_properties(${SHEAVES_CSHARP_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - CSharp")
      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      # Linux 

      add_dependencies(${SHEAVES_CSHARP_BINDING_LIB} ${SHEAVES_SHARED_LIB})
      target_link_libraries(${SHEAVES_CSHARP_BINDING_LIB} ${SHEAVES_SHARED_LIB} ${CSHARP_LIBRARY})

   endif()    
   
   set_target_properties(${SHEAVES_CSHARP_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${SHEAVES_CSHARP_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})

   # Create the csharp assembly

   if(SHEAFSYSTEM_WINDOWS)

      add_custom_target(${SHEAVES_CSHARP_BINDING_ASSY} 
         ALL
         COMMAND ${CMAKE_COMMAND} -E echo ""
         COMMAND ${CMAKE_COMMAND} -E echo "Creating Csharp Binding for sheaves ..."
         COMMAND ${CMAKE_COMMAND} -E echo ""                           
         COMMAND ${CSHARP_COMPILER} /nologo /noconfig /warn:1 
            /errorreport:prompt /target:library 
            /out:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${SHEAVES_CSHARP_BINDING_ASSY} 
            ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )
      add_dependencies(${SHEAVES_CSHARP_BINDING_ASSY} ${SHEAVES_CSHARP_BINDING_LIB})

      set_target_properties(${SHEAVES_CSHARP_BINDING_ASSY} PROPERTIES FOLDER "CSharp Assembly Targets")

   else()

      add_custom_target(${SHEAVES_CSHARP_BINDING_ASSY} 
         ALL
         COMMAND ${CSHARP_COMPILER} -target:library -nowarn:0114,0108 
         -out:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${SHEAVES_CSHARP_BINDING_ASSY}  
         ${CMAKE_CURRENT_BINARY_DIR}/*.cs
         )      
      add_dependencies(${SHEAVES_CSHARP_BINDING_ASSY} ${SHEAVES_CSHARP_BINDING_LIB})

      # Add library alias; only in Linux because clutters up Solution Explorer too much

      add_custom_target(sheaves-csharp-binding)
      add_dependencies(sheaves-csharp-binding ${SHEAVES_CSHARP_BINDING_ASSY})

   endif()

endfunction(SheafSystem_add_sheaves_csharp_bindings_targets)

#
# Create the python bindings targets for this component.
#
function(SheafSystem_add_sheaves_python_bindings_targets)

   # Requires swig and python to build the bindings

   dbc_require(SHEAFSYSTEM_FOUND_SWIG)
   dbc_require(SHEAFSYSTEM_FOUND_PYTHONLIBS)

   set(CMAKE_SWIG_FLAGS -c++ -py3)

   include_directories(${SHEAFSYSTEM_PYTHON_INCLUDE_DIRS})
   
   set_source_files_properties(${SHEAVES_PYTHON_BINDING_SRC_DIR}/${SHEAVES_SWIG_PYTHON_INTERFACE} 
      PROPERTIES CPLUSPLUS ON)

   swig_add_module(${SHEAVES_PYTHON_BINDING_LIB} python 
      ${SHEAVES_PYTHON_BINDING_SRC_DIR}/${SHEAVES_SWIG_PYTHON_INTERFACE})

   if(SHEAFSYSTEM_WINDOWS)

      add_dependencies(${SHEAVES_PYTHON_BINDING_LIB} ${SHEAVES_IMPORT_LIB})

      swig_link_libraries(${SHEAVES_PYTHON_BINDING_LIB}
         PUBLIC ${SHEAVES_IMPORT_LIB} ${SHEAFSYSTEM_PYTHON_LIBRARIES}
         PRIVATE hdf5-static)

      # The leading underscore on a python library's name is apparently implicit to 
      # the swig python functions. If we want to refer to it, then we need to 
      # prepend an underscore.

      set_target_properties(${SHEAVES_PYTHON_BINDING_LIB}
         PROPERTIES FOLDER "Binding Targets - Python")

      set_source_files_properties(${swig_generated_file_fullname}
         PROPERTIES COMPILE_FLAGS "-DSHEAF_DLL_IMPORTS")

   else()

      add_dependencies(${SHEAVES_PYTHON_BINDING_LIB} ${SHEAVES_SHARED_LIB})
      swig_link_libraries(${SHEAVES_PYTHON_BINDING_LIB}
         ${SHEAVES_SHARED_LIB} ${SHEAFSYSTEM_PYTHON_LIBRARIES})

      # Add library alias; only in Linux because clutter up Solution Explorer too much

      add_custom_target(sheaves-python-binding)
      add_dependencies(sheaves-python-binding ${SHEAVES_PYTHON_BINDING_LIB})

   endif()
   
   set_target_properties(${SHEAVES_PYTHON_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)

   # Define the library version.

   set_target_properties(${SHEAVES_PYTHON_BINDING_LIB} PROPERTIES VERSION ${SHEAFSYSTEM_LIB_VERSION})  
   
endfunction(SheafSystem_add_sheaves_python_bindings_targets)


#
# Create the bindings targets for this component.
#
function(SheafSystem_add_sheaves_bindings_targets)

   # Can't add the bindings targets unless bindings are enabled.
   # Note that SHEAFSYSTEM_BUILD_BINDINGS implies Java, VTK, Swig, etc found, 
   # see SheafSystem_find_prerequisites

   dbc_require(SHEAFSYSTEM_BUILD_BINDINGS)

   include(${SHEAFSYSTEM_CMAKE_MODULE_PATH}/UseSWIG.cmake)

   SheafSystem_add_sheaves_java_bindings_targets()

   SheafSystem_add_sheaves_csharp_bindings_targets()

   SheafSystem_add_sheaves_python_bindings_targets()

   # Add aggregate bindings target for this component.

   add_custom_target(sheaves-bindings)
   add_dependencies(sheaves-bindings sheaves_java_binding.jar
      ${SHEAVES_CSHARP_BINDING_LIB} ${SHEAVES_PYTHON_BINDING_LIB})

endfunction(SheafSystem_add_sheaves_bindings_targets)


function(SheafSystem_add_sheaves_install_target)

   SheafSystem_add_component_install_target(sheaves)
   install(FILES ${SHEAVES_STD_HEADERS} DESTINATION include/${SHEAFSYSTEM_HEADER_SCOPE})
   
endfunction(SheafSystem_add_sheaves_install_target)
