
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

// Implementation for class poset_state

#include "poset_state.h"

#include "assert_contract.h"
#include "poset_crg_state.h"
#include "poset_powerset_state.h"
#include "poset_table_state.h"
#include "schema_poset_member.h"
#include "subposet.h"

// ===========================================================
// POSET_STATE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::poset_state::
poset_state(const abstract_poset_member* xschema, poset_type xtype_id, const string& xname)
{
  // Preconditions:
  
  require(xschema != 0 ? xschema->is_attached() : true);

  // Body:

  // Prevent recursive calls to invariant

  disable_invariant_check();

  _name = xname;

  _type_id = xtype_id;

  // Create the cover relation graph data structure

  _crg = new poset_crg_state();

  // Create the powerset (set of subposets) data structure

  const size_type lsubset_ct= 4; // arbitrary

  _powerset = new poset_powerset_state(lsubset_ct, _crg->end());

  // Create the table (dof tuples) structure.
  // Assume one dof tuple for each member as initial guess
  // for number of row dof tuples.

  const size_type lmbr_ct = 16; // arbitrary

  _table = new poset_table_state(xschema, lmbr_ct);

  // Invariant is not satisfied until client initializes
  // standard subsets, standard members, and schema.
  // Leave invariant checking disabled.

  // Postconditions:

  ensure(crg() != 0);
  ensure(!crg()->jim_edit_mode());
  ensure(powerset() != 0);
  ensure(powerset()->subposet_member_index_ub() >= crg()->end());
  ensure(xschema != 0 ? table()->schema().is_same_state(xschema) : true);

  // Exit:

  return;
}

// sheaf::poset_state::
// poset_state(const abstract_poset_member* xschema,
//             poset_type xtype_id,
//             size_type xmbr_ct,
//             size_type xlink_ct,
//             size_type xsubset_ct)
// {
//   // Preconditions:

//   require(xschema != 0 ? xschema->is_attached() : true);
//   require(xmbr_ct >= 0);
//   require(xlink_ct >=0);
//   require(xsubset_ct >= 0);

//   // Body:

//   // Prevent recursive calls to invariant

//   disable_invariant_check();

//   _type_id = xtype_id;

//   // Create the cover relation graph data structure

//   _crg = new poset_crg_state();

//   // Create the powerset (set of subposets) data structure

//   _powerset = new poset_powerset_state(xsubset_ct, _crg->end());

//   // Create the table (dof tuples) structure.
//   // Assume one dof tuple for each member as initial guess
//   // for number of row dof tuples.

//   _table = new poset_table_state(xschema, xmbr_ct);

//   // Invariant is not satisfied until client initializes
//   // standard subsets, standard members, and schema.
//   // Leave invariant checking disabled.

//   // Postconditions:

//   ensure(crg() != 0);
//   ensure(!crg()->jim_edit_mode());
//   ensure(powerset() != 0);
//   ensure(powerset()->subposet_member_index_ub() >= crg()->end());
//   ensure( (xschema != 0) == table()->schema().is_attached() );

//   // Exit:

//   return;
// }

sheaf::poset_state::
~poset_state()
{
  // Preconditions:

  // Body:

  // Deallocate powerset (set of subposets)

  delete _powerset;

  // Deallocate the table (dof tuples).

  delete _table;

  // Deallocate cover relation graph.

  delete _crg;

  // Postconditions:

  // Exit:

  return;
}

const string&
sheaf::poset_state::
name() const
{
  return _name;
}

void
sheaf::poset_state::
put_name(const string& xname)
{
  // cout << endl << "Entering poset_state::put_name." << endl;

  // Preconditions:

  require(poset_path::is_valid_name(xname));
  
  // Body:

  _name = xname;

  // Postconditions:

  ensure(name() == xname);
  
  // Exit:

  // cout << "Leaving poset_state::put_name." << endl;
  return;
}

sheaf::poset_type
sheaf::poset_state::
type_id() const
{
  poset_type result;

  // Preconditions:

  // Body:

  result = _type_id;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_crg_state*
sheaf::poset_state::
crg()
{
  poset_crg_state* result;

  // Preconditions:

  // Body:

  result = _crg;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

sheaf::poset_powerset_state*
sheaf::poset_state::
powerset()
{
  poset_powerset_state* result;

  // Preconditions:

  // Body:

  result = _powerset;

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

sheaf::poset_table_state*
sheaf::poset_state::
table() const
{
  poset_table_state* result;

  // Preconditions:

  // Body:

  result = _table;

  // Postconditions:

  ensure(result != 0);

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
sheaf::poset_state::
is_ancestor_of(const any*  xother) const
{
  bool result;

  // Preconditions:

  // Body:

  result = dynamic_cast<const poset_state*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

sheaf::poset_state*
sheaf::poset_state::
clone() const
{
  poset_state* result = 0;

  // Preconditions:

  // Body:

  /// @todo implement poset_state::clone

  not_implemented();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

bool
sheaf::poset_state::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  if(invariant_check())
  {
    // Test invariant of base class

    result = result && read_write_monitor::invariant();

    // Prevent recursive calls to invariant();

    disable_invariant_check();

    // Test invariants of individual components

    result = result && _crg->invariant();
    result = result && _powerset->invariant();
    result = result && _table->invariant();

    // Check inter-component dependencies

    result = result && (_powerset->subposet_member_index_ub() == _crg->end());

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
sheaf::deep_size(const poset_state& xp, bool xinclude_shallow, size_t xresults[4])
{
  size_t result;

  // Preconditions:

  // Body:

  result = xinclude_shallow ? sizeof(xp) : 0;

  poset_state& lxp = const_cast<poset_state&>(xp);

  if(lxp.crg() != 0)
  {
    size_t lmemory_parts[2];    
    size_t lcrg_result = deep_size(*lxp.crg(), true, lmemory_parts);
    result += lcrg_result;

    if(xresults != 0) 
    {
      xresults[0] = lmemory_parts[0];
      xresults[1] = lmemory_parts[1];
    }
  }
  else if(xresults != 0)
  {
    xresults[0] = 0;
    xresults[1] = 0;
  }

  if(lxp.powerset() != 0)
  {
    size_t lpowerset_result = deep_size(*lxp.powerset(), true);
    result += lpowerset_result;

    if(xresults != 0)
      xresults[2] = lpowerset_result;
  }
  else if(xresults != 0)
  {
    xresults[2] = 0;
  }

  if(lxp.table() != 0)
  {
    size_t ltable_result = deep_size(*lxp.table());
    result += ltable_result;

    if(xresults != 0)
      xresults[3] = ltable_result;
  }
  else if(xresults != 0)
  {
    xresults[3] = 0;
  }

  // Postconditions:
  
  ensure(result >= 0);

  // Exit

  return result;
}
