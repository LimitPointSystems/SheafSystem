
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

// Implementation for class trilinear_3d

#include "trilinear_3d.h"
#include "assert_contract.h"
#include "error_message.h"
#include "std_iostream.h"
#include "std_iomanip.h"
#include "std_limits.h"
#include "std_cmath.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

namespace
{
// The convergence failure parameter.

const int ITR_UB = 10;

// The convergence success parameter.
/// @issue we've found it difficult to specify a reliable tolerance
/// using numeric_limits::epsilon(). But because the unknowns in the
/// inversion solver are local coordinates that are always in the range (-1, 1),
/// we can specify an absolute tolerance.

// const double TOLERANCE = 1000.0*numeric_limits<double>::epsilon();
const double TOLERANCE = 1.0e-9;

// True if x2 is close enough to x1 to be considered converged.

///@issue Currently setting the test to use the absolute difference
/// due to certain cases where convergence to 0.0 is not working.
/// This is an acceptable approach because the values for x1 and x2
/// are always in the range (-1, 1), so there are no scaling issues.

inline bool is_close_enough(double x1, double x2)
{
  //return ( fabs(x1-x2) <= ((fabs(x1)+fabs(x2))*TOLERANCE) );
  //return ( (x2 == 0.0) ? fabs(x1) : fabs((x2 - x1)/x2) ) <= TOLERANCE;
  return (fabs(x2 - x1) <= TOLERANCE);
}
}

// ===========================================================
// TRILINEAR_3D FACET
// ===========================================================

///
fiber_bundle::trilinear_3d::
trilinear_3d()
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


// Copy constructor.
///
fiber_bundle::trilinear_3d::
trilinear_3d(const trilinear_3d& xother)
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




// Destructor.
///
fiber_bundle::trilinear_3d::
~trilinear_3d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

///
double
fiber_bundle::trilinear_3d::
inverse_jacobian(const double xjacobian[3][3],
                 double xinverse_jacobian[3][3])
{
  // Invert the jacobian matrix

  double j00 = xjacobian[0][0];
  double j01 = xjacobian[0][1];
  double j02 = xjacobian[0][2];
  double j10 = xjacobian[1][0];
  double j11 = xjacobian[1][1];
  double j12 = xjacobian[1][2];
  double j20 = xjacobian[2][0];
  double j21 = xjacobian[2][1];
  double j22 = xjacobian[2][2];

  double c00 = j11 * j22 - j12 * j21;
  double c01 = j12 * j20 - j10 * j22;
  double c02 = j10 * j21 - j11 * j20;

  double c10 = j02 * j21 - j01 * j22;
  double c11 = j00 * j22 - j02 * j20;
  double c12 = j01 * j20 - j00 * j21;

  double c20 = j01 * j12 - j02 * j11;
  double c21 = j02 * j10 - j00 * j12;
  double c22 = j00 * j11 - j01 * j10;

  double determinant = j00 * c00 + j01 * c01 + j02 * c02;

  xinverse_jacobian[0][0] = c00 / determinant;
  xinverse_jacobian[0][1] = c10 / determinant;
  xinverse_jacobian[0][2] = c20 / determinant;
  xinverse_jacobian[1][0] = c01 / determinant;
  xinverse_jacobian[1][1] = c11 / determinant;
  xinverse_jacobian[1][2] = c21 / determinant;
  xinverse_jacobian[2][0] = c02 / determinant;
  xinverse_jacobian[2][1] = c12 / determinant;
  xinverse_jacobian[2][2] = c22 / determinant;

  // Return the determinant also.

  return determinant;
}

// ///
// double
// trilinear_3d::
// determinant(const dof_type xcoord_dofs[],
//             size_type xcoord_dofs_ub,
//             const coord_type xlocal_coords[],
//             size_type xlocal_coords_ub)
// {
//   return jacobian(xcoord_dofs, xcoord_dofs_ub,
//                   xlocal_coords, xlocal_coords_ub);
// }

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::trilinear_3d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 8);

  // Exit:

  return result;
}

///
void
fiber_bundle::trilinear_3d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{

  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions.

  dof_type r = xlocal_coord[0];
  dof_type s = xlocal_coord[1];
  dof_type t = xlocal_coord[2];

  _basis_values[0] = 0.125*(1-r)*(1-s)*(1-t);
  _basis_values[1] = 0.125*(1+r)*(1-s)*(1-t);
  _basis_values[2] = 0.125*(1+r)*(1+s)*(1-t);
  _basis_values[3] = 0.125*(1-r)*(1+s)*(1-t);
  _basis_values[4] = 0.125*(1-r)*(1-s)*(1+t);
  _basis_values[5] = 0.125*(1+r)*(1-s)*(1+t);
  _basis_values[6] = 0.125*(1+r)*(1+s)*(1+t);
  _basis_values[7] = 0.125*(1-r)*(1+s)*(1+t);

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::trilinear_3d::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  // Evaluate the derivatives of the interpolation functions.
  // The derivatives are interleaved (N,r[0], N,s[0], N,t[0],
  //  N,r[1], N,s[1], N,t[1], ...).

  double r = xlocal_coords[0];
  double s = xlocal_coords[1];
  double t = xlocal_coords[2];

  double rp = 1.0 + r;
  double rm = 1.0 - r;
  double sp = 1.0 + s;
  double sm = 1.0 - s;
  double tp = 1.0 + t;
  double tm = 1.0 - t;

  double rmxsm = rm * sm;
  double rpxsm = rp * sm;
  double rpxsp = rp * sp;
  double rmxsp = rm * sp;

  double rmxtm = rm * tm;
  double rpxtm = rp * tm;
  double rpxtp = rp * tp;
  double rmxtp = rm * tp;

  double smxtm = sm * tm;
  double spxtm = sp * tm;
  double spxtp = sp * tp;
  double smxtp = sm * tp;

  // Derivative with respect to r.

  _basis_deriv_value_buffer[ 0] = -smxtm;
  _basis_deriv_value_buffer[ 3] =  smxtm;
  _basis_deriv_value_buffer[ 6] =  spxtm;
  _basis_deriv_value_buffer[ 9] = -spxtm;
  _basis_deriv_value_buffer[12] = -smxtp;
  _basis_deriv_value_buffer[15] =  smxtp;
  _basis_deriv_value_buffer[18] =  spxtp;
  _basis_deriv_value_buffer[21] = -spxtp;

  // Derivative with respect to s.

  _basis_deriv_value_buffer[ 1] = -rmxtm;
  _basis_deriv_value_buffer[ 4] = -rpxtm;
  _basis_deriv_value_buffer[ 7] =  rpxtm;
  _basis_deriv_value_buffer[10] =  rmxtm;
  _basis_deriv_value_buffer[13] = -rmxtp;
  _basis_deriv_value_buffer[16] = -rpxtp;
  _basis_deriv_value_buffer[19] =  rpxtp;
  _basis_deriv_value_buffer[22] =  rmxtp;

  // Derivative with respect to t.

  _basis_deriv_value_buffer[ 2] = -rmxsm;
  _basis_deriv_value_buffer[ 5] = -rpxsm;
  _basis_deriv_value_buffer[ 8] = -rpxsp;
  _basis_deriv_value_buffer[11] = -rmxsp;
  _basis_deriv_value_buffer[14] =  rmxsm;
  _basis_deriv_value_buffer[17] =  rpxsm;
  _basis_deriv_value_buffer[20] =  rpxsp;
  _basis_deriv_value_buffer[23] =  rmxsp;

  for(int i=0; i<24; i++)
  {
    _basis_deriv_value_buffer[i] *= 0.125;
  }

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
fiber_bundle::trilinear_3d::
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

  // Jacobian matrix has dimensions xdf x 3.

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
fiber_bundle::trilinear_3d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 3);

  // Body:

  /// @todo Add method number_of_gauss_points().

  static int NUM_GAUSS_POINTS = 8;

  value_type result = 0.0;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[3];
    gauss_point(n, local_coords, 3);

    value_type det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                          local_coords, 3);

    //     cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    //     cout << "trilinear_3d::volume det = " << det << endl;
    //     cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    // Just sum up the integrand values since the gauss weights are all 1.0
    // for 2x2x2 quadrature.

    result += det;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
void
fiber_bundle::trilinear_3d::
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

  // Initialize the integrals.

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = 0.0;
  }

  /// @todo Add method number_of_gauss_points().

  static int NUM_GAUSS_POINTS = 8;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[3];
    gauss_point(n, local_coords, 3);

    //double det = determinant(xcoord_dofs, xcoord_dofs_ub, local_coords, 3);
    value_type det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                          local_coords, 3);

    //cout << " det = " << det << endl;

    basis_at_coord(local_coords, 3);
    const value_type* basis = basis_values();

    for(int i=0; i<xresult_integrals_ub; ++i)
    {
      dof_type fn = 0.0;
      const dof_type* integrands_n = xintegrands+(i*8);

      for(int k=0; k<8; ++k)
      {
        fn += basis[k]*integrands_n[k];
      }

      xresult_integrals[i] += det*fn;
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::trilinear_3d::
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

  // Initialize the integrals.

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = 0.0;
  }

  static int NUM_GAUSS_POINTS = 8;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[3];
    gauss_point(n, local_coords, 3);

    value_type det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                          local_coords, 3);

    //cout << " det = " << det << endl;

    basis_at_coord(local_coords, 3);
    const value_type* basis = basis_values();

    for(int i=0; i<8; ++i)
    {
      xresult_integrals[i] += basis[i] * det;
    }
  }

  // Multiple by "F" for constant F case.

  for(int i=0; i<8; ++i)
  {
    xresult_integrals[i] *= xintegrand;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::trilinear_3d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  // Local coordinates of the gauss points.

  static const double d = 1.0 / sqrt(3.0);
  static const coord_type gauss_coords[8][3] =
    {
      {
        -d, -d, -d
      }
      , {d, -d, -d}, {d, d, -d}, {-d, d, -d},
      {-d, -d,  d}, {d, -d,  d}, {d, d,  d}, {-d, d,  d}
    };

  xresult[0] = gauss_coords[xindex][0];
  xresult[1] = gauss_coords[xindex][1];
  xresult[2] = gauss_coords[xindex][2];

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
fiber_bundle::trilinear_3d::
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

  if(xlocal_coord_index == 0)
  {
    dof_type d_minus_minus = 0.5 * (xsource_dofs[1] - xsource_dofs[0]);
    dof_type d_plus_minus  = 0.5 * (xsource_dofs[2] - xsource_dofs[3]);
    dof_type d_minus_plus  = 0.5 * (xsource_dofs[5] - xsource_dofs[4]);
    dof_type d_plus_plus   = 0.5 * (xsource_dofs[6] - xsource_dofs[7]);

    xresult_dofs[0] = d_minus_minus;
    xresult_dofs[1] = d_minus_minus;
    xresult_dofs[2] = d_plus_minus;
    xresult_dofs[3] = d_plus_minus;
    xresult_dofs[4] = d_minus_plus;
    xresult_dofs[5] = d_minus_plus;
    xresult_dofs[6] = d_plus_plus;
    xresult_dofs[7] = d_plus_plus;
  }
  else if(xlocal_coord_index == 1)
  {
    dof_type d_minus_minus = 0.5 * (xsource_dofs[3] - xsource_dofs[0]);
    dof_type d_plus_minus  = 0.5 * (xsource_dofs[2] - xsource_dofs[1]);
    dof_type d_minus_plus  = 0.5 * (xsource_dofs[7] - xsource_dofs[4]);
    dof_type d_plus_plus   = 0.5 * (xsource_dofs[6] - xsource_dofs[5]);

    xresult_dofs[0] = d_minus_minus;
    xresult_dofs[1] = d_plus_minus;
    xresult_dofs[2] = d_plus_minus;
    xresult_dofs[3] = d_minus_minus;
    xresult_dofs[4] = d_minus_plus;
    xresult_dofs[5] = d_plus_plus;
    xresult_dofs[6] = d_plus_plus;
    xresult_dofs[7] = d_minus_plus;

  }
  else
  {
    dof_type d_minus_minus = 0.5 * (xsource_dofs[4] - xsource_dofs[0]);
    dof_type d_plus_minus  = 0.5 * (xsource_dofs[5] - xsource_dofs[1]);
    dof_type d_minus_plus  = 0.5 * (xsource_dofs[7] - xsource_dofs[3]);
    dof_type d_plus_plus   = 0.5 * (xsource_dofs[6] - xsource_dofs[2]);

    xresult_dofs[0] = d_minus_minus;
    xresult_dofs[1] = d_plus_minus;
    xresult_dofs[2] = d_plus_plus;
    xresult_dofs[3] = d_minus_plus;
    xresult_dofs[4] = d_minus_minus;
    xresult_dofs[5] = d_plus_minus;
    xresult_dofs[6] = d_plus_plus;
    xresult_dofs[7] = d_minus_plus;
  }

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::trilinear_3d::
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

        //         cout << "++++++++++++++++++++++++++++++++++" << endl;
        //   cout << "    deriv = " << deriv << endl;
        //   cout << "    coord = " << coord << endl;
        //   cout << "    sum = " << sum << endl;
        //         cout << "++++++++++++++++++++++++++++++++++" << endl;
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

///@todo xlocal_coords_ub, etc.

// ///
// double
// trilinear_3d::
// jacobian(const dof_type xcoord_dofs[],
//          size_type xcoord_dofs_ub,
//          const coord_type xlocal_coords[],
//          size_type xlocal_coords_ub,
//          double xjacobian[3][3])
// {
//   // This method can be called with xjacobian == NULL
//   // which allows only the determinant to be computed
//   // and returned.

//   basis_derivs_at_coord(xlocal_coords, 3);
//   const value_type* derivs = basis_deriv_values();

//   double xr = 0.0;
//   double xs = 0.0;
//   double xt = 0.0;
//   double yr = 0.0;
//   double ys = 0.0;
//   double yt = 0.0;
//   double zr = 0.0;
//   double zs = 0.0;
//   double zt = 0.0;

//   for(int i = 0; i<dl(); ++i)
//   {
//  // Coords are interleaved (x0, y0, x1, y1, ...)

//  int index = db()*i;
//     double xi = xcoord_dofs[index];
//     double yi = xcoord_dofs[index+1];
//     double zi = xcoord_dofs[index+2];

//     //cout << " xi = " << xi << ", yi = " << yi << endl;

//  // Derivatives are "interleaved".

//     double Nri = derivs[index];
//     double Nsi = derivs[index+1];
//     double Nti = derivs[index+2];

//     xr += Nri * xi;
//     xs += Nsi * xi;
//     xt += Nti * xi;

//     yr += Nri * yi;
//     ys += Nsi * yi;
//     yt += Nti * yi;

//     zr += Nri * zi;
//     zs += Nsi * zi;
//     zt += Nti * zi;
//   }

//   if(xjacobian != NULL)
//   {
//     xjacobian[0][0] = xr;
//     xjacobian[0][1] = yr;
//     xjacobian[0][2] = yt;
//     xjacobian[1][0] = xs;
//     xjacobian[1][1] = ys;
//     xjacobian[1][2] = zs;
//     xjacobian[2][0] = xt;
//     xjacobian[2][1] = yt;
//     xjacobian[2][2] = zt;
//   }

//   // Calculate the determinant of the jacobian
//   // and return it.

//   double determinant = xr * (ys * zt - yt * zs)
//                      + xs * (yt * zr - yr * zt)
//                      + xt * (yr * zs - ys * zr);

//   return determinant;
// }

// ===========================================================
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::trilinear_3d::
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
fiber_bundle::trilinear_3d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[8][3] =
    {
      {
        -1.0, -1.0, -1.0
      },
      { 1.0, -1.0, -1.0},
      { 1.0,  1.0, -1.0},
      {-1.0,  1.0, -1.0},
      {-1.0, -1.0,  1.0},
      { 1.0, -1.0,  1.0},
      { 1.0,  1.0,  1.0},
      {-1.0,  1.0,  1.0}
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
bool
fiber_bundle::trilinear_3d::
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

  dof_type one = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= -one) && (u <= one) &&
                (v >= -one) && (v <= one) &&
                (w >= -one) && (w <= one);

  //   cout << "################# trilinear_3d::in_standard_domain" << endl;
  //   cout << "  one = " << one << endl;
  //   cout << "  u = " << u << endl;
  //   cout << "  v = " << v << endl;
  //   cout << "  w = " << w << endl;
  //   cout << "  result = " << result << endl;
  //   cout << "  (u >= -one) = " << (u >= -one) << endl;
  //   cout << "  (v >= -one) = " << (v >= -one) << endl;
  //   cout << "  (w >= -one) = " << (w >= -one) << endl;
  //   cout << "  (u <=  one) = " << (u <=  one) << endl;
  //   cout << "  (v <=  one) = " << (v <=  one) << endl;
  //   cout << "  (w <=  one) = " << (w <=  one) << endl;

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::trilinear_3d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 24);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 3);

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  bool ldiagnostic_output = true;
#else

  bool ldiagnostic_output = false;
#endif

  //require(xdofs != 0);
  // ...

  // Make one or two passes through the inversion alogorithm.
  // If first pass fails, repeat the algoithm with diagnostic output turned on.

  for(int ipass = 0; ipass < 2; ++ipass)
  {

    //The dofs are assumed to be interleaved
    // (x0, y0, z0, x1, y1, z1, x2, y2, z2, ...).

    dof_type x0 = xdofs[0];
    dof_type x1 = xdofs[3];
    dof_type x2 = xdofs[6];
    dof_type x3 = xdofs[9];
    dof_type x4 = xdofs[12];
    dof_type x5 = xdofs[15];
    dof_type x6 = xdofs[18];
    dof_type x7 = xdofs[21];

    dof_type y0 = xdofs[1];
    dof_type y1 = xdofs[4];
    dof_type y2 = xdofs[7];
    dof_type y3 = xdofs[10];
    dof_type y4 = xdofs[13];
    dof_type y5 = xdofs[16];
    dof_type y6 = xdofs[19];
    dof_type y7 = xdofs[22];

    dof_type z0 = xdofs[2];
    dof_type z1 = xdofs[5];
    dof_type z2 = xdofs[8];
    dof_type z3 = xdofs[11];
    dof_type z4 = xdofs[14];
    dof_type z5 = xdofs[17];
    dof_type z6 = xdofs[20];
    dof_type z7 = xdofs[23];

    dof_type x_global = xglobal_coords[0];
    dof_type y_global = xglobal_coords[1];
    dof_type z_global = xglobal_coords[2];

    if((ipass > 0) || ldiagnostic_output)
    {
      cout << endl << "trilinear_3d: global coords:"
      << setw(15) << x_global
      << setw(15) << y_global
      << setw(15) << z_global
      << endl;
    }

    ////////////////////////////////////////////////////////////////////////

    // Use Newton's method to determine the roots of the equations.

    // Initial starting values for the iteration.

    double r = 0.0;
    double s = 0.0;
    double t = 0.0;

    int itr_ct;
    for(itr_ct=0; itr_ct < ITR_UB; ++itr_ct)
    {

      // Evaluate basis functions at local coordinates (r,s,t).

      // Note: Each value is 8 times the correct value.  The
      //       missing 1/8 factor will be applied later for
      //       computational efficiency.

      double basis0 = (1-r)*(1-s)*(1-t);
      double basis1 = (1+r)*(1-s)*(1-t);
      double basis2 = (1+r)*(1+s)*(1-t);
      double basis3 = (1-r)*(1+s)*(1-t);
      double basis4 = (1-r)*(1-s)*(1+t);
      double basis5 = (1+r)*(1-s)*(1+t);
      double basis6 = (1+r)*(1+s)*(1+t);
      double basis7 = (1-r)*(1+s)*(1+t);

      double basis0_r = -(1-s)*(1-t);
      double basis1_r =  (1-s)*(1-t);
      double basis2_r =  (1+s)*(1-t);
      double basis3_r = -(1+s)*(1-t);
      double basis4_r = -(1-s)*(1+t);
      double basis5_r =  (1-s)*(1+t);
      double basis6_r =  (1+s)*(1+t);
      double basis7_r = -(1+s)*(1+t);

      double basis0_s = -(1-r)*(1-t);
      double basis1_s = -(1+r)*(1-t);
      double basis2_s =  (1+r)*(1-t);
      double basis3_s =  (1-r)*(1-t);
      double basis4_s = -(1-r)*(1+t);
      double basis5_s = -(1+r)*(1+t);
      double basis6_s =  (1+r)*(1+t);
      double basis7_s =  (1-r)*(1+t);

      double basis0_t = -(1-r)*(1-s);
      double basis1_t = -(1+r)*(1-s);
      double basis2_t = -(1+r)*(1+s);
      double basis3_t = -(1-r)*(1+s);
      double basis4_t =  (1-r)*(1-s);
      double basis5_t =  (1+r)*(1-s);
      double basis6_t =  (1+r)*(1+s);
      double basis7_t =  (1-r)*(1+s);

      double f = basis0*x0
                 + basis1*x1
                 + basis2*x2
                 + basis3*x3
                 + basis4*x4
                 + basis5*x5
                 + basis6*x6
                 + basis7*x7;

      f = 0.125*f - x_global;

      double g = basis0*y0
                 + basis1*y1
                 + basis2*y2
                 + basis3*y3
                 + basis4*y4
                 + basis5*y5
                 + basis6*y6
                 + basis7*y7;

      g = 0.125*g - y_global;

      double h = basis0*z0
                 + basis1*z1
                 + basis2*z2
                 + basis3*z3
                 + basis4*z4
                 + basis5*z5
                 + basis6*z6
                 + basis7*z7;

      h = 0.125*h - z_global;

      // Evaluate the derivatives of the basis functions at
      // local coordinates (r,s,t).

      double f_r = basis0_r*x0
                   + basis1_r*x1
                   + basis2_r*x2
                   + basis3_r*x3
                   + basis4_r*x4
                   + basis5_r*x5
                   + basis6_r*x6
                   + basis7_r*x7;

      f_r *= 0.125;

      double g_r = basis0_r*y0
                   + basis1_r*y1
                   + basis2_r*y2
                   + basis3_r*y3
                   + basis4_r*y4
                   + basis5_r*y5
                   + basis6_r*y6
                   + basis7_r*y7;

      g_r *= 0.125;

      double h_r = basis0_r*z0
                   + basis1_r*z1
                   + basis2_r*z2
                   + basis3_r*z3
                   + basis4_r*z4
                   + basis5_r*z5
                   + basis6_r*z6
                   + basis7_r*z7;

      h_r *= 0.125;

      double f_s = basis0_s*x0
                   + basis1_s*x1
                   + basis2_s*x2
                   + basis3_s*x3
                   + basis4_s*x4
                   + basis5_s*x5
                   + basis6_s*x6
                   + basis7_s*x7;

      f_s *= 0.125;

      double g_s = basis0_s*y0
                   + basis1_s*y1
                   + basis2_s*y2
                   + basis3_s*y3
                   + basis4_s*y4
                   + basis5_s*y5
                   + basis6_s*y6
                   + basis7_s*y7;

      g_s *= 0.125;

      double h_s = basis0_s*z0
                   + basis1_s*z1
                   + basis2_s*z2
                   + basis3_s*z3
                   + basis4_s*z4
                   + basis5_s*z5
                   + basis6_s*z6
                   + basis7_s*z7;

      h_s *= 0.125;

      double f_t = basis0_t*x0
                   + basis1_t*x1
                   + basis2_t*x2
                   + basis3_t*x3
                   + basis4_t*x4
                   + basis5_t*x5
                   + basis6_t*x6
                   + basis7_t*x7;

      f_t *= 0.125;

      double g_t = basis0_t*y0
                   + basis1_t*y1
                   + basis2_t*y2
                   + basis3_t*y3
                   + basis4_t*y4
                   + basis5_t*y5
                   + basis6_t*y6
                   + basis7_t*y7;

      g_t *= 0.125;

      double h_t = basis0_t*z0
                   + basis1_t*z1
                   + basis2_t*z2
                   + basis3_t*z3
                   + basis4_t*z4
                   + basis5_t*z5
                   + basis6_t*z6
                   + basis7_t*z7;

      h_t *= 0.125;

      ////////////////////////////////////////////////////////////////////////

      double det = -(  f_r*(g_t*h_s - g_s*h_t)
                       + g_r*(f_s*h_t - f_t*h_s)
                       + h_r*(f_t*g_s - f_s*g_t) );

      double rnew = f*(g_t*h_s - g_s*h_t)
                    + g*(f_s*h_t - f_t*h_s)
                    + h*(f_t*g_s - f_s*g_t);

      rnew = rnew/det + r;

      double snew = f*(g_r*h_t - g_t*h_r)
                    + g*(f_t*h_r - f_r*h_t)
                    + h*(f_r*g_t - f_t*g_r);

      snew = snew/det + s;

      double tnew = f*(g_s*h_r - g_r*h_s)
                    + g*(f_r*h_s - f_s*h_r)
                    + h*(f_s*g_r - f_r*g_s);

      tnew = tnew/det + t;

      if((ipass > 0) || ldiagnostic_output)
      {
        cout << "cur: "
        << setprecision(14) << setw(20) << r
        << setprecision(14) << setw(20) << s
        << setprecision(14) << setw(20) << t
        << endl;
        cout << "new: "
        << setprecision(14) << setw(20) << rnew
        << setprecision(14) << setw(20) << snew
        << setprecision(14) << setw(20) << tnew
        << endl;

        cout << "TOLERANCE = " << TOLERANCE << endl;

        cout << "r - rnew = "
        << setprecision(14) << setw(20) << r - rnew
        << endl;
        cout << "s - snew = "
        << setprecision(14) << setw(20) << s - snew
        << endl;
        cout << "t - tnew = "
        << setprecision(14) << setw(20) << t - tnew
        << endl;

        cout << endl;
      }

      // Check for convergence.

      if(is_close_enough(r, rnew) &&
          is_close_enough(s, snew) &&
          is_close_enough(t, tnew))
      {
        // We've converged.

        break;
      }


      // Update the values and get the next iterate.

      r = rnew;
      s = snew;
      t = tnew;

    }

    if(ipass > 0)
    {
      // Inversion failed and we've already made the diagnostic output pass.
      // Post error message and exit.

      post_fatal_error_message("inversion algorithm failed to converge");
    }

    if(itr_ct < ITR_UB)
    {
      // Inversion succeeded.
      // Assign the return values to the solutions of the equations.

      xlocal_coords[0] = r;
      xlocal_coords[1] = s;
      xlocal_coords[2] = t;

      // Don't make a second pass.

      break;
    }

  } // end for(ipass...)

  ////////////////////////////////////////////////////////////////////////

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::trilinear_3d*
fiber_bundle::trilinear_3d::
clone() const
{
  trilinear_3d* result;

  // Preconditions:

  // Body:

  result = new trilinear_3d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}

///
fiber_bundle::trilinear_3d&
fiber_bundle::trilinear_3d::
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
fiber_bundle::trilinear_3d&
fiber_bundle::trilinear_3d::
operator=(const trilinear_3d& xother)
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
fiber_bundle::trilinear_3d::
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
fiber_bundle::trilinear_3d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const trilinear_3d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================


