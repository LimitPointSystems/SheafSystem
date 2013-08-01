
/**
 * Classname: TimeSlider
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

import bindings.java.*;
import tools.viewer.user.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.reflect.*;
import javax.swing.event.*;
import javax.swing.*;
import vtk.*;

/**
 *
 * <code>JPanel</code> with a slider and spinners which controls the
 * time of an animation.
 *
 */
public class TimeSlider extends JPanel
{
  /**
   * Precision value for converting between double and int
   */
  public static final double PERCISION = 100.0;

  /**
   * The step size of the spinners
   */
  public static final double STEP_SIZE = 1/PERCISION;

  /**
   * The <code>Viewer</code>
   */
  private Viewer viewer;

  /**
   * The script
   */
  private Script script;

  /**
   * The start value spinner
   */
  private JSpinner start;

  /**
   * The end value spinner
   */
  private JSpinner end;

  /**
   * The current value spinner
   */
  private JSpinner current;

  /**
   * The time slider
   */
  private JSlider timeSlider;

  /**
   * Flag to stop the time slider event during setTime()
   */
  private boolean timeChanging = false;

  /**
   * The description.
   */
  private String description = "Time";

  /**
   * The constructor
   *
   * @param xviewer The viewer
   * @param xscript The script
   */
  public TimeSlider(Viewer xviewer, Script xscript)
  {
    this(xviewer);

    setScript(xscript);
  }

  /**
   * The constructor
   *
   * @param xviewer The viewer
   */
  public TimeSlider(Viewer xviewer)
  {
    viewer = xviewer;

    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

    addMouseListener(new TimeSliderMouseAdapter());

    // Create the time slider.

    timeSlider = new JSlider();
    timeSlider.addChangeListener(new TimeSliderChangeListener());
    timeSlider.addMouseListener(new TimeMouseAdapter());

    // Create the spinners

    start = new JSpinner();
    start.addChangeListener(new StartTimeChangeListener());
    start.setPreferredSize(new Dimension(80, 24));
    start.setMaximumSize(new Dimension(80, 24));
    start.setMinimumSize(new Dimension(80, 24));
    start.addMouseListener(new TimeSliderMouseAdapter());

    end = new JSpinner();
    end.addChangeListener(new EndTimeChangeListener());
    end.setPreferredSize(new Dimension(80, 24));
    end.setMaximumSize(new Dimension(80, 24));
    end.setMinimumSize(new Dimension(80, 24));
    end.addMouseListener(new TimeSliderMouseAdapter());

    current = new JSpinner();
    current.addChangeListener(new CurrentTimeChangeListener());
    current.setPreferredSize(new Dimension(80, 24));
    current.setMaximumSize(new Dimension(80, 24));
    current.setMinimumSize(new Dimension(80, 24));
    current.addMouseListener(new TimeSliderMouseAdapter());

    // Layout the slider.

    this.add(timeSlider);
    Box box = Box.createHorizontalBox();
    box.add(start);
    box.add(Box.createHorizontalGlue());
    box.add(current);
    box.add(Box.createHorizontalGlue());
    box.add(end);
    this.add(box);

    setDescription(description);
  }

  /**
   * Set the decription
   */
  public void setDescription(String xdescription)
  {
    description  = xdescription;

    timeSlider.setToolTipText(description);
    start.setToolTipText(description);
    end.setToolTipText(description);
    current.setToolTipText(description);
  }

  /**
   * Set the <code>Script</code>
   *
   * @param xscript The script
   */
  public void setScript(Script xscript)
  {
    script = xscript;

    // Set the slider values

    // Calculate the min and max values as integers.

    int min = (int) (script.minTime*PERCISION);
    int max = (int) (script.maxTime*PERCISION);

    timeSlider.setMinimum(min);
    timeSlider.setMaximum(max);
    timeSlider.setValue(min);

    // Set the spinner models

    start.setModel(createModel(script.minTime));
    end.setModel(createModel(script.maxTime));
    current.setModel(createModel(script.minTime));
  }

  /**
   * Return a spinner model with the value, xvalue
   */
  private SpinnerNumberModel createModel(double xvalue)
  {
    return new SpinnerNumberModel(xvalue, script.minTime,
                                  script.maxTime, STEP_SIZE);
  }

  /**
   * Return the script sceens
   */
  public Script getScript()
  {
    return script;
  }

  /**
   * Set the time slider value
   */
  public void setTime(double xtime)
  {
    // $$TODO: Make sure xtime is between min and max.

    timeChanging = true;

    timeSlider.setValue((int) (xtime*PERCISION));
    current.setValue(new Double(xtime));

    timeChanging = false;
  }

  /**
   * The time value of this slider
   */
  public double getTime()
  {
    return ((Double) current.getValue()).doubleValue();
  }

  /**
   * The start time value of this slider
   */
  public double getStartTime()
  {
    return ((Double) start.getValue()).doubleValue();
  }

  /**
   * The end time value of this slider
   */
  public double getEndTime()
  {
    return ((Double) end.getValue()).doubleValue();
  }

  /**
   * Set the slider values.
   */
  public void setTimeValues()
  {
    timeChanging = true;

    double currentVal = ((Double) current.getValue()).doubleValue();
    double startVal = ((Double) start.getValue()).doubleValue();
    double endVal = ((Double) end.getValue()).doubleValue();

    boolean currentChanged = false;

    if(currentVal < startVal)
    {
      currentVal = startVal;
      currentChanged = true;
    }
    else if(currentVal > endVal)
    {
      currentVal = endVal;
      currentChanged = true;
    }

    current.setModel(new SpinnerNumberModel(currentVal, startVal, endVal, STEP_SIZE));

    int val = (int) (currentVal*PERCISION);
    int min = (int) (startVal*PERCISION);
    int max = (int) (endVal*PERCISION);

    timeSlider.setValue(val);
    timeSlider.setMinimum(min);
    timeSlider.setMaximum(max);

    if(currentChanged)
      viewer.updateAnimationTime();

    timeChanging = false;
  }

  public void setEnabled(boolean enabled)
  {
    current.setEnabled(enabled);
    start.setEnabled(enabled);
    end.setEnabled(enabled);
    timeSlider.setEnabled(enabled);
  }

  private class TimeSliderChangeListener implements ChangeListener
  {
    public TimeSliderChangeListener()
    {}

    public void stateChanged(ChangeEvent e)
    {
      if(timeChanging)
        return;

      timeChanging = true;

      int val = timeSlider.getValue();
      double time = ((double) val)/PERCISION;
      current.setValue(time);

      timeChanging = false;
    }
  }

  private class CurrentTimeChangeListener implements ChangeListener
  {
    public CurrentTimeChangeListener()
    {}

    public void stateChanged(ChangeEvent e)
    {
      if(timeChanging)
        return;

      timeChanging = true;

      double val = ((Double) current.getValue()).doubleValue();
      int time = (int) (val*PERCISION);
      timeSlider.setValue(time);

      // $$ISSUE:  This will cause the viewer to update everytime the user
      //           changes the current time using the spinner.

      viewer.updateAnimationTime();

      timeChanging = false;
    }
  }

  private class StartTimeChangeListener implements ChangeListener
  {
    public StartTimeChangeListener()
    {}

    public void stateChanged(ChangeEvent e)
    {
      // Set the lower value of the end time.

      double val = ((Double) start.getValue()).doubleValue();
      end.setModel(new SpinnerNumberModel(((Double) end.getValue()).doubleValue(),
                                          val, script.maxTime, STEP_SIZE));

      // Set the spinner and slider values for the current time.

      setTimeValues();
    }
  }

  private class EndTimeChangeListener implements ChangeListener
  {
    public EndTimeChangeListener()
    {}

    public void stateChanged(ChangeEvent e)
    {
      // Set the lower value of the end time.

      double val = ((Double) end.getValue()).doubleValue();
      start.setModel(new SpinnerNumberModel(((Double) start.getValue()).doubleValue(),
                                            script.minTime, val, STEP_SIZE));

      // Set the spinner and slider values for the current time.

      setTimeValues();
    }
  }

  private class TimeSliderMouseAdapter extends MouseAdapter
  {
    /**
     *
     */
    public void mouseEntered(MouseEvent e)
    {
      viewer.setStatus(description);
    }

    /**
     *
     */
    public void mouseExited(MouseEvent e)
    {
      viewer.defaultStatus();
    }
  }

  private class TimeMouseAdapter extends TimeSliderMouseAdapter
  {
    private double time;

    public void mousePressed(MouseEvent e)
    {
      // Record the current time.

      time = getTime();
    }

    public void mouseReleased(MouseEvent e)
    {
      // If the time did not change, ignore this event.

      if(time == getTime())
        return;

      viewer.updateAnimationTime();
    }
  }
}
