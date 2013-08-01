
/**
 * Classname: HedgeHogFieldActorDescriptor
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
 * Struct which describes a <code>HedgeHogFieldActor</code>
 *
 */
public class HedgeHogFieldActorDescriptor extends G3DFieldActorDescriptor
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
   * The scale factor
   */
  public double scaleFactor = 0.05;

  /**
   * The scale by data type
   */
  public String vectorMode = ViewerConstants.VECTOR_MAGNITUDE;

  /**
   * Default constructor
   */
  public HedgeHogFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Clone this <code>HedgeHogFieldActorDescriptor</code>.
   */
  public synchronized HedgeHogFieldActorDescriptor clone()
  {
    HedgeHogFieldActorDescriptor result = new HedgeHogFieldActorDescriptor();

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
   * Copy the values of xactor into this <code>HedgeHogFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // G3D FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // PSEUDO COLOR FIELD ACTOR DESCRIPTOR FACET

    HedgeHogFieldActorDescriptor actor = (HedgeHogFieldActorDescriptor) xactor;

    if(actor.scalarProperty == null)
      scalarProperty = null;
    else
      scalarProperty = actor.scalarProperty.clone();

    vectorProperty = actor.vectorProperty.clone();

    scaleFactor = actor.scaleFactor;
    vectorMode = actor.vectorMode;
  }

  /**
   * Build a <code>HedgeHogFieldActor</code> from this
   * <code>HedgeHogFieldActorDescriptor</code>.
   */
  public HedgeHogFieldActor build()
  {
    namespace_poset ns = Viewer.APPLICATION.getNamespace(namespace);
    sec_vd coords = coordinates.build(ns);

    sec_vd scalar = null;
    if(scalarProperty != null)
      scalar = scalarProperty.build(ns);

    sec_vd vector = vectorProperty.build(ns);

    LookupTable lookup = lookupTable.build(ns);

    HedgeHogFieldActor result = new HedgeHogFieldActor(coords, scalar,
                                vector, lookup);

    update(result, null);

    return result;
  }

  /**
   * Update xactor to this <code>HedgeHogFieldDescriptor</code>
   */
  public void update(FieldActor xactor, FieldActorDescriptor xdescriptor)
  {
    // G3D FIELD ACTOR FACET

    super.update(xactor, xdescriptor);

    // HEDGE HOG FIELD ACTOR FACET

    HedgeHogFieldActor actor = (HedgeHogFieldActor) xactor;
    HedgeHogFieldActorDescriptor descriptor =
      (HedgeHogFieldActorDescriptor) xdescriptor;

    // Set scale factor

    if(descriptor == null || scaleFactor != descriptor.scaleFactor)
      actor.hedgeHog.SetScaleFactor(scaleFactor);

    // Set Scale Mode

    if(descriptor == null || vectorMode != descriptor.vectorMode)
    {
      if(vectorMode.equals(ViewerConstants.VECTOR_MAGNITUDE))
        actor.hedgeHog.SetVectorModeToUseVector();
      else
        actor.hedgeHog.SetVectorModeToUseNormal();
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
    vectorProperty = new SectionDescriptor();
    vectorProperty.read(xinput);

    scaleFactor = Script.readDouble(xinput);
    vectorMode = Script.readCell(xinput);
  }

  /**
   * Write this <code>HedgeHogFieldActorDescriptor</code> to xout.
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
    Script.write(vectorProperty.getClass().getName(), xout);
    Script.writeSeparator(xout);
    vectorProperty.write(xout);

    Script.writeSeparator(xout);
    Script.write(scaleFactor, xout);
    Script.writeSeparator(xout);
    Script.write(vectorMode, xout);
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

    result[ct] = vectorProperty;

    return result;
  }

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>HedgeHogFieldActorDescriptor</code>.
   */
  public PropertiesDialog getPropertiesDialog(Viewer viewer,
      FieldActorDescriptor[] actors)
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    HedgeHogFieldActorPropertiesPanel panel =
      new HedgeHogFieldActorPropertiesPanel((G3DViewer) viewer, actors);

    PropertiesDialog result = new PropertiesDialog(frame, "Actor Properties",
                              panel);
    result.setLocationRelativeTo(viewer.getContentPane());

    return result;
  }
}
