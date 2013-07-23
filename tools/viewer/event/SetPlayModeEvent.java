/**
 *  Classname: SetPlayModeEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:59 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

import java.awt.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for setting the play mode.
 *
 */
public class SetPlayModeEvent extends ViewerEvent
{
  /**
   * The mode
   */
  protected boolean mode;

  /**
   * The constructor
   */
  public SetPlayModeEvent(boolean xmode)
  {
    mode = xmode;
  }

  /**
   * Handle this <code>SetPlayModeEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.setPlayMode(mode);
  }
}
