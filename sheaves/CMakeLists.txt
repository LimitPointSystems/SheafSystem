#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.19 $ $Date: 2013/01/20 19:40:47 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

project(sheaves)

cmake_minimum_required(VERSION 2.8.3)

#
# Include the functions and variable definitions unique to this component.
#
include(${CMAKE_CURRENT_SOURCE_DIR}/component_definitions.cmake)

#
# Announce current status.
#
status_message("Processing ${PROJECT_NAME}")

#
# Set compiler flags for all build configurations
#
set_compiler_flags()

#
# Set up output directories
#
create_output_dirs()

#
# Add the library targets
#
add_library_targets()

#
# Add Bindings targets
#
add_bindings_targets()

#
# Installation target
#
add_install_target()

#
# Add files to the clean target
#
add_clean_files()

#
# Write this component's lib targets and include paths to an export file.
#
export_targets()

#
# Prepare this component's lib targets and include paths for export to an install config file.
# This data only gets used by clients when the SheafSystem has been installed.
#
export_install_config_file_vars()

#
# Sheaves is responsible for the std headers;
# append their location to the exports file.
#
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(STD_HEADERS ${STD_HEADERS} CACHE STRING \"STD headers\")\n")
file(APPEND ${CMAKE_BINARY_DIR}/${EXPORTS_FILE} "set(STD_IPATH ${CMAKE_BINARY_DIR}/include CACHE STRING \"STD header include path\")\n")


