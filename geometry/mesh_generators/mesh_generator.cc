

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
/// Implementation for class mesh_generator.

#include "mesh_generator.h"

#include "assert_contract.h"
#include "std_string.h"

using namespace geometry;

//#define DIAGNOSTIC_OUTPUT 1

// =============================================================================
// MESH_GENERATOR FACET
// =============================================================================

geometry::mesh_generator::
mesh_generator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

geometry::mesh_generator::
~mesh_generator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:
}

void
geometry::mesh_generator::
generate()
{
  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

// =============================================================================
// ANY FACET
// =============================================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::mesh_generator::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this.

  bool result = dynamic_cast<const mesh_generator*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;
}

geometry::mesh_generator*
geometry::mesh_generator::
clone() const
{
  mesh_generator* result;
  
  // Preconditions:

  // Body:
  
  //result = new mesh_generator();
  result = 0;

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result; 
}

bool
geometry::mesh_generator::
invariant() const
{
  bool result = true;
 
  // Preconditions:

  // Body:
 
  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(any::invariant());

    // Invariances for this class:
      
    // Finished, turn invariant checking back on.      

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}

// =============================================================================
//  NON-MEMBER FUNCTIONS
// =============================================================================
 
//#undef DIAGNOSTIC_OUTPUT

