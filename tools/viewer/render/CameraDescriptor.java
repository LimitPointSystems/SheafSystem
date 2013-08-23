
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
import tools.viewer.animation.*;
import tools.viewer.common.*;

import java.awt.*;
import java.io.*;
import java.util.*;

import vtk.*;

/**
 *
 * Struct which describes a camera
 *
 */
public class CameraDescriptor extends Descriptor
{
  // CAMERA_DESCRIPTOR FACET

  /**
   * The camera id
   */
  public int id = 0;

  /**
   * The position
   */
  public double[] position = null;

  /**
   * The focal point
   */
  public double[] focalPoint = null;

  /**
   * The view up
   */
  public double[] viewUp = null;

  /**
   * The background color
   */
  public Color background = new Color((float) 0.4,
                                      (float) 0.4,
                                      (float) 0.6);

  /**
   * The parallel projection
   */
  public boolean projection = false;

  /**
   * Default constructor
   */
  public CameraDescriptor()
  {}

  /**
   * Clone this <code>CameraDescriptor</code>.
   */
  public synchronized CameraDescriptor clone()
  {
    CameraDescriptor result = new CameraDescriptor();

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xcamera into this <code>CameraDescriptor</code>.
   */
  public synchronized void copy(CameraDescriptor xcamera)
  {
    // DESCRIPTOR FACET

    selected = xcamera.selected;
    time = xcamera.time;

    // CAMERA DESCRIPTOR FACET

    id = xcamera.id;

    if(xcamera.position != null)
    {
      if(position == null)
        position = new double[3];

      position[0] = xcamera.position[0];
      position[1] = xcamera.position[1];
      position[2] = xcamera.position[2];
    }
    else
    {
      position = null;
    }

    if(xcamera.focalPoint != null)
    {
      if(focalPoint == null)
        focalPoint = new double[3];

      focalPoint[0] = xcamera.focalPoint[0];
      focalPoint[1] = xcamera.focalPoint[1];
      focalPoint[2] = xcamera.focalPoint[2];
    }
    else
    {
      focalPoint = null;
    }

    if(xcamera.viewUp != null)
    {
      if(viewUp == null)
        viewUp = new double[3];

      viewUp[0] = xcamera.viewUp[0];
      viewUp[1] = xcamera.viewUp[1];
      viewUp[2] = xcamera.viewUp[2];
    }
    else
    {
      viewUp = null;
    }

    background = new Color(xcamera.background.getRGB());

    projection = xcamera.projection;
  }

  /**
   * The name of this descriptor, used by the <code>CameraPanel</code>
   */
  public String toString()
  {
    return "Camera " + Integer.toString(id);
  }

  /**
   * Build a <code>vtkCamera</code> from this <code>CameraDescriptor</code>.
   */
  public vtkCamera build()
  {
    vtkCamera result = new vtkCamera();

    update(result, null);

    return result;
  }

  /**
   * Update xcamera to this <code>CameraDescriptor</code>
   */
  public void update(vtkCamera xcamera, CameraDescriptor xdescriptor)
  {
    if(position != null &&
        (xdescriptor == null || xdescriptor.position == null ||
         !compare(position, xdescriptor.position)))
      xcamera.SetPosition(position);

    if(focalPoint != null &&
        (xdescriptor == null || xdescriptor.focalPoint == null ||
         !compare(focalPoint, xdescriptor.focalPoint)))
      xcamera.SetFocalPoint(focalPoint);

    if(viewUp != null &&
        (xdescriptor == null || xdescriptor.viewUp == null ||
         !compare(viewUp, xdescriptor.viewUp)))
      xcamera.SetViewUp(viewUp);

    if(xdescriptor == null || projection != xdescriptor.projection)
      xcamera.SetParallelProjection(projection ? ViewerConstants.TRUE
                                    : ViewerConstants.FALSE);
  }

  /**
   * Calculate and return a two dimensional array of increments used for
   * interpolation.  The first index is the variable, The second index is the
   * coordinate values; (x, y, z) or (latitude, longitude, distance).
   */
  public double[][] calcIncrements(CameraDescriptor xcamera,
                                   boolean xshort, int xsteps)
  {
    double[][] result = new double[3][3];

    // Index 0, The position

    LPSMath.calcPolarIncrement(result[0], xcamera.position,
                               position, xshort, xsteps);

    // Index 1, The focal point

    LPSMath.calcLinearIncrement(result[1], xcamera.focalPoint,
                                focalPoint, xsteps);

    // Index 2, The view up

    LPSMath.calcLinearIncrement(result[2], xcamera.viewUp,
                                viewUp, xsteps);

    return result;
  }

  /**
   * Interpolate the values of this <code>CameraDescriptor</code> given
   * the start point, increment, and step.
   */
  public void interpolate(CameraDescriptor xstart, double[][] xincrement, int xstep)
  {
    // Index 0, The position

    LPSMath.incrementPolar(position, xstart.position, xincrement[0], xstep);

    // Index 1, The focal point

    LPSMath.incrementLinear(focalPoint, xstart.focalPoint, xincrement[1], xstep);

    // Index 2, The view up

    LPSMath.incrementLinear(viewUp, xstart.viewUp, xincrement[2], xstep);
  }

  // DESCRIPTOR FACET

  /**
   * Read the values of this <code>CameraDescriptor</code> from xinput
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    id = Script.readInt(xinput);
    try
    {
      position = new double[3];
      position[0] = Script.readDouble(xinput);
      position[1] = Script.readDouble(xinput);
      position[2] = Script.readDouble(xinput);
    }
    catch(IOException e)
    {
      position = null;
    }

    try
    {
      focalPoint = new double[3];
      focalPoint[0] = Script.readDouble(xinput);
      focalPoint[1] = Script.readDouble(xinput);
      focalPoint[2] = Script.readDouble(xinput);
    }
    catch(IOException e)
    {
      focalPoint = null;
    }

    try
    {
      viewUp = new double[3];
      viewUp[0] = Script.readDouble(xinput);
      viewUp[1] = Script.readDouble(xinput);
      viewUp[2] = Script.readDouble(xinput);
    }
    catch(IOException e)
    {
      viewUp = null;
    }
    background = Script.readColor(xinput);
    projection = Script.readBoolean(xinput);
  }

  /**
   * Write this <code>CameraDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(id, xout);
    Script.writeSeparator(xout);
    if(position != null)
    {
      Script.write(position[0], xout);
      Script.writeSeparator(xout);
      Script.write(position[1], xout);
      Script.writeSeparator(xout);
      Script.write(position[2], xout);
    }
    Script.writeSeparator(xout);
    if(focalPoint != null)
    {
      Script.write(focalPoint[0], xout);
      Script.writeSeparator(xout);
      Script.write(focalPoint[1], xout);
      Script.writeSeparator(xout);
      Script.write(focalPoint[2], xout);
    }
    Script.writeSeparator(xout);
    if(viewUp != null)
    {
      Script.write(viewUp[0], xout);
      Script.writeSeparator(xout);
      Script.write(viewUp[1], xout);
      Script.writeSeparator(xout);
      Script.write(viewUp[2], xout);
    }
    Script.writeSeparator(xout);
    Script.write(background, xout);
    Script.writeSeparator(xout);
    Script.write(projection, xout);
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
    if(!(obj instanceof CameraDescriptor))
      return false;

    CameraDescriptor input = (CameraDescriptor) obj;

    return (input.id == id);
  }
}
