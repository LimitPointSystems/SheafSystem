
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
/// Implementation for class crg_interval.

#include "crg_interval.h"

#include "arg_list.h"
#include "assert_contract.h"
#include "factory.h"
#include "index_space_family.h"
#include "index_space_iterator.h"
#include "list_index_space_handle.h"
#include "list_index_space_state.h"
#include "poset_crg_state.h"
#include "poset_path.h"

using namespace std;

// ===========================================================
// CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::crg_interval::
crg_interval()
  : _id_spaces(0),
    _id_spaces_initialized(false),
    _local_id_space_initialized(false),
    _lower_covers_initialized(false),
    _lower_covers_begin(invalid_pod_index()),
    _upper_covers_initialized(false),
    _upper_covers_begin(invalid_pod_index())
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());
}

sheaf::crg_interval::
~crg_interval()
{
  // Preconditions:

  // Body:

  // Delete explicit overrides.

  const explicit_cover_map_type& llower_cover_map = explicit_cover_map(LOWER);
  explicit_cover_map_type::const_iterator itr;
  for(itr = llower_cover_map.begin();
      itr != llower_cover_map.end();
      ++itr)
  {
    _id_spaces->delete_space(itr->second);
  }
  
  const explicit_cover_map_type& lupper_cover_map = explicit_cover_map(UPPER);
  for(itr = lupper_cover_map.begin();
      itr != lupper_cover_map.end();
      ++itr)
  {
    _id_spaces->delete_space(itr->second);
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::pod_index_type
sheaf::crg_interval::
begin() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset();
}

void
sheaf::crg_interval::
begin(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::pod_index_type
sheaf::crg_interval::
end() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.offset() + _local_id_space.end();
}

void
sheaf::crg_interval::
end(scoped_index& result) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  result.put(hub_id_space(), end());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

sheaf::size_type
sheaf::crg_interval::
size() const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.ct();
}

bool
sheaf::crg_interval::
contains_member(pod_index_type xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return _local_id_space.contains_hub(xindex);
}

bool
sheaf::crg_interval::
contains_member(const scoped_index& xindex) const
{
  // Preconditions:

  require(local_id_space_initialized());
  
  // Body:

  return contains_member(xindex.hub_pod());
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ID SPACE FAMILY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::index_space_family&
sheaf::crg_interval::
id_spaces() const
{
  // Preconditions:

  require(id_spaces_initialized());

  // Body:

  return *_id_spaces;
}

const sheaf::hub_index_space_handle&
sheaf::crg_interval::
hub_id_space() const
{
  // Preconditions:

  require(id_spaces_initialized());

  // Body:

  return _id_spaces->hub_id_space();
}

void
sheaf::crg_interval::
initialize_id_spaces(index_space_family& xid_spaces)
{
  // Preconditions:

  require(!id_spaces_initialized());

  // Body:

  _id_spaces = &xid_spaces;
  _id_spaces_initialized = true;

  // Postconditions:

  ensure(id_spaces_initialized());

  // Exit:

  return;
}

bool
sheaf::crg_interval::
id_spaces_initialized() const
{
  return _id_spaces_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// LOCAL ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

std::string
sheaf::crg_interval::
local_id_space_name(pod_index_type xindex)
{
  // Preconditions:

  // Body:

  string result(poset_path::make_reserved_name("", xindex, "_local_ids"));

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::primary_index_space_handle&
sheaf::crg_interval::
local_id_space() const
{
  // Preconditions:

  require(local_id_space_initialized());

  // Body:

  return _local_id_space;
}

void
sheaf::crg_interval::
initialize_local_id_space(const index_space_handle& xlocal_id_space)
{
  // Preconditions:

  require(!local_id_space_initialized());

  // Body:

  // Initialize the local id space.

  _local_id_space.attach_to(xlocal_id_space);
  _local_id_space_initialized = true;

  // Postconditions:

  ensure(local_id_space_initialized());

  // Exit:

  return;
}

bool
sheaf::crg_interval::
local_id_space_initialized() const
{
  return _local_id_space_initialized;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER_SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::pod_index_type
sheaf::crg_interval::
cover_id_space_id(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));
  require(covers_initialized(xlower));

  // Body:

  pod_index_type result;

  explicit_cover_map_type::const_iterator litr =
    explicit_cover_map(xlower).find(xmbr_index);

  if(litr != explicit_cover_map(xlower).end())
  {
    result = litr->second;
  }
  else
  {
    pod_index_type lpod = _local_id_space.pod(xmbr_index);
    result = xlower ? _lower_covers_begin + lpod : _upper_covers_begin + lpod;
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::crg_interval::
covers_initialized(bool xlower) const
{
  // Preconditions:

  // Body:

  bool result = xlower ? _lower_covers_initialized : _upper_covers_initialized;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::crg_interval::
initialize_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(LOWER));
  require(!covers_initialized(UPPER));

  // Body:

  initialize_lower_covers();
  initialize_upper_covers();

  // Postconditions:

  ensure(covers_initialized(LOWER));
  ensure(covers_initialized(UPPER));

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

void
sheaf::crg_interval::
initialize_lower_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(LOWER));

  // Body:

  is_abstract();

  // Posconditions:

  ensure(covers_initialized(LOWER));

  // Exit:

  return;
}

void
sheaf::crg_interval::
initialize_upper_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(UPPER));

  // Body:

  is_abstract();

  // Posconditions:

  ensure(covers_initialized(UPPER));

  // Exit:

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// EXPLICIT COVER SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::crg_interval::
cover_is_explicit(bool xlower, pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  return _id_spaces->handle_conforms_to_state<mutable_index_space_handle>(cover_id_space_id(xlower, xmbr_index));
}

sheaf::pod_index_type
sheaf::crg_interval::
force_explicit_cover(bool xlower, pod_index_type xmbr_index, bool xinitialize)
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  pod_index_type result = cover_id_space_id(xlower, xmbr_index);
  
  if(!_id_spaces->handle_conforms_to_state<mutable_index_space_handle>(result))
  {
    // Id space is not explicit.  Construct an interval id space in its place.

    list_index_space_handle lid_space =
      list_index_space_state::new_space(*_id_spaces, explicit_cover_name(xlower, xmbr_index), false);

    result = lid_space.index();

    if(xinitialize)
    {
      // Initialize the ids of the cover.

      index_space_iterator& litr =
	_id_spaces->get_id_space_iterator(cover_id_space_id(xlower, xmbr_index));

      while(!litr.is_done())
      {
	lid_space.push_back(litr.hub_pod());
	litr.next();
      }

      _id_spaces->release_id_space_iterator(litr);
    }

    // Set the explicit override in the interval.

    explicit_cover_map(xlower)[xmbr_index] = result;
  }
  else
  {
    // Explicit cover already exists, return the id.
  }

  // Postconditions:

  ensure(id_spaces().contains(result));
  ensure(cover_is_explicit(xlower, xmbr_index));

  // Exit:

  return result;
}

std::string
sheaf::crg_interval::
explicit_cover_name(bool xlower, pod_index_type xmbr_index)
{
  // Preconditions:

  // Body:

  string suffix = xlower ? "_lower_cover" : "_upper_cover";

  string result = poset_path::make_reserved_name("explicit_", xmbr_index, suffix);

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

std::string
sheaf::crg_interval::
explicit_cover_name(bool xlower, const scoped_index& xmbr_index)
{
  // Preconditions:

  // Body:

  return explicit_cover_name(xlower, xmbr_index.hub_pod());
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::factory<sheaf::crg_interval>&
sheaf::crg_interval::
interval_factory()
{
  static factory<crg_interval> result;

  return result;
}

sheaf::crg_interval*
sheaf::crg_interval::
new_interval(const std::string& xname)
{
  // Preconditions:

  require(interval_factory().contains_prototype(xname));

  // Body:

  crg_interval* result = interval_factory().new_instance(xname);

  // Postconditions:

  ensure(result != 0);
  ensure(result->class_name() == xname);

  // Exit:

  return result;
}

void
sheaf::crg_interval::
initialize(const namespace_poset& xnamespace)
{
  // Preconditions:

  // Body:

  _id_spaces_initialized = true;
  _local_id_space_initialized = true;
  _lower_covers_initialized = true;
  _upper_covers_initialized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

bool
sheaf::crg_interval::
is_initialized() const
{
  bool result =
    id_spaces_initialized() &&
    local_id_space_initialized() &&
    covers_initialized(LOWER) &&
    covers_initialized(UPPER);

  return result;
}

const std::string&
sheaf::crg_interval::
class_name() const
{
  static const string result("crg_interval");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::crg_interval*
sheaf::crg_interval::
clone() const
{
  crg_interval* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    invariance(local_id_space_initialized() ? begin() == local_id_space().offset() : true);
    invariance(local_id_space_initialized() ? end() == local_id_space().offset() + local_id_space().end() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

std::ostream&
sheaf::operator << (std::ostream& os, const crg_interval& m)
{

  os << "interval begin: " << m.begin()
  << "  interval end: " << m.end()
  << "  interval size: " << m.size()
  << endl;

  return os;
}

size_t
sheaf::deep_size(const crg_interval& xp, bool xinclude_shallow)
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

