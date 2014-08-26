
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
import com.limitpoint.tools.viewer.common.*;
import com.limitpoint.tools.viewer.render.*;
import com.limitpoint.tools.viewer.table.*;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 *  Specialization of <code>MemberDescriptorPanel</code> for displaying
 * a list of <code>FieldActorDescriptors</code>
 *
 */
public class FieldActorPanel extends MemberDescriptorPanel
{
  // GUI FACET

  /**
   * The View action
   */
  protected ViewerAction viewAction;

  /**
   * The current properties dialog.
   */
  protected PropertiesDialog dialog = null;  

  /**
   * Constructor
   *
   */
  public FieldActorPanel(Viewer xviewer, int xwidth, int xheight)
  {
    super(xviewer, xviewer.getScene().getActors(), "Actor",
          xwidth, xheight);
  }

  /**
   * Constructor
   *
   */
  public FieldActorPanel(Viewer xviewer)
  {
    super(xviewer, xviewer.getScene().getActors(), "Actor");
  }

  // DESCRIPTOR PANEL FACET

  /**
   * Force an update of the list
   */
  public void update()
  {
    reinit(viewer.getScene().getActors());

    list.invalidate();
    invalidate();
    repaint();
  }

  /**
   * Create the popup menu and actions
   */
  protected ViewerPopupMenu createPopupMenu()
  {
    ViewerPopupMenu menu = super.createPopupMenu();

    viewAction = new ViewerAction(this, "View", "view",
                                  "View Dofs",
                                  "View the dofs of an Actor in table form.",
                                  null, null, "Ctrl-V", null, "false");

    menu.addSeparator();
    menu.add(viewAction);

    return menu;
  }

  /**
   * Register keystrokes
   */
  protected void registerKeyStrokes()
  {
    super.registerKeyStrokes();

    list.registerKeyboardAction(newAction,
                                KeyStroke.getKeyStroke(KeyEvent.VK_V, InputEvent.CTRL_MASK),
                                list.WHEN_FOCUSED);
  }

  /**
   * Enable the popup menu items.
   */
  protected void enablePopupMenu()
  {
    if(viewer.getEditScriptMode())
      newAction.setEnabled(false);
    else
      newAction.setEnabled(true);

    FieldActorDescriptor[] selectedActors = getHighlightedActors();
    if(selectedActors.length == 0)
    {
      editAction.setEnabled(false);
      removeAction.setEnabled(false);
      selectAction.setEnabled(false);
      viewAction.setEnabled(false);
    }
    else if(selectedActors.length == 1)
    {
      editAction.setEnabled(true);

      if(viewer.getEditScriptMode())
        removeAction.setEnabled(false);
      else
        removeAction.setEnabled(true);

      if(selectedActors[0].selected)
        selectAction.setEnabled(false);
      else
        selectAction.setEnabled(true);

      viewAction.setEnabled(true);
    }
    else
    {
      if(sameActorTypes(selectedActors))
        editAction.setEnabled(true);
      else
        editAction.setEnabled(false);

      if(viewer.getEditScriptMode())
        removeAction.setEnabled(false);
      else
        removeAction.setEnabled(true);

      selectAction.setEnabled(false);

      viewAction.setEnabled(false);
    }
  }

  // MEMBER DESCRIPTOR PANEL FACET

  /**
   * The Edit Action
   */
  public void edit()
  {
    openProperties(getHighlightedActors());
  }

  /**
   * The New Action
   */
  public void add()
  {
    // Clear the list selections.

    list.clearSelection();

    // Make the viewer invisible.

    viewer.setVisible(false);

    // Open the client application

    Viewer.APPLICATION.setSelectedViewer(viewer);
    Viewer.APPLICATION.toForeground();
  }

  /**
   * The Remove Action
   */
  public void remove()
  {
    FieldActorDescriptor[] actors = getHighlightedActors();
    boolean noSelected = false;
    for(int i=0; i<actors.length; i++)
    {
      // Set no selected flag

      if(actors[i].selected)
        noSelected = true;

      // Remove the actor from the scene.

      synchronized (viewer.getScene())
      {
        viewer.getScene().actors.remove(actors[i]);
      }
    }

    // Set the selected actor to the first actor in the list
    // if the selected actor was removed.

    if(noSelected && viewer.getScene().actors.size() > 0)
    {
      // The selected actor has been removed.  Select the
      // first actor in the list.

      selectedDescriptor = (Descriptor) viewer.getScene().getActors()[0];

      synchronized (selectedDescriptor)
      {
        selectedDescriptor.selected = true;
      }
    }
    else
    {
      selectedDescriptor = null;
    }

    // Clear the list selections.

    list.clearSelection();

    // Initialize the list.

    refresh();

    // Update the clients.

    viewer.updateClients(true);
  }

  /**
   * View the highlighed actor's dofs in table form.
   */
  public void view()
  {
    FieldActorDescriptor actor = getHighlightedActors()[0];

    FieldTableDescriptor table = new FieldTableDescriptor();
    table.namespace = actor.namespace;
    table.sections.add(actor.coordinates.clone());
    SectionDescriptor[] properties = actor.getProperties();
    for(int i=0; i<properties.length; i++)
    {
      table.sections.add(properties[i].clone());
    }

    TableViewer viewer = new TableViewer(table);
  }

  // FIELD ACTOR PANEL FACET

  /**
   * The selected actor
   */
  public FieldActorDescriptor getSelectedActor()
  {
    return (FieldActorDescriptor) selectedDescriptor;
  }

  /**
   * Open the actor properties dialog for the selected actor
   */
  public void openSelectedProperties()
  {
    FieldActorDescriptor[] actors = new FieldActorDescriptor[1];
    actors[0] = getSelectedActor();

    openProperties(actors);
  }

  /**
   * Return the selected list values as an array of
   * <code>FieldActorDescriptors</code>
   */
  public FieldActorDescriptor[] getHighlightedActors()
  {
    Object[] objs = list.getSelectedValues();
    FieldActorDescriptor[] result = new FieldActorDescriptor[objs.length];
    for(int i=0; i<objs.length; i++)
    {
      result[i] = (FieldActorDescriptor) objs[i];
    }

    return result;
  }

  /**
   * Open the actor properties dialog
   */
  protected void openProperties(FieldActorDescriptor[] xactors)
  {
    // Get the properties dialog from the first actor in the list.
    // The user interface should make sure all the actors are of
    // the same type.

    dialog = xactors[0].getPropertiesDialog(viewer, xactors);
    dialog.setVisible(true);
  }

  /**
   * Update the properties dialog.
   */
  protected void updateProperties(FieldActorDescriptor[] xactors)
  {
    if((dialog != null) && dialog.isVisible())
    {
      ((FieldActorPropertiesPanel) dialog.getPropertiesPanel()).setDescriptors(xactors);
    }
  }

  /**
   * Add a <code>FieldActorDescriptor</code>
   */
  public boolean addFieldActor(FieldActorDescriptor actor)
  {
    // Check to see if the actor can be added

    if(viewer.getScene().actors.contains(actor))
    {
      Frame frame = Viewer.APPLICATION.getFrame();

      JOptionPane.showMessageDialog(frame, "Can not add actor:\n" + actor +
                                    "\n\nIt already exists in the Scene.",
                                    "Can Add Actor",
                                    JOptionPane.ERROR_MESSAGE);

      return false;
    }

    // Set the time of the actor to the time of the scene.

    synchronized (actor)
    {
      actor.time = viewer.getScene().time;
    }

    // Add actor to the scene.

    synchronized (viewer.getScene())
    {
      viewer.getScene().actors.add(actor);
    }

    // Set the selected actor to the added actor.

    deselect();

    synchronized (actor)
    {
      actor.selected = true;
    }

    selectedDescriptor = actor;

    // Initialize the list

    refresh();

    // Update the clients

    viewer.updateClients(true);

    return true;
  }

  /**
   * True, if the actor types are the same.
   */
  protected boolean sameActorTypes(FieldActorDescriptor[] xactors)
  {
    // Compare all the other objects in the array to the first argument's
    // class type.

    Class type = xactors[0].getClass();

    for(int i=1; i<xactors.length; i++)
    {
      if(!type.isInstance(xactors[i]))
        return false;
    }

    return true;
  }
}
