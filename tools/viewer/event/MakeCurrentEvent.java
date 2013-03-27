/**
 *  Classname: MakeCurrentEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: MakeCurrentEvent.java,v $ $Revision: 1.7 $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * making the interactor current.
 *
 */
public class MakeCurrentEvent extends RenderThreadEvent
{
  /**
   * The constructor
   */
  public MakeCurrentEvent()
  {}

  /**
   * Handle this <code>MakeCurrentEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.makeCurrent();
  }
}
