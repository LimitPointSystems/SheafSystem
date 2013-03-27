/**
 *  Classname: LPSMath
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: LPSMath.java,v $ $Revision: 1.9 $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.util;

import java.awt.*;

/**
 * Math utilities.
 */
public class LPSMath
{
  /**
   * Convert from xyz coordinates to polar coordinates
   */
  public static double[] xyzToPolar(double[] xyz, double[] result)
  {
    double rad2deg = 180.0/Math.PI;

    result[2] = Math.sqrt(xyz[0] * xyz[0] +
                          xyz[1] * xyz[1] +
                          xyz[2] * xyz[2]);

    result[0] = 90.0 - (Math.acos(xyz[2] / result[2]) * rad2deg);

    result[1] = Math.atan2(xyz[1], xyz[0]) * rad2deg;

    return result;
  }

  /**
   * Conver from polar coordinates to xyz coordinates.
   */
  public static void polarToXYZ(double[] polar, double[] result)
  {
    double deg2rad = Math.PI/180.0;
    double phi = (90.0 - polar[0])*deg2rad;
    double theta = polar[1]*deg2rad;

    double r_sin_phi = polar[2]*Math.sin(phi);

    result[0] = r_sin_phi*Math.cos(theta);
    result[1] = r_sin_phi*Math.sin(theta);
    result[2] = polar[2]*Math.cos(phi);
  }

  /**
   * Calculate the increment for linear polar interpolation
   */
  public static void calcPolarIncrement(double result[], double[] d1,
                                        double[] d2, boolean xshort, int steps)
  {
    double[] diff = calcPolarDiff(d1, d2, xshort);

    result[0] = diff[0]/(double) steps;
    result[1] = diff[1]/(double) steps;
    result[2] = diff[2]/(double) steps;
  }

  /**
   * Calculate the difference for linear polar interpolation.
   */
  public static double[] calcPolarDiff(double[] d1, double[] d2, boolean xshort)
  {
    double[] p1 = new double[3];
    xyzToPolar(d1, p1);

    double[] p2 = new double[3];
    xyzToPolar(d2, p2);


    double[] diff = new double[3];

    if(xshort)
    {
      diff[0] = p2[0] - p1[0];
      diff[1] = p2[1] - p1[1];
      diff[2] = p2[2] - p1[2];
    }
    else
    {
      diff[0] = p2[0] - p1[0];
      diff[1] = p2[1] - p1[1];
      if(diff[1] > 0)
        diff[1] = diff[1] - 360.0;
      else
        diff[1] = 360.0 + diff[1];
      diff[2] = p2[2] - p1[2];
    }

    return diff;
  }

  /**
   * Calculate the increment for linear interpolation
   */
  public static void calcLinearIncrement(double result[], double[] d1,
                                         double[] d2, int steps)
  {
    double[] diff = calcLinearDiff(d1, d2);

    result[0] = diff[0]/(double) steps;
    result[1] = diff[1]/(double) steps;
    result[2] = diff[2]/(double) steps;
  }

  /**
   * Calculate the difference for linear intepolation
   */
  public static double[] calcLinearDiff(double[] d1, double[] d2)
  {
    double[] diff = new double[3];
    diff[0] = d2[0] - d1[0];
    diff[1] = d2[1] - d1[1];
    diff[2] = d2[2] - d1[2];

    return diff;
  }

  /**
   * Calculate the incremented linear polar interpolation values
   */
  public static void incrementPolar(double[] result, double[] start,
                                    double[] increment, int step)
  {
    double[] pstart = new double[3];
    xyzToPolar(start, pstart);
    double[] presult = new double[3];

    presult[0] = pstart[0] + (increment[0] * (double) step);
    presult[1] = pstart[1] + (increment[1] * (double) step);
    presult[2] = pstart[2] + (increment[2] * (double) step);

    polarToXYZ(presult, result);
  }

  /**
   * Calculate the incremented linear interpolation values
   */
  public static void incrementLinear(double[] result, double[] start,
                                     double[] increment, int step)
  {
    result[0] = start[0] + (increment[0] * (double) step);
    result[1] = start[1] + (increment[1] * (double) step);
    result[2] = start[2] + (increment[2] * (double) step);
  }

  /**
   * The rgb values from hue, saturation, intensity.
   */
  public static double[] getRGB(double hue,
                                double saturation,
                                double intensity)
  {
    double[] result = new double[3];

    // Make sure all values in range.

    if(hue < 0.0)
      hue = 1.0 + hue;
    else if(hue > 1.0)
      hue = hue - 1.0;

    if(saturation < 0.0)
      saturation = 0.0;
    else if(saturation > 1.0)
      saturation = 1.0;

    if(intensity < 0.0)
      intensity = 0.0;
    else if(intensity > 1.0)
      intensity = 1.0;

    int rgb = Color.HSBtoRGB((float) hue, (float) saturation, (float) intensity);
    Color color = new Color(rgb);
    result[0] = (double) color.getRed() / 255.0;
    result[1] = (double) color.getGreen() / 255.0;
    result[2] = (double) color.getBlue() / 255.0;

    return result;
  }
}
