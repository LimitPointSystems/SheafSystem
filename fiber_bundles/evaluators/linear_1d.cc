
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

// Implementation for class linear_1d

#include "SheafSystem/linear_1d.h"
#include "SheafSystem/assert_contract.h"
#include "SheafSystem/std_limits.h"
#include "SheafSystem/std_cmath.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// LINEAR_1D FACET
// ===========================================================

///
fiber_bundle::linear_1d::
linear_1d()
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
fiber_bundle::linear_1d::
linear_1d(const linear_1d& xother)
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
fiber_bundle::linear_1d::
~linear_1d()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

#ifndef DOXYGEN_SKIP_UNKNOWN

///
double
fiber_bundle::linear_1d::
inverse_jacobian(const double xjacobian[1],
                 double xinverse_jacobian[1])
{
  double j00 = xjacobian[0];

  // Calculate the determinant of the jacobian
  // (also return it).

  double determinant = j00;

  xinverse_jacobian[0] =  1.0 / determinant;

  // Return the determinant also.

  return determinant;
}

#endif // ifndef DOXYGEN_SKIP_UNKNOWN

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::linear_1d::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 2);

  // Exit:

  return result;
}

void
fiber_bundle::linear_1d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions at the local coordinate.

  _basis_values[0] = 0.5*(1.0 - xlocal_coord[0]);
  _basis_values[1] = 0.5*(1.0 + xlocal_coord[0]);

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::linear_1d::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  //require(xlocal_coords != 0);
  //require(xlocal_coords_ub >= db());

  // Body:

  // Evaluate the derivatives of the interpolation functions.
  // The derivatives are interleaved (N,r[0], N,s[0], N,r[1], N,s[1], ...).

  // Note that we do not use the local coordinates here because the
  // derivatives are constant.

  // Derivative with respect to r.

  _basis_deriv_value_buffer[0] = -0.5;
  _basis_deriv_value_buffer[1] =  0.5;

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
fiber_bundle::linear_1d::
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

  // Here the "jacobian determinant" is the of same as the jacobian;

  value_type result = jvalues[0];

  return result;
}

///
fiber_bundle::section_evaluator::value_type
fiber_bundle::linear_1d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  ///@todo Fix.

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 1 || xdf == 2 || xdf == 3);

  // Body:

  // Here "volume" is actually the length.
  // We assume that the cross sectional area is unit size.

  // Sum the squares for the coordinate component differences.

  ///@issue For xdf == 1 we can just take the absolute value
  ///         of x1-x0 (no need to take the sqrt of the product).

  double sum = 0.0;
  int index = 0;
  for(int i=0; i<xdf; ++i)
  {
    // The coordinate dofs are interlaced (x0, y0, z0, x1,...).

    double c0 = xcoord_dofs[index];
    double c1 = xcoord_dofs[index+xdf];
    index++;
    double c10 = c1 - c0;
    sum += c10*c10;
  }

  // Length is the square root of sum.

  value_type result = sqrt(sum);

  // Postconditions:

  ensure(invariant());
  ensure(result >= 0.0);

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_1d::
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

  value_type length = volume(xcoord_dofs, xcoord_dofs_ub, xdf);
  value_type half_length = 0.5*length;

  int index = 0;
  for(int i=0; i<xresult_integrals_ub; ++i)
  {
    dof_type fn = 0.0;
    const dof_type* integrands_n = &xintegrands[i*2];

    for(int k=0; k<2; ++k)
    {
      fn += integrands_n[k];
    }

    xresult_integrals[i] = fn*half_length;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_1d::
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

  // In 1d the integrations can be done exactly.

  value_type length = volume(xcoord_dofs, xcoord_dofs_ub, xdf);
  value_type half_length = 0.5*length;
  value_type nodal_value = xintegrand * half_length;
  xresult_integrals[0] = nodal_value;
  xresult_integrals[1] = nodal_value;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_1d::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= 1);

  // Body:

  // Local coordinates of the gauss points.

  static const double d = 1.0 / sqrt(3.0);
  static const coord_type gauss_coords[2] =
    {
      -d, d
    };

  xresult[0] = gauss_coords[xindex];

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
fiber_bundle::linear_1d::
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

  // The 1st derivative is constant for linear 1d.

  dof_type derivative = 0.5 * (xsource_dofs[1] - xsource_dofs[0]);

  xresult_dofs[0] = derivative;
  xresult_dofs[1] = derivative;

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::linear_1d::
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
  require(xdf == 1 || xdf == 2 || xdf == 3);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 1);
  require(jacobian_values() != 0);

  // Body:

  int index = 0;
  for(int i=0; i<xdf; ++i)
  {
    // The coordinate dofs are interlaced (x0, y0, z0, x1,...).

    double c0 = xcoord_dofs[index];
    double c1 = xcoord_dofs[index+xdf];
    index++;
    _jacobian_values[i] = 0.5*(c1-c0);
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
fiber_bundle::linear_1d::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 1;

  // Postconditions:

  ensure(result == 1);

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_1d::
local_coordinates(pod_index_type xindex,
                  coord_type xresult[],
                  size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[2] =
    {
      -1.0, 1.0
    };

  xresult[0] = lcoords[xindex];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::linear_1d::
in_standard_domain(const dof_type xlocal_coords[],
                   size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 1);

  // Body:

  dof_type u = xlocal_coords[0];

  // "Extend" the bounds by the dof type epsilon (attempting
  // to ensure that the boundary is included in the domain).

  dof_type one = 1.0 + 1000.0*numeric_limits<dof_type>::epsilon();

  bool result = (u >= -one) && (u <= one);

  // Postconditions:

  // Exit:

  return result;

}

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::linear_1d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 2);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 1);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 1);

  // Body:

  //cout << "linear_1d::coord_at_value()" << endl;

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[1];

  dof_type x_global = xglobal_coords[0];

  double length = x1 - x0;

  xlocal_coords[0] = (2.0*x_global - (x0 + x1)) / length;

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
fiber_bundle::linear_1d*
fiber_bundle::linear_1d::
clone() const
{
  linear_1d* result;

  // Preconditions:

  // Body:

  result = new linear_1d();

  // Postconditions:

  ensure(result != 0);
  //ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}


///
fiber_bundle::linear_1d&
fiber_bundle::linear_1d::
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
fiber_bundle::linear_1d&
fiber_bundle::linear_1d::
operator=(const linear_1d& xother)
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
fiber_bundle::linear_1d::
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
fiber_bundle::linear_1d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const linear_1d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

