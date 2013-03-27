
// $RCSfile: field_ed_funcs.impl.h,v $ $Revision: 1.10 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_ed algebra functions.

//=============================================================================
// NON-MEMBER FUNCTIONS OF ED FACET
//=============================================================================

#ifndef FIELD_AT0_H
#include "field_at0.h"
#endif


///
void 
fields::field_ed_algebra::
dot(const field_ed& x0, const field_ed& x1, field_at0& xresult,
    bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    dot(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_ed_algebra::dot(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    dot(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_ed_algebra::
length(const field_ed& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    length(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_ed_algebra::length(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    length(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_ed_algebra::
put_length(field_ed& x0, const vd_value_type& xlength, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    put_length(x0.property(), xlength, xauto_access)));

  // Body:

  fiber_bundle::sec_ed_algebra::put_length(x0.property(), xlength, xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    put_length(x0.property(), xlength, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_ed_algebra::
normalize(const field_ed& x0, field_ed& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    normalize(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_ed_algebra::normalize(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    normalize(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_ed_algebra::
normalize(field_ed& x0, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    normalize(x0.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_ed_algebra::normalize(x0.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    normalize(x0.property(), xauto_access)));

  // Exit:

  return;
}
