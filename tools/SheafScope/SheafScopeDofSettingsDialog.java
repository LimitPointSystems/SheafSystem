
/**
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

package tools.SheafScope;

import tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * SheafScopeDofSettingsDialog provides dialog mechanisms for dofs display.
 */
public class SheafScopeDofSettingsDialog extends GenericDialog implements ActionListener
{
  protected JComboBox displayComboBox;
  protected JLabel limitLabel;
  protected JTextField limitTextField;

  private String display;
  private int limit;

  /**
   * Constructor
   * @param xframe The display frame.
   */
  public SheafScopeDofSettingsDialog(Frame xframe)
  {
    this(xframe, SheafScopeApplication.dofDisplay,
         SheafScopeApplication.dofLimit);
  }

  /**
   * Constructor
   * @param xframe The display frame.
   */
  public SheafScopeDofSettingsDialog(Frame xframe, String xdisplay, int xlimit)
  {
    super(xframe, "Dof Settings");

    display = xdisplay;
    limit = xlimit;

    // Create the content pane.

    JPanel dofsPanel = new JPanel();
    dofsPanel.setLayout(new BoxLayout(dofsPanel, BoxLayout.Y_AXIS));
    dofsPanel.add(Box.createVerticalStrut(6));

    // Create the display type combo box.

    displayComboBox = new JComboBox(SheafScopeApplication.DISPLAY_OPTIONS);
    displayComboBox.setSelectedItem(display);
    displayComboBox.addActionListener(this);
    Box box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(displayComboBox);
    box.add(Box.createHorizontalStrut(6));

    dofsPanel.add(box);
    dofsPanel.add(Box.createVerticalStrut(6));

    // Create the limit number text field

    limitTextField = new JTextField();
    limitTextField.setText(Integer.toString(limit));
    limitLabel = new JLabel("Limit:");
    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(limitLabel);
    box.add(Box.createHorizontalStrut(6));
    box.add(limitTextField);
    box.add(Box.createHorizontalStrut(6));

    dofsPanel.add(box);
    dofsPanel.add(Box.createVerticalStrut(6));

    addPane(dofsPanel, 0);

    // Enable the limit number text field

    enableLimitTextField();
  }

  /**
   * The action listener interface for the display type combo box
   *
   *
   */
  public void actionPerformed(ActionEvent e)
  {
    enableLimitTextField();
  }

  /**
   * Set the enabled state of the limit number combo box
   *
   *
   */
  protected void enableLimitTextField()
  {
    if(displayComboBox.getSelectedItem().
        equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS))
    {
      limitLabel.setEnabled(true);
      limitTextField.setEnabled(true);
    }
    else
    {
      limitLabel.setEnabled(false);
      limitTextField.setEnabled(false);
    }
  }

  /**
   * Cancels the dialog.<p>
   *
   * 
   */
  public void cancelPressed()
  {
    display = null;
    setVisible(false);
  }

  /**
   * Accepts the selected value.<p>
   *
   * 
   */
  public void okPressed()
  {
    display = displayComboBox.getSelectedItem().toString();

    if(display.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS))
    {
      try
      {
        limit = Integer.parseInt(limitTextField.getText());
      }
      catch(Exception e)
      {
        JOptionPane.showMessageDialog(this,
                                      "Invalid Limit Number.  Must be an Integer!",
                                      "Invalid Limit",
                                      JOptionPane.ERROR_MESSAGE);

        limitTextField.setText(Integer.toString(SheafScopeApplication.dofLimit));

        return;
      }
    }

    setVisible(false);
  }

  /**
   * Public accessor for the dof display.
   */
  public String getDofDisplay()
  {
    return display;
  }

  /**
   * Public accessor for the dof limit
   */
  public int getDofLimit()
  {
    return limit;
  }
}

