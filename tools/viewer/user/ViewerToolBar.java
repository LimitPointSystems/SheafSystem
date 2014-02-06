
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

package tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import tools.viewer.common.*;
import tools.common.gui.*;

/**
 *
 * Specialization of <code>JToolBar</code> for tool bars which interact
 * with the <code>Viewer</code>
 *
 */
public abstract class ViewerToolBar extends JToolBar
{
  /**
   * The <code>Viewer</code>
   */
  protected Viewer viewer;

  /**
   * Constructor
   *
   */
  protected ViewerToolBar(Viewer xviewer)
  {
    viewer = xviewer;
  }

  /**
   * Add a <code>ViewerAction</code>
   */
  public JButton add
    (ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JButton result = super.add(action);
    result.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    return result;
  }

  /**
   * Add a <code>ViewerAction</code> as a
   * <code>JToogleButton</code>
   */
  public JToggleButton addToggle(ViewerAction action)
  {
    // Add the viewer action mouse listener to the resulting button.

    JToggleButton button = new JToggleButton(action);
    button.setText("");
    button.addMouseListener(new ViewerActionMouseAdapter(action,
                            viewer));

    super.add(button);

    return button;
  }
}
