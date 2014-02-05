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

# - Find MONO
# This module finds an installed MONO.  It sets the following variables:
#  MONO_FOUND - set to true if MONO is found
#  MONO_DIR - the directory where swig is installed
#  MONO_EXECUTABLE - the path to the swig executable
#  MONO_VERSION   - the version number of the swig executable
#
# All informations are collected from the MONO_EXECUTABLE so the
# version to be found can be changed from the command line by
# means of setting MONO_EXECUTABLE
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
SET(MONO_FOUND FALSE)

FIND_PROGRAM(MONO_EXECUTABLE mono PATHS /usr/bin)
message(STATUS "${MONO_EXECUTABLE}")
FIND_PROGRAM(MCS_EXECUTABLE  mcs)    # 1.0
FIND_PROGRAM(GMCS_EXECUTABLE mono-csc gmcs)  # 2.0
FIND_PROGRAM(SMCS_EXECUTABLE smcs)  # Moonlight

FIND_PROGRAM(GACUTIL_EXECUTABLE gacutil)  # gacutil - Global Assembly Cache management utility.
FIND_PROGRAM(ILASM_EXECUTABLE ilasm)  #  ilasm, ilasm2 - Mono IL assembler
FIND_PROGRAM(SN_EXECUTABLE sn)  #  sn - Digitally sign/verify/compare strongnames on CLR assemblies.

# We decide to declare mono found when both interpreter and compiler 1.0 are found.
IF(MONO_EXECUTABLE AND MCS_EXECUTABLE)
SET(MONO_FOUND TRUE)
ELSEIF(MONO_EXECUTABLE AND GMCS_EXECUTABLE)
SET(MONO_FOUND TRUE)
ELSEIF(MONO_EXECUTABLE AND SMCS_EXECUTABLE)
SET(MONO_FOUND TRUE)
ENDIF(MONO_EXECUTABLE AND MCS_EXECUTABLE)
IF(NOT MONO_FOUND)
  IF(NOT MONO_FIND_QUIETLY)
    IF(MONO_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "MONO was not found. Please specify mono/mcs executable location")
    ELSE(MONO_FIND_REQUIRED)
      MESSAGE(STATUS "MONO was not found. Please specify mono/mcs executable location")
    ENDIF(MONO_FIND_REQUIRED)
  ENDIF(NOT MONO_FIND_QUIETLY)
ENDIF(NOT MONO_FOUND)
message(STATUS "In FINDMONO")
message(STATUS "In FINDMONO: ${MONO_FOUND}")
GET_FILENAME_COMPONENT(current_list_path ${CMAKE_CURRENT_LIST_FILE} PATH)
SET(MONO_USE_FILE ${current_list_path}/UseMONO.cmake)

MARK_AS_ADVANCED(
  MONO_EXECUTABLE
  MCS_EXECUTABLE
  GMCS_EXECUTABLE
  SMCS_EXECUTABLE
  ILASM_EXECUTABLE
  SN_EXECUTABLE
  GACUTIL_EXECUTABLE
)
