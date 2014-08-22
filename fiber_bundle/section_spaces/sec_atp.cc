
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
/// Implementation for class sec_atp.

#include "sec_atp.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/atp.h"
#include "ComLimitPoint/fiber_bundle/atp_space.h"
#include "binary_section_space_schema_member.impl.h"
#include "ComLimitPoint/fiber_bundle/binary_section_space_schema_poset.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "section_space_schema_member.impl.h"
#include "ComLimitPoint/fiber_bundle/section_space_schema_poset.h"
#include "sec_at1.h"
#include "sec_at1_space.h"
#include "sec_atp_space.h"
#include "sec_tuple_space.impl.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS SEC_ATP
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS SEC_ATP
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_atp::host_type&
fiber_bundle::sec_atp::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering sec_atp::new_host." << endl;

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
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path);

  // Exit:

  // cout << "Leaving sec_atp::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// ATP FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_atp::
sec_atp()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::sec_atp::
sec_atp(const sec_rep_space* xhost, pod_index_type xhub_id)
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

fiber_bundle::sec_atp::
sec_atp(const sec_rep_space* xhost, const scoped_index& xid)
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

fiber_bundle::sec_atp::
sec_atp(const sec_rep_space* xhost, const std::string& xname)
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

fiber_bundle::sec_atp::
sec_atp(const namespace_poset* xnamespace,
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

fiber_bundle::sec_atp::
sec_atp(const sec_rep_space_member* xother)
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

fiber_bundle::sec_atp::
sec_atp(sec_rep_space* xhost, section_dof_map* xdof_map, bool xauto_access)
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

fiber_bundle::sec_atp::
sec_atp(sec_rep_space* xhost,
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

fiber_bundle::sec_atp&
fiber_bundle::sec_atp::
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

fiber_bundle::sec_atp&
fiber_bundle::sec_atp::
operator=(const sec_atp& xother)
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

fiber_bundle::sec_atp&
fiber_bundle::sec_atp::
operator=(const atp& xfiber)
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

fiber_bundle::sec_atp&
fiber_bundle::sec_atp::
operator=(const atp_lite& xfiber)
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

fiber_bundle::sec_atp::
~sec_atp()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::sec_atp::fiber_type&
fiber_bundle::sec_atp::
fiber_prototype() const
{
  // Preconditions:

  // Body:

  static const fiber_type result;

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::sec_atp::
is_p_form(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->contains_variance_subposets(xauto_access));

  // Body:

  bool result = host()->is_p_form(_index, xauto_access);
  
  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_atp::
put_is_p_form(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(host()->contains_variance_subposets(xauto_access));

  // Body:

  host()->put_is_p_form(_index, xauto_access);

  // Postconditions:

  ensure(is_p_form(xauto_access));
  
  // Exit:

  return;
}


bool
fiber_bundle::sec_atp::
is_p_vector(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->contains_variance_subposets(xauto_access));

  // Body:

  bool result = host()->is_p_vector(_index, xauto_access);

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_atp::
put_is_p_vector(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  require(host()->contains_variance_subposets(xauto_access));

  // Body:

  host()->put_is_p_vector(_index, xauto_access);

  // Postconditions:

  ensure(is_p_vector(xauto_access));
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::sec_atp::
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
fiber_bundle::sec_atp::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_atp");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::sec_atp*
fiber_bundle::sec_atp::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  sec_atp *result = new sec_atp();

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

fiber_bundle::sec_atp::host_type*
fiber_bundle::sec_atp::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::sec_atp::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS SEC_ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_atp::
fiber_is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this fiber then this
  // fiber is an ancestor of xother.

  bool result = dynamic_cast<const atp*>(xother) != 0;

  // Postconditions:

  ensure(invariant());
  ensure(xother->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_atp::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const sec_atp*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::sec_atp::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(sec_tp::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    ///@todo Fix this when we have is_p_form, etc. implemented.
    //invariance(is_attached() ?  (is_p_form() || is_p_vector()) : true);

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

#include "ComLimitPoint/sheaf/error_message.h"
#include "sec_at0.h"
#include "sec_e2.h"
#include "sec_e3.h"
#include "sec_at2_e2.h"
#include "sec_at2_e3.h"
#include "sec_at3_e3.h"

void
fiber_bundle::sec_atp_algebra::
hook(const sec_atp& x0, const  sec_atp& x1, sec_atp& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x1.dd(xauto_access) == x0.dd(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(x0.is_p_form(xauto_access) == xresult.is_p_form(xauto_access));

  // Body:

  const sec_e2* e2_x0 = dynamic_cast<const sec_e2*>(&x0);
  const sec_e3* e3_x0 = dynamic_cast<const sec_e3*>(&x0);
  const sec_at2_e2* at2_e2_x0 = dynamic_cast<const sec_at2_e2*>(&x0);
  const sec_at2_e3* at2_e3_x0 = dynamic_cast<const sec_at2_e3*>(&x0);
  const sec_at3_e3* at3_e3_x0 = dynamic_cast<const sec_at3_e3*>(&x0);

  const sec_e2* e2_x1 = dynamic_cast<const sec_e2*>(&x1);
  const sec_e3* e3_x1 = dynamic_cast<const sec_e3*>(&x1);

  sec_at0* at0_xresult = dynamic_cast<sec_at0*>(&xresult);
  sec_e2* e2_xresult = dynamic_cast<sec_e2*>(&xresult);
  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);
  sec_at2_e3* at2_e3_xresult = dynamic_cast<sec_at2_e3*>(&xresult);

  if(e2_x0 && e2_x1 && at0_xresult)
  {
    hook(*e2_x0, *e2_x1, *at0_xresult, xauto_access);
  }
  else if(at2_e2_x0 && e2_x1 && e2_xresult)
  {
    hook(*at2_e2_x0, *e2_x1, *e2_xresult, xauto_access);
  }
  else if(e3_x0 && e3_x1 && at0_xresult)
  {
    hook(*e3_x0, *e3_x1, *at0_xresult, xauto_access);
  }
  else if(at2_e3_x0 && e3_x1 && e3_xresult)
  {
    hook(*at2_e3_x0, *e3_x1, *e3_xresult, xauto_access);
  }
  else if(at3_e3_x0 && e3_x1 && at2_e3_xresult)
  {
    hook(*at3_e3_x0, *e3_x1, *at2_e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to hook(...)");
  } 

  // Postconditions:

  ensure(xresult.variance(xauto_access) == hook(x0.variance(xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
star(const sec_atp& x0, sec_atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));

  // Body:

  const sec_at2_e2* at2_e2_x0 = dynamic_cast<const sec_at2_e2*>(&x0);
  const sec_at0* at0_x0 = dynamic_cast<const sec_at0*>(&x0);
  const sec_e2* e2_x0 = dynamic_cast<const sec_e2*>(&x0);
  const sec_at2_e3* at2_e3_x0 = dynamic_cast<const sec_at2_e3*>(&x0);
  const sec_e3* e3_x0 = dynamic_cast<const sec_e3*>(&x0);
  const sec_at3_e3* at3_e3_x0 = dynamic_cast<const sec_at3_e3*>(&x0);

  sec_at0* at0_xresult = dynamic_cast<sec_at0*>(&xresult);
  sec_at2_e2* at2_e2_xresult = dynamic_cast<sec_at2_e2*>(&xresult);
  sec_e2* e2_xresult = dynamic_cast<sec_e2*>(&xresult);
  sec_e3* e3_xresult = dynamic_cast<sec_e3*>(&xresult);
  sec_at2_e3* at2_e3_xresult = dynamic_cast<sec_at2_e3*>(&xresult);
  sec_at3_e3* at3_e3_xresult = dynamic_cast<sec_at3_e3*>(&xresult);

  if(at2_e2_x0 && at0_xresult)
  {
    star(*at2_e2_x0, *at0_xresult, xauto_access);
  }
  else if(at0_x0 && at2_e2_xresult)
  {
    star(*at0_x0, *at2_e2_xresult, xauto_access);
  }
  else if(e2_x0 && e2_xresult)
  {
    star(*e2_x0, *e2_xresult, xauto_access);
  }
  else if(at2_e3_x0 && e3_xresult)
  {
    star(*at2_e3_x0, *e3_xresult, xauto_access);
  }
  else if(e3_x0 && at2_e3_xresult)
  {
    star(*e3_x0, *at2_e3_xresult, xauto_access);
  }
  else if(at3_e3_x0 && at0_xresult)
  {
    star(*at3_e3_x0, *at0_xresult, xauto_access);
  }
  else if(at0_x0 && at3_e3_xresult)
  {
    star(*at0_x0, *at3_e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to star(...)");
  } 

  // Postconditions:

  ///@todo Postconditions.

//   ensure((x0.p(xauto_access)>0) \
//     ? (xresult.is_p_form(xauto_access) == x0.is_p_form(xauto_access)) : true);
//   ensure((x0.p(xauto_access)==0) \
//     ? (xresult.is_p_form(xauto_access) == old_xresult_is_p_form): true );

  // Exit:

  return;
}

void
fiber_bundle::sec_atp_algebra::
wedge(const sec_atp& x0, const sec_atp& x1, sec_atp& xresult, bool xauto_access)
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

  const sec_e2* e2_x0 = dynamic_cast<const sec_e2*>(&x0);
  const sec_e3* e3_x0 = dynamic_cast<const sec_e3*>(&x0);
  const sec_at2_e3* at2_e3_x0 = dynamic_cast<const sec_at2_e3*>(&x0);

  const sec_e2* e2_x1 = dynamic_cast<const sec_e2*>(&x1);
  const sec_e3* e3_x1 = dynamic_cast<const sec_e3*>(&x1);

  sec_at2_e2* at2_e2_xresult = dynamic_cast<sec_at2_e2*>(&xresult);
  sec_at2_e3* at2_e3_xresult = dynamic_cast<sec_at2_e3*>(&xresult);
  sec_at3_e3* at3_e3_xresult = dynamic_cast<sec_at3_e3*>(&xresult);

  if(e2_x0 && e2_x1 && at2_e2_xresult)
  {
    wedge(*e2_x0, *e2_x1, *at2_e2_xresult, xauto_access);
  }
  else if(e3_x0 && e3_x1 && at2_e3_xresult)
  {
    wedge(*e3_x0, *e3_x1, *at2_e3_xresult, xauto_access);
  }
  else if(at2_e3_x0 && e3_x1 && at3_e3_xresult)
  {
    wedge(*at2_e3_x0, *e3_x1, *at3_e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to wedge(...)");
  } 

  // Postconditions:

  ///@todo Postconditions.

//   ensure(xresult.variance(xauto_access) == \
//     wedge(x0.variance(xauto_access), x1.variance(xauto_access)));

  // Exit:

  return;
}

