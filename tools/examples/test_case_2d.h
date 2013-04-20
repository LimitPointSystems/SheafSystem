
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class test_case_2d.

#ifndef TEST_CASE_2D_H
#define TEST_CASE_2D_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_CONNECTIVITY_H
#include "block_connectivity.h"
#endif

//#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
//#endif

#ifndef SEC_ATO_H
#include "sec_at0.h"
#endif

#ifndef SEC_E2_H
#include "sec_e2.h"
#endif

namespace fiber_bundle
{
class base_space_poset;
class fiber_bundles_namespace;
class unstructured_block;
}

namespace tool
{

using namespace sheaf;
using namespace fiber_bundle; 
  
///
///
///
class SHEAF_DLL_SPEC test_case_2d
{

public:

  typedef block_connectivity::cell_type cell_type;
  typedef sec_e2::dof_type dof_type;
  typedef sec_e2::value_type value_type;

  ///
  ///
  ///
  test_case_2d(fiber_bundles_namespace& xns,
               size_type xi_size,
               size_type xj_size,
               cell_type xcell_type = block_connectivity::QUAD);

  ///
  /// Destructor.
  ///
  ~test_case_2d();


protected:

  ///
  /// Makes a mesh poset and a mesh block.
  ///
  void make_base_space();

  ///
  /// Make the coordinates section space and coordinates.
  ///
  void make_coordinates();

  ///
  /// Make the dofs for a coordinate section with corners xcoordinates_corners.
  ///
  void make_coordinate_dofs(dof_type* xcorner_coordinates,
                            size_type xcorner_coordinates_ub,
                            block<dof_type>& xdofs);

  ///
  /// Make the scalars.
  ///
  void make_scalars();

  ///
  /// Makes scalar section dofs.
  ///
  void make_scalar_dofs(block<dof_type>& xdofs);

  ///
  /// Make the vectorss.
  ///
  void make_vectors();

  ///
  /// Makes vector section dofs.
  ///
  void make_vector_dofs(block<dof_type>& xdofs);

  ///
  /// Make the tensors.
  ///
  void make_tensors();

  ///
  /// Makes tensor section dofs.
  ///
  void make_tensor_dofs(block<dof_type>& xdofs);

  ///
  /// The node id associated with (xi,xj).
  ///
  size_type node_id(size_type xi, size_type xj)
  {
    return (xi*(_j_size+1) + xj);
  };

  ///
  /// The value of the scalar field at global coordinates xcoordinates.
  ///
  value_type scalar_value(value_type* xcoordinates, size_type xcoordinates_ub);

  ///
  /// The value of the vextor field at global coordinates xcoordinates.
  ///
  void vector_value(value_type* xcoordinates, size_type xcoordinates_ub,
                    value_type* xresult, size_type xresult_ub);

  ///
  /// The value of the tensor field at global coordinates xcoordinates.
  ///
  void tensor_value(value_type* xcoordinates, size_type xcoordinates_ub,
                    value_type* xresult, size_type xresult_ub);


  // Data Members:

  fiber_bundles_namespace* _name_space;
  size_type _i_size;
  size_type _j_size;
  cell_type _cell_type;

  base_space_poset* _mesh_poset;
  unstructured_block* _block_0;

  sec_rep_space* _coordinates_space;
  sec_rep_space* _scalars_space;
  sec_rep_space* _vectors_space;
  sec_rep_space* _tensors_space;

  block<dof_type> _coords;
};
 
} // namespace tool

#endif // TEST_CASE_2D_H

