
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





