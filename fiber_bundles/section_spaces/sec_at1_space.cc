
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

/// @file
/// Implementation for class sec_at1_space.

#include "sec_at1_space.h"

#include "abstract_poset_member.impl.h"
#include "assert_contract.h"
#include "binary_section_space_schema_member.impl.h"
#include "binary_section_space_schema_poset.h"
#include "fiber_bundles_namespace.h"
#include "namespace_poset.impl.h"
#include "namespace_poset_member.h"
#include "poset_handle_factory.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1.h"
#include "sec_tuple_space.impl.h"
#include "section_space_schema_member.impl.h"
#include "section_space_schema_poset.h"
#include "at1.h"
#include "at1_space.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

//==============================================================================
// SEC_AT1_SPACE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::sec_at1_space&
fiber_bundle::sec_at1_space::
new_table(namespace_type& xns, 
          const poset_path& xpath, 
          const poset_path& xschema_path,
          const poset_path& xscalar_space_path, 
          bool xauto_access)
{
  // cout << endl << "Entering sec_at1_space::new_table." << endl;

  // Preconditions:


  require(!xpath.empty());
  require(!xns.contains_path(xpath, xauto_access));

  require(xschema_path.full());
  require(xns.path_is_auto_read_accessible<schema_type::host_type>(xschema_path, xauto_access));
  require(fiber_space_conforms<fiber_type::host_type>(xns, xschema_path, xauto_access));  

  require(xns.path_is_auto_read_accessible<scalar_type::host_type>(xscalar_space_path, xauto_access));

  require(same_scalar_fiber_space(xns, xschema_path, xscalar_space_path, xauto_access));

  // Body:

  // Create the table; have to new it because namespace keeps a pointer.

  typedef sec_at1_space table_type;

  table_type& result = *(new table_type());

  // Create a handle of the right type for the schema member.

  schema_type lschema(xns, xschema_path, xauto_access);

  if(xauto_access)
  {
    lschema.get_read_access();
  }

  // Create the table dof map.

  array_poset_dof_map& lmap = *(new array_poset_dof_map(&lschema, true));

  // The table dofs are mostly the same as the fiber schema,
  // so just copy them from the fiber schema.
  // Can't use copy constructor because schema objects are different.

  array_poset_dof_map& lfiber_map = lschema.fiber_space().table_dof_map();
  lmap.copy_dof_tuple(lfiber_map);

  // Replace the fiber scalar space path with the section scalar space path.

  lmap.put_dof("scalar_space_path", xscalar_space_path);

  // Replace the fiber vector space path with the section vector space path.
  // sec_at1 is its own vector section space.

  lmap.put_dof("vector_space_path", xpath);
  
  // Create the state.

  result.new_state(xns, xpath, lschema, lmap);

  if(xauto_access)
  {
    lschema.release_access();
  }

  // Postconditions:

  ensure(xns.owns(result, xauto_access));
  ensure(result.path(true) == xpath);
  ensure(result.state_is_not_read_accessible());
  ensure(result.schema(true).path(xauto_access) == xschema_path);

  ensure(result.factor_ct(true) == result.schema(true).fiber_space<fiber_type::host_type>().factor_ct(xauto_access));
  ensure(result.d(true) == result.schema(true).fiber_space<fiber_type::host_type>().d(xauto_access));
  ensure(result.d(true) == result.dd(true));
  ensure(result.scalar_space_path(true) == xscalar_space_path);
  ensure(result.p(true) == result.schema(true).fiber_space<fiber_type::host_type>().p(xauto_access));
  ensure(result.p(true) == 1);
  ensure(result.dd(true) == result.schema(true).fiber_space<fiber_type::host_type>().dd(xauto_access));
  ensure(result.vector_space_path(true) == xpath);

  // Exit:

  // cout << "Leaving sec_at1_space::new_table." << endl;
  return result;
}

// PROTECTED MEMBER FUNCTIONS

fiber_bundle::sec_at1_space::
sec_at1_space()
  : sec_atp_space(new sec_at1, new sec_at1)
{
  // Preconditions:

  // Body:

  // Nothing to do, handled by base class

  // Postconditions:

  ensure(postcondition_of(sec_atp_space::sec_atp_space()));
}

fiber_bundle::sec_at1_space::
~sec_at1_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit

  return;
}

fiber_bundle::sec_at1_space::
sec_at1_space(sec_at1* xtop, sec_at1* xbottom)
  : sec_atp_space(xtop, xbottom)
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

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_ATP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_TP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_VD_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_TUPLE_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// SEC_REP_SPACE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS

bool
fiber_bundle::sec_at1_space::
make_prototype()
{
  bool result = false;

  // Preconditions:

  // Body:

  sec_at1_space* lproto = new sec_at1_space;
  poset_type ltype      = lproto->type_id();

  factory().insert_prototype(lproto);
  factory().insert_prototype(ltype, lproto);

  // Postconditions:

  // Exit:

  return result;
}


//==============================================================================
// POSET_STATE_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_type
fiber_bundle::sec_at1_space::
type_id() const
{
  return SEC_AT1_SPACE_ID;
}

///@todo: Return string&.
///@todo: Static version.

const char*
fiber_bundle::sec_at1_space::
class_name() const
{
  // Preconditions:

  // Body:

  static const char* result = "sec_at1_space";

  // Postconditions:

  // Exit:

  return result;
}

sheaf::pod_index_type
fiber_bundle::sec_at1_space::
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

    case 1:

      // The vector space over which this tensor space is built.

      result = name_space()->member_id(scalar_space_path().poset_name(), false);
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

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// READ_WRITE_MONITOR_HANDLE FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// ANY FACET
//==============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
fiber_bundle::sec_at1_space::
is_ancestor_of(const any* xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const sec_at1_space*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fiber_bundle::sec_at1_space*
fiber_bundle::sec_at1_space::
clone() const
{
  sec_at1_space* result;

  // Preconditions:

  // Body:

  result = new sec_at1_space;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  ensure(!result->is_attached());

  // Exit

  return result;
}

bool
fiber_bundle::sec_at1_space::
invariant() const
{
  bool result = true;


  if(invariant_check())
  {
    disable_invariant_check();

    invariance(sec_atp_space::invariant());

    invariance(state_is_read_accessible() ? p() == 1 : true);
    invariance(state_is_read_accessible() ? vector_space_path().poset_name() == name() : true);

    enable_invariant_check();
  }

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS



