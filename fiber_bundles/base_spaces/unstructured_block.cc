//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class unstructured_block.

#include "unstructured_block.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_member_prototype.h"
#include "fiber_bundles_namespace.impl.h"
#include "hex_connectivity.h"
#include "line_connectivity.h"
#include "namespace_poset.h"
#include "point_connectivity.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "quad_connectivity.h"
#include "tetra_connectivity.h"
#include "triangle_connectivity.h"
#include "unstructured_block_builder.h"
#include "wsv_block.h"


//using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

const sheaf::poset_path&
fiber_bundle::unstructured_block::
standard_schema_path()
{

  // Preconditions:

  // Body:

  static const poset_path result(standard_schema_poset_name(),
                                 "unstructured_block_schema");

  // Postconditions:

  // Exit

  return result;
}


const sheaf::poset_path&
fiber_bundle::unstructured_block::
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
fiber_bundle::unstructured_block::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  // Unstructured_block schema does not introduce any new dofs.

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              homogeneous_block::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

const sheaf::poset_path&
fiber_bundle::unstructured_block::
static_prototype_path()
{

  // Preconditions:

  // Body:

  static const poset_path
  STATIC_PROTOTYPE_PATH(base_space_member::prototypes_poset_name(),
                        "unstructured_block");

  const poset_path& result = STATIC_PROTOTYPE_PATH;

  // Postconditions:

  ensure(result.poset_name() == base_space_member::prototypes_poset_name());
  ensure(result.member_name() == "unstructured_block");

  // Exit

  return result;
}

fiber_bundle::unstructured_block::host_type&
fiber_bundle::unstructured_block::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering unstructured_block::new_host." << endl;

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

  // cout << "Leaving unstructured_block::new_host." << endl;
  return result;
}

fiber_bundle::unstructured_block::host_type&
fiber_bundle::unstructured_block::
new_host(namespace_type& xns, const poset_path& xhost_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering unstructured_block::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));
  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));
  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  require(xmax_db >= 0);

  // Body:

  host_type& result =
    new_host(xns, xhost_path, standard_schema_path(), xmax_db, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.max_db() == xmax_db);
  
  // Exit:

  // cout << "Leaving unstructured_block::new_host." << endl;
  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

bool
fiber_bundle::unstructured_block::
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



bool
fiber_bundle::unstructured_block::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const unstructured_block*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}


fiber_bundle::unstructured_block&
fiber_bundle::unstructured_block::
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

fiber_bundle::unstructured_block&
fiber_bundle::unstructured_block::
operator=(const unstructured_block& xother)
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

// ===========================================================
// ABSTRACT POSET MEMBER FACET
// ===========================================================

fiber_bundle::unstructured_block*
fiber_bundle::unstructured_block::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  unstructured_block *result = new unstructured_block();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}


// ===========================================================
// UNSTRUCTURED_BLOCK FACET
// ===========================================================


fiber_bundle::unstructured_block::
unstructured_block()
{

  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(! is_attached() );
}


fiber_bundle::unstructured_block::
unstructured_block(const abstract_poset_member& xother, bool xnew_jem)
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

fiber_bundle::unstructured_block::
~unstructured_block()
{

  // Preconditions:

  // Body:

  // Exit

  return;
}

// ===========================================================
// NEW HANDLE, NEW STATE CONSTRUCTORS
// ===========================================================

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const string& xlocal_cell_prototype_name,
                   bool xis_prototype_name,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(xhost, xlocal_cell_prototype_name, xauto_access)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_name, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(xhost, xlocal_cell_prototype_name, xauto_access)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const poset_path& xlocal_cell_prototype_path,
                   const scoped_index* xids,
                   int xub,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_path, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const base_space_member_prototype& xlocal_cell_prototype,
                   const scoped_index* xids,
                   int xub,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const poset_path& xlocal_cell_prototype_path,
                   const pod_index_type* xids,
                   int xub,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_path, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const base_space_member_prototype& xlocal_cell_prototype,
                   const pod_index_type* xids,
                   int xub,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const poset_path& xlocal_cell_prototype_path,
                   const size_type& xi_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_path, xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const base_space_member_prototype& xlocal_cell_prototype,
                   const size_type& xi_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype, xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const poset_path& xlocal_cell_prototype_path,
                   const size_type& xi_size,
                   const size_type& xj_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_path, xi_size, xj_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const base_space_member_prototype& xlocal_cell_prototype,
                   const size_type& xi_size,
                   const size_type& xj_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype, xi_size, xj_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const poset_path& xlocal_cell_prototype_path,
                   const size_type& xi_size,
                   const size_type& xj_size,
                   const size_type& xk_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype_path, xi_size, xj_size, xk_size,
            xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

fiber_bundle::unstructured_block::
unstructured_block(poset* xhost,
                   const base_space_member_prototype& xlocal_cell_prototype,
                   const size_type& xi_size,
                   const size_type& xj_size,
                   const size_type& xk_size,
                   bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  new_state(xhost, xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));

  // Exit

  return;
}

// ===========================================================
// NEW HANDLE, EXISTING STATE CONSTRUCTORS
// ===========================================================


fiber_bundle::unstructured_block::
unstructured_block(const poset* xhost, scoped_index xindex)
{

  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xindex)));

  // Body:

  attach_to_state(xhost, xindex);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xindex)));
}


fiber_bundle::unstructured_block::
unstructured_block(const poset* xhost, const string& xname)
{

  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}


fiber_bundle::unstructured_block::
unstructured_block(const namespace_poset* xnamespace,
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

fiber_bundle::unstructured_block::
unstructured_block(const namespace_poset* xnamespace,
                   const scoped_index& xposet_id,
                   const scoped_index& xmember_id)
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


// ===========================================================
// EXISTING HANDLE, NEW STATE "CONSTRUCTORS"
// ===========================================================


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const string& xlocal_cell_prototype_name,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access || xhost->in_jim_edit_mode());

  // Get access if auto access is requested.  Need to do it here so the
  // remaining preconditions can be executed.

  if(xauto_access)
    xhost->begin_jim_edit_mode(true);

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));
  require(prototype_exists(xlocal_cell_prototype_name, true));

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the dof map and initialize the dofs.

  array_poset_dof_map* lmap = new_row_dof_map(xhost,
                              static_prototype_path().member_name(),
                              xlocal_cell_prototype_name,
                              0);

  // Create the new state.

  new_jim_state(xhost, lmap, false, false);

  // Link it as an isolated atom.

  host()->top().create_cover_link(this);
  create_cover_link(&host()->bottom());

  // Postconditions:

  ensure(invariant());
  ensure(prototype_path() == static_prototype_path());
  ensure(local_cell_type_name() == xlocal_cell_prototype_name);
  ensure(size() == 0);
  ensure(is_jim());

  // Release access if auto access was requested.

  if(xauto_access)
    xhost->end_jim_edit_mode(true, true);

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const poset_path& xlocal_cell_prototype_path,
          const scoped_index* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->name_space()->contains_poset_member(xlocal_cell_prototype_path));
  require(precondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype_path, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const base_space_member_prototype& xlocal_cell_prototype,
          const scoped_index* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const poset_path& xlocal_cell_prototype_path,
          const scoped_index* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost->is_attached() : xhost->state_is_read_write_accessible());
  require(xauto_access || xhost->name_space()->state_is_read_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));

  require(precondition_of(new_state(xhost, xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  base_space_member_prototype lproto(xhost->name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  new_state(xhost, lproto, xids, xub, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const base_space_member_prototype& xlocal_cell_prototype,
          const scoped_index* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());
  require(xauto_access || xlocal_cell_prototype.name_space()->state_is_read_accessible());

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xlocal_cell_prototype.get_read_access();
    xlocal_cell_prototype.name_space()->get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));
  require(xlocal_cell_prototype.schema().row_conforms_to(xhost->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(xhost));
  require(xlocal_cell_prototype.atom_ct() > 0);
  require(xids != 0);
  require(xub > 0);
  require( (xub % xlocal_cell_prototype.atom_ct()) == 0 );

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the dof map and initialize the dofs.

  size_type lsize = xub/xlocal_cell_prototype.atom_ct();
  array_poset_dof_map* lmap = new_row_dof_map(xhost,
                              static_prototype_path().member_name(),
                              xlocal_cell_prototype.name(),
                              lsize);

  // Create the new state.

  new_jim_state(xhost, lmap, false, false);

  // Link it as an isolated atom.

  host()->top().create_cover_link(this);
  create_cover_link(&host()->bottom());

  /// @hack assume if block has maximal dimension,
  /// we don't need to compute the upper cover.

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(host());

  bool lcompute_cover = (db() < lhost->max_db());

  // Build the block

  unstructured_block_builder block_builder;
  block_builder.build_block_pa(&xlocal_cell_prototype,
                               xids,
                               xub,
                               this,
                               lcompute_cover,
                               false);

  // Postconditions:

  ensure(db() == xlocal_cell_prototype.db());
  ensure(prototype_path() == static_prototype_path());
  //  ensure(local_cell_type_name() == xlocal_cell_prototype.name());
  ensure(xlocal_cell_prototype.has_name(local_cell_type_name()));
  ensure(size() == xub/xlocal_cell_prototype.atom_ct());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xlocal_cell_prototype.name_space()->release_access();
    xlocal_cell_prototype.release_access();
    xhost->end_jim_edit_mode(true, true);
  }

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const poset_path& xlocal_cell_prototype_path,
          const pod_index_type* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(host()->name_space()->contains_poset_member(xlocal_cell_prototype_path));
  require(precondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype_path, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const base_space_member_prototype& xlocal_cell_prototype,
          const pod_index_type* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const poset_path& xlocal_cell_prototype_path,
          const pod_index_type* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost->is_attached() : xhost->state_is_read_write_accessible());
  require(xauto_access || xhost->name_space()->state_is_read_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));

  require(precondition_of(new_state(xhost, xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  base_space_member_prototype lproto(xhost->name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  new_state(xhost, lproto, xids, xub, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const base_space_member_prototype& xlocal_cell_prototype,
          const pod_index_type* xids,
          int xub,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());
  require(xauto_access || xlocal_cell_prototype.name_space()->state_is_read_accessible());

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xlocal_cell_prototype.get_read_access();
    xlocal_cell_prototype.name_space()->get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));
  require(xlocal_cell_prototype.schema().row_conforms_to(xhost->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(xhost));
  require(xlocal_cell_prototype.atom_ct() > 0);
  require(xids != 0);
  require(xub > 0);
  require( (xub % xlocal_cell_prototype.atom_ct()) == 0 );

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the dof map and initialize the dofs.

  size_type lsize = xub/xlocal_cell_prototype.atom_ct();
  array_poset_dof_map* lmap = new_row_dof_map(xhost,
                              static_prototype_path().member_name(),
                              xlocal_cell_prototype.name(),
                              lsize);

  // Create the new state.

  new_jim_state(xhost, lmap, false, false);

  // Link it as an isolated atom.

  host()->top().create_cover_link(this);
  create_cover_link(&host()->bottom());

  /// @hack assume if block has maximal dimension,
  /// we don't need to compute the upper cover.

  /// @todo replace lhost with host()
  /// when base_space_member::host is type base_space_poset.

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(host());

  bool lcompute_cover = (db() < lhost->max_db());

  // Build the block

  unstructured_block_builder block_builder;
  block_builder.build_block_pa(&xlocal_cell_prototype,
                               xids,
                               xub,
                               this,
                               lcompute_cover,
                               false);

  // Postconditions:

  ensure(db() == xlocal_cell_prototype.db());
  ensure(prototype_path() == static_prototype_path());
  //  ensure(local_cell_type_name() == xlocal_cell_prototype.name());
  ensure(xlocal_cell_prototype.has_name(local_cell_type_name()));
  ensure(size() == xub/xlocal_cell_prototype.atom_ct());

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xlocal_cell_prototype.name_space()->release_access();
    xlocal_cell_prototype.release_access();
    xhost->end_jim_edit_mode(true, true);
  }

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(precondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype_path, xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype, xi_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xauto_access)));

  // Exit

  return;
}


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost->is_attached() : xhost->state_is_read_write_accessible());
  require(xauto_access || xhost->name_space()->state_is_read_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));

  require(precondition_of(new_state(xhost, xlocal_cell_prototype, xi_size, xauto_access)));

  // Body:

  base_space_member_prototype lproto(xhost->name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  new_state(xhost, lproto, xi_size, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xlocal_cell_prototype.get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));

  require(xlocal_cell_prototype.schema().row_conforms_to(xhost->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(xhost));
  require(xlocal_cell_prototype.atom_ct() > 0);
  require(xlocal_cell_prototype.name() == "segment_complex" ||
          xlocal_cell_prototype.name() == "point");
  require(xi_size > 0);

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the connectivity.

  block_connectivity* lconnectivity;
  if(xlocal_cell_prototype.name() == "segment_complex")
  {
    lconnectivity = new line_connectivity(xi_size);
  }
  else
  {
    lconnectivity = new point_connectivity(xi_size);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << *lconnectivity << endl;
#endif

  int* lnode_ids = lconnectivity->node_ids();
  int lnode_ids_ub = lconnectivity->node_id_ct();

  new_state(xhost,
            xlocal_cell_prototype,
            lnode_ids,
            lnode_ids_ub,
            false);

  delete lconnectivity;

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, lnode_ids, lnode_ids_ub, false)));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xhost->end_jim_edit_mode(true, true);
    xlocal_cell_prototype.release_access();
  }


  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          const size_type& xj_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(precondition_of(new_state(host(), xlocal_cell_prototype_path, xi_size, xj_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype_path, xi_size, xj_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          const size_type& xj_size,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xauto_access)));

  // Exit

  return;
}


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          const size_type& xj_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost->is_attached() : xhost->state_is_read_write_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));
  require(precondition_of(new_state(xhost, xlocal_cell_prototype, xi_size, xj_size, xauto_access)));

  // Body:


  base_space_member_prototype lproto(xhost->name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  new_state(xhost, lproto, xi_size, xj_size, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          const size_type& xj_size,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());
  require(xauto_access || xlocal_cell_prototype.name_space()->state_is_read_accessible());

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xlocal_cell_prototype.get_read_access();
    xlocal_cell_prototype.name_space()->get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));
  require(xlocal_cell_prototype.schema().row_conforms_to(xhost->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(xhost));
  require(xlocal_cell_prototype.atom_ct() > 0);
  require(xlocal_cell_prototype.db() == 2);
  //   require((xlocal_cell_prototype.name() == "quad_nodes") ||
  //           (xlocal_cell_prototype.name() == "quad_complex") ||
  //           (xlocal_cell_prototype.name() == "triangle_complex") ||
  //           (xlocal_cell_prototype.name() == "triangle_nodes"));
  require((xlocal_cell_prototype.has_name("quad_nodes")) ||
          (xlocal_cell_prototype.has_name("quad_complex")) ||
          (xlocal_cell_prototype.has_name("triangle_complex")) ||
          (xlocal_cell_prototype.has_name("triangle_nodes")));
  require(xi_size > 0);
  require(xj_size > 0);

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the connectivity.

  block_connectivity* lconnectivity = 0;

  if((xlocal_cell_prototype.name() == "quad_nodes") ||
      (xlocal_cell_prototype.name() == "quad_complex"))
  {
    lconnectivity = new quad_connectivity(xi_size, xj_size);
  }
  else
  {
    // Has to be "triangle_nodes" or "triangle_complex"
    // due to the precondition.

    lconnectivity = new triangle_connectivity(xi_size, xj_size);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << *lconnectivity << endl;
#endif

  int* lnode_ids = lconnectivity->node_ids();
  int lnode_ids_ub = lconnectivity->node_id_ct();

  new_state(xhost,
            xlocal_cell_prototype,
            lnode_ids,
            lnode_ids_ub,
            false);

  delete lconnectivity;

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, lnode_ids, lnode_ids_ub, false)));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xlocal_cell_prototype.name_space()->release_access();
    xlocal_cell_prototype.release_access();
    xhost->end_jim_edit_mode(true, true);
  }


  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access || state_is_read_write_accessible());
  require(precondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype_path, xi_size, xj_size, xk_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Body:

  new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Exit

  return;
}


void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const poset_path& xlocal_cell_prototype_path,
          const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? xhost->is_attached() : xhost->state_is_read_write_accessible());
  require(xauto_access || xhost->name_space()->state_is_read_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));

  require(precondition_of(new_state(xhost, xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Body:

  base_space_member_prototype lproto(xhost->name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  new_state(xhost, lproto, xi_size, xj_size, xk_size, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, xi_size, xj_size, xk_size, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
new_state(poset* xhost,
          const base_space_member_prototype& xlocal_cell_prototype,
          const size_type& xi_size,
          const size_type& xj_size,
          const size_type& xk_size,
          bool xauto_access)
{
  // Preconditions:

  require(xhost != 0);
  require(xauto_access ? xhost->is_attached() : xhost->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());
  require(xauto_access || xlocal_cell_prototype.name_space()->state_is_read_accessible());

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
    xlocal_cell_prototype.get_read_access();
    xlocal_cell_prototype.name_space()->get_read_access();
  }

  require(namespace_is_ancestor_of(xhost->name_space()));
  require(xhost->schema().row_conforms_to(standard_schema_path()));
  require(xlocal_cell_prototype.state_is_read_accessible());
  require(xlocal_cell_prototype.schema().row_conforms_to(xhost->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(xhost));
  require(xlocal_cell_prototype.atom_ct() > 0);
  require(xlocal_cell_prototype.db() == 3);
  require((xlocal_cell_prototype.name().substr(0, 3) == "hex") ||
          (xlocal_cell_prototype.name() == "tetra_nodes"));
  require(xi_size > 0);
  require(xj_size > 0);
  require(xk_size > 0);

  // Body:

  // $$HACK: force subposets to be persistent

  make_standard_subposets_persistent(*xhost);

  // Create the connectivity.

  block_connectivity* lconnectivity = 0;

  if(xlocal_cell_prototype.name().substr(0, 3) == "hex")
  {
    lconnectivity = new hex_connectivity(xi_size, xj_size, xk_size);
  }
  else
  {
    // Has to be (xlocal_cell_prototype.name() == "tetra_nodes")
    // due to the precondition.
    lconnectivity = new tetra_connectivity(xi_size, xj_size, xk_size);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << *lconnectivity << endl;
#endif

  int* lnode_ids = lconnectivity->node_ids();
  int lnode_ids_ub = lconnectivity->node_id_ct();

  new_state(xhost,
            xlocal_cell_prototype,
            lnode_ids,
            lnode_ids_ub,
            false);

  delete lconnectivity;

  // Postconditions:

  ensure(postcondition_of(new_state(host(), xlocal_cell_prototype, lnode_ids, lnode_ids_ub, false)));

  // Release access if auto access was requested.

  if(xauto_access)
  {
    xlocal_cell_prototype.name_space()->release_access();
    xlocal_cell_prototype.release_access();
    xhost->end_jim_edit_mode(true, true);
  }

  // Exit

  return;
}

// ===========================================================
// ROW DOFS
// ===========================================================


// ===========================================================
// OTHER FEATURES
// ===========================================================

void
fiber_bundle::unstructured_block::
refine(const poset_path& xlocal_cell_prototype_path,
       const scoped_index* xids,
       int xub,
       bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? is_attached() : state_is_read_write_accessible());
  require(xauto_access || name_space()->state_is_read_accessible());
  require(xlocal_cell_prototype_path.member_exists(xauto_access));
  require(xauto_access || xlocal_cell_prototype_path.state_is_read_accessible(xauto_access));

  require(precondition_of(refine(xlocal_cell_prototype, xids, xub, xauto_access)));

  // Body:

  base_space_member_prototype lproto(name_space(),
                                     xlocal_cell_prototype_path,
                                     xauto_access);

  refine(lproto, xids, xub, xauto_access);

  lproto.detach_from_state();

  // Postconditions:

  ensure(postcondition_of(refine(xlocal_cell_prototype, xids, xub, xauto_access)));

  // Exit

  return;
}

void
fiber_bundle::unstructured_block::
refine(const base_space_member_prototype& xlocal_cell_prototype,
       const scoped_index* xids,
       int xub,
       bool xauto_access)
{
  // Preconditions:

  require(xauto_access ? is_attached() : host()->in_jim_edit_mode());
  require(xauto_access ?
          xlocal_cell_prototype.is_attached() :
          xlocal_cell_prototype.state_is_read_accessible());

  if(xauto_access)
  {
    get_read_write_access();
    xlocal_cell_prototype.get_read_access();
  }

  require(is_atom());
  require(prototype_path() == static_prototype_path());

  require(xlocal_cell_prototype.schema().row_conforms_to(host()->schema()));
  require(!xlocal_cell_prototype.host()->is_same_state(host()));
  require(xlocal_cell_prototype.atom_ct() > 0);

  require(xids != 0);
  require(xub > 0);
  require((xub % xlocal_cell_prototype.atom_ct()) == 0);

  // Body:

  // Build the block;

  if(xauto_access)
  {
    host()->begin_jim_edit_mode(false);
  }

  // Refine the block; assume we don't need to compute the upper cover.

  unstructured_block_builder block_builder;
  block_builder.build_block_pa(&xlocal_cell_prototype, xids, xub, this, false, false);

  if(xauto_access)
  {
    // Exit jim edit mode but do not ensure lattice invariant
    // because it is expensive and we don't need to do it -
    // the block building routine has properly hooked up everything.
    // Don't release access because we still need it below.

    host()->end_jim_edit_mode(false, false);
  }

  // Postconditions:

  ensure(db() == xlocal_cell_prototype.db());
  ensure(local_cell_type_name() == xlocal_cell_prototype.name());
  ensure(size() == xub/xlocal_cell_prototype.atom_ct());

  if(xauto_access)
  {
    release_access();
    xlocal_cell_prototype.release_access();
  }

  // Exit

  return;
}

bool
fiber_bundle::unstructured_block::
host_created_with_new_host(const poset_state_handle& xhost)
{
  bool result;

  // Preconditions:

  require(xhost.state_is_read_accessible());
  
  // Body:

  // $$HACK: unstructured_block hack.

  // If new_host created xhost, it's actually a base_space_poset
  // and the standard subposets, vertices in particular, are persisent.

  const base_space_poset* lhost = dynamic_cast<const base_space_poset*>(&xhost);
  
  result = (lhost != 0) && lhost->vertices().is_persistent();

  // Postconditions:


  // Exit:

  return result;
}

void
fiber_bundle::unstructured_block::
make_standard_subposets_persistent(poset_state_handle& xhost)
{

  // Preconditions:

  require(xhost.state_is_read_accessible());
  
  // Body:

  base_space_poset* lhost = dynamic_cast<base_space_poset*>(&xhost);

  // @hack unstructured_block hack.
  // The standard subposets created by base_space_poset are now volatile
  // by default, but unstructured_block has no mechanism for recreating
  // them when read from a file. So they must be made persistent.

  lhost->get_read_write_access();
  lhost->blocks().put_is_persistent(true);
  lhost->block_vertices().put_is_persistent(true);
  lhost->cells().put_is_persistent(true);
  for(int_type i=0; i<=lhost->max_db(); ++i)
  {
    lhost->d_cells(i).put_is_persistent(true);
  }
  lhost->release_access();

  // Postconditions:

  // Exit:
}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

// ===========================================================
// PRIVATE MEMBER FUNCTIONS
// ===========================================================

