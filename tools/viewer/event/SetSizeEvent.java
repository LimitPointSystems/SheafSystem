/**
 *  Classname: SetSizeEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:59 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * setting the size of the render window.
 *
 */
public class SetSizeEvent extends RenderThreadEvent
{
  /**
   * The width
   */
  protected int width;

  /**
   * The height
   */
  protected int height;

  /**
   * The constructor
   */
  public SetSizeEvent(int xwidth, int xheight)
  {
    width = xwidth;
    height = xheight;
  }

  /**
   * Handle this <code>SetSizeEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.setSize(width, height);
  }
}
