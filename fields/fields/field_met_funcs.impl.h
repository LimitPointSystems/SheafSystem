

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_met algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF MET FACET
//==============================================================================

#ifndef FIELD_ED_H
#include "field_ed.h"
#endif


///
void
fields::field_met_algebra::
lower(const field_met& xmetric, const field_ed& xvector, field_ed& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    lower(xmetric.property(), xvector.property(), xresult.property(),\
          xauto_access)));

  // Body:

  fiber_bundle::sec_met_algebra::lower(xmetric.property(),
				       xvector.property(),
				       xresult.property(),
				       xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    lower(xmetric.property(), xvector.property(), xresult.property(),\
          xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_met_algebra::
raise(const field_met& xmetric, const field_ed& xcovector, field_ed& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    raise(xmetric.property(), xcovector.property(), xresult.property(),\
          xauto_access)));

  // Body:

  fiber_bundle::sec_met_algebra::raise(xmetric.property(),
				       xcovector.property(),
				       xresult.property(),
				       xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    raise(xmetric.property(), xcovector.property(), xresult.property(),\
          xauto_access)));

  // Exit:

  return;
}
