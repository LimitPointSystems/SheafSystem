
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
import tools.common.gui.*;
import tools.common.util.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

/**
 * SheafScopeTableDofTablePane specializes the <code>JPanel</code> class to
 * display a <code>SheafScopeTableDofTableModel</code>.<p>
 */
public class SheafScopeTableDofTablePane extends JPanel
{
  protected SheafScopePosetPane posetPane;
  protected JTable table;
  protected SheafScopeTableDofTableModel tableModel;

  protected abstract_poset_member member;

  private JToolBar toolBar;
  protected JLabel title;

  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> for the table.
   * @param xmember The <code>abstract_poset_member</code> with the table dofs.
   */
  public SheafScopeTableDofTablePane(SheafScopePosetPane xposetPane,
                                     abstract_poset_member xmember)
  {
    this.posetPane = xposetPane;
    this.member = xmember;

    makeTable();
    makePane();
  }

  /**
   * Instantiates the <code>JTable</code>.
   */
  public void makeTable()
  {
    tableModel = new SheafScopeTableDofTableModel(member);
    table = new JTable(tableModel);
    table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    table.setRowSelectionAllowed(false);
  }

  /**
   * Instantiates a new <code>SheafScopeTableScrollPane</code>
   */
  protected void makePane()
  {
    title = new JLabel(" ");

    setLayout(new BorderLayout());

    // Assemble the toolbar

    JPanel toolBarPanel = new JPanel(new BorderLayout());
    toolBarPanel.setBorder(BorderFactory.createRaisedBevelBorder());

    toolBar = createToolBar();
    toolBarPanel.add(toolBar, BorderLayout.CENTER);

    // Assemble the scrollpane.

    JPanel scrollPanePanel = new JPanel(new BorderLayout());

    if(tableModel.getColumnCount() > 0)
    {
      SheafScopeTableScrollPane scrollPane =
        new SheafScopeTableScrollPane(table, posetPane.getMainPane().getEnableRemoteX());

      scrollPanePanel.add(scrollPane, BorderLayout.CENTER);
    }
    else
    {
      JLabel label = new JLabel(" No Table Dofs");
      label.setOpaque(true);
      label.setBackground(Color.white);
      label.setForeground(Color.gray);

      scrollPanePanel.add(label, BorderLayout.CENTER);
    }

    if(SheafScopeConstants.DEBUG == true)
    {
      setBorder(BorderFactory.createMatteBorder(5,5,5,5,Color.green));

      scrollPanePanel.setBorder(
        BorderFactory.createMatteBorder(5,5,5,5,Color.magenta));
    }

    //
    // $$ISSUE: Must pick a maximum size for the scroll pane.  By
    //          default the preferred size of the viewport is
    //          too large.  Picked the max height of 50 which
    //          displays the table and gives enough space for
    //          the vertical scrollbar.  Should use the following
    //          code:
    //table.setPreferredScrollableViewportSize(table.getPreferredSize());
    //
    //          However, the vertical scrollbar hides the table
    //          dof values.
    //

    scrollPanePanel.setPreferredSize(new Dimension(500, 50));
    scrollPanePanel.setMaximumSize(new Dimension(5000, 50));

    // Add the components.

    this.add(toolBarPanel, BorderLayout.NORTH);
    this.add(scrollPanePanel, BorderLayout.CENTER);

    try
    {
      setTitle("Table Dofs: " + member.host().name());
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
   *         this instance of <code>SheafScopeTableDofTablePane</code>.
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
   * Creates toolbars for the new <code>SheafScopeDofTableTablePane</code>.<p>
   *
   * @return The newly created <code>JToolBar</code>.
   */
  protected JToolBar createToolBar()
  {
    JToolBar bar = new JToolBar();

    bar.addSeparator();
    bar.add(title);

    return bar;
  }

  /**
   * Public mutator for the new <code>SheafScopeTableDofTablePane</code>.<p>
   *
   * @param xtext The desired window title.
   */
  public void setTitle(String xtext)
  {
    title.setText(xtext);
  }

  /**
   * Public accessor for the <code>SheafScopeTableDofTableModel</code>
   * associated with this pane.<p>
   *
   * @return The <code>SheafScopeTableDofTableModel</code> associated with this pane.
   */
  public SheafScopeTableDofTableModel getTableModel()
  {
    TableModel model = table.getModel();
    return (SheafScopeTableDofTableModel)table.getModel();
  }

}
