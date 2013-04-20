#
# $RCSfile: FindDoxygen.cmake,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:16:50 $
#
#
# Some portions Copyright (c) 2013 Limit Point Systems, Inc.
#
#

# - This module looks for Doxygen and the path to Graphviz's dot
# Doxygen is a documentation generation tool.  Please see
# http://www.doxygen.org
#
# This module accepts the following optional variables:
#
#   DOXYGEN_SKIP_DOT       = If true this module will skip trying to find Dot
#                            (an optional component often used by Doxygen)
#
# This modules defines the following variables:
#
#   DOXYGEN_EXECUTABLE     = The path to the doxygen command.
#   DOXYGEN_FOUND          = Was Doxygen found or not?
#
#   DOXYGEN_DOT_EXECUTABLE = The path to the dot program used by doxygen.
#   DOXYGEN_DOT_FOUND      = Was Dot found or not?
#   DOXYGEN_DOT_PATH       = The path to dot not including the executable
#
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

#=============================================================================
# LPS Modifications:
#
# - Look in ${ENV{HOME}/LPS/prerequisites/doxygen/bin for doxygen.
# - If it's not there, look in the directory specified by the DOXYGEN_BIN
#   environment variable.
# - The version is checked against what is passed in from CMakeLists.txt.
#=============================================================================

# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

# For backwards compatibility support
IF(Doxygen_FIND_QUIETLY)
  SET(DOXYGEN_FIND_QUIETLY TRUE)
ENDIF()

# ===== Rationale for OS X AppBundle mods below =====
#     With the OS X GUI version, Doxygen likes to be installed to /Applications and
#     it contains the doxygen executable in the bundle. In the versions I've 
#     seen, it is located in Resources, but in general, more often binaries are 
#     located in MacOS.
#
#     NOTE: The official Doxygen.app that is distributed for OS X uses non-standard 
#     conventions.  Instead of the command-line "doxygen" tool being placed in
#     Doxygen.app/Contents/MacOS, "Doxywizard" is placed there instead and 
#     "doxygen" is placed in Contents/Resources.  This is most likely done
#     so that something happens when people double-click on the Doxygen.app
#     package.  Unfortunately, CMake gets confused by this as when it sees the
#     bundle it uses "Doxywizard" as the executable to use instead of
#     "doxygen".  Therefore to work-around this issue we temporarily disable
#     the app-bundle feature, just for this CMake module:
if(APPLE)
    #  Save the old setting
    SET(TEMP_DOXYGEN_SAVE_CMAKE_FIND_APPBUNDLE ${CMAKE_FIND_APPBUNDLE})
    # Disable the App-bundle detection feature
    SET(CMAKE_FIND_APPBUNDLE "NEVER")
endif()
#     FYI:
#     In the older versions of OS X Doxygen, dot was included with the 
#     Doxygen bundle. But the new versions require you to download
#     Graphviz.app which contains "dot" in it's bundle.
# ============== End OSX stuff ================

#
# Find Doxygen...
#

FIND_PROGRAM(DOXYGEN_EXECUTABLE
  NAMES doxygen doxygen.exe
  HINTS
    "$ENV{HOME}/LPS/prerequisites/doxygen/bin"
    "$ENV{USERPROFILE}/LPS/prerequisites/doxygen/bin"
    "C:/Program Files (x86)/doxygen/bin"
    "C:/Program\ Files/doxygen/bin"
    ENV DOXYGEN_BIN
  PATHS
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\doxygen_is1;Inno Setup: App Path]/bin"
    /Applications/Doxygen.app/Contents/Resources
    /Applications/Doxygen.app/Contents/MacOS
  DOC "Doxygen documentation generation tool (http://www.doxygen.org)"
)

#
# Check version
#

# Ask the executable for version number
execute_process(COMMAND ${DOXYGEN_EXECUTABLE} "--version" OUTPUT_VARIABLE Doxygen_VERSION)

# Remove trailing newline
string(REPLACE "\n" "" Doxygen_VERSION "${Doxygen_VERSION}")

# Check
set(Doxygen_VERSION_VALID)

if(Doxygen_VERSION)
  set(Doxygen_VERSION_VALID 1)
endif()

# handle the QUIETLY and REQUIRED arguments and set DOXYGEN_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Doxygen DEFAULT_MSG DOXYGEN_EXECUTABLE Doxygen_VERSION_VALID)
message(STATUS "Doxygen version is: " ${Doxygen_VERSION})
#
# Find Dot...
#

IF(NOT DOXYGEN_SKIP_DOT)
  FIND_PROGRAM(DOXYGEN_DOT_EXECUTABLE
    NAMES dot
    PATHS 
      "$ENV{ProgramFiles}/Graphviz 2.21/bin"
      "C:/Program Files/Graphviz 2.21/bin"
      "$ENV{ProgramFiles}/ATT/Graphviz/bin"
      "C:/Program Files/ATT/Graphviz/bin"
      [HKEY_LOCAL_MACHINE\\SOFTWARE\\ATT\\Graphviz;InstallPath]/bin
      /Applications/Graphviz.app/Contents/MacOS
      /Applications/Doxygen.app/Contents/Resources
      /Applications/Doxygen.app/Contents/MacOS
    DOC "Graphviz Dot tool for using Doxygen"
  )
  
  if(DOXYGEN_DOT_EXECUTABLE)
    set(DOXYGEN_DOT_FOUND TRUE)
    # The Doxyfile wants the path to Dot, not the entire path and executable
    get_filename_component(DOXYGEN_DOT_PATH "${DOXYGEN_DOT_EXECUTABLE}" PATH CACHE)
  endif()
  
endif()

#
# Backwards compatibility...
#

if(APPLE)
  # Restore the old app-bundle setting setting
  SET(CMAKE_FIND_APPBUNDLE ${TEMP_DOXYGEN_SAVE_CMAKE_FIND_APPBUNDLE})
endif()

# Maintain the _FOUND variables as "YES" or "NO" for backwards compatibility
# (allows people to stuff them directly into Doxyfile with configure_file())
if(DOXYGEN_FOUND)
  set(DOXYGEN_FOUND "YES")
else()
  set(DOXYGEN_FOUND "NO")
endif()
if(DOXYGEN_DOT_FOUND)
  set(DOXYGEN_DOT_FOUND "YES")
else()
  set(DOXYGEN_DOT_FOUND "NO")
endif()

# For backwards compatibility support
SET (DOXYGEN ${DOXYGEN_EXECUTABLE} )
SET (DOT ${DOXYGEN_DOT_EXECUTABLE} )

MARK_AS_ADVANCED(
  DOXYGEN_EXECUTABLE
  DOXYGEN_DOT_EXECUTABLE
  DOXYGEN_DOT_PATH
  )