
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
 * Specialization of <code>DescriptorPanel</code> for displaying
 * a list of <code>SceneDescriptors</code>
 *
 */
public class ScenePanel extends DescriptorPanel
{
  // GUI FACET

  /**
   * The load action
   */
  protected ViewerAction loadAction;

  /**
   * The edit action
   */
  protected ViewerAction editAction;

  /**
   * The cancel action
   */
  protected ViewerAction cancelAction;

  /**
   * The interpolate action
   */
  protected ViewerAction interpolateAction;

  /**
   * Constructor
   *
   */
  public ScenePanel(Viewer xviewer, int xwidth, int xheight)
  {
    super(xviewer, xviewer.getScript().toArray(), "Scene",
          xwidth, xheight);

    list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
  }

  /**
   * Constructor
   *
   */
  public ScenePanel(Viewer xviewer)
  {
    super(xviewer, xviewer.getScript().toArray(), "Scene");

    list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
  }

  /**
   * Clear highlighted list items and force the update of the list.
   */
  public void refresh()
  {
    list.clearSelection();

    selectedDescriptor = null;

    update();

    SceneDescriptor scene = (SceneDescriptor) selectedDescriptor;
    viewer.setScriptScene(scene.clone());
  }

  /**
   * Force an update of the list
   */
  protected void update()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        init(viewer.getScript().toArray());
      }
    }

    repaint();
  }

  /**
   * Create the descriptor list cell renderer.
   */
  protected DescriptorCellRenderer createListCellRenderer()
  {
    return new SceneCellRenderer();
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
                                        if(viewer.getEditScriptMode())
                                        {
                                          // In script edit mode. Cancel existing key frame or
                                          // open the scene as a key frame for editting.

                                          SceneDescriptor scene = getHighlightedScene();
                                          if(scene.selected && scene.keyFrame)
                                            cancel();
                                          else
                                            edit();
                                        }
                                        else
                                        {
                                          // Not in script mode, load scene.

                                          load();
                                        }
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

    String menuName = "Scenes";
    ViewerPopupMenu menu = new ViewerPopupMenu(viewer, menuName);
    menu.setLightWeightPopupEnabled(false);

    loadAction = new ViewerAction(this, "Load", "load",
                                  "Load Scene",
                                  "Load the highlighted scene into the viewer.",
                                  null, null, "Ctrl-L", null, "true");
    menu.add(loadAction);

    menu.addSeparator();

    editAction = new ViewerAction(this, "Edit", "edit",
                                  "Edit Key Frame",
                                  "Load and open the highlighted scene as a " +
                                  "Key Frame for editing.",
                                  null, null, "Ctrl-E", null, "false");
    menu.add(editAction);

    cancelAction = new ViewerAction(this, "Cancel", "cancel",
                                    "Cancel Key Frame",
                                    "Cancel the highlighted scene as a Key Frame " +
                                    "and ignore changes when interpolating",
                                    null, null, "Ctrl-C", null, "false");
    menu.add(cancelAction);

    interpolateAction = new ViewerAction(this, "Interpolate", "interpolate",
                                         "Interpolate",
                                         "Interpolate Script between Key Frames",
                                         null, null, "Ctrl-I", null, "false");
    menu.add(interpolateAction);

    return menu;
  }

  /**
   * Register keystrokes
   */
  protected void registerKeyStrokes()
  {
    // Register keystrokes for the list.

    list.registerKeyboardAction(loadAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_L, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(editAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_E, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(cancelAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(cancelAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_C, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);

    list.registerKeyboardAction(interpolateAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_I, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);
  }

  // THE ACTIONS

  /**
   * Load the scene into the viewer
   */
  public void load()
  {
    // Update the selection

    deselect();

    SceneDescriptor scene = getHighlightedScene();
    synchronized (scene)
    {
      scene.selected = true;
    }

    selectedDescriptor = scene;

    // Load a clone of the scene into the viewer.
    // By loading a clone, changes to the scene will
    // not effect the script.

    viewer.setScriptScene(scene.clone());

    repaint();
  }

  /**
   * Load scene into the viewer and open as a key frame for editting.
   */
  public void edit()
  {
    // Update the selection and keyFrag flag

    deselect();

    SceneDescriptor scene = getHighlightedScene();
    synchronized (scene)
    {
      scene.selected = true;
      scene.keyFrame = true;
    }

    selectedDescriptor = scene;

    // Load the scene into the viewer.  By loading a non-clone,
    // changes to the scene will not change the script scene.

    viewer.setScriptScene(scene);

    repaint();

    // Enable popup menu

    enablePopupMenu();
  }

  /**
   * Cancel scene as a key frame and ignore changes made during
   * interpolation
   */
  public void cancel()
  {
    getHighlightedScene().keyFrame = false;

    repaint();

    // Enable popup menu

    enablePopupMenu();
  }

  /**
   * Interpolate changes between key frames.
   */
  public void interpolate()
  {
    if(needsInterpolation())
      viewer.getScript().interpolate();

    // Clear the key frames

    clearKeyFrames();

    // Enable popup menu

    enablePopupMenu();
  }

  /**
   * Clear the key frames
   */
  public void clearKeyFrames()
  {
    for(int i=0; i<data.length; i++)
    {
      ((SceneDescriptor) data[i]).keyFrame = false;
    }

    repaint();
  }

  /**
   * Set the selected scene to xscene
   */
  public void setScene(SceneDescriptor xscene)
  {
    list.clearSelection();
    deselect();

    // Use the equals method to find the scene index
    // in the script.  Then, use that index to get
    // the scene object in the list.

    synchronized (viewer.getScript())
    {
      int idx = viewer.getScript().indexOf(xscene);
      selectedDescriptor = viewer.getScript().get(idx);

      // Select the scene.

      synchronized (selectedDescriptor)
      {
        selectedDescriptor.selected = true;
      }
    }

    repaint();
  }

  /**
   * Invoked when the script edit mode has changed
   */
  public void editScriptModeChanged()
  {
    enablePopupMenu();

    if(!viewer.getEditScriptMode() && needsInterpolation())
    {
      int result =
        JOptionPane.showConfirmDialog(viewer,
                                      "Exiting Script Edit Mode.\n\n" +
                                      "Would you like to Interpolate?");

      if(result == JOptionPane.YES_OPTION)
        interpolate();
      else if(result == JOptionPane.CANCEL_OPTION)
        viewer.editScript();
    }
    else if(!viewer.getEditScriptMode())
    {
      clearKeyFrames();
    }
  }

  /**
   * Enable the popup menu items.
   */
  protected void enablePopupMenu()
  {
    if(viewer.getEditScriptMode() && getHighlightedScene() != null)
    {
      if(getHighlightedScene().keyFrame)
      {
        editAction.setEnabled(true);
        cancelAction.setEnabled(true);
      }
      else
      {
        editAction.setEnabled(true);
        cancelAction.setEnabled(false);
      }

      interpolateAction.setEnabled(true);
    }
    else
    {
      editAction.setEnabled(false);
      cancelAction.setEnabled(false);
      interpolateAction.setEnabled(false);
    }
  }

  /**
   * The selected <code>SceneDescriptor</code>
   */
  public SceneDescriptor getSelectedScene()
  {
    return (SceneDescriptor) selectedDescriptor;
  }

  // LIST FACET

  /**
   * Return the selected object as a <code>SceneDescriptor</code>
   */
  public SceneDescriptor getHighlightedScene()
  {
    return (SceneDescriptor) list.getSelectedValue();
  }

  /**
   * True, if any scene other than the last scene is a key frame.
   */
  public boolean needsInterpolation()
  {
    SceneDescriptor scene;
    for(int i=0; i<data.length-1; i++)
    {
      scene = (SceneDescriptor) data[i];
      if(scene.keyFrame)
        return true;
    }

    return false;
  }
}
