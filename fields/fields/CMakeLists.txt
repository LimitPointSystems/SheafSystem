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
    discretization_push_action.cc
    discretization_pusher.cc
    field_at0.cc
    field_at1.cc
    field_at2.cc
    field_at2_e2.cc
    field_at2_e3.cc
    field_at3.cc
    field_at3_e3.cc
    field_atp.cc
    field_e1.cc
    field_e1_uniform.cc
    field_e2.cc
    field_e2_uniform.cc
    field_e3.cc
    field_e3_uniform.cc
    field_e4.cc
    field_ed.cc
    field_factory.cc
    field_factory_2.cc
    field_jcb.cc
    field_jcb_e13.cc
    field_jcb_e23.cc
    field_jcb_e33.cc
    field_jcb_ed.cc
    field_met.cc
    field_met_e1.cc
    field_met_e2.cc
    field_met_e3.cc
    field_met_ed.cc
    field_st2.cc
    field_st2_e2.cc
    field_st2_e3.cc
    field_st3.cc
    field_st3_e3.cc
    field_st4.cc
    field_st4_e2.cc
    field_st4_e3.cc
    field_stp.cc
    field_t2.cc
    field_t2_e2.cc
    field_t2_e3.cc
    field_t3.cc
    field_t3_e3.cc
    field_t4.cc
    field_t4_e2.cc
    field_t4_e3.cc
    field_tp.cc
    field_traits.cc
    field_vd.cc
    fields.cc
    print_property_dofs_action.cc
    put_property_dofs_action.cc
    put_property_dofs_fcn_action.cc
   )

collect_sources()

#
# Headers that are NOT associated with a .cc file.
#
set(ADDITIONAL_INCS
    field_at0_funcs.h 
    field_at0_funcs.impl.h 
    field_atp_funcs.h 
    field_atp_funcs.impl.h 
    field_e3_funcs.h 
    field_e3_funcs.impl.h 
    field_ed_funcs.h 
    field_ed_funcs.impl.h 
    field_factory_2.impl.h 
    field_jcb_funcs.h 
    field_jcb_funcs.impl.h 
    field_met_funcs.h 
    field_met_funcs.impl.h 
    field_st2_funcs.h 
    field_st2_funcs.impl.h 
    field_stp_funcs.h 
    field_stp_funcs.impl.h 
    field_tp_funcs.h 
    field_tp_funcs.impl.h 
    field_vd_funcs.h 
    field_vd_funcs.impl.h 
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
