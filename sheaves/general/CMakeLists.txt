#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:35 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER general)

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
