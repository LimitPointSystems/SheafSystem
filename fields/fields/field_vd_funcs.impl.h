
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

/// Implementation for field_vd algebra functions.

//=============================================================================
// NON-MEMBER FUNCTIONS OF VD FACET
//=============================================================================

#ifndef FIELD_AT0_H
#include "field_at0.h"
#endif


///
void
fields::field_vd_algebra::
add(const field_vd& x0, const field_vd& x1, field_vd& xresult,
    bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    add(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::add(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    add(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
add_equal(field_vd& xresult, const field_vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(add(xresult, xother, xresult, xauto_access)));

   // Body:

  add(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(add(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
subtract(const field_vd& x0, const field_vd& x1, field_vd& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    subtract(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::subtract(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    subtract(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
subtract_equal(field_vd& xresult, const field_vd& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(subtract(xresult, xother, xresult, xauto_access)));

   // Body:

  subtract(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(subtract(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
multiply(const field_vd& x0, const sec_at0& x1, field_vd& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    multiply(x0.property(), x1, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::multiply(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    multiply(x0.property(), x1, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
multiply_equal(field_vd& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
multiply(const field_vd& x0, const vd_value_type& x1, field_vd& xresult,
         bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    multiply(x0.property(), x1, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::multiply(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    multiply(x0.property(), x1, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
multiply_equal(field_vd& xresult, const vd_value_type& xother,
               bool xauto_access)
{
  // Preconditions:

  require(precondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Body:

  multiply(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(multiply(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

void
fields::field_vd_algebra::
divide(const field_vd& x0, const sec_at0& x1, field_vd& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    divide(x0.property(), x1, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::divide(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    divide(x0.property(), x1, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
divide_equal(field_vd& xresult, const sec_at0& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
divide(const field_vd& x0, const vd_value_type& x1, field_vd& xresult,
       bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    divide(x0.property(), x1, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::divide(x0.property(), x1, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    divide(x0.property(), x1, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
divide_equal(field_vd& xresult, const vd_value_type& xother, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Body:

  divide(xresult, xother, xresult, xauto_access);

  // Postconditions:

  ensure(postcondition_of(divide(xresult, xother, xresult, xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_vd_algebra::
contract(const field_vd& xvector, const field_vd& xcovector,
         field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    contract(xvector.property(), xcovector.property(),\
             xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_vd_algebra::contract(xvector.property(), xcovector.property(),
					 xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    contract(xvector.property(), xcovector.property(),\
             xresult.property(), xauto_access)));

  // Exit:

  return;
}
