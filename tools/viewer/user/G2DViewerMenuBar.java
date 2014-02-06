
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


package tools.viewer.user;

import tools.viewer.render.*;
import tools.viewer.common.*;
import tools.common.gui.*;

import javax.swing.*;
import javax.swing.event.*;

/**
 *
 * Specialization of <code>ViewerMenuBar</code> for
 * <code>G2DFieldActor</code>'s
 *
 */
public class G2DViewerMenuBar extends ViewerMenuBar
{
  protected ViewerMenu actorMenu;

  /**
   * Constructor
   *
   */
  public G2DViewerMenuBar(G2DViewer xviewer, G2DViewerActions xactions)
  {
    super(xviewer, xactions);

    // Create the menus of the menu bar

    actorMenu = createActorMenu();

    this.add(createEditMenu());
    this.add(actorMenu);
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

    G2DFieldActorDescriptor actor = ((G2DViewer) viewer).getSelectedActor();
    if(actor != null)
    {
      actorMenu.setEnabled(true);
    }
    else
    {
      actorMenu.setEnabled(false);
    }
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

    menu.addSeparator();

    menu.add(actions.get("BackgroundColorAction"));
    menu.add(actions.get("ForegroundColorAction"));

    menu.getPopupMenu().setLightWeightPopupEnabled(false);

    return menu;
  }
}
