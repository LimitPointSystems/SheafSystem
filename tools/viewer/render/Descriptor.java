
/**
 * Classname: Descriptor
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.render;

import tools.viewer.animation.*;
import tools.viewer.common.*;

import java.awt.*;
import java.io.*;

/**
 *
 * Base class for the descriptor structs.  Handles the hash code.
 *
 */
public abstract class Descriptor
{
  // DESCRIPTOR FACET

  /**
   * Selected flag
   */
  public boolean selected = false;

  /**
   * The time
   */
  public double time = 0.0;

  /**
   * Set the time
   */
  public void setTime(double xtime)
  {
    time = xtime;
  }

  /**
   * Read the values of this <code>Descriptor</code> from xinput
   */
  public void read(InputStream xinput) throws IOException
  {
    selected = Script.readBoolean(xinput);
    time = Script.readDouble(xinput);
  }

  /**
   * Write this <code>Descriptor</code> to xout.
   */
  public void write(OutputStream xout) throws IOException
  {
    Script.write(selected, xout);
    Script.writeSeparator(xout);
    Script.write(time, xout);
  }

  /**
   * Forces the <code>Descriptor</code> to override the
   * hashCode() method.
   */
  public abstract int hashCode();

  /**
   * Forces the <code>Descriptor</code> to override the
   * equals(Object obj) method.
   */
  public abstract boolean equals(Object obj);

  // UTILITY FACET

  /**
   * Utility function for comparing the values of a two double arrays
   */
  public boolean compare(double[] a1, double[] a2)
  {
    if(a1.length != a2.length)
      return false;

    for(int i=0; i<a1.length; i++)
    {
      if(a1[i] != a2[i])
        return false;
    }

    return true;
  }
}
