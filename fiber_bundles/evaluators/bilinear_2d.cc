//
// Copyright (c) 2014 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Implementation for class bilinear_2d

#include "bilinear_2d.h"
#include "assert_contract.h"
#include "std_cfloat.h"
#include "std_cmath.h"
#include "std_limits.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// BILINEAR_2D FACET
// ===========================================================

///
fiber_bundle::bilinear_2d::
bilinear_2d()
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
fiber_bundle::bilinear_2d::
bilinear_2d(const bilinear_2d& xother)
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
fiber_bundle::bilinear_2d::
~bilinear_2d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

///
double
fiber_bundle::bilinear_2d::
inverse_jacobian(const double xjacobian[2][2],
                 double xinverse_jacobian[2][2])
{
  double j00 = xjacobian[0][0];
  double j01 = xjacobian[0][1];
  double j10 = xjacobian[1][0];
  double j11 = xjacobian[1][1];

  // Calculate the determinant of the jacobian
  // (also return it).

  double determinant = j00*j11 - j01*j10;

  xinverse_jacobian[0][0] =  j11 / determinant;
  xinverse_jacobian[0][1] = -j01 / determinant;
  xinverse_jacobian[1][0] = -j10 / determinant;
  xinverse_jacobian[1][1] =  j00 / determinant;

  // Return the determinant also.

  return determinant;
}

///
double
fiber_bundle::bilinear_2d::
solve_quadratic(double xcoefficients[])
{
  double u = 0.0;

  int num_roots = solve_quadratic(xcoefficients, xcoefficients);

  if(num_roots > 0)
  {
    ///@issue Use EPISILON below.

    if(num_roots == 2)
    {

      u = (fabs(xcoefficients[0]) <= (1.0 + DBL_EPSILON))
          ? xcoefficients[0] : xcoefficients[1];
    }

    else
    {
      // Only 1 root (num_roots == 1).

      u = xcoefficients[0];
    }

  }

  return u;
}

///
int
fiber_bundle::bilinear_2d::
solve_quadratic(double xcoefficients[], double xresult[])
{
  double a = xcoefficients[0];
  double b = xcoefficients[1];
  double c = xcoefficients[2];

  int num_roots = 0;

  if(a == 0.0)
  {
    // The quadratic parabola has degenerated to a line.

    if(b == 0.0)
    {
      // The line has degenerated to a constant.

      return -1;
    }

    xresult[num_roots++] = -c/b;

  }
  else
  {
    // From Numerical Recipes, 5.6, Quadratic and Cubic Equations.

    double d = b*b - 4.0*a* c;

    if(d < 0.0)
    {
      // If d < 0.0, then there are no roots.

      return 0;
    }

    d = sqrt(d);

    // For accuracy(?), calculate one root using:
    //     (-b +/- d) / 2a
    // and the other using:
    //     2c / (-b +/- d)

    // Choose the sign of the +/- so that b+d gets larger in magnitude.

    if(b < 0.0)
    {
      d = -d;
    }

    double q = (b + d)/(-2.0);

    // Already tested for a==0 above, so no divide by zero problem here.

    xresult[num_roots++] = q/a;

    if(q != 0.0)
    {
      xresult[num_roots++] = c/q;
    }
  }

  return num_roots;
}

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::bilinear_2d::
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
fiber_bundle::bilinear_2d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  //cout << "bilinear_2d::basis_at_coord()" << endl;

  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions.

  dof_type r = xlocal_coord[0];
  dof_type s = xlocal_coord[1];

  _basis_values[0] = 0.25*(1.0 - r)*(1.0 - s);
  _basis_values[1] = 0.25*(1.0 + r)*(1.0 - s);
  _basis_values[2] = 0.25*(1.0 + r)*(1.0 + s);
  _basis_values[3] = 0.25*(1.0 - r)*(1.0 + s);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::bilinear_2d::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  // Evaluate the derivatives of the interpolation functions.
  // The derivatives are interleaved (N,r[0], N,s[0], N,r[1], N,s[1], ...).

  double r = xlocal_coords[0];
  double s = xlocal_coords[1];

  double quartr = 0.25 * r;
  double quarts = 0.25 * s;

  double rp = 0.25 + quartr;
  double rm = 0.25 - quartr;
  double sp = 0.25 + quarts;
  double sm = 0.25 - quarts;

  // Derivative with respect to r.

  _basis_deriv_value_buffer[0] = -sm;
  _basis_deriv_value_buffer[2] =  sm;
  _basis_deriv_value_buffer[4] =  sp;
  _basis_deriv_value_buffer[6] = -sp;

  // Derivative with respect to s.

  _basis_deriv_value_buffer[1] = -rm;
  _basis_deriv_value_buffer[3] = -rp;
  _basis_deriv_value_buffer[5] =  rp;
  _basis_deriv_value_buffer[7] =  rm;

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
fiber_bundle::bilinear_2d::
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

  // Form the metric tensor g = [J]'*[J] (' == transpose).

  value_type g00 = 0.0;
  value_type g01 = 0.0;
  value_type g11 = 0.0;

  // Jacobian matrix has dimensions xdf x 2.

  // Just do the matrix multiplication in place (for efficiency).

  int index = 0;
  for(int i=0; i<xdf; ++i)
  {
    value_type Ji0 = jvalues[index++];
    value_type Ji1 = jvalues[index++];

    g00 += Ji0*Ji0;
    g01 += Ji0*Ji1;
    g11 += Ji1*Ji1;
  }

  // Metric tensor is symmetric, so g10 = g01.

  value_type g10 = g01;

  // Evaulate the determinant of the metrix tensor

  value_type g_det = g00*g11 - g01*g10;

  // The "jacobian determinant" is the square root of g_det;

  value_type result = sqrt(fabs(g_det));

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::bilinear_2d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 3);

  // Body:

  /// @todo Add method number_of_gauss_points().

  static int NUM_GAUSS_POINTS = 4;

  value_type result = 0.0;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[2];
    gauss_point(n, local_coords, 2);

    value_type det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                          local_coords, 2);

    // Just sum up the integrand values since the gauss weights are all 1.0
    // for 2x2 quadrature.

    result += det;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
void
fiber_bundle::bilinear_2d::
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

  ///@issue Interpreting the number of integrands per node
  ///         as xintegrands_ub/xresult_integrals_ub.

  int integrands_per_node = xintegrands_ub/xresult_integrals_ub;

  // Initialize the integrals.

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = 0.0;
  }

  /// @todo Add method number_of_gauss_points().

  static int NUM_GAUSS_POINTS = 4;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[2];
    gauss_point(n, local_coords, 2);

    double det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                      local_coords, 2);

    //cout << " det = " << det << endl;

    basis_at_coord(local_coords, 2);
    const value_type* basis = basis_values();

    for(int i=0; i<xresult_integrals_ub; ++i)
    {
      dof_type fn = 0.0;
      //const dof_type* integrands_n = xintegrands+(i*4);
      const dof_type* integrands_n = xintegrands+(i*integrands_per_node);

      for(int k=0; k<4; ++k)
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
fiber_bundle::bilinear_2d::
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

  /// @todo Add method number_of_gauss_points().

  static int NUM_GAUSS_POINTS = 4;

  for(int n=0; n<NUM_GAUSS_POINTS; ++n)
  {
    coord_type local_coords[2];
    gauss_point(n, local_coords, 2);

    double det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
                                      local_coords, 2);

    //cout << " det = " << det << endl;

    basis_at_coord(local_coords, 2);
    const value_type* basis = basis_values();

    for(int i=0; i<4; ++i)
    {
      xresult_integrals[i] += basis[i] * xintegrand * det;
    }
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
void
fiber_bundle::bilinear_2d::
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
  static const coord_type gauss_coords[4][2] =
    {
      {
        -d, -d
      }
      , {d, -d}, {d, d}, {-d, d}
    };

  xresult[0] = gauss_coords[xindex][0];
  xresult[1] = gauss_coords[xindex][1];

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
fiber_bundle::bilinear_2d::
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
    dof_type d_minus = 0.5 * (xsource_dofs[1] - xsource_dofs[0]);
    dof_type d_plus =  0.5 * (xsource_dofs[2] - xsource_dofs[3]);

    xresult_dofs[0] = d_minus;
    xresult_dofs[1] = d_minus;

    xresult_dofs[2] = d_plus;
    xresult_dofs[3] = d_plus;
  }
  else
  {
    dof_type d_minus = 0.5 * (xsource_dofs[3] - xsource_dofs[0]);
    dof_type d_plus =  0.5 * (xsource_dofs[2] - xsource_dofs[1]);

    xresult_dofs[0] = d_minus;
    xresult_dofs[3] = d_minus;

    xresult_dofs[1] = d_plus;
    xresult_dofs[2] = d_plus;
  }

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::bilinear_2d::
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
  bilinear_2d* cthis = const_cast<bilinear_2d*>(this);
  require(cthis->jacobian_values() != 0);

  // Body:

  // Get the derivatives of the basis functions at the
  // specified local coordinates.

  int local_coords_ct = 2;

  basis_derivs_at_coord(xlocal_coords, local_coords_ct);
  const value_type* derivs = basis_deriv_values();

  //   // Loop over the rows of the jacobian matrix
  //   // (rows correspond to the derivatives w.r.t. the local coordinates.)

  ///   ///@issue This can probably be made more efficient by reordering
  ///   ///         the loops.

  //   for(int i=0; i<local_coords_ct; ++i)
  //   {
  //     // Loop over the columns of the jacobian matrix
  //     // (columns correspond to the global coordinates.)

  //     for(int j=0; j<xdf; ++j)
  //     {
  //    // Loop over the nodes and sum the product of the derivatives and
  //    // the global nodal coordinates.

  //    value_type sum = 0.0;

  //       for(int k=0; k<dl(); ++k)
  //       {
  //         // Derivatives and coordinate dofs are "interleaved".

  //   value_type deriv = derivs[local_coords_ct*k+i];
  //         value_type coord = xcoord_dofs[xdf*k+j];

  //         sum += deriv*coord;

  //         cout << "++++++++++++++++++++++++++++++++++" << endl;
  //   cout << "    deriv = " << deriv << endl;
  //   cout << "    coord = " << coord << endl;
  //   cout << "    sum = " << sum << endl;
  //         cout << "++++++++++++++++++++++++++++++++++" << endl;
  //    }

  //       // Store the sum in the appropriate location in the Jacobian matrix.

  //       _jacobian_values[xdf*i+j] = sum;
  //     }
  //   }

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

  //   cout << "++++++++++++++++++++++++++++++++++" << endl;
  //   for(int i=0; i<6; ++i)
  //     cout <<  _jacobian_values[i] << endl;
  //   cout << "++++++++++++++++++++++++++++++++++" << endl;

  //   double xr = 0.0;
  //   double xs = 0.0;
  //   double yr = 0.0;
  //   double ys = 0.0;

  //   for(int i = 0; i<dl(); ++i)
  //   {
  //  // Coords are interleaved (x0, y0, x1, y1, ...)

  //  int index = xdf*i;
  //     double xi = xcoord_dofs[index];
  //     double yi = xcoord_dofs[index+1];

  //     //cout << " xi = " << xi << ", yi = " << yi << endl;

  //  // Derivatives are "interleaved".

  //     double Nri = derivs[index];
  //     double Nsi = derivs[index+1];

  //     xr += Nri * xi;
  //     xs += Nsi * xi;
  //     yr += Nri * yi;
  //     ys += Nsi * yi;
  //   }

  //   _jacobian_values[0] = xr; // 00
  //   _jacobian_values[1] = yr; // 01
  //   _jacobian_values[2] = xs; // 10
  //   _jacobian_values[3] = ys; // 11

  //   cout << "----------------------------------" << endl;
  //   for(int i=0; i<4; ++i)
  //     cout <<  _jacobian_values[i] << endl;
  //   cout << "----------------------------------" << endl;


  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///@todo xlocal_coords_ub, etc.

// ///
// double
// bilinear_2d::
// jacobian(const dof_type xcoord_dofs[],
//          size_type xcoord_dofs_ub,
//          const coord_type xlocal_coords[2],
//          double xjacobian[2][2])
// {
//   // This method can be called with xjacobian == NULL
//   // which allows only the determinant to be computed
//   // and returned.

//   basis_derivs_at_coord(xlocal_coords, 2);
//   const value_type* derivs = basis_deriv_values();

//   double xr = 0.0;
//   double xs = 0.0;
//   double yr = 0.0;
//   double ys = 0.0;

//   for(int i = 0; i<dl(); ++i)
//   {
//  // Coords are interleaved (x0, y0, x1, y1, ...)

//  int index = db()*i;
//     double xi = xcoord_dofs[index];
//     double yi = xcoord_dofs[index+1];

//     //cout << " xi = " << xi << ", yi = " << yi << endl;

//  // Derivatives are "interleaved".

//     double Nri = derivs[index];
//     double Nsi = derivs[index+1];

//     xr += Nri * xi;
//     xs += Nsi * xi;
//     yr += Nri * yi;
//     ys += Nsi * yi;
//   }

//   if(xjacobian != NULL)
//   {
//     xjacobian[0][0] = xr;
//     xjacobian[0][1] = yr;
//     xjacobian[1][0] = xs;
//     xjacobian[1][1] = ys;
//   }

//   // Calculate the determinant of the jacobian
//   // and return it.

//   double determinant = xr * ys - yr * xs;

//   return determinant;
// }

// ===========================================================
// DOMAIN FACET
// ===========================================================

///
int
fiber_bundle::bilinear_2d::
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
fiber_bundle::bilinear_2d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[4][2] =
    {
      {
        -1.0, -1.0
      }
      , {1.0, -1.0}, {1.0, 1.0}, {-1.0, 1.0}
    };

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
void
fiber_bundle::bilinear_2d::
edge_center(pod_index_type xi, coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require(xresult != 0);
  require(xresult_ub >= db());

  // Body:

  // Edge indexing: edges are numbered 0, 1, 2, 3 going CCW from vertex 0.
  //
  //                edge 2
  //              3****#****2
  //              *         *
  //              *         *
  //      edge 3  #         # edge 1
  //              *         *
  //              *         *
  //              0****#****1
  //                edge 0
  //

  static const coord_type lcoords[4][2] =
    {
      {
        0.0, -1.0
      },
      { 1.0, 0.0 },
      { 0.0, 1.0 },
      { -1.0, 0.0 },
    };

  xresult[0] = lcoords[xi][0];
  xresult[1] = lcoords[xi][1];

  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::bilinear_2d::
edge_center(pod_index_type xi, block<coord_type>& xresult) const
{
  // Preconditions:

  require(precondition_of(center(xresult.base(), xresult.ub())));

  // Body:

  edge_center(xi, xresult.base(), xresult.ub());
  xresult.set_ct(db());

  // Postconditions:

  ensure(postcondition_of(edge_center(xresult.base(), xresult.ub())));
  ensure(xresult.ct() == db());

  // Exit:

  return;
}

///
bool
fiber_bundle::bilinear_2d::
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

///
void
fiber_bundle::bilinear_2d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 8);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 2);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);
  require(unexecutable(xdofs must be interleaved));

  // Body:

  //cout << "bilinear_2d::coord_at_value()" << endl;

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[2];
  dof_type x2 = xdofs[4];
  dof_type x3 = xdofs[6];

  dof_type y0 = xdofs[1];
  dof_type y1 = xdofs[3];
  dof_type y2 = xdofs[5];
  dof_type y3 = xdofs[7];

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];

  double x20 = x2 - x0;
  double y20 = y2 - y0;
  double x13 = x1 - x3;
  double y13 = y1 - y3;

  double a0 = 4*x_global - (x0+x1+x2+x3);
  double a1 = x20 + x13;
  double a2 = x20 - x13;
  double a3 = x0 - x1 + x2 - x3;

  double b0 = 4*y_global - (y0+y1+y2+y3);
  double b1 = y20 + y13;
  double b2 = y20 - y13;
  double b3 = y0 - y1 + y2 - y3;

  double coefficients[3];

  // Solve for u.

  bilinear_2d* cthis = const_cast<bilinear_2d*>(this);

  coefficients[0] = a1*b3 - b1*a3;
  coefficients[1] = a1*b2 - b1*a2 + b0*a3 - a0*b3;
  coefficients[2] = b0*a2 - a0*b2;
  xlocal_coords[0] = cthis->solve_quadratic(coefficients);

  // Solve for v.

  coefficients[0] = a3*b2 - a2*b3;
  coefficients[1] = a0*b3 - a3*b0 + a1*b2 - a2*b1;
  coefficients[2] = a0*b1 - a1*b0;
  xlocal_coords[1] = cthis->solve_quadratic(coefficients);

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::bilinear_2d*
fiber_bundle::bilinear_2d::
clone() const
{
  bilinear_2d* result;

  // Preconditions:

  // Body:

  result = new bilinear_2d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::bilinear_2d&
fiber_bundle::bilinear_2d::
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
fiber_bundle::bilinear_2d&
fiber_bundle::bilinear_2d::
operator=(const bilinear_2d& xother)
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
fiber_bundle::bilinear_2d::
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
fiber_bundle::bilinear_2d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const bilinear_2d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================



