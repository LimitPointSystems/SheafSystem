
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

import java.lang.reflect.Method;

/**
 * A panel for displaying a Poset or SecRepSpace.  In general,
 * it is composed of four quadrants separated both vertically and
 * horizontally by Swing split panes. 
 * <p>
 * Each quadrant contains a scrolling pane containing either
 * a tree or a table. Starting at the lower left quadrant and
 * proceeding clockwise the panes contain the "focus" tree
 * representing the row graph, the namespace tree representing the
 * row graph of the initial namespace for the focus (initially null),
 * the "schema" tree representing the column graph and finally a
 * table whose rows represent the nodes in the focus tree.
 * <p>
 * For case of a SecRepSpace, the "schema" pane is further
 * subdivided into two panes oriented  horizontally and containing
 * a "base" and a "fiber schema" tree.  
 */
public class SheafScopePosetPane extends JPanel
{
  //$$TODO: Need to fix this so we can use proportional locations!
  /**
   * A bug in the JSplitPane class prevents the setDividerLocation(double)
   * method from working until the displaying frame has been validated.
   * We force the size here to one aesthically pleasing for this frame.
   * See BUG ID: 4182558 on JDC
   */

  static final int HORIZ_DIV_LOCATION = 300;
  static final int VERT_DIV_LOCATION = 396;
  static final int DIVIDER_SIZE = 8;

  private SheafScopeMainPane mainPane;
  private String name;
  private abstract_poset_member member;
  private namespace_poset namespace = null;
  private SheafScopePosetPane parentPane;

  private SheafScopeTreeNode parentNode;

  private ArrayList<SheafScopePosetPane> children;
  //private ArrayList children;

  private boolean showBottoms = false;

  private SheafScopeFocusPane         focusPane = null;
  private SheafScopeNamespacePane     namespacePane = null;
  private SheafScopeSchemaPane        schemaPane = null;
  private SheafScopeFiberSchemaPane   fiberSchemaPane = null;
  private SheafScopeBasePane          basePane = null;
  private SheafScopeSchemaAndBasePane schemaAndBasePane = null;
  private SheafScopeAbstractTablePane tablePane = null;
  private SheafScopeTableDofTablePane tableDofPane = null;

  /**
   * Returns a <code>SheafScopePosetPane</code>.
   *
   * @param xmainPane   the instance of <code>SheafScopeMainPane</code> containing
   *                   this pane.
   * @param xname       a <code>String</code> containg the name which will be used to
   *                   identify this pane.
   * @param xmember     the <code>poset_member</code> to be displayed in this pane.
   * @param xparentPane the <code>SheafScopePosetPane</code> representing the parent
   *                   of this pane (it is null in the case of the initial namespace). 
   */
  public SheafScopePosetPane(SheafScopeMainPane xmainPane,
                             String xname,
                             abstract_poset_member xmember,
                             SheafScopePosetPane xparentPane)
  {
    //     System.err.println("####SheafScopePosetPane CTOR");
    //     System.err.println("####  xname = " + xname);
    //     System.err.println("####  xmember = " + xmember);
    //     System.err.println("####  xmember.name() = " + xmember.name());
    //     System.err.println("####  xmember.host() = " + xmember.host());
    //     System.err.println("####  xmember.host().name_space() = " + xmember.host().name_space());
    //     System.err.println("####  xmember.name_space() = " + xmember.name_space());
    //     System.err.println("####  xparentPane = " + xparentPane);

    this.mainPane = xmainPane;
    this.name = xname;
    this.parentPane = xparentPane;
    this.namespace = (namespace_poset)xmember.host(); //$$ISSUE: Is this OK?
    this.member = (parentPane == null) ? xmember : getTop(xmember);

    member.get_read_access();

    makePane();
  }

  /**
   * Detach the members of this pane.
   */
  public void detachStates()
  {
    if(focusPane != null)
      focusPane.detachStates();

    if(namespacePane != null)
      namespacePane.detachStates();

    if(schemaPane != null)
      schemaPane.detachStates();

    if(fiberSchemaPane != null)
      fiberSchemaPane.detachStates();

    if(basePane != null)
      basePane.detachStates();

    if(tablePane != null) 
      tablePane.detachStates();
  }

  /**
   * Convenience method to get the "top" member of the namespace.
   *
   * @param xMember a specified <code>abstract_poset_member</code> object.
   *
   * @return an <code>abstract_poset_member</code> representing the "top". 
   */
  private abstract_poset_member getTop(abstract_poset_member xMember)
  {
    try
    {
      scoped_index index = xMember.index();

      //       System.err.println("SheafScopePosetPane.getTop");
      //       System.err.println("  xMember = " + xMember);
      //       System.err.println("  xMember.name_space() = " + xMember.name_space());
      //       System.err.println("  xMember.index() = " + xMember.index());
      //       System.err.println("  xMember.index().pod() = " + xMember.index().pod());
      //       System.err.println("  xMember.host() = " + xMember.host());
      //       System.err.println("  xMember.host().name() = " + xMember.host().name());
      //       System.err.println("  namespace = " + namespace);

      //namespace_poset namespacePoset = (namespace_poset) xMember.host();
      //poset_state_handle psh = namespacePoset.member_poset(index, true);

      poset_state_handle psh = namespace.member_poset(index, true);
      poset_state_handle real_psh = dynamic_cast(psh);

      real_psh.get_read_access();

      abstract_poset_member result = real_psh.top();

      real_psh.release_access();

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return null;
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
    setLayout(new BorderLayout());

    if(SheafScopeConstants.DEBUG == true)
    {
      setBackground(Color.yellow);
      setBorder(BorderFactory.createMatteBorder(5,5,5,5,Color.blue));
    }

    focusPane       = createFocusPane();
    namespacePane   = createNamespacePane();
    tablePane       = createTablePane();
    tableDofPane    = createTableDofPane();

    if(member instanceof sec_rep_space_member)
    {
      fiberSchemaPane = createFiberSchemaPane();
      basePane = createBasePane();

      schemaAndBasePane
      = new SheafScopeSchemaAndBasePane(mainPane,
                                        fiberSchemaPane,
                                        basePane);

      // Force a selection of row zero in the table
      // so that the per member restriction mechanism
      // works properly.

      //$$TODO: Fix!
      //SheafScopeJTable table = tablePane.getTable();
      //table.setRowSelectionInterval(0, 0);
      ////tablePane.getTable().setRowSelectionInterval(0, 0);

    }
    else if(member instanceof schema_poset_member)
    {
      schemaPane = createSchemaPane();
    }
    else if(member instanceof abstract_poset_member)
    {
      schemaPane = createSchemaPane();
    }
    else
    {
      System.out.println("SheafScopeFocusPane.makePane: ERROR...");
      System.out.println("  Can't create pane for member " + member);
    }

    add
      (createMainSplitPane(), BorderLayout.CENTER);
  }

  /**
   * Creates the main top/bottom <code>JSplitPane<code>.
   *
   * @return The newly created <code>JSplitPane</code>
   */
  protected JSplitPane createMainSplitPane()
  {
    JSplitPane top;

    if(member instanceof sec_rep_space_member)
    {
      top = createSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                            namespacePane, schemaAndBasePane);
    }
    else
    {
      top  = createSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                             namespacePane, schemaPane);
    }

    SheafScopeTableDofTableModel tableDofModel = tableDofPane.getTableModel();

    JSplitPane bottom = createSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                                        focusPane, tablePane);

    JSplitPane main = createSplitPane(JSplitPane.VERTICAL_SPLIT,
                                      top, bottom);

    return main;
  }

  /**
   *  Creates a generic <code>JSplitPane</code>.
   *
   * @param xorientation    integer representing the orientation of the
   *                       <code>JSplitPane</code>
   * @param xleftComponent  <code>Component</code> to insert on the left
   *                       (or top)
   * @param xrightComponent <code>Component</code> to insert on the right
   *                       (or bottom)
   *
   * @return The newly created <code>JSplitPane</code>
   */
  protected JSplitPane createSplitPane(int xorientation,
                                       Component xleftComponent,
                                       Component xrightComponent)
  {
    JSplitPane splitPane
    = new JSplitPane(xorientation, xleftComponent, xrightComponent);

    splitPane.setOneTouchExpandable(true);
    splitPane.setDividerSize(DIVIDER_SIZE);

    int dividerLocation = (xorientation == JSplitPane.HORIZONTAL_SPLIT)
                          ? VERT_DIV_LOCATION
                          : HORIZ_DIV_LOCATION;
    splitPane.setDividerLocation(dividerLocation);

    return splitPane;
  }

  /**
   * Creates the focus pane.
   *
   * @return  The newly created <code>SheafScopeFocusPane</code>.
   */
  protected SheafScopeFocusPane createFocusPane()
  {
    // Set tree truncation mode.
    // Default for namespace poset is do not truncate,
    // default for all others is truncate.
    // Only namespace has a null namespace

    boolean truncateTree = true;
    try
    {
      //namespace_poset nsp = member.name_space();
      //truncateTree = nsp != null;
      truncateTree = namespace != null;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }


    SheafScopeFocusPane result = new SheafScopeFocusPane(this, member);

    return result;
  }

  /**
   * Creates the schema pane (Poset case).
   *
   * @return  The newly created <code>SheafScopeSchemaPane</code>.
   */
  protected SheafScopeSchemaPane createSchemaPane()
  {
    try
    {
      abstract_poset_member schema = member.schema();
      SheafScopeSchemaPane result = new SheafScopeSchemaPane(this, schema);

      return result;
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return null;
    }
  }

  /**
   * Creates the fiber schema pane (SecRepSpace case).
   *
   * @return  The newly created <code>SheafScopeFiberSchemaPane</code>.
   */
  protected SheafScopeFiberSchemaPane createFiberSchemaPane()
  {
    try
    {
      schema_poset_member fiberSchema =
	  ((sec_rep_space_member)member).fiber_schema();

      // SheafScopeFiberSchemaPane constructs its own schema member.
      // This will stop restriction from changing the fiber_schema() of member,
      // which in turn changes the member of the root SheafScopeTreeNode

      return (new SheafScopeFiberSchemaPane(this, fiberSchema.host(),
					    fiberSchema.index()));
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return null;
    }
  }

  /**
   * Creates the base pane (SecRepSpace case).
   *
   * @return  The newly created <code>SheafScopeBasePane</code>.
   */
  protected SheafScopeBasePane createBasePane()
  {
    try
    {
      abstract_poset_member base = ((sec_rep_space_member)member).base();

      // SheafScopeBasePane constructs its own schema member.
      // This will stop restriction from changing the base() of member,
      // which in turn changes the member of the root SheafScopeTreeNode

      return (new SheafScopeBasePane(this, base.host(), base.index()));
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      return null;
    }
  }

  /**
   * Creates the namespace pane.
   *
   * @return  The newly created <code>SheafScopeNamespacePane</code>.
   */
  protected SheafScopeNamespacePane createNamespacePane()
  {
    SheafScopeNamespacePane namespacePane = null;

    try
    {
      namespace_poset nsp = member.name_space();

      if(nsp != null)
      {
        namespacePane = new SheafScopeNamespacePane(this, member);
      }
      else
      {
        namespacePane = new SheafScopeNamespacePane(this);
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    return namespacePane;
  }

  /**
   * Creates the table.
   *
   * @return  The newly created <code>SheafScopeAbstractTablePane</code>.
   */
  protected SheafScopeAbstractTablePane createTablePane()
  {
    SheafScopeAbstractTablePane result = null;

    //@issue Class state_tuple has been removed from the library
    //       for testing and, thus, is commented out below.

    if(member instanceof sec_rep_space_member)
    {
      result = new SheafScopeSecRepSpaceTablePane(this, member);
    }
//     else if(member instanceof state_tuple)
//     {
//       result = new SheafScopeStateTupleTablePane(this, member);
//     }
    else if(member instanceof namespace_poset_member)
    {
      result = new SheafScopeNamespacePosetTablePane(this, member);
    }
    else
    {
      result = new SheafScopePosetTablePane(this, member);
    }

    return result;
  }

  /**
   * Creates the table dof table.
   *
   * @return  The newly created <code>SheafScopeTableDofTablePane</code>.
   */
  protected SheafScopeTableDofTablePane createTableDofPane()
  {
    SheafScopeTableDofTablePane result =
      new SheafScopeTableDofTablePane(this, member);

    return result;
  }

  /**
   * Public accessor for the private <i>mainPane</i> data member.
   *
   * @return The newly created <code>SheafScopeMainPane</code>.
   */
  public SheafScopeMainPane getMainPane()
  {
    return mainPane;
  }

  /**
   * Returns the <code>SheafScopeDisplayPanel/code> (a specialized
   * <code>JTabbedPane</code>) containing this pane
   * in one of its tabs.
   *
   * @return The <code>SheafScopeDisplayPanel</code> associated with this instance
   *         of <code>SheafScopePosetPane</code>..
   */
  public SheafScopeDisplayPanel getDisplayPanel()
  {
    return mainPane.getDisplayPanel();
  }

  /**
   *  Public accessor for the private <i>focusPane</i> data member.
   *
   * @return The <code>SheafScopeFocusPane</code> associated with this instance
   *         of <code>SheafScopePosetPane</code>.
   */
  public SheafScopeFocusPane getFocusPane()
  {
    return focusPane;
  }

  /**
   * Public accessor for the private <i>namespacePane</i> data member.
   *
   * @return The <code>SheafScopeNamespacePane</code> associated with this instance
   *         of <code>SheafScopePosetPane</code>.
   */
  public SheafScopeNamespacePane getNamespacePane()
  {
    return namespacePane;
  }

  /**
   * Public accessor for the private <i>schemaPane</i> data member.
   *
   * @return The <code>SheafScopeSchemaPane</code>(or null for the SecRepSpace
   *         case) associated with this instance of
   *         <code>SheafScopePosetPane</code>.
   */
  public SheafScopeSchemaPane getSchemaPane()
  {
    return schemaPane;
  }

  /**
   * Public accessor for the private <i>fiberSchemaPane</i> data member.
   *
   * @return The <code>SheafScopeFiberSchemaPane</code>(or null for the Poset
   *         case) associated with this instance of
   *         <code>SheafScopePosetPane</code>.
   */
  public SheafScopeFiberSchemaPane getFiberSchemaPane()
  {
    return fiberSchemaPane;
  }

  /**
   * Public accessor for the private <i>basePane</i> data member.
   *
   * @return The <code>SheafScopeBasePane</code>(or null for the Poset
   *         case) associated with this instance of
   *         <code>SheafScopePosetPane</code>.
   */
  public SheafScopeBasePane getBasePane()
  {
    return basePane;
  }

  /**
   * Public accessor for the private <i>tablePane</i> data member.
   *
   * @return The <code>SheafScopeAbstractTablePane</code> associated with this
   *         instance of <code>SheafScopePosetPane</code>.
   */
  public SheafScopeAbstractTablePane getTablePane()
  {
    return tablePane;
  }

  /**
   * Returns the <code>SheafScopeJTable/code>
   * contained in the table pane.
   *
   * @return The <code>SheafScopeJTable</code> associated with this instance
   *         of <code>SheafScopePosetPane</code>.
   */
  public SheafScopeJTable getTable()
  {
    return tablePane.getTable();
  }

  /**
   * Returns the <code>SheafScopeAbstractTableModel/code>
   * for the table contained in the table pane.
   *
   * @return The <code>SheafScopeAbtractTableModel</code>
   * associated with this pane's table.
   */
  public SheafScopeAbstractTableModel getTableModel()
  {
    return tablePane.getTableModel();
  }

  /**
   * Specifies the parent <code>SheafScopeTreeNode</code>
   * for this pane.
   *
   * @param xnode the parent node for this pane.
   *
   * 
   */
  public void setParentNode(SheafScopeTreeNode xnode)
  {
    parentNode = xnode;
  }

  /**
   * Public accessor for the private <i>parentNode</i> data member.
   *
   * @return The parent node.
   */
  public SheafScopeTreeNode getParentNode()
  {
    return parentNode;
  }

  /**
   * Specifies the parent <code>SheafScopePosetPane</code>
   * for this pane.
   *
   * @param parent The parent pane.
   */
  private void setParentPosetPane(SheafScopePosetPane xparent)
  {
    parentPane = xparent;
  }

  /**
   * Public accessor for the private <i>parentPane</i> data member.
   *
   * @return The parent pane.
   */
  public SheafScopePosetPane getParentPosetPane()
  {
    return parentPane;
  }

  /**
   * Public accessor for the private <i>member</i> data member.
   *
   * @return The <code>abstract_poset_member</code> for this pane.
   */
  public abstract_poset_member getMember()
  {
    return member;
  }

  /**
   * Specifies the name for this pane.
   *
   * @param xname a <code>String</code> representing the name.
   *
   * 
   */
  public void setName(String xname)
  {
    this.name = xname;
  }

  /**
   * Public accessor for the private <i>name</i> data member.
   *
   * @return a <code>String</code> representing this pane's name.
   */
  public String getName()
  {
    return name;
  }

  /**
   * Adds a child <code>SheafScopePosetPane</code> to this parent
   *
   * @param xchild The child pane to add.
   *
   * 
   */
  public void addChild(SheafScopePosetPane xchild)
  {
    if(children == null)
      children = new ArrayList<SheafScopePosetPane>();
    //children = new ArrayList();

    children.add(xchild);
  }

  /**
   * Removes a child <code>SheafScopePosetPane</code> from this parent
   *
   * @param xchild The child pane to remove.
   *
   * 
   */
  public void removeChild(SheafScopePosetPane xchild)
  {
    if(children == null)
      return;
    children.remove(xchild);
  }

  /**
   * Returns an array of type <code>SheafScopePosetPane[]</code>
   * containing all of the children of this parent.
   *
   * @return An array of child objects.
   */
  public SheafScopePosetPane[] getChildren()
  {
    if(children == null)
      children = new ArrayList<SheafScopePosetPane>();

    SheafScopePosetPane[] kids
    = (SheafScopePosetPane[])children.toArray(new SheafScopePosetPane[0]);

    return kids;
  }

  /**
   * Update the member after a focus tree selection.<p>
   *
   * 
   */
  void updateMember()
  {
    // Get the selected node -- make sure it's not null.

    SheafScopeTreeNode node
    = (SheafScopeTreeNode)(getFocusPane().getTree().getLastSelectedPathComponent());

    //LPSDebug.println("node = " + node);

    if(node != null)
    {
      getFocusPane().setOpenPosetEnabled();

      // We're going to wait, set cursor back to an hourglass and block user input.

      getMainPane().getParentFrame().setWaitState(true);

      // Update the table.

      getTablePane().updateTable();

      // We're done waiting, set cursor back to normal.

      getMainPane().getParentFrame().setWaitState(false);

      // Force a selection on row zero of the table.

      getTablePane().getTable().setRowSelectionInterval(0, 0);
    }
  }


  /**
   * Function to cast an instance of type poset_state_handle
   * to the proper type.
   *
   * @return The properly cast instance.
   */
  public static poset_state_handle dynamic_cast(poset_state_handle xpsh)
  {
    poset_state_handle result = null;

    //$$SCRIBBLE: Note that this only works with classes which have
    //            a "klass_name" ("class_name" in the c++ code)
    //            member function.

    String class_name = xpsh.klass_name();

    //System.err.println("### class_name = " + class_name);

    if("namespace_poset".equals(class_name))
    {
      result = namespace_poset.dynamic_cast(xpsh);
    }
    else if("primitives_poset".equals(class_name))
    {
      result = primitives_poset.dynamic_cast(xpsh);
    }
    else if("primitives_poset_schema".equals(class_name))
    {
      result = primitives_poset_schema.dynamic_cast(xpsh);
    }
    else if("namespace_poset_schema".equals(class_name))
    {
      result = namespace_poset_schema.dynamic_cast(xpsh);
    }
    else if("poset".equals(class_name))
    {
      result = poset.dynamic_cast(xpsh);
    }
    else if("at0_space".equals(class_name))
    {
      result = at0_space.dynamic_cast(xpsh);
    }
    else if("at1_space".equals(class_name))
    {
      result = at1_space.dynamic_cast(xpsh);
    }
    else if("atp_space".equals(class_name))
    {
      result = atp_space.dynamic_cast(xpsh);
    }
    else if("gln_space".equals(class_name))
    {
      result = gln_space.dynamic_cast(xpsh);
    }
    else if("jcb_space".equals(class_name))
    {
      result = jcb_space.dynamic_cast(xpsh);
    }
    else if("stp_space".equals(class_name))
    {
      result = stp_space.dynamic_cast(xpsh);
    }
    else if("tp_space".equals(class_name))
    {
      result = tp_space.dynamic_cast(xpsh);
    }
    else if("tuple_space".equals(class_name))
    {
      result = tuple_space.dynamic_cast(xpsh);
    }
    else if("vd_space".equals(class_name))
    {
      result = vd_space.dynamic_cast(xpsh);
    }
    else if("base_space_poset".equals(class_name))
    {
      result = base_space_poset.dynamic_cast(xpsh);
    }
    else if("sec_rep_space".equals(class_name))
    {
      result = sec_rep_space.dynamic_cast(xpsh);
    }
    else if("sec_at0_space".equals(class_name))
    {
      result = sec_at0_space.dynamic_cast(xpsh);
    }
    else if("sec_at1_space".equals(class_name))
    {
      result = sec_at1_space.dynamic_cast(xpsh);
    }
    else if("sec_atp_space".equals(class_name))
    {
      result = sec_atp_space.dynamic_cast(xpsh);
    }
    else if("sec_jcb_space".equals(class_name))
    {
      result = sec_jcb_space.dynamic_cast(xpsh);
    }
    else if("sec_stp_space".equals(class_name))
    {
      result = sec_stp_space.dynamic_cast(xpsh);
    }
    else if("sec_tp_space".equals(class_name))
    {
      result = sec_tp_space.dynamic_cast(xpsh);
    }
    else if("sec_tuple_space".equals(class_name))
    {
      result = sec_tuple_space.dynamic_cast(xpsh);
    }
    else if("sec_vd_space".equals(class_name))
    {
      result = sec_vd_space.dynamic_cast(xpsh);
    }
    else if("binary_section_space_schema_poset".equals(class_name))
    {
      result = binary_section_space_schema_poset.dynamic_cast(xpsh);
    }
    else
    {
      // Probably should throw exception.
      System.err.println("### ERROR: Type " + class_name + " not found.");
      result = null;
    }

    //================================================================================

    //$$SCRIBBLE: We could also do the above with the following (more general too):

    //     try
    //     {
    //       Class cls = Class.forName("bindings.java." + class_name);
    //       Class argtype[] = new Class[] {bindings.java.poset_state_handle.class};
    //       Method method = cls.getMethod("dynamic_cast", argtype);
    //       Object arglist[] = new Object[] {xpsh};
    //       Object return_obj = method.invoke(null, arglist);
    //       result = (poset_state_handle)return_obj;
    //      }
    //      catch(Throwable e)
    //      {
    //        System.err.println("Error... " + e);
    //      }

    //================================================================================

    return result;

  }

}
