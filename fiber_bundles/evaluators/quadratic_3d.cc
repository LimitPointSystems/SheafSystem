//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class quadratic_3d

#include "quadratic_3d.h"
#include "assert_contract.h"
#include "std_cmath.h"
#include "std_iostream.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// QUADRATIC_3D FACET
// ===========================================================

///
fiber_bundle::quadratic_3d::
quadratic_3d()
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
fiber_bundle::quadratic_3d::
quadratic_3d(const quadratic_3d& xother)
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
fiber_bundle::quadratic_3d::
~quadratic_3d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

/// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::quadratic_3d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 10);

  // Exit:

  return result;
}

void
fiber_bundle::quadratic_3d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:
  // Evaluate the interpolation functions.

  double L0 = xlocal_coord[0];
  double L1 = xlocal_coord[1];
  double L2 = xlocal_coord[2];
  double L3 = 1.0 - (L0 + L1 + L2);

  // Corner nodes:

  _basis_values[0] = (2.0*L0-1.0)*L0;
  _basis_values[1] = (2.0*L1-1.0)*L1;
  _basis_values[2] = (2.0*L2-1.0)*L2;
  _basis_values[3] = (2.0*L3-1.0)*L3;

  // Midside nodes:

  _basis_values[4] = 4.0*L0*L1;
  _basis_values[5] = 4.0*L0*L2;
  _basis_values[6] = 4.0*L0*L3;
  _basis_values[7] = 4.0*L1*L2;
  _basis_values[8] = 4.0*L2*L3;
  _basis_values[9] = 4.0*L3*L1;

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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

  // The 1st derivatives are constant for linear 3d.

  dof_type derivative = xsource_dofs[xlocal_coord_index] - xsource_dofs[3];

  for(int i=0; i<4; ++i)
    xresult_dofs[i] = derivative;

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
local_coordinates(pod_index_type xindex, coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[10][3] =
    {
      // Corner nodes:

      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, 0.0},

      // Mid-side nodes

      {0.5, 0.5, 0.0},
      {0.5, 0.0, 0.5},
      {0.5, 0.0, 0.0},
      {0.0, 0.5, 0.5},
      {0.0, 0.0, 0.5},
      {0.0, 0.5, 0.0}
    };

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];
  xresult[2] = lcoords[xindex][2];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::quadratic_3d::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  dof_type u = xlocal_coords[0];
  dof_type v = xlocal_coords[1];
  dof_type w = xlocal_coords[2];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type zero = 0.0 - 1000.0*numeric_limits<dof_type>::epsilon();
  dof_type one  = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= zero) && (u <= one) &&
                (v >= zero) && (v <= one) &&
                (w >= zero) && (w <= one);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::quadratic_3d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 30);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  cout << "quadratic_3d::coord_at_value()" << endl;


  // Dofs are assumed to be interleaved (x0, y0,z0,  x1, y1, z1, ...).

  ///@todo Decide what order the coordinates will be in.
  ///        The following assumes the corner nodes come first.

  // Note: The local ids for the corner nodes is (0, 1, 2, 3)
  //       and for the midside nodes (3, 4, 5, 6, 7, 8, 9)

  // Corner nodes:

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[3];
  dof_type x2 = xdofs[6];
  dof_type x3 = xdofs[9];

  dof_type y0 = xdofs[1];
  dof_type y1 = xdofs[4];
  dof_type y2 = xdofs[7];
  dof_type y3 = xdofs[10];

  dof_type z0 = xdofs[2];
  dof_type z1 = xdofs[5];
  dof_type z2 = xdofs[8];
  dof_type z3 = xdofs[11];

  // Midside nodes:

  /// @hack commented out to suppress compiler warnings
  /// about declared but not referenced.

  //   dof_type x4 = xdofs[12];
  //   dof_type x5 = xdofs[15];
  //   dof_type x6 = xdofs[18];
  //   dof_type x7 = xdofs[21];
  //   dof_type x8 = xdofs[24];
  //   dof_type x9 = xdofs[27];

  //   dof_type y4 = xdofs[12];
  //   dof_type y5 = xdofs[16];
  //   dof_type y6 = xdofs[19];
  //   dof_type y7 = xdofs[22];
  //   dof_type y8 = xdofs[25];
  //   dof_type y9 = xdofs[28];

  //   dof_type z4 = xdofs[13];
  //   dof_type z5 = xdofs[17];
  //   dof_type z6 = xdofs[20];
  //   dof_type z7 = xdofs[23];
  //   dof_type z8 = xdofs[26];
  //   dof_type z9 = xdofs[29];

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];
  dof_type z_global = xglobal_coords[2];

  ///@todo Finish:  What is below is copied from linear_3d.

  ////////////////////////////////////////////////////////////////////////

  double a01 = x0*y1-x1*y0;
  double a02 = x0*y2-x2*y0;
  double a03 = x0*y3-x3*y0;
  double a12 = x1*y2-x2*y1;
  double a13 = x1*y3-x3*y1;
  double a23 = x2*y3-x3*y2;

  double a10 = -a01;
  double a20 = -a02;
  double a30 = -a03;
  double a21 = -a12;
  double a31 = -a13;
  double a32 = -a23;

  ////////////////////////////////////////////////////////////////////////

  double b01 = y0-y1;
  double b02 = y0-y2;
  double b12 = y1-y2;
  double b23 = y2-y3;
  double b30 = y3-y0;
  double b31 = y3-y1;

  /// @hack commented out to suppress compiler warnings
  /// about declared but not referenced.

  //  double b10 = -b01;
  double b20 = -b02;
  //  double b21 = -b12;
  double b32 = -b23;
  double b03 = -b30;
  double b13 = -b31;

  double c01 = x0-x1;
  double c02 = x0-x2;
  double c12 = x1-x2;
  double c23 = x2-x3;
  double c30 = x3-x0;
  double c31 = x3-x1;

  double c10 = -c01;
  //  double c20 = -c02;
  double c21 = -c12;
  double c03 = -c30;
  double c13 = -c31;
  double c32 = -c23;

  ////////////////////////////////////////////////////////////////////////

  // The following z## values represent the adjoint of the matrix:
  //
  //  1  1  1  1
  // x0 x2 x3 x4
  // y0 y2 y3 y4
  // z0 z2 z3 z4
  //
  // (Dividing by the determinant gives the inverse).

  double z00 = a23*z1 + a31*z2 + a12*z3;
  double z01 = b23*z1 + b31*z2 + b12*z3;
  double z02 = c32*z1 + c13*z2 + c21*z3;
  double z03 = a32 + a21 + a13;

  double z10 = a32*z0 + a03*z2 + a20*z3;
  double z11 = b32*z0 + b03*z2 + b20*z3;
  double z12 = c23*z0 + c30*z2 + c02*z3;
  double z13 = a23 + a02 + a30;

  double z20 = a13*z0 + a30*z1 + a01*z3;
  double z21 = b13*z0 + b30*z1 + b01*z3;
  double z22 = c31*z0 + c03*z1 + c10*z3;
  double z23 = a31 + a10 + a03;

  double z30 = a21*z0 + a02*z1 + a10*z2;
  //   double z31 = b21*z0 + b02*z1 + b10*z2;
  //   double z32 = c12*z0 + c20*z1 + c01*z2;
  //   double z33 = a12 + a01 + a20;

  ////////////////////////////////////////////////////////////////////////

  // The determinant (which is 6 times the volume of the tetraherdon)
  // can be calcluated as:
  //   double det = a01*(z3-z2) + a02*(z1-z3) + a03*(z2-z1)
  //              + a12*(z3-z0) + a13*(z0-z2) + a23*(z1-z0);

  // However, the following is more efficient:
  double det = z00 + z10 + z20 + z30;

  cout << " det = " << det << endl;

  double shape0 = (z00 + z01*x_global + z02*y_global + z03*z_global) / det;
  double shape1 = (z10 + z11*x_global + z12*y_global + z13*z_global) / det;
  double shape2 = (z20 + z21*x_global + z22*y_global + z23*z_global) / det;

  //double shape3 = (z30 + z31*x_global + z32*y_global + z33*z_global) / det;
  double shape3 = 1.0 - (shape0 + shape1 + shape2);

  cout << "shape0 = " << shape0 << endl;
  cout << "shape1 = " << shape1 << endl;
  cout << "shape2 = " << shape2 << endl;
  cout << "shape3 = " << shape3 << endl;

  ////////////////////////////////////////////////////////////////////////

  // Return 3 local (area) coordinates and later generate the fourth from
  // the fact that they sum to 1 (ie: shape0 + shape1 + shape2 + shape3 = 1).

  xlocal_coords[0] = shape0;
  xlocal_coords[1] = shape1;
  xlocal_coords[2] = shape1;

  // Return non null only if the search point is inside the element
  // or on the element boundary.

  //if((shape0 >= 0.0) && (shape1 >= 0.0) && (shape2 >= 0.0) && (shape3 >= 0.0))
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
fiber_bundle::quadratic_3d*
fiber_bundle::quadratic_3d::
clone() const
{
  quadratic_3d* result;

  // Preconditions:

  // Body:

  result = new quadratic_3d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}

///
fiber_bundle::quadratic_3d&
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d&
fiber_bundle::quadratic_3d::
operator=(const quadratic_3d& xother)
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
fiber_bundle::quadratic_3d::
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
fiber_bundle::quadratic_3d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const quadratic_3d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================



