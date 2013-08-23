
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
