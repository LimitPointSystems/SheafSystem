
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
import tools.common.gui.*;
import tools.common.util.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

/**
 * This class provides an abstract class from which
 * to derive specialized tree pane classes.  It contains
 * variables and methods which are common to several
 * classes within the application framework.<p>
 */
public abstract class SheafScopeAbstractTreePane extends JPanel
{

  /**
   * The <code>SheafScopePosetPane</code> associated with this tree pane.
   */
  protected SheafScopePosetPane posetPane;

  /**
   * The <code>abstract_poset_member</code> associated with this tree pane.
   */
  protected abstract_poset_member member = null;

  /**
   * The <code>SheafScopeJTree</code> associated with this tree pane.
   */
  protected SheafScopeJTree tree = null;

  /**
   * The currently selected tree node.
   */
  protected SheafScopeTreeNode currentNode;

  /**
   * The scroll pane <code>JPanel</code> container for this tree pane.
   */
  protected JPanel scrollPanePanel;

  /**
   * The <code>SheafScopeTreeScrollPane</code> container for this tree.
   */
  protected SheafScopeTreeScrollPane scrollPane;

  /**
   * The tool bar associated with this tree pane.
   */
  protected JToolBar toolBar;

  //   /**
  //    * The "show bottoms" button associated with this tree pane.
  //    */
  //   protected JToggleButton showBottomsButton;

  /**
   * The title of this tree pane window.
   */
  protected JLabel title;

  /**
   * The <code>JLabel</code> associated with this tree pane.
   */
  protected JLabel paneLabel;

  /**
   * The <code>Action</code> for expand branch events.
   */
  protected Action expandAction;

  /**
   * The <code>Action</code> for collapse branch events.
   */
  protected Action collapseAction;

  //   /**
  //    * The <code>Action</code> for show bottoms events.
  //    */
  //   protected Action showBottomsAction;


  /**
   *  Provides a super constructor to specialized classes.<p>
   *
   * @param xposetPane the <code>SheafScopePosetPane</code> container
   *                  within which an instance of a specialized class
   *                  will reside.
   * @param xmember the <code>PosetMember</code> to be represented in the
   *               tree pane. 
   */
  protected SheafScopeAbstractTreePane(SheafScopePosetPane xposetPane,
                                       abstract_poset_member xmember)
  {
    this.posetPane = xposetPane;
    this.member = xmember;

    if(member != null)
      createTree(false);

    makePane();

    if(tree != null)
    {
      TreePath path = tree.getSelectionPath();

      // Get the number of items in the path.

      int pathCt = path.getPathCount();

      if(path != null)
      {
        // pathCt-1 reflects the currently selected item.

        currentNode = (SheafScopeTreeNode)path.getPathComponent(pathCt-1);
      }
    }
  }

  /**
   * Method to construct and assemble the appropriate Swing
   * components for this pane.<p>
   *
   * 
   */
  protected void makePane()
  {
    title = new JLabel(" ");

    createActions();

    setLayout(new BorderLayout());
    setBackground(Color.white);

    JPanel toolBarPanel = new JPanel(new BorderLayout());
    toolBarPanel.setBorder(BorderFactory.createRaisedBevelBorder());

    toolBar = createToolBar();
    toolBarPanel.add(toolBar, BorderLayout.CENTER);

    scrollPanePanel = new JPanel(new BorderLayout());

    if(member != null)
    {
      scrollPane = new SheafScopeTreeScrollPane(tree, posetPane.getMainPane().getEnableRemoteX());
      scrollPanePanel.add(scrollPane, BorderLayout.CENTER);
    }
    else
    {
      paneLabel = new JLabel("N/A", SwingConstants.CENTER);
      paneLabel.setOpaque(true);
      paneLabel.setBackground(Color.white);
      scrollPanePanel.add(paneLabel, BorderLayout.CENTER);
    }

    if(SheafScopeConstants.DEBUG == true)
    {
      setBorder(BorderFactory.createMatteBorder(5,5,5,5,Color.green));

      scrollPanePanel.setBorder(
        BorderFactory.createMatteBorder(5,5,5,5,Color.magenta));
    }

    add
      (toolBarPanel, BorderLayout.NORTH);
    add
      (scrollPanePanel, BorderLayout.CENTER);
  }

  /**
   * Method to construct and assemble the appropriate action
   * components for this pane.<p>
   *
   * 
   */
  protected void createActions()
  {
    // Establish an actionListener for branch expansion events.

    //expandAction = new SheafScopeExpandBranchCommand(this);

    String iconPath = SheafScopeConstants.IMAGE_PATH + "expand.png";
    expandAction
    = new GenericAction(this,              //target
                        "expandBranch",    //method
                        "Expand Branch",   //action name
                        "Expand Branch",   //label
                        iconPath,          //icon
                        "Expand branch");  //tooltip

    // Establish an actionListener for branch collapse events.

    //collapseAction = new SheafScopeCollapseBranchCommand(this);

    iconPath = SheafScopeConstants.IMAGE_PATH + "expand.png";
    collapseAction
    = new GenericAction(this,               //target
                        "collapseBranch",   //method
                        "Collapse Branch",  //action name
                        "Collapse Branch",  //label
                        iconPath,           //icon
                        "Collapse branch"); //tooltip


    //     String iconPath = SheafScopeConstants.IMAGE_PATH + "showBottoms.png";
    //     showBottomsAction
    //     = new GenericAction(this,
    //                         "showBottoms",        //method
    //                         "Show Bottoms",       //action name
    //                         "Show Bottoms",       //label
    //                         iconPath,             //icon
    //                         "Show bottom nodes"); //tooltip
  }

  /**
   * Method to construct and assemble the appropriate toolBar
   * components for this pane.<p>
   *
   * @return The newly created <code>JToolBar</code>.
   */
  JToolBar createToolBar()
  {
    JToolBar bar = new JToolBar();

    bar.add(title);

    bar.addSeparator();
    bar.add(Box.createHorizontalGlue());

    addToolBarButtons(bar);
    bar.addSeparator();

    return bar;
  }

  /**
   * Method to construct toolbar buttons.<p>
   *
   * @param xbar The toolbar to add the buttons to.
   *
   * 
   */
  void addToolBarButtons(JToolBar xbar)
  {
    //     // Add showBottoms button

    //     //$$ISSUE: JDK 1.3 specific;
    //     //$$showBottomsButton = new JToggleButton(showBottomsAction);

    //     Icon icon = (Icon)(showBottomsAction.getValue(Action.SMALL_ICON));
    //     String tooltip = (String)(showBottomsAction.getValue(Action.SHORT_DESCRIPTION));
    //     showBottomsButton = new JToggleButton(icon);
    //     showBottomsButton.setToolTipText(tooltip);
    //     showBottomsButton.addActionListener(showBottomsAction);

    //     showBottomsButton.setPreferredSize(new Dimension(24, 24));
    //     showBottomsButton.setMaximumSize(new Dimension(24, 24));
    //     xbar.add(showBottomsButton);

    return;
  }

  /**
   * Public accessor for the <code>JToolBar</code> associated with
   * this pane.<p>
   *
   * @return The <code>JToolBar</code> associated with this pane.
   */
  public JToolBar getToolBar()
  {
    return toolBar;
  }

  /**
   * Sets the window title to the specified <code>String</code><p>
   *
   * @param xtext The <code>String</code> to use as window title.
   *
   * 
   */
  public void setTitle(String xtext)
  {
    title.setText(xtext);
  }

  /**
   * Sets the window title to the specified <code>String</code>
   * Currently used only for "NameSpace" case.<p>
   *
   * @param xtext The <code>String</code> to use as window title.
   *
   * 
   */
  public void setPaneText(String xtext)
  {
    paneLabel.setText(xtext);
  }

  /**
   * Public accessor for the posetpane associated with this 
   * treepane.<p>
   *
   * @return The <code>SheafScopePosetPane</code> associated with this treepane.
   */
  public SheafScopePosetPane getPosetPane()
  {
    return posetPane;
  }

  /**
   * Public accessor for the <code>abstract_poset_member</code> associated with this 
   * treepane.<p>
   *
   * @return The <code>abstract_poset_member</code> associated with this treepane.
   */
  public abstract_poset_member getPosetMember()
  {
    return member;
  }

  /**
   * Gets the <code>SheafScopeJTree</code> associated with this Pane.<p>
   *
   * @return The <code>SheafScopeJTree</code> associated with this Pane.
   */
  public SheafScopeJTree getTree()
  {
    return tree;
  }

  /**
   * Makes <i>xnode</i> the currently selected node.<p>
   *
   * @param xnode The selected tree node
   */
  public void setSelectedNode(SheafScopeTreeNode xnode)
  {
    currentNode = xnode;
  }

  /**
   * Returns the <code>SheafScopeTreeNode</code> which is
   * currently selected.<p>
   *
   * @return The selected tree node.
   */
  public SheafScopeTreeNode getSelectedNode()
  {
    TreePath path = tree.getSelectionPath();

    // Kludge to deal with potential problem.
    // Want to make sure this method does not return null;

    if(currentNode == null)
    {
      tree.setSelectionRow(0);
      TreeNode node =(TreeNode)path.getPathComponent(0);
      currentNode = (SheafScopeTreeNode)node;
    }

    return currentNode;
  }

  /**
   * Returns the <code>abstract_poset_member</code> represented by the
   * currently selected tree node.<p>
   *
   * @return the <code>abstract_poset_member(/code> represented by the
   *         currently selected tree node.
   */
  public abstract_poset_member getSelectedMember()
  {
    return getSelectedNode().getMember();
  }

  /**
   * Expands the tree contained in this pane.<p>
   *
   * 
   */
  public void expandBranch()
  {
    if(tree == null)
      return;

    // Block all user input to the interface while busy.

    getPosetPane().getMainPane().getParentFrame().setWaitState(true);

    // Get the currently selected node.

    SheafScopeTreeNode node = getSelectedNode();
    if(node == null)
    {
      node = getRoot();
      setSelectedNode(node);
    }

    // Iterate over children of node in pre-order,
    // expanding the path as we go.

    for(Enumeration children = node.preorderEnumeration();
        children.hasMoreElements(); )
    {
      SheafScopeTreeNode nextNode
      = (SheafScopeTreeNode)children.nextElement();

      // Expand the path for each node found.

      tree.expandPath(new TreePath(nextNode.getPath()));
    }

    // Unblock input

    getPosetPane().getMainPane().getParentFrame().setWaitState(false);
  }

  /**
   * Collapses the tree contained in this pane.<p>
   * 
   * 
   */
  public void collapseBranch()
  {
    if(tree == null)
      return;

    // Get the currently selected node.

    SheafScopeTreeNode node = getSelectedNode();

    if(node == null)
      return;

    // Enumerate over children of node in post-order,
    // collapsing the path as we go.

    for(Enumeration children = node.postorderEnumeration();
        children.hasMoreElements(); )
    {
      SheafScopeTreeNode nextNode
      = (SheafScopeTreeNode)children.nextElement();

      tree.collapsePath(new TreePath(nextNode.getPath()));
    }
  }

  //   /**
  //    * If the tree is not empty, show the "bottom" nodes.<p>
  //    *
  //    *
  //    */
  //   public void showBottoms()
  //   {
  //     if(tree != null)
  //     {
  //       tree.setShowBottoms(showBottomsButton.isSelected());
  //     }
  //   }

  /**
   * Create and assemble the tree.<p>
   *
   * @param xshowBottoms Toggle display of "bottom" nodes.
   *
   */
  void createTree(boolean xshowBottoms)
  {
    //     System.out.println(member);

    // $$ISSUE: Do not reuse the member for the root node to allow the
    //          finalize() method of SheafScopeTreeNode to detach the member.

    SheafScopeTreeNode root =
	new SheafScopeTreeNode(member.host(), member.index().pod(), null);

    tree = new SheafScopeJTree(this, root, xshowBottoms);

    tree.putClientProperty("JTree.lineStyle", "Angled");

    tree.getSelectionModel()
    .setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

    // Collapse root then expand to show the only the
    // first generation of children.

    tree.collapseRow(0);

    try
    {
      abstract_poset_member mbr = root.getMember();

      long lower_cover_ct = mbr.cover_ct(true);
      if(lower_cover_ct > 0 && lower_cover_ct <= SheafScopeConstants.CHILD_LIMIT)
      {
        // The number of children did not exceed the limit.
        // Expand the root node.

        //$$ISSUE: Originally this method returned a tree object
        //         to the constructor from which it is called.
        //         However, in certain cases the following call
        //         to expandRow wound up trying to access the tree
        //         data member of this class which was null until
        //         the current method returned a reference to one.
        //         The expandRow call now works since the tree data
        //         member is created in this method.  We still need
        //         to find out why the expandRow call resulted in
        //         the tree data member being referenced.

        tree.expandRow(0);
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    //$$return tree;
  }

  /**
   * Detach the member members of this pane's tree.
   */
  public void detachStates()
  {
    if(tree != null)
    {
      tree.detachStates();
    }
  }

  /**
   * Sets the currently selected row in the tree based on 
   *  a match of the passed in string with a node in the tree.<p>
   *
   * @param xname The string value of the node(row) to be selected
   * in the tree.
   *
   * 
   */
  protected void setSelectionRow(String xname)
  {
    // Get the root of the tree.

    SheafScopeTreeNode node = getRoot();

    // Iterate over children of root node in pre-order.

    for(Enumeration children = node.preorderEnumeration();
        children.hasMoreElements(); )
    {
      SheafScopeTreeNode nextNode
      = (SheafScopeTreeNode)children.nextElement();

      String nodeName = nextNode.getName();

      // We got a name match, select the node.

      if(nodeName.equals(xname))
      {
        TreePath path = new TreePath(nextNode.getPath());
        tree.setSelectionPath(path);
      }
    }
  }

  /**
  * Tag the nodes in a tree as being displayed and with a color.
  * Used by <code>SheafScopeDisplayPanel</code> to 
  * tag nodes in the namespace tree and parent's focus tree
  * to show this member as displayed and to set the node background
  * color to match the color of the corresponding tab in the JTabbedPane.
  *
  * @param xname The member name.
  * @param xcolor A reference to a <code>Color</code> instance.
  */
  protected void tagPaths(String xname, Color xcolor)
  {
    tagPaths(xname, xcolor, true);
  }

  /**
   *  Untags nodes in a tree previously tagged by calling <code>tagPaths</code>.
   *  The node background colors (in the tree) are reset to the default. 
   */
  protected void untagPaths(String xname)
  {
    tagPaths(xname, null, true);
  }

  /**
   *  Convenience method used (presently) by <code>tagPaths</code> and
   *  <code>untagPaths</code>.
   */
  private void tagPaths(String xname, Color xcolor, boolean xisDisplayed)
  {
    SheafScopeTreeNode root = getRoot();

    Enumeration itr =  root.depthFirstEnumeration();

    while(itr.hasMoreElements())
    {
      SheafScopeTreeNode node = (SheafScopeTreeNode) itr.nextElement();

      try
      {
        abstract_poset_member pm = node.getMember();
        String nodeName = pm.name();

        if(xname.equals(nodeName))
        {
          node.setIsDisplayed(xisDisplayed);

          if(xisDisplayed)
            node.setDisplayedColor(xcolor);
          else
            node.setDisplayedColor(null);
        }
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();
      }
    }
  }

  /**
   *
   */
  protected void scrollToVisible(String xname)
  {
    SheafScopeTreeNode root = getRoot();

    Enumeration itr =  root.breadthFirstEnumeration();
    while(itr.hasMoreElements())
    {
      SheafScopeTreeNode node
      = (SheafScopeTreeNode) itr.nextElement();

      try
      {
        abstract_poset_member pm = node.getMember();
        String nodeName = pm.name();

        if(xname.equals(nodeName))
        {
          TreePath path = new TreePath(node.getPath());
          int row = tree.getRowForPath(path);
          tree.scrollRowToVisible(row);
          break;
        }
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();
      }
    }
  }

  //$$TODO: Change to "getRootNode".
  /**
   *
   */
  protected SheafScopeTreeNode getRoot()
  {
    SheafScopeTreeNode result
    = (SheafScopeTreeNode)tree.getModel().getRoot();

    return result;
  }

  /**
   *
   */
  protected SheafScopeJTable getTable()
  {
    SheafScopeJTable result = posetPane.getTable();
    return result;
  }

  /**
   *
   */
  protected SheafScopeAbstractTablePane getTablePane()
  {
    SheafScopeAbstractTablePane result = posetPane.getTablePane();
    return result;
  }

  /**
   *
   */
  protected SheafScopeAbstractTableModel getTableModel()
  {
    SheafScopeJTable table = posetPane.getTable();
    SheafScopeAbstractTableModel result
    = (SheafScopeAbstractTableModel)table.getModel();

    return result;
  }

  /**
   * Abstract method for coloring the tree nodes upon expansion
   */
  protected abstract void annotate();
}

