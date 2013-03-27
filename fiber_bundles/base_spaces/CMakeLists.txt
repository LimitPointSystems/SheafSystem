#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:16:51 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER base_spaces)

#
# Library sources.
#
set(SRCS
    base_space_crg_interval.cc
    base_space_factory.cc
    base_space_member.cc
    base_space_member_prototype.cc
    base_space_poset.cc
    binary_index.cc
    binary_index_space.cc
    block_adjacency.cc
    block_connectivity.cc
    block_relation.cc
    chart_point.cc
    chart_point_1d.cc
    chart_point_2d.cc
    chart_point_3d.cc
    hex_connectivity.cc
    homogeneous_block.cc
    homogeneous_block_crg_interval.cc
    line_connectivity.cc
    point_block_1d.cc
    point_block_2d.cc
    point_block_3d.cc
    point_block_crg_interval.cc
    point_connectivity.cc
    local_base_space_member.cc
    quad_connectivity.cc
    structured_block.cc
    structured_block_1d.cc
    structured_block_1d_crg_interval.cc
    structured_block_2d.cc
    structured_block_2d_crg_interval.cc
    structured_block_3d.cc
    structured_block_3d_crg_interval.cc
    ternary_index.cc
    ternary_index_space.cc
    tetra_connectivity.cc
    triangle_connectivity.cc
    unary_index_space.cc
    unstructured_block.cc
    unstructured_block_builder.cc
    zone_nodes_block.cc
    zone_nodes_block_crg_interval.cc
# The following files are no longer part of the build.
# they are deprecated and only remain around as a reference
# for future development.
#    connectivity_array.cc
#    material_decomposition.cc
#    mesh_decomposition.cc
#    mesh_partition.cc
#    processor_decomposition.cc
#    zone_partition.cc
#    adjacency_extractor.cc
#    connectivity_extractor.cc
#    neighborhood_extractor.cc
#    stencil_extractor.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    base_space_factory.impl.h 
    unary_index.h
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

