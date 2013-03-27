#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.10 $ $Date: 2013/01/12 17:17:38 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER iterators)

#
# Library sources.
#
set(SRCS
    biorder_iterator.cc
    biorder_itr.cc
    block_decomposition_iterator.cc
    depth_first_iterator.cc
    depth_first_itr.cc
    filtered_depth_first_itr.cc
    filtered_depth_first_iterator.cc
    filtered_depth_first_member_iterator.cc
    index_iterator.cc
    linkorder_iterator.cc
    linkorder_itr.cc
    postorder_iterator.cc
    postorder_itr.cc
    postorder_member_iterator.cc
    preorder_iterator.cc
    preorder_itr.cc
    preorder_member_iterator.cc
    subposet_member_iterator.cc
    triorder_iterator.cc
    triorder_itr.cc
)

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    poset_member_iterator.h 
	biorder_itr.impl.h 
	depth_first_itr.impl.h 
	filtered_depth_first_itr.impl.h 
	linkorder_itr.impl.h 
	postorder_itr.impl.h 
	preorder_itr.impl.h 
	triorder_itr.impl.h
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
