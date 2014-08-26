
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


package com.limitpoint.tools.viewer.render;

import com.limitpoint.tools.viewer.animation.*;
import com.limitpoint.tools.viewer.common.*;
import com.limitpoint.tools.viewer.user.*;
import com.limitpoint.bindings.java.*;

import java.awt.*;
import java.io.*;
import java.util.*;

/**
 *
 * Struct which describes an <code>FieldActor</code>
 *
 */
public abstract class FieldActorDescriptor extends Descriptor
{
  // FIELD_ACTOR_DESCRIPTOR FACET

  /**
   * The name of the <code>namespace_poset</code> for the field.
   */
  public String namespace = null;

  /**
   * The <code>SectionDescriptor</code> of the coordinates
   */
  public SectionDescriptor coordinates = new SectionDescriptor();

  /**
   * The visibility of the <code>FieldActor</code>
   */
  public boolean visibility = true;

  /**
   * Default constructor
   */
  protected FieldActorDescriptor()
  {}

  /**
   * Clone this <code>FieldActorDescriptor</code>.
   */
  public abstract FieldActorDescriptor clone();

  /**
   * Copy the values of xactor into this <code>FieldActorDescriptor</code>.
   */
  public void copy(FieldActorDescriptor xactor)
  {
    // DESCRIPTOR FACET

    selected = xactor.selected;
    time = xactor.time;

    // FIELD ACTOR DESCRIPTOR FACET

    namespace = new String(xactor.namespace);
    coordinates.copy(xactor.coordinates);
    time = xactor.time;
    visibility = xactor.visibility;
  }

  /**
   * Build a <code>FieldActor</code> from this
   * <code>FieldActorDescriptor</code>.
   */
  public abstract FieldActor build();

  /**
   * Update xactor to this <code>FieldActorDescriptor</code>
   */
  public abstract void update(FieldActor xactor,
                              FieldActorDescriptor xdescriptor);

  /**
   * The array of this <code>FieldActorDescriptor</code> properties.
   */
  public abstract SectionDescriptor[] getProperties();

  /**
   * The <code>PropertiesDialog</code> associated with this
   * <code>FieldActorDescriptor</code>.
   */
  public abstract PropertiesDialog getPropertiesDialog(Viewer viewer,
      FieldActorDescriptor[] xactors);

  /**
   * Calculate and return a two dimensional array of increments used for
   * interpolation.  The first index is the variable, The second index is the
   * coordinate values; (x, y, z) or (latitude, longitude, distance).
   */
  public abstract double[][] calcIncrements(FieldActorDescriptor xactor,
      boolean xshort, int xsteps);

  /**
   * Interpolate the values of this <code>FieldActorDescriptor</code> given
   * the start point, increment, and step.
   */
  public abstract void interpolate(FieldActorDescriptor xstart,
                                   double[][] xincrement, int xstep);

  /**
   * The name of this descriptor, used by the <code>FieldActorPanel</code>
   */
  public String toString()
  {
    //
    // $$ISSUE: The creation of this name is done every time toString() is called
    //          There should be a name variable which is instantiated once and
    //          then returned by this method.  This variable would need to be
    //          changed everytime a property section is added.
    //

    String result = "";
    poset_path lpath;

    try
    {
      SectionDescriptor[] properties = getProperties();
      boolean multiple = properties.length>1;

      if(multiple)
        result += "[";

      for(int i=0; i<properties.length; i++)
      {
        lpath = new poset_path(properties[i].path);
        result += lpath.member_name();

        if(i+1<properties.length)
          result += ", ";
      }

      if(multiple)
        result += "]";

      if(properties.length > 0)
        result += " vs ";

      lpath = new poset_path(coordinates.path);
      result += lpath.member_name();
    }
    catch(Exception e)
    {}

    return result;
  }

  // DESCRIPTOR FACET

  /**
   * Set the time
   */
  public void setTime(double xtime)
  {
    super.setTime(xtime);

    coordinates.setTime(xtime);
    SectionDescriptor[] properties = getProperties();
    for(int i=0; i<properties.length; i++)
    {
      properties[i].setTime(xtime);
    }
  }

  /**
   * Read from a stream constructor
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    namespace = Script.readCell(xinput);

    String type = Script.readCell(xinput);
    if(!type.equals(SectionDescriptor.class.getName()))
      throw new IOException("Did not find a Section Descriptor." +
                            "\nInstead found: " + type);
    coordinates = new SectionDescriptor();
    coordinates.read(xinput);

    time = Script.readDouble(xinput);
    visibility = Script.readBoolean(xinput);

    // Test to make sure the poset paths are contained in the
    // namespace.

    try
    {
      namespace_poset ns =
        Viewer.APPLICATION.getNamespace(namespace);
      if(ns == null)
        throw new IOException("Namespace is not open: " + namespace);

      poset_path path = new poset_path(coordinates.path);
      if(!ns.contains_poset(path, true))
        throw new IOException("Coordinate Poset is not in the Namespace: " +
                              coordinates);
    }
    catch(java.rmi.RemoteException e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }
  }

  /**
   * Write this <code>FieldActorDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(namespace, xout);
    Script.writeSeparator(xout);
    Script.write(coordinates.getClass().getName(), xout);
    Script.writeSeparator(xout);
    coordinates.write(xout);
    Script.writeSeparator(xout);
    Script.write(time, xout);
    Script.writeSeparator(xout);
    Script.write(visibility, xout);
  }

  /**
   * Override the hashCode method.  It is the addition of all the
   * section <code>String</code> hash codes.
   */
  public int hashCode()
  {
    if(coordinates == null)
      return 0;

    //
    // $$ISSUE: This method calculates the hashCode
    //          every time it is called.  Hence, it
    //          is not very efficent.
    //

    SectionDescriptor[] properties = getProperties();
    int result = namespace.hashCode() + coordinates.hashCode();
    for(int i=0; i<properties.length; i++)
    {
      result += properties[i].hashCode();
    }

    return result;
  }

  /**
   * Override the equals method.  This is a test of equivalence.  True,
   * if the section paths are the same.
   */
  public boolean equals(Object obj)
  {
    if(!(obj instanceof FieldActorDescriptor))
      return false;

    FieldActorDescriptor input = (FieldActorDescriptor) obj;

    if(!input.namespace.equals(namespace))
      return false;

    if(!input.coordinates.equals(coordinates))
      return false;

    return true;
  }
}
