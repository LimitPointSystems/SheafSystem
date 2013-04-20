

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Implementation for class kd_display

#include "kd_display.h"
#include "assert_contract.h"
#include "at0.h"
#include "at0_space.h"
#include "at1.h"
#include "at1_space.h"
#include "base_space_member.h"
#include "base_space_member_prototype.h"
#include "base_space_poset.h"
#include "block.impl.h"
#include "d_cells_cohort.h"
#include "e3.h"
#include "fiber_bundles_namespace.impl.h"
#include "geometry_namespace.h"
#include "hash_set_filter.h"
#include "index_space_iterator.h"
#include "jim_cohort.h"
#include "kd_bounding_box.h"
#include "kd_edge.h"
#include "kd_edge_cohort.h"
#include "kd_face.h"
#include "kd_face_cohort.h"
#include "kd_lattice.h"
#include "kd_line.h"
#include "kd_line_fragment.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_segment.h"
#include "kd_surface.h"
#include "kd_triangle.h"
#include "kd_vertex.h"
#include "kd_vertex_cohort.h"
#include "kd_zone.h"
#include "kd_zone_cohort.h"
#include "linkorder_itr.h"
#include "postorder_itr.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_tuple_space.h"
#include "sec_e3.h"
#include "std_fstream.h"
#include "subcohort.h"
#include "tolerance_comparison.h"
#include "vertex_cohort.h"

#ifdef USE_VTK

#include "vtkActor.h"
#include "vtkAssembly.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkCellCenters.h"
#include "vtkCellData.h"
#include "vtkCubeAxesActor.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkDataSetMapper.h"
#include "vtkDoubleArray.h"
#include "vtkFieldData.h"
#include "vtkIdTypeArray.h"
#include "vtkIntArray.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLabeledDataMapper.h"
#include "vtkLookupTable.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSelectVisiblePoints.h"
#include "vtkTextProperty.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkUnstructuredGrid.h"
#include "vtkUnstructuredGridWriter.h"

#endif // USE_VTK

using namespace fiber_bundle;
using namespace fiber_bundle::vd_algebra;
using namespace geometry;

namespace
{
  
#ifdef USE_VTK

void build_exploded_zone_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{

  double lexpansion_factor = xkdl.display_expansion_factor();
  
  const sec_e3& lcoords = xkdl.coords();
  //  sec_e3::host_type* lcoord_space = lcoords.host();  
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  scoped_index lvids[kd_zone::VERTEX_CT];
  vtkIdType* lvtk_vids = new vtkIdType[kd_zone::VERTEX_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove);
  
    // Get the vertices for the zone.
  
    lzone.vertices(lvids);    
    
    // Populate the vtk point data.

    e3_lite lcoord_fiber;
    double* lpoint = reinterpret_cast<double*>(lcoord_fiber.row_dofs());

    for(int i=0; i<kd_zone::VERTEX_CT; ++i)
    {
      // Get the unmoved coordinates.

      lcoords.get_fiber(lvids[i], lcoord_fiber, false);

      // Move them.

      lcoord_fiber += lmove;
      
      lvtk_points->InsertNextPoint(lpoint);

      // Label each corner of the zone
      // with the zone_id.

      lpt_label_ids->InsertNextValue(litr.index().pod());
      //      lpt_label_ids->InsertNextValue(lvids[i].pod());
      lvtk_vids[i] = lpt_ct++;
    }

    // Populate the vtk cell array.

    lvtk_cells->InsertNextCell(kd_zone::VERTEX_CT, lvtk_vids);

    // Move on.

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_HEXAHEDRON, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  return;
};

void build_exploded_line_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  //  cout << "Entering build_exploded_line_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[kd_segment::POINT_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove);
  
    // Get the line fragments for the zone.
    
    frag_list lfrags;
    lzone.line_fragments(lfrags);

    for(frag_list::iterator f=lfrags.begin(); f!=lfrags.end(); ++f)
    {
      // Get the first point of the line fragment.

      lpt_id = f->pt_ids.front();

      //      cout << "pt_id: " << lpt_id;

      // Get the unmoved coordinates of the first point.

      lcoords.get_fiber(lpt_id, lpt, false);

      //      cout<< " coords: " << lpt << endl;

      // Move them.

      lpt += lmove;

      // Insert the first point in the vtk point data
      // as the second point, it will get transferred
      // below.
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[1] = lpt_ct++;

      // Move past the first point.

      f->pt_ids.pop_front();

      // Iterate over the rest of the fragment.

      while(!f->pt_ids.empty())
      {
        // First point is same as preceeding second point.

        lvtk_vids[0] = lvtk_vids[1];

        // Get the second point of the segment.

        lpt_id = f->pt_ids.front();
      
        // Get the unmoved coordinates of the second point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "  pt1_id: " << setw(6) << lpt_id.internal_pod() << "  coords: " << setw(12) << lpt[0] << endl;

        // Move them.

        lpt += lmove;

        // Insert the second point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lpt_label_ids->InsertNextValue(lpt_id.pod());
        lvtk_vids[1] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(kd_segment::POINT_CT, lvtk_vids);      

        // Move to the next segment.

        f->pt_ids.pop_front();
      } // end points in fragment
    } // end for all fragments

    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_LINE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_line_grid" << endl;
  return;
};

void build_line_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  //  cout << "Entering build_line_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[kd_segment::POINT_CT];

  // Iterate over the leaf zones.

  int lpt_ct = 0;
  int lcell_ct = 0;
  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());
  
    // Get the line fragments for the zone.
    
    frag_list lfrags;
    lzone.line_fragments(lfrags);

    for(frag_list::iterator f=lfrags.begin(); f!=lfrags.end(); ++f)
    {
      // Get the first point of the line fragment.

      lpt_id = f->pt_ids.front();

      //      cout << "pt_id: " << lpt_id;

      // Get the coordinates of the first point.

      lcoords.get_fiber(lpt_id, lpt, false);

      //      cout<< " coords: " << lpt << endl;

      // Insert the first point in the vtk point data
      // as the second point, it will get transferred
      // below.
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[1] = lpt_ct++;

      // Move past the first point.

      f->pt_ids.pop_front();

      // Iterate over the rest of the fragment.

      while(!f->pt_ids.empty())
      {
        // First point is same as preceeding second point.

        lvtk_vids[0] = lvtk_vids[1];

        // Get the second point of the segment.

        lpt_id = f->pt_ids.front();
      
        // Get the unmoved coordinates of the second point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "  pt1_id: " << setw(6) << lpt_id.internal_pod() << "  coords: " << setw(12) << lpt[0] << endl;

        // Insert the second point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lpt_label_ids->InsertNextValue(lpt_id.pod());
        lvtk_vids[1] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(kd_segment::POINT_CT, lvtk_vids);      

        // Move to the next segment.

        f->pt_ids.pop_front();
      } // end points in fragment
    } // end for all fragments

    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_LINE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_line_grid" << endl;
  return;
};

void build_exploded_intersection_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "intersection_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the unmoved coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Move them.

      lpt += lmove;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_point_grid" << endl;
  return;
};

void build_intersection_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "intersection_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_intersection_point_grid" << endl;
  return;
};

void build_exploded_first_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_first_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_first(xkdl, lpt_id))
      {
        // Get the unmoved coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Move them.

        lpt += lmove;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_first_point_grid" << endl;
  return;
};

void build_exploded_last_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_last_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_last(xkdl, lpt_id))
      {
        // Get the unmoved coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Move them.

        lpt += lmove;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_last_point_grid" << endl;
  return;
};

void build_exploded_first_and_last_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_first_and_last_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_first(xkdl, lpt_id) && kd_point::is_last(xkdl, lpt_id))
      {
        // Get the unmoved coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Move them.

        lpt += lmove;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_first_and_last_point_grid" << endl;
  return;
};

void build_first_and_last_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_first_and_last_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_first(xkdl, lpt_id) && kd_point::is_last(xkdl, lpt_id))
      {
        // Get the coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_first_and_last_point_grid" << endl;
  return;
};

void build_first_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_first_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_first(xkdl, lpt_id))
      {
        // Get the coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_first_point_grid" << endl;
  return;
};

void build_last_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_last_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "__vertices", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();

      if(kd_point::is_last(xkdl, lpt_id))
      {
        // Get the coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lvtk_vids[0] = lpt_ct++;

        // Populate the vtk cell array.

        lvtk_cells->InsertNextCell(1, lvtk_vids);
      }      

      // Move to the next point.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_last_point_grid" << endl;
  return;
};

void build_exploded_triangle_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_triangle_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[kd_triangle::POINT_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // cout << "zone: " << lzone.id().pod() << "  " << lzone.name() << endl;

    // Want to move each point of the triangle
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove);
  
    // Get the triangles for the zone.
  
    list<scoped_index> ltriangles;
    lzone.triangle_members(ltriangles);

    while(!ltriangles.empty())
    {
      int i = 0;
      while(ltriangles.front().is_valid())
      {

        // Get the point.

        lpt_id = ltriangles.front();
      
        // Get the unmoved coordinates of the point.

        lcoords.get_fiber(lpt_id, lpt, false);

        // cout << "  pt_id: " << setw(6) << lpt_id.internal_pod() << "  coords: " << setw(12) << lpt[0] << endl;

        // Move them.

        lpt += lmove;

        // Insert the point in the vtk point data
      
        lvtk_points->InsertNextPoint(lpt_dofs);
        lpt_label_ids->InsertNextValue(lpt_id.pod());
        lvtk_vids[i++] = lpt_ct++;

        // Move to the next point.

        ltriangles.pop_front();
      }

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(kd_triangle::POINT_CT, lvtk_vids);      

      // Skip past the triangle terminator.

      ltriangles.pop_front();

    } // end while !ltriangles.empty()    

    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_TRIANGLE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_triangle_grid" << endl;
  return;
};

void build_triangle_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  //  cout << "Entering build_triangle_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

//   e3_lite lpt;
//   double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
//   scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);


  vtkIdType* lvtk_vids = new vtkIdType[kd_triangle::POINT_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  scoped_index ltri_pt_ids[kd_triangle::POINT_CT];
  e3_lite ltri_pts[kd_triangle::POINT_CT];

  typedef hash_map<pod_index_type, pod_index_type> pt_id_map_type;
  pt_id_map_type lpt_id_map;
  pt_id_map_type::iterator lmap_itr;

  // Iterate over the active triangles.

  zn_to_bool_postorder_itr litr(xkdl.active_part(), xkdl.triangles().sp(), DOWN, NOT_STRICT);
  while(!litr.is_done())
  {
    kd_triangle ltri(xkdl, litr.index());

    ltri.points(ltri_pt_ids, ltri_pts);

    // Insert the points in the vtk point data
    // @hack: treat every point as unique.
      
    int i=0;
    
    for(i=0; i<kd_triangle::POINT_CT; ++i)
    {
      lmap_itr = lpt_id_map.find(ltri_pt_ids[i].pod());
      if(lmap_itr != lpt_id_map.end())
      {
        // Pt id was already in the map.

        lvtk_vids[i] = lmap_itr->second;
      }
      else
      {
        // pt id was not in the map;
        // enter the point data in vtk and
        // enter the pt id in the map..

        lvtk_points->InsertNextPoint(reinterpret_cast<double*>(ltri_pts[i].row_dofs()));
        lpt_id_map[ltri_pt_ids[i].pod()] = lpt_ct;
        lpt_label_ids->InsertNextValue(ltri_pt_ids[i].pod());
        lvtk_vids[i] = lpt_ct++;
      }
    }

    // Populate the vtk cell array.

    lvtk_cells->InsertNextCell(kd_triangle::POINT_CT, lvtk_vids);

    // Move to next triangle.

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_TRIANGLE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // $$SCRIBBLE: should we Delete the vtk ptrs?

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_triangle_grid" << endl;
  return;
};

void create_pt_labels(vtkUnstructuredGrid* xresult, vtkRenderer* xren, vtkAssembly* xassembly)
{  
  vtkTransform* ltransform = vtkTransform::New();
  if(xassembly != 0)
  {
    ltransform->SetMatrix(xassembly->GetMatrix());
  }

  vtkTransformFilter* ltransform_filter = vtkTransformFilter::New();
  ltransform_filter->SetInput(xresult);
  ltransform_filter->SetTransform(ltransform);

  vtkSelectVisiblePoints* lpt_labels_vis_pts = vtkSelectVisiblePoints::New();
  //  lpt_labels_vis_pts->SetTolerance(sheaf::double_tolerance);
  lpt_labels_vis_pts->SetInput(ltransform_filter->GetOutput());
  lpt_labels_vis_pts->SetRenderer(xren);


  vtkLabeledDataMapper* ldata_mapper = vtkLabeledDataMapper::New();
  ldata_mapper->SetInput(lpt_labels_vis_pts->GetOutput());

  ldata_mapper->SetLabelFormat("%ld");
  ldata_mapper->GetLabelTextProperty()->ShadowOff();    
  ldata_mapper->GetLabelTextProperty()->SetFontSize(18);    
  ldata_mapper->GetLabelTextProperty()->SetColor(0, 0, 0);    
  ldata_mapper->SetLabelModeToLabelFieldData();
  ldata_mapper->SetFieldDataArray(0);

  vtkActor2D* lpt_labels_actor = vtkActor2D::New();
  lpt_labels_actor->SetMapper(ldata_mapper);
  lpt_labels_actor->GetProperty()->SetColor(0.0, 0.0, 0.0);

  // Add actor to the renderer.

  xren->AddActor(lpt_labels_actor);

  return;
}

void create_cell_labels(vtkUnstructuredGrid* xresult, vtkRenderer* xren)
{  
  vtkTransform* ltransform = vtkTransform::New();
  vtkTransformFilter* ltransform_filter = vtkTransformFilter::New();
  ltransform_filter->SetInput(xresult);
  ltransform_filter->SetTransform(ltransform);

  //CellCenters doesn't seem to pass on the cell field data as it should.
  vtkCellCenters* lcc = vtkCellCenters::New();
  lcc->SetInput(ltransform_filter->GetOutput());

  vtkSelectVisiblePoints* lcell_labels_vis_cells = vtkSelectVisiblePoints::New();
  lcell_labels_vis_cells->SetTolerance(0.01*sheaf::double_tolerance);
  //  lcell_labels_vis_cells->SetInput(ltransform_filter->GetOutput());
  lcell_labels_vis_cells->SetInput(lcc->GetOutput());
  lcell_labels_vis_cells->SetRenderer(xren);

  vtkLabeledDataMapper* ldata_mapper = vtkLabeledDataMapper::New();
  ldata_mapper->SetInput(lcell_labels_vis_cells->GetOutput());

  ldata_mapper->SetLabelFormat("%ld");
  ldata_mapper->GetLabelTextProperty()->ShadowOff();    
  ldata_mapper->GetLabelTextProperty()->SetFontSize(18);    
  ldata_mapper->GetLabelTextProperty()->SetColor(0, 0, 0);    
  ldata_mapper->SetLabelModeToLabelFieldData();
  ldata_mapper->SetFieldDataArray(0);

  vtkActor2D* lcell_labels_actor = vtkActor2D::New();
  lcell_labels_actor->SetMapper(ldata_mapper);
  lcell_labels_actor->GetProperty()->SetColor(1, 1, 1);

  // Add actor to the renderer.

  xren->AddActor(lcell_labels_actor);

  return;
}


void build_exploded_truncation_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_truncation_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the unmoved coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Move them.

      lpt += lmove;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_truncation_point_grid" << endl;
  return;
};

void build_truncation_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_truncation_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_truncation_point_grid" << endl;
  return;
};

void build_exploded_truncation_reversal_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_truncation_reversal_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_reversal_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the unmoved coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Move them.

      lpt += lmove;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_truncation_reversal_point_grid" << endl;
  return;
};

void build_truncation_reversal_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_truncation_reversal_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_reversal_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_truncation_reversal_point_grid" << endl;
  return;
};

void build_exploded_truncation_mid_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_truncation_mid_point_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();

  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    // Want to move each point of the zone
    // some distance away from the the top center
    // in the direction from the top conter 
    // to the zone center. Compute the move vector.

    e3_lite lmove(lzone.center());
    lmove -= ltop_ctr;
    multiply(lmove, lexpansion_factor, lmove); 

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_mid_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the unmoved coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Move them.

      lpt += lmove;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_truncation_mid_point_grid" << endl;
  return;
};

void build_truncation_mid_point_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_truncation_mid_point_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  e3_lite lpt;
  double* lpt_dofs = reinterpret_cast<double*>(lpt.row_dofs());
  scoped_index lpt_id;

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  vtkIdType* lvtk_vids = new vtkIdType[1];
  int lpt_ct = 0;
  int lcell_ct = 0;

  // Iterate over the leaf zones.

  index_iterator litr = xkdl.zone_leaves().sp().indexed_member_iterator();
  while(!litr.is_done())
  {
    kd_zone lzone(xkdl, litr.index());

    base_space_member lzone_mbr(&xkdl.base_space(), litr.index());
    hash_set_postorder_itr lpt_itr(lzone_mbr, "truncation_mid_points", DOWN, NOT_STRICT);
    while(!lpt_itr.is_done())
    {
      lpt_id = lpt_itr.index();
      
      // Get the coordinates of the point.

      lcoords.get_fiber(lpt_id, lpt, false);

      // cout << "pt_id: " << lpt_id << " coords: " << lpt << endl;

      // Insert the point in the vtk point data
      
      lvtk_points->InsertNextPoint(lpt_dofs);
      lpt_label_ids->InsertNextValue(lpt_id.pod());
      lvtk_vids[0] = lpt_ct++;

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(1, lvtk_vids);

      // Move to the next segment.

      lpt_itr.next();
    }
    lzone_mbr.detach_from_state();
    
    // Move to next zone..

    litr.next();
  }  

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_VERTEX, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_truncation_mid_point_grid" << endl;
  return;
};

void display_vtk_grid(vtkRenderer* xrenderer, 
		      vtkUnstructuredGrid* xzone_grid, 
                      vtkUnstructuredGrid* xline_grid, 
                      vtkUnstructuredGrid* xintersection_point_grid, 
                      vtkUnstructuredGrid* xfirst_point_grid, 
                      vtkUnstructuredGrid* xlast_point_grid, 
                      vtkUnstructuredGrid* xtriangle_grid, 
                      vtkUnstructuredGrid* xtruncation_point_grid, 
                      vtkUnstructuredGrid* xtruncation_reversal_point_grid, 
                      vtkUnstructuredGrid* xtruncation_mid_point_grid,
                      double xorigin[],
                      double xscale[],
                      bool xpt_labels)
{
  // Clear renderer.

  vtkAssembly* lassembly = vtkAssembly::New();

  if(xzone_grid != 0)
  {  
    // Create the vtk mapper for the zone grid.

    vtkDataSetMapper* lzone_grid_mapper = vtkDataSetMapper::New();
    lzone_grid_mapper->SetInput(xzone_grid);

    // Create the zone grid actor.

    vtkActor* lzone_grid_actor = vtkActor::New();
    lzone_grid_actor->SetMapper(lzone_grid_mapper);

    // Turn edge visibility on.

    lzone_grid_actor->GetProperty()->EdgeVisibilityOn();
    lzone_grid_actor->GetProperty()->SetOpacity(0.2);

    // Add the actor to the assmebly.

    lassembly->AddPart(lzone_grid_actor);
  }
  
  if((xline_grid != 0)  && (xline_grid->GetNumberOfCells() != 0))
  {  
    // Create the vtk mapper for the line grid.

    vtkDataSetMapper* lline_grid_mapper = vtkDataSetMapper::New();
    lline_grid_mapper->SetInput(xline_grid);

    // Create the line grid actor.

    vtkActor* lline_grid_actor = vtkActor::New();
    lline_grid_actor->SetMapper(lline_grid_mapper);

    // Set the color and width

    lline_grid_actor->GetProperty()->SetColor(.9, 0.9, 0.9); // White
    lline_grid_actor->GetProperty()->SetLineWidth(6.0);

    // Add the actor to the assmebly.

    lassembly->AddPart(lline_grid_actor);
  }
  
  if(xintersection_point_grid != 0)
  {
    // Create the vtk mapper for the intersection point grid.

    vtkDataSetMapper* lintersection_point_grid_mapper = vtkDataSetMapper::New();
    lintersection_point_grid_mapper->SetInput(xintersection_point_grid);

    // Create the intersection point grid actor.

    vtkActor* lintersection_point_grid_actor = vtkActor::New();
    lintersection_point_grid_actor->SetMapper(lintersection_point_grid_mapper);

    // Set the color and size for the intersection point grid

    lintersection_point_grid_actor->GetProperty()->SetColor(0.9, 0.9, 0.9); // White
    lintersection_point_grid_actor->GetProperty()->SetPointSize(24.0);

    // Add the actor to the assmebly.

    lassembly->AddPart(lintersection_point_grid_actor);
  }
  
  if(xfirst_point_grid != 0)
  {
    // Create the vtk mapper for the first point grid.

    vtkDataSetMapper* lfirst_point_grid_mapper = vtkDataSetMapper::New();
    lfirst_point_grid_mapper->SetInput(xfirst_point_grid);

    // Create the first point grid actor.

    vtkActor* lfirst_point_grid_actor = vtkActor::New();
    lfirst_point_grid_actor->SetMapper(lfirst_point_grid_mapper);

    // Set the color and size for the first point grid

    lfirst_point_grid_actor->GetProperty()->SetColor(0.0, 0.9, 0.0); // Green
    lfirst_point_grid_actor->GetProperty()->SetPointSize(16.0);

    // Add the actor to the assmebly.

    lassembly->AddPart(lfirst_point_grid_actor);
  }
  
  if(xlast_point_grid != 0)
  {
    // Create the vtk mapper for the last point grid.

    vtkDataSetMapper* llast_point_grid_mapper = vtkDataSetMapper::New();
    llast_point_grid_mapper->SetInput(xlast_point_grid);

    // Create the last point grid actor.

    vtkActor* llast_point_grid_actor = vtkActor::New();
    llast_point_grid_actor->SetMapper(llast_point_grid_mapper);

    // Set the color and size for the last point grid

    llast_point_grid_actor->GetProperty()->SetColor(0.9, 0.0, 0.0); // Red
    llast_point_grid_actor->GetProperty()->SetPointSize(12.0);

    // Add the actor to the assmebly.

    lassembly->AddPart(llast_point_grid_actor);
  }
  
  if((xtriangle_grid != 0) && (xtriangle_grid->GetNumberOfCells() != 0))
  {  
    // Create the vtk mapper for the triangle grid.

    vtkDataSetMapper* ltriangle_grid_mapper = vtkDataSetMapper::New();
    ltriangle_grid_mapper->SetInput(xtriangle_grid);

    // Create the triangle grid actor.

    vtkActor* ltriangle_grid_actor = vtkActor::New();
    ltriangle_grid_actor->SetMapper(ltriangle_grid_mapper);

    // Turn edge visibility off.

    ltriangle_grid_actor->GetProperty()->EdgeVisibilityOn();
    ltriangle_grid_actor->GetProperty()->SetOpacity(1.0);
    ltriangle_grid_actor->GetProperty()->SetColor(0.9, 0.9, 0.0); // Yellow

    // Add the actor to the assmebly.

    lassembly->AddPart(ltriangle_grid_actor);
  }
  
  if(xtruncation_mid_point_grid != 0 && (xtruncation_mid_point_grid->GetNumberOfCells() != 0))
  {
    // Create the vtk mapper for the truncation mid point grid.

    vtkDataSetMapper* ltruncation_mid_point_grid_mapper = vtkDataSetMapper::New();
    ltruncation_mid_point_grid_mapper->SetInput(xtruncation_mid_point_grid);

    // Create the truncation point grid actor.

    vtkActor* ltruncation_mid_point_grid_actor = vtkActor::New();
    ltruncation_mid_point_grid_actor->SetMapper(ltruncation_mid_point_grid_mapper);

    // Set the color and size for the truncation point grid

    ltruncation_mid_point_grid_actor->GetProperty()->SetColor(0.9, 0.0, 0.9); // Magenta
    ltruncation_mid_point_grid_actor->GetProperty()->SetPointSize(24.0);

    // Add the actor to the assembly.

    lassembly->AddPart(ltruncation_mid_point_grid_actor);

//     // Create the point labels.

//     create_pt_labels(xtruncation_mid_point_grid, xrenderer);
  }  
  
  if(xtruncation_point_grid != 0)
  {
    // Create the vtk mapper for the truncation point grid.

    vtkDataSetMapper* ltruncation_point_grid_mapper = vtkDataSetMapper::New();
    ltruncation_point_grid_mapper->SetInput(xtruncation_point_grid);

    // Create the truncation point grid actor.

    vtkActor* ltruncation_point_grid_actor = vtkActor::New();
    ltruncation_point_grid_actor->SetMapper(ltruncation_point_grid_mapper);

    // Set the color and size for the truncation point grid

    ltruncation_point_grid_actor->GetProperty()->SetColor(0.0, 0.0, 0.9); // Blue
    ltruncation_point_grid_actor->GetProperty()->SetPointSize(24.0);

    // Add the actor to the assembly.

    lassembly->AddPart(ltruncation_point_grid_actor);
  }  
  
  if(xtruncation_reversal_point_grid != 0 && (xtruncation_reversal_point_grid->GetNumberOfCells() != 0))
  {
    // Create the vtk mapper for the truncation reversal point grid.

    vtkDataSetMapper* ltruncation_reversal_point_grid_mapper = vtkDataSetMapper::New();
    ltruncation_reversal_point_grid_mapper->SetInput(xtruncation_reversal_point_grid);

    // Create the truncation point grid actor.

    vtkActor* ltruncation_reversal_point_grid_actor = vtkActor::New();
    ltruncation_reversal_point_grid_actor->SetMapper(ltruncation_reversal_point_grid_mapper);

    // Set the color and size for the truncation point grid

    ltruncation_reversal_point_grid_actor->GetProperty()->SetColor(0.0, 0.9, 0.9); // Cyan
    ltruncation_reversal_point_grid_actor->GetProperty()->SetPointSize(16.0);

    // Add the actor to the assembly.

    lassembly->AddPart(ltruncation_reversal_point_grid_actor);
  }  

  // Compute the scale

  double* lbounds = new double[6];
  lassembly->GetBounds(lbounds);

  double lxsize = lbounds[1] - lbounds[0];
  double lysize = lbounds[3] - lbounds[2];
  double lzsize = lbounds[5] - lbounds[4];

  xorigin[0] = 0.5*(lbounds[1] + lbounds[0]);
  xorigin[1] = 0.5*(lbounds[3] + lbounds[2]);
  xorigin[2] = 0.5*(lbounds[5] + lbounds[4]);

  double lmax = lxsize > lysize ? lxsize : lysize;
  lmax = lzsize > lmax ? lzsize : lmax;

  xscale[0] = lmax/lxsize;
  xscale[1] = lmax/lysize;
  xscale[2] = lmax/lzsize;

  lassembly->SetOrigin(xorigin);
  lassembly->SetScale(xscale);

  // Add the assembly to the renderer.

  xrenderer->AddActor(lassembly);

  if(xpt_labels)
  {    
    // Create the point labels.

    if((xtriangle_grid != 0) && (xtriangle_grid->GetNumberOfCells() != 0))
    {
      create_pt_labels(xtriangle_grid, xrenderer, lassembly);
    }
    else if((xline_grid != 0) && (xline_grid->GetNumberOfCells() != 0))
      //    if((xline_grid != 0) && (xline_grid->GetNumberOfCells() != 0))
    {
      create_pt_labels(xline_grid, xrenderer, lassembly);
    }

    if(xzone_grid != 0)
    {
      create_pt_labels(xzone_grid, xrenderer, lassembly);
    }  
  }

  // Create bounding box axes.

  vtkCubeAxesActor* laxes = vtkCubeAxesActor::New();

  lassembly->GetBounds(lbounds);
  laxes->SetBounds(lbounds);
  delete [] lbounds;

  laxes->SetCamera(xrenderer->GetActiveCamera());
  laxes->SetFlyModeToStaticTriad();
  xrenderer->AddViewProp(laxes);
  xrenderer->ResetCamera();

};

void display_exploded_lattice(vtkRenderer* xrenderer, kd_lattice& xkdl, double xorigin[], double xscale[], bool xpt_labels)
{
  vtkUnstructuredGrid* lzone_grid = vtkUnstructuredGrid::New();
  build_exploded_zone_grid(xkdl, lzone_grid);

  vtkUnstructuredGrid* lline_grid = vtkUnstructuredGrid::New();
  build_exploded_line_grid(xkdl, lline_grid);

  vtkUnstructuredGrid* lintersection_point_grid = vtkUnstructuredGrid::New();
  build_exploded_intersection_point_grid(xkdl, lintersection_point_grid);

  vtkUnstructuredGrid* lfirst_point_grid = vtkUnstructuredGrid::New();
  build_exploded_first_point_grid(xkdl, lfirst_point_grid);

  vtkUnstructuredGrid* llast_point_grid = vtkUnstructuredGrid::New();
  build_exploded_last_point_grid(xkdl, llast_point_grid);

  vtkUnstructuredGrid* ltriangle_grid = vtkUnstructuredGrid::New();
  build_exploded_triangle_grid(xkdl, ltriangle_grid);

  vtkUnstructuredGrid* ltruncation_point_grid = vtkUnstructuredGrid::New();
  build_exploded_truncation_point_grid(xkdl, ltruncation_point_grid);

  vtkUnstructuredGrid* ltruncation_reversal_point_grid = vtkUnstructuredGrid::New();
  build_exploded_truncation_reversal_point_grid(xkdl, ltruncation_reversal_point_grid);

  vtkUnstructuredGrid* ltruncation_mid_point_grid = vtkUnstructuredGrid::New();
  build_exploded_truncation_mid_point_grid(xkdl, ltruncation_mid_point_grid);

  display_vtk_grid(xrenderer, lzone_grid, lline_grid, lintersection_point_grid, lfirst_point_grid, llast_point_grid, 
                   ltriangle_grid, ltruncation_point_grid, ltruncation_reversal_point_grid, ltruncation_mid_point_grid,
                   xorigin, xscale, xpt_labels);
};

void display_lattice(vtkRenderer* xrenderer, kd_lattice& xkdl, double xorigin[], double xscale[], bool xpt_labels)
{
  //   vtkUnstructuredGrid* lzone_grid = vtkUnstructuredGrid::New();
  //   build_exploded_zone_grid(xkdl, lzone_grid);

  vtkUnstructuredGrid* lline_grid = vtkUnstructuredGrid::New();
  build_line_grid(xkdl, lline_grid);

  vtkUnstructuredGrid* lintersection_point_grid = vtkUnstructuredGrid::New();
  build_intersection_point_grid(xkdl, lintersection_point_grid);

  vtkUnstructuredGrid* lfirst_point_grid = vtkUnstructuredGrid::New();
  build_first_point_grid(xkdl, lfirst_point_grid);

  vtkUnstructuredGrid* llast_point_grid = vtkUnstructuredGrid::New();
  build_last_point_grid(xkdl, llast_point_grid);

  vtkUnstructuredGrid* ltriangle_grid = vtkUnstructuredGrid::New();
  build_triangle_grid(xkdl, ltriangle_grid);

  vtkUnstructuredGrid* ltruncation_point_grid = vtkUnstructuredGrid::New();
  build_truncation_point_grid(xkdl, ltruncation_point_grid);

  vtkUnstructuredGrid* ltruncation_reversal_point_grid = vtkUnstructuredGrid::New();
  build_truncation_reversal_point_grid(xkdl, ltruncation_reversal_point_grid);

  vtkUnstructuredGrid* ltruncation_mid_point_grid = vtkUnstructuredGrid::New();
  build_truncation_mid_point_grid(xkdl, ltruncation_mid_point_grid);

  display_vtk_grid(xrenderer, 0, lline_grid, lintersection_point_grid, lfirst_point_grid, llast_point_grid, 
                   ltriangle_grid, ltruncation_point_grid, ltruncation_reversal_point_grid, ltruncation_mid_point_grid,
                   xorigin, xscale, xpt_labels);
};


void build_subvolume_triangle_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_subvolume_triangle_grid" << endl;
  
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  // Allocate the cell labels array.

  vtkIdTypeArray* lcell_label_ids = vtkIdTypeArray::New();
  lcell_label_ids->SetName("cell_label_ids");
  lcell_label_ids->SetNumberOfComponents(1);


  vtkIdType* lvtk_vids = new vtkIdType[kd_triangle::POINT_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  scoped_index ltri_pt_ids[kd_triangle::POINT_CT];
  e3_lite ltri_pts[kd_triangle::POINT_CT];

  typedef hash_map<pod_index_type, pod_index_type> pt_id_map_type;
  pt_id_map_type lpt_id_map;
  pt_id_map_type::iterator lmap_itr;

  // Iterate over the subvolume surfaces

  index_space_iterator& lsv_itr = xkdl.subvolume_surfaces().id_space().get_iterator();
  scoped_index lsv_id(xkdl.subvolume_surfaces().id_space());
  while(!lsv_itr.is_done())
  {
    // cout << "building vtk grid for subvolume: " << lsv_itr->pod() << "  " << kd_member::name(xkdl, lsv_itr->id()) << endl;
    
    // Iterate over triangles in this subvolume

    id_list ltris;
    lsv_id = lsv_itr.pod();
    kd_surface::triangles(xkdl, lsv_id, ltris);
    
    for(id_list::iterator lt=ltris.begin(); lt != ltris.end(); ++lt)
    {
      kd_triangle ltri(xkdl, *lt);

      // cout << "triangle: " << ltri.id().pod() << "  " << ltri.name() << endl;
      
      ltri.points(ltri_pt_ids, ltri_pts);

      // Insert the points in the vtk point data
      // @hack: treat every point as unique.
      
      int i=0;
    
      for(i=0; i<kd_triangle::POINT_CT; ++i)
      {
        lmap_itr = lpt_id_map.find(ltri_pt_ids[i].pod());
        if(lmap_itr != lpt_id_map.end())
        {
          // Pt id was already in the map.

          lvtk_vids[i] = lmap_itr->second;
        }
        else
        {
          // pt id was not in the map;
          // enter the point data in vtk and
          // enter the pt id in the map..

          lvtk_points->InsertNextPoint(reinterpret_cast<double*>(ltri_pts[i].row_dofs()));
          lpt_id_map[ltri_pt_ids[i].pod()] = lpt_ct;
          lpt_label_ids->InsertNextValue(ltri_pt_ids[i].pod());
          lvtk_vids[i] = lpt_ct++;
        }
      }

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(kd_triangle::POINT_CT, lvtk_vids);
      lcell_label_ids->InsertNextValue(lt->pod());
    }

    lsv_itr.next();
  }

  xkdl.subvolume_surfaces().id_space().release_iterator(lsv_itr);

  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_TRIANGLE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  vtkCellData* lcell_data = xresult->GetCellData();
  lcell_data->AddArray(lcell_label_ids);

  // $$SCRIBBLE: should we Delete the vtk ptrs?

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_subvolume_triangle_grid" << endl;
  return;
};

void build_exploded_subvolume_triangle_grid(kd_lattice& xkdl, vtkUnstructuredGrid* xresult)
{
  // cout << "Entering build_exploded_subvolume_triangle_grid" << endl;
  
  double lexpansion_factor = xkdl.display_expansion_factor();
  sec_e3& lcoords = xkdl.coords();
  lcoords.get_read_access();

  // Allocate the vtk point data.

  vtkPoints* lvtk_points = vtkPoints::New();
  lvtk_points->SetDataTypeToDouble();

  // Allocate the vtk cell array..

  vtkCellArray* lvtk_cells = vtkCellArray::New();

  // Allocate the pt labels array.

  vtkIdTypeArray* lpt_label_ids = vtkIdTypeArray::New();
  lpt_label_ids->SetName("point_label_ids");
  lpt_label_ids->SetNumberOfComponents(1);

  // Allocate the cell labels array.

  vtkIdTypeArray* lcell_label_ids = vtkIdTypeArray::New();
  lcell_label_ids->SetName("cell_label_ids");
  lcell_label_ids->SetNumberOfComponents(1);


  vtkIdType* lvtk_vids = new vtkIdType[kd_triangle::POINT_CT];
  int lpt_ct = 0;
  int lcell_ct = 0;

  scoped_index ltri_pt_ids[kd_triangle::POINT_CT];
  e3_lite ltri_pts[kd_triangle::POINT_CT];

  typedef hash_map<pod_index_type, pod_index_type> pt_id_map_type;
  pt_id_map_type lpt_id_map;
  pt_id_map_type::iterator lmap_itr;

  // Get the center of the top zone.

  e3_lite ltop_ctr(xkdl.top_zone().center());

  // Iterate over the subvolume surfaces

  index_space_iterator& lsv_itr = xkdl.subvolume_surfaces().id_space().get_iterator();
  scoped_index lsv_id(xkdl.subvolume_surfaces().id_space());
  while(!lsv_itr.is_done())
  {
    // cout << "building vtk grid for subvolume: " << lsv_itr->pod() << "  " << kd_member::name(xkdl, lsv_itr->id()) << endl;

    // Get the triangles for this subvolume.

    id_list ltris;
    lsv_id = lsv_itr.pod();
    kd_surface::triangles(xkdl, lsv_id, ltris);

    // Compute the centroid of this subvolume.
    // hack: just use the map we need for the pt labels
    // to make sure we only add each point once.

    pod_id_hash_set lsv_pt_set;
    int lsv_pt_ct = 0;
    e3_lite lsv_ctr(0.0, 0.0, 0.0);
    
    for(id_list::iterator lt=ltris.begin(); lt != ltris.end(); ++lt)
    {
      kd_triangle ltri(xkdl, *lt);

      ltri.points(ltri_pt_ids, ltri_pts);

      for(int i=0; i<kd_triangle::POINT_CT; ++i)
      {
        if(lsv_pt_set.find(ltri_pt_ids[i].pod()) == lsv_pt_set.end())
        {
          // Haven't seen this point before.
          // add to centroid and enter the pt id in the set
          // so we won't count it again.

          lsv_pt_set.insert(ltri_pt_ids[i].pod());
          lsv_ctr += ltri_pts[i];
          lsv_pt_ct++;
        }
      }
    }

    lsv_ctr /= lsv_pt_ct;
    
    e3_lite lmove(lsv_ctr);
    lmove -= ltop_ctr;
    lmove[0] = 0.0;
    lmove[1] = 0.0;
    lmove[2] *= lexpansion_factor;
    //    multiply(lmove, lexpansion_factor, lmove);

    // Clear the point map but not the pt_ct;
    // points on the boundary between subvolumes
    // get entered once for each subvolume.

    lpt_id_map.clear();

    // Iterate over triangles in this subvolume

    for(id_list::iterator lt=ltris.begin(); lt != ltris.end(); ++lt)
    {
      kd_triangle ltri(xkdl, *lt);

      // cout << "triangle: " << ltri.id().pod() << "  " << ltri.name() << endl;

      ltri.points(ltri_pt_ids, ltri_pts);

      // Insert the points in the vtk point data
      
      for(int i=0; i<kd_triangle::POINT_CT; ++i)
      {
        //         lmap_itr = lpt_id_map.find(ltri_pt_ids[i].pod());
        //         if(lmap_itr != lpt_id_map.end())
        //         {
        //           // Pt id was already in the map.

        //           lvtk_vids[i] = lmap_itr->second;
        //         }
        //         else
        //         {
        //           // pt id was not in the map;
        //           // enter the point data in vtk and
        //           // enter the pt id in the map..

        //           ltri_pts[i] += lmove;

        //           cout << "pt_id: " << ltri_pt_ids[i].pod() << " vtk_pt_id: " << lpt_ct << " coords: " << ltri_pts[i] << endl;
          
        //           lvtk_points->InsertNextPoint(reinterpret_cast<double*>(ltri_pts[i].row_dofs()));
        //           lpt_id_map[ltri_pt_ids[i].pod()] = lpt_ct;
        //           lpt_label_ids->InsertNextValue(ltri_pt_ids[i].pod());
        //           lvtk_vids[i] = lpt_ct++;
        //         }

        ltri_pts[i] += lmove;
        lvtk_points->InsertNextPoint(reinterpret_cast<double*>(ltri_pts[i].row_dofs()));
        lpt_label_ids->InsertNextValue(ltri_pt_ids[i].pod());
        lvtk_vids[i] = lpt_ct++;
      }

      // Populate the vtk cell array.

      lvtk_cells->InsertNextCell(kd_triangle::POINT_CT, lvtk_vids);
      lcell_label_ids->InsertNextValue(lt->pod());
    }
    lsv_itr.next();
  }  
  xkdl.subvolume_surfaces().id_space().release_iterator(lsv_itr);
  
  delete [] lvtk_vids;

  // Insert the points and cells in the grid
  
  xresult->SetPoints(lvtk_points);
  xresult->SetCells(VTK_TRIANGLE, lvtk_cells);

  // Insert the label ids in the grid.

  vtkPointData* lpt_data = xresult->GetPointData();
  lpt_data->AddArray(lpt_label_ids);

  vtkCellData* lcell_data = xresult->GetCellData();
  lcell_data->AddArray(lcell_label_ids);

  // $$SCRIBBLE: should we Delete the vtk ptrs?

  // Clean up.

  lcoords.release_access();
  
  // cout << "Leaving build_exploded_subvolume_triangle_grid" << endl;
  return;
};


void display_subvolume_vtk_grid(vtkRenderer* xrenderer, vtkUnstructuredGrid* xtriangle_grid, bool xpt_labels)
{
  // Clear renderer.

  //  xrenderer->RemoveAllViewProps();
  
  if((xtriangle_grid != 0) && (xtriangle_grid->GetNumberOfCells() != 0))
  {  
    // Create the vtk mapper for the triangle grid.

    vtkDataSetMapper* ltriangle_grid_mapper = vtkDataSetMapper::New();
    ltriangle_grid_mapper->SetInput(xtriangle_grid);

    // Create the triangle grid actor.

    vtkActor* ltriangle_grid_actor = vtkActor::New();
    ltriangle_grid_actor->SetMapper(ltriangle_grid_mapper);

    // Turn edge visibility off.

    ltriangle_grid_actor->GetProperty()->EdgeVisibilityOn();
    ltriangle_grid_actor->GetProperty()->SetOpacity(1.0);
    ltriangle_grid_actor->GetProperty()->SetColor(0.9, 0.9, 0.0); // Yellow

    // Add the actor to the renderer.

    xrenderer->AddActor(ltriangle_grid_actor);

    // Create the cell labels.

    if(xpt_labels && (xtriangle_grid != 0) && (xtriangle_grid->GetNumberOfCells() != 0))
    {
      create_cell_labels(xtriangle_grid, xrenderer);
      create_pt_labels(xtriangle_grid, xrenderer, 0);
    }

    // Create bounding box axes.

    vtkCubeAxesActor* laxes = vtkCubeAxesActor::New();

    double* lbounds = new double[6];
    xtriangle_grid->GetBounds(lbounds);
    laxes->SetBounds(lbounds);
    delete [] lbounds;

    laxes->SetCamera(xrenderer->GetActiveCamera());
    laxes->SetFlyModeToStaticTriad();
    xrenderer->AddViewProp(laxes);
    xrenderer->ResetCamera();
  }
};

void display_subvolume_lattice(vtkRenderer* xrenderer, kd_lattice& xkdl, bool xpt_labels)
{
  vtkUnstructuredGrid* lsv_grid = vtkUnstructuredGrid::New();
  build_subvolume_triangle_grid(xkdl, lsv_grid);

  display_subvolume_vtk_grid(xrenderer, lsv_grid, xpt_labels);
};

void display_exploded_subvolume_lattice(vtkRenderer* xrenderer, kd_lattice& xkdl, bool xpt_labels)
{
  vtkUnstructuredGrid* lsv_grid = vtkUnstructuredGrid::New();
  build_exploded_subvolume_triangle_grid(xkdl, lsv_grid);

  display_subvolume_vtk_grid(xrenderer, lsv_grid, xpt_labels);
};






#endif // USE_VTK

} // end unnamed namespace


// ===========================================================
// KD_DISPLAY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::kd_display::
kd_display()
{
  // Preconditions:
    
  // Body:

#ifdef USE_VTK

  _renderer = 0;

#endif

  display_point_labels = false;
  display_zone_labels = false;
  
  
  // Postconditions:


  // Exit:

  return; 
}

geometry::kd_display::
~kd_display()
{  
  // Preconditions:
    
  // Body:
  
#ifdef USE_VTK

  if(_renderer != 0)
  {
    _renderer->Delete();
  }

#endif

  // Postconditions:

  // Exit:

  return; 
}

void
geometry::kd_display::
display(kd_lattice& xkdl, bool xexploded)
{
  // Preconditions:

  // Body:

#ifdef USE_VTK

  if(_renderer == 0)
  {
    _renderer = vtkRenderer::New();
    _renderer->SetBackground(0.3, 0.3, 0.3);
    

    if(xexploded)
    {
      display_exploded_lattice(_renderer, xkdl, _origin, _scale, display_point_labels);
    }
    else
    {
      display_lattice(_renderer, xkdl, _origin, _scale, display_point_labels);
    }

    // Create the render window.

    _window = vtkRenderWindow::New();
    _window->AddRenderer( _renderer );
    _window->SetSize( 1000, 1152 );

    // Create the interactor.

    _interactor = vtkRenderWindowInteractor::New();
    _interactor->SetRenderWindow(_window);
    _interactor->SetInteractorStyle(vtkInteractorStyleTrackballCamera::New());

    _interactor->Initialize();
    _interactor->Start();
  }
  else
  {
    
    _renderer->RemoveAllViewProps();

    if(xexploded)
    {
      display_exploded_lattice(_renderer, xkdl, _origin, _scale, display_point_labels);
    }
    else
    {
      display_lattice(_renderer, xkdl, _origin, _scale, display_point_labels);
    }
  
    _renderer->GetRenderWindow()->Render();
    _renderer->GetRenderWindow()->GetInteractor()->ReInitialize();
    _renderer->GetRenderWindow()->GetInteractor()->Start();
  }
  

#endif // USE_VTK

  // Postconditions:

  // Exit:

  return;
} 

void
geometry::kd_display::
display_subvolumes(kd_lattice& xkdl, bool xexploded)
{
  // Preconditions:

  // Body:

#ifdef USE_VTK

  if(_renderer == 0)
  {
    _renderer = vtkRenderer::New();

    if(xexploded)
    {
      display_exploded_subvolume_lattice(_renderer, xkdl, display_point_labels);
    }
    else
    {
      display_subvolume_lattice(_renderer, xkdl, display_point_labels);
    }

    // Create the render window.

    _window = vtkRenderWindow::New();
    _window->AddRenderer( _renderer );
    _window->SetSize( 1000, 1152 );

    // Create the interactor.

    _interactor = vtkRenderWindowInteractor::New();
    _interactor->SetRenderWindow(_window);
    _interactor->SetInteractorStyle(vtkInteractorStyleTrackballCamera::New());

    _interactor->Initialize();
  }
  else
  {
    _renderer->RemoveAllViewProps();

    if(xexploded)
    {
      display_exploded_subvolume_lattice(_renderer, xkdl, display_point_labels);
    }
    else
    {
      display_subvolume_lattice(_renderer, xkdl, display_point_labels);
    }
  
    _window->Render();
    _interactor->Start();
  }
  

#endif // USE_VTK

  // Postconditions:

  // Exit:

  return;
} 

// PROTECTED MEMBER FUNCTIONS

// PRIVATE MEMBER FUNCTIONS


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================
 
