// $RCSfile: constant_quad.cc,v $ $Revision: 1.19 $ $Date: 2013/03/20 21:56:05 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class constant_quad

#include "constant_quad.h"

#include "assert_contract.h"
#include "error_message.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// CONSTANT_QUAD FACET
// ===========================================================

///
fiber_bundle::constant_quad::
constant_quad()
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::constant_quad::
constant_quad(const constant_quad& xother)
    : constant_fcn_space(xother)
{
  // Preconditions:

  // Body:

  _basis_deriv_values = _basis_deriv_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::constant_quad::
~constant_quad()
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
fiber_bundle::constant_quad::value_type
fiber_bundle::constant_quad::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub,
       size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);

  // Body:


  /// @todo Implement const_quad::volume.

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
fiber_bundle::constant_quad::
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
fiber_bundle::constant_quad::
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
fiber_bundle::constant_quad::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);

  // Body:

  dof_type u = xlocal_coords[0];
  dof_type v = xlocal_coords[1];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type one = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= -one) && (u <= one) && (v >= -one) && (v <= one);

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
fiber_bundle::constant_quad*
fiber_bundle::constant_quad::
clone() const
{
  constant_quad* result;

  // Preconditions:

  // Body:

  result = new constant_quad();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::constant_quad&
fiber_bundle::constant_quad::
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
fiber_bundle::constant_quad&
fiber_bundle::constant_quad::
operator=(const constant_quad& xother)
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
fiber_bundle::constant_quad::
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
fiber_bundle::constant_quad::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const constant_quad*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================


