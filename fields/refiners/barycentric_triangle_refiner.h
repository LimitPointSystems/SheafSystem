// $RCSfile: barycentric_triangle_refiner.h,v $ $Revision: 1.8 $ $Date: 2013/01/12 17:17:27 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class barycentric_triangle_refiner

#ifndef BARYCENTRIC_TRIANGLE_REFINER_H
#define BARYCENTRIC_TRIANGLE_REFINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EDGE_CENTERED_POLYGON_REFINER_H
#include "edge_centered_polygon_refiner.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

namespace fields
{

///
/// A field refiner that subdivides a triangle into 6 triangles by
/// introducing a new vertex in the center of the triangle and each of its edges.
///
class SHEAF_DLL_SPEC barycentric_triangle_refiner : public edge_centered_polygon_refiner
{

  // ===========================================================
  /// @name BARYCENTRIC_TRIANGLE_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for refining base space
  /// xbase_space using policy xpolicy.
  ///
  barycentric_triangle_refiner(const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor.
  ///
  barycentric_triangle_refiner(const barycentric_triangle_refiner& xother);

protected:

  ///
  /// Default constructor; disabled.
  ///
  barycentric_triangle_refiner();

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
  enum static_const_int {REFINED_ZONE_CT = 6};
  //  static const size_type REFINED_ZONE_CT = 6;
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
  /// t0 the local coordinates of the parent zone.
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
  virtual barycentric_triangle_refiner* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual barycentric_triangle_refiner& operator=(const local_field_refiner& xother);

  ///
  /// Assignment operator
  ///
  barycentric_triangle_refiner& operator=(const barycentric_triangle_refiner& xother);

  ///
  /// Destructor.
  ///
  virtual ~barycentric_triangle_refiner();

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

#endif // ifndef BARYCENTRIC_TRIANGLE_REFINER_H
