
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class vtk_abstract_grid_builder

#ifndef VTK_ABSTRACT_GRID_BUILDER_H
#define VTK_ABSTRACT_GRID_BUILDER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef SHEAF_H
#include "sheaf.h"
#endif

class vtkDataSet;
class vtkDataArray;
class vtkDoubleArray;
class vtkIdTypeArray;
class vtkUnstructuredGrid;

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{
class base_space_poset;
class sec_rep_space;
}

///
/// Namespace for the tools component of the sheaf system.
///
namespace tool
{

using namespace sheaf;
using namespace fiber_bundle;

///
/// Abstract class for creating a vtkUnstructuredGrid from sheaf field objects.
///
class SHEAF_DLL_SPEC vtk_abstract_grid_builder : public any
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
  virtual vtk_abstract_grid_builder* clone() const;

  ///
  /// Assignment operator
  ///
  ///
  virtual vtk_abstract_grid_builder& operator=(const vtk_abstract_grid_builder& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  // ===========================================================
  // VTK_ABSTRACT_GRID_BUILDER FACET
  // ===========================================================

  ///
  /// If this instance's namespace is not equal to xns, this instance is
  /// initialized to have namespace xns.
  ///
  void set_name_space(namespace_poset& xns);

  ///
  /// Destructor
  ///
  virtual ~vtk_abstract_grid_builder();

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and xproperty.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords, const sec_vd& xproperty);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, xproperty1, and xproperty2.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords,
                             const sec_vd& xproperty1,
                             const sec_vd& xproperty2);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords only.
  ///
  vtkUnstructuredGrid* build(const sec_vd& xcoords);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords and xproperty
  /// (pre-allocated version).
  ///
  void build_pa(const sec_vd& xcoords, const sec_vd& xproperty,
                vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords, xproperty1, and xproperty2
  /// (pre-allocated version).
  ///
  void build_pa(const sec_vd& xcoords,
                const sec_vd& xproperty1,
                const sec_vd& xproperty2,
                vtkUnstructuredGrid& xresult);

  ///
  /// Builds a vtkUnstructuredGrid from xcoords only with no property
  /// (pre-allocated version).  The result is a reprecentation for the mesh
  /// only.
  ///
  void build_pa(const sec_vd& xcoords, vtkUnstructuredGrid& xresult);

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
  /// Array of top ids for points.
  ///
  vtkIdTypeArray* vtk_pt_label_ids() const;

  ///
  /// Array of top ids for cells.
  ///
  vtkIdTypeArray* vtk_cell_label_ids() const;

protected:

  ///
  /// Defualt constructor.
  ///
  vtk_abstract_grid_builder();
  

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
  /// Array of top ids for points.
  ///
  vtkIdTypeArray* _vtk_pt_label_ids;

  ///
  /// Array of top ids for cells.
  ///
  vtkIdTypeArray* _vtk_cell_label_ids;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

 
} // namespace tool

#endif // ifndef VTK_ABSTRACT_GRID_BUILDER_H
