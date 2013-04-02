#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:45 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER support)

#
# Library sources.
#
set(SRCS
    any.cc
    arg_list.cc
    assert_contract.cc
    auto_block.cc
    binary_index_block.cc
    block.cc
    deep_size.cc
    error_message.cc
    id_block.cc
    int_set.cc
    interval_set.cc
    interval_set_iterator.cc
    list_pool.cc
    plot.cc
    pod_types.cc
    primitive_attributes.cc
    primitive_traits.cc
    primitive_type.cc
    primitive_value.cc
    ragged_array.cc
    rc_any.cc
    rc_ptr.cc
    report.cc
    scoped_index.cc
    stl_scoped_index.cc
    stop_watch.cc
    tern.cc
    tolerance_comparison.cc
    zn_to_bool.cc
    wsv_block.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    auto_block.impl.h 
    binary_index_block.impl.h 
    block.impl.h
    deep_size.impl.h 
    factory.h 
    factory.impl.h 
    factory_2.h 
    factory_2.impl.h 
    hash_set_filter.h 
    index_traits.h 
    list_pool.impl.h
    pool.h 
    pool.impl.h 
    ptr_linked_pool.h 
    ptr_linked_pool.impl.h 
    ragged_array.impl.h 
    rc_ptr.impl.h 
    set_filter.h 
    sheaf_dll_spec.h
    stl_scoped_index.impl.h 
    wsv_block.impl.h 
    zn_to_bool_filter.h
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
