
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
/// Implementation for class index_space_interval

#include "SheafSystem/index_space_interval.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/index_space_family.h"

// ===========================================================
// INDEX_SPACE_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::index_space_interval::
~index_space_interval()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

sheaf::index_space_interval::pod_type
sheaf::index_space_interval::
begin() const
{
  // Preconditions:

  // Body:

  pod_type result = _begin;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_interval::pod_type
sheaf::index_space_interval::
end() const
{
  // Preconditions:

  // Body:

  pod_type result = _end;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval::
in_bounds(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  bool result = (_begin <= xspace_id) && (xspace_id < _end);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_interval::
index_space_interval()
  : index_space_collection(),
    _begin(invalid_pod_index()),
    _end(invalid_pod_index())
{
  // Preconditions:
    
  // Body:
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return; 
}

void
sheaf::index_space_interval::
new_state(index_space_family& xid_spaces, size_type xub)
{
  // Preconditions:

  // Body:

  define_old_variable(size_type old_id_spaces_end = xid_spaces.end());

  _id_spaces = &xid_spaces;
  _begin = _id_spaces->end();
  _end = _begin + xub;

  _id_spaces->insert_interval(*this);

  // Postconditions:

  ensure(&id_spaces() == &xid_spaces);
  ensure(begin() == old_id_spaces_end);
  ensure(end() == xid_spaces.end());
  ensure(end() == begin() + xub);

  // Exit:

  return;
}

bool
sheaf::index_space_interval::
supports_persistent_id_spaces() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return false;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const std::string&
sheaf::index_space_interval::
class_name() const
{
  static const std::string result("index_space_interval");
  return result;
}

sheaf::factory<sheaf::index_space_interval>&
sheaf::index_space_interval::
id_space_interval_factory()
{
  // Preconditions:

  // Body:

  static factory<index_space_interval> result;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::index_space_interval*
sheaf::index_space_interval::
clone() const
{
  // Preconditions:

  // Body:

  index_space_interval* result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX_SPACE_COLLECTION FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::index_space_interval::
operator==(const index_space_collection& xother) const
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const index_space_interval& lother =
    dynamic_cast<const index_space_interval&>(xother);

  bool result = (_begin == lother._begin);
  result = result && (_end == lother._end);
  result = result && (_id_spaces == lother._id_spaces);

  // Postconditions:

  // Exit

  return result;
}

bool
sheaf::index_space_interval::
contains(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  bool result = in_bounds(xlocal_id + _begin);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
sheaf::index_space_interval::
contains_family(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  bool result = in_bounds(xspace_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_interval::
local_scope(pod_type xspace_id) const
{
  // Preconditions:

  // Body:

  pod_type result =
    contains_family(xspace_id) ? xspace_id - _begin : invalid_pod_index();

  // Postconditions:

  ensure(!is_valid(result) || contains(result));

  // Exit:

  return result;
}

sheaf::index_space_collection::pod_type
sheaf::index_space_interval::
family_scope(pod_type xlocal_id) const
{
  // Preconditions:

  // Body:

  pod_type result = xlocal_id + _begin;

  if(!contains_family(result))
  {
    result = invalid_pod_index();
  }

  // Postconditions:

  ensure(!is_valid(result) || contains_family(result));

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

sheaf::index_space_interval&
sheaf::index_space_interval::
operator=(const index_space_collection& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  const index_space_interval& lother =
    dynamic_cast<const index_space_interval&>(xother);

  _begin     = lother._begin;
  _end       = lother._end;
  _id_spaces = lother._id_spaces;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return *this;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// INDEX SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::index_space_family&
sheaf::index_space_interval::
id_spaces() const
{
  // Preconditions:

  // Body:

  const index_space_family& result = *_id_spaces;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_family&
sheaf::index_space_interval::
id_spaces()
{
  // Preconditions:

  // Body:

  index_space_family& result = *_id_spaces;

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
sheaf::index_space_interval::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const index_space_interval*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::index_space_interval::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(index_space_collection::invariant());

    // Invariances for this class:
      
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
 
std::ostream& 
sheaf::
operator << (std::ostream& xos, const index_space_interval& xn)
{
  // Preconditions:

  // Body:

  xos << "[" << xn.begin() << ", " << xn.end() << "] "
      << xn.class_name() << std::endl;

  // Postconditions:

  // Exit:

  return xos;
}

