
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
import com.limitpoimt.tools.common.event.*;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;

/**
 *  Class to provide a listener for table row/column list selection events
 *  and communicate the selection to a <code>FieldActorDialog</code>
 *  instance for eventual visualization.<p>
 */
public abstract class SheafScopeAbstractTableSelectionListener
      implements ListSelectionListener
{

  protected SheafScopePosetPane posetPane;
  protected SheafScopeJTable table;

  /**
   * Constructor
   *
   * @param xpane The SheafScopePosetPane containing the table
   *              listener is registered with.
   */
  public SheafScopeAbstractTableSelectionListener(SheafScopePosetPane xpane)
  {
    posetPane = xpane;
  }

  /**
   * The action to be taken when a single table row
   * selection event is detected.<p>
   * 
   * @param event The detected <code>ListSelectionEvent</code>.
   *
   * 
   */
  public abstract void valueChanged(ListSelectionEvent event);

  /**
   * Convenience method. Checks if the current member's host
   * is a <code>SecRepSpace</code>.<p>
   */
  protected boolean checkIsSecRepSpace(poset_member xrowMember)
  {
    if(xrowMember == null)
      return false;

    try
    {
      boolean  result =  xrowMember.host() instanceof sec_rep_space;

      // By Commenting the following out we do nothing when a row is
      // selected in a table which is not for a SecRepSpace.
      // if(!result)
      // {
      //   //$$TODO: Make this do something (message to status bar, beep, etc.)

      //  System.out.println("Error... " + host.getName() + " is not a SecRepSpace");
      //  return;
      // }

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }
  }

  /**
   * Convenience method. Checks if the current member
   * is a <code>sec_rep_space_member</code>.<p>
   */
  protected boolean checkIsSecRepSpaceMember(Object xobj)
  {
    poset_member member = (poset_member)xobj;

    if(member == null)
      return false;

    return(member instanceof sec_rep_space_member);
  }

  /**
   * Convenience method. Checks if the current member
   * is a <code>sec_vd</code>.<p>
   */
  protected boolean checkIsSecVd(Object xobj)
  {
    poset_member member = (poset_member)xobj;
    if(member == null)
      return false;

    return(member instanceof sec_vd);
  }

  /**
   * Check if the node at row n is a <code>jim</code>.<p>
   *
   * @param xrow The table row containing the Object to be tested.
   *
   * @return true if node at row n is a jim.
   */
  protected boolean checkIsJim(int xrow)
  {
    Object value = table.getValueAt(xrow, 2);

    String type = value.toString();

    boolean result = "jim".equals(type);

    if(!result)
    {
      //$$TODO: Make this do something (message to status bar, beep, etc.)

      value = table.getValueAt(xrow, 0);
    }
    return result;
  }

  /**
   * Check if the node at row n is a <code>jrm</code>.  If so, return 
   * true if the <code>FieldActorDialog</code> allows a jrm to be
   * inserted.
   *
   * @param xrow The table row containing the Object to be tested.
   * @param xmember The member to test
   * 
   * @return true if node at xrow is a jrm and can be selected.
   */
  public boolean checkCanSelectJrm(int xrow, Object xmember)
  {
    Object value = table.getValueAt(xrow, 2);

    String type = value.toString();

    if("jrm".equals(type) && checkIsSecVd(xmember))
      return posetPane.getMainPane().canSelectJrm((sec_vd) xmember);

    return false;
  }

  /**
   *  Update the fiber schema and base panes to reflect restriction set
   *  of current table member.<p>
   * 
   * @param xsvd The <code>sec_vd</code> to restrict.
   *
   * 
   */
  protected void updatePaneDisplay(sec_vd xsvd)
  {
    try
    {
      // Get the base restriction.

      abstract_poset_member base = xsvd.base();

      // Get the fiber restriction.

      schema_poset_member schema = xsvd.fiber().schema();

      // Set the base selection.

      if(posetPane.getBasePane() != null)
        posetPane.getBasePane().setSelectionRow(base.name());

      // Set the schema selection.

      if(posetPane.getFiberSchemaPane() != null)
        posetPane.getFiberSchemaPane().setSelectionRow(schema.name());
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }
}
