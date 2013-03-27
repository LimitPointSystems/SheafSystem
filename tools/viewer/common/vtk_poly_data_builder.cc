// $RCSfile: vtk_poly_data_builder.cc,v $ $Revision: 1.28 $ $Date: 2013/03/13 00:59:09 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class vtk_poly_data_builder

#include "vtk_poly_data_builder.h"
#include "assert_contract.h"
#include "base_space_member.h"
#include "eval_iterator.h"
#include "namespace_poset.h"
#include "sec_vd_space.h"

#include "vtkPolyData.h"
#include "vtkPolyDataWriter.h"
#include "vtkDoubleArray.h"
#include "vtkFieldData.h"
#include "vtkIntArray.h"

#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkPointData.h"

//#unfine DIAGNOSTIC_OUTPUT
// #define DIAGNOSTIC_OUTPUT

// Workaround for MS Visual C++
using namespace tool;

// ============================================================================
// ANY FACET
// ============================================================================


///
bool
tool::vtk_poly_data_builder::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const vtk_poly_data_builder*>(other) != 0;

  // Postconditions:

  return result;
}

 

///
tool::vtk_poly_data_builder*
tool::vtk_poly_data_builder::
clone() const
{
  vtk_poly_data_builder* result;

  // Preconditions:

  // Body:

  result = new vtk_poly_data_builder();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}


///
tool::vtk_poly_data_builder&
tool::vtk_poly_data_builder::
operator=(const vtk_poly_data_builder& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

///
bool
tool::vtk_poly_data_builder::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(any::invariant());

    // Invariances for this class:

    ///@todo
    ///     invariance(_coords_dof_buf.ub() == 3);
    ///     invariance(_coords_dof_buf.ct() == _coords_dof_buf.ub());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}



// ============================================================================
// VTK_DATA_SET_BUILDER FACET
// ============================================================================

///
tool::vtk_poly_data_builder::
vtk_poly_data_builder(const vtk_poly_data_builder& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}


///
tool::vtk_poly_data_builder::
~vtk_poly_data_builder()
{

  // Preconditions:


  // Body:

  // Nothing to do.

  // Postconditions:

  // Exit:

  return;
}

///
tool::vtk_poly_data_builder::
vtk_poly_data_builder(namespace_poset& xns)
{
  // Preconditions:

  // Body:

  _name_space = &xns;

  // Initialize the mapping from sheaf cell types to vtk cell types.

  init_cell_type_map();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}



///
void
tool::vtk_poly_data_builder::
build_file(const sec_vd& xcoords, const sec_vd& xproperty,
           const string& xvtk_file_name, bool xis_ascii)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);
  require(xproperty.state_is_read_accessible());
  require(xproperty.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));
  require(!xvtk_file_name.empty());

  // Body:


  // Create a vtk data object.

  vtkPolyData* lug = build(xcoords, xproperty);

  // Create a vtk data object writer and set it to write
  // either ascii or binary.

  vtkPolyDataWriter* writer = vtkPolyDataWriter::New();
  writer->SetInput(lug);
  writer->SetFileName(xvtk_file_name.c_str());

  if(xis_ascii)
    writer->SetFileTypeToASCII();
  else
    writer->SetFileTypeToBinary();

  // Actually write the file.

  writer->Write();

  // Cleanup.

  writer->Delete();
  lug->Delete();


  // Postconditions:


  // Exit:

  return;

}

///
void
tool::vtk_poly_data_builder::
build_file(const sec_vd& xcoords,
           const string& xvtk_file_name, bool xis_ascii)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);
  require(!xvtk_file_name.empty());

  // Body:


  // Create a vtk data object.

  vtkPolyData* lug = build(xcoords);

  // Create a vtk data object writer and set it to write
  // either ascii or binary.

  vtkPolyDataWriter* writer = vtkPolyDataWriter::New();
  writer->SetInput(lug);
  writer->SetFileName(xvtk_file_name.c_str());

  if(xis_ascii)
    writer->SetFileTypeToASCII();
  else
    writer->SetFileTypeToBinary();

  // Actually write the file.

  writer->Write();

  // Cleanup.

  writer->Delete();
  lug->Delete();


  // Postconditions:


  // Exit:

  return;
}


///
vtkPolyData*
tool::vtk_poly_data_builder::
build(const sec_vd& xcoords, const sec_vd& xproperty)
{
  vtkPolyData* result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);
  require(xproperty.state_is_read_accessible());
  require(xproperty.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));

  // Body:

  result = vtkPolyData::New();

  build_pa(xcoords, xproperty, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
vtkPolyData*
tool::vtk_poly_data_builder::
build(const sec_vd& xcoords)
{
  vtkPolyData* result;

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);

  // Body:

  result = vtkPolyData::New();

  build_pa(xcoords, *result);

  // Postconditions:


  // Exit:

  return result;
}

///
void
tool::vtk_poly_data_builder::
build_pa(const sec_vd& xcoords, const sec_vd& xproperty, vtkPolyData& xresult)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);
  require(xproperty.state_is_read_accessible());
  require(xproperty.schema().base_space().is_same_state(&xcoords.schema().base_space()));
  require(xproperty.schema().evaluation().is_same_state(&xcoords.schema().evaluation()));
  require(&xresult != 0);

  // Body:

  construct_mesh(xcoords, xresult);

  // Add the property to the vtkDataSet

  construct_property(xproperty, xresult);

#ifdef DIAGNOSTIC_OUTPUT

  vtkIndent lindent;
  xresult.PrintSelf(cout, lindent);
#endif

  // Postconditions:


  // Exit:

  return;
}

///
void
tool::vtk_poly_data_builder::
build_pa(const sec_vd& xcoords, vtkPolyData& xresult)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);
  require(&xresult != 0);

  // Body:

  construct_mesh(const_cast<sec_vd&>(xcoords), xresult);

  // Postconditions:


  // Exit:

  return;
}

// ============================================================================
// PRIVATE MEMBER FUNCTIONS
// ============================================================================

///
tool::vtk_poly_data_builder::
vtk_poly_data_builder()
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

///
void
tool::vtk_poly_data_builder::
init_cell_type_map()
{
  // Preconditions:

  require(name_space().state_is_read_accessible());

  // Body:

  poset* lprototypes =
    &name_space().member_poset<poset>(base_space_member::prototypes_poset_name(), false);
  lprototypes->get_read_access();

  _cell_type_map.reserve(lprototypes->member_index_ub().pod());

  _cell_type_map.set_ct(_cell_type_map.ub());
  _cell_type_map.assign(0);

  base_space_member lmbr;
  lmbr.attach_to_state(lprototypes, "segment");
  _cell_type_map.set_item(lmbr.type_id(), 3);

  lmbr.attach_to_state(lprototypes, "segment_complex");
  _cell_type_map.set_item(lmbr.type_id(), 3);

  //   lmbr.attach_to_state(lprototypes, "triangle");
  //   _cell_type_map.set_item(lmbr.type_id(), 5);

  //   lmbr.attach_to_state(lprototypes, "triangle_nodes");
  //   _cell_type_map.set_item(lmbr.type_id(), 5);

  //   lmbr.attach_to_state(lprototypes, "quad");
  //   _cell_type_map.set_item(lmbr.type_id(), 9);

  //   lmbr.attach_to_state(lprototypes, "quad_nodes");
  //   _cell_type_map.set_item(lmbr.type_id(), 9);

  //   lmbr.attach_to_state(lprototypes, "hex");
  //   _cell_type_map.set_item(lmbr.type_id(), 12);

  //   lmbr.attach_to_state(lprototypes, "hex_nodes");
  //   _cell_type_map.set_item(lmbr.type_id(), 12);

  //   lmbr.attach_to_state(lprototypes, "tetra");
  //   _cell_type_map.set_item(lmbr.type_id(), 10);

  //   lmbr.attach_to_state(lprototypes, "tetra_nodes");
  //   _cell_type_map.set_item(lmbr.type_id(), 10);

  lmbr.detach_from_state();
  lprototypes->release_access();

  // Postconditions:

  // Exit:

  return;
}


///
void
tool::vtk_poly_data_builder::
get_connectivity(const sec_vd& xcoords)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 2);

  // Body:

  // Count the number of eval cells and connectivity entries.

  // Allocate the vtk cell type array.

  size_type leval_ct = xcoords.schema().evaluation_ct();
  _vtk_cell_types.reserve(leval_ct);
  _vtk_cell_types.set_ct(0);

  // Allocate the vtk cell connectivity array.

  int num_cells = leval_ct;

  size_type lconn_ct = count_connectivity_entries(xcoords);
  size_type lconn_tuple_ct = lconn_ct + leval_ct;
  _vtk_cell_connectivity.reserve(lconn_tuple_ct);
  _vtk_cell_connectivity.set_ct(0);

  // Get the client id space for the discretization subposet.

  const index_space_handle& ldisc_space =
    xcoords.schema().discretization().id_space();

  // Iterate over the evluation subposet, transferring the
  // connectivity and type  data.

  eval_iterator litr(xcoords.schema());

  while(!litr.is_done())
  {
    // Convert the cell type to vtk and transfer to the vtk array.

    int lvtk_cell_type = _cell_type_map[litr.type_id()];
    _vtk_cell_types.push_back(lvtk_cell_type);

    // We're assuming that the discretiation subposet for the coordinate
    // field is the vertices, so the "discretization members" is the
    // "connectivity".

    block<scoped_index>& ldisc_ids = litr.discretization_members();
    size_type ldisc_ct = ldisc_ids.ct();

    _vtk_cell_connectivity.push_back(ldisc_ct);

    // Iterate over the connectivity (discretization members)
    // for this evaluation member.

    for(size_type i=0; i<ldisc_ct; ++i)
    {
      scoped_index ldisc_id = ldisc_ids[i];

      int lclient_id = ldisc_space.pod(ldisc_id);

      // Save the current member of the connectivity.

      _vtk_cell_connectivity.push_back(lclient_id);
    }

    // Move to the next evaluation member.

    litr.next();
  }

  // Postconditions:

  // Exit:

  return;
}

///
sheaf::size_type
tool::vtk_poly_data_builder::
count_connectivity_entries(const sec_vd& xcoords) const
{
  size_type result = 0;

  // Preconditions:

  require(xcoords.state_is_read_accessible());

  // Body:

  eval_iterator litr(xcoords.schema());
  while(!litr.is_done())
  {
    result += litr.discretization_members().ct();
    litr.next();
  }

  // Postconditions:

  ensure(result > 0);

  // Exit:

  return result;
}


///
sheaf::namespace_poset&
tool::vtk_poly_data_builder::
name_space() const
{
  return *_name_space;
}

///
void
tool::vtk_poly_data_builder::
construct_mesh(const sec_vd& xcoords, vtkPolyData& xresult)
{
  // Preconditions

  require(xcoords.df() == 1);

  // Body:

  // Allocate the vtk points object for the coordinates field.

  vtkPoints* vtk_points = vtkPoints::New();
  int num_points = xcoords.schema().discretization_ct();
  vtk_points->SetNumberOfPoints(num_points);

  int num_vtk_points = vtk_points->GetNumberOfPoints();

  int coord_dof_count = get_dof_count(xcoords);

  dof_type* coord_dofs = get_dofs(const_cast<sec_vd&>(xcoords));

  vtkDoubleArray* vtk_coord_dofs = vtkDoubleArray::New();
  vtk_coord_dofs->SetName(xcoords.name().c_str());

  int num_comps = xcoords.df();

  vtk_coord_dofs->SetNumberOfComponents(3);  // Must be 3 for vtkPoints (coordinates)

  dof_type x[3];

  int num_tuples = coord_dof_count/num_comps;
  vtk_coord_dofs->SetNumberOfTuples(num_tuples);
  int index = 0;
  for(int i=0; i<num_tuples; ++i)
  {
    x[0] = coord_dofs[index++];
    if(num_comps==2)
      x[1] = coord_dofs[index++];
    else
      x[1] = 0.0;
    x[2] = 0.0;
    vtk_coord_dofs->SetTuple(i, x);
  }

  vtk_points->SetData(vtk_coord_dofs);
  vtk_points->SetDataTypeToDouble();

  // Connectivity:

  get_connectivity(xcoords);

  vtkCellArray* vtk_cells = vtkCellArray::New();
  int num_cells = _vtk_cell_types.ct();
  vtk_cells->Allocate(num_cells);

  vtkIdTypeArray* vtk_connectivity = vtkIdTypeArray::New();
  vtk_connectivity->SetNumberOfComponents(1);
  vtk_connectivity->SetArray(_vtk_cell_connectivity.base(), _vtk_cell_connectivity.ct(), 1);

  vtk_cells->SetCells(num_cells, vtk_connectivity);

  xresult.SetPoints(vtk_points);
  xresult.SetPolys(vtk_cells);

  vtk_points->Delete();
  vtk_cells->Delete();
  vtk_connectivity->Delete();
  vtk_coord_dofs->Delete();

  // Postconditions:

}

///
void
tool::vtk_poly_data_builder::
construct_property(const sec_vd& xproperty, vtkPolyData& xresult)
{
  // Preconditions:

  require(xproperty.df() == 1);

  // Body:

  vtkDoubleArray* propertyArray = vtkDoubleArray::New();

  int dof_count = get_dof_count(xproperty);
  dof_type* dofs = get_dofs(xproperty);

  propertyArray->SetName(xproperty.name().c_str());

  sec_rep_space* lhost = xproperty.host();

  propertyArray->SetNumberOfComponents(1);
  propertyArray->SetArray(dofs, dof_count, 1);
  xresult.GetPointData()->SetScalars(propertyArray);

  propertyArray->Delete();

  // Postconditions:

}


///
int
tool::vtk_poly_data_builder::
get_dof_count(const sec_vd& xmbr) const
{
  return xmbr.schema().row_dof_ct();
}

///
tool::vtk_poly_data_builder::dof_type*
tool::vtk_poly_data_builder::
get_dofs(const sec_vd& xmbr) const
{
  const section_dof_map& dof_map = xmbr.dof_map();

  dof_type* result = reinterpret_cast<dof_type*>(const_cast<section_dof_map&>(dof_map).dof_tuple());

  return result;
}

// ============================================================================
//  NON-MEMBER FUNCTIONS
// ============================================================================

