
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
/// Implementation for class field_refiner_family

#include "ComLimitPoint/fields/field_refiner_family.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/fiber_bundle/base_space_member.h"
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#include "ComLimitPoint/sheaf/factory.impl.h"
#include "ComLimitPoint/fields/field_refinement_policy.h"
#include "ComLimitPoint/fields/local_field_refiner.h"
#include "ComLimitPoint/sheaf/namespace_poset.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// FIELD_REFINER_FAMILY FACET
// ===========================================================

fields::field_refiner_family*
fields::field_refiner_family::
new_family(const std::string& xname)
{
  field_refiner_family* result;

  // Preconditions:

  require(family_factory().contains_prototype(xname));

  // Body:

  result = family_factory().new_instance(xname);

  // Postconditions:

  ensure(result != 0);
  ensure(result->class_name() == xname);
  ensure(!result->is_initialized());

  // Exit

  return result;
}

fields::field_refiner_family::
field_refiner_family(const field_refiner_family& xother)
{

  // Preconditions:

  // Body:

  _members.reserve(xother._members.ct());

  for(int i=0; i<xother._members.ct(); ++i)
  {
    local_field_refiner* lmbr = xother._members[i];
    _members[i] = (lmbr != 0) ? lmbr->clone() : 0;
  }
  _members.set_ct(xother._members.ct());

  _policy = 0;
  if(xother.is_initialized())
  {
    _policy =  xother._policy->clone();
  }

  if(xother._cell_type_id_space != 0)
  {
    _cell_type_id_space = &xother._cell_type_id_space->get_id_space();
  }
  else
  {
    _cell_type_id_space = 0;
  }
  
  _is_initialized = xother._is_initialized;

  // Postconditions:

  ensure(invariant());
}

fields::field_refiner_family::
~field_refiner_family()
{
  // Preconditions:

  // Body:

  for(size_type i=0; i<_members.ct(); ++i)
  {
    local_field_refiner* lref = _members[i];
    if(lref !=0)
    {
      delete lref;
    }
  }

  if(_is_initialized)
  {
    delete _policy;
  }

  if(_cell_type_id_space != 0)
  {
    _cell_type_id_space->release_id_space();
  }

  // Postconditions:

  // Exit:

  return;
}

const std::string&
fields::field_refiner_family::
class_name() const
{
  // Preconditions:

  // Body:

  is_abstract();

  static const string result;

  // Postconditions:

  ensure(!result.empty());

  // Exit

  return result;
}

fields::local_field_refiner*
fields::field_refiner_family::
member(pod_index_type xtype_id) const
{
  local_field_refiner* result;

  // Preconditions:

  require((0 <= xtype_id) && (xtype_id < size()));

  // Body:

  // Get the family member associated with base space member.

  result = _members[xtype_id];

  // Postconditions:

  // Exit

  return result;
}

sheaf::size_type
fields::field_refiner_family::
size() const
{
  size_type result;

  // Preconditions:

  // Body:

  result = _members.ct();

  // Postconditions:


  // Exit:

  return result;
}

fields::field_refinement_policy&
fields::field_refiner_family::
policy() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  field_refinement_policy& result = *_policy;

  // Postconditions:


  // Exit:

  return result;
}

sheaf::factory<fields::field_refiner_family>&
fields::field_refiner_family::
family_factory()
{

  // Preconditions:


  // Body:

  static factory<field_refiner_family> result;

  // Postconditions:


  // Exit:

  return result;
}


void
fields::field_refiner_family::
initialize(const base_space_poset& xbase_space, const field_refinement_policy& xpolicy)
{
  // Preconditions:

  require(!is_initialized());
  require(xbase_space.state_is_read_accessible());

  // Body:

  poset& lprototypes_poset =
    xbase_space.name_space()->member_poset<poset>(base_space_member::prototypes_poset_name(), false);

  lprototypes_poset.get_read_access();

  // Initialize the members.

  _members.reserve(lprototypes_poset.member_index_ub().pod());

  _members.set_ct(_members.ub());
  _members.assign(0);

  // Initialize refinement policy.

  _policy = xpolicy.clone();

  // Initialize the cell type id space.

  _cell_type_id_space =
    &lprototypes_poset.member_id_spaces(false).get_id_space("cell_types");

  // Mark as initialized.

  _is_initialized = true;

  // Clean up.

  lprototypes_poset.release_access();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure_for_all(i, 0, size(), (member(i) != 0) ? (&member(i)->policy() == &xpolicy) : true);

  // Exit:

  return;
}

bool
fields::field_refiner_family::
is_initialized() const
{
  return _is_initialized;
}


// PROTECTED MEMBER FUNCTIONS

fields::field_refiner_family::
field_refiner_family()
    : _policy(0),
    _cell_type_id_space(0),
    _is_initialized(false)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_refiner_family*
fields::field_refiner_family::
clone() const
{
  field_refiner_family* result = 0; // Initialize to avoid compiler warnings.

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

bool
fields::field_refiner_family::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant

  result = result && any::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

bool
fields::field_refiner_family::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const field_refiner_family*>(xother) != 0;

  // Postconditions:

  return result;

}



