/**
 * Classname: SheafScopeNamespacePosetTablePane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.gui.*;
import tools.common.util.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

/**
 * SheafScopeNamespacePosetTablePane specializes the <code>JPanel</code>
 * class to meet the needs of the SheafScope.<p>
 */
public class SheafScopeNamespacePosetTablePane extends SheafScopeAbstractTablePane
{
  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> for the table.
   * @param xmember The <code>abstract_poset_member</code> to traverse.
   */
  public SheafScopeNamespacePosetTablePane(SheafScopePosetPane xposetPane,
      abstract_poset_member xmember)
  {
    super(xposetPane, xmember);
  }

  /**
   * Instantiates a new object of class <code>SheafScopeJTable</code>
   * with a instance of <code>SheafScopeNamespacePosetTableModel</code> as model.<p>
   *
   * 
   */
  protected void makeTable()
  {
    tableModel = new SheafScopeNamespacePosetTableModel((namespace_poset_member)member);

    table = new SheafScopeJTable(tableModel);

    // Get the currently selected node.

    SheafScopeTreeNode focusNode = getFocusPane().getSelectedNode();

    // Get an enumeration over the node's children.

    Enumeration itr = focusNode.preorderEnumeration();

    // Refresh the table.

    tableModel.refresh(itr, selectedName);

    // Set some of the table attributes.

    table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    table.setRowSelectionAllowed(true);

    SheafScopeNamespacePosetTableSelectionListener sl
    = new SheafScopeNamespacePosetTableSelectionListener(posetPane);

    table.getSelectionModel().addListSelectionListener(sl);

    table.setDefaultRenderer(table.getColumnClass(0),
                             new SheafScopeTableCellRenderer());

    setColumnSizes();
  }
}
