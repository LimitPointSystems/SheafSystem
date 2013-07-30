# Copyright (c) 2013 Limit Point Systems, Inc. 

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#   http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# - Find SWIG
# This module finds an installed SWIG.  It sets the following variables:
#  SWIG_FOUND - set to true if SWIG is found
#  SWIG_DIR - the directory where swig is installed
#  SWIG_EXECUTABLE - the path to the swig executable
#  SWIG_VERSION   - the version number of the swig executable
#  SWIG_JAVA_INC_DIR - the directory containing the java .i files
#  SWIG_PYTHON_INC_DIR - the directory containing the python .i files
#
# The minimum required version of SWIG can be specified using the
# standard syntax, e.g. FIND_PACKAGE(SWIG 1.1)
#
# All information is collected from the SWIG_EXECUTABLE so the
# version to be found can be changed from the command line by
# means of setting SWIG_EXECUTABLE
#

#=============================================================================
# Copyright 2004-2009 Kitware, Inc.
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
# - Also find the directories with the java and python .i files.
#=============================================================================


# Use HINTS because this is searched before the environment variables.
# PATHS is searched after.
FIND_PROGRAM(SWIG_EXECUTABLE swig
             HINTS 
             "$ENV{HOME}/LPS/prerequisites/swig/bin"
             "$ENV{USERPROFILE}/LPS/prerequisites/swig/"
             "$ENV{USERPROFILE}/LPS/prerequisites/swig-2.0.3-x86_64/"
             "$ENV{USERPROFILE}/LPS/prerequisites/swig-2.0.3/"
             "$ENV{USERPROFILE}/LPS/prerequisites/swig-2.0.8"
             "$ENV{USERPROFILE}/LPS/prerequisites/swig/bin"
             "C:/Program Files (x86)/swig-2.0.3/bin"
             "C:/Program Files (x86)/swig-2.0.8/bin"
             "C:/Program Files (x86)/swig-2.0.3"
             "C:/Program Files (x86)/swig-2.0.8/")
IF(SWIG_EXECUTABLE)
  EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} -swiglib
    OUTPUT_VARIABLE SWIG_swiglib_output
    ERROR_VARIABLE SWIG_swiglib_error
    RESULT_VARIABLE SWIG_swiglib_result)

  IF(SWIG_swiglib_result) 
    IF(SWIG_FIND_REQUIRED)
      MESSAGE(SEND_ERROR "Command \"${SWIG_EXECUTABLE} -swiglib\" failed with output:\n${SWIG_swiglib_error}")
    ELSE(SWIG_FIND_REQUIRED)
      MESSAGE(STATUS "Command \"${SWIG_EXECUTABLE} -swiglib\" failed with output:\n${SWIG_swiglib_error}")
    ENDIF(SWIG_FIND_REQUIRED)
  ELSE(SWIG_swiglib_result)
    STRING(REGEX REPLACE "[\n\r]+" ";" SWIG_swiglib_output ${SWIG_swiglib_output})
    # force the path to be computed each time in case SWIG_EXECUTABLE has changed.
    SET(SWIG_DIR SWIG_DIR-NOTFOUND)
    FIND_PATH(SWIG_DIR swig.swg PATHS ${SWIG_swiglib_output})
    IF(SWIG_DIR)
      #SET(SWIG_USE_FILE ${CMAKE_ROOT}/Modules/UseSWIG.cmake)
      SET(SWIG_USE_FILE ${CMAKE_MODULE_PATH}/UseSWIG.cmake)
      EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} -version
        OUTPUT_VARIABLE SWIG_version_output
        ERROR_VARIABLE SWIG_version_output
        RESULT_VARIABLE SWIG_version_result)
      IF(SWIG_version_result)
        MESSAGE(SEND_ERROR "Command \"${SWIG_EXECUTABLE} -version\" failed with output:\n${SWIG_version_output}")
      ELSE(SWIG_version_result)
        STRING(REGEX REPLACE ".*SWIG Version[^0-9.]*\([0-9.]+\).*" "\\1"
          SWIG_version_output "${SWIG_version_output}")
        SET(SWIG_VERSION ${SWIG_version_output} CACHE STRING "Swig version" FORCE)
      ENDIF(SWIG_version_result)
    ENDIF(SWIG_DIR)
  ENDIF(SWIG_swiglib_result)

  find_path(SWIG_JAVA_INC_DIR java.swg PATHS ${SWIG_DIR}/java)
  find_path(SWIG_PYTHON_INC_DIR python.swg PATHS ${SWIG_DIR}/python)
ENDIF(SWIG_EXECUTABLE)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SWIG REQUIRED_VARS SWIG_EXECUTABLE SWIG_DIR SWIG_JAVA_INC_DIR SWIG_PYTHON_INC_DIR
                                       VERSION_VAR SWIG_VERSION)
