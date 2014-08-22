
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

 
// Implementation for class auto_block.

#include "ComLimitPoint/sheaf/auto_block.impl.h"

using namespace std;

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

