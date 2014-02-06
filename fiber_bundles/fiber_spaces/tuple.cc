
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
/// Implementation for class tuple.

#include "tuple.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "schema_poset_member.h"
#include "wsv_block.h"

#include "fiber_bundles_namespace.h"
#include "tuple_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// CLASS TUPLE_LITE
//==============================================================================

//==============================================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
//==============================================================================

fiber_bundle::tuple_lite::
tuple_lite()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tuple_lite::
tuple_lite(const tuple_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:
}

fiber_bundle::tuple_lite&
fiber_bundle::tuple_lite::
operator=(const tuple_lite& xother)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fiber_bundle::tuple_lite::
~tuple_lite()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

const std::string&
fiber_bundle::tuple_lite::
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
fiber_bundle::tuple_lite::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("tuple_lite");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::tuple_lite::table_dofs_type
fiber_bundle::tuple_lite::
table_dofs() const
{
  // Preconditions:

  // Body:

  // The order here is factor_ct, d, u, v, dd, p.

  int lfactor_ct = factor_ct();
  table_dofs_type result = {lfactor_ct};

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::tuple_lite::
is_ancestor_of(const any_lite& xother) const
{
  // Preconditions:

  require(&xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const tuple_lite*>(&xother) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::tuple_lite*
fiber_bundle::tuple_lite::
clone() const
{
  tuple_lite* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(*result));

  // Exit:

  return result;
}

bool
fiber_bundle::tuple_lite::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(any_lite::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


//==============================================================================
// CLASS TUPLE
//==============================================================================

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
fiber_bundle::tuple::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string result("fiber_space_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::tuple::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path result(standard_schema_poset_name(), "tuple_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::tuple::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false).state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string lmember_names = "factor_ct INT true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_poset_name(), "bottom"),
                              lmember_names,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit:

  return;
}

fiber_bundle::tuple::host_type&
fiber_bundle::tuple::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, int xfactor_ct, bool xauto_access)
{
  // cout << endl << "Entering tuple::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path()));

  require(xfactor_ct > 0);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xfactor_ct, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == xfactor_ct);

  // Exit:

  // cout << "Leaving tuple::new_host." << endl;
  return result;
}


// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

// ===========================================================
// CARTESIAN ALGEBRA (TUPLE) FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS
 
fiber_bundle::tuple::
tuple()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}

fiber_bundle::tuple::
tuple(const poset_state_handle* xhost, pod_index_type xhub_id)
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

fiber_bundle::tuple::
tuple(const poset_state_handle* xhost, const scoped_index& xid)
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

fiber_bundle::tuple::
tuple(const poset_state_handle* xhost, const std::string& xname)
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

fiber_bundle::tuple::
tuple(const abstract_poset_member* xother)
{

  // Preconditions:

  require(xother != 0);
  require(xother->is_attached() ? xother->state_is_read_accessible() : true);
  require(abstract_poset_member::is_ancestor_of(xother));

  // Body:

  attach_to_state(xother);

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(is_same_state(xother));

  // Exit:
}

fiber_bundle::tuple::
tuple(poset_state_handle* xhost, bool xauto_access)
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

fiber_bundle::tuple&
fiber_bundle::tuple::
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

fiber_bundle::tuple&
fiber_bundle::tuple::
operator=(const tuple& xother)
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

fiber_bundle::tuple::
~tuple()
{

  // Preconditions:

  // Body:

  // Postconditions:

}

int
fiber_bundle::tuple::
factor_ct() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = host()->factor_ct();

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::tuple::
factor_ct(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  int result = host()->factor_ct();
  
  // Postconditions:

  // Exit:

  return result;
}

sheaf::array_poset_dof_map&
fiber_bundle::tuple::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  array_poset_dof_map& result =
    reinterpret_cast<array_poset_dof_map&>(abstract_poset_member::dof_map());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::array_poset_dof_map&
fiber_bundle::tuple::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  const array_poset_dof_map& result =
    reinterpret_cast<const array_poset_dof_map&>(abstract_poset_member::dof_map());

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::tuple::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  // This handle requires xdof_map to be of type array_poset_dof_map.

  result = dynamic_cast<const array_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

//==============================================================================
// ABSTRACT POSET MEMBER FACET
//==============================================================================

const std::string&
fiber_bundle::tuple::
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
fiber_bundle::tuple::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("tuple");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

fiber_bundle::tuple*
fiber_bundle::tuple::
clone() const
{

  // Preconditions:

  // Body:

  // Create new handle of the current class.

  tuple *result = new tuple();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

// ===========================================================
// POSET_COMPONENT FACET
// =========================================================== 

fiber_bundle::tuple::host_type*
fiber_bundle::tuple::
host() const
{
  return reinterpret_cast<host_type*>(_host);
}

bool
fiber_bundle::tuple::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  return dynamic_cast<const host_type*>(xother) != 0;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::tuple::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  // If other may be dynamically cast to the type of this then this is an
  // ancestor of xother.

  bool result = dynamic_cast<const tuple*>(xother) != 0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

bool
fiber_bundle::tuple::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  invariance(total_poset_member::invariant());

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

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

