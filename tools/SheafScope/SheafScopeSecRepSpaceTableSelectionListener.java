/**
 * Classname: SheafScopeSecRepSpaceTableSelectionListener
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.event.*;
import tools.common.util.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;

/**
 *  Class to provide a listener for table row/column list selection events
 *  and communicate the selection to a <code>FieldActorToolBar</code>
 *  instance for eventual visualization.<p>
 */
public class SheafScopeSecRepSpaceTableSelectionListener
      extends SheafScopeAbstractTableSelectionListener
{
  /**
   * Constructor
   *
   * @param xpane The SheafScopePosetPane containing the table
   *              listener is registered with.
   */
  public SheafScopeSecRepSpaceTableSelectionListener(SheafScopePosetPane xpane)
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

    //LPSDebug.println("event = " + event);

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
    // Get the PosetMember represented by the selected row.
    // At this point we don't know if we really have a SecVd.

    table = posetPane.getTable();

    SheafScopeAbstractTableModel tableModel
    = (SheafScopeAbstractTableModel)table.getModel();

    // Get the selected row in the table.

    int row = table.getSelectedRow();

    // Get the member at selected row.

    poset_member rowMember = (poset_member)tableModel.getMemberForRow(row);
    //SecRepSpaceMember rowMember = (SecRepSpaceMember)tableModel.getMemberForRow(row);

    // Update where appropriate if this is a rowMember SecRepSpace and
    // row is a "jim"

    if(checkIsSecRepSpace(rowMember) && (checkIsJim(row) || checkCanSelectJrm(row, rowMember)))
    {
      //LPSDebug.println("rowMember = " + rowMember);

      sec_vd member = (sec_vd)rowMember;

      // Notify the action handler that a field has been updated.

      posetPane.getMainPane().setSection(member);

      updatePaneDisplay(member);

      // Clear the selection once the field is given to the action handler.
      // This allows the user to reselect the table entry.

      table.clearSelection();
    }
  }
}
