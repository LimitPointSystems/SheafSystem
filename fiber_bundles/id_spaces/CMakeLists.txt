#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:08 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER id_spaces)

#
# Library sources.
#
set(SRCS
    i_adjacency_implicit_index_space_iterator.cc
    i_adjacency_index_space_interval.cc
    i_connectivity_implicit_index_space_iterator.cc
    i_connectivity_index_space_interval.cc
    ij_adjacency_implicit_index_space_iterator.cc
    ij_adjacency_index_space_interval.cc
    ij_connectivity_implicit_index_space_iterator.cc
    ij_connectivity_index_space_interval.cc
    ijk_adjacency_implicit_index_space_iterator.cc
    ijk_adjacency_index_space_interval.cc
    ijk_connectivity_implicit_index_space_iterator.cc
    ijk_connectivity_index_space_interval.cc
    section_space_schema_jims_index_space_handle.cc
    section_space_schema_jims_index_space_iterator.cc
    section_space_schema_jims_index_space_state.cc
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

