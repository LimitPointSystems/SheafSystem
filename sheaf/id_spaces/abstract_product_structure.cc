
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

/// @file
/// Implementation for class abstract_product_structure

#include "ComLimitPoint/sheaf/abstract_product_structure.h"
#include "ComLimitPoint/sheaf/assert_contract.h"


// ===========================================================
// ABSTRACT_PRODUCT_STRUCTURE FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

sheaf::abstract_product_structure::
~abstract_product_structure()
{  
  // Preconditions:
    
  // Body:
  
  // nothing to do.

  // Postconditions:

  // Exit:

  return; 
}

sheaf::abstract_product_structure*
sheaf::abstract_product_structure::
clone() const
{
  abstract_product_structure* result = 0; // Silence compiler warnings
  
  // Preconditions:

  // Body:
  
  is_abstract();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

sheaf::abstract_product_structure&
sheaf::abstract_product_structure::
operator=(const abstract_product_structure& xother)
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:
  
  is_abstract();

  // Postconditions:

  ensure(invariant());
  ensure((*this) == xother);

  // Exit
  
  return *this;
}

bool
sheaf::abstract_product_structure::
operator==(const abstract_product_structure& xother) const
{
  // Preconditions:
    
  require(is_ancestor_of(&xother));

  // Body:

  bool result = false; // Just to silence compiler warnings.
  
  is_abstract();

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
sheaf::abstract_product_structure::
d() const
{
  // Preconditions:

  // Body:

  size_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result > 1);

  // Exit:

  return result;
}

sheaf::size_type
sheaf::abstract_product_structure::
ub(pod_type xi) const
{
  // Preconditions:

  require((0 <= xi) && (xi < d()));

  // Body:

  size_type result = 0; // Just to silence compiler warnings.

  is_abstract();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

void
sheaf::abstract_product_structure::
ordinal(pod_type* xtuple, pod_type& xordinal) const
{
  // Preconditions:

  require(unexecutable("length of xtuple equals d()"));
  require_for_range(pod_type i=0, i<d(), ++i,
		    (0 <= xtuple[i]) && (xtuple[i] < ub(i)));

  // Body:

  is_abstract();

  // Postconditions:

  ensure((0 <= xordinal) && (xordinal < ordinal_ub()));

  // Exit:

  return;
}

void
sheaf::abstract_product_structure::
tuple(pod_type xordinal, pod_type* xtuple) const
{
  // Preconditions:

  require((0 <= xordinal) && (xordinal < ordinal_ub()));
  require(unexecutable("length of xtuple equals d()"));

  // Body:

  is_abstract();

  // Postconditions:

  ensure_for_range(pod_type i=0, i<d(), ++i,
		   (0 <= xtuple[i]) && (xtuple[i] < ub(i)));

  // Exit:

  return;
}

sheaf::size_type
sheaf::abstract_product_structure::
ordinal_ub() const
{
  // Preconditions:

  // Body:

  size_type result = 1;

  for(pod_type i=0; i<d(); i++)
  {
    result *= ub(i);
  }

  // Postconditions:

  ensure(is_basic_query);

  // Exit:

  return result;
}

void
sheaf::abstract_product_structure::
put_ubs(size_type* xubs)
{
  // Preconditions:

  require(unexecutable("xubs.length >= d()"));
  require_for_range(pod_type i=0, i<d(), ++i, xubs[i] > 0);

  // Body:

  is_abstract();

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
sheaf::abstract_product_structure::
is_ancestor_of(const any *other) const
{
  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const abstract_product_structure*>(other) != 0;

  // Postconditions:

  // Exit:

  return result;
}

bool
sheaf::abstract_product_structure::
invariant() const
{
  bool result = true;
  
  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:
      
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
 
