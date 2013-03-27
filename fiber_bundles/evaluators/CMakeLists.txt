#
# $RCSfile: CMakeLists.txt,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:16:57 $
#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

#------------------------------------------------
# Programmer Filename Entry Section
#------------------------------------------------

set(CLUSTER evaluators)

#
# Library sources.
#
set(SRCS
    dlinear_eval_family.cc
    differentiable_section_evaluator.cc
    constant_eval_family.cc
    constant_fcn_space.cc
    constant_hex.cc
    constant_point.cc
    constant_quad.cc
    constant_segment.cc
    constant_tet.cc
    constant_triangle.cc
    eval_family.cc
    integrable_section_evaluator.cc
    uniform_eval_family.cc
    section_evaluator.cc
    linear_fcn_space.cc
    bilinear_2d.cc
    linear_1d.cc
    linear_2d.cc
    linear_3d.cc
    quadratic_1d.cc
    quadratic_2d.cc
    quadratic_3d.cc
    trilinear_3d.cc
    uniform_1d.cc
    uniform_2d.cc
    uniform_3d.cc
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
# Source for non-test executables.
#
set(EXAMPLE_SRCS

 )

collect_example_sources()

