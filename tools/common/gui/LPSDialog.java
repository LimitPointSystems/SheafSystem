
/**
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
 * 
 */

package tools.common.gui;

import java.awt.*;
import javax.swing.*;

//import SheafScope.*;

/**
 * LPSDialog is a specialization of JDialog which uses uses the
 * LPS logo.
 *
 * @see JDialog
 */
public class LPSDialog extends JDialog
{
  // Logo image is static amd immutable (We only need one instance).

  static final ImageIcon logo
  = GuiUtilities.getImageIcon("tools/common/gui/resources/lps_logo.png");

  /**
   * The wait state count.
   */
  protected int waitCount = 0;

  public LPSDialog(JFrame owner)
  {
    this(owner, "");
  }

  public LPSDialog(JFrame owner, String title)
  {
    super(owner, title);

    //     //setDefaultLookAndFeelDecorated(true);
    //     try
    //     {
    //       UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    //       //JDialog.setDefaultLookAndFeelDecorated(true);
    //     }
    //     catch(Exception e)
    //     {
    //       System.out.println("Error: " + e);
    //     }

    if(logo != null)
      setIconImage(logo.getImage());
  }

  /**
   * Puts up a glasspane to prevent user input while the system is busy.<p>
   *
   * @param xwait indicates the "wait" state for this pane.
   *
   * 
   */
  public void setWaitState(boolean xwait)
  {
    //$$TODO: Should save current cursor and reset to it
    //        when xwait == false.

    if(xwait)
      waitCount++;
    else
      waitCount--;

    if(waitCount == 1)
    {
      // The first time the wait state is set.  Set the wait cursor
      // and display the glass pane.

      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      getGlassPane().setVisible(true);
    }
    else if(waitCount <= 0)
    {
      // The last time the wait state is unset.  Set back to the
      // default cursor and hide the glass pane.  Invoke this
      // action in the event queue, to allow all painting to
      // finish.

      SwingUtilities.invokeLater(new Runnable()
      {
        public void run()
        {
          setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	  getGlassPane().setVisible(false);
	}
      });
    }
  }

}
