

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_atp algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF ATP FACET
//==============================================================================

///
void
fields::field_atp_algebra::
hook(const field_atp& x0, const  field_atp& x1, field_atp& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    hook(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_atp_algebra::hook(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    hook(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_atp_algebra::
star(const field_atp& x0, field_atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    star(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_atp_algebra::star(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    star(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_atp_algebra::
wedge(const field_atp& x0, const field_atp& x1, field_atp& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    wedge(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_atp_algebra::wedge(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    wedge(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}




