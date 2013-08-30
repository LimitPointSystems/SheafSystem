

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class base_space_member_prototype.

#include "base_space_member_prototype.h"

#include "assert_contract.h"
#include "arg_list.h"
#include "base_space_poset.h"
#include "fiber_bundles_namespace.impl.h"
#include "poset_path.h"
#include "preorder_iterator.h"
#include "std_cstring.h"

using namespace fiber_bundle;

// ===========================================================
// HOST FACTORY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::base_space_member_prototype::
standard_schema_path()
{

  // Preconditions:

  // Body:

  // Schema is base_space_member_schema/base_space_schema_member
  // so that a prototype can represent any type of base space member.
  // ("restriction polymorphism")

  static const poset_path result("base_space_schema", "base_space_member_prototype_schema");

  // Postconditions:

  // Exit

  return result;
}

const sheaf::poset_path&
fiber_bundle::base_space_member_prototype::
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
fiber_bundle::base_space_member_prototype::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_path(), false));
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  // Schema for prototypes has to conform to every other base space member schema,
  // so it is the join of all the other members, which means it is a jem of top.
  
  poset_path lschema_top_path(standard_schema_path().poset_name(), "top");  
  schema_poset_member lschema_top(&xns, lschema_top_path, false);
  schema_poset_member lmember(lschema_top, true, false);
  lmember.put_name(standard_schema_path().member_name(), true, false);

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path(), false));

  // Exit:

  return;
}

const sheaf::poset_path&
fiber_bundle::base_space_member_prototype::
standard_host_path()
{

  // Preconditions:

  // Body:

  static const poset_path result("base_space_member_prototypes", "");

  // Postconditions:

  ensure(!result.empty());
  ensure(!result.full());

  // Exit

  return result;
}

fiber_bundle::base_space_member_prototype::host_type&
fiber_bundle::base_space_member_prototype::
new_host(namespace_type& xns, const poset_path& xhost_path, const poset_path& xschema_path, int xmax_db, bool xauto_access)
{
  // cout << endl << "Entering base_space_member_prototype::new_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xhost_path.empty());
  require(!xns.contains_path(xhost_path, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));  

  require(xmax_db >= 0);

  // Body:

  host_type& result = host_type::new_table(xns, xhost_path, xschema_path, xmax_db, xauto_access);

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xhost_path);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.max_db() == xmax_db);

  // Exit:

  // cout << "Leaving base_space_member_prototype::new_host." << endl;
  return result;
}

fiber_bundle::base_space_member_prototype::host_type&
fiber_bundle::base_space_member_prototype::
standard_host(namespace_type& xns, bool xauto_access)
{
  // cout << endl << "Entering base_space_member_prototype::standard_host." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xns.path_is_available<host_type>(standard_host_path(), true));

  require(xns.path_is_auto_read_accessible(standard_schema_path(), xauto_access));
  
  // Body:

  host_type* lresult_ptr;
  if(xns.contains_path(standard_host_path(), xauto_access))
  {
    lresult_ptr = &xns.member_poset<host_type>(standard_host_path(), xauto_access);
  }
  else
  {
    lresult_ptr = &host_type::new_table(xns, standard_host_path(), standard_schema_path(), 3, xauto_access);
  }
  
  host_type& result = *lresult_ptr;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == standard_host_path());
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == standard_schema_path());

  ensure(result.max_db() == 3);
  
  // Exit:

  // cout << "Leaving base_space_member_prototype::standard_host." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// BASE_SPACE_MEMBER_PROTOTYPE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::base_space_member_prototype::
base_space_member_prototype()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(!is_attached());
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const abstract_poset_member& xother, bool xnew_jem)
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

fiber_bundle::base_space_member_prototype::
~base_space_member_prototype()
{

  // Preconditions:

  // Body:

  // Exit

  return;
}

// NEW HANDLE, NEW STATE CONSTRUCTORS

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(poset* xhost,
                            const string& xname,
                            int xdb,
                            const string& xlocal_cell_name,
                            bool xauto_access)
{
  // Preconditions:

  require(xauto_access || xhost->in_jim_edit_mode());
  require(!xname.empty());
  require(!xhost->contains_member(xname, true));
  require(xlocal_cell_name.empty() || xhost->contains_member(xlocal_cell_name));

  // Body:

  // Can't check invariant until construction done.

  disable_invariant_check();

  if(xauto_access)
  {
    xhost->begin_jim_edit_mode(true);
  }

  // Create the member and set its name.

  new_jim_state(xhost, 0, false, false);
  put_name(xname, true, false);

  // Initialize the dofs.

  init_row_dof_tuple(xdb, xlocal_cell_name);

  // Now we can check the invaraint.

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(host() == xhost);
  ensure(name() == xname);
  ensure(db() == xdb);
  ensure(local_cell_type_name() == xlocal_cell_name);


  if(xauto_access)
  {
    xhost->end_jim_edit_mode(true, true);
  }

  // Exit:

  return;
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(poset* xhost,
                            const scoped_index& xdof_tuple_id,
                            bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_tuple_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(poset* xhost,
                            pod_index_type xdof_tuple_id,
                            bool xauto_access)
{
  // Preconditions:

  require(precondition_of(new_jim_state(same args)));

  // Body:

  new_jim_state(xhost, xdof_tuple_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jim_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(poset* xhost,
                            scoped_index* xexpansion,
                            int xexpansion_ct,
                            const tern& xnew_jem,
                            bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_jrm_state(same args)));

  // Body:

  new_jrm_state(xhost, xexpansion, xexpansion_ct, xnew_jem, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_jrm_state(same args)));

  // Exit:

  return;
}

// NEW HANDLE, EXISTING STATE CONSTRUCTORS

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const poset* xhost, pod_index_type xhub_id)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xhub_id)));

  // Body:

  attach_to_state(xhost, xhub_id);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xhub_id)));
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const poset* xhost, const scoped_index& xid)
{
  // Preconditions:

  require(precondition_of(attach_to_state(xhost, xid)));

  // Body:

  attach_to_state(xhost, xid.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(xhost, xid)));
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const poset* xhost, const string& xname)
{
  // Preconditions:

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xhost, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const namespace_poset* xnamespace,
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

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const namespace_poset* xnamespace,
                            pod_index_type xposet_id,
                            pod_index_type xmember_id,
                            bool xauto_access)
{
  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace, xposet_id, xmember_id, xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

fiber_bundle::base_space_member_prototype::
base_space_member_prototype(const namespace_poset* xnamespace,
                            const scoped_index& xposet_id,
                            const scoped_index& xmember_id,
                            bool xauto_access)
{

  // Preconditions:

  /// @error how do we require that the host schema conforms to SCHEMA_PATH?

  require(precondition_of(attach_to_state(same args)));

  // Body:

  attach_to_state(xnamespace,
		  xposet_id.hub_pod(),
		  xmember_id.hub_pod(),
		  xauto_access);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::base_space_member_prototype::
init_row_dof_tuple(int xdb, const string& xlocal_cell_name)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(host()->member_id_spaces(false).contains("cell_types"));
  require(xlocal_cell_name.empty() || host()->contains_member(xlocal_cell_name));


  // Body:
  row_dof_tuple_type& ltuple = *row_dof_tuple();

  // Set db.

  ltuple.db = xdb;

  // Set type id.

  mutable_index_space_handle& ltype_id_space =
    host()->member_id_spaces(false).get_id_space<mutable_index_space_handle>("cell_types");
  ltype_id_space.push_back(index());

  ltuple.type_id = ltype_id_space.pod(index());

  ltype_id_space.release_id_space();

  // Set type name.

  /// @error where does this string get deleted?

  ltuple.type_name = strdup(name().c_str());

  // Set the refinement depth.

  ltuple.refinement_depth = 0;

  // Set local cell type id and type name.

  if(xlocal_cell_name.empty())
  {
    ltuple.local_cell_type_id = sheaf::invalid_pod_index();

    /// @error where does this string get deleted?

    ltuple.local_cell_type_name = strdup("");
  }
  else
  {
    base_space_member_prototype lcell(host(), xlocal_cell_name);
    ltuple.local_cell_type_id = lcell.type_id();

    /// @error where does this string get deleted?

    ltuple.local_cell_type_name = strdup(lcell.type_name());
    lcell.detach_from_state();
  }


  // Set the remaining dofs to default values.

  ltuple.size = 0;
  ltuple.i_size = 0;
  ltuple.j_size = 0;
  ltuple.k_size = 0;

  // Postconditions:

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ROW DOFS FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fiber_bundle::base_space_member_prototype::
db() const
{
  int result = -1;

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  result = cthis->row_dof_tuple(false)->db;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

const sheaf::pod_index_type&
fiber_bundle::base_space_member_prototype::
type_id() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  // Type_id is member_id member of prototype_id.

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  const pod_index_type& result = cthis->row_dof_tuple(false)->type_id;

  // Postconditions:

  // Exit

  return result;
}

const char*
fiber_bundle::base_space_member_prototype::
type_name() const
{

  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  const char* result = cthis->row_dof_tuple(false)->type_name;

  // Postconditions:


  // Exit:

  return result;
}

int
fiber_bundle::base_space_member_prototype::
refinement_depth() const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_jim(false));

  // Body:

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  int result = cthis->row_dof_tuple()->refinement_depth;

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::base_space_member_prototype::
local_cell_type_id() const
{
  pod_index_type result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  result = cthis->row_dof_tuple(false)->local_cell_type_id;

  // Postconditions:


  // Exit:

  return result;
}


const char*
fiber_bundle::base_space_member_prototype::
local_cell_type_name() const
{
  const char* result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  base_space_member_prototype* cthis = const_cast<base_space_member_prototype*>(this);
  result = cthis->row_dof_tuple(false)->local_cell_type_name;

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}



fiber_bundle::base_space_member_prototype::row_dof_tuple_type*
fiber_bundle::base_space_member_prototype::
row_dof_tuple(bool xrequire_write_access)
{
  row_dof_tuple_type* result;

  // Preconditions:

  require(xrequire_write_access ?
          state_is_read_write_accessible() : state_is_read_accessible());
  require(is_jim(false));

  // Body:

  result =  reinterpret_cast<row_dof_tuple_type*>(dof_map().dof_tuple());

  // Postconditions:

  ensure(result != 0);

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// TOTAL_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ABSTRACT_POSET_MEMBER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET_COMPONENT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset*
fiber_bundle::base_space_member_prototype::
host() const
{
  poset* result;

  // Preconditions:


  // Body:

  result = reinterpret_cast<poset*>(total_poset_member::host());

  // Postconditions:


  // Exit:

  return result;
}


bool
fiber_bundle::base_space_member_prototype::
host_is_ancestor_of(const poset_state_handle* xother) const
{
  bool result;

  // Preconditions:

  require(xother != 0);

  // Body:

  result = dynamic_cast<const poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::base_space_member_prototype::
invariant() const
{
  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Must satisfy base class invariant

    invariance(total_poset_member::invariant());

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
fiber_bundle::base_space_member_prototype::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const base_space_member_prototype*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::base_space_member_prototype*
fiber_bundle::base_space_member_prototype::
clone() const
{

  // Preconditions:

  // Body:

  // create new handle of the current class.

  base_space_member_prototype *result = new base_space_member_prototype();

  // Postconditions:

  ensure(result != 0);
  ensure(result->invariant());

  // Exit:

  return result;

}

fiber_bundle::base_space_member_prototype&
fiber_bundle::base_space_member_prototype::
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

fiber_bundle::base_space_member_prototype&
fiber_bundle::base_space_member_prototype::
operator=(const base_space_member_prototype& xother)
{
  // Preconditions:

  // Body:

  attach_to_state(&xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit

  return *this;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

