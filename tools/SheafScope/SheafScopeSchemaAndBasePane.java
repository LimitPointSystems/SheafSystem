/**
 * Classname: SheafScopeSchemaAndBasePane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

/**
 * SheafScopeSchemaAndBasePane specializes <code>JPanel</code> to
 * provide a container for the schema and "base" panes.<p>
 */
public class SheafScopeSchemaAndBasePane extends JPanel
{
  // Sets the location of the split pane's vertical divider.

  static final int verticalDividerLocation = 300;

  // Sets the location of the split pane's vertical divider.

  static final int horizontalDividerLocation = 200;

  // Sets the size of the split pane's dividers.

  static final int dividerSize = 8;

  private SheafScopeMainPane        mainPane;
  private SheafScopeFiberSchemaPane fiberSchemaPane;
  private SheafScopeBasePane        basePane;

  /**
   * Constructor
   *
   * @param xmainPane The <code>SheafScopeMainPane</code> this will be attached to.
   * @param xfiberSchemaPane The <code>SheafScopeFiberSchemaPane</code> to be attached to this pane.
   * @param xbasePane The <code>SheafScopeBasePane</code> to be attached top this pane.
   */
  public SheafScopeSchemaAndBasePane(SheafScopeMainPane xmainPane,
                                     SheafScopeFiberSchemaPane xfiberSchemaPane,
                                     SheafScopeBasePane  xbasePane)
  {
    this.mainPane   = xmainPane;
    this.fiberSchemaPane = xfiberSchemaPane;
    this.basePane   = xbasePane;

    setLayout(new BorderLayout());

    if(SheafScopeConstants.DEBUG == true)
    {
      setBackground(Color.yellow);
      setBorder(BorderFactory.createMatteBorder(5,5,5,5,Color.blue));
    }

    add
      (createSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                       xbasePane, xfiberSchemaPane),
          BorderLayout.CENTER);
  }

  /**
   * Creates a new <code>JSplitPane</code> and initializes various properties
   * of the pane.<p>
   *
   * @param xorientation The screen orientation of the new pane.
   * @param xleftComponent The component to appear in the left-hand window.
   * @param xrightComponent The component to appear in the right-hand window. 
   * 
   * @return The newly created <code>JSplitPane</code>.
   */
  protected JSplitPane createSplitPane(int xorientation,
                                       Component xleftComponent,
                                       Component xrightComponent)
  {
    JSplitPane splitPane
    = new JSplitPane(xorientation, xleftComponent, xrightComponent);

    splitPane.setOneTouchExpandable(true);
    splitPane.setDividerSize(dividerSize);

    int dividerLocation = (xorientation == JSplitPane.HORIZONTAL_SPLIT)
                          ? verticalDividerLocation
                          : horizontalDividerLocation;
    splitPane.setDividerLocation(dividerLocation);

    return splitPane;
  }

}
