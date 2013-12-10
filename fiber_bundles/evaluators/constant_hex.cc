
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

// Implementation for class constant_hex

#include "constant_hex.h"

#include "assert_contract.h"
#include "error_message.h"
#include "std_limits.h"
#include "std_cmath.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

// ===========================================================
// CONSTANT_HEX FACET
// ===========================================================

///
fiber_bundle::constant_hex::
constant_hex()
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


// Copy constructor.
///
fiber_bundle::constant_hex::
constant_hex(const constant_hex& xother)
    : constant_fcn_space(xother)
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}




// Destructor.
///
fiber_bundle::constant_hex::
~constant_hex()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// CONSTANT_FCN_SPACE FACET
// ===========================================================

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

// ===========================================================
// INTEGRABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::constant_hex::value_type
fiber_bundle::constant_hex::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub,
       size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);

  // Body:

  /// @todo Implement const_hex::volume.

  not_implemented();

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

// ===========================================================
// DIFFERENTIABLE_SECTION_EVALUATOR FACET
// ===========================================================

// ===========================================================
//  DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::constant_hex::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 3;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}

///
void
fiber_bundle::constant_hex::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  center(xresult, xresult_ub);

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::constant_hex::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  dof_type u = xlocal_coords[0];
  dof_type v = xlocal_coords[1];
  dof_type w = xlocal_coords[2];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type one = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= -one) && (u <= one) &&
                (v >= -one) && (v <= one) &&
                (w >= -one) && (w <= one);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::constant_hex*
fiber_bundle::constant_hex::
clone() const
{
  constant_hex* result;

  // Preconditions:

  // Body:

  result = new constant_hex();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}

///
fiber_bundle::constant_hex&
fiber_bundle::constant_hex::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fiber_bundle::constant_hex&
fiber_bundle::constant_hex::
operator=(const constant_hex& xother)
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

///
bool
fiber_bundle::constant_hex::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && constant_fcn_space::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    invariance(basis_values() != 0);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

///
bool
fiber_bundle::constant_hex::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const constant_hex*>(xother) != 0;

  // Postconditions:

  return result;

}


// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

