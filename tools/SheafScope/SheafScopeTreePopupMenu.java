/**
 * Classname: SheafScopeTreePopupMenu
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:53 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.SheafScope;

import bindings.java.*;
import tools.common.gui.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;

/**
 * Popup menu for expanding and collapsing tree items.
 *
 */
public class SheafScopeTreePopupMenu extends JPopupMenu
{
  private SheafScopeJTree tree;

  private Action expandAction;
  private Action expandAllAction;
  private Action collapseAction;
  private Action collapseAllAction;

  private boolean prompt = true;

  /**
   * Constructor
   *
   * @param xtree The tree for this menu
   */
  public SheafScopeTreePopupMenu(SheafScopeJTree xtree)
  {
    tree = xtree;

    String tip = "Expand Selected Item";
    expandAction = new GenericAction(this,        // target
                                     "expand",    // method
                                     "Expand",    // action name
                                     "Expand",    // label
                                     null,        // icon
                                     tip);        // tooltip
    add
      (expandAction);

    tip = "Expand Selected Item and All Sub-Items";
    expandAllAction = new GenericAction(this,         // target
                                        "expandAll",  // method
                                        "Expand All", // action name
                                        "Expand All", // label
                                        null,         // icon
                                        tip);         // tooltip
    add
      (expandAllAction);

    tip = "Collapse Selected Item";
    collapseAction = new GenericAction(this,        // target
                                       "collapse",  // method
                                       "Collapse",  // action name
                                       "Collapse",  // label
                                       null,        // icon
                                       tip);        // tooltip
    add
      (collapseAction);

    tip = "Collapse Selected Item and All Sub-Items";
    collapseAllAction = new GenericAction(this,           // target
                                          "collapseAll",  // method
                                          "Collapse All", // action name
                                          "Collapse All", // label
                                          null,           // icon
                                          tip);           // tooltip
    add
      (collapseAllAction);
  }

  public void show(Component invoker, int x, int y)
  {
    // Set appropriate enabling for the selected node

    SheafScopeTreeNode node = (SheafScopeTreeNode)
                              tree.getLastSelectedPathComponent();

    if(node == null || node.isLeaf())
    {
      // No node is selected or the node that is selected is a leaf,
      // do not show the menu.

      return;
    }

    TreePath path = tree.getSelectionPath();

    if(tree.isExpanded(path))
    {
      // Node is already expanded, can't expand and can collapse.

      expandAction.setEnabled(false);
      collapseAction.setEnabled(true);
    }
    else
    {
      // Node must be collapsed, can't collapse and can expand.

      expandAction.setEnabled(true);
      collapseAction.setEnabled(false);
    }

    super.show(invoker, x, y);
  }

  /**
   * Expand selected item
   */
  public void expand()
  {
    TreePath path = tree.getSelectionPath();
    tree.expandPath(path);
  }

  /**
   * Expand selected item and all children
   */
  public void expandAll()
  {
    SheafScopeTreeNode node = (SheafScopeTreeNode)
                              tree.getLastSelectedPathComponent();

    if(prompt)
    {
      // Have not prompted the user yet for this instance of
      // the popup menu.  Prompt the user if the member count
      // of the host is larger than the child limit.

      try
      {
        poset_state_handle host = node.getMember().host();

        if(host.member_ct() > SheafScopeConstants.CHILD_LIMIT)
        {
          int result = JOptionPane.showConfirmDialog(tree.getTreePane(),
                       "The size of this poset is large.\n" +
                       "Expansion may take a few seconds." +
                       "\n\nContinue with expansion?",
                       "Expand?",
                       JOptionPane.WARNING_MESSAGE);

          if(result != JOptionPane.YES_OPTION)
            return;
        }
      }
      catch(Exception e)
      {}

      prompt = false;
    }

    tree.removeExpandListener();
    expand(node);
    tree.addExpandListener();

    tree.getTreePane().annotate();

    // Force the selection of the expanded path.  This will cause
    // the focus table to update.

    tree.clearSelection();
    tree.setSelectionPath(new TreePath(node.getPath()));
  }

  /**
   * Expand the children of a node.
   */
  public void expand(SheafScopeTreeNode xparent)
  {
    if(xparent.getChildCount() == 0)
    {
      // Make next generation of children before expanding.

      tree.makeChildren(xparent, false);
    }

    TreePath path = new TreePath(xparent.getPath());
    tree.expandPath(path);

    // Expand children

    Enumeration e = xparent.children();
    SheafScopeTreeNode child;
    while(e.hasMoreElements())
    {
      child = (SheafScopeTreeNode) e.nextElement();
      expand(child);
    }
  }

  /**
   * Collapse selected item
   */
  public void collapse()
  {
    TreePath path = tree.getSelectionPath();
    tree.collapsePath(path);
  }

  /**
   * Collapse selected item and all children
   */
  public void collapseAll()
  {
    SheafScopeTreeNode node = (SheafScopeTreeNode)
                              tree.getLastSelectedPathComponent();

    tree.removeExpandListener();
    collapse(node);
    tree.addExpandListener();

    tree.getTreePane().annotate();
  }

  /**
   * Collapse the children of a node.
   */
  public void collapse(SheafScopeTreeNode xparent)
  {
    // Collapse children first

    Enumeration e = xparent.children();
    SheafScopeTreeNode child;
    while(e.hasMoreElements())
    {
      child = (SheafScopeTreeNode) e.nextElement();
      collapse(child);
    }

    TreePath path = new TreePath(xparent.getPath());
    tree.collapsePath(path);
  }
}
