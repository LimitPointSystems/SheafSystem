
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


package tools.SheafScope;

import java.awt.*;
import javax.swing.event.*;

/**
 * SheafScopeSelectTabCommand is a listener
 * for <code>SheafScopeDisplayPanel</code> tab selection
 * events.<p>
 *
 */
public class SheafScopeSelectTabCommand implements ChangeListener
{
  private SheafScopeDisplayPanel panel;
  private static final Color unselectedForeground = Color.black;

  /**
   * Constructor
   *
   * @param xdisplayPanel The <code>SheafScopeDisplayPanel</code>
   * to perform tab selection upon.<p>
   */
  public SheafScopeSelectTabCommand(SheafScopeDisplayPanel xdisplayPanel)
  {
    panel = xdisplayPanel;
  }

  /**
   * Responds to tab selection events.<p>
   *
   * @param event A tab selection <code>ChangeEvent</code>
   *
   * 
   */
  public void stateChanged(ChangeEvent event)
  {
    // Color the selected and non-selected tabs appropriately.

    //$$TODO: Tab in the foreground (most recently used) should be the brightest,
    // farthest back(least recently used) darkest. Tabs should be
    // assigned varying shades of gray on an LRU basis.

    int selectedIndex = panel.getSelectedIndex();

    for(int i=0; i<panel.getTabCount(); i++)
    {
      Color bg = panel.getBackgroundAt(i);
      Color fg = panel.getForegroundAt(i);

      if(bg == fg)
      {
        fg = unselectedForeground;
      }

      if(i == selectedIndex)
      {
        panel.setForegroundAt(i, bg);
        panel.setBackgroundAt(i, bg);
      }
      else
      {
        panel.setBackgroundAt(i, bg);
        panel.setForegroundAt(i, fg);
      }
    }
  }
}
