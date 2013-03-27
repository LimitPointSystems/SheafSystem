/**
 * Classname: SheafScopeTreeScrollPane
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeTreeScrollPane.java,v $ $Revision: 1.16 $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import javax.swing.*;

/**
 * Specialized version of JscrollPane to accommodate the needs of the SheafScope.<p>
 *
 */
public class SheafScopeTreeScrollPane extends JScrollPane
{

  /**
   * Constructor
   *
   * @param xtree The <code>JTree</code> holding our poset rep.
   * @param enableRemoteX true, if remote X is enabled
   */
  public SheafScopeTreeScrollPane(JTree xtree, boolean enableRemoteX)
  {
    super(xtree);
    initScrollPane();

    // If the scope is invoked with "-r",
    // dumb down the scroll mode to improve remote X performance.

    if(enableRemoteX)
    {
      this.getViewport().setScrollMode(JViewport.SIMPLE_SCROLL_MODE);
    }
  }

  /**
   * Initialize the ScrollPane with these parameters.<p>
   *
   * 
   */
  private void initScrollPane()
  {
    // Set the scrollbar policies.

    setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
    setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

    setOpaque(false);
  }

  /**
   * Default finalizer.<p>
   *
    */
  public void finalize()throws Throwable
  {
    // No specific action required, just call the superclass finalizer.

    super.finalize();
  }

}
