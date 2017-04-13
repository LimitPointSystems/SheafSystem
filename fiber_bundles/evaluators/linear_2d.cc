
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

// Implementation for class linear_2d

#include "SheafSystem/linear_2d.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"
#include "SheafSystem/std_cmath.h"
#include "SheafSystem/std_iostream.h"
#include "SheafSystem/std_limits.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// LINEAR_2D FACET
// ===========================================================

///
fiber_bundle::linear_2d::
linear_2d()
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
fiber_bundle::linear_2d::
linear_2d(const linear_2d& xother)
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
fiber_bundle::linear_2d::
~linear_2d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  return;
}

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::linear_2d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 3);

  // Exit:

  return result;
}

void
fiber_bundle::linear_2d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions.

  _basis_values[0] = xlocal_coord[0];
  _basis_values[1] = xlocal_coord[1];
  _basis_values[2] = 1.0 - (_basis_values[0] + _basis_values[1]);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
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
  // given barycentric coordinates L0, L1, L2 (L0+L1+L2=1) where we use
  // the the convention that L2 = 1-L0-L1.

  // The basis fumctions are:
  //   N0(r, s, t) = r;
  //   N1(r, s, t) = s;
  //   N2(r, s, t) = 1-r-s;

  // Note that the basis functions are linear in r,s.
  // Therefore the derivatives are constant and the
  // local coordinates are not needed in their evaluation.

  // Derivatives with respect to r.

  _basis_deriv_value_buffer[ 0] =  1.0;
  _basis_deriv_value_buffer[ 2] =  0.0;
  _basis_deriv_value_buffer[ 4] = -1.0;

  // Derivatives with respect to s.

  _basis_deriv_value_buffer[ 1] =  0.0;
  _basis_deriv_value_buffer[ 3] =  1.0;
  _basis_deriv_value_buffer[ 5] = -1.0;

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
fiber_bundle::linear_2d::
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

  value_type det = g00*g11 - g01*g10;

  // The "jacobian determinant" is the square root of det;

  value_type result = sqrt(fabs(det));

  //===========================================================================

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::linear_2d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  ///@todo Fix!

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());

  // Body:

  // Coordinates dofs are interleaved (x0, y0, x1, y1, ...).

  // Here we use the following equation for xdf == 2:
  //
  //  2*Volume = | 1 x0 y0 |
  //             | 1 x1 y1 |
  //             | 1 x2 y2 |

  // Note that the "volume" is actually the area
  // (we assume a unit thickness).

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // Testing:

  //   coord_type local_coords[3] = {1.0/3.0, 1.0/3.0, 1.0/3.0};
  //   value_type det = jacobian_determinant(xcoord_dofs, xcoord_dofs_ub, xdf,
  //                                         local_coords, 3);
  //   cout << "+++++++++++++ jacobian_determinant = " << det << endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  value_type result = 0.0;

  ///@issue For xdf == 2 the area is 0.5*(x1-x0)*(y2-y0)-(x2-x0)*(y1-y0));
  ///         so for efficiency we use tis equation.

  if(xdf == 2)
  {
    double x0 = xcoord_dofs[0];
    double x1 = xcoord_dofs[2];
    double x2 = xcoord_dofs[4];

    double y0 = xcoord_dofs[1];
    double y1 = xcoord_dofs[3];
    double y2 = xcoord_dofs[5];

    result = 0.5*((x1-x0)*(y2-y0)-(x2-x0)*(y1-y0));
  }
  else
  {
    double sum = 0.0;
    for(int i=0; i<xdf; ++i)
    {
      // The coordinate dofs are interlaced (x0, y0, z0, x1,...).

      int index = i;
      double a0 = xcoord_dofs[index];
      double a1 = xcoord_dofs[index+xdf];
      double a2 = xcoord_dofs[index+2*xdf];

      double a10 = a1 - a0;
      double a20 = a2 - a0;

      index++;
      if(index == xdf)
        index = 0;

      double b0 = xcoord_dofs[index];
      double b1 = xcoord_dofs[index+xdf];
      double b2 = xcoord_dofs[index+2*xdf];

      double b10 = b1 - b0;
      double b20 = b2 - b0;

      double v = a10*b20 - a20*b10;

      // Sum the squares.

      sum += v*v;
    }

    // Area is one half the square root of sum.

    result = 0.5*sqrt(sum*sum);
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_2d::
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

  double area = volume(xcoord_dofs, xcoord_dofs_ub, xdf);
  double third_area = area/3.0;

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    dof_type fn = 0.0;
    const dof_type* integrands_n = &xintegrands[i*3];

    for(int k=0; k<3; ++k)
    {
      fn += integrands_n[k];
    }

    xresult_integrals[i] = fn*third_area;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
integrate(const dof_type xcoord_dofs[],
          size_type xcoord_dofs_ub,
          size_type xdf,
          const dof_type xintegrands[],
          value_type xresult_integrals[],
          size_type xresult_integrals_ub)
{
  ///@todo Get these correct.

  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xintegrands != 0);
  //require(xintegrands_ub >= dl());
  require(xresult_integrals != 0);
  require(xresult_integrals_ub > 0);

  // Body:

  double vol = volume(xcoord_dofs, xcoord_dofs_ub, xdf);
  double v3 = vol/3.0;

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = xintegrands[i]*v3;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
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

  double vol = volume(xcoord_dofs, xcoord_dofs_ub, xdf);

  value_type value = xintegrand*vol/3.0;

  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    xresult_integrals[i] = value;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  // Local coordinates of the gauss points.

  static const double d = 1.0/3.0;

  xresult[0] = d;
  xresult[1] = d;
  xresult[2] = d;

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
fiber_bundle::linear_2d::
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
fiber_bundle::linear_2d::
jacobian(const dof_type xcoord_dofs[],
         size_type xcoord_dofs_ub,
         size_type xdf,
         const dof_type xlocal_coords[],
         size_type xlocal_coords_ub)
{

  ///@issue This method is broken.
  ///@todo Fix it!

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

  // Iterate over the columns of the jacobian matrix
  // (columns correspond to the derivatives w.r.t. the local coordinates.)

  for(int i=0; i<local_coords_ct; ++i)
  {
    // Iterate over the rows of the jacobian matrix
    // (rows correspond to the global coordinates.)

    for(int j=0; j<xdf; ++j)
    {
      // Iterate over the nodes and sum the product of the derivatives and
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
fiber_bundle::linear_2d::
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
fiber_bundle::linear_2d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[3][2] =
    {
      {
        1.0, 0.0
      }
      , {0.0, 1.0}, {0.0, 0.0}
    } ;

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
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
void
fiber_bundle::linear_2d::
edge_center(pod_index_type xi, coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require(xresult != 0);
  require(xresult_ub >= db());

  // Body:

  // Edge indexing: edges are numbered 0, 1, 2 going CCW from
  // vertex 0. This numbering is consistent with the usual
  // connectivity ordering for any 2D cell, but conflicts with
  // the natural edge indexing of simplices in barycentric coordinates,
  // in which the i-th edge is oppposite the i-th vertex.
  //
  // Barycentric coordinate view: i-th edge is opposite
  // i-th vertex, i-th coordinate axis is perpendicular
  // to ith edge, 0 at i-th edge, 1 at i-th vertex.
  //
  //
  //          2
  //         * *
  // edge   *   *
  //  1    *     *
  //      *       *  edge 0
  //     *         *
  //    *           *
  //   *             *
  //  0***************1
  //        edge 2
  //
  //
  // Vector coordinate view:
  //
  //
  //         ^
  //         v
  //
  //         1
  //         * *
  //         *   *
  //   edge  *     *    edge
  //    1    *       *   0
  //         *         *
  //         *           *
  //         2*************0 -> u
  //             edge 2
  //
  //

  static const coord_type lcoords[3][2] =
    {
      {
        0.5, 0.5
      },
      { 0.0, 0.5 },
      { 0.5, 0.0 }
    };

  xresult[0] = lcoords[xi][0];
  xresult[1] = lcoords[xi][1];

  // Postconditions:


  // Exit:

  return;
}

///
void
fiber_bundle::linear_2d::
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
fiber_bundle::linear_2d::
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

  //  bool result = (u >= zero) && (u <= one) && (v >= zero) && (v <= one);
  bool result = (u >= zero) && (u <= one) && (v >= zero) && (v <= one - u);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::linear_2d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 6);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 2);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 2);

  // Body:

  // Dofs are assumed to be interleaved (x0. y0, x1, y1, x2, y2).

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[2];
  dof_type x2 = xdofs[4];

  dof_type y0 = xdofs[1];
  dof_type y1 = xdofs[3];
  dof_type y2 = xdofs[5];

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];

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

  double basis0 = (a0 + b0*x_global + c0*y_global) / area_x_2;
  double basis1 = (a1 + b1*x_global + c1*y_global) / area_x_2;
  //double basis2 = (a2 + b2*x_global + c2*y_global) / area_x_2;

  //double basis2 = 1.0 - (basis0 + basis1);

#ifdef DIAGNOSTIC_OUTPUT

  cout << "basis0 = " << basis0 << endl;
  cout << "basis1 = " << basis1 << endl;
  cout << "basis2 = " << 1.0 - (basis0 + basis1) << endl;
#endif

  // Return 2 local (area) coordinates and later generate the third
  // from the fact that they sum to 1 (ie: basis0 + basis1 + basis2 = 1).

  xlocal_coords[0] = basis0;
  xlocal_coords[1] = basis1;

  // Return non null only if the search point is inside the element
  // or on the element boundary.

  //if((basis0 >= 0.0) && (basis1 >= 0.0) && (basis2 >= 0.0))
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
fiber_bundle::linear_2d*
fiber_bundle::linear_2d::
clone() const
{
  linear_2d* result;

  // Preconditions:

  // Body:

  result = new linear_2d();

  // Postconditions:

  ensure(result != 0);
  //ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}


///
fiber_bundle::linear_2d&
fiber_bundle::linear_2d::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  /// @todo implement linear_2d::operator=(const linear_2d& xother)

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fiber_bundle::linear_2d&
fiber_bundle::linear_2d::
operator=(const linear_2d& xother)
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
fiber_bundle::linear_2d::
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
fiber_bundle::linear_2d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const linear_2d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================
