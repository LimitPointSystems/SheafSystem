//
// Copyright (c) 2013 Limit Point Systems, Inc. 

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

// Implementation for class quadratic_1d

#include "quadratic_1d.h"
#include "assert_contract.h"
#include "std_cmath.h"
#include "std_iostream.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// QUADRATIC_1D FACET
// ===========================================================

///
fiber_bundle::quadratic_1d::
quadratic_1d()
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
fiber_bundle::quadratic_1d::
quadratic_1d(const quadratic_1d& xother)
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
fiber_bundle::quadratic_1d::
~quadratic_1d()
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
fiber_bundle::quadratic_1d::
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

///
void
fiber_bundle::quadratic_1d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Evaluate the interpolation functions.

  dof_type r = xlocal_coord[0];

  _basis_values[0] = 0.5*r*(r - 1.0);
  _basis_values[1] = 1.0 - r*r;
  _basis_values[2] = 0.5*r*(r + 1.0);

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::quadratic_1d::
basis_derivs_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  dof_type r = xlocal_coord[0];

  _basis_deriv_values[0] = r - 0.5;
  _basis_deriv_values[1] = -2.0*r;
  _basis_deriv_values[2] = r + 0.5;

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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  ///@todo Fix.

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 1 || xdf == 2 || xdf == 3);

  // Body:

  ///@issue Note that this is "isoparametric"
  ///         which means that for xdf == 2 or xdf == 3 the
  ///         1d segment may not be straight.  For now we
  ///         assume that it is.

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
    double c10 = c1 - c0;
    sum += c10*c10;

    index++;
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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
dxi_local(size_type xlocal_coord_index,
          const dof_type xsource_dofs[],
          size_type xsource_dofs_ub,
          dof_type xresult_dofs[],
          size_type xresult_dofs_ub) const
{
  // Preconditions:

  require(xlocal_coord_index < db());
  require(xsource_dofs != 0);
  require(xsource_dofs_ub >= 3);
  require(xresult_dofs != 0);
  require(xresult_dofs_ub >= 3);

  // Body:

  // The first derivative is linear for quadratic 1d.

  double u0 = xsource_dofs[0];
  double u1 = xsource_dofs[1];
  double u2 = xsource_dofs[2];

  xresult_dofs[0] = -1.5*u0 + 2.0*u1 - 0.5*u2;
  xresult_dofs[1] =  0.5*(u2 - u0);
  xresult_dofs[2] =  0.5*u0 - 2.0*u1 + 1.5*u2;

  // Postconditions:

  ensure(invariant());

  return;
}

///
void
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
local_coordinates(pod_index_type xindex, coord_type xresult[], size_type xresult_ub) const
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  static const coord_type lcoords[3] =
    {
      -1.0 , 0.0, 1.0
    } ;

  xresult[0] = lcoords[xindex];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= 3);
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= 1);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= 1);

  // Body:

  cout << "quadratic_1d::coord_at_value()" << endl;

  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[1];
  dof_type x2 = xdofs[2];

  dof_type x_global = xglobal_coords[0];

  cout << "##### x0 = " << x0 << endl;
  cout << "##### x1 = " << x1 << endl;
  cout << "##### x2 = " << x2 << endl;
  cout << "##### x_global = " << x_global << endl;


  // NOTE: a is always 0 for this element (2*x1 == x0 + x2).

  double a = x0 - 2.0*x1 + x2;
  double b = x2 - x0;
  double c = 2.0*(x1 - x_global);

  cout << "#### a = " << a << endl;
  cout << "#### b = " << b << endl;
  cout << "#### c = " << c << endl;

  //double local_coord = (-b + sqrt(b*b - 4.0*a*c))/(2.0*a);

  double local_coord = -c/b;

  cout << "#### local_coord = " << local_coord << endl;

  xlocal_coords[0] = local_coord;

  // Return non null only if the search point is inside the element
  // or on the element boundary.

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
fiber_bundle::quadratic_1d*
fiber_bundle::quadratic_1d::
clone() const
{
  quadratic_1d* result;

  // Preconditions:

  // Body:

  result = new quadratic_1d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::quadratic_1d&
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d&
fiber_bundle::quadratic_1d::
operator=(const quadratic_1d& xother)
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
fiber_bundle::quadratic_1d::
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
fiber_bundle::quadratic_1d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const quadratic_1d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================
