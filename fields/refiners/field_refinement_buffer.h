
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
/// Interface for class field_refinement_buffer

#ifndef FIELD_REFINEMENT_BUFFER_H
#define FIELD_REFINEMENT_BUFFER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELDS_H
#include "ComLimitPoint/fields/fields.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_FIBER_BUNDLE_H
#include "ComLimitPoint/fiber_bundle/fiber_bundle.h"
#endif

#ifndef COM_LIMITPOINT_FIELDS_FIELD_VD_H
#include "ComLimitPoint/fields/field_vd.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

namespace sheaf
{
class mutable_index_space_handle;
class subposet;
}

namespace fiber_bundle
{
class base_space_poset;
class section_evaluator;
}

namespace fields
{
  //  using namespace fields;

  class field_vd;
  class local_field_refiner;

///
/// A buffer for data which is used by both a local_field_refiner object
/// and its associated field_refinement_policy object.
///
class SHEAF_DLL_SPEC field_refinement_buffer
{

  // ===========================================================
  /// @name CANONICAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  bool invariant() const;

  //@}


  // ===========================================================
  /// @name FIELD_REFINEMENT_BUFFER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance for refining xtarget using xsource as the reference field.
  ///
  field_refinement_buffer(const field_vd& xsource,
                          field_vd& xtarget,
                          const block<scoped_index>& xcoord_disc_ids,
                          const block<scoped_index>& xprop_disc_ids,
                          int xdepth_ub);

  ///
  /// Creates an instance for refining xtarget using the unrefined
  /// version of itself as the reference field.
  ///
  field_refinement_buffer(field_vd& xtarget,
                          const block<scoped_index>& xcoord_disc_ids,
                          const block<scoped_index>& xprop_disc_ids,
                          int xdepth_ub);

  ///
  /// Destructor; not virtual, this can not be used as a base class.
  ///
  ~field_refinement_buffer();

  ///
  /// The reference field.
  ///
  const field_vd& source;

  ///
  /// The field being refined.
  ///
  field_vd& target;

  ///
  /// A buffer for gathering the coordinate
  /// discretization members for the current zone.
  ///
  const block<scoped_index>& coord_disc_ids;

  ///
  /// A buffer for gathering the property
  /// discretization members for the current zone.
  ///
  const block<scoped_index>& prop_disc_ids;

  ///
  /// True if i-th member has been pused.
  ///
  zn_to_bool has_been_pushed;

  ///
  /// The current base space.
  ///
  base_space_poset* base_space;

  ///
  /// The sequence id space used by the vertices subposet.
  ///
  mutable_index_space_handle* vertices_id_space;

  ///
  /// The discretization sequence id space of the target coordinates.
  ///
  mutable_index_space_handle* coord_disc_seq_id_space;

  ///
  /// The sequence id space used by the elements subposet.
  ///
  mutable_index_space_handle* elements_id_space;

  ///
  /// The evaluation subposet used by both the
  /// coordinates and property sections of the target.
  ///
  subposet& evaluation;

  ///
  /// The discretization subposet of the coordinate section of the target.
  ///
  subposet& coord_discretization;

  ///
  /// The discretization subposet of the property section of the target.
  ///
  subposet& prop_discretization;

  ///
  /// The discretization sequence id space of the target coordinates.
  ///
  mutable_index_space_handle* prop_disc_seq_id_space;

  ///
  /// A buffer for gathering coordinate dofs.
  ///
  block<sec_vd_dof_type> coord_dofs;

  ///
  /// A buffer for computing coordinates at a point.
  ///
  block<sec_vd_value_type> coord_value;

  ///
  /// A buffer for gathering property dofs.
  ///
  block<sec_vd_dof_type> prop_dofs;

  ///
  /// A buffer for computing target property at a point.
  ///
  block<sec_vd_value_type> prop_value;

  ///
  /// A buffer for computing source property at a point.
  ///
  block<sec_vd_value_type> source_prop_value;

  ///
  /// A buffer for the local coordinates of a point.
  ///
  block<chart_point_coord_type> local_coords;

  ///
  /// Another buffer for the local coordinates of a point.
  ///
  block<chart_point_coord_type> local_coords2;

  ///
  /// True if target property uses same
  /// discretization as target coordinates.
  ///
  bool same_discretization;

  ///
  /// The id of the current zone.
  ///
  scoped_index zone_id;

  ///
  /// The refinement depth of the current zone.
  ///
  int depth;

  ///
  /// The upper bound for the refinement depth.
  ///
  int depth_ub;

  ///
  /// The section evaluator for the coordinates section of the target.
  ///
  section_evaluator* coord_evaluator;

  ///
  /// The section evaluator for the property section of the target.
  ///
  section_evaluator* prop_evaluator;

  ///
  /// A buffer for property dofs of the parent zones.
  ///
  block<sec_vd_dof_type>* parent_prop_dofs;

  ///
  /// The property section evaluators for the parent zones.
  ///
  section_evaluator** parent_prop_evaluator;

  ///
  /// The index of the current subzone of the parent zones.
  ///
  int* parent_subzone_id;

  ///
  /// Gathers the coordinate dofs
  /// from the target for the current zone.
  ///
  void gather_coordinate_dofs();

  ///
  /// Gathers the property dofs
  /// from the target for the current zone.
  ///
  void gather_property_dofs();

  ///
  /// Pushes the source property dofs to the target
  /// for any discretization members that have not
  /// already been pushed.
  ///
  void push_prop_dofs();

  ///
  /// Evaluates the property dofs of the target in the parent zone
  /// for any discretization members that have not
  /// already been pushed.
  ///
  void refine_prop_dofs(local_field_refiner* xrefiner);

  ///
  /// Evaluates the property, the coordinates,
  /// and the source property at the center of the zone.
  ///
  void evaluate_at_center();

  ///
  /// Evaluates the coordinates and the source property
  /// at the position of the xi-th (local indexing)
  /// property discretization member.
  ///
  void evaluate_source_at_disc(size_type xi);

  ///
  /// Saves the prop_dofs and prop_evaluator
  /// of the current zone into the parent buffers.
  ///
  void save_parent();

  ///
  /// Ensures the coordinate dofs have enough capacity for discretization id xdisc.
  ///
  void reserve_coord_fiber(const scoped_index& xdisc_id);

  ///
  /// Ensures the property dofs have enough capacity for discretization id xdisc.
  ///
  void reserve_prop_fiber(const scoped_index& xdisc_id);

private:

  ///
  /// Default constructor; disabled.
  ///
  ///
  field_refinement_buffer();

  ///
  /// Copy constructor; disabled.
  ///
  ///
  field_refinement_buffer(const field_refinement_buffer& xother);

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace fields

#endif // ifndef FIELD_REFINEMENT_BUFFER_H
