
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

import com.limitpoimt.tools.SheafScope.SheafScopeApplication;
import bindings.java.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.viewer.common.*;

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
