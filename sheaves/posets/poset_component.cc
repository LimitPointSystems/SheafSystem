
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
/// Implementation for class poset_component

#include "SheafSystem/poset_component.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/poset.h"
#include "SheafSystem/poset_state.h"
#include "SheafSystem/poset_crg_state.h"
#include "SheafSystem/pool.h"
#include "SheafSystem/std_typeinfo.h"

using namespace std;

// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_component::
~poset_component()
{
  // Preconditions:

  // Body:

  // Nothing todo.

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::poset_component::
poset_component()
{
  // Preconditions:

  // Body:

  _host = 0;

  _index.invalidate();

  _version = NOT_A_STANDARD_VERSION_INDEX;

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());

  // Exit:

  return;
}

sheaf::poset_state*
sheaf::poset_component::
state_obj() const
{
  poset_state* result;

  // Precondition:

  // Body:

  result = _host != 0 ? _host->state_obj() : 0;

  // Note: poset_state_handle::invariant ensures _state != 0

  // Postcondition:

  ensure(_host == 0 ? result == 0 : true);

  // Exit:

  return result;
} 

sheaf::poset_powerset_state*
sheaf::poset_component::
powerset() const
{
  return state_obj()->powerset();
}

sheaf::poset_crg_state*
sheaf::poset_component::
crg() const
{
  return state_obj()->crg();
}

sheaf::subposet_state*
sheaf::poset_component::
powerset_member(const scoped_index& xindex) const
{
  subposet_state* result;

  /// @todo should be inlined

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = &(_host->powerset().member(xindex));

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

sheaf::poset_dof_map*
sheaf::poset_component::
row_dof_tuple(const scoped_index& xindex) const
{
  poset_dof_map* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = state_obj()->table()->row_dof_tuple(xindex);

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_component::
init_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Have just attached to a new or different host.
  // Initialize the handle data members for the different host.

  // Nothing to do in this class; intended for redefintion in descendants.

  // Postconditions:

  ensure(unexecutable(data members created but not attached));

  // Exit

  return;
}

void
sheaf::poset_component::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(unexecutable(data members created));

  // Body:

  // Have just attached to a new or different member in the same host.
  // Attach the handle data members for the different member.

  // Nothing to do in this class; intended for redefintion in descendants.

  // Postconditions:

  ensure(unexecutable(data members attached()));

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT INDEX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::scoped_index&
sheaf::poset_component::
index() const
{
  // Preconditions:

  // Body:

  define_old_variable(const scoped_index& result = _index);

  // Postconditions:

  ensure(result.is_hub_scope() || !result.is_valid());
  ensure(result.is_positive() || !result.is_valid());

  // Exit

  return _index;
}

bool
sheaf::poset_component::
is_valid_index(const poset_state_handle* xhost, pod_index_type xhub_id, int xversion) const
{
  bool result = false;

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(host_is_ancestor_of(xhost));

  // Body:

  is_abstract();

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
is_valid_index(const poset_state_handle* xhost, const scoped_index& xid, int xversion) const
{
  bool result = false;

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(host_is_ancestor_of(xhost));

  // Body:

  return is_valid_index(xhost, xid.hub_pod(), xversion);
}

const sheaf::hub_index_space_handle&
sheaf::poset_component::
hub_id_space() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  static const hub_index_space_handle* result;

  is_abstract();

  // Postconditions:

  // Exit:

  return *result;
}

const sheaf::scoped_index&
sheaf::poset_component::
hub_id() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  static const scoped_index result;

  is_abstract();

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return result;
}

sheaf::scoped_index
sheaf::poset_component::
hub_id(pod_index_type xid) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  static scoped_index result;

  is_abstract();

  // Postconditions:

  ensure(result.is_hub_scope());
  ensure(result.pod() == xid);

  // Exit:

  return result;
}

sheaf::pod_index_type
sheaf::poset_component::
get_index_from_name(const poset_state_handle* xhost, const std::string& xname) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  pod_index_type result = 0; // Just to silence the compiler.

  is_abstract();

  // Postconditions:

  // Exit

  return result;
}

void
sheaf::poset_component::
get_index_from_name(const poset_state_handle* xhost, const std::string& xname,
		    scoped_index& result) const
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  is_abstract();

  // Postconditions:

  // Exit

  return;
}

int
sheaf::poset_component::
version(bool xunalias) const
{
  int result;

  // Preconditions:

  require(xunalias ? state_is_read_accessible() : true);

  // Body:

  result = xunalias ? unaliased_version(_version) : _version;

  // Postconditions:

  ensure(result != CURRENT_MEMBER_VERSION);
  ensure(xunalias ? (result != CURRENT_HOST_VERSION) : true);

  // Exit

  return result;
}

void
sheaf::poset_component::
put_version(int xversion, bool xunalias)
{
  // Preconditions:

  require(xunalias ? state_is_read_accessible() : true);
  require(has_version(xversion));
  require(!xunalias ? xversion != CURRENT_MEMBER_VERSION : true);

  // Body:

  _version = xunalias ? unaliased_version(xversion) : xversion;

  // Postconditions:

  ensure(xunalias ?
         version(false) == unaliased_version(xversion) :
         version(false) == xversion);

  // Exit

  return;
}

int
sheaf::poset_component::
unaliased_version(int xversion) const
{
  int result;

  // Preconditions:

  // Body:

  if(xversion == CURRENT_HOST_VERSION)
  {
    result = host()->version();
  }
  else if(xversion == CURRENT_MEMBER_VERSION)
  {
    result = _version;
    if(result == CURRENT_HOST_VERSION)
    {
      result = host()->version();
    }
  }
  else
  {
    result = xversion;
  }

  // Postconditions:


  ensure(result != CURRENT_HOST_VERSION);
  ensure(result != CURRENT_MEMBER_VERSION);

  // Exit

  return result;
}

sheaf::pod_index_type
sheaf::poset_component::
version_index() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  pod_index_type result = host()->version_index(version(true));

  // Postconditions:

  ensure(host()->includes_subposet(result));

  // Exit

  return result;
}

void
sheaf::poset_component::
version_index(scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  host()->version_index(version(true), result);

  // Postconditions:

  ensure(host()->includes_subposet(result));

  // Exit

  return;
}

std::string
sheaf::poset_component::
version_name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = host()->version_to_name(version(true));

  // Postconditions:

  ensure(host()->includes_subposet(result));

  // Exit

  return result;
}

bool
sheaf::poset_component::
has_version(int xversion) const
{
  bool result;

  // Preconditions:

  // Body:

  result = ((xversion == CURRENT_MEMBER_VERSION) ||
            (xversion == CURRENT_HOST_VERSION) ||
            host()->has_version(xversion));

  // Postconditions:

  ensure( result == ( (xversion == CURRENT_MEMBER_VERSION) ||
                      (xversion == CURRENT_HOST_VERSION) ||
                      host()->has_version(xversion)));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COMPONENT NAME FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

std::string
sheaf::poset_component::
name() const
{
  string result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Postconditions:

  ensure(unexecutable(result.empty() implies this has no name));

  // Exit:

  return name(false);
}

std::string
sheaf::poset_component::
name(bool xauto_access) const
{
  string result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(unexecutable(result.empty() implies this has no name));

  // Exit:

  return result;
}

void
sheaf::poset_component::
all_names(block<std::string>& xresult, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(xresult.ct() == name_ct(xauto_access));
  ensure_for_all(i, 0, xresult.ct(), !xresult[i].empty());

  // Exit:

  return;
}

sheaf::size_type
sheaf::poset_component::
name_ct(bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  size_type result = 0;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::poset_component::
has_name(const std::string& xname, bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(!xname.empty());

  // Body:

  bool result = false;

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

void
sheaf::poset_component::
put_name(const std::string& xname, bool xunique, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(xunique ? (name(xauto_access) == xname) : has_name(xname, xauto_access));

  // Exit

  return;
}

void
sheaf::poset_component::
delete_name(const std::string& xname, bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(!xname.empty());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!has_name(xname, xauto_access));

  // Exit:

  return;
}

void
sheaf::poset_component::
delete_all_names(bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(name_ct(xauto_access) == 0);

  // Exit:

  return;
}

bool
sheaf::poset_component::
is_valid_name(const poset_state_handle* xhost, const std::string& xname) const
{
  bool result;

  // Preconditions:

  require(xhost != 0);
  require(xhost->state_is_read_accessible());
  require(!xname.empty());

  // Body:

  result = is_valid(get_index_from_name(xhost, xname));

  // Postconditions:

  ensure(unexecutable(xhost has a component of the same type as this with name xname));

  // Exit

  return result;
}

sheaf::poset_path
sheaf::poset_component::
path(bool xauto_access) const
{

  // Preconditions:

  require(is_attached());
  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  require(!name().empty());

  // Body:

  poset_path result(host()->name(), name());

  // Postconditions:

  ensure(result.poset_name() == host()->name());
  ensure(result.member_name() == name());

  if(xauto_access)
  {
    release_access();
  }

  // Exit:

  return result;
}

bool
sheaf::poset_component::
has_path(const poset_path& xpath, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result =
    (host()->name() == xpath.poset_name())
    && has_name(xpath.member_name(), xauto_access);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HOST POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_state_handle*
sheaf::poset_component::
host() const
{
  poset_state_handle* result;

  // Preconditions:

  // Body:

  result = _host;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  // Given the signature, the following is always true:
  // result = dynamic_cast<const poset_state_handle*>(xother) != 0;

  result = true;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
has_same_host(const poset_component* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  if(xother == 0)
  {
    result = false;
  }
  else if(is_attached())
  {
    result = xother->is_attached() && (xother->host()->is_same_state(host()));
  }
  else
  {
    result = !xother->is_attached();
  }

  /// @error below is not true if both are unattached, in fact, it segfaults

  // Postconditions:

  // ensure(result == ((xother != 0) && (xother->host()->is_same_state(host()))));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NAMESPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::namespace_poset*
sheaf::poset_component::
name_space() const
{
  namespace_poset* result;

  // Preconditions:

  // Body:

  result = host()->name_space();

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
namespace_is_ancestor_of(const namespace_poset* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  // Given the signature, the following is always true:
  // result = dynamic_cast<namespace_poset*>(xother) != 0;
  // Intended to be redefined in descendants.

  result = true;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
same_namespace(const poset_component* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  if(is_attached() && xother->is_attached())
  {
    // both attached, so true if in same namespace
    result = host()->host()->is_same_state(xother->host()->host());
  }
  else
  {
    // not both attached, so true if both unattached
    result = (!is_attached()) && (!xother->is_attached());
  }

  // Postconditions:

  ensure(unexecutable(true if hosts of this and xother are in same namespace or if this and xother both unattached));

  // Exit

  return result;
}

bool
sheaf::poset_component::
same_namespace(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  if(is_attached() && xother->is_attached())
  {
    // both attached, so true if in same namespace
    result = host()->host()->is_same_state(xother->host());
  }
  else
  {
    // not both attached, so true if both unattached
    result = (!is_attached()) && (!xother->is_attached());
  }

  // Postconditions:

  ensure(unexecutable("true if hosts of this and xother are in same namespace or if this and xother both unattached"));

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_component::
attach_to_state(const poset_state_handle* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(is_valid_index(xhost, xhub_id));

  /// @issue poset_component::attach_to_state()
  /// only precondition requires read_access

  /// @error attaching to state via host leaves member handle with
  ///  dangling ref when host handle deleted

  // Body:

  // Attach to the new or different host.

  _host  = const_cast<poset_state_handle*>(xhost);
  _index = hub_id();

  // The following does not work because the standard members
  // must be attached before the poset is attached to the namespace.

  // Use the host pointer held by the namespace to avoid
  // holding a dangling reference if xhost deleted.

  // _host = xhost->name_space()->member_poset(xhost->index());


  // Initialize the handle data members, if any;
  // does not attach them.

  init_handle_data_members();

  // Initialize the version to the current version of the host.

  _version = CURRENT_HOST_VERSION;

  // Attach to the new or different member;
  // attaches the handle data members, if any.

  attach_to_state(xhub_id);

  // Postconditions:

  ensure(is_attached());
  ensure(host()->is_same_state(xhost));
  ensure(index().is_hub_scope());
  ensure(index() == xhub_id);
  ensure(version() == xhost->version());
  ensure(postcondition_of(attach_handle_data_members()));

  // Exit:

  return;
}

void
sheaf::poset_component::
attach_to_state(const poset_state_handle* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(is_valid_index(xhost, xid));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(is_attached());
  ensure(host()->is_same_state(xhost));
  ensure(index().is_hub_scope());
  ensure(index() ==~ xid);
  ensure(version() == xhost->version());
  ensure(postcondition_of(attach_handle_data_members()));

  // Exit:

  return;
}

void
sheaf::poset_component::
attach_to_state(const poset_state_handle* xhost, const std::string& xname)
{
  // Preconditions:

  require(xhost != 0);
  require(host_is_ancestor_of(xhost));
  require(xhost->state_is_read_accessible());
  require(is_valid_name(xhost, xname));

  // Body:

  pod_index_type lindex = get_index_from_name(xhost, xname);

  attach_to_state(xhost, lindex);

  // Postconditions:

  ensure(is_attached());
  ensure(host() == xhost);
  ensure(has_name(xname));
  ensure(postcondition_of(attach_handle_data_members()));
}

void
sheaf::poset_component::
attach_to_state(const std::string& xname)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(!xname.empty());
  require(is_valid_name(host(), xname));
  require(precondition_of(attach_to_state(get_index_from_name(host(), xname))));

  // Body:

  attach_to_state(get_index_from_name(host(), xname));

  // Postconditions:

  ensure(postcondition_of(attach_to_state(get_index_from_name(host(), xname))));

  // Exit:

  return;
}

void
sheaf::poset_component::
attach_to_state(pod_index_type xhub_id)
{
  // preconditions:

  require(state_is_read_accessible());
  require(is_valid_index(host(), xhub_id, version(false)));

  // Body:

  define_old_variable(poset_state_handle* old_host = _host);
  define_old_variable(int old_version = _version);

  // Attach to the new or different member;

  _index = xhub_id;

  // Leave version unchanged.

  // Attach the data members, if any, to the new or different member.

  attach_handle_data_members();

  // postconditions:

  ensure(is_attached());
  ensure(host() == old_host);
  ensure(index().is_hub_scope());
  ensure(index() == xhub_id);
  ensure(version(false) == old_version);
  ensure(postcondition_of(attach_handle_data_members()));
}

void
sheaf::poset_component::
attach_to_state(const scoped_index& xid)
{
  // preconditions:

  require(state_is_read_accessible());
  require(is_valid_index(host(), xid, version(false)));

  // Body:

  define_old_variable(poset_state_handle* old_host = _host);
  define_old_variable(int old_version = _version);

  attach_to_state(xid.hub_pod());

  // postconditions:

  ensure(is_attached());
  ensure(host() == old_host);
  ensure(index().is_hub_scope());
  ensure(index() ==~ xid);
  ensure(version(false) == old_version);
  ensure(postcondition_of(attach_handle_data_members()));
}

void
sheaf::poset_component::
attach_to_state(const poset_component* xother)
{
  // Preconditions:

  require(xother != 0);

  /// @issue need some way to enforce attachment to valid handles, in particular
  /// to enforce members to members and subposets to subposets, but the
  /// following is too strict. Won;t let schema_poset_members attach to
  /// abstract_poset_member.

  // require(is_ancestor_of(xother));
  require(xother->is_attached() ? xother->state_is_read_accessible() : true);

  // Body:

  if(is_attached())
  {
    if(xother->is_attached())
    {
      // Both this and other are already attached.

      if(!_host->is_same_state(xother->host()))
      {
        // We're attaching to a different host;
        // have to initialize the handle data members.

        _host = xother->host();
        init_handle_data_members();
      }

      _index = xother->index();

      // Want version data members to be identical,
      // without binding to current version number
      // See poset_component::version()

      _version = xother->_version;
      attach_handle_data_members();
    }
    else
    {
      // This is attached, but not other;
      // detach this.

      detach_from_state();
    }
  }
  else
  {
    // This is not already attached;

    if(xother->is_attached())
    {
      _host = xother->host();
      _index = xother->index();

      // Want version data members to be identical,
      // without binding to current version number.
      // See poset_component::version()

      _version = xother->_version;
      init_handle_data_members();
      attach_handle_data_members();
    }
  }

  // Postconditions:

  ensure(is_same_state(xother));
  //  ensure(is_attached() ? version() == xother->version(): true);
  ensure(version(false) == xother->version(false));
  //   ensure(!is_restricted()); // True in abstract_poset_member but not defined here.

  // Exit:

  return;
}

void
sheaf::poset_component::
attach_to_state(const poset_component* xother, bool xauto_access)
{

  // Preconditions:

  require(xother != 0);
  require(xother->is_attached() ?
          (xauto_access || xother->state_is_read_accessible()) :
          true);

  // Body:

  if(xauto_access && xother->is_attached())
  {
    xother->get_read_access();
  }

  attach_to_state(xother);

  if(xauto_access && xother->is_attached())
  {
    xother->release_access();
  }

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xother)));

  // Exit:

  return;
}

void
sheaf::poset_component::
detach_from_state()
{

  // Preconditions:

  // Body:

  _host = 0;

  _index.invalidate();

  _version = NOT_A_STANDARD_VERSION_INDEX;

  // Postconditions:

  // Both detach_from_state and invariant may be redefined in
  // descendants.  We can only be responsible for maintaining
  // poset_component's invariant.

  ensure(poset_component::invariant());
  ensure(!is_attached());
}


bool
sheaf::poset_component::
is_attached() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_host != 0) && (_index.is_positive());

  // Postconditions:

  ensure(result == ((host() != 0) && (index().is_positive())));

  // Exit

  return result;
}

bool
sheaf::poset_component::
is_same_state(const poset_state_handle* xhost, pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(xhost != 0 ? host_is_ancestor_of(xhost) : true);

  // Body:

  // "is_same_state" is state equality - a.is_same_state(b) if both a and b
  // refer to the same poset member state.If both are attached, they must have
  // the same poset state and same index. If neither are attached,
  // they are both considered to be attached to the (unique) void object,
  // and hence must have the same host and index.
  // If one is attached and the other not, they will have different
  // host and index.

  result = ( (xhost != 0) && (xhost->state_obj() == state_obj()) && (index() == xhub_id) );

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
is_same_state(const poset_state_handle* xhost, const scoped_index& xid) const
{
  bool result;

  // Preconditions:

  require(xhost != 0 ? host_is_ancestor_of(xhost) : true);

  // Body:

  return is_same_state(xhost, xid.hub_pod());
}

bool
sheaf::poset_component::
is_same_state(const poset_component* xother) const
{
  bool result = true;

  // Preconditions:

  // Body:

  // "is_same_state" is state equality - a.is_same_state(b) if both a and b
  // refer to the same component state. If both are attached, they must have
  // the same poset state and same index. If neither are attached,
  // they are both considered to be attached to the (unique) void object,
  // and hence must have the same host and index.
  // If one is attached and the other not, they will have different
  // host and index. Both must be the same type of component.

  result = result && (xother != 0);
  result = result && (xother->state_obj() == state_obj());
  result = result && (xother->index() == index());

  /// @issue how do we enforce the "same kind of component" condition?
  /// The following is too stringent, it won't allow descendants of
  /// abstract_poset_member to interoperate:
  /// result = result && is_ancestor_of(xother);

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE ACCESS CONTROL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::poset_component::
get_read_access() const
{
  // Preconditions:
  
  require(is_attached());

  // Body:

  int old_access_request_depth = host()->access_request_depth();

  host()->get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
}

void
sheaf::poset_component::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);


  // Body:

  int old_access_request_depth = host()->access_request_depth();

  host()->get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
}

void
sheaf::poset_component::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = host()->access_request_depth();

  host()->release_access(xall);

  // Postconditions:

  ensure(xall ?
         access_request_depth() == 0 :
         access_request_depth() == old_access_request_depth - 1);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::poset_component::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_component*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::poset_component::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && read_write_monitor_handle::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    result = result && ((_host == 0) ? (!_index.is_valid()) : (_index.is_hub_scope()));

    result = result && (_version != CURRENT_MEMBER_VERSION);

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
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
sheaf::deep_size(const poset_component& xp, bool xinclude_shallow)

{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
