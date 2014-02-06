
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

/// @file
/// Explicit instantiation for class d_uniform_point_locator


#include "d_uniform_point_locator.impl.h"

#include "sec_rep_descriptor.h"

using namespace std;
using namespace geometry; // Workaround for MS C++ bug.

// ============================================================================
/// @name SPECIALIZATIONS
// ============================================================================
//@{

template <>
geometry::d_uniform_point_locator<1, 1>::
d_uniform_point_locator(sec_ed& xcoords)
    : point_locator(xcoords)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));
  require(xcoords.schema().rep().name() == "vertex_block_uniform");

  // Body:


  this->_block     = new structured_block_1d(xcoords.schema().base_space());
  this->_block_pt  = new chart_point_1d();
  this->_evaluator = new uniform_1d;

  update();

  // Postconditions:


  // Exit:

  return;
}

template <>
geometry::d_uniform_point_locator<2, 2>::
d_uniform_point_locator(sec_ed& xcoords)
    : point_locator(xcoords)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));
  require(xcoords.schema().rep().name() == "vertex_block_uniform");

  // Body:


  this->_block     = new structured_block_2d(xcoords.schema().base_space());
  this->_block_pt  = new chart_point_2d();
  this->_evaluator = new uniform_2d;

  update();

  // Postconditions:


  // Exit:

  return;
}

template <>
geometry::d_uniform_point_locator<3, 3>::
d_uniform_point_locator(sec_ed& xcoords)
    : point_locator(xcoords)
{
  // Preconditions:

  require(precondition_of(point_locator(xcoords)));
  require(xcoords.schema().rep().name() == "vertex_block_uniform");

  // Body:


  this->_block     = new structured_block_3d(xcoords.schema().base_space());
  this->_block_pt  = new chart_point_3d();
  this->_evaluator = new uniform_3d;

  update();

  // Postconditions:


  // Exit:

  return;
}

//@}

