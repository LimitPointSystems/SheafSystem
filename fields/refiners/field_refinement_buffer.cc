
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class field_refinement_buffer

#include "field_refinement_buffer.h"

#include "assert_contract.h"
#include "array_section_dof_map.h"
#include "base_space_member.h"
#include "base_space_poset.h"
#include "binary_section_space_schema_member.h"
#include "postorder_iterator.h"
#include "local_field_refiner.h"
#include "section_evaluator.h"
#include "sec_ed_invertible.h"
#include "sec_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// CANONICAL FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
fields::field_refinement_buffer::
invariant() const
{
  bool result = true;

  invariance(target.same_evaluation());

  // Exit

  return result;
}


// ===========================================================
// FIELD_REFINEMENT_BUFFER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::field_refinement_buffer::
field_refinement_buffer(const field_vd& xsource,
                        field_vd& xtarget,
                        const block<scoped_index>& xcoord_disc_ids,
                        const block<scoped_index>& xprop_disc_ids,
                        int xdepth_ub)
    :  source(xsource),
    target(xtarget),
    coord_disc_ids(xcoord_disc_ids),
    prop_disc_ids(xprop_disc_ids),
    has_been_pushed(xtarget.base_space().host()->member_index_ub().pod()),
    base_space(dynamic_cast<base_space_poset*>(xtarget.base_space().host())),
    evaluation(xtarget.coordinates().schema().evaluation()),
    coord_discretization(xtarget.coordinates().schema().discretization()),
    prop_discretization(xtarget.property().schema().discretization()),
    coord_dofs(xcoord_disc_ids.ub()*xtarget.dc()),
    coord_value(xtarget.dc()),
    prop_dofs(xprop_disc_ids.ub()*xtarget.dp()),
    prop_value(xtarget.dp()),
    source_prop_value(xsource.dp()),
    local_coords(xtarget.db()),
    local_coords2(xtarget.db()),
    same_discretization(xtarget.same_discretization()),
    depth_ub(xdepth_ub),
    parent_prop_dofs(new block<sec_vd_dof_type>[xdepth_ub]),
    parent_prop_evaluator(new section_evaluator*[xdepth_ub]),
    parent_subzone_id(new int[xdepth_ub])

{
  // Preconditions:

  require(xsource.state_is_read_accessible());
  require(xtarget.state_is_read_accessible());
  require(xtarget.name_space().state_is_read_accessible());
  require(xsource.dc() == xtarget.dc());
  require(xsource.dp() == xtarget.dp());
  require(xtarget.same_evaluation());

  // Body:

  /// @issue Assuming that the discretization id space is a mutable_index_space.
  /// This is true because refinement is currently only implemented on
  /// unstructured blocks (or potentially zone node blocks).  Once zone
  /// node blocks support binary id spaces, this assumption is not true.
  /// See bug 0000381.

  vertices_id_space       = &base_space->vertices().id_space();
  elements_id_space       = &base_space->elements().id_space();
  coord_disc_seq_id_space = reinterpret_cast<mutable_index_space_handle*>(&xtarget.coordinates().schema().discretization_id_space());
  prop_disc_seq_id_space  = reinterpret_cast<mutable_index_space_handle*>(&xtarget.property().schema().discretization_id_space());

  coord_value.set_ct(xtarget.dc());
  prop_value.set_ct(xtarget.dp());

  for(size_type i=0; i<depth_ub; ++i)
  {
    parent_prop_dofs[i].reserve(prop_dofs.ub());
  }

  // Postconditions:

  ensure(invariant());

  return;
}


fields::field_refinement_buffer::
field_refinement_buffer(field_vd& xtarget,
                        const block<scoped_index>& xcoord_disc_ids,
                        const block<scoped_index>& xprop_disc_ids,
                        int xdepth_ub)
    :  source(xtarget),
    target(xtarget),
    coord_disc_ids(xcoord_disc_ids),
    prop_disc_ids(xprop_disc_ids),
    has_been_pushed(xtarget.base_space().host()->member_index_ub().pod()),
    base_space(dynamic_cast<base_space_poset*>(xtarget.base_space().host())),
    evaluation(xtarget.coordinates().schema().evaluation()),
    coord_discretization(xtarget.coordinates().schema().discretization()),
    prop_discretization(xtarget.property().schema().discretization()),
    coord_dofs(xcoord_disc_ids.ub()*xtarget.dc()),
    coord_value(xtarget.dc()),
    prop_dofs(xprop_disc_ids.ub()*xtarget.dp()),
    prop_value(xtarget.dp()),
    source_prop_value(xtarget.dp()),
    local_coords(xtarget.db()),
    local_coords2(xtarget.db()),
    same_discretization(xtarget.same_discretization()),
    depth_ub(xdepth_ub),
    parent_prop_dofs(new block<sec_vd_dof_type>[xdepth_ub]),
    parent_prop_evaluator(new section_evaluator*[xdepth_ub]),
    parent_subzone_id(new int[xdepth_ub])

{
  // Preconditions:

  require(xtarget.state_is_read_accessible());
  require(xtarget.name_space().state_is_read_accessible());
  require(xtarget.same_evaluation());

  // Body:

  /// @issue Assuming that the discretization id map is a mutable_index_map.
  /// This is true because refinement is currently only implemented on
  /// unstructured blocks (or potentially zone node blocks).  Once zone
  /// node blocks support binary id spaces, this assumption is not true.
  /// See bug 0000381.

  vertices_id_space       = &base_space->vertices().id_space();
  elements_id_space       = &base_space->elements().id_space();
  coord_disc_seq_id_space = reinterpret_cast<mutable_index_space_handle*>(&xtarget.coordinates().schema().discretization_id_space());
  prop_disc_seq_id_space  = reinterpret_cast<mutable_index_space_handle*>(&xtarget.property().schema().discretization_id_space());

  coord_value.set_ct(xtarget.dc());
  prop_value.set_ct(xtarget.dp());

  for(size_type i=0; i<depth_ub; ++i)
  {
    parent_prop_dofs[i].reserve(prop_dofs.ub());
  }

  // Mark all existing disc members as already evaluated.

  postorder_iterator litr(target.base_space(), prop_discretization, DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    has_been_pushed.put(litr.index().pod(), true);

    litr.next();
  }


  // Postconditions:

  ensure(invariant());

  return;
}


fields::field_refinement_buffer::
~field_refinement_buffer()
{
  // Preconditions:


  // Body:

  delete [] parent_prop_dofs;
  delete [] parent_prop_evaluator;
  delete [] parent_subzone_id;

  // Postconditions:

  // Exit:

  return;
}


void
fields::field_refinement_buffer::
gather_coordinate_dofs()
{
  // Preconditions:

  require(target.state_is_read_accessible());

  // Indexing below only correct for binary schema.
  /// @todo revise when ternary schema are supported.

  require(dynamic_cast<binary_section_space_schema_member*>(&target.coordinates().schema()) != 0);

  // Body:

  size_type ldc = target.dc();
  size_type ldofs_ct = 0;
  size_type ldisc_ct = coord_disc_ids.ct();
  size_type ldofs_ub = ldisc_ct*ldc;
  coord_dofs.reserve(ldofs_ub);
  sec_vd_dof_type* ldofs = coord_dofs.base();

  sec_vd& lcoords = target.coordinates();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    lcoords.get_fiber(coord_disc_ids[i], ldofs,
		      ldofs_ub*sizeof(sec_vd_dof_type), false);

    ldofs += ldc;
    ldofs_ct += ldc;
    ldofs_ub -= ldc;
  }

  coord_dofs.set_ct(ldofs_ct);

  // Postconditions:

  ensure(coord_dofs.ct() == coord_disc_ids.ct()*target.dc());

  // Exit:

  return;
}


void
fields::field_refinement_buffer::
gather_property_dofs()
{
  // Preconditions:

  require(target.state_is_read_accessible());

  // Indexing below only correct for binary schema.
  /// @todo revise when ternary schema are supported.

  require(dynamic_cast<binary_section_space_schema_member*>(&target.property().schema()) != 0);

  // Body:

  size_type ldp = target.dp();
  size_type ldofs_ct = 0;
  size_type ldisc_ct = prop_disc_ids.ct();
  size_type ldofs_ub = ldisc_ct*ldp;
  prop_dofs.reserve(ldofs_ub);
  sec_vd_dof_type* ldofs = prop_dofs.base();

  sec_vd& lprop = target.property();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    lprop.get_fiber(prop_disc_ids[i], ldofs,
		    ldofs_ub*sizeof(sec_vd_dof_type), false);

    ldofs += ldp;
    ldofs_ct += ldp;
    ldofs_ub -= ldp;
  }

  prop_dofs.set_ct(ldofs_ct);

  // Postconditions:

  ensure(prop_dofs.ct() == prop_disc_ids.ct()*target.dp());

  // Exit:

  return;
}

void
fields::field_refinement_buffer::
push_prop_dofs()
{
  // Preconditions:

  require(target.same_evaluation());
  require(coord_value.ub() >= target.dc());

  // Body:

  // Make sure has_been_pushed has enough capacity for
  // any changes we've made to the base space.

  has_been_pushed.extend_to(base_space->member_index_ub().pod());

  size_type ldc = target.dc();

  size_type ldisc_ct =  prop_disc_ids.ct();
  for(size_type i=0; i<ldisc_ct; ++i)
  {
    scoped_index ldisc_id = prop_disc_ids[i];

    if(!has_been_pushed[ldisc_id.pod()])
    {
      // This property disc member has not been pushed
      // from the source yet; do it now.

      evaluate_source_at_disc(i);

      // Put the dofs in the property section.

      reserve_prop_fiber(ldisc_id);

      target.property().put_fiber(ldisc_id,
				  source_prop_value.base(),
				  source_prop_value.ct()*sizeof(sec_vd_dof_type),
				  false);

      // Mark the disc mbr as pushed.

      has_been_pushed.put(ldisc_id.pod(), true);
    }
  }

  // Postconditions:

  ensure_for_all(i, 0, prop_disc_ids.ct(), has_been_pushed[prop_disc_ids[i].pod()]);

  // Exit:

  return;
}

void
fields::field_refinement_buffer::
refine_prop_dofs(local_field_refiner* xrefiner)
{
  // Preconditions:

  require(xrefiner != 0);
  require(depth > 0);
  require(parent_subzone_id[depth-1] < xrefiner->refined_zone_ct());

  // Body:

  int lparent_depth = depth - 1;
  section_evaluator* lparent_prop_evaluator = parent_prop_evaluator[lparent_depth];
  block<sec_vd_dof_type>& lparent_prop_dofs = parent_prop_dofs[lparent_depth];
  int lparent_subzone_id =  parent_subzone_id[lparent_depth];
  const chart_point_coord_type* lmap =
    xrefiner->local_coordinates_map(lparent_subzone_id);

  sec_vd& lprop = target.property();

  // Make sure has_been_pushed has enough capacity for
  // any changes we've made to the base space.

  has_been_pushed.extend_to(base_space->member_index_ub().pod());

  size_type ldisc_ct =  prop_disc_ids.ct();
  for(size_type i=0; i<ldisc_ct; ++i)
  {
    scoped_index ldisc_id = prop_disc_ids[i];
    

    if(!has_been_pushed[ldisc_id.pod()])
    {
      // This property disc member has not been evaluated
      // from the parent zone yet; do it now.

      // Get the local coordinates of the disc member in the current zone

      prop_evaluator->local_coordinates(i, local_coords2);

      // Map the local coordinates to the local coordinates of the parent zone.

      // Affine transformation u'[i] = T[i][j]*u[j] + T[i][db];
      // with sum convention over  0 <= j < db.

      size_type lmap_index = 0;
      size_type ldb = local_coords2.ct();
      for(size_type k = 0; k<ldb; ++k)
      {
        local_coords[k] = 0.0;
        for(size_type l = 0; l<ldb; ++l)
        {
          local_coords[k] += lmap[lmap_index++]*local_coords2[l];
        }

        local_coords[k] += lmap[lmap_index++];
      }

      // Evaluate the property in the parent zone.

      lparent_prop_evaluator->value_at_coord(lparent_prop_dofs,
                                             local_coords,
                                             prop_value);

      // Make sure the property dof map has enough capacity for the new point.

      reserve_prop_fiber(ldisc_id);

      // Put the value into the property section.

      lprop.put_fiber(ldisc_id, prop_value.base(), prop_value.ct()*sizeof(sec_vd_dof_type), false);

      // Mark the disc mbr as pushed.

      has_been_pushed.put(ldisc_id.pod(), true);
    }
  }

  // We're finished with this zone; increment the subzone id in the parent

  parent_subzone_id[lparent_depth]++;

  // Postconditions:

  ensure_for_all(i, 0, prop_disc_ids.ct(), has_been_pushed[prop_disc_ids[i].pod()]);

  // Exit:

  return;
}

void
fields::field_refinement_buffer::
evaluate_at_center()
{
  // Preconditions:


  // Body:

  // Set the local coordinates to the center of the zone.

  prop_evaluator->center(local_coords);

  // Evaluate property at center.

  prop_evaluator->value_at_coord(prop_dofs, local_coords, prop_value);

  // Evaluate the coordinates at the center
  /// @issue requires same evaluation subposet.

  coord_evaluator->value_at_coord(coord_dofs, local_coords, coord_value);

  // Evaluate the source field at the global coordinates of the center.

  source.property_at_coordinates(coord_value, source_prop_value);

  // Postconditions:


  // Exit:

  return;
}

void
fields::field_refinement_buffer::
evaluate_source_at_disc(size_type xi)
{
  // Preconditions:

  require(target.state_is_read_accessible());
  require(unexecutable("dofs have been gathered for this zone"));


  // Body:

  size_type ldc = target.dc();

  if(same_discretization)
  {
    // Property dofs co-located with coordinate dofs.
    // Don't have to evaluate the coordinates, just grab dofs.

    /// @issue requires coord dofs are coord values.

    for(size_type j=0; j<ldc; ++j)
    {
      coord_value[j] = coord_dofs[xi*ldc + j];
    }
    coord_value.set_ct(ldc);
  }
  else
  {
    // Must evaluate the global coordinate section at
    // the local coordinates of the property disc member.

    // Set the local coordinates to the position of the disc member.

    prop_evaluator->local_coordinates(xi, local_coords);

    // Evaluate the global coordinates at the local coordinates.
    /// @issue requires same evaluation subposet.

    coord_evaluator->value_at_coord(coord_dofs, local_coords, coord_value);
  }

  // Evaluate the source field at the global coordinates of
  // the property disc member..

  source.property_at_coordinates(coord_value, source_prop_value);

  // Postconditions:


  // Exit:

  return;
}


void
fields::field_refinement_buffer::
save_parent()
{
  // Preconditions:

  require(depth < depth_ub);

  // Body:

  parent_prop_dofs[depth] = prop_dofs;
  parent_prop_evaluator[depth] = prop_evaluator;
  parent_subzone_id[depth] = 0;

  // Postconditions:

  ensure(unexecutable(parent_prop_dofs[depth] == prop_dofs));
  ensure(parent_prop_evaluator[depth] == prop_evaluator);
  ensure(parent_subzone_id[depth] == 0);

  // Exit:

  return;
}

void
fields::field_refinement_buffer::
reserve_coord_fiber(const scoped_index& xdisc_id)
{
  // Preconditions:

  require(dynamic_cast<array_section_dof_map*>(&target.coordinates().dof_map(true)) != 0);
  require(coord_disc_seq_id_space->contains_hub(xdisc_id));
  
  // Body:

  pod_index_type ldisc_id = coord_disc_seq_id_space->pod(xdisc_id);
  
  array_section_dof_map* lcoord_dof_map = 
    dynamic_cast<array_section_dof_map*>(&target.coordinates().dof_map(true));

  lcoord_dof_map->reserve_fiber(ldisc_id);

  // Postconditions:

  ensure(unexecutable("coord dof map has enough capacity for the fiber associated with xdisc_id"));
  
  // Exit:

  return;
}

void
fields::field_refinement_buffer::
reserve_prop_fiber(const scoped_index& xdisc_id)
{
  // Preconditions:

  require(dynamic_cast<array_section_dof_map*>(&target.property().dof_map(true)) != 0);
  require(prop_disc_seq_id_space->contains_hub(xdisc_id));
  
  // Body:

  pod_index_type ldisc_id = prop_disc_seq_id_space->pod(xdisc_id);
  
  array_section_dof_map* lcoord_dof_map = 
    dynamic_cast<array_section_dof_map*>(&target.property().dof_map(true));

  lcoord_dof_map->reserve_fiber(ldisc_id);

  // Postconditions:

  ensure(unexecutable("coord dof map has enough capacity for the fiber associated with xdisc_id"));
  
  // Exit:

  return;
}

// PRIVATE MEMBER FUNCTIONS

fields::field_refinement_buffer::
field_refinement_buffer()
    : source(*(new field_vd())), // All these inits just to keep compiler happy.
    target(*(new field_vd())),
    coord_disc_ids(*(new block<scoped_index>())),
    prop_disc_ids(*(new block<scoped_index>())),
    has_been_pushed(*(new zn_to_bool())),
    base_space(0),
    evaluation(*(new subposet())),
    coord_discretization(*(new subposet())),
    prop_discretization(*(new subposet()))
{

  // Preconditions:


  // Body:

  // Above initializations just to keep compiler happy.
  // This routine should never be called.

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


fields::field_refinement_buffer::
field_refinement_buffer(const field_refinement_buffer& xother)
    : source(xother.source), // All these inits just to keep compiler happy.
    target(xother.target),
    coord_disc_ids(xother.coord_disc_ids),
    prop_disc_ids(xother.prop_disc_ids),
    has_been_pushed(xother.has_been_pushed),
    base_space(xother.base_space),
    evaluation(xother.evaluation),
    coord_discretization(xother.coord_discretization),
    prop_discretization(xother.prop_discretization)
{

  // Preconditions:

  // Body:

  // The above initializations just to make compiler happy.
  // If we want to enable copy construction, just delete this routine
  // and the declaration in the .h file; default memberwise copy
  // construction will do fine.

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}



// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================

