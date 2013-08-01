
/**
 * Classname: SheafScopeSchemaSelectionListener
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
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

package tools.SheafScope;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;


/**
 * SheafScopeSchemaSelectionListener is a specialized <code>TreeSelectionListener</code> to
 * suit the needs of the SheafScope. Listens for single node selections on the
 * tree and updates the table model accordingly.<p> 
 */
public class SheafScopeSchemaSelectionListener extends MouseAdapter
{

  private SheafScopePosetPane posetPane;
  //private SheafScopeFiberSchemaPane pane;

  /**
   * Constructor
   * @param xpane The SheafScopePosetPane containing the tree this listener 
   *              is registered on.
   */
  public SheafScopeSchemaSelectionListener(SheafScopePosetPane xpane)
  {
    //$$TODO: "target" is pane, so pass it in to CTOR.

    // Precondition: pane != null.

    posetPane = xpane;
    //pane = posetPane.getFiberSchemaPane();
  }

  /**
   * The action to be taken when a single mouse click
   * event is detected.<p>
   * We only want to call restrictTo if the user clicked on a node;
   * ignore programmatic selections.<p>
   *
   * @param xevent The detected <code>MouseEvent</code>.
   *
   * 
   */
  public void mouseClicked(MouseEvent xevent)
  {
    SheafScopeFiberSchemaPane pane = posetPane.getFiberSchemaPane();

    if(pane == null)
      return;

    pane.doRestrictTo(xevent);
  }
}
