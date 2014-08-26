
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

import com.limitpoint.tools.viewer.render.*;

import javax.swing.*;

/**
 *
 * Abstract implementation of <code>JTabbedPane</code> for
 * containing the script panels for the <code>Viewer</code>
 *
 */
public class DescriptorsTabbedPane extends JTabbedPane
{
  /**
   * The scene list panel
   */
  protected ScenePanel scenePanel;

  /**
   * The actor list panel
   */
  protected FieldActorPanel actorPanel;

  /**
   * Default constructor
   */
  protected DescriptorsTabbedPane(Viewer xviewer)
  {
    scenePanel = new ScenePanel(xviewer);
    add
      ("Script", scenePanel);

    actorPanel = new FieldActorPanel(xviewer);
    add
      ("Actors", actorPanel);
  }

  /**
   * Refresh the scene panel.
   */
  public void refreshScene()
  {
    scenePanel.refresh();
  }

  /**
   * Set the script edit mode
   */
  public void editScriptModeChanged()
  {
    scenePanel.editScriptModeChanged();
    actorPanel.editScriptModeChanged();
  }

  /**
   * Set the enabled state of this <code>DescriptorsTabbedPane</code>
   * and the descriptor panels.
   */
  public void setEnabled(boolean xenabled)
  {
    super.setEnabled(xenabled);

    scenePanel.setEnabled(xenabled);
    actorPanel.setEnabled(xenabled);
  }

  /**
   * Set the scene
   */
  public void setScene(SceneDescriptor xscene)
  {
    scenePanel.setScene(xscene);

    update();
  }

  /**
   * The selected scene
   */
  public SceneDescriptor getSelectedScene()
  {
    return scenePanel.getSelectedScene();
  }

  /**
   * Update the descriptor panels
   */
  public void update()
  {
    actorPanel.update();
  }

  /**
   * The selected actor
   */
  public FieldActorDescriptor getSelectedActor()
  {
    return actorPanel.getSelectedActor();
  }

  /**
   * Open the actor properties dialog for the selected actor
   */
  public void openSelectedActorProperties()
  {
    actorPanel.openSelectedProperties();
  }

  /**
   * Add a <code>FieldActorDescriptor</code>.
   */
  public boolean addFieldActor(FieldActorDescriptor xactor)
  {
    return actorPanel.addFieldActor(xactor);
  }
}
