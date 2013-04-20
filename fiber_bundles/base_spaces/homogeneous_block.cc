

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class homogeneous_block.

#include "homogeneous_block.h"

#include "assert_contract.h"
#include "array_index_space_state.h"
#include "arg_list.h"
#include "base_space_member_prototype.h"
#include "homogeneous_block_crg_interval.h"
#include "index_space_handle.h"
#include "index_space_iterator.h"
#include "namespace_poset.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "section_space_schema_member.h"
#include "tern.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::homogeneous_block::
homogeneous_block()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}

fiber_bundle::homogeneous_block::
~homogeneous_block()
{

  // Preconditions:

  // Body:

  // Exit

  return;
}

const sheaf::hub_index_space_handle&
fiber_bundle::homogeneous_block::
hub_id_space() const
{
  // Preconditions:

  /// @todo Need to export the preconditions in the implicit interval object.

  // Body:

  const hub_index_space_handle& result = _interval->hub_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
local_id_space() const
{
  // Preconditions:

  /// @todo Need to export the preconditions in the implicit interval object.

  // Body:

  const index_space_handle& result = _interval->local_id_space();

  // Postconditions:

  ensure(result.is_attached());

  // Exit:

  return result;
}

const sheaf::pod_index_type&
fiber_bundle::homogeneous_block::
local_cell_type_id() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Type_id is member_id member of prototype_id.

  homogeneous_block* cthis = const_cast<homogeneous_block*>(this);
  const pod_index_type& result = cthis->row_dof_tuple()->local_cell_type_id;

  // Postconditions:


  // Exit

  return result;
}

const char*
fiber_bundle::homogeneous_block::
local_cell_type_name() const
{

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  homogeneous_block* cthis = const_cast<homogeneous_block*>(this);
  const char* result = cthis->row_dof_tuple()->local_cell_type_name;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::size_type&
fiber_bundle::homogeneous_block::
size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  homogeneous_block* cthis = const_cast<homogeneous_block*>(this);
  const size_type& result = cthis->row_dof_tuple()->size;

  // Postconditions:

  // Exit

  return result;
}

sheaf::array_poset_dof_map*
fiber_bundle::homogeneous_block::
new_row_dof_map(const poset* xhost,
                const string& xprototype_name,
                const string& xlocal_cell_name,
                size_type xsize)
{
  // Preconditions:

  require(xhost->state_is_read_accessible());
  require(xhost->name_space()->member_poset(prototypes_poset_name(), true).state_is_read_accessible());
  require(!xprototype_name.empty());
  require(xhost->name_space()->member_poset(prototypes_poset_name(), true).contains_member(xprototype_name));
  require(!xlocal_cell_name.empty());
  require(xhost->name_space()->member_poset(prototypes_poset_name(), true).contains_member(xlocal_cell_name));


  // Body:

  // Create the map and initialize type_id and type_name dofs from prototype.

  array_poset_dof_map* result = new_row_dof_map(xhost, xprototype_name);

  row_dof_tuple_type& ltuple =
    *reinterpret_cast<row_dof_tuple_type*>(result->dof_tuple());

  // Set local cell type id and name.

  poset_path local_proto_path(prototypes_poset_name(), xlocal_cell_name);
  base_space_member_prototype local_proto(xhost->name_space(), local_proto_path, true);

  ltuple.local_cell_type_id = local_proto.type_id();
  ltuple.local_cell_type_name = strdup(local_proto.type_name());

  // Dimension of block is same as dimension of local cell.

  ltuple.db = local_proto.db();

  local_proto.detach_from_state();

  // Set the size.

  ltuple.size = xsize;

  // Postconditions:


  // Exit:

  return result;
}

const sheaf::scoped_index&
fiber_bundle::homogeneous_block::
new_row_dof_map(poset_state_handle& xhost,
                const string& xprototype_name,
                const string& xlocal_cell_name,
                size_type xsize,
                bool xauto_access)
{
  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));
  require(xhost.name_space()->member_poset(prototypes_poset_name(), true).state_is_auto_read_accessible(xauto_access));
  require(!xprototype_name.empty());
  require(xhost.name_space()->member_poset(prototypes_poset_name(), true).contains_member(xprototype_name));
  require(!xlocal_cell_name.empty());
  require(xhost.name_space()->member_poset(prototypes_poset_name(), true).contains_member(xlocal_cell_name));


  // Body:

  if(xauto_access)
  {
    xhost.get_read_write_access(true);
    xhost.name_space()->get_read_access();
    xhost.name_space()->member_poset(prototypes_poset_name(), false).get_read_access();
  }

  // Create the dof map and set dofs to defaults.

  const scoped_index& result = base_space_member::new_row_dof_map(xhost, xprototype_name, false);
  row_dof_tuple_type* ltuple =
    reinterpret_cast<row_dof_tuple_type*>(xhost.row_dof_map(result, true).dof_tuple());

  // Get the local cell prototype

  poset_path local_proto_path(prototypes_poset_name(), xlocal_cell_name);
  base_space_member_prototype local_proto(xhost.name_space(), local_proto_path, false);

  // Copy its dofs;
  // dimension of block same as local cell.

  ltuple->db                   = local_proto.db();
  ltuple->local_cell_type_id   = local_proto.type_id();
  ltuple->local_cell_type_name = strdup(local_proto.type_name());
  ltuple->size                 = xsize;

  // Relase the prototype.

  local_proto.detach_from_state();

  if(xauto_access)
  {
    xhost.name_space()->member_poset(prototypes_poset_name(), false).release_access();
    xhost.name_space()->release_access();
    xhost.release_access();
  }

  // Postconditions:


  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

void
fiber_bundle::homogeneous_block::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(unexecutable(data members created));

  // Body:

  // Have just attached to a new or different member in the same host.
  // Attach the handle data members for the different member.

  _interval = 
    dynamic_cast<homogeneous_block_crg_interval*>(crg()->implicit_member(_index));

  // Postconditions:

  ensure(!is_restricted());

  // Exit

  return;
}

const fiber_bundle::homogeneous_block_crg_interval&
fiber_bundle::homogeneous_block::
interval() const
{
  return *_interval;
}

void
fiber_bundle::homogeneous_block::
put_size(const size_type& xsize)
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  row_dof_tuple()->size = xsize;

  // Postconditions:

  ensure(size() == xsize);

  // Exit

  return;
}

// PRIVATE DATA MEMBERS


// ===========================================================
// ZONE ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::homogeneous_block::
contains_zone_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  bool result = lhost->contains_zone_id_space(_index, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_zone_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_zone_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_handle& result = lhost->get_zone_id_space(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_zone_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_zone_id_space(xid_space, xauto_access);

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_zone_id_space_iterator(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_zone_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_iterator& result = lhost->get_zone_id_space_iterator(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_zone_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_zone_id_space_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTEX ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::homogeneous_block::
contains_vertex_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  bool result = lhost->contains_vertex_id_space(_index, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_vertex_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_vertex_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_handle& result = lhost->get_vertex_id_space(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_vertex_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_vertex_id_space(xid_space, xauto_access);

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_vertex_id_space_iterator(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_vertex_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_iterator& result = lhost->get_vertex_id_space_iterator(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_vertex_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_vertex_id_space_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// CONNECTIVITY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::homogeneous_block::
contains_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  bool result = lhost->contains_connectivity_id_space(xzone_id, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::homogeneous_block::
contains_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));

  // Body:

  bool result = contains_connectivity_id_space(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_connectivity_id_space(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_handle& result = lhost->get_connectivity_id_space(xzone_id, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_connectivity_id_space(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  index_space_handle& result = get_connectivity_id_space(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_connectivity_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_connectivity_id_space(xid_space, xauto_access);
  
  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_connectivity_id_space_iterator(pod_index_type xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_iterator& result = lhost->get_connectivity_id_space_iterator(xzone_id, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_connectivity_id_space_iterator(const scoped_index& xzone_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xzone_id));
  require(contains_connectivity_id_space(xzone_id, xauto_access));

  // Body:

  index_space_iterator& result = get_connectivity_id_space_iterator(xzone_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_connectivity_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_connectivity_id_space_iterator(xitr, xauto_access);

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
fiber_bundle::homogeneous_block::
contains_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  bool result = lhost->contains_adjacency_id_space(xvertex_id, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::homogeneous_block::
contains_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));

  // Body:

  bool result = contains_adjacency_id_space(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_adjacency_id_space(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_handle& result = lhost->get_adjacency_id_space(xvertex_id, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::homogeneous_block::
get_adjacency_id_space(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  index_space_handle& result = get_adjacency_id_space(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_adjacency_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_adjacency_id_space(xid_space, xauto_access);
  
  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_adjacency_id_space_iterator(pod_index_type xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_iterator& result = lhost->get_adjacency_id_space_iterator(xvertex_id, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

sheaf::index_space_iterator&
fiber_bundle::homogeneous_block::
get_adjacency_id_space_iterator(const scoped_index& xvertex_id, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(local_id_space().contains_hub(xvertex_id));
  require(contains_adjacency_id_space(xvertex_id, xauto_access));

  // Body:

  index_space_iterator& result = get_adjacency_id_space_iterator(xvertex_id.hub_pod(), xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::homogeneous_block::
release_adjacency_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_adjacency_id_space_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::homogeneous_block::
standard_schema_path()
{

  // Preconditions:

  // Body:

  static const poset_path result(base_space_member::standard_schema_poset_name(),
                                 "homogeneous_block_schema");

  // Postconditions:

  // Exit

  return result;
}


const sheaf::poset_path&
fiber_bundle::homogeneous_block::
schema_path() const
{
  // Preconditions:

  // Body:

  const poset_path& result = standard_schema_path();

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::homogeneous_block::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs = "local_cell_type_id INT false";
  ldof_specs       += " local_cell_type_name C_STRING false";
  ldof_specs       += " size SIZE_TYPE false";


  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              base_space_member::standard_schema_path(),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::homogeneous_block::
invariant() const
{
  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  invariance(total_poset_member::invariant());

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Invariants for this class:

    invariance(state_is_read_accessible() ? is_jim(false) : true);
    invariance(unexecutable("db() == local cell db"));


    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}


bool
fiber_bundle::homogeneous_block::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const homogeneous_block*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


fiber_bundle::homogeneous_block&
fiber_bundle::homogeneous_block::
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

fiber_bundle::homogeneous_block&
fiber_bundle::homogeneous_block::
operator=(const homogeneous_block& xother)
{
  
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body

  not_implemented();
  
  // Postconditions

  ensure(invariant());

  // Exit

  return *this;
  
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

