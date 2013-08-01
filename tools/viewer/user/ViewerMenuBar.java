
/**
 * Classname: ViewerMenuBar
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:02 $
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


package tools.viewer.user;

import javax.swing.*;
import javax.swing.event.*;
import tools.viewer.common.*;
import tools.common.gui.*;

import java.util.*;

/**
 *
 * Specialization of <code>JMenuBar</code> with sets up a menu bar
 * for the <code>Viewer</code>
 *
 */
public abstract class ViewerMenuBar extends JMenuBar
{
  /**
   * The Viewer.
   */
  protected Viewer viewer;

  /**
   * The Actions of the Viewer.
   */
  protected ViewerActions actions;

  /**
   * The Script edit mode radio menu item.
   */
  protected JRadioButtonMenuItem editModeMenuItem;

  /**
   * Constructor
   *
   */
  protected ViewerMenuBar(Viewer xviewer, ViewerActions xactions)
  {
    // Set the data members from input arguments.

    viewer = xviewer;
    actions = xactions;

    setBorder(BorderFactory.createRaisedBevelBorder());

    // Create the menus of the menu bar

    add
      (createFileMenu());
  }

  /**
   * Set the edit mode
   */
  public void setEditMode(boolean mode)
  {
    editModeMenuItem.setSelected(mode);
  }

  /**
   * Override <code>setEnabled()</code>
   */
  public void setEnabled(boolean xenabled)
  {
    Iterator<String> names = actions.names().iterator();
    while(names.hasNext())
    {
      actions.get(names.next()).setEnabled(xenabled);
    }
  }

  /**
   * Update the menu bar.
   */
  protected abstract void update();

  /**
   *
   */
  protected ViewerMenu createFileMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "File");
    menu.setMnemonic('F');

    menu.add(actions.get("SaveImageAction"));
    menu.add(createImageFileFormatMenu());

    menu.addSeparator();

    menu.add(actions.get("CloseAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createScriptMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Script");
    menu.setMnemonic('A');

    menu.add(actions.get("NewScriptAction"));

    menu.addSeparator();

    editModeMenuItem =
      new JRadioButtonMenuItem(actions.get("EditScriptAction"));
    menu.add(editModeMenuItem);
    menu.add(actions.get("ResetSceneAction"));

    menu.addSeparator();

    menu.add(actions.get("OpenScriptAction"));
    menu.add(createSaveMenu());

    menu.addSeparator();

    menu.add(actions.get("OpenMovieAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createSaveMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Save");
    menu.setMnemonic('S');

    menu.add(actions.get("SaveSceneAction"));
    menu.add(actions.get("SaveScriptAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createHelpMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Help");
    menu.setMnemonic('H');

    menu.add(actions.get("HelpAboutAction"));
    menu.add(actions.get("HelpGeneralAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createImageFileFormatMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Image File Format");
    menu.setMnemonic('I');

    ButtonGroup group = new ButtonGroup();
    JRadioButtonMenuItem rbItem;

    String[] formats = {"BMP", "JPEG", "PNG", "PNM", "POSTSCRIPT", "TIFF"};

    // Do them all in a loop.
    for(int i=0; i<formats.length; ++i)
    {
      rbItem = new JRadioButtonMenuItem(actions.get(formats[i]+"ImageFormatAction"));
      group.add(rbItem);
      menu.add(rbItem);

      // Set default to JPEG.
      if("JPEG".equals(formats[i]))
        rbItem.setSelected(true);
    }

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }
}
