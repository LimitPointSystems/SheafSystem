
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


package com.limitpoint.tools.viewer.animation;

import com.limitpoint.bindings.java.*;
import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.common.util.*;
import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.viewer.user.*;

import java.awt.*;
import java.util.*;
import java.io.*;
import javax.swing.*;

/**
 *
 * The <code>Script</code> is the collection of scenes which
 * make up the Play.  It contains the time information, the
 * interpolation method and frame rate.
 *
 */
public class Script extends ArrayList<SceneDescriptor>
{
  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  // DATA FACET

  /**
   * The min time
   */
  public double minTime = 0.0;

  /**
   * The max time
   */
  public double maxTime = 0.0;

  /**
   * The unit of time
   */
  public String unit = "";

  /**
   * Sceen rate (scenes/second)
   */
  public double rate = 10.0;

  /**
   * The interpolation mode
   */
  public int interpolation = ViewerConstants.SHORT_INTERPOLATION;

  /**
   * The file filter suffix list.
   */
  private static String[] suffixes = {"csv"};

  /**
   * The file filter for all Scripts.
   */
  private static SuffixFileFilter  filter = new SuffixFileFilter(suffixes);

  /**
   * The Constructor
   */
  public Script(Viewer xviewer)
  {
    viewer = xviewer;
  }

  /**
   * Read from a file constructor
   */
  public Script(Viewer xviewer, File xfile) throws IOException
  {
    viewer = xviewer;

    FileInputStream fis = new FileInputStream(xfile);
    BufferedInputStream bis = new BufferedInputStream(fis);

    String type = readCell(bis);
    if(!type.equals(viewer.getClass().getName()))
    {
      throw new IOException("Viewer types do not match!\n\nExpected: " +
                            viewer.getClass().getName() + "\nFound: " +
                            type);
    }
    
    minTime = readDouble(bis);
    maxTime = readDouble(bis);
    unit = readCell(bis);
    rate = readDouble(bis);
    interpolation = readInt(bis);

    // Read the first scene type identifier.
    type = readCell(bis);
    if(!type.equals(SceneDescriptor.class.getName()))
      throw new IOException("Did not find a Scene Descriptor." +
                            "\nInstead found: " + type);

    SceneDescriptor scene;
    while(true)
    {
      try
      {
        scene = new SceneDescriptor();
        scene.read(bis);
        add(scene);
      }
      catch(EOFException ex)
      {
        break;
      }
    }

    fis.close();
  }

  /**
   * Get a script file from the user
   */
  public static File getScriptFile(JFileChooser chooser,
                                   Frame owner, String action)
  {
    // Get the file from the user.

    chooser.updateUI();
    chooser.setFileFilter(filter);
    
    int result = chooser.showDialog(owner, action);
    if(result != JFileChooser.APPROVE_OPTION)
      return null;

    File file = chooser.getSelectedFile();

    //
    // $$HACK: The file chooser returns a sun.awt.shell.DefaultShellFolder
    //         which is an implementation of java.io.File.  However, to
    //         use this object with the Constructor.newInstance() method
    //         it must be converted to a java.io.File.
    //

    return new File(file.getPath());
  }

  /**
   * Return the viewer class type of the script file, xfile.
   */
  public static Class readViewerType(File xfile) throws IOException,
        ClassNotFoundException
  {
    FileInputStream fis = new FileInputStream(xfile);
    BufferedInputStream bis = new BufferedInputStream(fis);
    String type = readCell(bis);
    fis.close();

    return Class.forName(type);
  }

  /**
   * Clone this <code>Script</code>.
   *
   * @param xscenes Include the scenes in the clone.
   */
  public synchronized Script clone(boolean xscenes)
  {
    Script result = new Script(viewer);

    result.minTime = minTime;
    result.maxTime = maxTime;
    result.unit = new String(unit);
    result.rate = rate;

    if(xscenes)
    {
      for(int i=0; i<size(); i++)
      {
        result.add(this.get(i).clone());
      }
    }

    return result;
  }

  /**
   * Clone this <code>Script</code> with the scenes.
   */
  public synchronized Script clone()
  {
    return clone(true);
  }

  /**
   * Return the closest scene index to the time, xtime.
   */
  public synchronized int getScene(double xtime)
  {
    int result = 0;
    SceneDescriptor scene = this.get(0);

    double diff = Math.abs(scene.time - xtime);

    double tempDiff;
    for(int i=1; i<size(); i++)
    {
      scene = get
                (i);
      tempDiff = Math.abs(scene.time - xtime);

      if(tempDiff < diff)
      {
        result = i;
        diff = tempDiff;
      }
    }

    return result;
  }

  /**
   * Return the closest <code>SceneDescriptor</code> to the time, xtime
   */
  public synchronized SceneDescriptor get(double xtime)
  {
    return get(getScene(xtime));
  }

  /**
   * Return the last scene.
   */
  public synchronized int lastScene()
  {
    return size()-1;
  }

  /**
   * Synchronized implementation of <code>ArrayList.toArray()</code>.
   */
  public synchronized Object[] toArray()
  {
    return super.toArray();
  }

  /**
   * Interpolate this <code>Script</code>
   */
  public void interpolate()
  {
    // SCRIPT FACET

    boolean shortInterpolation =
      (interpolation == ViewerConstants.SHORT_INTERPOLATION);

    // SCENE FACET

    SceneDescriptor scene = get(0);

    int f1 = -1;
    int f2 = -1;

    SceneDescriptor s1 = null;
    SceneDescriptor s2 = null;

    // CAMERA FACET

    Iterator<CameraDescriptor> citr1;
    Iterator<CameraDescriptor> citr2;

    CameraDescriptor c1;
    CameraDescriptor c2;

    double[][][] cameraIncrements = new double[scene.cameras.size()][][];

    // LIGHT FACET

    Iterator<LightDescriptor> litr1;
    Iterator<LightDescriptor> litr2;

    LightDescriptor l1;
    LightDescriptor l2;

    double[][][] lightIncrements = new double[scene.lights.size()][][];

    // ACTOR FACET

    Iterator<FieldActorDescriptor> aitr1;
    Iterator<FieldActorDescriptor> aitr2;

    FieldActorDescriptor a1;
    FieldActorDescriptor a2;

    double[][][] actorIncrements = new double[scene.actors.size()][][];

    for(int i=0; i<size(); i++)
    {
      scene = get
                (i);
      if(scene.keyFrame)
      {
        if(f1 < 0)
        {
          // Mark the first key frame.

          f1 = i;
          s1 = scene;
        }
        else
        {
          // Do the interpolation between key frames.

          f2 = i;
          s2 = scene;

          int steps = f2 - f1;

          // Calculate the interpolation increments

          // CAMERA FACET

          citr1 = s1.cameras.iterator();
          citr2 = s2.cameras.iterator();
          int idx = 0;
          while(citr1.hasNext())
          {
            c1 = citr1.next();
            c2 = citr2.next();

            cameraIncrements[idx] =
              c2.calcIncrements(c1, shortInterpolation, steps);

            idx++;
          }

          // LIGHT FACET

          litr1 = s1.lights.iterator();
          litr2 = s2.lights.iterator();
          idx = 0;
          while(litr1.hasNext())
          {
            l1 = litr1.next();
            l2 = litr2.next();

            lightIncrements[idx] =
              l2.calcIncrements(l1, shortInterpolation, steps);

            idx++;
          }

          // ACTOR FACET

          aitr1 = s1.actors.iterator();
          aitr2 = s2.actors.iterator();
          idx = 0;
          while(aitr1.hasNext())
          {
            a1 = aitr1.next();
            a2 = aitr2.next();

            actorIncrements[idx] =
              a2.calcIncrements(a1, shortInterpolation, steps);

            idx++;
          }

          // Interpolate

          int step;
          for(int j=f1+1; j<=f2-1; j++)
          {
            step = j-f1;

            // CAMERA FACET

            citr1 = s1.cameras.iterator();
            citr2 = get(j).cameras.iterator();
            idx = 0;
            while(citr1.hasNext())
            {
              c1 = citr1.next();
              c2 = citr2.next();

              c2.interpolate(c1, cameraIncrements[idx], step);

              idx++;
            }

            // LIGHT FACET

            litr1 = s1.lights.iterator();
            litr2 = get(j).lights.iterator();
            idx = 0;
            while(litr1.hasNext())
            {
              l1 = litr1.next();
              l2 = litr2.next();

              l2.interpolate(l1, lightIncrements[idx], step);

              idx++;
            }

            // ACTOR FACET

            aitr1 = s1.actors.iterator();
            aitr2 = get(j).actors.iterator();
            idx = 0;
            while(aitr1.hasNext())
            {
              a1 = aitr1.next();
              a2 = aitr2.next();

              a2.interpolate(a1, actorIncrements[idx], step);

              idx++;
            }
          }

          // Set the first key frame to the second frame.

          f1 = f2;
          s1 = s2;
        }
      }
      else if(f1 >= 0)
      {
        // Copy the member descriptor values of the last key
        // frame scene into the current scene.

        // CAMERA FACET

        citr1 = s1.cameras.iterator();
        citr2 = scene.cameras.iterator();

        while(citr1.hasNext())
        {
          c1 = citr1.next();
          c2 = citr2.next();

          c2.copy(c1);
        }

        // LIGHT FACET

        litr1 = s1.lights.iterator();
        litr2 = scene.lights.iterator();

        while(litr1.hasNext())
        {
          l1 = litr1.next();
          l2 = litr2.next();

          l2.copy(l1);
        }

        // ACTOR FACET

        aitr1 = s1.actors.iterator();
        aitr2 = scene.actors.iterator();

        while(aitr1.hasNext())
        {
          a1 = aitr1.next();
          a2 = aitr2.next();

          a2.copy(a1);
        }

        // Reset the time of the scene so that
        // the members have the correct time.

        scene.setTime(scene.time);
      }
    }
  }

  /**
   * Write <code>Script</code> to xfile.
   */
  public synchronized void write(File xfile) throws IOException
  {
    FileOutputStream fos = new FileOutputStream(xfile);
    BufferedOutputStream bos = new BufferedOutputStream(fos);

    // Write the script values

    write(viewer.getClass().getName(), bos);
    writeSeparator(bos);
    write(minTime, bos);
    writeSeparator(bos);
    write(maxTime, bos);
    writeSeparator(bos);
    write(unit, bos);
    writeSeparator(bos);
    write(rate, bos);
    writeSeparator(bos);
    write(interpolation, bos);
    writeNewLine(bos);

    // Write the scenes

    SceneDescriptor scene;
    for(int i=0; i<size(); i++)
    {
      scene = this.get(i);
      Script.write(scene.getClass().getName(), bos);
      Script.writeSeparator(bos);
      scene.write(bos);
      writeNewLine(bos);
    }

    // Close the stream.

    bos.close();
  }

  // WRITE UTILITY FACET

  /**
   * Write new line to xout
   */
  public static void writeNewLine(OutputStream xout) throws IOException
  {
    write("\n", xout);
  }

  /**
   * Write comma separator to xout
   */
  public static void writeSeparator(OutputStream xout) throws IOException
  {
    write(",", xout);
  }

  /**
   * Write the xvalue to xout.
   */
  public static void write(double xvalue,
                           OutputStream xout) throws IOException
  {
    write(Double.toString(xvalue), xout);
  }

  /**
   * Write the xvalue to xout.
   */
  public static void write(int xvalue,
                           OutputStream xout) throws IOException
  {
    write(Integer.toString(xvalue), xout);
  }

  /**
   * Write the xvalue to xout.
   */
  public static void write(boolean xvalue,
                           OutputStream xout) throws IOException
  {
    write(Boolean.toString(xvalue), xout);
  }

  /**
   * Write the xvalue to xout.
   */
  public static void write(Color xvalue,
                           OutputStream xout) throws IOException
  {
    // Store color as a hex string.

    String red = Integer.toHexString(xvalue.getRed());
    String green = Integer.toHexString(xvalue.getGreen());
    String blue = Integer.toHexString(xvalue.getBlue());

    if(red.length() != 2)
      red = "0"+red;
    if(green.length() != 2)
      green = "0"+green;
    if(blue.length() != 2)
      blue = "0"+blue;

    String hex = "#" + red + green + blue;

    write(hex, xout);
  }

  /**
   * Write the xvalue to xout.
   */
  public static void write(String xvalue,
                           OutputStream xout) throws IOException
  {
    xout.write(xvalue.getBytes(), 0, xvalue.length());
  }

  // READ UTITLITY FACET

  /**
   * Read a double cell
   */
  public static double readDouble(InputStream input) throws IOException
  {
    String value = readCell(input);

    Double doubleValue;

    try
    {
      doubleValue = Double.parseDouble(value);
    }
    catch(Exception e)
    {
      throw new IOException("Invalid Double Value: " + value);
    }

    return doubleValue;
  }

  /**
   * Read a int cell
   */
  public static int readInt(InputStream input) throws IOException
  {
    String value = readCell(input);

    Integer intValue;

    try
    {
      intValue = Integer.parseInt(value);
    }
    catch(Exception e)
    {
      throw new IOException("Invalid Integer Value: " + value);
    }

    return intValue;
  }

  /**
   * Read a boolean cell
   */
  public static boolean readBoolean(InputStream input) throws IOException
  {
    String value = readCell(input);

    Boolean booleanValue;

    try
    {
      booleanValue = Boolean.parseBoolean(value);
    }
    catch(Exception e)
    {
      throw new IOException("Invalid Boolean Value: " + value);
    }

    return booleanValue;
  }

  /**
   * Read a color cell
   */
  public static Color readColor(InputStream input) throws IOException
  {
    String value = readCell(input);

    int start = 0;
    if(value.startsWith("#"))
      start = 1;

    if(value.length() != 6+start)
      throw new IOException("Color must be a hex string: " + value);

    String red = value.substring(start, start+2);
    String green = value.substring(start+2, start+4);
    String blue = value.substring(start+4);

    Color color;

    try
    {
      int r = Integer.parseInt(red, 16);
      int g = Integer.parseInt(green, 16);
      int b = Integer.parseInt(blue, 16);

      color = new Color(r, g, b);
    }
    catch(Exception e)
    {
      throw new IOException("Invalid Hex Color: " + value);
    }

    return color;
  }

  /**
   * Read a cell within the script
   */
  public static String readCell(InputStream input) throws IOException
  {
    int i;
    char c;
    StringBuffer result = new StringBuffer();
    while(true)
    {
      i = input.read();
      if(i < 0)
        throw new EOFException();

      c = (char) i;

      if(c == '\n')
      {
        // Hit the end of the cell.

        break;
      }
      else if(c == ',')
      {
        // Hit the end of the cell.

        break;
      }
      else if(c != '"')
      {
        // Ignore quotes because open office will add quotes
        // around a string.

        result.append(c);
      }
    }

    return result.toString().trim();
  }
}
