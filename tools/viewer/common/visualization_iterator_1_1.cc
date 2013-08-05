//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class visualization_iterator_1_1


#include "visualization_iterator_1_1.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "binary_section_space_schema_member.h"
#include "eval_family.h"
#include "int_set.h"
#include "sec_rep_descriptor.h"
#include "sec_vd.h"
#include "section_evaluator.h"
#include "section_space_schema_member.h"
#include "std_limits.h"
#include "structured_block_1d.h"
#include "structured_block_2d.h"
#include "structured_block_3d.h"
#include "subposet_member_iterator.h"
#include "uniform_eval_family.h"
#include "vtkDoubleArray.h"
#include "vtkIdTypeArray.h"

//#define DIAGNOSTIC_OUTPUT 1

// Workaround for MS Visual C++
using namespace tool;

// ===========================================================
// ANY FACET
// ===========================================================

bool
tool::visualization_iterator_1_1::
is_ancestor_of(const any* xother) const
{
  // Preconditions:

  // Body:

  bool result = dynamic_cast<const visualization_iterator_1_1*>(xother) != 0;

  // Postconditions:

  // Exit

  return result;
}

tool::visualization_iterator_1_1*
tool::visualization_iterator_1_1::
clone() const
{
  // Preconditions:

  // Body:

  visualization_iterator_1_1* cthis =
    const_cast<visualization_iterator_1_1*>(this);

  visualization_iterator_1_1* result =
    new visualization_iterator_1_1(cthis->coordinates_schema(),
                                   cthis->property_schema());

  // Postconditions:

  //  ensure(invariant());
  ensure(result != 0);

  // Exit

  return result;
}

bool
tool::visualization_iterator_1_1::
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

    invariance((is_initialized() && has_property()) ?
               property_schema().rep().is_same_state(&coordinates_schema().rep()) :
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

void
tool::visualization_iterator_1_1::
next(bool xtruncate)
{
  // Preconditions:

  require(!is_done());

  // Body:

  // A set to contain discretization ids.

  int_set lvisited;

  bool ltruncate = xtruncate;

  // Traverse the graph gathering coord and prop disc members until
  // we have enough context to evaluate the coordinates at the
  // the property disc points or until the traversal is done.

  visualization_iterator::next(ltruncate);

  while(!is_done())
  {

#ifdef DIAGNOSTIC_OUTPUT
    cout << "vis_itr_1_1: current item: " << _index << "  name: " << anchor().host()->member_name(_index) << endl;
#endif    
    
    if(action() == PREVISIT_ACTION)
    {
      // The coord and prop eval are both the element subposet and
      // the coord disc is the vertices. The prop disc is strictly below
      // the elements, but not necessarily equal to the vertices.

      _at.vis_eval = _vis_state.eval_sp.contains_member(_index);
      _at.vis_disc = _vis_state.disc_sp.contains_member(_index);

      if(!_maximal_eval_id.is_valid() && _at.vis_eval)
      {
        _above.vis_eval = false;
        _maximal_eval_id = _index;

        // Turn off put_visit_once.

        put_visit_once(false);

        _vis_state.set_evaluation_member(_index);
        _vis_state.initialize_order_correction();
        _vis_state.discretization_members.set_ct(0);
      }

      if(_at.vis_disc)
      {
        _above.vis_disc = false;

        //$$SCRIBBLE: We need a way to prevent the discretization member from being
        //            entered into _vis_state.discretization_members more than once.
        //            we could search the discretization_members (type block<scoped_index> )
        //            directly or just save them in a local int_set.
        //$$ISSUE: Isn't there a better way to handle this?

        int lid = _index.hub_pod();
        if(!lvisited.contains(lid))
        {
          lvisited.insert(lid);
          _vis_state.gather_discretization_member(_index, greater_index());
          _vis_state.local_id++;
        }

        ltruncate = true;
      }
    }
    else if(action() == POSTVISIT_ACTION)
    {
      if(_maximal_eval_id ==~ index())
      {
        _maximal_eval_id.invalidate();

        // Turn on put_visit_once.

        put_visit_once(true);

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

void
tool::visualization_iterator_1_1::
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

  typedef hash_map<pod_index_type, pod_index_type> map_type;
  typedef map_type::const_iterator iterator_type;

  int lprop_df = xprop.schema().df();
  block<discretization_context>& ldisc_mbrs = _vis_state.discretization_members;
  size_type ldisc_ct = ldisc_mbrs.ct();
  map_type* lmap = _vis_state.disc_to_seq_map;

  const index_space_handle& ldisc_id_space =
    xcoords.schema().discretization_id_space();

  // Transfer the cell label id.

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
    scoped_index ldisc_id = ldisc_mbrs[i].disc_id;
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

      // Transfer the coordinate data

      xcoords.get_fiber(ldisc_id, _coord_dofs,
			static_cast<size_type>(COORD_DOFS_UB)*sizeof(sec_vd_dof_type), false);

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

      // Transfer the property data

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

void
tool::visualization_iterator_1_1::
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

#ifdef DIAGNOSTIC_OUTPUT
  cout << "id: " << index()
  << " eval_id: " << _vis_state.eval_id
  << endl;
#endif

  typedef hash_map<pod_index_type, pod_index_type> map_type;
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
    scoped_index ldisc_id = ldisc_mbrs[i].disc_id;
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

      // Transfer the coordinate data

      xcoords.get_fiber(ldisc_id, _coord_dofs,
			static_cast<size_type>(COORD_DOFS_UB)*sizeof(sec_vd_dof_type), false);

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

void
tool::visualization_iterator_1_1::
set_vtk_data(const sec_vd& xprop,
             vtkDoubleArray* xvtk_prop,
             int xprop_tensor_rank)
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
    scoped_index ldisc_id = ldisc_mbrs[i].disc_id;
    pod_index_type ldisc_pod = ldisc_id.hub_pod();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "\tdisc_id: " << setw(6) << ldisc_id;
#endif

    if(!_vis_state.visited[ldisc_pod])
    {
      // Haven't visited this vertex before.
      // Transfer the property data and increment the pt seq id.

      xprop.get_fiber(ldisc_id, _prop_dofs,
		      static_cast<size_type>(PROP_DOFS_UB)*sizeof(sec_vd_dof_type), false);

#ifdef DIAGNOSTIC_OUTPUT
      cout << " seq_id:"   << setw(6) << _pt_seq_id;
      cout << " prop: " << setw(10) << _prop_dofs[0];
#endif

      put_prop_dofs(_prop_dofs, lprop_df, xprop_tensor_rank, xvtk_prop,
                    _pt_seq_id++);

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
// VISUALIZATION_ITERATOR_1_1 FACET
// ===========================================================

tool::visualization_iterator_1_1::
visualization_iterator_1_1()
    : visualization_iterator()
{
  // Preconditions:


  // Body:

  // Postconditions:

  ensure(!is_initialized());

  // Exit:

  return;
}

tool::visualization_iterator_1_1::
visualization_iterator_1_1(const section_space_schema_member& xcoordinates_schema,
                           const section_space_schema_member& xproperty_schema)
    : visualization_iterator()
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));
  require(xproperty_schema.state_is_read_accessible());
  require(xproperty_schema.rep().is_same_state(&xcoordinates_schema.rep()));

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

  // Exit:

  return;
}


tool::visualization_iterator_1_1::
visualization_iterator_1_1(const section_space_schema_member& xcoordinates_schema)
    : visualization_iterator()
{

  // Preconditions:

  require(xcoordinates_schema.state_is_read_accessible());
  require(xcoordinates_schema.base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));

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

  // Exit:

  return;
}

tool::visualization_iterator_1_1::
~visualization_iterator_1_1()
{
  // Preconditions:

  // Body:

  // Postconditions:

  // Exit:

}

// ===========================================================
// PROTECTED MEMBER FUNCTIONS
// ===========================================================

// =============================================================================
// PRIVATE MEMBER FUNCTIONS
// =============================================================================

