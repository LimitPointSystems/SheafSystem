
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
import javax.swing.tree.*;

/**
 * Specialization of <code>DefaultMutableTreeNode</code> to add SheafScope
 * specific features.<p>
 */
public class SheafScopeTreeNode extends DefaultMutableTreeNode
{
  /*
   * Switch to control whether bottoms should be shown,
   * used by isLeaf(). We need an object for this purpose
   * so that all nodes in a tree can share a reference to it. 
   */

  // $$HACK: Class Boolean would be more appropriate,
  // except instances of Boolean are immutable.

  protected StringBuffer showBottomsControl;

  private boolean isDisplayed = false;
  private Color   displayedColor = null;
  private String  toolTipText = null;

  private abstract_poset_member member = null;

  /**
   * Creates a tree node that has no parent and no children, but which
   * allows children.
   */
  public SheafScopeTreeNode()
  {
    super();
  }

  /**
   * Creates a tree node with no parent or no child nodes.  Initialize
   * the user object to the member with xhost and xindex. Allow children.
   *
   * @param xhost The member host.
   * @param xindex The index of the member.
   * @param xshowBottomsControl Controls whether bottom is shown under this node. 
   *                            If null, defaults to "F", i.e. not shown.
   */
  public SheafScopeTreeNode(poset_state_handle xhost,
			    int xindex,
			    StringBuffer xshowBottomsControl)
  {
    this(xhost, xindex, xshowBottomsControl, true);
  }

  /**
   * Creates a tree node with no parent or no child nodes.  Initialize
   * the user object to the member with xhost and xindex. 
   * Allow children only if specified.
   *
   * @param xhost The member host.
   * @param xindex The index of the member.
   * @param xshowBottomsControl Controls whether bottom is shown under this node. 
   *                            If null, defaults to "F", i.e. not shown.
   * @param xallowsChildren If true, the node is allowed to have child
   *                        nodes -- otherwise, it is always a leaf node.
   */
  public SheafScopeTreeNode(poset_state_handle xhost,
			    int xindex,
			    StringBuffer xshowBottomsControl,
			    boolean xallowChildren)
  {
    super();

    // Create the member with the correct type.

    // $$TODO: Fix for general case.

    if(xhost instanceof sec_rep_space)
    {
      sec_rep_space lhost = (sec_rep_space) xhost;

      member = new sec_vd(lhost, xindex);
    }
    else if(xhost instanceof namespace_poset)
    {
      namespace_poset lhost = (namespace_poset) xhost;

      member = new namespace_poset_member(lhost, xindex);
    }
    else // assume it's an abstract_poset_member
    {
      member = new total_poset_member(xhost, xindex);
    }

    setUserObject(member);

    // Set the show bottom control flag.

    if(xshowBottomsControl != null)
    {
      this.showBottomsControl = xshowBottomsControl;
    }
    else
    {
      this.showBottomsControl = new StringBuffer("F");
    }

    // Set the allow children flag.

    setAllowsChildren(xallowChildren);
  }

  /**
   * Detach the member of this node and the members of child nodes.
   */
  public void detachStates()
  {
    // Detach this node's member.  The member may be null if an empty
    // node was create.  It may also already be unattached if it is the
    // top node.

    if(member != null && member.is_attached())
    {
      member.detach_from_state();
    }
    
    // Detach the members of the child nodes.

    Enumeration children = children();
    while(children.hasMoreElements())
    {
      ((SheafScopeTreeNode) children.nextElement()).detachStates();
    }
  }

  /**
   * Returns the result of sending <code>toString()</code> to this node's
   * user object, or null if this node has no user object.<p>
   *
   * @return The string value of this node's user object. null if this
   *         node has no user object.
   */
  public String toString()
  {
    if(member == null)
    {
      return null;
    }
    else
    {
      try
      {
        String name = member.name();
        if(name == null || name.equals(""))
          name = "index= " + member.index().pod();

        return name;
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();

        return null;
      }
    }
  }

  /**
   * Get the name of the poset member represented by this node. 
   *
   * @return The <code>String</code> value of the name.
   */
  public String getName()
  {
    return toString();
  }

  /**
   * public accessor method to return the <code>abstract_poset_member</code> attached
   * to the current <code>userObject/code>.<p>
   *
   * @return The <code>abstract_poset_member</code> attached to this node.
   */
  public abstract_poset_member getMember()
  {
    return member;
  }

  /**
   * public accessor method to set the isDisplayed() property of this node.<p>
   *
   * @param tf Boolean indicating the desired display state of this
   * <code>SheafScopeTreeNode</code>.
   *
   * 
   *
   */
  public void setIsDisplayed(boolean tf)
  {
    isDisplayed = tf;
  }

  /**
   * Public accessor method to return the display status of this node.<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is currently displayed.
   *
   */
  public boolean isDisplayed()
  {
    return isDisplayed;
  }

  /**
   * Public accessor method to get the display color of this node.<p>
   *
   * @return The current display color of this <code>SheafScopeTreeNode</code>.
   *
   */
  public Color getDisplayedColor()
  {
    return displayedColor;
  }

  /**
   * Public accessor method to set the display color of this node.<p>
   *
   * @param color The desired color for this <code>SheafScopeTreeNode</code>.
   *
   * 
   *
   */
  public void setDisplayedColor(Color color)
  {
    displayedColor = color;
  }

  /**
   * Public accessor for the private <i>showBottomsControl</i> data member.<p>
   *
   * @return  The showBottomsControl string for this <code>SheafScopeTreeNode</code>.
   *
   */
  public StringBuffer getShowBottomsControl()
  {
    return showBottomsControl;
  }

  /**
   * Inserts control as showBottomsControl string for this <code>SheafScopeTreeNode</code>.<p>
   *
   * @param control The <code>StringBuffer</code> containing the showBottomsControl string 
   * for this <code>SheafScopeTreeNode</code>.
   *
   */
  public void setShowBottomsControl(StringBuffer control)
  {
    showBottomsControl = control;
  }

  /**
   * Public accessor method to get current node's status as leaf.<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is a leaf.
   *
   */
  public boolean isLeaf()
  {
    try
    {
      return (isBottom() ||
	      ((showBottomsControl.charAt(0) == 'F') && isAtom()));
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }

  }

  /**
   * Public accessor method to get node's status as "bottom".<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is "bottom".
   *
   */
  public boolean isBottom()
  {
    try
    {
      //$$HACK:
      //$$ISSUE: We would like to use the following here, but the SWIG generated bindings
      //         currently do not produce direct access from sheaf_constants.BOTTOM_INDEX
      //         or to the "==" operator of scoped_index.  So until this is fixed in
      //         the LPS version of swig we compare the pod values.

      //return ( member.index().pod() == sheaf_constants.BOTTOM_INDEX().pod() );
      return ( member.index().pod() == standard_member_index.BOTTOM_INDEX.swigValue() );

    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }
  }

  /**
   * Public accessor method to get node's status as "top".<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is "top".
   *
   */
  public boolean isTop()
  {
    try
    {
      //$$HACK:
      //$$ISSUE: We would like to use the following here, but the SWIG generated bindings
      //         currently do not produce direct access from sheaf_constants.BOTTOM_INDEX
      //         or to the "==" operator of scoped_index.  So until this is fixed in
      //         the LPS version of swig we compare the pod values.

      //return ( member.index().pod() == sheaf_constants.TOP_INDEX().pod() );
      return ( member.index().pod() == standard_member_index.TOP_INDEX.swigValue() );

    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }
  }

  /**
   * Public accessor method to get node's status as atom.<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is atom.
   *
   */
  public boolean isAtom()
  {
    try
    {
      return ( member.is_atom() );
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }
  }

  /**
   * Public accessor method to get node's status as jim.<p>
   *
   * @return true if this <code>SheafScopeTreeNode</code> is a jim.
   *
   */
  public boolean isJim()
  {
    try
    {
      return ( member.is_jim(false) );
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return false;
    }
  }

  /**
   * Public accessor method to get node's tooltip text.<p>
   *
   * @return The current ToolTipText for this node.
   *
   */
  public String getToolTipText()
  {
    return toolTipText;
  }

  /**
   * Public mutator method to set this node's tooltip text.<p>
   *
   * @param tip The desired ToolTipText for this node.
   *
   * 
   *
   */
  public void setToolTipText(String tip)
  {
    toolTipText = tip;
  }

}
