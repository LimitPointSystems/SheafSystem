
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
/// Implementation for class sec_rep_descriptor_poset

#include "SheafSystem/sec_rep_descriptor_poset.h"

#include "SheafSystem/abstract_poset_member.impl.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/array_poset_dof_map.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/namespace_poset.impl.h"
#include "SheafSystem/poset_handle_factory.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// SEC_REP_DESCRIPTOR_POSET FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

const sheaf::poset_path&
fiber_bundle::sec_rep_descriptor_poset::
standard_schema_path()
{
  // Preconditions:

  // Body:

  const poset_path& result = sec_rep_descriptor::standard_schema_path();

  // Postconditions:

  ensure(result.full());

  // Exit:

  return result;
}


fiber_bundle::sec_rep_descriptor_poset& 
fiber_bundle::sec_rep_descriptor_poset::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          const poset_path& xprototypes_path,
          bool xauto_access)
{
  // cout << endl << "Entering sec_rep_descriptor_poset::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));

  require(!xprototypes_path.empty());
  require(xns.path_is_auto_read_accessible(xprototypes_path, xauto_access));  
  
  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef sec_rep_descriptor_poset table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("prototypes_path", xprototypes_path);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  sec_rep_descriptor_poset& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.prototypes().path(xauto_access) == xprototypes_path);

  // Exit:

  // cout << "Leaving sec_rep_descriptor_poset::new_table." << endl;
  return result;
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
 

