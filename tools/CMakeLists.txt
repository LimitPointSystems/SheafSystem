#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.19 $ $Date: 2013/03/27 17:31:37 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

project(tools)

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
# examples will corrupt the scope sources. Include it after.
#
add_subdirectory(examples)

#
# Intialize the SheafScope sources var
#
set_scope_sources()

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
# Explicit target for the dumpsheaf tool.
#
add_dumpsheaf_target()

#
# Write this component's lib targets and include paths to an export file.
#
export_targets()

#
# Prepare this component's lib targets and include paths for export to an install config file.
#
export_install_config_file_vars()
