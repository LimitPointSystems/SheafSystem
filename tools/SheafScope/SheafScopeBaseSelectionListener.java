/**
 * Classname: SheafScopeBaseSelectionListener
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeBaseSelectionListener.java,v $ $Revision: 1.15 $
 *
 * $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import tools.common.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

/**
 * SheafScopeBaseSelectionListener is a specialized TreeSelectionListener to
 * suit the needs of the SheafScope. Listens for single node selections on the
 * tree and updates the table model accordingly. <p>
 */
public class SheafScopeBaseSelectionListener extends MouseAdapter
{
  private SheafScopePosetPane posetPane;
  //private SheafScopeBasePane pane;

  /**
   * Constructor<p>
   * @param xpane The SheafScopePosetPane containing the tree this listener 
   *              is registered on.
   */
  public SheafScopeBaseSelectionListener(SheafScopePosetPane xpane)
  {
    //$$TODO: "target" is pane, so pass it in to CTOR.

    // Precondition: pane != null.
    posetPane = xpane;
    //pane = posetPane.getBasePane();
  }

  /**
   * The action to be taken when a single mouse click
   * event is detected.
   * We only want to call restrictTo if the user clicked on a node.
   * Ignore programmatic selections.<p>
   *
   * @param xevent The detected <code>MouseEvent</code>.
   *
   * 
   */
  public void mouseClicked(MouseEvent xevent)
  {
    SheafScopeBasePane pane = posetPane.getBasePane();

    if(pane == null)
      return;

    pane.doRestrictTo(xevent);
  }
}
