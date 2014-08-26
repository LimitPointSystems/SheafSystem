
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
import com.limitpoint.tools.viewer.render.*;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 * Specialization of <code>MemberDescriptorPanel</code> for displaying
 * a list of <code>LightDescriptors</code>
 *
 */
public class LightPanel extends MemberDescriptorPanel
{
  /**
   * The properties dialog
   */
  protected PropertiesDialog dialog;

  /**
   * Constructor
   *
   */
  public LightPanel(G3DViewer xviewer, int xwidth, int xheight)
  {
    super(xviewer, xviewer.getScene().getLights(), "Light",
          xwidth, xheight);

    createPropertiesDialog();
  }

  /**
   * Constructor
   *
   */
  public LightPanel(G3DViewer xviewer)
  {
    super(xviewer, xviewer.getScene().getLights(), "Light");

    createPropertiesDialog();
  }

  // DESCRIPTOR PANEL FACET

  /**
   * Force an update of the list
   */
  public void update()
  {
    reinit(viewer.getScene().getLights());
    repaint();
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

    LightDescriptor[] selectedLights = getHighlightedLights();
    if(selectedLights.length == 0)
    {
      // No descriptors are hightlighted, can't edit
      // remove or select.

      editAction.setEnabled(false);
      removeAction.setEnabled(false);
      selectAction.setEnabled(false);
    }
    else if(selectedLights.length == 1)
    {
      // One descriptor is highlighted.

      editAction.setEnabled(true);

      // Can't remove the camera light

      if(selectedLights[0].cameraLight ||
          viewer.getEditScriptMode())
        removeAction.setEnabled(false);
      else
        removeAction.setEnabled(true);

      if(selectedLights[0].selected)
        selectAction.setEnabled(false);
      else
        selectAction.setEnabled(true);
    }
    else
    {
      // More than one descriptor is selected.

      editAction.setEnabled(true);

      // Can't remove the camera light

      if(viewer.getEditScriptMode())
      {
        removeAction.setEnabled(false);
      }
      else
      {
        removeAction.setEnabled(true);
        for(int i=0; i<selectedLights.length; i++)
        {
          if(selectedLights[i].cameraLight)
          {
            removeAction.setEnabled(false);
            break;
          }
        }
      }

      selectAction.setEnabled(false);
    }
  }

  // MEMBER DESCRIPTOR PANEL FACET

  /**
   * The Edit Action
   */
  public void edit()
  {
    openProperties(getHighlightedLights());
  }

  /**
   * The New Action
   */
  public void add
    ()
  {
    // Construct a non-camera light.

    LightDescriptor light = new LightDescriptor();
    light.cameraLight = false;

    // Calculate the id.  Find the last descriptor added
    // and add on to it's id

    synchronized (viewer.getScene())
    {
      HashSet<LightDescriptor> set
        = viewer.getScene().lights;
      LightDescriptor last = (LightDescriptor) set.toArray()[set.size()-1];

      light.id = last.id + 1;

      // Initialize the light to the position and
      // focal point of the selected camera.

      CameraDescriptor camera = null;
      Iterator<CameraDescriptor> itr = viewer.getScene().cameras.iterator();
      while(itr.hasNext())
      {
        camera = itr.next();
        if(camera.selected)
          break;
      }

      if(camera != null)
      {
        light.position[0] = camera.position[0];
        light.position[1] = camera.position[1];
        light.position[2] = camera.position[2];
        light.focalPoint[0] = camera.focalPoint[0];
        light.focalPoint[1] = camera.focalPoint[1];
        light.focalPoint[2] = camera.focalPoint[2];
      }

      // Add the light to the scene

      viewer.getScene().lights.add(light);
    }

    // Clear the list selections.

    list.clearSelection();

    // Set the selected light to the added light.

    deselect();

    synchronized (light)
    {
      light.selected = true;
    }

    selectedDescriptor = light;

    // Initialize the list

    init(viewer.getScene().getLights());
    repaint();

    // Update the clients.

    viewer.updateClients();
  }

  /**
   * The Remove Action
   */
  public void remove
    ()
  {
    LightDescriptor[] lights = getHighlightedLights();
    boolean noSelected = false;
    for(int i=0; i<lights.length; i++)
    {
      // Set no selected flag

      if(lights[i].selected)
        noSelected = true;

      // Remove the light from the scene.

      synchronized (viewer.getScene())
      {
        viewer.getScene().lights.remove(lights[i]);
      }
    }

    // Set the selected light to the first light in the list
    // if the selected light was removed.

    if(noSelected)
    {
      // The selected light has been removed.  Select the
      // first light in the list.

      selectedDescriptor = (Descriptor) viewer.getScene().getLights()[0];

      synchronized (selectedDescriptor)
      {
        selectedDescriptor.selected = true;
      }
    }

    // Clear the list selections.

    list.clearSelection();

    // Update the list.

    init(viewer.getScene().getLights());
    repaint();

    // Update the clients.

    viewer.updateClients();
  }

  // LIGHT PANEL FACET

  /**
   * Create the <code>PropertiesDialog</code>
   */
  protected void createPropertiesDialog()
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    LightPropertiesPanel panel = new LightPropertiesPanel((G3DViewer) viewer);
    dialog = new PropertiesDialog(frame, "Light Properties", panel);
    dialog.setLocationRelativeTo(viewer.getContentPane());
  }

  /**
   * The selected light
   */
  public LightDescriptor getSelectedLight()
  {
    return (LightDescriptor) selectedDescriptor;
  }

  /**
   * Return the selected list values as an array of
   * <code>LightDescriptors</code>
   */
  public LightDescriptor[] getHighlightedLights()
  {
    Object[] objs = list.getSelectedValues();
    LightDescriptor[] result = new LightDescriptor[objs.length];
    for(int i=0; i<objs.length; i++)
    {
      result[i] = (LightDescriptor) objs[i];
    }

    return result;
  }

  /**
   * Open the light properties dialog for the selected light
   */
  public void openSelectedProperties()
  {
    LightDescriptor[] lights = new LightDescriptor[1];
    lights[0] = getSelectedLight();

    openProperties(lights);
  }

  /**
   * Open the light properties dialog
   */
  protected void openProperties(LightDescriptor[] xlights)
  {
    LightPropertiesPanel panel =
      (LightPropertiesPanel) dialog.getPropertiesPanel();
    panel.setLights(xlights);

    if(!dialog.isVisible())
      dialog.setVisible(true);
    else
      dialog.requestFocus();
  }
}
