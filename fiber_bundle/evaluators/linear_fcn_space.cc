
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

// Implementation for class linear_fcn_space

#include "ComLimitPoint/fiber_bundle/linear_fcn_space.h"

#include "ComLimitPoint/sheaf/assert_contract.h"
#include "std_cmath.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//#define DIAGNOSTIC_OUTPUT

// ===========================================================
// LINEAR_FCN_SPACE FACET
// ===========================================================

///
fiber_bundle::linear_fcn_space::
linear_fcn_space(const linear_fcn_space& xother)
{
  // Preconditions:

  // Body:

  // Initialize _basis_values to 0 here just to
  // make precondition in basis_at_coord meaningful.
  // Will be reinitialized in descendants to point to
  // an auto allocated data member. This allows us to
  // avoid newing the basis values buffer within
  // deeply nested loops without using a virtual function.

  _basis_values = 0;

  // Postconditions:

  ensure(invariant());

  return;
}

// Destructor.
///
fiber_bundle::linear_fcn_space::
~linear_fcn_space()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

///
int
fiber_bundle::linear_fcn_space::
dl() const
{
  int result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_fcn_space::
basis_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_values() != 0);

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::linear_fcn_space::
basis_derivs_at_coord(const dof_type xlocal_coord[], size_type xlocal_coord_ub)
{
  // Preconditions:

  require(xlocal_coord != 0);
  require(xlocal_coord_ub >= db());
  require(basis_deriv_values() != 0);

  // Body:

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
const fiber_bundle::linear_fcn_space::value_type*
fiber_bundle::linear_fcn_space::
basis_values() const
{

  // Preconditions:


  // Body:

  const value_type* result = _basis_values;

  // Postconditions:


  // Exit:

  return result;
}

///
const fiber_bundle::linear_fcn_space::value_type*
fiber_bundle::linear_fcn_space::
basis_deriv_values() const
{

  // Preconditions:


  // Body:

  const value_type* result = _basis_deriv_values;

  // Postconditions:


  // Exit:

  return result;
}

///
fiber_bundle::linear_fcn_space::
linear_fcn_space()
{
  // Preconditions:

  // Body:

  // Initialize _basis_values to 0 here just to
  // make precondition in basis_at_coord meaningful.
  // Will be reinitialized in descendants to point to
  // an auto allocated data member. This allows us to
  // avoid newing the basis values buffer within
  // deeply nested loops without using a virtual function.

  _basis_values = 0;

  // Postconditions:

  ensure(invariant());

  return;
}


// ===========================================================
// EVALUATION FACET
// ===========================================================

///
sheaf::size_type
fiber_bundle::linear_fcn_space::
dof_ct() const
{
  int result;

  // Preconditions:


  // Body:

  result = dl();

  // Postconditions:

  ensure(result >= 0);

  // Exit:

  return result;
}

///
void
fiber_bundle::linear_fcn_space::
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

  int ldl = dl();

  linear_fcn_space* cthis = const_cast<linear_fcn_space*>(this);
  cthis->basis_at_coord(xlocal_coords, xlocal_coords_ub);

  for(size_type i=0; i<xresult_ub; ++i)
  {
    dof_type value = 0.0;
    size_type dof_index = i;

    for(size_type j=0; j<ldl; ++j)
    {
      value += _basis_values[j]*xdofs[dof_index];
      dof_index += xresult_ub;
    }

    xresult[i] = value;
  }

  // Postconditions:

  ensure(invariant());

}

// ===========================================================
// ANY FACET
// ===========================================================

///
fiber_bundle::linear_fcn_space*
fiber_bundle::linear_fcn_space::
clone() const
{
  linear_fcn_space* result = 0;

  // Preconditions:

  is_abstract();

  // Body:

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  return result;
}


// Assignment operator.
///
fiber_bundle::linear_fcn_space&
fiber_bundle::linear_fcn_space::
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
fiber_bundle::linear_fcn_space&
fiber_bundle::linear_fcn_space::
operator=(const linear_fcn_space& xother)
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

// Class invariant.
///
bool
fiber_bundle::linear_fcn_space::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && section_evaluator::invariant();

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

// Conformance test.
///
bool
fiber_bundle::linear_fcn_space::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const linear_fcn_space*>(xother) != 0;

  // Postconditions:

  return result;

}

