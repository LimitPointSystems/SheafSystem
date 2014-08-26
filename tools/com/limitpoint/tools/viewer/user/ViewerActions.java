
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


package com.limitpoint.tools.viewer.user;

import com.limitpoint.tools.common.gui.*;
import com.limitpoint.tools.viewer.animation.*;
import com.limitpoint.tools.viewer.common.*;
import com.limitpoint.tools.viewer.common.ViewerConstants.ImageFormat;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 *
 * Class that creates actions for the user components.
 *
 */
public abstract class ViewerActions extends Actions
{
  /**
   * The Viewer.
   */
  protected Viewer viewer;

  /**
   * The image current image file format.
   */
  protected ImageFormat format = ImageFormat.JPEG;

  /**
   * The help frame.
   */
  protected HelpFrame helpFrame = null;

  //$$ISSUE: We are using the following procedure consisting of actionSpecs
  //         (an array of String arrays) and the method "createActions" to
  //         make it potentially possible to read the actions from a text
  //         or xml file.  We are still using the Swing AbstractAction
  //         coupled with common.gui.GenericAction to emulate (weakly)
  //         the "command" pattern.  GenericAction (probably should be
  //         "GenericCommand") is limited to invoking methods with no arguments.
  //         This results in more Actions than we would like in cases where we
  //         could reduce the number of Actions (and the associated methods)
  //         if we could just pass a single parameter such as a boolean.

  // The actionSpecs contain the following for each action:
  // 0. action name
  // 1. action method
  // 2. action label
  // 3. description text
  // 4. tooltip text
  // 5. icon path
  // 6. accelerator key
  // 7. mnemonic
  // 8. is enabled: "true" or "false"

  static final String[][] actionSpecs =
    {
      // FILE MENU ACTIONS

      {"CloseAction", "doClose", "Close", "Close the viewer.", null, null, "Ctrl-E", "E", "true"},

      {"SaveImageAction", "doSaveImage", "Save Image As...",
       "Save the window as an image file", null, null, null, null, "true"},

      {"BMPImageFormatAction",        "doBMPImageFormat",        "BMP",
       null, null, null, null, null, "true"},
      {"JPEGImageFormatAction",       "doJPEGImageFormat",       "JPEG",
       null, null, null, null, null, "true"},
      {"PNGImageFormatAction",        "doPNGImageFormat",        "PNG",
       null, null, null, null, null, "true"},
      {"PNMImageFormatAction",        "doPNMImageFormat",        "PNM",
       null, null, null, null, null, "true"},
      {"POSTSCRIPTImageFormatAction", "doPOSTSCRIPTImageFormat", "PostScript",
       null, null, null, null, null, "true"},
      {"TIFFImageFormatAction",       "doTIFFImageFormat",       "TIFF",
       null, null, null, null, null, "true"},

      // EDIT MENU ACTIONS

      {"CloneAction", "doClone", "Clone Viewer",
       "Make a \"clone\" of this viewer.", null, null,
       "Ctrl-C", "C", "true"},

      // HELP MENU ACTIONS

      {"HelpAboutAction", "doHelpAbout", "About", "About help", null,
       ViewerConstants.IMAGE_PATH + "About16.png", null, "A", "true"},

      {"HelpGeneralAction", "doHelpGeneral", "General", "General help, user guide, etc.", null,
       ViewerConstants.IMAGE_PATH + "Help16.png", null, "G", "true"},

      // SCRIPT MENU ACTIONS

      {"NewScriptAction", "doNewScript", "New", "Create a New Script..", null,
       null, "Alt-N", null, "true"},

      {"EditScriptAction", "doEditScript", "Edit Mode",
       "Toggle the Script Edit Mode..", null,
       null, "Alt-E", null, "true"},

      {"ResetSceneAction", "doResetScene", "Reset Scene",
       "Reset the Scene..", null,
       null, "Alt-R", null, "true"},

      {"SaveScriptAction", "doSaveScript", "Script", "Save loaded Script.",
       null, null, "Alt-I", null, "true"},

      {"SaveSceneAction", "doSaveScene", "Scene", "Save current Stage Scene",
       null, null, "Alt-C", null, "true"},

      {"OpenScriptAction", "doOpenScript", "Open", "Load Script from file.",
       null, null, "Alt-O", null, "true"},

      {"OpenMovieAction", "doOpenMovie", "Open Movie", "Open Movie from file.",
       null, null, "Alt-M", null, "true"},
    };

  // CONSTRUCTORS

  /**
   * Constructor
   *
   */
  protected ViewerActions(Viewer xviewer)
  {
    super();

    viewer = xviewer;

    for(int i=0; i<actionSpecs.length; ++i)
    {
      put(actionSpecs[i][0], new ViewerAction(this, actionSpecs[i]));
    }
  }

  //$$ISSUE: Don't depend on this, it probably never gets called.
  /**
   * Finalize method
   */
  public void finalize()
  {
    if(helpFrame != null)
      helpFrame.dispose();
  }

  // ENABLED STATE FACET

  /**
   * Set the enabled state for all the actions
   */
  public void setEnabledAll(boolean xenabled)
  {
    Collection<AbstractAction> values = actionMap.values();

    ViewerAction action;
    Iterator<AbstractAction> itr = values.iterator();
    while(itr.hasNext())
    {
      action = (ViewerAction) itr.next();

      if(xenabled)
      {
        // Set the enabled state to the original enabled
        // state of the action.

        action.setToOriginalEnabledState();
      }
      else
      {
        // Disable all actions except the help actions.

        String name = action.getActionName();
        if(!name.equals("HelpAboutAction") &&
            !name.equals("HelpGeneralAction"))
        {
          action.setEnabled(false);
        }
      }
    }
  }

  // THE FILE MENU ACTIONS FACET

  /**
   * Close the viewer.
   */
  public void doClose()
  {
    viewer.setVisible(false);
  }

  /**
   * Save the canvas image to a file.
   */
  public void doSaveImage()
  {
    JFileChooser fileChooser = new JFileChooser();
    fileChooser.setDialogTitle("Save Window As Image File");

    String[] suffixes;
    switch(format)
    {
    case BMP:
      suffixes = new String[1];
      suffixes[0] = "bmp";
      break;
    case JPEG:
      suffixes = new String[2];
      suffixes[0] = "jpg";
      suffixes[1] = "jpeg";
      break;
    case PNG:
      suffixes = new String[1];
      suffixes[0] = "png";
      break;
    case PNM:
      suffixes = new String[1];
      suffixes[0] = "pnm";
      break;
    case POSTSCRIPT:
      suffixes = new String[1];
      suffixes[0] = "ps";
      break;
    case TIFF:
      suffixes = new String[2];
      suffixes[0] = "tif";
      suffixes[1] = "tiff";
      break;
    default:
      return;
    }

    SuffixFileFilter  filter = new SuffixFileFilter(suffixes);
    fileChooser.setFileFilter(filter);

    int returnVal = fileChooser.showSaveDialog(viewer);
    if(returnVal == JFileChooser.APPROVE_OPTION)
    {
      String fileName = fileChooser.getSelectedFile().getAbsolutePath();
      viewer.saveImage(fileName, format);
    }
  }

  /**
   * Set image type to BMP
   */
  public void doBMPImageFormat()
  {
    format = ImageFormat.BMP;
  }

  /**
   * Set image type to JPEG
   */
  public void doJPEGImageFormat()
  {
    format = ImageFormat.JPEG;
  }

  /**
   * Set image type to PNG
   */
  public void doPNGImageFormat()
  {
    format = ImageFormat.PNG;
  }

  /**
   * Set image type to PNM
   */
  public void doPNMImageFormat()
  {
    format = ImageFormat.PNM;
  }

  /**
   * Set image type to POSTCRIPT
   */
  public void doPOSTSCRIPTImageFormat()
  {
    format = ImageFormat.POSTSCRIPT;
  }

  /**
   * Set image type to TIFF
   */
  public void doTIFFImageFormat()
  {
    format = ImageFormat.TIFF;
  }

  // THE EDIT MENU ACTIONS FACET

  /**
   * Make a clone of the viewer.
   */
  public void doClone()
  {
    viewer.cloneViewer();
  }

  // HELP MENU ACTIONS FACET

  /**
   *
   */
  public void doHelpAbout()
  {
    String path = ViewerConstants.DOC_PATH + ViewerConstants.ABOUT;

    openHelp(path);
  }

  /**
   *
   */
  public void doHelpGeneral()
  {
    String path = ViewerConstants.DOC_PATH + ViewerConstants.USERS_GUIDE;

    openHelp(path);
  }

  /**
   *
   */
  protected void openHelp(String path)
  {
    try
    {
      URL helpURL = getClass().getResource(path);

      if(helpURL == null)
      {
        System.out.println("Couldn't find file: " + path);
        return;
      }

      String iconPath = ViewerConstants.IMAGE_PATH
                        + ViewerConstants.MAIN_ICON;
      URL iconURL = getClass().getResource(iconPath);

      if(helpFrame == null)
        helpFrame = new HelpFrame(helpURL, iconURL);
      else
        helpFrame.setPage(helpURL);
    }
    catch(IOException e)
    {
      System.out.println(e);
      return;
    }

    JFrame frame = (JFrame)(SwingUtilities.windowForComponent(viewer.getContentPane()));

    helpFrame.setVisible(true);

    // Make sure this frame is disposed of when the main window closes.

    frame.addWindowListener(
      new WindowAdapter()
      {
        public void windowClosing(WindowEvent e)
        {
          helpFrame.setVisible(false);
        }
      }
    );
  }

  // SCRIPT MENU ACTIONS

  /**
   * Toggle the edit script mode
   */
  public void doEditScript()
  {
    viewer.editScript();
  }

  /**
   * Reset the scene.
   */
  public void doResetScene()
  {
    viewer.resetScene();
  }

  /**
   * Create a new Script
   */
  public void doNewScript()
  {
    (new ScriptDialog(viewer)).setVisible(true);
  }

  /**
   * Save the Script to a file.
   */
  public void doSaveScript()
  {
    viewer.saveScript();
  }

  /**
   * Save the current stage scene to a file.
   */
  public void doSaveScene()
  {
    viewer.saveScene();
  }

  /**
   * Load script from a file.
   */
  public void doOpenScript()
  {
    viewer.openScript();
  }

  /**
   * Open a movie in the viewer
   */
  public void doOpenMovie()
  {
    viewer.openMovie();
  }
}
