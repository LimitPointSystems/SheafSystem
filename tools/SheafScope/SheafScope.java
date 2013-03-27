/**
 * Classname: SheafScope
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScope.java,v $ $Revision: 1.13 $
 *
 *      $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

import tools.SheafScope.SheafScopeApplication;
import bindings.java.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import tools.common.gui.*;
import tools.viewer.common.*;

/**
 * The main SheafScope application.
 */
public class SheafScope extends SheafScopeApplication
{
  /**
   * The SheafScope's main routine.
   *
   * @param xargs the command line argumemts passed to "main"
   * 
   */
  public static void main(String[] xargs)
  {
    // Handle input arguments.

    interpretCommandLineArgs("SheafScope", xargs);

    // Set the look and feel to the system L&F.

    try
    {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch(Exception e)
    {
      System.out.println("Error: " + e);
    }

    //     if(runMode == LOCAL)
    //     {
    //       new SheafScope();
    //     }
    //     else
    //     {
    //       new SheafScope(port, host);
    //     }
    new SheafScope();
  }

  /**
   * Creates a <code>SheafScope</code> application object.
   */
  public SheafScope()
  {
    super("tools_java_binding");
  }

  //   /**
  //    *  Creates a <code>SheafScope</code> application object for remote execution.
  //    */
  //   public SheafScope(int xport, String xhost)
  //   {
  //     super("tools_java_binding", xport, xhost);
  //   }
}
