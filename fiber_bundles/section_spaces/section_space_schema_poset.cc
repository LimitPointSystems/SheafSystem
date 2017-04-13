
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

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

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
#include "SheafSystem/array_poset_dof_map.h"
#include "SheafSystem/ij_product_structure.h"
#include "SheafSystem/index_iterator.h"
#include "SheafSystem/index_space_iterator.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/namespace_poset_member.h"
#include "SheafSystem/pod_types.h"
#include "SheafSystem/poset_member_iterator.h"
#include "SheafSystem/poset_state.h"
#include "SheafSystem/primary_index_space_handle.h"
#include "SheafSystem/schema_descriptor.h"
#include "SheafSystem/schema_poset_member.h"
#include "SheafSystem/section_space_schema_member.impl.h"
#include "SheafSystem/section_space_schema_table_dofs_type.h"
#include "SheafSystem/std_limits.h"
#include "SheafSystem/std_sstream.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

namespace
{
  /// @hack Cartesian product subspace hack. Should be using product id space.

  //
  // Fiber schema radix for ad-hoc factoring of section_space_schema ids.
  //
  const pod_index_type FIBER_SCHEMA_MEMBER_ID_UB = 256;

  //
  // Base space radix for ad-hoc factoring of section_space_schema ids.
  //
  const pod_index_type BASE_SPACE_MEMBER_ID_UB = 
    numeric_limits<pod_index_type>::max()/FIBER_SCHEMA_MEMBER_ID_UB;

  //
  // The increment in the member id when the id of the
  // fiber schema component is increased by one.
  //
  const pod_index_type FIBER_SCHEMA_STRIDE = 1;

  //
  // The increment in the member id when the id of the
  // base space component is increased by one.
  //
  const pod_index_type BASE_SPACE_STRIDE = FIBER_SCHEMA_MEMBER_ID_UB*FIBER_SCHEMA_STRIDE;
  
}

// ===========================================================
// SECTION_SPACE_SCHEMA_POSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

const sheaf::poset_path&
fiber_bundle::section_space_schema_poset::
standard_schema_path()
{
  // Preconditions:


  // Body:

  const poset_path& result = section_space_schema_member::standard_schema_path();

  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}

sheaf::poset_path
fiber_bundle::section_space_schema_poset::
rep_path(bool xauto_access) const
{
  // cout << endl << "Entering section_space_schema_poset::rep_path." << endl;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).rep_path);


  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving section_space_schema_poset::rep_path." << endl;
  return result;
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
is_multivalued() const
{
  // Preconditions:

  require(rep().state_is_read_accessible());
  require(base_space().state_is_read_accessible());

  // Body:

  bool result = !rep().multivalued_subposet_name().empty() &&
                base_space().includes_subposet(rep().multivalued_subposet_name());

  // Postconditions:

  // Exit:

  return result;
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

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
base_space_member_id_ub() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return BASE_SPACE_MEMBER_ID_UB;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
get_base_space_id_from_index(pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space_stride() > 0);

  // Body:

  pod_index_type result = xmbr_hub_id/base_space_stride();

  // Postconditions:

  ensure(result < base_space_member_id_ub());

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_poset::
get_base_space_id_from_index(const scoped_index& xmbr_id,
			     scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space_stride() > 0);
  require(xmbr_id.in_scope());

  // Body:

  result.put(_base_space->member_hub_id_space(false),
	     get_base_space_id_from_index(xmbr_id.hub_pod()));

  // Postconditions:

  ensure(result.same_scope(_base_space->member_hub_id_space(false)));
  ensure(result.pod() < base_space_member_id_ub());

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_poset::
base_space_stride() const
{
  // Preconditions:

  // Body:

  static const int result = BASE_SPACE_STRIDE;

  // Postconditions:

  ensure(result > 0);

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

sheaf::poset_path
fiber_bundle::section_space_schema_poset::
base_space_path(bool xauto_access) const
{
  // cout << endl << "Entering section_space_schema_poset::base_space_path." << endl;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).base_space_path);


  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving section_space_schema_poset::base_space_path." << endl;
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

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
fiber_schema_member_id_ub() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  return FIBER_SCHEMA_MEMBER_ID_UB;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
get_fiber_schema_id_from_index(pod_index_type xmbr_hub_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_stride() > 0);
  require(fiber_schema_member_id_ub() > 0);


  // Body:

  pod_index_type lfiber_schema_member_id_ub = fiber_schema_member_id_ub();
  pod_index_type lfiber_schema_stride = fiber_schema_stride();

  /// @hack Cartesian product subspace hack. Should be using product id space.
  // Assume base space id is first index, fiber schema id is second. 

  pod_index_type result = (xmbr_hub_id/lfiber_schema_stride) % lfiber_schema_member_id_ub;

  // Postconditions:

  ensure(result < fiber_schema_member_id_ub());

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_poset::
get_fiber_schema_id_from_index(const scoped_index& xmbr_id,
			       scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(fiber_schema_stride() > 0);
  require(fiber_schema_member_id_ub() > 0);
  require(xmbr_id.in_scope());

  // Body:

  result.put(fiber_schema().member_hub_id_space(false),
	     get_fiber_schema_id_from_index(xmbr_id.hub_pod()));

  // Postconditions:

  ensure(result.same_scope(fiber_schema().member_hub_id_space(false)));
  ensure(result.pod() < fiber_schema_member_id_ub());

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_poset::
fiber_schema_stride() const
{
  // Preconditions:

  // Body:

  static const int result = FIBER_SCHEMA_STRIDE;

  // Postconditions:

  ensure(result > 0);

  // Exit

  return result;
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

sheaf::poset_path
fiber_bundle::section_space_schema_poset::
fiber_space_path(bool xauto_access) const
{
  // cout << endl << "Entering section_space_schema_poset::fiber_space_path." << endl;

  // Preconditions:

  require(state_is_auto_read_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  poset_path result(sheaf::table_dofs(*this).fiber_space_path);


  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:


  // Exit:

  // cout << "Leaving section_space_schema_poset::fiber_space_path." << endl;
  return result;
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
multivalued()
{
  return _multivalued;
}

const sheaf::subposet&
fiber_bundle::section_space_schema_poset::
multivalued() const
{
  return _multivalued;
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

std::string
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

const sheaf::ij_product_structure&
fiber_bundle::section_space_schema_poset::
product_structure() const
{
  // Precondtions:

  require(state_is_read_accessible());

  // Body:

  const ij_product_structure& result = *_product;

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
get_index_from_components(pod_index_type xbase_space_id,
			  pod_index_type xfiber_schema_id) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_id));
  require(fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  pod_index_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  // Exit:

  return result;
}

void
fiber_bundle::section_space_schema_poset::
get_index_from_components(const scoped_index& xbase_space_id,
			  const scoped_index& xfiber_schema_id,
			  scoped_index& result) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().contains_member(xbase_space_id));
  require(fiber_schema().contains_member(xfiber_schema_id));

  // Body:

  result.put(member_hub_id_space(false),
	     get_index_from_components(xbase_space_id.hub_pod(),
				       xfiber_schema_id.hub_pod()));

  // Postconditions:

  ensure(result.same_scope(member_hub_id_space(false)));

  // Exit:

  return;
}

void
fiber_bundle::section_space_schema_poset::
update_hub_id_space(bool xauto_access)
{
  // Preconditions:

  require(state_is_auto_read_write_accessible(xauto_access));
  
  // Body:

  if(xauto_access)
  {
    get_read_write_access(true);
  }

  pod_index_type lmember_id_ub =
    base_space().member_index_ub().pod()*base_space_stride();

  extend_last_member_term(lmember_id_ub, false);

  _product->put_ubs(base_space().member_index_ub().pod(), base_space_stride());

  if(xauto_access)
  {
    release_access();
  }

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

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::section_space_schema_poset::
section_space_schema_poset(section_space_schema_member* xtop, section_space_schema_member* xbottom)
    : poset_state_handle(xtop, xbottom)
{
  // Preconditions:

  // Body:

  _base_space = 0;
  _fiber_space = 0;

  // Postconditions:

  // Exit

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
  poset_state_handle::get_read_access();

  // Postconditions:

  ensure(state_is_read_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(rep().state_is_read_accessible());
  ensure(base_space().state_is_read_accessible());
  ensure(fiber_space().state_is_read_accessible());

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
  poset_state_handle::get_read_write_access(xrelease_read_only_access);

  // Postconditions:

  ensure(state_is_read_write_accessible());
  ensure(access_request_depth() == old_access_request_depth + 1);
  ensure(rep().state_is_read_accessible());
  ensure(base_space().state_is_read_accessible());
  ensure(fiber_space().state_is_read_accessible());

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
    poset_state_handle::release_access(false);
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
  _base_space = &xns.member_poset<base_space_poset>(lbase_space_path, true);

  poset_path lfiber_space_path(ldofs.fiber_space_path);
  _fiber_space = &xns.member_poset<poset>(lfiber_space_path, true);



  // Attach the subposet handles to the current state.

  base_space().get_read_access();
  rep().get_read_access();
  discretization().attach_to_state(&(base_space()), rep().discretization_subposet_name());

  if(is_multivalued())
  {
    multivalued().attach_to_state(&(base_space()), rep().multivalued_subposet_name());
  }

  evaluation().attach_to_state(&(base_space()), rep().evaluation_subposet_name());

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  ensure(fiber_space().is_attached());
  ensure(discretization().is_attached());
  ensure(is_multivalued() ? multivalued().is_attached() : true);
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

  poset_state_handle::attach_handle_data_members();

  table_dofs_type& ldofs = sheaf::table_dofs(*this);
  namespace_poset* lns = name_space();

  // Attach the rep handle to the current state.

  /// @error Attach_to_state requires access, but since this is not attached yet,
  /// we can't tell what we need access to, so we can't require it.
  /// This is really an error in attach_to_state - it shouldn't require access.

  rep().attach_to_state(lns, ldofs.rep_path, true);

  // Attach the component handles to the current state.

  poset_path lbase_space_path(ldofs.base_space_path);
  _base_space = &lns->member_poset<base_space_poset>(lbase_space_path, true);

  poset_path lfiber_space_path(ldofs.fiber_space_path);
  _fiber_space = &lns->member_poset<poset>(lfiber_space_path, true);

  // Attach the subposet handles to the current state.

  discretization().attach_to_state(&(base_space()), rep().discretization_subposet_name());

  if(is_multivalued())
  {
    multivalued().attach_to_state(&(base_space()), rep().multivalued_subposet_name());
  }

  evaluation().attach_to_state(&(base_space()), rep().evaluation_subposet_name());

  // Postconditions:

  ensure(rep().is_attached());
  ensure(base_space().is_attached());
  //  ensure(fiber_schema().is_attached());
  ensure(fiber_space().is_attached());
  ensure(discretization().is_attached());
  ensure(is_multivalued() ? multivalued().is_attached() : true);
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

  poset_state_handle::terminate_access();

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

bool
fiber_bundle::section_space_schema_poset::
is_schematized(bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  // Body:

  if(xauto_access)
  {
    get_read_access();
  }

  result = fiber_schema().is_schematized(false);

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  /// @todo make the following executable.

  ensure(unexecutable(result == top member has been schematized));

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_poset::
schematize(subposet* xtable_dof_subposet,
           subposet* xrow_dof_subposet,
           bool xall_members)
{
  // Preconditions:

  require(state_is_read_write_accessible());
  require(dynamic_cast<primitives_poset_schema*>(schema().host()) != 0);
  // can only schematize posets which have same schema as primitives_poset
  require(xtable_dof_subposet != 0);
  require(includes_subposet(xtable_dof_subposet));
  require(xrow_dof_subposet != 0);
  require(includes_subposet(xrow_dof_subposet));

  // Body:

  not_implemented();

  /// @error this poset is immutable and does not support this operation

  // Postconditions:

  ensure(is_schematized(false));

  // Exit

  return;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


// ===========================================================
// MEMBERSHIP FACET
// ===========================================================

// PUBLIC FUNCTIONS

int
fiber_bundle::section_space_schema_poset::
member_ct() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  int result = base_space().member_ct()*fiber_schema().member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

int
fiber_bundle::section_space_schema_poset::
standard_member_ct() const
{
  int result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = base_space().standard_member_ct()*fiber_schema().standard_member_ct();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

sheaf::scoped_index
fiber_bundle::section_space_schema_poset::
member_index_ub() const
{

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  scoped_index result(member_hub_id_space(false));

  result =
    base_space().member_index_ub().pod()*
    fiber_schema().member_index_ub().pod();

  // Postconditions:

  ensure(result >= 0);

  return result;
}

sheaf::index_iterator
fiber_bundle::section_space_schema_poset::
member_iterator() const
{
  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  not_implemented();

  /// @todo implement section_space_schema_poset::member_iterator()

  index_iterator  result;

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
contains_member(pod_index_type xhub_id, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(!xauto_access ? state_is_read_accessible() : true);

  // Body:

  result =
    base_space().contains_member(get_base_space_id_from_index(xhub_id), xauto_access) &&
    fiber_schema().contains_member(get_fiber_schema_id_from_index(xhub_id), xauto_access);

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
contains_member(pod_index_type xhub_id, int xversion, bool xauto_access) const
{
  bool result;

  // Preconditions:

  require(!xauto_access ? state_is_read_accessible() : true);

  // Body:
  
  result =
    base_space().contains_member(get_base_space_id_from_index(xhub_id), xversion, xauto_access) &&
    fiber_schema().contains_member(get_fiber_schema_id_from_index(xhub_id), xauto_access);

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
is_jim(pod_index_type xhub_id, bool xin_current_version) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = 
    base_space().is_jim(get_base_space_id_from_index(xhub_id), xin_current_version) &&
    fiber_schema().is_jim(get_fiber_schema_id_from_index(xhub_id), xin_current_version);

  // Postconditions:

  // Exit

  return result;
}

bool
fiber_bundle::section_space_schema_poset::
is_atom(pod_index_type xhub_id) const
{
  bool result;

  // Preconditions:

  require(state_is_read_accessible());

  // Body:

  result = 
    base_space().is_atom(get_base_space_id_from_index(xhub_id)) &&
    fiber_schema().is_atom(get_fiber_schema_id_from_index(xhub_id));

  // Postconditions:

  // Exit

  return result;
}

// string
// fiber_bundle::section_space_schema_poset::
// member_name(pod_index_type xhub_id, bool xauto_access) const
// {
//   string result;

//   // Preconditions:

//   require(state_is_auto_read_accessible(xauto_access));

//   // Body:

//   if(xauto_access)
//   {
//     get_read_access();
//   }

//   result = poset_state_handle::member_name(xhub_id, false);
//   if(result.empty())
//   {
//     // Member does not have a client assigned name;
//     // try to construct a default name from factor names.

//     pod_index_type lbase_id = get_base_space_id_from_index(xhub_id);

//     pod_index_type lfiber_schema_id = get_fiber_schema_id_from_index(xhub_id);
//     string lfiber_name = fiber_schema().member_name(lfiber_schema_id);

//     if( (lbase_id == BOTTOM_INDEX) &&
//         (fiber_schema().table_dof_subposet().contains_member(lfiber_schema_id)) )
//     {
//       // This is a table dof member;
//       // name is name of fiber factor.

//       result = lfiber_name;
//     }
//     else
//     {
//       // This is not a table dof member;
//       // construct name from both base and fiber factor.

//       string lbase_name = base_space().member_name(lbase_id);

//       if(lbase_name.empty())
//       {
//         // Construct a name from the base space id.

//         stringstream lstr;
//         lstr << lbase_id;
//         lbase_name = lstr.str();
//       }

//       if(lfiber_name.empty())
//       {
//         // Construct a name from the fiber schema id.

//         stringstream lstr;
//         lstr << lfiber_schema_id;
//         lfiber_name = lstr.str();
//       }

//       result = lbase_name + "_" + lfiber_name;

//       // ERROR: the following produces the same name for different members.
//       //       if(!lbase_name.empty() || !lfiber_name.empty())
//       //       {
//       //         result = lbase_name + '_' + lfiber_name;
//       //       }
//       //       else
//       //       {
//       //         // Both base and fiber names are empty; do nothing.
//       //       }
//     }

//   }

//   if(xauto_access)
//   {
//     release_access();
//   }

//   // Postconditions:


//   // Exit:

//   return result;
// }

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

// PROTECTED FUNCTIONS

void
fiber_bundle::section_space_schema_poset::
initialize_standard_members()
{
  // Preconditions:

  require(state_is_read_write_accessible());

  // Body:


  /// @hack Cartesian product subspace hack. Should be using product id space.
  /// There are no entries in the hub id space for the members of the Cartesian 
  /// subspace of the general tensor product.Add an interval term to the 
  /// hub id space which creates a general index space. Really should be a 
  /// product index space and the factoring of the indices should use 
  /// the tuple and ordinal functions of the index space. 
  /// But since this class hierarchy is currently set up
  /// to do it's own factors with get_base_space_id_from_index, etc,
  /// we'll continue to do it that way, temporarily. 
  /// The id space allocated here is in the interval  
  /// [0, base_space().member_index_ub().pod()*base_space_stride()),
  /// which includes the ids reserved for bootom and top.
  /// This means bottom is the same as (base bottom, fiber_schema bottom),
  /// which is correct, and top is the same as (base bottom, fiber schema top),
  /// which is not correct. We can get away with it because
  /// we never refer to the (base bottom, fiber schema top).

  pod_index_type lbase_space_stride = base_space_stride();
  pod_index_type lmember_id_ub =
    base_space().member_index_ub().pod()*lbase_space_stride;

  pod_index_type lspace_id = new_term(lmember_id_ub, false);
  primary_index_space_handle lproduct_id_space(member_id_spaces(false), lspace_id);

  ij_product_structure lproduct(base_space().member_index_ub().pod(), lbase_space_stride);
  lproduct_id_space.new_product_structure(lproduct);

  _product = &lproduct_id_space.product_structure<ij_product_structure>();

  // Bottom member already allocated at index 0;
  // just have to make explicit cover sets.

  new_standard_member_hack(BOTTOM_INDEX);
  put_member_name(BOTTOM_INDEX, "bottom", true, false);
  bottom().attach_to_state(this, BOTTOM_INDEX);

  // Top member already allocated at index 1;
  // just have to make explicit cover sets.

  new_standard_member_hack(TOP_INDEX);
  put_member_name(TOP_INDEX, "top", true, false);
  top().attach_to_state(this, TOP_INDEX);

  // All the members exist implicitly, but they
  // don't have names unless we explicitly give them names.
  // Make the names for the table schema members 
  // the same as the corresponding members of the fiber schema

  schema_poset_member lfiber_schema = fiber_space().schema();  
  index_space_iterator& litr = lfiber_schema.table_dof_id_space().get_iterator();
  while(!litr.is_done())
  {
    // Get the name for the table dof in the fiber schema.

    string ltable_dof_name = lfiber_schema.host()->member_name(litr.hub_pod(), false);

    // Get the index for the corresponding member of this poset.

    pod_index_type ltable_dof_id = get_index_from_components(BOTTOM_INDEX, litr.hub_pod());

    // Set the name in this poset the same as in the fiber schema.

    put_member_name(ltable_dof_id, ltable_dof_name, true, false);

    litr.next();
  }
  lfiber_schema.table_dof_id_space().release_iterator(litr);

  // Only two standard members and no dof tuples so far.
  // (More may be added in descendants.)

  // All the members and row dof tuples are standard.

  put_standard_member_ct(2); // != member_ct(), which is always the product of component cts
  put_standard_row_dof_tuple_ct(row_dof_tuple_ct());

  // Now the cover relation graph invariant is satisfied

  state_obj()->crg()->enable_invariant_check();

  // Postconditions:

  ensure(state_obj()->crg()->invariant());
  ensure(bottom().is_attached() && (bottom().index() == BOTTOM_INDEX));
  ensure(top().is_attached() && (top().index() == TOP_INDEX));
  ensure(has_standard_row_dof_tuple_ct());

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
new_standard_member_hack(standard_member_index xindex)
{
  // Preconditions:

  require((xindex == BOTTOM_INDEX) || (xindex == TOP_INDEX));

  // Body:

  define_old_variable(const scoped_index old_member_index_ub = member_index_ub());
  define_old_variable(int old_member_ct = member_ct());

  // Create new node in crg; ensures lower and upper covers empty.

  // $$SCRIBBLE start here - retrofitting new_std_mbr_hack

  crg().new_standard_member_hack(xindex);

  // If node allocation has extended the member pool,
  // extend the subposet characteristic functions to match.

  if(crg().end() > powerset().subposet_member_index_ub())
  {
    powerset().put_subposet_member_index_ub(crg().end());
  }

  // Put new node in subposet of all members.

  powerset().whole().insert_member(xindex);

  // Postconditions:

  ensure(invariant());
  ensure(contains_member(xindex));
  ensure(cover_is_empty(LOWER, xindex));
  ensure(cover_is_empty(UPPER, xindex));

  // Exit

  return;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_member(bool xis_jim, pod_index_type xdof_tuple_id)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

  pod_index_type result = poset_state_handle::new_member(xis_jim, xdof_tuple_id);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::new_member(), result = " << result << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_member(bool xis_jim, poset_dof_map* xdof_map, bool xcopy_dof_map)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

  pod_index_type result = poset_state_handle::new_member(xis_jim, xdof_map, xcopy_dof_map);

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::new_member(), result = " << result << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_poset::
delete_member(pod_index_type xhub_id)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::delete_member(), index = " << xhub_id << endl;
#endif

  poset_state_handle::delete_member(xhub_id);

  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// COVER RELATION FACET
// ===========================================================

// PUBLIC FUNCTIONS

// PROTECTED FUNCTIONS

void
fiber_bundle::section_space_schema_poset::
new_link(pod_index_type xgreater, pod_index_type xlesser)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::new_link(), gtr, lsr = " << xgreater << ", " << xlesser << endl;
#endif

  poset_state_handle::new_link(xgreater, xlesser);

  // Postconditions:

  // Exit

  return;
}

void
fiber_bundle::section_space_schema_poset::
delete_link(pod_index_type xgreater, pod_index_type xlesser)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::delete_link(), gtr, lsr = " << xgreater << ", " << xlesser << endl;
#endif

  poset_state_handle::delete_link(xgreater, xlesser);

  // Postconditions:

  // Exit

  return;
}

// PRIVATE FUNCTIONS


// ===========================================================
// POWERSET FACET
// ===========================================================

// PUBLIC FUNCTIONS

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
new_subposet(const block<pod_index_type>& xmembers)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

  pod_index_type result = poset_state_handle::new_subposet(xmembers);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::new_subposet(), result = " << result << endl;
#endif

  // Postconditions:

  // Exit

  return result;
}

void
fiber_bundle::section_space_schema_poset::
delete_subposet(pod_index_type xsubposet_hub_id)
{
  // Preconditions:

  // Body:

  /// @todo implement this routine

#ifdef DIAGNOSTIC_OUTPUT
  cout << "DIAGNOSTIC_OUTPUT: call to section_space_schema_poset::delete_subposet(), index = " << xsubposet_hub_id << endl;
#endif

  poset_state_handle::delete_subposet(xsubposet_hub_id);

  // Postconditions:

  // Exit

  return;
}

int
fiber_bundle::section_space_schema_poset::
version_ct() const
{
  int result = 0;

  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().state_is_read_accessible());

  // Body:

  result = base_space().version_ct();

  ensure(result >= 0);

  // Exit

  return result;
}

int
fiber_bundle::section_space_schema_poset::
version() const
{
  int result = 0;

  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().state_is_read_accessible());

  // Body:

  /// @hack section_space_schema version hack:
  /// version of this is same as version of base space.

  result = base_space().version();

  // Postconditions:

  ensure( has_version(result) );

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
version_index(int xversion) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  pod_index_type result = base_space().version_index(xversion);

  // Postconditions:

  ensure(base_space().includes_subposet(result));

  // Exit

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
version_jims_index(int xversion) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(base_space().state_is_read_accessible());
  require(has_version(xversion));

  // Body:

  pod_index_type result = base_space().version_jims_index(xversion);

  // Postconditions:

  ensure(base_space().includes_subposet(result));

  // Exit

  return result;
}

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

bool
fiber_bundle::section_space_schema_poset::
is_valid_int_id(pod_index_type xint_id,
		const std::string& xid_space_name,
		bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());

  if(xauto_access)
  {
    get_read_access();
  }

  // Body:

  bool result = true;

  if(xint_id >= standard_member_ct())
  {
    result = base_space().member_id_spaces(false).contains(xid_space_name);
    if(result)
    {
      result = base_space().member_id_spaces(false).contains_hub(xid_space_name,
								 get_base_space_id_from_index(xint_id));
    }
  }

  if(xauto_access)
  {
    release_access();
  }

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::section_space_schema_poset::
get_ext_id(pod_index_type xint_id,
           const std::string& xid_space_name,
           bool xauto_access) const
{
  // Preconditions:

  require(xauto_access || state_is_read_accessible());
  require(is_valid_int_id(xint_id, xid_space_name, xauto_access));


  // Body:

  pod_index_type result = base_space().get_ext_id(get_base_space_id_from_index(xint_id),
						  xid_space_name,
						  xauto_access);

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
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

  invariance(poset_state_handle::invariant());

  if(invariant_check())
  {
    disable_invariant_check();

    invariance(state_is_read_accessible() ? rep().state_is_read_accessible() : true);

    invariance(state_is_read_accessible() ? base_space().state_is_read_accessible() : true);

    invariance(state_is_read_accessible() ? fiber_space().state_is_read_accessible() : true);

    /// @hack Cartesian product subspace hack. Should be using product id space.

    invariance(state_is_read_accessible() ? 
	       fiber_space().schema().host()->member_index_ub().pod() <= FIBER_SCHEMA_MEMBER_ID_UB : 
	       true);

    /// @todo make the following executable.

    invariance(unexecutable("rep.evaluator_family_name is compatible with base_space"));

    /// @todo finish section_space_schema_poset::invariant() const
    /// What is the invariant?

    enable_invariant_check();
  }

  return result;
}

// PROTECTED FUNCTIONS

// PRIVATE FUNCTIONS


