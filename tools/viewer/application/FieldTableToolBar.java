/**
 *  Classname: FieldTableToolBar
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:56 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.table.*;
import tools.viewer.render.*;

import java.util.*;
import javax.swing.*;

/**
 * Implementation of <code>FieldActorToolBar</code>
 * table representations.
 */
public class FieldTableToolBar extends FieldActorToolBar
{
  /**
   * The roles
   */
  private static Class[] ROLES = {PropertyRolePanel.class,
                                  PropertyRolePanel.class,
                                  PropertyRolePanel.class};

  /**
   * The constructor
   */
  public FieldTableToolBar(FieldActorToolBarApplication xapplication)
  {
    super(xapplication, ROLES);
  }

  /**
   * True, if the representation can be visualized.
   */
  protected boolean canView()
  {
    for(int i=0; i<roles.length; i++)
    {
      if(roles[i].getSection() != null)
        return true;
    }

    return false;
  }

  /**
   * View this representation.
   */
  public void view()
  {
    // Get the Sheaf values from the fields.

    FieldTableDescriptor table = new FieldTableDescriptor();
    SectionDescriptor section;

    try
    {
      for(int i=0; i<roles.length; i++)
      {
        if(roles[i].getSection() != null)
        {
          // Set the namespace

          if(table.namespace == null)
            table.namespace = roles[i].getSection().name_space().name();

          // Add the section

          section = getSectionDescriptor(roles[i].getSection());
          if(section == null)
            return;
          table.sections.add(section);
        }
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling

      e.printStackTrace();

      return;
    }

    // Open the table viewer

    new TableViewer(table);
  }

  /**
   * Overwriting of toString().
   */
  public String toString()
  {
    return "Table";
  }
}
