
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
/// Implementation for class sec_jcb.

#include "sec_jcb.h"

#include "assert_contract.h"
#include "binary_section_space_schema_member.impl.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "sec_at0.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_jcb_space.h"
#include "sec_tuple_space.impl.h"
#include "jcb.h"
#include "jcb_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_JCB
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_jcb::host_type&
fiber_bundle::sec_jcb::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xdomain_path,
	 const poset_path& xrange_path,
         bool xauto_access)
{
  // cout << endl << "Entering sec_jcb::new_host." << endl;

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

  // cout << "Leaving sec_jcb::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// JCB FACET OF CLASS SEC_JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_jcb::
sec_jcb()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_jcb::
sec_jcb(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_jcb::
sec_jcb(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_jcb::
sec_jcb(const sec_rep_space* xhost, const std::string& xname)
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


fiber_bundle::sec_jcb::
sec_jcb(const namespace_poset* xnamespace,
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


fiber_bundle::sec_jcb::
sec_jcb(const sec_rep_space_member* xother)
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

fiber_bundle::sec_jcb::
sec_jcb(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_jcb&
fiber_bundle::sec_jcb::
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

fiber_bundle::sec_jcb&
fiber_bundle::sec_jcb::
operator=(const sec_jcb& xother)
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

fiber_bundle::sec_jcb&
fiber_bundle::sec_jcb::
operator=(const jcb& xfiber)
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

fiber_bundle::sec_jcb&
fiber_bundle::sec_jcb::
operator=(const jcb_lite& xfiber)
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

fiber_bundle::sec_jcb::
~sec_jcb()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_jcb::fiber_type&
fiber_bundle::sec_jcb::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}


int
fiber_bundle::sec_jcb::
dd() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->dd();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb::
dd(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->dd(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb::
domain_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->domain_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb::
domain_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->domain_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb::
dr() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->dr();
  
  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

int
fiber_bundle::sec_jcb::
dr(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  int result = host()->dr(xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb::
range_path() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:
 
  poset_path result(host()->range_path());

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::sec_jcb::
range_path(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:
 
  poset_path result(host()->range_path(xauto_access));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_jcb::
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
fiber_bundle::sec_jcb::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_jcb");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_jcb*
fiber_bundle::sec_jcb::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_jcb *result = new sec_jcb();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_jcb::host_type*
fiber_bundle::sec_jcb::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_jcb::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_JCB
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_jcb::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const jcb*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_jcb::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_jcb*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_jcb::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(sec_vd::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(is_attached() ? df() == dd()*dr() : true);
    invariance(is_attached() ? dr() == db() : true);

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


//##############################################################################
//##############################################################################

///@issue Where do these functions go?

fiber_bundle::sec_at0*
fiber_bundle::sec_jcb::
comp2(int row, int col) const
{

  // Preconditions:

  require(0 <= row && row <= dd());
  require(0 <= col && col <= dr());

  // Body:

  // Convert (row, col) into an index into linear component storage and
  // retrieve result.

  sec_at0 *result = comp(row * dr() + col);

  // Postconditions:

  ensure(result != 0);
  ensure(invariant());
  ensure(result->invariant());

  // Exit:

  return result;

}

void
fiber_bundle::sec_jcb::
set_comp2(int row, int col, sec_at0* new_comp)
{

  // Preconditions:

  require(0 <= row && row <= dd());
  require(0 <= col && col <= dr());
  require(new_comp != 0);

  // Body:

  // Convert (row, col) into an index into linear component storage and
  // set requested component to new_comp.

  set_comp(row * dr() + col, new_comp);

  // Postconditions:

  ensure(invariant());

}

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#include "error_message.h"
#include "sec_at1.h"
#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_jcb_e13.h"
#include "sec_jcb_e23.h"
#include "sec_jcb_e33.h"

void
fiber_bundle::sec_jcb_algebra::
push(const sec_jcb& xjcb, const sec_at1& xvector, sec_at1& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  //require(xvector.d(xauto_access) == xjcb.dd(xauto_access));
  //require(xresult.d(xauto_access) == xjcb.dr(xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual
  require(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Body:

  const sec_jcb_e13* jcb_e13_xjcb = dynamic_cast<const sec_jcb_e13*>(&xjcb);
  const sec_jcb_e23* jcb_e23_xjcb = dynamic_cast<const sec_jcb_e23*>(&xjcb);
  const sec_jcb_e33* jcb_e33_xjcb = dynamic_cast<const sec_jcb_e33*>(&xjcb);

  const sec_e1* e1_xvector = dynamic_cast<const sec_e1*>(&xvector);
  const sec_e2* e2_xvector = dynamic_cast<const sec_e2*>(&xvector);
  const sec_e3* e3_xvector = dynamic_cast<const sec_e3*>(&xvector);

  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);

  if(jcb_e13_xjcb && e1_xvector && e3_xresult)
  {
    push(*jcb_e13_xjcb, *e1_xvector, *e3_xresult, xauto_access);
  }
  else if(jcb_e23_xjcb && e2_xvector && e3_xresult)
  {
    push(*jcb_e23_xjcb, *e2_xvector, *e3_xresult, xauto_access);
  }
  else if(jcb_e33_xjcb && e3_xvector && e3_xresult)
  {
    push(*jcb_e33_xjcb, *e3_xvector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to push(...)");
  } 

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

void
fiber_bundle::sec_jcb_algebra::
pull(const sec_jcb& xjcb, const sec_at1& xcovector, sec_at1& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(xjcb.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  //require(xcovector.d(xauto_access) == xjcb.dr(xauto_access));
  //require(xresult.d(xauto_access) == xjcb.dd(xauto_access));
  require(xcovector.is_covariant(0, xauto_access)); // is_dual
  require(xresult.is_covariant(0, xauto_access));   // is_dual

  // Body:

  const sec_jcb_e13* jcb_e13_xjcb = dynamic_cast<const sec_jcb_e13*>(&xjcb);
  const sec_jcb_e23* jcb_e23_xjcb = dynamic_cast<const sec_jcb_e23*>(&xjcb);
  const sec_jcb_e33* jcb_e33_xjcb = dynamic_cast<const sec_jcb_e33*>(&xjcb);

  const sec_e3* e3_xcovector = dynamic_cast<const sec_e3*>(&xcovector);

  sec_e1* e1_xresult = dynamic_cast<sec_e1*>(&xresult);
  sec_e2* e2_xresult = dynamic_cast<sec_e2*>(&xresult);
  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);

  if(jcb_e13_xjcb && e3_xcovector && e1_xresult)
  {
    pull(*jcb_e13_xjcb, *e3_xcovector, *e1_xresult, xauto_access);
  }
  else if(jcb_e23_xjcb && e3_xcovector && e2_xresult)
  {
    pull(*jcb_e23_xjcb, *e3_xcovector, *e2_xresult, xauto_access);
  }
  else if(jcb_e33_xjcb && e3_xcovector && e3_xresult)
  {
    pull(*jcb_e33_xjcb, *e3_xcovector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to pull(...)");
  } 

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));   // is_dual

  // Exit:

  return;
}

