// $RCSfile: integrable_section_evaluator.cc,v $ $Revision: 1.11 $ $Date: 2013/03/20 21:56:05 $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class section_evaluator

#include "integrable_section_evaluator.h"

#include "assert_contract.h"
#include "block.h"
#include "sec_vd.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

// ===========================================================
// INTEGRABLE_SECTION_EVALUATOR FACET
// ===========================================================

///
fiber_bundle::integrable_section_evaluator::
integrable_section_evaluator(const integrable_section_evaluator& xother)
{
  // Preconditions:

  // Body:

  // No action required.

  // Postconditions:

  ensure(invariant());

  return;
}

///
fiber_bundle::integrable_section_evaluator::
~integrable_section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


///
fiber_bundle::integrable_section_evaluator::value_type
fiber_bundle::integrable_section_evaluator::
volume(const dof_type xcoord_dofs[],
       size_type xcoord_dofs_ub,
       size_type xdf)
{
  // Preconditions:

  require(xcoord_dofs != 0);
  require(xcoord_dofs_ub >= 0);

  // Body:

  is_abstract();

  value_type result = 0.0;

  // Postconditions:

  ensure(invariant());

  // Exit:

  return result;
}

///
void
fiber_bundle::integrable_section_evaluator::
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

  is_abstract();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::integrable_section_evaluator::
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
  require(xcoord_dofs_ub >= 0);
  require(xresult_integrals != 0);
  require(xresult_integrals_ub >= 0);

  // Body:

  integrate(xcoord_dofs, xcoord_dofs_ub, xdf, &xintegrand, 1, xresult_integrals, xresult_integrals_ub);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
fiber_bundle::integrable_section_evaluator::
gauss_point(pod_index_type xindex,
            coord_type xresult[],
            size_type xresult_ub)
{
  // Preconditions:

  require((0 <= xindex) && (xindex < dof_ct()));
  require(xresult_ub >= db());

  // Body:

  is_abstract();

  // Postconditions:

  ensure(in_standard_domain(xresult, xresult_ub));
  ensure(invariant());

  // Exit:

  return;
}

///
fiber_bundle::integrable_section_evaluator::
integrable_section_evaluator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}

// ===========================================================
// DOMAIN FACET
// =========================================================== 

// ===========================================================
// ANY FACET
// ===========================================================


///
fiber_bundle::integrable_section_evaluator*
fiber_bundle::integrable_section_evaluator::
clone() const
{
  integrable_section_evaluator* result = 0;

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
fiber_bundle::integrable_section_evaluator&
fiber_bundle::integrable_section_evaluator::
operator=(const integrable_section_evaluator& xother)
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
fiber_bundle::integrable_section_evaluator::
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
fiber_bundle::integrable_section_evaluator::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const integrable_section_evaluator*>(xother) != 0;

  // Postconditions:

  return result;

}


// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

size_t
fiber_bundle::
deep_size(const integrable_section_evaluator& xe, bool xinclude_shallow)
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

