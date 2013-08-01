
/**
 * Classname:DescriptorPanel
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

import tools.common.gui.*;
import tools.viewer.render.*;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 * Specialization of <code>DescriptorPanel</code> for members
 * of the scene (actors, lights, and cameras).
 *
 */
public abstract class MemberDescriptorPanel extends DescriptorPanel
{
  // GUI FACET

  /**
   * The Edit action
   */
  protected ViewerAction editAction;

  /**
   * The New action
   */
  protected ViewerAction newAction;

  /**
   * The Remove action
   */
  protected ViewerAction removeAction;

  /**
   * The Select action
   */
  protected ViewerAction selectAction;

  /**
   * Constructor
   *
   */
  protected MemberDescriptorPanel(Viewer xviewer, Object[] xdata,
                                  String xname,
                                  int xwidth, int xheight)
  {
    super(xviewer, xdata, xname, xwidth, xheight);
  }

  /**
   * Constructor
   *
   */
  protected MemberDescriptorPanel(Viewer xviewer, Object[] xdata,
                                  String xname)
  {
    super(xviewer, xdata, xname);
  }

  // DESCRIPTOR PANEL FACET

  /**
   * Create the list cell renderer.
   */
  protected DescriptorCellRenderer createListCellRenderer()
  {
    return new DescriptorCellRenderer();
  }

  /**
   * Create the double click mouse listener
   */
  protected MouseListener createMouseListener()
  {
    MouseListener mouseListener = new MouseAdapter()
                                  {
                                    public void mouseClicked(MouseEvent e)
                                    {
                                      if(e.getClickCount() == 2)
                                      {
                                        Descriptor descriptor = getHighlightedDescriptor();

                                        if(descriptor == null)
                                          return;

                                        if(descriptor.selected)
                                          edit();
                                        else
                                          select();
                                      }
                                    }
                                  };

    return mouseListener;
  }

  /**
   * Create the popup menu and actions
   */
  protected ViewerPopupMenu createPopupMenu()
  {
    // Create and add popup menu

    String menuName = name + "s";
    ViewerPopupMenu menu = new ViewerPopupMenu(viewer, menuName);
    menu.setLightWeightPopupEnabled(false);

    String description = "Add a new " + name + " to the list";
    String title = "New";

    newAction = new ViewerAction(this, "New", "add",
                                 title,
                                 description,
                                 null, null, "Ctrl-N", null, "true");

    menu.add(newAction);

    description = "Edit the highlighted " + name + "(s)";
    title = "Edit " + name + "(s)";

    editAction = new ViewerAction(this, "Edit", "edit",
                                  title,
                                  description,
                                  null, null, "Ctrl-E", null, "false");

    menu.addSeparator();
    menu.add(editAction);

    description = "Remove the highlighted " + name + "(s)";
    title = "Remove " + name + "(s)";

    removeAction = new ViewerAction(this, "Remove", "remove",
                                    title,
                                    description,
                                    null, null, "Ctrl-R", null, "false");

    menu.add(removeAction);

    description = "Set the highlighted " + name +
                  " to the currently selected " + name + ".";
    title = "Select " + name;

    selectAction = new ViewerAction(this, "Select", "select",
                                    title,
                                    description,
                                    null, null, "Ctrl-S", null, "false");

    menu.add(selectAction);

    return menu;
  }

  /**
   * Register keystrokes
   */
  protected void registerKeyStrokes()
  {
    // Register keystrokes for the list.

    list.registerKeyboardAction(newAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_INSERT, 0),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(newAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_N, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(editAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_E, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(removeAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(removeAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_R, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(selectAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_S, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);
  }

  /**
   * Invoked when the script edit mode has changed
   */
  public void editScriptModeChanged()
  {
    enablePopupMenu();
  }

  // MEMBER DESCRIPTOR PANEL FACET

  /**
   * The Edit Action
   */
  public abstract void edit();

  /**
   * The New Action
   */
  public abstract void add
    ();

  /**
   * The Remove Action
   */
  public abstract void remove
    ();
}
