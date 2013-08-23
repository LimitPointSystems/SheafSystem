
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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




