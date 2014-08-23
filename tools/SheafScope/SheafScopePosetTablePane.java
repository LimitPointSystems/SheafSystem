
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

import bindings.java.*;
import com.limitpoimt.tools.common.gui.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

/**
 * SheafScopePosetTablePane specializes the <code>JPanel</code> class to
 * meet the needs of the SheafScope.<p>
 */
public class SheafScopePosetTablePane extends SheafScopeAbstractTablePane
{
  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> for the table.
   * @param xmember The <code>abstract_poset_member</code> to traverse.
   */
  public SheafScopePosetTablePane(SheafScopePosetPane xposetPane,
                                  abstract_poset_member xmember)
  {
    super(xposetPane, xmember);
  }

  /**
   * Instantiates a new object of class <code>SheafScopeJTable</code>
   * with a instance of <code>SheafScopePosetTableModel</code> as model.<p>
   *
   * 
   */
  protected void makeTable()
  {
    tableModel = new SheafScopePosetTableModel(member);

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
    table.getSelectionModel()
    .addListSelectionListener(new SheafScopePosetTableSelectionListener(posetPane));


    table.setDefaultRenderer(table.getColumnClass(0),
                             new SheafScopeTableCellRenderer());

    setColumnSizes();
  }
}
