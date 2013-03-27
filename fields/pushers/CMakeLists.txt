#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:26 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER pushers)

#
# Library sources.
#
set(SRCS
    average_push_action.cc
    avg_section_pusher.cc
    body_builder.cc
    body_factory.cc
    body_pusher.cc
    body_pusher_pullback_action.cc
    constant_push_action.cc
    copy_push_action.cc
    pullback_map.cc
    section_pusher.cc
    section_pusher_pullback_action.cc
    section_pusher_push_action.cc

)

## @hack: The following 5 classes are excluded from the SRCS list because they 
## are currently unused and there is no working test driver. -- JEB 01/03/13

##    average_base_space_map_push_action.cc
##    base_space_map.cc
##    base_space_map_push_action.cc
##    constant_base_space_map_push_action.cc
##    copy_base_space_map_push_action.cc

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

