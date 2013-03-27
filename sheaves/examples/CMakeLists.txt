#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/03/13 00:59:01 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER examples)

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
    sheaves_read.cc
 #   write_sheaves_namespace.cc
  )

collect_example_sources()
