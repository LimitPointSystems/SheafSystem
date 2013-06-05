#
# $RCSfile: FindTetgen.cmake,v $ $Revision: 1.8 $ $Date: 2013/01/17 01:45:12 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

# Look for Tetgen.
# This modules defines the following variables:
#
# TETGEN_FOUND
# TETGEN_LIB
# TETGEN_LIB_DIR
# TETGEN_INC_DIR
#

#
# Initialize the found variable
#
set(TETGEN_FOUND 0)

#
# Find the tetgen lib
#
if(WIN64MSVC OR WIN64INTEL)
	find_library(TETGEN_LIB NAMES tetgen HINTS $ENV{USERPROFILE}/LPS/prerequisites/tetgen/lib)
	find_path(TETGEN_LIB_DIR tetgen.lib
          HINTS $ENV{USERPROFILE}/LPS/prerequisites/tetgen/lib)
          
	# And the include path
	find_path(TETGEN_INC_DIR tetgen.h
          HINTS $ENV{USERPROFILE}/LPS/prerequisites/tetgen/include)
else()
#    if(ENABLE_STATIC_PREREQS)
    	find_file(TETGEN_LIB NAMES libtetgen.a HINTS $ENV{HOME}/LPS/prerequisites/tetgen/lib  /usr/local/tetgen/lib)
    	find_path(TETGEN_LIB_DIR libtetgen.a
              HINTS $ENV{HOME}/LPS/prerequisites/tetgen/lib /usr/local/tetgen/lib)
#	else()
#		find_file(TETGEN_LIB NAMES libtetgen.so HINTS $ENV{HOME}/LPS/prerequisites/tetgen/lib  /usr/local/tetgen/lib)
 #   	find_path(TETGEN_LIB_DIR libtetgen.so
 #             HINTS $ENV{HOME}/LPS/prerequisites/tetgen/lib /usr/local/tetgen/lib)          
 #   endif()
    	# And the include path
	find_path(TETGEN_INC_DIR tetgen.h
          HINTS $ENV{HOME}/LPS/prerequisites/tetgen/include /usr/local/tetgen/include)
endif()

if(EXISTS ${TETGEN_LIB})
    set(TETGEN_FOUND 1)
endif()



          