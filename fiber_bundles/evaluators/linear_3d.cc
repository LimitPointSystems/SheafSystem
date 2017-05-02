
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

// Implementation for class linear_3d

#include "SheafSystem/linear_3d.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_cmath.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_limits.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// LINEAR_3D FACET
// ===========================================================

///
fiber_bundle::linear_3d::
linear_3d()
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::linear_3d::
linear_3d(const linear_3d& xother)
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;
  _basis_deriv_values = _basis_deriv_value_buffer;
  _jacobian_values = _jacobian_value_buffer;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
fiber_bundle::linear_3d::
~linear_3d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  return;
}

///
double
fiber_bundle::linear_3d::
determinant_3x3(double a00, double a01, double a02,
                double a10, double a11, double a12,
                double a20, double a21, double a22)
{
  double result = a00*(a11*a22-a12*a21)
                  - a10*(a01*a22-a02*a21)
                  + a20*(a01*a12-a02*a11);

  return result;
}

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::linear_3d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 4);

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_3d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions.

  _basis_values[0] = xlocal_coord[0];
  _basis_values[1] = xlocal_coord[1];
  _basis_values[2] = xlocal_coord[2];
  _basis_values[3] = 1.0 - (_basis_values[0] + _basis_values[1] + _basis_values[2]);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_3d::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  // Evaluate the derivatives of the interpolation functions.
  // The derivatives are interleaved (N,r[0], N,s[0], N,t[0],
  //  N,r[1], N,s[1], N,t[1], ...).

  // Here the basis functions are in terms of barycentric coordinates.
  // given barycentric coordinates L0, L1, L2, L3 (L0+L1+L2+L3=1) where we use
  // the the convention that L3 = 1-L0-L1-L2.

  // The basis fumctions are:
  //   N0(r, s, t) = r;
  //   N1(r, s, t) = s;
  //   N2(r, s, t) = t;
  //   N3(r, s, t) = 1-r-s-t;

  // Note that the basis functions are linear in r,s,t.
  // Therefore the derivatives are constant and the
  // local coordinates are not needed in their evaluation.

  // Derivatives with respect to r.

  _basis_deriv_value_buffer[ 0] =  1.0;
  _basis_deriv_value_buffer[ 3] =  0.0;
  _basis_deriv_value_buffer[ 6] =  0.0;
  _basis_deriv_value_buffer[ 9] = -1.0;

  // Derivatives with respect to s.

  _basis_deriv_value_buffer[ 1] =  0.0;
  _basis_deriv_value_buffer[ 4] =  1.0;
  _basis_deriv_value_buffer[ 7] =  0.0;
  _basis_deriv_value_buffer[10] = -1.0;

  // Derivative with respect to t.

  _basis_deriv_value_buffer[ 2] =  0.0;
  _basis_deriv_value_buffer[ 5] =  0.0;
  _basis_deriv_value_buffer[ 8] =  1.0;
  _basis_deriv_value_buffer[11] = -1.0;

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
fiber_bundle::linear_3d::
jacobian_determinant(const dof_type xcoord_dofs[],
                     size_type xcoord_dofs_ub,
                     size_type xdf,
                     const coord_type xlocal_coords[],
                     size_type xlocal_coords_ub)
{
  // Precondition: xdf = 2 or xdf = 3 ?.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 3);

  // Get the jacobian matrix.

  jacobian(xcoord_dofs, xcoord_dofs_ub, xdf, xlocal_coords, xlocal_coords_ub);
  const value_type* jvalues = jacobian_values();

  //===========================================================================

  // Form the metric tensor g = [J]'*[J] (' == transpose).

  value_type g00 = 0.0;
  value_type g01 = 0.0;
  value_type g02 = 0.0;
  value_type g11 = 0.0;
  value_type g12 = 0.0;
  value_type g22 = 0.0;

  // Jacobian matrix has dimensions xdf x 2.

  // Just do the matrix multiplication in place (for efficiency).

  int index = 0;
  for(int i=0; i<xdf; ++i)
  {
    value_type Ji0 = jvalues[index++];
    value_type Ji1 = jvalues[index++];
    value_type Ji2 = jvalues[index++];

    g00 += Ji0*Ji0;
    g01 += Ji0*Ji1;
    g02 += Ji0*Ji2;
    g11 += Ji1*Ji1;
    g12 += Ji1*Ji2;
    g22 += Ji2*Ji2;
  }

  // Metric tensor is symmetric, so g10 = g01.

  value_type g10 = g01;
  value_type g20 = g02;
  value_type g21 = g12;

  // Evaulate the determinant of the metrix tensor

  value_type det = g00*(g11*g22-g12*g21)
                   - g10*(g01*g22-g02*g21)
                   + g20*(g01*g12-g02*g11);

  // The "jacobian determinant" is the square root of det;

  value_type result = sqrt(fabs(det));

  //===========================================================================

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::linear_3d::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub, size_type xdf)
{
  // Coordinates are interleaved (x0,y0,z0,x1,y1,z1,...).

  // Here we use the following equation:
  //
  //  6*Volume = | 1 x0 y0 z0 |
  //             | 1 x1 y1 z1 |
  //             | 1 x2 y2 z2 |
  //             | 1 x3 y3 z3 |

  dof_type x0 = xcoord_dofs[ 0];
  dof_type x1 = xcoord_dofs[ 3];
  dof_type x2 = xcoord_dofs[ 6];
  dof_type x3 = xcoord_dofs[ 9];

  dof_type y0 = xcoord_dofs[ 1];
  dof_type y1 = xcoord_dofs[ 4];
  dof_type y2 = xcoord_dofs[ 7];
  dof_type y3 = xcoord_dofs[10];

  dof_type z0 = xcoord_dofs[ 2];
  dof_type z1 = xcoord_dofs[ 5];
  dof_type z2 = xcoord_dofs[ 8];
  dof_type z3 = xcoord_dofs[11];

  // Evaluate the 4x4 determinant using cofactors.

  value_type result = determinant_3x3(x1, y1, z1, x2, y2, z2, x3, y3, z3)
                      - determinant_3x3(x0, y0, z0, x2, y2, z2, x3, y3, z3)
                      + determinant_3x3(x0, y0, z0, x1, y1, z1, x3, y3, z3)
                      - determinant_3x3(x0, y0, z0, x1, y1, z1, x2, y2, z2);

  result /= 6.0;

  return result;
}

///
void
fiber_bundle::linear_3d::
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

  double vol = volume(xcoord_dofs, xcoord_dofs_ub, 3);
  double quarter_vol = 0.25*vol;

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    dof_type fn = 0.0;
    const dof_type* integrands_n = &xintegrands[i*4];

    for(int k=0; k<4; ++k)
    {
      fn += integrands_n[k];
    }

    xresult_integrals[i] = fn*quarter_vol;
  }

  //cout << " vol = " << vol << endl;

  /// @todo Add method number_of_gauss_points().

  //   static int NUM_GAUSS_POINTS = 4;

  //   for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  //   {
  //     coord_type local_coords[4];
  //     gauss_point(n, local_coords, 4);

  //     //double det = determinant(xcoord_dofs, xcoord_dofs_ub, local_coords, 4);

  //     basis_at_coord(local_coords, 4);
  //  const value_type* basis = basis_values();

  //     for(int i=0; i<xresult_integrals_ub; ++i)
  //     {
  //       dof_type fn = 0.0;
  //       const dof_type* integrands_n = xintegrands+(i*4);

  //       for(int k=0; k<4; ++k)
  //    {
  //         fn += basis[k]*integrands_n[k];
  //    }

  //       xresult_integrals[i] += det*fn;
  //  }
  //   }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_3d::
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

  double vol = volume(xcoord_dofs, xcoord_dofs_ub, 3);

  value_type value = 0.25*xintegrand*vol;

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = value;
  }

  //   // Initialize the integrals.

  //   for(int i=0; i<xresult_integrals_ub; ++i)
  //   {
  //     xresult_integrals[i] = 0.0;
  //   }


  //   static int NUM_GAUSS_POINTS = 8;

  //   for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  //   {
  //     coord_type local_coords[3];
  //     gauss_point(n, local_coords, 3);

  //  double det = determinant(xcoord_dofs, xcoord_dofs_ub, local_coords, 3);

  //     cout << " det = " << det << endl;

  //     basis_at_coord(local_coords, 3);
  //  const value_type* basis = basis_values();

  //     for(int i=0; i<8; ++i)
  //     {
  //       xresult_integrals[i] += basis[i] * det;
  //     }
  //   }

  //   // Multiple by "F" for constant F case.

  //   for(int i=0; i<8; ++i)
  //   {
  //     xresult_integrals[i] *= xintegrand;
  //   }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_3d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  // Local coordinates of the gauss points.

  static const double d = 0.25;

  xresult[0] = d;
  xresult[1] = d;
  xresult[2] = d;
  xresult[3] = d;

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

// ===========================================================
// DIFFERENTIABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
void
fiber_bundle::linear_3d::
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
fiber_bundle::linear_3d::
jacobian(const dof_type xcoord_dofs[],
         size_type xcoord_dofs_ub,
         size_type xdf,
         const dof_type xlocal_coords[],
         size_type xlocal_coords_ub)
{
  // Preconditions:

  ///@todo Fix!

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= xdf*dl());
  require(xdf == 2 || xdf == 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);
  require(jacobian_values() != 0);

  // Body:

  // Get the derivatives of the basis functions at the
  // specified local coordinates.

  int local_coords_ct = 3;

  basis_derivs_at_coord(xlocal_coords, local_coords_ct);
  const value_type* derivs = basis_deriv_values();

  // Loop over the columns of the jacobian matrix
  // (columns correspond to the derivatives w.r.t. the local coordinates.)

  for(int i=0; i<local_coords_ct; ++i)
  {
    // Loop over the rows of the jacobian matrix
    // (rows correspond to the global coordinates.)

    for(int j=0; j<xdf; ++j)
    {
      // Loop over the nodes and sum the product of the derivatives and
      // the global nodal coordinates.

      value_type sum = 0.0;

      for(int k=0; k<dl(); ++k)
      {
        // Derivatives and coordinate dofs are "interleaved".

        value_type deriv = derivs[local_coords_ct*k+i];
        value_type coord = xcoord_dofs[xdf*k+j];

        sum += deriv*coord;

        cout << "++++++++++++++++++++++++++++++++++" << endl;
        cout << "    deriv = " << deriv << endl;
        cout << "    coord = " << coord << endl;
        cout << "    sum = " << sum << endl;
        cout << "++++++++++++++++++++++++++++++++++" << endl;
      }

      // Store the sum in the appropriate location in the Jacobian matrix.

      int ij = local_coords_ct*j+i;
      _jacobian_values[ij] = sum;
    }
  }

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
fiber_bundle::linear_3d::
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
fiber_bundle::linear_3d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[4][3] =
    {
      {
        1.0, 0.0, 0.0
      }
      , {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}
    } ;

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];
  xresult[2] = lcoords[xindex][2];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
void
fiber_bundle::linear_3d::
center(coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require(xresult != 0);
  require(xresult_ub >= db());

  // Body:

  static coord_type one_fourth =
    static_cast<coord_type>(1.0)/static_cast<coord_type>(4.0);

  xresult[0] = one_fourth;
  xresult[1] = one_fourth;
  xresult[2] = one_fourth;

  // Postconditions:


  // Exit:

  return;
}

///
bool
fiber_bundle::linear_3d::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);

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
fiber_bundle::linear_3d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 9);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

  // cout << "linear_3d::coord_at_value()" << endl;

  // The dofs are assumed to be interleaved
  // (x0, y0, z0, x1, y1, z1, x2, y2, z2).

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

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];
  dof_type z_global = xglobal_coords[2];

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

  // cout << " det = " << det << endl;

  double shape0 = (z00 + z01*x_global + z02*y_global + z03*z_global) / det;
  double shape1 = (z10 + z11*x_global + z12*y_global + z13*z_global) / det;
  double shape2 = (z20 + z21*x_global + z22*y_global + z23*z_global) / det;

  // double shape3 = (z30 + z31*x_global + z32*y_global + z33*z_global) / det;

  double shape3 = 1.0 - (shape0 + shape1 + shape2);

  //   cout << "shape0 = " << shape0 << endl;
  //   cout << "shape1 = " << shape1 << endl;
  //   cout << "shape2 = " << shape2 << endl;
  //   cout << "shape3 = " << shape3 << endl;

  ////////////////////////////////////////////////////////////////////////

  // Return 3 local (area) coordinates.

  xlocal_coords[0] = shape0;
  xlocal_coords[1] = shape1;
  xlocal_coords[2] = shape2;

  // Return non null only if the search point is inside the element
  // or on the element boundary.

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::linear_3d*
fiber_bundle::linear_3d::
clone() const
{
  linear_3d* result;

  // Preconditions:

  // Body:

  result = new linear_3d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::linear_3d&
fiber_bundle::linear_3d::
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
fiber_bundle::linear_3d&
fiber_bundle::linear_3d::
operator=(const linear_3d& xother)
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
fiber_bundle::linear_3d::
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
fiber_bundle::linear_3d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const linear_3d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================


