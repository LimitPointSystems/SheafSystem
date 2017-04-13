
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
/// Implementation for class point_block_1d

#include "SheafSystem/point_block_1d.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/arg_list.h"
//#include "SheafSystem/base_space_member_prototype.h"
#include "SheafSystem/chart_point_3d.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/namespace_poset.h"
#include "SheafSystem/point_block_crg_interval.h"
#include "SheafSystem/poset_path.h"
#include "SheafSystem/preorder_iterator.h"
#include "SheafSystem/tern.h"
#include "SheafSystem/wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::point_block_1d::
static_prototype_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  result(base_space_member::prototypes_poset_name(), "point_block_1d");

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "point_block_1d");

  // Exit

  return result;
}

fiber_bundle::point_block_1d::host_type&
fiber_bundle::point_block_1d::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering point_block_1d::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));  

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 0, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == 0);

  // Exit:

  // cout << "Leaving point_block_1d::new_host." << endl;
  return result;
}

fiber_bundle::point_block_1d::host_type&
fiber_bundle::point_block_1d::
standard_host(namespace_type& xns, const poset_path& xhost_path, bool xauto_access)
{
  // cout << endl << "Entering point_block_1d::standard_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(poset_path::is_valid_name(xhost_path.poset_name()));
  require(xns.path_is_auto_read_write_available<host_type>(xhost_path.poset_name(), xauto_access));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));

  // Body:

  host_type* result_ptr;
  if(xns.contains_path(xhost_path.poset_name(), xauto_access))
  {
    result_ptr = &xns.member_poset<host_type>(xhost_path, xauto_access);
  }
  else
  {
    result_ptr = &new_host(xns, xhost_path, standard_schema_path(), xauto_access);
  }
  
  host_type& result = *result_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.max_db() == 0);
  
  // Exit:

  // cout << "Leaving point_block_1d::standard_host." << endl;
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// POINT_BLOCK_1D FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::point_block_1d::
point_block_1d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

fiber_bundle::point_block_1d::
point_block_1d(const abstract_poset_member& xother, bool xnew_jem)
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

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == xother.is_attached() );
}

fiber_bundle::point_block_1d::
~point_block_1d()
{
  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS:

fiber_bundle::point_block_1d::
point_block_1d(poset* xhost, const size_type& xi_size, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS:

fiber_bundle::point_block_1d::
point_block_1d(poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::point_block_1d::
point_block_1d(poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}

fiber_bundle::point_block_1d::
point_block_1d(const poset* xhost, const std::string& xname)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::point_block_1d::
point_block_1d(const namespace_poset* xnamespace,
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

fiber_bundle::point_block_1d::
point_block_1d(const namespace_poset* xnamespace,
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

fiber_bundle::point_block_1d::
point_block_1d(const namespace_poset* xnamespace,
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

// EXISTING HANDLE, NEW STATE "CONSTRUCTORS":

void
fiber_bundle::point_block_1d::
new_state(const size_type& xi_size, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xi_size, xauto_access)));

  // Body:

  new_state(host(), xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xi_size, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::point_block_1d::
new_state(poset* xhost, const size_type& xi_size, bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access || xhost->name_space()->state_is_read_accessible());
  require(xhost->name_space()->contains_poset_member(static_prototype_path(), true));
  require(xauto_access || xhost->name_space()->member_poset(prototypes_poset_name(), true).state_is_read_accessible());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xhost->name_space()->get_read_access();
    xhost->name_space()->member_poset(prototypes_poset_name(), false).get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));

  /// @hack a step in the direction of redeclaring host to base_space_poset

  require(dynamic_cast<base_space_poset*>(xhost) != 0);

  require(xi_size > 0);

  // Body:

  // Get the size for the interval.

  size_type lsize;
  point_block_crg_interval::get_size(xi_size, lsize);

  // Get the dof tuple_ids.

  block<pod_index_type> ldof_tuple_ids;
  point_block_crg_interval::get_dof_tuple_ids(*xhost, xi_size, ldof_tuple_ids);

  // Get the private data for the interval

  block<pod_index_type> ldata;
  point_block_crg_interval::get_private_data(xi_size, ldata);

  // Create the implicit crg interval for the block.

  pod_index_type lindex =
    xhost->new_member_interval("point_block_crg_interval", lsize, ldof_tuple_ids, ldata);

  // Attach this handle to it.

  attach_to_state(xhost, lindex);

  // $$SCRIBBLE dmb:
  // Update max_db in host

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(xhost);
  lhost->update_max_db(db());

  // Block is linked to bottom via implicit lower cover of vertices,
  // but not linked to top; link it now.

  lhost->top().create_cover_link(this);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(is_attached());
  ensure(db() == 0);
  ensure(prototype_path() == static_prototype_path());
  ensure(local_cell_type_name() ==
         static_local_cell_prototype_path().member_name());
  ensure(i_size() == xi_size);

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->name_space()->member_poset(prototypes_poset_name(), false).release_access();
    xhost->name_space()->release_access();

    // End jim edit mode without ensure_lattice_invariant;
    // the check is unnecessary and expensive.

    xhost->end_jim_edit_mode(false, true);
  }

  // Exit:

  return;
}

// FEATURES:

const sheaf::size_type&
fiber_bundle::point_block_1d::
i_size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  point_block_1d* cthis = const_cast<point_block_1d*>(this);
  const size_type& result = cthis->row_dof_tuple()->i_size;

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::point_block_1d::
put_i_size(const size_type& xi_size)
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  row_dof_tuple()->i_size = xi_size;

  // Postconditions:

  ensure(i_size() == xi_size);

  // Exit

  return;
}

// PROTECTED DATA MEMBERS

sheaf::scoped_index
fiber_bundle::point_block_1d::
new_row_dof_map(poset_state_handle& xhost, size_type xi_size, bool xauto_access)
{
  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));

  require(xauto_access || xhost.name_space()->poset_state_is_read_accessible(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_local_cell_prototype_path()));

  require(xi_size > 0);

  // Body:

  if(xauto_access)
  {
    xhost.get_read_write_access(true);
    xhost.name_space()->get_read_access();
    xhost.name_space()->member_poset(prototypes_poset_name(), false).get_read_access();
  }

  // Calculate the number of cells.

  size_type lsize = xi_size;

  // Create the map and initialize inherited dofs.

  scoped_index result =
    new_row_dof_map(xhost,
		    static_prototype_path().member_name(),
		    static_local_cell_prototype_path().member_name(),
		    lsize,
		    false);

  row_dof_tuple_type* ltuple =
    reinterpret_cast<row_dof_tuple_type*>(xhost.row_dof_map(result, true).dof_tuple());

  // Set the size in the i direction.

  ltuple->i_size = xi_size;

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

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::point_block_1d::
static_local_cell_prototype_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  result(base_space_member::prototypes_poset_name(), "point");

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "point");

  // Exit

  return result;
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

fiber_bundle::point_block_1d*
fiber_bundle::point_block_1d::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  point_block_1d *result = new point_block_1d();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

bool
fiber_bundle::point_block_1d::
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
    invariance(state_is_read_accessible() ? size() == i_size() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

bool
fiber_bundle::point_block_1d::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const point_block_1d*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::point_block_1d&
fiber_bundle::point_block_1d::
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

fiber_bundle::point_block_1d&
fiber_bundle::point_block_1d::
operator=(const point_block_1d& xother)
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


