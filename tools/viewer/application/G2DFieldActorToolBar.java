/**
 *  Classname: G2DFieldActorToolBar
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:56 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.render.*;
import tools.viewer.user.*;

import java.util.*;
import javax.swing.*;

/**
 * Implementation of <code>FieldActorToolBar</code> for 2D representations.
 */
public class G2DFieldActorToolBar extends FieldActorToolBar
{
  /**
   * The roles
   */
  private static Class[] ROLES = {XAxisRolePanel.class,
                                  YAxisRolePanel.class};

  /**
   * The constructor
   */
  public G2DFieldActorToolBar(FieldActorToolBarApplication xapplication)
  {
    super(xapplication, ROLES);
  }

  /**
   * True, if the representation can be visualized.
   */
  protected boolean canView()
  {
    return ((roles[0].getSection() != null) &&
            (roles[1].getSection() != null));
  }

  /**
   * Override <code>FieldActorToolBar.checkBase()</code>.
   * Any base space is compatible.
   */
  protected boolean checkBase(RolePanel xrole, sec_vd xsection)
  {
    return true;
  }

  /**
   * View this representation.
   */
  public void view()
  {
    // Get the Sheaf values from the fields.

    G2DFieldActorDescriptor actor = new G2DFieldActorDescriptor();
    SectionDescriptor section;

    try
    {
      // Set the namespace.

      actor.namespace = roles[0].getSection().name_space().name();

      // Set the coordinates

      section = getSectionDescriptor(roles[0].getSection());
      if(section == null)
        return;
      actor.coordinates = section;

      // Set the properties

      section = getSectionDescriptor(roles[1].getSection());
      if(section == null)
        return;
      actor.property = section;

      // Set the titles

      String coordName = roles[0].getSection().name();
      String propName = roles[1].getSection().name();

      actor.title = coordName + " vs. " + propName;
      actor.xtitle = coordName;
      actor.ytitle = propName;
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling

      e.printStackTrace();

      return;
    }

    // Open the viewer

    application.openG2DViewer(actor);
  }

  /**
   * Overwriting of toString().
   */
  public String toString()
  {
    return "X-Y Plot";
  }
}
