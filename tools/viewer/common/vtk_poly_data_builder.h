
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

// Interface for class vtk_poly_data_builder

#ifndef VTK_POLY_DATA_BUILDER_H
#define VTK_POLY_DATA_BUILDER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ANY_H
#include "ComLimitPoint/sheaf/any.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_BLOCK_H
#include "ComLimitPoint/sheaf/block.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_H
#include "ComLimitPoint/sheaf/sheaf.h"
#endif

#ifndef VTKTYPE_H
#include "vtkType.h"
#endif
 
class vtkDataSet;
class vtkDataArray;
class vtkDoubleArray;
class vtkPolyData;

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{
class base_space_poset;
class sec_rep_space;
}

namespace tool
{

using namespace sheaf;
using namespace fiber_bundle;


///
/// Creates a vtkPolyData from sheaf field objects.
///
class SHEAF_DLL_SPEC vtk_poly_data_builder : public any
{

public:

  typedef sheaf::size_type size_type;

  typedef sec_vd::dof_type dof_type;

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
  virtual vtk_poly_data_builder* clone() const;

  ///
  /// Assignment operator
  ///
  ///
  vtk_poly_data_builder& operator=(const vtk_poly_data_builder& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // VTK_POLY_DATA_BUILDER FACET
  // ===========================================================

  ///
  /// Copy constructor
  ///
  ///
  vtk_poly_data_builder(const vtk_poly_data_builder& xother);

  ///
  /// Destructor
  ///
  virtual ~vtk_poly_data_builder();

  ///
  /// Creates an instance for fields in namespace xns.
  ///
  vtk_poly_data_builder(namespace_poset& xns);

  ///
  /// Builds a vtkPolyData from xcoords and xproperty.
  ///
  vtkPolyData* build(const sec_vd& xcoords, const sec_vd& xproperty);

  ///
  /// Builds a vtkPolyData from xcoords only.
  ///
  vtkPolyData* build(const sec_vd& xcoords);

  ///
  /// Builds a vtkPolyData from xcoords and xproperty (pre-allocated version).
  ///
  void build_pa(const sec_vd& xcoords, const sec_vd& xproperty, vtkPolyData& xresult);

  ///
  /// Builds a vtkPolyData from xcoords only with no property (pre-allocated version).
  /// The result is a reprecentation for the mesh only.
  ///
  void build_pa(const sec_vd& xcoords, vtkPolyData& xresult);

  ///
  /// Builds a vtk file representation of a vtkPolyData from xcoords and xproperty
  /// with file name xvtk_file_name.
  /// If xis_ascii is true, write an  ascii (text) file; otherwise write a
  /// binary file.
  ///
  void build_file(const sec_vd& xcoords, const sec_vd& xproperty,
                  const std::string& xvtk_file_name, bool xis_ascii = true);

  ///
  /// Builds a vtk file representation of a vtkPolyData from xcoords only
  /// with file name xvtk_file_name.
  /// If xis_ascii is true, write an  ascii (text) file; otherwise write a
  /// binary file.
  ///
  void build_file(const sec_vd& xcoords,
                  const std::string& xvtk_file_name, bool xis_ascii = true);

  ///
  ///  Construct the VTK "mesh" (vtkPolyData) object
  ///
  void construct_property(const sec_vd& xproperty, vtkPolyData& xresult);


private:

  ///
  /// Default constructor; disabled
  ///
  ///
  vtk_poly_data_builder();


  //===========================================================================

  ///
  ///  Get the namespace_poset.
  ///
  namespace_poset& name_space() const;

  ///
  ///  Construct the VTK "mesh" (vtkPolyData) object
  ///
  void construct_mesh(const sec_vd& xcoords, vtkPolyData& xresult);

  ///
  ///  Initialize the cell type map.
  ///
  void init_cell_type_map();

  ///
  ///  Get the count of the connectivity entries.
  ///
  size_type count_connectivity_entries(const sec_vd& xcoords) const;

  ///
  /// Get the connectivity for the mesh.
  ///
  void get_connectivity(const sec_vd& xmbr);

  ///
  /// Get the (row) dof count for a specified member (section).
  ///
  int get_dof_count(const sec_vd& xmbr) const;

  ///
  /// Get the (row) dofs for a specified member (section).
  ///
  dof_type* get_dofs(const sec_vd& xmbr) const;

  // ==========================================================================
  // DATA MEMBERS
  // ==========================================================================

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
  block<int> _vtk_cell_types;

  ///
  ///  Block (array) containing the VTK cell connectivities.
  ///
  block<vtkIdType> _vtk_cell_connectivity;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

 
} // namespace tool

#endif // ifndef VTK_POLY_DATA_BUILDER_H
