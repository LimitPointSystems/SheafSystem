
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
/// Implementation for class atp.

#include "ComLimitPoint/fiber_bundle/atp.h"

#include "ComLimitPoint/sheaf/abstract_poset_member.impl.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/at1.h"
#include "ComLimitPoint/fiber_bundle/at1_space.h"
#include "ComLimitPoint/fiber_bundle/atp_space.h"
#include "ComLimitPoint/fiber_bundle/fiber_bundle_namespace.h"
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#include "ComLimitPoint/sheaf/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.
using namespace fiber_bundle::vd_algebra;

//==============================================================================
// CLASS ATP_LITE
//==============================================================================

//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::atp_lite::
atp_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::atp_lite::
atp_lite(const atp_lite& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::atp_lite&
fiber_bundle::atp_lite::
operator=(const atp_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::atp_lite::
~atp_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::atp_lite::
atp_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::atp_lite&
fiber_bundle::atp_lite::
operator=(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  vd_lite::operator=(xrow_dofs);
  
  // Postconditions:

  postcondition_of(vd_lite::operator=(xrow_dofs));

  // Exit:

  return *this;

}

//==============================================================================
// TENSOR ALGEBRA (TP) FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::atp_lite::
d() const
{
  // Preconditions:

  //require(dd() >= p() && p() >= 0);

  // Body:

  //$$SCRIBBLE: Don't know what the correct value is here when
  //            dd() == 0 and p() == 1 (or 0).  For now just return 0.          

  int result = 0;

  if(!(dd() == 0 && p() == 0))
  {
    if(dd() >= p() && p() >= 0)
    {
      result = static_cast<int>(binomial_coefficient(dd(), p()));
    }
  }

  // Postconditions:

  ensure(invariant());
  //ensure(result == static_cast<int>(binomial_coefficient(dd(), p())));

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::atp::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "atp_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::atp::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              tp::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::atp::host_type&
fiber_bundle::atp::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
	 int xp,
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering atp::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xp >= 0);

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<vector_space_type::host_type>(xvector_space_path, xauto_access));

  require(host_type::d(xns, xschema_path, xauto_access) == host_type::d(xns, xp, xvector_space_path, xauto_access)); // dmb new  

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xp, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == host_type::d(xns, xschema_path, xauto_access));
  ensure(result.scalar_space_path(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).scalar_space_path(xauto_access) );
  ensure(result.p(true) == xp);
  ensure(result.dd(true) == xns.member_poset<vector_space_type::host_type>(xvector_space_path, xauto_access).d());
  ensure(result.vector_space_path(true) == xvector_space_path );

  // Exit:

  // cout << "Leaving atp::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::atp_lite::
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
fiber_bundle::atp_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("atp_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::atp_lite*
fiber_bundle::atp_lite::
clone() const
{
  atp_lite* result = 0;

  // Preconditions:

  // Body:

  result = new atp_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ATP_LITE
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::atp_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const atp_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::atp_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(tp_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CLASS ATP
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

//==============================================================================
// EXTERIOR ALGEBRA (ATP) FACET OF CLASS ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::atp::
atp()
{

  // Preconditions:

   // Body:

   // Postconditions:

  ensure(invariant());
}

fiber_bundle::atp::
atp(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

fiber_bundle::atp::
atp(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  // ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

fiber_bundle::atp::
atp(const poset_state_handle* xhost, const std::string& xname)
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
  // ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());

}

fiber_bundle::atp::
atp(abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

}

fiber_bundle::atp::
atp(poset_state_handle* xhost, bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Body:

  new_jim_state(xhost, 0, false, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(xhost, 0, false, xauto_access)));

  // Exit:

  return;
}

///
fiber_bundle::atp&
fiber_bundle::atp::
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

///
fiber_bundle::atp&
fiber_bundle::atp::
operator=(const atp& xother)
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

fiber_bundle::atp::
~atp()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::atp::volatile_type&
fiber_bundle::atp::
lite_prototype() const
{
  // Preconditions:

  // Body:

  static const volatile_type result;

  // Postconditions:

  // Exit:

  return result;
}

///
fiber_bundle::atp::volatile_type*
fiber_bundle::atp::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::atp::
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
fiber_bundle::atp::
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
fiber_bundle::atp::
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
fiber_bundle::atp::
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
// TP FACET OF CLASS ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET OF CLASS ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET OF CLASS ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::atp::
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
fiber_bundle::atp::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("atp");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::atp::host_type*
fiber_bundle::atp::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::atp::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET OF CLASS ATP
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::atp::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const atp*>(xother) != 0;

  // Postconditions:

  //ensure(invariant());
  //ensure(other->invariant());

  // Exit:

  return result;

}

fiber_bundle::atp*
fiber_bundle::atp::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  atp* result = new atp();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::atp::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(tp::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(state_is_read_accessible() ? is_covariant(false) || is_contravariant(false) : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  ensure(is_derived_query);

  // Exit:

  return result;
}

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

#include "ComLimitPoint/sheaf/error_message.h"
#include "ComLimitPoint/fiber_bundle/at0.h"
#include "ComLimitPoint/fiber_bundle/e2.h"
#include "ComLimitPoint/fiber_bundle/e3.h"
#include "ComLimitPoint/fiber_bundle/at2_e2.h"
#include "ComLimitPoint/fiber_bundle/at2_e3.h"
#include "ComLimitPoint/fiber_bundle/at3_e3.h"

///
void
fiber_bundle::atp_algebra::
hook(const atp& x0, const atp& x1, atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.is_p_form(xauto_access) == x1.is_p_form(xauto_access));
  require(x0.is_p_form(xauto_access) == xresult.is_p_form(xauto_access));

  // Body:

  const e2* e2_x0 = dynamic_cast<const e2*>(&x0);
  const e3* e3_x0 = dynamic_cast<const e3*>(&x0);
  const at2_e2* at2_e2_x0 = dynamic_cast<const at2_e2*>(&x0);
  const at2_e3* at2_e3_x0 = dynamic_cast<const at2_e3*>(&x0);
  const at3_e3* at3_e3_x0 = dynamic_cast<const at3_e3*>(&x0);

  const e2* e2_x1 = dynamic_cast<const e2*>(&x1);
  const e3* e3_x1 = dynamic_cast<const e3*>(&x1);

  at0* at0_xresult = dynamic_cast<at0*>(&xresult);
  e2* e2_xresult = dynamic_cast<e2*>(&xresult);
  e3* e3_xresult = dynamic_cast<e3*>(&xresult);
  at2_e3* at2_e3_xresult = dynamic_cast<at2_e3*>(&xresult);

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

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;

}

///
void
fiber_bundle::atp_algebra::
hook(const atp_lite& x0, const atp_lite& x1, atp_lite& xresult)
{
  // Preconditions:

  // Body:

// hook(const e2_lite& x0, const e2_lite& x1, at0_lite& xresult);
// hook(const at2_e2_lite& x0, const e2_lite& x1, e2_lite& xresult);
// hook(const e3_lite& x0, const e3_lite& x1, at0_lite& xresult);
// hook(const at2_e3_lite& x0, const e3_lite& x1, e3_lite& xresult);
// hook(const at3_e3_lite& x0, const e3_lite& x1, at2_e3_lite& xresult);

  const e2_lite* e2_x0 = dynamic_cast<const e2_lite*>(&x0);
  const e3_lite* e3_x0 = dynamic_cast<const e3_lite*>(&x0);
  const at2_e2_lite* at2_e2_x0 = dynamic_cast<const at2_e2_lite*>(&x0);
  const at2_e3_lite* at2_e3_x0 = dynamic_cast<const at2_e3_lite*>(&x0);
  const at3_e3_lite* at3_e3_x0 = dynamic_cast<const at3_e3_lite*>(&x0);

  const e2_lite* e2_x1 = dynamic_cast<const e2_lite*>(&x1);
  const e3_lite* e3_x1 = dynamic_cast<const e3_lite*>(&x1);

  at0_lite* at0_xresult = dynamic_cast<at0_lite*>(&xresult);
  e2_lite* e2_xresult = dynamic_cast<e2_lite*>(&xresult);
  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);
  at2_e3_lite* at2_e3_xresult = dynamic_cast<at2_e3_lite*>(&xresult);

  if(e2_x0 && e2_x1 && at0_xresult)
  {
    hook(*e2_x0, *e2_x1, *at0_xresult);
  }
  else if(at2_e2_x0 && e2_x1 && e2_xresult)
  {
    hook(*at2_e2_x0, *e2_x1, *e2_xresult);
  }
  else if(e3_x0 && e3_x1 && at0_xresult)
  {
    hook(*e3_x0, *e3_x1, *at0_xresult);
  }
  else if(at2_e3_x0 && e3_x1 && e3_xresult)
  {
    hook(*at2_e3_x0, *e3_x1, *e3_xresult);
  }
  else if(at3_e3_x0 && e3_x1 && at2_e3_xresult)
  {
    hook(*at3_e3_x0, *e3_x1, *at2_e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to hook(...)");
  } 

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;

}

///
void
fiber_bundle::atp_algebra::
star(const atp& x0, atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) == xresult.dd(xauto_access));

  // Body:

  const at2_e2* at2_e2_x0 = dynamic_cast<const at2_e2*>(&x0);
  const at0* at0_x0 = dynamic_cast<const at0*>(&x0);
  const e2* e2_x0 = dynamic_cast<const e2*>(&x0);
  const at2_e3* at2_e3_x0 = dynamic_cast<const at2_e3*>(&x0);
  const e3* e3_x0 = dynamic_cast<const e3*>(&x0);
  const at3_e3* at3_e3_x0 = dynamic_cast<const at3_e3*>(&x0);

  at0* at0_xresult = dynamic_cast<at0*>(&xresult);
  at2_e2* at2_e2_xresult = dynamic_cast<at2_e2*>(&xresult);
  e2* e2_xresult = dynamic_cast<e2*>(&xresult);
  e3* e3_xresult = dynamic_cast<e3*>(&xresult);
  at2_e3* at2_e3_xresult = dynamic_cast<at2_e3*>(&xresult);
  at3_e3* at3_e3_xresult = dynamic_cast<at3_e3*>(&xresult);

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

  //ensure();

  // Exit:

  return;
}

///
void
fiber_bundle::atp_algebra::
star(const atp_lite& x0, atp_lite& xresult)
{
  // Preconditions:

//   require(x0.dd() == xresult.dd());

  // Body:

  const at2_e2_lite* at2_e2_x0 = dynamic_cast<const at2_e2_lite*>(&x0);
  const at0_lite* at0_x0 = dynamic_cast<const at0_lite*>(&x0);
  const e2_lite* e2_x0 = dynamic_cast<const e2_lite*>(&x0);
  const at2_e3_lite* at2_e3_x0 = dynamic_cast<const at2_e3_lite*>(&x0);
  const e3_lite* e3_x0 = dynamic_cast<const e3_lite*>(&x0);
  const at3_e3_lite* at3_e3_x0 = dynamic_cast<const at3_e3_lite*>(&x0);

  at0_lite* at0_xresult = dynamic_cast<at0_lite*>(&xresult);
  at2_e2_lite* at2_e2_xresult = dynamic_cast<at2_e2_lite*>(&xresult);
  e2_lite* e2_xresult = dynamic_cast<e2_lite*>(&xresult);
  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);
  at2_e3_lite* at2_e3_xresult = dynamic_cast<at2_e3_lite*>(&xresult);
  at3_e3_lite* at3_e3_xresult = dynamic_cast<at3_e3_lite*>(&xresult);

  if(at2_e2_x0 && at0_xresult)
  {
    star(*at2_e2_x0, *at0_xresult);
  }
  else if(at0_x0 && at2_e2_xresult)
  {
    star(*at0_x0, *at2_e2_xresult);
  }
  else if(e2_x0 && e2_xresult)
  {
    star(*e2_x0, *e2_xresult);
  }
  else if(at2_e3_x0 && e3_xresult)
  {
    star(*at2_e3_x0, *e3_xresult);
  }
  else if(e3_x0 && at2_e3_xresult)
  {
    star(*e3_x0, *at2_e3_xresult);
  }
  else if(at3_e3_x0 && at0_xresult)
  {
    star(*at3_e3_x0, *at0_xresult);
  }
  else if(at0_x0 && at3_e3_xresult)
  {
    star(*at0_x0, *at3_e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to star(...)");
  } 

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;
}

///
fiber_bundle::atp_lite*
fiber_bundle::atp_algebra::
star(const atp_lite& x0)
{
  // Preconditions:

  require(precondition_of(star(x0, *result)));

  // Body:

  atp_lite* result = new atp_lite();;

  star(x0, *result);

  // Postconditions:

  ensure(postcondition_of(star(x0, *result)));

  // Exit:

  return result;
}

///
void
fiber_bundle::atp_algebra::
wedge(const atp& x0, const atp& x1, atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(x0.state_is_auto_read_accessible(xauto_access));
  require(x1.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(x0.dd(xauto_access) >= xresult.dd(xauto_access));
  require(x1.dd(xauto_access) >= xresult.dd(xauto_access));
  require(xresult.p(xauto_access) == x0.p(xauto_access) + x1.p(xauto_access));

  // Body:

  const e2* e2_x0 = dynamic_cast<const e2*>(&x0);
  const e3* e3_x0 = dynamic_cast<const e3*>(&x0);
  const at2_e3* at2_e3_x0 = dynamic_cast<const at2_e3*>(&x0);

  const e2* e2_x1 = dynamic_cast<const e2*>(&x1);
  const e3* e3_x1 = dynamic_cast<const e3*>(&x1);

  at2_e2* at2_e2_xresult = dynamic_cast<at2_e2*>(&xresult);
  at2_e3* at2_e3_xresult = dynamic_cast<at2_e3*>(&xresult);
  at3_e3* at3_e3_xresult = dynamic_cast<at3_e3*>(&xresult);

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

  //ensure();

  // Exit:

  return;
}

///
void
fiber_bundle::atp_algebra::
wedge(const atp_lite& x0, const atp_lite& x1, atp_lite& xresult)
{
  // Preconditions:

  require(x0.dd() == x1.dd());
  require(x0.dd() == xresult.dd());
  require(xresult.p() == x0.p() + x1.p());

  // Body:

  //wedge(const e2_lite& x0, const e2_lite& x1, at2_e2_lite& xresult);
  //wedge(const e3_lite& x0, const e3_lite& x1, at2_e3_lite& xresult);
  //wedge(const at2_e3_lite& x0, const e3_lite& x1, at3_e3_lite& xresult);

  const e2_lite* e2_x0 = dynamic_cast<const e2_lite*>(&x0);
  const e3_lite* e3_x0 = dynamic_cast<const e3_lite*>(&x0);
  const at2_e3_lite* at2_e3_x0 = dynamic_cast<const at2_e3_lite*>(&x0);

  const e2_lite* e2_x1 = dynamic_cast<const e2_lite*>(&x1);
  const e3_lite* e3_x1 = dynamic_cast<const e3_lite*>(&x1);

  at2_e2_lite* at2_e2_xresult = dynamic_cast<at2_e2_lite*>(&xresult);
  at2_e3_lite* at2_e3_xresult = dynamic_cast<at2_e3_lite*>(&xresult);
  at3_e3_lite* at3_e3_xresult = dynamic_cast<at3_e3_lite*>(&xresult);

  if(e2_x0 && e2_x1 && at2_e2_xresult)
  {
    wedge(*e2_x0, *e2_x1, *at2_e2_xresult);
  }
  else if(e3_x0 && e3_x1 && at2_e3_xresult)
  {
    wedge(*e3_x0, *e3_x1, *at2_e3_xresult);
  }
  else if(at2_e3_x0 && e3_x1 && at3_e3_xresult)
  {
    wedge(*at2_e3_x0, *e3_x1, *at3_e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to hook(...)");
  } 

  // Postconditions:

  ///@todo Postconditions.

  //ensure();

  // Exit:

  return;
}
