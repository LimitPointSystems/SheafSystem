/**
 *  Classname: RenderThreadEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: RenderThreadEvent.java,v $ $Revision: 1.8 $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

/**
 *
 * Abstract class for a <code>RenderThread</code> event
 *
 */
public abstract class RenderThreadEvent
{
  /**
   * The abort flag
   */
  protected boolean abort = false;

  /**
   * Abort this <code>RenderThreadEvent</code>
   */
  public void abort()
  {
    abort = true;
  }

  /**
   * Handle this <code>RenderThreadEvent</code>
   */
  public abstract void handle(RenderThread xrenderThread);

  /**
   * Set the screen cursor
   */
  public void setScreenCursor(RenderThread xrenderThread, int xcursor)
  {
    xrenderThread.invokeEvent(new SetScreenCursorEvent(xcursor));
  }
}
