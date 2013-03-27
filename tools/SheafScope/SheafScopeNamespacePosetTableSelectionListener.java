/**
 * Classname: SheafScopeNamespacePosetTableSelectionListener
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeNamespacePosetTableSelectionListener.java,v $ $Revision: 1.15 $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
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
