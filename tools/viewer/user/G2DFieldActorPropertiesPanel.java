
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

package com.limitpoint.tools.viewer.user;

import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.text.*;
import vtk.*;

/**
 * Implementation of <code>FieldActorPropertiesPanel</code> for editing the
 * values of a <code>G2DFieldActorDescriptor</code>.
 */
public class G2DFieldActorPropertiesPanel extends FieldActorPropertiesPanel
{
  // DEFAULT VALUE FACET

  static final String[] SHOW_HIDE = {"Show", "Hide"};

  // DESCRIPTOR FACET

  protected JPanel displayStylePanel;
  protected JPanel titlePanel;
  protected JPanel colorPanel;

  protected JComboBox pointsComboBox;
  protected JSpinner pointSizeSpinner;
  protected JComboBox linesComboBox;
  protected JSpinner lineWidthSpinner;

  protected JTextField titleTextField;
  protected JTextField xtitleTextField;
  protected JTextField ytitleTextField;

  protected JButton editBackgroundButton;
  protected Action editBackgroundAction;
  protected JButton editForegroundButton;
  protected Action editForegroundAction;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  public G2DFieldActorPropertiesPanel(G2DViewer xviewer,
                                      FieldActorDescriptor[] xdescriptors)
  {
    super(xviewer, xdescriptors);

    displayStylePanel = createDisplayStylePanel();
    titlePanel = createTitlePanel();
    colorPanel = createColorPanel();

    tabbedPane.addTab("Display", displayStylePanel);
    tabbedPane.addTab("Titles", titlePanel);
    tabbedPane.addTab("Colors", colorPanel);

    initValues();
  }

  // CREATE FACET

  /**
   *
   */
  protected JPanel createDisplayStylePanel()
  {
    JPanel result = new JPanel();
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Display:")));

    result.setLayout(new BorderLayout());

    JPanel mainPanel = new JPanel();
    GridLayout layout = new GridLayout(4,2);
    layout.setVgap(36);
    layout.setHgap(6);
    mainPanel.setLayout(layout);

    result.add(Box.createVerticalStrut(24), BorderLayout.NORTH);
    result.add(Box.createVerticalStrut(24), BorderLayout.SOUTH);
    result.add(Box.createHorizontalStrut(60), BorderLayout.EAST);
    result.add(Box.createHorizontalStrut(60), BorderLayout.WEST);
    result.add(mainPanel, BorderLayout.CENTER);

    //=====

    JLabel pointsLabel = new JLabel("Points:", JLabel.RIGHT);
    pointsLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    pointsComboBox = new JComboBox(SHOW_HIDE);

    mainPanel.add(pointsLabel);
    mainPanel.add(pointsComboBox);

    //=====

    JLabel pointSizeLabel = new JLabel("Point Size: ", JLabel.RIGHT);
    pointSizeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    int initialSize = 1;
    SpinnerModel pointSizeModel = new SpinnerNumberModel(initialSize, 0, 100, 1);

    pointSizeSpinner = new JSpinner(pointSizeModel);

    mainPanel.add(pointSizeLabel);
    mainPanel.add(pointSizeSpinner);

    //=====

    JLabel linesLabel = new JLabel("Lines:", JLabel.RIGHT);
    linesLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    linesComboBox = new JComboBox(SHOW_HIDE);

    mainPanel.add(linesLabel);
    mainPanel.add(linesComboBox);

    //=====

    JLabel lineWidthLabel = new JLabel("Line Width: ", JLabel.RIGHT);
    lineWidthLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    int initialWidth = 1;
    SpinnerModel lineWidthModel = new SpinnerNumberModel(initialWidth, 0, 100, 1);

    lineWidthSpinner = new JSpinner(lineWidthModel);

    mainPanel.add(lineWidthLabel);
    mainPanel.add(lineWidthSpinner);

    return result;
  }

  /**
   *
   */
  protected JPanel createTitlePanel()
  {
    titleTextField = new JTextField();
    xtitleTextField = new JTextField();
    ytitleTextField = new JTextField();

    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Titles:")));

    // Create the title panel.

    JPanel panel = new JPanel();

    JLabel label = new JLabel("Title: ", JLabel.RIGHT);
    label.setPreferredSize(new Dimension(100, 30));
    titleTextField.setPreferredSize(new Dimension(150, 30));

    panel.add(Box.createHorizontalGlue());
    panel.add(label);
    panel.add(Box.createHorizontalStrut(6));
    panel.add(titleTextField);
    panel.add(Box.createHorizontalGlue());

    result.add(Box.createVerticalStrut(36));
    result.add(panel);

    // Create the x-axis title panel.

    panel = new JPanel();

    label = new JLabel("X-Axis Title: ", JLabel.RIGHT);
    label.setPreferredSize(new Dimension(100, 30));
    xtitleTextField.setPreferredSize(new Dimension(150, 30));

    panel.add(Box.createHorizontalGlue());
    panel.add(label);
    panel.add(Box.createHorizontalStrut(6));
    panel.add(xtitleTextField);
    panel.add(Box.createHorizontalGlue());

    result.add(Box.createVerticalStrut(36));
    result.add(panel);

    // Create the y-axis title panel.

    panel = new JPanel();

    label = new JLabel("Y-Axis Title: ", JLabel.RIGHT);
    label.setPreferredSize(new Dimension(100, 30));
    ytitleTextField.setPreferredSize(new Dimension(150, 30));

    panel.add(Box.createHorizontalGlue());
    panel.add(label);
    panel.add(Box.createHorizontalStrut(6));
    panel.add(ytitleTextField);
    panel.add(Box.createHorizontalGlue());

    result.add(Box.createVerticalStrut(36));
    result.add(panel);
    result.add(Box.createVerticalStrut(36));

    return result;
  }

  /**
   *
   */
  protected JPanel createColorPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Colors:")));

    //=====

    // Create background color panel

    JLabel label = new JLabel("Background Color: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);

    editBackgroundAction =
      new GenericAction(this,
                        "EditBackground",
                        "doEditBackground",
                        "        ",
                        "Select the backgorund color value",
                        null, null, null, "true");

    editBackgroundButton = new JButton(editBackgroundAction);
    editBackgroundButton.setSize(50, 20);

    JPanel panel = new JPanel();
    panel.add(label);
    panel.add(editBackgroundButton);

    result.add(Box.createVerticalGlue());
    result.add(panel);

    // Create foreground color panel

    label = new JLabel("Foreground Color: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);

    editForegroundAction =
      new GenericAction(this,
                        "EditForeground",
                        "doEditForeground",
                        "        ",
                        "Select the foreground color value",
                        null, null, null, "true");

    editForegroundButton = new JButton(editForegroundAction);
    editForegroundButton.setSize(50, 20);

    panel = new JPanel();
    panel.add(label);
    panel.add(editForegroundButton);

    result.add(Box.createVerticalStrut(36));
    result.add(panel);
    result.add(Box.createVerticalGlue());

    return result;
  }

  // INITIALIZE FACET

  /**
   *
   */
  public void initValues()
  {
    // Use the first actor in the list to initialize the
    // user interface.

    G2DFieldActorDescriptor descriptor =
      (G2DFieldActorDescriptor) descriptors[0];

    initDisplayStylePanel(descriptor);
    initTitlePanel(descriptor);
    initColorPanel(descriptor);
  }

  /**
   *
   */
  protected void initDisplayStylePanel(G2DFieldActorDescriptor xdescriptor)
  {
    int b = xdescriptor.points ? 0 : 1;
    pointsComboBox.setSelectedIndex(b);
    pointSizeSpinner.setValue((int) xdescriptor.pointSize);
    b = xdescriptor.lines ? 0 : 1;
    linesComboBox.setSelectedIndex(b);
    lineWidthSpinner.setValue((int) xdescriptor.lineWidth);
  }

  /**
   *
   */
  protected void initTitlePanel(G2DFieldActorDescriptor descriptor)
  {
    titleTextField.setText(descriptor.title);
    xtitleTextField.setText(descriptor.xtitle);
    ytitleTextField.setText(descriptor.ytitle);
  }

  /**
   *
   */
  protected void initColorPanel(G2DFieldActorDescriptor xdescriptor)
  {
    // There should be one and only one camera.  Get the background color
    // from it.

    CameraDescriptor camera = viewer.getScene().cameras.iterator().next();

    editBackgroundButton.setBackground(camera.background);
    editForegroundButton.setBackground(xdescriptor.foreground);
  }

  // APPLY FACET

  /**
   *
   */
  public void doApply()
  {
    // Set the wait state to true, it is restored by
    // UpdatePropertiesPanelEvent.

    setWaitState(true);

    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        // Apply the changed to the descriptors

        G2DFieldActorDescriptor descriptor;

        for(int i=0; i<descriptors.length; i++)
        {
          descriptor = (G2DFieldActorDescriptor) descriptors[i];

          applyDisplayStyle(descriptor);
          applyTitle(descriptor);
          applyColor(descriptor);
        }
      }
    }

    // Update the clients of the viewer

    viewer.updateClients();

    // Update the values of this panel.

    viewer.updatePropertiesPanel(this);
  }

  /**
   *
   */
  public void applyDisplayStyle(G2DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.points =
      (pointsComboBox.getSelectedIndex() == 0) ? true : false;
    xdescriptor.pointSize = ((SpinnerNumberModel)pointSizeSpinner.getModel()).getNumber().doubleValue();
    xdescriptor.lines =
      (linesComboBox.getSelectedIndex() == 0) ? true : false;
    xdescriptor.lineWidth = ((SpinnerNumberModel)lineWidthSpinner.getModel()).getNumber().doubleValue();
  }

  /**
   *
   */
  public void applyTitle(G2DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.title = titleTextField.getText().trim();
    xdescriptor.xtitle = xtitleTextField.getText().trim();
    xdescriptor.ytitle = ytitleTextField.getText().trim();
  }

  /**
   *
   */
  public void applyColor(G2DFieldActorDescriptor xdescriptor)
  {
    // There should be one and only one camera.  Set the background color
    // of it.

    CameraDescriptor camera = viewer.getScene().cameras.iterator().next();

    camera.background = editBackgroundButton.getBackground();
    xdescriptor.foreground = editForegroundButton.getBackground();
  }

  // ACTIONS FACET

  /**
   * The value of xfield has changed.  Returns true if the changed value
   * is valid.
   */
  public boolean valueChanged(JTextField xfield)
  {
    return true;
  }

  /**
   * Selects background color.
   */
  public void doEditBackground()
  {
    Color background = editBackgroundButton.getBackground();
    Color color = JColorChooser.showDialog(this, "Select Background Color",
                                           background);
    if(color != null && color != background)
    {
      editBackgroundButton.setBackground(color);
    }
  }

  /**
   * Selects foreground color.
   */
  public void doEditForeground()
  {
    Color foreground = editForegroundButton.getBackground();
    Color color = JColorChooser.showDialog(this, "Select Foreground Color",
                                           foreground);
    if(color != null && color != foreground)
    {
      editForegroundButton.setBackground(color);
    }
  }
}
