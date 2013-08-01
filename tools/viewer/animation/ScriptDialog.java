
/**
 * Classname: ScriptDialog
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:56 $
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

package tools.viewer.animation;

import tools.common.gui.*;
import tools.viewer.common.*;
import tools.viewer.user.*;
import tools.viewer.render.*;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * Dialog for creating the <code>Script</code>.
 */
public class ScriptDialog extends GenericDialog
{
  // VALUE FACET

  public static final String LONG  = "Long Way";
  public static final String SHORT = "Short Way";

  // GUI FACET

  /**
   * The viewer
   */
  protected Viewer viewer;

  /**
   * The minimum animation time text field.
   */
  protected JTextField minTextField;

  /**
   * The maximum animation time text field.
   */
  protected JTextField maxTextField;

  /**
   * The unit of time text field.
   */
  protected JTextField unitTextField;

  /**
   * The animation scenes text field.
   */
  protected JTextField scenesTextField;

  /**
   * The scene rate text field
   */
  protected JTextField rateTextField;

  /**
   * The interpolation check box
   */
  protected JComboBox interpolationComboBox;

  /**
   * Constructor
   *
   * @param xviewer The viewer
   */
  public ScriptDialog(Viewer xviewer)
  {
    super(xviewer, "Create Script");

    setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);

    viewer = xviewer;

    // Create the text fields

    Script script = viewer.getScript();
    minTextField = new JTextField(Double.toString(script.minTime));
    minTextField.setColumns(8);

    maxTextField = new JTextField(Double.toString(script.maxTime));
    maxTextField.setColumns(8);

    unitTextField = new JTextField(script.unit);
    unitTextField.setColumns(8);

    scenesTextField = new JTextField(Integer.toString(script.size()));
    scenesTextField.setColumns(6);

    rateTextField = new JTextField(Double.toString(script.rate));
    rateTextField.setColumns(8);

    String[] data = { SHORT, LONG };
    interpolationComboBox = new JComboBox(data);
    interpolationComboBox.setSelectedIndex(script.interpolation);

    // Layout the rows

    Box minBox = Box.createHorizontalBox();
    JLabel label = new JLabel("Minimum Time:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    minBox.add(label);
    minBox.add(minTextField);
    minBox.add(Box.createHorizontalGlue());

    Box maxBox = Box.createHorizontalBox();
    label = new JLabel("Maximum Time:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    maxBox.add(label);
    maxBox.add(maxTextField);
    maxBox.add(Box.createHorizontalGlue());

    Box unitBox = Box.createHorizontalBox();
    label = new JLabel("Unit of Time:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    unitBox.add(label);
    unitBox.add(unitTextField);
    unitBox.add(Box.createHorizontalGlue());

    Box scenesBox = Box.createHorizontalBox();
    label = new JLabel("# of Scenes:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    scenesBox.add(label);
    scenesBox.add(scenesTextField);
    scenesBox.add(Box.createHorizontalGlue());

    Box rateBox = Box.createHorizontalBox();
    label = new JLabel("Scene Rate:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    rateBox.add(label);
    rateBox.add(rateTextField);
    rateBox.add(new JLabel("scenes/sec"));
    rateBox.add(Box.createHorizontalGlue());

    Box interpolationBox = Box.createHorizontalBox();
    label = new JLabel("Interpolate:");
    label.setPreferredSize(new Dimension(104, 24));
    label.setMaximumSize(new Dimension(104, 24));
    label.setMinimumSize(new Dimension(104, 24));
    interpolationBox.add(label);
    interpolationBox.add(interpolationComboBox);

    // Layout this dialog

    JPanel panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

    Box box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(minBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(maxBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(unitBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(scenesBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(rateBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(6));
    box.add(interpolationBox);
    box.add(Box.createHorizontalStrut(6));

    panel.add(Box.createVerticalStrut(3));
    panel.add(box);
    panel.add(Box.createVerticalStrut(3));

    addPane(panel, 0);
  }

  public void cancelPressed()
  {
    setVisible(false);
    dispose();
  }

  public void okPressed()
  {
    // Accumulate the values from the gui and warn the user
    // on errors.

    Script script = new Script(viewer);
    int scenes = 1;

    try
    {
      script.minTime = Double.parseDouble(minTextField.getText().trim());
    }
    catch(Exception e)
    {
      JOptionPane.showMessageDialog(this,
                                    "Invalid Minimum Time: " +
                                    minTextField.getText().trim(),
                                    "Invalud Min",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    try
    {
      script.maxTime = Double.parseDouble(maxTextField.getText().trim());
    }
    catch(Exception e)
    {
      JOptionPane.showMessageDialog(this,
                                    "Invalid Maximum Time: " +
                                    maxTextField.getText().trim(),
                                    "Invalud Max",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    if(script.minTime > script.maxTime)
    {
      JOptionPane.showMessageDialog(this,
                                    "Maximum Time must be greater or equal to Minimum Time.",
                                    "Invalid Time Range",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    try
    {
      scenes = Integer.parseInt(scenesTextField.getText().trim());
    }
    catch(Exception e)
    {
      JOptionPane.showMessageDialog(this,
                                    "Invalid # of Scenes: " +
                                    scenesTextField.getText().trim(),
                                    "Invalid Scenes",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    if(scenes < 1)
    {
      JOptionPane.showMessageDialog(this,
                                    "At least one scene is needed.",
                                    "Invalid # of Scenes",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    if((script.minTime == script.maxTime) && scenes > 1)
    {
      JOptionPane.showMessageDialog(this,
                                    "A single scene is required if\n" +
                                    "min and max times are equal.",
                                    "Need Single Scene",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    try
    {
      script.rate = Double.parseDouble(rateTextField.getText().trim());
    }
    catch(Exception e)
    {
      JOptionPane.showMessageDialog(this,
                                    "Invalid Scene Rate: " +
                                    rateTextField.getText().trim(),
                                    "Invalud Scene Rate",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    script.unit = unitTextField.getText().trim();

    if(script.rate <= 0.0)
    {
      JOptionPane.showMessageDialog(this,
                                    "Scene Rate must be greater than zero.",
                                    "Invalid Scene Rate",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    String value = (String) interpolationComboBox.getSelectedItem();
    if(value == SHORT)
      script.interpolation = ViewerConstants.SHORT_INTERPOLATION;
    else
      script.interpolation = ViewerConstants.LONG_INTERPOLATION;

    // Create the scenes.

    double increment = 0.0;
    if(scenes > 1)
      increment = (script.maxTime - script.minTime)/(double) (scenes-1);

    double time = script.minTime;
    SceneDescriptor scene;
    for(int i=0; i<scenes; i++)
    {
      scene = viewer.getScene().clone();
      scene.selected = false;
      scene.scene = i;
      scene.keyFrame = false;

      scene.setTime(time);

      // Add scene to script.

      script.add(scene);

      // Increment the time.  Because of rounding
      // issues, make sure the last scene is at
      // the max time.

      if(i==scenes-2)
        time = script.maxTime;
      else
        time += increment;
    }

    // Automatically interpolate if there is more than two scenes
    // and long interpolation is used.

    if(script.size() > 2 &&
        script.interpolation == ViewerConstants.LONG_INTERPOLATION)
    {
      script.get(0).keyFrame = true;
      script.get(script.size()-1).keyFrame = true;

      script.interpolate();

      script.get(0).keyFrame = false;
      script.get(script.size()-1).keyFrame = false;
    }

    // Select the first scene.

    script.get(0).selected = true;

    // Set the script

    viewer.setScript(script);

    // Close the dialog

    setVisible(false);
    dispose();
  }
}

