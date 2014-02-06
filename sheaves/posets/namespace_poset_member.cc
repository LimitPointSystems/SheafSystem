
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
/// Implementation for class namespace_poset_member.

#include "namespace_poset_member.h"

#include "assert_contract.h"
#include "namespace_poset.h"
#include "postorder_iterator.h"
#include "tern.h"

// ===========================================================
// NAMESPACE_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::namespace_poset_member::
namespace_poset_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

sheaf::namespace_poset_member::
namespace_poset_member(const namespace_poset_member& xother, bool xnew_jem)
{
  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<namespace_poset_member*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached());
}

sheaf::namespace_poset_member&
sheaf::namespace_poset_member::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

sheaf::namespace_poset_member&
sheaf::namespace_poset_member::
operator=(const namespace_poset_member& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

sheaf::namespace_poset_member::
~namespace_poset_member()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

sheaf::namespace_poset_member::
namespace_poset_member(namespace_poset* xhost,
                       const scoped_index* xexpansion,
                       int xexpansion_ct,
                       const tern& xnew_jem,
                       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_jrm_state(same args)));
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

sheaf::namespace_poset_member::
namespace_poset_member(const namespace_poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xhub_id));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() == xhub_id);
  ensure(is_attached());
}

sheaf::namespace_poset_member::
namespace_poset_member(const namespace_poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->contains_member(xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(index() ==~ xid);
  ensure(is_attached());
}

sheaf::namespace_poset_member::
namespace_poset_member(const namespace_poset* xhost, const std::string& xname)
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
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(is_attached());
}

sheaf::namespace_poset_member::
namespace_poset_member(const poset_state_handle& xmember_poset)
{
  // Preconditions:

  require(xmember_poset.is_attached() || xmember_poset.is_external());
  require(xmember_poset.name_space()->state_is_read_accessible());
  require(xmember_poset.name_space()->contains_member(xmember_poset.index()));

  // Body:

  attach_to_state(xmember_poset.name_space(), xmember_poset.index());

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(index() ==~ xmember_poset.index());
}

sheaf::poset_state_handle*
sheaf::namespace_poset_member::
poset_pointer() const
{
  poset_state_handle* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  result = dof_map().poset_pointer();

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_type
sheaf::namespace_poset_member::
poset_type_id() const
{
  poset_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  result = dof_map().poset_type_id();

  // Postconditions:

  // Exit

  return result;
}

const char*
sheaf::namespace_poset_member::
poset_class() const
{
  const char* result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  result = dof_map().poset_class();

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::namespace_poset_member::
poset_prereq_id(int xi) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());
  require((0 <= xi) && (xi < PREREQ_IDS_UB));

  // Body:

  pod_index_type result = dof_map().poset_prereq_id(xi);

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset_member::
poset_is_external() const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim());

  // Body:

  result = poset_pointer()->is_external();

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::namespace_poset_member::
namespace_poset_member(namespace_poset* xhost,
                       namespace_poset_dof_map* xdof_map,
                       bool xcopy_dof_map,
                       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_map, xcopy_dof_map, xauto_access);

  // Postconditions:

  ensure(invariant());
  ensure(postcondition_of(new_jim_state(same args)));

}

void
sheaf::namespace_poset_member::
put_poset_pointer(const poset_state_handle* xposet)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  /// @error the "pointer bug":
  /// If handle xposet is deleted, namespace is left with dangling reference
  /// need to either allocate a new handle or actually store pointer to poset state.

  dof_map().put_poset_pointer(xposet);

  // Postconditions:

  ensure(poset_pointer() == xposet);

  // Exit

  return;
}

void
sheaf::namespace_poset_member::
put_poset_type_id(poset_type xtype_id)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  dof_map().put_poset_type_id(xtype_id);

  // Postconditions:

  ensure(poset_type_id() == xtype_id);

  // Exit

  return;
}

void
sheaf::namespace_poset_member::
put_poset_class(const char* xclass)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  dof_map().put_poset_class(xclass);

  // Postconditions:

  ensure(poset_class() == xclass);

  // Exit

  return;
}

void
sheaf::namespace_poset_member::
put_poset_prereq_id(int xi, pod_index_type xid)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());
  require((0 <= xi) && (xi < PREREQ_IDS_UB));

  // Body:

  dof_map().put_poset_prereq_id(xi, xid);

  // Postconditions:

  ensure(poset_prereq_id(xi) == xid);

  // Exit:

  return;
}

void
sheaf::namespace_poset_member::
put_poset(const poset_state_handle& xposet)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  put_poset_pointer(&xposet);
  put_poset_type_id(xposet.type_id());
  put_poset_class(xposet.class_name());
  for(int i=0; i<PREREQ_IDS_UB; ++i)
  {
    put_poset_prereq_id(i, xposet.prereq_id(i));
  }

  // Postconditions:

  ensure(poset_pointer() == &xposet);
  ensure(poset_type_id() == xposet.type_id());
  ensure(poset_class() == xposet.class_name());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DEGREE OF FREEDOM (DOF) TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::namespace_poset_dof_map&
sheaf::namespace_poset_member::
dof_map(bool xrequire_write_access)
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // Invariant ensures dof maps are of type namespace_poset_dof_map.

  namespace_poset_dof_map& result =
    reinterpret_cast<namespace_poset_dof_map&>(total_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::namespace_poset_dof_map&
sheaf::namespace_poset_member::
dof_map(bool xrequire_write_access) const
{
  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // Invariant ensures dof maps are of type namespace_poset_dof_map.

  const namespace_poset_dof_map& result =
    reinterpret_cast<const namespace_poset_dof_map&>(total_poset_member::dof_map(xrequire_write_access));

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::namespace_poset_member::
dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const
{
  bool result;

  // Preconditions:

  require(xdof_map != 0);

  // Body:

  result = dynamic_cast<const namespace_poset_dof_map*>(xdof_map) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::namespace_poset*
sheaf::namespace_poset_member::
host() const
{
  namespace_poset* result;

  // Preconditions:

  // Body:

  result = dynamic_cast<namespace_poset*>(_host);

  // Postconditions:

  ensure( (_host != 0) == (result != 0) );

  // Exit

  return result;
}

bool
sheaf::namespace_poset_member::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = (dynamic_cast<const namespace_poset*>(xother) != 0);

  // Postconditions:

  ensure(result == (dynamic_cast<const namespace_poset*>(xother) != 0));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::namespace_poset_member::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const namespace_poset_member*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::namespace_poset_member*
sheaf::namespace_poset_member::
clone() const
{
  // Preconditions:

  // Body:

  // create new handle of the current class.

  namespace_poset_member *result = new namespace_poset_member();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

bool
sheaf::namespace_poset_member::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && total_poset_member::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    // Dof map is of type primitives_poset_dof_map
    result = result &&
             (is_attached() && is_jim() ?
              (dynamic_cast<const namespace_poset_dof_map*>(&total_poset_member::dof_map()) !=0) :
              true);

    /// @issue what are the invariants for this class
    /// @todo implement namespace_poset_member::invariant() const

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS FACET
// ===========================================================
 
