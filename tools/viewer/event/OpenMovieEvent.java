
/**
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
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
