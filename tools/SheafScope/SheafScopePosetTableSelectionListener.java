/**
 * Classname: SheafScopePosetTableSelectionListener
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopePosetTableSelectionListener.java,v $ $Revision: 1.16 $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import tools.common.event.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;

/**
 *  Class to provide a listener for table row/column list selection events
 *  and communicate the selection to a <code>FieldActorDialog</code>
 *  instance for eventual visualization.<p>
 */
public class SheafScopePosetTableSelectionListener
      extends SheafScopeAbstractTableSelectionListener
{
  /**
   * Constructor
   *
   * @param xpane The SheafScopePosetPane containing the table
   *             listener is registered with.
   */
  public SheafScopePosetTableSelectionListener(SheafScopePosetPane xpane)
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
    // Get the PosetMember represented by the selected row.
    // At this point we don't know if we really have a SecVd.

    //table = posetPane.getTable();

    //SheafScopeAbstractTableModel tableModel = (SheafScopeAbstractTableModel)table.getModel();

    // Get the selected row in the table.

    //int row = table.getSelectedRow();

    // Get the member at selected row.

    //PosetMember rowMember = (PosetMember)tableModel.getMemberForRow(row);

    // Find and set the Poset member.

    //PosetMember member = rowMember;

    //$$ISSUE: We are not currently doing anything here (with "member")!
  }
}
