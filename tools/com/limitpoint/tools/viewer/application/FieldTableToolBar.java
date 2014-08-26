
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

package com.limitpoint.tools.viewer.application;

import com.limitpoint.bindings.java.*;
import com.limitpoint.tools.viewer.table.*;
import com.limitpoint.tools.viewer.render.*;

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
