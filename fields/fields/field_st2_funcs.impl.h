

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_st2 algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF ST2 FACET
//==============================================================================

#ifndef FIELD_AT0_H
#include "field_at0.h"
#endif


///
void
fields::field_st2_algebra::
trace(const field_st2& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    trace(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_st2_algebra::trace(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    trace(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_st2_algebra::
determinant(const field_st2& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    determinant(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_st2_algebra::determinant(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    determinant(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}





