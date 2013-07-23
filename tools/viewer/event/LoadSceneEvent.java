/**
 *  Classname: LoadSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;
import tools.viewer.animation.*;

/**
 *
 * Implementation <code>LoadSceneThreadEvent</code> for
 * updating the <code>Script</code> to a scene.
 *
 */
public class LoadSceneEvent extends PlayThreadEvent
{
  /**
   * The scene
   */
  protected SceneDescriptor scene;

  /**
   * The constructor
   */
  public LoadSceneEvent(SceneDescriptor xscene)
  {
    scene = xscene;
  }

  /**
   * Handle this <code>LoadSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.loadScene(scene);
  }
}
