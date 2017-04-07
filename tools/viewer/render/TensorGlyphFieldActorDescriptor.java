
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
 * Struct which describes a <code>TensorGlyphFieldActor</code>
 *
 */
public class TensorGlyphFieldActorDescriptor extends G3DFieldActorDescriptor
{
  // PSUEDO_COLOR_FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The scalar property
   */
  public SectionDescriptor scalarProperty = null;

  /**
   * The tensor property
   */
  public SectionDescriptor tensorProperty = null;

  /**
   * The glyph source
   */
  public String source = ViewerConstants.SPHERE;

  /**
   * The scale factor
   */
  public double scaleFactor = 0.05;

  /**
   * The symmetric flag
   */
  public boolean symmetric = true;

  /**
   * Default constructor
   */
  public TensorGlyphFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Clone this <code>TensorGlyphFieldActorDescriptor</code>.
   */
  public synchronized TensorGlyphFieldActorDescriptor clone()
  {
    TensorGlyphFieldActorDescriptor result =
      new TensorGlyphFieldActorDescriptor();

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
   * Copy the values of xactor into this
   * <code>TensorGlyphFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // G3D FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // PSEUDO COLOR FIELD ACTOR DESCRIPTOR FACET

    TensorGlyphFieldActorDescriptor actor =
      (TensorGlyphFieldActorDescriptor) xactor;

    if(actor.scalarProperty == null)
      scalarProperty = null;
    else
      scalarProperty = actor.scalarProperty.clone();

    tensorProperty = actor.tensorProperty.clone();

    source = actor.source;
    scaleFactor = actor.scaleFactor;
    symmetric = actor.symmetric;
  }

  /**
   * Build a <code>TensorGlyphFieldActor</code> from this
   * <code>TensorGlyphFieldActorDescriptor</code>.
   */
  public TensorGlyphFieldActor build()
  {
    namespace_poset ns = Viewer.APPLICATION.getNamespace(namespace);
    sec_vd coords = coordinates.build(ns);

    sec_vd scalar = null;
    if(scalarProperty != null)
      scalar = scalarProperty.build(ns);

    sec_vd tensor = tensorProperty.build(ns);

    LookupTable lookup = lookupTable.build(ns);

    TensorGlyphFieldActor result = new TensorGlyphFieldActor(coords, scalar,
                                   tensor, lookup);

    update(result, null);

    return result;
  }

  /**
   * Update xactor to this <code>TensorGlyphFieldDescriptor</code>
   */
  public void update(FieldActor xactor, FieldActorDescriptor xdescriptor)
  {
    // G3D FIELD ACTOR FACET

    super.update(xactor, xdescriptor);

    // TENSOR GLYPH FIELD ACTOR FACET

    TensorGlyphFieldActor actor = (TensorGlyphFieldActor) xactor;
    TensorGlyphFieldActorDescriptor descriptor =
      (TensorGlyphFieldActorDescriptor) xdescriptor;

    int b;

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

      actor.tensorGlyph.SetSourceData(glyphSource);
    }

    // Set scale factor

    if(descriptor == null || scaleFactor != descriptor.scaleFactor)
      actor.tensorGlyph.SetScaleFactor(scaleFactor);

    // Set the symmetric mode

    if(descriptor == null || symmetric != descriptor.symmetric)
    {
      b = symmetric ? ViewerConstants.TRUE : ViewerConstants.FALSE;
      actor.tensorGlyph.SetSymmetric(b);
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

    type = Script.readCell(xinput);
    if(!type.equals(SectionDescriptor.class.getName()))
      throw new IOException("Did not find a Section Descriptor." +
                            "\nInstead found: " + type);
    tensorProperty = new SectionDescriptor();
    tensorProperty.read(xinput);

    source = Script.readCell(xinput);
    scaleFactor = Script.readDouble(xinput);
    symmetric = Script.readBoolean(xinput);
  }

  /**
   * Write this <code>TensorGlyphFieldActorDescriptor</code> to xout.
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
    Script.write(tensorProperty.getClass().getName(), xout);
    Script.writeSeparator(xout);
    tensorProperty.write(xout);

    Script.writeSeparator(xout);
    Script.write(source, xout);
    Script.writeSeparator(xout);
    Script.write(scaleFactor, xout);
    Script.writeSeparator(xout);
    Script.write(symmetric, xout);
  }

  // FIELD ACTOR DESCRIPTOR FACET

  /**
   * The properties
   */
  public SectionDescriptor[] getProperties()
  {
    int ct = 1;
    if(scalarProperty != null)
      ct++;

    SectionDescriptor[] result = new SectionDescriptor[ct];

    ct = 0;
    if(scalarProperty != null)
    {
      result[ct] = scalarProperty;
      ct++;
    }

    result[ct] = tensorProperty;

    return result;
  }

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>TensorGlyphFieldActorDescriptor</code>.
   */
  public PropertiesDialog getPropertiesDialog(Viewer viewer,
      FieldActorDescriptor[] actors)
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    TensorGlyphFieldActorPropertiesPanel panel =
      new TensorGlyphFieldActorPropertiesPanel((G3DViewer) viewer, actors);

    PropertiesDialog result = new PropertiesDialog(frame, "Actor Properties",
                              panel);
    result.setLocationRelativeTo(viewer.getContentPane());

    return result;
  }
}
