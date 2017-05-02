
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
/// Implementation for class zone_nodes_block

#include "SheafSystem/zone_nodes_block.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/arg_list.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/block_connectivity.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/wsv_block.h"


using namespace fiber_bundle; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT


// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::zone_nodes_block::
static_prototype_path()
{
  // Preconditions:

  // Body:

  static const poset_path
  STATIC_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(), "zone_nodes_block");

  const poset_path& result = STATIC_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "zone_nodes_block");

  // Exit

  return result;
}

fiber_bundle::zone_nodes_block::host_type&
fiber_bundle::zone_nodes_block::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering zone_nodes_block::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));  

  require(xmax_db >= 0);

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, xmax_db, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == xmax_db);

  // Exit:

  // cout << "Leaving zone_nodes_block::new_host." << endl;
  return result;
}

fiber_bundle::zone_nodes_block::host_type&
fiber_bundle::zone_nodes_block::
standard_host(namespace_type& xns, const poset_path& xhost_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering zone_nodes_block::standard_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(poset_path::is_valid_name(xhost_path.poset_name()));
  require(xns.path_is_auto_read_write_available<host_type>(xhost_path.poset_name(), xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xmax_db >= 0);

  // Body:

  host_type* result_ptr;
  if(xns.contains_path(xhost_path.poset_name(), xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(xhost_path, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, xhost_path, standard_schema_path(), xmax_db, xauto_access);
  }
  
  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.max_db() == xmax_db);
  
  // Exit:

  // cout << "Leaving zone_nodes_block::standard_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ZONE_NODES_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::zone_nodes_block::
zone_nodes_block()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const abstract_poset_member& xother, bool xnew_jem)
{
  // Preconditions:

  require(xnew_jem ? xother.is_attached() : true);

  // Body:

  if(xnew_jem)
  {
    new_jem_state(const_cast<abstract_poset_member*>(&xother), true, true);
  }
  else
  {
    attach_to_state(&xother);
  }

  // Postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::zone_nodes_block::
~zone_nodes_block()
{
  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::zone_nodes_block::
zone_nodes_block(base_space_poset& xhost, const block_connectivity& xconn, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(xhost, xconn, xauto_access)));

  // Body:

  new_state(xhost, xconn, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xconn, xauto_access)));

  // Exit

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::zone_nodes_block::
zone_nodes_block(const base_space_poset& xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(&xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const base_space_poset& xhost, const scoped_index& xid)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(&xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const base_space_poset& xhost, const std::string& xname)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(&xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const namespace_poset* xnamespace,
                 const poset_path& xpath,
                 bool xauto_access)
{
  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xpath, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const namespace_poset* xnamespace,
                 pod_index_type xposet_id,
                 pod_index_type xmember_id)
{
  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_id, xmember_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::zone_nodes_block::
zone_nodes_block(const namespace_poset* xnamespace,
                 const scoped_index& xposet_id,
                 const scoped_index& xmember_id)
{
  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_id.hub_pod(), xmember_id.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

void
fiber_bundle::zone_nodes_block::
new_state(const block_connectivity& xconn, bool xauto_access)
{
  // Preconditions:

  require(is_attached());
  require(dynamic_cast<base_space_poset*>(host()) != 0);
  require(precondition_of(new_state(*host(), xconn, xauto_access)));

  // Body:

  base_space_poset& lhost = dynamic_cast<base_space_poset&>(*host());

  new_state(lhost, xconn, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(*host(), xconn, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::zone_nodes_block::
new_state(base_space_poset& xhost, const block_connectivity& xconn, bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost.is_attached() : xhost.in_jim_edit_mode());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost.begin_jim_edit_mode(true);
    xhost.name_space()->get_read_access();
    xhost.name_space()->member_poset(prototypes_poset_name(), false).get_read_access();
  }

  require(namespace_is_ancestor_of(xhost.name_space()));
  require(xhost.schema().row_conforms_to(standard_schema_path()));

  // Body:

  // Get the size for the interval.

  size_type lsize;
  zone_nodes_block_crg_interval::get_size(xconn, lsize);

  // Get the dof tuple_ids.

  block<pod_index_type> ldof_tuple_ids;
  zone_nodes_block_crg_interval::get_dof_tuple_ids(xhost, xconn, ldof_tuple_ids);

  // Get the private data for the interval

  block<pod_index_type> ldata;
  zone_nodes_block_crg_interval::get_private_data(xconn, ldata);

  // Create the implicit crg interval for the block.

  pod_index_type lindex =
    xhost.new_member_interval("zone_nodes_block_crg_interval", lsize, ldof_tuple_ids, ldata);

  // Attach this handle to it.

  attach_to_state(&xhost, lindex);

  // Block is linked to bottom via implicit lower cover of vertices,
  // but not linked to top; link it now.

  xhost.top().create_cover_link(this);

  // Postconditions:

  ensure(size() == xconn.element_ct());
  ensure(is_attached());
  /// @todo finish postconditions.

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost.name_space()->member_poset(prototypes_poset_name(), false).release_access();
    xhost.name_space()->release_access();

    // End jim edit mode without ensure_lattice_invariant;
    // the check is unnecessary and expensive.

    xhost.end_jim_edit_mode(false, true);
  }

  // Exit

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// VERTEX CLIENT ID SPACE FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::zone_nodes_block::
contains_vertex_client_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  bool result = lhost->contains_vertex_client_id_space(_index, xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

sheaf::index_space_handle&
fiber_bundle::zone_nodes_block::
get_vertex_client_id_space(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_vertex_client_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_handle& result = lhost->get_vertex_client_id_space(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space(result));

  // Exit:

  return result;
}

void
fiber_bundle::zone_nodes_block::
release_vertex_client_id_space(index_space_handle& xid_space, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space(xid_space));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_vertex_client_id_space(xid_space, xauto_access);

  // Postconditions:

  ensure(!xid_space.is_attached());

  // Exit:

  return;
}

sheaf::index_space_iterator&
fiber_bundle::zone_nodes_block::
get_vertex_client_id_space_iterator(bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(contains_vertex_client_id_space(xauto_access));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  index_space_iterator& result = lhost->get_vertex_client_id_space_iterator(_index, xauto_access);

  // Postconditions:

  ensure(result.is_attached());
  ensure(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(result));

  // Exit:

  return result;
}

void
fiber_bundle::zone_nodes_block::
release_vertex_client_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  require(host()->member_id_spaces(xauto_access).allocated_id_space_iterator(xitr));

  // Body:

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = reinterpret_cast<base_space_poset*>(host());

  lhost->release_vertex_client_id_space_iterator(xitr, xauto_access);

  // Postconditions:

  ensure(!xitr.is_attached());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const fiber_bundle::zone_nodes_block_crg_interval&
fiber_bundle::zone_nodes_block::
interval() const
{
  return *reinterpret_cast<const zone_nodes_block_crg_interval*>(_interval);
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

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

fiber_bundle::zone_nodes_block&
fiber_bundle::zone_nodes_block::
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

fiber_bundle::zone_nodes_block&
fiber_bundle::zone_nodes_block::
operator=(const zone_nodes_block& xother)
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


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::zone_nodes_block::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const zone_nodes_block*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::zone_nodes_block*
fiber_bundle::zone_nodes_block::
clone() const
{
  // Preconditions:

  // Body:

  // create new handle of the current class.

  zone_nodes_block *result = new zone_nodes_block();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

fiber_bundle::zone_nodes_block*
fiber_bundle::zone_nodes_block::
clone(bool xnew_state, bool xauto_access) const
{
  return reinterpret_cast<zone_nodes_block*>(homogeneous_block::clone(xnew_state, xauto_access));
}

bool
fiber_bundle::zone_nodes_block::
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

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS

