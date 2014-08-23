
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

import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.viewer.render.*;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 * Specialization of <code>MemberDescriptorPanel</code> for displaying
 * a list of <code>CameraDescriptors</code>
 *
 */
public class CameraPanel extends MemberDescriptorPanel
{
  /**
   * The properties dialog
   */
  protected PropertiesDialog dialog;

  /**
   * Constructor
   *
   */
  public CameraPanel(G3DViewer xviewer, int xwidth, int xheight)
  {
    super(xviewer, xviewer.getScene().getCameras(), "Camera",
          xwidth, xheight);

    createPropertiesDialog();
  }

  /**
   * Constructor
   *
   */
  public CameraPanel(G3DViewer xviewer)
  {
    super(xviewer, xviewer.getScene().getCameras(), "Camera");

    createPropertiesDialog();
  }

  // DESCRIPTOR PANEL FACET

  /**
   * Force an update of the list
   */
  public void update()
  {
    reinit(viewer.getScene().getCameras());
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

    CameraDescriptor[] selectedCameras = getHighlightedCameras();
    if(selectedCameras.length == 0)
    {
      // No descriptors are hightcameraed, can't edit
      // remove or select.

      editAction.setEnabled(false);
      removeAction.setEnabled(false);
      selectAction.setEnabled(false);
    }
    else if(selectedCameras.length == 1)
    {
      // One descriptor is highlighted.

      editAction.setEnabled(true);

      // Can't remove the last light

      if(viewer.getScene().cameras.size() == 1 ||
          viewer.getEditScriptMode())
        removeAction.setEnabled(false);
      else
        removeAction.setEnabled(true);

      if(selectedCameras[0].selected)
        selectAction.setEnabled(false);
      else
        selectAction.setEnabled(true);
    }
    else
    {
      // More than one descriptor is selected.

      editAction.setEnabled(true);

      // Can't remove all the lights

      if(viewer.getScene().cameras.size() == selectedCameras.length ||
          viewer.getEditScriptMode())
        removeAction.setEnabled(false);
      else
        removeAction.setEnabled(true);

      selectAction.setEnabled(false);
    }
  }

  // MEMBER DESCRIPTOR PANEL FACET

  /**
   * The Edit Action
   */
  public void edit()
  {
    openProperties(getHighlightedCameras());
  }

  /**
   * The New Action
   */
  public void add
    ()
  {
    // Add the camera to the scene

    CameraDescriptor camera = new CameraDescriptor();

    // Calculate the id.  Find the last descriptor added
    // and add on to it's id

    synchronized (viewer.getScene())
    {
      HashSet<CameraDescriptor> set
        = viewer.getScene().cameras;
      CameraDescriptor last = (CameraDescriptor) set.toArray()[set.size()-1];

      camera.id = last.id + 1;

      // Add the camera to the scene

      viewer.getScene().cameras.add(camera);
    }

    // Clear the list selections.

    list.clearSelection();

    // Set the selected camera to the added camera.

    deselect();

    synchronized (camera)
    {
      camera.selected = true;
    }

    selectedDescriptor = camera;

    // Initialize the list

    init(viewer.getScene().getCameras());
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
    CameraDescriptor[] cameras = getHighlightedCameras();
    boolean noSelected = false;
    for(int i=0; i<cameras.length; i++)
    {
      // Set no selected flag

      if(cameras[i].selected)
        noSelected = true;

      // Remove the camera from the scene.

      synchronized (viewer.getScene())
      {
        viewer.getScene().cameras.remove(cameras[i]);
      }
    }

    // Clear the list selections.

    list.clearSelection();

    // Set the selected camera to the first camera in the list
    // if the selected camera was removed.

    if(noSelected)
    {
      // The selected camera has been removed.  Select the
      // first camera in the list.

      selectedDescriptor = (Descriptor) viewer.getScene().getCameras()[0];

      synchronized (selectedDescriptor)
      {
        selectedDescriptor.selected = true;
      }
    }

    // Initialize the list.

    init(viewer.getScene().getCameras());
    repaint();

    // Update the clients.

    viewer.updateClients();
  }

  // CAMERA PANEL FACET

  /**
   * Create the <code>PropertiesDialog</code>
   */
  protected void createPropertiesDialog()
  {
    JFrame frame = (JFrame)
                   (SwingUtilities.windowForComponent(viewer.getContentPane()));

    CameraPropertiesPanel panel = new CameraPropertiesPanel((G3DViewer) viewer);
    dialog = new PropertiesDialog(frame, "Camera Properties", panel);
    dialog.setLocationRelativeTo(viewer.getContentPane());
  }

  /**
   * The selected camera
   */
  public CameraDescriptor getSelectedCamera()
  {
    return (CameraDescriptor) selectedDescriptor;
  }

  /**
   * Return the selected list values as an array of
   * <code>CameraDescriptors</code>
   */
  public CameraDescriptor[] getHighlightedCameras()
  {
    Object[] objs = list.getSelectedValues();
    CameraDescriptor[] result = new CameraDescriptor[objs.length];
    for(int i=0; i<objs.length; i++)
    {
      result[i] = (CameraDescriptor) objs[i];
    }

    return result;
  }

  /**
   * Open the camera properties dialog for the selected camera
   */
  public void openSelectedProperties()
  {
    CameraDescriptor[] cameras = new CameraDescriptor[1];
    cameras[0] = getSelectedCamera();

    openProperties(cameras);
  }

  /**
   * Open the camera properties dialog
   */
  protected void openProperties(CameraDescriptor[] xcameras)
  {
    CameraPropertiesPanel panel =
      (CameraPropertiesPanel) dialog.getPropertiesPanel();
    panel.setCameras(xcameras);

    if(!dialog.isVisible())
      dialog.setVisible(true);
    else
      dialog.requestFocus();
  }
}
