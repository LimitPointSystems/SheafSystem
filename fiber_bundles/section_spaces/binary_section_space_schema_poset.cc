

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class binary_section_space_schema_poset.

#include "binary_section_space_schema_poset.h"

#include "abstract_poset_member.h"
#include "array_poset_dof_map.h"
#include "base_space_member.h"
#include "base_space_poset.h"
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
#include "sec_rep_descriptor_poset.h"
#include "sheaves_namespace.h"
#include "subposet.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BINARY_SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

fiber_bundle::binary_section_space_schema_poset&
fiber_bundle::binary_section_space_schema_poset::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          const poset_path& xbase_path,
          const poset_path& xfiber_path,
          const poset_path& xrep_path,
          bool xauto_access)
{
  // cout << endl << "Entering binary_section_space_schema_poset::new_table." << endl;

  // Preconditions:

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(xbase_path.full());
  require(xns.path_is_auto_read_accessible<base_space_poset>(xbase_path, xauto_access));

  require(!xfiber_path.empty());
  require(xns.path_is_auto_read_accessible(xfiber_path, xauto_access));

  require(xrep_path.full());
  require(xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(xrep_path, xauto_access));
  

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef binary_section_space_schema_poset table_type;

  table_type& result = *(new table_type());

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("base_space_path", xbase_path);
  lmap->put_dof("fiber_space_path", xfiber_path);
  lmap->put_dof("rep_path", xrep_path);
  
  // Create the state.

  result.new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }


  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(unexecutable("result.base_space_path() == xbase_space_path"));
  ensure(unexecutable("result.fiber_space_path() == xfiber_space_path"));
  ensure(unexecutable("result.rep_path() == xrep_path"));


  // Exit:

  // cout << "Leaving binary_section_space_schema_poset::new_table." << endl;
  return result;
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
new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map)
{

  // Preconditions:

  require(schema_is_ancestor_of(&xschema));
  require(xschema.state_is_read_accessible());

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

  string lname = xpath.poset_name();

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

  // $$SCRIBBLE: should merge two new_state signatures into a single routine
  // and move to poset_state_handle.
  //  initialize_handle_data_members(*name_space());
  initialize_handle_data_members(*xschema.name_space());

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

// PRIVATE FUNCTIONS



