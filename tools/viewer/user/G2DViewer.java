
/**
 * Classname: G2DViewer
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: G2DViewer.java,v $ $Revision: 1.9 $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
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
 * <code>G2DFieldActor</code>'s
 *
 */
public class G2DViewer extends Viewer
{
  /**
   * The probe dialog
   */
  protected ProbeDialog probeDialog;

  /**
   * Constructor
   */
  public G2DViewer(FieldActorDescriptor xactor)
  {
    super("2D Viewer", xactor);
  }

  /**
   * Constructor
   */
  public G2DViewer(Integer id, FieldActorDescriptor xactor)
  {
    super("2D Viewer " + id.toString(), xactor);
  }

  /**
   * Constructor
   */
  public G2DViewer(String xtitle, FieldActorDescriptor xactor)
  {
    super(xtitle, xactor);
  }

  /**
   * Constructor
   */
  public G2DViewer(Script xscript)
  {
    super("2D Viewer", xscript);
  }

  /**
   * Constructor
   */
  public G2DViewer(Integer id, Script xscript)
  {
    super("2D Viewer " + id.toString(), xscript);
  }

  /**
   * Constructor
   */
  public G2DViewer(String xtitle, Script xscript)
  {
    super(xtitle, xscript);
  }

  /**
   * Constructor
   */
  public G2DViewer(File xscriptFile) throws IOException
  {
    super("2D Viewer", xscriptFile);
  }

  /**
   * Constructor
   */
  public G2DViewer(Integer id, File xscriptFile) throws IOException
  {
    super("2D Viewer " + id.toString(), xscriptFile);
  }

  /**
   * Constructor
   */
  public G2DViewer(String xtitle, File xscriptFile) throws IOException
  {
    super(xtitle, xscriptFile);
  }

  // VIEWER FACET

  /**
   * Make a clone of this <code>Viewer</code> and display it.
   */
  public void cloneViewer()
  {
    G2DViewer viewer = new G2DViewer(script.clone());
    viewer.setVisible(true);
  }

  /**
   * Create a default <code>Script</code>
   */
  protected Script createDefaultScript(FieldActorDescriptor xactor)
  {
    SceneDescriptor lscene = new SceneDescriptor();

    if(xactor != null)
    {
      xactor.selected = true;
      lscene.actors.add(xactor);
    }

    CameraDescriptor camera = new CameraDescriptor();
    camera.selected = true;
    lscene.cameras.add(camera);

    LightDescriptor light = new LightDescriptor();
    light.selected = true;
    lscene.lights.add(light);

    lscene.selected = true;

    Script result = new Script(this);
    result.add(lscene);

    return result;
  }

  /**
   * Add a <code>FieldActorDescriptor</code>.
   */
  public boolean addFieldActor(FieldActorDescriptor xactor)
  {
    G2DFieldActorDescriptor actor = (G2DFieldActorDescriptor) xactor;

    return ((G2DDescriptorsTabbedPane) tabbedPane).addFieldActor(actor);
  }

  /**
   * Create the <code>ViewerMenuBar</code>
   */
  protected ViewerMenuBar createMenuBar()
  {
    G2DViewerActions actions = new G2DViewerActions(this);

    return new G2DViewerMenuBar(this, actions);
  }

  /**
   * Create the <code>DescriptorsTabbedPane</code>.
   */
  protected DescriptorsTabbedPane createTabbedPane()
  {
    return new G2DDescriptorsTabbedPane(this);
  }

  /**
   * Pick xposition
   */
  public void pick(double[] xposition)
  {
    // NOT IMPLEMENTED
  }

  // G2D VIEWER FACET

  /**
   * The selected actor
   */
  public G2DFieldActorDescriptor getSelectedActor()
  {
    return (G2DFieldActorDescriptor) tabbedPane.getSelectedActor();
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
   * Open the actor properties dialog for the selected actor
   */
  public void openSelectedActorProperties()
  {
    tabbedPane.openSelectedActorProperties();
  }
}
