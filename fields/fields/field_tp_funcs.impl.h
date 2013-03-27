
// $RCSfile: field_tp_funcs.impl.h,v $ $Revision: 1.8 $ $Date: 2013/03/13 00:58:56 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_tp algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF TP FACET
//==============================================================================

#ifndef FIELD_ATP_H
#include "field_atp.h"
#endif

#ifndef FIELD_STP_H
#include "field_stp.h"
#endif


///
void
fields::field_tp_algebra::
alt(const field_tp& x0, field_atp& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    alt(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_tp_algebra::alt(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    alt(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_tp_algebra::
sym(const field_tp& x0, field_stp& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    sym(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_tp_algebra::sym(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    sym(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_tp_algebra::
contract(const field_tp& x0, int xp, int xq, field_tp& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    contract(x0.property(), xp, xq, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_tp_algebra::contract(x0.property(),xp, xq, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    contract(x0.property(), xp, xq, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_tp_algebra::
tensor(const field_tp& x0, const field_tp& x1, field_tp& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    tensor(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_tp_algebra::tensor(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    tensor(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}


