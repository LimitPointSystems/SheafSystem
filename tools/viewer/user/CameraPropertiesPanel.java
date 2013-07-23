/**
 * Classname: CameraPropertiesPanel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

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
 * values of a <code>CameraDescriptor</code>.
 */
public class CameraPropertiesPanel extends PropertiesPanel
{
  // DEFAULT VALUE FACET

  // VIEWER FACET

  /**
   * The cameras descriptors to edit.
   */
  protected CameraDescriptor[] cameras;

  // GUI FACET

  protected JTextField latPositionTextField;
  protected JTextField lonPositionTextField;
  protected JTextField distPositionTextField;

  protected JTextField xfocalPointTextField;
  protected JTextField yfocalPointTextField;
  protected JTextField zfocalPointTextField;

  protected JTextField xviewUpTextField;
  protected JTextField yviewUpTextField;
  protected JTextField zviewUpTextField;

  protected JCheckBox resetViewCheckBox;

  protected JRadioButton perspectiveRadioButton;
  protected JRadioButton orthogonalRadioButton;

  protected JButton editBackgroundColorButton;
  protected Action editBackgroundColorAction;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  public CameraPropertiesPanel(G3DViewer xviewer)
  {
    super(xviewer);

    tabbedPane.addTab("Position", createPositionPanel());
    tabbedPane.addTab("Focal Point", createFocalPointPanel());
    tabbedPane.addTab("View Up", createViewUpPanel());
    tabbedPane.addTab("Options", createOptionsPanel());
  }

  /**
   * Set the cameras.
   */
  public void setCameras(CameraDescriptor[] xcameras)
  {
    cameras = xcameras;

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
    xfocalPointTextField = new JTextField();
    yfocalPointTextField = new JTextField();
    zfocalPointTextField = new JTextField();

    return createXYZPanel("Focal Point", xfocalPointTextField,
                          yfocalPointTextField, zfocalPointTextField);
  }

  /**
   *
   */
  protected JPanel createViewUpPanel()
  {
    xviewUpTextField = new JTextField();
    yviewUpTextField = new JTextField();
    zviewUpTextField = new JTextField();

    return createXYZPanel("View Up", xviewUpTextField,
                          yviewUpTextField, zviewUpTextField);
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

    // Create camera view panel

    resetViewCheckBox = new JCheckBox("Auto View");

    JPanel panel = new JPanel();
    panel.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Camera View:")));
    panel.add(resetViewCheckBox);

    result.add(panel);

    // Create projection panel

    ButtonGroup group = new ButtonGroup();

    perspectiveRadioButton = new JRadioButton("Perspective");
    orthogonalRadioButton = new JRadioButton("Orthogonal");

    panel = new JPanel();
    panel.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Projections:")));
    panel.add(perspectiveRadioButton);
    group.add(perspectiveRadioButton);
    panel.add(orthogonalRadioButton);
    group.add(orthogonalRadioButton);

    result.add(panel);

    // Create background color panel

    JLabel label = new JLabel("Edit Color: ", JLabel.CENTER);
    label.setAlignmentX(Component.CENTER_ALIGNMENT);


    editBackgroundColorAction = new GenericAction(this,
                                "EditColorAction",
                                "doEditBackgroundColor",
                                "        ",
                                "Select the representation's color",
                                null, null, null, "true");

    editBackgroundColorButton = new JButton(editBackgroundColorAction);
    editBackgroundColorButton.setBackground(Color.white);
    editBackgroundColorButton.setSize(50, 20);

    panel = new JPanel();
    panel.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder("Background Color:")));
    panel.add(label);
    panel.add(editBackgroundColorButton);

    result.add(panel);


    return result;
  }

  // INITIALIZE FACET

  public void initValues()
  {
    // For multiple cameras selection, we use the first one in the list
    // for the initial values.

    CameraDescriptor camera = cameras[0];

    double[] polar = new double[3];
    LPSMath.xyzToPolar(camera.position, polar);

    addToTextField(polar[0], latPositionTextField);
    addToTextField(polar[1], lonPositionTextField);
    addToTextField(polar[2], distPositionTextField);

    addToTextField(camera.focalPoint[0], xfocalPointTextField);
    addToTextField(camera.focalPoint[1], yfocalPointTextField);
    addToTextField(camera.focalPoint[2], zfocalPointTextField);

    addToTextField(camera.viewUp[0], xviewUpTextField);
    addToTextField(camera.viewUp[1], yviewUpTextField);
    addToTextField(camera.viewUp[2], zviewUpTextField);

    if(camera.projection)
      orthogonalRadioButton.setSelected(true);
    else
      perspectiveRadioButton.setSelected(true);

    editBackgroundColorButton.setBackground(camera.background);

    // Can only reset the view when only the selected camera
    // is being edited.

    if(cameras.length == 1 && camera.selected)
      resetViewCheckBox.setEnabled(true);
    else
      resetViewCheckBox.setEnabled(false);
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

        CameraDescriptor camera;

        for(int i=0; i<cameras.length; i++)
        {
          camera = cameras[i];

          double[] polar = new double[3];

          polar[0] = getFromTextField(latPositionTextField);
          polar[1] = getFromTextField(lonPositionTextField);
          polar[2] = getFromTextField(distPositionTextField);

          LPSMath.polarToXYZ(polar, camera.position);

          camera.focalPoint[0] = getFromTextField(xfocalPointTextField);
          camera.focalPoint[1] = getFromTextField(yfocalPointTextField);
          camera.focalPoint[2] = getFromTextField(zfocalPointTextField);

          camera.viewUp[0] = getFromTextField(xviewUpTextField);
          camera.viewUp[1] = getFromTextField(yviewUpTextField);
          camera.viewUp[2] = getFromTextField(zviewUpTextField);

          camera.projection = orthogonalRadioButton.isSelected();

          camera.background = editBackgroundColorButton.getBackground();
        }
      }
    }

    // Update the clients of the viewer

    viewer.updateClients(resetViewCheckBox.isSelected());

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
    if(xfield == latPositionTextField ||
        xfield == lonPositionTextField ||
        xfield == distPositionTextField)
    {
      if(xfield == latPositionTextField)
      {
        double value = getFromTextField(latPositionTextField);

        if(value > 85.0 || value < -85.0)
        {
          JOptionPane.showMessageDialog(this,
                                        "Latitude value must be between 85 and -85 degrees.",
                                        "Invalid Latitude",
                                        JOptionPane.ERROR_MESSAGE);

          return false;
        }
      }
      else if(xfield == lonPositionTextField)
      {
        double value = getFromTextField(lonPositionTextField);

        if(value > 180.0 || value < -180.0)
        {
          JOptionPane.showMessageDialog(this,
                                        "Longitude value must be between 180 and -180 degrees.",
                                        "Invalid Longitude",
                                        JOptionPane.ERROR_MESSAGE);

          return false;
        }
      }
    }

    return true;
  }

  /**
   * Selects the rep color. Applys only when the
   * rep is not being colored by scalar values.
   */
  public void doEditBackgroundColor()
  {
    Color backgroundColor = editBackgroundColorButton.getBackground();
    Color color = JColorChooser.showDialog(this, "Select Background Color",
                                           backgroundColor);
    if(color != null && color != backgroundColor)
    {
      editBackgroundColorButton.setBackground(color);
    }
  }
}
