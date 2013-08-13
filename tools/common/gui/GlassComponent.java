/**
 * Classname: GlassComponent
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:55 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.common.gui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 * GlassComponent 
 * This class intercepts and disposes of mouse and keyboard events while it is visible.
 * The purpose: prevent the user from interfacing with the GUI while it's busy.
 */
public class GlassComponent extends JComponent implements AWTEventListener
{
  private Window parentWindow;
  private Component owner;

  public GlassComponent(Component xOwner)
  {
    owner = xOwner;
    setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

    setOpaque(false);

    addMouseListener(new MouseAdapter()
                     {}
                    );
  }

  /**
   * Override setVisible to install/remove key events hook that will allow us to 
   * disable key events when the glass pane is visible. 
   * @param visible specifies whether or not we can "see" this component.
   */
  public void setVisible(boolean visible)
  {
    if(parentWindow == null)
      parentWindow = SwingUtilities.windowForComponent(owner);

    if(visible)
    {
      Toolkit.getDefaultToolkit().addAWTEventListener(this, AWTEvent.KEY_EVENT_MASK);
    }
    else
    {
      Toolkit.getDefaultToolkit().removeAWTEventListener(this);
    }
    super.setVisible(visible);
  }

  /**
   * Called whenever there is an event in AWT queue. Note that the current implementation 
   * skips all key events, not just events for this window. Logic can be enhanced to examine 
   * the source of the event and it's parent window and skip only those events 
   * that originated from disabled window. 
   */
  public void eventDispatched(AWTEvent event)
  {
    if(event instanceof KeyEvent && event.getSource() instanceof Component)
    {
      Component c = (Component)event.getSource();
      if(SwingUtilities.windowForComponent(c) == parentWindow)
      {
        // Consume events only for our window.

        ((KeyEvent)event).consume();
      }
    }
  }

}

