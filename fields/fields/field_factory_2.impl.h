// $RCSfile: field_factory_2.impl.h,v $ $Revision: 1.18 $ $Date: 2013/03/13 00:58:55 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class field_factory_2

#ifndef FIELD_FACTORY_2_IMPL_H
#define FIELD_FACTORY_2_IMPL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FIELD_FACTORY_2_H
#include "field_factory_2.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef POINT_BLOCK_1D_H
#include "point_block_1d.h"
#endif

#ifndef POINT_BLOCK_2D_H
#include "point_block_2d.h"
#endif

#ifndef POINT_BLOCK_3D_H
#include "point_block_3d.h"
#endif

#ifndef SEC_E1_UNIFORM_H
#include "sec_e1_uniform.h"
#endif

#ifndef SEC_E2_UNIFORM_H
#include "sec_e2_uniform.h"
#endif

#ifndef SEC_E3_UNIFORM_H
#include "sec_e3_uniform.h"
#endif

#ifndef SECTION_TRAITS_H
#include "section_traits.h"
#endif

#ifndef STRUCTURED_BLOCK_1D_H
#include "structured_block_1d.h"
#endif

#ifndef STRUCTURED_BLOCK_2D_H
#include "structured_block_2d.h"
#endif

#ifndef STRUCTURED_BLOCK_3D_H
#include "structured_block_3d.h"
#endif

#ifndef UNSTRUCTURED_BLOCK_H
#include "unstructured_block.h"
#endif

#include "sec_e1.h"
#include "sec_e2.h"
#include "sec_e3.h"

#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "section_space_schema_poset.h"


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
      lhost = &xns.new_base_space<structured_block_1d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<structured_block_2d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<structured_block_3d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<point_block_1d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<point_block_2d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<point_block_3d>(xbase_path.poset_name());
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
      lhost = &xns.new_base_space<unstructured_block>(xbase_path.poset_name(),
						      "",
						      "",
						      ldb,
						      true);
    }

    string lposet_name(xns.standard_base_space_member_prototypes_poset_name());

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
          const poset_path& xprop_path)
{
  field_type* result;

  // Preconditions:

  require(xns.state_is_read_write_accessible());

  require(xbase_path.full());
  require(unexecutable("base exists or index_ubs compatible with base_type"));

  require(xcoord_path.full());
  require(xprop_path.full());

  require(!coord_fiber_schema_path().empty() ?
          xns.contains_poset_member(coord_fiber_schema_path(), false) :
          true);
  require(!prop_fiber_schema_path().empty() ?
          xns.contains_poset_member(prop_fiber_schema_path(), false) :
          true);

  // Body:


  _coord_section_space_path = xcoord_path.poset_name();
  _prop_section_space_path  = xprop_path.poset_name();

  result =
    new_field(xns, xbase_path, xcoord_path.member_name(), xprop_path.member_name());


  // Postconditions:


  // Exit:

  return result;
}

template <typename coord_type, typename prop_type, typename base_type>
typename field_traits<prop_type>::field_type*
field_factory_2<coord_type, prop_type, base_type>::
new_field(fiber_bundles_namespace& xns,
          const poset_path& xbase_path,
          const char* xcoord_name,
          const char* xprop_name)
{
  field_type* result;

  // Preconditions:

  require(precondition_of(new_field(xns, xbase_path, string(xcoord_name), string(xprop_name))));

  // Body:

  string lcoord_name(xcoord_name);
  string lprop_name(xprop_name);

  result = new_field(xns, xbase_path, lcoord_name, lprop_name);

  // Postconditions:

  ensure(postcondition_of(new_field(xns, xbase_path, string(xcoord_name), string(xprop_name))));

  // Exit:

  return result;
}

template <typename coord_type, typename prop_type, typename base_type>
typename field_traits<prop_type>::field_type*
field_factory_2<coord_type, prop_type, base_type>::
new_field(fiber_bundles_namespace& xns,
          const poset_path& xbase_path,
          const string& xcoord_name,
          const string& xprop_name)
{
  field_type* result;

  // Preconditions:

  require(xns.state_is_read_write_accessible());
  require(xbase_path.full());
  require(unexecutable("base exists or index_ubs compatible with base_type"));
  require(poset_path::is_valid_name(xcoord_name));
  require(!coord_fiber_schema_path().empty() ?
          xns.contains_poset_member(coord_fiber_schema_path(), false) :
          true);
  require(poset_path::is_valid_name(xprop_name));
  require(!prop_fiber_schema_path().empty() ?
          xns.contains_poset_member(prop_fiber_schema_path(), false) :
          true);

  // Body:

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

  // Find or create the coord section space schema.

  string lcoord_schema_name =
    coord_section_space_path().poset_name() + "_schema";

  poset_path lcoord_schema_path =
    xns.new_section_space_schema<coord_type>(lcoord_schema_name,
					     "", // xsection_space_schema_args
					     "", // xsection_space_schema_schema_path
					     coord_rep_path(),
					     xbase_path,
					     coord_fiber_path(),
					     coord_fiber_args(),
					     coord_fiber_schema_path(),
					     true);

  // Find or create the coordinates section space.

  typename coord_type::host_type& lcoords_host =
    xns.new_section_space<coord_type>(coord_section_space_path(),
				      coord_section_space_args(),
				      lcoord_schema_path,
				      true);

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
  
  // Find or create the prop section space schema.

  string lprop_schema_name =
    prop_section_space_path().poset_name() + "_schema";

  poset_path lprop_schema_path =
    xns.new_section_space_schema<prop_type>(lprop_schema_name,
					    "", // xsection_space_schema_args
					    "", // xsection_space_schema_schema_path
					    prop_rep_path(),
					    xbase_path,
					    prop_fiber_path(),
					    prop_fiber_args(),
					    prop_fiber_schema_path(),
					    true);

  // Find or create the propinates section space.

  typename prop_type::host_type& lprop_host =
    xns.new_section_space<prop_type>(prop_section_space_path(),
				     prop_section_space_args(),
				     lprop_schema_path,
				     true);

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

  // Postconditions:


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
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
coord_fiber_schema_path()
{
  return _coord_fiber_schema_path;
}

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
coord_fiber_path()
{
  return _coord_fiber_path;
}

template <typename coord_type, typename prop_type, typename base_type>
arg_list&
field_factory_2<coord_type, prop_type, base_type>::
coord_fiber_args()
{
  return _coord_fiber_args;
}

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
coord_section_space_path()
{
  return _coord_section_space_path;
}

template <typename coord_type, typename prop_type, typename base_type>
arg_list&
field_factory_2<coord_type, prop_type, base_type>::
coord_section_space_args()
{
  return _coord_section_space_args;
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
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
prop_fiber_schema_path()
{
  return _prop_fiber_schema_path;
}

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
prop_fiber_path()
{
  return _prop_fiber_path;
}

template <typename coord_type, typename prop_type, typename base_type>
arg_list&
field_factory_2<coord_type, prop_type, base_type>::
prop_fiber_args()
{
  return _prop_fiber_args;
}

template <typename coord_type, typename prop_type, typename base_type>
poset_path&
field_factory_2<coord_type, prop_type, base_type>::
prop_section_space_path()
{
  return _prop_section_space_path;
}

template <typename coord_type, typename prop_type, typename base_type>
arg_list&
field_factory_2<coord_type, prop_type, base_type>::
prop_section_space_args()
{
  return _prop_section_space_args;
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
