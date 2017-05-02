
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
/// Implementation for class index_space_iterator

#include "SheafSystem/index_space_iterator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/hub_index_space_handle.h"
#include "SheafSystem/index_space_family.h"

// ===========================================================
// INDEX_SPACE_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator::
~index_space_iterator()
{
  // Preconditions:

  // Body:

  // Nothing to do;

  // Postconditions:

  // Exit:

  return;
}

sheaf::index_space_iterator&
sheaf::index_space_iterator::
operator=(const index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  if(xother.is_attached())
  {
    _is_done = xother._is_done;
    _pod = xother._pod;
    _hub_pod = xother._hub_pod;
  }
  
  // Postconditions:

  ensure(invariant());
//  ensure((*this) == xother);

  // Exit

  return *this;
}

bool
sheaf::index_space_iterator::
operator==(const index_space_iterator& xother) const
{
  // Preconditions:

  // Body:

  bool result = (is_attached() == xother.is_attached());
  if(result && is_attached())
  {
    result = result && (_is_done == xother._is_done);
    result = result && (_pod == xother._pod);
    result = result && (_hub_pod == xother._hub_pod);
  }
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_iterator*
sheaf::index_space_iterator::
clone() const
{
  index_space_iterator* result;

  // Preconditions:

  // Body:

  result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(*result == *this);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_iterator::
index_space_iterator()
{
  // Preconditions:

  // Body:

  invalidate_ids();

  // Postconditions:

  // Can't call invariant because it calls pure virtual functions.
  //ensure(invariant());
  ensure(is_done());

  // Exit:

  return;
}

sheaf::index_space_iterator::
index_space_iterator(const index_space_iterator& xother)
{
  // Preconditions:

  // Body:

  _is_done = xother._is_done;
  _pod = xother._pod;
  _hub_pod = xother._hub_pod;

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
sheaf::index_space_iterator::
next()
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  define_old_variable(pod_type old_pod = pod());
  define_old_variable(pod_type old_hub_pod = hub_pod());

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(is_done() || pod() != old_pod);
  ensure(is_done() || hub_pod() != old_hub_pod);

  // Exit:

  return;
}

bool
sheaf::index_space_iterator::
is_done() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _is_done;
}

void
sheaf::index_space_iterator::
reset()
{
  // Preconditions:

  require(is_attached());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  invalidate_ids();

  // Postconditions:

  ensure(is_done());

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POD FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_iterator::pod_type
sheaf::index_space_iterator::
pod() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _pod;
}

sheaf::index_space_iterator::pod_type
sheaf::index_space_iterator::
hub_pod() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _hub_pod;
}

sheaf::index_space_iterator::pod_type
sheaf::index_space_iterator::
unglued_hub_pod() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _hub_pod;
}

sheaf::index_space_iterator::pod_type
sheaf::index_space_iterator::
glued_hub_pod() const
{
  // Preconditions:

  require(is_attached());
  require(!is_done());

  // Body:

  pod_type result = hub_id_space().unglued_hub_pod(_hub_pod);

  // Postconditions:

  ensure(hub_id_space().contains_unglued_hub(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

void
sheaf::index_space_iterator::
invalidate_ids()
{
  // Preconditions:

  // Body:

  _pod = invalid_pod_index();
  _hub_pod = invalid_pod_index();
  _is_done = true;

  // Posconditions:

  ensure(is_done());

  // Exite:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::index_space_iterator::
id_spaces() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const index_space_family& result = host().id_spaces();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

const sheaf::hub_index_space_handle&
sheaf::index_space_iterator::
hub_id_space() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  const hub_index_space_handle& result = id_spaces().hub_id_space();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// HANDLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_collection&
sheaf::index_space_iterator::
host() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  index_space_collection* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);
  
  // Exit:

  return *result;
}

sheaf::index_space_iterator::pod_type
sheaf::index_space_iterator::
index() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  pod_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(id_spaces().contains(result));

  // Exit:

  return result;
}

std::string
sheaf::index_space_iterator::
name() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  std::string result = id_spaces().name(index());

  // Postconditions:

  ensure(result.empty() || id_spaces().contains(result));

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
is_attached() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  bool result = false; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::index_space_iterator::
attach_to(const index_space_family& xid_spaces, pod_type xindex)
{
  // Preconditions:

  require(xid_spaces.contains(xindex));
  require(conforms_to_state(xid_spaces, xindex));

  // Body:

  const index_space_collection* lhost = xid_spaces.collection(xindex);
  attach_to(*lhost, lhost->local_scope(xindex));

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
attach_to(const index_space_family& xid_spaces, const std::string& xname)
{
  // Preconditions:

  require(!xname.empty());
  require(xid_spaces.contains(xname));
  require(conforms_to_state(xid_spaces, xname));

  // Body:

  attach_to(xid_spaces, xid_spaces.index(xname));

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &xid_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
attach_to(pod_type xindex)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xindex));
  require(conforms_to_state(xindex));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(index() == xindex);

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
attach_to(const std::string& xname)
{
  // Preconditions:

  require(is_attached());
  require(id_spaces().contains(xname));
  require(conforms_to_state(xname));

  // Body:

  define_old_variable(const index_space_family& old_id_spaces = id_spaces());

  attach_to(id_spaces().index(xname));

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&id_spaces() == &old_id_spaces);
  ensure(name() == xname);

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
attach_to(const index_space_handle& xid_space)
{
  // Preconditions:

  require(xid_space.is_attached());
  require(conforms_to_state(xid_space.id_spaces(), xid_space.index()));

  // Body:

  if(is_attached() && (host() == xid_space.host()))
  {
    attach_to(xid_space.index());
  }
  else
  {
    attach_to(xid_space.id_spaces(), xid_space.index());
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(&host() == &xid_space.host());
  ensure(index() == xid_space.index());

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
attach_to(const index_space_collection& xhost, pod_type xlocal_id)
{
  // Preconditions:

  require(xhost.contains(xlocal_id));
  require(conforms_to_state(xhost, xlocal_id));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_attached());
  ensure(&host() == &xhost);
  ensure(index() == xhost.family_scope(xlocal_id));

  // Exit:

  return;
}

void
sheaf::index_space_iterator::
detach()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

bool
sheaf::index_space_iterator::
conforms_to_state(const index_space_family& xid_spaces,
		  pod_type xindex) const
{
  // Preconditions:

  require(xid_spaces.contains(xindex));

  // Body:

  const index_space_collection* lhost = xid_spaces.collection(xindex);
  bool result = conforms_to_state(*lhost, lhost->local_scope(xindex));
  
  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
conforms_to_state(const index_space_family& xid_spaces,
		  const std::string& xname) const
{
  // Preconditions:

  require(xid_spaces.contains(xname));

  // Body:

  bool result = conforms_to_state(xid_spaces, xid_spaces.index(xname));

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
conforms_to_state(pod_type xindex) const
{
  // Preconditions:

  require(id_spaces().contains(xindex));

  // Body:

  bool result = conforms_to_state(id_spaces(), xindex);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
conforms_to_state(const std::string& xname) const
{
  // Preconditions:

  require(id_spaces().contains(xname));

  // Body:

  bool result = conforms_to_state(id_spaces(), xname);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
conforms_to_state(const index_space_collection& xhost,
		  pod_type xlocal_id) const
{
  // Preconditions:

  require(xhost.contains(xlocal_id));

  // Body:

  bool result = false;

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::index_space_iterator::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_iterator*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_iterator::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(any::invariant());

    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariances for this class:

    invariance(!is_attached() || is_done() || is_valid(pod()));
    invariance(!is_attached() || is_done() || is_valid(hub_pod()));

    /// @hack The following invariance should be true except when
    /// iterating over reserved terms.
//     invariance(!is_attached() || is_done() || pod() == id_spaces().pod(index(), hub_pod()));
//     invariance(!is_attached() || is_done() || hub_pod() == id_spaces().hub_pod(index(), pod()));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
sheaf::
deep_size(const index_space_iterator& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
