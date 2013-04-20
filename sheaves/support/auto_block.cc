
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

 
// Implementation for class auto_block.

#include "auto_block.impl.h"

// ===========================================================
// INVALID_BLOCK_INITIALIZATION_POLICY SPECIALIZATIONS
// ===========================================================

// float

float
sheaf::invalid_block_initialization_policy<float>::
invalid()
{
  static const float result =
    numeric_limits<float>::has_quiet_NaN ?
    numeric_limits<float>::quiet_NaN() :
    numeric_limits<float>::max();

  return result;
}

void
sheaf::invalid_block_initialization_policy<float>::
initialize(float* xbegin, float* xend)
{
  for(float* i=xbegin; i<xend; ++i)
  {
    *i = invalid();
  }
}

void
sheaf::invalid_block_initialization_policy<float>::
initialize(float& xvalue)
{
  xvalue = invalid();
}

// double

double
sheaf::invalid_block_initialization_policy<double>::
invalid()
{
  static const double result =
    numeric_limits<double>::has_quiet_NaN ?
    numeric_limits<double>::quiet_NaN() :
    numeric_limits<double>::max();

  return result;
}

void
sheaf::invalid_block_initialization_policy<double>::
initialize(double* xbegin, double* xend)
{
  for(double* i=xbegin; i<xend; ++i)
  {
    *i = invalid();
  }
}

void
sheaf::invalid_block_initialization_policy<double>::
initialize(double& xvalue)
{
  xvalue = invalid();
}

