// $RCSfile: vtk_unstructured_grid_builder.cc,v $ $Revision: 1.43 $ $Date: 2013/03/13 00:59:09 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class vtk_unstructured_grid_builder

#include "vtk_unstructured_grid_builder.h"

#include "assert_contract.h"
#include "base_space_member.h"
#include "biorder_iterator.h"
#include "block.impl.h"
#include "error_message.h"
#include "eval_iterator.h"
#include "namespace_poset.h"
#include "postorder_iterator.h"
#include "preorder_iterator.h"
#include "sec_rep_descriptor.h"
#include "sec_vd_space.h"
#include "section_space_schema_poset.h"
#include "visualization_iterator.h"

#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"
#include "vtkDoubleArray.h"
#include "vtkFieldData.h"
#include "vtkIdTypeArray.h"
#include "vtkIntArray.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkPointData.h"

//#undefine DIAGNOSTIC_OUTPUT
//#define DIAGNOSTIC_OUTPUT

// Workaround for MS Visual C++
using namespace tool;

// ============================================================================
// ANY FACET
// ============================================================================

bool
tool::vtk_unstructured_grid_builder::
is_ancestor_of(const any* other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const vtk_unstructured_grid_builder*>(other) != 0;

  // Postconditions:

  return result;
}

tool::vtk_unstructured_grid_builder*
tool::vtk_unstructured_grid_builder::
clone() const
{
  vtk_unstructured_grid_builder* result;

  // Preconditions:

  // Body:

  result = new vtk_unstructured_grid_builder();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

tool::vtk_unstructured_grid_builder&
tool::vtk_unstructured_grid_builder::
operator=(const vtk_abstract_grid_builder& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

tool::vtk_unstructured_grid_builder&
tool::vtk_unstructured_grid_builder::
operator=(const vtk_unstructured_grid_builder& xother)
{

  // Preconditions:

  require(is_ancestor_of(&xother));

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return *this;
}

bool
tool::vtk_unstructured_grid_builder::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant.

    disable_invariant_check();

    // Must satisfy base class invariant.

    invariance(vtk_abstract_grid_builder::invariant());

    // Invariances for this class:

    ///@todo
    ///     invariance(_coords_dof_buf.ub() == 3);
    ///     invariance(_coords_dof_buf.ct() == _coords_dof_buf.ub());

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit:

  return result;
}

// ============================================================================
// VTK_DATA_SET_BUILDER FACET
// ============================================================================

tool::vtk_unstructured_grid_builder::
vtk_unstructured_grid_builder()
{
  // Preconditions:

  // Body:

  _vtk_cell_types        = new block<int>;
  _vtk_cell_connectivity = new block<vtkIdType>;

  // Postconditions:

  // Exit:

  return;
}

tool::vtk_unstructured_grid_builder::
vtk_unstructured_grid_builder(const vtk_unstructured_grid_builder& xother)
{
  // Preconditions:

  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

tool::vtk_unstructured_grid_builder::
vtk_unstructured_grid_builder(namespace_poset& xns)
{
  // Preconditions:

  // Body:

  _vtk_cell_types        = new block<int>;
  _vtk_cell_connectivity = new block<vtkIdType>;

  set_name_space(xns);

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

tool::vtk_unstructured_grid_builder::
~vtk_unstructured_grid_builder()
{
  // Preconditions:

  // Body:

  delete _vtk_cell_types;
  delete _vtk_cell_connectivity;

  // Postconditions:

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
set_name_space(namespace_poset& xns)
{
  // Preconditions:

  // Body:

  if(_name_space != &xns)
  {
    _name_space = &xns;

    // Initialize the mapping from sheaf cell types to vtk cell types.

    init_cell_type_map();
  }

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

vtkUnstructuredGrid*
tool::vtk_unstructured_grid_builder::
build(const sec_vd& xcoords, const sec_vd& xproperty)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(precondition_of(build_pa(xcoords, xproperty, result)));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xproperty, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(build_pa(xcoords, xproperty, result)));

  // Exit:

  return result;
}

vtkUnstructuredGrid*
tool::vtk_unstructured_grid_builder::
build(const sec_vd& xcoords, const sec_vd& xproperty1, const sec_vd& xproperty2)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(precondition_of(build_pa(xcoords, xproperty1, xproperty2, result)));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xproperty1, xproperty2, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(build_pa(xcoords, xproperty1, xproperty2, result)));

  // Exit:

  return result;
}

vtkUnstructuredGrid*
tool::vtk_unstructured_grid_builder::
build(const sec_vd& xcoords)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(precondition_of(build_pa(xcoords, result)));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(build_pa(xcoords, result)));

  // Exit:

  return result;
}

vtkUnstructuredGrid*
tool::vtk_unstructured_grid_builder::
build(const sec_vd& xcoords, const string& xpartition_name)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(precondition_of(build_pa(xcoords, xparitition_name, result)));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xpartition_name, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(build_pa(xcoords, xparitition_name, result)));

  // Exit:

  return result;
}

vtkUnstructuredGrid*
tool::vtk_unstructured_grid_builder::
build(const sec_vd& xcoords, const block<sec_vd*>& xproperties)
{
  vtkUnstructuredGrid* result;

  // Preconditions:

  require(precondition_of(build_pa(xcoords, xproperties, result)));

  // Body:

  result = vtkUnstructuredGrid::New();

  build_pa(xcoords, xproperties, *result);

  // Postconditions:

  ensure(result != 0);
  ensure(postcondition_of(build_pa(xcoords, xproperties, result)));

  // Exit:

  return result;
}

void
tool::vtk_unstructured_grid_builder::
build_pa(const sec_vd& xcoords,
         const sec_vd& xproperty,
         vtkUnstructuredGrid& xresult)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("build_pa with property");
#endif

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(!xcoords.name().empty());
  require(xproperty.state_is_read_accessible());

  /// @hack a temporary restriction, until if below generalized.

  require(xproperty.is_jim());

  /// @hack if the coordinates are a multi-section and the property
  /// is defined on some smaller chunk than the coordinates, we currently
  /// have no way to compute the vertex count for the restriction of
  /// the coordinates to the base space of the property. So:

  require(!xcoords.is_jim() ? xproperty.schema().same_base_space(xcoords.schema()) \
                            : true);

  // Body:

  // The vis iterators will iterate over the smaller of the coords or prop
  // base space. So initialize the vtk mesh data with the smaller of the two.

  const sec_vd& lsmaller =
    xcoords.schema().base_space().le(&xproperty.schema().base_space()) ?
    xcoords : xproperty;

  initialize_vtk_mesh_data(lsmaller, xcoords.name());

  // Reset the property data

  _vtk_prop_dofs.set_ct(0);
  _prop_is_pt_data.set_ct(0);
  _prop_tensor_rank.set_ct(0);

  // Initialize property data.

  initialize_vtk_prop_data(&xproperty);


  if(xcoords.is_jim())
  {
    // The coords are an ordinary section, not multi-section.
    // Gather the point and cell data for the section.

    visualization_iterator* litr =
      visualization_iterator::new_visualization_iterator(xcoords.schema(), xproperty.schema());

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);
    
    while(!litr->is_done())
    {
      litr->set_vtk_data(xcoords,
                         xproperty,
                         _vtk_coord_dofs,
                         _vtk_prop_dofs[0],
                         _prop_tensor_rank[0],
                         *_vtk_cell_types,
                         *_vtk_cell_connectivity,
                         _cell_type_map,
                         _vtk_pt_label_ids,
                         _vtk_cell_label_ids);
      litr->next();
    }

    delete litr;
  }
  else
  {
    // The coords are a multi-section.
    // Gather the point and cell data separately for each branch.

    sec_rep_space* lhost = xcoords.host();

    visualization_iterator* litr =
      visualization_iterator::new_visualization_iterator(xcoords.schema(),
                                                         xproperty.schema(),
                                                         false);

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    sec_vd lbranch;
    preorder_iterator lbranch_itr(xcoords, "jims", DOWN, NOT_STRICT);
    while(!lbranch_itr.is_done())
    {
      lbranch.attach_to_state(lhost, lbranch_itr.index());
      section_space_schema_member& lbranch_schema =
        lhost->member_dof_map(lbranch_itr.index()).schema();

      litr->put_anchor(lbranch_schema, xproperty.schema());
      litr->reset();

      while(!litr->is_done())
      {
        litr->set_vtk_data(lbranch,
                           xproperty,
                           _vtk_coord_dofs,
                           _vtk_prop_dofs[0],
                           _prop_tensor_rank[0],
                           *_vtk_cell_types,
                           *_vtk_cell_connectivity,
                           _cell_type_map,
			   _vtk_pt_label_ids,
			   _vtk_cell_label_ids);
        litr->next();
      }
      lbranch_itr.next();
    }

    lbranch.detach_from_state();
    delete litr;
  }

  finalize_vtk_mesh_data(xresult);
  finalize_vtk_prop_data(&xproperty,
                         _prop_is_pt_data[0],
                         _prop_tensor_rank[0],
                         _vtk_prop_dofs[0],
                         xresult);

  // Encourage vtk to reclaim memory.

  xresult.Squeeze();

#ifdef DIAGNOSTIC_OUTPUT

  vtkIndent lindent;
  xresult.PrintSelf(cout, lindent);
#endif

  // Postconditions:


  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
build_pa(const sec_vd& xcoords, const sec_vd& xproperty1, const sec_vd& xproperty2,
         vtkUnstructuredGrid& xresult)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("build_pa with properties");
#endif

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(!xcoords.name().empty());
  require(xproperty1.state_is_read_accessible());
  require(xproperty2.state_is_read_accessible());

  /// @hack a temporary restriction, until if below generalized.

  require(xproperty1.is_jim());
  require(xproperty2.is_jim());

  /// @hack if the coordinates are a multi-section and the property
  /// is defined on some smaller chunk than the coordinates, we currently
  /// have no way to compute the vertex count for the restriction of
  /// the coordinates to the base space of the property. So:

  require(!xcoords.is_jim() ? xproperty1.schema().same_base_space(xcoords.schema()) : true);
  require(!xcoords.is_jim() ? xproperty2.schema().same_base_space(xcoords.schema()) : true);

  // Body:

  // Construct a block for the properties

  block<sec_vd*> properties;
  properties.push_back(const_cast<sec_vd*>(&xproperty1));
  properties.push_back(const_cast<sec_vd*>(&xproperty2));

  // Call the block build function

  build_pa(xcoords, properties, xresult);

  // Postconditions:


  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
build_pa(const sec_vd& xcoords, vtkUnstructuredGrid& xresult)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("build_pa without property");
#endif

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(!xcoords.name().empty());

  // Body:

  initialize_vtk_mesh_data(xcoords, xcoords.name());

  if(xcoords.is_jim())
  {
    // The coords are an ordinary section, not multi-section.
    // Gather the point and cell data for the section.

    visualization_iterator* litr =
      visualization_iterator::new_visualization_iterator(
        const_cast<sec_vd&>(xcoords).schema());

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    while(!litr->is_done())
    {
      litr->set_vtk_data(const_cast<sec_vd&>(xcoords),
                         _vtk_coord_dofs,
                         *_vtk_cell_types,
                         *_vtk_cell_connectivity,
                         _cell_type_map,
                         _vtk_pt_label_ids,
                         _vtk_cell_label_ids);
      litr->next();
    }

    delete litr;
  }
  else
  {
    // The coords are a multi-section.
    // Gather the point and cell data separately for each branch.

    sec_rep_space* lhost = xcoords.host();

    visualization_iterator* litr =
      visualization_iterator::new_visualization_iterator(
        const_cast<sec_vd&>(xcoords).schema(), false);

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    sec_vd lbranch;
    preorder_iterator lbranch_itr(xcoords, "jims", DOWN, NOT_STRICT);
    while(!lbranch_itr.is_done())
    {
      lbranch.attach_to_state(lhost, lbranch_itr.index());
      section_space_schema_member& lbranch_schema =
        lhost->member_dof_map(lbranch_itr.index()).schema();

      litr->put_anchor(lbranch_schema);
      litr->reset();

      while(!litr->is_done())
      {
        litr->set_vtk_data(lbranch,
                           _vtk_coord_dofs,
                           *_vtk_cell_types,
                           *_vtk_cell_connectivity,
                           _cell_type_map,
                           _vtk_pt_label_ids,
                           _vtk_cell_label_ids);
        litr->next();
      }
      lbranch_itr.next();
    }

    lbranch.detach_from_state();
    delete litr;
  }

  finalize_vtk_mesh_data(xresult);

  // Encourage vtk to reclaim memory.

  xresult.Squeeze();

#ifdef DIAGNOSTIC_OUTPUT
  vtkIndent lindent;
  xresult.PrintSelf(cout, lindent);
#endif

  // Postconditions:


  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
build_pa(const sec_vd& xcoords,
         const string& xpartition_name,
         vtkUnstructuredGrid& xresult)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("build_pa with partition");
#endif

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(!xpartition_name.empty());
  require(xcoords.schema().base_space().host()->member_id_spaces(true).contains(xpartition_name));

  // Body:

  build_pa(xcoords, xresult);
  set_cell_data(const_cast<sec_vd&>(xcoords).schema().base_space(), xpartition_name, xresult);

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
build_pa(const sec_vd& xcoords,
         const block<sec_vd*>& xproperties,
         vtkUnstructuredGrid& xresult)
{

#ifdef DIAGNOSTIC_OUTPUT
  post_information_message("build_pa with multiple properties");
#endif

  // Preconditions:

  require(xcoords.state_is_read_accessible());
  require(xcoords.schema().base_space().schema().\
    conforms_to(base_space_member::standard_schema_path()));
  require(xcoords.schema().df() <= 3);
  require(!xcoords.name().empty());
  require(xproperties.ct() > 0);
  require_for_all(i, 0, xproperties.ct(), xproperties[i]->state_is_read_accessible());

  /// @hack a temporary restriction, until if below generalized.

  require_for_all(i, 0, xproperties.ct(), xproperties[i]->is_jim());

  /// @hack if the coordinates are a multi-section and the property
  /// is defined on some smaller chunk than the coordinates, we currently
  /// have no way to compute the vertex count for the restriction of
  /// the coordinates to the base space of the property. So:

  require_for_all(i, 0, xproperties.ct(), !xcoords.is_jim() ?
                  xproperties[i]->schema().same_base_space(xcoords.schema()) : true);

  // Body:

  // The vis iterators will iterate over the smaller of the coords or prop
  // base space. So initialize the vtk mesh data with the smaller of the two.

  const sec_vd* lsmaller = &xcoords;
  for(int i=0; i<xproperties.ct(); ++i)
  {
    if(xproperties[i]->schema().base_space().le(&lsmaller->schema().base_space()))
    {
      lsmaller = xproperties[i];
    }
  }

  initialize_vtk_mesh_data(*lsmaller, xcoords.name());

  // Reset the property data.

  _vtk_prop_dofs.set_ct(0);
  _prop_is_pt_data.set_ct(0);
  _prop_tensor_rank.set_ct(0);

  // Initialize property data.

  for(int i=0; i<xproperties.ct(); ++i)
  {
    initialize_vtk_prop_data(xproperties[i]);
  }


  visualization_iterator* litr;

  // Tranfer the coordinates and the first property to vtk.

  if(xcoords.is_jim())
  {
    // The coords are an ordinary section, not multi-section.
    // Gather the point and cell data for the section.

    litr =
      visualization_iterator::new_visualization_iterator(xcoords.schema(),
                                                         xproperties[0]->schema());

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    while(!litr->is_done())
    {
      litr->set_vtk_data(xcoords,
                         *xproperties[0],
                         _vtk_coord_dofs,
                         _vtk_prop_dofs[0],
                         _prop_tensor_rank[0],
                         *_vtk_cell_types,
                         *_vtk_cell_connectivity,
                         _cell_type_map,
			 _vtk_pt_label_ids,
			 _vtk_cell_label_ids);
      litr->next();
    }
    delete litr;
  }
  else
  {
    // The coords are a multi-section.
    // Gather the point and cell data separately for each branch.

    sec_rep_space* lhost = xcoords.host();

    litr =
      visualization_iterator::new_visualization_iterator(xcoords.schema(),
                                                         xproperties[0]->schema(),
                                                         false);

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    sec_vd lbranch;
    preorder_iterator lbranch_itr(xcoords, "jims", DOWN, NOT_STRICT);
    while(!lbranch_itr.is_done())
    {
      lbranch.attach_to_state(lhost, lbranch_itr.index());
      section_space_schema_member& lbranch_schema =
        lhost->member_dof_map(lbranch_itr.index()).schema();

      litr->put_anchor(lbranch_schema, xproperties[0]->schema());
      litr->reset();

      while(!litr->is_done())
      {
        litr->set_vtk_data(lbranch,
                           *xproperties[0],
                           _vtk_coord_dofs,
                           _vtk_prop_dofs[0],
                           _prop_tensor_rank[0],
                           *_vtk_cell_types,
                           *_vtk_cell_connectivity,
                           _cell_type_map,
			   _vtk_pt_label_ids,
			   _vtk_cell_label_ids);
        litr->next();
      }
      lbranch_itr.next();
    }

    lbranch.detach_from_state();
    delete litr;
  }

  // Transfer the remaining properties to vtk.

  for(int i=1; i<xproperties.ct(); ++i)
  {
    /// @hack we don't need to iterate over the coordinates now,
    /// but the iterators don't know how to avoid it.

    litr =
      visualization_iterator::new_visualization_iterator(xcoords.schema(),
                                                         xproperties[i]->schema());

    litr->put_use_point_top_ids(_use_point_top_ids);
    litr->put_use_cell_top_ids(_use_cell_top_ids);

    while(!litr->is_done())
    {
      litr->set_vtk_data(*xproperties[i], _vtk_prop_dofs[i], _prop_tensor_rank[i]);
      litr->next();
    }

    delete litr;
  }

  // Finalize vtk data.

  finalize_vtk_mesh_data(xresult);

  for(int i=0; i<xproperties.ct(); ++i)
  {
    finalize_vtk_prop_data(xproperties[i],
                           _prop_is_pt_data[i],
                           _prop_tensor_rank[i],
                           _vtk_prop_dofs[i],
                           xresult);
  }

  // Encourage vtk to reclaim memory.

  xresult.Squeeze();

#ifdef DIAGNOSTIC_OUTPUT
  vtkIndent lindent;
  xresult.PrintSelf(cout, lindent);
#endif

  // Postconditions:

  // Exit:

  return;
}


// ============================================================================
// PRIVATE MEMBER FUNCTIONS
// ============================================================================

sheaf::namespace_poset&
tool::vtk_unstructured_grid_builder::
name_space() const
{
  return *_name_space;
}

void
tool::vtk_unstructured_grid_builder::
init_cell_type_map()
{
  // Preconditions:

  require(name_space().state_is_read_accessible());

  // Body:

  poset* lprototypes =
    &name_space().member_poset<poset>(base_space_member::prototypes_poset_name(),
                                     false);
  lprototypes->get_read_access();

  _cell_type_map.reserve(lprototypes->member_index_ub().pod());

  _cell_type_map.set_ct(_cell_type_map.ub());
  _cell_type_map.assign(0);

  base_space_member lmbr;
  lmbr.attach_to_state(lprototypes, "point");
  _cell_type_map.set_item(lmbr.type_id(), 1);

  lmbr.attach_to_state(lprototypes, "segment");
  _cell_type_map.set_item(lmbr.type_id(), 3);

  lmbr.attach_to_state(lprototypes, "segment_complex");
  _cell_type_map.set_item(lmbr.type_id(), 3);

  lmbr.attach_to_state(lprototypes, "triangle");
  _cell_type_map.set_item(lmbr.type_id(), 5);

  lmbr.attach_to_state(lprototypes, "triangle_nodes");
  _cell_type_map.set_item(lmbr.type_id(), 5);

  lmbr.attach_to_state(lprototypes, "triangle_complex");
  _cell_type_map.set_item(lmbr.type_id(), 5);

  lmbr.attach_to_state(lprototypes, "quad");
  _cell_type_map.set_item(lmbr.type_id(), 9);

  lmbr.attach_to_state(lprototypes, "quad_nodes");
  _cell_type_map.set_item(lmbr.type_id(), 9);

  lmbr.attach_to_state(lprototypes, "quad_complex");
  _cell_type_map.set_item(lmbr.type_id(), 9);

  lmbr.attach_to_state(lprototypes, "hex");
  _cell_type_map.set_item(lmbr.type_id(), 12);

  lmbr.attach_to_state(lprototypes, "hex_nodes");
  _cell_type_map.set_item(lmbr.type_id(), 12);

  lmbr.attach_to_state(lprototypes, "hex_complex");
  _cell_type_map.set_item(lmbr.type_id(), 12);

  lmbr.attach_to_state(lprototypes, "tetra");
  _cell_type_map.set_item(lmbr.type_id(), 10);

  lmbr.attach_to_state(lprototypes, "tetra_nodes");
  _cell_type_map.set_item(lmbr.type_id(), 10);

  lmbr.attach_to_state(lprototypes, "tetra_complex");
  _cell_type_map.set_item(lmbr.type_id(), 10);

  lmbr.detach_from_state();
  lprototypes->release_access();

  // Postconditions:

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
set_cell_data(abstract_poset_member& xbase,
              const string& xpartition_name,
              vtkUnstructuredGrid& xresult)
{
  // Preconditions:

  require(!xpartition_name.empty());
  require(xbase.host()->member_id_spaces(true).contains(xpartition_name));  

  // Body:

  // Create the paritition coloring data

  vtkDoubleArray* lvtk_part_ids = vtkDoubleArray::New();
  string lpart_ids_name(xpartition_name + "_mbr_ids");
  lvtk_part_ids->SetName(lpart_ids_name.c_str());
  lvtk_part_ids->SetNumberOfComponents(1);
  lvtk_part_ids->SetNumberOfTuples(_cell_ct);

#ifdef DIAGNOSTIC_OUTPUT
  cout << xbase << endl;
#endif

  subposet lparts(xbase.host(), xpartition_name);

  const index_space_handle& lpart_space = lparts.id_space();
  double lpart_id = 0.0;

  subposet lzones(xbase.host(), "__elements");
  int lzone_id = 0;
  bool ltruncate = false;

  biorder_iterator lpart_itr(xbase, DOWN, NOT_STRICT);
  while(!lpart_itr.is_done())
  {
    scoped_index lmbr_id = lpart_itr.index();
    switch(lpart_itr.action())
    {
      case biorder_iterator::PREVISIT_ACTION:

        if(lparts.contains_member(lmbr_id))
        {
          // This member is one of the parts;
          // set the current part id and continue descent

	  lpart_id = static_cast<double>(lpart_space.pod(lmbr_id) + 1);

#ifdef DIAGNOSTIC_OUTPUT
          cout << "entering part with mbr_id: " << lmbr_id
               << " and with part id: " << lpart_id
               << endl;
#endif

          ltruncate = false;
        }
        else if(lzones.contains_member(lmbr_id))
        {
          // This member is a zone;
          // store the current part id as cell data.
          // No need to go deeper.


#ifdef DIAGNOSTIC_OUTPUT
          cout << "mbr_id: " << lmbr_id
               << " is a zone with seq id: " << lzone_id
               << " and with part id: " << lpart_id
               << endl;
#endif

          lvtk_part_ids->SetTuple(lzone_id++, &lpart_id);
          ltruncate = true;
        }
        else
        {
          // This member is neither a part nor a zone;
          // just continue descent.

          ltruncate = false;
        }

        break;
      case biorder_iterator::POSTVISIT_ACTION:

        if(lparts.contains_member(lmbr_id))
        {
          // This member is one of the parts and we're leaving it;
          // set the current part id back to -1.

#ifdef DIAGNOSTIC_OUTPUT
          cout << "leaving part with mbr_id: " << lmbr_id
               << " and with part id: " << lpart_id
               << endl;
#endif

          lpart_id = 0.0;
          ltruncate = false;
        }

        break;
      default:
        post_fatal_error_message("Unrecognized iterator action");
        break;
    }
    lpart_itr.next(ltruncate);
  }

  // Set the partition data into the result.

  xresult.GetCellData()->SetScalars(lvtk_part_ids);

  // Clean up.

  lzones.detach_from_state();
  lparts.detach_from_state();
  lvtk_part_ids->Delete();

  // Postconditions:

  // Exit:

  return;
}

bool
tool::vtk_unstructured_grid_builder::
is_scalar(const sec_vd* xsec) const
{
  // Preconditions:

  require(xsec->state_is_read_accessible());

  // Body:

  static const int num_paths = 2;

  static const string schema_paths[num_paths] =
    {
      "fiber_space_schema/at0_schema",
      "fiber_space_schema/e1_schema"
    };

  bool result = false;

  const schema_poset_member& fiber_schema = xsec->schema().fiber_schema();

  for(int i=0; i<num_paths; ++i)
  {
    result = fiber_schema.conforms_to(schema_paths[i]);
    if(result)
      break;
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
tool::vtk_unstructured_grid_builder::
is_vector(const sec_vd* xsec) const
{
  // Preconditions:

  require(xsec->state_is_read_accessible());

  // Body:

  static const int num_paths = 2;

  static const string schema_paths[num_paths] =
    {
      "fiber_space_schema/e2_schema",
      "fiber_space_schema/e3_schema"
    };

  bool result = false;

  const schema_poset_member& fiber_schema = xsec->schema().fiber_schema();

  for(int i=0; i<num_paths; ++i)
  {
    result = fiber_schema.conforms_to(schema_paths[i]);
    if(result)
      break;
  }

  // Postconditions:

  // Exit:

  return result;
}

bool
tool::vtk_unstructured_grid_builder::
is_tensor(const sec_vd* xsec) const
{
  // Preconditions:

  require(xsec->state_is_read_accessible());

  // Body:

  ///@todo Complete the list of tensor types.

  static const int num_paths = 7;

  static const string schema_paths[num_paths] =
    {
      // VTK only supports rank 2 symmetric tensors
      // "fiber_space_schema/at2_e2_schema",
      // "fiber_space_schema/at2_e3_schema",
      // "fiber_space_schema/t02_e2_schema",
      // "fiber_space_schema/t02_e3_schema",
      // "fiber_space_schema/t03_e3_schema",
      "fiber_space_schema/st2_e2_schema",
      "fiber_space_schema/st2_e3_schema"
    };

  bool result = false;

  const schema_poset_member& fiber_schema = xsec->schema().fiber_schema();

  for(int i=0; i<num_paths; ++i)
  {
    result = fiber_schema.conforms_to(schema_paths[i]);
    if(result)
      break;
  }

  // Postconditions:

  // Exit:

  return result;
}

void
tool::vtk_unstructured_grid_builder::
initialize_vtk_mesh_data(const sec_vd& xsec, string xcoords_name)
{
  // Preconditions:

  require(xsec.state_is_read_accessible());

  /// @hack multisections have to be represented on vertices/elements.
  /// @todo implement other cases below.

  require(!xsec.is_jim() ?
          (xsec.schema().rep().name() == "vertex_element_dlinear" ||
           xsec.schema().rep().name() == "vertex_vertex_constant")  :
          true);

  // Body:

  const section_space_schema_member& lschema = xsec.schema();
  int ldb = lschema.db();
  base_space_poset& lbase_host = lschema.host()->base_space();
  _is_point_mesh = (lbase_host.max_db() == 0);

  // Calculate the vertex and cell counts.

  _pt_ct = 0;
  postorder_iterator litr(xsec.base(), lbase_host.d_cells(0), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    _pt_ct++;
    litr.next();
  }

  _cell_ct = 0;  
  postorder_iterator litr2(xsec.base(), lbase_host.d_cells(ldb), DOWN, NOT_STRICT);
  while(!litr2.is_done())
  {
    _cell_ct++;
    litr2.next();
  }

  // Allocate the vtk coord data arrays.
  // Parameter xcoords_name passed by value because .c_str() modifies state.

  _vtk_coord_dofs = vtkDoubleArray::New();
  _vtk_coord_dofs->SetName(xcoords_name.c_str());
  _vtk_coord_dofs->SetNumberOfComponents(3);  // Must be 3 for vtkPoints (coordinates)
  _vtk_coord_dofs->SetNumberOfTuples(_pt_ct);

  // Allocate space in the vtk cell type and connectivity arrays;
  // blocks will resize but we want to avoid many small reallocations.

  _vtk_cell_types->reserve(_cell_ct);
  _vtk_cell_types->set_ct(0);

  _vtk_cell_connectivity->reserve(_cell_ct*9);
  _vtk_cell_connectivity->set_ct(0);


  _vtk_pt_label_ids = vtkIdTypeArray::New();
  _vtk_pt_label_ids->SetName("point_label_ids");
  _vtk_pt_label_ids->SetNumberOfComponents(1);

  // Will use SetValue in vis itr set_vtk_data,
  // so have to set number of values.

  _vtk_pt_label_ids->SetNumberOfValues(_pt_ct);

  _vtk_cell_label_ids = vtkIdTypeArray::New();
  _vtk_cell_label_ids->SetName("cell_label_ids");
  _vtk_cell_label_ids->SetNumberOfComponents(1);

  // Will use InsertNextTuple in vis itr set_vtk_data,
  // so must not set number of values.

  //  _vtk_cell_label_ids->SetNumberOfTuples(_cell_ct);

  // Postconditions:

#ifdef DIAGNOSTIC_OUTPUT
  cout << "in initialize_vtk_mesh_data: pt ct: " << _pt_ct
       << " cell ct: " << _cell_ct << endl;
#endif

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
finalize_vtk_mesh_data(vtkUnstructuredGrid& xresult)
{
  // Preconditions:

  // Body:

  // Construct the vtk point object.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetNumberOfPoints(_pt_ct);
  lvtk_points->SetData(_vtk_coord_dofs);
  lvtk_points->SetDataTypeToDouble();
  xresult.SetPoints(lvtk_points);

  // Set the cell data in the result.

  vtkCellArray* lvtk_cells = vtkCellArray::New();
  lvtk_cells->Allocate(_cell_ct);

  vtkIdTypeArray* lvtk_connectivity = vtkIdTypeArray::New();
  lvtk_connectivity->SetNumberOfComponents(1);
  lvtk_connectivity->SetArray(_vtk_cell_connectivity->base(),
                              _vtk_cell_connectivity->ct(),
                              1);

  lvtk_cells->SetCells(_cell_ct, lvtk_connectivity);

  xresult.SetCells(_vtk_cell_types->base(), lvtk_cells);

  vtkPointData* lpt_data = xresult.GetPointData();
  lpt_data->AddArray(_vtk_pt_label_ids);

  vtkCellData* lcell_data = xresult.GetCellData();
  lcell_data->AddArray(_vtk_cell_label_ids);

  // Clean up.

  lvtk_points->Delete();
  _vtk_coord_dofs->Delete();
  lvtk_cells->Delete();
  lvtk_connectivity->Delete();
  _vtk_pt_label_ids->Delete();
  _vtk_cell_label_ids->Delete();
  
  // Postconditions:

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
initialize_vtk_prop_data(const sec_vd* xprop)
{
  // Preconditions:

  require(xprop->state_is_read_accessible());

  // Body:

  define_old_variable(int old_vtk_prop_dofs_ct = _vtk_prop_dofs.ct());

  const section_space_schema_member& lschema = xprop->schema();
  string lprop_name = xprop->name();

  /// @hack more accurate but less efficent definition of is_pt_data
  /// would be subposet vertices includes discretization.

  bool lprop_is_pt_data = _is_point_mesh || lschema.rep().eval_is_above_disc();
  _prop_is_pt_data.push_back(lprop_is_pt_data);

  int ltensor_rank;
  if(is_scalar(xprop))
  {
    ltensor_rank = 0;
  }
  else if(is_vector(xprop))
  {
    ltensor_rank = 1;
  }
  else if(is_tensor(xprop))
  {
    ltensor_rank = 2;
  }
  else
  {
    // Must be an abstract vector;
    // vtk doesn't exactly know what to do
    // with it, so lie.

    int ldf = xprop->schema().df();
    if(ldf == 1)
    {
      ltensor_rank = 0;
    }
    else if(ldf <= 3)
    {
      ltensor_rank = 1;
    }
    else
    {
      ltensor_rank = -1; // Not supported
    }
  }
  _prop_tensor_rank.push_back(ltensor_rank);

  vtkDoubleArray* lvtk_prop_dofs = vtkDoubleArray::New();
  lvtk_prop_dofs->SetName(lprop_name.c_str());
  lvtk_prop_dofs->SetNumberOfComponents(ltensor_rank == 2 ? 9 : lschema.df());
  lvtk_prop_dofs->SetNumberOfTuples(lprop_is_pt_data ? _pt_ct : _cell_ct);

  _vtk_prop_dofs.push_back(lvtk_prop_dofs);

  // Postconditions:

  ensure(_vtk_prop_dofs.ct() == old_vtk_prop_dofs_ct + 1);
  ensure(_prop_is_pt_data.ct() == _vtk_prop_dofs.ct());
  ensure(_prop_tensor_rank.ct() == _vtk_prop_dofs.ct());

  // Exit:

  return;
}

void
tool::vtk_unstructured_grid_builder::
finalize_vtk_prop_data(const sec_vd* xprop,
                       bool xprop_is_pt_data,
                       int xprop_tensor_rank,
                       vtkDoubleArray* xvtk_prop_dofs,
                       vtkUnstructuredGrid& xresult)
{
  // Preconditions:


  // Body:

  // Put the prop data into the result.

  vtkDataSetAttributes* latt;
  if(xprop_is_pt_data)
  {
    latt = xresult.GetPointData();
  }
  else
  {
    latt = xresult.GetCellData();
  }

  latt->DebugOn();

  switch(xprop_tensor_rank)
  {
    case 0:
      latt->SetScalars(xvtk_prop_dofs);
      break;
    case 1:
      latt->SetVectors(xvtk_prop_dofs);
      break;
    case 2:
      latt->SetTensors(xvtk_prop_dofs);
      break;
    default:
      post_warning_message("Algebraic type of property section not supported");
      break;
  }

  latt->DebugOff();

  // Clean up.

  xvtk_prop_dofs->Delete();

  // Postconditions:


  // Exit:

  return;
}


// ============================================================================
//  NON-MEMBER FUNCTIONS
// ============================================================================

