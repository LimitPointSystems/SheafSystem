
/**
 * Classname: AnimationThread
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: MovieHeader.java,v $ $Revision: 1.8 $
 *
 * $Date: 2013/01/12 17:17:56 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.animation;

import bindings.java.*;
import tools.viewer.common.*;
import java.io.*;
import java.util.*;
import javax.media.*;

/**
 *
 * Class for writing an animation to a quick time file.
 *
 */
public class MovieHeader
{
  /**
   * The movie header file
   */
  private File file;

  /**
   * The start time
   */
  private double start = -1.0;

  /**
   * The end time
   */
  private double end = -1.0;

  /**
   * The media end
   */
  private double mediaEnd = -1.0;

  /**
   * The constructor
   *
   * @param xfile The file
   */
  public MovieHeader(File xfile)
  {
    file = xfile;
  }

  /**
   * The start time
   */
  public double getStartTime()
  {
    return start;
  }

  /**
   * The end time
   */
  public double getEndTime()
  {
    return end;
  }

  /**
   * The media end
   */
  public double getMediaEnd()
  {
    return mediaEnd;
  }

  /**
   * Write the movie header file.
   */
  public void write(double xstart, double xend, double sceneRate, int scenes) throws IOException
  {
    start = xstart;
    end = xend;

    // Calcluate the media end time

    double mediaEnd = ((double) scenes)/sceneRate;

    String text = Double.toString(start) + "," +
                  Double.toString(end) + "," + Double.toString(mediaEnd);

    FileOutputStream fos = new FileOutputStream(file);
    fos.write(text.getBytes(), 0, text.length());
    fos.close();
  }

  /**
   * Read the movie header file
   */
  public void read() throws IOException
  {
    FileInputStream fis = new FileInputStream(file);
    byte[] buffer = new byte[(int) file.length()];
    fis.read(buffer);

    String text = new String(buffer);
    StringTokenizer tok = new StringTokenizer(text, ",", false);
    if(tok.countTokens() != 3)
      throw new IOException("Invalid Movie Header File.");

    start = Double.parseDouble(tok.nextToken());
    end = Double.parseDouble(tok.nextToken());
    mediaEnd = Double.parseDouble(tok.nextToken());
  }

  /**
   * Returns the header file name based on the movie file name
   */
  public static File getFile(File xmovieFile)
  {
    String name = xmovieFile.getName();
    if(!name.endsWith(".mov"))
      return null;

    String base = name.substring(0, name.indexOf(".mov"));
    File headerFile = new File(xmovieFile.getParent(), base + ".mhr");

    return headerFile;
  }

  /**
   * Calculate the real time from the given media time
   * Return the value as a String
   */
  public String calculate(Time mediaTime)
  {
    if(start<0.0 || end<0.0 || mediaEnd<0.0)
      return "N/A";

    double current = mediaTime.getSeconds();

    double percent;

    if(current < 0.0)
    {
      percent = 0.0;
    }
    else if(current > mediaEnd)
    {
      percent = 1.0;
    }
    else
    {
      percent = mediaTime.getSeconds()/mediaEnd;
    }

    double value = (end-start)*percent;

    String result = Double.toString(value);

    int idx = result.indexOf(".");
    if(idx+3 < result.length())
    {
      result = result.substring(0,  idx+3);
    }

    return result;
  }
}
