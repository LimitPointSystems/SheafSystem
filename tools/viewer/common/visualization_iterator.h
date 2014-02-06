
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

// Interface for class visualization_iterator


#ifndef VISUALIZATION_ITERATOR_H
#define VISUALIZATION_ITERATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FILTERED_DEPTH_FIRST_ITERATOR_H
#include "filtered_depth_first_iterator.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef SECTION_ITERATION_STATE_H
#include "section_iteration_state.h"
#endif

#ifndef VTKTYPE_H
#include "vtkType.h"
#endif
   
class vtkDoubleArray;
class vtkIdTypeArray;

namespace tool
{

using namespace fiber_bundle;

///
/// Abstract iterator over the schema of both the coordinates
/// and property sections of a visualization.
///
class SHEAF_DLL_SPEC visualization_iterator :
  public filtered_depth_first_iterator
{
public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual visualization_iterator* clone() const = 0;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // ===========================================================
  // DEPTH_FIRST_ITERATOR FACET
  // ===========================================================

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

  using filtered_depth_first_iterator::put_anchor;

  ///
  /// Reinitializes anchor() to iterate over xcoord_schema and xprop_schema.
  ///
  virtual void put_anchor(const section_space_schema_member& xcoords_schema,
                          const section_space_schema_member& xprop_schema);

  ///
  /// Reinitializes anchor() to iterate over xcoord_schema and xprop_schema.
  ///
  virtual void put_anchor(const section_space_schema_member& xcoords_schema);

  ///
  /// Restarts the iteration over the down set of anchor().
  ///
  virtual void reset(bool xreset_markers = true);

  // ===========================================================
  // VISUALIZATION_ITERATOR FACET
  // ===========================================================

  ///
  /// Creates an iterator appropriate for xcoords and xprop.
  ///
  static visualization_iterator*
  new_visualization_iterator(const section_space_schema_member& xcoords_schema,
                             const section_space_schema_member& xprop_schema,
                             bool xinitialize = true);

  ///
  /// Creates an iterator appropriate for xcoords alone.
  ///
  static visualization_iterator*
  new_visualization_iterator(const section_space_schema_member& xcoords_schema,
                             bool xinitialize = true);

  ///
  /// Destructor.
  ///
  ~visualization_iterator();

  ///
  /// The coordinates field schema member which is being iterated over.
  ///
  const section_space_schema_member& coordinates_schema() const;

  ///
  /// True if this visualization has a property section.
  ///
  bool has_property() const;

  ///
  /// The property field schema member which is being iterated over.
  ///
  const section_space_schema_member& property_schema() const;

  ///
  /// If true use top ids to label points; 
  /// otherwise, use discretization ids.
  ///
  bool use_point_top_ids() const;
  
  ///
  /// Sets use_point_top_ids() to xvalue.
  ///
  void put_use_point_top_ids(bool xvalue);

  ///
  /// If true use top ids to label cells; 
  /// otherwise, use evaluation ids.
  ///
  bool use_cell_top_ids() const;
  
  ///
  /// Sets use_cell_top_ids() to xvalue.
  ///
  void put_use_cell_top_ids(bool xvalue);
  

  ///
  /// Transfers coordinate and property data to vtk data structures.
  ///
  virtual void set_vtk_data(const sec_vd& xcoords,
                            const sec_vd& xprop,
                            vtkDoubleArray* xvtk_pt_coords,
                            vtkDoubleArray* xvtk_prop,
                            int xprop_tensor_rank,
                            block<int>& xvtk_cell_types,
                            block<vtkIdType>& xvtk_cell_connectivity,
                            block<int>& xvtk_cell_type_map,
                            vtkIdTypeArray* xvtk_pt_label_ids,
                            vtkIdTypeArray* xvtk_cell_label_ids);

  ///
  /// Transfers coordinate data to vtk data structures.
  ///
  virtual void set_vtk_data(const sec_vd& xcoords,
                            vtkDoubleArray* xvtk_pt_coords,
                            block<int>& xvtk_cell_types,
                            block<vtkIdType>& xvtk_cell_connectivity,
                            block<int>& xvtk_cell_type_map,
                            vtkIdTypeArray* xvtk_pt_label_ids,
                            vtkIdTypeArray* xvtk_cell_label_ids);

  ///
  /// Transfers property data to vtk data structures.
  ///
  virtual void set_vtk_data(const sec_vd& xprop,
                            vtkDoubleArray* xvtk_prop,
                            int xprop_tensor_rank);

protected:

  ///
  /// Default constructor.
  ///
  visualization_iterator();

  ///
  /// Copy constructor; disabled.
  ///
  visualization_iterator(const visualization_iterator& xother)
  {}

  ///
  /// Initializes this for iteration of type xorder over
  /// xcoordinates_schema and xproperty_schema.
  ///
  void initialize_iteration(const section_space_schema_member& xcoordinates_schema,
                            const section_space_schema_member& xproperty_schema);

  ///
  /// Initializes this for iteration of type xorder over
  /// xcoordinates_schema and xproperty_schema.
  ///
  void initialize_iteration(
    const section_space_schema_member& xcoordinates_schema);

  ///
  /// True if this visualization has a property section.
  ///
  bool _has_property;

  ///
  /// If true use top ids to label points; 
  /// otherwise, use discretization ids.
  ///
  bool _use_point_top_ids;

  ///
  /// If true use top ids to label cells; 
  /// otherwise, use evaluation ids.
  ///
  bool _use_cell_top_ids;

  ///
  /// Descriptor for coordinate section iteration.
  ///
  section_iteration_state _coord_state;

  ///
  /// Descriptor for property section iteration.
  ///
  section_iteration_state _prop_state;

  ///
  /// Descriptor for visualization section iteration.
  ///
  section_iteration_state _vis_state;

  ///
  /// Relative depth flags type.
  ///
  struct SHEAF_DLL_SPEC depth_flags_type
  {
    bool coord_eval;
    bool coord_disc;
    bool prop_eval;
    bool prop_disc;
    bool vis_eval;
    bool vis_disc;

    depth_flags_type& operator=(bool xvalue)
    {
      coord_eval = xvalue;
      coord_disc = xvalue;
      prop_eval  = xvalue;
      prop_disc  = xvalue;
      vis_eval   = xvalue;
      vis_disc   = xvalue;

      return(*this);
    };
  };

  ///
  /// True if current iteration is a member of the
  /// subposet associated with the flag.
  ///
  depth_flags_type _at;

  ///
  /// True if current iteration is above the
  /// subposet associated with the flag.
  ///
  depth_flags_type _above;

  ///
  /// Upper bound for _coord_dofs.
  ///
  // static const size_type _coord_dofs_ub = 3;

  enum static_const_int {COORD_DOFS_UB = 3, PROP_DOFS_UB = 16};

  ///
  /// A buffer for the coord dofs at a disc point.
  ///
  sec_vd_dof_type _coord_dofs[COORD_DOFS_UB];

  /// Upper bound for _prop_dofs.
  ///
  //static const size_type _prop_dofs_ub = 16;

  ///
  /// A buffer for the prop dofs at a disc point.
  ///
  sec_vd_dof_type _prop_dofs[PROP_DOFS_UB];

  ///
  /// Initializes the coord dofs and prop dofs buffers.
  ///
  void initialize_buffers();

  ///
  /// Unmarks the down set and clears the dow set buffer.
  ///
  void clear_down_set();

  ///
  /// x1 if x1 <= x2, otherwise x2.
  ///
  const abstract_poset_member& min(const abstract_poset_member& x1,
                                   const abstract_poset_member& x2) const;

  ///
  /// Initializes _coord_state, _prop_state, and _vis_state.
  ///
  void initialize_states(const section_space_schema_member& xcoordinates_schema,
                         const section_space_schema_member& xproperty_schema);


  ///
  /// Initializes _coord_state and _vis_state.
  ///
  void initialize_states(const section_space_schema_member& xcoordinates_schema);

  ///
  /// The sequece id of the current vtk cell (i.e. element or zone).
  ///
  int _cell_seq_id;

  ///
  /// The sequece id of the current vtk point (i.e. vertex).
  ///
  int _pt_seq_id;

  ///
  /// Converts xprop_dofs as needed depending on xprop_tenosr_rank
  /// and puts them into xvtk_prop_dofs at xvtk_tuple_id.
  ///
  void put_prop_dofs(sec_vd_dof_type* xprop_dofs,
                     size_type xprop_df,
                     int xprop_tensor_rank,
                     vtkDoubleArray* xvtk_prop,
                     int xvtk_tuple_id);

  ///
  /// Buffer for vtk rep of st2_e3 tensors.
  ///
  double _st2_e3[3][3];

  ///
  /// Buffer for vtk rep of st2_e2 tensors.
  ///
  double _st2_e2[3][3];

  ///
  /// The index of the current maximal evaluation member.
  ///
  scoped_index _maximal_eval_id;

};
 
} // namespace tool

#endif // ifndef VISUALIZATION_ITERATOR_H
