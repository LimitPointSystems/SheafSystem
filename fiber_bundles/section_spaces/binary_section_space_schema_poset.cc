

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class binary_section_space_schema_poset.

#include "binary_section_space_schema_poset.h"

#include "abstract_poset_member.h"
#include "arg_list.h"
#include "array_poset_dof_map.h"
#include "base_space_member.h"
#include "binary_section_space_schema_member.h"
#include "index_iterator.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "poset_member_iterator.h"
#include "poset_state.h"
#include "poset_type.h"
#include "postorder_member_iterator.h"
#include "schema_poset_member.h"
#include "sheaves_namespace.h"
#include "subposet.h"
#include "wsv_block.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BINARY_SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::arg_list
fiber_bundle::binary_section_space_schema_poset::
make_arg_list(const poset_path& xrep_path, 
	      const poset_path& xbase_space_path, 
	      const poset_path& xfiber_space_path)
{
  // Preconditions:


  // Body:

  sheaf::arg_list result;

  result << "rep_path" << xrep_path
	 << "base_space_path" << xbase_space_path 
	 << "fiber_space_path" << xfiber_space_path;
  
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "binary_section_space_schema_poset::make_arg_list:result: " << result << endl;
#endif

  // Postconditions:

  ensure(unexecutable("result.conforms_to(schema of this class)"));
  ensure(result.value("rep_path") == xrep_path);
  ensure(result.value("base_space_path") == xbase_space_path);
  ensure(result.value("fiber_space_path") == xfiber_space_path);
  
  // Exit:

  return result;
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(namespace_poset& xns,
                                  const string& xname,
                                  const arg_list& xargs,
                                  const poset_path& xschema_path,
                                  bool xauto_access)

    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // Make the new state.

  new_state(xns, xname, xargs, xschema_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}

// PROTECTED FUNCTIONS

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset()
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(!is_attached());
  ensure(!top().is_attached());
  ensure(!bottom().is_attached());
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(const binary_section_space_schema_poset& xother)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(is_same_state(&xother));
}

fiber_bundle::binary_section_space_schema_poset::
~binary_section_space_schema_poset()
{
  // Preconditions:

  // Body:

  // Nothing to do; base class does it all.
  // Currently, this routine exists mostly for the precondition,
  // which is the same as poset_state_handle::~poset_state_handle.
  // With this precondition in place, the source of a precondition
  // violation will be clearer to the client.

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(namespace_poset* xhost,
                                  const string& xname,
                                  const sec_rep_descriptor& xrep,
                                  poset_state_handle& xbase_space,
                                  const poset_state_handle& xfiber_space,
                                  bool xauto_access)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // Make the new state.

  new_state(xhost, xname, xrep, xbase_space, xfiber_space, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(namespace_poset& xns,
                                  const string& xname,
                                  const poset_path& xrep_path,
                                  const poset_path& xbase_path,
                                  const poset_path& xfiber_path,
                                  bool xauto_access)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{

  // Preconditions:

  require(precondition_of(new_state(same args)));

  // Body:

  // Make the new state.

  new_state(xns, xname, xrep_path, xbase_path, xfiber_path, xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(same args)));
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(const namespace_poset* xns, pod_index_type xindex)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_member(xindex));
  require(xns->is_jim(xindex));

  // Body:

  attach_to_state(xns, xindex);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(const namespace_poset* xns, const scoped_index& xindex)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_member(xindex));
  require(xns->is_jim(xindex));

  // Body:

  attach_to_state(xns, xindex.hub_pod());

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(const namespace_poset* xns, const string& xname)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_accessible());
  require(xns->contains_member(xname));

  // Body:

  attach_to_state(xns, xname);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

fiber_bundle::binary_section_space_schema_poset::
binary_section_space_schema_poset(const namespace_poset_member* xmbr)
    : section_space_schema_poset(new binary_section_space_schema_member,
                                 new binary_section_space_schema_member)
{
  // Preconditions:

  require(xmbr != 0);
  require(xmbr->is_jim());
  require(xmbr->state_is_read_accessible());

  // Body:

  attach_to_state(xmbr);

  // Postconditions:

  ensure(postcondition_of(attach_to_state(same args)));
}

void
fiber_bundle::binary_section_space_schema_poset::
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

  require(xns.arg_is_auto_read_accessible("rep_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("base_space_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("fiber_space_path", xargs, xauto_access));
  
  // Body:

  // Nothing to do.  

  // Done.
  
#ifdef DIAGNOSTIC_OUTPUT
  cout << "binary_section_space_schema_poset::initialize_arg_list:xargs: " << endl 
       << xargs << endl;
#endif

  // Postconditions:
  
  // Exit:

  return;
}

bool
fiber_bundle::binary_section_space_schema_poset::
make_prototype()
{
  // Preconditions:

  // Body:

  poset_type ltype = BINARY_SECTION_SPACE_SCHEMA_POSET_ID;

  binary_section_space_schema_poset* lproto =
    new binary_section_space_schema_poset;

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return true;
}

// PRIVATE FUNCTIONS


// ===========================================================
// SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::poset_path&
fiber_bundle::binary_section_space_schema_poset::
standard_schema_path()
{
  // Preconditions:

  // Body:

  static const poset_path
  result(standard_schema_poset_name(), "binary_section_space_schema_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::binary_section_space_schema_poset::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false).state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  // This class doesn't add any dofs.

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              section_space_schema_poset::standard_schema_path(),
                              "",
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}

sheaf::pod_index_type
fiber_bundle::binary_section_space_schema_poset::
get_index_from_components(pod_index_type xbase_space_id,
                          pod_index_type xfiber_schema_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_id));
  require(fiber_schema().contains_member(xfiber_schema_id));


  // Body:

  /// @hack Cartesian product subspace hack. Should be using product id space.
  // Assume base space id is first index, fiber schema id is second. 

  pod_index_type result =
    xbase_space_id*base_space_stride() +
    xfiber_schema_id*fiber_schema_stride();

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
fiber_bundle::binary_section_space_schema_poset::
type_id() const
{
  return BINARY_SECTION_SPACE_SCHEMA_POSET_ID;
}

const char*
fiber_bundle::binary_section_space_schema_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "binary_section_space_schema_poset";

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::binary_section_space_schema_poset::
new_state(namespace_poset* xns,
          const string& xname,
          const sec_rep_descriptor& xrep,
          poset_state_handle& xbase_space,
          const poset_state_handle& xfiber_space,
          bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(xns, xname, xbase_space.index(), xfiber_space.index(), xrep.host()->index(), xrep.index(), xauto_access)));

  // Body:

  new_state(xns,
            xname,
            xrep.host()->index(),
            xrep.index(),
            xbase_space.index(),
            xfiber_space.index(),
            xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(xns, xname, xbase_space.index(), xfiber_space.index(), xrep.host()->index(), xrep.index(), xauto_access)));

  // Exit:

  return;
}

void
fiber_bundle::binary_section_space_schema_poset::
new_state(namespace_poset* xns,
          const string& xname,
          pod_index_type xrep_poset_id,
          pod_index_type xrep_member_id,
	  pod_index_type xbase_space_poset_id,
          pod_index_type xfiber_space_poset_id,
          bool xauto_access)
{

  // Preconditions:

  require(xns != 0);
  require(xauto_access || xns->in_jim_edit_mode());

  require(poset_path::is_valid_name(xname));
  require(!xns->contains_poset(xname, xauto_access));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.
  /// @hack unexecutable because may not have access.

  require(unexecutable(xname != xns->name()));


  require(xns->contains_poset_member(standard_schema_path()));
  require(xauto_access ||
          xns->member_poset(standard_schema_path()).state_is_read_accessible());

  require(xns->contains_poset_member(xrep_poset_id, xrep_member_id));
  require(xauto_access ||
          xns->member_poset(xrep_poset_id).state_is_read_accessible());

  require(xns->contains_poset(xbase_space_poset_id));
  require(xauto_access ||
          xns->member_poset(xbase_space_poset_id).state_is_read_accessible());
  require(unexecutable("base space schema conforms to base_space_member::static_schema_path"));


  require(xns->contains_poset(xfiber_space_poset_id));
  require(xauto_access ||
          xns->member_poset(xfiber_space_poset_id).state_is_read_accessible());

  //  require(rep_is_valid(xns, xrep_poset_id, xrep_member_id, xbase_space_poset_id));

  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  // Get a temporary handle to the schema.

  schema_poset_member lschema(xns, standard_schema_path(), xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&lschema, BINARY_SECTION_SPACE_SCHEMA_POSET_ID, xname);

  // Cleanup temporary schema handle.

  if(xauto_access)
  {
    lschema.release_access();
  }

  lschema.detach_from_state();

  // Get write access.

  get_read_write_access();

  // Initialize the namespace features;
  // must be done before initialize_table_dofs
  // so that postconditions there can be evaluated.

  if(xauto_access)
  {
    xns->begin_jim_edit_mode(true);
  }

  initialize_namespace(*xns, xname);

  if(xauto_access)
  {
    xns->end_jim_edit_mode(true, true);
  }

  // Initialize the table dofs.
  // Must be called before initialize_standard_members
  // because precondition contains_member in put_member_dof_tuple_id
  // called from new_member indirectly needs table dofs.

  //  initialize_table_dofs();

  // Initialize the row structure.

  initialize_standard_subposets(xname);
  initialize_standard_members();

  // Set the standard id spaces.

  update_standard_member_id_spaces();

  // Now invariant should be satisfied

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_attached());
  ensure(!in_jim_edit_mode());
  ensure(has_standard_row_dof_tuple_ct());
  ensure(has_standard_subposet_ct());
  ensure(member_id_spaces(false).has_only_standard_id_spaces());
  ensure(rep().is_attached());
//   ensure(rep_poset_id() ==~ xrep_poset_id);
//   ensure(rep_member_id() ==~ xrep_member_id);
  ensure(base_space().is_attached());
//   ensure(base_space_poset_id() == xbase_space_poset_id.hub_pod());
  ensure(base_space_member_id_ub() > 0);
  ensure(base_space_stride() == fiber_schema_member_id_ub()*fiber_schema_stride());
  ensure(db() >= 0);
  ensure(fiber_schema().is_attached());
//   ensure(fiber_schema_poset_id() == fiber_schema().index().hub_pod());
  ensure(fiber_schema_member_id_ub() > 0);
  ensure(fiber_schema_stride() > 0);
  ensure(df() > 0);
//   ensure(fiber_space_poset_id() == xfiber_space_poset_id.hub_pod());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

void
fiber_bundle::binary_section_space_schema_poset::
new_state(namespace_poset* xns,
          const string& xname,
          const scoped_index& xrep_poset_id,
          const scoped_index& xrep_member_id,
          const scoped_index& xbase_space_poset_id,
          const scoped_index& xfiber_space_poset_id,
          bool xauto_access)
{

  // Preconditions:

  require(precondition_of(new_state(xns, xname,
				    xrep_poset_id.hub_pod(),
				    xrep_member_id.hub_pod(),
				    xbase_space_poset_id.hub_pod(),
				    xfiber_space_poset_id.hub_pod(),
				    xauto_access)));

  // Body:

  new_state(xns, xname,
	    xrep_poset_id.hub_pod(),
	    xrep_member_id.hub_pod(),
	    xbase_space_poset_id.hub_pod(),
	    xfiber_space_poset_id.hub_pod(),
	    xauto_access);

  // Postconditions:

  ensure(postcondition_of(new_state(xns, xname,
				    xrep_poset_id.hub_pod(),
				    xrep_member_id.hub_pod(),
				    xbase_space_poset_id.hub_pod(),
				    xfiber_space_poset_id.hub_pod(),
				    xauto_access)));
 
  // Exit:

  return;
}

void
fiber_bundle::binary_section_space_schema_poset::
new_state(namespace_poset& xns,
          const string& xname,
          const poset_path& xrep_path,
          const poset_path& xbase_path,
          const poset_path& xfiber_path,
          bool xauto_access)
{

  // Preconditions:

  require(xauto_access || xns.state_is_read_write_accessible());
  require(poset_path::is_valid_name(xname));
  require(!xns.contains_poset(xname, xauto_access));

  /// @hack the following is necessary because
  /// the i/o subsystem can't handle poset with same name as namespace.
  /// @todo fix the i/o subsystem and remove these preconditions.
  /// @hack unexecutable because may not have access.

  require(unexecutable(xname != xns.name()));


  require(xrep_path.full());
  require(xns.contains_poset_member(xrep_path));
  require(xauto_access || xns.member_poset(xrep_path).state_is_read_accessible());

  require(!xbase_path.poset_name().empty());
  require(xns.contains_poset(xbase_path));
  require(xauto_access || xns.member_poset(xbase_path).state_is_read_accessible());
  require(unexecutable("base space schema conforms to base_space_member::static_schema_path"));

  require(!xfiber_path.poset_name().empty());
  require(xns.contains_poset(xfiber_path));
  require(xauto_access || xns.member_poset(xfiber_path).state_is_read_accessible());

  // Body:

  poset_state_handle& lrep_host = xns.member_poset(xrep_path, xauto_access);
  pod_index_type lrep_poset_id  = lrep_host.index().pod();

  if(xauto_access)
  {
    lrep_host.get_read_access();
  }

  pod_index_type lrep_mbr_id =
    lrep_host.member_id(xrep_path.member_name(), false);

  if(xauto_access)
  {
    lrep_host.release_access();
  }

  pod_index_type lbase_poset_id  =
    xns.member_poset(xbase_path, xauto_access).index();
  pod_index_type lfiber_poset_id =
    xns.member_poset(xfiber_path, xauto_access).index();

  new_state(&xns,
            xname,
            lrep_poset_id,
            lrep_mbr_id,
            lbase_poset_id,
            lfiber_poset_id,
            xauto_access);

  // Postconditions:

  ensure(xns.contains_poset(xname));

  // Exit:

  return;
}

void
fiber_bundle::binary_section_space_schema_poset::
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
  
  require(xns.arg_is_auto_read_accessible("rep_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("base_space_path", xargs, xauto_access));
  require(xns.arg_is_auto_read_accessible("fiber_space_path", xargs, xauto_access));  

  require(rep_is_valid(xns, xargs, xauto_access));

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

  _state = new poset_state(&lschema, BINARY_SECTION_SPACE_SCHEMA_POSET_ID, xname);

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
  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(base_space_member_id_ub() > 0);
  ensure(base_space_stride() == fiber_schema_member_id_ub()*fiber_schema_stride());
  ensure(db() >= 0);
  ensure(fiber_schema().is_attached());
  ensure(fiber_schema_member_id_ub() > 0);
  ensure(fiber_schema_stride() > 0);
  ensure(df() > 0);
  ensure(fiber_space().is_attached());

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
fiber_bundle::binary_section_space_schema_poset::
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

  require(unexecutable("rep in xdof_map exists"));
  require(unexecutable("rep in xdof_map is read accessible"));

  require(unexecutable("base space in xdof_map exists"));
  require(unexecutable("base space in xdof_map is read accessible"));

  require(unexecutable("fiber space in xdof_map exists"));
  require(unexecutable("fiber space in xdof_map is read accessible"));

  require(unexecutable("rep in xdof_map is valid for base and fiber in xdof_map"));


  // Body:

  // Disable invariant checking in
  // member functions until construction finished.

  disable_invariant_check();

  string lname = name_space()->member_name(index());

  // Create the poset state object;
  // allocates the data structures but does not (fully) initialize them.

  _state = new poset_state(&xschema, BINARY_SECTION_SPACE_SCHEMA_POSET_ID, lname);

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

  initialize_standard_subposets(lname);
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
  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_schema().is_attached());
  ensure(fiber_space().is_attached());

  // Now we're finished, release all access

  release_access();

  // One final postcondition

  ensure(state_is_not_read_accessible());

  // Exit:

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// COVER RELATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::binary_section_space_schema_poset::
contains_link(pod_index_type xgreater, pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  pod_index_type lgreater_base_id = get_base_space_id_from_index(xgreater);
  pod_index_type lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  pod_index_type llesser_base_id = get_base_space_id_from_index(xlesser);
  pod_index_type llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);

  result =
    ( base_space().contains_link(lgreater_base_id, llesser_base_id) && (lgreater_fiber_id == llesser_fiber_id)) ||
    ( (lgreater_base_id == llesser_base_id) && fiber_schema().contains_link(lgreater_fiber_id, llesser_fiber_id));

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fiber_bundle::binary_section_space_schema_poset::
cover_ct(bool xlower, pod_index_type xhub_id) const
{
  size_type result;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xhub_id));

  // Body:

  result = base_space().cover_ct(xlower, get_base_space_id_from_index(xhub_id)) +
           fiber_schema().cover_ct(xlower, get_fiber_schema_id_from_index(xhub_id));

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::binary_section_space_schema_poset::
le(const pod_index_type xgreater, const pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  pod_index_type lgreater_base_id = get_base_space_id_from_index(xgreater);
  pod_index_type llesser_base_id = get_base_space_id_from_index(xlesser);
  pod_index_type lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  pod_index_type llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);

  result = base_space().le(lgreater_base_id, llesser_base_id) &&
           fiber_schema().le(lgreater_fiber_id, llesser_fiber_id);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::binary_section_space_schema_poset::
leqv(pod_index_type xgreater, pod_index_type xlesser) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xlesser));
  require(contains_member(xgreater));

  // Body:

  pod_index_type lgreater_base_id = get_base_space_id_from_index(xgreater);
  pod_index_type llesser_base_id = get_base_space_id_from_index(xlesser);
  pod_index_type lgreater_fiber_id = get_fiber_schema_id_from_index(xgreater);
  pod_index_type llesser_fiber_id = get_fiber_schema_id_from_index(xlesser);

  result = base_space().leqv(lgreater_base_id, llesser_base_id) &&
           fiber_schema().leqv(lgreater_fiber_id, llesser_fiber_id);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::binary_section_space_schema_poset::
is_jem(pod_index_type xhub_id, pod_index_type xother) const
{
  bool result = false;

  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xhub_id));
  require(contains_member(xother));

  // Body:

  result =
    base_space().is_jem(get_base_space_id_from_index(xhub_id), get_base_space_id_from_index(xother)) &&
    fiber_schema().is_jem(get_fiber_schema_id_from_index(xhub_id), get_fiber_schema_id_from_index(xother));

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::binary_section_space_schema_poset::
greatest_jem(pod_index_type xhub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xhub_id));

  // Body:

  pod_index_type lbase_jem = base_space().greatest_jem(get_base_space_id_from_index(xhub_id));
  pod_index_type lfiber_jem = fiber_schema().greatest_jem(get_fiber_schema_id_from_index(xhub_id));

  pod_index_type result = get_index_from_components(lbase_jem, lfiber_jem);

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::binary_section_space_schema_poset::
least_jem(pod_index_type xhub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(contains_member(xhub_id));

  // Body:

  pod_index_type lbase_jem = base_space().least_jem(get_base_space_id_from_index(xhub_id));
  pod_index_type lfiber_jem = fiber_schema().least_jem(get_fiber_schema_id_from_index(xhub_id));

  pod_index_type result = get_index_from_components(lbase_jem, lfiber_jem);

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::binary_section_space_schema_poset::
merge_jems(pod_index_type xjem1, pod_index_type xjem2)
{
  // Preconditions:

  require(xjem1 !=~ xjem2);
  require(!is_jem(xjem1, BOTTOM_INDEX));
  require(state_is_read_write_accessible());
  require(contains_member(xjem1));
  require(contains_member(xjem2));
  require(!is_jim(xjem1));
  require(!is_jim(xjem2));
  require(cover_is_equal(LOWER, xjem1, xjem2));

  // Body:

  not_implemented();

  /// @todo make this class immutable; remove this function.

  // Postconditions:

  ensure(le(xjem1, xjem2));

  // Exit

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::schema_poset_member*
fiber_bundle::binary_section_space_schema_poset::
new_schema_handle(const string& xid_space_name,
                  pod_index_type xschema_member_ext_id,
                  pod_index_type xbase_space_ext_id,
                  pod_index_type xfiber_schema_ext_id,
                  pod_index_type xlocal_schema_ext_id)
{
  // Preconditions:

  // Body:

  // Create a handle of the type appropriate for members of this
  // which will be used as a schema.

  schema_poset_member* result = new binary_section_space_schema_member();

  // Get the internal id for the base space.

  pod_index_type lbase_id =
    base_space().get_int_id(xbase_space_ext_id, xid_space_name, false);

  // Get the internal id for the fiber schema.

  pod_index_type lfiber_id =
    fiber_schema().get_int_id(xfiber_schema_ext_id, xid_space_name, false);

  // Get the member id from its components

  pod_index_type lint_id = get_index_from_components(lbase_id, lfiber_id);

  // Attach the handle.

  result->attach_to_state(this, lint_id);

  // Postconditions:

  ensure(result != 0);
  ensure(schema_is_ancestor_of(result));
  ensure(result->is_attached());

  // Exit

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::binary_section_space_schema_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const binary_section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::binary_section_space_schema_poset::
invariant() const
{
  bool result = true;

  result = result && section_space_schema_poset::invariant();

  if(invariant_check())
  {
    disable_invariant_check();

    /// @todo finish binary_section_space_schema_poset::invariant() const
    /// What is the invariant?

    invariance(state_is_read_accessible() ?
               base_space().schema().conforms_to(base_space_member::standard_schema_path()) :
               true);


    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

fiber_bundle::binary_section_space_schema_poset*
fiber_bundle::binary_section_space_schema_poset::
clone() const
{
  binary_section_space_schema_poset* result;

  // Preconditions:

  // Body:

  result = new binary_section_space_schema_poset;

  // Postconditions:

  ensure(result != 0);
  ensure(!result->is_attached());

  // Exit

  return result;
}

fiber_bundle::binary_section_space_schema_poset&
fiber_bundle::binary_section_space_schema_poset::
operator=(const poset_state_handle& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  poset_state_handle::operator=(xother);

  // Postconditions:

  ensure(is_same_state(&xother));

  // Exit:

  return *this;
}

// PRIVATE FUNCTIONS



