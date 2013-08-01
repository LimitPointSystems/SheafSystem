/**
 * Classname: ProbePanel
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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.text.*;

/**
 *
 */
public class ProbePanel extends JPanel
      implements ItemListener, KeyListener, ActionListener
{
  protected G3DViewer viewer;
  protected Screen screen;

  protected JTextArea textArea;
  protected JPanel buttonPanel;

  protected JToggleButton probeButton;
  protected String startProbeString = "Start Probe";
  protected String endProbeString = "End Probe";

  protected boolean mode = false;

  protected double[] pickerPosition;

  public static final NumberFormat formatter = new DecimalFormat("0.00000000");
  public static final String endl = System.getProperty("line.separator");

  public ProbePanel(G3DViewer xviewer)
  {
    viewer = xviewer;
    screen = viewer.getScreen();

    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

    buttonPanel = new JPanel();

    probeButton = new JToggleButton(startProbeString);
    probeButton.addItemListener(this);
    buttonPanel.add(probeButton);

    JButton clearButton = new JButton("Clear");
    clearButton.addActionListener(this);
    buttonPanel.add(clearButton);

    textArea = new JTextArea(10, 40);
    textArea.setFont(new Font("MonoSpaced", Font.BOLD, 14));

    JScrollPane scrollPane =
      new JScrollPane(textArea,
                      JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                      JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

    TitledBorder border = BorderFactory.createTitledBorder("Probe Results:");
    scrollPane.setBorder(border);

    textArea.setEditable(false);

    textArea.setText(endl);
    textArea.append("Probe result area:" + endl);
    textArea.setText(endl);
    textArea.append("Press \"Start Probe\" to begin." + endl);
    textArea.append("Press \"End Probe\" button to stop." + endl);
    textArea.append("To probe, move the cursor to the desired" + endl);
    textArea.append("position and press the \"p\" key." + endl);
    textArea.append("The position in user coordinates will" + endl);
    textArea.append("appear below." + endl);
    textArea.append(endl);

    add
      (buttonPanel);
    add
      (scrollPane);

    screen.addKeyListener(this);
  }

  public void setPickerPosition(double[] xpickerPosition)
  {
    pickerPosition = xpickerPosition;
  }

  public void itemStateChanged(ItemEvent e)
  {
    if(e.getStateChange() == ItemEvent.SELECTED)
    {
      startProbe();
    }
    else //ItemEvent.DESELECTED
    {
      endProbe();
    }
  }

  public void startProbe()
  {
    //System.out.println("ProbePanel.startProbe");

    probeButton.setText(endProbeString);
    probeButton.setSelected(true);

    mode = true;

    // Use crosshair cursor for additional feedback.

    screen.setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
    setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
  }

  public void endProbe()
  {
    //System.out.println("ProbePanel.endProbe");

    probeButton.setText(startProbeString);
    probeButton.setSelected(false);

    mode = false;

    // Set cursor back to the default.

    screen.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
  }


  public void actionPerformed(ActionEvent e)
  {
    // Event can only as be from the clear button. So we don't have to check.
    // Just "clear" the text area.

    textArea.setText(null);
  }

  /**
   *
   */
  public void keyPressed(KeyEvent e)
  {
    if(mode)
    {
      // Forward the keypress to the renderer.

      synchronized (this)
      {
        screen.keyPressed(e);

        // Wait for the render thread to notify this panel
        // with the updated picker position.

        try
        {
          wait();
        }
        catch(InterruptedException ex)
        {}
      }

      // Try to make the output pretty.

      if(pickerPosition != null)
      {

        String x = formatter.format(pickerPosition[0]);
        if(pickerPosition[0] >= 0.0)
          x = " " + x;

        String y = formatter.format(pickerPosition[1]);
        if(pickerPosition[1] >= 0.0)
          y = " " + y;

        String z = formatter.format(pickerPosition[2]);
        if(pickerPosition[2] >= 0.0)
          z = " " + z;

        textArea.append("x=" + x + ", " +
                        "y=" + y + ", " +
                        "z=" + z + endl);
      }
      else
      {
        textArea.append("Nothing picked." + endl);
      }
    }
  }


  /**
   *
   */
  public void keyTyped(KeyEvent e)
  {}

  /**
   *
   */
  public void keyReleased(KeyEvent e)
  {}
}
