
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

import com.limitpoint.tools.common.util.*;
import com.limitpoint.tools.viewer.animation.*;
import com.limitpoint.tools.viewer.common.*;

import java.awt.*;
import java.io.*;
import java.util.*;

import vtk.*;

/**
 *
 * Struct which describe a light.
 *
 */
public class LightDescriptor extends Descriptor
{
  // LIGHT_DESCRIPTOR FACET

  /**
   * The light id
   */
  public int id = 0;

  /**
   * The camera light
   */
  public boolean cameraLight = true;

  /**
   * The position
   */
  public double[] position = {0.0, 0.0, 0.0};

  /**
   * The focal point
   */
  public double[] focalPoint = {0,0, 0.0, 0.0};

  /**
   * The on/off switch
   */
  public boolean switchOn = true;

  /**
   * The color
   */
  public Color color = new Color((float) 1.0,
                                 (float) 1.0,
                                 (float) 1.0);

  /**
   * The intensity
   */
  public double intensity = 1.0;

  /**
   * Default constructor
   */
  public LightDescriptor()
  {}

  /**
   * Clone this <code>LightDescriptor</code>.
   */
  public synchronized LightDescriptor clone()
  {
    LightDescriptor result = new LightDescriptor();

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xlight into this <code>LightDescriptor</code>.
   */
  public synchronized void copy(LightDescriptor xlight)
  {
    // DESCRIPTOR FACET

    selected = xlight.selected;
    time = xlight.time;

    // LIGHT DESCRIPTOR FACET

    id = xlight.id;
    cameraLight = xlight.cameraLight;

    position[0] = xlight.position[0];
    position[1] = xlight.position[1];
    position[2] = xlight.position[2];

    focalPoint[0] = xlight.focalPoint[0];
    focalPoint[1] = xlight.focalPoint[1];
    focalPoint[2] = xlight.focalPoint[2];

    switchOn = xlight.switchOn;

    color = new Color(xlight.color.getRGB());

    intensity = xlight.intensity;
  }

  /**
   * The name of this descriptor, used by the <code>LightPanel</code>
   */
  public String toString()
  {
    if(cameraLight)
      return "Camera Light";
    else
      return "Light " + Integer.toString(id);
  }

  /**
   * Build a <code>vtkLight</code> from this <code>LightDescriptor</code>.
   */
  public vtkLight build()
  {
    vtkLight result = new vtkLight();

    if(cameraLight)
      result.SetLightTypeToCameraLight();
    else
      result.SetLightTypeToSceneLight();

    update(result, null);

    return result;
  }

  /**
   * Update xlight to this <code>LightDescriptor</code>
   */
  public void update(vtkLight xlight, LightDescriptor xdescriptor)
  {
    if(!cameraLight &&
        (xdescriptor == null || !compare(position, xdescriptor.position)))
      xlight.SetPosition(position);

    if(!cameraLight &&
        (xdescriptor == null || !compare(focalPoint, xdescriptor.focalPoint)))
      xlight.SetFocalPoint(focalPoint);

    if(xdescriptor == null || switchOn != xdescriptor.switchOn)
      xlight.SetSwitch(switchOn ? ViewerConstants.TRUE
                       : ViewerConstants.FALSE);

    if(xdescriptor == null || !color.equals(xdescriptor.color))
    {
      float[] rgba = new float[4];
      color.getRGBComponents(rgba);
      xlight.SetColor(rgba[0], rgba[1], rgba[2]);
    }

    if(xdescriptor == null || intensity != xdescriptor.intensity)
      xlight.SetIntensity(intensity);
  }

  /**
   * Calculate and return a two dimensional array of increments used for
   * interpolation.  The first index is the variable, The second index is the
   * coordinate values; (x, y, z) or (latitude, longitude, distance).
   */
  public double[][] calcIncrements(LightDescriptor xlight,
                                   boolean xshort, int xsteps)
  {
    double[][] result = new double[2][3];

    if(!cameraLight)
    {
      // Index 0, The position

      LPSMath.calcPolarIncrement(result[0], xlight.position,
                                 position, xshort, xsteps);

      // Index 1, The focal point

      LPSMath.calcLinearIncrement(result[1], xlight.focalPoint,
                                  focalPoint, xsteps);
    }

    return result;
  }

  /**
   * Interpolate the values of this <code>LightDescriptor</code> given
   * the start point, increment, and step.
   */
  public void interpolate(LightDescriptor xstart, double[][] xincrement, int xstep)
  {
    if(!cameraLight)
    {
      // Index 0, The position

      LPSMath.incrementPolar(position, xstart.position, xincrement[0], xstep);

      // Index 1, The focal point

      LPSMath.incrementPolar(focalPoint, xstart.focalPoint, xincrement[1], xstep);
    }
  }

  // DESCRIPTOR FACET

  /**
   * Read the values of this <code>LightDescriptor</code> from xinput
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    id = Script.readInt(xinput);
    cameraLight = Script.readBoolean(xinput);
    position[0] = Script.readDouble(xinput);
    position[1] = Script.readDouble(xinput);
    position[2] = Script.readDouble(xinput);
    focalPoint[0] = Script.readDouble(xinput);
    focalPoint[1] = Script.readDouble(xinput);
    focalPoint[2] = Script.readDouble(xinput);
    switchOn = Script.readBoolean(xinput);
    color = Script.readColor(xinput);
    intensity = Script.readDouble(xinput);
  }

  /**
   * Write this <code>LightDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(id, xout);
    Script.writeSeparator(xout);
    Script.write(cameraLight, xout);
    Script.writeSeparator(xout);
    Script.write(position[0], xout);
    Script.writeSeparator(xout);
    Script.write(position[1], xout);
    Script.writeSeparator(xout);
    Script.write(position[2], xout);
    Script.writeSeparator(xout);
    Script.write(focalPoint[0], xout);
    Script.writeSeparator(xout);
    Script.write(focalPoint[1], xout);
    Script.writeSeparator(xout);
    Script.write(focalPoint[2], xout);
    Script.writeSeparator(xout);
    Script.write(switchOn, xout);
    Script.writeSeparator(xout);
    Script.write(color, xout);
    Script.writeSeparator(xout);
    Script.write(intensity, xout);
  }

  /**
   * Override the hashCode method.  Same as the id.
   */
  public int hashCode()
  {
    return id;
  }

  /**
   * Override the equals method.  True, if the ids
   * are the same.
   */
  public boolean equals(Object obj)
  {
    if(!(obj instanceof LightDescriptor))
      return false;

    LightDescriptor input = (LightDescriptor) obj;

    return (input.id == id);
  }
}
