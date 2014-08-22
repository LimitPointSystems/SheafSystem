
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

// Implementation for class constant_fcn_space

#include "ComLimitPoint/fiber_bundle/constant_fcn_space.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "ComLimitPoint/sheaf/error_message.h"
#include "std_limits.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// CONSTANT_FCN_SPACE FACET
// ===========================================================

///
fiber_bundle::constant_fcn_space::
constant_fcn_space()
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::constant_fcn_space::
constant_fcn_space(const constant_fcn_space& xother)
{
  // Preconditions:

  // Body:

  _basis_values = _basis_value_buffer;

  // Postconditions:

  ensure(invariant());

  return;
}



// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
int
fiber_bundle::constant_fcn_space::
dl() const
{
  int result;

  // Preconditions:


  // Body:

  result = DL;

  // Postconditions:

  ensure(result == 1);

  // Exit:

  return result;
}

void
fiber_bundle::constant_fcn_space::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());

  // Body:

  // Basis is 1, independent of the local coordinate.

  _basis_values[0] = 1.0;

  // Postconditions:

  ensure(invariant());
}

///
void
fiber_bundle::constant_fcn_space::
basis_derivs_at_coord(const dof_type xlocal_coords[],
                      size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:

  int ldb = db();

  if(ldb == 0)
  {
    /// @hack For point, db = 0 and there really aren't any derivatives,
    /// but we don't gaurd against that exceptional case, so
    /// just set db = 1 here; see also constant_point.h

    ldb = 1;
  }  

  int lct = ldb*dl();

  for(int i=0; i< lct; i++)
  {
    _basis_deriv_values[i] = 0.0;
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
void
fiber_bundle::constant_fcn_space::
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
  require(xcoord_dofs_ub >= 0);
  require(xintegrands != 0);
  require(xintegrands_ub >= 0);
  require(xresult_integrals != 0);
  require(xresult_integrals_ub > 0);

  // Body:

  value_type lvolume = volume(xcoord_dofs, xcoord_dofs_ub, xdf);
  
  for(size_type i=0; i<xintegrands_ub; ++i)
  {
    xresult_integrals[i] = xintegrands[i]*lvolume;
  }
  
  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::constant_fcn_space::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  int ldb = db();
  for(size_type i=0; i<ldb; ++i)
  {
    xresult[i] = 0.0;
  }

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
fiber_bundle::constant_fcn_space::
dxi_local(size_type xlocal_coord_index,
          const dof_type xsource_dofs[],
          size_type xsource_dofs_ub,
          dof_type xresult_dofs[],
          size_type xresult_dofs_ub) const
{
  // Preconditions:

  require(xlocal_coord_index < db());
  require(xsource_dofs != 0);
  require(xsource_dofs_ub >= dl());
  require((xsource_dofs_ub % dl()) == 0);
  require(xresult_dofs != 0);
  require(xresult_dofs_ub >= xsource_dofs_ub);

  // Body:

  // The 1st derivative is 0.

  for(size_type l=0; l<xsource_dofs_ub; ++l)
  {
    xresult_dofs[l] = 0.0;
  }

  // Postconditions:

  // Exit:

  return;
}

///
void
fiber_bundle::constant_fcn_space::
jacobian(const dof_type xcoord_dofs[],
         size_type xcoord_dofs_ub,
         size_type xdf,
         const dof_type xlocal_coords[],
         size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(jacobian_values() != 0);

  // Body:

  int ldj = xdf*db();
  for(int i=0; i<ldj; ++i)
  {
    _jacobian_values[i] = 0.0;
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::constant_fcn_space::value_type
fiber_bundle::constant_fcn_space::
jacobian_determinant(const dof_type xcoord_dofs[],
                     size_type xcoord_dofs_ub,
                     size_type xdf,
                     const coord_type xlocal_coords[],
                     size_type xlocal_coords_ub)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(jacobian_values() != 0);

  // Body:

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

// ===========================================================
// DOMAIN FACET
// ===========================================================

// ===========================================================
// EVALUATION FACET
// ===========================================================

///
void
fiber_bundle::constant_fcn_space::
value_at_coord(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xlocal_coords[],
               size_type xlocal_coords_ub,
               dof_type xresult[],
               size_type xresult_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= dl()*xresult_ub);
  require(unexecutable(xdofs must be interleaved));
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());
  require(xresult != 0);
  require(xresult_ub > 0);
  require(basis_values() != 0);


  // Body:

  for(size_type i=0; i<xresult_ub; ++i)
  {
    xresult[i] = xdofs[i];
  }

  // Postconditions:

  ensure(invariant());

}

///
void
fiber_bundle::constant_fcn_space::
coord_at_value(const dof_type xdofs[],
               size_type xdofs_ub,
               const dof_type xglobal_coords[],
               size_type xglobal_coord_ub,
               dof_type xlocal_coords[],
               size_type xlocal_coords_ub) const
{
  // Preconditions:

  require(xdofs != 0);
  require(xdofs_ub >= dl()*db());
  require(xglobal_coords != 0);
  require(xglobal_coord_ub >= db());
  require(xlocal_coords != 0);
  require(xlocal_coords_ub >= db());

  // Body:


  // The inverse of the constant function is not unique;
  // define it to be the center of the evaluator.

  center(xlocal_coords, xlocal_coords_ub);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::constant_fcn_space*
fiber_bundle::constant_fcn_space::
clone() const
{
  constant_fcn_space* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  //ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}


///
fiber_bundle::constant_fcn_space&
fiber_bundle::constant_fcn_space::
operator=(const section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fiber_bundle::constant_fcn_space&
fiber_bundle::constant_fcn_space::
operator=(const constant_fcn_space& xother)
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
fiber_bundle::constant_fcn_space::
~constant_fcn_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


///
bool
fiber_bundle::constant_fcn_space::
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
fiber_bundle::constant_fcn_space::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const constant_fcn_space*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// PRIVATE MEMBERS
// ===========================================================

