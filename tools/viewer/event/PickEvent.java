/**
 *  Classname: PickEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: PickEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for picking a position on the screen.
 *
 */
public class PickEvent extends ViewerEvent
{
  /**
   * The position
   */
  protected double[] position;

  /**
   * The constructor
   */
  public PickEvent(double[] xposition)
  {
    position = xposition;
  }

  /**
   * Handle this <code>PickEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.pick(position);
  }
}
