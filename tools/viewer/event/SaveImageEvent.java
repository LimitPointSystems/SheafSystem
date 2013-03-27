/**
 *  Classname: SaveImageEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SaveImageEvent.java,v $ $Revision: 1.7 $
 *
 *  $Date: 2013/01/12 17:17:59 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;
import tools.viewer.common.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * saving the render window to an image.
 *
 */
public class SaveImageEvent extends RenderThreadEvent
{
  /**
   * The filename
   */
  protected String fileName;

  /**
   * The image format to save.
   */
  protected ViewerConstants.ImageFormat format;

  /**
   * The constructor
   */
  public SaveImageEvent(String xfileName, ViewerConstants.ImageFormat xformat)
  {
    fileName = xfileName;
    format = xformat;
  }

  /**
   * Handle this <code>SaveImageEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.saveImage(fileName, format);
  }
}
