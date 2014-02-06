

//
// Copyright (c) 2014 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Implementation for class met.

#include "met.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "stp_space.h"
#include "fiber_bundles_namespace.h"
#include "schema_poset_member.h"
#include "wsv_block.h"


using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.


//==============================================================================
// CLASS MET_LITE
//==============================================================================

//==============================================================================
// METRIC TENSOR (MET) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_lite::
met_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_lite::
met_lite(const met_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_lite&
fiber_bundle::met_lite::
operator=(const met_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::met_lite::
~met_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

fiber_bundle::met_lite::
met_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_lite&
fiber_bundle::met_lite::
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// INTERIOR ALGEBRA (STP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TENSOR ALGEBRA (TP) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VECTOR ALGEBRA (VD) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::met_lite::
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
fiber_bundle::met_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_lite*
fiber_bundle::met_lite::
clone() const
{
  met_lite* result = 0;

  // Preconditions:

  // Body:

  result = new met_lite();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const met_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::met_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(st2_lite::invariant());

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
// CLASS MET
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS MET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::met::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "met_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::met::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              st2::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::met::host_type&
fiber_bundle::met::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering met::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xns.path_is_auto_read_accessible(xvector_space_path, xauto_access));
  require(xns.contains_poset<scalar_type::host_type>(xvector_space_path, xauto_access));

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 2, xvector_space_path, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.d(true));
  ensure(result.d(true) == schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access));
  ensure(result.vector_space_path(true) == xvector_space_path );
  ensure(result.p(true) == 2);
  ensure(result.dd(true) == result.d(true));
  ensure(result.vector_space_path(true) == xhost_path );

  // Exit:

  // cout << "Leaving met::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met::
met()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::met::
met(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::met::
met(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::met::
met(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::met::
met(abstract_poset_member* xother)
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

fiber_bundle::met::
met(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::met&
fiber_bundle::met::
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
fiber_bundle::met&
fiber_bundle::met::
operator=(const met& xother)
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

fiber_bundle::met::
~met()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::met::volatile_type&
fiber_bundle::met::
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
fiber_bundle::met::volatile_type*
fiber_bundle::met::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ST2 FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// STP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TP FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// VD FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// TUPLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::met::
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
fiber_bundle::met::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met*
fiber_bundle::met::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  met* result = new met();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::met::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const met*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::met::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(st2::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

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


//==============================================================================
// MET FACET
//==============================================================================

#include "error_message.h"
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "met_e1.h"
#include "met_e2.h"
#include "met_e3.h"

///
void
fiber_bundle::met_algebra::
raise(const met& xmetric, const ed& xcovector, ed& xresult,
	  bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xcovector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xcovector.d(xauto_access) == xmetric.dd(xauto_access));
  require(xresult.d(xauto_access) == xmetric.dd(xauto_access));
  require(xmetric.is_contravariant(0, xauto_access));
  require(xcovector.is_covariant(0, xauto_access));   //  is_dual;

  // Body:

  const met_e1* met_e1_xmetric = dynamic_cast<const met_e1*>(&xmetric);
  const met_e2* met_e2_xmetric = dynamic_cast<const met_e2*>(&xmetric);
  const met_e3* met_e3_xmetric = dynamic_cast<const met_e3*>(&xmetric);

  const e1* e1_xcovector = dynamic_cast<const e1*>(&xcovector);
  const e2* e2_xcovector = dynamic_cast<const e2*>(&xcovector);
  const e3* e3_xcovector = dynamic_cast<const e3*>(&xcovector);

  e1* e1_xresult = dynamic_cast<e1*>(&xresult);
  e2* e2_xresult = dynamic_cast<e2*>(&xresult);
  e3* e3_xresult = dynamic_cast<e3*>(&xresult);

  if(met_e1_xmetric &&  e1_xcovector && e1_xresult)
  {
    raise(*met_e1_xmetric, *e1_xcovector, *e1_xresult, xauto_access);
  }
  else if(met_e2_xmetric &&  e2_xcovector && e2_xresult, xauto_access)
  {
    raise(*met_e2_xmetric, *e2_xcovector, *e2_xresult, xauto_access);
  }
  else if(met_e3_xmetric &&  e3_xcovector && e3_xresult, xauto_access)
  {
    raise(*met_e3_xmetric, *e3_xcovector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to raise(...)");
  }

  // Postconditions:

  ensure(xresult.is_contravariant(0, xauto_access)); // !is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::met_algebra::
lower(const met& xmetric, const ed& xvector, ed& xresult, bool xauto_access)
{
  // Preconditions:

  require(xmetric.state_is_auto_read_accessible(xauto_access));
  require(xvector.state_is_auto_read_accessible(xauto_access));
  require(xresult.state_is_auto_read_write_accessible(xauto_access));
  require(xvector.d(xauto_access) == xmetric.dd(xauto_access));
  require(xresult.d(xauto_access) == xmetric.dd(xauto_access));
  require(xmetric.is_covariant(0, xauto_access));
  require(xvector.is_contravariant(0, xauto_access)); // !is_dual;

  // Body:

  const met_e1* met_e1_xmetric = dynamic_cast<const met_e1*>(&xmetric);
  const met_e2* met_e2_xmetric = dynamic_cast<const met_e2*>(&xmetric);
  const met_e3* met_e3_xmetric = dynamic_cast<const met_e3*>(&xmetric);

  const e1* e1_xvector = dynamic_cast<const e1*>(&xvector);
  const e2* e2_xvector = dynamic_cast<const e2*>(&xvector);
  const e3* e3_xvector = dynamic_cast<const e3*>(&xvector);

  e1* e1_xresult = dynamic_cast<e1*>(&xresult);
  e2* e2_xresult = dynamic_cast<e2*>(&xresult);
  e3* e3_xresult = dynamic_cast<e3*>(&xresult);

  if(met_e1_xmetric &&  e1_xvector && e1_xresult)
  {
    lower(*met_e1_xmetric, *e1_xvector, *e1_xresult, xauto_access);
  }
  else if(met_e2_xmetric &&  e2_xvector && e2_xresult, xauto_access)
  {
    lower(*met_e2_xmetric, *e2_xvector, *e2_xresult, xauto_access);
  }
  else if(met_e3_xmetric &&  e3_xvector && e3_xresult, xauto_access)
  {
    lower(*met_e3_xmetric, *e3_xvector, *e3_xresult, xauto_access);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to lower(...)");
  }

  // Postconditions:

  ensure(xresult.is_covariant(0, xauto_access));     //  is_dual

  // Exit:

  return;
}

///
void
fiber_bundle::met_algebra::
raise(const met_lite& xmetric, const ed_lite& xcovector, ed_lite& xresult)
{
  // Preconditions:

  require(xcovector.d() == xmetric.dd());
  require(xresult.d() == xmetric.dd());
  require(unexecutable("xmetric.is_contravariant())"));
  require(unexecutable("xcovector.is_covariant())"));   //  is_dual;

  // Body:

// met_e1.h: raise(const met_e1_lite& xmetric, const e1_lite& xcovector,
// met_e2.h: raise(const met_e2_lite& xmetric, const e2_lite& xcovector,
// met_e3.h: raise(const met_e3_lite& xmetric, const e3_lite& xcovector,

  const met_e1_lite* met_e1_xmetric = dynamic_cast<const met_e1_lite*>(&xmetric);
  const met_e2_lite* met_e2_xmetric = dynamic_cast<const met_e2_lite*>(&xmetric);
  const met_e3_lite* met_e3_xmetric = dynamic_cast<const met_e3_lite*>(&xmetric);

  const e1_lite* e1_xcovector = dynamic_cast<const e1_lite*>(&xcovector);
  const e2_lite* e2_xcovector = dynamic_cast<const e2_lite*>(&xcovector);
  const e3_lite* e3_xcovector = dynamic_cast<const e3_lite*>(&xcovector);

  e1_lite* e1_xresult = dynamic_cast<e1_lite*>(&xresult);
  e2_lite* e2_xresult = dynamic_cast<e2_lite*>(&xresult);
  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);

  if(met_e1_xmetric &&  e1_xcovector && e1_xresult)
  {
    raise(*met_e1_xmetric, *e1_xcovector, *e1_xresult);
  }
  else if(met_e2_xmetric &&  e2_xcovector && e2_xresult)
  {
    raise(*met_e2_xmetric, *e2_xcovector, *e2_xresult);
  }
  else if(met_e3_xmetric &&  e3_xcovector && e3_xresult)
  {
    raise(*met_e3_xmetric, *e3_xcovector, *e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to raise(...)");
  } 

  // Postconditions:

  ensure(unexecutable("xresult.is_contravariant())")); // !is_dual

  // Exit:

  return;
}

///
fiber_bundle::ed_lite*
fiber_bundle::met_algebra::
raise(const met_lite& xmetric, const ed_lite& xcovector)
{
  // Preconditions:

  require(precondition_of(raise(xmetric, xcovector, *result)));

  // Body:

  ed_lite* result = new ed_lite();
  raise(xmetric, xcovector, *result);

  // Postconditions:

  ensure(postcondition_of(raise(xmetric, xcovector, *result)));

  // Exit:

  return result;
}

///
void
fiber_bundle::met_algebra::
lower(const met_lite& xmetric, const ed_lite& xvector, ed_lite& xresult)
{
  // Preconditions:

  require(xvector.d() == xmetric.dd());
  require(xresult.d() == xmetric.dd());
  require(unexecutable("xmetric.is_covariant())"));
  require(unexecutable("xcovector.is_contravariant())")); // !is_dual

  // Body:

  const met_e1_lite* met_e1_xmetric = dynamic_cast<const met_e1_lite*>(&xmetric);
  const met_e2_lite* met_e2_xmetric = dynamic_cast<const met_e2_lite*>(&xmetric);
  const met_e3_lite* met_e3_xmetric = dynamic_cast<const met_e3_lite*>(&xmetric);

  const e1_lite* e1_xvector = dynamic_cast<const e1_lite*>(&xvector);
  const e2_lite* e2_xvector = dynamic_cast<const e2_lite*>(&xvector);
  const e3_lite* e3_xvector = dynamic_cast<const e3_lite*>(&xvector);

  e1_lite* e1_xresult = dynamic_cast<e1_lite*>(&xresult);
  e2_lite* e2_xresult = dynamic_cast<e2_lite*>(&xresult);
  e3_lite* e3_xresult = dynamic_cast<e3_lite*>(&xresult);

  if(met_e1_xmetric &&  e1_xvector && e1_xresult)
  {
    lower(*met_e1_xmetric, *e1_xvector, *e1_xresult);
  }
  else if(met_e2_xmetric &&  e2_xvector && e2_xresult)
  {
    lower(*met_e2_xmetric, *e2_xvector, *e2_xresult);
  }
  else if(met_e3_xmetric &&  e3_xvector && e3_xresult)
  {
    lower(*met_e3_xmetric, *e3_xvector, *e3_xresult);
  }
  else
  {
    post_fatal_error_message(\
      "Unsupported argument types in call to lower(...)");
  } 

  // Postconditions:

  ensure(unexecutable("xresult.is_covariant())"));       // is_dual

  // Exit:

  return;
}

///
fiber_bundle::ed_lite*
fiber_bundle::met_algebra::
lower(const met_lite& xmetric, const ed_lite& xvector)
{
  // Preconditions:

  require(precondition_of(lower(xmetric, xvector, *result)));

  // Body:

  ed_lite* result = new ed_lite();
  lower(xmetric, xvector, *result);

  // Postconditions:

  ensure(postcondition_of(lower(xmetric, xvector, *result)));

  // Exit:

  return result;
}


