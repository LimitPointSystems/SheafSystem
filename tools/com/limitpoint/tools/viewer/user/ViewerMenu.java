
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//


package com.limitpoint.tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import com.limitpoint.tools.viewer.common.*;
import com.limitpoint.tools.common.gui.*;

/**
 *
 * Specialization of <code>JMenu</code> for tool bars which interact
 * with the <code>Viewer</code>
 *
 */
public class ViewerMenu extends JMenu
{
  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   *
   */
  public ViewerMenu(Viewer xviewer, String xtitle)
  {
    super(xtitle);

    viewer = xviewer;
  }

  /**
   * Add a <code>ViewerAction</code>
   */
  public JMenuItem add
    (ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JMenuItem result = super.add(action);
    result.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    return result;
  }
}
