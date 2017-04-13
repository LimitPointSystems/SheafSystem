
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

// Implementation for class section_evaluator

#include "SheafSystem/differentiable_section_evaluator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/block.h"
#include "SheafSystem/sec_vd.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// DIFFERENTIABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::differentiable_section_evaluator::
differentiable_section_evaluator(const differentiable_section_evaluator& xother)
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::differentiable_section_evaluator::
~differentiable_section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

///
void
fiber_bundle::differentiable_section_evaluator::
dxi_local(size_type xlocal_coord_index,
          const block<dof_type>& xsource_dofs,
          block<dof_type>& xresult_dofs) const
{
  // Preconditions:


  require(precondition_of(dxi_local(xlocal_coord_index,
                                    xsource_dofs.base(),
                                    xsource_dofs.ct(),
                                    xresult_dofs.base(),
                                    xresult_dofs.ub())));

  // Body:

  dxi_local(xlocal_coord_index,
            xsource_dofs.base(),
            xsource_dofs.ct(),
            xresult_dofs.base(),
            xresult_dofs.ub());

  xresult_dofs.set_ct(xsource_dofs.ct());

  // Postconditions:

  ensure(postcondition_of(dxi_local(xlocal_coord_index,
                                    xsource_dofs.base(),
                                    xsource_dofs.ct(),
                                    xresult_dofs.base(),
                                    xresult_dofs.ub())));

  ensure(xresult_dofs.ct() == xsource_dofs.ct());

  // Exit:

  return;
}

///
void
fiber_bundle::differentiable_section_evaluator::
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

  /// @todo Implement general version of jacobian using dxi_local;
  /// can be optimized in derived classes.

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
const fiber_bundle::differentiable_section_evaluator::value_type*
fiber_bundle::differentiable_section_evaluator::
jacobian_values() const
{

  // Preconditions:


  // Body:

  const value_type* result = _jacobian_values;

  // Postconditions:


  // Exit:

  return result;
}

///
fiber_bundle::differentiable_section_evaluator::value_type
fiber_bundle::differentiable_section_evaluator::
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


  /// @todo Implement general version of jacobian_determinant using dxi_local;
  /// can be optimixed in derived classes.

  not_implemented();

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
fiber_bundle::differentiable_section_evaluator::
differentiable_section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// ANY FACET
// ===========================================================


///
fiber_bundle::differentiable_section_evaluator*
fiber_bundle::differentiable_section_evaluator::
clone() const
{
  differentiable_section_evaluator* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
fiber_bundle::differentiable_section_evaluator&
fiber_bundle::differentiable_section_evaluator::
operator=(const differentiable_section_evaluator& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
fiber_bundle::differentiable_section_evaluator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && any::invariant();

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
fiber_bundle::differentiable_section_evaluator::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const section_evaluator*>(xother) != 0;

  // Postconditions:

  return result;

}

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const differentiable_section_evaluator& xe, bool xinclude_shallow)
{
  size_t result;
  
  // Preconditions:

  // Body:

  /// @issue This function is incorrectly implemented.
  /// @todo Implement correctly.

  result = 0;
  
  // Postconditions:

  ensure(result == 0);
  //ensure(result >= 0);

  // Exit

  return result;
}

