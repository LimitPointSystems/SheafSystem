
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
/// Interface for class local_field_refiner

#ifndef LOCAL_FIELD_REFINER_H
#define LOCAL_FIELD_REFINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef FIELDS_H
#include "fields.h"
#endif

namespace fiber_bundle
{
class base_space_poset;
}

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;

class field_refinement_buffer;
class field_refinement_policy;

///
/// An abstract refiner for a field over a local region (primitive cell)
/// in the base space.
///
class SHEAF_DLL_SPEC local_field_refiner : public any
{

  // ===========================================================
  /// @name LOCAL_FIELD_REFINER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Destructor
  ///
  virtual ~local_field_refiner();

  ///
  /// The base dimension; the dimension of the
  /// local coordinates (independent variable).
  ///
  virtual int db() const = 0;

  ///
  /// The name of the type of zone this creates during refinement.
  ///
  virtual const string& zone_type_name() const = 0;

  ///
  /// The name of the type of vertex this creates during refinement.
  ///
  virtual const string& vertex_type_name() const;

  ///
  /// The refinement policy for this refiner.
  ///
  const field_refinement_policy& policy() const;

  ///
  /// Refines the zone specified by xbuffer.zone_id one level
  /// and evaluates the coordinates section on the refined zone.
  ///
  void refine(field_refinement_buffer& xbuffer);

  ///
  /// The number of refined zones created by this.
  ///
  virtual size_type refined_zone_ct() const = 0;

  ///
  /// The member ids of the zones created by the most recent
  /// execution of refine().
  ///
  const block<scoped_index>& refined_zone_ids() const;

  ///
  /// The affine map from the local coordinates of refined zone xi
  /// the the local coordinates of the parent zone. Specifically,
  /// u_parent[i] = result[i*(db()+1) + j]*u[j] + result[i*(db()+1) + db()];
  /// sum convention on 0 <= j < db().
  ///
  virtual const chart_point_coord_type* local_coordinates_map(size_type xi) const = 0;

protected:

  ///
  /// Default constructor; disabled.
  ///
  ///
  local_field_refiner();

  ///
  /// Copy constructor.
  ///
  ///
  local_field_refiner(const local_field_refiner& xother);

  ///
  /// Creates an instance for refining xtarget using xsource as the reference field.
  ///
  local_field_refiner(const field_refinement_policy& xpolicy);

  ///
  /// The refinement policy.
  ///
  const field_refinement_policy& _policy;

  ///
  /// The dof tuple index for point cells at various depths.
  ///
  block<scoped_index> _point_dof_tuple_ids;

  ///
  /// The dof tuple index for quadrangle cells at various depths.
  ///
  block<scoped_index> _zone_dof_tuple_ids;

  ///
  /// The member ids of the zones created by the most recent
  /// execution of refine().
  ///
  block<scoped_index> _refined_zone_ids;

  ///
  /// Initializes the dof tuple and refined zone buffers.
  ///
  void initialize_buffers();

  ///
  /// Refines the base space or the target.
  ///
  virtual void refine_base_space(field_refinement_buffer& xbuffer) = 0;

  ///
  /// Refines the coordinates section of the target.
  ///
  virtual void refine_coordinates(field_refinement_buffer& xbuffer) = 0;

  ///
  /// Creates a new vertex at depth xdepth.
  ///
  pod_index_type create_vertex(base_space_poset& xbase, int xdepth);

  ///
  /// Creates a new quadrangle in base space xbase, with refinement depth xdepth.
  ///
  pod_index_type create_zone(base_space_poset& xbase, int xdepth);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual local_field_refiner* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  ///
  virtual local_field_refiner& operator=(const local_field_refiner& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

  //@}

};
 
} // namespace fields

#endif // ifndef LOCAL_FIELD_REFINER_H
