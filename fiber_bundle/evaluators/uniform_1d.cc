
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
// Implementation for class uniform_1d

#include "ComLimitPoint/fiber_bundle/uniform_1d.h"
#include "ComLimitPoint/sheaf/assert_contract.h"
#include "std_limits.h"

using namespace std;
using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// UNIFORM_1D FACET
// ===========================================================

///
fiber_bundle::uniform_1d::
uniform_1d()
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
fiber_bundle::uniform_1d::
uniform_1d(const uniform_1d& xother)
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
fiber_bundle::uniform_1d::
~uniform_1d()
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
fiber_bundle::uniform_1d::
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

///
void
fiber_bundle::uniform_1d::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // cout << "uniform_1d::basis_at_coord()" << endl;

  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_values() != 0);

  // Body:

  // Interpolate the field value at the global coordinates.

  dof_type u = xlocal_coord[0];

  _basis_values[0] = 0.5*(1.0 - u);
  _basis_values[1] = 0.5*(1.0 + u);

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::uniform_1d::
basis_derivs_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  _basis_deriv_values[0] = -0.5;
  _basis_deriv_values[1] =  0.5;

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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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


  xresult_dofs[0] = 0.5 * (xsource_dofs[1] - xsource_dofs[0]);

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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
    } ;

  xresult[0] = lcoords[xindex];

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));

  // Exit:

  return;
}

///
bool
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
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

  // cout << "uniform_1d::coord_at_value()" << endl;


  dof_type x0 = xdofs[0];
  dof_type x1 = xdofs[1];

  dof_type x_global = xglobal_coords[0];

  // Solve for u.

  double xlength = x1 - x0;

  xlocal_coords[0] = (2.0*x_global - (x0 + x1)) / xlength;

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================


///
fiber_bundle::uniform_1d*
fiber_bundle::uniform_1d::
clone() const
{
  uniform_1d* result;

  // Preconditions:

  // Body:

  result = new uniform_1d();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));
  //ensure(invariant());
  ensure(result->invariant());

  return result;
}


///
fiber_bundle::uniform_1d&
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d&
fiber_bundle::uniform_1d::
operator=(const uniform_1d& xother)
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
fiber_bundle::uniform_1d::
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
fiber_bundle::uniform_1d::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const uniform_1d*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================


