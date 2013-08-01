/**
 * Classname:SheafScopeOpenFileCommand
 *
 * @author $Author: dmbutler $
 *
 * $Date: 2013/03/13 00:59:09 $
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
import tools.common.gui.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * SheafScopeOpenFileCommand is an action listener for
 * SheafScopeFrame open file events.
 *
 */
public class SheafScopeOpenFileCommand extends AbstractAction
{

  /**
   * The <code>SheafScopeFrame</code> this command is associated with.
   */
  protected SheafScopeFrame frame;

  /**
   * The file name chosen from the dialog.
   */
  protected String filename;

  /**
   * The file filter.
   */
  private static SuffixFileFilter hdf_filter = new SuffixFileFilter(".hdf");

  /**
   * Constructor
   *
   * @param xframe The main panel containing the major components
   * (including the file chooser) of the application or applet.
   */
  public SheafScopeOpenFileCommand(SheafScopeFrame xframe)
  {
    super("Open");
    this.frame = xframe;

    Icon icon = GuiUtilities.getImageIcon(SheafScopeConstants.IMAGE_PATH + "open.png");
    putValue(Action.SMALL_ICON, icon);
    putValue(Action.SHORT_DESCRIPTION, "Open file...");

    // Set directory to current.

    JFileChooser fc = frame.getFileChooser();
    fc.setSelectedFile(null);
    
    File userDir = new File(System.getProperty("user.dir"));
    fc.setCurrentDirectory(userDir);

    // Set the window title.

    fc.setDialogTitle(SheafScopeApplication.APPLICATION_NAME +
                      " - Open Data File");

    // Set the chooser selection mode.
    // Cannot be open "dirs" when *.* is chosen as file type.

    fc.setFileSelectionMode(fc.FILES_ONLY);

    // do not show hidden files

    fc.setFileHidingEnabled(true);

  }

  /**
   * The action to be taken if an open file event is detected.<p>
   *
   * @param event The detected <code>ActionEvent</code>.
   *
   * 
   */
  public void actionPerformed(ActionEvent event)
  {
    try
    {
      // Show the file selection dialog.

      JFileChooser fc = frame.getFileChooser();
      fc.setSelectedFile(null);
      fc.updateUI();

      // Set the hdf_filter file filter.

      fc.setFileFilter(hdf_filter);

      int option = fc.showOpenDialog(frame);

      if(option == fc.APPROVE_OPTION)
      {
        // Show and hourglass and disable gui input.

        frame.setWaitState(true);

        // Get the filename.

        filename = fc.getCurrentDirectory()
                   + "/" + fc.getSelectedFile().getName();

        // Open the file.

        approveSelection();

        // Disable the hourglass.

	frame.setWaitState(false);
      }
    }
    catch(Exception e)
    { }

  }

  /**
   * Action to be taken once a file selection is approved
   * in the chooser dialog.<p>
   *
   * 
   */
  public void approveSelection()
  {
    try
    {
      String lname = filename.substring(filename.lastIndexOf("/")+1);
      namespace_poset namespace = new namespace_poset(lname);
      namespace.get_read_write_access(true);

      storage_agent sa = new storage_agent(filename,
                                           sheaf_file.access_mode.READ_ONLY,
                                           true, false);
      sa.put_member_record_buffer_ub(15);
      sa.put_dof_tuple_record_buffer_ub(15);
      sa.read_entire(namespace);

      frame.openNamespace(namespace, filename);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Default finalize method.<p>
   *
   * 
   */
  public void finalize()throws Throwable
  {
    // No specific action required, just call the superclass finalizer.

    super.finalize();
  }
}
