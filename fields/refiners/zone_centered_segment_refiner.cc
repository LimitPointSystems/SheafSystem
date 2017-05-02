
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
/// Implementation for class zone_centered_segment_refiner

#include "SheafSystem/zone_centered_segment_refiner.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_poset.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/block.impl.h"
#include "SheafSystem/field_refinement_buffer.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/sec_ed_invertible.h"
#include "SheafSystem/field_vd.h"

using namespace std;
using namespace fields; // Workaround for MS C++ bug.

// ===========================================================
// ZONE_CENTERED_SEGMENT_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::zone_centered_segment_refiner::
zone_centered_segment_refiner(const field_refinement_policy& xpolicy)
    : local_field_refiner(xpolicy)
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());
  ensure(&policy() == &xpolicy);

  return;
}


fields::zone_centered_segment_refiner::
zone_centered_segment_refiner(const zone_centered_segment_refiner& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}


// PROTECTED MEMBER FUNCTIONS

fields::zone_centered_segment_refiner::
zone_centered_segment_refiner()
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}

void
fields::zone_centered_segment_refiner::
refine_base_space(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  // Modify the cover relation graph.

  modify_crg(xbuffer);

  // Modify the subposets.

  modify_subposets(xbuffer);

  // Put the new zones in the refined zone ids buffer

  _refined_zone_ids.set_ct(0);
  _refined_zone_ids.push_back(_new_seg_0_id);
  _refined_zone_ids.push_back(_new_seg_1_id);

  // Postconditions:

  // Exit:

  return;
}

void
fields::zone_centered_segment_refiner::
modify_crg(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;
  int lzone_depth = lbase->refinement_depth(lzone_id);
  int lnew_depth  = lzone_depth + 1;

  assertion(lzone_id.same_scope(lbase->member_hub_id_space(false)));

  /// @issue assume the lower cover of the zone
  /// contains only its standard 2 vertices.

  // Unlink the lower cover of the current zone.

  pod_index_type lpoint0_id = lbase->first_cover_member(LOWER, lzone_id.pod());
  lbase->delete_link(lzone_id.pod(), lpoint0_id);
  pod_index_type lpoint1_id = lbase->first_cover_member(LOWER, lzone_id.pod());
  lbase->delete_link(lzone_id.pod(), lpoint1_id);

  // Create a new point.

  _new_point_id = lbase->member_id(create_vertex(*lbase, lnew_depth), false);

  // Create a first new segment.

  _new_seg_0_id = lbase->member_id(create_zone(*lbase, lnew_depth), false);

  // Link the first new segment to the first point and the new point.

  lbase->new_link(_new_seg_0_id.pod(), lpoint0_id);
  lbase->new_link(_new_seg_0_id.pod(), _new_point_id.pod());

  // Link the current zone to the first new segment.

  lbase->new_link(lzone_id, _new_seg_0_id);

  // Create a second new segment.

  _new_seg_1_id = lbase->member_id(create_zone(*lbase, lnew_depth), false);

  // Link the second new segment to the new point and the second point.

  lbase->new_link(_new_seg_1_id.pod(), _new_point_id.pod());
  lbase->new_link(_new_seg_1_id.pod(), lpoint1_id);

  // Link the current zone to the second new segment.

  lbase->new_link(lzone_id.pod(), _new_seg_1_id.pod());

  // Postconditions:

  // Exit:

  return;
}

void
fields::zone_centered_segment_refiner::
modify_subposets(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);

  // Body:

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;
  subposet& lvertices = lbase->vertices();
  subposet& lelements = lbase->elements();

  // More efficient to get id spaces from buffer than directly from subposets
  // because latter uses lookup by name.

  scattered_insertion_index_space_handle* lvertices_id_space       = xbuffer.vertices_id_space;
  scattered_insertion_index_space_handle* lcoord_disc_seq_id_space = xbuffer.coord_disc_seq_id_space;
  scattered_insertion_index_space_handle* lelements_id_space       = xbuffer.elements_id_space;

  // Put the new point in the vertices subposet and extend the sequence id space.

  lvertices.insert_member(_new_point_id);
  lvertices_id_space->push_back(_new_point_id);
  lcoord_disc_seq_id_space->push_back(_new_point_id);

  // The refined zone is no longer an element;
  // remove it from the elements subposet.

  /// @issue There's subtle question here:
  /// what defines the membership of the elements subposet?
  /// For instance, is it all the triangle shaped cells, or
  /// just the finest ones that are also jims?
  /// We're following the latter definition.
  /// The elements subposet is frequently used as an evaluation
  /// subposet and we don't want non-jims showing up as evaluators.

  // When removing the member, we have to be careful to reuse its
  // sequence id, so the sequence id stays sequential.

  /// @issue is this producing some sort of efficiency problem
  /// by scattering dofs allocated on this sequence id?

  pod_index_type lseq_id = lelements_id_space->pod(lzone_id);

  lelements_id_space->remove(lzone_id, true);
  lelements.remove_member(lzone_id);

  // Put the first new segment in the elements subposet,
  // reusing the sequence id of the old segment.

  lelements.insert_member(_new_seg_0_id);
  lelements_id_space->insert(lseq_id, _new_seg_0_id);

  // Put the second new segment in the elements subposet,
  // extending the sequence id space.

  lelements.insert_member(_new_seg_1_id);
  lelements_id_space->push_back(_new_seg_1_id);

  // Postconditions:

  // Exit:

  return;
}


void
fields::zone_centered_segment_refiner::
refine_coordinates(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  // Body:

  scoped_index lzone_id = xbuffer.zone_id;

  // Set the local coordinates buffer to the center of the zone.

  xbuffer.coord_evaluator->center(xbuffer.local_coords);

  // Evaluate the global coordinates at the local coordinates.

  xbuffer.coord_evaluator->value_at_coord(xbuffer.coord_dofs,
                                          xbuffer.local_coords,
                                          xbuffer.coord_value);

  // Make sure the coordinates dof map has enough capacity for the new point.

  xbuffer.reserve_coord_fiber(_new_point_id);

  // Insert the value in the coordinates section.  

  xbuffer.target.coordinates().put_fiber(_new_point_id,
					 xbuffer.coord_value.base(),
					 xbuffer.coord_value.ct()*sizeof(sec_vd_dof_type),
					 false);

  // Postconditions:


  // Exit:

  return;
}


// PRIVATE MEMBERS

//const sheaf::size_type
//fields::zone_centered_segment_refiner::
//REFINED_ZONE_CT;


// ===========================================================
// LOCAL_FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fields::zone_centered_segment_refiner::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 1;

  // Postconditions:

  ensure(result == 1);

  // Exit:

  return result;
}


const std::string&
fields::zone_centered_segment_refiner::
zone_type_name() const
{
  // Preconditions:


  // Body:

  static const string result("segment_complex");

  // Postconditions:

  ensure(!result.empty());

  // Exit:

  return result;
}

sheaf::size_type
fields::zone_centered_segment_refiner::
refined_zone_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  result = REFINED_ZONE_CT;

  // Postconditions:

  ensure(result > 1);

  // Exit:

  return result;
}

const fiber_bundle::chart_point_coord_type*
fields::zone_centered_segment_refiner::
local_coordinates_map(size_type xi) const
{
  // Preconditions:

  require(xi < refined_zone_ct());

  // Body:

  // Affine transformation u'[i] = T[i][j]*u[j] + T[i][db];
  // with sum convention over  0 <= j < db.

  // Specifically:
  //
  // u' = a*u +b*v + c;
  // v' = d*u _e*v + f.
  //
  // map = {a, b, c, d, e, f}
  // One such map for each refined zone.

  // 2 = db*(db+1)

  static const chart_point_coord_type lmap[REFINED_ZONE_CT][2] =
    {
      {
        0.5, 0.0
      },
      {0.5, 0.5}
    };


  const chart_point_coord_type* result = lmap[xi];

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::zone_centered_segment_refiner*
fields::zone_centered_segment_refiner::
clone() const
{
  zone_centered_segment_refiner* result;

  // Preconditions:

  // Body:

  result = new zone_centered_segment_refiner();

  // Postconditions:

  ensure(result != 0);
  //  ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}

fields::zone_centered_segment_refiner&
fields::zone_centered_segment_refiner::
operator=(const local_field_refiner& xother)
{
  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return *this;
}

///
fields::zone_centered_segment_refiner&
fields::zone_centered_segment_refiner::
operator=(const zone_centered_segment_refiner& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

fields::zone_centered_segment_refiner::
~zone_centered_segment_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


bool
fields::zone_centered_segment_refiner::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:

  // Must satisfy base class invariant.

  result = result && local_field_refiner::invariant();

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  return result;
}

bool
fields::zone_centered_segment_refiner::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const zone_centered_segment_refiner*>(xother) != 0;

  // Postconditions:

  return result;

}



