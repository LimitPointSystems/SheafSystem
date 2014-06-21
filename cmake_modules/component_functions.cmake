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
# Contains all that is LPS specific; all flags, all macros, etc.
#


#------------------------------------------------------------------------------ 
# Variable Definition Section
#------------------------------------------------------------------------------

#
# Turn on project folders for Visual Studio.
#
if(WIN64MSVC OR WIN64INTEL)
    set_property(GLOBAL PROPERTY USE_FOLDERS On)
endif()
 
#
# Comvert the project name to UC
#
string(TOUPPER ${PROJECT_NAME} COMPONENT)

#
# Tell the compiler where to find the std_headers.
#
include_directories(${CMAKE_BINARY_DIR}/include)
 
#
# Tell the linker where to look for COMPONENT libraries.
#
link_directories(${CMAKE_BINARY_DIR}/lib)

#
# Set some variables for the Intel coverage utilities.
# $$TODO: Linux only for now -- hook up for Windows as well if we pursue 
# support for Intel.
#
if(LINUX64INTEL)
    set(UNCOVERED_COLOR DE0829 CACHE STRING "Color for uncovered code.")
    set(COVERED_COLOR 319A44 CACHE STRING "Color for covered code.")
    set(PARTIAL_COLOR E1EA43 CACHE STRING "Color for partially covered code.")
    # Lop the compiler name off the end of the CXX string
    string(REPLACE "/icpc" "" INTELPATH ${CMAKE_CXX_COMPILER})
    # The codecov executable
    set(CODECOV "${INTELPATH}/bin/codecov" CACHE STRING 
        "Intel Code coverage utility.")
    # The profmerge executable
    set(PROFMERGE "${INTELPATH}/bin/profmerge" CACHE STRING 
        "Intel dynamic profile merge utility." )
    # The compiler library path.
    set(INTEL_LIBPATH "${INTELPATH}/lib/intel64" CACHE STRING 
        "Intel C++ compiler library path." )
elseif(LINUX64GNU)
    # Lop the compiler name off the end of the CXX string to get the gnu root.
    string(REPLACE "bin/g++" "" GNUPATH ${CMAKE_CXX_COMPILER})
    # The compiler library path.
    set(GNU_LIBPATH "${GNUPATH}lib64" CACHE STRING 
        "GNU C++ compiler library path." )
endif()

#------------------------------------------------------------------------------
# Function Definition Section.
#------------------------------------------------------------------------------

#
# Check for and configure system cxx includes.
#
function(check_cxx_includes)

   include(CheckIncludeFileCXX)

    # C++ Headers for C Library Facilities

    if(NOT HAVE_CASSERT)
        status_message("Looking for C++ Headers For C Library Functions")   
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
        status_message("Looking for C++ Standard Library Headers")    
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

endfunction(check_cxx_includes)

#
# Check for C++ headers and configure the STD wrappers 
# for the current platform.
#
function(configure_std_headers)

    status_message("Configuring STD include files")

    # Glob all the .h.cmake.in files in std
    file(GLOB STD_INC_INS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/std 
        ${CMAKE_CURRENT_SOURCE_DIR}/std/*.h.in)

    # Configure the .h file from each .h.cmake.in
    foreach(input_file ${STD_INC_INS})
        # Strip .in from globbed filenames for output filenames
        string(REGEX REPLACE ".in$" ""  std_h ${input_file})
        message(STATUS "Creating ${CMAKE_BINARY_DIR}/include/${std_h} from std/${input_file}")
        list(APPEND std_incs ${CMAKE_BINARY_DIR}/include/${std_h})
        set(STD_HEADERS ${std_incs} CACHE STRING "STD Includes" FORCE)          
        # Configure the .h files
        configure_file(std/${input_file} ${CMAKE_BINARY_DIR}/include/${std_h})
    endforeach()

endfunction(configure_std_headers)

#
# Create the build output directories.
#
function(create_output_dirs)

    # Create build/include for STD header files.
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
    
    # Visual Studio will generate cmake_build_dir folders for the current build type.
    # Linux needs to be told.
    
    # These uber-verbose variable names have special meaning to cmake --
    # they are the cmake counterpart to what GNU autotools calls a "precious" variable.
    # Not a good idea to change them to anything shorter and sweeter; so don't.

    if(WIN64MSVC OR WIN64INTEL)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/bin PARENT_SCOPE)
        # Create build/lib for libraries.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
        # Create build/bin for executables.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)        
    else()
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin PARENT_SCOPE)
            
        # Create build/lib for libraries.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
        
        # Create build/bin for executables.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)        
   endif()

endfunction()

#
# Add the documentation targets.
# Default Doc state is "Dev"
#
function(add_doc_targets)
    if(DOC_TARGETS)
            if(DOC_STATE MATCHES Dev OR DOC_STATE MATCHES dev OR DOC_STATE MATCHES DEV)
                add_custom_target(doc ALL
                        COMMAND ${CMAKE_COMMAND} -E echo 
                        "Generating Developer Documentation ... " 
                        COMMAND ${CMAKE_COMMAND} -E make_directory 
                        ${CMAKE_BINARY_DIR}/documentation                    
                        COMMAND ${DOXYGEN_EXECUTABLE} 
                        ${CMAKE_BINARY_DIR}/dev_doxyfile
                                )
            else()
                add_custom_target(doc ALL
                        COMMAND ${CMAKE_COMMAND} -E echo 
                        "Generating User Documentation ... "  
                        COMMAND ${CMAKE_COMMAND} -E make_directory 
                        ${CMAKE_BINARY_DIR}/documentation                     
                        COMMAND ${DOXYGEN_EXECUTABLE} 
                        ${CMAKE_BINARY_DIR}/user_doxyfile
                                 )
            endif()
                    set_target_properties(doc PROPERTIES FOLDER "Documentation Targets")    
    endif() 
endfunction(add_doc_targets)
    
#
# Add the list of clusters to this component.
#
function(add_clusters clusters)

    foreach(cluster ${clusters})
        #Add each cluster subdir to the project. 
        add_subdirectory(${cluster})
        #Add each cluster to the compiler search path.
        include_directories(${cluster})
        # Add the fully-qualified cluster names to this component's ipath var
        set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} 
        ${CMAKE_CURRENT_SOURCE_DIR}/${cluster} CACHE 
        STRING "Include paths for ${PROJECT_NAME}" FORCE)
    endforeach()

endfunction(add_clusters)

# 
# Declare and initialize all variables that are component-specific.
#
function(set_component_vars)

    if(WIN64MSVC OR WIN64INTEL)
        set(${COMPONENT}_DYNAMIC_LIB ${PROJECT_NAME} 
            CACHE STRING "${PROJECT_NAME} dynamic link library")
        set(${COMPONENT}_IMPORT_LIB ${PROJECT_NAME} 
            CACHE STRING "${PROJECT_NAME} import library")
        set(${COMPONENT}_CSHARP_BINDING_ASSY 
            ${PROJECT_NAME}_csharp_assembly.dll 
            CACHE STRING "${PROJECT_NAME} csharp binding assembly name")
    else()
        set(${COMPONENT}_SHARED_LIB lib${PROJECT_NAME}.so 
            CACHE STRING "${PROJECT_NAME} shared library")
        set(${COMPONENT}_STATIC_LIB lib${PROJECT_NAME}.a 
            CACHE STRING "${PROJECT_NAME} static library")
        set(${COMPONENT}_CSHARP_BINDING_ASSY 
            ${PROJECT_NAME}_csharp_assembly.so 
            CACHE STRING "${PROJECT_NAME} csharp binding assembly name")
    endif()
            
    set(${COMPONENT}_COMMON_BINDING_SRC_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/src 
        CACHE STRING "${PROJECT_NAME} common binding source directory")
    set(${COMPONENT}_SWIG_COMMON_INTERFACE 
        ${PROJECT_NAME}_common_binding.i 
        CACHE STRING "${PROJECT_NAME} common interface filename")
    set(${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE 
        ${PROJECT_NAME}_common_binding_includes.i 
        CACHE STRING "${PROJECT_NAME} common includes interface filename" )
      
    set(${COMPONENT}_JAVA_BINDING_LIB ${PROJECT_NAME}_java_binding 
        CACHE STRING "${PROJECT_NAME} java binding library basename")
    set(${COMPONENT}_JAVA_BINDING_SRC_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/java/src 
        CACHE STRING "${PROJECT_NAME} java binding source directory")
    set(${COMPONENT}_SWIG_JAVA_INTERFACE ${PROJECT_NAME}_java_binding.i 
        CACHE STRING "${PROJECT_NAME} java binding interface file")
    set(${COMPONENT}_JAVA_BINDING_JAR ${PROJECT_NAME}_java_binding.jar 
        CACHE STRING "${PROJECT_NAME} java binding jar name")

    set(${COMPONENT}_PYTHON_BINDING_LIB ${PROJECT_NAME}_python_binding 
        CACHE STRING "${PROJECT_NAME} python binding library name")    
    set(${COMPONENT}_PYTHON_BINDING_SRC_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/python/src 
        CACHE STRING "${PROJECT_NAME} python source directory")
    set(${COMPONENT}_SWIG_PYTHON_INTERFACE ${PROJECT_NAME}_python_binding.i 
        CACHE STRING "${PROJECT_NAME} python binding interface file")
    
    set(${COMPONENT}_CSHARP_BINDING_LIB ${PROJECT_NAME}_csharp_binding 
        CACHE STRING "${PROJECT_NAME} csharp binding library name")
    set(${COMPONENT}_CSHARP_BINDING_SRC_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/bindings/csharp/src 
        CACHE STRING "${PROJECT_NAME} csharp source directory")
    set(${COMPONENT}_SWIG_CSHARP_INTERFACE ${PROJECT_NAME}_csharp_binding.i 
        CACHE STRING "${PROJECT_NAME} csharp binding interface file")

    
    # Mark all the above as "advanced"
    mark_as_advanced(FORCE ${COMPONENT}_BINARY_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_LIB_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_DYNAMIC_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_IMPORT_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_SHARED_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_STATIC_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_COMMON_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_COMMON_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_JAVA_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_JAVA_BINDING_JAR)
    mark_as_advanced(FORCE ${COMPONENT}_PYTHON_BINDING_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_PYTHON_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_PYTHON_INTERFACE)
    mark_as_advanced(FORCE ${COMPONENT}_CSHARP_BINDING_LIB)
    mark_as_advanced(FORCE ${COMPONENT}_CSHARP_BINDING_SRC_DIR)
    mark_as_advanced(FORCE ${COMPONENT}_SWIG_CSHARP_INTERFACE)
    
endfunction(set_component_vars)

#
# Export this component's library targets and list of includes
#
function(write_exports_file)

    message(STATUS 
        "Writing ${PROJECT_NAME} detail to ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}")
    if(WIN64MSVC OR WIN64INTEL)
        export(TARGETS ${${COMPONENT}_IMPORT_LIB} APPEND 
            FILE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(${COMPONENT}_IMPORT_LIB ${${COMPONENT}_IMPORT_LIB} CACHE STRING \"${PROJECT_NAME} Win32 import library \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative Win32 import library list\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    else()
        export(TARGETS ${${COMPONENT}_SHARED_LIB} 
            ${${COMPONENT}_STATIC_LIB} APPEND FILE 
            ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
        file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    endif()
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_INCS ${${COMPONENT}_INCS} CACHE STRING \"${PROJECT_NAME} includes\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} CACHE STRING \"${PROJECT_NAME} include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATHS} CACHE STRING \"${PROJECT_NAME} cumulative include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_STATIC_LIB ${${COMPONENT}_STATIC_LIB} CACHE STRING \"${PROJECT_NAME} static library \")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")    
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_SHARED_LIB ${${COMPONENT}_SHARED_LIB} CACHE STRING \"${PROJECT_NAME} shared library \")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")    
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_CLASSPATH ${${COMPONENT}_CLASSPATH} CACHE STRING \"${PROJECT_NAME} Java classpath\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_BIN_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} binary output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
        "set(${COMPONENT}_LIB_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    if("${COMPONENT}" MATCHES "SHEAVES")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(HDF_INCLUDE_DIR ${HDF5_INCLUDE_DIRS} CACHE STRING \"HDF5 Include Path \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    endif()
                
    if("${COMPONENT}" MATCHES "TOOLS")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(VTK_LIB_DIR @VTK_LIB_DIR@ CACHE PATH \"VTK library path\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(VTK_LIBS @VTK_LIBS@ CACHE PATH \"VTK libraries \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")        
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(VTK_BIN_DIR @VTK_BIN_DIR@ CACHE PATH  \"VTK DLL path\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(VTK_INC_DIR @VTK_INC_DIRS@ CACHE PATH  \"VTK DLL path\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} 
            "set(VTK_LIBS ${VTK_LIBS} CACHE STRING \"VTK Libraries\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")                  
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")        
        file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
            "set(JMF_JAR ${JMF_JAR} CACHE STRING \"JMF jar location\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")        

    endif()             
endfunction(write_exports_file)

#
# Export this component's library targets and list of includes for install
# The file locations on an install (includes, libs, etc) are different
# than they are in a build tree. The install config produces
# a .cmake.in file that is configured by the client.
#
function(export_install_config_file_vars)

    if(WIN64MSVC OR WIN64INTEL)
        export(TARGETS ${${COMPONENT}_DYNAMIC_LIB} 
            APPEND FILE ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE})
        file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
            "set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative import library list\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
    else()
        export(TARGETS ${${COMPONENT}_SHARED_LIB} 
            ${${COMPONENT}_STATIC_LIB} 
            APPEND FILE ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE})
        if("${COMPONENT}" MATCHES "SHEAVES")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")    
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            # This variable should be SHEAFSYSTEM_LIB_OUTPUT_DIR. Fix it.
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(${COMPONENT}_LIB_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        else()
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")    
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        endif()

        if("${COMPONENT}" MATCHES "TOOLS")        
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
                "set(JMF_JAR ${JMF_JAR} CACHE STRING \"JMF jar location\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        endif()             
    endif()
    file(APPEND  ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
        "set(${COMPONENT}_IPATH @SHEAFSYSTEM_HOME@/include CACHE STRING \"${PROJECT_NAME} include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} 
        "set(${COMPONENT}_IPATHS @SHEAFSYSTEM_HOME@/include CACHE STRING \"${PROJECT_NAME} cumulative include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")

endfunction(export_install_config_file_vars)

#
# Generate the installed <project>-exports file. Replace hardcoded vars with cmake substitution vars.
#
function(generate_install_config_file)

    file(READ ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} INSTALL_FILE_CONTENTS)

    string(REPLACE ${CMAKE_BINARY_DIR} "\@SHEAFSYSTEM_HOME\@" 
        MASSAGED_OUTPUT "${INSTALL_FILE_CONTENTS}")

    file(WRITE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "${MASSAGED_OUTPUT}")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in 
        "set(VTK_LIBS ${VTK_LIBS} CACHE STRING \"VTK Runtime Libraries\" FORCE)\n")      
endfunction(generate_install_config_file)

#
# Append sources to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_sources)

    # Prepend the cluster name to each member of the srcs list
    foreach(src ${SRCS})
        list(APPEND lsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()
        
    set(${COMPONENT}_SRCS ${${COMPONENT}_SRCS} 
        ${lsrcs} CACHE STRING "${PROJECT} sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_SRCS)

endfunction()

#
# Append incs to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_includes)

    get_filename_component(CLUSTERNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    # Prepend the cluster name to each member of the srcs list
    if(NOT ${CLUSTERNAME} STREQUAL "template_instantiations")
        foreach(src ${SRCS})
            string(REGEX REPLACE ".cc$" ".h"  inc ${src})
            list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
        endforeach()
   endif()
    
    # Prepend the cluster name to each member of the additional_incs list
    foreach(inc ${ADDITIONAL_INCS})
        list(APPEND lincs ${CMAKE_CURRENT_SOURCE_DIR}/${inc})
    endforeach()

    set(${COMPONENT}_INCS ${${COMPONENT}_INCS} 
        ${lincs} CACHE STRING "${PROJECT} includes." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_INCS)

endfunction(collect_includes)

#
# Append unit test executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_unit_test_sources)

    # Prepend the path to each member of the check_execs list
    foreach(src ${UNIT_TEST_SRCS})
        list(APPEND chksrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()
    
    set(${COMPONENT}_UNIT_TEST_SRCS ${${COMPONENT}_UNIT_TEST_SRCS} 
        ${chksrcs} CACHE STRING "Unit test sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_UNIT_TEST_SRCS)
    
endfunction(collect_unit_test_sources)

#
# Append standalone executables to their respective component variables
# Used in cluster level CMakeLists.txt
#
function(collect_example_sources)

    # Prepend the path to each member of the execs list
    foreach(src ${EXAMPLE_SRCS})
        list(APPEND execsrcs ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()

    set(${COMPONENT}_EXAMPLE_SRCS ${${COMPONENT}_EXAMPLE_SRCS} 
        ${execsrcs} CACHE STRING "EXEC sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_EXAMPLE_SRCS)

endfunction(collect_example_sources)

# 
# Convenience wrapper for the massage function.
# The Eclipse Cmakeed plugin renders this pretty much obsolete
# from a pregramming viewpoint, but the syntax is prettier
# than what it wraps.
#
function(status_message txt)

    # Let the user know what's being configured
    message(STATUS " ")
    message(STATUS "${txt} - ")
    message(STATUS " ")

endfunction()

# 
# Convenience routine for diagnostic output during configure phase.
# Displays a list of included directories for module it is called in.
#
function(showincs)
    message(STATUS "Displaying include directories for ${PROJECT_NAME}:")
    message(STATUS "===================================================")    
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "dir='${dir}'")
    endforeach() 
    message(STATUS "===================================================")       
endfunction()


# 
# Install any prerequisites that need to ship with our libs
#
function(install_prereqs)
    # Prerequisite components install
    # Install only the HDF includes we use 
    foreach(inc ${HDF5_INCS})
        install(FILES ${HDF5_INCLUDE_DIRS}/${inc} DESTINATION include
        PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ WORLD_READ)
    endforeach()

    install(DIRECTORY ${PROJECT_BINARY_DIR}/documentation/ DESTINATION documentation)
    install(DIRECTORY ${CMAKE_MODULE_PATH}/css DESTINATION documentation)
    install(DIRECTORY ${CMAKE_MODULE_PATH}/images DESTINATION documentation)
    
endfunction(install_prereqs)

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
