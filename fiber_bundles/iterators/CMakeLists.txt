#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:08 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER iterators)

#
# Library sources.
#
set(SRCS
    binary_section_component_iterator.cc
    discretization_context.cc
    discretization_iterator.cc
    eval_iterator.cc
    section_component_iterator.cc
    section_eval_iterator.cc
    section_iteration_state.cc
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
