
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

import tools.viewer.render.*;
import tools.common.gui.*;
import tools.common.util.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.text.*;

/**
 * Implementation of <code>PropertiesPanel</code> for editing the
 * values of a <code>LightDescriptor</code>.
 */
public class LightPropertiesPanel extends PropertiesPanel
{
  // DEFAULT VALUE FACET

  // DESCRIPTOR FACET

  /**
   * The light descriptors to edit.
   */
  protected LightDescriptor[] lights;

  // GUI FACET

  protected JPanel positionPanel;
  protected JPanel focalPointPanel;
  protected JPanel optionsPanel;

  protected JTextField latPositionTextField;
  protected JTextField lonPositionTextField;
  protected JTextField distPositionTextField;

  protected JTextField latFocalPointTextField;
  protected JTextField lonFocalPointTextField;
  protected JTextField distFocalPointTextField;

  protected JRadioButton onRadioButton;
  protected JRadioButton offRadioButton;
  protected Action editColorAction;
  protected JButton editColorButton;
  protected JSpinner intensitySpinner;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  public LightPropertiesPanel(G3DViewer xviewer)
  {
    super(xviewer);

    positionPanel = createPositionPanel();
    focalPointPanel = createFocalPointPanel();
    optionsPanel = createOptionsPanel();

    tabbedPane.addTab("Position", positionPanel);
    tabbedPane.addTab("Focal Point", focalPointPanel);
    tabbedPane.addTab("Options", optionsPanel);
  }

  /**
   * Set the lights.
   */
  public void setLights(LightDescriptor[] xlights)
  {
    lights = xlights;
    initValues();
  }

  // CREATE FACET

  /**
   *
   */
  protected JPanel createPositionPanel()
  {
    latPositionTextField = new JTextField();
    lonPositionTextField = new JTextField();
    distPositionTextField = new JTextField();

    return createPolarPanel("Position", latPositionTextField,
                            lonPositionTextField, distPositionTextField);
  }

  /**
   *
   */
  protected JPanel createFocalPointPanel()
  {
    latFocalPointTextField = new JTextField();
    lonFocalPointTextField = new JTextField();
    distFocalPointTextField = new JTextField();

    return createPolarPanel("Focal Point", latFocalPointTextField,
                            lonFocalPointTextField, distFocalPointTextField);
  }

  /**
   *
   */
  protected JPanel createOptionsPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Options:")));

    result.add(createSwitchPanel());
    result.add(createColorPanel());
    result.add(createIntensityPanel());

    return result;
  }

  /**
   *
   */
  protected JPanel createSwitchPanel()
  {
    JPanel result = new JPanel();
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Light Switch:")));

    ButtonGroup group = new ButtonGroup();

    onRadioButton = new JRadioButton("On");
    result.add(onRadioButton);
    group.add(onRadioButton);

    offRadioButton = new JRadioButton("Off");
    result.add(offRadioButton);
    group.add(offRadioButton);

    return result;
  }

  /**
   *
   */
  protected JPanel createColorPanel()
  {
    JPanel result = new JPanel();
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Light Color:")));

    JLabel label = new JLabel("Color: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);
    result.add(label);

    editColorAction = new GenericAction(this,
                                        "EditColorAction",
                                        "doEditColor",
                                        "        ",
                                        "Select the light color",
                                        null, null, null, "true");

    editColorButton = new JButton(editColorAction);
    editColorButton.setSize(50, 20);
    result.add(editColorButton);

    return result;
  }

  /**
   *
   */
  protected JPanel createIntensityPanel()
  {
    JPanel result = new JPanel();
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Light Intensity:")));

    JLabel label = new JLabel("Intensity: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);
    result.add(label);

    intensitySpinner = new JSpinner(new SpinnerNumberModel(1.0, 0.0, 1.0, 0.05));
    intensitySpinner.setPreferredSize(new Dimension(50, 30));
    result.add(intensitySpinner);

    return result;
  }

  // INITIALIZE FACET

  public void initValues()
  {
    // For multiple light selection, we use the first one in the list
    // for the initial values.

    LightDescriptor light = lights[0];

    double[] polar = new double[3];
    LPSMath.xyzToPolar(light.position, polar);

    addToTextField(polar[0], latPositionTextField);
    addToTextField(polar[1], lonPositionTextField);
    addToTextField(polar[2], distPositionTextField);

    LPSMath.xyzToPolar(light.focalPoint, polar);

    addToTextField(polar[0], latFocalPointTextField);
    addToTextField(polar[1], lonFocalPointTextField);
    addToTextField(polar[2], distFocalPointTextField);

    if(light.switchOn)
      onRadioButton.setSelected(true);
    else
      offRadioButton.setSelected(true);

    editColorButton.setBackground(light.color);

    intensitySpinner.setValue(light.intensity);

    if(containsCameraLight())
    {
      tabbedPane.setEnabledAt(0, false);
      tabbedPane.setEnabledAt(1, false);
      tabbedPane.setSelectedIndex(2);
    }
    else
    {
      tabbedPane.setEnabledAt(0, true);
      tabbedPane.setEnabledAt(1, true);
    }
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
        // Copy the values from the user interface.

        LightDescriptor light;
        boolean copyView = !containsCameraLight();

        for(int i=0; i<lights.length; i++)
        {
          light = lights[i];
          if(copyView)
          {
            double[] polar = new double[3];

            polar[0] = getFromTextField(latPositionTextField);
            polar[1] = getFromTextField(lonPositionTextField);
            polar[2] = getFromTextField(distPositionTextField);

            LPSMath.polarToXYZ(polar, light.position);

            polar[0] = getFromTextField(latFocalPointTextField);
            polar[1] = getFromTextField(lonFocalPointTextField);
            polar[2] = getFromTextField(distFocalPointTextField);

            LPSMath.polarToXYZ(polar, light.focalPoint);
          }

          light.switchOn = onRadioButton.isSelected();

          light.color = editColorButton.getBackground();

          light.intensity = ((Double) intensitySpinner.getValue()).doubleValue();
        }
      }
    }

    // Update the clients of the viewer

    viewer.updateClients();

    // Update the values of this panel.

    viewer.updatePropertiesPanel(this);
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
   * Selects the light color.
   */
  public void doEditColor()
  {
    Color currentColor = editColorButton.getBackground();
    Color color = JColorChooser.showDialog(this, "Select Light Color",
                                           currentColor);
    if(color != null && color != currentColor)
    {
      editColorButton.setBackground(color);
    }
  }

  /**
   * Returns wether the lights of this panel contain the camera light
   * of the viewer.
   */
  public boolean containsCameraLight()
  {
    for(int i=0; i<lights.length; i++)
    {
      if(lights[i].cameraLight)
        return true;
    }

    return false;
  }
}
