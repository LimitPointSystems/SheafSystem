
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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

import tools.viewer.animation.*;
import tools.viewer.common.*;
import tools.viewer.render.*;
import tools.common.gui.*;

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
 * <code>G2DFieldActor</code>'s
 *
 */
public class G2DViewerActions extends ViewerActions
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
      // ACTOR MENU ACTIONS

      {"ActorPropertiesAction", "doActorProperties", "Edit Actor",
       "Display a dialog for editing actor properties.", null,
       null, "Alt-E", "E", "true"},
      {"BackgroundColorAction", "doBackgroundColor", "Background Color",
       "Select the background color for the plot.",
       null, null, null, null, "true"} ,
      {"ForegroundColorAction", "doForegroundColor", "Foreground Color",
       "Select the foreground color for the plot.",
       null, null, null, null, "true"} ,
    };

  // CONSTRUCTORS

  /**
   * Constructor
   *
   */
  protected G2DViewerActions(G2DViewer xviewer)
  {
    super(xviewer);

    for(int i=0; i<g3DActionSpecs.length; ++i)
    {
      put(g3DActionSpecs[i][0], new ViewerAction(this, g3DActionSpecs[i]));
    }
  }

  // ACTOR MENU ACTIONS FACET

  /**
   * Open the properties dialog for the selected actor
   */
  public void doActorProperties()
  {
    ((G2DViewer) viewer).openSelectedActorProperties();
  }

  /**
   * Set the background color of the selected actor
   */
  public void doBackgroundColor()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        CameraDescriptor camera = viewer.getScene().cameras.iterator().next();
        Color color = JColorChooser.showDialog(viewer,
                                               "Select Background Color",
                                               camera.background);

        if(color != null && !color.equals(camera.background))
          camera.background = color;
        else
          return;
      }
    }

    viewer.updateClients();
  }

  /**
   * Set the foreground color of the selected actor
   */
  public void doForegroundColor()
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        G2DFieldActorDescriptor actor = ((G2DViewer) viewer).getSelectedActor();
        Color color = JColorChooser.showDialog(viewer,
                                               "Select Foreground Color",
                                               actor.foreground);

        if(color != null && !color.equals(actor.foreground))
          actor.foreground = color;
        else
          return;
      }
    }

    viewer.updateClients();
  }
}
