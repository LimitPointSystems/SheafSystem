
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
 * Implementation of <code>G3DFieldActorPropertiesPanel</code> for editing the
 * values of a <code>HedgeHogFieldActorDescriptor</code>.
 */
public class HedgeHogFieldActorPropertiesPanel
      extends G3DFieldActorPropertiesPanel
{
  // CONSTANTS FACET

  protected static final String[] VECTOR_MODES =
    { ViewerConstants.VECTOR_MAGNITUDE,
      ViewerConstants.VECTOR_NORMAL };

  // GUI FACET

  protected JPanel hedgeHogPanel;

  protected JSpinner scaleFactorSpinner;
  protected JComboBox vectorModeComboBox;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  public HedgeHogFieldActorPropertiesPanel(G3DViewer xviewer,
      FieldActorDescriptor[] xdescriptors)
  {
    super(xviewer, xdescriptors);

    hedgeHogPanel = createHedgeHogPanel();

    tabbedPane.addTab("Hedge Hog", hedgeHogPanel);

    initValues();
  }

  // CREATE FACET

  /**
   * Create hedge hog panel
   */
  protected JPanel createHedgeHogPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Hedge Hog:")));

    //=====

    result.add(Box.createVerticalGlue());

    JPanel panel = new JPanel();
    JLabel scaleFactorLabel = new JLabel("Scale Factor: ", JLabel.RIGHT);
    scaleFactorLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    SpinnerModel scaleFactorModel = new SpinnerNumberModel(1.0, 0.0,
                                    10000000.0, 0.01);

    scaleFactorSpinner = new JSpinner(scaleFactorModel);

    panel.add(scaleFactorLabel);
    panel.add(scaleFactorSpinner);

    result.add(panel);

    result.add(Box.createVerticalGlue());

    //=====

    panel = new JPanel();
    JLabel vectorModeLabel = new JLabel("Vector Mode:", JLabel.RIGHT);
    vectorModeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    vectorModeComboBox = new JComboBox(VECTOR_MODES);

    panel.add(vectorModeLabel);
    panel.add(vectorModeComboBox);

    result.add(panel);

    result.add(Box.createVerticalGlue());

    //=====

    return result;
  }

  // INITIALIZE FACET

  /**
   *
   */
  public void initValues()
  {
    super.initValues();

    // Use the first actor in the list to initialize the
    // user interface.

    HedgeHogFieldActorDescriptor actor =
      (HedgeHogFieldActorDescriptor) descriptors[0];

    initHedgeHogPanel(actor);
  }

  /**
   *
   */
  protected void initHedgeHogPanel(HedgeHogFieldActorDescriptor actor)
  {
    scaleFactorSpinner.setValue(actor.scaleFactor);
    vectorModeComboBox.setSelectedItem(actor.vectorMode);
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

        HedgeHogFieldActorDescriptor actor;

        for(int i=0; i<descriptors.length; i++)
        {
          actor = (HedgeHogFieldActorDescriptor) descriptors[i];

          applyHedgeHog(actor);
        }
      }
    }

    super.doApply(false);
  }

  /**
   *
   */
  public void applyHedgeHog(HedgeHogFieldActorDescriptor actor)
  {
    actor.scaleFactor = ((SpinnerNumberModel)scaleFactorSpinner.getModel()).getNumber().doubleValue();
    actor.vectorMode = (String) vectorModeComboBox.getSelectedItem();
  }
}
