
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
/// Implementation for class base_space_poset.

#include "SheafSystem/base_space_poset.h"

#include "SheafSystem/array_index_space_state.h"
#include "SheafSystem/array_poset_dof_map.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/index_space_handle.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/interval_index_space_state.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/namespace_poset_member.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/poset_type.h"
#include "SheafSystem/preorder_iterator.h"
#include "SheafSystem/std_sstream.h"
#include "SheafSystem/zone_nodes_block_crg_interval.h"

using namespace std;
using namespace fiber_bundle;

// ===========================================================
// BASE_SPACE_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::poset_path&
fiber_bundle::base_space_poset::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = base_space_member::standard_schema_path();

  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}

fiber_bundle::base_space_poset&
fiber_bundle::base_space_poset::
new_table(namespace_type& xns, const poset_path& xpath, const poset_path& xschema_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering base_space_poset::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(unexecutable("xschema_path conforms to standard_schema_path"));
  //  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xmax_db >= 0);

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef base_space_poset table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("max_db", xmax_db);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  base_space_poset& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == xmax_db);

  // Exit:

  // cout << "Leaving base_space_poset::new_table." << endl;
  return result;
}

// PROTECTED FUNCTIONS

fiber_bundle::base_space_poset::
base_space_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(refinable_poset::refinable_poset()));
}

fiber_bundle::base_space_poset::
~base_space_poset()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS

bool
fiber_bundle::base_space_poset::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  poset_type ltype = POSET_ID;

  base_space_poset* lproto = new base_space_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}

// ===========================================================
// ZONE ID SPACE FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
contains_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval* linterval =
    dynamic_cast<const homogeneous_block_crg_interval*>(&crg().interval(xmbr_id));

  bool result = (linterval != 0) && linterval->zones_initialized();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
contains_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  bool result = contains_zone_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_zone_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_zone_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_handle& result = crg().id_spaces().get_id_space(linterval.zones_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_zone_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_zone_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_handle& result = get_zone_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_zone_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_zone_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_zone_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_iterator& result = crg().id_spaces().get_id_space_iterator(linterval.zones_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_zone_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_zone_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_iterator& result = get_zone_id_space_iterator(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_zone_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// VERTEX ID SPACE FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
contains_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval* linterval =
    dynamic_cast<const homogeneous_block_crg_interval*>(&crg().interval(xmbr_id));

  bool result = (linterval != 0) && linterval->vertices_initialized();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
contains_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  bool result = contains_vertex_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_vertex_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_handle& result = crg().id_spaces().get_id_space(linterval.vertices_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_vertex_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_handle& result = get_vertex_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_vertex_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_vertex_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_iterator& result = crg().id_spaces().get_id_space_iterator(linterval.vertices_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_vertex_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_iterator& result = get_vertex_id_space_iterator(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_vertex_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// VERTEX CLIENT ID SPACE FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
contains_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const zone_nodes_block_crg_interval* linterval =
    dynamic_cast<const zone_nodes_block_crg_interval*>(&crg().interval(xmbr_id));

  bool result = (linterval != 0) && linterval->vertex_client_id_space_initialized();

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
contains_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));

  // Body:

  bool result = contains_vertex_client_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_vertex_client_id_space(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_client_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const zone_nodes_block_crg_interval& linterval =
    reinterpret_cast<const zone_nodes_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_handle& result = crg().id_spaces().get_id_space(linterval.vertex_client_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_vertex_client_id_space(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_client_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_handle& result = get_vertex_client_id_space(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_vertex_client_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_vertex_client_id_space_iterator(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_client_id_space(xmbr_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const zone_nodes_block_crg_interval& linterval =
    reinterpret_cast<const zone_nodes_block_crg_interval&>(crg().interval(xmbr_id));

  index_space_iterator& result = crg().id_spaces().get_id_space_iterator(linterval.vertex_client_space_id());

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_vertex_client_id_space_iterator(const scoped_index& xmbr_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xmbr_id, xauto_access));
  require(contains_vertex_client_id_space(xmbr_id, xauto_access));

  // Body:

  index_space_iterator& result = get_vertex_client_id_space_iterator(xmbr_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_vertex_client_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS



// ===========================================================
// CONNECTIVITY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
contains_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval* linterval =
    dynamic_cast<const homogeneous_block_crg_interval*>(&crg().interval(xzone_id));

  bool result =
    (linterval != 0) &&
    crg().id_spaces().contains_hub(linterval->zones_space_id(), xzone_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
contains_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));

  // Body:

  bool result = contains_connectivity_id_space(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xzone_id));

  index_space_handle& result =
    crg().id_spaces().get_id_space(linterval.connectivity_space_id(xzone_id));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  index_space_handle& result = get_connectivity_id_space(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_connectivity_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_connectivity_id_space_iterator(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xzone_id));

  index_space_iterator& result =
    crg().id_spaces().get_id_space_iterator(linterval.connectivity_space_id(xzone_id));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_connectivity_id_space_iterator(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xzone_id, xauto_access));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  index_space_iterator& result = get_connectivity_id_space_iterator(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_connectivity_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ADJACENCY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
contains_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval* linterval =
    dynamic_cast<const homogeneous_block_crg_interval*>(&crg().interval(xvertex_id));

  bool result =
    (linterval != 0) &&
    crg().id_spaces().contains_hub(linterval->vertices_space_id(), xvertex_id);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
contains_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));

  // Body:

  bool result = contains_adjacency_id_space(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xvertex_id));

  index_space_handle& result =
    crg().id_spaces().get_id_space(linterval.adjacency_space_id(xvertex_id));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::base_space_poset::
get_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  index_space_handle& result = get_adjacency_id_space(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_adjacency_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space(xid_space);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_adjacency_id_space_iterator(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  const homogeneous_block_crg_interval& linterval =
    reinterpret_cast<const homogeneous_block_crg_interval&>(crg().interval(xvertex_id));

  index_space_iterator& result =
    crg().id_spaces().get_id_space_iterator(linterval.adjacency_space_id(xvertex_id));

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::base_space_poset::
get_adjacency_id_space_iterator(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_member(xvertex_id, xauto_access));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  index_space_iterator& result = get_adjacency_id_space_iterator(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
release_adjacency_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  crg().id_spaces().release_id_space_iterator(xitr);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBER PROTOTYPES FACET
// ===========================================================

// PUBLIC FUNCTIONS

const std::string&
fiber_bundle::base_space_poset::
prototypes_poset_name()
{

  // Preconditions:

  // Body:

  const string& result = base_space_member::prototypes_poset_name();

  // Postconditions:

  ensure(result == base_space_member::prototypes_poset_name());

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_poset::
prototype_type_id(const std::string& xname, bool xauto_access) const
{

  // Preconditions:

  require(xauto_access ? is_attached() : state_is_read_accessible());
  require(xauto_access || name_space()->state_is_read_accessible());
  require(xauto_access || name_space()->member_poset(prototypes_poset_name(), true).state_is_read_accessible());
  require(name_space()->contains_poset_member(prototypes_poset_name()+"/"+xname, true));
  require(unexecutable("!xauto_access ? prototypes poset is read accessible : true"));


  // Body:

  if(xauto_access)
  {
    get_read_access();
    name_space()->get_read_access();
  }

  poset_state_handle& lproto_host =
    name_space()->member_poset(prototypes_poset_name(), false);

  if(xauto_access)
  {
    lproto_host.get_read_access();
  }

  base_space_member lmbr(reinterpret_cast<poset*>(&lproto_host), xname);
  pod_index_type result = lmbr.type_id();
  lmbr.detach_from_state();

  if(xauto_access)
  {
    lproto_host.release_access();
    name_space()->release_access();
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::scoped_index
fiber_bundle::base_space_poset::
prototype_dof_tuple_id(const std::string& xname,
                       int xdepth,
                       bool xcreate,
                       bool xauto_access) const
{
  // Preconditions:

  require(is_attached());
  require(xauto_access || (xcreate ? state_is_read_write_accessible() : state_is_read_accessible()));

  // Body:

  base_space_poset* cthis = const_cast<base_space_poset*>(this); 

  if(xauto_access)
  {
    xcreate ? cthis->get_read_write_access(true) : get_read_access();
  }

  scoped_index result;

  size_type ltuple_ct = row_dof_tuple_ct();
  for(pod_index_type ltuple_id = 0; ltuple_id < ltuple_ct; ++ltuple_id)
  {
    row_dof_tuple_type* ltuple = row_dof_tuple(ltuple_id);
    if((xname == ltuple->type_name) && xdepth == ltuple->refinement_depth)
    {
      result = dof_tuple_id(ltuple_id, false);
      break;
    }
  }

  if(!result.is_valid() && xcreate)
  {
    // Couldn't find a dof tuple, have to make one.

    result = cthis->new_row_dof_map(xname);
    row_dof_tuple(result, true)->refinement_depth = xdepth;
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  ensure(!result.is_valid() || contains_row_dof_tuple(result));
  ensure(!result.is_valid() || (xname == row_dof_tuple(result)->type_name));
  ensure(!result.is_valid() || (xdepth == row_dof_tuple(result)->refinement_depth));

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

// ===========================================================
// POSET_STATE_HANDLE FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS

// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
fiber_bundle::base_space_poset::
type_id() const
{
  return BASE_SPACE_POSET_ID;
}

const char*
fiber_bundle::base_space_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "base_space_poset";

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::base_space_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  refinable_poset::attach_handle_data_members();

  // Attch the standard subposets.

  _blocks.attach_to_state(this, blocks_name());
  _block_vertices.attach_to_state(this, block_vertices_name());

  int lmax_db = max_db();
  _d_cells.reserve(lmax_db+1);
  _d_cells.set_ct(lmax_db+1);

  _d_cells_id_spaces.reserve(lmax_db+1);
  _d_cells_id_spaces.set_ct(lmax_db+1);

  for(int i=0; i<=lmax_db; i++)
  {
    _d_cells[i].attach_to_state(this, d_cells_name(i, lmax_db));
    _d_cells_id_spaces[i] = &_d_cells[i].id_space();
  }

  _cells.attach_to_state(this, cells_name());

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE FUNCTIONS

// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::base_space_poset::
new_member(const std::string& xprototype_name, bool xcopy_dof_map)
{
  // cout << endl << "Entering base_space_poset::new_member." << endl;

  // Preconditions:

  require(in_jim_edit_mode());
  require(name_space()->state_is_read_accessible());
  require(name_space()->member_poset(prototypes_poset_name(), false).state_is_read_accessible());
  require(!xprototype_name.empty());
  require(name_space()->contains_poset_member(poset_path(prototypes_poset_name(), xprototype_name), false));

  // Body:

  scoped_index ltuple_id;
  
  if(xcopy_dof_map)
  {
    ltuple_id = new_row_dof_map(xprototype_name);
  }
  else
  {
    ltuple_id = prototype_dof_tuple_id(xprototype_name, 0, true, false);
  }

  pod_index_type result = new_member(true, ltuple_id.hub_pod());

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(result, false));
  ensure(type_name(result) == xprototype_name);
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // Exit:

  // cout << "Leaving base_space_poset::new_member." << endl;
  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_poset::
new_member(const char* xprototype_name, bool xcopy_dof_map)
{
  // cout << endl << "Entering base_space_poset::new_member." << endl;

  // Preconditions:

  require(precondition_of(new_member(string(xprototype_name), xcopy_dof_map)));

  // Body:

  string lprotoname(xprototype_name);
  
  pod_index_type result = new_member(lprotoname, xcopy_dof_map);

  // Postconditions:

  ensure(postcondition_of(new_member(string(xprototype_name), xcopy_dof_map)));

  // Exit:

  // cout << "Leaving base_space_poset::new_member." << endl;
  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_poset::
new_member(const std::string& xtype_name, int xdb, const std::string& xlocal_cell_name)
{
  // cout << endl << "Entering base_space_poset::new_member." << endl;

  // Preconditions:

  require(in_jim_edit_mode());
  require(name_space()->state_is_read_accessible());
  require(poset_path::is_valid_name(xtype_name));
  require(!contains_member(xtype_name, true));
  require(member_id_spaces(false).contains("cell_types"));
  require(xlocal_cell_name.empty() || contains_member(xlocal_cell_name));

  // Body:

  // Create the dof map and set dofs to defaults.

  pod_index_type result = new_member(true, 0, false);

  // Set name to type name.

  put_member_name(result, xtype_name, true, false);

  // Get the row dof tuple.

  row_dof_tuple_type* ltuple = member_dof_tuple(result, true);

  // Set db.

  ltuple->db = xdb;

  // Set type id.

  scattered_insertion_index_space_handle& ltype_id_space =
    member_id_spaces(false).get_id_space<scattered_insertion_index_space_handle>("cell_types");

  ltype_id_space.push_back(result);

  ltuple->type_id = ltype_id_space.pod(result);

  ltype_id_space.release_id_space();

  // Set type name.

  /// @error where does this string get deleted?

  ltuple->type_name = strdup(xtype_name.c_str());

  // Set the refinement depth.

  ltuple->refinement_depth = 0;

  // Set local cell type id and type name.

  if(xlocal_cell_name.empty())
  {
    ltuple->local_cell_type_id = sheaf::invalid_pod_index();

    /// @error where does this string get deleted?

    ltuple->local_cell_type_name = strdup("");
  }
  else
  {
    base_space_member lcell(this, xlocal_cell_name);
    ltuple->local_cell_type_id = lcell.type_id();

    /// @error where does this string get deleted?

    ltuple->local_cell_type_name = strdup(lcell.type_name());
    lcell.detach_from_state();
  }

  // Set the remaining dofs to default values.

  ltuple->size = 0;
  ltuple->i_size = 0;
  ltuple->j_size = 0;
  ltuple->k_size = 0;

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(result, false));
  ensure(member_name(result, false) == xtype_name);
  ensure(db(result) == xdb);
  ensure(type_name(result) == xtype_name);
  ensure(unexecutable("local_cell_type_name(result) == xlocal_cell_name"));
  ensure(cover_is_empty(LOWER, result));
  ensure(cover_is_empty(UPPER, result));

  // Exit:

  // cout << "Leaving base_space_poset::new_member." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS
 

// ===========================================================
// POWERSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::subposet&
fiber_bundle::base_space_poset::
blocks()
{
  // Preconditions:

  // Body:

  subposet& result = _blocks;

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
blocks() const
{
  // Preconditions:

  // Body:

  const subposet& result = _blocks;

  // Postconditions:

  // Exit:

  return result;
}

std::string
fiber_bundle::base_space_poset::
blocks_name()
{

  // Preconditions:

  // Body:

  string result = poset_path::reserved_prefix() + "blocks";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::base_space_poset::
block_vertices()
{
  // Preconditions:

  // Body:

  subposet& result = _block_vertices;

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
block_vertices() const
{
  // Preconditions:

  // Body:

  const subposet& result = _block_vertices;

  // Postconditions:

  // Exit:

  return result;
}

std::string
fiber_bundle::base_space_poset::
block_vertices_name()
{

  // Preconditions:

  // Body:

  string result = poset_path::reserved_prefix() + "block_vertices";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::base_space_poset::
vertices()
{
  // Preconditions:

  // Body:

  subposet& result = _d_cells[0];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
vertices() const
{
  // Preconditions:

  // Body:

  subposet& result = _d_cells[0];

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::base_space_poset::
elements()
{
  // Preconditions:

  // Body:

  subposet& result = _d_cells[max_db()];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
elements() const
{
  // Preconditions:

  // Body:

  subposet& result = _d_cells[max_db()];

  // Postconditions:

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::base_space_poset::
d_cells(int xd)
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xd) && (xd <= max_db()));

  // Body:

  subposet& result = _d_cells[xd];

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
d_cells(int xd) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xd) && (xd <= max_db()));

  // Body:

  subposet& result = _d_cells[xd];

  // Postconditions:

  // Exit:

  return result;
}

sheaf::scattered_insertion_index_space_handle&
fiber_bundle::base_space_poset::
d_cells_id_space(int xd)
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xd) && (xd <= max_db()));

  // Body:

  scattered_insertion_index_space_handle& result = *_d_cells_id_spaces[xd];

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::scattered_insertion_index_space_handle&
fiber_bundle::base_space_poset::
d_cells_id_space(int xd) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require((0 <= xd) && (xd <= max_db()));

  // Body:

  const scattered_insertion_index_space_handle& result = *_d_cells_id_spaces[xd];

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

std::string
fiber_bundle::base_space_poset::
d_cells_name(int xdb, int xmax_db)
{
  string result;

  // Preconditions:

  // Body:

  if(xdb == 0)
  {
    result = poset_path::reserved_prefix() + "vertices";
  }
  else if(xdb == xmax_db)
  {
    result = poset_path::reserved_prefix() + "elements";
  }
  else
  {
    stringstream lsp_name_stream;
    lsp_name_stream << poset_path::reserved_prefix() << xdb << "_cells";
    lsp_name_stream >> result;
  }

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::subposet&
fiber_bundle::base_space_poset::
cells()
{
  // Preconditions:

  // Body:

  subposet& result = _cells;

  // Postconditions:

  // Exit:

  return result;
}

const sheaf::subposet&
fiber_bundle::base_space_poset::
cells() const
{
  // Preconditions:

  // Body:

  const subposet& result = _cells;

  // Postconditions:

  // Exit:

  return result;
}

std::string
fiber_bundle::base_space_poset::
cells_name()
{

  // Preconditions:

  // Body:

  string result = poset_path::reserved_prefix() + "cells";

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
insert_interval_in_standard_subposets(base_space_crg_interval& xinterval)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(contains_member(xinterval.interval_member()));

  // Body:

  // Insert the block in the blocks subposet.

  pod_index_type linterval_mbr = xinterval.interval_member();
  subposet& lblocks_sp = blocks();
  lblocks_sp.insert_member(linterval_mbr);
  lblocks_sp.id_space().push_back(linterval_mbr);

  // Insert the cells in the d-cells subposets.

  for(pod_index_type i = xinterval.cells_begin(); i < xinterval.cells_end(); ++i)
  {
    // Get the dimension directly from the interval member;
    // doesn't access dof tuples, which don't exist yet when
    // poset is being read from file.

    int ldb = xinterval.db(i);
    d_cells(ldb).insert_member(i);

    // Populate cells subposet as well.

    cells().insert_member(i);
  }

  // Populate the d-cells id spaces.

  for(int i = 0; i <= max_db(); ++i)
  {
    pod_index_type lspace_id = xinterval.d_cells_space_id(i);

    if(is_valid(lspace_id))
    {
      pod_index_type lbegin = member_id_spaces(false).hub_begin(lspace_id);
      pod_index_type lend = lbegin + member_id_spaces(false).ct(lspace_id) - 1;

      reinterpret_cast<interval_index_space_handle&>
	(d_cells_id_space(i)).push_interval(lbegin, lend);
    }
  }

  // Populate the cells id space.

  reinterpret_cast<interval_index_space_handle&>
    (cells().id_space()).push_interval(xinterval.cells_begin(),
				       xinterval.cells_end());

  // Insert the block vertices, if any, in the block vertices subposet.

  scattered_insertion_index_space_handle& lvertices_id_space = block_vertices().id_space();

  index_space_iterator& lvertex_itr =
    member_id_spaces(false).get_id_space_iterator(xinterval.block_vertices_space_id());
  while(!lvertex_itr.is_done())
  {
    block_vertices().insert_member(lvertex_itr.hub_pod());
    lvertices_id_space.push_back(lvertex_itr.hub_pod());
    lvertex_itr.next();
  }
  member_id_spaces(false).release_id_space_iterator(lvertex_itr);

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::base_space_poset::
initialize_standard_subposets(const std::string& xname)
{
  // Preconditions:

  require(poset_path::is_valid_name(xname));
  require(state_is_read_write_accessible());

  // Body:

  // Create the usual subposets

  refinable_poset::initialize_standard_subposets(xname);

  string lsp_name;

  // Make the blocks subposet.

  _blocks.new_state(this);
  lsp_name = blocks_name();
  _blocks.put_name(lsp_name, true, false);
  _blocks.new_id_space("array_index_space_state");
  _blocks.put_is_persistent(false);

  // Make the block vertices subposet.

  _block_vertices.new_state(this);
  lsp_name = block_vertices_name();
  _block_vertices.put_name(lsp_name, true, false);
  _block_vertices.new_id_space("array_index_space_state");
  _block_vertices.put_is_persistent(false);

  // Make the d-cells subposets.

  int lmax_db = max_db();
  _d_cells.reserve(lmax_db + 1);
  _d_cells_id_spaces.reserve(lmax_db + 1);

  for(int i=0; i<=lmax_db; i++)
  {
    _d_cells[i].new_state(this);
    lsp_name = d_cells_name(i, lmax_db);
    _d_cells[i].put_name(lsp_name, true, false);
    _d_cells[i].new_id_space("interval_index_space_state");
    _d_cells_id_spaces[i] = &_d_cells[i].id_space();
    _d_cells[i].put_is_persistent(false);
  }

  // Make the cells subposet.

  _cells.new_state(this);
  lsp_name = cells_name();
  _cells.put_name(lsp_name, true, false);
  _cells.new_id_space("interval_index_space_state");
  _cells.put_is_persistent(false);

  // Version subposets are not standard subposets;
  // don't change the standard subposet count.

  //   // All the subposets are standard.

  //   put_standard_subposet_ct(subposet_ct());

  // Postconditions:

  ensure(state_obj()->powerset()->invariant());
  ensure(jims().is_attached());
  ensure(whole().is_attached());
  ensure(resident().is_attached() && resident().index() == RESIDENT_INDEX);
  //   ensure(has_standard_subposet_ct());
  ensure(includes_subposet(blocks_name()));
  ensure(includes_subposet(block_vertices_name()));
  ensure_for_all(i, 0, max_db(), includes_subposet(d_cells_name(i, max_db())));
  ensure(includes_subposet("__cells"));

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// TABLE DOFS FACET
// ===========================================================

// PUBLIC FUNCTIONS

int
fiber_bundle::base_space_poset::
max_db() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = table_dof_tuple()->max_db;

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::base_space_poset::
put_max_db(int xmax_db)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  table_dof_tuple()->max_db = xmax_db;

  // Postconditions:

  ensure(max_db() == xmax_db);

  // Exit:

  return;
}

void
fiber_bundle::base_space_poset::
update_max_db(int xmax_db)
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_max_db = max_db());

  if(xmax_db > max_db())
  {
    table_dof_tuple()->max_db = xmax_db;
  }

  // Postconditions:

  ensure(max_db() == ((xmax_db > old_max_db) ? xmax_db : old_max_db));

  // Exit:

  return;
}


const fiber_bundle::base_space_poset::table_dof_tuple_type*
fiber_bundle::base_space_poset::
table_dof_tuple() const
{
  const table_dof_tuple_type* result;

  // Preconditions:


  // Body:

  result = reinterpret_cast<const table_dof_tuple_type*>(table_dof_map().dof_tuple());

  // Postconditions:


  // Exit:

  return result;
}

fiber_bundle::base_space_poset::table_dof_tuple_type*
fiber_bundle::base_space_poset::
table_dof_tuple()
{
  table_dof_tuple_type* result;

  // Preconditions:


  // Body:

  result = reinterpret_cast<table_dof_tuple_type*>(table_dof_map().dof_tuple());

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ROW DOFS FACET
// ===========================================================

// PUBLIC FUNCTIONS

int
fiber_bundle::base_space_poset::
db(pod_index_type xhub_id) const
{
  int result = -1;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xhub_id, false));

  // Body:

  if(is_jim(xhub_id, false))
  {
    // Dimension is a dof.

    result = member_dof_tuple(xhub_id)->db;
  }
  else
  {
    // Dimension is max dimension of maximal jims in downset.

    index_space_iterator& litr = get_cover_id_space_iterator(LOWER, xhub_id);
    while(!litr.is_done())
    {
      int lmbr_dim = db(litr.hub_pod());
      result = lmbr_dim > result ? lmbr_dim : result;
      litr.next();
    }
    release_cover_id_space_iterator(litr);
  }

  // Postconditions:

  ensure(result >= -1);
  ensure( (result == -1) == is_jem(xhub_id, bottom().index().pod()) );

  // Exit

  return result;
}

int
fiber_bundle::base_space_poset::
db(const scoped_index& xid) const
{
  int result = -1;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xid, false));

  // Body:

  result = db(xid.hub_pod());

  // Postconditions:

  ensure(result >= -1);
  ensure( (result == -1) == is_jem(xid, bottom().index()) );

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_poset::
type_id(pod_index_type xhub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xhub_id, false));

  // Body:

  pod_index_type result = member_dof_tuple(xhub_id)->type_id;

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_poset::
type_id(const scoped_index& xid) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xid, false));

  // Body:

  return type_id(xid.hub_pod());
}

std::string
fiber_bundle::base_space_poset::
type_name(pod_index_type xhub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xhub_id, false));

  // Body:

  string result(member_dof_tuple(xhub_id)->type_name);

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

std::string
fiber_bundle::base_space_poset::
type_name(const scoped_index& xid) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xid, false));

  // Body:

  string result = type_name(xid.hub_pod());

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

int
fiber_bundle::base_space_poset::
refinement_depth(pod_index_type xhub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xhub_id, false));

  // Body:

  int result = member_dof_tuple(xhub_id)->refinement_depth;

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::base_space_poset::
refinement_depth(const scoped_index& xid) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(xid, false));

  // Body:

  return refinement_depth(xid.hub_pod());
}

void
fiber_bundle::base_space_poset::
put_refinement_depth(pod_index_type xhub_id, int xdepth)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim(xhub_id, false));

  // Body:

  member_dof_tuple(xhub_id)->refinement_depth = xdepth;

  // Postconditions:

  ensure(refinement_depth(xhub_id) == xdepth);

  // Exit:

  return;
}

void
fiber_bundle::base_space_poset::
put_refinement_depth(const scoped_index& xid, int xdepth)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim(xid, false));

  // Body:

  put_refinement_depth(xid.hub_pod(), xdepth);

  // Postconditions:

  ensure(refinement_depth(xid) == xdepth);

  // Exit:

  return;
}

fiber_bundle::base_space_poset::row_dof_tuple_type*
fiber_bundle::base_space_poset::
member_dof_tuple(pod_index_type xhub_id, bool xrequire_write_access) const
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(contains_member(xhub_id));
  require(is_jim(xhub_id, false));

  // Body:

  result = row_dof_tuple(member_dof_tuple_id(xhub_id, false),
			 xrequire_write_access);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

fiber_bundle::base_space_poset::row_dof_tuple_type*
fiber_bundle::base_space_poset::
member_dof_tuple(const scoped_index& xid, bool xrequire_write_access) const
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(contains_member(xid));
  require(is_jim(xid, false));

  // Body:

  result = member_dof_tuple(xid.hub_pod(), xrequire_write_access);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

fiber_bundle::base_space_poset::row_dof_tuple_type*
fiber_bundle::base_space_poset::
row_dof_tuple(pod_index_type xtuple_hub_id, bool xrequire_write_access) const
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(contains_row_dof_tuple(xtuple_hub_id));

  // Body:

  poset_dof_map& ldof_map = row_dof_map(xtuple_hub_id, xrequire_write_access);
  result = reinterpret_cast<row_dof_tuple_type*>(ldof_map.dof_tuple());

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

fiber_bundle::base_space_poset::row_dof_tuple_type*
fiber_bundle::base_space_poset::
row_dof_tuple(const scoped_index& xtuple_id, bool xrequire_write_access) const
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() :
          state_is_read_accessible());
  require(contains_row_dof_tuple(xtuple_id));

  // Body:

  result = row_dof_tuple(xtuple_id.hub_pod(), xrequire_write_access);

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

const sheaf::scoped_index&
fiber_bundle::base_space_poset::
new_row_dof_map(const std::string& xprototype_name)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(name_space()->member_poset(prototypes_poset_name()).state_is_auto_read_accessible(true));
  require(name_space()->contains_poset_member(prototypes_poset_name()+"/"+xprototype_name, false));

  // Body:

  define_old_variable(int old_row_dof_tuple_ct = row_dof_tuple_ct());

  // Create the dof map and set dofs to defaults.

  const scoped_index& result = new_row_dof_map();
  row_dof_tuple_type* ltuple = row_dof_tuple(result.pod(), true);

  // Get the prototype.

  poset_path lproto_path(prototypes_poset_name(), xprototype_name);
  base_space_member lproto(name_space(), lproto_path, false);
  lproto.get_read_access();
  row_dof_tuple_type* lproto_tuple = lproto.row_dof_tuple(false);

  // Copy its dofs.

  ltuple->db                   = lproto_tuple->db;
  ltuple->type_id              = lproto_tuple->type_id;
  ltuple->type_name            = strdup(lproto_tuple->type_name);
  ltuple->refinement_depth     = lproto_tuple->refinement_depth;
  ltuple->local_cell_type_id   = lproto_tuple->local_cell_type_id;
  ltuple->local_cell_type_name = strdup(lproto_tuple->local_cell_type_name);
  ltuple->size                 = lproto_tuple->size;
  ltuple->i_size               = lproto_tuple->i_size;
  ltuple->j_size               = lproto_tuple->j_size;
  ltuple->k_size               = lproto_tuple->k_size;
  
  // Release the prototype.

  lproto.release_access();

  // Postconditions:

  ensure(row_dof_tuple_ct() == old_row_dof_tuple_ct+1);
  ensure(contains_row_dof_tuple(result));

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
is_explicit_member(pod_index_type xmbr_id) const
{
  // Preconditions::

  // Body:

  bool result = crg().contains_explicit_member(xmbr_id);

  // Postconditions:

  // Exit:

  return result;
}

bool
fiber_bundle::base_space_poset::
is_block_member(pod_index_type xmbr_id) const
{
  // Preconditions::

  // Body:

  implicit_crg_interval* linterval = crg().implicit_member(xmbr_id);

  bool result = (linterval != 0) && linterval->is_interval_member(xmbr_id);

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::base_space_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const base_space_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::base_space_poset::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(refinable_poset::invariant());

    /// @todo finish base_space_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

fiber_bundle::base_space_poset*
fiber_bundle::base_space_poset::
clone() const
{
  base_space_poset* result;

  // Preconditions:

  // Body:

  result = new base_space_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

// PRIVATE FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::deep_size(const base_space_poset& xp, bool xinclude_shallow, size_t xresults[4])
{
  size_t result;

  // Preconditions:

  require(xp.state_is_read_accessible());

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  // Add contributions of the parent class.

  const poset_state_handle& lxp =
    reinterpret_cast<const poset_state_handle&>(xp);

  result += deep_size(lxp, false, xresults);

  // Add contributions of _d_cells_id_spaces.

  /// @hack Should have an deep size policy for computing the size
  /// of the block without calling deep size on the pointers.

  for(pod_index_type i = 0; i < xp._d_cells_id_spaces.ub(); ++i)
  {
    result += sizeof(xp._d_cells_id_spaces[i]);
  }

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
