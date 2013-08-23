
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

// Interface for class vtk_unstructured_grid_builder

#ifndef VTK_UNSTRUCTURED_GRID_BUILDER_H
#define VTK_UNSTRUCTURED_GRID_BUILDER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VTK_ABSTRACT_GRID_BUILDER_H
#include "vtk_abstract_grid_builder.h"
#endif

#ifndef VTKTYPE_H
#include "vtkType.h"
#endif
  
namespace tool
{

///
/// Creates a vtkUnstructuredGrid from sheaf field objects.
///
class SHEAF_DLL_SPEC vtk_unstructured_grid_builder :
    public vtk_abstract_grid_builder
{

public:

  // ===========================================================
  // ANY FACET
  // ===========================================================

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual vtk_unstructured_grid_builder* clone() const;

  ///
  /// Assignment operator.
  ///
  ///
  virtual vtk_unstructured_grid_builder& operator=
    (const vtk_abstract_grid_builder& xother);

  ///
  /// Assignment operator.
  ///
  vtk_unstructured_grid_builder& operator=
    (const vtk_unstructured_grid_builder& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // VTK_UNSTRUCTURED_GRID_BUILDER FACET
  // ===========================================================

  ///
  /// Default constructor
  ///
  vtk_unstructured_grid_builder();

  ///
  /// Copy constructor.
  ///
  ///
  vtk_unstructured_grid_builder(const vtk_unstructured_grid_builder& xother);

  ///
  /// Creates an instance for fields in namespace xns.
  ///
  vtk_unstructured_grid_builder(namespace_poset& xns);

  ///
  /// Destructor
  ///
  virtual ~vtk_unstructured_grid_builder();

  ///
  /// If this instance's namespace is not equal to xns, this instance is
  /// initialized to have namespace xns.
  ///
  void set_name_space(namespace_poset& xns);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and xproperty, auto_allocated.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords, const sec_vd& xproperty);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, xproperty1,
  /// and xproperty2, auto_allocated.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords,
                             const sec_vd& xproperty1,
                             const sec_vd& xproperty2);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, auto-allocated.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords with cells colored by
  /// membership in the partition with name xpartition_name, auto-allocated.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords,
                             const string& xpartition_name);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and the property
  /// sections in xproperties, auto_allocated.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords,
                             const block<sec_vd*>& xproperties);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and xproperty, pre-allocated.
  ///
  void build_pa(const sec_vd& xcoords,
                const sec_vd& xproperty,
                vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, xproperty1 and
  /// xproperty2, pre-allocated.
  ///
  void build_pa(const sec_vd& xcoords,
                const sec_vd& xproperty1,
                const sec_vd& xproperty2,
                vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, pre-allocated.
  ///
  void build_pa(const sec_vd& xcoords, vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords with cells colored by
  /// membership in the partition with name xpartition_name, pre-allocated.
  ///
  void build_pa(const sec_vd& xcoords,
                const string& xpartition_name,
                vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and the property
  /// sections in xproperties, pre_allocated.
  ///
  void build_pa(const sec_vd& xcoords,
                const block<sec_vd*>& xproperties,
                vtkUnstructuredGrid& xresult);


  ///
  /// Builds a vtk file representation of a vtkPolyData from xcoords and xproperty
  /// with file name xvtk_file_name.
  /// If xis_ascii is true, write an  ascii (text) file; otherwise write a
  /// binary file.
  ///
  void build_file(const sec_vd& xcoords, const sec_vd& xproperty,
                  const string& xvtk_file_name, bool xis_ascii = true);

  ///
  /// True if the fiber of xsec is a scalar type.
  ///
  bool is_scalar(const sec_vd* xsec) const;

  ///
  /// True if the fiber of xsec is a vector type.
  ///
  bool is_vector(const sec_vd* xsec) const;

  ///
  ///  True if the fiber of xsec is a tensor type.
  ///
  bool is_tensor(const sec_vd* xsec) const;

private:

  //===========================================================================

  ///
  ///  Get the namespace_poset.
  ///
  namespace_poset& name_space() const;

  ///
  ///  Initialize the cell type map.
  ///
  void init_cell_type_map();

  ///
  /// Constructs cell coloring data from partition with name xpartition_name
  /// in base space xbase.
  ///
  void set_cell_data(abstract_poset_member& xbase,
                     const string& xpartition_name,
                     vtkUnstructuredGrid& xresult);

  ///
  /// The namespace_poset representing the contents of the sheaf file.
  ///
  namespace_poset* _name_space;

  ///
  /// Map from sheaf cell types to vtk cell types.
  ///
  block<int> _cell_type_map;

  ///
  /// Block (array) containing the VTK cell types (one entry for each cell).
  ///
  block<int>* _vtk_cell_types;

  ///
  ///  Block (array) containing the VTK cell connectivities.
  ///
  block<vtkIdType>* _vtk_cell_connectivity;

  ///
  /// True if mesh is just points.
  ///
  bool _is_point_mesh;

  ///
  /// True if property is point data, false if cell data.
  ///
  block<bool> _prop_is_pt_data;

  ///
  /// Tensor rank of properties.
  ///
  block<int> _prop_tensor_rank;

  ///
  /// Number of points in current grid.
  ///
  int _pt_ct;

  ///
  /// Number of cells in current grid.
  ///
  int _cell_ct;

  ///
  /// Array of coordinate values.
  ///
  vtkDoubleArray* _vtk_coord_dofs;

  ///
  /// Array of property values.
  ///
  block<vtkDoubleArray*> _vtk_prop_dofs;

  ///
  /// Initializes vtk mesh and coordinate data structures before iteration.
  ///
  void initialize_vtk_mesh_data(const sec_vd& xsec, string xcoords_name);

  ///
  /// Finalizes vtk mesh and coordinate data structures after iteration.
  ///
  void finalize_vtk_mesh_data(vtkUnstructuredGrid& xresult);

  ///
  /// Initializes vtk property data structures for section xprop.
  ///
  void initialize_vtk_prop_data(const sec_vd* xprop);

  ///
  /// Finalizes vtk property data structures after iteration.
  ///
  void finalize_vtk_prop_data(const sec_vd* xprop,
                              bool xprop_is_pt_data,
                              int xprop_tensor_rank,
                              vtkDoubleArray* xvtk_prop_dofs,
                              vtkUnstructuredGrid& xresult);
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

  
} // namespace tool

#endif // ifndef VTK_UNSTRUCTURED_GRID_BUILDER_H
