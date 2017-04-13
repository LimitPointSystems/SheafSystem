
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
/// Implementation for class zone_centered_error_bound_refinement_policy

#include "SheafSystem/zone_centered_error_bound_refinement_policy.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/field_refinement_buffer.h"
#include "SheafSystem/std_cmath.h"
#include "SheafSystem/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// ZONE_CENTERED_ERROR_BOUND_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::zone_centered_error_bound_refinement_policy::
zone_centered_error_bound_refinement_policy(size_type xrefinement_depth_ub,
    sec_vd_value_type xerror_ub)
    : field_refinement_policy(xrefinement_depth_ub),
    _error_ub(xerror_ub)
{

  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(refinement_depth_ub() == xrefinement_depth_ub);
  ensure(error_ub() == xerror_ub);

  // Exit:

  return;
}

fields::zone_centered_error_bound_refinement_policy::
zone_centered_error_bound_refinement_policy(const zone_centered_error_bound_refinement_policy& xother)
    : field_refinement_policy(xother),
    _error_ub(xother._error_ub)
{

  // Preconditions:


  // Body:

  _refinement_depth_ub = xother._refinement_depth_ub;
  _error_ub = xother._error_ub;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fields::zone_centered_error_bound_refinement_policy::
~zone_centered_error_bound_refinement_policy()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::sec_vd_value_type
fields::zone_centered_error_bound_refinement_policy::
error_ub() const
{
  return _error_ub;
}

void
fields::zone_centered_error_bound_refinement_policy::
put_error_ub(sec_vd_value_type xub)
{
  // Preconditions:

  require(xub > 0.0);

  // Body:

  _error_ub = xub;

  // Postconditions:

  ensure(error_ub() == xub);

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

bool
fields::zone_centered_error_bound_refinement_policy::
_has_prototype = make_prototype();

bool
fields::zone_centered_error_bound_refinement_policy::
make_prototype()
{
  bool result = true;

  // Preconditions:


  // Body:

  zone_centered_error_bound_refinement_policy* lproto =
    new zone_centered_error_bound_refinement_policy();

  policy_factory().insert_prototype(lproto);

  // Postconditions:

  ensure(policy_factory().contains_prototype(static_class_name()));

  // Exit:

  return result;
}


// ===========================================================
// FIELD_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::zone_centered_error_bound_refinement_policy::
should_refine(field_refinement_buffer& xbuffer, size_type xrefinement_depth) const
{
  bool result;

  // Preconditions:

  require(xbuffer.source.state_is_read_accessible());
  require(xbuffer.target.state_is_read_accessible());
  require(xbuffer.target.same_evaluation());

  // Body:

  result = (xrefinement_depth < _refinement_depth_ub);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "  zone_id: " << xbuffer.zone_id
  << "  refinement_depth: " << xrefinement_depth;
#endif

  if(result)
  {
    // Evaluate the coordinates, property and source property
    // at the center of the zone.

    xbuffer.evaluate_at_center();

    // Compute the error using the L1 norm.

    sec_vd_value_type lerror_norm = 0.0;
    sec_vd_value_type lprop_norm = 0.0;

    size_type ldp = xbuffer.target.dp();
    for(size_type i=0; i<ldp; ++i)
    {
      sec_vd_value_type lsrc_val = xbuffer.source_prop_value[i];
      lprop_norm += abs(lsrc_val);
      lerror_norm += abs(xbuffer.prop_value[i] - lsrc_val);
    }

    // Check the difference.
    /// @todo replace this with something more general and robust.

    if(lprop_norm != 0.0)
    {
      result = (lerror_norm > (ldp*lprop_norm*_error_ub));
    }
    else
    {
      result = (lerror_norm > (ldp*_error_ub));
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout  << "  prop: " << xbuffer.prop_value[0]
    << "  src: " << xbuffer.source_prop_value[0]
    << "  prop norm: " << lprop_norm
    << "  error norm: " << lerror_norm;
#endif

  }

#ifdef DIAGNOSTIC_OUTPUT
  cout  << "  result: " << boolalpha << result << noboolalpha  << endl;
#endif

  // Postconditions:

  ensure( result ? xrefinement_depth < refinement_depth_ub() : true);

  // Exit:

  return result;
}

const std::string&
fields::zone_centered_error_bound_refinement_policy::
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
fields::zone_centered_error_bound_refinement_policy::
static_class_name()
{
  // Preconditions:

  // Body:

  static const string result("zone_centered_error_bound_refinement_policy");

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::zone_centered_error_bound_refinement_policy::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const zone_centered_error_bound_refinement_policy*>(other) != 0;

  // Postconditions:

  return result;
}

fields::zone_centered_error_bound_refinement_policy*
fields::zone_centered_error_bound_refinement_policy::
clone() const
{
  zone_centered_error_bound_refinement_policy* result;

  // Preconditions:

  // Body:

  result = new zone_centered_error_bound_refinement_policy(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::zone_centered_error_bound_refinement_policy&
fields::zone_centered_error_bound_refinement_policy::
operator=(const field_refinement_policy& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::zone_centered_error_bound_refinement_policy&
fields::zone_centered_error_bound_refinement_policy::
operator=(const zone_centered_error_bound_refinement_policy& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::zone_centered_error_bound_refinement_policy::
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

