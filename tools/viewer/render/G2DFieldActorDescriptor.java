
/**
 * Classname: G2DFieldActorDescriptor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: G2DFieldActorDescriptor.java,v $ $Revision: 1.8 $
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
import javax.swing.*;
import vtk.*;

/**
 *
 * Struct which describes a <code>G2DFieldActor</code>
 *
 */
public class G2DFieldActorDescriptor extends FieldActorDescriptor
{
  // G2D_FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The psuedo color property
   */
  public SectionDescriptor property = null;

  /**
   * The points flag
   */
  public boolean points = false;

  /**
   * The point width
   */
  public double pointSize = 4.0;

  /**
   * The lines flag
   */
  public boolean lines = true;

  /**
   * The line width
   */
  public double lineWidth = 2.0;

  /**
   * The plot title
   */
  public String title = "";

  /**
   * The x-axis title
   */
  public String xtitle = "";

  /**
   * The y-axis title
   */
  public String ytitle = "";

  /**
   * The plot foreground color
   */
  public Color foreground = Color.white;

  /**
   * Default constructor
   */
  public G2DFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Clone this <code>G2DFieldActorDescriptor</code>.
   */
  public synchronized G2DFieldActorDescriptor clone()
  {
    G2DFieldActorDescriptor result = new G2DFieldActorDescriptor();

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xactor into this <code>G2DFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // G2D FIELD ACTOR DESCRIPTOR FACET

    G2DFieldActorDescriptor actor = (G2DFieldActorDescriptor) xactor;

    property = actor.property;
    points = actor.points;
    pointSize = actor.pointSize;
    lines = actor.lines;
    lineWidth = actor.lineWidth;
    title = new String(actor.title);
    xtitle = new String(actor.xtitle);
    ytitle = new String(actor.ytitle);
    foreground = new Color(actor.foreground.getRGB());
  }

  /**
   * Build a <code>G2DFieldActor</code> from this
   * <code>G2DFieldActorDescriptor</code>.
   */
  public G2DFieldActor build()
  {
    namespace_poset ns = Viewer.APPLICATION.getNamespace(namespace);
    sec_vd coords = coordinates.build(ns);
    sec_vd prop = property.build(ns);

    G2DFieldActor result = new G2DFieldActor(coords, prop);

    update(result, null);

    return result;
  }

  /**
   * Update xactor to this <code>G2DFieldDescriptor</code>
   */
  public synchronized void update(FieldActor xactor,
                                  FieldActorDescriptor xdescriptor)
  {
    G2DFieldActor actor = (G2DFieldActor) xactor;
    G2DFieldActorDescriptor descriptor = (G2DFieldActorDescriptor) xdescriptor;

    // DESCRIPTOR FACET

    if(descriptor == null || selected != descriptor.selected)
    {
      int b = selected ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.fieldRep.SetVisibility(b);
    }

    // G2D FIELD ACTOR FACET

    if(descriptor == null || points != descriptor.points)
      actor.xyPlotActor.SetPlotPoints(points ? ViewerConstants.TRUE :
                                      ViewerConstants.FALSE);

    if(descriptor == null || pointSize  != descriptor.pointSize)
      actor.xyPlotProperty.SetPointSize(pointSize);

    if(descriptor == null || lines != descriptor.lines)
      actor.xyPlotActor.SetPlotLines(lines ? ViewerConstants.TRUE :
                                     ViewerConstants.FALSE);

    if(descriptor == null || lineWidth  != descriptor.lineWidth)
      actor.xyPlotProperty.SetLineWidth(lineWidth);

    if(descriptor == null || !title.equals(descriptor.title))
      actor.xyPlotActor.SetTitle(title);

    if(descriptor == null || !xtitle.equals(descriptor.xtitle))
      actor.xyPlotActor.SetXTitle(xtitle);

    if(descriptor == null || !ytitle.equals(descriptor.ytitle))
      actor.xyPlotActor.SetYTitle(ytitle);

    if(descriptor == null || !foreground.equals(descriptor.foreground))
    {
      float[] rgba = new float[4];
      foreground.getRGBComponents(rgba);
      actor.xyPlotProperty.SetColor(rgba[0], rgba[1], rgba[2]);
      actor.titleProperty.SetColor(rgba[0], rgba[1], rgba[2]);
      actor.axisTitleProperty.SetColor(rgba[0], rgba[1], rgba[2]);
      actor.axisLabelProperty.SetColor(rgba[0], rgba[1], rgba[2]);
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
    // Nothing to interpolate

    return new double[0][0];
  }

  /**
   * Interpolate the values of this <code>FieldActorDescriptor</code> given
   * the start point, increment, and step.
   */
  public void interpolate(FieldActorDescriptor xstart,
                          double[][] xincrement, int xstep)
  {
    // Nothing to interpolate
  }

  // DESCRIPTOR FACET

  /**
   * Read from a stream constructor
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    String type = Script.readCell(xinput);
    if(!type.equals(SectionDescriptor.class.getName()))
      throw new IOException("Did not find a Section Descriptor." +
                            "\nInstead found: " + type);
    property = new SectionDescriptor();
    property.read(xinput);

    points = Script.readBoolean(xinput);
    pointSize = Script.readDouble(xinput);
    lines = Script.readBoolean(xinput);
    lineWidth = Script.readDouble(xinput);
    title = Script.readCell(xinput);
    xtitle = Script.readCell(xinput);
    ytitle = Script.readCell(xinput);
    foreground = Script.readColor(xinput);
  }

  /**
   * Write this <code>G2DFieldActorDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(property.getClass().getName(), xout);
    Script.writeSeparator(xout);
    property.write(xout);
    Script.writeSeparator(xout);
    Script.write(points, xout);
    Script.writeSeparator(xout);
    Script.write(pointSize, xout);
    Script.writeSeparator(xout);
    Script.write(lines, xout);
    Script.writeSeparator(xout);
    Script.write(lineWidth, xout);
    Script.writeSeparator(xout);
    Script.write(title, xout);
    Script.writeSeparator(xout);
    Script.write(xtitle, xout);
    Script.writeSeparator(xout);
    Script.write(ytitle, xout);
    Script.writeSeparator(xout);
    Script.write(foreground, xout);
  }

  // FIELD ACTOR DESCRIPTOR FACET

  /**
   * The properties
   */
  public SectionDescriptor[] getProperties()
  {
    SectionDescriptor[] result = new SectionDescriptor[1];
    result[0] = property;

    return result;
  }

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>PseudoColorFieldActorDescriptor</code>.
   */
  public PropertiesDialog getPropertiesDialog(Viewer viewer, FieldActorDescriptor[] xactors)
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    G2DFieldActorPropertiesPanel panel =
      new G2DFieldActorPropertiesPanel((G2DViewer) viewer, xactors);

    PropertiesDialog result = new PropertiesDialog(frame, "Actor Properties",
                              panel);
    result.setLocationRelativeTo(viewer.getContentPane());

    return result;
  }
}
