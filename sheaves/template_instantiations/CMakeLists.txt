#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.4 $ $Date: 2013/01/12 17:17:49 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER template_instantiations)

#
# Library sources.
#
set(SRCS
    abstract_poset_member.inst.cc
    auto_block.inst.cc
    binary_index_block.inst.cc
    biorder_itr.inst.cc
    block.inst.cc
    deep_size.inst.cc
    depth_first_itr.inst.cc
    factory.inst.cc
    factory_2.inst.cc
    filtered_depth_first_itr.inst.cc
    index_space_family.inst.cc
    index_space_handle.inst.cc
    linkorder_itr.inst.cc
    list_pool.inst.cc
    name_multimap.inst.cc
    namespace_poset.inst.cc
    pool.inst.cc
    poset_crg_state.inst.cc
    poset_state_handle.inst.cc
    postorder_itr.inst.cc
    preorder_itr.inst.cc
    ragged_array.inst.cc
    rc_ptr.inst.cc
    record_map.inst.cc
    stl_scoped_index.inst.cc
    triorder_itr.inst.cc
    wsv_block.inst.cc
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
