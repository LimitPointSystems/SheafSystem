
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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

/**
 * Abstract class for choicing the section to play a role.
 */
public abstract class RolePanel extends JPanel
{
  // CONSTANTS FACET

  static final Color ENABLED_COLOR  = new Color(255, 255, 255);
  static final Color DISABLED_COLOR = new Color(230, 230, 230);

  // GUI FACET

  /**
   * The <code>JRadioButton</code> defining the role.
   */
  protected JRadioButton roleRadioButton;

  /**
   * The section <code>JTextField</code>
   */
  protected SectionTextField sectionTextField;

  /**
   * The <code>SectionInfoDialog</code>
   */
  protected SectionInfoDialog infoDialog;

  // SECTION FACET

  /**
   * The section
   */
  protected sec_vd section = null;

  /**
   * The constructor
   */
  protected RolePanel()
  {
    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    setBorder(new EtchedBorder());

    roleRadioButton = new JRadioButton(getRole());
    roleRadioButton.addChangeListener(new RadioButtonAction());
    add
      (roleRadioButton);

    sectionTextField = new SectionTextField();
    add
      (sectionTextField);

    infoDialog = new SectionInfoDialog(getRole());
  }

  /**
   * Return the role <code>JRadioButton</code>
   */
  public JRadioButton getRoleRadioButton()
  {
    return roleRadioButton;
  }

  /**
   * Return the section
   */
  public sec_vd getSection()
  {
    return section;
  }

  /**
   * Set the section
   */
  public void setSection(sec_vd xsection)
  {
    if(!canFillRole(xsection))
      return;

    section = xsection;
    infoDialog.setSection(section);

    String text = "";
    try
    {
      text = section.path(true).path();
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    sectionTextField.setText(text);
  }

  /**
   * Clear the section
   */
  public void clear()
  {
    section = null;

    sectionTextField.setText("");
  }

  /**
   * Return the role text
   */
  protected abstract String getRole();

  /**
   * True, if the role can be filled by xsection
   */
  protected abstract boolean canFillRole(sec_vd xsection);

  /**
   *  Class to allow handling of mouse clicks on a TextField.
   *  When click on, it brings up a small window with
   *  more detailed information about the selected field.
   */
  public class SectionTextField extends JTextField implements MouseListener
  {
    public SectionTextField()
    {
      super(16);
      setEditable(false);
      setEnabled(false);
      addMouseListener(this);
    }

    public void setEnabled(boolean enabled)
    {
      super.setEnabled(enabled);

      Color c = (enabled) ? ENABLED_COLOR : DISABLED_COLOR;
      setBackground(c);
    }

    public void mouseClicked(MouseEvent evt)
    {
      if(section != null)
        infoDialog.setVisible(true);
    }

    public void mouseEntered(MouseEvent e)
  {}
    public void mouseExited(MouseEvent e)
    {}
    public void mousePressed(MouseEvent e)
    {}
    public void mouseReleased(MouseEvent e)
    {}
  }

  /**
   *  Action to enable/disable associated text fields.
   */
  public class RadioButtonAction implements ChangeListener
  {
    public RadioButtonAction()
    {
      super();
    }

    public void stateChanged(ChangeEvent evt)
    {
      sectionTextField.setEnabled(roleRadioButton.isSelected());
    }
  }
}
