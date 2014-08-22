
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

// Interface for class visualization_iterator_4_3


#ifndef VISUALIZATION_ITERATOR_4_3_H
#define VISUALIZATION_ITERATOR_4_3_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef VISUALIZATION_ITERATOR_H
#include "visualization_iterator.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_BASE_SPACE_POSET_H
#include "ComLimitPoint/fiber_bundle/base_space_poset.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_CHART_POINT_3D_H
#include "ComLimitPoint/fiber_bundle/chart_point_3d.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_H
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#endif

#ifndef STD_LIST_H
#include "std_list.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ZN_TO_BOOL_H
#include "ComLimitPoint/sheaf/zn_to_bool.h"
#endif

namespace fiber_bundle
{
class eval_family;
class section_space_schema_member;
class section_evaluator;
class sec_rep_descriptor;
class structured_block;
}

namespace tool
{
  
///
/// A visualization iterator for uniform coordinates and
/// property section with evaluation at elements and
/// discretization at or above the elements.
///
/// Since the prop disc is above the prop eval, we need to decide how
/// to associate a point with the prop disc member. We interpret this
/// construction as a method for saving memory when the same dof
/// or set of dofs is to be used for some collection of zones
/// and we let the zones assign the location of the dof, just
/// as for dofs below the eval subposet. Thus, when the disc is above
/// the eval, the disc member gets a location for each eval member.
/// Note that typically the zones are the maximal local members of
/// the base space lattice and hence there is no way to specify a
/// point on any larger objects, since they don't have local coords.
///
class SHEAF_DLL_SPEC visualization_iterator_4_3 : public visualization_iterator
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
  virtual visualization_iterator_4_3* clone() const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  // ===========================================================
  // DEPTH_FIRST_ITERATOR FACET
  // ===========================================================

  using visualization_iterator::next;

  ///
  /// Makes this the next member of the subset.
  /// If xtruncate, new this is not less than old this,
  /// i.e. the depth-first descent is truncated
  /// and the cover of this is not visited.
  ///
  virtual void next(bool xtruncate);

  // ===========================================================
  // VISUALIZATION_ITERATOR FACET
  // ===========================================================

  using visualization_iterator::set_vtk_data;

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

  // ===========================================================
  // VISUALIZATION_ITERATOR_4_3 FACET
  // ===========================================================


  ///
  /// Creates an uninitialized iterator.
  ///
  visualization_iterator_4_3();

  ///
  /// Creates an iterator for xcoordinates_schema and xproperty_schema.
  ///
  visualization_iterator_4_3(const section_space_schema_member& xcoordinate_schema,
                             const section_space_schema_member& xproperty_schema);

  ///
  /// Destructor.
  ///
  ~visualization_iterator_4_3();

protected:

private:

  ///
  /// Copy constructor; disabled.
  ///
  visualization_iterator_4_3(const visualization_iterator_4_3& xother) {};

};

} // namespace tool
  
#endif // ifndef VISUALIZATION_ITERATOR_4_3_H
