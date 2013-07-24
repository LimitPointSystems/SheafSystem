/**
 *  Classname: ScreenPanel
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:18:02 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
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
