
/**
 * Classname: ViewerActionMouseAdaptor
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
 * Implementation of <code>MouseAdapter</code> that allows
 * clients to hook <code>ViewerAction</code>'s to the status
 * bar of the <code>Viewer</code>.
 */
public class ViewerActionMouseAdapter extends MouseAdapter
{
  /**
   * The <code>ViewerAction</code>.
   */
  protected ViewerAction action;

  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   */
  public ViewerActionMouseAdapter(ViewerAction xaction, Viewer xviewer)
  {
    action = xaction;
    viewer = xviewer;
  }

  /**
   *
   */
  public void mouseEntered(MouseEvent e)
  {
    if(action.isEnabled())
      viewer.setStatus(action.getDescription());
  }

  /**
   *
   */
  public void mouseExited(MouseEvent e)
  {
    if(action.isEnabled())
      viewer.defaultStatus();
  }
}
