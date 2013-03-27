
/**
 * Classname: SheafScopeSchemaSelectionListener
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeSchemaSelectionListener.java,v $ $Revision: 1.16 $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;


/**
 * SheafScopeSchemaSelectionListener is a specialized <code>TreeSelectionListener</code> to
 * suit the needs of the SheafScope. Listens for single node selections on the
 * tree and updates the table model accordingly.<p> 
 */
public class SheafScopeSchemaSelectionListener extends MouseAdapter
{

  private SheafScopePosetPane posetPane;
  //private SheafScopeFiberSchemaPane pane;

  /**
   * Constructor
   * @param xpane The SheafScopePosetPane containing the tree this listener 
   *              is registered on.
   */
  public SheafScopeSchemaSelectionListener(SheafScopePosetPane xpane)
  {
    //$$TODO: "target" is pane, so pass it in to CTOR.

    // Precondition: pane != null.

    posetPane = xpane;
    //pane = posetPane.getFiberSchemaPane();
  }

  /**
   * The action to be taken when a single mouse click
   * event is detected.<p>
   * We only want to call restrictTo if the user clicked on a node;
   * ignore programmatic selections.<p>
   *
   * @param xevent The detected <code>MouseEvent</code>.
   *
   * 
   */
  public void mouseClicked(MouseEvent xevent)
  {
    SheafScopeFiberSchemaPane pane = posetPane.getFiberSchemaPane();

    if(pane == null)
      return;

    pane.doRestrictTo(xevent);
  }
}
