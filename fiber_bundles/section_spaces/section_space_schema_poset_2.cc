
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
/// Implementation for class section_space_schema_poset.

#include "SheafSystem/section_space_schema_poset.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/arg_list.h"
#include "SheafSystem/array_poset_dof_map.h"
#include "SheafSystem/index_iterator.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/list_cover_set.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/namespace_poset_member.h"
#include "SheafSystem/pod_types.h"
#include "SheafSystem/poset_member_iterator.h"
#include "SheafSystem/poset_state.h"
#include "SheafSystem/schema_descriptor.h"
#include "SheafSystem/section_space_schema_member.impl.h"
#include "SheafSystem/section_space_schema_table_dofs_type.h"
#include "SheafSystem/std_limits.h"
#include "SheafSystem/tern.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const std::string&
fiber_bundle::section_space_schema_poset::
standard_schema_poset_name()
{

  // Preconditions:


  // Body:

  static const string result("section_space_schema_schema");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

const sheaf::poset_path&
fiber_bundle::section_space_schema_poset::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path
  result(standard_schema_poset_name(), "section_space_schema_schema");

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
make_standard_schema(namespace_poset& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xns.contains_poset(standard_schema_poset_name(), false));
  require(xns.member_poset(standard_schema_poset_name(), false)->state_is_read_write_accessible());
  require(!xns.contains_poset_member(standard_schema_path(), false));

  // Body:

  string ldof_specs;

  // Row dofs are same as row dofs of primitives:

  ldof_specs =  "size SIZE_TYPE false";
  ldof_specs += " alignment SIZE_TYPE false";
  ldof_specs += " type POD_INDEX_TYPE false";

  // Table dofs:

  ldof_specs += " rep_path C_STRING true";
  ldof_specs += " base_space_path C_STRING true";
  ldof_specs += " fiber_space_path C_STRING true";

  schema_poset_member lschema(xns,
                              standard_schema_path().member_name(),
                              poset_path(standard_schema_poset_name(), "bottom"),
                              ldof_specs,
                              false,
                              false);

  lschema.detach_from_state();

  // Postconditions:

  ensure(xns.contains_poset_member(standard_schema_path()));

  // Exit

  return;
}

fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_poset::
rep()
{
  return _rep;
}

const fiber_bundle::sec_rep_descriptor&
fiber_bundle::section_space_schema_poset::
rep() const
{
  return _rep;
}

bool
fiber_bundle::section_space_schema_poset::
rep_is_valid(const sec_rep_descriptor& xrep, const poset_state_handle& xbase_space)
{
  bool result;

  // Preconditions:

  require(xrep.state_is_read_accessible());
  require(xbase_space.state_is_read_accessible());

  // Body:

  // Discretization subposet must exist.

  result = xbase_space.includes_subposet(xrep.discretization_subposet_name());

  // Discretization must have a non-empty id space;
  // see section_space_schems_index_map - doesn't support empty factors.

  subposet ldisc_sp(&xbase_space, xrep.discretization_subposet_name());
  result = result && ldisc_sp.has_id_space() && !ldisc_sp.id_space().is_empty();
  ldisc_sp.detach_from_state();

  // Evaluation subposets must exist.

  result = result && xbase_space.includes_subposet(xrep.evaluation_subposet_name());

  /// @todo check for compatibility between base space and evaluator family.
  /// Just instantiate the evaluator family and see if it contains an entry
  /// for each dof tuple of the base space.

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
rep_is_valid(const namespace_poset& xns, const arg_list& xargs, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xargs.conforms_to(xns, standard_schema_path(), true, xauto_access));
  
  require(xns.contains_poset_member(poset_path(xargs.value("rep_path")), xauto_access));
  require(xns.member_poset(poset_path(xargs.value("rep_path")), xauto_access)->state_is_auto_read_accessible(xauto_access));

  require(xns.contains_poset(poset_path(xargs.value("base_space_path")), xauto_access));
  require(xns.member_poset(poset_path(xargs.value("base_space_path")), xauto_access)->state_is_auto_read_accessible(xauto_access));

  // Body:

  poset_state_handle& lbase_space = *xns.member_poset(poset_path(xargs.value("base_space_path")), xauto_access);
  sec_rep_descriptor lrep(&xns, xargs.value("rep_path"), xauto_access);

  if(xauto_access)
  {
    lbase_space.get_read_access();
    lrep.get_read_access();
  }

  result = rep_is_valid(lrep, lbase_space);

  if(xauto_access)
  {
    lrep.release_access();
    lbase_space.release_access();
  }

  lrep.detach_from_state();

  // Postconditions:

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_poset::
db() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = _base_space->max_db();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

fiber_bundle::base_space_poset&
fiber_bundle::section_space_schema_poset::
base_space()
{
  return *_base_space;
}

const fiber_bundle::base_space_poset&
fiber_bundle::section_space_schema_poset::
base_space() const
{
  return *_base_space;
}

int
fiber_bundle::section_space_schema_poset::
df() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  /// @hack The fibers don't really have a dimension at this level of abstraction,
  /// dimesion is a vector space notion. The closest we can come is the number
  /// of columns in the representation, that is, the row dof ct.

  result = _fiber_space->schema().row_dof_ct();

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}

sheaf::poset_state_handle&
fiber_bundle::section_space_schema_poset::
fiber_schema()
{
  require(state_is_read_accessible());
  
  return *_fiber_space->schema().host();
}

const sheaf::poset_state_handle&
fiber_bundle::section_space_schema_poset::
fiber_schema() const
{
  require(state_is_read_accessible());

  return *_fiber_space->schema().host();
}

sheaf::poset&
fiber_bundle::section_space_schema_poset::
fiber_space()
{
  return *_fiber_space;
}

const sheaf::poset&
fiber_bundle::section_space_schema_poset::
fiber_space() const
{
  return *_fiber_space;
}

sheaf::subposet&
fiber_bundle::section_space_schema_poset::
discretization()
{
  return _discretization;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_poset::
discretization() const
{
  return _discretization;
}

sheaf::subposet&
fiber_bundle::section_space_schema_poset::
evaluation()
{
  return _evaluation;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_poset::
evaluation() const
{
  return _evaluation;
}

string
fiber_bundle::section_space_schema_poset::
evaluator_family_name() const
{
  // Preconditions:

  require(rep().state_is_read_accessible());

  // Body:

  string result = _rep.evaluator_family_name();

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
tuple(const scoped_index& xindex,
      scoped_index& xbase_space_id,
      scoped_index& xfiber_schema_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_homogeneous(xindex));

  // Body:

  pod_index_type lbase_space_id, lfiber_schema_id;
  tuple(xindex.hub_pod(), lbase_space_id, lfiber_schema_id);

  xbase_space_id.put(base_space().member_hub_id_space(false), lbase_space_id);
  xfiber_schema_id.put(fiber_schema().member_hub_id_space(false), lfiber_schema_id);

  // Postconditions:

  ensure(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_poset::
tuple(pod_index_type xindex,
      pod_index_type& xbase_space_id,
      pod_index_type& xfiber_schema_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(is_homogeneous(xindex));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_poset::
ordinal(const scoped_index& xbase_space_id,
	const scoped_index& xfiber_schema_id,
	scoped_index& xindex) const
{
  // Preconditions:

  require(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  pod_index_type lindex;
  ordinal(xbase_space_id.hub_pod(), xfiber_schema_id.hub_pod(), lindex);

  xindex.put(member_hub_id_space(false), lindex);

  // Postconditions:

  ensure(is_homogeneous(xindex));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_poset::
ordinal(pod_index_type xbase_space_id,
	pod_index_type xfiber_schema_id,
	pod_index_type& xindex) const
{
  // Preconditions:

  require(contains_range_member(xbase_space_id, xfiber_schema_id, false));

  // Body:

  is_abstract();

  // Postconditions:

  ensure(is_homogeneous(xindex));

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_poset::
is_homogeneous(const scoped_index& xindex) const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return is_homogeneous(xindex.hub_pod());
}

bool
fiber_bundle::section_space_schema_poset::
is_homogeneous(pod_index_type xindex) const
{
  // Preconditions:

  // Body:

  bool result = false; // Just to silence compiler

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
contains_range_member(const scoped_index& xbase_space_id,
		      const scoped_index& xfiber_schema_id,
		      bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  bool result = contains_range_member(xbase_space_id.hub_pod(),
				      xfiber_schema_id.hub_pod(),
				      xauto_access);

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
contains_range_member(pod_index_type xbase_space_id,
		      pod_index_type xfiber_schema_id,
		      bool xauto_access) const
{
  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));

  // Body:

  bool result = false; // Just to silence compiler

  is_abstract();

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
update_hub_id_space(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

// PROTECTED FUNCTIONS

fiber_bundle::section_space_schema_poset::
~section_space_schema_poset()
{
  // Preconditions:

  // Body:

  _rep.detach_from_state();
  _discretization.detach_from_state();
  _evaluation.detach_from_state();

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::section_space_schema_poset::
section_space_schema_poset(section_space_schema_member* xtop, section_space_schema_member* xbottom)
  : poset(xtop, xbottom),
    _base_space(0),
    _fiber_space(0)
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
initialize_table_dof_subposet()
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(fiber_schema().is_attached());

  // Body:

  // Create the table dof subposet.

  table_dof_subposet().new_state(this);
  table_dof_subposet().put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

  // Enter jim edit mode.

  begin_jim_edit_mode(false);

  // Create members for the table dofs.

  pod_index_type lid;

  index_space_iterator& litr =
    fiber_schema().table_dof_subposet().id_space().get_iterator();
  while(!litr.is_done())
  {
    /// @todo Remove.
//     // Construct a member at the same hub id as the fiber schema table
//     // dof member.

//     new_member(litr.hub_pod(), true, 0, false);

//     // Link member to top and bottom (table dof is an atom).

//     new_link(TOP_INDEX, litr.hub_pod());
//     new_link(litr.hub_pod(), BOTTOM_INDEX);

    // Insert member into the subposets.

    ordinal(BOTTOM_INDEX, litr.hub_pod(), lid);
    table_dof_subposet().insert_member(lid);

    litr.next();
  }
  fiber_schema().table_dof_subposet().id_space().release_iterator(litr);

  // Initialize the table dof subposet id space.

  initialize_dof_id_space(table_dof_subposet());

  end_jim_edit_mode(false, false);

  // Now the cover relation graph invariant is satisfied

  crg().enable_invariant_check();

  // Postconditions:

  ensure(crg().invariant());
  ensure(table_dof_subposet().is_attached());

  // Exit:

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// STATE FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::poset_type
fiber_bundle::section_space_schema_poset::
type_id() const
{
  return SECTION_SPACE_SCHEMA_POSET_ID;
}

const char*
fiber_bundle::section_space_schema_poset::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "section_space_schema_poset";

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
get_read_access() const
{
  // Preconditions:

  require(is_attached());

  // Body:

  int old_access_request_depth = access_request_depth();

  rep().get_read_access();
  base_space().get_read_access();
  fiber_space().get_read_access();
  poset::get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(rep().state_is_read_accessible());
  ensure(base_space().state_is_read_accessible());
  ensure(fiber_space().state_is_read_accessible());
  ensure(fiber_schema().state_is_read_accessible());

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
get_read_write_access(bool xrelease_read_only_access)
{
  // Preconditions:

  require(is_attached());
  require(!xrelease_read_only_access ? state_is_not_read_only_accessible() : true);


  // Body:

  int old_access_request_depth = access_request_depth();

  rep().get_read_access();
  base_space().get_read_access();
  fiber_space().get_read_access();
  poset::get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(rep().state_is_read_accessible());
  ensure(base_space().state_is_read_accessible());
  ensure(fiber_space().state_is_read_accessible());
  ensure(fiber_schema().state_is_read_accessible());

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
release_access(bool xall) const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int old_access_request_depth = access_request_depth();

  // Release at least one level of access for this. If xall, release all levels
  // of access for this. Since each level of access to this also
  // acquired a level of access to the rep, the base space, and the fiber space,
  // release the same number of levels of access to each of these.
  // Note that this may not be all the levels of access of these.

  do
  {
    // Release one level of access.

    rep().release_access(false);
    base_space().release_access(false);
    fiber_space().release_access(false);
    poset::release_access(false);
  }
  while(xall && state_is_read_accessible());

  // Postconditions:

  ensure(!xall ? access_request_depth() == old_access_request_depth - 1 :
         access_request_depth() == 0);
  ensure(access_request_depth() == 0 ? state_is_not_read_accessible() : true);
  ensure(unexecutable("schema, rep, base, base schema, fiber, and fiber schema access released"));

  // Exit

  return;
}

// PROTECTED FUNCTIONS

void
fiber_bundle::section_space_schema_poset::
initialize_handle_data_members(const namespace_poset& xns)
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  // Attach the handle data members that depend on the table dofs
  // and are required to get access.

  table_dofs_type& ldofs = sheaf::table_dofs(*this);

  // Attach the rep handle to the current state.

  /// @error Attach_to_state requires access, but since this is not attached yet,
  /// we can't tell what we need access to, so we can't require it.
  /// This is really an error in attach_to_state - it shouldn't require access.

  poset_path lrep_path(ldofs.rep_path);
  rep().attach_to_state(&xns, lrep_path, true);

  // Attach the component handles to the current state.

  poset_path lbase_space_path(ldofs.base_space_path);
  _base_space = xns.member_poset<base_space_poset>(lbase_space_path, true);

  poset_path lfiber_space_path(ldofs.fiber_space_path);
  _fiber_space = xns.member_poset<poset>(lfiber_space_path, true);

  // Attach the subposet handles to the current state.

  base_space().get_read_access();
  rep().get_read_access();
  discretization().attach_to_state(&(base_space()), rep().discretization_subposet_name());
  evaluation().attach_to_state(&(base_space()), rep().evaluation_subposet_name());

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_space().is_attached());
  ensure(discretization().is_attached());
  ensure(evaluation().is_attached());

  rep().release_access();
  base_space().release_access();

  // Postconditions:


  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
attach_handle_data_members()
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  poset::attach_handle_data_members();

  table_dofs_type& ldofs = sheaf::table_dofs(*this);
  namespace_poset* lns = name_space();

  // Attach the rep handle to the current state.

  /// @error Attach_to_state requires access, but since this is not attached yet,
  /// we can't tell what we need access to, so we can't require it.
  /// This is really an error in attach_to_state - it shouldn't require access.

  rep().attach_to_state(lns, ldofs.rep_path, true);

  // Attach the component handles to the current state.

  poset_path lbase_space_path(ldofs.base_space_path);
  _base_space = lns->member_poset<base_space_poset>(lbase_space_path, true);

  poset_path lfiber_space_path(ldofs.fiber_space_path);
  _fiber_space = lns->member_poset<poset>(lfiber_space_path, true);

  // Attach the subposet handles to the current state.

  discretization().attach_to_state(&(base_space()), rep().discretization_subposet_name());
  evaluation().attach_to_state(&(base_space()), rep().evaluation_subposet_name());

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  //  ensure(fiber_schema().is_attached());
  ensure(fiber_space().is_attached());
  ensure(discretization().is_attached());
  ensure(evaluation().is_attached());


  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
terminate_access()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:

  define_old_variable(int old_rep_access_request_depth         = rep().access_request_depth());
  define_old_variable(int old_base_space_access_request_depth  = base_space().access_request_depth());
  define_old_variable(int old_fiber_space_access_request_depth = fiber_space().access_request_depth());

  // Release all levels of access this poset has to its various parts,
  // but do not release access to the state of this because
  // we are going to delete the state and don't want another
  // client able to sneak in and get access before we do.

  /// @issue we should either prevent termination if other clients
  /// exist or have some mechanism for notifying them of termination.
  /// Currently we can't do either one.

  string rep_name(rep().name());
  string base_space_name(base_space().name());
  string fiber_space_name(fiber_space().name());

#ifdef DIAGNOSTIC_OUTPUT
  cout << "poset: " << name() << endl
       << "\trep: " << rep_name
       << "  old lvl:" << old_rep_access_request_depth << endl
       << "\tbase_space: " << base_space_name
       << "  old lvl:" << old_base_space_access_request_depth << endl
       << "\tfiber_space: " << fiber_space_name
       << "  old lvl:" << old_fiber_space_access_request_depth << endl;
#endif

  int old_access_request_depth = access_request_depth();
  for(size_type i=0; i<old_access_request_depth; ++i)
  {
    rep().release_access(false);
    base_space().release_access(false);
    fiber_space().release_access(false);
  }

  define_old_variable(int rep_access_request_depth         = rep().access_request_depth());
  define_old_variable(int base_space_access_request_depth  = base_space().access_request_depth());
  define_old_variable(int fiber_space_access_request_depth = fiber_space().access_request_depth());

#ifdef DIAGNOSTIC_OUTPUT
  cout << " \trep lvl:" << rep_access_request_depth
       << "  base_space lvl:" << base_space_access_request_depth
       << "  fiber_space lvl:" << fiber_space_access_request_depth
       << endl;
#endif

  // Detach and delete the state.

  poset::terminate_access();

  // Postconditions:

  ensure(!is_attached());
  ensure(unexecutable("state has been deleted"));
  ensure(rep_access_request_depth == (old_rep_access_request_depth - old_access_request_depth));
  ensure(base_space_access_request_depth == (old_base_space_access_request_depth - old_access_request_depth));
  ensure(fiber_space_access_request_depth == (old_fiber_space_access_request_depth - old_access_request_depth));

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMA FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// SCHEMATIZATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_member(bool xis_jim, const scoped_index& xdof_tuple_id)
{
  // Preconditions:

  require(precondition_of(poset_state_handle::new_member(xis_jim, xdof_tuple_id)));
  require(is_new_member_available());

  // Body:

  pod_index_type result =
    poset_state_handle::new_member(xis_jim, xdof_tuple_id);

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::new_member(xis_jim, xdof_tuple_id)));

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_member(bool xis_jim, poset_dof_map* xdof_map, bool xcopy_dof_map)
{
  // Preconditions:

  require(precondition_of(poset_state_handle::new_member(xis_jim, xdof_map, xcopy_dof_map)));
  require(is_new_member_available());

  // Body:

  pod_index_type result =
    poset_state_handle::new_member(xis_jim, xdof_map, xcopy_dof_map);

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::new_member(xis_jim, xdof_map, xcopy_dof_map)));

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_member_range(const std::string& xrange_type,
                 size_type xsize,
                 const block<scoped_index>& xdof_tuple_ids,
                 const block<pod_index_type>& xdata)
{
  /// @hack This function can not be available to the client.

  not_implemented();
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_poset::
top()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<section_space_schema_member*>(_top));
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_poset::
top() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<const section_space_schema_member*>(_top));
}

fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_poset::
bottom()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<section_space_schema_member*>(_bottom));
}

const fiber_bundle::section_space_schema_member&
fiber_bundle::section_space_schema_poset::
bottom() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return *(static_cast<const section_space_schema_member*>(_bottom));
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
member_id(const std::string& xbase_space_name, const std::string& xfiber_schema_name) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_name, false));
  require(fiber_schema().contains_member(xfiber_schema_name, false));

  // Body:

  pod_index_type lbase_space_id =
    base_space().member_id(xbase_space_name, false);
  pod_index_type lfiber_schema_id =
    fiber_schema().member_id(xfiber_schema_name, false);

  pod_index_type result;
  ordinal(lbase_space_id, lfiber_schema_id, result);

  // Postconditions:

  ensure(contains_member(result, false));

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
member_id(const std::string& xbase_space_name,
	  const std::string& xfiber_schema_name,
	  scoped_index& result) const
{
  // Postconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_name, false));
  require(fiber_schema().contains_member(xfiber_schema_name, false));

  // Body:

  result.put(member_hub_id_space(false),
	     member_id(xbase_space_name, xfiber_schema_name));

  // Postconditions:

  ensure(contains_member(result, false));

  // Exit:

  return;
}

bool
fiber_bundle::section_space_schema_poset::
is_new_member_available() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  bool result =
    member_hub_id_space(false).is_empty() ||          // For the construction of bottom
    !member_id_spaces(false).is_reserved_term_full(); // Can't expand past the first reserved term

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// COVER RELATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// POWERSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

/// @todo Remove.
// $$SCRIBBLE: Remove version hack.

// int
// fiber_bundle::section_space_schema_poset::
// version_ct() const
// {
//   int result = 0;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(base_space().state_is_read_accessible());

//   // Body:

//   result = base_space().version_ct();

//   ensure(result >= 0);

//   // Exit

//   return result;
// }

// int
// fiber_bundle::section_space_schema_poset::
// version() const
// {
//   int result = 0;

//   // Preconditions:

//   require(state_is_read_accessible());
//   require(base_space().state_is_read_accessible());

//   // Body:

//   /// @hack section_space_schema version hack:
//   /// version of this is same as version of base space.

//   result = base_space().version();

//   // Postconditions:

//   ensure( has_version(result) );

//   // Exit

//   return result;
// }

// sheaf::pod_index_type
// fiber_bundle::section_space_schema_poset::
// version_index(int xversion) const
// {
//   // Preconditions:

//   require(state_is_read_accessible());
//   require(base_space().state_is_read_accessible());
//   require(has_version(xversion));

//   // Body:

//   pod_index_type result = base_space().version_index(xversion);

//   // Postconditions:

//   ensure(base_space().includes_subposet(result));

//   // Exit

//   return result;
// }

// sheaf::pod_index_type
// fiber_bundle::section_space_schema_poset::
// version_jims_index(int xversion) const
// {
//   // Preconditions:

//   require(state_is_read_accessible());
//   require(base_space().state_is_read_accessible());
//   require(has_version(xversion));

//   // Body:

//   pod_index_type result = base_space().version_jims_index(xversion);

//   // Postconditions:

//   ensure(base_space().includes_subposet(result));

//   // Exit

//   return result;
// }

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// I/O SUPPORT FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::index_iterator*
fiber_bundle::section_space_schema_poset::
get_decomposition(pod_index_type xindex) const
{
  /// @hack the product subposet hack, version 2.
  /// This member exists only to encapsulate the hack.

  // Preconditions:

  require(state_is_read_accessible());

  // It is precisely because we can't support product subposets
  // that we can't require the following here.

  // require(includes_subposet(xindex));

  // Body:

  // This routine should only be called for writing or reading row decompositions,
  // which is not supported for section_space_schema_posets.

  post_fatal_error_message("Product subposet hack, ver 2. Row decomposition i/o not supported for section space schema.");

  // Postconditions:

  // Exit:

  return 0;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
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
  case 1: // rep
    result = _rep.host()->index().pod();
    break;
  case 2: // fiber space
    result = _fiber_space->index().pod();
    break;
  case 3: // base
    result = _base_space->index().pod();
    break;
  default:
    result = invalid_pod_index();
    break;
  }

  // Postconditions:

  // Exit:

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC FUNCTIONS

bool
fiber_bundle::section_space_schema_poset::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const section_space_schema_poset*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
invariant() const
{
  bool result = true;

  invariance(poset::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(state_is_read_accessible() ? rep().state_is_read_accessible() : true);

    invariance(state_is_read_accessible() ? base_space().state_is_read_accessible() : true);

    invariance(state_is_read_accessible() ? fiber_space().state_is_read_accessible() : true);

    /// @todo make the following executable.

    invariance(unexecutable("rep.evaluator_family_name is compatible with base_space"));

    /// @todo finish section_space_schema_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

fiber_bundle::section_space_schema_poset&
fiber_bundle::section_space_schema_poset::
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

// PRIVATE FUNCTIONS


// ===========================================================
// EXPLICIT INSTANTIATIONS FOR CLASS SECTION_SPACE_SCHEMA_POSET
// ===========================================================

#ifndef DOXYGEN_SKIP_INSTANTIATIONS
 
template
SHEAF_DLL_SPEC 
fiber_bundle::section_space_schema_poset*
sheaf::namespace_poset::
member_poset<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_poset<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
contains_path<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_accessible<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;
 
template
SHEAF_DLL_SPEC 
bool
sheaf::namespace_poset::
path_is_auto_read_available<fiber_bundle::section_space_schema_poset>(const poset_path& xpath, bool xauto_access) const;

#endif // ifndef DOXYGEN_SKIP_INSTANTIATIONS
