/**
 * Classname: SheafScopeDisplayPanel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:52 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.gui.*;
import tools.common.util.*;

import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.net.*;
import java.util.*;

/**
 *
 * SheafScopeDisplayPanel specializes JPanel to accommodate the
 * needs of the SheafScope. It is responsible for instantiation of
 * SheafScope's graphical elements.<p>
 */
public class SheafScopeDisplayPanel extends JTabbedPane
{
  // Color data used to select tab and tree node colors.

  // Starting angle (green);

  private static float hue = 240.0f;
  private static float saturation = 25.0f;
  private static float brightness = 100.0f;

  // Angle increment.

  private static float delta = 40.0f;

  private static Color selectedBackgroundColor = Color.gray;

  private SheafScopeMainPane mainPane;
  private SheafScopeTreeNode selectedNode;

  private ArrayList<String> parentNames = new ArrayList<String>(1);

  /**
   * Table to map names to namespaces
   */
  private Hashtable<String, namespace_poset> namespaces =
    new Hashtable<String, namespace_poset>();

  /**
   * Delimiter for names on tabs.  Inserted between parent
   * name and child name for tabs which are children.
   * Assumes that this string does not occur in any child name.
   * (Probably not a good assumption).<p>
   */
  public static final String NAME_DELIMITER = ": ";

  /**
   * Constructor<p>
   *
   * @param xmainPane Main panel containing this tabbed pane.
   */
  public SheafScopeDisplayPanel(SheafScopeMainPane xmainPane)
  {
    this.mainPane = xmainPane;

    // Add a listener for tab selection events.

    addChangeListener(new SheafScopeSelectTabCommand(this));

    // Create icons for tree.
    // (This is done here because it only needs to be done once.)

    createTreeIcons();

    // Set the selected tab background color.

    UIManager.put("TabbedPane.selected",
                  new ColorUIResource(selectedBackgroundColor));
    SwingUtilities.updateComponentTreeUI(this);
  }

  /**
   * Reopen this pane.  Remove all tabs and clear namespaces.
   */
  public void reopen()
  {
    removeAll();

    parentNames.clear();
    namespaces.clear();
  }

  //$$TODO: Find a better place for this!

  /**
   * Sets our Windows explorer type "collapsed" and "expanded" icon
   * behaviour into the tree.<p>
   */
  private void createTreeIcons()
  {
    String imagePath = SheafScopeConstants.IMAGE_PATH;

    ImageIcon minusIcon = GuiUtilities.getImageIcon(imagePath + "minus.png" );
    ImageIcon plusIcon = GuiUtilities.getImageIcon(imagePath + "plus.png" );

    UIManager.put("Tree.expandedIcon", minusIcon);
    UIManager.put("Tree.collapsedIcon", plusIcon);
  }

  /**
   * Creates a new tab for <code>namespace_poset</code> <i>namespace</i> with tool tip
   * <i>fileName</i>.<p>
   * 
   * @param xnamespace The <code>namespace_poset</code> to display.
   * @param xfileName The file name with which to create the tab ToolTip.
   *
   * 
   */
  public void createTab(namespace_poset xnamespace, String xfileName)
  {
    try
    {
      // Get read access to the namespace in case we don't already have it.

      xnamespace.get_read_write_access(true);

      // Add the namespace to the table

      namespaces.put(xnamespace.name(), xnamespace);

      // Create a name for the tab (and poset pane).

      String lname = createParentName(xnamespace.name());

      // Add the name to a list for later lookups.

      parentNames.add(lname);

      // Create a poset pane.

      SheafScopePosetPane posetPane
      = new SheafScopePosetPane(mainPane, lname, xnamespace.top(), null);

      // Create a tool tip for the tab (shows the file name).

      String ltoolTip = "Namespace from \"" + getFileNameFromPath(xfileName) + "\"";

      // Add the tab to this tabbed pane (icon == null).

      String tname = getFileNameFromPath(lname);
      //String tname = lname;

      addTab(tname, null, posetPane, ltoolTip);

      // Get the index of the tab.

      int index = indexOfTab(tname);

      // Set the tab component.

      setTabComponentAt(index, new SheafScopeTabPane(this, tname));

      // Set unselected tab colors.

      Color tabColor = createColor();
      setBackgroundAt(index, tabColor);

      // Select the new tab.

      setSelectedIndex(index);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
    * Creates a new tab for <i>node</i>.<p>
    * 
    * @param xnode  The <code>SheafScopeTreeNode</code> with which to create the tab.
    *
    * 
    */
  public void createTab(SheafScopeTreeNode xnode)
  {
    try
    {
      selectedNode = xnode;

      //$$ISSUE: Is this the right place for this???
      mainPane.clearErrorStatus();

      // Get the poset member attached to the selected node.

      abstract_poset_member member = selectedNode.getMember();

      // Get it's host.

      poset_state_handle host = member.host();

      // determine the type

      boolean hostIsNamespace = host instanceof namespace_poset;

      boolean memberIsJim = member.is_jim(false);
      boolean nodeIsDisplayed = selectedNode.isDisplayed();

      // If the poset member is part of a namespace and is a jim and isn't
      // currently displayed, display it.

      if(hostIsNamespace  && memberIsJim && !nodeIsDisplayed)
        createMemberTab(member);

      // If the node is a jrm, do nothing

      else if(hostIsNamespace && !memberIsJim && !nodeIsDisplayed)
        return;
      else if(nodeIsDisplayed)
      {
        SheafScopePosetPane parentPane =
          (SheafScopePosetPane)getSelectedComponent();
        String name = createName(parentPane.getName(), member.name());
        setSelectedIndex(indexOfTab(name));
      }

      // User selected, but we don't have part of a namespace here, so complain.

      else
        mainPane.showErrorStatus(
          "  WARN: Selected node is not part of a namespace ", true);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Creates a tab for the current <code>poset_member</code><p>
   *
   * @param xposetMember The current poset_member.
   *
   * 
   */
  protected void createMemberTab(abstract_poset_member xposetMember)
  {
    try
    {
      // Get the currently selected tab (poset) pane.
      // (Presently, this can only be a parent (namespace) pane);

      SheafScopePosetPane parentPane = (SheafScopePosetPane)getSelectedComponent();

      String parentName = parentPane.getName();

      String memberName = xposetMember.name();

      // Create a new tab with an appropriate label.

      String name = createName(parentName, memberName);

      // Create a new poset pane to display this member in.

      SheafScopePosetPane posetPane
      = new SheafScopePosetPane(mainPane, name, xposetMember, parentPane);

      // Add child (this) pane to parent.

      parentPane.addChild(posetPane);

      String toolTip = "Child of \"" + getFileNameFromPath(parentName) + "\"";
      addTab(name, null, posetPane, toolTip);

      // Get the index of the new tab.

      int index = indexOfComponent(posetPane);

      // Set the tab component.

      setTabComponentAt(index, new SheafScopeTabPane(this, name));

      // Set tab color.

      Color tabColor = createColor();
      setBackgroundAt(index, tabColor);

      // Select the new tab.

      setSelectedIndex(index);

      // Mark the member as displayed.

      selectedNode.setIsDisplayed(true);

      // Tell the new poset pane about it's parent node.

      posetPane.setParentNode(selectedNode);

      // Tag the nodes in the namespace tree and parent's focus tree
      // to show this member as displayed.

      parentPane.getFocusPane().tagPaths(memberName, tabColor);
      posetPane.getNamespacePane().tagPaths(memberName, tabColor);
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Method to create a color based on hue, saturation, and brightness.
   * Saturation and brightness are held fixed while hue ranges from
   * 0-360 degrees in increments of "delta" degrees.<p>
   *
   * @return a new <code>Color</code>
   */
  protected static Color createColor()
  {
    hue = hue % 360.0f;
    float h = hue/360.0f;
    float s = saturation/100.0f;
    float b = brightness/100.0f;
    Color color = Color.getHSBColor(h, s, b);
    hue += delta;

    return color;
  }

  /**
   * Create a name for a "parent" pane.
   * All names are kept in a list so that duplicate
   * names can be avoided.  If a name already exists,
   * a new one is created by appending the String
   * "<#>" where # represents an integer which
   * increments starting from 2.<p>
   *
   * @param xname The name of the parent.
   *
   * @return a <code>String</code> containing the new
   *         name for the parent or the original if
   *         there were no duplicates
   */
  String createParentName(final String xname)
  {
    if(parentNames.contains(xname))
    {
      int i = 2;
      while(true)
      {
        String testName = xname + "<" + i + ">";
        if(!parentNames.contains(testName))
        {
          return testName;
        }
        i++;
      }
    }

    return xname;
  }

  /**
   * Create a name for a child tab label by adding a delimiter between
   * the name of the parent and the name of the child.<p>
   *
   * @param xparentName The name of the parent.
   * @param xchildName The name of the child.
   *
   * @return a <code>String</code> containing the name
   */
  String createName(final String xparentName, final String xchildName)
  {
    String name  = getFileNameFromPath(xparentName) + NAME_DELIMITER + xchildName;
    return name;
  }

  /**
   * Strips the parent name prefix from a name.
   * Currently assumes child names are of the form:
   *     "parentname: childname"<p>
   *
   * @return The name with it's parent stripped.
   */
  String stripParentFromName(final String xname)
  {
    int delimitIndex = xname.lastIndexOf(NAME_DELIMITER);
    if(delimitIndex == -1)
      return xname;

    String childName = xname.substring(delimitIndex+2);
    return childName;
  }

  /**
   * Gets just the file name from a path name.<p>
   *
   * @param xpath A <code>String</code> representing the full path to a file.
   *
   * @return The file name associated with <i>path</i>.
   */
  public String getFileNameFromPath(final String xpath)
  {
    int sepIndex = xpath.lastIndexOf('/');
    String fileName = xpath;
    if(sepIndex >= 0)
      fileName = fileName.substring(sepIndex+1);
    return fileName;
  }

  /**
   * Deletes the currently selected tab.<p>
   *
   * 
   */
  public void deleteTab()
  {
    deleteTab(getSelectedIndex());
  }

  /**
   * Delete tab at xindex.
   */
  public void deleteTab(int xindex)
  {
    // Get the currently selected tab (poset) pane.

    SheafScopePosetPane posetPane = (SheafScopePosetPane)getComponentAt(xindex);

    // Get currently selected tab (poset) pane's  parent.

    SheafScopePosetPane parentPane = posetPane.getParentPosetPane();

    if(parentPane != null)
    {
      deleteChildTab(posetPane);
    }
    else
    {
      deleteParentTab(posetPane);
    }
  }

  /**
   * Deletes the currently selected tab's child.<p>
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> associated
   * with this display panel.
   *
   * 
   */
  protected void deleteChildTab(SheafScopePosetPane xposetPane)
  {
    try
    {
      // Get parent pane

      SheafScopePosetPane parentPane = xposetPane.getParentPosetPane();

      // Untag this name in parent focus pane.

      SheafScopeFocusPane focusPane = parentPane.getFocusPane();
      String name = stripParentFromName(xposetPane.getName());
      focusPane.untagPaths(name);

      // Select the parent tab.

      setSelectedComponent(parentPane);

      // Remove child from parent.

      parentPane.removeChild(xposetPane);

      // Remove the pane.

      remove(xposetPane);

      // Reset the actor tool bar.

      mainPane.resetActorToolBar();
    }
    catch(Exception e)
    {
      System.out.println("deleteTab failed: " + e);
    }
  }

  /**
   * Deletes the currently selected tab, killing it's
   * children in the process.<p>
   *
   * @param xparentPane The <code>SheafScopePosetPane</code> associated
   * with this display panel.
   *
   * 
   */
  public void deleteParentTab(SheafScopePosetPane xparentPane)
  {
    // Throw up a confirmation dialog if we want to delete a parent
    // having children.

    SheafScopePosetPane[] kids = xparentPane.getChildren();
    if(kids.length > 0)
    {
      String parentName= xparentPane.getName();
      String title = "Really Delete Parent Tab?";
      String[] message = {"Tab \"" + parentName + "\" has children.",
                          "Deleting it will also delete its children",
                          "(tabs starting with \"" + parentName + "\").",
                          " ",
                          "Do you really want to do this?"};

      int result
      = JOptionPane.showConfirmDialog(this, message, title,
                                      JOptionPane.YES_NO_OPTION,
                                      JOptionPane.QUESTION_MESSAGE);

      // Don't do anything if "Yes" is not selected.

      if(result != JOptionPane.YES_OPTION)
        return;

      // Throw away the kids.

      for(int i=0; i<kids.length; i++)
      {
        remove(kids[i]);
        kids[i].getDisplayPanel().getSelectedNode().setIsDisplayed(false);
      }

      // Remove the parent tab name from the list.

      parentNames.remove(parentNames.indexOf(parentName));

    }

    // Remove the parent.

    remove(xparentPane);

    // Reset the actor tool bar.

    mainPane.resetActorToolBar();

    // Since we don't have a parent to select,
    // select the first tab (if it exists);

    if(getTabCount() > 0)
      setSelectedIndex(0);
  }

  /**
   * Deletes all tabs associated with this display panel.<p>
   *
   * 
   */
  public void deleteAllTabs()
  {
    // Throw up a dialog so users can change their minds.

    String title = "Really Delete All Tabs?";
    String[] message = {"This will delete all tabs.",
                        " ",
                        "Do you really want to do this?"};

    int result
    = JOptionPane.showConfirmDialog(this, message, title,
                                    JOptionPane.YES_NO_OPTION,
                                    JOptionPane.QUESTION_MESSAGE);

    if(result != JOptionPane.YES_OPTION)
      return;

    // Delete all of the tabs.

    removeAll();

    // Reset the actor tool bar.

    mainPane.resetActorToolBar();
  }

  /**
   * Removes the tab and component which corresponds to the specified index.<p>
   * Detach the members of the <code>SheafScopePosetPane</code>.
   */
  public void remove(int index)
  {
    detachStates(getComponentAt(index));

    super.remove(index);
  }

  /**
   * Removes the tab at index. After the component associated with index
   * is removed, its visibility is reset to true to ensure it will be
   * visible if added to other containers.<p>
   * Detach the members of the <code>SheafScopePosetPane</code>.
   */
  public void removeTabAt(int index)
  {
    detachStates(getComponentAt(index));

    super.removeTabAt(index);
  }

  /**
   * Removes the specified Component from the JTabbedPane.
   * The method does nothing if the component is null.<p>
   * Detach the members of the <code>SheafScopePosetPane</code>.
   */
  public void remove(Component component)
  {
    detachStates(component);

    super.remove(component);
  }

  /**
   * Removes all the tabs and their corresponding components from the
   * tabbedpane.<p>
   * Detach the members of the <code>SheafScopePosetPane</code>s.
   */
  public void removeAll()
  {
    for(int i=0; i<getTabCount(); i++)
    {
      detachStates(getComponentAt(i));
    }

    super.removeAll();
  }

  /**
   * Detach the members of component.  Does nothing if component is
   * not a <code>SheafScopePosetPane</code>.
   */
  protected void detachStates(Component component)
  {
    if((component != null) && (component instanceof SheafScopePosetPane))
    {
      SheafScopePosetPane pane = (SheafScopePosetPane) component;
      pane.detachStates();
    }
  }

  /**
   * The <code>namespace_poset</code> with name, xname.
   */
  public namespace_poset getNamespace(String xname)
  {
    return namespaces.get(xname);
  }

  /**
   * Returns the currently selected node in the tree associated with this display panel.<p>
   *
   * @return the currently selected node in the tree associated with this display panel.
   */
  public SheafScopeTreeNode getSelectedNode()
  {
    return selectedNode;
  }

  /**
   * Returns the <code>SheafScopePosetPane</code> associated with a specified PosetMember.<p>
   *
   * @return the <code>SheafScopePosetPane</code> associated with the specified PosetMember.
   */
  public SheafScopePosetPane getPosetPaneForPosetMember(abstract_poset_member posetMember)
  {
    SheafScopePosetPane result = null;

    if(posetMember == null)
      return result;

    for(int i=0; i<getTabCount(); i++)
    {
      SheafScopePosetPane posetPane = (SheafScopePosetPane)(getComponentAt(i));
      abstract_poset_member paneMember = posetPane.getMember();

      try
      {
        if(posetMember.host() == paneMember.host())
        {
          result = posetPane;
          break;
        }
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();
      }
    }

    return result;
  }
}
