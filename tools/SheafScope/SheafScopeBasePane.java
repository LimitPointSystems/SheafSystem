
/**
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
 * 
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.event.*;
import tools.common.util.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;

/**
 * SheafScopeBasePane specializes <code>SheafScopeAbstractTreePane</code>
 * to provide the parent SheafScope window.<p>
 */
public class SheafScopeBasePane extends SheafScopeAbstractTreePane
      implements ProxyListener
{
  // Background colors for special tree nodes.

  private final static Color discretizationColor = new Color(232, 200, 232);
  private final static Color evaluationColor     = new Color(200, 232, 232);
  private final static Color bothColor           = new Color(232, 232, 200);

  // Tool tips for special tree nodes.

  private final static String discretizationToolTip = "Discretization";
  private final static String evaluationToolTip     = "Evaluation";
  private final static String bothToolTip           = "Discretization & Evaluation";


  private int lastRow = -1;

  /**
   * Constructor
   *
   * @param xposetPane The pane containing the poset to be viewed.
   * @param xhost The host of the member to be traversed.
   * @param xindex The index of the member to be traversed.
   */
  public SheafScopeBasePane(SheafScopePosetPane xposetPane,
                            poset_state_handle xhost,
			    scoped_index xindex)
  {
    super(xposetPane, new total_poset_member(xhost, xindex));

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

    setTitle("Base: " + name);

    //SheafScopeFocusPane fp =  xposetPane.getFocusPane();
    //PosetMember pm = (PosetMember)(fp.getSelectedMember());

    //System.out.println("SheafScopeBasePane = xposetPane.getFocusPane().getSelectedMember() = "
    //                   + pm.getName());

    //if(xposetPane != null)
    // pm.addProxyListener(this);

    SheafScopeBaseSelectionListener listener = new SheafScopeBaseSelectionListener(xposetPane);
    tree.addMouseListener(listener);
    tree.setSelectionRow(tree.getRowCount());

    annotate();
  }

  /**
   * Detach the member of this pane and the members of its tree.
   */
  public void detachStates()
  {
    member.detach_from_state();

    super.detachStates();
  }

  //$$ISSUE: Probably shouldn't be called "annotate" (need a better name
  //         like (maybe) "tagNodes".

  /**
   * Iterates over the evaluation and discretization subposets
   * of the <code>sec_rep_space</code> associated with this tree
   * and sets the background colors and the tooltip texts of
   * the nodes according to whether the corresponding members
   * are in the evaluation or discretization subposets or both.
   */
  protected void annotate()
  {
    try
    {
      //$$TODO: Shouldn't need sec_rep_space_member here!

      sec_rep_space_member srsm = (sec_rep_space_member) posetPane.getMember();
      sec_rep_space srs = (sec_rep_space) srsm.host();
      abstract_poset_member base = srs.base();

      SheafScopeTreeNode root = getRoot();

      Enumeration itr =  root.breadthFirstEnumeration();

      while(itr.hasMoreElements())
      {
        SheafScopeTreeNode node = (SheafScopeTreeNode) itr.nextElement();

        abstract_poset_member apm = node.getMember();

        if(srs.discretization().contains_member(apm))
        {
          node.setIsDisplayed(true);
          node.setDisplayedColor(discretizationColor);
          node.setToolTipText(discretizationToolTip);
        }
        else if(srs.evaluation().contains_member(apm))
        {
          node.setIsDisplayed(true);
          node.setDisplayedColor(evaluationColor);
          node.setToolTipText(evaluationToolTip);
        }
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Test to determine if a member is included in an array of members.
   *
   * @param xindices An integer array of member indices.
   * @param xindex The index of the member to test.
   * @return True if index is in the indices array. 
   */
  private boolean matchingIndices(int[] xindices, int xindex)
  {
    for(int i=0; i<xindices.length; i++)
    {
      if(xindex == xindices[i])
        return true;
    }
    return false;
  }

  /**
   *  Method required by the ProxyListener interface.  Called
   *  from any descendent of Proxy  when a field is restricted or unrestricted.
   *  Usually not called directly by a client.
   *
   *  @param event Instance of a <code>ProxyEvent</code>.
   */
  public void valueChanged(ProxyEvent event)
  {
    //LPSDebug.println("SheafScopeBasePane.valueChanged: " + event);
  }

  /**
   *
   */
  public void doRestrictTo(MouseEvent event)
  {
    //LPSDebug.println("event = " + event);

    //=====================================================================

    JTree tree = getTree();

    int row = tree.getRowForLocation(event.getX(), event.getY());

    //LPSDebug.println("row = " + row);

    if((row == -1) || (row == lastRow))
      return;

    lastRow = row;

    TreePath path = tree.getPathForRow(row);

    SheafScopeTreeNode node  = (SheafScopeTreeNode)tree.getLastSelectedPathComponent();

    if(node == null)
      return;

    //=====================================================================

    // Get the table model.

    SheafScopeAbstractTableModel tableModel = getTableModel();

    // Restrict the member of the tableModel.

    sec_rep_space_member mbr = (sec_rep_space_member)tableModel.getMember();

    if(mbr == null)
    {
      // $$HACK: Is there a better way to handle the null selection?

      return;
    }

    // "top" is a jrm. If the user attempts to change it's restriction
    // issue a warning and return.

    //     String mbrName = mbr.getName();
    //     if(mbrName.equals("top"))
    //     {
    //       Toolkit.getDefaultToolkit().beep();
    //       posetPane.getMainPane().errorStatusBar.setText("Error: top is not a jim");
    //       return;
    //     }

    // setSelectedNode(node);

    try
    {
      // Get the currently selected node in the base pane.

      abstract_poset_member baseMbr = node.getMember();

      // Get the existing fiber schema for the node selected in the table.

      schema_poset_member schemaMbr = mbr.fiber_schema();

      // Call restrictTo on the current table node, passing it the base
      // value selected in this pane and the existing fiber restriction
      // from the selected table member.

      mbr.restrict_to(baseMbr, schemaMbr);

      // Refresh the table

      getTablePane().refreshTable();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }
}
