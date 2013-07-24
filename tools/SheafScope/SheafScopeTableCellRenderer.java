/**
 * Classname: SheafScopeTableCellRenderer
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;

/**
 * SheafScopeTableCellRender specializes the <code>DefaultTableCellRenderer</code> class
 * to provide appropriate rendering of table cells. <p>
 */
public class SheafScopeTableCellRenderer extends DefaultTableCellRenderer
{

  // The background colors for the first 3 columns

  private static Color columns123Background = new Color(220,220,240);

  // The jrm cell background colors

  private static Color jrmBackground = new Color(240,220,220);

  /**
   * Constructor
   */
  public SheafScopeTableCellRenderer()
  {
    super();
  }

  /**
   * Overload of the default class of the same name, specialized to
   * handle SheafScope table cells.<p>
   *
   * @param table The JTable to render nodes for.
   * @param value The object attached to the current cell
   * @param isSelected The selection state of the current cell
   * @param row The row index of the current node
   * @param column The column index of the current node
   * @param hasFocus true is the current tree has the focus.
   * 
   * @return The <code>TableCellRendererComponent</code> for <i>table</i>.
   */
  public Component getTableCellRendererComponent(
    JTable table, Object value, boolean isSelected, boolean hasFocus,
    int row, int column)
  {

    if(value == null)
      return null;

    String text = value.toString();

    if(text.length() == 0)
    {
      // HACK: This doesn't deal with partial sections.
      //       The jims of partial sections can have
      //       cells that are empty.

      setBackground(jrmBackground);
      setForeground(Color.black);
    }
    else if(column <= 2)
    {
      setBackground(columns123Background);
      setForeground(Color.black);
    }
    else
    {
      setBackground(Color.white);
      setForeground(Color.black);
    }

    return super.getTableCellRendererComponent(
             table, value, isSelected, hasFocus, row, column);
  }

}
