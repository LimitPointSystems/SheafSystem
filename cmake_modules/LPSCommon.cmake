#
# Copyright (c) 2013 Limit Point Systems, Inc.
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
# $$TODO: Linux only for now -- hook up for Windows as well.
#
if(LINUX64INTEL)
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
elseif(LINUX64GNU)
    # Lop the compiler name off the end of the CXX string to get the gnu root.
    string(REPLACE "bin/g++" "" GNUPATH ${CMAKE_CXX_COMPILER})
    # The compiler library path.
    set(GNU_LIBPATH "${GNUPATH}lib64" CACHE STRING "GNU C++ compiler library path." )
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
    check_include_file_cxx(typeinfo HAVE_TYPEINFO)
    check_include_file_cxx(utility HAVE_UTILITY)
    check_include_file_cxx(valarray HAVE_VALARRAY)
    check_include_file_cxx(vector HAVE_VECTOR)

    # STL

    if(NOT (HAVE_HASH_MAP OR HAVE_EXT_HASH_MAP))
        status_message("Looking for C++ STL Headers")
    endif()

    check_include_file_cxx(hash_map HAVE_HASH_MAP)
    check_include_file_cxx(ext/hash_map HAVE_EXT_HASH_MAP)
    check_include_file_cxx(hash_set HAVE_HASH_SET)
    check_include_file_cxx(ext/hash_set HAVE_EXT_HASH_SET)    
    check_include_file_cxx(slist HAVE_SLIST)
    check_include_file_cxx(ext/slist HAVE_EXT_SLIST)
    
    # C++ TR1 Extensions

    if(NOT (HAVE_UNORDERED_MAP OR HAVE_TR1_UNORDERED_MAP))
        status_message("Looking for C++ TR1 Headers") 
    endif()

    check_include_file_cxx(unordered_map HAVE_UNORDERED_MAP) 
    check_include_file_cxx(tr1/unordered_map HAVE_TR1_UNORDERED_MAP) 
    check_include_file_cxx(unordered_set HAVE_UNORDERED_SET)
    check_include_file_cxx(tr1/unordered_set HAVE_TR1_UNORDERED_SET)

endfunction(check_cxx_includes)

#
# Check for C++ headers and configure the STD wrappers 
# for the current platform.
#
function(configure_std_headers)

    status_message("Configuring STD include files")

    # Glob all the .h.cmake.in files in std
    file(GLOB STD_INC_INS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/std ${CMAKE_CURRENT_SOURCE_DIR}/std/*.h.cmake.in)

    # Configure the .h file from each .h.cmake.in
    foreach(input_file ${STD_INC_INS})
        # Strip .cmake.in from globbed filenames for output filenames
        string(REGEX REPLACE ".cmake.in$" ""  std_h ${input_file})
        message(STATUS "Creating ${CMAKE_BINARY_DIR}/include/${std_h} from std/${input_file}")
        list(APPEND std_incs ${CMAKE_BINARY_DIR}/include/${std_h})
        set(STD_HEADERS ${std_incs} CACHE STRING "STD Includes" FORCE)          
        # Configure the .h files
        configure_file(std/${input_file} ${CMAKE_BINARY_DIR}/include/${std_h})
    endforeach()

endfunction(configure_std_headers)

#
# Set the compiler flags per build configuration
#
function(set_compiler_flags)

       # Clear all cmake's intrinsic vars. If we don't, then their values will be appended to our
       # compile and link lines.
       set(CMAKE_CXX_FLAGS "" CACHE STRING "CXX Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "Debug Shared Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Exe Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS "" CACHE STRING "Module Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "" CACHE STRING "Module Linker Flags" FORCE)
       set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "Module Linker Flags" FORCE) 
        
       # Toggle multi-process compilation in Windows
       # Set in system_definitions.cmake
       if(ENABLE_WIN32_MP)
           set(MP "/MP")
       else()
           set(MP "")
       endif()
        
    if(WIN64MSVC)
       set(LPS_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /EHsc ${OPTIMIZATION} /D_HDF5USEDLL_" CACHE STRING "C++ Compiler Flags" FORCE)
       set(LPS_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /MACHINE:X64"  CACHE STRING "Linker Flags" FORCE)

    elseif(WIN64INTEL)
       set(LPS_CXX_FLAGS "/D_USRDLL ${MP} /GR /nologo /DWIN32 /D_WINDOWS /W1 /wd2651 /EHsc ${OPTIMIZATION} /Qprof-gen:srcpos /D_HDF5USEDLL_" CACHE STRING "C++ Compiler Flags" FORCE)
       set(LPS_SHARED_LINKER_FLAGS "/INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /MACHINE:X64"  CACHE STRING "Linker Flags" FORCE) 
       
    elseif(LINUX64INTEL)
        if(ENABLE_COVERAGE)
            if(INTELWARN)
               set(LPS_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ${OPTIMIZATION} -prof-gen=srcpos")
            else()
               set(LPS_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ${OPTIMIZATION} -prof-gen=srcpos")
            endif()
        else()
            if(INTELWARN)
               set(LPS_CXX_FLAGS "-ansi -m64 -w1 -wd186,1125 -Wno-deprecated ${OPTIMIZATION}")
            else()
               set(LPS_CXX_FLAGS "-ansi -m64 -w0 -Wno-deprecated ${OPTIMIZATION}")
            endif()
       endif() # ENABLE_COVERAGE        
    elseif(LINUX64GNU)
       set(LPS_CXX_FLAGS "-ansi -m64 -Wno-deprecated ${OPTIMIZATION}")
        
    #$$TODO: A 32 bit option is not needed. Do away with this case.
    else() # Assume 32-bit i686 linux for the present
       set(LPS_CXX_FLAGS "-ansi -m32 -Wno-deprecated ${OPTIMIZATION}")
    endif()

    #                 
    # DEBUG_CONTRACTS section
    #
        
    # Configuration specific flags 
    if(WIN64MSVC OR WIN64INTEL)
#        if(${USE_VTK})     
#            set(CMAKE_CXX_FLAGS_DEBUG-CONTRACTS "${LPS_CXX_FLAGS} /Zi /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=1\" /MDd /DUSE_VTK" CACHE
#                STRING "Flags used by the C++ compiler for Debug-contracts builds" FORCE)
#        else()
             set(CMAKE_CXX_FLAGS_DEBUG-CONTRACTS "${LPS_CXX_FLAGS} /Zi /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=1\" /MDd" CACHE
                STRING "Flags used by the C++ compiler for Debug-contracts builds" FORCE)       
#        endif()
    else()
#        if(${USE_VTK})
#            set(CMAKE_CXX_FLAGS_DEBUG-CONTRACTS "${LPS_CXX_FLAGS} -g -DUSE_VTK " CACHE
#                STRING "Flags used by the C++ compiler for Debug-contracts builds" FORCE)
#        else()         
            set(CMAKE_CXX_FLAGS_DEBUG-CONTRACTS "${LPS_CXX_FLAGS} -g" CACHE
                STRING "Flags used by the C++ compiler for Debug-contracts builds" FORCE)
#        endif()
    endif()
    
    # True for all currently supported platforms    
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG-CONTRACTS ${CMAKE_EXE_LINKER_FLAGS}  CACHE
        STRING "Flags used by the linker for executables for Debug-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG-CONTRACTS ${LPS_SHARED_LINKER_FLAGS} CACHE
        STRING "Flags used by the linker for shared libraries for Debug-contracts builds" FORCE)
    mark_as_advanced(CMAKE_CXX_FLAGS_DEBUG-CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_DEBUG-CONTRACTS CMAKE_SHARED_LINKER_FLAGS_DEBUG-CONTRACTS)

    #                 
    # DEBUG_NO_CONTRACTS section
    #      

    # Configuration specific flags 
    if(WIN64MSVC OR WIN64INTEL)
#        if(${USE_VTK}) 
#            set(CMAKE_CXX_FLAGS_DEBUG-NO-CONTRACTS "${LPS_CXX_FLAGS} /Zi /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=1\" /MDd /DUSE_VTK /DNDEBUG" CACHE
#                STRING "Flags used by the C++ compiler for Debug-no-contracts builds" FORCE)
#         else()   
            set(CMAKE_CXX_FLAGS_DEBUG-NO-CONTRACTS "${LPS_CXX_FLAGS} /Zi /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=1\" /MDd /DNDEBUG" CACHE
                STRING "Flags used by the C++ compiler for Debug-no-contracts builds" FORCE)
#         endif()
    else()
#        if(${USE_VTK})    
#            set(CMAKE_CXX_FLAGS_DEBUG-NO-CONTRACTS "${LPS_CXX_FLAGS} -g -DNDEBUG -DUSE_VTK" CACHE
#                STRING "Flags used by the C++ compiler for Debug-no-contracts builds" FORCE)
#        else()
            set(CMAKE_CXX_FLAGS_DEBUG-NO-CONTRACTS "${LPS_CXX_FLAGS} -g -DNDEBUG" CACHE
                STRING "Flags used by the C++ compiler for Debug-no-contracts builds" FORCE)
#        endif()
    endif()

    # True for all currently supported platforms       
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG-NO-CONTRACTS ${CMAKE_EXE_LINKER_FLAGS} CACHE
        STRING "Flags used by the linker for executables for Debug-no-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG-NO-CONTRACTS ${LPS_SHARED_LINKER_FLAGS} CACHE
        STRING "Flags used by the linker for shared libraries for Debug-no-contracts builds" FORCE)
    mark_as_advanced(CMAKE_CXX_FLAGS_DEBUG-NO-CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_DEBUG-NO-CONTRACTS CMAKE_SHARED_LINKER_FLAGS_DEBUG-NO-CONTRACTS)
    #                 
    # RELEASE_CONTRACTS section
    #

    # Configuration specific flags 
    if(WIN64MSVC OR WIN64INTEL)
#     if(${USE_VTK})
#        set(CMAKE_CXX_FLAGS_RELEASE-CONTRACTS "${LPS_CXX_FLAGS} /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=0\" /DUSE_VTK /MD" CACHE
#            STRING "Flags used by the C++ compiler for Release-contracts builds" FORCE)
#      else()   
        set(CMAKE_CXX_FLAGS_RELEASE-CONTRACTS "${LPS_CXX_FLAGS} /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=0\" /MD" CACHE
            STRING "Flags used by the C++ compiler for Release-contracts builds" FORCE)
#     endif()
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE-CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD"  CACHE
        STRING "Flags used by the linker for executables for Release-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE-CONTRACTS "${LPS_SHARED_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" CACHE
        STRING "Flags used by the linker for shared libraries for Release-contracts builds" FORCE)   
    else()
        set(CMAKE_CXX_FLAGS_RELEASE-CONTRACTS "${LPS_CXX_FLAGS}" CACHE
            STRING "Flags used by the C++ compiler for Release-contracts builds" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE-CONTRACTS "${CMAKE_EXE_LINKER_FLAGS}"  CACHE
        STRING "Flags used by the linker for executables for Release-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE-CONTRACTS "${LPS_SHARED_LINKER_FLAGS}" CACHE
        STRING "Flags used by the linker for shared libraries for Release-contracts builds" FORCE)
    endif()
    
    # True for all currently supported platforms        
    mark_as_advanced(CMAKE_CXX_FLAGS_RELEASE-CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_RELEASE-CONTRACTS CMAKE_SHARED_LINKER_FLAGS_RELEASE-CONTRACTS
                    )
    #                 
    # RELEASE_NO_CONTRACTS section
    #

    # Configuration specific flags         
    if(WIN64MSVC OR WIN64INTEL)
#        if(${USE_VTK})
#            set(CMAKE_CXX_FLAGS_RELEASE-NO-CONTRACTS "${LPS_CXX_FLAGS} /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=0\" /MD /DUSE_VTK /DNDEBUG" CACHE
#                STRING "Flags used by the C++ compiler for Release-no-contracts builds" FORCE)
#       else()        
            set(CMAKE_CXX_FLAGS_RELEASE-NO-CONTRACTS "${LPS_CXX_FLAGS} /D\"_SECURE_SCL=1\" /D\"_HAS_ITERATOR_DEBUG=0\" /MD /DNDEBUG" CACHE
                STRING "Flags used by the C++ compiler for Release-no-contracts builds" FORCE)
#      endif()               
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE-NO-CONTRACTS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" CACHE
        STRING "Flags used by the linker for executables for Release-no-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE-NO-CONTRACTS "${LPS_SHARED_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD" CACHE
        STRING "Flags used by the linker for shared libraries for Release-no-contracts builds" FORCE)
    else()
        set(CMAKE_CXX_FLAGS_RELEASE-NO-CONTRACTS "${LPS_CXX_FLAGS} -DNDEBUG" CACHE
            STRING "Flags used by the C++ compiler for Release-no-contracts builds" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE-NO-CONTRACTS "${CMAKE_EXE_LINKER_FLAGS}" CACHE
        STRING "Flags used by the linker for executables for Release-no-contracts builds" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE-NO-CONTRACTS "${LPS_SHARED_LINKER_FLAGS}" CACHE
        STRING "Flags used by the linker for shared libraries for Release-no-contracts builds" FORCE)
    endif()
    
    # True for all currently supported platforms        
    mark_as_advanced(CMAKE_CXX_FLAGS_RELEASE-NO-CONTRACTS
                     CMAKE_EXE_LINKER_FLAGS_RELEASE-NO-CONTRACTS CMAKE_SHARED_LINKER_FLAGS_RELEASE-NO-CONTRACTS
                  )

endfunction(set_compiler_flags)

#
# Create the build output directories.
#
function(create_output_dirs)

    # Create build/include for STD header files.
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
    
    # Visual Studio will generate cmake_build_dir folders for the current build type.
    # Linux needs to be told.
    # These uber-verbose variable names have special meaning to cmake --
    # the cmake counterpart to what GNU autotools calls a "precious" variable.
    # Not a good idea to change them to anything shorter and sweeter; so don't.

    if(WIN64MSVC OR WIN64INTEL)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin PARENT_SCOPE)
        # Create build/lib for libraries.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
        # Create build/bin for executables.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)        
    else()
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin PARENT_SCOPE)
        # Create build/lib for libraries.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
        # Create build/bin for executables.
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)        
   endif()
    

endfunction()

#
# Add the documentation targets.
# Default Doc state is "User"
#
function(add_doc_targets)

    if(DOXYGEN_FOUND)
        if(LPS_DOC_STATE MATCHES Dev OR LPS_DOC_STATE MATCHES dev OR LPS_DOC_STATE MATCHES DEV)
            add_custom_target(doc ALL
                    COMMAND ${CMAKE_COMMAND} -E echo "Generating Developer Documentation ... " 
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/documentation                    
                    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/dev_doxyfile
                    # Hack to correct a bug in doxygend. Dowxygen puts the graph legend into the output dir
                    # but looks for it in the location from which doxygen was run.
                    # This trick won't fly with an install, and needs to be addressed ASAP.
                    #COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/documentation/C++/graph_legend.png ${CMAKE_BINARY_DIR}
                            )
        else()
            add_custom_target(doc ALL
                    COMMAND ${CMAKE_COMMAND} -E echo "Generating User Documentation ... "  
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/documentation                     
                    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/user_doxyfile
                    # Hack to correct a bug in doxygend. Dowxygen puts the graph legend into the output dir
                    # but looks for it in the location from which doxygen was run
                    # This trick won't fly with an install, and needs to be addressed ASAP.
                    #COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/documentation/C++/graph_legend.png ${CMAKE_BINARY_DIR}
                             )
        endif()
                set_target_properties(doc PROPERTIES FOLDER "Documentation Targets")    
    endif()
                    
endfunction(add_doc_targets)

# 
#  Append file types to CMake's default clean list.
#
function(add_clean_files)
    #$$TODO: Probably need to get the location property from the targets and use it in this section.
    #Define the file types to be included in the clean operation.
    
    file(GLOB HDF_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/*.hdf)
    file(GLOB WIN_JAR_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Outdir)/*.jar)
    file(GLOB LINUX_JAR_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.jar)
    # Clean up the mess left by the Intel coverage tool
    file(GLOB DYN_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.dyn)
    file(GLOB DPI_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.dpi)
    file(GLOB SPI_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*.spi)
    # List of files with paths for SheafScope.jar build
    file(GLOB SCOPE_FILE_LIST ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/scopesrcs)
                
    # Append them to the list
    list(APPEND CLEAN_FILES ${HDF_FILES})
    list(APPEND CLEAN_FILES ${WIN_JAR_FILES})
    list(APPEND CLEAN_FILES ${LINUX_JAR_FILES})    
    list(APPEND CLEAN_FILES ${SWIG_JAVA_FILES})
    list(APPEND CLEAN_FILES ${DYN_FILES})
    list(APPEND CLEAN_FILES ${DPI_FILES})
    list(APPEND CLEAN_FILES ${SPI_FILES})
    list(APPEND CLEAN_FILES ${SCOPE_FILE_LIST})
    list(APPEND CLEAN_FILES "TAGS")
  
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_FILES}")

endfunction(add_clean_files) 

# 
# Establish a system level "bin" target
#
function(add_bin_target)

    add_custom_target(bin DEPENDS ${ALL_BIN_TARGETS})
    set_target_properties(bin PROPERTIES FOLDER "Bin Targets")
        
endfunction(add_bin_target)

#
# Add component specific bin targets. e.g., "sheaves-bin", "tools-bin", etc.
#
function(add_component_bin_target)

    add_custom_target(${PROJECT_NAME}-bin DEPENDS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_UNIT_TESTS} ${${COMPONENT}_EXAMPLES})
    # Add a bin target for this component to the system list. "make bin" will invoke this list.
    set(ALL_BIN_TARGETS ${ALL_BIN_TARGETS} ${PROJECT_NAME}-bin CACHE STRING "Aggregate list of component bin targets" FORCE)
        set_target_properties(${PROJECT_NAME}-bin PROPERTIES FOLDER "Bin Targets")
    mark_as_advanced(ALL_BIN_TARGETS) 

endfunction(add_component_bin_target)

# 
# Establish a system level "check" target
#
function(add_check_target)

    if(WIN64MSVC OR WIN64INTEL)
        # $$TODO: Spend a little time finding out what's going on here.
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR})
        add_dependencies(check ${${COMPONENT}_SHARED_LIB} ${ALL_CHECK_TARGETS})
    else()
        add_custom_target(check COMMAND DEPENDS ${ALL_CHECK_TARGETS})
    endif()
    set_target_properties(check PROPERTIES FOLDER "Check Targets")
        
endfunction(add_check_target)

#
# Add component specific check targets. e.g., "sheaves-check", "tools-check", etc.
#
function(add_component_check_target)

    add_custom_target(${PROJECT_NAME}-check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_UNIT_TESTS})
    # Add a check target for this component to the system list. "make check" will invoke this list.
    set(ALL_CHECK_TARGETS ${ALL_CHECK_TARGETS} ${PROJECT_NAME}-check CACHE STRING "Aggregate list of component check targets" FORCE)
        set_target_properties(${PROJECT_NAME}-check PROPERTIES FOLDER "Check Targets")
    mark_as_advanced(ALL_CHECK_TARGETS) 

endfunction(add_component_check_target)

#
# Add component specific coverage targets. e.g., "sheaves-coverage", "tools-coverage", etc.
#
#$$TODO: Expand this to cover windows/intel as well.
function(add_component_coverage_target)

    if(LINUX64INTEL)
        # if the component unit test list is not empty, generate coverage data.   
        if(NOT ${COMPONENT}_UNIT_TEST_SRCS STREQUAL "")
            add_custom_target(${PROJECT_NAME}-coverage DEPENDS ${PROJECT_NAME}-check
                COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${PROFMERGE}
                COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${CODECOV} -bcolor ${UNCOVERED_COLOR} -ccolor ${COVERED_COLOR} -pcolor ${PARTIAL_COLOR} -prj ${PROJECT_NAME} -txtbcvrgfull ${PROJECT_NAME}_cov.out -demang 
                COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/CODE_COVERAGE.HTML ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/index.html
                )
        else()
            # Component has no unit tests associated with it, make target an "informational no-op"
            add_custom_target(${PROJECT_NAME}-coverage
                COMMAND ${CMAKE_COMMAND} -E echo " " 
                COMMAND ${CMAKE_COMMAND} -E echo "   There are currently no unit tests for the ${PROJECT_NAME} component. Coverage results will not be generated." 
                COMMAND ${CMAKE_COMMAND} -E echo " "                      
                )
        endif()
            # Append the coverage target to the system wide list
            set(ALL_COVERAGE_TARGETS ${ALL_COVERAGE_TARGETS} ${PROJECT_NAME}-coverage CACHE STRING "Aggregate list of component coverage targets" FORCE)
            mark_as_advanced(ALL_COVERAGE_TARGETS)
    endif()

endfunction()

# 
# Establish a system level "coverage" target
#
#$$TODO: Expand this to cover windows/intel as well.
function(add_coverage_target)

    if(LINUX64INTEL)
        add_custom_target(coverage DEPENDS ${ALL_COVERAGE_TARGETS})
    endif()

endfunction()

# 
# Create a cmake test for each unit test executable.
#
function(add_test_targets)

    if(${USE_VTK})
        link_directories(${VTK_LIB_DIR})
    endif()
    # link_directories only applies to targets created after it is called.
    if(LINUX64GNU OR LINUX64INTEL)
        link_directories($CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR})
    else()
        link_directories($CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR})        
    endif()    
    # Let the user know what's being configured
    status_message("Configuring Unit Tests for ${PROJECT_NAME}")   
    foreach(t_cc_file ${${COMPONENT}_UNIT_TEST_SRCS})

        # Extract name of executable from source filename
        string(REPLACE .t.cc .t t_file_with_path ${t_cc_file})
        # Remove path information  
        get_filename_component(t_file ${t_file_with_path} NAME)

        set(${COMPONENT}_UNIT_TESTS ${${COMPONENT}_UNIT_TESTS} ${t_file} CACHE STRING "List of unit test binaries" FORCE)
        mark_as_advanced(${COMPONENT}_UNIT_TESTS)
        # If the target already exists, don't try to create it.
        if(NOT TARGET ${t_file})
             message(STATUS "Creating ${t_file} from ${t_cc_file}")
             add_executable(${t_file} EXCLUDE_FROM_ALL ${t_cc_file})
            # Make sure the library is up to date
            if(WIN64MSVC OR WIN64INTEL)
                # Supply the *_DLL_IMPORTS directive to preprocessor
                set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
                add_dependencies(${t_file} ${${COMPONENT}_IMPORT_LIBS})
            else()
                add_dependencies(${t_file} ${${COMPONENT}_SHARED_LIB})
            endif()

            if(LINUX64GNU OR LINUX64INTEL)
                target_link_libraries(${t_file} ${${COMPONENT}_SHARED_LIB} ${HDF5_LIBRARIES})
            elseif(WIN64MSVC OR WIN64INTEL)
                if(${USE_VTK})
                    target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS} ${HDF5_LIBRARIES} ${VTK_LIBS}) 
                else()
                    target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS} ${HDF5_LIBRARIES})                                         
                endif()
                # Insert the unit tests into the VS folder "unit test targets"
                set_target_properties(${t_file} PROPERTIES FOLDER "Unit Test Targets")
            endif()

            # Add a test target for ${t_file}
         
            add_test(${t_file} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${t_file})
            # Tag the test with the name of the current component.
            set_property(TEST ${t_file} PROPERTY LABELS "${PROJECT_NAME}")

            if(WIN64MSVC OR WIN64INTEL)
                # Set the PATH environment variable for CTest so the HDF5 and Fields dlls lie in it.
                set_tests_properties(${t_file} PROPERTIES ENVIRONMENT
                                     "PATH=${HDF5_LIBRARY_DIRS};$CMAKE_ARCHIVE_OUTPUT_DIRECTORY}:${CMAKE_CFG_INTDIR}")
            endif()
        endif()
    endforeach()

endfunction(add_test_targets)

# 
# Create a target for each example.
#
function(add_example_targets)

    if(${USE_VTK})
        link_directories(${VTK_LIB_DIR})
    endif()

    foreach(t_cc_file ${${COMPONENT}_EXAMPLE_SRCS})
        # link_directories only applies to targets created after it is called.
        if(LINUX64GNU OR LINUX64INTEL)
            link_directories($CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR})
        else()
            link_directories($CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR})
        endif()    
        # Let the user know what's being configured
        status_message("Configuring example executables for ${PROJECT_NAME}")   
        # Deduce name of executable from source filename
        string(REPLACE .cc "" t_file_with_path ${t_cc_file})
        # Remove path information so the executable goes into build/bin (or build/VisualStudio)
        # and not into build/bin/examples (or build/VisualStudio/examples)
        get_filename_component(t_file ${t_file_with_path} NAME)
        set(${COMPONENT}_EXAMPLES ${${COMPONENT}_EXAMPLES} ${t_file} CACHE STRING "List of example binaries" FORCE)
        mark_as_advanced(${COMPONENT}_EXAMPLES)    
        # Add building of executable and link with shared library
        message(STATUS "Creating ${t_file} from ${t_cc_file}")
        add_executable(${t_file} ${t_cc_file})
    
        # Make sure the library is up to date
        if(WIN64MSVC OR WIN64INTEL)
            add_dependencies(${t_file} ${${COMPONENT}_IMPORT_LIB})
            if(${USE_VTK})
                link_directories(${${COMPONENT}_OUTPUT_DIR}/$(OutDir) ${VTK_LIB_DIR})
                target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS} ${VTK_LIBS})
            else()
                link_directories(${${COMPONENT}_OUTPUT_DIR}/$(OutDir))
                target_link_libraries(${t_file} ${${COMPONENT}_IMPORT_LIBS})

            endif()
            
            # Insert the unit tests into the VS folder "unit_tests"
            set_target_properties(${t_file} PROPERTIES FOLDER "Example Targets")
        else()
            add_dependencies(${t_file} ${${COMPONENT}_STATIC_LIB})
            if(${USE_VTK})
                link_directories(${${COMPONENT}_OUTPUT_DIR} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR} ${VTK_LIB_DIR})
                target_link_libraries(${t_file} ${${COMPONENT}_SHARED_LIB} ${HDF5_LIBRARIES} ${TETGEN_LIBS} ${VTK_LIBS})
            else()
                link_directories(${${COMPONENT}_OUTPUT_DIR} ${HDF5_LIBRARY_DIRS} ${TETGEN_DIR})
                target_link_libraries(${t_file} ${${COMPONENT}_SHARED_LIB} ${HDF5_LIBRARIES} ${TETGEN_LIBS})
            endif()
        endif()
    
        # Supply the *_DLL_IMPORTS directive to preprocessor
        set_target_properties(${t_file} PROPERTIES COMPILE_DEFINITIONS "SHEAF_DLL_IMPORTS")
    
    endforeach()

endfunction(add_example_targets)

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
        set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} ${CMAKE_CURRENT_SOURCE_DIR}/${cluster} CACHE STRING "Include paths for ${PROJECT_NAME}" FORCE)
    endforeach()

endfunction(add_clusters)

# 
# Declare and initialize all variables that are component-specific.
#
function(set_component_vars)

    if(WIN64MSVC OR WIN64INTEL)
        # Fields import lib won't exist when it's antecedents are configured. Force it.
        set(FIELDS_IMPORT_LIB fieldsdll CACHE STRING "${PROJECT_NAME} import library")
        set(${COMPONENT}_DYNAMIC_LIB ${PROJECT_NAME}dll CACHE STRING "${PROJECT_NAME} dynamic link library")
        set(${COMPONENT}_IMPORT_LIB ${PROJECT_NAME}dll CACHE STRING "${PROJECT_NAME} import library")
        set(${COMPONENT}_CSHARP_BINDING_ASSY ${PROJECT_NAME}_csharp_assembly.dll CACHE STRING "${PROJECT_NAME} csharp binding assembly name")
    else()
        set(${COMPONENT}_SHARED_LIB lib${PROJECT_NAME}.so CACHE STRING "${PROJECT_NAME} shared library")
        set(${COMPONENT}_STATIC_LIB lib${PROJECT_NAME}.a CACHE STRING "${PROJECT_NAME} static library")
        set(${COMPONENT}_CSHARP_BINDING_ASSY ${PROJECT_NAME}_csharp_assembly.so CACHE STRING "${PROJECT_NAME} csharp binding assembly name")
    endif()

    set(${COMPONENT}_COMMON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/src CACHE STRING "${PROJECT_NAME} common binding source directory")
    set(${COMPONENT}_SWIG_COMMON_INTERFACE ${PROJECT_NAME}_common_binding.i CACHE STRING "${PROJECT_NAME} common interface filename")
    set(${COMPONENT}_SWIG_COMMON_INCLUDES_INTERFACE ${PROJECT_NAME}_common_binding_includes.i CACHE STRING "${PROJECT_NAME} common includes interface filename" )
      
    set(${COMPONENT}_JAVA_BINDING_LIB ${PROJECT_NAME}_java_binding CACHE STRING "${PROJECT_NAME} java binding library basename")
    set(${COMPONENT}_JAVA_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/java/src CACHE STRING "${PROJECT_NAME} java binding source directory")
    set(${COMPONENT}_SWIG_JAVA_INTERFACE ${PROJECT_NAME}_java_binding.i CACHE STRING "${PROJECT_NAME} java binding interface file")

    set(${COMPONENT}_JAVA_BINDING_JAR ${PROJECT_NAME}_java_binding.jar CACHE STRING "${PROJECT_NAME} java binding jar name")
    
    set(${COMPONENT}_PYTHON_BINDING_LIB _${PROJECT_NAME}_python_binding CACHE STRING "${PROJECT_NAME} python binding library name")
    set(${COMPONENT}_PYTHON_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/python/src CACHE STRING "${PROJECT_NAME} python source directory")
    set(${COMPONENT}_SWIG_PYTHON_INTERFACE ${PROJECT_NAME}_python_binding.i CACHE STRING "${PROJECT_NAME} python binding interface file")
    
    set(${COMPONENT}_CSHARP_BINDING_LIB ${PROJECT_NAME}_csharp_binding CACHE STRING "${PROJECT_NAME} csharp binding library name")
    set(${COMPONENT}_CSHARP_BINDING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bindings/csharp/src CACHE STRING "${PROJECT_NAME} csharp source directory")
    set(${COMPONENT}_SWIG_CSHARP_INTERFACE ${PROJECT_NAME}_csharp_binding.i CACHE STRING "${PROJECT_NAME} csharp binding interface file")

    
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
function(export_targets)

    message(STATUS "Writing ${PROJECT_NAME} detail to ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}")
    if(WIN64MSVC OR WIN64INTEL)
        export(TARGETS ${${COMPONENT}_IMPORT_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_IMPORT_LIB ${${COMPONENT}_IMPORT_LIB} CACHE STRING \"${PROJECT_NAME} Win32 import library \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative Win32 import library list\")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n") 
    else()
        export(TARGETS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_STATIC_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE})
        file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    endif()
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_INCS ${${COMPONENT}_INCS} CACHE STRING \"${PROJECT_NAME} includes\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_IPATH ${${COMPONENT}_IPATH} CACHE STRING \"${PROJECT_NAME} include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_IPATHS ${${COMPONENT}_IPATHS} CACHE STRING \"${PROJECT_NAME} cumulative include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_STATIC_LIB ${${COMPONENT}_STATIC_LIB} CACHE STRING \"${PROJECT_NAME} static library \")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")    
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_SHARED_LIB ${${COMPONENT}_SHARED_LIB} CACHE STRING \"${PROJECT_NAME} shared library \")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")     
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")    
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_CLASSPATH ${${COMPONENT}_CLASSPATH} CACHE STRING \"${PROJECT_NAME} Java classpath\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_BIN_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} binary output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(${COMPONENT}_LIB_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    if("${COMPONENT}" MATCHES "SHEAVES")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(HDF_INCLUDE_DIR ${HDF5_INCLUDE_DIRS} CACHE STRING \"HDF5 Include Path \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    endif()
    #$$TODO: "GEOMETRY" will change to "TOOLS" when we pull kd_lattice out of SheafSystem
    if("${COMPONENT}" MATCHES "TOOLS")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
    #    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(USE_VTK ON CACHE BOOL \"Set to link against VTK libs\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(VTK_LIB_DIR @VTK_LIB_DIR@ CACHE PATH \"VTK library path\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(VTK_BIN_DIR @VTK_BIN_DIR@ CACHE PATH  \"VTK DLL path\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(VTK_INC_DIR @VTK_INC_DIR@ CACHE PATH  \"VTK DLL path\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")        
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(TETGEN_INCLUDE_DIR ${TETGEN_INC_DIR} CACHE STRING \"Tetgen Include Path \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(TETGEN_LIB_DIR ${TETGEN_LIB_DIR} CACHE STRING \"Tetgen Library Path \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(TETGEN_LIB ${TETGEN_LIB} CACHE STRING \"Tetgen Library \")\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")        
    endif()             
endfunction(export_targets)

#
# Export this component's library targets and list of includes for install
# The file locations on an install (includes, libs, etc) are different
# than they are in a build tree. The install config produces
# a .cmake.in file that is configured by the client.
#
function(export_install_config_file_vars)

    if(WIN64MSVC OR WIN64INTEL)
        export(TARGETS ${${COMPONENT}_DYNAMIC_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE})
        # $$HACK: the below is a temporary measure until we completely sort out the staic link issues. JEB 01.17.13
        if("${COMPONENT}" MATCHES "SHEAVES")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIB} CACHE STRING \"${PROJECT_NAME} cumulative import library list\")\n")
        else()
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_IMPORT_LIBS ${${COMPONENT}_IMPORT_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative import library list\")\n")
        endif()
        file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        if("${COMPONENT}" MATCHES "GEOMETRY")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
#            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(USE_VTK ON CACHE BOOL \"Set to link against VTK libs\" FORCE)\n")
#            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(VTK_LIB_DIR @SHEAFSYSTEM_HOME@/lib/vtk CACHE PATH \"VTK library path\" FORCE)\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(VTK_BIN_DIR @SHEAFSYSTEM_HOME@/bin/vtk CACHE PATH  \"Set to link against VTK libs\" FORCE)\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        endif()            
    else()
        export(TARGETS ${${COMPONENT}_SHARED_LIB} ${${COMPONENT}_STATIC_LIB} APPEND FILE ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE})
        if("${COMPONENT}" MATCHES "SHEAVES")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIB} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")    
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIB} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            # This variable should be SHEAFSYSTEM_LIB_OUTPUT_DIR. Fix it.
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_LIB_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING \"${PROJECT_NAME} library output directory\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        else()
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_STATIC_LIBS ${${COMPONENT}_STATIC_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative static library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")    
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_SHARED_LIBS ${${COMPONENT}_SHARED_LIBS} CACHE STRING \"${PROJECT_NAME} cumulative shared library list\")\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
        endif()
        #$$ISSUE: The below commented-out syntax should work, but doesnt. Find out why.
        #if(${USE_VTK} AND (${COMPONENT} MATCHES "GEOMETRY"))
        if("${COMPONENT}" MATCHES "GEOMETRY")        
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
#            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(USE_VTK ON CACHE BOOL \"Set ON to link against VTK libs\" FORCE)\n")
#            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(VTK_INC_DIR @SHEAFSYSTEM_HOME@/include/VTK CACHE PATH \"VTK library path\" FORCE)\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")            
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(VTK_LIB_DIR @SHEAFSYSTEM_HOME@/lib/VTK CACHE PATH \"VTK library path\" FORCE)\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(VTK_LIBS ${VTK_LIBS} CACHE STRING \"VTK Libraries\" FORCE)\n")
            file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")   
        endif()             
    endif()
    file(APPEND  ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_IPATH @SHEAFSYSTEM_HOME@/include CACHE STRING \"${PROJECT_NAME} include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "set(${COMPONENT}_IPATHS @SHEAFSYSTEM_HOME@/include CACHE STRING \"${PROJECT_NAME} cumulative include path\")\n")
    file(APPEND ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} "\n")

endfunction(export_install_config_file_vars)

#
# Generate the install config file. Replace hardcoded vars with cmake substitution vars.
#
function(generate_install_config_file)

    file(READ ${CMAKE_BINARY_DIR}/${INSTALL_CONFIG_FILE} INSTALL_FILE_CONTENTS)
    string(REPLACE ${CMAKE_BINARY_DIR} "\@SHEAFSYSTEM_HOME\@" MASSAGED_OUTPUT "${INSTALL_FILE_CONTENTS}")
    file(WRITE ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "${MASSAGED_OUTPUT}")
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "\n")
    if(WIN64MSVC OR WIN64INTEL)
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "set(INSTALLED_VTK_LIB_DIR "\@SHEAFSYSTEM_HOME\@"/lib/VTK CACHE STRING \"VTK Base Dir\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "set(VTK_BIN_DIR "\@SHEAFSYSTEM_HOME\@"/bin/VTK CACHE STRING \"VTK Base Dir\" FORCE)\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "set(VTK_INC_DIR "\@SHEAFSYSTEM_HOME\@"/include/VTK CACHE STRING \"VTK Base Dir\" FORCE)\n") 
    endif()
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "set(VTK_LIBS ${VTK_LIBS} CACHE STRING \"VTK Runtime Libraries\" FORCE)\n")      
    file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in "set(HDF_INCLUDE_DIR ${HDF_INCLUDE_DIR} CACHE STRING \"HDF Include Directory\" FORCE)\n")  
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
        
    set(${COMPONENT}_SRCS ${${COMPONENT}_SRCS} ${lsrcs} CACHE STRING "${PROJECT} sources." FORCE)
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

    set(${COMPONENT}_INCS ${${COMPONENT}_INCS} ${lincs} CACHE STRING "${PROJECT} includes." FORCE)
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
    
    set(${COMPONENT}_UNIT_TEST_SRCS ${${COMPONENT}_UNIT_TEST_SRCS} ${chksrcs} CACHE STRING "Unit test sources." FORCE)
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

    set(${COMPONENT}_EXAMPLE_SRCS ${${COMPONENT}_EXAMPLE_SRCS} ${execsrcs} CACHE STRING "EXEC sources." FORCE)
    mark_as_advanced(FORCE ${COMPONENT}_EXAMPLE_SRCS)

endfunction(collect_example_sources)

# 
# Convenience routine for diagnostic output during configure phase.
#
function(status_message txt)

    # Let the user know what's being configured
    message(STATUS " ")
    message(STATUS "${txt} - ")
    message(STATUS " ")

endfunction()

# 
# Convenience routine for diagnostic output during configure phase.
# Displays list of included directories for module it is called in.
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
