
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

package com.limitpoint.tools.common.gui;

import com.limitpoint.bindings.java.base_client;
import java.util.*;
import java.io.*;

/**
 * LPSApp.  Class designed to serve as a base class for LPS applications.
 * The functionality of this class will be enhanced as the requirements
 * of derived classes evolve.
 */

public class LPSApp extends base_client
{
  //$$TODO: Temporarily commented out.  Activate when
  //        we decide how we should handle multiple enviroment
  //        variable names for multiple LD_LIBRARY_PATHs, CLASSPATHS,
  //        etc.

  //   /**
  //    *
  //    */
  //   static
  //   {
  //     // Make sure that the LPS script which sets the environment variable
  //     // "LPS_SCRIPT_HAS_RUN" has been executed.

  //     checkLPSScriptHasRun();
  //   }

  /**
   *
   */
  static private Properties props = new Properties();

  /**
   *
   */
  protected LPSApp()
  {}

  /**
   *
   */
  public void loadProperties(InputStream inStream)
  {
    try
    {
      props.load(inStream);
    }
    catch(IOException e)
    {
      e.printStackTrace();
    }
  }

  /**
   *
   */
  public static Properties getProperties()
  {
    return props;
  }

  /**
   *
   */
  public static String getProperty(String xkey)
  {
    return (String)props.get(xkey);
  }

  /**
   *
   */
  public static String setProperty(String xkey, String xvalue)
  {
    return (String)props.put(xkey, xvalue);
  }

  /**
   *
   */
  public static String removeProperty(String xkey)
  {
    return (String)props.remove(xkey);
  }

  /**
   *
   */
  public static void checkLPSScriptHasRun()
  {
    // Check to see if the environment variable LPS_SCRIPT_HAS_RUN
    // has been set.  If not, exit with an exception;
    // otherwise do nothing.

    if(System.getenv("LPS_SCRIPT_HAS_RUN") == null)
    {
      System.out.println("LPS script has not been executed.");
      System.exit(1);
    }
  }

  /**
   *
   */
  public static void loadLibrary(String xname)
  {
    try
    {
      System.loadLibrary(xname);
    }
    catch(Error e)
    {
      System.out.println(e);
      e.printStackTrace();
      System.out.println("ERROR: lib" + xname +".so didn't load.");
      System.exit(1);
    }
  }

}
