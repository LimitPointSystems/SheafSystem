/**
 * Classname: TensorGlyphFieldActorPropertiesPanel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:02 $
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
 */

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
 * values of a <code>TensorGlyphFieldActorDescriptor</code>.
 */
public class TensorGlyphFieldActorPropertiesPanel
      extends G3DFieldActorPropertiesPanel
{
  // GUI FACET

  protected JPanel tensorGlyphPanel;

  protected JComboBox sourceComboBox;
  protected JSpinner scaleFactorSpinner;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  public TensorGlyphFieldActorPropertiesPanel(G3DViewer xviewer,
      FieldActorDescriptor[] xdescriptors)
  {
    super(xviewer, xdescriptors);

    tensorGlyphPanel = createTensorGlyphPanel();

    tabbedPane.addTab("Tensor Glyph", tensorGlyphPanel);

    initValues();
  }

  // CREATE FACET

  /**
   * Create tensor glyph panel
   */
  protected JPanel createTensorGlyphPanel()
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Tensor Glyph:")));

    //=====

    result.add(Box.createVerticalGlue());

    JPanel panel = new JPanel();
    JLabel sourceLabel = new JLabel("Source:", JLabel.RIGHT);
    sourceLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    sourceComboBox = new JComboBox(ViewerConstants.SOURCES);

    panel.add(sourceLabel);
    panel.add(sourceComboBox);

    result.add(panel);

    result.add(Box.createVerticalGlue());

    //=====

    result.add(Box.createVerticalGlue());

    panel = new JPanel();
    JLabel scaleFactorLabel = new JLabel("Scale Factor: ", JLabel.RIGHT);
    scaleFactorLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

    SpinnerModel scaleFactorModel = new SpinnerNumberModel(1.0, 0.0,
                                    10000.0, 0.01);

    scaleFactorSpinner = new JSpinner(scaleFactorModel);

    panel.add(scaleFactorLabel);
    panel.add(scaleFactorSpinner);

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

    TensorGlyphFieldActorDescriptor actor =
      (TensorGlyphFieldActorDescriptor) descriptors[0];

    initTensorGlyphPanel(actor);
  }

  /**
   *
   */
  protected void initTensorGlyphPanel(TensorGlyphFieldActorDescriptor actor)
  {
    sourceComboBox.setSelectedItem(actor.source);
    scaleFactorSpinner.setValue(actor.scaleFactor);
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

        TensorGlyphFieldActorDescriptor actor;

        for(int i=0; i<descriptors.length; i++)
        {
          actor = (TensorGlyphFieldActorDescriptor) descriptors[i];

          applyTensorGlyph(actor);
        }
      }
    }

    super.doApply(false);
  }

  /**
   *
   */
  public void applyTensorGlyph(TensorGlyphFieldActorDescriptor actor)
  {
    actor.source = (String) sourceComboBox.getSelectedItem();
    actor.scaleFactor = ((SpinnerNumberModel)scaleFactorSpinner.getModel()).getNumber().doubleValue();
  }
}
