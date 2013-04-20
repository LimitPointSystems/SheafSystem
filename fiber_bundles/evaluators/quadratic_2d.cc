//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class quadratic_2d

#include "quadratic_2d.h"
#include "assert_contract.h"
#include "std_cmath.h"
#include "std_iostream.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// QUADRATIC_2D FACET
// ===========================================================

///
fiber_bundle::quadratic_2d::
quadratic_2d()
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::quadratic_2d::
quadratic_2d(const quadratic_2d& xother)
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::quadratic_2d::
~quadratic_2d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::quadratic_2d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 6);

  // Exit:

  return result;
}

///
void
fiber_bundle::quadratic_2d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_values() != 0);

  // Body:

  // Evaluate the interpolation functions.

  double l0 = xlocal_coord[0];
  double l1 = xlocal_coord[1];
  double l2 = 1.0 - (l0 + l1);

  // corner nodes:

  _basis_values[0] = (2.0*l0-1.0)*l0;
  _basis_values[1] = (2.0*l1-1.0)*l1;
  _basis_values[2] = (2.0*l2-1.0)*l2;

  // midside nodes:

  _basis_values[3] = 4.0*l0*l1;
  _basis_values[4] = 4.0*l1*l2;
  _basis_values[5] = 4.0*l2*l0;

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::quadratic_2d::
basis_derivs_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  ///@todo Implement.

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// INTEGRABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::quadratic_2d::
jacobian_determinant(const dof_type xcoord_dofs[],
                     size_type xcoord_dofs_ub,
                     size_type xdf,
                     const coord_type xlocal_coords[],
                     size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= db()*dl());
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  //require(jacobian_values() != 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::quadratic_2d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 3);

  // Body:

  ///@todo Implement.

  not_implemented();

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
void
fiber_bundle::quadratic_2d::
integrate(const dof_type xcoord_dofs[],
          size_type xcoord_dofs_ub,
          size_type xdf,
          const dof_type xintegrands[],
          size_type xintegrands_ub,
          value_type xresult_integrals[],
          size_type xresult_integrals_ub)
{
  ///@todo Get these correct.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xintegrands != 0);
  require(xintegrands_ub >= dl());
  require(xresult_integrals != 0);
  require(xresult_integrals_ub > 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::quadratic_2d::
integrate(const dof_type xcoord_dofs[],
          size_type xcoord_dofs_ub,
          size_type xdf,
          const dof_type xintegrand,
          value_type xresult_integrals[],
          size_type xresult_integrals_ub)
{
  ///@todo Get these correct.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xresult_integrals != 0);
  require(xresult_integrals_ub >= dl());

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::quadratic_2d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));
  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// DIFFERENTIABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
void
fiber_bundle::quadratic_2d::
dxi_local(size_type xlocal_coord_index,
          const dof_type xsource_dofs[],
          size_type xsource_dofs_ub,
          dof_type xresult_dofs[],
          size_type xresult_dofs_ub) const
{
  // Preconditions:

  require(xlocal_coord_index < db());
  require(xsource_dofs != 0);
  //require(xsource_dofs_ub >= dof_ct());
  require(xresult_dofs != 0);
  //require(xresult_dofs_ub >= dof_ct());

  // Body:

  // The 1st derivatives are constant for linear 2d.

  dof_type derivative = xsource_dofs[xlocal_coord_index] - xsource_dofs[2];

  for(int i=0; i<3; ++i)
    xresult_dofs[i] = derivative;

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::quadratic_2d::
jacobian(const dof_type xcoord_dofs[],
         size_type xcoord_dofs_ub,
         size_type xdf,
         const dof_type xlocal_coords[],
         size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= db()*dl());
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(jacobian_values() != 0);

  // Body:

  not_implemented();

  ///@todo Implement.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::quadratic_2d::
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
fiber_bundle::quadratic_2d::
local_coordinates(pod_index_type xindex, coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[6][2] =
    {
      {
        1.0, 0.0
      }
      , {0.0, 1.0}, {0.0, 0.0}, {0.5, 0.5}, {0.0, 0.5}, {0.5, 0.0}
    };

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::quadratic_2d::
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

  dof_type zero = 0.0 - 1000.0*numeric_limits<dof_type>::epsilon();
  dof_type one  = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= zero) && (u <= one) && (v >= zero) && (v <= one);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::quadratic_2d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 12);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 2);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);

  // Body:

  cout << "quadratic_2d::coord_at_value()" << endl;

  // Dofs are assumed to be interleaved (x0, y0, x1, y1, x2, y2, ...).


  ///@todo Decide what order the coordinates will be in.
  ///        The following assumes the corner nodes come first.

  // Note: The local ids for the corner nodes is (0, 1, 2)
  //       and for the midside nodes (3, 4, 5)

  // Corner nodes:

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[2];
  dof_type x2 = xdofs[4];

  dof_type y0 = xdofs[1];
  dof_type y1 = xdofs[3];
  dof_type y2 = xdofs[5];

  // Midside nodes:

  /// @hack commented out to prevent KCC warnings about
  /// declared but not referenced.

  //   dof_type x3 = xdofs[6];
  //   dof_type x4 = xdofs[8];
  //   dof_type x5 = xdofs[10];

  //   dof_type y3 = xdofs[7];
  //   dof_type y4 = xdofs[9];
  //   dof_type y5 = xdofs[11];


  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];

  ///@todo Finish:  What is below is copied from linear_2d.

  double a0 = x1*y2 - x2*y1;
  double a1 = x2*y0 - x0*y2;
  double a2 = x0*y1 - x1*y0;

  double b0 = y1 - y2;
  double b1 = y2 - y0;
  //double b2 = y0 - y1;

  double c0 = x2 - x1;
  double c1 = x0 - x2;
  //double c2 = x1 - x0;

  double area_x_2 = a0 + a1 + a2;

  double shape0 = (a0 + b0*x_global + c0*y_global) / area_x_2;
  double shape1 = (a1 + b1*x_global + c1*y_global) / area_x_2;
  //double shape2 = (a2 + b2*x_global + c2*y_global) / area_x_2;

  //double shape2 = 1.0 - (shape0 + shape1);

  cout << "shape0 = " << shape0 << endl;
  cout << "shape1 = " << shape1 << endl;
  cout << "shape2 = " << 1.0 - (shape0 + shape1) << endl;

  // Return 2 local (area) coordinates and later generate the third
  // from the fact that they sum to 1 (ie: shape0 + shape1 + shape2 = 1).

  xlocal_coords[0] = shape0;
  xlocal_coords[1] = shape1;

  // Return non null only if the search point is inside the element
  // or on the element boundary.

  //if((shape0 >= 0.0) && (shape1 >= 0.0) && (shape2 >= 0.0))
  //  result = xlocal_coords;

  // Postconditions:

  ensure(invariant());

  //ensure(result != 0 ? result == xlocal_coords : true);

  /// @issue Made unexecutable because it is true only in exact arithmetic.

  //   ensure(unexecutable(result != 0
  //                       ? value_at_coord_ua(xdofs, xdofs_ub, xcoords, xcoords_ub) == xvalue
  //                       : true));

  //return result;

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::quadratic_2d*
fiber_bundle::quadratic_2d::
clone() const
{
  quadratic_2d* result;

  // Preconditions:

  // Body:

  result = new quadratic_2d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}

///
fiber_bundle::quadratic_2d&
fiber_bundle::quadratic_2d::
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
fiber_bundle::quadratic_2d&
fiber_bundle::quadratic_2d::
operator=(const quadratic_2d& xother)
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
fiber_bundle::quadratic_2d::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && linear_fcn_space::invariant();

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
fiber_bundle::quadratic_2d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const quadratic_2d*>(xother) != 0;

  // Postconditions:

  return result;

}


// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

