
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

// Implementation for class uniform_2d

#include "uniform_2d.h"
#include "assert_contract.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// UNIFORM_2D FACET
// ===========================================================

///
fiber_bundle::uniform_2d::
uniform_2d()
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
fiber_bundle::uniform_2d::
uniform_2d(const uniform_2d& xother)
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
fiber_bundle::uniform_2d::
~uniform_2d()
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
fiber_bundle::uniform_2d::
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

// BILINEAR_2D INTERFACE

///
void
fiber_bundle::uniform_2d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Interpolate the field value at the global coordinates.

  dof_type u = xlocal_coord[0];
  dof_type v = xlocal_coord[1];

  _basis_values[0] = 0.25*(1.0 - u)*(1.0 - v);
  _basis_values[1] = 0.25*(1.0 + u)*(1.0 - v);
  _basis_values[2] = 0.25*(1.0 + u)*(1.0 + v);
  _basis_values[3] = 0.25*(1.0 - u)*(1.0 + v);

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::uniform_2d::
basis_derivs_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  double r = xlocal_coord[0];
  double s = xlocal_coord[1];

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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
volume(const dof_type xcoord_dofs[], size_type xcoord_dofs_ub, size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= dl()*db());
  require(xdf == 2 || xdf == 2 || xdf == 3);

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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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
        -1, -1
      }
      , {1, -1}, {1, 1}, {-1, 1}
    } ;

  xresult[0] = lcoords[xindex][0];
  xresult[1] = lcoords[xindex][1];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}


///
bool
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d::
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

  // Body:

  //cout << "uniform_2d::coord_at_value()" << endl;

  // The dofs are assumed to be interleaved (x0, y0, x1, y1, ...).

  dof_type x0 = xdofs[0];
  //dof_type x1 = xdofs[2];
  dof_type x2 = xdofs[4];
  //dof_type x3 = xdofs[6];

  dof_type y0 = xdofs[1];
  //dof_type y1 = xdofs[3];
  dof_type y2 = xdofs[5];
  //dof_type y3 = xdofs[7];

  dof_type x_global = xglobal_coords[0];
  dof_type y_global = xglobal_coords[1];

  // Solve for u.

  double xlength = x2 - x0;

  xlocal_coords[0] = (2.0*x_global - (x0 + x2)) / xlength;

  // Solve for v.

  double ylength = y2 - y0;

  xlocal_coords[1] = (2.0*y_global - (y0 + y2)) / ylength;

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::uniform_2d*
fiber_bundle::uniform_2d::
clone() const
{
  uniform_2d* result;

  // Preconditions:

  // Body:

  result = new uniform_2d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::uniform_2d&
fiber_bundle::uniform_2d::
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
fiber_bundle::uniform_2d&
fiber_bundle::uniform_2d::
operator=(const uniform_2d& xother)
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
fiber_bundle::uniform_2d::
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

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

///
bool
fiber_bundle::uniform_2d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const uniform_2d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

