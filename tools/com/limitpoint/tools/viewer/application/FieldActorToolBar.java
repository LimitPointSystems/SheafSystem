
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
import com.limitpoint.tools.common.gui.*;
import com.limitpoint.tools.viewer.render.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 * Abstract class for filling the roles of a field actor.
 */
public abstract class FieldActorToolBar extends JToolBar
{
  /**
   * The <code>FieldActorToolBarApplication</code>
   */
  protected FieldActorToolBarApplication application;

  /**
   * The <code>RolePanel</code>'s
   */
  protected RolePanel[] roles;

  /**
   * The <code>ButtonGroup</code> for the radio buttons.
   */
  protected ButtonGroup buttonGroup;

  /**
   * The map between button models and role panels.
   */
  protected Hashtable<ButtonModel, RolePanel> roleMap;

  /**
   * The view action
   */
  protected Action viewAction;

  /**
   * The reset action
   */
  protected Action resetAction;

  /**
   * The cancel action
   */
  protected Action cancelAction;

  /**
   * The constructor
   */
  protected FieldActorToolBar(FieldActorToolBarApplication xapplication,
                              Class[] xroles)
  {
    application = xapplication;

    // Instantiate the roles

    setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));

    int sz = xroles.length;
    roles = new RolePanel[sz];
    buttonGroup = new ButtonGroup();
    roleMap = new Hashtable<ButtonModel, RolePanel>();
    JRadioButton radioButton;
    add(Box.createGlue());
    for(int i=0; i<sz; i++)
    {
      try
      {
        roles[i] = (RolePanel) xroles[i].newInstance();
        radioButton = roles[i].getRoleRadioButton();
        buttonGroup.add(radioButton);
        roleMap.put(radioButton.getModel(), roles[i]);

        add(roles[i]);
      }
      catch(Exception e)
      {
        // $$HACK: Need better error handling.

        e.printStackTrace();
      }
    }

    roles[0].getRoleRadioButton().setSelected(true);

    // Create and add the buttons

    viewAction = new GenericAction(this,
                                   "view",
                                   "View",
                                   "View",
                                   null,
                                   "View the Representation");
    viewAction.setEnabled(false);

    JPanel buttons = new JPanel();
    buttons.setLayout(new GridLayout(1, 2));
    JButton button = new JButton(viewAction);
    buttons.add(button);

    JPanel buttons2 = new JPanel();
    buttons2.setLayout(new GridLayout(2, 1));
    resetAction = new GenericAction(this,
                                    "reset",
                                    "Reset",
                                    "Reset",
                                    null,
                                    "Reset the Representation");
    resetAction.setEnabled(false);
    button = new JButton(resetAction);
    buttons2.add(button);
    cancelAction = new GenericAction(this,
                                     "cancel",
                                     "Cancel",
                                     "Cancel",
                                     null,
                                     "Cancel the Representation");
    button = new JButton(cancelAction);
    buttons2.add(button);

    buttons.add(buttons2);
    this.add(buttons);
  }

  /**
   * The role panels
   */
  public RolePanel[] getRoles()
  {
    return roles;
  }

  /**
   * Set the section of the selected role.
   */
  public void setSection(sec_vd xsection)
  {
    ButtonModel model = buttonGroup.getSelection();
    RolePanel role = roleMap.get(model);

    // Check compatibility

    if(!checkNamespace(role, xsection) || !checkBase(role, xsection))
      return;

    role.setSection(xsection);

    buttonActivity();
  }

  /**
   * True, if the namespace is compatible
   */
  protected boolean checkNamespace(RolePanel xrole, sec_vd xsection)
  {
    try
    {
      sec_vd section;
      namespace_poset ns = xsection.name_space();
      String xname = ns.name();

      for(int i=0; i<roles.length; i++)
      {
        if(roles[i] != xrole)
        {
          section = roles[i].getSection();

          //$$HACK (WEM): For testing.
          //if(section != null && section.name_space() != ns)

          boolean showDialog = false;
          if(section != null)
          {
            //System.err.println("section.name_space() = " + section.name_space());

            String sname = section.name_space().name();

            //System.err.println(" xname  = " + xname);
            //System.err.println(" sname  = " + sname);
            //System.err.println(" sname.equals(xname) = " + sname.equals(xname));

            // Just compare the names for now. This has the remote possibility
            // for failure though (WEM).

            showDialog = !sname.equals(xname);
          }

          if(showDialog)
          {
            getToolkit().beep();

            String[] msg = {"Different Namespaces:",
                            section.name_space().name() + " not same as "
                            + ns.name() };
            JOptionPane.showMessageDialog(this, msg, "Incompatible Namespaces",
                                          JOptionPane.ERROR_MESSAGE);

            return false;
          }
        }
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return true;
  }

  /**
   * True, if base spaces are compatible.
   */
  protected boolean checkBase(RolePanel xrole, sec_vd xsection)
  {
    try
    {
      int db = xsection.db();

      if(xrole == roles[0])
      {
        // Setting the dependent role, make sure all other roles have
        // compatible base spaces.

        sec_vd section;

        for(int i=1; i<roles.length; i++)
        {
          section = roles[i].getSection();
          if(section != null && section.db() > db)
          {
            getToolkit().beep();

            String[] msg = {"Incompatible Base Spaces:",
                            "Property sections must have a base\n" +
                            "dimesion less than or equal to the\n" +
                            "coordinate section."};
            JOptionPane.showMessageDialog(this, msg,
                                          "Incompatible Base Spaces",
                                          JOptionPane.ERROR_MESSAGE);

            return false;
          }
        }
      }
      else
      {
        sec_vd coord = roles[0].getSection();
        if(coord != null && db > coord.db())
        {
          String[] msg = {"Incompatible Base Spaces:",
                          "Property sections must have a base\n" +
                          "dimesion less than or equal to the\n" +
                          "coordinate section."};
          JOptionPane.showMessageDialog(this, msg,
                                        "Incompatible Base Spaces",
                                        JOptionPane.ERROR_MESSAGE);

          return false;
        }
      }
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return true;
  }

  /**
   * Set the button activity
   */
  public void buttonActivity()
  {
    if(canView())
      viewAction.setEnabled(true);
    else
      viewAction.setEnabled(false);

    if(hasSection())
      resetAction.setEnabled(true);
    else
      resetAction.setEnabled(false);
  }

  /**
   * True, if the representation can be visualized.
   */
  protected abstract boolean canView();

  /**
   * True, if any role has been filled
   */
  protected boolean hasSection()
  {
    for(int i=0; i<roles.length; i++)
    {
      if(roles[i].getSection() != null)
        return true;
    }

    return false;
  }

  /**
   * Force the overwriting of toString().
   */
  public abstract String toString();

  // ACTIONS FACET

  /**
   * View this representation
   */
  public abstract void view();

  /**
   * Reset the roles
   */
  public void reset()
  {
    for(int i=0; i<roles.length; i++)
    {
      roles[i].clear();
    }

    roles[0].getRoleRadioButton().setSelected(true);

    viewAction.setEnabled(false);
    resetAction.setEnabled(false);
  }

  /**
   * Cancel this <code>FieldActoToolBar</code>
   */
  public void cancel()
  {
    application.cancelFieldActorToolBar();
  }

  // UTILITY FACET

  /**
   * Return a <code>SectionDescriptor</code> for xsection.
   * Null, if the use cancels the creation.
   */
  protected SectionDescriptor getSectionDescriptor(sec_vd xsection)
  throws java.rmi.RemoteException
  {
    SectionDescriptor descriptor = new SectionDescriptor();

    descriptor.path = xsection.path(true).path();
    if(xsection.base_is_restricted())
    {
      // Restricted base.

      if(xsection.base().name().length() == 0)
      {
        // Can not use an empty base.

        if(!useUnrestrictedBase())
          return null;
      }
      else
      {
        descriptor.base = xsection.base().path(true).path();
      }
    }

    if(xsection.fiber_schema_is_restricted())
    {
      // Restricted fiber schema

      if(xsection.fiber_schema().name().length() == 0)
      {
        if(!useUnrestrictedFiberSchema())
          return null;
      }
      else
      {
        descriptor.fiberSchema = xsection.fiber_schema().path(true).path();
      }
    }

    return descriptor;
  }

  /**
   * Open dialog to inform the user the base restriction
   * can not be used.
   */
  protected boolean useUnrestrictedBase()
  {
    return useUnrestricted("base");
  }

  /**
   * Open dialog to inform the user the fiber schema restriction
   * can not be used.
   */
  protected boolean useUnrestrictedFiberSchema()
  {
    return useUnrestricted("fiber schema");
  }

  /**
   * Open dialog to inform the user, type, restriction can not be used.
   */
  protected boolean useUnrestricted(String type)
  {
    JFrame frame = (JFrame)(SwingUtilities.windowForComponent(this));

    int result =
      JOptionPane.showConfirmDialog(frame,
                                    "Restricted " + type + " name is " +
                                    "empty.\nCan not view an unnamed " +
                                    "restricted " + type + ".\n\n" +
                                    "Continue with a unrestricted " +
                                    type + "?");

    return (result == JOptionPane.YES_OPTION);
  }
}
