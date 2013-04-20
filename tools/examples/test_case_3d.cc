
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/test_case_3d.cc
/// Implementation for class test_case_3d.


#include "test_case_3d.h"

#include "base_space_poset.h"
#include "error_message.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_rep_space.h"
#include "sec_st2_e3.h"
#include "sec_stp_space.h"
#include "trilinear_3d.h"
#include "unstructured_block.h"

///@todo Cleanup and refactor to eliminate duplicate code.

// Workaround for Microsoft C++ bug.
using namespace tool;

///
tool::test_case_3d::
test_case_3d(fiber_bundles_namespace& xns,
             size_type xi_size,
             size_type xj_size,
             size_type xk_size,
             cell_type xcell_type)
{

  _name_space = &xns;
  _i_size = xi_size;
  _j_size = xj_size;
  _k_size = xk_size;
  _cell_type = xcell_type;

  make_base_space();

  make_coordinates();

  make_scalars();

  make_vectors();

  make_tensors();
}


///
tool::test_case_3d::
~test_case_3d()
{}

///
void
tool::test_case_3d::
make_base_space()
{
  // Make the base space.

  _mesh_poset = &_name_space->new_base_space<unstructured_block>("mesh_base_space",
								 "",
								 "",
								 3,
								 true);

  _mesh_poset->get_read_write_access();

  string proto_member_name;

  if(_cell_type == block_connectivity::HEX)
  {
    proto_member_name = "hex_nodes";
  }
  else if(_cell_type == block_connectivity::TETRA)
  {
    proto_member_name = "tetra_nodes";
  }
  else
  {
    post_fatal_error_message("Unrecognized cell type");
  }

  // Make a block of elements.

  poset_path lproto_path(base_space_member::prototypes_poset_name(),
                         proto_member_name);

  ///@todo Decide how we want to handle muliple blocks ( and the "whole" mesh).

  _block_0 = new unstructured_block(_mesh_poset, lproto_path, _i_size, _j_size, _k_size);
  _block_0->put_name("unstructured_block_0", true, false);

  //cout << *_mesh_poset << endl;
}

///
void
tool::test_case_3d::
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

  //block<dof_type> dofs;

  static dof_type corner_coordinates[24] =
    {
      0.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
      1.0, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 0.0, 1.0,
      1.0, 0.0, 1.0,
      1.0, 1.0, 1.0,
      0.0, 1.0, 1.0
    };

  make_coordinate_dofs(corner_coordinates, 24, _coords);

  //sec_e3_general* coordinates = new sec_e3_general(_coordinates_space, dofs.base(), dofs.ct());

  sec_e3 coordinates(_coordinates_space);
  coordinates.put_name("coordinates_0", true, false);
  coordinates.put_dof_tuple(_coords.base(), _coords.ct()*sizeof(dof_type));

  // Detach members so destructor won't complain.

  coordinates.detach_from_state();

  // Postconditions:

}

///
void
tool::test_case_3d::
make_coordinate_dofs(dof_type* xcorner_coordinates,
                     size_type xcorner_coordinates_ub,
                     block<dof_type>& xdofs)
{
  // Preconditions:

  require(_coordinates_space->state_is_read_accessible());
  require(xcorner_coordinates != 0);
  require(xcorner_coordinates_ub >= 24);

  // Body:

  size_type dofs_ct = _coordinates_space->schema().row_dof_ct();
  xdofs.reserve(dofs_ct);
  xdofs.set_ct(dofs_ct);

  trilinear_3d levaluator;

  dof_type local_coordinates[3];
  dof_type values[3];

  dof_type delu = 2.0/_i_size;
  dof_type delv = 2.0/_j_size;
  dof_type delw = 2.0/_k_size;

  size_type i_vertex_size = _i_size + 1;
  size_type j_vertex_size = _j_size + 1;
  size_type k_vertex_size = _k_size + 1;

  for(int i=0; i<i_vertex_size; ++i)
  {
    local_coordinates[0] = i*delu - 1.0;

    for(int j=0; j<j_vertex_size; ++j)
    {
      local_coordinates[1] = j*delv - 1.0;

      for(int k=0; k<k_vertex_size; ++k)
      {
        local_coordinates[2] = k*delw - 1.0;

        levaluator.value_at_coord(xcorner_coordinates,
                                  xcorner_coordinates_ub,
                                  local_coordinates,
                                  3,
                                  values,
                                  3);

        int index = 3*node_id(i, j, k);
        xdofs[index++] = values[0];
        xdofs[index++] = values[1];
        xdofs[index]   = values[2];
      }
    }
  }

  // Postconditions:

}

///
void
tool::test_case_3d::
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
tool::test_case_3d::
make_scalar_dofs(block<dof_type>& xdofs)
{
  // Preconditions:

  require(_scalars_space->state_is_read_accessible());

  // Body:

  size_type dofs_ct = _coordinates_space->schema().row_dof_ct();
  xdofs.reserve(dofs_ct);
  xdofs.set_ct(dofs_ct);

  dof_type global_coordinates[3];

  size_type i_vertex_size = _i_size + 1;
  size_type j_vertex_size = _j_size + 1;
  size_type k_vertex_size = _k_size + 1;

  for(int i=0; i<i_vertex_size; ++i)
  {
    for(int j=0; j<j_vertex_size; ++j)
    {
      for(int k=0; k<k_vertex_size; ++k)
      {
        int id = node_id(i, j, k);

        int index = 3*id;
        global_coordinates[0] = _coords[index++];
        global_coordinates[1] = _coords[index++];
        global_coordinates[2] = _coords[index];

        // Scalar = (1+x)*(1+y)*(1+z)

        xdofs[id] = scalar_value(global_coordinates, 3);
      }
    }
  }

  // Postconditions:

}

///
tool::test_case_3d::value_type
tool::test_case_3d::
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
tool::test_case_3d::
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
tool::test_case_3d::
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

  size_type i_vertex_size = _i_size + 1;
  size_type j_vertex_size = _j_size + 1;
  size_type k_vertex_size = _k_size + 1;

  for(int i=0; i<i_vertex_size; ++i)
  {
    for(int j=0; j<j_vertex_size; ++j)
    {
      for(int k=0; k<k_vertex_size; ++k)
      {
        int index = 3*node_id(i, j, k);
        global_coordinates[0] = _coords[index++];
        global_coordinates[1] = _coords[index++];
        global_coordinates[2] = _coords[index];

        vector_value(global_coordinates, 3, values, 3);

        index = 3*node_id(i, j, k);
        ;
        xdofs[index++] = values[0];
        xdofs[index++] = values[1];
        xdofs[index]   = values[2];
      }
    }
  }

  // Postconditions:

}

///
void
tool::test_case_3d::
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
tool::test_case_3d::
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
tool::test_case_3d::
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

  size_type i_vertex_size = _i_size + 1;
  size_type j_vertex_size = _j_size + 1;
  size_type k_vertex_size = _k_size + 1;

  for(int i=0; i<i_vertex_size; ++i)
  {
    for(int j=0; j<j_vertex_size; ++j)
    {
      for(int k=0; k<k_vertex_size; ++k)
      {
        int index = 3*node_id(i, j, k);
        global_coordinates[0] = _coords[index++];
        global_coordinates[1] = _coords[index++];
        global_coordinates[2] = _coords[index];

        tensor_value(global_coordinates, 3, values, 6);

        index = 6*node_id(i, j, k);
        xdofs[index++] = values[0];
        xdofs[index++] = values[1];
        xdofs[index++] = values[2];
        xdofs[index++] = values[3];
        xdofs[index++] = values[4];
        xdofs[index]   = values[5];
      }
    }
  }

  // Postconditions:

}

///
void
tool::test_case_3d::
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

