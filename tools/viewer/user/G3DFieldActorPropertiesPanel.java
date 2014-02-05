
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

package tools.viewer.user;

import tools.viewer.common.*;
import tools.viewer.render.*;
import tools.common.gui.*;

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
 * values of a <code>G3DFieldActorDescriptor</code>.
 */
public abstract class G3DFieldActorPropertiesPanel
      extends FieldActorPropertiesPanel implements ItemListener
{
  // DEFAULT VALUE FACET

  protected static final String[] POINT_LABEL_IDS = { "None", "Top Ids", "Disc Ids" };
  protected static final String[] CELL_LABEL_IDS = { "None", "Top Ids", "Eval Ids" };

  // GUI FACET

  protected JPanel displayStylePanel;
  protected JPanel colorPanel;
  protected JPanel colorMapPanel;
  protected JPanel labelsPanel;
  protected JPanel positionPanel;
  protected JPanel originPanel;
  protected JPanel orientationPanel;
  protected JPanel scalePanel;
  protected JPanel boundsPanel;
  
  protected JTable boundsTable;
  protected Object[][] boundsData = 
  {
      {"X min", 1.0},
      {"X max", 0.0},
      {"Y min", 1.0},
      {"Y max", 0.0},
      {"Z min", 1.0},
      {"Z max", 0.0}
   };
  
  protected JComboBox visibilityComboBox;
  protected JSpinner pointSizeSpinner;
  protected JSpinner lineWidthSpinner;
  protected JComboBox styleComboBox;
  protected JComboBox interpComboBox;
  protected JSpinner opacitySpinner;
  protected JCheckBox showEdgesCheckBox;

  protected JComboBox colorByComboBox;
  protected JButton editSolidColorButton;
  protected Action editSolidColorAction;
  protected Color solidColor;

  protected JSpinner[] extremeHueSpinners = new JSpinner[2];
  protected JSpinner[] thresholdSizeSpinners = new JSpinner[2];
  protected JComboBox[] thresholdComponentComboBoxs = new JComboBox[2];
  protected JComboBox[] componentMethodComboBoxs = new JComboBox[2];
  protected JSpinner[] extremeComponentValueSpinners = new JSpinner[2];
  protected JComboBox[] extremeHueMethodComboBoxs = new JComboBox[2];

  protected JComboBox pointLabelsComboBox;
  protected JComboBox cellLabelsComboBox;

  protected JTextField xpositionTextField;
  protected JTextField ypositionTextField;
  protected JTextField zpositionTextField;

  protected JTextField xoriginTextField;
  protected JTextField yoriginTextField;
  protected JTextField zoriginTextField;

  protected JTextField xorientationTextField;
  protected JTextField yorientationTextField;
  protected JTextField zorientationTextField;

  protected JTextField xscaleTextField;
  protected JTextField yscaleTextField;
  protected JTextField zscaleTextField;

  // CONSTRUCTORS

  /**
   *
   */
  public G3DFieldActorPropertiesPanel(G3DViewer xviewer, FieldActorDescriptor[] xdescriptors)
  {
    super(xviewer, xdescriptors);

    displayStylePanel = createDisplayStylePanel();
    colorPanel = createColorPanel();
    colorMapPanel = createColorMapPanel();
    labelsPanel = createLabelsPanel();
    positionPanel = createPositionPanel();
    originPanel = createOriginPanel();
    orientationPanel = createOrientationPanel();
    scalePanel = createScalePanel();
    boundsPanel = createBoundsPanel();

    tabbedPane.addTab("Display", displayStylePanel);
    tabbedPane.addTab("Color", colorPanel);
    tabbedPane.addTab("Color Map", colorMapPanel);
    tabbedPane.addTab("Labels", labelsPanel);
    tabbedPane.addTab("Position", positionPanel);
    tabbedPane.addTab("Origin", originPanel);
    tabbedPane.addTab("Orientation", orientationPanel);
    tabbedPane.addTab("Scale", scalePanel);
    tabbedPane.addTab("Bounds", boundsPanel);

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
    GridLayout layout = new GridLayout(7,2);
    layout.setVgap(12);
    layout.setHgap(6);
    mainPanel.setLayout(layout);
    result.add(Box.createVerticalStrut(12), BorderLayout.NORTH);
    result.add(Box.createVerticalStrut(12), BorderLayout.SOUTH);
    result.add(Box.createHorizontalStrut(60), BorderLayout.EAST);
    result.add(Box.createHorizontalStrut(60), BorderLayout.WEST);
    result.add(mainPanel, BorderLayout.CENTER);

    //=====

    JLabel visibilityLabel = new JLabel("Visibility:", JLabel.RIGHT);
    visibilityLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    visibilityComboBox = new JComboBox(SHOW_HIDE);

    mainPanel.add(visibilityLabel);
    mainPanel.add(visibilityComboBox);

    //=====

    JLabel displayLabel = new JLabel("Style: ", JLabel.RIGHT);
    displayLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    String[] displayStrings = { "Points", "Wireframe", "Surface"};

    styleComboBox = new JComboBox(displayStrings);
    styleComboBox.setSelectedIndex(0);

    mainPanel.add(displayLabel);
    mainPanel.add(styleComboBox);

    //=====

    JLabel interpLabel = new JLabel("Interpolation: ", JLabel.RIGHT);
    interpLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    String[] interpStrings = { "Flat", "Gouraud", "Phong"  };

    interpComboBox = new JComboBox(interpStrings);
    interpComboBox.setSelectedIndex(0);

    mainPanel.add(interpLabel);
    mainPanel.add(interpComboBox);

    //=====

    JLabel opacityLabel = new JLabel("Opacity: ", JLabel.RIGHT);
    opacityLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    SpinnerModel opacityModel = new SpinnerNumberModel(1.0, 0.0, 1.0, 0.01);

    opacitySpinner = new JSpinner(opacityModel);

    mainPanel.add(opacityLabel);
    mainPanel.add(opacitySpinner);

    //=====

    JLabel pointSizeLabel = new JLabel("Point Size: ", JLabel.RIGHT);
    pointSizeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    SpinnerModel pointSizeModel = new SpinnerNumberModel(1, 0, 100, 1);

    pointSizeSpinner = new JSpinner(pointSizeModel);

    mainPanel.add(pointSizeLabel);
    mainPanel.add(pointSizeSpinner);

    //=====

    JLabel lineWidthLabel = new JLabel("Line Width: ", JLabel.RIGHT);
    lineWidthLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    SpinnerModel lineWidthModel = new SpinnerNumberModel(1, 0, 100, 1);

    lineWidthSpinner = new JSpinner(lineWidthModel);

    mainPanel.add(lineWidthLabel);
    mainPanel.add(lineWidthSpinner);

    //=====

    showEdgesCheckBox = new JCheckBox("Show Edges");
    mainPanel.add(Box.createHorizontalGlue());
    mainPanel.add(showEdgesCheckBox);

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
        BorderFactory.createTitledBorder("Color:")));

    //=====

    JLabel label = new JLabel("Color By: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);

    String[] strings = { "Solid", "Scalar" };

    colorByComboBox = new JComboBox(strings);
    colorByComboBox.setSelectedIndex(1);
    colorByComboBox.addItemListener(this);

    JPanel panel = new JPanel();
    panel.add(label);
    panel.add(colorByComboBox);

    result.add(panel);

    // Create solid color panel

    label = new JLabel("Edit Color: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);


    editSolidColorAction = new GenericAction(this,
                           "EditColorAction",
                           "doEditSolidColor",
                           "        ",
                           "Select the Actor's sold color",
                           null, null, null, "true");

    editSolidColorButton = new JButton(editSolidColorAction);
    editSolidColorButton.setBackground(solidColor);
    editSolidColorButton.setSize(50, 20);

    panel = new JPanel();
    panel.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Solid:")));
    panel.add(label);
    panel.add(editSolidColorButton);

    result.add(panel);

    return result;
  }

  /**
   *
   */
  protected JPanel createColorMapPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Color Map:")));

    //=====

    // Create scalar color panel

    JPanel scalarPanel = new JPanel();
    GridLayout layout = new GridLayout(7,3);
    layout.setVgap(8);
    layout.setHgap(8);
    scalarPanel.setLayout(layout);

    // Labels

    scalarPanel.add(Box.createHorizontalGlue());

    JLabel label = new JLabel("Minimum");
    label.setHorizontalAlignment(JLabel.CENTER);
    scalarPanel.add(label);

    label = new JLabel("Maximum");
    label.setHorizontalAlignment(JLabel.CENTER);
    scalarPanel.add(label);

    // Hue

    JPanel panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Extreme"));
    panel.add(new JLabel("Hue"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      extremeHueSpinners[i] =
        new JSpinner(new SpinnerNumberModel(0.0, 0.0, 1.0, 0.001));
      scalarPanel.add(extremeHueSpinners[i]);
    }

    // Threshold Size

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Threshold"));
    panel.add(new JLabel("Size (%)"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      thresholdSizeSpinners[i] =
        new JSpinner(new SpinnerNumberModel(0.2, 0.0, 1.0, 0.01));
      scalarPanel.add(thresholdSizeSpinners[i]);
    }

    // Threshold Component

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Threshold"));
    panel.add(new JLabel("Component"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      thresholdComponentComboBoxs[i] = new
                                       JComboBox(ViewerConstants.THRESHOLD_COMPONENTS);
      scalarPanel.add(thresholdComponentComboBoxs[i]);
    }

    // Component Method

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Component"));
    panel.add(new JLabel("Method"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      componentMethodComboBoxs[i] = new
                                    JComboBox(ViewerConstants.THRESHOLD_METHODS);
      scalarPanel.add(componentMethodComboBoxs[i]);
    }

    // Extreme Component Value

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Extreme"));
    panel.add(new JLabel("Value"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      extremeComponentValueSpinners[i] =
        new JSpinner(new SpinnerNumberModel(0.2, 0.0, 1.0, 0.01));
      scalarPanel.add(extremeComponentValueSpinners[i]);
    }

    // Extreme Hue Method

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(Box.createVerticalGlue());
    panel.add(new JLabel("Extreme"));
    panel.add(new JLabel("Hue Method"));
    panel.add(Box.createVerticalGlue());
    scalarPanel.add(panel);

    for(int i=0; i<2; i++)
    {
      extremeHueMethodComboBoxs[i] = new
                                     JComboBox(ViewerConstants.THRESHOLD_METHODS);
      scalarPanel.add(extremeHueMethodComboBoxs[i]);
    }

    // Add the scalar panel

    result.add(scalarPanel);

    return result;
  }

  /**
   *
   */
  protected JPanel createLabelsPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Labels:")));

    // Create the point labels button.

    result.add(Box.createVerticalGlue());

    JPanel panel = new JPanel();
    JLabel label = new JLabel("Point Labels: ");
    pointLabelsComboBox = new JComboBox(POINT_LABEL_IDS);

    panel.add(label);
    panel.add(pointLabelsComboBox);

    result.add(panel);

    result.add(Box.createVerticalGlue());

    // Create the cell labels button.

    panel = new JPanel();
    label = new JLabel("Cell Labels: ");
    cellLabelsComboBox = new JComboBox(CELL_LABEL_IDS);

    panel.add(label);
    panel.add(cellLabelsComboBox);

    result.add(panel);

    result.add(Box.createVerticalGlue());

    return result;
  }

  /**
   *
   */
  protected JPanel createPositionPanel()
  {
    xpositionTextField = new JTextField();
    ypositionTextField = new JTextField();
    zpositionTextField = new JTextField();

    return createXYZPanel("Position", xpositionTextField,
                          ypositionTextField, zpositionTextField);
  }

  /**
   *
   */
  protected JPanel createOriginPanel()
  {
    xoriginTextField = new JTextField();
    yoriginTextField = new JTextField();
    zoriginTextField = new JTextField();

    return createXYZPanel("Origin", xoriginTextField,
                          yoriginTextField, zoriginTextField);
  }

  /**
   *
   */
  protected JPanel createOrientationPanel()
  {
    xorientationTextField = new JTextField();
    yorientationTextField = new JTextField();
    zorientationTextField = new JTextField();

    return createXYZPanel("Orientation", "Theta ", xorientationTextField,
                          yorientationTextField, zorientationTextField);
  }

  /**
   *
   */
  protected JPanel createScalePanel()
  {
    xscaleTextField = new JTextField();
    yscaleTextField = new JTextField();
    zscaleTextField = new JTextField();

    return createXYZPanel("Scale", xscaleTextField,
                          yscaleTextField, zscaleTextField);
  }

  /**
   *
   */
  protected JPanel createBoundsPanel()
  {  
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(6, 12, 6, 12), 
		   BorderFactory.createTitledBorder("Bounds:")));
    // Add some vertical space above the data
    result.add(Box.createVerticalGlue());	

    String[] columnNames = {"Bound","Value"};
 
    // Create a table to display the bounds data.
    boundsTable = new JTable(boundsData, columnNames)
    {
      public boolean isCellEditable(int rowIndex, int vColIndex)
      {
        return false;
      }
    };	    
    
    result.add(boundsTable);
 
    // Add some vertical space below the data
    result.add(Box.createVerticalGlue());	

    return result;
  }

  // INITIALIZE FACET

  /**
   *
   */
  public void initValues()
  {
    // Use the first descriptor in the list to initialize the
    // user interface.

    G3DFieldActorDescriptor descriptor = (G3DFieldActorDescriptor) descriptors[0];
    initDisplayStylePanel(descriptor);
    initColorPanel(descriptor);
    initColorMapPanel(descriptor);
    initLabelsPanel(descriptor);
    initPositionPanel(descriptor);
    initOriginPanel(descriptor);
    initOrientationPanel(descriptor);
    initScalePanel(descriptor);

    initBounds();
  }

  /**
   * Initialize bounds.
   */
  protected void initBounds()
  {
    // Find the bounds extrema for all the selected actors.

    double[] bounds = new double[6];

    double min = Double.MIN_VALUE;
    double max = Double.MAX_VALUE;
    double[] extrema = { max, min, max, min, max, min };

    G3DFieldActorDescriptor descriptor;

    for(int i=0; i<descriptors.length; i++)
    {
      ((G3DViewer) viewer).
	  getBounds((G3DFieldActorDescriptor) descriptors[i], bounds);

      // Find the min extrema.

      extrema[0] = Math.min(extrema[0], bounds[0]);
      extrema[2] = Math.min(extrema[2], bounds[2]);
      extrema[4] = Math.min(extrema[4], bounds[4]);

      // Find the max extrema.

      extrema[1] = Math.max(extrema[1], bounds[1]);
      extrema[3] = Math.max(extrema[3], bounds[3]);
      extrema[5] = Math.max(extrema[5], bounds[5]);
    }  

    for(int i = 0; i < bounds.length; i++)
    {
      boundsTable.setValueAt(formatBound(extrema[i]), i, 1);
    }
  }

  /**
   * Make doubles display to three significant digits.
   */
  protected double formatBound(double xdouble)
  {
    DecimalFormat df = new DecimalFormat("#.###");

    return Double.valueOf(df.format(xdouble).toString());
  }

  /**
   *
   */
  protected void initDisplayStylePanel(G3DFieldActorDescriptor xdescriptor)
  {
    int vis = xdescriptor.visibility ? 0 : 1;
    visibilityComboBox.setSelectedIndex(vis);
    opacitySpinner.setValue(xdescriptor.opacity);
    pointSizeSpinner.setValue((int) xdescriptor.pointSize);
    lineWidthSpinner.setValue((int) xdescriptor.lineWidth);
    styleComboBox.setSelectedIndex(xdescriptor.displayStyle);
    interpComboBox.setSelectedIndex(xdescriptor.interpolation);
    showEdgesCheckBox.setSelected(xdescriptor.edgeVisibility);
  }

  /**
   *
   */
  protected void initColorPanel(G3DFieldActorDescriptor xdescriptor)
  {
    G3DFieldActorDescriptor descriptor =
      (G3DFieldActorDescriptor) xdescriptor;

    int index = (descriptor.scalarVisibility) ? 1 : 0;
    colorByComboBox.setSelectedIndex(index);
    solidColor = descriptor.solidColor;
    setColorEnabled(descriptor.scalarVisibility);
  }

  /**
   *
   */
  protected void initColorMapPanel(G3DFieldActorDescriptor xdescriptor)
  {
    G3DFieldActorDescriptor descriptor =
      (G3DFieldActorDescriptor) xdescriptor;

    RangeLookupTableDescriptor lookupTable =
      (RangeLookupTableDescriptor) descriptor.lookupTable;

    for(int i=0; i<2; i++)
    {
      extremeHueSpinners[i].setValue(lookupTable.extremeHues[i]);
      thresholdSizeSpinners[i].setValue(lookupTable.thresholdSizes[i]);
      thresholdComponentComboBoxs[i].setSelectedItem(lookupTable.thresholdComponents[i]);
      componentMethodComboBoxs[i].setSelectedItem(lookupTable.componentMethods[i]);
      extremeComponentValueSpinners[i].setValue(lookupTable.extremeComponentValues[i]);
      extremeHueMethodComboBoxs[i].setSelectedItem(lookupTable.extremeHueMethods[i]);
    }
  }

  /**
   *
   */
  protected void initLabelsPanel(G3DFieldActorDescriptor xdescriptor)
  {
    pointLabelsComboBox.setSelectedIndex(xdescriptor.pointLabels);
    cellLabelsComboBox.setSelectedIndex(xdescriptor.cellLabels);
  }

  /**
   *
   */
  protected void initPositionPanel(G3DFieldActorDescriptor xdescriptor)
  {
    addToTextField(xdescriptor.position[0], xpositionTextField);
    addToTextField(xdescriptor.position[1], ypositionTextField);
    addToTextField(xdescriptor.position[2], zpositionTextField);
  }

  /**
   *
   */
  protected void initOriginPanel(G3DFieldActorDescriptor xdescriptor)
  {
    addToTextField(xdescriptor.origin[0], xoriginTextField);
    addToTextField(xdescriptor.origin[1], yoriginTextField);
    addToTextField(xdescriptor.origin[2], zoriginTextField);
  }

  /**
   *
   */
  protected void initOrientationPanel(G3DFieldActorDescriptor xdescriptor)
  {
    addToTextField(xdescriptor.orientation[0], xorientationTextField);
    addToTextField(xdescriptor.orientation[1], yorientationTextField);
    addToTextField(xdescriptor.orientation[2], zorientationTextField);
  }

  /**
   *
   */
  protected void initScalePanel(G3DFieldActorDescriptor xdescriptor)
  {
    addToTextField(xdescriptor.scale[0], xscaleTextField);
    addToTextField(xdescriptor.scale[1], yscaleTextField);
    addToTextField(xdescriptor.scale[2], zscaleTextField);
  }

  // APPLY FACET

  /**
   *
   */
  public void doApply()
  {
    doApply(true);
  }

  /**
   *
   */
  public void doApply(boolean xwait)
  {
    // Set the wait state to true, it is restored by
    // UpdatePropertiesPanelEvent.

    if(xwait)
      setWaitState(true);

    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        // Apply the changed to the descriptors

        G3DFieldActorDescriptor descriptor;

        for(int i=0; i<descriptors.length; i++)
        {
          descriptor = (G3DFieldActorDescriptor) descriptors[i];

          applyDisplayStyle(descriptor);

          applyColor(descriptor);

          applyColorMap(descriptor);

          applyLabels(descriptor);

          applyPosition(descriptor);

          applyOrigin(descriptor);

          applyOrientation(descriptor);

          applyScale(descriptor);
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
  public void applyDisplayStyle(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.visibility =
      (visibilityComboBox.getSelectedIndex() == 0) ? true : false;
    xdescriptor.opacity = ((SpinnerNumberModel)opacitySpinner.getModel()).getNumber().doubleValue();
    xdescriptor.pointSize = ((SpinnerNumberModel)pointSizeSpinner.getModel()).getNumber().doubleValue();
    xdescriptor.lineWidth = ((SpinnerNumberModel)lineWidthSpinner.getModel()).getNumber().doubleValue();
    xdescriptor.displayStyle = styleComboBox.getSelectedIndex();
    xdescriptor.interpolation = interpComboBox.getSelectedIndex();
    xdescriptor.edgeVisibility = showEdgesCheckBox.isSelected();
  }

  /**
   *
   */
  public void applyColor(G3DFieldActorDescriptor xdescriptor)
  {
    G3DFieldActorDescriptor descriptor =
      (G3DFieldActorDescriptor) xdescriptor;

    descriptor.scalarVisibility =
      (colorByComboBox.getSelectedIndex() == 1) ? true : false;
    if(!descriptor.scalarVisibility)
    {
      descriptor.solidColor = editSolidColorButton.getBackground();
    }
  }

  /**
   *
   */
  public void applyColorMap(G3DFieldActorDescriptor xdescriptor)
  {
    G3DFieldActorDescriptor descriptor =
      (G3DFieldActorDescriptor) xdescriptor;

    // scalarVisiblity is set by applyColor

    if(descriptor.scalarVisibility)
    {
      RangeLookupTableDescriptor lookupTable =
        (RangeLookupTableDescriptor) descriptor.lookupTable;

      for(int i=0; i<2; i++)
      {
        lookupTable.extremeHues[i] =
          ((SpinnerNumberModel) extremeHueSpinners[i].getModel()).getNumber().doubleValue();

        lookupTable.thresholdSizes[i] =
          ((SpinnerNumberModel) thresholdSizeSpinners[i].getModel()).getNumber().doubleValue();

        lookupTable.thresholdComponents[i] =
          thresholdComponentComboBoxs[i].getSelectedItem().toString();

        lookupTable.componentMethods[i] =
          componentMethodComboBoxs[i].getSelectedItem().toString();

        lookupTable.extremeComponentValues[i] =
          ((SpinnerNumberModel) extremeComponentValueSpinners[i].getModel()).getNumber().doubleValue();

        lookupTable.extremeHueMethods[i] =
          extremeHueMethodComboBoxs[i].getSelectedItem().toString();
      }
    }
  }

  /**
   *
   */
  public void applyLabels(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.pointLabels = pointLabelsComboBox.getSelectedIndex();
    xdescriptor.cellLabels = cellLabelsComboBox.getSelectedIndex();

    // $$HACK: Need to change check box here.
    //viewer.setCellLabelsCheckBoxMenuItem(selectedPointLabels);
  }

  /**
   *
   */
  public void applyPosition(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.position[0] = getFromTextField(xpositionTextField);
    xdescriptor.position[1] = getFromTextField(ypositionTextField);
    xdescriptor.position[2] = getFromTextField(zpositionTextField);
  }

  /**
   *
   */
  public void applyOrigin(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.origin[0] = getFromTextField(xoriginTextField);
    xdescriptor.origin[1] = getFromTextField(yoriginTextField);
    xdescriptor.origin[2] = getFromTextField(zoriginTextField);
  }

  /**
   *
   */
  public void applyOrientation(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.orientation[0] = getFromTextField(xorientationTextField);
    xdescriptor.orientation[1] = getFromTextField(yorientationTextField);
    xdescriptor.orientation[2] = getFromTextField(zorientationTextField);
  }

  /**
   *
   */
  public void applyScale(G3DFieldActorDescriptor xdescriptor)
  {
    xdescriptor.scale[0] = getFromTextField(xscaleTextField);
    xdescriptor.scale[1] = getFromTextField(yscaleTextField);
    xdescriptor.scale[2] = getFromTextField(zscaleTextField);
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
   * Selects the actor color. Applys only when the
   * actor is not being colored by scalar values.
   */
  public void doEditSolidColor()
  {
    Color solidColor = editSolidColorButton.getBackground();
    Color color = JColorChooser.showDialog(this, "Select Actor Solid Color",
                                           solidColor);
    if(color != null && color != solidColor)
    {
      editSolidColorButton.setBackground(color);
    }
  }

  /**
   * Implementation if ItemListener
   */
  public void itemStateChanged(ItemEvent e)
  {
    int index = colorByComboBox.getSelectedIndex();
    setColorEnabled(index == 1);
  }

  /**
   * Set enabled state for the solid color choice.
   */
  public void setColorEnabled(boolean xscalar)
  {
    tabbedPane.setEnabledAt(2, xscalar);

    editSolidColorAction.setEnabled(!xscalar);
    editSolidColorButton.setBackground(xscalar ? getBackground() : solidColor);
  }
}
