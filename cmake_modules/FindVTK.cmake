#
# $RCSfile: FindVTK.cmake,v $ $Revision: 1.8 $ $Date: 2013/01/30 04:38:35 $
#
#
# Some portions Copyright (c) 2013 Limit Point Systems, Inc.
#
#
#
#
#
# Some portions Copyright (c) 2013 Limit Point Systems, Inc.
#
#

# - Find a VTK installation or build tree.
# The following variables are set if VTK is found.  If VTK is not
# found, VTK_FOUND is set to false.
#  VTK_FOUND         - Set to true when VTK is found.
#  VTK_USE_FILE      - CMake file to use VTK.
#  VTK_MAJOR_VERSION - The VTK major version number.
#  VTK_MINOR_VERSION - The VTK minor version number 
#                       (odd non-release).
#  VTK_BUILD_VERSION - The VTK patch level 
#                       (meaningless for odd minor).
#  VTK_INCLUDE_DIRS  - Include directories for VTK
#  VTK_LIBRARY_DIRS  - Link directories for VTK libraries
# The following cache entries must be set by the user to locate VTK:
#  VTK_LIB_DIR  - The directory containing VTKConfig.cmake.  
#             This is either the root of the build tree,
#             or the lib/vtk directory.  This is the 
#             only cache entry.
# The following variables are set for backward compatibility and
# should not be used in new code:
#  USE_VTK_FILE - The full path to the UseVTK.cmake file.
#                 This is provided for backward 
#                 compatibility.  Use VTK_USE_FILE 
#                 instead.
#

#=============================================================================
# Copyright 2001-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

#=============================================================================
# LPS Modifications:
#
# - Check in the LPS standard prerequisites location.
#=============================================================================

# VTK 5.10 has a bug that causes a crash in Xwindows upon closing.
# Uncomment/comment appropriately below to use 5.6 on Linux for now. 5.10 seems to work fine on windows.
#
set(VERSION 5.10)
#set(VERSION 5.6)

# Assume not found.
set(VTK_FOUND 0)

# Construct consitent error messages for use below.
set(VTK_DIR_DESCRIPTION "directory containing VTKConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/vtk for an installation.")
set(VTK_DIR_MESSAGE "VTK not found.  Set the VTK_LIB_DIR cmake cache entry to the ${VTK_DIR_DESCRIPTION}")

# Use the Config mode of the find_package() command to find VTKConfig.
# If this succeeds (possibly because VTK_LIB_DIR is already set), the
# command will have already loaded VTKConfig.cmake and set VTK_FOUND.
#if(NOT VTK_FOUND)
#  find_package(VTK QUIET NO_MODULE
#                   HINTS $ENV{HOME}/LPS/prerequisites/vtk $ENV{USERPROFILE}/LPS/prerequisites/vtk/lib)
#endif()

if(VERSION MATCHES "5.10")

  # Look for UseVTK.cmake in build trees or under <prefix>/include/vtk.
  find_path(VTK_LIB_DIR
    NAMES UseVTK.cmake
    PATH_SUFFIXES vtk-5.10 vtk
    HINTS $ENV{VTK_LIB_DIR} $ENV{HOME}/LPS/prerequisites/vtk/lib $ENV{USERPROFILE}/LPS/prerequisites/vtk/lib

    PATHS

    # Support legacy cache files.
    ${VTK_DIR_SEARCH_LEGACY}

    # Read from the CMakeSetup registry entries.  It is likely that
    # VTK will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${VTK_DIR_DESCRIPTION}"
    )
    get_filename_component(__TMP_DIR "${VTK_LIB_DIR}" PATH)
    get_filename_component(__TMP_DIR "${__TMP_DIR}" PATH)
    set(VTK_BIN_DIR "${__TMP_DIR}/bin" CACHE PATH "VTK Runtime libraries location.")
    
    get_filename_component(__TMP_DIR "${VTK_LIB_DIR}" PATH)
    get_filename_component(__TMP_DIR "${__TMP_DIR}" PATH)
    set(VTK_INCLUDE_DIRS "${__TMP_DIR}/include/vtk-5.10" CACHE PATH "VTK Headers location.")
message(STATUS "${VTK_LIB_DIR}")
message(STATUS "${__TMP_DIR}/include/vtk-5.10")
message(STATUS "HOME dir is: $ENV{HOME}")
message(STATUS "$ENV{HOME}/LPS/prerequisites/vtk/lib")
else()    

  # Look for UseVTK.cmake in build trees or under <prefix>/include/vtk.
  find_path(VTK_LIB_DIR
    NAMES UseVTK.cmake
    PATH_SUFFIXES vtk-5.6 vtk
    HINTS $ENV{VTK_LIB_DIR} $ENV{HOME}/LPS/prerequisites/vtk/lib $ENV{USERPROFILE}/LPS/prerequisites/vtk/lib

    PATHS

    # Support legacy cache files.
    ${VTK_DIR_SEARCH_LEGACY}

    # Read from the CMakeSetup registry entries.  It is likely that
    # VTK will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${VTK_DIR_DESCRIPTION}"
    )
    get_filename_component(__TMP_DIR "${VTK_LIB_DIR}" PATH)
    get_filename_component(__TMP_DIR "${__TMP_DIR}" PATH)
    set(VTK_BIN_DIR "${__TMP_DIR}/bin" CACHE PATH "VTK Runtime libraries location.")
  
    get_filename_component(__TMP_DIR "${VTK_LIB_DIR}" PATH)
    get_filename_component(__TMP_DIR "${__TMP_DIR}" PATH)
    set(VTK_INCLUDE_DIRS "${__TMP_DIR}/include/vtk-5.6" CACHE PATH "VTK Headers location.")
endif()

if(VTK_LIB_DIR)
    set(VTK_FOUND 1)
endif()

#-----------------------------------------------------------------------------
if(VTK_FOUND)
  # set USE_VTK_FILE for backward-compatability.
  set(USE_VTK_FILE ${VTK_USE_FILE})
else(VTK_FOUND)
  # VTK not found, explain to the user how to specify its location.
  if(VTK_FIND_REQUIRED)
    message(FATAL_ERROR ${VTK_DIR_MESSAGE})
  else(VTK_FIND_REQUIRED)
    if(NOT VTK_FIND_QUIETLY)
      message(STATUS ${VTK_DIR_MESSAGE})
    endif(NOT VTK_FIND_QUIETLY)
  endif(VTK_FIND_REQUIRED)
endif(VTK_FOUND)
