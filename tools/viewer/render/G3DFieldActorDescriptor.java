
/**
 * Classname: G3DFieldActorDescriptor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: G3DFieldActorDescriptor.java,v $ $Revision: 1.10 $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.render;

import tools.common.util.*;
import tools.viewer.common.*;
import tools.viewer.animation.*;
import tools.viewer.user.*;
import bindings.java.*;

import java.awt.*;
import java.io.*;
import java.util.*;

import vtk.*;

/**
 *
 * Struct which describes a <code>G3DFieldActor</code>
 *
 */
public abstract class G3DFieldActorDescriptor extends FieldActorDescriptor
{
  // G3D_FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The point size
   */
  public double pointSize = 4.0;

  /**
   * The line width
   */
  public double lineWidth = 2.0;

  /**
   * The display style
   */
  public int displayStyle = ViewerConstants.SURFACE_STYLE;

  /**
   * The interpolation
   */
  public int interpolation = 1;

  /**
   * The opacity
   */
  public double opacity = 1.0;

  /**
   * The edge visibility
   */
  public boolean edgeVisibility = true;

  /**
   * The scalar visibility
   */
  public boolean scalarVisibility = true;

  /**
   * The solid color
   */
  public Color solidColor = Color.gray;

  /**
   * The <code>LookupTableDescriptor</code>
   */
  public LookupTableDescriptor lookupTable = new RangeLookupTableDescriptor();

  /**
   * The point labels
   */
  public int pointLabels = ViewerConstants.NO_IDS;

  /**
   * The cell labels
   */
  public int cellLabels = ViewerConstants.NO_IDS;

  /**
   * The position
   */
  public double[] position = {0.0, 0.0, 0.0};

  /**
   * The origin
   */
  public double[] origin = {0.0, 0.0, 0.0};

  /**
   * The orientation
   */
  public double[] orientation = {0.0, 0.0, 0.0};

  /**
   * The scale
   */
  public double[] scale = {1.0, 1.0, 1.0};

  /**
   * Default constructor
   */
  public G3DFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Copy the values of xactor into this <code>G3DFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // G3D FIELD ACTOR DESCRIPTOR FACET

    G3DFieldActorDescriptor actor = (G3DFieldActorDescriptor) xactor;
 
    pointSize = actor.pointSize;
    lineWidth = actor.lineWidth;
    displayStyle = actor.displayStyle;
    interpolation = actor.interpolation;
    opacity = actor.opacity;
    edgeVisibility = actor.edgeVisibility;
    scalarVisibility = actor.scalarVisibility;
    solidColor = new Color(actor.solidColor.getRGB());
    lookupTable.copy(actor.lookupTable);
    pointLabels = actor.pointLabels;
    cellLabels = actor.cellLabels;
    position[0] = actor.position[0];
    position[1] = actor.position[1];
    position[2] = actor.position[2];
    origin[0] = actor.origin[0];
    origin[1] = actor.origin[1];
    origin[2] = actor.origin[2];
    orientation[0] = actor.orientation[0];
    orientation[1] = actor.orientation[1];
    orientation[2] = actor.orientation[2];
    scale[0] = actor.scale[0];
    scale[1] = actor.scale[1];
    scale[2] = actor.scale[2];
  }

  /**
   * Update xactor to this <code>G3DFieldDescriptor</code>
   */
  public void update(FieldActor xactor, FieldActorDescriptor xdescriptor)
  {
    G3DFieldActor actor = (G3DFieldActor) xactor;
    G3DFieldActorDescriptor descriptor = (G3DFieldActorDescriptor) xdescriptor;

    int b;

    // FIELD ACTOR FACET

    if(descriptor == null || visibility != descriptor.visibility)
    {
      b = visibility ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.fieldRep.SetVisibility(b);
      actor.coordinateFiberRep.SetVisibility(b);
      actor.propertyFiberRep.SetVisibility(b);
    }

    if(descriptor == null || selected != descriptor.selected)
    {
      b = selected ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.coordinateFiberRep.SetVisibility(b);
      actor.propertyFiberRep.SetVisibility(b);
    }

    // G3D FIELD ACTOR FACET

    if(descriptor == null || pointSize != descriptor.pointSize)
      actor.gridProperty.SetPointSize(pointSize);

    if(descriptor == null || lineWidth != descriptor.lineWidth)
    {
      actor.gridProperty.SetLineWidth(lineWidth);
      actor.edgeProperty.SetLineWidth(lineWidth);
    }

    if(descriptor == null || displayStyle != descriptor.displayStyle)
      actor.gridProperty.SetRepresentation(displayStyle);

    if(descriptor == null || interpolation != descriptor.interpolation)
      actor.gridProperty.SetInterpolation(interpolation);

    if(descriptor == null || opacity != descriptor.opacity)
    {
      actor.gridProperty.SetOpacity(opacity);
      actor.edgeProperty.SetOpacity(opacity);
    }

    vtkPropAssembly fieldRep = ((vtkPropAssembly) actor.fieldRep);

    if(descriptor == null || edgeVisibility != descriptor.edgeVisibility)
    {
      b = edgeVisibility ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.edgeActor.SetVisibility(b);
    }

    if(descriptor == null || scalarVisibility != descriptor.scalarVisibility)
    {
      b = scalarVisibility ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.gridMapper.SetScalarVisibility(b);
      actor.colorBar.SetVisibility(b);
    }

    if(!scalarVisibility &&
        (descriptor == null || !solidColor.equals(descriptor.solidColor)))
    {
      float[] rgba = new float[4];
      solidColor.getRGBComponents(rgba);
      actor.gridProperty.SetColor(rgba[0], rgba[1], rgba[2]);
    }
    else if(scalarVisibility)
    {
      if(descriptor == null)
        lookupTable.update(actor.lookupTable, null);
      else
        lookupTable.update(actor.lookupTable, descriptor.lookupTable);
    }

    if(descriptor == null || pointLabels != descriptor.pointLabels)
    {
      switch(pointLabels)
      {
        case ViewerConstants.NO_IDS:
        {
	  actor.pointLabelsActor.SetVisibility(ViewerConstants.FALSE);
	  break;
	}
        case ViewerConstants.TOP_IDS:
        {
	  actor.gridBuilder.put_use_point_top_ids(true);
	  actor.modify();
	  actor.pointLabelsActor.SetVisibility(ViewerConstants.TRUE);
	  break;
	}
        case ViewerConstants.DISC_EVAL_IDS:
        {
	  actor.gridBuilder.put_use_point_top_ids(false);
	  actor.modify();
	  actor.pointLabelsActor.SetVisibility(ViewerConstants.TRUE);
	  break;
	}
        default:
        {
          System.err.println("Invalid pointLabel value: " + pointLabels);
          actor.pointLabelsActor.SetVisibility(ViewerConstants.FALSE);
	  break;
	}
      }
    }

    if(descriptor == null || cellLabels != descriptor.cellLabels)
    {
      switch(cellLabels)
      {
        case ViewerConstants.NO_IDS:
        {
	  actor.cellLabelsActor.SetVisibility(ViewerConstants.FALSE);
	  break;
	}
        case ViewerConstants.TOP_IDS:
        {
	  actor.gridBuilder.put_use_cell_top_ids(true);
	  actor.modify();
	  actor.cellLabelsActor.SetVisibility(ViewerConstants.TRUE);
	  break;
	}
        case ViewerConstants.DISC_EVAL_IDS:
        {
	  actor.gridBuilder.put_use_cell_top_ids(false);
	  actor.modify();
	  actor.cellLabelsActor.SetVisibility(ViewerConstants.TRUE);
	  break;
	}
        default:
        {
          System.err.println("Invalid cellLabel value: " + cellLabels);
          actor.cellLabelsActor.SetVisibility(ViewerConstants.FALSE);
	  break;
	}
      }
    }

    // Process transform values.

    if(descriptor == null ||
       !compare(position, descriptor.position) ||
       !compare(origin, descriptor.origin) ||
       !compare(orientation, descriptor.orientation) ||
       !compare(scale, descriptor.scale))
    {
      // Transform the grid data.  Got this sequence from vtkProp3D.

      vtkTransform transform = (vtkTransform) actor.transformFilter.GetTransform();

      transform.Push();
      transform.Identity();
      transform.PostMultiply();

      // Shift back to actor's origin .

      double[] center = actor.dataSet.GetCenter();
      double originX = center[0] + origin[0];
      double originY = center[1] + origin[1];
      double originZ = center[2] + origin[2];

      transform.Translate(-originX, -originY, -originZ);

      // Scale

      transform.Scale(scale);

      // Rotate.

      transform.RotateY(orientation[1]);
      transform.RotateX(orientation[0]);
      transform.RotateZ(orientation[2]);

      // move back from origin and translate

      transform.Translate(originX + position[0],
			  originY + position[1],
			  originZ + position[2]);

      transform.PreMultiply();

      // Adjust the axes and axis labels position.

      double axisBound = actor.getAxisBound(scale);

      actor.axes.SetOrigin(originX, originY, originZ);
      actor.xTextActor.SetPosition(originX + axisBound, originY, originZ);
      actor.yTextActor.SetPosition(originX, originY + axisBound, originZ);
      actor.zTextActor.SetPosition(originX, originY, originZ + axisBound);

      // Adjust the axes and axis labels scale.

      actor.axes.SetScaleFactor(axisBound);
   //   actor.axesTubeFilter.SetRadius(actor.axes.GetScaleFactor() / 265.0);
      double labelScale = axisBound / 20.0;
      actor.xTextActor.SetScale(labelScale, labelScale, labelScale);
      actor.yTextActor.SetScale(labelScale, labelScale, labelScale);
      actor.zTextActor.SetScale(labelScale, labelScale, labelScale);
    }
  }
  
  /**
   * Calculate and return a two dimensional array of increments used for
   * interpolation.  The first index is the variable, The second index is the
   * coordinate values; (x, y, z) or (latitude, longitude, distance).
   */
  public double[][] calcIncrements(FieldActorDescriptor xactor,
                                   boolean xshort, int xsteps)
  {
    double[][] result = new double[4][3];

    G3DFieldActorDescriptor actor = (G3DFieldActorDescriptor) xactor;

    // Index 0, the position

    LPSMath.calcLinearIncrement(result[0], actor.position, position, xsteps);

    // Index 1, the origin

    LPSMath.calcLinearIncrement(result[1], actor.origin, origin, xsteps);

    // Index 2, the orientation

    LPSMath.calcLinearIncrement(result[2], actor.orientation, orientation, xsteps);

    // Index 3, the scale

    LPSMath.calcLinearIncrement(result[3], actor.scale, scale, xsteps);

    return result;
  }

  /**
   * Interpolate the values of this <code>FieldActorDescriptor</code> given
   * the start point, increment, and step.
   */
  public void interpolate(FieldActorDescriptor xstart,
                          double[][] xincrement, int xstep)
  {
    G3DFieldActorDescriptor start = (G3DFieldActorDescriptor) xstart;

    // Index 0, the position

    LPSMath.incrementLinear(position, start.position, xincrement[0], xstep);

    // Index 1, the origin

    LPSMath.incrementLinear(origin, start.origin, xincrement[1], xstep);

    // Index 2, the orientation

    LPSMath.incrementLinear(orientation, start.orientation, xincrement[2], xstep);

    // Index 3, the scale

    LPSMath.incrementLinear(scale, start.scale, xincrement[3], xstep);
  }

  // DESCRIPTOR FACET

  /**
   * Set the time
   */
  public void setTime(double xtime)
  {
    super.setTime(xtime);

    lookupTable.setTime(xtime);
  }

  /**
   * Read from a stream constructor
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    pointSize = Script.readDouble(xinput);
    lineWidth = Script.readDouble(xinput);
    displayStyle = Script.readInt(xinput);
    interpolation = Script.readInt(xinput);
    opacity = Script.readDouble(xinput);
    edgeVisibility = Script.readBoolean(xinput);
    scalarVisibility = Script.readBoolean(xinput);
    solidColor = Script.readColor(xinput);
    String type = Script.readCell(xinput);
    Descriptor descriptor = null;
    try
    {
      descriptor = (Descriptor) Class.forName(type).newInstance();
    }
    catch(Exception e)
    {}
    if(descriptor == null || !(descriptor instanceof LookupTableDescriptor))
      throw new IOException("Invalid Lookup Table: " + type);
    lookupTable = (LookupTableDescriptor) descriptor;
    lookupTable.read(xinput);
    pointLabels = Script.readInt(xinput);
    cellLabels = Script.readInt(xinput);
    position[0] = Script.readDouble(xinput);
    position[1] = Script.readDouble(xinput);
    position[2] = Script.readDouble(xinput);
    origin[0] = Script.readDouble(xinput);
    origin[1] = Script.readDouble(xinput);
    origin[2] = Script.readDouble(xinput);
    orientation[0] = Script.readDouble(xinput);
    orientation[1] = Script.readDouble(xinput);
    orientation[2] = Script.readDouble(xinput);
    scale[0] = Script.readDouble(xinput);
    scale[1] = Script.readDouble(xinput);
    scale[2] = Script.readDouble(xinput);
  }

  /**
   * Write this <code>G3DFieldActorDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(pointSize, xout);
    Script.writeSeparator(xout);
    Script.write(lineWidth, xout);
    Script.writeSeparator(xout);
    Script.write(displayStyle, xout);
    Script.writeSeparator(xout);
    Script.write(interpolation, xout);
    Script.writeSeparator(xout);
    Script.write(opacity, xout);
    Script.writeSeparator(xout);
    Script.write(edgeVisibility, xout);
    Script.writeSeparator(xout);
    Script.write(scalarVisibility, xout);
    Script.writeSeparator(xout);
    Script.write(solidColor, xout);
    Script.writeSeparator(xout);
    Script.write(lookupTable.getClass().getName(), xout);
    Script.writeSeparator(xout);
    lookupTable.write(xout);
    Script.writeSeparator(xout);
    Script.write(pointLabels, xout);
    Script.writeSeparator(xout);
    Script.write(cellLabels, xout);
    Script.writeSeparator(xout);
    Script.write(position[0], xout);
    Script.writeSeparator(xout);
    Script.write(position[1], xout);
    Script.writeSeparator(xout);
    Script.write(position[2], xout);
    Script.writeSeparator(xout);
    Script.write(origin[0], xout);
    Script.writeSeparator(xout);
    Script.write(origin[1], xout);
    Script.writeSeparator(xout);
    Script.write(origin[2], xout);
    Script.writeSeparator(xout);
    Script.write(orientation[0], xout);
    Script.writeSeparator(xout);
    Script.write(orientation[1], xout);
    Script.writeSeparator(xout);
    Script.write(orientation[2], xout);
    Script.writeSeparator(xout);
    Script.write(scale[0], xout);
    Script.writeSeparator(xout);
    Script.write(scale[1], xout);
    Script.writeSeparator(xout);
    Script.write(scale[2], xout);
  }
}
