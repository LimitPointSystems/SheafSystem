
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
/// Implementation for class met_ed

#include "met_ed.h"

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
// CLASS MET_ED_LITE
//==============================================================================

//==============================================================================
// EUCLIDEAN METRIC (MET_ED) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_ed_lite::
met_ed_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_ed_lite::
met_ed_lite(const met_ed_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_ed_lite&
fiber_bundle::met_ed_lite::
operator=(const met_ed_lite& xother)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::met_ed_lite::
~met_ed_lite()
{

  // Preconditions:


  // Body:


  // Postconditions:

  // Exit:

}

fiber_bundle::met_ed_lite::
met_ed_lite(const row_dofs_type& xrow_dofs)
{
  // Preconditions:

  // Body:

  *this = xrow_dofs;

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::met_ed_lite&
fiber_bundle::met_ed_lite::
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
// METRIC TENSOR (MET) FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

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
fiber_bundle::met_ed_lite::
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
fiber_bundle::met_ed_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_ed_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_ed_lite*
fiber_bundle::met_ed_lite::
clone() const
{
  met_ed_lite* result = 0;

  // Preconditions:

  // Body:

  result = new met_ed_lite();

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
fiber_bundle::met_ed_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const met_ed_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::met_ed_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(met_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

//==============================================================================
// CLASS MET_ED
//==============================================================================

// ===========================================================
// HOST FACTORY FACET OF CLASS MET_ED
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::met_ed::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "met_ed_schema");

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::met_ed::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name()));
  require(!xns.contains_poset_member(standard_schema_path()));

  // Body:

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              met::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::met_ed::host_type&
fiber_bundle::met_ed::
new_host(namespace_type& xns, 
         const poset_path& xhost_path, 
         const poset_path& xschema_path, 
         const poset_path& xvector_space_path, 
         bool xauto_access)
{
  // cout << endl << "Entering met_ed::new_host." << endl;

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

  // cout << "Leaving met_ed::new_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// MET_ED FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::met_ed::
met_ed()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::met_ed::
met_ed(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::met_ed::
met_ed(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::met_ed::
met_ed(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::met_ed::
met_ed(abstract_poset_member* xother)
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

fiber_bundle::met_ed::
met_ed(poset_state_handle* xhost, bool xauto_access)
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
fiber_bundle::met_ed&
fiber_bundle::met_ed::
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
fiber_bundle::met_ed&
fiber_bundle::met_ed::
operator=(const met_ed& xother)
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

fiber_bundle::met_ed::
~met_ed()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

const fiber_bundle::met_ed::volatile_type&
fiber_bundle::met_ed::
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
fiber_bundle::met_ed::volatile_type*
fiber_bundle::met_ed::
lite_type() const
{
  // Preconditions:

  // Body:

  volatile_type* result = new volatile_type(sheaf::row_dofs(*this));

  // Postconditions:

  // Exit:

  return result;
}


//==============================================================================
// MET FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

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
fiber_bundle::met_ed::
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
fiber_bundle::met_ed::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("met_ed");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::met_ed*
fiber_bundle::met_ed::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class..

  met_ed *result = new met_ed();

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
fiber_bundle::met_ed::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // If xother may be dynamically cast to the type of this then this is an
  // ancestor of other.

  bool result = dynamic_cast<const met_ed*>(xother) != 0;

  // Postconditions:

  //  ensure(invariant());

  // Exit:

  return result;

}

bool
fiber_bundle::met_ed::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(met::invariant());

  if (invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Invariants for this class:

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

