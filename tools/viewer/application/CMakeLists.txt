# $RCSfile: CMakeLists.txt,v $ $Revision: 1.5 $ $Date: 2012/07/04 16:42:30 $

#
# Copyright (c) 2010 Limit Point Systems, Inc.
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER Viewer/application)

#
# Library sources.
#
set(SRCS 
   )
     
collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
   )

collect_includes()  

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
   )

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS
   )

collect_example_sources()