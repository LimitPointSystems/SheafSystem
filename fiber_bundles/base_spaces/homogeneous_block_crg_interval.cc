
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
/// Implementation for class homogeneous_block_crg_interval

#include "homogeneous_block_crg_interval.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_poset.h"
#include "error_message.h"
#include "offset_index_space_state.h"
#include "index_space_iterator.h"
#include "std_iomanip.h"
#include "std_string.h"
#include "std_sstream.h"
#include "homogeneous_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// ===========================================================
// HOMOGENEOUS_BLOCK_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::homogeneous_block_crg_interval::
homogeneous_block_crg_interval()
  : _zones_initialized(false),
    _zones_space_id(invalid_pod_index()),
    _vertices_initialized(false),
    _vertices_space_id(invalid_pod_index()),
    _connectivity_begin(invalid_pod_index()),
    _adjacency_begin(invalid_pod_index())
{
  // Body:

  // Initialize dof tuple ids.

  _dof_tuple_ids.reserve(MEMBER_CLASS_END);
  _dof_tuple_ids.set_ct(MEMBER_CLASS_END);
  _dof_tuple_ids.assign(invalid_pod_index());

  // Postconditions:

  ensure(invariant());
  ensure(!is_initialized());

  return;
}

fiber_bundle::homogeneous_block_crg_interval::
~homogeneous_block_crg_interval()
{
  // Preconditions:

  // Body:

  if(is_valid(_zones_space_id) &&
     _id_spaces->contains(_zones_space_id))
  {
    _id_spaces->delete_secondary_state(_zones_space_id);
  }

  if(is_valid(_vertices_space_id) &&
     _id_spaces->contains(_vertices_space_id))
  {
    _id_spaces->delete_secondary_state(_vertices_space_id);
  }

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::homogeneous_block_crg_interval::member_class_type
fiber_bundle::homogeneous_block_crg_interval::
member_class(pod_index_type xmbr_index) const
{

  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  member_class_type result;

  if(_id_spaces->contains_hub(_vertices_space_id, xmbr_index))
  {
    result = VERTEX;
  }
  else if(_id_spaces->contains_hub(_zones_space_id, xmbr_index))
  {
    result = ZONE;
  }
  else
  {
    result = BLOCK;
  }

  // Postconditions:

  // Exit:

  return result;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ZONES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_interval::
zones_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _zones_initialized;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
zones_space_id() const
{
  // Preconditions:

  require(zones_initialized());

  // Body:

  pod_index_type result = _zones_space_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// VERTICES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_interval::
vertices_initialized() const
{
  // Preconditions:

  // Body:

  bool result = _vertices_initialized;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
vertices_space_id() const
{
  // Preconditions:

  require(vertices_initialized());

  // Body:

  pod_index_type result = _vertices_space_id;

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// CONNECTIVITY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
connectivity_space_id(pod_index_type xzone_id) const
{
  // Preconditions:

  require(id_spaces().contains_hub(zones_space_id(), xzone_id));

  // Body:

  pod_index_type result =
    _connectivity_begin + id_spaces().pod(_zones_space_id, xzone_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ADJACENCY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
adjacency_space_id(pod_index_type xvertex_id) const
{
  // Preconditions:

  require(id_spaces().contains_hub(vertices_space_id(), xvertex_id));

  // Body:

  pod_index_type result =
    _adjacency_begin + id_spaces().pod(_vertices_space_id, xvertex_id);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BLOCK VERTICES FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BASE_SPACE_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
cells_begin() const
{
  return implicit_begin();
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
cells_end() const
{
  return end();
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IMPLICIT_CRG_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// CRG_INTERVAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// COVER SET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// DOF TUPLE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_interval::
is_jim(pod_index_type xmbr_index) const
{
  // Every member except the block itself is a jim.

  return !is_interval_member(xmbr_index);
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
dof_tuple_id(pod_index_type xmbr_index) const
{
  // Preconditions:

  require(contains_member(xmbr_index));

  // Body:

  // Map xmbr_index to the id space of this.

  pod_index_type result =
    _dof_tuple_ids[member_class(xmbr_index)];

  // Postconditions:

  ensure(is_valid(result));

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
block_dof_tuple_id() const
{
  return _dof_tuple_ids[BLOCK];
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
zone_dof_tuple_id() const
{
  return _dof_tuple_ids[ZONE];
}

sheaf::pod_index_type
fiber_bundle::homogeneous_block_crg_interval::
vertex_dof_tuple_id() const
{
  return _dof_tuple_ids[VERTEX];
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fiber_bundle::homogeneous_block_crg_interval::
initialize(const namespace_poset& xnamespace)
{
  // Preconditions:

  // Body:

  base_space_crg_interval::initialize(xnamespace);

  _zones_initialized = true;
  _vertices_initialized = true;

  // Postconditions:

  ensure(is_initialized());

  // Exit:

  return;
}

bool
fiber_bundle::homogeneous_block_crg_interval::
is_initialized() const
{
  bool result =
    base_space_crg_interval::is_initialized() &&
    _zones_initialized &&
    _vertices_initialized;

  return result;
}

const string&
fiber_bundle::homogeneous_block_crg_interval::
class_name() const
{
  static const string result("homogeneous_block_crg_interval");
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::homogeneous_block_crg_interval::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const homogeneous_block_crg_interval*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::homogeneous_block_crg_interval*
fiber_bundle::homogeneous_block_crg_interval::
clone() const
{
  // Preconditions:

  // Body:

  homogeneous_block_crg_interval* result = 0;

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fiber_bundle::homogeneous_block_crg_interval::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(base_space_crg_interval::invariant());

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

