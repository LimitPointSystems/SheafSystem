
/**
 *  Classname: SectionTable
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SectionTable.java,v $ $Revision: 1.7 $
 *
 *  $Date: 2013/01/12 17:18:01 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.table;

import bindings.java.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;

/**
 * Specialization of <code>JPanel</code> for displaying a
 * section.
 */
public class SectionTable extends JPanel
{
  //$$ISSUE: Probably would want to allow the page size
  //to be specified by the client (in the constructor).
  static int pageSize = 100;

  /**
   * The section
   */
  protected sec_vd section;

  /**
   * The text panel
   */
  protected JPanel textPanel;

  /**
   * The table
   */
  protected JTable table;

  /**
   * The space name label
   */
  protected JLabel spaceNameLabel;

  /**
   * The section name label
   */
  protected JLabel sectionNameLabel;

  /**
   * The table model
   */
  protected PagedTableModel tableModel;

  /**
   * The constructor
   */
  public SectionTable(sec_vd xsection)
  {
    section = xsection;

    makeGUI();

    initValues();

    update();
  }

  /**
   * Create the gui
   */
  private void makeGUI()
  {
    setLayout(new BorderLayout());
    setBorder(BorderFactory.createRaisedBevelBorder());

    JPanel topPanel = new JPanel();
    topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.Y_AXIS));
    //topPanel.setBorder(BorderFactory.createRaisedBevelBorder());

    topPanel.add(Box.createVerticalStrut(4));

    spaceNameLabel = new JLabel();

    JPanel spaceNamePanel = new JPanel();
    spaceNamePanel.setLayout(new BorderLayout());

    spaceNamePanel.add(spaceNameLabel, BorderLayout.WEST);

    topPanel.add(spaceNamePanel);

    JPanel sectionNamePanel = new JPanel();
    sectionNamePanel.setLayout(new BorderLayout());

    sectionNameLabel = new JLabel();

    sectionNamePanel.add(sectionNameLabel, BorderLayout.WEST);

    topPanel.add(sectionNamePanel);

    topPanel.add(Box.createVerticalStrut(4));

    add
      (topPanel, BorderLayout.NORTH);

    textPanel = new JPanel();
    textPanel.setLayout(new BorderLayout());

    table = new JTable();

    PagedScrollPane scrollPane = new PagedScrollPane(table);

    textPanel.add(scrollPane, BorderLayout.CENTER);
    add
      (textPanel, BorderLayout.CENTER);
  }

  /**
   * Initialize the values of the gui
   */
  private void initValues()
  {
    String name = "";
    try
    {
      name = section.host().name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    spaceNameLabel.setText("  Space: " + name);

    try
    {
      name = section.name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    sectionNameLabel.setText("  Section: " + name);

    tableModel = new PagedTableModel(section, pageSize);

    table.setModel(tableModel);

    // Set the preferred width of the "Row" column.
    //$$ISSUE: Could calculate the actual columns width and use them.

    TableColumnModel tcm = table.getColumnModel();

    if(tcm.getColumnCount() > 0)
    {
      TableColumn tc = tcm.getColumn(0);
      tc.setPreferredWidth(16);
    }
  }

  /**
   * Update the table.
   */
  public void update()
  {
    tableModel.update();

    //$$ISSUE: For now, the "Refresh" button is always activated.
    //         But eventually we should only enable it when the section
    //         underlying this model has changed (eg: via restriction).
    //enableRefresh(true);

    revalidate();
  }
}
