
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

package tools.common.gui;

import javax.swing.plaf.metal.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class LookAndFeelMenu extends JMenu implements ActionListener
{
  JComponent component;

  ButtonGroup group = new ButtonGroup();

  public LookAndFeelMenu(JComponent c)
  {
    super("Look & Feel");
    addItem("Java",    true,  true);
    addItem("Motif",   true,  false);
    addItem("Windows", false, false);
    addItem("Mac",     false, false);

    component = c;
  }

  private void addItem(String command, boolean enable, boolean select)
  {
    JRadioButtonMenuItem item = new JRadioButtonMenuItem(command);
    item.setActionCommand(command);
    item.setEnabled(enable);
    item.setSelected(select);
    item.addActionListener(this);
    group.add(item);
    add
      (item);
  }

  private static String[] lafNames =
    {
      "javax.swing.plaf.metal.MetalLookAndFeel",
      "com.sun.java.swing.plaf.motif.MotifLookAndFeel",
      "com.sun.java.swing.plaf.windows.WindowsLookAndFeel",
      "javax.swing.plaf.mac.MacLookAndFeel"
    };

  public void actionPerformed(ActionEvent e)
  {
    String command = e.getActionCommand();
    String lafName;
    if(command.equals("Java"))
      lafName = lafNames[0];
    else if(command.equals("Motif"))
      lafName = lafNames[1];
    else if(command.equals("Windows"))
      lafName = lafNames[2];
    else if(command.equals("Mac"))
      lafName = lafNames[3];
    else
      lafName = lafNames[0];

    try
    {
      UIManager.setLookAndFeel(lafName);
      SwingUtilities.updateComponentTreeUI(component);
    }
    catch(UnsupportedLookAndFeelException e0)
    {}
    catch(IllegalAccessException e1)
    {}
    catch(ClassNotFoundException e2)
    {}
    catch(InstantiationException e3)
    {}
  }
}
