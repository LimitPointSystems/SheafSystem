
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

package tools.viewer.render;

import bindings.java.*;
import tools.viewer.common.*;
import java.awt.*;
import java.util.*;
import vtk.*;

/**
 *
 * Implementation of <code>FieldActor</code> for a 2 dimensional graphic
 * representation..
 *
 */
public class G2DFieldActor extends FieldActor
{
  // SHEAF FACET

  /**
   * The pseudo color property section
   */
  protected sec_vd property = null;

  // FIELD REP FACET

  /**
   * The <code>vtkXYPlotActor</code>
   */
  protected vtkXYPlotActor xyPlotActor = null;

  /**
   * The xy plot <code>vtkProperty2D</code>
   */
  protected vtkProperty2D xyPlotProperty = null;

  /**
   * The title <code>vtkTextProperty</code>
   */
  protected vtkTextProperty titleProperty = null;

  /**
   * The axis title <code>vtkTextProperty</code>
   */
  protected vtkTextProperty axisTitleProperty = null;

  /**
   * The axis label <code>vtkTextProperty</code>
   */
  protected vtkTextProperty axisLabelProperty = null;

  // OTHER VTK FACET

  /**
   * The PolyData Builder.
   */
  protected vtk_poly_data_builder builder = null;

  /**
   * Constructor
   *
   */
  public G2DFieldActor(sec_vd xcoordinates,
                       sec_vd xproperty)
  {
    super(xcoordinates);

    property = xproperty;

    // Initialize the data set and builder.

    try
    {
      namespace_poset ns = coordinates.name_space();
      builder = new vtk_poly_data_builder(ns);
      dataSet = new vtkPolyData();
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }

    // FIELD REP FACET

    fieldRep = new vtkPropAssembly();

    createPolyData();
    createPolyDataActor();
  }

  // FIELD ACTOR FACET

  /**
   * Add this actor to xrenderer.
   */
  public void addTo(vtkRenderer xrenderer)
  {
    xrenderer.AddViewProp(fieldRep);
  }

  /**
   * Remove this actor from xrenderer.
   */
  public void removeFrom(vtkRenderer xrenderer)
  {
    xrenderer.RemoveViewProp(fieldRep);

    detachStates();
  }

  /**
   * The list of psuedo color properties
   */
  public sec_vd[] getProperties()
  {
    sec_vd[] result = new sec_vd[1];
    result[0] = property;

    return result;
  }

  // FIELD REP FACET

  /**
   * Create the VTK poly data set.
   */
  protected void createPolyData()
  {
    try
    {
      vtkPolyData ugrid = (vtkPolyData) dataSet;

      long ptr = NativeVtk.getCppPointer(ugrid);
      SWIGTYPE_p_vtkPolyData swigPtr = new SWIGTYPE_p_vtkPolyData(ptr, true);

      sec_vd[] properties = getProperties();
      int idx = properties.length - 1;

      if(idx>=0)
        builder.build_pa(coordinates, properties[idx], swigPtr);
      else
        builder.build_pa(coordinates, swigPtr);
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }

  /**
   * Create the VTK actor for the poly data actor
   */
  protected void createPolyDataActor()
  {
    vtkPolyData mapperInput = null;

    vtkPolyData grid = (vtkPolyData) dataSet;

    // Check for vector data.

    mapperInput = grid;

    xyPlotActor = new vtkXYPlotActor();
    xyPlotActor.SetHeight(1.0);
    xyPlotActor.SetWidth(1.0);
    xyPlotActor.SetPosition(0.0, 0.0);
    xyPlotActor.AddDataSetInput(grid);

    xyPlotProperty = xyPlotActor.GetProperty();
    titleProperty = xyPlotActor.GetTitleTextProperty();
    axisTitleProperty = xyPlotActor.GetAxisTitleTextProperty();
    axisLabelProperty = xyPlotActor.GetAxisLabelTextProperty();

    try
    {
      // Set the plot title.

      xyPlotActor.SetTitle(toString());

      // Set the x and y labels

      xyPlotActor.SetXTitle(coordinates.name());

      String ylabel = "";
      sec_vd[] properties = getProperties();
      for(int i=0; i<properties.length; i++)
      {
        ylabel += properties[i].name();
        if(i+1 < properties.length)
          ylabel += "\n";
      }

      // $$HACK: There is no way to rotate the y-axis in vtk 4.4.  We need
      //         to upgrade to vtk 5.0 to fix this hack.

      xyPlotActor.SetYTitle(ylabel);
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }

    // Add actor to the field rep.

    ((vtkPropAssembly) fieldRep).AddPart(xyPlotActor);
  }

  // VTK FACET

  /**
   * Modify the VTK components.
   */
  public void modify()
  {
    createPolyData();
    xyPlotActor.Modified();
  }
}
