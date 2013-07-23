
/**
 * Classname: SheafScopeTreeWillExpandListener
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import javax.swing.*;
import javax.swing.event.*;

/**
 * SheafScopeTreeWillExpandListener creates tree nodes before expansion.<p> 
 */
public class SheafScopeTreeWillExpandListener implements TreeWillExpandListener
{
  private SheafScopeJTree tree;

  /**
   * Constructor
   * @param xtree The <code>SheafScopeJTree</code> this listener is registered on.
   */
  public SheafScopeTreeWillExpandListener(SheafScopeJTree xtree)
  {
    tree = xtree;
  }

  /**
   * The action to be taken when a <code>TreeExpansionEvent</code> is detected.<p>
   *
   * @param event A TreeExpansionEvent</code>.
   *
   * 
   */
  public void treeWillExpand(TreeExpansionEvent event)
  {
    tree.doExpand(event);
  }

  /**
   * The action to be taken whenever a node in the tree is about to be collapsed.<p>    
   *
   * @param event A <code>TreeExpansionEvent</code>.
   *
   * 
   */
  public void treeWillCollapse(TreeExpansionEvent event)
  {
    tree.doCollapse(event);
  }

}
