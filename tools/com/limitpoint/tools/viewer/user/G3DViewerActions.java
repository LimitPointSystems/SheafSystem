
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

import com.limitpoint.tools.viewer.animation.*;
import com.limitpoint.tools.viewer.common.*;
import com.limitpoint.tools.viewer.render.*;
import com.limitpoint.tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 *
 * Specialization of <code>ViewerActions</code> for
 * <code>G3DFieldActor</code>'s
 *
 */
public class G3DViewerActions extends ViewerActions
{
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
  // 3. tooltip text
  // 4. icon path
  // 5. accelerator key
  // 6. mnemonic
  // 7. is enabled: "true" or "false"

  static final String[][] g3DActionSpecs =
    {
      // EDIT MENU ACTIONS

      {"ProbeAction", "doProbe", "Show Probe Panel",
       "Display a dialog for point and cell information.", null,
       null, "Alt-P", "P", "true"},

      // ACTOR MENU ACTIONS

      {"ActorPropertiesAction", "doActorProperties", "Edit Actor",
       "Display a dialog for editing actor properties.", null,
       null, "Alt-E", "E", "true"},

      {"ResetActorAction", "doResetActor", "Reset Actor",
       "Reset actor to the original scene values.", null,
       null, "Alt-R", "R", "true"},

      // POINT LABELS SUBMENU ACTIONS

      {"NoIdsPointLabelsAction", "doNoIdsPointLabels", "No Ids",
       "No Id Point Labels", null, null, "Alt-N", "N", "true"},
      {"TopIdsPointLabelsAction", "doTopIdsPointLabels", "Top Ids",
       "Top Id Point Labels", null, null, "Alt-T", "T", "true"},
      {"DiscIdsPointLabelsAction", "doDiscIdsPointLabels",
       "Disc Ids", "Discretization Id Point Labels",
       null, null, "Alt-D", "D", "true"},

      // CELL LABELS SUBMENU ACTIONS

      {"NoIdsCellLabelsAction", "doNoIdsCellLabels", "No Ids",
       "No Id Cell Labels", null, null, "Alt-N", "N", "true"},
      {"TopIdsCellLabelsAction", "doTopIdsCellLabels", "Top Ids",
       "Top Id Cell Labels", null, null, "Alt-T", "T", "true"},
      {"EvalIdsCellLabelsAction", "doEvalIdsCellLabels",
       "Eval Ids", "Evaluation Id Cell Labels",
       null, null, "Alt-E", "E", "true"},

      // LIGHT MENU ACTIONS

      {"LightPropertiesAction", "doLightProperties", "Edit Light",
       "Display a dialog for editing light properties.", null,
       null, "Alt-E", "E", "true"},

      {"ResetLightAction", "doResetLight", "Reset Light",
       "Reset light to the original scene values.", null,
       null, "Alt-R", "R", "true"},

      {"LightColorAction", "doEditLightColor", "Edit Color",
       "Display a dialog for editing the light color", null,
       null, "Alt-C", "C", "true"},

      {"LightIntensityAction", "doEditLightIntensity", "Edit Intensity",
       "Display a dialog for editing the light intensity", null,
       null, "Alt-I", "I", "true"},

      // CAMERA MENU ACTIONS

      {"CameraPropertiesAction", "doCameraProperties", "Edit Camera",
       "Display a dialog for editing camera properties.", null,
       null, "Alt-E", "E", "true"},

      {"ResetCameraAction", "doResetCamera", "Reset Camera",
       "Reset camera to the original scene values.", null,
       null, "Alt-R", "R", "true"},

      {"ResetViewAction", "doResetView", "Auto View",
       "Automatically set the view so all props are visible", null,
       null, "Alt-A", "A", "true"},

      // PROJECTIONS SUBMENU ACTIONS

      {"PerspectiveAction", "doPerspective", "Perspective", null, null, null, "Alt-V", null, "true"},
      {"OrthogonalAction", "doOrthogonal", "Orthogonal", null, null, null, "Alt-O", null, "true"},

      {"SelectBackgroundColorAction", "selectBackgroundColor", "Background Color",
       "Select the background color.", null,
       null, "Alt-B", "B", "true"},

      // INTERACTION MENU ACTIONS

      {"TrackballStyleAction", "doTrackballStyle", "Trackball", null, null, null, "Alt-T", "T", "true"},
      {"JoystickStyleAction", "doJoystickStyle", "Joystick", null, null, null, "Alt-J", "J", "false"},
      {"CameraStyleAction", "doCameraStyle", "Camera", null, null, null, "Alt-C", "C", "true"},
      {"ActorStyleAction", "doActorStyle", "Actor", null, null, null, "Alt-A", null, "false"},
    };

  // CONSTRUCTORS

  /**
   * Constructor
   *
   */
  protected G3DViewerActions(G3DViewer xviewer)
  {
    super(xviewer);

    for(int i=0; i<g3DActionSpecs.length; ++i)
    {
      put(g3DActionSpecs[i][0], new ViewerAction(this, g3DActionSpecs[i]));
    }
  }

  /**
   * Open the probe dialog
   */
  public void doProbe()
  {
    ((G3DViewer) viewer).openProbe();
  }


  // ACTOR MENU ACTIONS FACET

  /**
   * Open the properties dialog for the selected actor
   */
  public void doActorProperties()
  {
    ((G3DViewer) viewer).openSelectedActorProperties();
  }

  /**
   * Reset the actor values.
   */
  public void doResetActor()
  {
    ((G3DViewer) viewer).resetSelectedActor();
  }

  // POINT LABEL SUBMENU ACTIONS FACET

  /**
   * Set point labels to no ids.
   */
  public void doNoIdsPointLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.pointLabels = ViewerConstants.NO_IDS;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set point labels to top ids.
   */
  public void doTopIdsPointLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.pointLabels = ViewerConstants.TOP_IDS;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set point labels to disc/eval ids.
   */
  public void doDiscIdsPointLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.pointLabels = ViewerConstants.DISC_EVAL_IDS;
      }
    }

    viewer.updateClients();
  }

  // CELL LABEL SUBMENU ACTIONS FACET

  /**
   * Set cell labels to no ids.
   */
  public void doNoIdsCellLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.cellLabels = ViewerConstants.NO_IDS;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set cell labels to top ids.
   */
  public void doTopIdsCellLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.cellLabels = ViewerConstants.TOP_IDS;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set cell labels to disc/eval ids.
   */
  public void doEvalIdsCellLabels()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.cellLabels = ViewerConstants.DISC_EVAL_IDS;
      }
    }

    viewer.updateClients();
  }


  // DISPLAY SUBMENU ACTIONS FACET

  /**
   * Set to point representation of the selected actor
   */
  public void doPointsRepresentation()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.displayStyle = ViewerConstants.POINT_STYLE;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set to wire frame representation of the selected actor
   */
  public void doWireframeRepresentation()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.displayStyle = ViewerConstants.LINE_STYLE;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set to surface representation of the selected actor
   */
  public void doSurfaceRepresentation()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
        actor.displayStyle = ViewerConstants.SURFACE_STYLE;
      }
    }

    viewer.updateClients();
  }

  // LIGHT MENU ACTIONS FACET

  /**
   * Open the property dialog for the selected light
   */
  public void doLightProperties()
  {
    ((G3DViewer) viewer).openSelectedLightProperties();
  }

  /**
   * Reset the light values.
   */
  public void doResetLight()
  {
    ((G3DViewer) viewer).resetSelectedLight();
  }

  /**
   * Edit the color of the selected light
   */
  public void doEditLightColor()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        LightDescriptor light = ((G3DViewer) viewer).getSelectedLight();
        Color color = JColorChooser.showDialog(viewer, "Select Light Color",
                                               light.color);
        if(color != null && !color.equals(light.color))
          light.color = color;
        else
          return;
      }
    }

    viewer.updateClients();
  }

  /**
   * Edit the intensity of the selected light
   */
  public void doEditLightIntensity()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        LightDescriptor light = ((G3DViewer) viewer).getSelectedLight();
        Double d = getDoubleFromDialog(light.intensity,
                                       "Light Intensity:",
                                       "Edit Light Intensity");
        if(d != null)
          light.intensity = d.doubleValue();
        else
          return;
      }
    }

    viewer.updateClients();
  }

  // CAMERA MENU ACTIONS FACET

  /**
   * Open the properties dialog for the selected camera
   */
  public void doCameraProperties()
  {
    ((G3DViewer) viewer).openSelectedCameraProperties();
  }

  /**
   * Reset the camera values.
   */
  public void doResetCamera()
  {
    ((G3DViewer) viewer).resetSelectedCamera();
  }

  /**
   * Reset the view of the selected camera
   */
  public void doResetView()
  {
    viewer.resetView();
  }

  // PROJECTIONS SUBMENU ACTIONS FACET

  /**
   * Set the projection of the selected camera to perspective (false)
   */
  public void doPerspective()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        CameraDescriptor camera = ((G3DViewer) viewer).getSelectedCamera();
        camera.projection = false;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set the projection of the selected camera to orthogonal (true)
   */
  public void doOrthogonal()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        CameraDescriptor camera = ((G3DViewer) viewer).getSelectedCamera();
        camera.projection = true;
      }
    }

    viewer.updateClients();
  }


  /**
   * Select the background color of the selected camera.
   */
  public void selectBackgroundColor()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        CameraDescriptor camera = ((G3DViewer) viewer).getSelectedCamera();
        Color color = JColorChooser.showDialog(viewer, "Select Background Color",
                                               camera.background);
        if(color != null && !color.equals(camera.background))
          camera.background = color;
        else
          return;
      }
    }

    viewer.updateClients();
  }

  // INTERACTION MENU ACTIONS FACET

  /**
   * Set the interactor style to trackball
   */
  public void doTrackballStyle()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        viewer.getScene().interactorStyle[0] = ViewerConstants.TRACKBALL_INTERACTOR;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set the interactor style to joystick
   */
  public void doJoystickStyle()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        viewer.getScene().interactorStyle[0] = ViewerConstants.JOYSTICK_INTERACTOR;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set the interactor style to actor
   */
  public void doActorStyle()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        viewer.getScene().interactorStyle[1] = ViewerConstants.ACTOR_INTERACTOR;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set the interactor style to camera
   */
  public void doCameraStyle()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        viewer.getScene().interactorStyle[1] = ViewerConstants.CAMERA_INTERACTOR;
      }
    }

    viewer.updateClients();
  }

  /**
   * Convenience method. Returns dialog value as Double unless
   * user cancels or the value input to the test field is the
   * same as currentValue in which case it returns null.
   * 
   */
  protected Double getDoubleFromDialog(double currentValue,
                                       String message,
                                       String title)
  {
    Double result = null;

    //$$ISSUE: Using InputDialog just to get something working.
    //         Eventually should create a custom dialog and use
    //         JFormattedTextField.

    String valueString = Double.toString(currentValue);

    Object obj = JOptionPane.showInputDialog(viewer, message, title,
                 JOptionPane.QUESTION_MESSAGE,
                 null, null, valueString);
    if(obj != null)
    {
      try
      {
        String value = (String)obj;
        double newValue = Double.parseDouble(value);

        if(currentValue != newValue)
        {
          result = new Double(newValue);
        }
      }
      catch(NumberFormatException e)
      {
        System.out.println(e);
      }
    }

    return result;
  }
}
