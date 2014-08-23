
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

import bindings.java.*;
import com.limitpoimt.tools.common.gui.*;

import java.awt.*;
import java.lang.reflect.*;
import javax.swing.*;

/**
 * Abstract dialog for choicing a <code>FieldActorToolBar</code>
 */
public abstract class FieldActorDialog extends GenericDialog
{
  /**
   * The <code>FieldActorToolBarApplicaiton</code>
   */
  protected FieldActorToolBarApplication application;

  /**
   * The <code>FieldActorToolBar</code> representation combo box.
   */
  protected JComboBox repComboBox;

  /**
   * The selected <code>FieldActorToolBar</code> representation
   */
  protected FieldActorToolBar selectedRep = null;

  /**
   * The constructor
   */
  protected FieldActorDialog(Frame owner,
                             FieldActorToolBarApplication xapplication,
                             Class[] xreps)
  {
    super(owner, "Select Graphic Representation");

    application = xapplication;

    repComboBox = new JComboBox();
    repComboBox.setToolTipText("Select Graphic Representation");
    int sz = xreps.length;
    for(int i=0; i<sz; i++)
    {
      try
      {
        Constructor constructor =
          xreps[i].getConstructor(FieldActorToolBarApplication.class);
        FieldActorToolBar rep =
          (FieldActorToolBar) constructor.newInstance(application);
        repComboBox.addItem(rep);
      }
      catch(Exception e)
      {
        // $$HACK: Need better error handling.

        e.printStackTrace();
      }
    }

    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());
    panel.add(Box.createVerticalStrut(10), BorderLayout.NORTH);
    panel.add(Box.createVerticalStrut(10), BorderLayout.SOUTH);
    panel.add(Box.createHorizontalStrut(10), BorderLayout.EAST);
    panel.add(Box.createHorizontalStrut(10), BorderLayout.WEST);
    panel.add(repComboBox, BorderLayout.CENTER);

    addPane(panel, 0);
  }

  /**
   * Return the selected representation.
   */
  public FieldActorToolBar getSelectedRep()
  {
    return selectedRep;
  }

  /**
   * Cancels the dialog.
   */
  public void cancelPressed()
  {
    selectedRep = null;
    setVisible(false);
  }

  /**
   * Accepts the selected filter.<p>
   *
   * 
   */
  public void okPressed()
  {
    selectedRep = (FieldActorToolBar) repComboBox.getSelectedItem();
    setVisible(false);
  }
}
