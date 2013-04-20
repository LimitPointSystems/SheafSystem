
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/test_case_3d_irregular.cc
/// Implementation for class test_case_3d_irregular.


#include "test_case_3d_irregular.h"

#include "base_space_poset.h"
#include "unstructured_block.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_rep_space.h"
#include "sec_st2_e3.h"
#include "sec_stp_space.h"
#include "trilinear_3d.h"

#include "vtkConnectivityFilter.h"
#include "vtkDelaunay3D.h"
#include "vtkMath.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"


///@todo Cleanup and refactor to eliminate duplicate code.

// Workaround for Microsoft C++ bug.
using namespace tool;

///
tool::test_case_3d_irregular::
test_case_3d_irregular(fiber_bundles_namespace& xns, size_type xnum_points)
{
  _name_space = &xns;
  _num_points = xnum_points;

  create_vtk_data_set();
  make_base_space();
  make_coordinates();
  make_scalars();
  make_vectors();
  make_tensors();
}


///
tool::test_case_3d_irregular::
~test_case_3d_irregular()
{}

///
void
tool::test_case_3d_irregular::
make_base_space()
{
  // Make the base space.

  _mesh_poset = &_name_space->new_base_space<unstructured_block>("mesh_base_space", "", "", 3, true);

  _mesh_poset->get_read_write_access();

  string proto_member_name;

  //Only create triangular meshes here.

  proto_member_name = "tetra_nodes";

  poset_path lproto_path(base_space_member::prototypes_poset_name(),  proto_member_name);

  _block_0 = new unstructured_block(_mesh_poset,
                                    lproto_path,
                                    _cell_ids,
                                    _num_cell_ids,
                                    true);

  _block_0->put_name("unstructured_block_0", true, false);

  // cout << *_mesh << endl;
}

///
void
tool::test_case_3d_irregular::
make_coordinates()
{
  // Preconditions:

  // Body:

  // Make unstructured (coordinate) sec_rep_space.

  string lname = "coordinate_section_space";

  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  _coordinates_space = &_name_space->new_section_space<sec_e3>(lname,
							       _block_0->path(),
							       lpath,
							       true);
  
  // Add dofs to the coordinate space.

  _coordinates_space->get_read_write_access();

  // Make coordinate dofs


  dof_type x0 = 1.0;
  dof_type x1 = 2.0;
  dof_type y0 = 1.0;
  dof_type y1 = 2.0;
  dof_type z0 = 0.5;
  dof_type z1 = 1.5;

  dof_type corner_coords[] = { x0, y0, z0,
                               x1, y0, z0,
                               x1, y1, z0,
                               x0, y1, z0,
                               x0, y0, z1,
                               x1, y0, z1,
                               x1, y1, z1,
                               x0, y1, z1 };

  // Points are originally on (-1,+1), so scale them to the corner coords.

  trilinear_3d levaluator;

  dof_type local_coords[3];
  dof_type values[3];

  for(int i=0; i<_num_points; i++)
  {
    // Delaunay generated points are on (-1,1)

    int n0 = 3*i;
    int n1 = n0+1;
    int n2 = n1+1;

    local_coords[0] = _points[n0];
    local_coords[1] = _points[n1];
    local_coords[2] = _points[n2];

    levaluator.value_at_coord(corner_coords, 24, local_coords, 3, values, 3);

    _points[n0] = values[0];
    _points[n1] = values[1];
    _points[n2] = values[2];
  }

  sec_e3 coordinates(_coordinates_space);
  coordinates.put_name("coordinates_0", true, false);

  coordinates.put_dof_tuple(_points, 3*_num_points*sizeof(dof_type));

  // Detach members so destructor won't complain.

  coordinates.detach_from_state();

  // Postconditions:

}

///
void
tool::test_case_3d_irregular::
make_scalars()
{
  // Preconditions:

  // Body:

  // Make sec_rep_space.

  string lname = "scalars_section_space";

  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  _scalars_space = &_name_space->new_section_space<sec_at0>(lname,
							    _block_0->path(),
							    lpath,
							    true);
  
  // Add dofs to the test space.

  _scalars_space->get_read_write_access();

  block<dof_type> dofs;

  make_scalar_dofs(dofs);

  sec_at0 scalar_0(_scalars_space);
  scalar_0.put_name("scalar_0", true, false);
  scalar_0.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  // Make other members for testing (identical for now).

  sec_at0 scalar_1(_scalars_space);
  scalar_1.put_name("scalar_1", true, false);
  scalar_1.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  sec_at0 scalar_2(_scalars_space);
  scalar_2.put_name("scalar_2", true, false);
  scalar_2.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  // Detach members so destructor won't complain.

  scalar_0.detach_from_state();
  scalar_1.detach_from_state();
  scalar_2.detach_from_state();
}

///
void
tool::test_case_3d_irregular::
make_scalar_dofs(block<dof_type>& xdofs)
{
  // Preconditions:

  require(_scalars_space->state_is_read_accessible());

  // Body:

  size_type dofs_ct = _coordinates_space->schema().row_dof_ct();
  xdofs.reserve(dofs_ct);
  xdofs.set_ct(dofs_ct);

  dof_type global_coordinates[3];

  for(int i=0; i<_num_points; ++i)
  {
    int index = 3*i;
    global_coordinates[0] = _points[index++];
    global_coordinates[1] = _points[index++];
    global_coordinates[2] = _points[index];

    // Scalar = (1+x)*(1+y)*(1+z)

    xdofs[i] = scalar_value(global_coordinates, 3);
  }

  // Postconditions:

}

///
tool::test_case_3d_irregular::value_type
tool::test_case_3d_irregular::
scalar_value(value_type* xcoordinates, size_type xcoordinates_ub)
{
  value_type result = 20.0;

  // Preconditions:

  require(xcoordinates_ub >= 3);

  // Body:

  // result = xcoordinates[2] + 10.0;

  for(int i=0; i<3; ++i)
  {
    result += (i+1)*xcoordinates[i];
  }

  // Postconditions:

  // Exit:

  return result;
}


///
void
tool::test_case_3d_irregular::
make_vectors()
{
  // Preconditions:

  // Body:

  // Make unstructured (vector) sec_rep_space.

  string lname = "vectors_section_space";

  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  _vectors_space = &_name_space->new_section_space<sec_e3>(lname,
							   _block_0->path(),
							   lpath,
							   true);  

  // Add dofs to the vector space.

  _vectors_space->get_read_write_access();

  block<dof_type> dofs;

  make_vector_dofs(dofs);

  sec_e3 vector_0(_vectors_space);
  vector_0.put_name("vector_0", true, false);
  vector_0.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  sec_e3 vector_1(_vectors_space);
  vector_1.put_name("vector_1", true, false);
  vector_1.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  sec_e3 vector_2(_vectors_space);
  vector_2.put_name("vector_2", true, false);
  vector_2.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  // Detach members so destructor won't complain.

  vector_0.detach_from_state();
  vector_1.detach_from_state();
  vector_2.detach_from_state();

  // Postconditions:

}

///
void
tool::test_case_3d_irregular::
make_vector_dofs(block<dof_type>& xdofs)
{
  // Preconditions:

  require(_vectors_space->state_is_read_accessible());

  // Body:

  size_type dofs_ct = _vectors_space->schema().row_dof_ct();
  xdofs.reserve(dofs_ct);
  xdofs.set_ct(dofs_ct);

  dof_type global_coordinates[3];
  dof_type values[3];

  for(int i=0; i<_num_points; ++i)
  {
    int index = 3*i;
    global_coordinates[0] = _points[index++];
    global_coordinates[1] = _points[index++];
    global_coordinates[2] = _points[index];

    vector_value(global_coordinates, 3, values, 3);

    index = 3*i;
    xdofs[index++] = values[0];
    xdofs[index++] = values[1];
    xdofs[index]   = values[2];
  }

  // Postconditions:

}

///
void
tool::test_case_3d_irregular::
vector_value(value_type* xcoordinates, size_type xcoordinates_ub,
             value_type* xresult, size_type xresult_ub)
{

  // Preconditions:

  require(xcoordinates != 0);
  require(xcoordinates_ub >= 3);
  require(xresult != 0);
  require(xresult_ub >= 3);

  // Body:

  //   value_type sum = 0.0;

  //   for(int i=0; i<3; ++i)
  //   {
  //     sum += xcoordinates[i];
  //   }

  //   xresult[0] = 20.0+sum;
  //   xresult[1] = 20.0+2*sum;
  //   xresult[2] = 20.0+3*sum;

  xresult[0] = xcoordinates[0];
  xresult[1] = 1.0+xcoordinates[1];
  xresult[2] = 2.0+xcoordinates[2];

  // Postconditions:

  // Exit:
}

///
void
tool::test_case_3d_irregular::
make_tensors()
{
  // Preconditions:

  // Body:

  // Make unstructured (tensor) sec_rep_space.

  string lname = "tensors_section_space";

  poset_path lpath("sec_rep_descriptors", "vertex_element_dlinear");

  _tensors_space = &_name_space->new_section_space<sec_st2_e3>(lname,
							       _block_0->path(),
							       lpath,
							       true);
  
  // Add dofs to the tensor space.

  _tensors_space->get_read_write_access();

  block<dof_type> dofs;

  make_tensor_dofs(dofs);

  sec_st2_e3 tensor_0(_tensors_space);
  tensor_0.put_name("tensor_0", true, false);
  tensor_0.put_dof_tuple(dofs.base(), dofs.ct()*sizeof(dof_type));

  // Detach members so destructor won't complain.

  tensor_0.detach_from_state();

  // Postconditions:

}


///
void
tool::test_case_3d_irregular::
make_tensor_dofs(block<dof_type>& xdofs)
{
  // Preconditions:

  require(_tensors_space->state_is_read_accessible());

  // Body:

  size_type dofs_ct = _tensors_space->schema().row_dof_ct();
  xdofs.reserve(dofs_ct);
  xdofs.set_ct(dofs_ct);

  dof_type global_coordinates[3];
  dof_type values[6];

  for(int i=0; i<_num_points; ++i)
  {
    int index = 3*i;
    global_coordinates[0] = _points[index++];
    global_coordinates[1] = _points[index++];
    global_coordinates[2] = _points[index];

    tensor_value(global_coordinates, 3, values, 6);

    index = 6*i;
    xdofs[index++] = values[0];
    xdofs[index++] = values[1];
    xdofs[index++] = values[2];
    xdofs[index++] = values[3];
    xdofs[index++] = values[4];
    xdofs[index]   = values[5];
  }

  // Postconditions:

}

///
void
tool::test_case_3d_irregular::
tensor_value(value_type* xcoordinates, size_type xcoordinates_ub,
             value_type* xresult, size_type xresult_ub)
{
  // Stretching of prismatic bar under it's own weight.

  // Preconditions:

  require(xcoordinates != 0);
  require(xcoordinates_ub >= 3);
  require(xresult != 0);
  require(xresult_ub >= 6);

  // Body:

  double x = xcoordinates[0];
  double y = xcoordinates[1];
  double z = xcoordinates[2];

  double A = 1.0;
  double B = 1.0;
  double C = 1.0;

  double sxx = A*x;
  ;
  double syy = C*y;
  ;
  double szz = B*z;
  double sxy = 0.0;
  double sxz = 0.0;
  double syz = 0.0;

  // Put in the correct order for libSheaf.

  xresult[0] = sxx;
  xresult[1] = sxy;
  xresult[2] = syy;
  xresult[3] = sxz;
  xresult[4] = syz;
  xresult[5] = szz;

  //   for(int j=0; j<6; ++j)
  //     cout << "  " << xresult[j];
  //   cout << endl;

  // Postconditions:

  // Exit:
}

///
void
tool::test_case_3d_irregular::
create_vtk_data_set()
{
  double xmin = -1.0;
  double xmax =  1.0;
  double ymin = -1.0;
  double ymax =  1.0;
  double zmin = -1.0;
  double zmax =  1.0;

  // Generate random points on (-1,1)and throw away those which don't lie
  // within a sphere of radius 1.

  vtkPoints* points = vtkPoints::New();

  int count = 0;
  while(count < _num_points)
  {
    double x = vtkMath::Random(xmin, xmax);
    double y = vtkMath::Random(ymin, ymax);
    double z = vtkMath::Random(zmin, zmax);

    double r2 = x*x + y*y + z*z;
    if(r2 <= 1.0)
    {
      points->InsertPoint(count, x, y, z);
      count++;
    }
  }

  vtkPolyData* profile = vtkPolyData::New();
  profile->SetPoints(points);

  vtkDelaunay3D* del = vtkDelaunay3D::New();
  del->SetInput(profile);
  del->SetTolerance(0.001);

  // Force update.

  del->Update();

  vtkUnstructuredGrid* ugrid = del->GetOutput();

  vtkUnstructuredGridWriter* writer = vtkUnstructuredGridWriter::New();
  writer->SetInput(ugrid);
  writer->SetFileName("test.vtk");
  writer->Write();
  writer->Delete();

  //===================================================

  int index = 0;
  _points = new double[3*_num_points];

  double coords[3];
  for(int i=0; i<_num_points; ++i)
  {
    ugrid->GetPoint(i, coords);

    _points[index++] = coords[0];
    _points[index++] = coords[1];
    _points[index++] = coords[2];
  }

  _num_cells = ugrid->GetNumberOfCells();

  // Assume triangles ONLY.

  _num_cell_ids = _num_cells*4;

  _cell_ids = new pod_index_type[_num_cell_ids];

  vtkIdType npts;
  vtkIdType* pts;
  index = 0;
  for(int i=0; i<_num_cells; ++i)
  {
    ugrid->GetCellPoints(i, npts, pts);
    _cell_ids[index++] = pts[0];
    _cell_ids[index++] = pts[1];
    _cell_ids[index++] = pts[2];
    _cell_ids[index++] = pts[3];
  }

}

