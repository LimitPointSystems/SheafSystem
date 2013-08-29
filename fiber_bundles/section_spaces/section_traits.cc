


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Template specialization and instantiation for class template section_traits

#include "section_traits.h"
#include "base_space_member.h"
#include "fiber_bundles_namespace.h"
#include "poset_path.h"
#include "sec_rep_descriptor.h"

#include "std_string.h"

// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_AT0
// =============================================================================

#ifndef SEC_AT0_H
#include "sec_at0.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_at0>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at0>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at0>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_at0>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS

// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_AT1
// =============================================================================

#ifndef SEC_AT1_H
#include "sec_at1.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_at1>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at1>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at1>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");

  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_at1>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_AT2_E2
// =============================================================================

#ifndef SEC_AT2_E2_H
#include "sec_at2_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_at2_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at2_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at2_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "element_element_constant");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_at2_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_AT2_E3
// =============================================================================

#ifndef SEC_AT2_E3_H
#include "sec_at2_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_at2_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at2_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at2_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "element_element_constant");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_at2_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_AT3_E3
// =============================================================================

#ifndef SEC_AT3_E3_H
#include "sec_at3_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_at3_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at3_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_at3_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "element_element_constant");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_at3_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E1
// =============================================================================

#ifndef SEC_E1_H
#include "sec_e1.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e1>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e1>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e1>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e1>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E1_UNIFORM
// =============================================================================

#ifndef SEC_E1_UNIFORM_H
#include "sec_e1_uniform.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e1_uniform>::
must_use_standard_base_type()
{
  return true;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e1_uniform>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e1_uniform>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_block_uniform");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e1_uniform>::
must_use_standard_rep()
{
  return true;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E2
// =============================================================================

#ifndef SEC_E2_H
#include "sec_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E2_UNIFORM
// =============================================================================

#ifndef SEC_E2_UNIFORM_H
#include "sec_e2_uniform.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e2_uniform>::
must_use_standard_base_type()
{
  return true;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e2_uniform>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e2_uniform>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_block_uniform");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e2_uniform>::
must_use_standard_rep()
{
  return true;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E3
// =============================================================================

#ifndef SEC_E3_H
#include "sec_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_E3_UNIFORM
// =============================================================================

#ifndef SEC_E3_UNIFORM_H
#include "sec_e3_uniform.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_e3_uniform>::
must_use_standard_base_type()
{
  return true;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e3_uniform>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_e3_uniform>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_block_uniform");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_e3_uniform>::
must_use_standard_rep()
{
  return true;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_JCB_E13
// =============================================================================

#ifndef SEC_JCB_E13_H
#include "sec_jcb_e13.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e13>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e13>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e13>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e13>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_JCB_E23
// =============================================================================

#ifndef SEC_JCB_E23_H
#include "sec_jcb_e23.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e23>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e23>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e23>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e23>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_JCB_E33
// =============================================================================

#ifndef SEC_JCB_E33_H
#include "sec_jcb_e33.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e33>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e33>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e33>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_jcb_e33>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_MET_E1
// =============================================================================

#ifndef SEC_MET_E1_H
#include "sec_met_e1.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e1>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e1>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e1>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e1>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_MET_E2
// =============================================================================

#ifndef SEC_MET_E2_H
#include "sec_met_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_MET_E3
// =============================================================================

#ifndef SEC_MET_E3_H
#include "sec_met_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_met_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_met_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_ST2_E2
// =============================================================================

#ifndef SEC_ST2_E2_H
#include "sec_st2_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_st2_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st2_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st2_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_st2_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_ST2_E3
// =============================================================================

#ifndef SEC_ST2_E3_H
#include "sec_st2_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_st2_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st2_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st2_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_st2_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_ST3_E3
// =============================================================================

#ifndef SEC_ST3_E3_H
#include "sec_st3_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_st3_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st3_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st3_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_st3_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_ST4_E2
// =============================================================================

#ifndef SEC_ST4_E2_H
#include "sec_st4_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_st4_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st4_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st4_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_st4_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_ST4_E3
// =============================================================================

#ifndef SEC_ST4_E3_H
#include "sec_st4_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_st4_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st4_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_st4_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_st4_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_T2_E2
// =============================================================================

#ifndef SEC_T2_E2_H
#include "sec_t2_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_t2_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t2_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t2_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_t2_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_T2_E3
// =============================================================================

#ifndef SEC_T2_E3_H
#include "sec_t2_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_t2_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t2_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t2_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_t2_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_T3_E3
// =============================================================================

#ifndef SEC_T3_E3_H
#include "sec_t3_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_t3_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t3_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t3_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_t3_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_T4_E2
// =============================================================================

#ifndef SEC_T4_E2_H
#include "sec_t4_e2.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_t4_e2>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t4_e2>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t4_e2>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_t4_e2>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_T4_E3
// =============================================================================

#ifndef SEC_T4_E3_H
#include "sec_t4_e3.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_t4_e3>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t4_e3>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_t4_e3>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_t4_e3>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


// =============================================================================
// SPECIALIZATION AND INSTANTIATION FOR SEC_VD
// =============================================================================

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
bool
fiber_bundle::section_traits<fiber_bundle::sec_vd>::
must_use_standard_base_type()
{
  return false;
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_vd>::
standard_fiber_schema_path()
{
  return standard_fiber_type::standard_schema_path();
};

const sheaf::poset_path&
fiber_bundle::section_traits<fiber_bundle::sec_vd>::
standard_rep_path()
{
  static const poset_path
  result(sec_rep_descriptor::standard_host_path().poset_name(), "vertex_element_dlinear");
  return result;
};

bool
fiber_bundle::section_traits<fiber_bundle::sec_vd>::
must_use_standard_rep()
{
  return false;
};
#endif // DOXYGEN_SKIP_INSTANTIATIONS


