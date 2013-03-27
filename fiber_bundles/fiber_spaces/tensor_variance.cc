
// $RCSfile: tensor_variance.cc,v $ $Revision: 1.9 $ $Date: 2013/01/12 17:17:03 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class tensor_variance

#include "tensor_variance.h"
#include "assert_contract.h"
#include "std_iostream.h"

using namespace fiber_bundle; // Workaround for MS C++ bug.

//==============================================================================
// TENSOR_VARIANCE FACET
//==============================================================================
 
// PUBLIC MEMBER FUNCTIONS

fiber_bundle::tensor_variance::
tensor_variance()
{
  // Preconditions:

  // Body:

  _p = 0;
  
  // Postconditions:

  ensure(p() == 0);
  
  // Exit:

  return;
}

fiber_bundle::tensor_variance::
tensor_variance(const tensor_variance& xother)
{
  // Preconditions:

  // Body:

  *this = xother;
  
  // Postconditions:

  // Exit:

  return;
}

fiber_bundle::tensor_variance::
tensor_variance(int xp)
{
  // Preconditions:

  require((0 <= xp) && (xp < capacity()));
  
  // Body:

  _p = xp;
  
  // Postconditions:

  ensure(p() == xp);
  ensure_for_all(i, 0, xp, is_contravariant(i));
  
  // Exit:

  return;
}

fiber_bundle::tensor_variance::
~tensor_variance()
{
  // Preconditions:

  // Body:

  // Nothing to do.

  // Postconditions:


  // Exit:

  return;
}

fiber_bundle::tensor_variance&
fiber_bundle::tensor_variance::
operator=(const tensor_variance& xother)
{
  // Preconditions:


  // Body:

  _p = xother._p;
  _variance = xother._variance;

  // Postconditions:

  ensure((*this) == xother);
  
  // Exit:

  return (*this);
}

bool
fiber_bundle::tensor_variance::
operator==(const tensor_variance& xother) const
{
  // Preconditions:


  // Body:

  bool result = (_p == xother._p) && (_variance == xother._variance);

  // Postconditions:

  // Exit:

  return result;
}


int
fiber_bundle::tensor_variance::
capacity()
{
  return numeric_limits<unsigned long int>::digits;
}

int
fiber_bundle::tensor_variance::
p() const
{
  return _p;
}

bool
fiber_bundle::tensor_variance::
variance(int xi) const
{
  bool result;

  // Preconditions:

  require((0 <= xi) && (xi < p()));
  
  // Body:

  result = _variance[xi];

  // Postconditions:


  // Exit:

  return result;
}

void
fiber_bundle::tensor_variance::
put_variance(int xi, bool xvalue)
{
  // Preconditions:

  require((0 <= xi) && (xi < p()));
  
  // Body:

  _variance[xi] = xvalue;

  // Postconditions:

  ensure(variance(xi) == xvalue);
  
  // Exit:

  return;
}

void
fiber_bundle::tensor_variance::
put_variance(bool xvalue)
{
  // Preconditions:
  
  // Body:

  for(int i=0; i< _p; ++i)
  {
    _variance[i] = xvalue;
  }
  

  // Postconditions:

  ensure_for_all(i, 0, p(), variance(i) == xvalue);
  
  // Exit:

  return;
}

bool
fiber_bundle::tensor_variance::
is_covariant(int xi) const
{
  bool result;

  // Preconditions:

  require((0 <= xi) && (xi < p()));
  
  // Body:

  result = _variance[xi];

  // Postconditions:

  ensure(result == variance(xi));
  
  // Exit:

  return result;
}

bool
fiber_bundle::tensor_variance::
is_covariant() const
{
  // Preconditions:

  // Body:

  bool result = (_p == 0) || (_variance.count() == _p);
  
  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::tensor_variance::
is_contravariant(int xi) const
{
  bool result;

  // Preconditions:

  require((0 <= xi) && (xi < p()));
  
  // Body:

  result = !_variance[xi];

  // Postconditions:

  ensure(result == !variance(xi));

  // Exit:

  return result;
}

bool
fiber_bundle::tensor_variance::
is_contravariant() const
{
  bool result;

  // Preconditions:

  // Body:

  result = (_p == 0) || (_variance.count() == 0);
  
  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::tensor_variance::
is_mixed() const
{
  bool result;

  // Preconditions:
  
  // Body:

  if(_p < 2)
  {
    result = false;
  }
  else
  {
    size_t lct = _variance.count();
    result = ((0 < lct) && (lct < _p));
  }

  // Postconditions:


  // Exit:

  return result;
}

bool
fiber_bundle::tensor_variance::
is_pure() const
{
  return !is_mixed();
}

void
fiber_bundle::tensor_variance::
purify()
{
  // Preconditions:
  
  // Body:

  for(int i=1; i< _p; ++i)
  {
    _variance[i] = _variance[0];
  }
  

  // Postconditions:

  ensure(is_pure());
  ensure_for_all(i, 0, p(), variance(i) == variance(0));
  
  // Exit:

  return;
}

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

fiber_bundle::tensor_variance
fiber_bundle::
contract(const tensor_variance& x0, int xp, int xq)
{

  // Preconditions:

  require((0 <= xp) && (xp < x0.p()));
  require((0 <= xq) && (xq < x0.p()));
  
  // Body:

  int p = x0.p();

  tensor_variance result(p-2);

  int i = 0;
  for(int j=0; j<p; ++j)
  {
    if((j!=xp) && (j!=xq))
    {
      result.put_variance(i++, x0.variance(j));
    }
  }

  // Postconditions:

  ensure(result.p() == x0.p() - 2);

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
tensor_product(const tensor_variance& x0, const tensor_variance& x1)
{

  // Preconditions:

  // Body:

  int p0 = x0.p();
  int p1 = x1.p();
  int pr = p0+p1;
  
  tensor_variance result(pr);

  int r=0;
  for(int i=0; i<p0; ++i)
  {
    result.put_variance(r++, x0.variance(i));
  }
  
  for(int i=0; i<p1; ++i)
  {
    result.put_variance(r++, x1.variance(i));
  }

  // Postconditions:

  ensure(result.p() == x0.p() + x1.p());
  ensure(result.is_covariant() == x0.is_covariant());

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
hook(const tensor_variance& x0)
{

  // Preconditions:

  require(x0.is_covariant() || x0.is_contravariant());
  require(x0.p() >= 1);
  
  // Body:

  int p = x0.p();

  tensor_variance result(p-1);

  result.put_variance(x0.is_covariant());
  
  // Postconditions:

  ensure(result.p() == x0.p() - 1);
  ensure(x0.is_covariant() ? result.is_covariant() : true);
  ensure(x0.is_contravariant() ? result.is_contravariant() : true);

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
star(const tensor_variance& x0, int xdd)
{

  // Preconditions:

  require(x0.is_covariant() || x0.is_contravariant());
  require(x0.p() > 0);
  require(x0.p() <= xdd);
  
  // Body:

  int p = x0.p();

  tensor_variance result(xdd - p);

  result.put_variance(x0.is_covariant());

  // Postconditions:

  ensure(result.p() == xdd - x0.p());
  ensure(x0.is_covariant() ? result.is_covariant() : true);
  ensure(x0.is_contravariant() ? result.is_contravariant() : true);

  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
wedge(const tensor_variance& x0, const tensor_variance& x1)
{

  // Preconditions:

  require(x0.is_covariant() || x0.is_contravariant());
  require(x1.is_covariant() || x1.is_contravariant());
  require(x0.is_covariant() == x1.is_covariant());

  // Body:

  int p0 = x0.p();
  int p1 = x1.p();
  int pr = p0+p1;
  
  tensor_variance result(pr);

  result.put_variance(x0.is_covariant());

  // Postconditions:

  ensure(result.p() == x0.p() + x1.p());
  ensure(result.is_covariant() == x0.is_covariant());
  
  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
raise(const tensor_variance& x0, int xi)
{

  // Preconditions:

  require((0 <= xi) && (xi < x0.p()));
  
  // Body:

  tensor_variance result(x0);

  result.put_variance(xi, false);
  
  // Postconditions:

  ensure(result.p() == x0.p());
  ensure(result.is_contravariant(xi));
  
  // Exit:

  return result;
}

fiber_bundle::tensor_variance
fiber_bundle::
lower(const tensor_variance& x0, int xi)
{

  // Preconditions:

  require((0 <= xi) && (xi < x0.p()));
  
  // Body:

  tensor_variance result(x0);

  result.put_variance(xi, true);
  
  // Postconditions:

  ensure(result.p() == x0.p());
  ensure(result.is_covariant(xi));
  
  // Exit:

  return result;
}

