/**
 * Classname: SheafScopeTreeCellRenderer
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

import javax.swing.*;
import javax.swing.tree.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;

/**
 * SheafScopeTreeCellRender extends the <code>defaultTreeCellRenderer</code>
 * to provide <code>SheafScopeMainPane</code> with appropriate icons for it's various
 * node types. <p>
 */
public class SheafScopeTreeCellRenderer extends DefaultTreeCellRenderer
{
  // Make icons static so we only have one set for
  // all trees.

  private static ImageIcon topIcon;
  private static ImageIcon bottomIcon;
  private static ImageIcon jrmIcon;
  private static ImageIcon jimIcon;
  private static ImageIcon nspaceJrmIcon;
  private static ImageIcon nspaceJimIcon;
  private static ImageIcon nspaceTopIcon;

  static
  {
    String path = SheafScopeConstants.IMAGE_PATH;

    topIcon       = GuiUtilities.getImageIcon(path + "top.png");
    bottomIcon    = GuiUtilities.getImageIcon(path + "bottom.png");
    jrmIcon       = GuiUtilities.getImageIcon(path + "jrm.png");
    jimIcon       = GuiUtilities.getImageIcon(path + "jim.png");
    nspaceJrmIcon = GuiUtilities.getImageIcon(path + "nspaceJrm.png");
    nspaceJimIcon = GuiUtilities.getImageIcon(path + "nspaceJim.png");
    nspaceTopIcon = GuiUtilities.getImageIcon(path + "nspaceTop.png");
  };

  // For saving the normal cell background colors.

  private Color normalBackgroundNonSelectionColor;
  private Color normalBackgroundSelectionColor;
  private Color normalBorderSelectionColor;

  // The displayed cell background colors.

  private static Color displayedBackgroundNonSelectionColor = Color.lightGray;
  private static Color displayedBorderSelectionColor        = Color.red;

  /**
   * Constructor
   */
  public SheafScopeTreeCellRenderer()
  {
    super();

    normalBackgroundNonSelectionColor = getBackgroundNonSelectionColor();
    normalBackgroundSelectionColor    = getBackgroundSelectionColor();
    normalBorderSelectionColor        = getBorderSelectionColor();
  }

  /**
   * Overload of the default class of the same name, specialized to
   * handle poset treeNodes.<p>
   *
   * @param tree The JTree to render nodes for.
   * @param value The object attached to the current TreeNode
   * @param sel The selection state of the current tree node
   * @param expanded true if the current node's state is expanded
   * @param leaf true if the current node is a leaf
   * @param row The row index of the current node
   * @param hasFocus true is the current tree has the focus.
   *
   * @return The <code>TreeCellRendererComponent</code> for this tree.
   */
  public Component getTreeCellRendererComponent(
    JTree tree, Object value,
    boolean sel, boolean expanded,
    boolean leaf, int row, boolean hasFocus)
  {

    super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);

    SheafScopeTreeNode treeNode = (SheafScopeTreeNode)value;
    abstract_poset_member member = treeNode.getMember();

    setToolTipText(treeNode.getToolTipText());

    setColors(treeNode);

    try
    {
      // Determine the type of the current member, and set
      // the appropriate icon for that type.

      //$$HACK:
      //$$ISSUE: We would like to use the following here, but the SWIG generated bindings
      //         currently do not produce direct access from sheaf_constants.*_INDEX
      //         or to the "==" operator of scoped_index.  So until this is fixed in
      //         the LPS version of swig we compare the pod values.

      //if(member.index().pod() == sheaf_constants.BOTTOM_INDEX().pod())
      if(member.index().pod() == standard_member_index.BOTTOM_INDEX.swigValue())
      {
        setIcon(bottomIcon);
      }
      //else if(member.index().pod() == sheaf_constants.TOP_INDEX().pod())
      else if(member.index().pod() == standard_member_index.TOP_INDEX.swigValue())
      {
        setIcon(topIcon);
      }
      else if(member.is_jim(false))
      {
        if(member.host() instanceof namespace_poset)
        {
          // Member is a namespace jim.

          setIcon(nspaceJimIcon);
        }
        else
        {
          // Member is just an ordinary jim.

          setIcon(jimIcon);
        }
      }
      else
      {
        // Must be a jrm.

        setIcon(jrmIcon);
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    return this;
  }

  /**
   * Sets the color of the actual tree node display.<p>
   *
   * @param xtreeNode The current <code>SheafScopeTreeNode</code>.
   *
   * 
   */
  protected void setColors(SheafScopeTreeNode xtreeNode)
  {
    setBackgroundNonSelectionColor(normalBackgroundNonSelectionColor);
    setBackgroundSelectionColor(normalBackgroundSelectionColor);
    setBorderSelectionColor(normalBorderSelectionColor);

    if(xtreeNode.isDisplayed())
    {
      setBackgroundNonSelectionColor(xtreeNode.getDisplayedColor());
      setBorderSelectionColor(displayedBorderSelectionColor);
    }
  }
}
