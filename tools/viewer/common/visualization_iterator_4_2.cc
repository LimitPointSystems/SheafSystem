
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

// Implementation for class visualization_iterator_4_2


#include "SheafSystem/visualization_iterator_4_2.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/base_space_member.h"
#include "SheafSystem/binary_section_space_schema_member.h"
#include "SheafSystem/eval_family.h"
#include "SheafSystem/sec_rep_descriptor.h"
#include "SheafSystem/section_evaluator.h"
#include "SheafSystem/section_space_schema_member.h"
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
using namespace unordered;

// ===========================================================
// ANY FACET
// ===========================================================


///
bool
tool::visualization_iterator_4_2::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const visualization_iterator_4_2*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

 

///
tool::visualization_iterator_4_2*
tool::visualization_iterator_4_2::
clone() const
{
  // Preconditions:

  // Body:

  visualization_iterator_4_2* cthis = const_cast<visualization_iterator_4_2*>(this);
  visualization_iterator_4_2* result =
    new visualization_iterator_4_2(cthis->coordinates_schema(), cthis->property_schema());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

///
bool
tool::visualization_iterator_4_2::
invariant() const
{
  bool result = true;

  // Preconditions:

  // Body:


  if(invariant_check())
  {
    invariance(visualization_iterator::invariant());

    disable_invariant_check();

    invariance(order() == BIORDER);
    invariance(is_initialized() ?
               coordinates_schema().rep().evaluator_family_name() == "uniform" :
               true);
    invariance((is_initialized() && has_property()) ?
               property_schema().discretization().name() == "__vertices" :
               true);

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Postconditions:

  // Exit

  return result;
}


// ===========================================================
// DEPTH_FIRST_ITERATOR FACET
// ===========================================================

///
void
tool::visualization_iterator_4_2::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  bool ltruncate = xtruncate;

  // Traverse the graph gathering coord and prop disc members until
  // we have enough context to evaluate the coordinates at the
  // the property disc points or until the trversal is done.

  visualization_iterator::next(ltruncate);

  while(!is_done())
  {
    if(action() == PREVISIT_ACTION)
    {
      if(_above.vis_eval)
      {
        /// @hack _coord_state down_set is convenient place to store
        /// all members at or above the elements that have been visited
        /// for efficient unmarking in visualization_iterator::reset.
        /// Note that since _bove.vis_eval has not yet been evaluated
        /// for this iteration, it is still true if we are at an element.

        _coord_state.down_set.push_back(_index);
      }
      else
      {
        // Store all members below the elements for
        // unmarking in postvisit action.

        _vis_state.down_set.push_back(_index);
      }

      _at.vis_eval   = _vis_state.eval_sp.contains_member(_index);
      _at.vis_disc   = _vis_state.disc_sp.contains_member(_index);
      _at.coord_eval = _coord_state.eval_sp.contains_member(_index);

      if(_at.vis_eval)
      {
	// $$SCRIBBLE eval-sp: same issue as in rep _1_1.
	// Want to execute only for maximal eval mbr we find.

        _above.vis_eval = false;

        _vis_state.set_evaluation_member(_index);
        _vis_state.initialize_order_correction();
        _vis_state.discretization_members.set_ct(0);
        _vis_state.down_set.set_ct(0);
      }

      if(_at.vis_disc)
      {
        _vis_state.gather_discretization_member(_index, greater_index());
        _vis_state.local_id++;

        ltruncate = true;
      }

      if(_at.coord_eval)
      {
	// $$SCRIBBLE eval-sp: same issue as in rep _1_1.
	// Want to execute only for maximal eval mbr we find,
	// but for uniform coordinates we currentlt have no
	// notion of restriction. Have to think about this one.

        _coord_state.set_and_attach_evaluation_member(_index);
        _coord_state.discretization_members.set_ct(0);
        _coord_state.gather_discretization_member(_index);
        _coord_state.local_id++;
        _coord_state.dofs.set_ct(0);
      }

    }
    else if(action() == POSTVISIT_ACTION)
    {
      _at.vis_eval = _vis_state.eval_sp.contains_member(_index);

      if(_at.vis_eval)
      {
	// $$SCRIBBLE eval-sp: same issue as in rep _1_1.
	// but see above comment.

        clear_down_set();
        _above.vis_eval  = true;
        break;
      }

      // If we invoke visualization_iterator::next() from the postvisit action,
      // the truncation flag will be ignored, since you can only truncate
      // in the previsit action. But just to be specific, we'll set it false no
      // matter what we've done here.

      ltruncate = false;
    }
    else
    {
      post_fatal_error_message("unrecognized action");
    }

    visualization_iterator::next(ltruncate);
  } // end while(!is_done())

  // Postconditions:

  ensure(invariant());
  ensure(!is_done() ? action() == POSTVISIT_ACTION : true);

  // Exit

  return;
}

// ===========================================================
// VISUALIZATION_ITERATOR FACET
// ===========================================================

///
void
tool::visualization_iterator_4_2::
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

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(xcoords.schema().df() <= 3);


  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "id: " << index()
  << " eval_id: " << _vis_state.eval_id
  << endl;
#endif

  if(_coord_state.dofs.ct() == 0)
  {
    // The dofs have not been gathered for this coord eval member.

    _coord_state.gather_dofs(xcoords);
  }

  typedef unordered_map<pod_index_type, pod_index_type> map_type;
  typedef map_type::const_iterator iterator_type;

  int lprop_df = xprop.schema().df();
  block<discretization_context>& ldisc_mbrs = _vis_state.discretization_members;
  size_type ldisc_ct = ldisc_mbrs.ct();
  map_type* lmap = _vis_state.disc_to_seq_map;

  const index_space_handle& ldisc_id_space =
    xcoords.schema().discretization_id_space();

  // Transfer the cell label ids.

  pod_index_type lvtk_cell_id =
    _use_cell_top_ids ?
    _vis_state.eval_id.hub_pod() :
    xcoords.schema().evaluation().id_space().pod(_vis_state.eval_id);
  
  xvtk_cell_label_ids->InsertNextValue(lvtk_cell_id);

  // Transfer the cell type.

  xvtk_cell_types.push_back(xvtk_cell_type_map[_vis_state.eval_type_id]);

  // Transfer the connectivity count.

  xvtk_cell_connectivity.push_back(ldisc_ct);

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    discretization_context& ldisc_mbr = ldisc_mbrs[i];
    scoped_index ldisc_id = ldisc_mbr.disc_id;
    pod_index_type ldisc_pod = ldisc_id.hub_pod();
    iterator_type lmap_itr = lmap->find(ldisc_pod);

#ifdef DIAGNOSTIC_OUTPUT

    cout << "\tdisc_id: " << setw(6) << ldisc_id;
#endif

    pod_index_type lseq_id;

    if(lmap_itr == lmap->end())
    {
      // Haven't visited this vertex before.
      // Create a seq id for it.

      lseq_id = _vis_state.next_seq_id++;
      (*lmap)[ldisc_pod] = lseq_id;

#ifdef DIAGNOSTIC_OUTPUT

      cout << " seq_id:" << setw(6) << lseq_id;
#endif

      // Transfer the coordinate data;
      // must evaluate coordintes section at vertices.

      // Get the local coordinates of the vertex in the element.

      chart_point_3d ldisc_pt;
      ldisc_pt.put_chart_id(ldisc_mbr.eval_id);

      _vis_state.eval->local_coordinates(ldisc_mbr.local_id,
                                         ldisc_pt.local_coords(),
                                         3);

      // Unrefine from the element to the coord eval.

      /// @error we assume the unrefine operator unrefines to the prop eval,
      /// but there is no way to ensure this condition.

      _coord_state.eval_mbr->unrefine_point_pa(ldisc_pt, ldisc_pt);

      // Evaluate the global coordinate section.

      _coord_state.eval->value_at_coord(_coord_state.dofs.base(),
                                        _coord_state.dofs.ct(),
                                        ldisc_pt.local_coords(),
                                        3,
                                        _coord_dofs,
                                        _coord_state.df);

      xvtk_pt_coords->SetTuple(lseq_id, _coord_dofs);

      // Transfer the point label ids.

      pod_index_type lvtk_pt_id =
	_use_point_top_ids ?
	ldisc_id.hub_pod() : ldisc_id_space.pod(ldisc_id);

      xvtk_pt_label_ids->SetValue(lseq_id, lvtk_pt_id);

#ifdef DIAGNOSTIC_OUTPUT

      cout << " coords: "
      << setw(6) << _coord_dofs[0]
      << setw(6) << _coord_dofs[1]
      << setw(6) << _coord_dofs[2];
#endif

      // Transfer the property data; no need to evaluate.

      xprop.get_fiber(ldisc_id, _prop_dofs,
		      static_cast<size_type>(PROP_DOFS_UB)*sizeof(sec_vd_dof_type), false);

      put_prop_dofs(_prop_dofs, lprop_df, xprop_tensor_rank, xvtk_prop, lseq_id);

#ifdef DIAGNOSTIC_OUTPUT

      cout << " prop: " << setw(10) << _prop_dofs[0];
#endif
    }
    else
    {
      lseq_id = lmap_itr->second;

#ifdef DIAGNOSTIC_OUTPUT

      cout << " seq_id:" << setw(6) << lseq_id;
#endif

    }

    // Transfer the connectivity.

    xvtk_cell_connectivity.push_back(lseq_id);

#ifdef DIAGNOSTIC_OUTPUT

    cout << endl;
#endif

  }

  // Postconditions:


  // Exit:

  return;
}

///
void
tool::visualization_iterator_4_2::
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

  /// @hack required because discretization_context::values capacity is fixed at 3.

  require(xcoords.schema().df() <= 3);


  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "id: " << index()
  << " eval_id: " << _vis_state.eval_id
  << endl;
#endif

  if(_coord_state.dofs.ct() == 0)
  {
    // The dofs have not been gathered for this coord eval member.

    _coord_state.gather_dofs(xcoords);
  }

  typedef unordered_map<pod_index_type, pod_index_type> map_type;
  typedef map_type::const_iterator iterator_type;

  block<discretization_context>& ldisc_mbrs = _vis_state.discretization_members;
  size_type ldisc_ct = ldisc_mbrs.ct();
  map_type* lmap = _vis_state.disc_to_seq_map;

  const index_space_handle& ldisc_id_space =
    xcoords.schema().discretization_id_space();

  // Transfer the cell label ids.

  pod_index_type lvtk_cell_id =
    _use_cell_top_ids ?
    _vis_state.eval_id.hub_pod() :
    xcoords.schema().evaluation().id_space().pod(_vis_state.eval_id);
  
  xvtk_cell_label_ids->InsertNextValue(lvtk_cell_id);

  // Transfer the cell type.

  xvtk_cell_types.push_back(xvtk_cell_type_map[_vis_state.eval_type_id]);

  // Transfer the connectivity count.

  xvtk_cell_connectivity.push_back(ldisc_ct);

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    discretization_context& ldisc_mbr = ldisc_mbrs[i];
    scoped_index ldisc_id = ldisc_mbr.disc_id;
    pod_index_type ldisc_pod = ldisc_id.hub_pod();
    iterator_type lmap_itr = lmap->find(ldisc_pod);

#ifdef DIAGNOSTIC_OUTPUT

    cout << "\tdisc_id: " << setw(6) << ldisc_id;
#endif

    pod_index_type lseq_id;

    if(lmap_itr == lmap->end())
    {
      // Haven't visited this vertex before.
      // Create a seq id for it.

      lseq_id = _vis_state.next_seq_id++;
      (*lmap)[ldisc_pod] = lseq_id;

#ifdef DIAGNOSTIC_OUTPUT

      cout << " seq_id:" << setw(6) << lseq_id;
#endif

      // Transfer the coordinate data;
      // must evaluate coordintes section at vertices.

      // Get the local coordinates of the vertex in the element.

      chart_point_3d ldisc_pt;
      ldisc_pt.put_chart_id(ldisc_mbr.eval_id);

      _vis_state.eval->local_coordinates(ldisc_mbr.local_id,
                                         ldisc_pt.local_coords(),
                                         3);

      // Unrefine from the element to the coord eval.

      /// @error we assume the unrefine operator unrefines to the prop eval,
      /// but there is no way to ensure this condition.

      _coord_state.eval_mbr->unrefine_point_pa(ldisc_pt, ldisc_pt);

      // Evaluate the global coordinate section.

      _coord_state.eval->value_at_coord(_coord_state.dofs.base(),
                                        _coord_state.dofs.ct(),
                                        ldisc_pt.local_coords(),
                                        3,
                                        _coord_dofs,
                                        _coord_state.df);

      xvtk_pt_coords->SetTuple(lseq_id, _coord_dofs);

      // Transfer the point label ids.

      pod_index_type lvtk_pt_id =
	_use_point_top_ids ?
	ldisc_id.hub_pod() : ldisc_id_space.pod(ldisc_id);

      xvtk_pt_label_ids->SetValue(lseq_id, lvtk_pt_id);

#ifdef DIAGNOSTIC_OUTPUT

      cout << " coords: "
      << setw(6) << _coord_dofs[0]
      << setw(6) << _coord_dofs[1]
      << setw(6) << _coord_dofs[2];
#endif
    }
    else
    {
      lseq_id = lmap_itr->second;

#ifdef DIAGNOSTIC_OUTPUT

      cout << " seq_id:" << setw(6) << lseq_id;
#endif

    }

    // Transfer the connectivity.

    xvtk_cell_connectivity.push_back(lseq_id);

#ifdef DIAGNOSTIC_OUTPUT

    cout << endl;
#endif

  }

  // Postconditions:


  // Exit:

  return;
}

///
void
tool::visualization_iterator_4_2::
set_vtk_data(const sec_vd& xprop, vtkDoubleArray* xvtk_prop, int xprop_tensor_rank)
{
  // Preconditions:

  require(has_property());
  require(xprop.state_is_read_accessible());
  require(xprop.schema().is_same_state(&property_schema()));

  // Body:

#ifdef DIAGNOSTIC_OUTPUT

  cout << "id: " << index() << " eval_id: " << _vis_state.eval_id << endl;
#endif

  int lprop_df = xprop.schema().df();
  block<discretization_context>& ldisc_mbrs = _vis_state.discretization_members;
  size_type ldisc_ct = ldisc_mbrs.ct();

  for(size_type i=0; i<ldisc_ct; ++i)
  {
    discretization_context& ldisc_mbr = ldisc_mbrs[i];
    scoped_index ldisc_id = ldisc_mbr.disc_id;
    pod_index_type ldisc_pod = ldisc_id.hub_pod();

#ifdef DIAGNOSTIC_OUTPUT

    cout << "\tdisc_id: " << setw(6) << ldisc_id;
#endif

    if(!_vis_state.visited[ldisc_pod])
    {
      // Haven't visited this vertex before.
      // Transfer the property data and increment the pt seq id;
      // no need to evaluate.

      xprop.get_fiber(ldisc_id, _prop_dofs,
		      static_cast<size_type>(PROP_DOFS_UB)*sizeof(sec_vd_dof_type), false);

#ifdef DIAGNOSTIC_OUTPUT

      cout << " seq_id:" << setw(6) << _pt_seq_id;
      cout << " prop: " << setw(10) << _prop_dofs[0];
#endif

      put_prop_dofs(_prop_dofs, lprop_df, xprop_tensor_rank, xvtk_prop, _pt_seq_id++);

      _vis_state.visited.put(ldisc_pod, true);
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << endl;
#endif

  }

  // Postconditions:


  // Exit:

  return;
}

// ===========================================================
// VISUALIZATION_ITERATOR_4_2 FACET
// ===========================================================


///
tool::visualization_iterator_4_2::
visualization_iterator_4_2()
    : visualization_iterator()
{
  // Preconditions:


  // Body:

  // Postconditions:

  ensure(!is_initialized());

  // Exit:

  return;
}

///
tool::visualization_iterator_4_2::
visualization_iterator_4_2(const section_space_schema_member& xcoordinates_schema,
                           const section_space_schema_member& xproperty_schema)
    : visualization_iterator()
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.base_space().le(&xcoordinates_schema.base_space()));
  require(xcoordinates_schema.rep().evaluator_family_name() == "uniform");
  require(xproperty_schema.discretization().name() == "__vertices");
  require(!(xcoordinates_schema.rep().path() == "sec_rep_descriptors/vertex_cells_dlinear"));
  require(!(xproperty_schema.rep().path() == "sec_rep_descriptors/vertex_cells_dlinear"));

  // Body:

  put_anchor(xcoordinates_schema, xproperty_schema);
  reset();

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


///
tool::visualization_iterator_4_2::
visualization_iterator_4_2(const section_space_schema_member& xcoordinates_schema)
    : visualization_iterator()
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoordinates_schema.rep().evaluator_family_name() == "uniform");
  require(!(xcoordinates_schema.rep().path() == "sec_rep_descriptors/vertex_cells_dlinear"));

  // Body:

  put_anchor(xcoordinates_schema);
  reset();

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


///
tool::visualization_iterator_4_2::
~visualization_iterator_4_2()
{
  // Preconditions:

  // Body:

  // Postconditions:

}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

