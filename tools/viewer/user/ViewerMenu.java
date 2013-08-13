
/**
 * Classname: ViewerMenu
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:02 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import tools.viewer.common.*;
import tools.common.gui.*;

/**
 *
 * Specialization of <code>JMenu</code> for tool bars which interact
 * with the <code>Viewer</code>
 *
 */
public class ViewerMenu extends JMenu
{
  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   *
   */
  public ViewerMenu(Viewer xviewer, String xtitle)
  {
    super(xtitle);

    viewer = xviewer;
  }

  /**
   * Add a <code>ViewerAction</code>
   */
  public JMenuItem add
    (ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JMenuItem result = super.add(action);
    result.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    return result;
  }
}
