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
    abstract_product_structure.cc
    array_implicit_index_space_iterator.cc
    array_index_space_interval.cc
    array_index_space_iterator.cc
    array_index_space_state.cc
    constant_implicit_index_space_iterator.cc
    constant_index_space_interval.cc
    explicit_index_space_collection.cc
    explicit_index_space_handle.cc
    explicit_index_space_interval.cc
    explicit_index_space_iterator.cc
    explicit_index_space_state.cc
    forwarding_index_space_handle.cc
    hash_index_space_iterator.cc
    hash_index_space_state.cc
    hub_index_space_handle.cc
    hub_index_space_iterator.cc
    ij_product_structure.cc
    ijk_product_structure.cc
    implicit_index_space_iterator.cc
    index_space_collection.cc
    index_equivalence_class.cc
    index_equivalence_iterator.cc
    index_space_family.cc
    index_space_family_iterator.cc
    index_space_handle.cc
    index_space_interval.cc
    index_space_interval_iterator.cc
    index_space_iterator.cc
    interval_index_space_handle.cc
    interval_index_space_iterator.cc
    interval_index_space_state.cc
    list_index_space_iterator.cc
    list_index_space_state.cc
    mutable_index_space_handle.cc
    mutable_index_space_state.cc
    offset_index_space_handle.cc
    offset_index_space_iterator.cc
    offset_index_space_state.cc
    primary_index_space_handle.cc
    primary_index_space_iterator.cc
    primary_index_space_state.cc
    primary_sum_index_space_state.cc
    primitives_index_space_iterator.cc
    primitives_index_space_state.cc
    ragged_array_implicit_index_space_iterator.cc
    ragged_array_index_space_interval.cc
    reserved_primary_index_space_handle.cc
    reserved_primary_index_space_iterator.cc
    reserved_primary_index_space_state.cc
    singleton_implicit_index_space_iterator.cc
    singleton_index_space_handle.cc
    singleton_index_space_interval.cc
    singleton_index_space_iterator.cc
    singleton_index_space_state.cc
    sum_index_space_handle.cc
    sum_index_space_state.cc
   )


collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    index_space_family.impl.h
    index_space_handle.impl.h
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
