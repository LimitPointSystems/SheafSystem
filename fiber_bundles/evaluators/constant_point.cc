//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class constant_point

#include "constant_point.h"

#include "assert_contract.h"
#include "error_message.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// CONSTANT_POINT FACET
// ===========================================================

///
fiber_bundle::constant_point::
constant_point()
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::constant_point::
constant_point(const constant_point& xother)
    : constant_fcn_space(xother)
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

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
fiber_bundle::constant_point::value_type
fiber_bundle::constant_point::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub,
       size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);

  // Body:


  /// @todo Implement const_point::volume.

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
fiber_bundle::constant_point::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 0;

  // Postconditions:

  ensure(result == 0);

  // Exit:

  return result;
}


///
void
fiber_bundle::constant_point::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[DL] =
    {
      0.0
    };

  xresult[0] = lcoords[xindex];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::constant_point::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  dof_type u = xlocal_coords[0];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type eps = 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= -eps) && (u <= eps);

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
fiber_bundle::constant_point*
fiber_bundle::constant_point::
clone() const
{
  constant_point* result;

  // Preconditions:

  // Body:

  result = new constant_point();

  // Postconditions:

  ensure(result != 0);
  //ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}


///
fiber_bundle::constant_point&
fiber_bundle::constant_point::
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
fiber_bundle::constant_point&
fiber_bundle::constant_point::
operator=(const constant_point& xother)
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
fiber_bundle::constant_point::
~constant_point()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


///
bool
fiber_bundle::constant_point::
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
fiber_bundle::constant_point::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const constant_point*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================



