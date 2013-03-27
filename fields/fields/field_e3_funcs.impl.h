
// $RCSfile: field_e3_funcs.impl.h,v $ $Revision: 1.7 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_e3 algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF E3 FACET
//==============================================================================

///
void
fields::field_e3_algebra::
cross(const field_e3& x0, const field_e3& x1, field_e3& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    cross(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_e3_algebra::cross(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    cross(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_e3_algebra::
cross_equal(field_e3& xresult, const field_e3& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    cross_equal(xresult.property(), xother.property(), xauto_access)));

   // Body:

   fiber_bundle::sec_e3_algebra::cross_equal(xresult.property(), xother.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    cross_equal(xresult.property(), xother.property(), xauto_access)));

  // Exit:

  return;
}
