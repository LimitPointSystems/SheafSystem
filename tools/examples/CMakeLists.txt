#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:56 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER examples)

configure_file(lps_environment.h.cmake.in lps_environment.h)

#
# Library sources.
#
set(SRCS
test_case_2d.cc
test_case_3d.cc
test_case_3d_irregular.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
#    lps_environment.h
)

collect_includes()

#
# Source for unit test executables.
#
set(UNIT_TEST_SRCS
#test_case_2d.t.cc
#test_case_3d.t.cc
#test_case_3d_irregular.t.cc

)

collect_unit_test_sources()

#
# Source for example executables.
#
set(EXAMPLE_SRCS
 #   SheafScope.cc
)

collect_example_sources()
