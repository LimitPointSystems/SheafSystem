
/**
 * Classname: G3DViewer
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:01 $
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

import bindings.java.*;
import tools.common.gui.*;
import tools.viewer.animation.*;
import tools.viewer.render.*;
import tools.viewer.common.ViewerConstants.ImageFormat;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.plaf.metal.*;

/**
 *
 * Class for providing a user interface to the <code>Stage</code> for
 * <code>G3DFieldActor</code>'s
 *
 */
public class G3DViewer extends Viewer
{
  /**
   * The probe dialog
   */
  protected ProbeDialog probeDialog;

  /**
   * Constructor
   */
  public G3DViewer(FieldActorDescriptor xactor)
  {
    super("3D Viewer", xactor);
  }

  /**
   * Constructor
   */
  public G3DViewer(Integer id, FieldActorDescriptor xactor)
  {
    super("3D Viewer " + id.toString(), xactor);
  }

  /**
   * Constructor
   */
  public G3DViewer(String xtitle, FieldActorDescriptor xactor)
  {
    super(xtitle, xactor);
  }

  /**
   * Constructor
   */
  public G3DViewer(Script xscript)
  {
    super("3D Viewer", xscript);
  }

  /**
   * Constructor
   */
  public G3DViewer(Integer id, Script xscript)
  {
    super("3D Viewer " + id.toString(), xscript);
  }

  /**
   * Constructor
   */
  public G3DViewer(String xtitle, Script xscript)
  {
    super(xtitle, xscript);
  }

  /**
   * Constructor
   */
  public G3DViewer(File xscriptFile) throws IOException
  {
    super("3D Viewer", xscriptFile);
  }

  /**
   * Constructor
   */
  public G3DViewer(Integer id, File xscriptFile) throws IOException
  {
    super("3D Viewer " + id.toString(), xscriptFile);
  }

  /**
   * Constructor
   */
  public G3DViewer(String xtitle, File xscriptFile) throws IOException
  {
    super(xtitle, xscriptFile);
  }

  protected void init(String xtitle, Script xscript)
  {
    super.init(xtitle, xscript);

    // Create the probe dialog

    JFrame frame = (JFrame)(SwingUtilities.windowForComponent(getContentPane()));
    probeDialog = new ProbeDialog(frame, this);
    probeDialog.setLocationRelativeTo(getContentPane());
  }

  // VIEWER FACET

  /**
   * Make a clone of this <code>Viewer</code> and display it.
   */
  public void cloneViewer()
  {
    G3DViewer viewer = new G3DViewer(script.clone());
    viewer.setVisible(true);
  }

  /**
   * Create a default <code>Script</code>
   */
  protected Script createDefaultScript(FieldActorDescriptor xactor)
  {
    // Create a single scene animation with min and max time of 0.

    SceneDescriptor lscene = new SceneDescriptor();
    lscene.selected = true;

    if(xactor != null)
    {
      // Add the actor to the scene

      G3DFieldActorDescriptor actor =
        (G3DFieldActorDescriptor) xactor.clone();
      actor.selected = true;

      lscene.actors.add(actor);
    }

    // Add default camera to the scene

    CameraDescriptor camera = new CameraDescriptor();
    camera.selected = true;
    lscene.cameras.add(camera);

    // Add default light to the scene

    LightDescriptor light = new LightDescriptor();
    light.selected = true;
    lscene.lights.add(light);

    // Create and return the script.

    Script result = new Script(this);
    result.add(lscene);

    return result;
  }

  /**
   * Add a <code>FieldActorDescriptor</code>.
   */
  public boolean addFieldActor(FieldActorDescriptor xactor)
  {
    G3DFieldActorDescriptor actor = (G3DFieldActorDescriptor) xactor;

    return ((G3DDescriptorsTabbedPane) tabbedPane).addFieldActor(actor);
  }

  /**
   * Create the <code>ViewerMenuBar</code>
   */
  protected ViewerMenuBar createMenuBar()
  {
    G3DViewerActions actions = new G3DViewerActions(this);

    return new G3DViewerMenuBar(this, actions);
  }

  /**
   * Create the <code>DescriptorsTabbedPane</code>.
   */
  protected DescriptorsTabbedPane createTabbedPane()
  {
    return new G3DDescriptorsTabbedPane(this);
  }

  /**
   * Pick xposition
   */
  public void pick(double[] xposition)
  {
    ProbePanel probe = probeDialog.getProbePanel();

    synchronized (probe)
    {
      probe.setPickerPosition(xposition);
      probe.notify();
    }
  }

  // G3D VIEWER FACET

  /**
   * Open the probe dialog
   */
  public void openProbe()
  {
    probeDialog.setVisible(true);
  }

  /**
   * The selected actor
   */
  public G3DFieldActorDescriptor getSelectedActor()
  {
    return (G3DFieldActorDescriptor) tabbedPane.getSelectedActor();
  }

  /**
   * The selected light
   */
  public LightDescriptor getSelectedLight()
  {
    return ((G3DDescriptorsTabbedPane) tabbedPane).getSelectedLight();
  }

  /**
   * The selected camera
   */
  public CameraDescriptor getSelectedCamera()
  {
    return ((G3DDescriptorsTabbedPane) tabbedPane).getSelectedCamera();
  }

  /**
   * Reset the selected camera
   */
  public void resetSelectedCamera()
  {
    // Copy the values from the selected script scene into the
    // current scenes descriptor.

    CameraDescriptor camera = getSelectedCamera();
    tabbedPane.getSelectedScene().copyTo(camera);

    // Ensure thtat the time is uniform in the descriptor.

    scene.setTime(scene.time);

    // Update the clients.

    updateClients();
  }

  /**
   * Reset the selected light
   */
  public void resetSelectedLight()
  {
    // Copy the values from the selected script scene into the
    // current scenes descriptor.

    LightDescriptor light = getSelectedLight();
    tabbedPane.getSelectedScene().copyTo(light);

    // Ensure thtat the time is uniform in the descriptor.

    scene.setTime(scene.time);

    // Update the clients.

    updateClients();
  }

  /**
   * Reset the selected camera
   */
  public void resetSelectedActor()
  {
    // Copy the values from the selected script scene into the
    // current scenes descriptor.

    FieldActorDescriptor actor = getSelectedActor();
    tabbedPane.getSelectedScene().copyTo(actor);

    // Ensure thtat the time is uniform in the descriptor.

    scene.setTime(scene.time);

    // Update the clients.

    updateClients();
  }

  /**
   * Return true if the Actor has vector data.
   */
  public boolean isVector(G3DFieldActorDescriptor xactor)
  {
    return renderThread.isVector(xactor);
  }

  /**
   * Return true if the Actor has tensor data.
   */
  public boolean isTensor(G3DFieldActorDescriptor xactor)
  {
    return renderThread.isTensor(xactor);
  }

  /**
   * The bounds for the Actor.
   */
  public void getBounds(G3DFieldActorDescriptor xactor, double[] xbounds)
  {
    renderThread.getBounds(xactor, xbounds);
  }

  /**
   * Open the actor properties dialog for the selected actor
   */
  public void openSelectedActorProperties()
  {
    tabbedPane.openSelectedActorProperties();
  }

  /**
   * Open the light properties dialog for the selected light
   */
  public void openSelectedLightProperties()
  {
    ((G3DDescriptorsTabbedPane) tabbedPane).openSelectedLightProperties();
  }

  /**
   * Open the camera properties dialog for the selected camera
   */
  public void openSelectedCameraProperties()
  {
    ((G3DDescriptorsTabbedPane) tabbedPane).openSelectedCameraProperties();
  }
}
