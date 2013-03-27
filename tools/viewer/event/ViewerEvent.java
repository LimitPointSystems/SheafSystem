/**
 *  Classname: ViewerEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: ViewerEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2013/01/12 17:17:59 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

/**
 *
 * Abstract class for a <code>Viewer</code> event
 *
 */
public abstract class ViewerEvent
{
  /**
   * The abort flag
   */
  protected boolean abort = false;

  /**
   * Abort this <code>ViewerEvent</code>
   */
  public void abort()
  {
    abort = true;
  }

  /**
   * Handle this <code>ViewerEvent</code>
   */
  public abstract void handle(Viewer xrenderThread);
}
