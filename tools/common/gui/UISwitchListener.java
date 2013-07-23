/**
 *  Classname: UISwitchListener
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

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
