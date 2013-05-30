#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

# Setting CMAKE_CONFIGURATION_TYPES prior to the project function call
# will eliminate the default configuration types (debug,release,RelWithDebugInfo, et al.) --
# or at least stop them from appearing in the VS configuration list.
# It does NOT stop cmake from setting all the cache variables associated with those same
# configurations however.

set(CMAKE_CONFIGURATION_TYPES Debug-contracts Debug-no-contracts Release-contracts Release-no-contracts CACHE
    STRING "Supported configuration types"
    FORCE)

#
# Establish the project name
#    
project(SheafSystem)

#
# Ensure that we have the required cmake version.
#
cmake_minimum_required(VERSION 2.8.5)

#
# Include variable definitions and functions
# unique to and/or required at the system level.
#
include(system_definitions.cmake)

#
# Set the compiler optimization level
#
set_optimization_level()

#
# Add components to the system
#
add_components()

#
# Set up output directories
#
create_output_dirs()

#
# Add the documentation targets (doc, docclean)
# Doc targets are system level and system scope.
# currently there is no notion of building a single
# component's documentation.
#
add_doc_targets()

#
# Add files to the clean target
#
add_clean_files()

#
# Target to generate emacs tags
#
add_tags_target()

#
# Configure the environment scripts. 
#
if(LINUX64GNU OR LINUX64INTEL)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.csh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.csh)
    configure_file(${CMAKE_MODULE_PATH}/set_env_vars.sh.cmake.in ${CMAKE_BINARY_DIR}/set_env_vars.sh)
endif()

#
# VS9 and VS10 handle output locations differently.
#
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 10 Win64" OR ${CMAKE_GENERATOR} MATCHES "Visual Studio 11 Win64")
    set(OUTDIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)" CACHE STRING "Visual Studio Output Directory")
elseif(${CMAKE_GENERATOR} MATCHES "Visual Studio 9 Win64" ) # VS 2008 
    set(OUTDIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Outdir)" CACHE STRING "Visual Studio Output Directory")
endif()
 
#
# System level is responsible for installing the documentation. The component list (see system_definitions.cmake)
# determines what components are included in the docs.
# NOTE: Prepending of ${CMAKE_INSTALL_PREFIX}/ to the value of DESTINATION is implicit in the install command.
# You need only specify the sub-directory within ${CMAKE_INSTALL_PREFIX}, cmake will create the dir.
# With no value specified for DESTINATION, all files are placed in ${CMAKE_INSTALL_PREFIX}.
#
# Only install the documentation when Release-no-contracts is being installed. This prevents 4 iterations of doc generation.
# The rationale here is that Release-no-contracts will always be released.
#
install(DIRECTORY ${CMAKE_BINARY_DIR}/documentation/ DESTINATION documentation)

# Prerequisite components install
if(LINUX64INTEL OR LINUX64GNU)

    # All forward slashes in path
    file(TO_CMAKE_PATH $ENV{HOME} HOME_DIR)
    
    install(DIRECTORY ${VTK_LIB_DIR}/ DESTINATION lib/vtk/ USE_SOURCE_PERMISSIONS PATTERN "lib*"
    PERMISSIONS
    OWNER_WRITE OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    PATTERN "*.cmake" EXCLUDE
    PATTERN "doc" EXCLUDE
    PATTERN "doxygen" EXCLUDE
    PATTERN "hints" EXCLUDE
    PATTERN "CMake" EXCLUDE
    PATTERN "testing" EXCLUDE)
    
    install(DIRECTORY ${HDF5_INCLUDE_DIR}/ DESTINATION include PATTERN "*.h"
    PERMISSIONS
    OWNER_WRITE OWNER_READ OWNER_EXECUTE
    GROUP_READ WORLD_READ)
    
    install(FILES ${TETGEN_INC_DIR}/tetgen.h DESTINATION include
    PERMISSIONS
    OWNER_WRITE OWNER_READ OWNER_EXECUTE
    GROUP_READ WORLD_READ)

    if(${USE_VTK})
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(USE_VTK OFF CACHE BOOL \"Set to link against VTK libs\")\n")
        file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(VTK_LIB_DIR @SHEAFSYSTEM_HOME@/lib/VTK CACHE STRING \"Location of VTK libs\")\n")
        file(APPEND  ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "\n")
        install(DIRECTORY ${VTK_INC_DIRS} DESTINATION include/VTK PATTERN "*.h"
        PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_READ WORLD_READ)
    endif()             
else()
    # Install only the VTK libs we use
    foreach(lib ${VTK_LIBS})
        install(FILES ${VTK_BIN_DIR}/${lib}.dll DESTINATION bin)
        install(FILES ${VTK_LIB_DIR}/${lib}.lib DESTINATION lib)    
    endforeach()
    # Install only the VTK includes we use    
    foreach(inc ${VTK_INCS})
        install(FILES ${VTK_INC_DIRS}/${inc} DESTINATION include)
    endforeach()
    # Tetgen header
    install(FILES ${TETGEN_INC_DIR}/tetgen.h DESTINATION include)  

    # HDF
    file(GLOB HDF_INCS ${HDF5_INCLUDE_DIR}/*.h)
    install(FILES ${HDF_INCS} DESTINATION include)

endif()

#
# Generate some info about the release
#
set(RELEASE_DATE)
get_date(RELEASE_DATE)
file(WRITE ${CMAKE_BINARY_DIR}/RELEASE "${PROJECT_NAME} version ${LIB_VERSION} ${RELEASE_DATE}  \n")
install(FILES ${CMAKE_BINARY_DIR}/RELEASE DESTINATION ${CMAKE_INSTALL_PREFIX})

#
# Generate the install configuration file.
#
generate_install_config_file()

#
# Install the exports file
#
if(LINUX64INTEL OR LINUX64GNU)
    install(FILES ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION ${CMAKE_BUILD_TYPE}/config)
else()
    include(InstallRequiredSystemLibraries)
    install(FILES ${CMAKE_BINARY_DIR}/${EXPORTS_FILE}.in DESTINATION config/\${BUILD_TYPE})
endif()    


