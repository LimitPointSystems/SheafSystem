
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

package tools.SheafScope;

import bindings.java.*;
import tools.common.util.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

/**
 * Specialized version of Jtree to accommodate the needs of SheafScope.
 * Retrieves the poset_member object attached to root and iterates recursively
 * over it's children, adding a single node to the tree for each.<p>
 */
public class SheafScopeJTree extends JTree
{
  private SheafScopeTreeCellRenderer renderer;
  private SheafScopeAbstractTreePane treePane;
  private SheafScopeTreeNode rootNode;
  private SheafScopeTreeWillExpandListener expandListener;

  /**
   * Bottom member shared by all nodes for efficiency.
   */
  private abstract_poset_member bottomMember;

  // Control for toggling bottoms, shared by all nodes in tree.
  // $$HACK: A Boolean (boolean wrapper) might seem more
  // appropriate, but Booleans are immutable, as are Strings.

  private StringBuffer showBottomsControl;

  /**
   * Constructor<p>
   *
   * @param xroot The <code>SheafScopeTreeNode</code> to use as the root node of this tree.
   */
  public SheafScopeJTree(SheafScopeAbstractTreePane xtreePane, SheafScopeTreeNode xroot)
  {
    this(xtreePane, xroot, false);
  }

  /**
   * Constructor
   *
   * @param xroot The SheafScopeTreeNode (with poset_member attached)
   *              which will be the root node of the generated tree.
   * @param xshowBottoms Toggles display of "bottom" nodes.
   */
  public SheafScopeJTree(SheafScopeAbstractTreePane xtreePane,
                         SheafScopeTreeNode xroot,
                         boolean xshowBottoms)
  {
    super(xroot);

    this.setLargeModel(true);

    treePane = xtreePane;
    rootNode = xroot;

    //     System.err.println("SheafScopeJTree CTOR");
    //     System.err.println("  xroot = " + xroot);
    //     System.err.println("  xroot.getUserObject() = " + xroot.getUserObject());
    //     System.err.println("  xroot.getMember() = " + xroot.getMember());
    //     System.err.println("  xroot.getMember().name_space() = " + xroot.getMember().name_space());
    //     System.err.println("  xroot.getMember().host() = " + xroot.getMember().host());
    //     System.err.println("  xroot.getMember().host().name() = " + xroot.getMember().host().name());

    showBottomsControl = new StringBuffer(xshowBottoms ? "T" : "F");
    xroot.setShowBottomsControl(showBottomsControl);

    try
    {
      // Create the bottom poset member;
      // shared by all bottom nodes for efficiency.

      abstract_poset_member mbr = xroot.getMember();

      poset_state_handle host = mbr.host();

      bottomMember = xroot.getMember().host().bottom();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    setSelectionRow(0);

    // Set the background color (use the same for the cells).

    Color backgroundColor = Color.white;
    setBackground(backgroundColor);

    if(SheafScopeConstants.DEBUG == true)
    {
      setBorder(BorderFactory.createMatteBorder(4, 4, 4, 4, Color.cyan));
    }

    setShowsRootHandles(true);

    // Enable tool tips.

    ToolTipManager.sharedInstance().registerComponent(this);

    // Set the popup menu.

    setComponentPopupMenu(new SheafScopeTreePopupMenu(this));

    // Create a cell renderer.

    renderer = new SheafScopeTreeCellRenderer();
    renderer.setBackgroundNonSelectionColor(backgroundColor);
    setCellRenderer(renderer);

    // Add a will expand listener to create children as tree is expanded.

    expandListener = new SheafScopeTreeWillExpandListener(this);
    addExpandListener();
  }

  /**
   * Disable the listening for expand events
   */
  public void removeExpandListener()
  {
    removeTreeWillExpandListener(expandListener);
  }

  /**
   * Enable the listening for expand events
   */
  public void addExpandListener()
  {
    addTreeWillExpandListener(expandListener);
  }

  /**
   * The tree pane
   */
  public SheafScopeAbstractTreePane getTreePane()
  {
    return treePane;
  }

  /**
   * Makes the children of parentNode.<p>
   *
   * @param xparentNode The parent treenode to which we will attach children
   * 
   * 
   */
  protected boolean makeChildren(SheafScopeTreeNode xparentNode)
  {
    return makeChildren(xparentNode, true);
  }

  /**
   * Makes the children of parentNode.<p>
   *
   * @param xparentNode The parent treenode to which we will attach children
   * @param xwarn Warn the user if the number of children exceed the <code>CHILD_LIMIT</code>
   * 
   */
  protected boolean makeChildren(SheafScopeTreeNode xparentNode, boolean xwarn)
  {
    try
    {

      abstract_poset_member parent = xparentNode.getMember();

      if(xwarn && parent.cover_ct(true) > SheafScopeConstants.CHILD_LIMIT)
      {
        // The number of children is larger than the limit.  Ask the user to continue.

        int result = JOptionPane.showConfirmDialog(treePane,
                     "There are " +
                     //$$Integer.toString(parent.cover_ct(true)) +
                     Long.toString(parent.cover_ct(true)) +
                     " children.\n" +
                     "Expansion may take a few seconds." +
                     "\n\nContinue with expansion?",
                     "Expand?",
                     JOptionPane.WARNING_MESSAGE);

        if(result != JOptionPane.YES_OPTION)
          return false;
      }

      // Iterate over lower cover of poset member of node, constructing children.

      index_space_iterator itr = parent.get_cover_id_space_iterator(true);

      while(!itr.is_done())
      {
        SheafScopeTreeNode childNode = new SheafScopeTreeNode(parent.host(), itr.hub_pod(), showBottomsControl);
        xparentNode.add(childNode);

        itr.next();
      }

      parent.release_cover_id_space_iterator(itr);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    // Notify the underlying tree model that the node structure has changed.

    DefaultTreeModel model = (DefaultTreeModel)getModel();
    model.nodeStructureChanged(xparentNode);

    return true;
  }

  /**
   * Detach the members of this tree.
   */
  public void detachStates()
  {
    rootNode.detachStates();
  }

  /**
   *  Determines whether or not the "bottom" nodes are visible.<p>
   *
   *  @param xbottomsVisible true if the "bottom" nodes should be displayed.
   *
   */
  public void setShowBottoms(boolean xbottomsVisible)
  {

    showBottomsControl.setCharAt(0, xbottomsVisible ? 'T' : 'F');

    // Save the expanded paths in a Vector.

    Vector<TreePath> paths = new Vector<TreePath>();

    for(int i=0; i<getRowCount(); i++)
    {
      if(isExpanded(i))
        paths.add(getPathForRow(i));
    }

    // Go through the paths and expand/or collapse as necessary.

    for(int i=0; i<paths.size(); i++)
    {
      TreePath path = (TreePath)paths.get(i);

      // Get the last node in the path.

      SheafScopeTreeNode lastNode
      = (SheafScopeTreeNode)path.getLastPathComponent();

      // Get the first child of the last node in the (expanded) path.
      // This node could contain a child which is a "bottom" node.

      SheafScopeTreeNode lastNodeChild
      = (SheafScopeTreeNode)lastNode.getFirstChild();

      // We were not showing "bottom" nodes before.

      if(xbottomsVisible)
      {
        // Expand every current path.

        expandPath(path);

        // Only expand more is we have a single child node.
        // "bottom: nodes are always an only (first) child.

        if(lastNodeChild.getChildCount() == 1)
        {
          // Get the first (only) child.

          SheafScopeTreeNode node
          = (SheafScopeTreeNode)lastNodeChild.getFirstChild();

          // Check if it is a "bottom" node and expand its parent
          // if it is.

          if(node.isBottom())
          {
            TreePath childPath = new TreePath(lastNodeChild.getPath());
            expandPath(childPath);
          }
        }
      }
      else
      {
        // Check if the path is to a "bottom" node and collapse
        // the path currently expanded path if it is.

        if(lastNodeChild.isBottom())
        {
          collapsePath(path);
        }
      }
    }
  }

  /**
   * Public accessor for private <i>rootNode</i> data member.<p>
   *
   * @return This tree's root node.
   */
  public SheafScopeTreeNode getRootNode()
  {
    return rootNode;
  }

  /**
   * Returns the currently selected node.<p>
   *
   * @return This tree's currently selected node.
   */
  public SheafScopeTreeNode getSelectedNode()
  {
    SheafScopeTreeNode node = (SheafScopeTreeNode)this.getLastSelectedPathComponent();
    return node;
  }

  /**
   * The action to be taken when a <code>TreeExpansionEvent</code> is detected.<p>
   *
   * @param event A TreeExpansionEvent</code>.
   *
   * 
   */
  void doExpand(TreeExpansionEvent event)
  {
    TreePath path = event.getPath();
    SheafScopeTreeNode node = (SheafScopeTreeNode)path.getLastPathComponent();
    SheafScopeTreeNode lastNodeChild = new SheafScopeTreeNode();

    if(node.getChildCount() == 0)
    {
      // Make the next generation of
      // children before expansion occurs.

      if(makeChildren(node))
      {
        // Get the first child of the last node in the (expanded) path.
        // make sure the child exists first.

        try
        {
          lastNodeChild = (SheafScopeTreeNode)node.getFirstChild();
          path = path.pathByAddingChild(lastNodeChild);
        }
        catch(NoSuchElementException nse)
        {
          //$$TODO: print the message out to the status bar
          System.out.println("Node has no children" + nse);
        }

        // Reset the selection.

        setSelectionPath(path);
      }
    }

    treePane.annotate();
  }

  /**
   * The action to be taken whenever a node in the tree is about to be collapsed.<p>    
   *
   * @param event A <code>TreeExpansionEvent</code>.
   *
   * 
   */
  void doCollapse(TreeExpansionEvent event)
  {}


}
