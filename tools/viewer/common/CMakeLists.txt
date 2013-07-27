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
    visualization_iterator_1_1.cc
    visualization_iterator_1_3.cc
    visualization_iterator_4_2.cc
    visualization_iterator_4_3.cc
    visualization_iterator.cc
    vtk_poly_data_builder.cc
    vtk_abstract_grid_builder.cc
    vtk_unstructured_grid_builder.cc
    NativeVtk.cc
   )

#
# $$HACK:
# jvm_launcher is linux specific. We may have to extend it to
# cover win32 as well, but for now, ignore it in windows.
#
#if((LINUX64INTEL OR LINUX64GNU) AND BUILD_BINDINGS)
#    set(SRCS ${SRCS} jvm_launcher.cc)
#endif()

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

