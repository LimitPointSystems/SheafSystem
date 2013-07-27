
/**
 *  Classname: FieldTable
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:18:01 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.table;

import tools.viewer.common.*;
import tools.viewer.render.*;
import tools.viewer.user.*;
import bindings.java.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 * Specialization of <code>JPanel</code> for displaying a
 * <code>FieldTableDescriptor</code>
 */
public class FieldTable extends JPanel
{
  /**
   * The <code>FieldTableDescriptor</code>
   */
  protected FieldTableDescriptor descriptor;

  /**
   * The list of <code>SectionTable</code>'s
   */
  protected ArrayList<SectionTable> sections =
    new ArrayList<SectionTable>();

  /**
   * The <code>JPanel</code> containing the <code>SectionTable</code>'s
   */
  protected JPanel tablePanel;

  /**
   * Constructor
   */
  public FieldTable(FieldTableDescriptor xdescriptor)
  {
    descriptor = xdescriptor;

    setLayout(new BorderLayout());

    //$$ISSUE: Probably should use a JSplitPane here.  The logic
    //         might be more complex in order to distinguish between
    //         the one viewer and two viewer cases though.

    tablePanel = new JPanel();
    tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.X_AXIS));

    // Construct the section tables

    namespace_poset ns = Viewer.APPLICATION.getNamespace(descriptor.namespace);

    Iterator<SectionDescriptor> itr = descriptor.sections.iterator();
    SectionTable table;
    while(itr.hasNext())
    {
      table = new SectionTable(itr.next().build(ns));
      sections.add(table);
      tablePanel.add(table);
    }

    add
      (tablePanel, BorderLayout.CENTER);
  }

  /**
   * Update the <code>SectionTable</code>'s
   */
  public void update()
  {
    Iterator<SectionTable> itr = sections.iterator();
    while(itr.hasNext())
    {
      itr.next().update();
    }
  }
}


