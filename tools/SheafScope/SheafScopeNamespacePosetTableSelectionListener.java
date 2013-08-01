/**
 * Classname: SheafScopeNamespacePosetTableSelectionListener
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

import bindings.java.*;
import tools.common.event.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;

/**
 *  Class to provide a listener for table row/column list selection events
 *  and communicate the selection to a <code>FieldActorDialog</code>
 *  instance for eventual visualization.<p>
 *
 */
public class SheafScopeNamespacePosetTableSelectionListener
      extends SheafScopeAbstractTableSelectionListener
{
  /**
   * Constructor
   *
   * @param xpane The SheafScopePosetPane containing the table
   *             listener is registered with.
   */
  public SheafScopeNamespacePosetTableSelectionListener(SheafScopePosetPane xpane)
  {
    super(xpane);
  }

  /**
   * The action to be taken when a single table row
   * selection event is detected.<p>
   * 
   * @param event The detected <code>ListSelectionEvent</code>.
   *
   * 
   */
  public void valueChanged(ListSelectionEvent event)
  {
    // Ignore all events except the last.

    if(event.getValueIsAdjusting())
      return;

    updateMember();
  }

  //$$TODO: Move to another class so we create this listener from properties.
  /**
   *
   */
  private void updateMember()
  {
    //     // Get the NamespacePosetMember represented by the selected row.
    //     // At this point we don't know if we really have a SecVd.

    //     table = posetPane.getTable();

    //     SheafScopeAbstractTableModel tableModel = (SheafScopeAbstractTableModel)table.getModel();

    //     // get the selected row in the table

    //     int row = table.getSelectedRow();

    //     // get the member at selected row

    //     NamespacePosetMember rowMember = (NamespacePosetMember)tableModel.getMemberForRow(row);

    //     // Find and set the Poset member.

    //     NamespacePosetMember member = rowMember;

    //     //$$ISSUE: We are not currently doing anything here (with "member")!
  }
}
