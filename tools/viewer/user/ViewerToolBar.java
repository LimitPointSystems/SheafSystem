
/**
 * Classname: ViewerToolBar
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: ViewerToolBar.java,v $ $Revision: 1.7 $
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
 * Specialization of <code>JToolBar</code> for tool bars which interact
 * with the <code>Viewer</code>
 *
 */
public abstract class ViewerToolBar extends JToolBar
{
  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   *
   */
  protected ViewerToolBar(Viewer xviewer)
  {
    viewer = xviewer;
  }

  /**
   * Add a <code>ViewerAction</code>
   */
  public JButton add
    (ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JButton result = super.add(action);
    result.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    return result;
  }

  /**
   * Add a <code>ViewerAction</code> as a
   * <code>JToogleButton</code>
   */
  public JToggleButton addToggle(ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JToggleButton button = new JToggleButton(action);
    button.setText("");
    button.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    super.add(button);

    return button;
  }
}
