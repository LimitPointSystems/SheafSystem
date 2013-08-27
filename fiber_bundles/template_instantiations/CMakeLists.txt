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
    abstract_poset_member.inst.cc
    antisymmetric_matrix_2x2.inst.cc
    antisymmetric_matrix_3x3.inst.cc
    at0.inst.cc
    at2_e2.inst.cc
    at2_e3.inst.cc
    at3_e3.inst.cc
    atp.inst.cc
    auto_block.inst.cc
    base_space_factory.inst.cc
    block.inst.cc
    e1.inst.cc
    e2.inst.cc
    e3.inst.cc
    e4.inst.cc
    ed.inst.cc
    factory.inst.cc
    fiber_bundles_namespace.inst.cc
    general_matrix_1x2.inst.cc
    general_matrix_1x3.inst.cc
    general_matrix_2x1.inst.cc
    general_matrix_2x2.inst.cc
    general_matrix_2x3.inst.cc
    general_matrix_3x1.inst.cc
    general_matrix_3x2.inst.cc
    general_matrix_3x3.inst.cc
    gl2.inst.cc
    gl3.inst.cc
    gln.inst.cc
    group.inst.cc
    index_space_family.inst.cc
    jcb.inst.cc
    jcb_e13.inst.cc
    jcb_e23.inst.cc
    jcb_e33.inst.cc
    list_pool.inst.cc
    met.inst.cc
    met_e1.inst.cc
    met_e2.inst.cc
    met_e3.inst.cc
    namespace_poset.inst.cc
    st2.inst.cc
    st2_e2.inst.cc
    st2_e3.inst.cc
    st3_e3.inst.cc
    st4_e2.inst.cc
    st4_e3.inst.cc
    stp.inst.cc
    symmetric_matrix_2x2.inst.cc
    symmetric_matrix_3x3.inst.cc
    t2_e2.inst.cc
    t2_e3.inst.cc
    t3_e3.inst.cc
    t4_e2.inst.cc
    t4_e3.inst.cc
    tp.inst.cc
    tuple.inst.cc
    vd.inst.cc
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
