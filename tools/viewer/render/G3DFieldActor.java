
/**
 * Classname: G3DFieldActor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: G3DFieldActor.java,v $ $Revision: 1.14 $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.render;

import tools.viewer.common.*;
import tools.viewer.user.*;
import bindings.java.*;

import java.awt.*;
import java.util.*;
import vtk.*;


// Obsolete. But leave it here as example.
// class TopIdFilter extends vtkProgrammableFilter
// {
//   vtkPoints outputPoints;
//   vtkIdTypeArray topIds;
 
//   public TopIdFilter()
//   {
//     SetExecuteMethod(this, "compute");
//   }
 
//   public void compute() 
//   {
//     vtkPolyData polyDataInput = GetPolyDataInput();
//     vtkPolyData polyDataOutput = GetPolyDataOutput();
//     polyDataOutput.CopyStructure(polyDataInput);
//     polyDataOutput.GetPointData().PassData(polyDataInput.GetPointData());
//     polyDataOutput.GetCellData().PassData(polyDataInput.GetCellData());

//     System.out.println("input point data:" + polyDataInput.GetPointData());

//     polyDataOutput.GetPointData().GetArray(0).SetName("TopIdFilter_ids");
    
//     System.out.println("output point data: " + polyDataOutput.GetPointData());

//     vtkIdTypeArray lfield_data = (vtkIdTypeArray) polyDataOutput.GetPointData().GetArray(0);
//     System.out.println("output id data: " + lfield_data);
//     vtkIdTypeArray ltop_ids = (vtkIdTypeArray) polyDataOutput.GetPointData().GetArray(1);
//     System.out.println("output top id data: " + ltop_ids);

//     for (int i = 0; i < lfield_data.GetNumberOfTuples(); i++)
//     {
//       lfield_data.SetValue(i, ltop_ids.GetValue(i));
//     }
    
//   }
// }

/**
 *
 * Implementation of <code>FieldActor</code> for a 3 dimensional graphic
 * representation.
 *
 * The pipeline:
 *
 *
 * <pre>
 * [dataSet] ==> [transformFilter] ==> [?scalar filter?] ==> [gridActor]
 *                                 |
 *                                 ==> [edgeActor]
 *                                 |
 *                                 ==> [pointLabelsVisPts] ==> [pointLabelsActor]
 *                                 |
 *                                 ==> [cellLabelsVisPtr] ==> [cellLabelsActor]
 * </pre>
 *
 */
public abstract class G3DFieldActor extends FieldActor
{
  // CONSTANT FACET

  protected boolean usingLODActors = true;

  // LOOKUP TABLE FACET

  /**
   * The <code>LookupTable</code> for the grid and
   * for the color bar.
   */
  protected LookupTable lookupTable = null;

  // COORDINATE FIBER REP FACET

  /**
   * The <code>vtkAxes</code> for the coordinate field.
   */
  protected vtkAxes axes = null;

  /**
   * The <code>vtkAxes</code> for the coordinate field.
   */
  protected vtkTubeFilter axesTubeFilter = null;

  /**
   * The axis actor.
   */
  protected vtkActor axesActor = null;

  /**
   * The <code>vtkFollower</code> for the x-axis label.
   */
  protected vtkFollower xTextActor = null;

  /**
   * The <code>vtkFollower</code> for the y-axis label.
   */
  protected vtkFollower yTextActor = null;

  /**
   * The <code>vtkFollower</code> for the z-axis label.
   */
  protected vtkFollower zTextActor = null;

  // PROPERTY FIBER REP FACET

  /**
   * The color <code>vtkScalarBarActor</code>
   */
  protected vtkScalarBarActor colorBar;

  // FIELD REP FACET

  /**
   * The grid <code>vtkActor</code>
   */
  public vtkActor gridActor = null;

  /**
   * The grid <code>vtkDataSetMapper</code>
   */
  protected vtkDataSetMapper gridMapper = null;

  /**
   * The grid <code>vtkProperty</code>
   */
  protected vtkProperty gridProperty = null;

  /**
   * The edge <code>vtkActor</code>
   */
  protected vtkActor edgeActor = null;

  /**
   * The edge <code>vtkDataSetMapper</code>
   */
  protected vtkDataSetMapper edgeMapper = null;

  /**
   * The edge <code>vtkProperty</code>
   */
  protected vtkProperty edgeProperty = null;

  /**
   * The point label <code>vtkActor2D</code>
   */
  protected vtkActor2D pointLabelsActor = null;

  /**
   * The cell label <code>vtkActor2D</code>
   */
  protected vtkActor2D cellLabelsActor  = null;

  //
  // Other VTK data members
  //

  /**
   * The filtered input to the grid actor mapper.
   */
  protected vtkDataSet mapperInput = null;

  /**
   * The scalar data set (grid data or the normalized data.
   */
  protected vtkDataSet scalarDataSet = null;

  /**
   * The <code>G3DFieldActor</code>'s copy of the grid builder
   */
  protected vtk_abstract_grid_builder gridBuilder;

  /**
   * The filter used to transform the grid data in the pipeline.
   */
  protected vtkTransformFilter transformFilter = null;

  protected vtkSelectVisiblePoints pointLabelsVisPts = new vtkSelectVisiblePoints();
  protected vtkSelectVisiblePoints cellLabelsVisPts  = new vtkSelectVisiblePoints();

  // CONSTRUTORS

  /**
   * Default constructor
   */
  public G3DFieldActor()
  {}

  /**
   * Constructor
   *
   * @param xcoordinates The coordinates section
   * @param xproperties  The property sections
   */
  public G3DFieldActor(sec_vd xcoordinates, LookupTable xlookupTable)
  {
    super(xcoordinates);

    lookupTable = xlookupTable;
  }

  /**
   * Initialize this <code>G3DFieldActor</code>
   */
  protected void init()
  {
    // Initialize the grid builder and data set.

    try
    {
      gridBuilder = (vtk_abstract_grid_builder)Viewer.APPLICATION.getGridBuilder().klone();
      gridBuilder.set_name_space(coordinates.name_space());
      dataSet = new vtkUnstructuredGrid();
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }

    // FIELD REP FACET

    fieldRep = new vtkPropAssembly();

    createUnstructuredGrid();
    createTransformFilter();
    createUnstructuredGridActor();
    createEdgeActor();
    createPointLabels();
    createCellLabels();

    // COORDIANTE FIBER REP FACET

    coordinateFiberRep = new vtkPropAssembly();

    createCoordinateFiberRep();
    
    // PROPERTIES FIBER REP FACET

    propertyFiberRep = new vtkPropAssembly();

    createPropertyFiberRep();
  }

  // FIELD ACTOR FACET

  /**
   * Add this actor to xrenderer.
   */
  public void addTo(vtkRenderer xrenderer)
  {
    xrenderer.AddViewProp(fieldRep);
    xrenderer.AddViewProp(coordinateFiberRep);
    xrenderer.AddViewProp(propertyFiberRep);
  }

  /**
   * Remove this actor from xrenderer.
   */
  public void removeFrom(vtkRenderer xrenderer)
  {
    // $$HACK: Must call SetMapper(null) on all actors so that
    // the mapper's graphic resources are not released by the call to
    // RemoveActor.  Must call ReleaseGraphicResource(null) on all the
    // mappers so that the mapper's destructor does not try to release
    // the graphic resources.  A bug in VTK causes a segfault otherwise.
    // This may couse a memory leak but that's better than a segfault.

    // $$TODO: Attempt to undo this when we upgrade versions of Mesa
    // and/or operating systems.

    axesActor.GetMapper().ReleaseGraphicsResources(null);
    axesActor.SetMapper(null);

    xTextActor.GetMapper().ReleaseGraphicsResources(null);
    xTextActor.SetMapper(null);

    yTextActor.GetMapper().ReleaseGraphicsResources(null);
    yTextActor.SetMapper(null);
   
    zTextActor.GetMapper().ReleaseGraphicsResources(null);
    zTextActor.SetMapper(null);

    gridActor.GetMapper().ReleaseGraphicsResources(null);
    gridActor.SetMapper(null);

    edgeActor.GetMapper().ReleaseGraphicsResources(null);
    edgeActor.SetMapper(null);

    pointLabelsActor.GetMapper().ReleaseGraphicsResources(null);
    pointLabelsActor.SetMapper(null);

    cellLabelsActor.GetMapper().ReleaseGraphicsResources(null);
    cellLabelsActor.SetMapper(null);
   
    xrenderer.RemoveViewProp(fieldRep);
    xrenderer.RemoveViewProp(propertyFiberRep);
    xrenderer.RemoveViewProp(coordinateFiberRep);

    detachStates();
  }

  // COORDINATES FIBER REP FACET

  /**
   * Create VTK Axes Actor
   */
  protected void createCoordinateFiberRep()
  {
    // Create new axes.
    axes = new vtkAxes();
    
    // Feed the axes to a tube filter to increase visibility
  //  axesTubeFilter = new vtkTubeFilter();
  //  axesTubeFilter.SetInput(axes.GetOutput());
  //  axesTubeFilter.SetNumberOfSides(8);
	
    // Make the axes extend in the negative direction as well.
    axes.SymmetricOn();
    
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    //mapper.SetInput(axesTubeFilter.GetOutput());
    mapper.SetInput(axes.GetOutput());
    axesActor = new vtkActor();
    axesActor.SetMapper(mapper);
    
    // Create the x axis label.

    vtkVectorText xtext = new vtkVectorText();
    xtext.SetText("x");
    vtkPolyDataMapper xTextMapper = new vtkPolyDataMapper();
    xTextMapper.SetInputConnection(xtext.GetOutputPort());
    
    xTextActor = new vtkFollower();
    xTextActor.SetMapper(xTextMapper);

    // Create the y axis label

    vtkVectorText ytext = new vtkVectorText();
    ytext.SetText("y");
    vtkPolyDataMapper yTextMapper = new vtkPolyDataMapper();
    yTextMapper.SetInputConnection(ytext.GetOutputPort());
    
    yTextActor = new vtkFollower();
    yTextActor.SetMapper(yTextMapper);

    // Create the z axis label

    vtkVectorText ztext = new vtkVectorText();
    ztext.SetText("z");
    vtkPolyDataMapper zTextMapper = new vtkPolyDataMapper();
    zTextMapper.SetInputConnection(ztext.GetOutputPort());
    
    zTextActor = new vtkFollower();
    zTextActor.SetMapper(zTextMapper);

    // Add the text actors to the stage

    ((vtkPropAssembly) coordinateFiberRep).AddPart(xTextActor);
    ((vtkPropAssembly) coordinateFiberRep).AddPart(yTextActor);
    ((vtkPropAssembly) coordinateFiberRep).AddPart(zTextActor);
    ((vtkPropAssembly) coordinateFiberRep).AddPart(axesActor);
  }
  
  /**
   * Calculate the bound for the an axis.
   */
  protected double getAxisBound(double[] xscale)
  {
    double[] bounds;
    bounds = new double[6];

    // Get the actor's bounds

    dataSet.GetBounds(bounds);
		
    double[] axesBounds;
    axesBounds = new double[3];

    // Subtract the min values from the max values values.  According to
    // the VTK documentation GetBounds() returns
    // (xMin, xMax, yMin, yMax, zMin, zMax).  Multiply by the
    // scale in each direction to make sure the axis is large enough.

    axesBounds[0] = (bounds[1] - bounds[0]) * xscale[0];
    axesBounds[1] = (bounds[3] - bounds[2]) * xscale[1];
    axesBounds[2] = (bounds[5] - bounds[4]) * xscale[2];

    // Sort the array in ascending order. Element at length-1 will have
    // the greatest value.

    Arrays.sort(axesBounds);

    double result = axesBounds[axesBounds.length - 1];
    return result;
  }

  // PROPERTIES FIBER REP FACET

  /**
   * Create the property rule for the render window.
   */
  protected void createPropertyFiberRep()
  {
    colorBar = new vtkScalarBarActor();

    // $$HACK: How should the title be found?

    //colorBar.SetTitle(xtitle);

    // Set color bar font & color

    colorBar.GetTitleTextProperty().BoldOff();
    colorBar.GetTitleTextProperty().ShadowOff();
    colorBar.GetLabelTextProperty().BoldOff();
    colorBar.GetLabelTextProperty().ShadowOff();
    colorBar.GetProperty().SetColor(0, 0, 0);
    colorBar.SetLabelFormat(lookupTable.getLabelFormat());

    // Set color bar location, size, etc.

    colorBar.GetPositionCoordinate().SetCoordinateSystemToNormalizedViewport();
    colorBar.GetPositionCoordinate().SetValue(0.1, 0.01);
    colorBar.SetOrientationToHorizontal();
    colorBar.SetWidth(0.8);
    colorBar.SetHeight(0.1);

    // Set the lookup table

    colorBar.SetLookupTable(lookupTable);

    ((vtkPropAssembly) propertyFiberRep).AddPart(colorBar);
  }

  // FIELD REP FACET

  /**
   * The grid actor
   */
  public vtkActor getGridActor()
  {
    return gridActor;
  }

  /**
   * The bounds of the actor.
   */
  public void getBounds(double[] xbounds)
  {
    gridActor.GetBounds(xbounds);  
  }
  
  /**
   * Create the VTK unstructured grid data set.
   */
  protected void createUnstructuredGrid()
  {
    try
    {
      vtkUnstructuredGrid ugrid = (vtkUnstructuredGrid) dataSet;
      //vtkUnstructuredGrid ugrid = new vtkUnstructuredGrid();

      // Here we invoke a native method to ask vtk to provide
      // the address (pointer) of the vtUnstructuredGrid instance.
      // We then create a SWIGTYPE_p_vtkUnstructuredGrid instance
      // which the lps wrapper for vtk_unstructured_grid_builder
      // accepts. Thus, following invocation of
      // vtk_unstructured_grid_builder.build_pa, our
      // vtkUnstructuredGrid (ugrid) will be populated with the
      // desired data members.

      long ptr = NativeVtk.getCppPointer(ugrid);
      SWIGTYPE_p_vtkUnstructuredGrid swigPtr
      = new SWIGTYPE_p_vtkUnstructuredGrid(ptr, true);

      sec_vd[] properties = getProperties();
      if(properties.length == 0)
      {
        gridBuilder.build_pa(coordinates, swigPtr);
      }
      else if(properties.length == 1)
      {
        gridBuilder.build_pa(coordinates, properties[0], swigPtr);
      }
      else if(properties.length == 2)
      {
        gridBuilder.build_pa(coordinates, properties[0],
                             properties[1], swigPtr);
      }
      else
      {
        System.err.println("WARNING: More than two properties where found." +
                           "         Only the first two properties will be " +
                           "         visualized.");
        gridBuilder.build_pa(coordinates, properties[0],
                             properties[1], swigPtr);
      }
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }

  /**
   * Create the filter used to transform the grid data in the pipeline.
   */
  protected void createTransformFilter()
  {
    vtkTransform transform = new vtkTransform();
    transformFilter = new vtkTransformFilter();
    transformFilter.SetInput(dataSet);
    transformFilter.SetTransform(transform);
  }

  /**
   * Create the VTK actor for the unstructured grid.
   */
  protected void createUnstructuredGridActor()
  {
    vtkUnstructuredGrid grid = (vtkUnstructuredGrid) dataSet;

    // Construct the grid mapper.

    gridMapper = new vtkDataSetMapper();

    // Check for vector data.

    if(grid.GetPointData().GetScalars() == null &&
       grid.GetPointData().GetVectors() == null &&
       grid.GetPointData().GetTensors() != null)
    {
      // Filter the tensor data to create scalars.

      vtkExtractTensorComponents tensorFilter =
	  new vtkExtractTensorComponents();
      tensorFilter.ExtractScalarsOn();
      tensorFilter.SetScalarModeToDeterminant();
      tensorFilter.SetInput(transformFilter.GetOutput());

      // Update to force the filter to execute.

      tensorFilter.Update();

      mapperInput = tensorFilter.GetOutput();

      scalarDataSet = mapperInput;
    }
    else if(grid.GetPointData().GetScalars() == null &&
	    grid.GetPointData().GetVectors() != null)
    {
      // Filter vector data to create scalars from the vector magnitudes
      // (not normalized).

      vtkVectorNorm vecNorm = new vtkVectorNorm();
      vecNorm.SetInput(transformFilter.GetOutput());

      // Update to force the filter to execute.

      vecNorm.Update();

      mapperInput = vecNorm.GetOutput();

      scalarDataSet = mapperInput;
    }
    else  // Must be scalar data
    {
      mapperInput = transformFilter.GetOutput();

      scalarDataSet = dataSet;
    }

    // Initialize the grid mapper's input.

    gridMapper.SetInput(mapperInput);

    // Set the lookup table

    gridMapper.SetLookupTable(lookupTable);

    // Set the scalar range

    initScalarRange();

    // Create the grid actor.

    gridActor = (usingLODActors) ? (new vtkLODActor()) : (new vtkActor());
    gridActor.SetMapper(gridMapper);

    // Get the property for use by the descriptor

    gridProperty = gridActor.GetProperty();

    // Add actor to the field rep.

    ((vtkPropAssembly) fieldRep).AddPart(gridActor);
  }

  /**
   * Initialize the scalar range.
   */
  public void initScalarRange()
  {
    double[] range = lookupTable.getScalarRange();
    if(range == null)
      gridMapper.SetScalarRange(scalarDataSet.GetScalarRange());
    else
      gridMapper.SetScalarRange(range);
  }

  /**
   * Create the Edge Actor.
   */
  protected void createEdgeActor()
  {
    // $$ISSUE:  The edge actor is a work around since the VTK method
    //           props.SetEdgeVisibility() does not seem to work.

    edgeMapper = new vtkDataSetMapper();
    edgeMapper.SetInput(transformFilter.GetOutput());
    edgeMapper.SetScalarVisibility(0);
    edgeActor = new vtkActor();
    edgeActor.SetMapper(edgeMapper);
    edgeProperty = edgeActor.GetProperty();
    edgeProperty.SetRepresentationToWireframe();
    edgeProperty.SetColor(0.2, 0.2, 0.2);

    // Add actor to the field rep.

    ((vtkPropAssembly) fieldRep).AddPart(edgeActor);
  }

  /**
   * Create the point labels
   */
  protected void createPointLabels()
  {
    pointLabelsVisPts.SetInput(transformFilter.GetOutput());

    vtkLabeledDataMapper dataMapper = new vtkLabeledDataMapper();
    dataMapper.SetInput(pointLabelsVisPts.GetOutput());
    dataMapper.SetLabelFormat("%ld");
    dataMapper.GetLabelTextProperty().ShadowOff();
    
    vtkUnstructuredGrid grid = (vtkUnstructuredGrid) dataSet;

    if(grid.GetPointData().GetArrayName(0).equals("point_label_ids"))
    {
      //     System.out.println("Found point label ids.");
      dataMapper.SetLabelModeToLabelFieldData();
      dataMapper.SetFieldDataArray(0);
    }    
    else
    {
      System.out.println("Can't find point label ids.");
      dataMapper.SetLabelModeToLabelIds();
    }

    pointLabelsActor = new vtkActor2D();
    pointLabelsActor.SetMapper(dataMapper);
    pointLabelsActor.GetProperty().SetColor(1, 1, 1);

    // Add actor to the field rep.

    ((vtkPropAssembly) fieldRep).AddPart(pointLabelsActor);
  }

  /**
   * Create the cell labels
   */
  protected void createCellLabels()
  {
    vtkCellCenters cc = new vtkCellCenters();
    cc.SetInput(transformFilter.GetOutput());

    cellLabelsVisPts.SetInput(cc.GetOutput());

    vtkLabeledDataMapper dataMapper = new vtkLabeledDataMapper();
    dataMapper.SetInput(cellLabelsVisPts.GetOutput());
    dataMapper.SetLabelFormat("%ld");
    dataMapper.GetLabelTextProperty().ShadowOff();

    vtkUnstructuredGrid grid = (vtkUnstructuredGrid) dataSet;

    if(grid.GetCellData().GetArrayName(0).equals("cell_label_ids"))
    {
      //      System.out.println("Found cell label ids.");
      dataMapper.SetLabelModeToLabelFieldData();
      dataMapper.SetFieldDataArray(0);
    }    
    else
    {
      System.out.println("Can't find cell label ids.");
      dataMapper.SetLabelModeToLabelIds();
    }

    cellLabelsActor = new vtkActor2D();
    cellLabelsActor.SetMapper(dataMapper);
    cellLabelsActor.GetProperty().SetColor(0, 0, 0);

    // Add actor to the field rep.

    ((vtkPropAssembly) fieldRep).AddPart(cellLabelsActor);
  }

  // VTK FACET

  /**
   * Modify the VTK components.
   */
  public void modify()
  {
    createUnstructuredGrid();
    gridActor.Modified();
    edgeActor.Modified();
    pointLabelsActor.Modified();
    cellLabelsActor.Modified();
  }

  /**
   * Set the renderer for this <code>FieldActor</code>
   */
  public void setRenderer(vtkRenderer xrenderer)
  {
    pointLabelsVisPts.SetRenderer(xrenderer);
    cellLabelsVisPts.SetRenderer(xrenderer);
  }
  /**
   * Get the renderer for this <code>FieldActor</code>
   */
  public vtkRenderer getRenderer()
  {
    return pointLabelsVisPts.GetRenderer();
  }
}
