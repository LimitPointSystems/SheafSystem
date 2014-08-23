
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
/// Interface for class edge_centered_polygon_refiner

#ifndef COM_LIMITPOINT_FIELDS_EDGE_CENTERED_POLYGON_REFINER_H
#define COM_LIMITPOINT_FIELDS_EDGE_CENTERED_POLYGON_REFINER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_LOCAL_FIELD_REFINER_H
#include "ComLimitPoint/fields/local_field_refiner.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

namespace fields
{

///
/// An abstract field refiner that subdivides a polygon by introducing
/// new vertices into the centers of the edges.
///
class SHEAF_DLL_SPEC edge_centered_polygon_refiner : public local_field_refiner
{

  // ===========================================================
  /// @name EDGE_CENTERED_POLYGON_REFINER FACET
  // ===========================================================
  //@{

protected:

  ///
  /// Creates an instance for refining base space
  /// xbase_space using policy xpolicy.
  ///
  edge_centered_polygon_refiner(const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor.
  ///
  edge_centered_polygon_refiner(const edge_centered_polygon_refiner& xother);

  ///
  /// The number of vertices with refinement depth <= unrefined zone depth.
  ///
  virtual size_type unrefined_vertex_ct() const = 0;

  ///
  /// The number of boundary vertices with
  /// refinement depth <= refined zone depth;
  /// does not include center vertex, if one exists.
  ///
  size_type refined_vertex_ct() const;

  ///
  /// The number of edges in the zone.
  ///
  size_type edge_ct() const;

  ///
  /// True if this adds a vertex at the center of the zone.
  ///
  virtual bool is_zone_centered_refiner() const = 0;

  ///
  /// Default constructor; disabled.
  ///
  edge_centered_polygon_refiner();

  ///
  /// The ids of the vertices in boundary <= new refinement depth.
  ///
  block<scoped_index> _vertex_ids;

  ///
  /// True if i-th member is a new vertex.
  ///
  block<bool> _is_new_vertex;

  ///
  /// The type of buffer used for processing vertices.
  ///
  typedef std::list<scoped_index> vertex_list_type;

  ///
  /// The position in _vertex_list of ids of the vertices
  /// in the currnet refinement.
  ///
  block<vertex_list_type::iterator> _vertex_pos;

  ///
  /// List for processing vertices.
  ///
  vertex_list_type _vertex_list;

  ///
  /// The id of the new vertex in the center of the zone.
  ///
  scoped_index _zone_ctr_id;

  ///
  /// Reserves space in vertex buffers.
  ///
  void reserve_vertex_buffers();

  ///
  /// Refines the base space or the target.
  ///
  virtual void refine_base_space(field_refinement_buffer& xbuffer);

  ///
  /// Modifies the cover relation graph of the base space.
  ///
  virtual void modify_crg(field_refinement_buffer& xbuffer);

  ///
  /// Modifies subposets in the base space.
  ///
  void modify_subposets(field_refinement_buffer& xbuffer);

  ///
  /// Refines the coordinates of the target.
  ///
  virtual void refine_coordinates(field_refinement_buffer& xbuffer);

  ///
  /// Creates a new edge center vextex and puts it in _new_point_ids[xid].
  ///
  pod_index_type create_edge_center(base_space_poset& xbase,
				    const scoped_index& xzone_id,
				    int xdepth,
				    const scoped_index& xprev_mbr_id,
				    const scoped_index& xmbr_id);

  ///
  /// Makes new vertices in edge centers as needed and
  /// builds the list of vertices in the boundary of the zone.
  ///
  void make_new_vertices(field_refinement_buffer& xbuffer);

  ///
  /// The index in _vertex_pos of the first vertex of each new zone;
  /// contains number of zones + 1 because first entry is duplicated
  /// at the end.
  ///
  virtual const block<size_type>& first_vertex_index() const = 0;

  ///
  /// Make the new zones in the refinement.
  ///
  void make_new_zones(field_refinement_buffer& xbuffer);

  //@}


  // ===========================================================
  /// @name LOCAL_FIELD_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The base dimension; the dimension of the
  /// local coordinates (independent variable).
  ///
  virtual int db() const;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, creates a new instance of the same type as this.
  ///
  virtual edge_centered_polygon_refiner* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  virtual edge_centered_polygon_refiner& operator=(const local_field_refiner& xother);

  ///
  /// Assignment operator
  ///
  edge_centered_polygon_refiner& operator=(const edge_centered_polygon_refiner& xother);

  ///
  /// Destructor.
  ///
  virtual ~edge_centered_polygon_refiner();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  //@}

};
  
} // namespace fields

#endif // ifndef COM_LIMITPOINT_FIELDS_EDGE_CENTERED_POLYGON_REFINER_H
