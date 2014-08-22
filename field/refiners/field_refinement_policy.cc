
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
/// Implementation for class field_refinement_policy

#include "field_refinement_policy.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/factory.impl.h"
#include "field_refinement_buffer.h"
#include "field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// FIELD_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_refinement_policy::
field_refinement_policy(size_type xrefinement_depth_ub)
    : _refinement_depth_ub(xrefinement_depth_ub)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(refinement_depth_ub() == xrefinement_depth_ub);

  // Exit:

  return;
}

fields::field_refinement_policy::
field_refinement_policy(const field_refinement_policy& xother)
    :  _refinement_depth_ub(xother._refinement_depth_ub)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fields::field_refinement_policy::
~field_refinement_policy()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

bool
fields::field_refinement_policy::
should_refine(field_refinement_buffer& xbuffer, size_type xrefinement_depth) const
{
  bool result = false;

  // Preconditions:

  require(xbuffer.target.state_is_read_accessible());
  require(xbuffer.source.state_is_read_accessible());

  // Body:

  is_abstract();

  // Postconditions:

  ensure( result ? xrefinement_depth < refinement_depth_ub() : true);

  // Exit:

  return result;
}

sheaf::size_type
fields::field_refinement_policy::
refinement_depth_ub() const
{
  return _refinement_depth_ub;
}

void
fields::field_refinement_policy::
put_refinement_depth_ub(size_type xub )
{
  // Preconditions:

  // Body:

  _refinement_depth_ub = xub;

  // Postconditions:

  ensure(refinement_depth_ub() == xub);

  // Exit:

  return;
}

const std::string&
fields::field_refinement_policy::
class_name() const
{
  // Preconditions:

  // Body:

  const string& result = static_class_name();

  // Postconditions:


  // Exit:

  return result;
}

const std::string&
fields::field_refinement_policy::
static_class_name()
{

  // Preconditions:


  // Body:

  static const string result("field_refinement_policy");

  // Postconditions:


  // Exit:

  return result;
}

fields::field_refinement_policy*
fields::field_refinement_policy::
new_policy(const std::string& xname)
{
  field_refinement_policy* result;

  // Preconditions:

  require(policy_factory().contains_prototype(xname));

  // Body:

  result = policy_factory().new_instance(xname);

  // Postconditions:

  ensure(result != 0);
  ensure(unexecutable("result is default constructed"));

  // Exit:

  return result;
}

sheaf::factory<fields::field_refinement_policy>&
fields::field_refinement_policy::
policy_factory()
{

  // Preconditions:


  // Body:

  static factory<field_refinement_policy> result;

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::field_refinement_policy::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const field_refinement_policy*>(other) != 0;

  // Postconditions:

  return result;
}

fields::field_refinement_policy&
fields::field_refinement_policy::
operator=(const field_refinement_policy& xother)
{

  // Preconditions:


  // Body:

  _refinement_depth_ub = xother._refinement_depth_ub;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::field_refinement_policy::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================


