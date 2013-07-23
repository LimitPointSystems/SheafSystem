/**
 *  Classname: UpdatePropertiesPanelEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:59 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;
import tools.viewer.user.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * saving the render window to an image.
 *
 */
public class UpdatePropertiesPanelEvent extends RenderThreadEvent
{
  /**
   * The properties panel
   */
  protected PropertiesPanel panel;

  /**
   * The constructor
   */
  public UpdatePropertiesPanelEvent(PropertiesPanel xpanel)
  {
    panel = xpanel;
  }

  /**
   * Handle this <code>UpdatePropertiesPanelEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    panel.initValues();
    panel.setWaitState(false);
  }
}
