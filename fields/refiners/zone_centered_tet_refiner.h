
//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

/// @file
/// Interface for class zone_centered_tet_refiner

#ifndef ZONE_CENTERED_TET_REFINER_H
#define ZONE_CENTERED_TET_REFINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef LOCAL_FIELD_REFINER_H
#include "local_field_refiner.h"
#endif

namespace fields
{

///
/// A field refiner that subdivides a tet into 4 tets by
/// introducing a new vertex in the center.
///
class SHEAF_DLL_SPEC zone_centered_tet_refiner : public local_field_refiner
{

  // ===========================================================
  /// @name ZONE_CENTERED_TET_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for refining base space
  /// xbase_space using policy xpolicy.
  ///
  zone_centered_tet_refiner(const field_refinement_policy& xpolicy);

  ///
  /// Copy constructor.
  ///
  zone_centered_tet_refiner(const zone_centered_tet_refiner& xother);

protected:

  ///
  /// Default constructor; disabled.
  ///
  zone_centered_tet_refiner();

  ///
  /// The index of the point added by the current base space refinement.
  ///
  scoped_index _zone_ctr_id;

  ///
  /// The ids of the original vertices.
  ///
  block<scoped_index> _vertex_ids;

  ///
  /// Refines the base space or the target.
  ///
  virtual void refine_base_space(field_refinement_buffer& xbuffer);

  ///
  /// Modifies the cover relation graph of the base space.
  ///
  void modify_crg(field_refinement_buffer& xbuffer);

  ///
  /// Modifies subposets in the base space.
  ///
  void modify_subposets(field_refinement_buffer& xbuffer);

  ///
  /// Refines the coordinates of the target.
  ///
  virtual void refine_coordinates(field_refinement_buffer& xbuffer);

private:

  ///
  /// The number of refined zones created by this refiner; static version.
  ///
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {REFINED_ZONE_CT = 4};
  //  static const size_type REFINED_ZONE_CT = 4;

  ///
  /// Connectivity of new tests.
  ///
  static const block<size_type>& connectivity();

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

  ///
  /// The name of the type of zone this creates during refinement.
  ///
  virtual const string& zone_type_name() const;

  ///
  /// The number of refined zones created by this.
  ///
  virtual size_type refined_zone_ct() const;

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
  virtual zone_centered_tet_refiner* clone() const;

  ///
  /// Assignment operator.
  ///
  virtual zone_centered_tet_refiner& operator=(const local_field_refiner& xother);

  ///
  /// Assignment operator
  ///
  zone_centered_tet_refiner& operator=(const zone_centered_tet_refiner& xother);

  ///
  /// Destructor.
  ///
  virtual ~zone_centered_tet_refiner();

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

#endif // ifndef ZONE_CENTERED_TET_REFINER_H
