
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


package tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import tools.viewer.common.*;
import tools.common.gui.*;


/**
 * Implementation of <code>MouseAdapter</code> that allows
 * clients to hook <code>ViewerAction</code>'s to the status
 * bar of the <code>Viewer</code>.
 */
public class ViewerActionMouseAdapter extends MouseAdapter
{
  /**
   * The <code>ViewerAction</code>.
   */
  protected ViewerAction action;

  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   */
  public ViewerActionMouseAdapter(ViewerAction xaction, Viewer xviewer)
  {
    action = xaction;
    viewer = xviewer;
  }

  /**
   *
   */
  public void mouseEntered(MouseEvent e)
  {
    if(action.isEnabled())
      viewer.setStatus(action.getDescription());
  }

  /**
   *
   */
  public void mouseExited(MouseEvent e)
  {
    if(action.isEnabled())
      viewer.defaultStatus();
  }
}
