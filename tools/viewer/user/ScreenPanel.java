
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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import vtk.*;

/**
 *
 */
public class ScreenPanel extends JPanel
{
  //$$TODO: Input width & height.

  protected Screen screen;

  public ScreenPanel()
  {
    super();

    screen = new Screen();

    setLayout(new BorderLayout());
    add(screen, BorderLayout.CENTER);
  }

  /**
   *
   */
  public ScreenPanel clone()
  {
    ScreenPanel result = new ScreenPanel();
    result.setSize(getSize().width, getSize().height);

    return result;
  }

  public Screen getScreen()
  {
    return screen;
  }

  public void setSize(int w, int h)
  {
    super.setSize(w, h);
    screen.setSize(w, h);
  }
}
