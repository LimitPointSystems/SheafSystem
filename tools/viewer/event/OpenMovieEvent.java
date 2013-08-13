/**
 *  Classname: OpenMovieEvent
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:58 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

import java.io.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for opening a movie file.
 *
 */
public class OpenMovieEvent extends ViewerEvent
{
  /**
   * The file
   */
  protected File file;

  /**
   * The constructor
   */
  public OpenMovieEvent(File xfile)
  {
    file = xfile;
  }

  /**
   * Handle this <code>OpenMovieEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.openMovie(file);
  }
}
