


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class sec_t4_e3.


#include "sec_t4_e3.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.impl.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "index_space_iterator.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "sec_stp_space.h"
#include "sec_tuple.impl.h"
#include "sec_tuple_space.impl.h"
#include "sec_vd.impl.h"
#include "t4_e3.h"
#include "stp_space.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_T4_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_T4_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_t4_e3::host_type&
fiber_bundle::sec_t4_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_t4_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(host_type::fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  require(xns.path_is_auto_read_accessible<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(host_type::same_vector_fiber_space(xns, xschema_path, xvector_space_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
         xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access));
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 4);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving sec_t4_e3::new_host." << endl;
  return result;
}

fiber_bundle::sec_t4_e3::host_type&
fiber_bundle::sec_t4_e3::
standard_host(namespace_type& xns, 
              const poset_path& xbase_path, 
              const poset_path& xrep_path, 
              const string& xsection_suffix, 
              const string& xfiber_suffix, 
              bool xauto_access)
{
  // cout << endl << "Entering sec_t4_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(xrep_path.empty() || xrep_path.full());
  require(xrep_path.empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));  

  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  require(standard_host_is_available<sec_t4_e3>(xns, xbase_path, xrep_path, xsection_suffix, xfiber_suffix, xauto_access));
  require(fiber_type::standard_host_is_available<fiber_type>(xns, xfiber_suffix, xauto_access));
  require(schema_type::standard_host_is_available<sec_t4_e3>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access));

  // Body:

  poset_path lstd_path = standard_host_path<sec_t4_e3>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix);
  
  host_type* lresult_ptr;
  
  if(xns.contains_path(lstd_path, xauto_access))
  {
    // Standard host already exists, just return it.

    lresult_ptr = &xns.member_poset<host_type>(lstd_path, xauto_access);
  }
  else
  {
    // Standard host doesn't exist, have to create it.

    // Apply default for rep path if needed.

    poset_path lrep_path = (!xrep_path.empty() ? xrep_path : standard_rep_path());

    // Find or create the standard schema member.

    poset_path lstd_schema_path = 
      schema_type::standard_member<sec_t4_e3>(xns, xbase_path, lrep_path, xfiber_suffix, xauto_access);

    // Find or create the standard vector space.

    poset_path lvector_space_path = 
      vector_space_type::standard_host(xns, xbase_path, lrep_path, xsection_suffix, xfiber_suffix, xauto_access).path(xauto_access);
    
    // Create the standard host.

    lresult_ptr = &new_host(xns, lstd_path, lstd_schema_path, lvector_space_path, xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<sec_t4_e3>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == 
         schema_type::standard_member_path<sec_t4_e3>(xbase_path, xrep_path, xfiber_suffix));

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
         scalar_type::standard_host_path<scalar_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 4);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == 
         vector_space_type::standard_host_path<vector_space_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));

  // Exit:

  // cout << "Leaving sec_t4_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// T4_E3 FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_t4_e3::
sec_t4_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(const sec_rep_space_member& xother)
{

  // Preconditions:

  require(xother.is_attached() ? xother.state_is_read_accessible() : true);

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached());
  ensure(is_same_state(&xother));
  ensure(is_same_restriction(&xother));
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(\
    xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Body:

  new_jim_state(xhost, xdof_map, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xdof_map, false, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(const sec_rep_space* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(const sec_rep_space* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
  ensure(!is_restricted());
}

fiber_bundle::sec_t4_e3::
sec_t4_e3(const sec_rep_space* xhost, const string& xname)
{

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());
  require(xhost->contains_member(xname));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(invariant());
  //ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
  ensure(!is_restricted());

}

fiber_bundle::sec_t4_e3::
sec_t4_e3(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::sec_t4_e3&
fiber_bundle::sec_t4_e3::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));
  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::sec_t4_e3&
fiber_bundle::sec_t4_e3::
operator=(const sec_t4_e3& xother)
{
  // Preconditions:

  require(precondition_of(attach_to_state(&xother)));

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(&xother)));

  // Exit:

  return *this;
}

fiber_bundle::sec_t4_e3&
fiber_bundle::sec_t4_e3::
operator=(const t4_e3& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_t4_e3&
fiber_bundle::sec_t4_e3::
operator=(const t4_e3_lite& xfiber)
{
  // Preconditions:

  require(precondition_of(sec_vd::operator=(xfiber)));

  // Body:

  sec_vd::operator=(xfiber);

  // Postconditions:

  ensure(postcondition_of(sec_vd::operator=(xfiber)));

  // Exit:

  return *this;
}

fiber_bundle::sec_t4_e3::
~sec_t4_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_t4_e3::fiber_type&
fiber_bundle::sec_t4_e3::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// T4 FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const string&
fiber_bundle::sec_t4_e3::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const string&
fiber_bundle::sec_t4_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_t4_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_t4_e3*
fiber_bundle::sec_t4_e3::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_t4_e3 *result = new sec_t4_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_T4_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_t4_e3::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const t4_e3*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_t4_e3::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const sec_t4_e3*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_t4_e3::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(sec_tp::invariant());

    // Invariances for this class:

    invariance(state_is_read_accessible() ? dd() == 3 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


