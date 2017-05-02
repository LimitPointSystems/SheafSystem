
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Implementation for class sec_at2_e3.


#include "SheafSystem/sec_at2_e3.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/binary_section_space_schema_member.impl.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_tuple.impl.h"
#include "SheafSystem/sec_tuple_space.impl.h"
#include "SheafSystem/sec_vd.impl.h"
#include "SheafSystem/at2_e3.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_AT2_E3
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_AT2_E3
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at2_e3::host_type&
fiber_bundle::sec_at2_e3::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_at2_e3::new_host." << endl;

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
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving sec_at2_e3::new_host." << endl;
  return result;
}

fiber_bundle::sec_at2_e3::host_type&
fiber_bundle::sec_at2_e3::
standard_host(namespace_type& xns, 
              const poset_path& xbase_path, 
              const poset_path& xrep_path, 
              const std::string& xsection_suffix, 
              const std::string& xfiber_suffix, 
              bool xauto_access)
{
  // cout << endl << "Entering sec_at2_e3::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(xrep_path.empty() || xrep_path.full());
  require(xrep_path.empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));  

  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  require(standard_host_is_available<sec_at2_e3>(xns, xbase_path, xrep_path, xsection_suffix, xfiber_suffix, xauto_access));
  require(fiber_type::standard_host_is_available<fiber_type>(xns, xfiber_suffix, xauto_access));
  require(schema_type::standard_host_is_available<sec_at2_e3>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access));

  // Body:

  poset_path lstd_path = standard_host_path<sec_at2_e3>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix);
  
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
      schema_type::standard_member<sec_at2_e3>(xns, xbase_path, lrep_path, xfiber_suffix, xauto_access);

    // Find or create the standard vector space.

    poset_path lvector_space_path = 
      vector_space_type::standard_host(xns, xbase_path, lrep_path, xsection_suffix, xfiber_suffix, xauto_access).path(xauto_access);
    
    // Create the standard host.

    lresult_ptr = &new_host(xns, lstd_path, lstd_schema_path, lvector_space_path, xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<sec_at2_e3>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == 
         schema_type::standard_member_path<sec_at2_e3>(xbase_path, xrep_path, xfiber_suffix));

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
         scalar_type::standard_host_path<scalar_type>(xbase_path, result.rep().path(xauto_access), xsection_suffix, xfiber_suffix));
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == 
         vector_space_type::standard_host_path<vector_space_type>(xbase_path, result.rep().path(xauto_access), xsection_suffix, xfiber_suffix));

  // Exit:

  // cout << "Leaving sec_at2_e3::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// AT2_E3 FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at2_e3::
sec_at2_e3()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_at2_e3::
sec_at2_e3(const sec_rep_space_member& xother)
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

fiber_bundle::sec_at2_e3::
sec_at2_e3(sec_rep_space* xhost,
           abstract_poset_member& xbase_mbr,
           int xbase_version, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Body:

  new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, xbase_mbr, xbase_version, xauto_access)));

  // Exit:

  return;
}

fiber_bundle::sec_at2_e3::
sec_at2_e3(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_at2_e3::
sec_at2_e3(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_at2_e3::
sec_at2_e3(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_at2_e3::
sec_at2_e3(const sec_rep_space* xhost, const std::string& xname)
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

fiber_bundle::sec_at2_e3::
sec_at2_e3(const namespace_poset* xnamespace,
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

fiber_bundle::sec_at2_e3&
fiber_bundle::sec_at2_e3::
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

fiber_bundle::sec_at2_e3&
fiber_bundle::sec_at2_e3::
operator=(const sec_at2_e3& xother)
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

fiber_bundle::sec_at2_e3&
fiber_bundle::sec_at2_e3::
operator=(const at2_e3& xfiber)
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

fiber_bundle::sec_at2_e3&
fiber_bundle::sec_at2_e3::
operator=(const at2_e3_lite& xfiber)
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

fiber_bundle::sec_at2_e3::
~sec_at2_e3()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_at2_e3::fiber_type&
fiber_bundle::sec_at2_e3::
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
// AT2 FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_at2_e3::
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

const std::string&
fiber_bundle::sec_at2_e3::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_at2_e3");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}


fiber_bundle::sec_at2_e3*
fiber_bundle::sec_at2_e3::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_at2_e3 *result = new sec_at2_e3();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_AT2_E3
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_at2_e3::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const at2_e3*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_at2_e3::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  bool result = dynamic_cast<const sec_at2_e3*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_at2_e3::
invariant() const
{
  bool result = true;

  // Body:

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(sec_atp::invariant());

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


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

namespace
{
  using namespace fiber_bundle::atp_algebra;

  class hook_functor
  {
  public:
    void operator()(const e3_lite& x0, const e3_lite& x1,
                    at0_lite& xresult) const
    {
      hook(x0, x1, xresult);
    }

    void operator()(const at2_e3_lite& x0, const e3_lite& x1,
                    e3_lite& xresult) const
    {
      hook(x0, x1, xresult);
    }
  };

  class star_functor
  {
  public:
    void operator()(const at2_e3_lite& x0, e3_lite& xresult) const
    {
      star(x0, xresult);
    }

    void operator()(const e3_lite& x0, at2_e3_lite& xresult) const
    {
      star(x0, xresult);
    }
  };

  class wedge_functor
  {
  public:
    void operator()(const e3_lite& x0, const e3_lite& x1,
                    at2_e3_lite& xresult) const
    {
      wedge(x0, x1, xresult);
    }
  };

} //end unnamed namespace

//==============================================================================

#include "SheafSystem/sec_vd.impl.h"
#include "SheafSystem/sec_e3.h"
#include "SheafSystem/sec_at0.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_atp_algebra::
hook(const sec_e3& x0, const sec_e3& x1, sec_at0& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 1);

  // Body:

  binary_op(x0, x1, xresult, hook_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(hook(x0.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
hook(const sec_at2_e3& x0, const sec_e3& x1, sec_e3& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) - 1);

  // Body:

  binary_op(x0, x1, xresult, hook_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(hook(x0.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));

  // Exit:

  return;
}


void
fiber_bundle::sec_atp_algebra::
star(const sec_at2_e3& x0, sec_e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, star_functor(), xauto_access);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do no need to set the variance
  // of the result because it does not change.

  define_old_variable(\
    bool old_xresult_is_p_form = xresult.is_p_form(xauto_access));

  if(x0.p(xauto_access) > 0)
  {
    xresult.put_variance(star(x0.variance(xauto_access), x0.dd(xauto_access)),
                         xauto_access);
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
star(const sec_e3& x0, sec_at2_e3& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  unary_op(x0, xresult, star_functor(), xauto_access);

  // Set the variance of the result.

  // If the x0.p() == 0 then x0 is a sec_at0 which is both a p_form
  // and a p_vector.  In that case we do no need to set the variance
  // of the result because it does not change.

  define_old_variable(\
    bool old_xresult_is_p_form = xresult.is_p_form(xauto_access));

  if(x0.p(xauto_access) > 0)
  {
    xresult.put_variance(star(x0.variance(xauto_access), x0.dd(xauto_access)),
                         xauto_access);
  }

  // Postconditions:

  ensure((x0.p(xauto_access)>0) \
    ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
  ensure((x0.p(xauto_access)==0) \
    ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
wedge(const sec_e3& x0, const sec_e3& x1, sec_at2_e3& xresult,
      bool xauto_access)
{
 // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  require(x0.dd(xauto_access) >= xresult.dd(xauto_access));
  require(x1.dd(xauto_access) >= xresult.dd(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) + x1.p(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));

  // Body:

  binary_op(x0, x1, xresult, wedge_functor(), xauto_access);

  // Set the variance of the result.

  xresult.put_variance(wedge(x0.variance(xauto_access), 
                             x1.variance(xauto_access)), xauto_access);

  // Postconditions:

  ensure(xresult.variance(xauto_access) == \
    wedge(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

