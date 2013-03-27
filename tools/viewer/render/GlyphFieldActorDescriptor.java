
/**
 * Classname: GlyphFieldActorDescriptor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: GlyphFieldActorDescriptor.java,v $ $Revision: 1.7 $
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
 * Struct which describes a <code>GlyphFieldActor</code>
 *
 */
public class GlyphFieldActorDescriptor extends G3DFieldActorDescriptor
{
  // PSUEDO_COLOR_FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The scalar property
   */
  public SectionDescriptor scalarProperty = null;

  /**
   * The vector property
   */
  public SectionDescriptor vectorProperty = null;

  /**
   * The glyph source
   */
  public String source = ViewerConstants.SPHERE;

  /**
   * The scale factor
   */
  public double scaleFactor = 0.05;

  /**
   * The scale by data type
   */
  public String scaleMode = ViewerConstants.VECTOR_MAGNITUDE;

  /**
   * The color by data type
   */
  public String colorMode = ViewerConstants.SCALAR;

  /**
   * Default constructor
   */
  public GlyphFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Clone this <code>GlyphFieldActorDescriptor</code>.
   */
  public synchronized GlyphFieldActorDescriptor clone()
  {
    GlyphFieldActorDescriptor result = new GlyphFieldActorDescriptor();

    try
    {
      // Get the correct type of lookup table.

      result.lookupTable = lookupTable.getClass().newInstance();
    }
    catch (Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xactor into this <code>GlyphFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // G3D FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // PSEUDO COLOR FIELD ACTOR DESCRIPTOR FACET

    GlyphFieldActorDescriptor actor = (GlyphFieldActorDescriptor) xactor;

    if(actor.scalarProperty == null)
      scalarProperty = null;
    else
      scalarProperty = actor.scalarProperty.clone();

    if(actor.vectorProperty == null)
      vectorProperty = null;
    else
      vectorProperty = actor.vectorProperty.clone();

    source = actor.source;
    scaleFactor = actor.scaleFactor;
    scaleMode = actor.scaleMode;
    colorMode = actor.colorMode;
  }

  /**
   * Build a <code>GlyphFieldActor</code> from this
   * <code>GlyphFieldActorDescriptor</code>.
   */
  public GlyphFieldActor build()
  {
    namespace_poset ns = Viewer.APPLICATION.getNamespace(namespace);
    sec_vd coords = coordinates.build(ns);

    sec_vd scalar = null;
    if(scalarProperty != null)
      scalar = scalarProperty.build(ns);

    sec_vd vector = null;
    if(vectorProperty != null)
      vector = vectorProperty.build(ns);

    LookupTable lookup = lookupTable.build(ns);

    GlyphFieldActor result = new GlyphFieldActor(coords, scalar,
                             vector, lookup);

    update(result, null);

    return result;
  }

  /**
   * Update xactor to this <code>GlyphFieldDescriptor</code>
   */
  public void update(FieldActor xactor, FieldActorDescriptor xdescriptor)
  {
    // G3D FIELD ACTOR FACET

    super.update(xactor, xdescriptor);

    // GLYPH FIELD ACTOR FACET

    GlyphFieldActor actor = (GlyphFieldActor) xactor;
    GlyphFieldActorDescriptor descriptor =
      (GlyphFieldActorDescriptor) xdescriptor;

    // Create the source

    if(descriptor == null || !source.equals(descriptor.source))
    {
      vtkPolyData glyphSource;

      if(source.equals(ViewerConstants.CONE))
        glyphSource = new vtkConeSource().GetOutput();
      else if(source.equals(ViewerConstants.CYLINDER))
        glyphSource = new vtkCylinderSource().GetOutput();
      else
        glyphSource = new vtkSphereSource().GetOutput();

      actor.glyph.SetSource(glyphSource);
    }

    // Set scale factor

    if(descriptor == null || scaleFactor != descriptor.scaleFactor)
      actor.glyph.SetScaleFactor(scaleFactor);

    // Set Scale Mode

    if(descriptor == null || scaleMode != descriptor.scaleMode)
    {
      if(scaleMode.equals(ViewerConstants.VECTOR_MAGNITUDE))
        actor.glyph.SetScaleModeToScaleByVector();
      else if(scaleMode.equals(ViewerConstants.VECTOR_COMPONENTS))
        actor.glyph.SetScaleModeToScaleByVectorComponents();
      else
        actor.glyph.SetScaleModeToScaleByScalar();
    }

    // Set Color Mode

    if(descriptor == null || colorMode != descriptor.colorMode)
    {
      if(colorMode.equals(ViewerConstants.VECTOR_MAGNITUDE))
        actor.glyph.SetColorModeToColorByVector();
      else
        actor.glyph.SetColorModeToColorByScalar();
    }
  }

  // DESCRIPTOR FACET

  /**
   * Read from a stream constructor
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    String type;

    boolean hasProp = Script.readBoolean(xinput);
    if(hasProp)
    {
      type = Script.readCell(xinput);
      if(!type.equals(SectionDescriptor.class.getName()))
        throw new IOException("Did not find a Section Descriptor." +
                              "\nInstead found: " + type);
      scalarProperty = new SectionDescriptor();
      scalarProperty.read(xinput);
    }
    else
    {
      scalarProperty = null;
    }

    hasProp = Script.readBoolean(xinput);
    if(hasProp)
    {
      type = Script.readCell(xinput);
      if(!type.equals(SectionDescriptor.class.getName()))
        throw new IOException("Did not find a Section Descriptor." +
                              "\nInstead found: " + type);
      vectorProperty = new SectionDescriptor();
      vectorProperty.read(xinput);
    }
    else
    {
      vectorProperty = null;
    }

    source = Script.readCell(xinput);
    scaleFactor = Script.readDouble(xinput);
    scaleMode = Script.readCell(xinput);
    colorMode = Script.readCell(xinput);
  }

  /**
   * Write this <code>GlyphFieldActorDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    if(scalarProperty != null)
    {
      Script.write(true, xout);
      Script.writeSeparator(xout);
      Script.write(scalarProperty.getClass().getName(), xout);
      Script.writeSeparator(xout);
      scalarProperty.write(xout);
    }
    else
    {
      Script.write(false, xout);
    }

    Script.writeSeparator(xout);
    if(vectorProperty != null)
    {
      Script.write(true, xout);
      Script.writeSeparator(xout);
      Script.write(vectorProperty.getClass().getName(), xout);
      Script.writeSeparator(xout);
      vectorProperty.write(xout);
    }
    else
    {
      Script.write(false, xout);
    }

    Script.writeSeparator(xout);
    Script.write(source, xout);
    Script.writeSeparator(xout);
    Script.write(scaleFactor, xout);
    Script.writeSeparator(xout);
    Script.write(scaleMode, xout);
    Script.writeSeparator(xout);
    Script.write(colorMode, xout);
  }

  // FIELD ACTOR DESCRIPTOR FACET

  /**
   * The properties
   */
  public SectionDescriptor[] getProperties()
  {
    int ct = 0;
    if(scalarProperty != null)
      ct++;
    if(vectorProperty != null)
      ct++;

    SectionDescriptor[] result = new SectionDescriptor[ct];

    ct = 0;
    if(scalarProperty != null)
    {
      result[ct] = scalarProperty;
      ct++;
    }
    if(vectorProperty != null)
    {
      result[ct] = vectorProperty;
    }

    return result;
  }

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>GlyphFieldActorDescriptor</code>.
   */
  public PropertiesDialog getPropertiesDialog(Viewer viewer,
      FieldActorDescriptor[] actors)
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    GlyphFieldActorPropertiesPanel panel =
      new GlyphFieldActorPropertiesPanel((G3DViewer) viewer, actors);

    PropertiesDialog result = new PropertiesDialog(frame, "Actor Properties",
                              panel);
    result.setLocationRelativeTo(viewer.getContentPane());

    return result;
  }
}
