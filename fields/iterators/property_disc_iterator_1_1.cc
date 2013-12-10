
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
/// Implementation for class property_disc_iterator_1_1


#include "property_disc_iterator_1_1.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "binary_section_space_schema_member.h"
#include "eval_family.h"
#include "sec_rep_descriptor.h"
#include "section_evaluator.h"
#include "section_space_schema_member.h"
#include "sec_ed_invertible.h"
#include "sec_vd.h"
#include "std_limits.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "subposet_member_iterator.h"
#include "uniform_eval_family.h"
#include "field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// PROPERTY_DISC_ITERATOR_1_1 FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::property_disc_iterator_1_1::
property_disc_iterator_1_1(const field_vd& xfield)
    : property_disc_iterator()
{

  // Preconditions:

  require(xfield.state_is_read_accessible());
  require(xfield.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xfield.property().schema().base_space().le(&xfield.coordinates().schema().base_space()));
  require(xfield.property().schema().rep().is_same_state(&xfield.coordinates().schema().rep()));

  // Body:

  initialize_iteration(xfield, POSTORDER);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xfield.coordinates().schema()));
  ensure(coordinates_schema().is_same_type(&xfield.coordinates().schema()));
  ensure(coordinates_schema().version() == xfield.coordinates().schema().version());
  ensure(property_schema().is_same_state(&xfield.property().schema()));
  ensure(property_schema().is_same_type(&xfield.property().schema()));
  ensure(property_schema().version() == xfield.property().schema().version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


fields::property_disc_iterator_1_1::
property_disc_iterator_1_1(
  const section_space_schema_member& xcoordinates_schema,
  const section_space_schema_member& xproperty_schema)
    : property_disc_iterator()
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.base_space().le(&xcoordinates_schema.base_space()));
  require(xproperty_schema.rep().is_same_state(&xcoordinates_schema.rep()));

  // Body:

  initialize_iteration(xcoordinates_schema, xproperty_schema, POSTORDER);

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xcoordinates_schema));
  ensure(coordinates_schema().is_same_type(&xcoordinates_schema));
  ensure(coordinates_schema().version() == xcoordinates_schema.version());
  ensure(property_schema().is_same_state(&xproperty_schema));
  ensure(property_schema().is_same_type(&xproperty_schema));
  ensure(property_schema().version() == xproperty_schema.version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}

fields::property_disc_iterator_1_1::
~property_disc_iterator_1_1()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

void
fields::property_disc_iterator_1_1::
get_prop_disc_values(const sec_vd& xsec)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());
  require(xsec.schema().is_same_state(&coordinates_schema()));

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(xsec.schema().df() <= 3);

  // Body:

  discretization_context& ldisc_mbr = _prop_state.discretization_members[0];

  // Don't need to evaluate, just get the coord disc.

  xsec.get_fiber(ldisc_mbr.disc_id, ldisc_mbr.values,
		 3*sizeof(sec_vd::dof_type), false);
  
  // Postconditions:


  // Exit:

  return;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

void
fields::property_disc_iterator_1_1::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Never want to see a prop disc member more than once,
  // so always clear the buffer before we start.

  _prop_state.discretization_members.set_ct(0);

  // Traverse the graph gathering coord and prop disc members until
  // we have enough context to evaluate the coordinates at the
  // the property disc points or until the trversal is done.

  property_disc_iterator::next(ltruncate);

  while(!is_done())
  {
    if(_prop_state.disc_sp.contains_member(_index))
    {
      _prop_state.gather_discretization_member(_index, greater_index());
      break;
    }

    property_disc_iterator::next(false);
  } // end while(!is_done())

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() ? action() == POSTVISIT_ACTION : true);

  // Exit

  return;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::property_disc_iterator_1_1::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const property_disc_iterator_1_1*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

fields::property_disc_iterator_1_1*
fields::property_disc_iterator_1_1::
clone() const
{
  // Preconditions:

  // Body:

  property_disc_iterator_1_1* result =
    new property_disc_iterator_1_1(coordinates_schema(), property_schema());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
fields::property_disc_iterator_1_1::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(property_disc_iterator::invariant());

    disable_invariant_check();

    invariance(order() == POSTORDER);
    invariance(property_schema().rep().is_same_state(&coordinates_schema().rep()));

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


