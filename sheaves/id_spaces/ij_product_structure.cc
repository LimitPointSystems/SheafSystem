

//
// Copyright (c) 2011 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class ij_product_structure

#include "ij_product_structure.h"
#include "assert_contract.h"


// ===========================================================
// IJ_PRODUCT_STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::ij_product_structure::
ij_product_structure(size_type xi_ub, size_type xj_ub)
  : _i_ub(xi_ub),
    _j_ub(xj_ub)
{
  // Preconditions:

  require(xi_ub > 0);
  require(xj_ub > 0);

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(ub(0) == xi_ub);
  ensure(ub(1) == xj_ub);
  ensure(ordinal_ub() == xi_ub*xj_ub);

  // Exit:

  return;
}

sheaf::ij_product_structure::
ij_product_structure(const ij_product_structure& xother)
{
  // Preconditions:

  // Body:

  *this = xother;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit:

  return;
}

sheaf::ij_product_structure&
sheaf::ij_product_structure::
operator=(const ij_product_structure& xother)
{
  // Preconditions:
    
  // Body:
  
  _i_ub = xother._i_ub;
  _j_ub = xother._j_ub;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

sheaf::ij_product_structure::
~ij_product_structure()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// IJ_PRODUCT_STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::ij_product_structure*
sheaf::ij_product_structure::
clone() const
{
  ij_product_structure* result;
  
  // Preconditions:

  // Body:
  
  result = new ij_product_structure(_i_ub, _j_ub);

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

sheaf::ij_product_structure&
sheaf::ij_product_structure::
operator=(const abstract_product_structure& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  const ij_product_structure lother =
    dynamic_cast<const ij_product_structure&>(xother);

  _i_ub = lother._i_ub;
  _j_ub = lother._j_ub;

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

bool
sheaf::ij_product_structure::
operator==(const abstract_product_structure& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:

  const ij_product_structure& lother =
    dynamic_cast<const ij_product_structure&>(xother);

  bool result = (_i_ub == lother._i_ub);
  result = result && (_j_ub == lother._j_ub);

  // Postconditions:

  ensure(is_basic_query);

  // Exit
  
  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// PRODUCT FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::size_type
sheaf::ij_product_structure::
d() const
{
  // Preconditions:

  // Body:

  size_type result = 2;

  // Postconditions:

  ensure(result > 1);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::ij_product_structure::
ub(pod_type xi) const
{
  // Preconditions:

  require((0 <= xi) && (xi < d()));

  // Body:

  size_type result = (xi == 0) ? _i_ub : _j_ub;

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::ij_product_structure::
i_ub() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _i_ub;
}

sheaf::size_type
sheaf::ij_product_structure::
j_ub() const
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return _j_ub;
}

void
sheaf::ij_product_structure::
ordinal(pod_type xi, pod_type xj, pod_type& xordinal) const
{
  // Preconditions:

  require((0 <= xi) && (xi < ub(0)));
  require((0 <= xj) && (xj < ub(1)));

  // Body:

  xordinal = sheaf::ordinal(xi, xj, _j_ub);

  // Postconditions:

  ensure((0 <= xordinal) && (xordinal < ordinal_ub()));

  // Exit:

  return;
}

void
sheaf::ij_product_structure::
ordinal(pod_type* xtuple, pod_type& xordinal) const
{
  // Preconditions:

  require(unexecutable("length of xtuple equals d()"));
  require_for_range(pod_type i=0, i<d(), ++i,
		    (0 <= xtuple[i]) && (xtuple[i] < ub(i)));

  // Body:

  xordinal = sheaf::ordinal(xtuple[0], xtuple[1], _j_ub);

  // Postconditions:

  ensure((0 <= xordinal) && (xordinal < ordinal_ub()));

  // Exit:

  return;
}

void
sheaf::ij_product_structure::
tuple(pod_type xordinal, pod_type& xi, pod_type& xj) const
{
  // Preconditions:

  require((0 <= xordinal) && (xordinal < ordinal_ub()));

  // Body:

  sheaf::tuple(xordinal, _j_ub, xi, xj);

  // Postconditions:

  ensure((0 <= xi) && (xi < ub(0)));
  ensure((0 <= xj) && (xj < ub(1)));
  
  // Exit:

  return;
}

void
sheaf::ij_product_structure::
tuple(pod_type xordinal, pod_type* xtuple) const
{
  // Preconditions:

  require((0 <= xordinal) && (xordinal < ordinal_ub()));
  require(unexecutable("length of xtuple equals d()"));

  // Body:

  sheaf::tuple(xordinal, _j_ub, xtuple[0], xtuple[1]);

  // Postconditions:

  ensure_for_range(pod_type i=0, i<d(), ++i,
		   (0 <= xtuple[i]) && (xtuple[i] < ub(i)));

  // Exit:

  return;
}

void
sheaf::ij_product_structure::
put_ubs(size_type xi_ub, size_type xj_ub)
{
  // Preconditions:

  require(xi_ub > 0);
  require(xj_ub > 0);

  // Body:

  _i_ub = xi_ub;
  _j_ub = xj_ub;

  // Postconditions:

  ensure(ub(0) == xi_ub);
  ensure(ub(1) == xj_ub);

  // Exit:

  return;
}

void
sheaf::ij_product_structure::
put_ubs(size_type* xubs)
{
  // Preconditions:

  require(unexecutable("xubs.length >= d()"));
  require_for_range(pod_type i=0, i<d(), ++i, xubs[i] > 0);

  // Body:

  _i_ub = xubs[0];
  _j_ub = xubs[1];

  // Postconditions:

  ensure_for_range(pod_type i=0, i<d(), ++i, ub(i) == xubs[i]);

  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
sheaf::ij_product_structure::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const ij_product_structure*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::ij_product_structure::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(abstract_product_structure::invariant());

    // Invariances for this class:

    invariance(d() == 2);
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }
  
  // Exit

  return result;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
size_t
sheaf::
deep_size(const ij_product_structure& xn, bool xinclude_shallow)
{
  // Preconditions:

  // Body:

  size_t result = xinclude_shallow ? sizeof(xn) : 0;

  // Postconditions:

  ensure(result >= 0);

  // Exit

  return result;
}
