
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

import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.common.gui.*;

import javax.swing.*;
import javax.swing.event.*;

/**
 *
 * Specialization of <code>ViewerMenuBar</code> for
 * <code>G3DFieldActor</code>'s
 *
 */
public class G3DViewerMenuBar extends ViewerMenuBar
{
  protected ViewerMenu actorMenu;

  protected JRadioButtonMenuItem[] pointLabelsItems = new JRadioButtonMenuItem[3];

  protected JRadioButtonMenuItem[] cellLabelsItems = new JRadioButtonMenuItem[3];

  protected JRadioButtonMenuItem perspectiveItem;
  protected JRadioButtonMenuItem orthogonalItem;

  protected JRadioButtonMenuItem joystickItem;
  protected JRadioButtonMenuItem trackballItem;
  protected JRadioButtonMenuItem cameraItem;
  protected JRadioButtonMenuItem actorItem;

  /**
   * Constructor
   *
   */
  public G3DViewerMenuBar(G3DViewer xviewer, G3DViewerActions xactions)
  {
    super(xviewer, xactions);

    // Create the menus of the menu bar

    actorMenu = createActorMenu();

    this.add(createEditMenu());
    this.add(actorMenu);
    this.add(createLightMenu());
    this.add(createCameraMenu());
    this.add(createInteractionsMenu());
    this.add(createScriptMenu());

    this.add(Box.createHorizontalGlue());
    this.add(createHelpMenu());
  }

  /**
   * Update the selected menu items to the selected descriptors.
   */
  public void update()
  {
    // ACTOR

    G3DFieldActorDescriptor actor = ((G3DViewer) viewer).getSelectedActor();
    if(actor != null)
    {
      actorMenu.setEnabled(true);

      pointLabelsItems[actor.pointLabels].setSelected(true);
      cellLabelsItems[actor.cellLabels].setSelected(true);
    }
    else
    {
      actorMenu.setEnabled(false);
    }

    // CAMERA

    CameraDescriptor camera = ((G3DViewer) viewer).getSelectedCamera();

    if(camera.projection)
      orthogonalItem.setSelected(true);
    else
      perspectiveItem.setSelected(true);

    // SCENE

    SceneDescriptor scene = viewer.getScene();

    if(scene.interactorStyle[0] == ViewerConstants.JOYSTICK_INTERACTOR)
      joystickItem.setSelected(true);
    else
      trackballItem.setSelected(true);

    if(scene.interactorStyle[1] == ViewerConstants.CAMERA_INTERACTOR)
      cameraItem.setSelected(true);
    else
      actorItem.setSelected(true);
  }

  // EDIT MENU

  /**
   *
   */
  protected ViewerMenu createEditMenu()
  {

    ViewerMenu menu = new ViewerMenu(viewer, "Edit");
    menu.setMnemonic('t');

    menu.add(actions.get("CloneAction"));

    menu.addSeparator();

    menu.add(actions.get("ProbeAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  // ACTORS MENU

  /**
   *
   */
  protected ViewerMenu createActorMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Actor");
    menu.setMnemonic('A');

    menu.add(actions.get("ActorPropertiesAction"));
    menu.add(actions.get("ResetActorAction"));

    menu.addSeparator();

    // Point labels.

    ButtonGroup pointLabelsGroup = new ButtonGroup();

    ViewerMenu pointLabelsMenu = new ViewerMenu(viewer, "Point Labels");
    pointLabelsMenu.setMnemonic('P');

    pointLabelsItems[0] = new JRadioButtonMenuItem(actions.get("NoIdsPointLabelsAction"));
    pointLabelsMenu.add(pointLabelsItems[0]);
    pointLabelsGroup.add(pointLabelsItems[0]);

    pointLabelsItems[1] = new JRadioButtonMenuItem(actions.get("TopIdsPointLabelsAction"));
    pointLabelsMenu.add(pointLabelsItems[1]);
    pointLabelsGroup.add(pointLabelsItems[1]);

    pointLabelsItems[2] = new JRadioButtonMenuItem(actions.get("DiscIdsPointLabelsAction"));
    pointLabelsMenu.add(pointLabelsItems[2]);
    pointLabelsGroup.add(pointLabelsItems[2]);

    pointLabelsMenu.getPopupMenu().setLightWeightPopupEnabled(false);
    menu.add(pointLabelsMenu);

    // Cell labels.

    ButtonGroup cellLabelsGroup = new ButtonGroup();

    ViewerMenu cellLabelsMenu = new ViewerMenu(viewer, "Cell Labels");
    cellLabelsMenu.setMnemonic('C');

    cellLabelsItems[0] = new JRadioButtonMenuItem(actions.get("NoIdsCellLabelsAction"));
    cellLabelsMenu.add(cellLabelsItems[0]);
    cellLabelsGroup.add(cellLabelsItems[0]);

    cellLabelsItems[1] = new JRadioButtonMenuItem(actions.get("TopIdsCellLabelsAction"));
    cellLabelsMenu.add(cellLabelsItems[1]);
    cellLabelsGroup.add(cellLabelsItems[1]);

    cellLabelsItems[2] = new JRadioButtonMenuItem(actions.get("EvalIdsCellLabelsAction"));
    cellLabelsMenu.add(cellLabelsItems[2]);
    cellLabelsGroup.add(cellLabelsItems[2]);

    cellLabelsMenu.getPopupMenu().setLightWeightPopupEnabled(false);
    menu.add(cellLabelsMenu);

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  // LIGHTS MENU

  /**
   *
   */
  protected ViewerMenu createLightMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Light");
    menu.setMnemonic('L');

    menu.add(actions.get("LightPropertiesAction"));
    menu.add(actions.get("ResetLightAction"));

    menu.addSeparator();

    menu.add(actions.get("LightColorAction"));
    menu.add(actions.get("LightIntensityAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  // CAMERA MENU

  /**
   *
   */
  protected ViewerMenu createCameraMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Camera");
    menu.setMnemonic('C');

    menu.add(actions.get("CameraPropertiesAction"));
    menu.add(actions.get("ResetCameraAction"));

    menu.addSeparator();

    menu.add(actions.get("ResetViewAction"));
    menu.add(actions.get("SelectBackgroundColorAction"));

    menu.addSeparator();

    menu.add(createProjectionsMenu());

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createProjectionsMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Projections");
    menu.setMnemonic('P');

    ButtonGroup group = new ButtonGroup();

    perspectiveItem = new JRadioButtonMenuItem(actions.get("PerspectiveAction"));
    group.add(perspectiveItem);
    menu.add(perspectiveItem);
    perspectiveItem.setSelected(true);

    orthogonalItem = new JRadioButtonMenuItem(actions.get("OrthogonalAction"));
    group.add(orthogonalItem);
    menu.add(orthogonalItem);

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createInteractionsMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Interactions");
    menu.setMnemonic('I');

    menu.add(createTrackballJoystickMenu());

    menu.addSeparator();

    menu.add(createCameraActorStyleMenu());

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createTrackballJoystickMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Trackball/Joystick");

    ButtonGroup group = new ButtonGroup();

    trackballItem = new JRadioButtonMenuItem(actions.get("TrackballStyleAction"));
    group.add(trackballItem);
    menu.add(trackballItem);

    joystickItem = new JRadioButtonMenuItem(actions.get("JoystickStyleAction"));
    group.add(joystickItem);
    menu.add(joystickItem);

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }

  /**
   *
   */
  protected ViewerMenu createCameraActorStyleMenu()
  {
    ViewerMenu menu = new ViewerMenu(viewer, "Camera/Actor");

    ButtonGroup group = new ButtonGroup();

    cameraItem = new JRadioButtonMenuItem(actions.get("CameraStyleAction"));
    group.add(cameraItem);
    menu.add(cameraItem);

    actorItem = new JRadioButtonMenuItem(actions.get("ActorStyleAction"));
    group.add(actorItem);
    menu.add(actorItem);

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }
}
