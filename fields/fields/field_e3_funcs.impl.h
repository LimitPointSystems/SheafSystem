

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
