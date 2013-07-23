/**
 *  Classname: PlayEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>PlayThreadEvent</code> for
 * playing a <code>Script</code>.
 *
 */
public class PlayEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public PlayEvent()
  {}

  /**
   * Handle this <code>PlayEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.initScene();

    if(abort)
      return;

    xplayThread.play();
  }
}
