
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

/// @file
/// Interface for class edge_centered_triangle_refiner

#ifndef EDGE_CENTERED_TRIANGLE_REFINER_H
#define EDGE_CENTERED_TRIANGLE_REFINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EDGE_CENTERED_POLYGON_REFINER_H
#include "edge_centered_polygon_refiner.h"
#endif

namespace fields
{

///
/// A field refiner that subdivides a triangle into 4 triangles
/// by introducing a new vertex in the center of each edge.
///
class SHEAF_DLL_SPEC edge_centered_triangle_refiner : public edge_centered_polygon_refiner
{

  // ===========================================================
  /// @name EDGE_CENTERED_TRIANGLE_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for refining base space
  /// xbase_space using policy xpolicy.
  ///
  edge_centered_triangle_refiner(const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor.
  ///
  edge_centered_triangle_refiner(const edge_centered_triangle_refiner& xother);

protected:

  ///
  /// Default constructor; disabled.
  ///
  edge_centered_triangle_refiner();

  ///
  /// Modifies the cover relation graph of the base space.
  ///
  virtual void modify_crg(field_refinement_buffer& xbuffer);

  ///
  /// The number of vertices with refinement depth <= unrefined zone depth.
  ///
  virtual size_type unrefined_vertex_ct() const;

  ///
  /// The number of refined zones created by this.
  ///
  virtual size_type refined_zone_ct() const;

  ///
  /// True if this adds a vertex at the center of the zone.
  ///
  virtual bool is_zone_centered_refiner() const;

  ///
  /// The index in _vertex_pos of the first vertex of each new zone;
  /// contains number of zones + 1 because first entry is duplicated
  /// at the end.
  ///
  virtual const block<size_type>& first_vertex_index() const;

private:

  ///
  /// The number of refined zones created by this refiner; static version.
  ///
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {REFINED_ZONE_CT = 4};
  //static const size_type REFINED_ZONE_CT = 4;

  //@}


  // ===========================================================
  /// @name LOCAL_FIELD_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of the type of zone this creates during refinement.
  ///
  virtual const string& zone_type_name() const;

  ///
  /// The map from the local coordinates of refined zone xi
  /// the the local coordinates of the parent zone.
  ///
  const chart_point_coord_type* local_coordinates_map(size_type xi) const;

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, creates a new instance of the same type as this.
  ///
  virtual edge_centered_triangle_refiner* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual edge_centered_triangle_refiner& operator=(const local_field_refiner& xother);

  ///
  /// Assignment operator
  ///
  edge_centered_triangle_refiner& operator=(const edge_centered_triangle_refiner& xother);

  ///
  /// Destructor.
  ///
  virtual ~edge_centered_triangle_refiner();

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

#endif // ifndef EDGE_CENTERED_TRIANGLE_REFINER_H
