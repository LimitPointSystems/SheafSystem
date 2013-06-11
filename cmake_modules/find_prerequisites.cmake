#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#
# Prerequisite Discovery
#
# This file is included in the top level CmakeLists.txt file, hence any prereq
# discovered and included here will be visible to the entire system.
#

# HDF5, Tetgen, and Doxygen need to be found for all target platforms.
#

find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_MODULE_PATH}/doxygen_definitions.cmake.in ${CMAKE_BINARY_DIR}/doxygen_definitions.cmake)
    configure_file(${CMAKE_MODULE_PATH}/dev_doxyfile.cmake.in ${CMAKE_BINARY_DIR}/dev_doxyfile)
    configure_file(${CMAKE_MODULE_PATH}/user_doxyfile.cmake.in ${CMAKE_BINARY_DIR}/user_doxyfile)
else()
    message(WARNING "Doxygen was not found. Documentation will not be generated.")
endif()

# Tell hdf to use static libs
set(HDF5_USE_STATIC_LIBRARIES ON)

find_package(HDF5 1.8.9 REQUIRED)
if(HDF5_FOUND)
    configure_file(${CMAKE_MODULE_PATH}/hdf_definitions.cmake.in ${CMAKE_BINARY_DIR}/hdf_definitions.cmake)
    include(${CMAKE_BINARY_DIR}/hdf_definitions.cmake)
    link_directories(${HDF5_LIB_DIR})
    include_directories(${HDF5_INCLUDE_DIRS})
endif()

#
# Find VTK
#
find_package(VTK 5.10 REQUIRED MODULE)
if(VTK_FOUND)
    configure_file(${CMAKE_MODULE_PATH}/vtk_definitions.cmake.in ${CMAKE_BINARY_DIR}/vtk_definitions.cmake)
    include(${CMAKE_BINARY_DIR}/vtk_definitions.cmake)
endif()

# Find the JDK
find_package(Java 1.7 REQUIRED)
if(JAVA_FOUND)
    configure_file(${CMAKE_MODULE_PATH}/java_definitions.cmake.in ${CMAKE_BINARY_DIR}/java_definitions.cmake)
    include(${CMAKE_BINARY_DIR}/java_definitions.cmake)
    set(JAVA_BINDING_COMPILE_OPTIONS "-I${JDK_INC_DIR}" "-I${JDK_PLATFORM_INC_DIR}" CACHE STRING "JDK compile includes") 
endif()
    
#
# Find tetgen
#
find_package(Tetgen REQUIRED)
if(TETGEN_FOUND)
    configure_file(${CMAKE_MODULE_PATH}/tetgen_definitions.cmake.in ${CMAKE_BINARY_DIR}/tetgen_definitions.cmake)
    include(${CMAKE_BINARY_DIR}/tetgen_definitions.cmake)
    include_directories(${TETGEN_INC_DIR})
    link_directories(${TETGEN_LIB_DIR})    
endif()


    
#
# Find Java, Python, VTK, JMF, Swig, and gnuplot
#

# Find gnuplot
if(LINUX64GNU OR LINUX64INTEL)
    # Needed for some checks
    find_package(Gnuplot)
    if(GNUPLOT_FOUND)
        message(STATUS "Found Gnuplot")
    endif()
endif()

if(BUILD_BINDINGS)
    
    # Find Swig
    find_package(SWIG)
    if(SWIG_FOUND)
        configure_file(${CMAKE_MODULE_PATH}/swig_definitions.cmake.in ${CMAKE_BINARY_DIR}/swig_definitions.cmake)
        include(${CMAKE_BINARY_DIR}/swig_definitions.cmake)
        message(STATUS "Swig version is: ${SWIG_VERSION}")        
        include(${CMAKE_MODULE_PATH}/UseSWIG.cmake)
    endif()
    
    # Find C#
        find_package(CSharp)
        if(CSHARP_FOUND)
              include(${CMAKE_MODULE_PATH}/UseCSharp.cmake)
        endif()
  
    
    find_package(PythonLibs REQUIRED)
    if(PYTHONLIBS_FOUND)
        configure_file(${CMAKE_MODULE_PATH}/python_definitions.cmake.in ${CMAKE_BINARY_DIR}/python_definitions.cmake)
        include(${CMAKE_BINARY_DIR}/python_definitions.cmake)
        message(STATUS "Python version is: ${PYTHONLIBS_VERSION_STRING}") 
    endif()
      
    # Find the JMF
    find_package(JMF REQUIRED)
        if(JMF_FOUND)
            configure_file(${CMAKE_MODULE_PATH}/jmf_definitions.cmake.in ${CMAKE_BINARY_DIR}/jmf_definitions.cmake)
           include(${CMAKE_BINARY_DIR}/jmf_definitions.cmake)
        endif()   
endif()


