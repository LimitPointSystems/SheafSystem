
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

// Implementation for class constant_triangle

#include "ComLimitPoint/fiber_bundle/constant_triangle.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "std_limits.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// CONSTANT_TRIANGLE FACET
// ===========================================================

///
fiber_bundle::constant_triangle::
constant_triangle()
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::constant_triangle::
constant_triangle(const constant_triangle& xother)
    : constant_fcn_space(xother)
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  // Exit:

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
fiber_bundle::constant_triangle::value_type
fiber_bundle::constant_triangle::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub,
       size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);

  // Body:

  /// @todo Implement const_triangle::volume.

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
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::constant_triangle::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 2;

  // Postconditions:

  ensure(result == 2);

  // Exit:

  return result;
}


///
void
fiber_bundle::constant_triangle::
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
void
fiber_bundle::constant_triangle::
center(coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require(xresult != 0);
  require(xresult_ub >= db());

  // Body:

  static coord_type one_third =
    static_cast<coord_type>(1.0)/static_cast<coord_type>(3.0);

  xresult[0] = one_third;
  xresult[1] = one_third;

  // Postconditions:


  // Exit:

  return;
}


///
bool
fiber_bundle::constant_triangle::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  dof_type u = xlocal_coords[0];
  dof_type v = xlocal_coords[1];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type zero = 0.0 - 1000.0*numeric_limits<dof_type>::epsilon();
  dof_type one  = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  //  bool result = (u >= zero) && (u <= one) && (v >= zero) && (v <= one);
  bool result = (u >= zero) && (u <= one) && (v >= zero) && (v <= one - u);

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
fiber_bundle::constant_triangle*
fiber_bundle::constant_triangle::
clone() const
{
  constant_triangle* result;

  // Preconditions:

  // Body:

  result = new constant_triangle();

  // Postconditions:

  ensure(result != 0);
  //ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}


///
fiber_bundle::constant_triangle&
fiber_bundle::constant_triangle::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  /// @todo implement constant_triangle::operator=(const constant_triangle& xother)

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fiber_bundle::constant_triangle&
fiber_bundle::constant_triangle::
operator=(const constant_triangle& xother)
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
fiber_bundle::constant_triangle::
~constant_triangle()
{
  // Preconditions:

  // Body:

  // Postconditions:

  return;
}

///
bool
fiber_bundle::constant_triangle::
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
fiber_bundle::constant_triangle::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const constant_triangle*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

