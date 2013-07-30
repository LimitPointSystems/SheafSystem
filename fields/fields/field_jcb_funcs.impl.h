

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

