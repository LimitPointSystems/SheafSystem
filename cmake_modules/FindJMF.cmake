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

#  Look for JMF.
#  This module finds an installed JMF.  It sets the following variables:
#  JMF_FOUND - set to true if JMF is found
#  JMF_DIR - the directory where jmf is installed
#  JMF_BIN_DIR - the path to the jmf executable
#  JMF_LIB_DIR - the path to the jmf libraries and jmf.jar
#

# $$TODO: When Windows, look in the registry for JMF location.

# Use HINTS because this is searched before the environment variables.
# PATHS is searched after.
if(WIN64MSVC OR WIN64INTEL)
    FIND_PROGRAM(JMFINIT_EXECUTABLE jmfinit
                 HINTS "$ENV{USERPROFILE}/LPS/prerequisites/jmf/bin")
else()             
    FIND_PROGRAM(JMFINIT_EXECUTABLE jmfinit
                 HINTS "$ENV{HOME}/LPS/prerequisites/jmf/bin")
endif()

if(JMFINIT_EXECUTABLE)
  get_filename_component(JMF_BIN_DIR ${JMFINIT_EXECUTABLE} PATH)
  get_filename_component(JMF_DIR ${JMF_BIN_DIR} PATH)
  find_path(JMF_LIB_DIR jmf.jar PATHS ${JMF_DIR}/lib)
endif()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JMF REQUIRED_VARS JMFINIT_EXECUTABLE JMF_DIR JMF_BIN_DIR JMF_LIB_DIR)

