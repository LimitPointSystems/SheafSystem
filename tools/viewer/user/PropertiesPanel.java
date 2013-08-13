/**
 * Classname: PropertiesPanel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:02 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.text.*;
import tools.common.gui.*;
import vtk.*;

/**
 *
 */
public abstract class PropertiesPanel extends JPanel
{
  // VIEWER FACET

  /**
   * The viewer.
   */
  protected Viewer viewer;

  /**
   * The dialog.
   */
  protected PropertiesDialog dialog;

  // GUI FACET

  protected JTabbedPane tabbedPane = new JTabbedPane();
  protected Action applyAction;
  protected Action cancelAction;

  // CONSTRUCTORS

  /**
   *
   */
  protected PropertiesPanel(Viewer xviewer)
  {
    viewer = xviewer;

    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

    this.add(tabbedPane);
    this.add(Box.createVerticalGlue());
    this.add(createApplyButtonPanel());
  }

  // DIALOG FACET

  /**
   * The dialog.
   */
  public void setDialog(PropertiesDialog xdialog)
  {
    dialog = xdialog;  
  }

  /**
   * Set the wait state of the dialog.
   */
  public void setWaitState(boolean xstate)
  {
    dialog.setWaitState(xstate);
  }

  // VIEWER FACET

  // GUI FACET

  /**
   *
   */
  protected JPanel createApplyButtonPanel()
  {
    applyAction = new GenericAction(this, "ApplyAction", "doApply", "Apply",
                                    null, null, null, null, "true");
    cancelAction = new GenericAction(this, "CancelAction", "doCancel", "Cancel",
                                     null, null, null, null, "true");

    JPanel result = new JPanel();
    result.setBorder(BorderFactory.createEmptyBorder(6, 12, 6, 12));

    result.add(new JButton(applyAction));
    result.add(new JButton(cancelAction));

    return result;
  }

  /**
   *
   */
  protected JPanel createXYZPanel(String title, JTextField xfield,
                                  JTextField yfield, JTextField zfield)
  {
    return createXYZPanel(title, "", xfield, yfield, zfield);
  }

  /**
   *
   */
  protected JPanel createXYZPanel(String title, String prefix, JTextField xfield,
                                  JTextField yfield, JTextField zfield)
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder(title + ":")));

    // Create the x panel.

    JPanel panel = new JPanel();

    JLabel label = new JLabel(prefix + "X: ");
    xfield.setPreferredSize(new Dimension(150, 30));
    xfield.addFocusListener(new TextFieldFocusListener(this, title, prefix + "X"));

    panel.add(label);
    panel.add(xfield);

    result.add(panel);

    // Create the y panel.

    panel = new JPanel();

    label = new JLabel(prefix + "Y: ");
    yfield.setPreferredSize(new Dimension(150, 30));
    yfield.addFocusListener(new TextFieldFocusListener(this, title, prefix + "Y"));

    panel.add(label);
    panel.add(yfield);

    result.add(panel);

    // Create the z panel.

    panel = new JPanel();

    label = new JLabel(prefix + "Z: ");
    zfield.setPreferredSize(new Dimension(150, 30));
    zfield.addFocusListener(new TextFieldFocusListener(this, title, prefix + "Z"));

    panel.add(label);
    panel.add(zfield);

    result.add(panel);

    return result;
  }

  /**
   *
   */
  protected JPanel createPolarPanel(String title, JTextField latField,
                                    JTextField lonField, JTextField disField)
  {
    return createPolarPanel(title, "", latField, lonField, disField);
  }

  /**
   *
   */
  protected JPanel createPolarPanel(String title, String prefix, JTextField latField,
                                    JTextField lonField, JTextField disField)
  {
    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
    result.setBorder(
      BorderFactory.createCompoundBorder(
        BorderFactory.createEmptyBorder(6, 12, 6, 12),
        BorderFactory.createTitledBorder(title + ":")));

    // Create the latitude panel.

    JPanel panel = new JPanel();

    JLabel label = new JLabel(prefix + "Latitude: ");
    label.setPreferredSize(new Dimension(80, 30));
    latField.setPreferredSize(new Dimension(150, 30));
    latField.addFocusListener(new TextFieldFocusListener(this, title, prefix + "Latitude"));

    panel.add(label);
    panel.add(latField);

    result.add(panel);

    // Create the longitude panel.

    panel = new JPanel();

    label = new JLabel(prefix + "Longitude: ");
    label.setPreferredSize(new Dimension(80, 30));
    lonField.setPreferredSize(new Dimension(150, 30));
    lonField.addFocusListener(new TextFieldFocusListener(this, title, prefix + "Longitude"));

    panel.add(label);
    panel.add(lonField);

    result.add(panel);

    // Create the distance panel.

    panel = new JPanel();

    label = new JLabel(prefix + "Distance: ");
    label.setPreferredSize(new Dimension(80, 30));
    disField.setPreferredSize(new Dimension(150, 30));
    disField.addFocusListener(new TextFieldFocusListener(this, title, prefix + "Distance"));

    panel.add(label);
    panel.add(disField);

    result.add(panel);

    return result;
  }

  // CONVIENCE FACET

  /**
   * Adds a double to a JTextField.  Rounds the number off after four decimal places.
   */
  protected void addToTextField(double xvalue, JTextField xfield)
  {
    //String str = Double.toString(xvalue);
    //int dec = str.indexOf(".");
    //if(dec >= 0 && (dec+5) < str.length())
    //  str = str.substring(0, dec+5);

    //xfield.setText(str);

    NumberFormat format = NumberFormat.getNumberInstance();
    format.setMaximumIntegerDigits(20);
    format.setMaximumFractionDigits(5);

    xfield.setText(format.format(xvalue));
  }

  /**
   * Get formatted double from a text field
   */
  protected double getFromTextField(JTextField xfield)
  {
    NumberFormat format = NumberFormat.getNumberInstance();

    try
    {
      return format.parse(xfield.getText()).doubleValue();
    }
    catch(java.text.ParseException e)
    {
      return Double.NaN;
    }
  }

  // LISTENER FACET

  /**
   * Class that listens to the focus of a text field and resets the value on focusLost if
   * the given value is not a valid double.
   */
  protected class TextFieldFocusListener implements FocusListener
  {
    /**
     * The original value
     */
    protected String originalValue;

    /**
     * The component used to open up the error dialog.
     */
    protected JComponent component;

    /**
     * The title of the XYZ panel.
     */
    protected String title;

    /**
     * The coordinate value.
     */
    protected String coord;

    /**
     * Default constructor.
     */
    public TextFieldFocusListener(JComponent xcomponent, String xtitle, String xcoord)
    {
      component = xcomponent;
      title = xtitle;
      coord = xcoord;
    }

    /**
     * 
     */
    public void focusGained(FocusEvent e)
    {
      originalValue = ((JTextField) e.getComponent()).getText();
    }

    /**
     * 
     */
    public void focusLost(FocusEvent e)
    {
      JTextField field = (JTextField) e.getComponent();
      double test = getFromTextField(field);

      if(test == Double.NaN)
      {
        JOptionPane.showMessageDialog(component, "Invalid " + coord + " " + title + " Value",
                                      "Invalid Value", JOptionPane.ERROR_MESSAGE);

        field.setText(originalValue);
      }
      else
      {
        if(!valueChanged(field))
          field.setText(originalValue);
      }
    }
  }

  // ACTION FACET

  public abstract void initValues();

  /**
   * The value of xfield has changed.  Returns true if the changed value
   * is valid.
   */
  public abstract void doApply();

  /**
   *
   */
  public abstract boolean valueChanged(JTextField xfield);

  /**
   *
   */
  public void doCancel()
  {
    initValues();
  }
}
