/**
 *  Classname: SetScreenCursorEvent
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
 * Implementation <code>ViewerEvent</code> for rendering being complete
 *
 */
public class SetScreenCursorEvent extends ViewerEvent
{
  /**
   * The cursor
   */
  protected int cursor;

  /**
   * The constructor
   */
  public SetScreenCursorEvent(int xcursor)
  {
    cursor = xcursor;
  }

  /**
   * Handle this <code>SetScreenCursorEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;


    xviewer.getScreen().setCursor(new Cursor(cursor));
  }
}
