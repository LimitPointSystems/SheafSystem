
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

import bindings.java.*;
import tools.viewer.animation.*;
import tools.viewer.common.*;
import tools.common.util.*;

import java.awt.*;
import java.io.*;

import vtk.*;

/**
 *
 * Struct which describes a range based <code>LookupTable</code>
 *
 */
public class RangeLookupTableDescriptor extends LookupTableDescriptor
{
  // RANGE_LOOKUP_TABLE_DESCRIPTOR FACET

  /**
   * The extreme hues:  The minimum hue value (0.677 - blue).
   * The maximum hue value (0.0 - red)
   */
  public double[] extremeHues =
    { 0.677, 0.0 };

  /**
   * The threshold sizes as a percentage.
   */
  public double[] thresholdSizes =
    { 0.0, 0.0 };

  /**
   * The components for the thresholds
   */
  public String[] thresholdComponents =
    { ViewerConstants.INTENSITY, ViewerConstants.SATURATION };

  /**
   * The components' methods for the thresholds
   */
  public String[] componentMethods =
    { ViewerConstants.RAMP, ViewerConstants.RAMP };

  /**
   * The extreme value of the components
   */
  public double[] extremeComponentValues =
    { 0.0, 0.0 };

  /**
   * The components' extreme hue methods for the thresholds
   */
  public String[] extremeHueMethods =
    { ViewerConstants.CONSTANT, ViewerConstants.CONSTANT };

  /**
   * Default constructor
   */
  public RangeLookupTableDescriptor()
  {}

  // LOOKUP_TABLE_DESCRIPTOR FACET

  /**
   * Clone this <code>RangeLookupTableDescriptor</code>
   */
  public synchronized LookupTableDescriptor clone()
  {
    RangeLookupTableDescriptor result = new RangeLookupTableDescriptor();

    result.copy(this);

    return result;
  }

  /**
   * Copy the values of xlookupTable into this
   * <code>RangeLookupTableDescriptor</code>.
   */
  public synchronized void copy(LookupTableDescriptor xlookupTable)
  {
    // DESCRIPTOR FACET

    selected = xlookupTable.selected;
    time = xlookupTable.time;

    // RANGE LOOKUP TABLE DESCRIPTOR FACET

    RangeLookupTableDescriptor rangeLookupTable =
      (RangeLookupTableDescriptor) xlookupTable;

    extremeHues[0] = rangeLookupTable.extremeHues[0];
    extremeHues[1] = rangeLookupTable.extremeHues[1];
    thresholdSizes[0] = rangeLookupTable.thresholdSizes[0];
    thresholdSizes[1] = rangeLookupTable.thresholdSizes[1];
    thresholdComponents[0] = rangeLookupTable.thresholdComponents[0];
    thresholdComponents[1] = rangeLookupTable.thresholdComponents[1];
    componentMethods[0] = rangeLookupTable.componentMethods[0];
    componentMethods[1] = rangeLookupTable.componentMethods[1];
    extremeComponentValues[0] = rangeLookupTable.extremeComponentValues[0];
    extremeComponentValues[1] = rangeLookupTable.extremeComponentValues[1];
    extremeHueMethods[0] = rangeLookupTable.extremeHueMethods[0];
    extremeHueMethods[1] = rangeLookupTable.extremeHueMethods[1];
  }

  /**
   * Build a <code>LookupTable</code> from this
   * <code>LookupTableDescriptor</code>.
   */
  public synchronized LookupTable build(namespace_poset xnamespace)
  {
    LookupTable result = new LookupTable();
    update(result, null);

    return result;
  }

  /**
   * Update xlookupTable to this <code>LookupTableDescriptor</code>
   */
  public synchronized void update(LookupTable xlookupTable,
                                  LookupTableDescriptor xdescriptor)
  {
    RangeLookupTableDescriptor descriptor = (RangeLookupTableDescriptor) xdescriptor;

    if(xdescriptor == null || !equals(descriptor))
    {
      // Set the total number of colors in the lookup table.

      int numColors = 256;
      xlookupTable.SetNumberOfTableValues(numColors);

      // Calculate the number of colors in each section of the table.
      // Three sections. min threshold, hue rame, max threshold.

      int colorsInMinThreshold =
        (int) ((double) numColors * thresholdSizes[0]);
      int colorsInMaxThreshold =
        (int) ((double) numColors * thresholdSizes[1]);

      int colorsBetweenThresholds =
        numColors - (colorsInMinThreshold + colorsInMaxThreshold);

      // Calcaulate the number of colors in the hue ramep.  Depends
      // if the hue is ramped in the threshold.

      int numRampColors = colorsBetweenThresholds;
      if(extremeHueMethods[0].equals(ViewerConstants.RAMP))
        numRampColors += colorsInMinThreshold;
      if(extremeHueMethods[1].equals(ViewerConstants.RAMP))
        numRampColors += colorsInMaxThreshold;

      // Calculate the hue incrmement.

      double hueIncrement =
        (extremeHues[0] - extremeHues[1])/(double) numRampColors;

      // MIN THRESHOLD FACET


      // Calculate the initial hue, saturation and intensity values and
      // do increment flags.

      boolean doIncrementHue =
        extremeHueMethods[0].equals(ViewerConstants.RAMP);
      double hue = extremeHues[0];

      boolean isSaturation =
        thresholdComponents[0].equals(ViewerConstants.SATURATION);
      boolean doIncrementSaturation =
        (isSaturation && componentMethods[0].equals(ViewerConstants.RAMP));
      double saturation = isSaturation ? extremeComponentValues[0] : 1.0;

      boolean doIncrementIntensity =
        (!isSaturation && componentMethods[0].equals(ViewerConstants.RAMP));
      double intensity = isSaturation ? 1.0 : extremeComponentValues[0];

      // Calculate the the value increment.

      double valueIncrement =
        ((1.0 - extremeComponentValues[0]) /
         (double) colorsInMinThreshold);

      int color = 0;

      for(int i=0; i<colorsInMinThreshold; i++)
      {
        // Increment values.

        if(doIncrementHue)
          hue -= hueIncrement;

        if(doIncrementSaturation)
          saturation += valueIncrement;

        if(doIncrementIntensity)
          intensity += valueIncrement;

        // Set the lookup table value.

        double[] rgb = LPSMath.getRGB(hue, saturation, intensity);
        xlookupTable.SetTableValue(color, rgb[0], rgb[1], rgb[2], 1.0);
        color++;
      }

      // HUE RAMP FACET


      // Initialize values

      saturation = 1.0;
      intensity = 1.0;

      for(int i=0; i<colorsBetweenThresholds; i++)
      {
        // Increment in hue.

        hue -= hueIncrement;

        // Set the lookup table value.

        double[] rgb = LPSMath.getRGB(hue, saturation, intensity);
        xlookupTable.SetTableValue(color, rgb[0], rgb[1], rgb[2], 1.0);
        color++;

        // In case of rounding problems.

        if(color >= numColors)
          break;
      }


      // MAX THRESHOLD FACET


      // Calculate the initial hue, saturation and intensity values and
      // do increment flags.

      doIncrementHue =
        extremeHueMethods[1].equals(ViewerConstants.RAMP);

      isSaturation =
        thresholdComponents[1].equals(ViewerConstants.SATURATION);
      doIncrementSaturation =
        (isSaturation && componentMethods[1].equals(ViewerConstants.RAMP));

      doIncrementIntensity =
        (!isSaturation && componentMethods[1].equals(ViewerConstants.RAMP));

      // Calculate the the value increment.

      valueIncrement =
        ((1.0 - extremeComponentValues[1]) /
         (double) colorsInMaxThreshold);

      // Set constant value

      if(componentMethods[1].equals(ViewerConstants.CONSTANT))
        if(isSaturation)
          saturation = extremeComponentValues[1];
        else
          intensity = extremeComponentValues[1];

      for(int i=0; i<colorsInMaxThreshold; i++)
      {
        // Increment values.

        if(doIncrementHue)
          hue -= hueIncrement;

        if(doIncrementSaturation)
          saturation -= valueIncrement;

        if(doIncrementIntensity)
          intensity -= valueIncrement;

        // Set the lookup table value.

        double[] rgb = LPSMath.getRGB(hue, saturation, intensity);
        xlookupTable.SetTableValue(color, rgb[0], rgb[1], rgb[2], 1.0);
        color++;

        // In case of rounding problems.

        if(color >= numColors)
          break;
      }
    }
  }

  // DESCRIPTOR FACET

  /**
   * Read the values of this <code>RangeLookupTableDescriptor</code> from xinput
   */
  public synchronized void read(InputStream xinput)
  throws IOException
  {
    super.read(xinput);

    extremeHues[0] = Script.readDouble(xinput);
    extremeHues[1] = Script.readDouble(xinput);
    thresholdSizes[0] = Script.readDouble(xinput);
    thresholdSizes[1] = Script.readDouble(xinput);
    thresholdComponents[0] = Script.readCell(xinput);
    thresholdComponents[1] = Script.readCell(xinput);
    componentMethods[0] = Script.readCell(xinput);
    componentMethods[1] = Script.readCell(xinput);
    extremeComponentValues[0] = Script.readDouble(xinput);
    extremeComponentValues[1] = Script.readDouble(xinput);
    extremeHueMethods[0] = Script.readCell(xinput);
    extremeHueMethods[1] = Script.readCell(xinput);
  }

  /**
   * Write this <code>RangeLookupTableDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(extremeHues[0], xout);
    Script.writeSeparator(xout);
    Script.write(extremeHues[1], xout);
    Script.writeSeparator(xout);
    Script.write(thresholdSizes[0], xout);
    Script.writeSeparator(xout);
    Script.write(thresholdSizes[1], xout);
    Script.writeSeparator(xout);
    Script.write(thresholdComponents[0], xout);
    Script.writeSeparator(xout);
    Script.write(thresholdComponents[1], xout);
    Script.writeSeparator(xout);
    Script.write(componentMethods[0], xout);
    Script.writeSeparator(xout);
    Script.write(componentMethods[1], xout);
    Script.writeSeparator(xout);
    Script.write(extremeComponentValues[0], xout);
    Script.writeSeparator(xout);
    Script.write(extremeComponentValues[1], xout);
    Script.writeSeparator(xout);
    Script.write(extremeHueMethods[0], xout);
    Script.writeSeparator(xout);
    Script.write(extremeHueMethods[1], xout);
  }

  /**
   * Override the hashCode method.
   */
  public int hashCode()
  {
    int code = (int) ((extremeHues[0] * 255.0) +
                      (extremeHues[1] * 255.0) +
                      (thresholdSizes[0] * 100.0) +
                      (thresholdSizes[1] * 100.0) +
                      thresholdComponents[0].hashCode() +
                      thresholdComponents[1].hashCode() +
                      componentMethods[0].hashCode() +
                      componentMethods[1].hashCode() +
                      (extremeComponentValues[0] * 100.0) +
                      extremeHueMethods[0].hashCode() +
                      (extremeComponentValues[1] * 100.0) +
                      extremeHueMethods[1].hashCode());

    return code;
  }

  /**
   * Override the equals method.  This is a test of equivalence.
   */
  public boolean equals(Object obj)
  {
    if(!(obj instanceof RangeLookupTableDescriptor))
      return false;

    RangeLookupTableDescriptor input = (RangeLookupTableDescriptor) obj;

    if(input.extremeHues[0] != extremeHues[0])
      return false;

    if(input.extremeHues[1] != extremeHues[1])
      return false;

    if(input.thresholdSizes[0] != thresholdSizes[0])
      return false;

    if(input.thresholdSizes[1] != thresholdSizes[1])
      return false;

    if(!input.thresholdComponents[0].equals(thresholdComponents[0]))
      return false;

    if(!input.thresholdComponents[1].equals(thresholdComponents[1]))
      return false;

    if(!input.componentMethods[0].equals(componentMethods[0]))
      return false;

    if(!input.componentMethods[1].equals(componentMethods[1]))
      return false;

    if(input.extremeComponentValues[0] != extremeComponentValues[0])
      return false;

    if(input.extremeComponentValues[1] != extremeComponentValues[1])
      return false;

    if(!input.extremeHueMethods[0].equals(extremeHueMethods[0]))
      return false;

    if(!input.extremeHueMethods[1].equals(extremeHueMethods[1]))
      return false;

    return true;
  }
}
