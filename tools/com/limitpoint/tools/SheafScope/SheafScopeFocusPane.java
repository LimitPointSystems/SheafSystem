
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

package com.limitpoint.tools.SheafScope;

import com.limitpoint.bindings.java.*;
import com.limitpoint.tools.common.gui.*;
import com.limitpoint.tools.common.util.*;

import java.awt.*;
import javax.swing.*;

/**
 * The pane displaying the current "focus" poset.
 * (Currently is positioned in the lower left corner of the poset pane.)
 */
public class SheafScopeFocusPane extends SheafScopeAbstractTreePane
{
  protected Action openPosetAction;
  protected JButton openPosetButton;

  /**
   * Constructor<p>
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to display.
   * @param xmember The <code>poset_member</code> to be traversed.
   */
  public SheafScopeFocusPane(SheafScopePosetPane xposetPane, abstract_poset_member xmember)
  {
    super(xposetPane, xmember);

    try
    {
      setTitle("Cover Relation: " + xmember.host().name());
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    posetPane = xposetPane;

    // Add the tree selection listener.

    tree.addTreeSelectionListener(new SheafScopeUpdatePosetMemberCommand(xposetPane));

    createActions();

    setOpenPosetEnabled();
  }

  /**
   * Method to construct and assemble the appropriate toolBar
   * components for this pane.<p>
   *
   * @param xbar The toolbar to add the buttons to.
   *
   * 
   */
  void addToolBarButtons(JToolBar xbar)
  {
    // Add buttons defined for all TreePanes.

    super.addToolBarButtons(xbar);

    openPosetButton = xbar.add(openPosetAction);

    return;
  }

  /**
   * Method to construct and assemble the appropriate action
   * components for this pane.<p>
   *
   * 
   */
  protected void createActions()
  {
    super.createActions();

    String iconPath = SheafScopeConstants.IMAGE_PATH + "open.png";

    openPosetAction
    = new GenericAction(this,              //target
                        "openPoset",       //method
                        "Open Poset",      //action name
                        "Open Poset",      //label
                        iconPath,          //icon
                        "Open Poset");     //tooltip
  }

  /**
   * Opens a new poset and displays it in this window.<p>
   *
   * 
   */
  public void openPoset()
  {
    SheafScopeTreeNode node = getTree().getSelectedNode();

    //LPSDebug.println(" node = " + node);

    if(node != null)
    {
      // Block all user input while busy.

      posetPane.getMainPane().getParentFrame().setWaitState(true);

      // Create a new tab.

      posetPane.getDisplayPanel().createTab(node);

      // Unblock input.

      posetPane.getMainPane().getParentFrame().setWaitState(false);
    }
  }

  /**
   * Set the enabled state of the open poset button for the
   * selected node.
   */
  public void setOpenPosetEnabled()
  {
    SheafScopeTreeNode node =
      (SheafScopeTreeNode)(tree.getLastSelectedPathComponent());

    if(node != null)
    {
      try
      {
        abstract_poset_member mbr = node.getMember();
        poset_state_handle host = mbr.host();

        if((host instanceof namespace_poset) && mbr.is_jim(false))
        {
          // The selected node is a namespace jim,
          // enable the "openPosetAction".

          openPosetButton.setEnabled(true);
        }
        else
        {
          // The selected node is not a namespace jim, disable it.

          openPosetButton.setEnabled(false);
        }
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();
      }
    }
  }

  /**
   *
   */
  protected void annotate()
  {}
}
