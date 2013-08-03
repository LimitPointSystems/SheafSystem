
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
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;

public class ThemeMenu extends JMenu implements ActionListener
{
  Color[] reds = { new Color(142,  0,  20),
                   new Color(193,  0,  40),
                   new Color(244,  0,  60) };

  MetalTheme redTheme = new ColorTheme("Red", reds);

  Color[] greens = { new Color( 51, 142,  71),
                     new Color(102, 193, 122),
                     new Color(153, 244, 173) };

  MetalTheme greenTheme = new ColorTheme("Green", greens);

  Color[] blues = { new Color( 51,  71, 142),
                    new Color(102, 122, 193),
                    new Color(153, 173, 244) };

  MetalTheme blueTheme = new ColorTheme("Blue", blues);

  MetalTheme[] themes = { new DefaultMetalTheme(),
                          redTheme,
                          greenTheme,
                          blueTheme,
                          new ContrastTheme(),
                          new DemoTheme()
                        };

  public ThemeMenu()
  {
    super("Themes");
    ButtonGroup group = new ButtonGroup();

    for(int i=0; i<themes.length; i++)
    {
      String tname = themes[i].getName();
      if(tname.equals("Steel"))
        tname = "Default"; //!!! fix

      JRadioButtonMenuItem item =
        new JRadioButtonMenuItem(tname + "  "); // spaces for looks

      group.add(item);
      add
        (item);
      item.setActionCommand(i+"");
      item.addActionListener(this);
      if(i==0)
        item.setSelected(true); // default
    }
  }

  public void actionPerformed(ActionEvent e)
  {
    String numStr = e.getActionCommand();
    MetalTheme selectedTheme = themes[Integer.parseInt(numStr)];
    MetalLookAndFeel.setCurrentTheme(selectedTheme);

    try
    {
      UIManager.setLookAndFeel(
        "javax.swing.plaf.metal.MetalLookAndFeel");
    }
    catch(Exception ex)
    {
      System.out.println("Failed loading MetalLookAndFeel");
      System.out.println(ex);
    }
  }
}
