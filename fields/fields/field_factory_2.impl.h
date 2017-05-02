
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
/// Implementation for class field_factory_2

#ifndef FIELD_FACTORY_2_IMPL_H
#define FIELD_FACTORY_2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef FIELD_FACTORY_2_H
#include "SheafSystem/field_factory_2.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "SheafSystem/assert_contract.h"
#endif

#ifndef BASE_SPACE_MEMBER_H
#include "SheafSystem/base_space_member.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "SheafSystem/error_message.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "SheafSystem/fiber_bundles_namespace.h"
#endif

#ifndef POINT_BLOCK_1D_H
#include "SheafSystem/point_block_1d.h"
#endif

#ifndef POINT_BLOCK_2D_H
#include "SheafSystem/point_block_2d.h"
#endif

#ifndef POINT_BLOCK_3D_H
#include "SheafSystem/point_block_3d.h"
#endif

#ifndef SEC_E1_UNIFORM_H
#include "SheafSystem/sec_e1_uniform.h"
#endif

#ifndef SEC_E2_UNIFORM_H
#include "SheafSystem/sec_e2_uniform.h"
#endif

#ifndef SEC_E3_UNIFORM_H
#include "SheafSystem/sec_e3_uniform.h"
#endif

#ifndef SECTION_TRAITS_H
#include "SheafSystem/section_traits.h"
#endif

#ifndef STRUCTURED_BLOCK_1D_H
#include "SheafSystem/structured_block_1d.h"
#endif

#ifndef STRUCTURED_BLOCK_2D_H
#include "SheafSystem/structured_block_2d.h"
#endif

#ifndef STRUCTURED_BLOCK_3D_H
#include "SheafSystem/structured_block_3d.h"
#endif

#ifndef UNSTRUCTURED_BLOCK_H
#include "SheafSystem/unstructured_block.h"
#endif

#include "SheafSystem/sec_e1.h"
#include "SheafSystem/sec_e2.h"
#include "SheafSystem/sec_e3.h"

#include "SheafSystem/sec_at0.h"
#include "SheafSystem/sec_at0_space.h"
#include "SheafSystem/sec_at1_space.h"
#include "SheafSystem/section_space_schema_poset.h"


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

//
// Initializes section dofs from xlb and xub.
//
void
put_bounds(sec_e1* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  // Preconditions:

  // Body:

  using namespace std;

  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // Check the bounds cts.

    /// @issue why check df(), doesn't sec_e1 ensure it is 1?

    if((xsec->schema().df() == 1) && (xlb.ct() == 1) && (xub.ct() == 1))
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
        put_dofs(xsec, lbase.i_size()+1, xlb, xub);
        lbase.detach_from_state();
      }
      else if((lbase_type_name == "point_block_1d"))
      {
        // The base space is a point_block_1d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_1d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), xlb, xub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();

  // Postconditions:

  // Exit:

  return;
}

//
// Sets the uniform coordinate dof bounds xlb, xub into section xsec.
//
void
put_bounds(sec_e1_uniform* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  if((xlb.ct() == 1) && (xub.ct() == 1))
  {
    xsec->put_bounds(xlb[0], xub[0], true);
  }
}
  
//
// Initializes section dofs from xlb and xub.
//
void
put_bounds(sec_e2* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  // Preconditions:

  // Body:

  using namespace std;

  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // Check the bounds cts.

    /// @issue why check df(), doesn't sec_e2 ensure it is 2?

    if((xsec->schema().df() == 2) && (xlb.ct() == 2) && (xub.ct() == 2))
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
        put_dofs(xsec, lbase.i_size()+1, lbase.j_size()+1, xlb, xub);
        lbase.detach_from_state();
      }
      else if(lbase_type_name == "point_block_2d")
      {
        // The base space is a point_block_2d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_2d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), lbase.j_size(), xlb, xub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();

  // Postconditions:

  // Exit:

  return;
}

//
// Sets the uniform coordinate dof bounds xlb, xub into section xsec.
//
void
put_bounds(sec_e2_uniform* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  if((xlb.ct() == 2) && (xub.ct() == 2))
  {
    xsec->put_bounds(xlb, xub, true);
  }
}
  
//
// Initializes section dofs from xlb and xub.
//
void
put_bounds(sec_e3* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  // Preconditions:

  // Body:

  using namespace std;

  xsec->get_read_write_access(true);

  // Set the coordinate dofs from the bounds if we know how.

  base_space_poset& lbase_host = xsec->schema().host()->base_space();
  pod_index_type lbase_id = xsec->schema().base_space_id();

  if(lbase_host.is_jim(lbase_id, false))
  {
    // The base space is a jim, may be able to set the dofs.
    // check the bounds.

    if((xsec->schema().df() == 3) && (xlb.ct() == 3) && (xub.ct() == 3))
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
        put_dofs(xsec, lbase.i_size()+1, lbase.j_size()+1, lbase.k_size()+1, xlb, xub);
        lbase.detach_from_state();
      }
      else if(lbase_type_name == "point_block_3d")
      {
        // The base space is a point_block_3d and
        // the user has provided appropriate bounds.
        // We know how to set the coordinates from the bounds.

        point_block_3d lbase(&lbase_host, lbase_id);
        put_dofs(xsec, lbase.i_size(), lbase.j_size(), lbase.k_size(), xlb, xub);
        lbase.detach_from_state();
      }
    }
  }
  else
  {
    // The base space is not a jim, don't know how to set the dofs.
  }

  xsec->release_access();

  // Postconditions:

  // Exit:

  return;
}

//
// Sets the uniform coordinate dof bounds xlb, xub into section xsec.
//
void
put_bounds(sec_e3_uniform* xsec,
	   block<int> xbase_index_ubs,
	   block<sec_vd_value_type> xlb,
	   block<sec_vd_value_type> xub)
{
  if((xlb.ct() == 3) && (xub.ct() == 3))
  {
    xsec->put_bounds(xlb, xub, true);
  }
}
  
} // unnamed namespace


namespace fields
{

///
/// Finds or creates the base space specified by xbase_path.
///
template <typename base_type>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                base_type& xresult)
{
  // Preconditions:

  require(xns.state_is_read_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true));


  // Body:

  xresult.attach_to_state(&xns, xbase_path);

  // Get

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for structured_lbock_1d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_1d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 1);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &structured_block_1d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost, xbase_index_ubs[0], true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for structured_block_2d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_2d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 2);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &structured_block_2d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost, xbase_index_ubs[0], xbase_index_ubs[1], true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for structured_block_3d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                structured_block_3d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 3);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &structured_block_3d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost,
                      xbase_index_ubs[0],
                      xbase_index_ubs[1],
                      xbase_index_ubs[2],
                      true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for point_block_1d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_1d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 1);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &point_block_1d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost, xbase_index_ubs[0], true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for point_block_2d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_2d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 2);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &point_block_2d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost, xbase_index_ubs[0], xbase_index_ubs[1], true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}

///
/// Finds or creates the base space specified by xbase_path;
/// specialization for point_block_3d.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                point_block_3d& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) || xbase_index_ubs.ct() >= 3);

  // Body:

  if(xns.contains_poset_member(xbase_path, true))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, false))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &point_block_3d::standard_host(xns, xbase_path.poset_name(), false);
    }

    xresult.new_state(lhost,
                      xbase_index_ubs[0],
                      xbase_index_ubs[1],
                      xbase_index_ubs[2],
                      true);
    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}


///
/// Finds or creates the base space specified by xbase_path;
/// specialization for unstructured_block.
///
template <>
void
make_base_space(fiber_bundles_namespace& xns,
                const poset_path& xbase_path,
                const wsv_block<int>& xbase_index_ubs,
                poset_path& xlocal_cell_prototype_path,
                unstructured_block& xresult)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(xns.contains_poset_member(xbase_path, true) ||
          ((1 <= xbase_index_ubs.ct()) && (xbase_index_ubs.ct() <= 3)));

  // Body:

  using namespace std;

  if(xns.contains_poset_member(xbase_path))
  {
    xresult.attach_to_state(&xns, xbase_path);
  }
  else
  {
    int ldb = xbase_index_ubs.ct();

    base_space_poset* lhost;

    if(xns.contains_poset(xbase_path, true))
    {
      lhost = dynamic_cast<base_space_poset*>(&xns.member_poset(xbase_path, false));
    }
    else
    {
      lhost = &unstructured_block::standard_host(xns, xbase_path.poset_name(), ldb, false);
    }

    string lposet_name(base_space_member::prototypes_poset_name());

    switch(ldb)
    {
    case 0:
      {
        int lpt_ct = 1;
        for(int i=0; i< xbase_index_ubs.ct(); ++i)
        {
          lpt_ct *= xbase_index_ubs.ct();
        }
        xresult.new_state(lhost, xlocal_cell_prototype_path, lpt_ct, true);
      }
      break;
    case 1:
      if(xlocal_cell_prototype_path.empty())
      {
        xlocal_cell_prototype_path.put_poset_name(lposet_name);
        xlocal_cell_prototype_path.put_member_name("segment_complex");
      }

      xresult.new_state(lhost,
                        xlocal_cell_prototype_path,
                        xbase_index_ubs[0],
                        true);
      break;
    case 2:
      if(xlocal_cell_prototype_path.empty())
      {
        xlocal_cell_prototype_path.put_poset_name(lposet_name);
        xlocal_cell_prototype_path.put_member_name("quad_nodes");
      }
      xresult.new_state(lhost,
                        xlocal_cell_prototype_path,
                        xbase_index_ubs[0],
                        xbase_index_ubs[1],
                        true);
      break;
    case 3:
      if(xlocal_cell_prototype_path.empty())
      {
        xlocal_cell_prototype_path.put_poset_name(lposet_name);
        xlocal_cell_prototype_path.put_member_name("hex_nodes");
      }
      xresult.new_state(lhost,
                        xlocal_cell_prototype_path,
                        xbase_index_ubs[0],
                        xbase_index_ubs[1],
                        xbase_index_ubs[2],
                        true);
      break;
    default:
      post_fatal_error_message("Unsupported base dimension");
      break;
    }

    xresult.put_name(xbase_path.member_name(), true, true);
  }

  // Postconditions:

  ensure(xns.contains_poset_member(xbase_path, true));

  // Exit:

  return;
}


//=============================================================================
// FIELD_FACTORY_2 FACET
//=============================================================================

// PUBLIC MEMBERS

template <typename coord_type, typename prop_type, typename base_type>
field_factory_2<coord_type, prop_type, base_type>::
field_factory_2()
{

  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

  return;
}


template <typename coord_type, typename prop_type, typename base_type>
field_factory_2<coord_type, prop_type, base_type>::
~field_factory_2()
{
  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}


template <typename coord_type, typename prop_type, typename base_type>
typename field_traits<prop_type>::field_type*
field_factory_2<coord_type, prop_type, base_type>::
new_field(fiber_bundles_namespace& xns,
          const poset_path& xbase_path,
          const poset_path& xcoord_path,
          const poset_path& xprop_path,
	  bool xauto_access)
{
  field_type* result;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(unexecutable("base exists or index_ubs compatible with base_type"));

  require(xcoord_path.full());
  require(xns.path_is_auto_read_write_accessible<typename coord_type::host_type>(xcoord_path.poset_name(), xauto_access));
  
  require(xprop_path.full());
  require(xns.path_is_auto_read_write_accessible<typename prop_type::host_type>(xprop_path.poset_name(), xauto_access));

  // Body:

  using namespace std;

  if(xauto_access)
  {
    xns.get_read_write_access();
  }

  // Find or create the base space.

  poset_path llocal_cell_prototype_path(_local_cell_prototype_path);

  if(section_traits<coord_type>::must_use_standard_base_type())
  {
    typename section_traits<coord_type>::standard_base_type lbase;
    make_base_space(xns,
                    xbase_path,
                    _base_index_ubs,
                    llocal_cell_prototype_path,
                    lbase);
    lbase.detach_from_state();
  }
  else
  {
    base_type lbase;
    make_base_space(xns,
                    xbase_path,
                    _base_index_ubs,
                    llocal_cell_prototype_path,
                    lbase);
    lbase.detach_from_state();
  }

  // Find the coordinates section space.

  typename coord_type::host_type& lcoords_host =
    xns.member_poset<typename coord_type::host_type>(xcoord_path, false);

  // Find or create the coordinate section.

  string lcoord_name(xcoord_path.member_name());

  coord_type lcoords;
  if(lcoords_host.contains_member(lcoord_name))
  {
    lcoords_host.get_read_access();
    lcoords.attach_to_state(&lcoords_host, lcoord_name);
    lcoords_host.release_access();
  }
  else
  {
    lcoords.new_jim_state(&lcoords_host);
    lcoords.put_name(lcoord_name, true, true);
    put_bounds(&lcoords, _base_index_ubs, _coord_lb, _coord_ub);
  }
  
  // Find property section space.

  typename prop_type::host_type& lprop_host =
    xns.member_poset<typename prop_type::host_type>(xprop_path, false);

  // Find or create the property section.

  string lprop_name(xprop_path.member_name());

  prop_type lprop;
  if(lprop_host.contains_member(lprop_name))
  {
    lprop_host.get_read_access();
    lprop.attach_to_state(&lprop_host, lprop_name);
    lprop_host.release_access();
  }
  else
  {
    lprop.new_jim_state(&lprop_host);
    lprop.put_name(lprop_name, true, true);
  }

  // Create the field.

  result = new field_type(xns, lcoords.path(), lprop.path(), true);

  // Clean up.

  lcoords.detach_from_state();
  lprop.detach_from_state();

  if(xauto_access)
  {
    xns.release_access();
  }

  // Postconditions:

  ensure(result->base_space().path(true) == xbase_path);
  ensure(result->coordinates().path(true) == xcoord_path);
  ensure(result->property().path(true) == xprop_path);

  // Exit:

  return result;
}

template <typename coord_type, typename prop_type, typename base_type>
typename field_traits<prop_type>::field_type*
field_factory_2<coord_type, prop_type, base_type>::
standard_field(fiber_bundles_namespace& xns,
	       const poset_path& xbase_path,
	       const std::string& xcoord_name,
	       const std::string& xprop_name,
	       bool xauto_access)
{
  field_type* result;

  // Preconditions:

  require(xns.state_is_auto_read_write_accessible(xauto_access));

  require(xbase_path.full());
  require(unexecutable("base exists or index_ubs compatible with base_type"));

  require(poset_path::is_valid_name(xcoord_name));
  require(poset_path::is_valid_name(xprop_name));

  require(coord_rep_path().empty() || coord_rep_path().full());
  require(coord_rep_path().empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(coord_rep_path(), xauto_access));  

  require(coord_fiber_suffix().empty() || poset_path::is_valid_name(coord_fiber_suffix()));
  require(coord_type::fiber_type::template standard_host_is_available<typename coord_type::fiber_type>(xns, coord_fiber_suffix(), xauto_access));

  require(coord_section_suffix().empty() || poset_path::is_valid_name(coord_section_suffix()));
  require(coord_type::template standard_host_is_available<coord_type>(xns, xbase_path, coord_rep_path(), coord_section_suffix(), coord_fiber_suffix(), xauto_access));

  require(prop_rep_path().empty() || prop_rep_path().full());
  require(prop_rep_path().empty() || xns.path_is_auto_read_accessible<sec_rep_descriptor_poset>(prop_rep_path(), xauto_access));  

  require(prop_fiber_suffix().empty() || poset_path::is_valid_name(prop_fiber_suffix()));
  require(prop_type::fiber_type::template standard_host_is_available<typename prop_type::fiber_type>(xns, prop_fiber_suffix(), xauto_access));

  require(prop_section_suffix().empty() || poset_path::is_valid_name(prop_section_suffix()));
  require(prop_type::template standard_host_is_available<prop_type>(xns, xbase_path, prop_rep_path(), prop_section_suffix(), prop_fiber_suffix(), xauto_access));

  // Body:

  if(xauto_access)
  {
    xns.get_read_write_access();
  }

  // Find or create the base space.

  poset_path llocal_cell_prototype_path(_local_cell_prototype_path);

  if(section_traits<coord_type>::must_use_standard_base_type())
  {
    typename section_traits<coord_type>::standard_base_type lbase;
    make_base_space(xns,
                    xbase_path,
                    _base_index_ubs,
                    llocal_cell_prototype_path,
                    lbase);
    lbase.detach_from_state();
  }
  else
  {
    base_type lbase;
    make_base_space(xns,
                    xbase_path,
                    _base_index_ubs,
                    llocal_cell_prototype_path,
                    lbase);
    lbase.detach_from_state();
  }

  // Find or create the standard coordinates section space.

  typename coord_type::host_type& lcoords_host =
    coord_type::standard_host(xns,
			      xbase_path,
			      coord_rep_path(),
			      coord_section_suffix(),
			      coord_fiber_suffix(),
			      false);

  // Find or create the coordinate section.

  coord_type lcoords;
  if(lcoords_host.contains_member(xcoord_name))
  {
    lcoords_host.get_read_access();
    lcoords.attach_to_state(&lcoords_host, xcoord_name);
    lcoords_host.release_access();
  }
  else
  {
    lcoords.new_jim_state(&lcoords_host);
    lcoords.put_name(xcoord_name, true, true);
    put_bounds(&lcoords, _base_index_ubs, _coord_lb, _coord_ub);
  }
  
  // Find or create the standard property section space.

  typename prop_type::host_type& lprop_host =
    prop_type::standard_host(xns,
			     xbase_path,
			     prop_rep_path(),
			     prop_section_suffix(),
			     prop_fiber_suffix(),
			     false);

  // Find or create the property section.

  prop_type lprop;
  if(lprop_host.contains_member(xprop_name))
  {
    lprop_host.get_read_access();
    lprop.attach_to_state(&lprop_host, xprop_name);
    lprop_host.release_access();
  }
  else
  {
    lprop.new_jim_state(&lprop_host);
    lprop.put_name(xprop_name, true, true);
  }

  // Create the field.

  result = new field_type(xns, lcoords.path(), lprop.path(), true);

  // Clean up.

  lcoords.detach_from_state();
  lprop.detach_from_state();

  if(xauto_access)
  {
    xns.release_access();
  }

  // Postconditions:

  ensure(result->base_space().path(true) == xbase_path);

  ensure(result->coordinates().path(true).poset_name() ==
	 coord_type::template standard_host_path<coord_type>(xbase_path, coord_rep_path(), coord_section_suffix(), coord_fiber_suffix()).poset_name());
  ensure(result->coordinates().path(true).member_name() == xcoord_name);
  
  ensure(result->property().path(true).poset_name() ==
	 prop_type::template standard_host_path<prop_type>(xbase_path, prop_rep_path(), prop_section_suffix(), prop_fiber_suffix()).poset_name());
  ensure(result->property().path(true).member_name() == xprop_name);

  // Exit:

  return result;
}

// =============================================================================
// BASE SPACE FACET
// =============================================================================

// PUBLIC MEMBERS

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
base_schema_path()
{
  return _base_schema_path;
}

template <typename coord_type, typename prop_type, typename base_type>
wsv_block<int>&
field_factory_2<coord_type, prop_type, base_type>::
base_index_ubs()
{
  return _base_index_ubs;
}

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
local_cell_prototype_path()
{
  return _local_cell_prototype_path;
}



// =============================================================================
// COORDINATES SECTION FACET
// =============================================================================

// PUBLIC MEMBERS

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
coord_rep_path()
{
  return _coord_rep_path;
}

template <typename coord_type, typename prop_type, typename base_type>
std::string&
field_factory_2<coord_type, prop_type, base_type>::
coord_fiber_suffix()
{
  return _coord_fiber_suffix;
}

template <typename coord_type, typename prop_type, typename base_type>
std::string&
field_factory_2<coord_type, prop_type, base_type>::
coord_section_suffix()
{
  return _coord_section_suffix;
}

template <typename coord_type, typename prop_type, typename base_type>
wsv_block<sec_vd_value_type>&
field_factory_2<coord_type, prop_type, base_type>::
coord_lb()
{
  return _coord_lb;
}

template <typename coord_type, typename prop_type, typename base_type>
wsv_block<sec_vd_value_type>&
field_factory_2<coord_type, prop_type, base_type>::
coord_ub()
{
  return _coord_ub;
}


// =============================================================================
// PROPERTY SECTION FACET
// =============================================================================

// PUBLIC MEMBERS

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
prop_rep_path()
{
  return _prop_rep_path;
}

template <typename coord_type, typename prop_type, typename base_type>
std::string&
field_factory_2<coord_type, prop_type, base_type>::
prop_fiber_suffix()
{
  return _prop_fiber_suffix;
}

template <typename coord_type, typename prop_type, typename base_type>
std::string&
field_factory_2<coord_type, prop_type, base_type>::
prop_section_suffix()
{
  return _prop_section_suffix;
}

template <typename coord_type, typename prop_type, typename base_type>
wsv_block<sec_vd_value_type>&
field_factory_2<coord_type, prop_type, base_type>::
prop_lb()
{
  return _prop_lb;
}

template <typename coord_type, typename prop_type, typename base_type>
wsv_block<sec_vd_value_type>&
field_factory_2<coord_type, prop_type, base_type>::
prop_ub()
{
  return _prop_ub;
}


// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================
 
} // namespace fields


#endif // FIELD_FACTORY_2_IMPL_H
