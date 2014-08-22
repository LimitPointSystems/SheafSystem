
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
/// Implementation for class standard_member_hack_crg_interval.

#include "ComLimitPoint/sheaf/standard_member_hack_crg_interval.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/explicit_index_space_interval.h"
#include "ComLimitPoint/sheaf/factory.h"
#include "ComLimitPoint/sheaf/index_space_family.h"
#include "ComLimitPoint/sheaf/index_space_iterator.h"

using namespace std;

// ===========================================================
// STANDARD_MEMBER_HACK_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

sheaf::standard_member_hack_crg_interval::
standard_member_hack_crg_interval()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());
}

sheaf::standard_member_hack_crg_interval::
~standard_member_hack_crg_interval()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// EXPLICIT_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// CRG_INTERVAL FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// COVER_SET FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

void
sheaf::standard_member_hack_crg_interval::
initialize_lower_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(LOWER));

  // Body:

  // Only supports covers for top and bottom.

  _lower_covers_begin =
    explicit_index_space_interval::new_space(*_id_spaces, 2).begin();

  _lower_covers_initialized = true;

  // Posconditions:

  ensure(covers_initialized(LOWER));

  // Exit:

  return;
}

void
sheaf::standard_member_hack_crg_interval::
initialize_upper_covers()
{
  // Preconditions:

  require(id_spaces_initialized());
  require(local_id_space_initialized());
  require(!covers_initialized(UPPER));

  // Body:

  // Only supports covers for top and bottom.

  _upper_covers_begin =
    explicit_index_space_interval::new_space(*_id_spaces, 2).begin();

  _upper_covers_initialized = true;

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

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const std::string&
sheaf::standard_member_hack_crg_interval::
class_name() const
{
  static const string result("standard_member_hack_crg_interval");
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

bool
sheaf::standard_member_hack_crg_interval::
make_prototype()
{
  // Preconditions:


  // Body:

  standard_member_hack_crg_interval* lproto = new standard_member_hack_crg_interval();

  interval_factory().insert_prototype(lproto);

  // Postconditions:


  // Exit:

  return true;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
sheaf::standard_member_hack_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const standard_member_hack_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

sheaf::standard_member_hack_crg_interval*
sheaf::standard_member_hack_crg_interval::
clone() const
{
  // Preconditions:

  // Body:

  standard_member_hack_crg_interval* result = new standard_member_hack_crg_interval();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
sheaf::standard_member_hack_crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(crg_interval::invariant());

    // Invariances for this class:

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

size_t
sheaf::deep_size(const standard_member_hack_crg_interval& xp, bool xinclude_shallow)
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

