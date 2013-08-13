//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class edge_centered_polygon_refiner

#include "edge_centered_polygon_refiner.h"

#include "assert_contract.h"
#include "base_space_poset.h"
#include "bilinear_2d.h"
#include "block.impl.h"
#include "error_message.h"
#include "field_refinement_buffer.h"
#include "index_space_iterator.h"
#include "integrable_section_evaluator.h"
#include "linear_2d.h"
#include "sec_ed_invertible.h"
#include "std_algorithm.h"
#include "std_iostream.h"
#include "field_vd.h"

using namespace fields; // Workaround for MS C++ bug.

// #define DIAGNOSTIC_OUTPUT 1

// ===========================================================
// EDGE_CENTERED_POLYGON_REFINER FACET
// ===========================================================

// PROTECTED MEMBER FUNCTIONS

fields::edge_centered_polygon_refiner::
edge_centered_polygon_refiner(const field_refinement_policy& xpolicy)
    : local_field_refiner(xpolicy)
{
  // Preconditions:

  // Body:

  reserve_vertex_buffers();

  _zone_ctr_id.invalidate();

  // Postconditions:

  ensure(invariant());
  ensure(&policy() == &xpolicy);

  return;
}


fields::edge_centered_polygon_refiner::
edge_centered_polygon_refiner(const edge_centered_polygon_refiner& xother)
    : local_field_refiner(xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  return;
}

sheaf::size_type
fields::edge_centered_polygon_refiner::
unrefined_vertex_ct() const
{
  size_type result = 0;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}

sheaf::size_type
fields::edge_centered_polygon_refiner::
refined_vertex_ct() const
{

  // Preconditions:


  // Body:

  // Since the number of refined verteices is
  // the number of unrefined vertices plus the
  // number of edges and the numbeer of edges
  // is equal to the number of unrefined vertices,
  // the number of refined vertices is always
  // twice the number of refined vertices.

  size_type result = 2*unrefined_vertex_ct();

  // Postconditions:

  ensure(result == 2*unrefined_vertex_ct());

  // Exit:

  return result;
}

sheaf::size_type
fields::edge_centered_polygon_refiner::
edge_ct() const
{
  size_type result;

  // Preconditions:


  // Body:

  // Since every unrefined vertex is the first vertex of an edge,
  // the number of edges is always equal to the number of unrefined vertices.

  result = unrefined_vertex_ct();

  // Postconditions:

  ensure(result == unrefined_vertex_ct());

  // Exit:

  return result;
}

bool
fields::edge_centered_polygon_refiner::
is_zone_centered_refiner() const
{
  bool result = false;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return result;
}

fields::edge_centered_polygon_refiner::
edge_centered_polygon_refiner()
{
  // Preconditions:

  // Body:

  not_implemented();

  reserve_vertex_buffers();

  // Postconditions:

  ensure(invariant());

  return;
}

void
fields::edge_centered_polygon_refiner::
reserve_vertex_buffers()
{
  // Preconditions:


  // Body:

  size_type l_ub = 16; // arbitrary, will resize as needed
  _vertex_ids.reserve(l_ub);
  _is_new_vertex.reserve(l_ub);
  _vertex_pos.reserve(l_ub);

  // Postconditions:


  // Exit:

  return;
}


void
fields::edge_centered_polygon_refiner::
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

  // Postconditions:

  // Exit:

  return;
}

void
fields::edge_centered_polygon_refiner::
modify_crg(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  make_new_vertices(xbuffer);

  make_new_zones(xbuffer);

  // Postconditions:

  ensure(_refined_zone_ids.ct() == refined_zone_ct());

  // Exit:

  return;
}

void
fields::edge_centered_polygon_refiner::
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

  mutable_index_space_handle* lvertices_id_space       = xbuffer.vertices_id_space;
  mutable_index_space_handle* lcoord_disc_seq_id_space = xbuffer.coord_disc_seq_id_space;
  mutable_index_space_handle* lelements_id_space       = xbuffer.elements_id_space;

  // Put the new points in the vertices subposet and extend the sequence id space.

  for(int i=0; i < _vertex_ids.ct(); ++i)
  {
    scoped_index le_ctr = _vertex_ids[i];
    if(_is_new_vertex[i])
    {
      lvertices.insert_member(le_ctr);
      lvertices_id_space->push_back(le_ctr);
      lcoord_disc_seq_id_space->push_back(le_ctr);
    }
  }

  if(is_zone_centered_refiner())
  {
    lvertices.insert_member(_zone_ctr_id);
    lvertices_id_space->push_back(_zone_ctr_id);
    lcoord_disc_seq_id_space->push_back(_zone_ctr_id);
  }

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

  // Put the first new triangle in the elements subposet,
  // reusing the sequence id of the old triangle.

  lelements.insert_member(_refined_zone_ids[0]);
  lelements_id_space->insert(lseq_id, _refined_zone_ids[0]);

  // Put the other new triangles on the elements subposet,
  // extending the sequence id space.

  for(int i=1; i < _refined_zone_ids.ct(); ++i)
  {
    lelements.insert_member(_refined_zone_ids[i]);
    lelements_id_space->push_back(_refined_zone_ids[i]);
  }

  // Postconditions:

  // Exit:

  return;
}


void
fields::edge_centered_polygon_refiner::
refine_coordinates(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require((dynamic_cast<bilinear_2d*>(xbuffer.coord_evaluator) != 0) || 
	  (dynamic_cast<linear_2d*>(xbuffer.coord_evaluator) != 0) );

  // Body:

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;
  section_evaluator* lcoord_evaluator = xbuffer.coord_evaluator;

  /// @hack Need abstract base class for polygon section evaluators.

  bilinear_2d* lquad_evaluator = dynamic_cast<bilinear_2d*>(xbuffer.coord_evaluator);
  linear_2d* ltri_evaluator = dynamic_cast<linear_2d*>(xbuffer.coord_evaluator);

  sec_vd& lcoordinates = xbuffer.target.coordinates();

  // Vertices at edge centers:

  for(int i=0; i<edge_ct(); ++i)
  {
    // The edges are at the odd offsets in the vertex buffers.

    int le = 2*i+1;

    if(_is_new_vertex[le])
    {
      // This is a new vertex; set its coordinates.
      // Get the local coordinates:

      if(lquad_evaluator != 0)
      {
	lquad_evaluator->edge_center(i, xbuffer.local_coords);
      }
      else
      {
	ltri_evaluator->edge_center(i, xbuffer.local_coords);
      }

      // Evaluate the global coordinates at the local coordinates.

      lcoord_evaluator->value_at_coord(xbuffer.coord_dofs,
                                       xbuffer.local_coords,
                                       xbuffer.coord_value);

#ifdef DIAGNOSTIC_OUTPUT

      cout << "vertex: " << _vertex_ids[le] << endl
      << "  local coords: " << xbuffer.local_coords
      << "  global coords: " << xbuffer.coord_value
      << endl;
#endif

      // Make sure the coordinates dof map has enough capacity for the new point.

      xbuffer.reserve_coord_fiber(_vertex_ids[le]);

      // Insert the value in the coordinates section.

      lcoordinates.put_fiber(_vertex_ids[le],
			     xbuffer.coord_value.base(),
			     xbuffer.coord_value.ct()*sizeof(sec_vd_dof_type),
			     false);
    }
  }

  // Vertex at zone center:

  if(is_zone_centered_refiner())
  {

    // Set the local coordinates buffer to the center of the zone.

    lcoord_evaluator->center(xbuffer.local_coords);

    // Evaluate the global coordinates at the local coordinates.

    lcoord_evaluator->value_at_coord(xbuffer.coord_dofs,
                                     xbuffer.local_coords,
                                     xbuffer.coord_value);

      // Make sure the coordinates dof map has enough capacity for the new point.

      xbuffer.reserve_coord_fiber(_zone_ctr_id);

    // Insert the value in the coordinates section.

    lcoordinates.put_fiber(_zone_ctr_id,
			   xbuffer.coord_value.base(),
			   xbuffer.coord_value.ct()*sizeof(sec_vd_dof_type),
			   false);
  }



  // Postconditions:


  // Exit:

  return;
}


// PRIVATE MEMBER FUNCTIONS

sheaf::pod_index_type
fields::edge_centered_polygon_refiner::
create_edge_center(base_space_poset& xbase,
                   const scoped_index& xzone_id,
                   int xdepth,
                   const scoped_index& xprev_mbr_id,
                   const scoped_index& xmbr_id)
{
  // Preconditions:

  require(xbase.in_jim_edit_mode());
  require(xbase.contains_member(xzone_id));
  require(xzone_id.same_scope(xbase.member_hub_id_space(false)));
  require(xprev_mbr_id.same_scope(xbase.member_hub_id_space(false)));
  require(xmbr_id.same_scope(xbase.member_hub_id_space(false)));

  // Body:

  // Create the edge center vertex.

  pod_index_type result = create_vertex(xbase, xdepth);

  // Each edge is contained in at most 2 triangles.
  // In the current triangle, the vertices of the current edge
  // have local indices xid-1 and xid+1, in that order.
  // In the other triangle, if it exists, the same vertices will
  // occur in the opposite order. Get their global ids:

  scoped_index ledge_begin = xmbr_id;
  scoped_index ledge_end   = xprev_mbr_id;

  // Note that begin and end refer to the order in the other triangle.

  // Find the other triangle, if it exists.

  // Iterate over the upper cover of the first vertex.

  index_space_iterator& uc_itr = xbase.get_cover_id_space_iterator(UPPER, ledge_begin);

  while(!uc_itr.is_done())
  {
    if(uc_itr.hub_pod() == xzone_id.pod())
    {
      // This is the triangle we're refining; skip it.

      uc_itr.next();
    }
    else
    {
      // We know that the lower cover of the current upper cover
      // member contains ledge_begin, find it.

      index_space_iterator& lc_itr = xbase.get_cover_id_space_iterator(LOWER, uc_itr.hub_pod());

      while(lc_itr.hub_pod() != ledge_begin.pod())
      {
        lc_itr.next();
      }

      assertion(lc_itr.hub_pod() == ledge_begin.pod());

      // Now the lower cover iterator is pointing at an occurence
      // of ledge_begin in some edge, we need to determine
      // whether it is the edge we are looking for.

      // Get the other end of the current edge;
      // it is either the next member of the lower cover
      // or the first member.

      lc_itr.next();

      pod_index_type lother_end = (!lc_itr.is_done())
	? lc_itr.hub_pod()
	: xbase.first_cover_member(LOWER, uc_itr.hub_pod());

      if(lother_end == ledge_end.pod())
      {
        // Found the edge we're looking for; insert the
        // new edge center vertex in the lower cover
        // between ledge_begin and ledge_end.

	if(lc_itr.is_done())
	{
	  // Iterator is done, insert at the end of cover.

	  xbase.insert_cover_member(result, LOWER, uc_itr.hub_pod());
	}
	else
	{
	  // Iterator is not done, insert at the iterator position.

	  xbase.insert_cover_member(result, LOWER, uc_itr.hub_pod(), lc_itr);
	}
	
        // We're done

        break;
      }
      else
      {
        // This is not the edge we are looking for;
        // so the edge is not in this member of the upper cover.
        // Move to the next member of the upper cover.

        uc_itr.next();
      }

      xbase.release_cover_id_space_iterator(lc_itr);
    }
  }
  xbase.release_cover_id_space_iterator(uc_itr);

  // Postconditions:

  ensure(xbase.contains_member(result));
  ensure(xbase.refinement_depth(result) == xdepth);

  // The following is made unexecutable because it is expensive,
  // have to search the upper cover of bottom, which is O(#vertices).

  ensure(unexecutable(xbase.contains_cover_link(result, BOTTOM_INDEX)));

  // Exit:

  return result;
}

void
fields::edge_centered_polygon_refiner::
make_new_vertices(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;

  // The vertices in the boundary of the refinement include
  // the original vertices and the/ vertices at the center of the edges.
  // The boundary may also include additional vertices from adjacent,
  // more highly refined, these appear between the desired vertices
  // and should appear in the lower cover of the new zone which contains them.

  int lzone_depth = lbase->refinement_depth(lzone_id);
  int lnew_depth  = lzone_depth + 1;

  // Initialize the new point and new triangle buffers.

  _vertex_ids.set_ct(0);
  _is_new_vertex.set_ct(0);
  _vertex_pos.set_ct(0);
  _vertex_list.clear();

  // Copy the lower cover of the zone to the vertex buffer.
  /// @issue assume the lower cover of the zone contains only vertices.

  index_space_iterator& lc_itr = lbase->get_cover_id_space_iterator(LOWER, lzone_id);
  scoped_index lvertex_id(lbase->member_hub_id_space(false));
  while(!lc_itr.is_done())
  {
    lvertex_id = lc_itr.hub_pod();
    _vertex_list.push_back(lvertex_id);
    lc_itr.next();
  }
  
  // Duplicate the first vertex at the end;

  _vertex_list.insert(_vertex_list.end(), *_vertex_list.begin());

  // Delete all the links between the original zone and its vertices.
  // Could call delete_link for each member of the lower cover, but
  // more efficient to do it in the following way:

  lc_itr.reset();
  while(!lc_itr.is_done())
  {
    lbase->remove_cover_member(lzone_id.pod(), UPPER, lc_itr.hub_pod());
    lc_itr.next();
  }
  lbase->clear_cover(LOWER, lzone_id);

  lbase->release_cover_id_space_iterator(lc_itr);

  // Create any edge centers that aren't already there.
  // If two vertices in sequence are unrefined, there
  // should be an edge center between them.

  vertex_list_type::iterator litr = _vertex_list.begin();
  scoped_index l_id = *litr;
  bool lunrefined = (lbase->refinement_depth(l_id) < lnew_depth);

  // The first vertex must be unrefined

  assertion(lunrefined);

  // Store it and mark it not new

  _vertex_ids.push_back(l_id);
  _is_new_vertex.push_back(false);
  _vertex_pos.push_back(litr);

  scoped_index& lprev_id = l_id;
  bool lprev_unrefined = lunrefined;
  ++litr;

  scoped_index ledge_ctr(lbase->member_hub_id_space(false));

  while(litr != _vertex_list.end())
  {
    scoped_index& l_id = *litr;
    int ldepth = lbase->refinement_depth(l_id);
    lunrefined = (ldepth < lnew_depth);

    if(lunrefined && lprev_unrefined)
    {
      // Two unrefined vertices in sequence;
      // create an edge center between them.

      ledge_ctr =
	create_edge_center(*lbase, lzone_id, lnew_depth, lprev_id, l_id);

      // Insert the edge center between the two unrefined vertices.

      vertex_list_type::iterator ledge_ctr_pos = _vertex_list.insert(litr, ledge_ctr);

      // Store the edge center and mark it new

      _vertex_ids.push_back(ledge_ctr);
      _is_new_vertex.push_back(true);
      _vertex_pos.push_back(ledge_ctr_pos);
    }

    if(ldepth <= lnew_depth)
    {
      // This is a previously created vertex at this refinement depth.
      // Store it and mark it not new

      _vertex_ids.push_back(l_id);
      _is_new_vertex.push_back(false);
      _vertex_pos.push_back(litr);
    }
    else
    {
      // This is a previously created vertex in some more highly
      // refined adjacent triangle; ignore it.
    }


    lprev_id = l_id;
    lprev_unrefined = lunrefined;
    ++litr;
  }

  // Now we should have visited all the edge vertices in this refinement.
  // There are refined_vertex_ct()+1 vertices in each buffer because the
  // 1st vertex is duplicated at the end. Remove it.

  _vertex_ids.pop_back();
  _is_new_vertex.pop_back();
  _vertex_pos.pop_back();

  // Remove the duplicate vertex at the end of the vertex buffer.

  _vertex_list.pop_back();

  if(is_zone_centered_refiner())
  {
    // Create the vertex in the center of the zone.

    _zone_ctr_id = lbase->member_id(create_vertex(*lbase, lnew_depth), false);
  }

#ifdef DIAGNOSTIC_OUTPUT
  cout << "refined_vertex_ct: " << refined_vertex_ct() << endl;
  cout << "center vertex: " << _zone_ctr_id << endl;
  cout << "vertex_ids:\t" << _vertex_ids << endl;
  cout << "is_new_vertex:\t" << _is_new_vertex << endl;
  cout << "vertex buffer:\t  ";
  copy(_vertex_list.begin(), _vertex_list.end(), ostream_iterator<scoped_index>(cout, " "));
  cout << endl << endl;
#endif

  // Postconditions:

  // Now there should be refined_vertex_ct() entries in each buffer.

  ensure(_vertex_ids.ct() == refined_vertex_ct());
  ensure(_is_new_vertex.ct() == refined_vertex_ct());
  ensure(_vertex_pos.ct() == refined_vertex_ct());

  // Exit:

  return;
}

const sheaf::block<sheaf::size_type>&
fields::edge_centered_polygon_refiner::
first_vertex_index() const
{
  static const block<size_type> result;

  // Preconditions:


  // Body:

  is_abstract();

  // Postconditions:

  ensure(result.ct() > 1);

  // Exit:

  return result;
}

void
fields::edge_centered_polygon_refiner::
make_new_zones(field_refinement_buffer& xbuffer)
{
  // Preconditions:

  require(xbuffer.base_space != 0);
  require(xbuffer.base_space->in_jim_edit_mode());

  // Body:

  base_space_poset* lbase = xbuffer.base_space;
  scoped_index lzone_id = xbuffer.zone_id;

  int lzone_depth = lbase->refinement_depth(lzone_id);
  int lnew_depth  = lzone_depth + 1;

  _refined_zone_ids.set_ct(0);

  // Create the new edge-centered zones;
  // number of edges == number of unrefined vertices.
  // edge centers are at index 1, 3, 5, and 7 in _vertex_pos and _vertex_ids.

  scoped_index lnew_zone;
  const block<size_type>& lfirst_vertex_index = first_vertex_index();

  // Number of zones is one less than number of entries in first_vertex_index
  // because last entry is duplicate of first.

  size_type lzone_ct = lfirst_vertex_index.ct() - 1;

  for(size_type i=0; i<lzone_ct; ++i)
  {
    // Create the zone.

    lnew_zone = lbase->member_id(create_zone(*lbase, lnew_depth), false);
    _refined_zone_ids.push_back(lnew_zone);

    // Create the upper cover of the new zone.

    lbase->new_link(lzone_id, lnew_zone);

    // Create the lower cover of the new zone.
    // The lower cover contains all the vertices in _vertex_list
    // between _vertex_pos[le] and _vertex_pos[le+2],
    // with appropriate "circular" indexing taken into account.

    // Get the position of the first vertex for this zone.

    size_type lv_first = lfirst_vertex_index[i];
    vertex_list_type::iterator litr = _vertex_pos[lv_first];

    // Get the position of the last vertex for this zone;
    // last vertex for this zone is first vertex for next zone.
    // Note that last entry in first_vertex_index contains duplicate
    // of first entry so i+1 won't run off the end.

    size_type lv_last = lfirst_vertex_index[i+1];
    vertex_list_type::iterator llast_vertex_pos = _vertex_pos[lv_last];

    // Link all the vertices between first and last, inclusive.

    while(litr != llast_vertex_pos)
    {

      lbase->new_link(lnew_zone, *litr);

      if(++litr == _vertex_list.end())
      {
        // Off the end; wrap around to the beginning.

        litr = _vertex_list.begin();
      }
    }

    assertion(litr == llast_vertex_pos);

    lbase->new_link(lnew_zone, *litr);

    if(is_zone_centered_refiner())
    {
      // Link the zone center vertex.

      lbase->new_link(lnew_zone, _zone_ctr_id);
    }


#ifdef DIAGNOSTIC_OUTPUT

    cout << "zone: " << setw(6) << lnew_zone;
    cout << "  lower cover: ";
    cover_set_state& lnew_zone_cvr = lbase->lower_cover(lnew_zone);
    copy(lnew_zone_cvr.begin(),
         lnew_zone_cvr.end(),
         ostream_iterator<scoped_index>(cout, " "));
    cout << endl;
#endif

  }

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// LOCAL_FIELD_REFINER FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

int
fields::edge_centered_polygon_refiner::
db() const
{
  int result;

  // Preconditions:


  // Body:

  result = 2;

  // Postconditions:

  ensure(result == 2);

  // Exit:

  return result;
}


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::edge_centered_polygon_refiner*
fields::edge_centered_polygon_refiner::
clone() const
{
  edge_centered_polygon_refiner* result = 0;

  // Preconditions:

  // Body:

  is_abstract();

  // Postconditions:

  ensure(result != 0);
  //  ensure(invariant());
  ensure(result->invariant());
  ensure(is_same_type(result));

  return result;
}

fields::edge_centered_polygon_refiner&
fields::edge_centered_polygon_refiner::
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
fields::edge_centered_polygon_refiner&
fields::edge_centered_polygon_refiner::
operator=(const edge_centered_polygon_refiner& xother)
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

fields::edge_centered_polygon_refiner::
~edge_centered_polygon_refiner()
{
  // Preconditions:

  // Body:

  // Postconditions:

  ensure(invariant());

  return;
}


bool
fields::edge_centered_polygon_refiner::
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
fields::edge_centered_polygon_refiner::
is_ancestor_of(const any* xother) const
{

  // Preconditions:

  require(xother != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const edge_centered_polygon_refiner*>(xother) != 0;

  // Postconditions:

  return result;

}



