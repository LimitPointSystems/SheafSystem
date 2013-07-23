/**
 *  Classname: FirstSceneEvent
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
 * Implementation <code>FirstSceneThreadEvent</code> for
 * going to the first scene of a <code>Script</code>.
 *
 */
public class FirstSceneEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public FirstSceneEvent()
  {}

  /**
   * Handle this <code>FirstSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.first();
  }
}
