// $RCSfile: d_uniform_point_locator.cc,v $ $Revision: 1.5 $ $Date: 2013/01/12 17:17:31 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Explicit instantiation for class d_uniform_point_locator


#include "d_uniform_point_locator.impl.h"

#include "sec_rep_descriptor.h"

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

