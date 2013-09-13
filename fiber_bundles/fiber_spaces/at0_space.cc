
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Implementation for class at0_space.

#include "at0_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "at0.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// AT0_SPACE FACET public member functions
//==============================================================================

///
const string&
fiber_bundle::at0_space::
standard_schema_poset_name()
{
  // Preconditions:


  // Body:

  static const string& result = at0::standard_schema_poset_name();

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

///
const sheaf::poset_path&
fiber_bundle::at0_space::
standard_schema_path()
{
  // Preconditions:


  // Body:

  static const poset_path& result = at0::standard_schema_path();

  // Postconditions:

  ensure(result.full());
  ensure(result.poset_name() == standard_schema_poset_name());

  // Exit:

  return result;
}

fiber_bundle::at0_space& 
fiber_bundle::at0_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path, 
          bool xauto_access)
{
  // cout << endl << "Entering at0_space::new_table." << endl;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible(xschema_path, xauto_access));
  require(schema_poset_member::conforms_to(xns, xschema_path, standard_schema_path(), xauto_access));
  require(schema_poset_member::row_dof_ct(xns, xschema_path, xauto_access) == 1);
  
  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef at0_space table_type;

  table_type* ltable = new table_type();

  // Create a handle of the right type for the schema member.

  schema_poset_member lschema(&xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }


  // Get the dimension of the domain vector space.
  // For AT0, the tensor space, the domain vector space, 
  // and the scalar space are all the same thing.

  int ld = 1;
  int ldd = ld;
  int lp = 0;
  
  // Create the table dof map and set dof values;
  // must be newed because poset_state::_table keep a pointer to it.

  array_poset_dof_map* lmap = new array_poset_dof_map(&lschema, true);
  lmap->put_dof("factor_ct", ld);
  lmap->put_dof("d", ld);
  lmap->put_dof("scalar_space_path", xpath);
  lmap->put_dof("p", lp);
  lmap->put_dof("dd", ldd);
  lmap->put_dof("vector_space_path", xpath);
  
  // Create the state.

  ltable->new_state(xns, xpath, lschema, *lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  at0_space& result = *ltable;

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == 1);
  ensure(result.d(true) == 1);
  ensure(result.scalar_space_path(true) == xpath);
  ensure(result.p(true) == 0);
  ensure(result.dd(true) == 1);
  ensure(result.vector_space_path(true) == xpath );

  // Exit:

  // cout << "Leaving at0_space::new_table." << endl;
  return result;
} 

// ===========================================================
// AT0_SPACE FACET protected member functions
// ===========================================================
 
fiber_bundle::at0_space::
at0_space()
  : atp_space(new at0, new at0)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(atp_space::atp_space()));
}

fiber_bundle::at0_space::
~at0_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::at0_space::
at0_space(at0* xtop, at0* xbottom)
  : atp_space(xtop, xbottom)
{
  // Preconditions:

  require(xtop != 0);
  require(xbottom != 0);
  
  // Body:

  // Nothing to do.

  // Postconditions:

  ensure(postcondition_of(poset_state_handle::poset_state_handle(xtop, xbottom)));
  
  // Exit:

  return;
}

// ===========================================================
// TP_SPACE FACET public member functions
// ===========================================================


// ===========================================================
// TP_SPACE FACET protected member functions
// ===========================================================
 

sheaf::size_type
fiber_bundle::at0_space::
covariant_subposet_ct() const
{
  return 0;
}

// ===========================================================
// VD_SPACE FACET
// ===========================================================
 

bool
fiber_bundle::at0_space::
is_vector(pod_index_type xmbr_id, bool xauto_access) const
{

  ///
  /// At0 is a special case; scalars can be considered a vector space
  /// over themselves, but even so a scalar is simultaneously a vector and a covector.
  /// This is because covectors transform inversely to vectors, but
  /// by definition the only transform for scalars is the identity transform,
  /// which is its own inverse.

  bool result = true;

  // Postconditions:

  ensure(result);
  
  // Exit:

  return result;
}

void
fiber_bundle::at0_space::
put_is_vector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  // Body:

  // Do nothing.

  // Postconditions:

  ensure(is_vector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

bool
fiber_bundle::at0_space::
is_covector(pod_index_type xmbr_id, bool xauto_access) const
{
  // Preconditions:

  // Body:

  bool result = true;

  // Postconditions:

  ensure(result);

  // Exit:

  return result;
}

void
fiber_bundle::at0_space::
put_is_covector(pod_index_type xmbr_id, bool xauto_access)
{
  // Preconditions:

  // Body:

  // Do nothing.

  // Postconditions:

  ensure(is_covector(xmbr_id, xauto_access));
  
  // Exit:

  return;
}

// ===========================================================
// POSET FACET
// =========================================================== 

bool
fiber_bundle::at0_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:


  at0_space* lproto = new at0_space;
  poset_type ltype = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}

//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================



sheaf::poset_type
fiber_bundle::at0_space::
type_id() const
{
  return AT0_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::at0_space::
class_name() const
{
  // Preconditions:


  // Body:

  static const char* result = "at0_space";

  // Postconditions:

  // Exit:

  return result;
}

///
sheaf::pod_index_type
fiber_bundle::at0_space::
prereq_id(int xi) const
{
  // Preconditions:

  require(state_is_read_accessible());
  require(name_space()->state_is_read_accessible());

  // Body:

  pod_index_type result;

  switch(xi)
  {
    case 0:

      // The first prerequisite is always the schema.

      result = schema().host()->index().pod();
      break;

    default:

      // No other prerequisites.

      result = invalid_pod_index();
      break;
  }

  // Postconditions:


  // Exit:

  return result;
}

//==============================================================================
// ANY FACET
//==============================================================================

bool
fiber_bundle::at0_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const at0_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::at0_space*
fiber_bundle::at0_space::
clone() const
{
  at0_space* result;

  // Preconditions:

  // Body:

  result = new at0_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::at0_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(atp_space::invariant());

    invariance(state_is_read_accessible() ? dd() == d() : true);
    invariance(state_is_read_accessible() ? vector_space_path().poset_name() == name() : true);
    invariance(state_is_read_accessible() ? p() == 0 : true);
    invariance(state_is_read_accessible() ? scalar_space_path().poset_name() == name() : true);
    invariance(state_is_read_accessible() ? d() == 1 : true);
    invariance(state_is_read_accessible() ? factor_ct() == d() : true);
    
    enable_invariant_check();
  }

  return result;
}


