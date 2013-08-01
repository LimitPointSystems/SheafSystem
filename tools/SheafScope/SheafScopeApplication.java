/**
 * Classname: SheafScopeApplication
 *
 * @author $Author: jebutler $
 *
 *      $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package tools.SheafScope;

import bindings.java.*;
import tools.viewer.application.*;
import tools.viewer.common.*;
import tools.viewer.user.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import tools.common.gui.*;

/**
 * The main SheafScope application.
 */
public abstract class SheafScopeApplication extends base_client
      implements ViewerClientApplication
{
  //   public static int LOCAL = 0;
  //   public static int REMOTE = 1;

  public static final String DISPLAY_NO_DOFS = "Display No Dofs";
  public static final String DISPLAY_ALL_DOFS = "Display All Dofs";
  public static final String DISPLAY_LIMITED_DOFS = "Display Limited Dofs";

  public static final String[] DISPLAY_OPTIONS = {DISPLAY_NO_DOFS,
      DISPLAY_ALL_DOFS,
      DISPLAY_LIMITED_DOFS};

  protected static String APPLICATION_NAME = "SheafScope";
  //   protected static int runMode = LOCAL;
  //   protected static String host = null;
  //   protected static int port = -1;
  protected static boolean showStdNamespace = false;
  protected static String startupFileName = null;
  protected static boolean  enableRemoteX = false;
  protected static String scriptFileName = null;

  protected SheafScopeFrame frame;

  public static String dofDisplay = DISPLAY_LIMITED_DOFS;
  public static int dofLimit = 100;

  protected vtk_abstract_grid_builder gridBuilder;

  /**
   * Creates a <code>SheafScopeApplication</code> object for local execution.
   */
  public SheafScopeApplication(String xmodule)
  {
    //$$ISSUE: We have disabled the client/server option
    //         and changed the base_client CTOR/ So the following
    //         change is neccessary.

    //super(false, xmodule);
    super(xmodule);

    createGridBuilder();

    openApplication();

    Viewer.APPLICATION = this;
  }

  //   /**
  //    *  Creates a <code>SheafScopeApplication</code> object for remote execution.
  //    */
  //   public SheafScopeApplication(String xmodule, int xport, String xhost)
  //   {
  //     super(true, xmodule, xport, xhost);

  //     createGridBuilder();

  //     openApplication();

  //     Viewer.APPLICATION = this;
  //   }

  /**
   * Open the frame of this application.
   */
  protected void openApplication()
  {
    frame = new SheafScopeFrame(enableRemoteX,
                                showStdNamespace,
                                startupFileName,
				scriptFileName);
  }

  /**
   * The frame of the application
   */
  public Frame getFrame()
  {
    return frame;
  }

  /**
   * Construct a vtk grid builder for this application.
   */
  protected void createGridBuilder()
  {
    try
    {
      gridBuilder = new vtk_unstructured_grid_builder();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  // VIEWER CLIENT APPLICATION FACET

  /**
   * Bring application to the foreground
   */
  public void toForeground()
  {
    frame.setExtendedState(JFrame.NORMAL);
    frame.toFront();
    frame.createView();
  }

  /**
   * Get the <code>namespace_poset</code> for xname
   */
  public namespace_poset getNamespace(String xname)
  {
    return frame.getNamespace(xname);
  }

  /**
   * Get the grid builder
   */
  public vtk_abstract_grid_builder getGridBuilder()
  {
    return gridBuilder;
  }

  /**
   * Set the selected viewer
   */
  public void setSelectedViewer(Viewer xviewer)
  {
    frame.setSelectedViewer(xviewer);
  }

  // COMMAND LINE FACET

  /**
   *  Parse command line arguments.
   * 
   * @param xargs The scope's command line arguments.
   *
   * 
   */
  protected static void interpretCommandLineArgs(String xappName, String[] xargs)
  {
    //$$TODO: Decide if we want command line args permanently
    //        and, if so, what form they should take.

    if(xargs.length > 0)
    {
      for(int i=0;i<xargs.length;i++)
      {
        if("-std".equals(xargs[i]))
        {
          showStdNamespace = true;
        }
        //         else if("-local".equals(xargs[i]) )
        //         {
        //           if(runMode == REMOTE)
        //           {
        //             System.out.println("Invalid argument list: The -local option can not ");
        //             System.out.println("used with the -host or -port argument.\n");
        //             usage(xappName);
        //           }
        //           runMode = LOCAL;
        //         }
        //         else if("-host".equals(xargs[i]) )
        //         {
        //           runMode = REMOTE;
        //           i++;
        //           host = xargs[i];
        //         }
        //         else if("-port".equals(xargs[i]) )
        //         {
        //           runMode = REMOTE;
        //           i++;
        //           try
        //           {
        //             port = (new Integer(xargs[i].trim())).intValue();
        //           }
        //           catch(Exception ex)
        //           {
        //             System.out.println("Invalid port number: '" + xargs[i] + "'.\n");
        //             usage(xappName);
        //           }
        //         }
        else if("-r".equals(xargs[i]))
        {
          enableRemoteX = true;
        }
	else if("-s".equals(xargs[i]))
	{
          i++;
	  if(i < xargs.length)
	  {
            scriptFileName = xargs[i];
	  }
	  else
	  {
            usage(xappName);
	  }
	}
        else if("-help".equals(xargs[0]))
        {
          usage(xappName);
        }
        else
        {
          //$$ISSUE: Why was this here?  SheafScope exits in "usage"!
          //usage(xappName);

          startupFileName = xargs[i];
        }
      }
    }
    //     if((runMode == REMOTE) && (host == null || port == -1))
    //     {
    //       System.out.println("Invalid argument list: The -host and -port options ");
    //       System.out.println("must be used together to run remotely.\n");
    //       usage(xappName);
    //     }
  }

  /**
   * Print the help message.
   */
  public static void usage(String xappName)
  {
    System.out.println("  ");
    System.out.println(xappName + " --  Copyright (c) 2013 Limit Point Systems, Inc.");
    System.out.println(" ");
    System.out.println("Usage: java " + xappName + " [OPTION]... [FILE]...");
    System.out.println(" ");
    System.out.println("Examples: ");
    System.out.println(" java " + xappName + " ");
    System.out.println(" java " + xappName + " testfile.hdf");
    System.out.println(" java " + xappName + " -std");
    System.out.println(" java " + xappName + " -r testfile.hdf");
    System.out.println(" java " + xappName + " -s testscript.csv testfile.hdf");
    //     System.out.println(" java " + xappName + " -port 99 -host 111.11.111.1");
    System.out.println(" ");
    System.out.println("Main Operation Mode: ");
    //     System.out.println(" -local: Execute as a local client. [Default]");
    //     System.out.println(" -host [url]: Server host name for remote execution.");
    //     System.out.println(" -port [number]: Port number for remote execution.");
    //     System.out.println("  [-host] and [-port] options must be used together ");
    //     System.out.println("  and can not be used with the [-local] option. ");
    //     System.out.println(" ");
    System.out.println(" -r: Optimizes " + xappName + " for remote windowing. ");
    System.out.println("  Using this switch when displaying on a local");
    System.out.println("  terminal will dramatically reduce performance and");
    System.out.println("  is not recommended.");
    System.out.println(" ");
    System.out.println(" -std: Loads a Standard Namespace Poset. Ignored if a");
    System.out.println("  filename is present on the command line.");
    System.out.println(" ");
    System.out.println(" -s [script]: The name of the Viewer Script file to");
    System.out.println("  load after the Sheaf File is opened.");
    System.out.println(" ");
    System.out.println(" -help: Displays this screen.");
    System.out.println(" ");

    System.exit(0);
  }

}
