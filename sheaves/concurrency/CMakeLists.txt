#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:33 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------
#

set(CLUSTER concurrency)

#
# Library sources.
#
set(SRCS
    equivalence.cc
    read_write_monitor.cc 
    read_write_monitor_handle.cc 
    runnable.cc 
    thread.cc 
    thread_condition_variable.cc 
    thread_mutex.cc
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