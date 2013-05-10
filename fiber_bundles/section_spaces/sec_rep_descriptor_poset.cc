

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class sec_rep_descriptor_poset

#include "sec_rep_descriptor_poset.h"

#include "abstract_poset_member.impl.h"
#include "base_space_poset.h"
#include "array_poset_dof_map.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "poset_handle_factory.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SEC_REP_DESCRIPTOR_POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::arg_list
fiber_bundle::sec_rep_descriptor_poset::
make_arg_list(const poset_path& xprototypes_path)
{
  // Preconditions:

  // Body:

  sheaf::arg_list result;

  result << "prototypes_path" << xprototypes_path.path();
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_rep_descriptor_poset::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("prototypes_path") == xprototypes_path);
  
  // Exit:

  return result;
}

const string&
fiber_bundle::sec_rep_descriptor_poset::
standard_schema_poset_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_rep_descriptor_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::sec_rep_descriptor_poset::
standard_schema_path()
{
  // Preconditions:

  // Body:

  static const poset_path
  result(standard_schema_poset_name(), "sec_rep_descriptor_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

const string&
fiber_bundle::sec_rep_descriptor_poset::
standard_poset_name()
{
  // Preconditions:

  // Body:

  static const string result("sec_rep_descriptors");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_descriptor_poset::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false).state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs;

  ldof_specs =  "discretization_subposet_name C_STRING false";
  ldof_specs += " multivalued_subposet_name C_STRING false";
  ldof_specs += " evaluation_subposet_name C_STRING false";
  ldof_specs += " evaluator_family_name C_STRING false";
  ldof_specs += " URL C_STRING false";
  ldof_specs += " multiplicity INT false";

  /// @hack the following realy should be a bool,
  /// but we don't support bool as a primitive.

  ldof_specs += " eval_is_above_disc SIZE_TYPE false";

  // Table dofs:

  ldof_specs += " prototypes_path C_STRING true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_poset_name(), "bottom"),
                              ldof_specs,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}

fiber_bundle::sec_rep_descriptor_poset::
sec_rep_descriptor_poset(namespace_poset& xns,
			 const string& xname,
			 const arg_list& xargs,
			 const poset_path& xschema_path,
			 bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // Make the new state.

  new_state(xns, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}

const fiber_bundle::base_space_poset&
fiber_bundle::sec_rep_descriptor_poset::
prototypes() const
{
  // Preconditions:

  // Body:

  const base_space_poset& result = *_prototypes;

  // Postconditions:

  // Exit:

  return result;
}

fiber_bundle::base_space_poset&
fiber_bundle::sec_rep_descriptor_poset::
prototypes()
{
  // Preconditions:

  // Body:

  base_space_poset& result = *_prototypes;

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_rep_descriptor_poset::
sec_rep_descriptor_poset()
{
  // Preconditions:

  // Body:

  _prototypes = 0;

  // Postconditions:

  ensure(!is_attached());

  // Exit:

  return;
}

fiber_bundle::sec_rep_descriptor_poset::
~sec_rep_descriptor_poset()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_rep_descriptor_poset&
fiber_bundle::sec_rep_descriptor_poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

void
fiber_bundle::sec_rep_descriptor_poset::
initialize_arg_list(const namespace_poset& xns, 
		    const string& xname,
		    arg_list& xargs, 
		    const poset_path& xschema_path,
		    bool xauto_access)
{
  // Preconditions:

  require(xns.state_is_auto_read_accessible(xauto_access));

  require(!xschema_path.empty());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xschema_path.conforms_to(xns, standard_schema_path(), xauto_access));

  require(xns.arg_is_auto_read_accessible("prototypes_path", xargs, xauto_access));

  // Body:

  // Nothing to do.

#ifdef DIAGNOSTIC_OUTPUT
  cout << "sec_rep_descriptor_poset::initialize_arg_list:xargs: " << endl 
       << xargs << endl;
#endif

  // Postconditions:
  
  // Exit:

  return;
}

bool
fiber_bundle::sec_rep_descriptor_poset::
make_prototype()
{
  // Preconditions:

  // Body:

  poset_type ltype = SEC_REP_DESCRIPTOR_POSET_ID;

  sec_rep_descriptor_poset* lproto =
    new sec_rep_descriptor_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return true;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_rep_descriptor_poset::
new_state(namespace_poset& xns,
          const string& xname,
	  const arg_list& xargs,
	  const poset_path& xschema_path,
          bool xauto_access)
{

  // Preconditions:

  require(xauto_access || xns.in_jim_edit_mode());

  require(poset_path::is_valid_name(xname));
  require(!xns.contains_poset(xname, xauto_access));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.
  /// @hack unexecutable because may not have access.

  require(unexecutable(xname != xns.name()));

  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(xschema_path.conforms_to(xns, standard_schema_path(), xauto_access));

  require(xargs.conforms_to(xns, xschema_path, true, xauto_access));
  
  require(xns.arg_is_auto_read_accessible("prototypes_path", xargs, xauto_access));

  // Body:

  if(xauto_access)
  {
    xns.get_read_write_access();
  }

  // Set any class specific args in arg list.

  arg_list largs(xargs);
  initialize_arg_list(xns, xname, largs, xschema_path, xauto_access);

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Get a temporary handle to the schema.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);
  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&lschema, type_id());

  // Get write access;
  // handle data members aren't attached yet, 
  // so use psh version.

  poset_state_handle::get_read_write_access();

  // Initialize the table dofs ("class variables").
  // Do this before initializing the row structure so the subposet
  // and member initialization routines can use the table dofs if needed.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof_tuple(xargs);
  initialize_table_dof_tuple(lmap);

  // Initialize any additional handle data members
  // that may depend on table dofs.

  initialize_handle_data_members(xns);

  // Release and regain access;
  // will get access to handle data members.

  poset_state_handle::release_access();
  get_read_write_access();

  // Initialize the row structure.

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Initialize the namespace features.

  initialize_namespace(xns, xname);

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Cleanup temporary schema handle.

  if(xauto_access)
  {
    lschema.release_access();
  }
  lschema.detach_from_state();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(schema().path() == xschema_path);
  ensure(name() == xname);
  ensure(!in_jim_edit_mode());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(prototypes().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  if(xauto_access)
  {
    xns.release_access();
  }

  // Exit:

  return;
}

void
fiber_bundle::sec_rep_descriptor_poset::
new_state(const schema_poset_member& xschema,
          array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(name_space() != 0);
  require(name_space()->state_is_read_accessible());

  require(xschema.state_is_read_accessible());
  require(is_external());
  require(schema_is_ancestor_of(&xschema));
  require(xschema.host()->name_space()->is_same_state(name_space()));

  /// @issue the following is unexecutable because dof maps don't have
  /// a schema until attached to a host; requires covariant schema feature to implement.

  /// @todo fix dof maps schema feature and make this precondition executable.

  require(unexecutable(xschema.is_same_state(xdof_map.schema())));

  require(unexecutable("prototypes in xdof_map exists"));
  require(unexecutable("prototypes in xdof_map is read accessible"));


  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&xschema, type_id());

  // Get write access;
  // handle data members aren't attached yet, 
  // so use psh version.

  poset_state_handle::get_read_write_access();

  // Initialize the table dofs.
  // Must be called before initialize_standard_members
  // because precondition contains_member in put_member_dof_tuple_id
  // called from new_member indirectly needs table dofs.

  initialize_table_dof_tuple(&xdof_map);

  // Initialize any additional handle data members
  // that may depend on table dofs.

  initialize_handle_data_members(*name_space());

  // Release and regain access;
  // will get access to handle data members.

  poset_state_handle::release_access();
  get_read_write_access();

  // Initialize the row structure.

  initialize_standard_subposets(name_space()->member_name(index()));
  initialize_standard_members();

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(schema().is_same_state(&xschema));
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(&(table_dof_map()) == &xdof_map);
  ensure(prototypes().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::sec_rep_descriptor_poset::
type_id() const
{
  return SEC_REP_DESCRIPTOR_POSET_ID;
}

const char*
fiber_bundle::sec_rep_descriptor_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_rep_descriptor_poset";

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::sec_rep_descriptor_poset::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  _prototypes->get_read_access();

  poset::get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(prototypes().state_is_read_accessible());

  // Exit

  return;
}

void
fiber_bundle::sec_rep_descriptor_poset::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);


  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  _prototypes->get_read_access();

  poset::get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(prototypes().state_is_read_accessible());

  // Exit

  return;
}

void
fiber_bundle::sec_rep_descriptor_poset::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  define_old_variable(int old_access_request_depth = access_request_depth());

  // Release at least one level of access for this. If xall, release all levels
  // of access for this. Since each level of access to this also
  // acquired a level of access to the rep, the base space, and the fiber space,
  // release the same number of levels of access to each of these.
  // Note that this may not be all the levels of access of these.

  do
  {
    // Release one level of access.

    _prototypes->release_access(false);

    poset::release_access(false);
  }
  while(xall && state_is_read_accessible());


  // Postconditions:

  ensure(!xall ? access_request_depth() == old_access_request_depth - 1 :
         access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);
  ensure(unexecutable("schema, and prototypes access released"));

  // Exit

  return;
}

// PROTECTED MEMBER FUNCTIONS

void
fiber_bundle::sec_rep_descriptor_poset::
initialize_handle_data_members(const namespace_poset& xns)
{
  // Preconditions:

  require(state_is_read_accessible());
  require(xns.state_is_read_accessible());

  // Body:

  // Attach the handle data members that depend on the table dofs
  // and are required to get access.

  table_dofs_type& ldofs = sheaf::table_dofs(*this);

  poset_path lprototypes_path(ldofs.prototypes_path);
  _prototypes = &xns.member_poset<base_space_poset>(lprototypes_path, false);

  // Postconditions:

  ensure(prototypes().is_attached());

  // Postconditions:


  // Exit

  return;
}

void
fiber_bundle::sec_rep_descriptor_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  poset::attach_handle_data_members();

  // Attach the base space members prototypes poset to the current state.

  table_dofs_type& ldofs = sheaf::table_dofs(*this);
  namespace_poset* lns = name_space();

  poset_path lprototypes_path(ldofs.prototypes_path);
  _prototypes = &lns->member_poset<base_space_poset>(lprototypes_path, false);
  
  // Postconditions:

  ensure(prototypes().is_attached());

  // Exit

  return;
}

void
fiber_bundle::sec_rep_descriptor_poset::
terminate_access()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_prototypes_access_request_depth = prototypes().access_request_depth());

  // Release all levels of access this poset has to its various parts,
  // but do not release access to the state of this because
  // we are going to delete the state and don't want another
  // client able to sneak in and get access before we do.

  /// @issue we should either prevent termination if other clients
  /// exist or have some mechanism for notifying them of termination.
  /// Currently we can't do either one.

  string prototypes_name(prototypes().name());

#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset: " << name() << endl
  << "\trep: " << prototypes_name
  << "  old lvl:" << old_prototypes_access_request_depth << endl
#endif

  int old_access_request_depth = access_request_depth();
  for(size_type i=0; i<old_access_request_depth; ++i)
  {
    prototypes().release_access(false);
  }

  define_old_variable(int prototypes_access_request_depth = prototypes().access_request_depth());

#ifdef DIAGNOSTIC_OUTPUT
  cout << " \tprototypes lvl:" << prototypes_access_request_depth << endl;
#endif

  // Detach and delete the state.

  poset::terminate_access();

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable("state has been deleted"));
  ensure(prototypes_access_request_depth ==
         (old_prototypes_access_request_depth - old_access_request_depth));

  // Exit

  return;
}

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::pod_index_type
fiber_bundle::sec_rep_descriptor_poset::
prereq_id(int xi) const
{
  pod_index_type result;

  // Preconditions:

  // Body:

  switch(xi)
  {
  case 0: // schema
    result = schema().host()->index().pod();
    break;
  case 1: // base space prototypes
    result = _prototypes->index().pod();
    break;
  default:
    result = invalid_pod_index();
    break;
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_rep_descriptor_poset::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const sec_rep_descriptor_poset*>(other) != 0;

  // Postconditions:

  return result;
}

fiber_bundle::sec_rep_descriptor_poset*
fiber_bundle::sec_rep_descriptor_poset::
clone() const
{
  sec_rep_descriptor_poset* result;
  
  // Preconditions:

  // Body:
  
  result = new sec_rep_descriptor_poset();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
fiber_bundle::sec_rep_descriptor_poset::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(poset::invariant());

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
//  NON-MEMBER FUNCTIONS
// ===========================================================
 

