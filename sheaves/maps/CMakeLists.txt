#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.12 $ $Date: 2013/03/13 00:59:05 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER maps)

#
# Library sources.
#
set(SRCS
    name_multimap.cc 
    record_map.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    name_multimap.impl.h 
    record_map.impl.h
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
