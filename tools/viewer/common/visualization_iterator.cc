
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

// Implementation for class visualization_iterator


#include "SheafSystem/visualization_iterator.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/binary_section_space_schema_member.h"
#include "SheafSystem/error_message.h"
#include "SheafSystem/eval_family.h"
#include "SheafSystem/visualization_iterator_1_1.h"
// #include "SheafSystem/visualization_iterator_1_2.h"
#include "SheafSystem/visualization_iterator_1_3.h"
#include "SheafSystem/visualization_iterator_4_2.h"
#include "SheafSystem/visualization_iterator_4_3.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/section_space_schema_member.h"
#include "SheafSystem/section_space_schema_poset.h"
#include "SheafSystem/sec_vd.h"
#include "SheafSystem/std_limits.h"
#include "SheafSystem/structured_block_1d.h"
#include "SheafSystem/structured_block_2d.h"
#include "SheafSystem/structured_block_3d.h"
#include "SheafSystem/subposet_member_iterator.h"
#include "SheafSystem/uniform_eval_family.h"
#include "vtkDoubleArray.h"
#include "vtkIdTypeArray.h"

//#define DIAGNOSTIC_OUTPUT 1

// Workaround for MS Visual C++
using namespace tool;
using namespace std;

// ===========================================================
// ANY FACET
// ===========================================================

bool
tool::visualization_iterator::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const visualization_iterator*>(xother) != 0;

  // Postconditions:

  // Exit:

  return result;
}

tool::visualization_iterator*
tool::visualization_iterator::
clone() const
{
  // Preconditions:

  // Body:

  visualization_iterator* result = 0; // Just to silence compiler.

  is_abstract();

  // Postconditions:

  // ensure(invariant());
  ensure(result != 0);

  // Exit:

  return result;
}

bool
tool::visualization_iterator::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(filtered_depth_first_iterator::invariant());

    disable_invariant_check();

    // The following is disabled because it can not be implemented
    // with our current invaraint machinery. It is true at client scope,
    // but not true in force_is_done called from put_anchor, i.e. it
    // is not true between the the we reset _coord_state and the time we
    // reset the anchor.

    //     invariance(is_initialized() ?
    //                anchor().is_same_state(&min(coordinates_schema().base_space(),
    //                                            property_schema().base_space())) :
    //                true);

    invariance(is_initialized() ? coordinates_schema().df() <= 3 : true);

    invariance((is_initialized() && has_property()) ?
               property_schema().df() <= 16 :
               true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit:

  return result;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

void
tool::visualization_iterator::
force_is_done()
{
  // Preconditions:

  // Body:

  _prop_state.down_set.set_ct(0);
  _prop_state.discretization_members.set_ct(0);

  /// @hack we're using coord_state.down_set for unmarking.
  /// Better not clear it here.
  _coord_state.discretization_members.set_ct(0);

  _vis_state.down_set.set_ct(0);
  _vis_state.discretization_members.set_ct(0);

  _above = true;
  _at    = false;

  _maximal_eval_id.invalidate();

  filtered_depth_first_iterator::force_is_done();

  // Postconditions:

  ensure(invariant());
  ensure(is_done());

  // Exit:

  return;
}

void
tool::visualization_iterator::
put_anchor(const section_space_schema_member& xcoords_schema,
           const section_space_schema_member& xprop_schema)
{
  // Preconditions:

  require(is_initialized() ? xcoords_schema.host()->is_same_state(coordinates_schema().host()) : true);
  require(is_initialized() ?xprop_schema.host()->is_same_state(property_schema().host()) : true);

  // Body:

  _has_property = true;

  initialize_states(xcoords_schema, xprop_schema);

  const abstract_poset_member& lsmaller =
    min(xcoords_schema.base_space(), xprop_schema.base_space());

  if(is_initialized())
  {
    put_anchor(lsmaller.index());
  }
  else
  {
    put_anchor(&lsmaller);
  }


  // Postconditions:

  ensure(coordinates_schema().is_same_state(&xcoords_schema));
  ensure(property_schema().is_same_state(&xprop_schema));
  ensure(is_done());

  // Exit:

  return;
}

void
tool::visualization_iterator::
put_anchor(const section_space_schema_member& xcoords_schema)
{
  // Preconditions:

  require(is_initialized() ? xcoords_schema.host()->is_same_state(coordinates_schema().host()) : true);

  // Body:

  _has_property = false;

  initialize_states(xcoords_schema);

  if(is_initialized())
  {
    put_anchor(xcoords_schema.base_space().index());
  }
  else
  {
    put_anchor(&xcoords_schema.base_space());
  }


  // Postconditions:

  ensure(coordinates_schema().is_same_state(&xcoords_schema));
  ensure(is_done());

  // Exit:

  return;
}

void
tool::visualization_iterator::
reset(bool xreset_markers)
{
  // Preconditions:

  require(is_initialized());
  require(anchor().state_is_read_accessible());

  // Body:

  define_old_variable(bool old_descending = _descending);
  define_old_variable(bool old_strict = _strict);

  _cell_seq_id = 0;
  _pt_seq_id   = 0;

  /// @error reset() does not correctly reset
  /// the section_iteration_state variables.

  filtered_depth_first_iterator::reset(xreset_markers);

  // Postconditions:

  ensure(invariant());
  ensure(descending() == old_descending);
  ensure(strict() == old_strict);

  // Exit:

  return;
}

// ===========================================================
// VISUALIZATION_ITERATOR FACET
// ===========================================================

tool::visualization_iterator*
tool::visualization_iterator::
new_visualization_iterator(const section_space_schema_member& xcoords_schema,
                           const section_space_schema_member& xprop_schema,
                           bool xinitialize)
{
  visualization_iterator* result;

  // Preconditions:

  require(xcoords_schema.state_is_read_accessible());
  require(xprop_schema.state_is_read_accessible());

  // Body:

  if(xcoords_schema.evaluator_family_name() == "uniform")
  {
    // Uniform coordinates.

    if(xprop_schema.rep().eval_is_above_disc())
    {
      if(xinitialize)
      {
        result = new visualization_iterator_4_2(xcoords_schema, xprop_schema);
      }
      else
      {
        result = new visualization_iterator_4_2();
      }
    }
    else
    {
      if(xinitialize)
      {
        result = new visualization_iterator_4_3(xcoords_schema, xprop_schema);
      }
      else
      {
        result = new visualization_iterator_4_3();
      }
    }
  }
  else if(xcoords_schema.evaluator_family_name() == "dlinear")
  {
    // Vertex element dlinear coordinates

    if(xprop_schema.evaluator_family_name() == "dlinear")
    {
      // Vertex element dlinear property.

      if(xinitialize)
      {
        result = new visualization_iterator_1_1(xcoords_schema, xprop_schema);
      }
      else
      {
        result = new visualization_iterator_1_1();
      }
    }
    else if(xprop_schema.evaluation().name() == "__elements")
    {
      // Property eval same as coordinates eval.

      if(xprop_schema.rep().eval_is_above_disc())
      {
        // Property disc is below elements, but not just vertices.
        // Ignore dofs not at vertices.

        if(xinitialize)
        {
          result = new visualization_iterator_1_1(xcoords_schema, xprop_schema);
        }
        else
        {
          result = new visualization_iterator_1_1();
        }
      }
      else
      {
        // Property disc is at or above elements
        // (typically element element constant).

        if(xinitialize)
        {
          result = new visualization_iterator_1_3(xcoords_schema, xprop_schema);
        }
        else
        {
          result = new visualization_iterator_1_3();
        }
      }
    }
    else
    {
      // Property eval is not same as coordinates;
      // we don't support this yet.

      post_fatal_error_message("Property rep not supported with this coordinates rep.");
    }
  }
  else if(xcoords_schema.rep().name() == "vertex_vertex_constant")
  {
    // Vertex_vertex_constant coordinates

    if(xprop_schema.rep().name() == "vertex_vertex_constant")
    {
      // Vertex_vertex_constant property.

      if(xinitialize)
      {
        result = new visualization_iterator_1_1(xcoords_schema, xprop_schema);
      }
      else
      {
        result = new visualization_iterator_1_1();
      }
    }
    else
    {
      // Property rep is not same as coordinates;
      // we don't support this yet.

      post_fatal_error_message("Property rep not supported with this coordinates rep.");
    }
  }
  else
  {
    // Unsupported coordinates rep.

    post_fatal_error_message("Coordinates rep not supported.");
  }

  // Postconditions:

  ensure(result != 0);
  ensure(xinitialize ?
         result->coordinates_schema().is_same_state(&xcoords_schema) :
         true);
  ensure(xinitialize ?
         result->property_schema().is_same_state(&xprop_schema) :
         true);

  // Exit:

  return result;
}

tool::visualization_iterator*
tool::visualization_iterator::
new_visualization_iterator(const section_space_schema_member& xcoords_schema,
                           bool xinitialize)
{
  visualization_iterator* result;

  // Preconditions:

  require(xcoords_schema.state_is_read_accessible());

  // Body:

  if(xcoords_schema.evaluator_family_name() == "uniform")
  {
    // Uniform coordinates.

    if(xinitialize)
    {
      result = new visualization_iterator_4_2(xcoords_schema);
    }
    else
    {
      result = new visualization_iterator_4_2();
    }
  }
  else if(xcoords_schema.evaluator_family_name() == "dlinear")
  {
    // Vertex element dlinear coordinates

    if(xinitialize)
    {
      result = new visualization_iterator_1_1(xcoords_schema);
    }
    else
    {
      result = new visualization_iterator_1_1();
    }
  }
  else if(xcoords_schema.rep().name() == "vertex_vertex_constant")
  {
    // Vertex_vertex_constant coordinates

    if(xinitialize)
    {
      result = new visualization_iterator_1_1(xcoords_schema);
    }
    else
    {
      result = new visualization_iterator_1_1();
    }
  }
  else
  {
    // Unsupported coordinates rep.

    post_fatal_error_message("Coordinates rep not supported.");
  }

  // Postconditions:

  ensure(result != 0);
  ensure(xinitialize ?
         result->coordinates_schema().is_same_state(&xcoords_schema) :
         true);

  // Exit:

  return result;
}



tool::visualization_iterator::
~visualization_iterator()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

const fiber_bundle::section_space_schema_member&
tool::visualization_iterator::
coordinates_schema() const
{
  // Preconditions:

  require(is_initialized());

  // Body:

  // Invariant ensures cast is appropriate.

  const section_space_schema_member& result = *_coord_state.schema;

  // Postconditions:

  // Exit:

  return result;
}
 

bool
tool::visualization_iterator::
has_property() const
{
  return _has_property;
}

const fiber_bundle::section_space_schema_member&
tool::visualization_iterator::
property_schema() const
{
  // Preconditions:

  require(is_initialized());
  require(has_property());

  // Body:

  // Invariant ensures cast is appropriate.

  const section_space_schema_member& result = *_prop_state.schema;

  // Postconditions:

  // Exit:

  return result;
}

bool
tool::visualization_iterator::
use_point_top_ids() const
{
  return _use_point_top_ids;
}

void
tool::visualization_iterator::
put_use_point_top_ids(bool xvalue)
{
  _use_point_top_ids = xvalue;
  
  ensure(use_point_top_ids() == xvalue);
  
  return;
}

bool
tool::visualization_iterator::
use_cell_top_ids() const
{
  return _use_cell_top_ids;
}

void
tool::visualization_iterator::
put_use_cell_top_ids(bool xvalue)
{
  _use_cell_top_ids = xvalue;
  
  ensure(use_cell_top_ids() == xvalue);
  
  return;
}

void
tool::visualization_iterator::
set_vtk_data(const sec_vd& xcoords,
             const sec_vd& xprop,
             vtkDoubleArray* xvtk_pt_coords,
             vtkDoubleArray* xvtk_prop,
             int xprop_tensor_rank,
             block<int>& xvtk_cell_types,
             block<vtkIdType>& xvtk_cell_connectivity,
             block<int>& xvtk_cell_type_map,
             vtkIdTypeArray* xvtk_pt_label_ids,
             vtkIdTypeArray* xvtk_cell_label_ids)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().is_same_state(&coordinates_schema()));

  require(has_property());
  require(xprop.state_is_read_accessible());
  require(xprop.schema().is_same_state(&property_schema()));

  /// @hack required because discretization_context::values capacity
  ///       is fixed at 3.

  require(xcoords.schema().df() <= 3);

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}

void
tool::visualization_iterator::
set_vtk_data(const sec_vd& xcoords,
             vtkDoubleArray* xvtk_pt_coords,
             block<int>& xvtk_cell_types,
             block<vtkIdType>& xvtk_cell_connectivity,
             block<int>& xvtk_cell_type_map,
             vtkIdTypeArray* xvtk_pt_label_ids,
             vtkIdTypeArray* xvtk_cell_label_ids)
{
  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().is_same_state(&coordinates_schema()));

  /// @hack required because discretization_context::values capacity
  ///       is fixed at 3.

  require(xcoords.schema().df() <= 3);

  // Body:

  is_abstract();

  // Postconditions:


  // Exit:

  return;
}

void
tool::visualization_iterator::
set_vtk_data(const sec_vd& xprop,
             vtkDoubleArray* xvtk_prop,
             int xprop_tensor_rank)
{
  // Preconditions:

  require(has_property());
  require(xprop.state_is_read_accessible());
  require(xprop.schema().is_same_state(&property_schema()));

  // Body:

  is_abstract();

  // Postconditions:

  // Exit:

  return;
}


// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

tool::visualization_iterator::
visualization_iterator()
{
  // Preconditions:


  // Body:

  disable_invariant_check();

  initialize_buffers();
  initialize_order(BIORDER);

  for(int i=0; i<3; ++i)
  {
    for(int j=0; j<3; ++j)
    {
      _st2_e2[i][j] = 0.0;
      _st2_e3[i][j] = 0.0;
    }
  }

  _use_point_top_ids = true;
  _use_cell_top_ids = true;
  

  enable_invariant_check();

  // Postconditions:


  // Exit:

  return;
}

void
tool::visualization_iterator::
initialize_iteration(const section_space_schema_member& xcoordinates_schema,
                     const section_space_schema_member& xproperty_schema)
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().\
          conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.base_space().le(&xcoordinates_schema.base_space()));

  // Body:

  disable_invariant_check();

  put_anchor(xcoordinates_schema, xproperty_schema);

  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xcoordinates_schema));
  ensure(coordinates_schema().is_same_type(&xcoordinates_schema));
  ensure(coordinates_schema().version() == xcoordinates_schema.version());
  ensure(has_property());
  ensure(property_schema().is_same_state(&xproperty_schema));
  ensure(property_schema().is_same_type(&xproperty_schema));
  ensure(property_schema().version() == xproperty_schema.version());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


void
tool::visualization_iterator::
initialize_iteration(const section_space_schema_member& xcoordinates_schema)
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().\
          conforms_to(base_space_member::standard_schema_path()));

  // Body:

  disable_invariant_check();

  /// @error initalize_states is called again from put_anchor.

  initialize_states(xcoordinates_schema);
  put_anchor(xcoordinates_schema);

  reset();

  enable_invariant_check();

  // Postconditions:

  ensure(invariant());
  ensure(is_initialized());
  ensure(coordinates_schema().is_same_state(&xcoordinates_schema));
  ensure(coordinates_schema().is_same_type(&xcoordinates_schema));
  ensure(coordinates_schema().version() == xcoordinates_schema.version());
  ensure(!has_property());
  ensure(descending());
  ensure(!strict());
  ensure(unexecutable(!is_done() implies this is first member));

  return;
}


//const sheaf::size_type
//tool::visualization_iterator::
//_coord_dofs_ub;

//const sheaf::size_type
//tool::visualization_iterator::
//_prop_dofs_ub;

void
tool::visualization_iterator::
initialize_buffers()
{
  // Preconditions:


  // Body:

  for(int i=0; i<COORD_DOFS_UB; ++i)
  {
    _coord_dofs[i] = 0.0;
  }

  for(int i=0; i<PROP_DOFS_UB; ++i)
  {
    _prop_dofs[i] = 0.0;
  }

  // Postconditions:


  // Exit:

  return;
}

void
tool::visualization_iterator::
clear_down_set()
{
  // Preconditions:

  // Body:

  block<scoped_index>& ldown_set = _vis_state.down_set;
  size_type lct = ldown_set.ct();
  for(size_type i=0; i<lct; ++i)
  {
    put_has_visited(ldown_set[i], false);
  }
  ldown_set.set_ct(0);

  // Postconditions:


  // Exit:

  return;
}

const sheaf::abstract_poset_member&
tool::visualization_iterator::
min(const abstract_poset_member& x1, const abstract_poset_member& x2) const
{
  // Preconditions:

  require(x1.host()->is_same_state(x2.host()));

  // Body:

  const abstract_poset_member& result = x1.le(&x2) ? x1 : x2;

  // Postconditions:


  // Exit:

  return result;
}

void
tool::visualization_iterator::
initialize_states(const section_space_schema_member& xcoordinates_schema,
                  const section_space_schema_member& xproperty_schema)
{
  // Preconditions:

  // Body:

  _coord_state.initialize(xcoordinates_schema);
  _prop_state.initialize(xproperty_schema);

  /// @hack Had to use the initialization method that takes a
  ///       schema_poset_member instead of a base_space_poset to avoid
  ///       the assumption that the evaluation subposet is the elements
  ///       subposet.  This needs explored before merging with the head.
  //_vis_state.initialize(xcoordinates_schema.host()->base_space());
  _vis_state.initialize(xcoordinates_schema);

  // Postconditions:

  // Exit:

  return;
}

void
tool::visualization_iterator::
initialize_states(const section_space_schema_member& xcoordinates_schema)
{
  // Preconditions:

  // Body:

  _coord_state.initialize(xcoordinates_schema);

  /// @hack Had to use the initialization method that takes a
  ///       schema_poset_member instead of a base_space_poset to avoid
  ///       the assumption that the evaluation subposet is the elements
  ///       subposet.  This needs explored before merging with the head.
  //_vis_state.initialize(xcoordinates_schema.host()->base_space());
  _vis_state.initialize(xcoordinates_schema);

  // Postconditions:

  // Exit:

  return;
}

void
tool::visualization_iterator::
put_prop_dofs(sec_vd_dof_type* xprop_dofs,
              size_type xprop_df,
              int xprop_tensor_rank,
              vtkDoubleArray* xvtk_prop,
              int xvtk_tuple_id)
{
  // Preconditions:

  // Body:

  if(xprop_tensor_rank < 2)
  {
    // This is a scalar or vector property,
    // just put the dofs.

    xvtk_prop->SetTuple(xvtk_tuple_id, xprop_dofs);
  }
  else
  {
    // This is a tensor property.
    // VTK only supports st2_e3 directly,
    // but we can treat st2_e2 as a subspace.

    if(xprop_df == 3)
    {
      // This is an st2_e2.

      _st2_e2[0][0] = xprop_dofs[0]; // xx
      _st2_e2[0][1] = xprop_dofs[1]; // xy
      _st2_e2[1][1] = xprop_dofs[2]; // yy

      _st2_e2[1][0] = _st2_e2[0][1]; // yx = xy

      // All others remain 0.0

      xvtk_prop->SetTuple(xvtk_tuple_id, &_st2_e2[0][0]);
    }
    else
    {
      // This is an st2_e3.

      _st2_e3[0][0] = xprop_dofs[0]; // xx
      _st2_e3[0][1] = xprop_dofs[1]; // xy
      _st2_e3[1][1] = xprop_dofs[2]; // yy
      _st2_e3[0][2] = xprop_dofs[3]; // xz
      _st2_e3[1][2] = xprop_dofs[4]; // yz
      _st2_e3[2][2] = xprop_dofs[5]; // zz

      _st2_e3[1][0] = _st2_e3[0][1]; // yx = xy
      _st2_e3[2][0] = _st2_e3[0][2]; // zx = xz
      _st2_e3[2][1] = _st2_e3[1][2]; // zy = yz

      xvtk_prop->SetTuple(xvtk_tuple_id, &_st2_e3[0][0]);
    }
  }

  // Postconditions:

  // Exit:

  return;
}
