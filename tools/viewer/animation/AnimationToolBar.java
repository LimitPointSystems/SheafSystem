
/**
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
 * 
 */


package tools.viewer.animation;

import tools.viewer.user.*;
import tools.viewer.common.*;
import tools.common.gui.*;

import javax.swing.*;
import javax.swing.event.*;


/**
 *
 * Implementation of <code>JToolBar</code> which contains the controls for
 * the <code>Animation</code>
 *
 */
public class AnimationToolBar extends ViewerToolBar
{
  /**
   * The <code>Script</code>
   */
  protected Script script;

  /**
   * The edit mode <code>JToogleButton</code>
   */
  protected JToggleButton editButton;

  /**
   * The edit mode action
   */
  protected ViewerAction editAction;

  /**
   * Go to the first scene of the animation
   */
  protected ViewerAction startAction;

  /**
   * Go to the previous scene in the animation.
   */
  protected ViewerAction previousAction;

  /**
   * Record the animation
   */
  protected ViewerAction recordAction;

  /**
   * Play the animation
   */
  protected ViewerAction playAction;

  /**
   * Pause the animation
   */
  protected ViewerAction pauseAction;

  /**
   * Go to the next scene in the animation
   */
  protected ViewerAction nextAction;

  /**
   * Go to the final scene in the animation
   */
  protected ViewerAction endAction;

  /**
   * The <code>TimeSlider</code>
   */
  protected TimeSlider timeSlider;

  /**
   * Constructor
   *
   */
  public AnimationToolBar(Viewer xviewer)
  {
    super(xviewer);

    setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));

    //$$HACK (WEM):
    ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);

    // Create and add the edit action

    editAction = new ViewerAction(viewer, "Edit Script", "editScript",
                                  "Edit Script", "Toggle the Edit Script Mode",
                                  "Toggle the Edit Script Mode",
                                  ViewerConstants.IMAGE_PATH+"EditProps.png",
                                  null, null, "true");

    editButton = this.addToggle(editAction);

    // Add Separator

    this.addSeparator();

    // Create and add the VCR control actions

    startAction = new ViewerAction(viewer, "Start Scene", "startScene",
                                   "Start Scene", "Go to the Start Scene",
                                   "Go to the Start Scene",
                                   ViewerConstants.IMAGE_PATH+"Start.png",
                                   null, null, "true");
    this.add(startAction);

    previousAction = new ViewerAction(viewer, "Previous Scene", "previousScene",
                                      "Previous Scene", "Go to the Previous Scene",
                                      "Go to the Previous Scene",
                                      ViewerConstants.IMAGE_PATH+"Previous.png",
                                      null, null, "true");
    this.add(previousAction);

    recordAction = new ViewerAction(viewer, "Record", "record",
                                    "Record", "Record the Animation",
                                    "Record the Animation",
                                    ViewerConstants.IMAGE_PATH+"Record.png",
                                    null, null, "true");
    this.add(recordAction);

    playAction = new ViewerAction(viewer, "Play", "play",
                                  "Play", "Play the Animation",
                                  "Play the Animation",
                                  ViewerConstants.IMAGE_PATH+"Play.png",
                                  null, null, "true");
    this.add(playAction);

    pauseAction = new ViewerAction(viewer, "Pause", "pause",
                                   "Pause", "Pause the Animation",
                                   "Pause the Animation",
                                   ViewerConstants.IMAGE_PATH+"Pause.png",
                                   null, null, "true");
    this.add(pauseAction);

    nextAction = new ViewerAction(viewer, "Next Scene", "nextScene",
                                  "Next Scene", "Go to the Next Scene",
                                  "Go to the Next Scene",
                                  ViewerConstants.IMAGE_PATH+"Next.png",
                                  null, null, "true");
    this.add(nextAction);

    endAction = new ViewerAction(viewer, "End Scene", "endScene",
                                 "End Scene", "Go to the End Scene",
                                 "Go to the End Scene",
                                 ViewerConstants.IMAGE_PATH+"End.png",
                                 null, null, "true");
    this.add(endAction);

    // Add Separator

    this.addSeparator();

    // Create and add the time slider

    timeSlider = new TimeSlider(viewer);

    this.add(timeSlider);
  }

  /**
   * Set the <code>Script</code>
   *
   * @param xscript The script
   */
  public void setScript(Script xscript)
  {
    script = xscript;

    if(script.minTime == script.maxTime)
      setEnabled(false);
    else
      setEnabled(true);
  }

  /**
   * Set the edit mode.
   */
  public void setEditMode(boolean xmode)
  {
    editButton.setSelected(xmode);

    if(script.minTime != script.maxTime)
      setEnabled(!xmode);
  }

  /**
   * Override <code>setEnabled()</code>
   */
  public void setEnabled(boolean xenabled)
  {
    startAction.setEnabled(xenabled);
    previousAction.setEnabled(xenabled);
    playAction.setEnabled(xenabled);
    recordAction.setEnabled(xenabled);
    pauseAction.setEnabled(xenabled);
    nextAction.setEnabled(xenabled);
    endAction.setEnabled(xenabled);
    timeSlider.setEnabled(xenabled);
  }

  /**
   * Set the play mode
   */
  public void setPlayMode(boolean xmode)
  {
    editAction.setEnabled(!xmode);
    startAction.setEnabled(!xmode);
    previousAction.setEnabled(!xmode);
    playAction.setEnabled(!xmode);
    recordAction.setEnabled(!xmode);
    nextAction.setEnabled(!xmode);
    endAction.setEnabled(!xmode);
    timeSlider.setEnabled(!xmode);
  }

  /**
   * The <code>TimeSlider</code>
   */
  public TimeSlider getTimeSlider()
  {
    return timeSlider;
  }
}
