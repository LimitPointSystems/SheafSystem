

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

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
/// Implementation for class subposet_state

#include "subposet_state.h"
#include "assert_contract.h"
#include "zn_to_bool.h"

// ===========================================================
// SUBPOSET_STATE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::subposet_state::
subposet_state()
{
  // Preconditions:

  // Body:

  _members = 0;
  _index.invalidate();
  _is_dof_subposet = false;
  _dof_ct = 0;
  _dof_descriptors = 0;
  _id_space = 0;
  _is_persistent = true;

  // Postconditions:

  ensure(!has_id_space());
  ensure(is_persistent());
  ensure(is_terminated());
}

sheaf::subposet_state::
~subposet_state()
{
  // Preconditions:

  // Body:

  terminate();

  // Postconditions:

  ensure(is_terminated());

  return;
}

void
sheaf::subposet_state::
initialize(int xmember_ub, const scoped_index& xindex, bool xinitialize)
{

  // Preconditions:

  require(xmember_ub >= 0);
  require(xindex.is_valid());
  require(unexecutable("for all i in xmembers: 0 <= i < xmember_ub"));

  // Body:

  _members = new zn_to_bool(xmember_ub);

  if(xinitialize)
  {
    // initialize to empty

    _members->make_false_sa();
  }
  else
  {
    // Do not initialize; leave membership undefined.
    // Presumably client will initialize before using.
    // Intended mostly for use by class storage_agent.
  }

  _index = xindex;

  // Postconditions:

  ensure(is_initialized());
  ensure(_members->ub() >= xmember_ub);
  ensure(_index == xindex);
  ensure(is_persistent());

  // Exit

  return;
}

void
sheaf::subposet_state::
initialize(int xmember_ub,
           const scoped_index& xindex,
           const block<pod_index_type>& xmembers)
{

  // Preconditions:

  require(xmember_ub >= 0);
  require(xindex.is_valid());
  require(unexecutable("for all i in xmembers: 0 <= i < xmember_ub"));

  // Body:

  _members = new zn_to_bool(xmember_ub);

  if(xmember_ub > 0)
  {
    // Initialize with client provided members.

    for(int i=0; i<xmembers.ct(); ++i)
    {
      _members->put(xmembers[i], true);
    }
  }

  _index = xindex;

  // Postconditions:

  ensure(is_initialized());
  ensure(_members->ub() >= xmember_ub);
  ensure(_index == xindex);
  ensure(is_persistent());

  // Exit

  return;
}

void
sheaf::subposet_state::
initialize(int xmember_ub,
           const scoped_index& xindex,
           const block<scoped_index>& xmembers)
{

  // Preconditions:

  require(xmember_ub >= 0);
  require(xindex.is_valid());
  require(unexecutable("for all i in xmembers: 0 <= i < xmember_ub"));

  // Body:

  _members = new zn_to_bool(xmember_ub);

  if(xmember_ub > 0)
  {
    // Initialize with client provided members.

    for(int i=0; i<xmembers.ct(); ++i)
    {
      _members->put(xmembers[i].hub_pod(), true);
    }
  }

  _index = xindex;

  // Postconditions:

  ensure(is_initialized());
  ensure(_members->ub() >= xmember_ub);
  ensure(_index == xindex);
  ensure(is_persistent());

  // Exit

  return;
}

bool
sheaf::subposet_state::
is_initialized() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && _members != 0;
  result = result && _index.is_valid();

  // Postconditions:

  ensure(_members != 0);
  ensure(_index.is_valid());

  // Exit

  return result;
}

void
sheaf::subposet_state::
terminate()
{
  // Preconditions:

  // Body:

  if(_members != 0)
  {
    delete _members;
    _members = 0;
  }

  _index.invalidate();
  _is_dof_subposet = false;
  _dof_ct = 0;

  if(_dof_descriptors != 0)
  {
    _dof_descriptors->remove_reference(); // may delete _dof_descriptors
    _dof_descriptors = 0;
  }

  if(_id_space != 0)
  {
    _id_space->release_id_space();
    _id_space = 0;
  }

  // Postconditions:

  ensure(is_terminated());

  // Exit

  return;
}

bool
sheaf::subposet_state::
is_terminated() const
{
  bool result = true;

  // Preconditions:

  // Body:

  result = result && (_members == 0);
  result = result && (!_index.is_valid());
  result = result && (_is_dof_subposet == false);
  result = result && (_dof_ct == 0);
  result = result && (_dof_descriptors == 0);
  result = result && (_id_space == 0);

  // Postconditions:

  ensure(result ? members() == 0 : true);
  ensure(result ? !index().is_valid() : true);
  ensure(result ? !is_dof_subposet() : true);
  ensure(result ? dof_ct() == 0 : true);
  ensure(result ? dof_descriptors() == 0 : true);
  ensure(result ? !has_id_space() : true);

  // Exit

  return result;
}

const sheaf::scoped_index&
sheaf::subposet_state::
next() const
{
  // pool uses _index member as link in free list

  return _index;
}

void
sheaf::subposet_state::
put_next(const scoped_index& xnext)
{
  // Preconditions:

  // Body:

  _index = xnext;

  // Postconditions:

  // Exit

  return;
}

sheaf::zn_to_bool*
sheaf::subposet_state::
members() const
{
  return _members;
}

void
sheaf::subposet_state::
put_members(const zn_to_bool* xmembers)
{
  // Postconditions:

  // Body:

  _members = const_cast<zn_to_bool*>(xmembers);

  // Postconditions:

  ensure(members() == xmembers);

  // Exit:

  return;
}

const sheaf::scoped_index&
sheaf::subposet_state::
index() const
{
  return _index;
}

bool
sheaf::subposet_state::
is_dof_subposet() const
{
  return _is_dof_subposet;
}

void
sheaf::subposet_state::
put_is_dof_subposet(bool xis_dof_subposet)
{
  // Preconditions:

  // Body:

  _is_dof_subposet = xis_dof_subposet;

  // Postconditions:

  ensure(is_dof_subposet() == xis_dof_subposet);

  // Exit:

  return;
}

sheaf::size_type
sheaf::subposet_state::
dof_ct() const
{
  return _dof_ct;
}

void
sheaf::subposet_state::
put_dof_ct(size_type xdof_ct)
{
  // Preconditions:

  // Body:

  _dof_ct = xdof_ct;

  // Postconditions:

  ensure(dof_ct() == xdof_ct);

  // Exit:

  return;
}

sheaf::size_type
sheaf::subposet_state::
dof_tuple_ub()
{
  // Preconditions:

  require(dof_descriptors() != 0);

  // Body:

  return (*_dof_descriptors)[_dof_ct].offset;
}

sheaf::dof_descriptor_array*
sheaf::subposet_state::
dof_descriptors() const
{
  return _dof_descriptors;
}

void
sheaf::subposet_state::
put_dof_descriptors(const dof_descriptor_array* xdof_descriptors)
{
  // Preconditions:

  // Body:

  _dof_descriptors = const_cast<dof_descriptor_array*>(xdof_descriptors);
  _dof_descriptors->add_reference();

  // Postconditions:

  ensure(dof_descriptors() == xdof_descriptors);

  // Exit:

  return;
}

bool
sheaf::subposet_state::
has_id_space() const
{
  return (_id_space != 0);
}

const sheaf::mutable_index_space_handle&
sheaf::subposet_state::
id_space() const
{
  // Preconditions:

  require(has_id_space());

  // Body:

  return *_id_space;
}

sheaf::mutable_index_space_handle&
sheaf::subposet_state::
id_space()
{
  // Preconditions:

  require(has_id_space());

  // Body:

  return *_id_space;
}

void
sheaf::subposet_state::
put_id_space(const index_space_family& xid_spaces, pod_index_type xid)
{
  // Preconditions:

  require(xid_spaces.contains(xid));
  require(xid_spaces.handle_conforms_to_state<mutable_index_space_handle>(xid));

  // Body:

  if(_id_space != 0)
  {
    // A handle to the subposet id space is already attached,
    // make sure it is release before assigning a new handle.

    _id_space->release_id_space();
  }

  _id_space = &xid_spaces.get_id_space<mutable_index_space_handle>(xid);

  // Postconditions:

  ensure(&id_space().id_spaces() == &xid_spaces);
  ensure(id_space().index() == xid);

  // Exit:

  return;
}

void
sheaf::subposet_state::
put_id_space(const index_space_family& xid_spaces, const string& xname)
{
  // Preconditions:

  require(xid_spaces.contains(xname));
  require(xid_spaces.handle_conforms_to_state<mutable_index_space_handle>(xname));

  // Body:

  if(_id_space != 0)
  {
    // A handle to the subposet id space is already attached,
    // make sure it is release before assigning a new handle.

    _id_space->release_id_space();
  }

  _id_space = &xid_spaces.get_id_space<mutable_index_space_handle>(xname);

  // Postconditions:

  ensure(&id_space().id_spaces() == &xid_spaces);
  ensure(id_space().name() == xname);

  // Exit:

  return;
}

bool
sheaf::subposet_state::
is_persistent() const
{
  return _is_persistent;
}

void
sheaf::subposet_state::
put_is_persistent(bool xvalue)
{
  // Preconditions:

  // Body:

  _is_persistent = xvalue;

  if(_id_space != 0)
  {
    _id_space->put_is_persistent(xvalue);
  }

  // Postconditions:

  ensure(is_persistent() == xvalue);
  ensure(!has_id_space() || id_space().is_persistent() == xvalue);

  // Exit:

  return;
}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

ostream &
sheaf::
operator << (ostream &os, subposet_state& s)
{
  if(s.members() != 0)
  {
    os << "members: ";
    for(int i=0; i<s.members()->ub(); i++)
    {
      (*(s.members()))[i] ? os << '1' : os << '0';
    }
    os << boolalpha
    << "  is_dof_sp: " << setw(6) << s.is_dof_subposet()
    << noboolalpha
    << "  dof_ct: " << s.dof_ct();

    os << "  offsets: ";

    if(s.dof_descriptors() != 0)
    {
      for(int i=0; i<s.dof_ct(); i++)
      {
        os << " " << (*(s.dof_descriptors()))[i] << ",";
      }
      os << " " << (*(s.dof_descriptors()))[s.dof_ct()];

    }
  }

  return os;
}

size_t
sheaf::
deep_size(const subposet_state& xp, bool xinclude_shallow)
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  subposet_state& lxp = const_cast<subposet_state&>(xp);

  // Calculate the total memory used by data member _members
  // of type zn_to_bool*.

  if(lxp.members() != 0)
  {
    result += deep_size(*(lxp.members()), true);
  }

  // Calculate the total memory used by data member _dof_descriptors
  // of type dof_descriptor_array*.

  if(lxp.dof_descriptors() != 0)
  {
    result += deep_size(*(lxp.dof_descriptors()), true);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "$$$ deep_size(const subposet_state& xp) result = " << result << endl;
#endif

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS
