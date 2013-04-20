

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Implementation for field_at0 algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF AT0 FACET
//==============================================================================

///
void
fields::field_at0_algebra::
acos(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    acos(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::acos(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    acos(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
asin(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    asin(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::asin(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    asin(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
atan(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    atan(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::atan(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    atan(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
atan2(const field_at0& x0, const field_at0& x1, field_at0& xresult,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    atan2(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::atan2(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    atan2(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
ceil(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    ceil(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::ceil(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    ceil(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
cos(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(cos(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::cos(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(cos(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
cosh(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(cosh(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::cosh(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    cosh(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
exp(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    exp(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::exp(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    exp(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
fabs(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    fabs(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::fabs(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    fabs(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
floor(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    floor(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::floor(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    floor(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
fmod(const field_at0& x0, const field_at0& x1, field_at0& xresult,
     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    fmod(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::fmod(x0.property(), x1.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    fmod(x0.property(), x1.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
frexp(const field_at0& x0, field_at0& xsignificand, field_at0& xexp,
      bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    frexp(x0.property(), xsignificand.property(), xexp.property(),\
          xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::frexp(x0.property(), xsignificand.property(), xexp.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    frexp(x0.property(), xsignificand.property(), xexp.property(),\
          xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
ldexp(const field_at0& x0, int xexp, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    ldexp(x0.property(), xexp, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::ldexp(x0.property(), xexp, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    ldexp(x0.property(), xexp, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
log(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    log(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::log(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    log(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
log10(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    log10(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::log10(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    log10(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
modf(const field_at0& x0, field_at0& xintpart, field_at0& xfractpart,
     bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    modf(x0.property(), xintpart.property(), xfractpart.property(),\
         xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::modf(x0.property(), xintpart.property(), xfractpart.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    modf(x0.property(), xintpart.property(), xfractpart.property(),\
         xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
pow(const field_at0& x0, const vd_value_type& xexponent, field_at0& xresult,
    bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    pow(x0.property(), xexponent, xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::pow(x0.property(), xexponent, xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    pow(x0.property(), xexponent, xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
sin(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    sin(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::sin(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    sin(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
sinh(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    sinh(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::sinh(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    sinh(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
sqrt(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    sqrt(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::sqrt(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    sqrt(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
tan(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    tan(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::tan(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    tan(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

///
void
fields::field_at0_algebra::
tanh(const field_at0& x0, field_at0& xresult, bool xauto_access)
{
  // Preconditions:

  require(precondition_of(\
    tanh(x0.property(), xresult.property(), xauto_access)));

  // Body:

  fiber_bundle::sec_at0_algebra::tanh(x0.property(), xresult.property(), xauto_access);

  // Postconditions:

  ensure(postcondition_of(\
    tanh(x0.property(), xresult.property(), xauto_access)));

  // Exit:

  return;
}

