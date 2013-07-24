/**
 * Classname: SheafScopeSelectTabCommand
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


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
