
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

/// Implementation for field_met algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF MET FACET
//==============================================================================

#ifndef COM_LIMITPOINT_FIELDS_FIELD_ED_H
#include "ComLimitPoint/fields/field_ed.h"
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
