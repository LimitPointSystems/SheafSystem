
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

// Template specializations for class section_space_factory.

#include "section_space_factory.impl.h"

#include "sec_e1.h"
#include "sec_e1_uniform.h"
#include "sec_e2.h"
#include "sec_e2_uniform.h"
#include "sec_e3.h"
#include "sec_e3_uniform.h"
#include "section_space_schema_poset.h"

// Local functions used only by the specializations
// are put into the empty namespace.

namespace
{

using namespace fiber_bundle;
  
//
// Sets the dofs implied by vertex index bound xi_size 
// and dof bounds xlb, xub into section xsec.
//
void put_dofs(sec_e1* xsec,
	      size_type xi_size,
	      block<sec_vd_value_type> xlb,
	      block<sec_vd_value_type> xub)
{
  // Preconditions:

  require(xi_size > 0);
  require(xlb.ct() >= 1);
  require(xub.ct() >= 1);

  // Body:
  
  sec_vd_dof_type ldelx = (xub[0] - xlb[0])/(xi_size-1);
  int i_ct = xi_size;

  sec_e1::fiber_type::volatile_type lfiber;
  for(int i=0; i<i_ct; ++i)
  {
    lfiber[0] = xlb[0] + i*ldelx;
    xsec->put_fiber(i, lfiber);
  }

  // Postconditions:

  // Exit:

  return;
}

//
// Sets the dofs implied by vertex index bounds xi_size, xj_size 
// and dof bounds xlb, xub into section xsec.
//
void put_dofs(sec_e2* xsec,
	      size_type xi_size,
	      size_type xj_size,
	      block<sec_vd_value_type> xlb,
	      block<sec_vd_value_type> xub)
{
  // Preconditions:

  require(xi_size > 0);
  require(xj_size > 0);
  require(xlb.ct() >= 2);
  require(xub.ct() >= 2);

  // Body:

  sec_vd_dof_type ldelx = (xub[0] - xlb[0])/(xi_size-1);
  int i_ct = xi_size;

  sec_vd_dof_type ldely = (xub[1] - xlb[1])/(xj_size-1);
  int j_ct = xj_size;
  
  sec_e2::fiber_type::volatile_type lfiber;

  pod_index_type ldisc_id;
  for(int i=0; i<i_ct; ++i)
  {
    lfiber[0] = xlb[0] + i*ldelx;
    for(int j=0; j<j_ct; ++j)
    {
      ldisc_id = i*j_ct+j;
      lfiber[1] = xlb[1] + j*ldely;
      xsec->put_fiber(ldisc_id, lfiber);
    }
  }

  // Postconditions:

  // Exit:

  return;
}

//
// Sets the dofs implied by vertex index bounds xi_size, 
// xj_size, xk_size and dof bounds xlb, xub into section xsec.
//
void put_dofs(sec_e3* xsec,
	      size_type xi_size,
	      size_type xj_size,
	      size_type xk_size,
	      block<sec_vd_value_type> xlb,
	      block<sec_vd_value_type> xub)
{
  // Preconditions:

  require(xi_size > 0);
  require(xj_size > 0);
  require(xlb.ct() >= 3);
  require(xub.ct() >= 3);

  // Body:

  sec_vd_dof_type ldelx = (xub[0] - xlb[0])/(xi_size-1);
  int i_ct = xi_size;

  sec_vd_dof_type ldely = (xub[1] - xlb[1])/(xj_size-1);
  int j_ct = xj_size;

  sec_vd_dof_type ldelz = (xub[2] - xlb[2])/(xk_size-1);
  int k_ct = xk_size;

  sec_e3::fiber_type::volatile_type lfiber;

  pod_index_type ldisc_id;

  for(int i=0; i<i_ct; ++i)
  {
    lfiber[0] = xlb[0] + i*ldelx;
    for(int j=0; j<j_ct; ++j)
    {
      lfiber[1] = xlb[1] + j*ldely;
      for(int k=0; k<k_ct; ++k)
      {
	lfiber[2] = xlb[2] + k*ldelz;
	ldisc_id = (i*j_ct+j)*k_ct + k;
	xsec->put_fiber(ldisc_id, lfiber);
      }
    }
  }

  // Postconditions:

  // Exit:

  return;
}
  
} // unnamed namespace



//==============================================================================
// SPECIALIZATIONS FOR COORDINATE SECTION TYPES
//==============================================================================

//==============================================================================
// SEC_E1
//==============================================================================

#include "point_block_1d.h"
#include "structured_block_1d.h"

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e1>::
put_bounds(sec_e1* xsec)
{
  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // Check the bounds cts.

    /// @issue why check df(), doesn't sec_e1 ensure it is 1?

    if((xsec->schema().df() == 1) && (lb.ct() == 1) && (ub.ct() == 1))
    {
      // Bounds are ok; get the cell type for the base space.

      string lbase_type_name(lbase_host.type_name(lbase_id));
      if((lbase_type_name == "structured_block_1d"))
      {
        // The base space is a structured_block_1d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.
	    // The number of "vertices" is the number of "zones" + 1.

        structured_block_1d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size()+1, lb, ub);
        lbase.detach_from_state();
      }
      else if((lbase_type_name == "point_block_1d"))
      {
        // The base space is a point_block_1d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_1d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), lb, ub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();
}

//==============================================================================
// SEC_E1_UNIFORM
//==============================================================================

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e1_uniform>::
put_bounds(sec_e1_uniform* xsec)
{
  xsec->put_bounds(lb[0], ub[0], true);
}

//==============================================================================
// SEC_E2
//==============================================================================

#include "point_block_2d.h"
#include "structured_block_2d.h"

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e2>::
put_bounds(sec_e2* xsec)
{
  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // Check the bounds cts.

    /// @issue why check df(), doesn't sec_e2 ensure it is 2?

    if((xsec->schema().df() == 2) && (lb.ct() == 2) && (ub.ct() == 2))
    {
      // Bounds are ok; get the cell type for the base space.

      string lbase_type_name(lbase_host.type_name(lbase_id));
      if(lbase_type_name == "structured_block_2d")
      {
        // The base space is a structured_block_2d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.
	    // The number of "vertices" is the number of "zones" + 1.

        structured_block_2d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size()+1, lbase.j_size()+1, lb, ub);
        lbase.detach_from_state();
      }
      else if(lbase_type_name == "point_block_2d")
      {
        // The base space is a point_block_2d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_2d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), lbase.j_size(), lb, ub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();

}

//==============================================================================
// SEC_E2_UNIFORM
//==============================================================================

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e2_uniform>::
put_bounds(sec_e2_uniform* xsec)
{
  xsec->put_bounds(lb, ub, true);
}

//==============================================================================
// SEC_E3
//==============================================================================

#include "point_block_3d.h"
#include "structured_block_3d.h"

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e3>::
put_bounds(sec_e3* xsec)
{
  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // check the bounds.

    if((xsec->schema().df() == 3) && (lb.ct() == 3) && (ub.ct() == 3))
    {
      // Bounds are ok; get the cell type for the base space.

      string lbase_type_name(lbase_host.type_name(lbase_id));
      if(lbase_type_name == "structured_block_3d")
      {
        // The base space is a structured_block_3d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.
	    // The number of "vertices" is the number of "zones" + 1.

        structured_block_3d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size()+1, lbase.j_size()+1, lbase.k_size()+1, lb, ub);
        lbase.detach_from_state();
      }
      else if(lbase_type_name == "point_block_3d")
      {
        // The base space is a point_block_3d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_3d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), lbase.j_size(), lbase.k_size(), lb, ub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();

}

//==============================================================================
// SEC_E3_UNIFORM
//==============================================================================

template <>
void
fiber_bundle::section_space_factory<fiber_bundle::sec_e3_uniform>::
put_bounds(sec_e3_uniform* xsec)
{
  xsec->put_bounds(lb, ub, true);
}



