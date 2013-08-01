/**
 * Classname: SheafScopeFiberSchemaPane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:52 $
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

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

/**
 * SheafScopeFiberSchemaPane is the base pane to display fiber schema.
 */
public class SheafScopeFiberSchemaPane extends SheafScopeAbstractTreePane
{

  private int lastRow = -1;

  /**
   * Constructor<p>
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to be displayed.
   * @param xhost The host of the member to be traversed.
   * @param xindex The index of the member to be traversed.
   */
  public SheafScopeFiberSchemaPane(SheafScopePosetPane xposetPane,
				   poset_state_handle xhost,
				   scoped_index xindex)
  {
    super(xposetPane, new schema_poset_member(xhost, xindex));

    String name = "N/A";
    try
    {
      name = member.name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    setTitle("Fiber Schema: " + name);

    //
    // $$TODO: Remove restriction entirely from the fiber schema.
    //

    //SheafScopeSchemaSelectionListener listener = new SheafScopeSchemaSelectionListener(xposetPane);

    //tree.addMouseListener(listener);
    tree.setSelectionRow(tree.getRowCount());
  }

  /**
   * Detach the member of this pane and the members of its tree.
   */
  public void detachStates()
  {
    member.detach_from_state();

    super.detachStates();
  }

  /**
   *
   */
  public void doRestrictTo(MouseEvent event)
  {
    // Get node from event position.

    JTree tree = getTree();

    int row = tree.getRowForLocation(event.getX(), event.getY());

    if((row == -1) || (row == lastRow))
      return;

    lastRow = row;


    TreePath path = tree.getPathForRow(row);

    SheafScopeTreeNode node  = (SheafScopeTreeNode)tree.getLastSelectedPathComponent();

    // Get the table model.

    SheafScopeAbstractTableModel tableModel = getTableModel();

    // Restrict the member of the tableModel.

    sec_rep_space_member mbr = (sec_rep_space_member)tableModel.getMember();
    restrict(node, mbr);

    // Refresh the table

    getTablePane().refreshTable();
  }

  /**
   * Restrict the mbr to the selected schema value
   */
  public void restrict(SheafScopeTreeNode node, sec_rep_space_member mbr)
  {
    try
    {
      // Get the existing base restriction for the node selected in the table.

      abstract_poset_member baseMbr = mbr.base();

      // Get the currently selected node in the schema pane.

      schema_poset_member schemaMbr = new schema_poset_member(node.getMember().host(), node.getMember().name());

      // Restrict the member to the restricted base and fiber schema

      mbr.restrict_to(baseMbr, schemaMbr);

      // Detach the schema member.

      schemaMbr.detach_from_state();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   *
   */
  protected void annotate()
  {}
}
