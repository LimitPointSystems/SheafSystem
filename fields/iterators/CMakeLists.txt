#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER ${CMAKE_CURRENT_BINARY_DIR})

#
# Library sources.
#
set(SRCS
    field_eval_iterator.cc
    property_disc_iterator.cc
    property_disc_iterator_1_1.cc
    property_disc_iterator_1_2.cc
    property_disc_iterator_1_3.cc
    property_disc_iterator_4_2.cc
    property_disc_iterator_4_3.cc
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