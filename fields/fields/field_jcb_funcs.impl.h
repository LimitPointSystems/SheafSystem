
// $RCSfile: field_jcb_funcs.impl.h,v $ $Revision: 1.8 $ $Date: 2013/03/13 00:58:55 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_jcb algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF JCB FACET
//==============================================================================

#ifndef FIELD_AT1_H
#include "field_at1.h"
#endif


///
void
fields::field_jcb_algebra::
push(const field_jcb& xjcb, const field_at1& xvector, field_at1& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    push(xjcb.property(), xvector.property(), xresult.property(),\
         xauto_access)));

  // Body:

  fiber_bundle::sec_jcb_algebra::push(xjcb.property(), xvector.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    push(xjcb.property(), xvector.property(), xresult.property(),\
         xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_jcb_algebra::
pull(const field_jcb& xjcb, const field_at1& xcovector, field_at1& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    pull(xjcb.property(), xcovector.property(), xresult.property(),\
         xauto_access)));

  // Body:

  fiber_bundle::sec_jcb_algebra::pull(xjcb.property(), xcovector.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    pull(xjcb.property(), xcovector.property(), xresult.property(),\
         xauto_access)));

  // Exit:

  return;
}

