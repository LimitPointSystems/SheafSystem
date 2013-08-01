
/**
 * Classname: PseudoColorFieldActorDescriptor
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
 * Struct which describes a <code>PseudoColorFieldActor</code>
 *
 */
public class PseudoColorFieldActorDescriptor extends G3DFieldActorDescriptor
{
  // PSUEDO_COLOR_FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The psuedo color property
   */
  public SectionDescriptor property = null;

  /**
   * Default constructor
   */
  public PseudoColorFieldActorDescriptor()
  {}

  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * Clone this <code>PseudoColorFieldActorDescriptor</code>.
   */
  public synchronized PseudoColorFieldActorDescriptor clone()
  {
    PseudoColorFieldActorDescriptor result = new PseudoColorFieldActorDescriptor();

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
   * Copy the values of xactor into this <code>PseudoColorFieldActorDescriptor</code>.
   */
  public synchronized void copy(FieldActorDescriptor xactor)
  {
    // G3D FIELD ACTOR DESCRIPTOR FACET

    super.copy(xactor);

    // PSEUDO COLOR FIELD ACTOR DESCRIPTOR FACET

    PseudoColorFieldActorDescriptor actor = (PseudoColorFieldActorDescriptor) xactor;

    if(actor.property == null)
      property = null;
    else
      property = actor.property.clone();
  }

  /**
   * Build a <code>PseudoColorFieldActor</code> from this
   * <code>PseudoColorFieldActorDescriptor</code>.
   */
  public PseudoColorFieldActor build()
  {
    namespace_poset ns = Viewer.APPLICATION.getNamespace(namespace);
    sec_vd coords = coordinates.build(ns);
    sec_vd prop = null;
    if(property != null)
      prop = property.build(ns);

    LookupTable lookup = lookupTable.build(ns);

    PseudoColorFieldActor result =
      new PseudoColorFieldActor(coords, prop, lookup);

    update(result, null);

    return result;
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
      property = new SectionDescriptor();
      property.read(xinput);
    }
    else
    {
      property = null;
    }
  }

  /**
   * Write this <code>PseudoColorFieldActorDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    if(property != null)
    {
      Script.write(true, xout);
      Script.writeSeparator(xout);
      Script.write(property.getClass().getName(), xout);
      Script.writeSeparator(xout);
      property.write(xout);
    }
    else
    {
      Script.write(false, xout);
    }
  }

  // FIELD ACTOR DESCRIPTOR FACET

  /**
   * The properties
   */
  public SectionDescriptor[] getProperties()
  {
    if(property == null)
      return new SectionDescriptor[0];

    SectionDescriptor[] result = new SectionDescriptor[1];
    result[0] = property;

    return result;
  }

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>PseudoColorFieldActorDescriptor</code>.
   */
  public PropertiesDialog getPropertiesDialog(Viewer viewer, FieldActorDescriptor[] actors)
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    PseudoColorFieldActorPropertiesPanel panel =
      new PseudoColorFieldActorPropertiesPanel((G3DViewer) viewer, actors);

    PropertiesDialog result = new PropertiesDialog(frame, "Actor Properties",
                              panel);
    result.setLocationRelativeTo(viewer.getContentPane());

    return result;
  }
}
