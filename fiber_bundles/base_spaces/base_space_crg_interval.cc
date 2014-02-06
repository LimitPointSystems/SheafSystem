
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
/// Implementation for class base_space_crg_interval.

#include "base_space_crg_interval.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "list_index_space_state.h"
#include "index_space_iterator.h"
#include "scoped_index.h"
#include "std_iomanip.h"
#include "std_string.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BASE_SAPCE_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::base_space_crg_interval::
base_space_crg_interval()
  : _block_vertices_initialized(false),
    _block_vertices_space_id(invalid_pod_index())
{
  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::base_space_crg_interval::
~base_space_crg_interval()
{
  // Preconditions:

  // Body:

  if(is_valid(_block_vertices_space_id))
  {
    _id_spaces->delete_space(_block_vertices_space_id);
  }

  // Postconditions:

  // Exit:

  return;
}

void
fiber_bundle::base_space_crg_interval::
cells_begin(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(hub_id_space(), cells_begin());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

void
fiber_bundle::base_space_crg_interval::
cells_end(scoped_index& result) const
{
  // Preconditions:

  // Body:

  result.put(hub_id_space(), cells_end());

  // Postconditions:

  ensure(result.is_hub_scope());

  // Exit:

  return;
}

int
fiber_bundle::base_space_crg_interval::
db(pod_index_type xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  is_abstract();

  int result = -1; // Just to silence compiler warnings.

  // Postconditions:

  // Exit:

  return result;
}

int
fiber_bundle::base_space_crg_interval::
db(const scoped_index& xmbr_id) const
{
  // Preconditions:

  require(contains_member(xmbr_id));

  // Body:

  return db(xmbr_id.hub_pod());
}

sheaf::pod_index_type
fiber_bundle::base_space_crg_interval::
d_cells_space_id(int xd) const
{
  // Preconditions:

  // Body:

  pod_index_type result = 0; // To silence the debugger
  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BLOCK VERTICES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_crg_interval::
block_vertices_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _block_vertices_initialized;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

pod_index_type
fiber_bundle::base_space_crg_interval::
block_vertices_space_id() const
{
  // Preconditions:

  require(block_vertices_initialized());

  // Body:

  pod_index_type result = _block_vertices_space_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

std::string
fiber_bundle::base_space_crg_interval::
block_vertices_name() const
{
  // Preconditions:

  // Body:

  string result =
    poset_path::make_reserved_name("block_vertices_", interval_member(), "");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::base_space_crg_interval::
initialize(const namespace_poset& xnamespace)
{
  // Preconditions:

  // Body:

  implicit_crg_interval::initialize(xnamespace);

  _block_vertices_initialized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

bool
fiber_bundle::base_space_crg_interval::
is_initialized() const
{
  bool result =
    implicit_crg_interval::is_initialized() &&
    _block_vertices_initialized;

  return result;
}

const std::string&
fiber_bundle::base_space_crg_interval::
class_name() const
{
  static const string result("base_space_crg_interval");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const base_space_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

bool
fiber_bundle::base_space_crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(implicit_crg_interval::invariant());

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
// NON-MEMBER FUNCTIONS
// ===========================================================

