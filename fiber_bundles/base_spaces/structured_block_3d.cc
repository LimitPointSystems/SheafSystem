
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
/// Implementation for class structured_block_3d.

#include "SheafSystem/structured_block_3d.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/arg_list.h"
//#include "SheafSystem/base_space_member_prototype.h"
#include "SheafSystem/chart_point_3d.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/namespace_poset.h"
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
fiber_bundle::structured_block_3d::
static_prototype_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  STATIC_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(), "structured_block_3d");

  const poset_path& result = STATIC_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "structured_block_3d");

  // Exit

  return result;
}

fiber_bundle::structured_block_3d::host_type&
fiber_bundle::structured_block_3d::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering structured_block_3d::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));  

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 3, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == 3);

  // Exit:

  // cout << "Leaving structured_block_3d::new_host." << endl;
  return result;
}

fiber_bundle::structured_block_3d::host_type&
fiber_bundle::structured_block_3d::
standard_host(namespace_type& xns, const poset_path& xhost_path, bool xauto_access)
{
  // cout << endl << "Entering structured_block_3d::standard_host." << endl;

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

  ensure(result.max_db() == 3);
  
  // Exit:

  // cout << "Leaving structured_block_3d::standard_host." << endl;
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// STRUCTURED_BLOCK_3D FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block_3d::
structured_block_3d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}

fiber_bundle::structured_block_3d::
structured_block_3d(const abstract_poset_member& xother, bool xnew_jem)
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
    attach_to_state(const_cast<abstract_poset_member*>(&xother));
  }

  // postconditions:

  ensure(invariant());
  ensure(is_attached() == const_cast<abstract_poset_member&>(xother).is_attached() );
}

fiber_bundle::structured_block_3d::
~structured_block_3d()
{
  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS:

fiber_bundle::structured_block_3d::
structured_block_3d(poset* xhost,
                    const size_type& xi_size,
                    const size_type& xj_size,
                    const size_type& xk_size,
                    bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xi_size, xj_size, xk_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS:

fiber_bundle::structured_block_3d::
structured_block_3d(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::structured_block_3d::
structured_block_3d(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}

fiber_bundle::structured_block_3d::
structured_block_3d(const poset* xhost, const std::string& xname)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::structured_block_3d::
structured_block_3d(const namespace_poset* xnamespace,
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

fiber_bundle::structured_block_3d::
structured_block_3d(const namespace_poset* xnamespace,
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

fiber_bundle::structured_block_3d::
structured_block_3d(const namespace_poset* xnamespace,
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
fiber_bundle::structured_block_3d::
new_state(const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xi_size, xj_size, xk_size, xauto_access)));

  // Body:

  new_state(host(), xi_size, xj_size, xk_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xi_size, xj_size, xk_size, xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d::
new_state(poset* xhost,
          const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
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

  // Body:

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(xhost);

  // Get the size for the interval.

  size_type lsize;
  structured_block_3d_crg_interval::get_size(xi_size, xj_size, xk_size, lsize);

  // Get the dof tuple_ids.

  block<pod_index_type> ldof_tuple_ids;
  structured_block_3d_crg_interval::get_dof_tuple_ids(*xhost, xi_size, xj_size, xk_size, ldof_tuple_ids);

  // Get the private data for the interval

  block<pod_index_type> ldata;
  structured_block_3d_crg_interval::get_private_data(xi_size, xj_size, xk_size, ldata);

  // Create the implicit crg interval for the block.

  pod_index_type lindex =
    lhost->new_member_interval("structured_block_3d_crg_interval", lsize, ldof_tuple_ids, ldata);

  // Attach this handle to it.

  attach_to_state(lhost, lindex);

  // Block is linked to bottom via implicit lower cover of vertices,
  // but not linked to top; link it now.

  lhost->top().create_cover_link(this);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(is_attached());
  ensure(db() == 3);
  ensure(prototype_path() == static_prototype_path());
  ensure(local_cell_type_name() == static_local_cell_prototype_path().member_name());
  ensure(i_size() == xi_size);
  ensure(j_size() == xj_size);
  ensure(k_size() == xk_size);

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

sheaf::size_type
fiber_bundle::structured_block_3d::
i_size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = interval().i_size(); 

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::structured_block_3d::
j_size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = interval().j_size();

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::structured_block_3d::
k_size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  size_type result = interval().k_size();

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

sheaf::scoped_index
fiber_bundle::structured_block_3d::
new_row_dof_map(poset_state_handle& xhost,
                size_type xi_size,
                size_type xj_size,
                size_type xk_size,
                bool xauto_access)
{
  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));
  require(xauto_access || xhost.name_space()->poset_state_is_read_accessible(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_local_cell_prototype_path()));

  // Body:

  if(xauto_access)
  {
    xhost.get_read_write_access();
  }

  define_old_variable(int old_xhost_row_dof_tuple_ct = xhost.row_dof_tuple_ct());

  // Create the dof map and set dofs to defaults.

  scoped_index result = xhost.new_row_dof_map();
  row_dof_tuple_type* ltuple =
    reinterpret_cast<row_dof_tuple_type*>(xhost.row_dof_map(result, true).dof_tuple());

  // Get the block prototype.

  base_space_member lproto(xhost.name_space(), static_prototype_path(), xauto_access);

  // Get the local cell prototype.

  base_space_member local_proto(xhost.name_space(), static_local_cell_prototype_path(), xauto_access);

  // Copy the dofs from the prototypes..

  ltuple->db                   = lproto.db();
  ltuple->type_id              = lproto.type_id();
  ltuple->type_name            = strdup(lproto.type_name());
  ltuple->refinement_depth     = lproto.refinement_depth();
  ltuple->local_cell_type_id   = local_proto.type_id();
  ltuple->local_cell_type_name = strdup(local_proto.type_name());
  ltuple->size                 = xi_size*xj_size*xk_size;
  ltuple->i_size               = xi_size;
  ltuple->j_size               = xj_size;
  ltuple->k_size               = xk_size;

  // Release the prototypes.

  local_proto.detach_from_state();
  lproto.detach_from_state();

  if(xauto_access)
  {
    xhost.release_access();
  }

  // Postconditions:

  ensure(xhost.row_dof_tuple_ct() == old_xhost_row_dof_tuple_ct + 1);

  // Exit:

  return result;
}

// PRIVATE DATA MEMBERS

#define NODE_ID(i, j, k) (((i)*node_ct_y + (j))*node_ct_z + (k))


// ===========================================================
// STRUCTURED_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// LOCAL_BASE_SPACE_MEMBER FACET
// ===========================================================

// PUBLIC DATA MEMBERS

void
fiber_bundle::structured_block_3d::
refine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(xpt.chart_id() == index().pod());

  // See comment at structured_block::refine_point_pa.

  require(xpt.db() >= db());
  require(result.db() >= db());

  // Body:


  // Transform to zone-local coordinates..

  chart_point_coord_type lu_coord = xpt.local_coords()[0];
  scoped_index::pod_type lu_chart_id;
  refine_coordinate(lu_coord, lu_chart_id, i_size());

  chart_point_coord_type lv_coord = xpt.local_coords()[1];
  scoped_index::pod_type lv_chart_id;
  refine_coordinate(lv_coord, lv_chart_id, j_size());

  chart_point_coord_type lw_coord = xpt.local_coords()[2];
  scoped_index::pod_type lw_chart_id;
  refine_coordinate(lw_coord, lw_chart_id, k_size());

  // Compute chart sequence id from components.

  pod_index_type lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

  // Convert sequence id to poset id and store result.

  result.put_chart_id(_elements_id_space->hub_pod(lref_chart_id));
  result.put_local_coord(0, lu_coord);
  result.put_local_coord(1, lv_coord);
  result.put_local_coord(2, lw_coord);

  // Postconditions:

  // see $$ISSUE at structured_block::unrefine_pt_pa.
  //  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d::
refine_point_pa(const chart_point& xpt, block<chart_point_3d>& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(xpt.chart_id() == index().pod());

  // See comment at structured_block::refine_point_pa.

  require(xpt.db() >= db());

  // Body:

  // Transform to zone-local coordinates..

  chart_point_coord_type lu_coord = xpt.local_coords()[0];
  scoped_index::pod_type lu_chart_id;
  refine_coordinate(lu_coord, lu_chart_id, i_size());

  chart_point_coord_type lv_coord = xpt.local_coords()[1];
  scoped_index::pod_type lv_chart_id;
  refine_coordinate(lv_coord, lv_chart_id, j_size());

  chart_point_coord_type lw_coord = xpt.local_coords()[2];
  scoped_index::pod_type lw_chart_id;
  refine_coordinate(lw_coord, lw_chart_id, k_size());

  // Compute chart sequence id from components.

  pod_index_type lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

  // Convert sequence id to poset id and store result.

  chart_point_3d lref_pt(_elements_id_space->hub_pod(lref_chart_id),
			 lu_coord, lv_coord, lw_coord);
  result.set_ct(0);
  result.push_back(lref_pt);

  // The computation above computes a sort of "principal value"
  // chart point: if xpt is on the boundary between two zones,
  // refine_coordinate always returns the coordinate lower bound
  // in the greater zone. Since zones are closed and share boundaries,
  // a point on a boundary is really in multiple zones. To return
  // all the zones a point is in we have to figure out if it is on a
  // boundary and if so, which boundary it is on. Then we have to
  // generate the chart points for all the neighboring zones which
  // contain the boundary. To do this, we first compute a 3 bit code:
  // bit 0 = is on u boundary, bit 1 = is on v boundary, bit 2 = is on w boundary.
  // Then we test the code to generate the appropriate chart points.


  unsigned int lbit_code = 0;

  if(is_close_enough(lu_coord, -1.0)  && (lu_chart_id > 0))
  {
    // Point is on an u-boundary.

    lbit_code |= static_cast<unsigned int>(1);
  }

  if(is_close_enough(lv_coord, -1.0)  && (lv_chart_id > 0))
  {
    // Point is on a v-boundary.

    lbit_code |= static_cast<unsigned int>(2);
  }

  if(is_close_enough(lw_coord, -1.0)  && (lw_chart_id > 0))
  {
    // Point is on a w-boundary.

    lbit_code |= static_cast<unsigned int>(4);
  }


  // Consider the "principal value" chart to be in the u > 0, v > 0, w > 0 octant.

  if((lbit_code & 1) == 1)
  {
    // Point is on the u = 0 face; return the u < 0, v > 0, w > 0 zone.

    --lu_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		1.0, lv_coord, lw_coord);
    result.push_back(lref_pt);
  }

  if((lbit_code & 2) == 2)
  {
    // Point is on the v = 0 face; return the u > 0, v < 0, w > 0 zone.

    --lv_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		lu_coord, 1.0, lw_coord);
    result.push_back(lref_pt);
  }

  if((lbit_code & 3) == 3)
  {
    // Point is on the u= 0, v = 0 edge; return the u < 0, v < 0, w > 0 zone.

    --lu_chart_id;
    --lv_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		1.0, 1.0, lw_coord);
    result.push_back(lref_pt);
  }

  if((lbit_code & 4) == 4)
  {
    // Point is on the w = 0 face; return the u > 0, v > 0, w < 0 zone.

    --lw_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		lu_coord, lv_coord, 1.0);
    result.push_back(lref_pt);
  }

  if((lbit_code & 5) == 5)
  {
    // Point is on the u = 0, w = 0 edge; return the u < 0, v > 0, w < 0 zone.

    --lu_chart_id;
    --lw_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		1.0, lv_coord, 1.0);
    result.push_back(lref_pt);
  }

  if((lbit_code & 6) == 6)
  {
    // Point is on the v = 0, w = 0 edge; return the u > 0, v < 0, w < 0 zone.

    --lv_chart_id;
    --lw_chart_id;
    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id),
		lu_coord, 1.0, 1.0);
    result.push_back(lref_pt);
  }

  if((lbit_code & 7) == 7)
  {
    // Point is on the u= 0, v = 0, w = 0 vertex; return the u < 0, v < 0, w < 0 zone.

    --lu_chart_id;
    --lv_chart_id;
    --lw_chart_id;

    lref_chart_id = offset(lu_chart_id, lv_chart_id, lw_chart_id);

    // Convert sequence id to poset id and store result.

    lref_pt.put(_elements_id_space->hub_pod(lref_chart_id), 1.0, 1.0, 1.0);
    result.push_back(lref_pt);
  }



  // Postconditions:

  // see $$ISSUE at structured_block::unrefine_pt_pa.
  //  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d::
unrefine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // See comment at structured_block::unrefine_point_pa.

  require(xpt.db() >= db());
  require(result.db() >= db());

  // see $$ISSUE at structured_block::unrefine_pt_pa.
  //  require(covers(xpt.chart_id()));

  // Body:

  // Convert poset id to sequence id.

  pod_index_type lref_chart_id = _elements_id_space->pod(xpt.chart_id());

  // Assume refined local coordinates [-1, 1]; map to [0, 1] ...

  double lxcoord = (xpt.local_coord(0) + 1.0)*0.5;
  double lycoord = (xpt.local_coord(1) + 1.0)*0.5;
  double lzcoord = (xpt.local_coord(2) + 1.0)*0.5;

  // ... and then to unrefined coord [0, i_size] ...

  size_type lxy = lref_chart_id/k_size();

  lxcoord = lxcoord + lxy/j_size();
  lycoord = lycoord + lxy%j_size();
  lzcoord = lzcoord + lref_chart_id%k_size();

  // ... and then to unrefined [-1, 1]
  /// @todo Precompute 2.0/i_size() and 2.0*j_size()
  ///         and store it some where.

  lxcoord = (lxcoord/i_size())*2.0 - 1.0;
  lycoord = (lycoord/j_size())*2.0 - 1.0;
  lzcoord = (lzcoord/k_size())*2.0 - 1.0;

  // Store result.

  result.put_chart_id(index().pod());

  result.put_local_coord(0, lxcoord);
  result.put_local_coord(1, lycoord);
  result.put_local_coord(2, lzcoord);

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d::
refine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}


void
fiber_bundle::structured_block_3d::
unrefine()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

void
fiber_bundle::structured_block_3d::
simplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(is_jim());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(!is_jim());

  // Exit:

  return;
}


void
fiber_bundle::structured_block_3d::
unsimplify()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(!is_jim());

  // Body:

  not_implemented();

  // Postconditions:

  ensure(is_jim());

  // Exit:

  return;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// HOMOGENEOUS_BLOCK FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::structured_block_3d::
static_local_cell_prototype_path()
{

  // Preconditions:

  // Body:

  /// @error should be hex_complex.
  /// @todo replaced with hex_complex when available.

  static const poset_path
  STATIC_LOCAL_CELL_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(),
                                   "hex_nodes");

  const poset_path& result = STATIC_LOCAL_CELL_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "hex_nodes");

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

const fiber_bundle::structured_block_3d_crg_interval&
fiber_bundle::structured_block_3d::
interval() const
{
  return *reinterpret_cast<const structured_block_3d_crg_interval*>(_interval);
}

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

fiber_bundle::structured_block_3d*
fiber_bundle::structured_block_3d::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  structured_block_3d *result = new structured_block_3d();

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
fiber_bundle::structured_block_3d::
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
    invariance(state_is_read_accessible() ? size() == i_size()*j_size()*k_size() : true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return true;
}

bool
fiber_bundle::structured_block_3d::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const structured_block_3d*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::structured_block_3d&
fiber_bundle::structured_block_3d::
operator=(const abstract_poset_member& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(const_cast<abstract_poset_member*>(&xother));

  // Postconditions:

  ensure(is_same_state(const_cast<abstract_poset_member*>(&xother)));

  // Exit

  return *this;
}

fiber_bundle::structured_block_3d&
fiber_bundle::structured_block_3d::
operator=(const structured_block_3d& xother)
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


