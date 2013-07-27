/**
 * Classname: SheafScopeTableScrollPane
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;

/**
 * Specialized version of <code>JScrollPane</code> to accommodate the needs of the
 * <code>SheafScope</code> table classes.<p>
 */
public class SheafScopeTableScrollPane extends JScrollPane
{
  static final Color defaultViewportBackgroundColor = Color.white;

  /**
   * Constructor
   *
   * @param xcomponent The <code>JTable</code> holding info
   * regarding the currently selected member(s).
   * @param enableRemoteX true, if remote X is enabled
   */
  public SheafScopeTableScrollPane(JTable xcomponent, boolean enableRemoteX)
  {
    super(xcomponent);
    initScrollPane(xcomponent);

    // If the scope is invoked with "-r",
    // dumb down the scroll mode to improve remote X performance.

    if(enableRemoteX)
    {
      this.getViewport().setScrollMode(JViewport.SIMPLE_SCROLL_MODE);
    }
  }

  /**
   * Initializes the visual parameters of the Pane.<p>
   *
   * @param xcomponent The <code>JTable</code> holding info regarding the currently selected 
   * <code>poset_member</code>(s).
   *     
   * 
   */
  private void initScrollPane(JTable xcomponent)
  {
    getViewport().add(xcomponent);
    setViewportView(xcomponent);
    setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
    setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    setOpaque(false);

    getViewport().setBackground(defaultViewportBackgroundColor);
  }

  /**
   * Default finalize method.
   * Just calls the superclass finalizer.
   *
   * 
   */
  public void finalize()throws Throwable
  {
    // No specific action required, just call the superclass finalizer.

    super.finalize();
  }
}

