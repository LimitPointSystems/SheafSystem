
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
/// Implementation for class variance_bound_refinement_policy

#include "SheafSystem/variance_bound_refinement_policy.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/factory.h"
#include "SheafSystem/field_refinement_buffer.h"
#include "SheafSystem/std_cmath.h"
#include "SheafSystem/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// VARIANCE_BOUND_REFINEMENT_POLICY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::variance_bound_refinement_policy::
variance_bound_refinement_policy(size_type xrefinement_depth_ub,
                                 sec_vd_value_type xvariance_ub)
    : field_refinement_policy(xrefinement_depth_ub),
    _variance_ub(xvariance_ub)
{

  // Preconditions:


  // Body:


  // Postconditions:

  ensure(invariant());
  ensure(refinement_depth_ub() == xrefinement_depth_ub);


  // Exit:

  return;
}


fields::variance_bound_refinement_policy::
variance_bound_refinement_policy(const variance_bound_refinement_policy& xother)
    : field_refinement_policy(xother),
    _variance_ub(xother._variance_ub)
{
  // Preconditions:


  // Body:

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


fields::variance_bound_refinement_policy::
~variance_bound_refinement_policy()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::sec_vd_value_type
fields::variance_bound_refinement_policy::
variance_ub() const
{
  return _variance_ub;
}

void
fields::variance_bound_refinement_policy::
put_variance_ub(sec_vd_value_type xub)
{
  // Preconditions:

  require(xub > 0.0);

  // Body:

  _variance_ub = xub;

  // Postconditions:

  ensure(variance_ub() == xub);

  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

bool
fields::variance_bound_refinement_policy::
_has_prototype = make_prototype();

bool
fields::variance_bound_refinement_policy::
make_prototype()
{
  bool result = true;

  // Preconditions:


  // Body:

  variance_bound_refinement_policy* lproto =
    new variance_bound_refinement_policy();

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
fields::variance_bound_refinement_policy::
should_refine(field_refinement_buffer& xbuffer, size_type xrefinement_depth) const
{
  bool result = false;

  // Preconditions:

  // Body:

  result = (xrefinement_depth < _refinement_depth_ub);


#ifdef DIAGNOSTIC_OUTPUT

  cout << "  zone_id: " << xbuffer.zone_id
  << "  refinement_depth: " << xrefinement_depth;
#endif

  if(result)
  {
    // Compute the average of the dofs.

    size_type ldp = xbuffer.target.dp();
    size_type ldofs_ct = 0;
    size_type ldisc_ct = xbuffer.prop_disc_ids.ct();
    size_type ldofs_ub = ldisc_ct*ldp;

    xbuffer.prop_value.set_ct(ldp);
    xbuffer.prop_value.assign(0.0);

    size_type k = 0;
    for(size_type i=0; i<ldisc_ct; ++i)
    {
      for(size_type j=0; j<ldp; ++j)
      {
        assertion(k < ldofs_ub);
        xbuffer.prop_value[j] += xbuffer.prop_dofs[k++];
      }
    }

    sec_vd_value_type lprop_norm = 0.0;

    for(size_type j=0; j<ldp; ++j)
    {
      xbuffer.prop_value[j] /= ldisc_ct;
      lprop_norm += abs(xbuffer.prop_value[j]);
    }

    // Compute the variance using the L1 norm.

    sec_vd_value_type lvariance_norm = 0.0;

    k = 0;
    for(size_type i=0; i<ldisc_ct; ++i)
    {
      for(size_type j=0; j<ldp; ++j)
      {
        lvariance_norm += abs(xbuffer.prop_value[j] - xbuffer.prop_dofs[k++]);
      }
    }

    // Check the difference.
    /// @todo replace this with something more general and robust.

    if(lprop_norm != 0.0)
    {
      result = (lvariance_norm > (ldp*lprop_norm*_variance_ub));
    }
    else
    {
      result = (lvariance_norm > (ldp*_variance_ub));
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout  << "  prop: " << xbuffer.prop_value[0]
    << "  prop norm: " << lprop_norm
    << "  variance norm: " << lvariance_norm;
#endif

  }

#ifdef DIAGNOSTIC_OUTPUT
  cout  << "  result: " << boolalpha << result << noboolalpha  << endl;
#endif

  // Postconditions:


  // Exit:

  return result;
}

const std::string&
fields::variance_bound_refinement_policy::
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
fields::variance_bound_refinement_policy::
static_class_name()
{

  // Preconditions:


  // Body:

  static const string result("variance_bound_refinement_policy");

  // Postconditions:


  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::variance_bound_refinement_policy::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const variance_bound_refinement_policy*>(other) != 0;

  // Postconditions:

  return result;
}

fields::variance_bound_refinement_policy*
fields::variance_bound_refinement_policy::
clone() const
{
  variance_bound_refinement_policy* result;

  // Preconditions:

  // Body:

  result = new variance_bound_refinement_policy(*this);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

///
fields::variance_bound_refinement_policy&
fields::variance_bound_refinement_policy::
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

fields::variance_bound_refinement_policy&
fields::variance_bound_refinement_policy::
operator=(const variance_bound_refinement_policy& xother)
{

  // Preconditions:


  // Body:

  _refinement_depth_ub = xother._refinement_depth_ub;
  _variance_ub = xother._variance_ub;

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
fields::variance_bound_refinement_policy::
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

