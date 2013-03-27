#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:16:56 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER dof_maps)

#
# Library sources.
#
set(SRCS
    array_section_dof_map.cc
    section_dof_map.cc
    sparse_section_dof_map.cc
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
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()