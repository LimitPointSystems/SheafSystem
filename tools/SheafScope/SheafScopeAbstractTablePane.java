
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
import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.common.util.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

/**
 * SheafScopeAbstractTablePane specializes the <code>JPanel</code> class to
 * meet the needs of the SheafScope.<p>
 */
public abstract class SheafScopeAbstractTablePane extends JPanel
{
  protected SheafScopePosetPane posetPane;
  protected SheafScopeJTable table;
  private   SheafScopeFilterDialog filterDialog;
  protected SheafScopeAbstractTableModel tableModel = null;

  protected abstract_poset_member member;

  private boolean isDown = true;
  private boolean isStrict = false;
  protected String selectedName = null;

  private JToolBar toolBar;
  private JLabel title;
  private Action selectFilterAction;
  private Action editDofSettingsAction;
  private Action selectIdSpacesAction;

  //private JToggleButton showBottomsButton;
  //private Action showBottomsAction;

  private static final String wholeName = "whole";

  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> for the table.
   * @param xmember The <code>abstract_poset_member</code> to traverse.
   */
  public SheafScopeAbstractTablePane(SheafScopePosetPane xposetPane,
                                     abstract_poset_member xmember)
  {
    this.posetPane = xposetPane;
    this.member = xmember;

    try
    {
      selectedName = xmember.host().name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      selectedName = "";
    }

    makeTable();
    makePane();
  }

  /**
   * Detach the filter subposet for this pane's table model.
   */
  public void detachStates()
  {
    if(tableModel != null)
    {
      tableModel.detachStates();
    }
  }

  /**
   * Abstract method to make the <code>SheafScopeJTable</code>.
   * Must be implemented by every class specializing this one.
   */
  protected abstract void makeTable();

  /**
   * Instantiates a new <code>SheafScopeTableScrollPane</code>.<p>
   *
   * 
   */
  protected void makePane()
  {
    title = new JLabel(" ");

    createActions();

    setLayout(new BorderLayout());

    // Assemble the toolbar.

    JPanel toolBarPanel = new JPanel(new BorderLayout());
    toolBarPanel.setBorder(BorderFactory.createRaisedBevelBorder());

    toolBar = createToolBar();
    toolBarPanel.add(toolBar, BorderLayout.CENTER);

    // Assemble the scrollpane.

    JPanel scrollPanePanel = new JPanel(new BorderLayout());

    SheafScopeTableScrollPane scrollPane =
      new SheafScopeTableScrollPane(table, posetPane.getMainPane().getEnableRemoteX());

    scrollPanePanel.add(scrollPane, BorderLayout.CENTER);

    if(SheafScopeConstants.DEBUG == true)
    {
      setBorder(BorderFactory.createMatteBorder(5,5,5,5,Color.green));

      scrollPanePanel.setBorder(
        BorderFactory.createMatteBorder(5,5,5,5,Color.magenta));
    }

    // Assemble the dof panel

    SheafScopeTableDofTablePane tableDofPane =
      new SheafScopeTableDofTablePane(posetPane, member);

    // Add the components.

    this.add(toolBarPanel, BorderLayout.NORTH);
    this.add(scrollPanePanel, BorderLayout.CENTER);
    this.add(tableDofPane, BorderLayout.SOUTH);

    try
    {
      setTitle("Row Dofs: " + member.host().name());
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }


  /**
   * Sets the table column sizes.<p>
   *
   * 
   */
  protected void setColumnSizes()
  {
    TableColumnModel columnModel = table.getColumnModel();

    for(int i=0; i<table.getColumnCount(); i++)
    {
      TableColumn column = columnModel.getColumn(i);
      int width = getColumnWidth(column);
      column.setPreferredWidth(width);
    }
  }

  /**
   * Gets the width of the specified column.<p>
   *
   * @param xcolumn User specified <code>TableColumn</code>
   *
   * @return The column width of the table associated with
   *         this instance of <code>SheafScopeAbstractTablePane</code>.
   */
  protected int getColumnWidth(TableColumn xcolumn)
  {
    //$$ISSUE: Works with both JDK1.3 and JDK1.2 (Not efficient???).
    //         If this stays, we should make it a class variable.

    TableCellRenderer  renderer = new DefaultTableCellRenderer();

    Component comp = renderer.getTableCellRendererComponent(
                       table, xcolumn.getHeaderValue(), false, false, 0, 0);

    int headerWidth = comp.getPreferredSize().width;

    // Loop through the cells.

    int cellWidth = 0;
    int c = xcolumn.getModelIndex();
    for(int r=0; r<table.getRowCount(); r++)
    {
      renderer = table.getCellRenderer(r, c);

      Object value = table.getValueAt(r, c);

      if(value == null)
        return 1;

      comp = renderer.getTableCellRendererComponent(
               table, value, false, false, r, c);

      if(comp == null)
        return 1;

      int width = comp.getPreferredSize().width;
      cellWidth = (cellWidth < width) ? width : cellWidth;
    }

    int width = (headerWidth > cellWidth) ? headerWidth : cellWidth;

    // Add a little space (for looks).

    width += 5;

    return width;
  }

  /**
   * Creates actions for the new <code>SheafScopeAbstractTablePane</code>.<p>
   *
   * 
   */
  protected void createActions()
  {
    String iconPath = SheafScopeConstants.IMAGE_PATH + "row_filter.png";
    String tip = "Select row filter";

    selectFilterAction
    = new GenericAction(this,              //target
                        "selectFilter",    //method
                        "Select Filter",   //action name
                        "Select Filter",   //label
                        iconPath,          //icon
                        tip);              //tooltip

    iconPath = SheafScopeConstants.IMAGE_PATH + "col_filter.png";
    tip = "Edit column filter";
    editDofSettingsAction
    = new GenericAction(this,                //target
                        "editDofSettings",   //method
                        "Column Filter",     //action name
                        "Column Filter",     //label
                        iconPath,            //icon
                        tip);                //tooltip

    iconPath = SheafScopeConstants.IMAGE_PATH + "id_space_filter.png";
    tip = "Select id spaces";
    selectIdSpacesAction
    = new GenericAction(this,                //target
                        "selectIdSpaces",    //method
                        "ID Spaces",         //action name
                        "ID Spaces",         //label
                        iconPath,            //icon
                        tip);                //tooltip


    //     String iconPath = SheafScopeConstants.IMAGE_PATH + "showBottoms.png";

    //     showBottomsAction
    //     = new GenericAction(this,                //target
    //                         "showBottoms",       //method
    //                         "Show Bottoms",      //action name
    //                         "Show Bottoms",      //label
    //                         iconPath,            //icon
    //                         "Show bottom rows"); //tooltip
  }

  /**
   * Creates toolbars for the new <code>SheafScopeAbstractTablePane</code>.<p>
   *
   * @return The newly created <code>JToolBar</code>.
   */
  protected JToolBar createToolBar()
  {
    JToolBar bar = new JToolBar();

    //showBottomsButton = new JToggleButton(showBottomsAction);

    bar.add(title);

    bar.addSeparator();
    bar.add(Box.createHorizontalGlue());

    bar.add(selectFilterAction);
    bar.add(editDofSettingsAction);
    bar.add(selectIdSpacesAction);
    bar.addSeparator();

    return bar;
  }

  /**
   * Public mutator for the new <code>SheafScopeAbstractTablePane</code>.<p>
   *
   * @param xtext The desired window title.
   *
   * 
   */
  public void setTitle(String xtext)
  {
    title.setText(xtext);
  }

  /**
   * Public accessor for the <code>SheafScopeJTable</code> associated with this pane.<p>
   *
   * @return The <code>SheafScopeJTable</code> associated with this pane.
   */
  public SheafScopeJTable getTable()
  {
    return table;
  }

  /**
   * Public accessor for the <code>SheafScopeAbstractTableModel</code>
   * associated with this pane.<p>
   *
   * @return The <code>SheafScopeAbstractTableModel</code> associated with this pane.
   */
  public SheafScopeAbstractTableModel getTableModel()
  {
    TableModel model = table.getModel();
    return (SheafScopeAbstractTableModel)table.getModel();
  }

  //   /**
  //    * Shows "bottom" nodes of current <code>SheafScopeAbstractTableModel</code>.<p>
  //    *
  //    *
  //    *
  //    */
  //   public void showBottoms()
  //   {
  //     SheafScopeAbstractTableModel tableModel = getTableModel();
  //     tableModel.setShowBottoms(showBottomsButton.isSelected());
  //     updateTable();
  //   }

  /**
   * Refreshes the table associated with this instance of
   * <code>SheafScopeAbstractTablePane</code>.<p>
   *
   * 
   */
  public void updateTable()
  {
    posetPane.getMainPane().getParentFrame().setWaitState(true);

    SheafScopeAbstractTreePane focusPane = getFocusPane();

    SheafScopeJTree tree = focusPane.getTree();

    SheafScopeTreeNode node
    = (SheafScopeTreeNode)tree.getLastSelectedPathComponent();

    focusPane.setSelectedNode(node);

    if(node == null)
    {
      return;
    }

    showFilteredData(selectedName);

    updateMember();

    posetPane.getMainPane().getParentFrame().setWaitState(false);
  }

  /**
   *
   */
  protected void updateMember()
  {}


  /**
   * Selects the restriction set for this data.
   *
   * 
   */
  public void selectFilter()
  {
    abstract_poset_member focusMember = getFocusPane().getSelectedMember();

    //$$TODO: Can we make this not happen???
    if(focusMember == null)
    {
      System.out.println(
        "SheafScopeAbstractTablePane.selectFilter: no member selected");
      return;
    }

    String[] names = getSubposetNames(focusMember);
    String[] filterNames = new String[names.length];

    //HashMap map = new HashMap(names.length);
    HashMap<String, String> map = new HashMap<String, String>(names.length);

    // If member name is same as subposetName, use "wholeName" in dialog.
    // Save filter names to subposet names mapping in a HashMap.

    String memberName = "";

    try
    {
      memberName = member.host().name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }


    for(int i=0; i<names.length; i++)
    {
      filterNames[i] = (memberName.equals(names[i]))
                       ? wholeName : names[i];
      map.put(filterNames[i], names[i]);
    }

    if(filterDialog == null)
    {
      Frame f = (Frame)this.getTopLevelAncestor();
      filterDialog = new SheafScopeFilterDialog(f, filterNames,
                     posetPane.getMainPane().getEnableRemoteX());
    }
    filterDialog.setVisible(true);

    isDown = filterDialog.directionIsDown();
    isStrict = filterDialog.isStrict();
    selectedName = filterDialog.getSubposetName();

    if(selectedName != null)
    {
      // Retrieve subposet name corresponding to filter name.

      String subposetName = (String)map.get(selectedName);

      // Display the filter data in the table.

      showFilteredData(subposetName);

      selectedName = subposetName;
    }
  }

  /**
   * Show dialog for editing Dof Settings
   *
   *
   */
  public void editDofSettings()
  {
    SheafScopeDofSettingsDialog dofs =
      new SheafScopeDofSettingsDialog(posetPane.getMainPane().getParentFrame(),
                                      tableModel.getDofDisplay(),
                                      tableModel.getDofLimit());
    dofs.setVisible(true);

    String dofDisplay = dofs.getDofDisplay();
    if(dofDisplay != null)
    {
      tableModel.setDofDisplay(dofDisplay);

      if(dofDisplay.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS))
      {
        tableModel.setDofLimit(dofs.getDofLimit());
      }
    }

    // Refresh the table

    refreshTable();
  }

  /**
   * Refresh the table for the current selected name.
   * Refresh includes refreshing the table model,
   * setting the column names and updating the
   * table.
   */
  public void refreshTable()
  {
    refreshTable(selectedName);
  }

  /**
   * Refresh the table for the given subposet name.
   */
  public void refreshTable(String xsubposetName)
  {
    refreshTableModel(xsubposetName);
    updateTable();
  }

  /**
   * Show dialog for selecting the id spaces to display
   *
   *
   */
  public void selectIdSpaces()
  {
    try
    {
      SheafScopeIdSpaceDialog dialog =
        new SheafScopeIdSpaceDialog(posetPane.getMainPane().getParentFrame(),
                                    member.host(),
                                    tableModel.getIdSpaces());

      dialog.setVisible(true);

      Vector<String> idSpaces = dialog.getIdSpaces();
      if(idSpaces == null)
        return;

      // Set the id spaces and update the column names.

      tableModel.setIdSpaces(idSpaces);

      // Refresh the table

      refreshTable();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Allows refresh of display with new restriction set data.<p>
   *
   * @param xsubposetName The name of the <code>subposet</code> filter.
   *
   * 
   */
  //protected abstract void showFilteredData(String xsubposetName);

  protected void showFilteredData(String xsubposetName)
  {
    // Refresh the table model

    refreshTableModel(xsubposetName);

    // Set title.

    setTitle(createTitle());

    // Adjust column widths.

    setColumnSizes();
  }

  /**
   * Refresh the table model
   */
  protected void refreshTableModel(String xsubposetName)
  {
    posetPane.getMainPane().getParentFrame().setWaitState(true);

    SheafScopeTreeNode focusNode = getFocusPane().getSelectedNode();
    Enumeration itr = focusNode.preorderEnumeration();

    tableModel.clear();
    tableModel.refresh(itr, xsubposetName);

    posetPane.getMainPane().getParentFrame().setWaitState(false);
  }

  /**
   * Create title string.<p>
   *
   * @return The generated title string.
   */
  protected String createTitle()
  {
    String posetName = "";
    try
    {
      posetName = member.host().name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    String subposetName = (selectedName.equals(posetName))
                          ? wholeName : selectedName;

    StringBuffer sb = new StringBuffer("Row Dofs: ");
    sb.append(posetName)
    .append(": ")
    .append(subposetName)
    .append(" [")
    .append(isDown ? "Down" : "Up")
    .append(", ")
    .append(isStrict ? "Strict" : "Nonstrict")
    .append("]");

    return sb.toString();
  }

  /**
   * Get an array of subposet names.
   *
   * @param xmbr The <code>abstract_poset_member</code>
   *
   * @return An array of subposet names
   *
   */
  public String [] getSubposetNames(abstract_poset_member xmbr)
  {
    try
    {
      poset_state_handle host = xmbr.host();
      host.get_read_access();

      // Get iterator over the subposets in subject.

      index_space_iterator lsp_itr = host.get_subposet_id_space_iterator();

      // Count the members (somewhere, must be a method to get this!).

      int count = 0;
      while(!lsp_itr.is_done())
      {
        count++;
        lsp_itr.next();
      }

      // Reset the iterator.

      lsp_itr.reset();

      String [] result = new String[count];

      int index = 0;
      while(!lsp_itr.is_done())
      {
        result[index] = host.subposet_name(lsp_itr.hub_pod());

        index++;
        lsp_itr.next();
      }

      host.release_access(false);

      host.release_subposet_id_space_iterator(lsp_itr);

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return new String[0];
    }
  }

  /**
   *
   */
  protected SheafScopeFocusPane getFocusPane()
  {
    return posetPane.getFocusPane();
  }
}
