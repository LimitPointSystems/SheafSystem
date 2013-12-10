
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Implementation for class sec_jcb_e23.

#include "sec_jcb_e23.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.impl.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "sec_at0.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_jcb_space.h"
#include "sec_tuple.impl.h"
#include "sec_tuple_space.impl.h"
#include "jcb_e23.h"
#include "jcb_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_JCB_E23
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_jcb_e23::host_type&
fiber_bundle::sec_jcb_e23::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xdomain_path,
	 const poset_path& xrange_path,
         bool xauto_access)
{
  // cout << endl << "Entering sec_jcb_e23::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(host_type::fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));

  require(xns.path_is_auto_read_accessible<domain_type::host_type>(xdomain_path, xauto_access));
  require(xns.path_is_auto_read_accessible<range_type::host_type>(xrange_path, xauto_access));

  require(host_type::same_vector_fiber_space(xns, xschema_path, xdomain_path, xrange_path, xauto_access));

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xdomain_path, xrange_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
         xns.member_poset<domain_type::host_type>(xdomain_path, xauto_access).scalar_space_path(xauto_access));
  ensure(result.scalar_space_path(true) == 
         xns.member_poset<range_type::host_type>(xrange_path, xauto_access).scalar_space_path(xauto_access));
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.dr(true) == result.schema(true).fiber_space<fiber_type::host_type>().dr(xauto_access));
  ensure(result.domain_path(true) == xdomain_path);
  ensure(result.range_path(true) == xrange_path);

  // Exit:

  // cout << "Leaving sec_jcb_e23::new_host." << endl;
  return result;
}

fiber_bundle::sec_jcb_e23::host_type&
fiber_bundle::sec_jcb_e23::
standard_host(namespace_type& xns, 
              const poset_path& xbase_path, 
              const poset_path& xrep_path, 
              const std::string& xsection_suffix, 
              const std::string& xfiber_suffix, 
              bool xauto_access)
{
  // cout << endl << "Entering sec_jcb_e23::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(xrep_path.empty() || xrep_path.full());
  require(xrep_path.empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));  

  require(xsection_suffix.empty() || poset_path::is_valid_name(xsection_suffix));

  require(xfiber_suffix.empty() || poset_path::is_valid_name(xfiber_suffix));

  require(standard_host_is_available<sec_jcb_e23>(xns, xbase_path, xrep_path, xsection_suffix, xfiber_suffix, xauto_access));
  require(fiber_type::standard_host_is_available<fiber_type>(xns, xfiber_suffix, xauto_access));
  require(schema_type::standard_host_is_available<sec_jcb_e23>(xns, xbase_path, xrep_path, xfiber_suffix, xauto_access));

  // Body:

  poset_path lstd_path = standard_host_path<sec_jcb_e23>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix);
  
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
      schema_type::standard_member<sec_jcb_e23>(xns, xbase_path, lrep_path, xfiber_suffix, xauto_access);

    // Find or create the standard domain space.

    poset_path ldomain_path = 
      domain_type::standard_host(xns, xbase_path, lrep_path, xsection_suffix, xfiber_suffix, xauto_access).path(xauto_access);
    
    // Find or create the standard range space.

    poset_path lrange_path = 
      range_type::standard_host(xns, xbase_path, lrep_path, xsection_suffix, xfiber_suffix, xauto_access).path(xauto_access);
    
    // Create the standard host.

    lresult_ptr = &new_host(xns, lstd_path, lstd_schema_path, ldomain_path, lrange_path, xauto_access);
  }

  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path<sec_jcb_e23>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == 
         schema_type::standard_member_path<sec_jcb_e23>(xbase_path, xrep_path, xfiber_suffix));

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.scalar_space_path(true) == 
	 standard_host_path<domain_type::scalar_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.scalar_space_path(true) == 
	 standard_host_path<range_type::scalar_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.dr(true) == result.schema(true).fiber_space<fiber_type::host_type>().dr(xauto_access));
  ensure(result.domain_path(true) ==
	 standard_host_path<domain_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));
  ensure(result.range_path(true) ==
	 standard_host_path<range_type>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix));

  // Exit:

  // cout << "Leaving sec_jcb_e23::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// JCB_E23 FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_jcb_e23::
sec_jcb_e23()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_jcb_e23::
sec_jcb_e23(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_jcb_e23::
sec_jcb_e23(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_jcb_e23::
sec_jcb_e23(const sec_rep_space* xhost, const std::string& xname)
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


fiber_bundle::sec_jcb_e23::
sec_jcb_e23(const namespace_poset* xnamespace,
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

fiber_bundle::sec_jcb_e23::
sec_jcb_e23(const sec_rep_space_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));
  ensure(is_same_restriction(xother));

}

fiber_bundle::sec_jcb_e23::
sec_jcb_e23(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_jcb_e23&
fiber_bundle::sec_jcb_e23::
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

fiber_bundle::sec_jcb_e23&
fiber_bundle::sec_jcb_e23::
operator=(const sec_jcb_e23& xother)
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

fiber_bundle::sec_jcb_e23&
fiber_bundle::sec_jcb_e23::
operator=(const jcb_e23& xfiber)
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

fiber_bundle::sec_jcb_e23&
fiber_bundle::sec_jcb_e23::
operator=(const jcb_e23_lite& xfiber)
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

fiber_bundle::sec_jcb_e23::
~sec_jcb_e23()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_jcb_e23::fiber_type&
fiber_bundle::sec_jcb_e23::
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
// JCB_ED FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// JCB FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_jcb_e23::
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
fiber_bundle::sec_jcb_e23::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_jcb_e23");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_jcb_e23*
fiber_bundle::sec_jcb_e23::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_jcb_e23 *result = new sec_jcb_e23();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_JCB_E23
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_jcb_e23::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const jcb_e23*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_jcb_e23::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_jcb_e23*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_jcb_e23::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(sec_jcb_ed::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(is_attached() ? dr() == 3 : true);
    invariance(is_attached() ? dd() == 2 : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

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
using namespace fiber_bundle::jcb_algebra;

class push_functor
{
public:
  void operator()(const jcb_e23_lite& x0, const e2_lite& x1,
                  e3_lite& xresult) const
  {
    push(x0, x1, xresult);
  }
};

class pull_functor
{
public:
  void operator()(const jcb_e23_lite& x0, const e3_lite& x1,
                  e2_lite& xresult) const
  {
    pull(x0, x1, xresult);
  }
};

} //end unnamed namespace 

//==============================================================================

#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_vd.impl.h"

using namespace fiber_bundle::sec_vd_algebra;

void
fiber_bundle::sec_jcb_algebra::
push(const sec_jcb_e23& xjcb, const sec_e2& xvector, sec_e3& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

   binary_op(xjcb, xvector, xresult, push_functor(), xauto_access);

  // Postconditions:


  // Exit:

  return;
}

void
fiber_bundle::sec_jcb_algebra::
pull(const sec_jcb_e23& xjcb, const sec_e3& xcovector, sec_e2& xresult,
     bool xauto_access)
{
 // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

 // Body:

  binary_op(xjcb, xcovector, xresult, pull_functor(), xauto_access);

  // Postconditions:


  // Exit:

  return;
}

