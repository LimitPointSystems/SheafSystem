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
    array_cylindrical_point_locator.cc
    cylindrical_point_locator.cc
    db0_point_locator.cc
    d_array_point_locator.cc
    d_bin_point_locator.cc
    d_bin_coordinates.cc
    d_bounding_box.cc
    d_tree_point_locator.cc
    d_tree_point_locator_node.cc
    d_tree_point_locator_path.cc
    d_uniform_point_locator.cc
    line_surface_intersecter.cc
    point_locator.cc 
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    db0_point_locator.impl.h 
    d_array_point_locator.impl.h 
    d_bin_coordinates.impl.h 
    d_bin_point_locator.impl.h 
    d_bounding_box.impl.h 
    d_tree_point_locator.impl.h 
    d_tree_point_locator_node.impl.h 
    d_tree_point_locator_path.impl.h 
    d_uniform_point_locator.impl.h
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
