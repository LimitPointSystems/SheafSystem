
/**
 *      Classname: LPSDebug
 *
 *      @author $Author: jebutler $
 *
 *      @version $RCSfile: LPSDebug.java,v $ $Revision: 1.11 $
 *
 *      $Date: 2013/01/12 17:17:55 $
 *
 *      Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.util;

import java.io.*;
import java.util.*;

/**
 *  Class providing static methods for use in debugging.
 */
public class LPSDebug
{
  private static boolean enabled = true;

  /**
   *  Constructor. Private so it can not be instantiated.
   */
  private LPSDebug()
  {}

  /**
   *  Enable or disable debug printing.
   */
  public static void setEnabled(boolean enabled)
  {
    LPSDebug.enabled = enabled;
  }

  /**
   *  Prints a specified message to standard out with the
   *  message prepended by the class name, method name,
   *  file name, and line number.
   */
  public static void print(String message)
  {
    if(enabled)
    {
      String location = getLocationInClass(3);
      System.out.print(location + ": " + message);
    }
  }

  /**
   *  Prints the class name, method name,
   *  file name, and line number to standard out.
   */
  public static void print()
  {
    if(enabled)
    {
      String location = getLocationInClass(3);
      System.out.print(location);
    }
  }

  /**
   *  Prints a specified message to standard out with the
   *  message prepended by the class name, method name,
   *  file name, and line number.
   */
  public static void println(String message)
  {
    if(enabled)
    {
      String location = getLocationInClass(3);
      System.out.println(location + ": " + message);
    }
  }

  /**
   *  Prints the class name, method name,
   *  file name, and line number to standard out.
   */
  public static void println()
  {
    if(enabled)
    {
      String location = getLocationInClass(3);
      System.out.println(location);
    }
  }


  /**
   *  Get a <code>String</code> representation of the stack trace.
   *
   *  @param e A <code>Throwable</code> object.
   *  @return The <code>String</code> representation.
   */
  public static String stackTraceToString(Throwable e)
  {
    try
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream(1024);
      PrintWriter pw = new PrintWriter(baos, true);
      e.printStackTrace(pw);
      return baos.toString();
    }
    catch(Exception ex)
    {
      return "Error getting stack trace: " + ex;
    }
  }

  /**
   *
   */
  public static String getLocationInClass(Throwable e, int level)
  {
    try
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream(1024);
      PrintWriter pw = new PrintWriter(baos, true);
      e.printStackTrace(pw);

      String s = baos.toString();

      StringTokenizer st = new StringTokenizer(s, "\n");

      for(int i=0; i<level; i++)
        st.nextToken();

      String line = st.nextToken();
      int begin = line.indexOf("at ") + 3;
      String result = line.substring(begin);

      return result;

    }
    catch(Exception ex)
    {
      return "Error getting location: " + ex;
    }
  }

  /**
   *
   */
  public static String getLocationInClass(int level)
  {
    Error e = new Error();
    return getLocationInClass(e, level);
  }

  /**
   *
   */
  public static String getLocationInClass()
  {
    return getLocationInClass(2);
  }

}
