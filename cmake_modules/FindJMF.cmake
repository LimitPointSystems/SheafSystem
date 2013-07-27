#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
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

