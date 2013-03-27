#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:34 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER dof_maps)

#
# Library sources.
#
set(SRCS
    array_poset_dof_map.cc
    dof_descriptor_array.cc
    dof_map_factory.cc
    dof_tuple_type.cc
    namespace_poset_dof_map.cc
    poset_dof_map.cc
    primitives_poset_dof_map.cc
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
