/**
 *  Classname: PlayThreadEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: PlayThreadEvent.java,v $ $Revision: 1.7 $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Abstract class for a <code>PlayThread</code> event
 *
 */
public abstract class PlayThreadEvent
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
   * Handle this <code>PlayThreadEvent</code>
   */
  public abstract void handle(PlayThread xrenderThread);
}
