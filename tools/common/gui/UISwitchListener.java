
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

package tools.common.gui;

import java.awt.*;
import java.beans.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class UISwitchListener implements PropertyChangeListener
{
  JComponent componentToSwitch;

  public UISwitchListener(JComponent c)
  {
    componentToSwitch = c;
  }

  public void propertyChange(PropertyChangeEvent e)
  {
    String name = e.getPropertyName();

    if(name.equals("lookAndFeel"))
    {
      SwingUtilities.updateComponentTreeUI(componentToSwitch);
      componentToSwitch.invalidate();
      componentToSwitch.validate();
      componentToSwitch.repaint();
    }
  }
}
