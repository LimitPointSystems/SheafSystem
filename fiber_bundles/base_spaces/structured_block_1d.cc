

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class structured_block_1d

#include "structured_block_1d.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_member_prototype.h"
#include "chart_point_3d.h"
#include "fiber_bundles_namespace.impl.h"
#include "namespace_poset.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "tern.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC DATA MEMBERS

const sheaf::poset_path&
fiber_bundle::structured_block_1d::
standard_schema_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  STATIC_SCHEMA_PATH(base_space_member::standard_schema_path().poset_name(),
                     "structured_block_1d_schema");

  const poset_path& result = STATIC_SCHEMA_PATH;

  // Postconditions:

  // Exit

  return result;
}


const sheaf::poset_path&
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_path(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs = "i_size SIZE_TYPE false";


  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              structured_block::standard_schema_path(),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

const sheaf::poset_path&
fiber_bundle::structured_block_1d::
static_prototype_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  STATIC_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(),
                        "structured_block_1d");

  const poset_path& result = STATIC_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "structured_block_1d");

  // Exit

  return result;
}

fiber_bundle::structured_block_1d::host_type&
fiber_bundle::structured_block_1d::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, bool xauto_access)
{
  // cout << endl << "Entering structured_block_1d::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));  

  // Body:

  host_type& result =
    host_type::new_table(xns, xhost_path, xschema_path, 1, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == 1);

  // Exit:

  // cout << "Leaving structured_block_1d::new_host." << endl;
  return result;
}

fiber_bundle::structured_block_1d::host_type&
fiber_bundle::structured_block_1d::
new_host(namespace_type& xns, const poset_path& xhost_path, bool xauto_access)
{
  // cout << endl << "Entering structured_block_1d::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));
  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));
  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));

  // Body:

  host_type& result =
    new_host(xns, xhost_path, standard_schema_path(), xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.max_db() == 1);
  
  // Exit:

  // cout << "Leaving structured_block_1d::new_host." << endl;
  return result;
}

// PROTECTED DATA MEMBERS

// PRIVATE DATA MEMBERS


// ===========================================================
// STRUCTURED_BLOCK_1D FACET
// ===========================================================

// PUBLIC DATA MEMBERS

fiber_bundle::structured_block_1d::
structured_block_1d()
{
  // Preconditions:

  // Body:

  _interval = 0;

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}


fiber_bundle::structured_block_1d::
structured_block_1d(const abstract_poset_member& xother, bool xnew_jem)
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

fiber_bundle::structured_block_1d::
~structured_block_1d()
{
  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS:


fiber_bundle::structured_block_1d::
structured_block_1d(poset* xhost, const size_type& xi_size, bool xauto_access)
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

fiber_bundle::structured_block_1d::
structured_block_1d(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::structured_block_1d::
structured_block_1d(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}


fiber_bundle::structured_block_1d::
structured_block_1d(const poset* xhost, const string& xname)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}


fiber_bundle::structured_block_1d::
structured_block_1d(const namespace_poset* xnamespace,
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

fiber_bundle::structured_block_1d::
structured_block_1d(const namespace_poset* xnamespace,
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

fiber_bundle::structured_block_1d::
structured_block_1d(const namespace_poset* xnamespace,
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
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
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

  // Body:

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(xhost);

  // Get the size for the interval.

  size_type lsize;
  structured_block_1d_crg_interval::get_size(xi_size, lsize);

  // Get the dof tuple_ids.

  block<pod_index_type> ldof_tuple_ids;
  structured_block_1d_crg_interval::get_dof_tuple_ids(*xhost, xi_size, ldof_tuple_ids);

  // Get the private data for the interval

  block<pod_index_type> ldata;
  structured_block_1d_crg_interval::get_private_data(xi_size, ldata);

  // Create the implicit crg interval for the block.

  pod_index_type lindex =
    lhost->new_member_interval("structured_block_1d_crg_interval", lsize, ldof_tuple_ids, ldata);

  // Attach this handle to it.

  attach_to_state(lhost, lindex);

  // Block is linked to bottom via implicit lower cover of vertices,
  // but not linked to top; link it now.

  lhost->top().create_cover_link(this);

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(is_attached());
  ensure(db() == 1);
  ensure(prototype_path() == static_prototype_path());
  ensure(local_cell_type_name() == static_local_cell_prototype_path().member_name());
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

sheaf::size_type
fiber_bundle::structured_block_1d::
i_size() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  //  const size_type& result = row_dof_tuple()->i_size;

  size_type result = interval().i_size();

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED DATA MEMBERS

void
fiber_bundle::structured_block_1d::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(unexecutable(data members created));

  // Body:

  // Have just attached to a new or different member in the same host.
  // Attach the handle data members for the different member.

  // Attach _interval first; need it to call i_size().

  _interval = 
    dynamic_cast<structured_block_1d_crg_interval*>(crg()->implicit_member(_index.pod()));

  // Postconditions:

  ensure(!is_restricted());

  // Exit

  return;
}

sheaf::scoped_index
fiber_bundle::structured_block_1d::
new_row_dof_map(poset_state_handle& xhost, size_type xi_size, bool xauto_access)
{
  // Preconditions:

  require(xhost.state_is_auto_read_write_accessible(xauto_access));
  require(xauto_access || xhost.name_space()->poset_state_is_read_accessible(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_prototype_path()));
  require(xhost.name_space()->contains_poset_member(static_local_cell_prototype_path()));

  // Body:

  if(xauto_access)
  {
    xhost.get_read_write_access(true);
  }

  define_old_variable(int old_xhost_row_dof_tuple_ct = xhost.row_dof_tuple_ct());

  // Create the dof map and set dofs to defaults.

  scoped_index result = xhost.new_row_dof_map();
  row_dof_tuple_type* ltuple =
    reinterpret_cast<row_dof_tuple_type*>(xhost.row_dof_map(result, true).dof_tuple());

  // Get the block prototype.

  base_space_member_prototype
  lproto(xhost.name_space(), static_prototype_path(), xauto_access);

  // Get the local cell prototype.

  base_space_member_prototype
  local_proto(xhost.name_space(), static_local_cell_prototype_path(), xauto_access);

  // Copy the dofs from the prototypes..

  ltuple->db                   = lproto.db();
  ltuple->type_id              = lproto.type_id();
  ltuple->type_name            = strdup(lproto.type_name());
  ltuple->refinement_depth     = lproto.refinement_depth();
  ltuple->local_cell_type_id   = local_proto.type_id();
  ltuple->local_cell_type_name = strdup(local_proto.type_name());
  ltuple->size                 = xi_size;
  ltuple->i_size               = xi_size;

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
fiber_bundle::structured_block_1d::
refine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  require(xpt.chart_id() == index().pod());

  // See comment at structured_block::refine_point_pa.

  require(xpt.db() >= db());
  require(result.db() >= db());

  /// @todo make the following executable.
  require(unexecutable("chart_pt is in standard domain"));


  // Body:


  // Transform to zone-local coordinates..

  chart_point_coord_type lu_coord = xpt.local_coords()[0];
  pod_index_type lu_chart_id_pod;
  refine_coordinate(lu_coord, lu_chart_id_pod, i_size());

  // Convert sequence id to poset id.

  pod_index_type lu_chart_id = _elements_id_space->hub_pod(lu_chart_id_pod);

  // Store result.

  result.put_chart_id(lu_chart_id);
  result.put_local_coord(0, lu_coord);

  // Postconditions:

  // see $$ISSUE at structured_block::unrefine_pt_pa.
  //  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_1d::
refine_point_pa(const chart_point& xpt, block<chart_point_3d>& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xpt.chart_id() == index().pod());

  // See comment at structured_block::unrefine_point_pa.

  require(xpt.db() >= db());

  /// @todo make the following executable.
  require(unexecutable("chart_pt is in standard domain"));

  // Body:

  // Transform to zone-local coordinates..

  chart_point_coord_type lu_coord = xpt.local_coords()[0];
  pod_index_type lu_chart_id;
  refine_coordinate(lu_coord, lu_chart_id, i_size());

  // Convert sequence id to poset id and store result.

  chart_point_3d lrefined_pt(_elements_id_space->hub_pod(lu_chart_id),
			     lu_coord, 0.0, 0.0);
  result.push_back(lrefined_pt);

  if(is_close_enough(lu_coord, -1.0) && (lu_chart_id > 0))
  {
    // Point is on boundary between two zones.
    // Have already returned greater zone,
    // return the lesser zone as well.

    --lu_chart_id;

    // Convert sequence id to poset id and store result.

    lrefined_pt.put(_elements_id_space->hub_pod(lu_chart_id), 1.0, 0.0, 0.0);
    result.push_back(lrefined_pt);
  }

  // Postconditions:

  // see $$ISSUE at structured_block::unrefine_pt_pa.
  //  ensure(covers(result.chart_id()));

  // Exit:

  return;
}

void
fiber_bundle::structured_block_1d::
unrefine_point_pa(const chart_point& xpt, chart_point& result) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // see $$ISSUE at structured_block::unrefine_point_pa.
  //  require(covers(xpt.chart_id()));

  // See comment at structured_block::unrefine_point_pa.

  require(xpt.db() >= db());
  require(result.db() >= db());
  require(host()->contains_member(xpt.chart_id()));

  // Body:

  // Convert chart id to elements id space.

  pod_index_type lref_chart_id = _elements_id_space->pod(xpt.chart_id());

  // Assume refined local coordinates [-1, 1]; map to [0, 1] ...

  double lcoord = (xpt.local_coord(0) + 1.0)*0.5;

  // ... and then to unrefined coord [0, i_size] ...

  lcoord = lcoord + lref_chart_id;

  // ... and then to unrefined [-1, 1]
  /// @todo precompute 2.0/i_size() and store it some where.

  lcoord = (lcoord/i_size())*2.0 - 1.0;

  // Store result.

  result.put_chart_id(index().pod());

  result.put_local_coord(0, lcoord);

  // Postconditions:

  ensure(result.chart_id() == index().pod());

  // Exit:

  return;
}

void
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
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

const fiber_bundle::structured_block_1d_crg_interval&
fiber_bundle::structured_block_1d::
interval() const
{
  return *reinterpret_cast<const structured_block_1d_crg_interval*>(_interval);
}

const sheaf::poset_path&
fiber_bundle::structured_block_1d::
static_local_cell_prototype_path()
{
  // Preconditions:

  // Body:

  static const poset_path
  STATIC_LOCAL_CELL_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(),
                                   "segment_complex");

  const poset_path& result = STATIC_LOCAL_CELL_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "segment_complex");

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

fiber_bundle::structured_block_1d*
fiber_bundle::structured_block_1d::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  structured_block_1d *result = new structured_block_1d();

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
fiber_bundle::structured_block_1d::
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
fiber_bundle::structured_block_1d::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const structured_block_1d*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::structured_block_1d&
fiber_bundle::structured_block_1d::
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

fiber_bundle::structured_block_1d&
fiber_bundle::structured_block_1d::
operator=(const structured_block_1d& xother)
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


