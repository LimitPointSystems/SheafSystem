
/**
 * Classname: DoubleField
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.common.gui;

import javax.swing.*;
import javax.swing.text.*;

import java.awt.Toolkit;
import java.text.*;

public class DoubleField extends JTextField
{
  private DecimalFormat format;

  public DoubleField(double value, int columns, DecimalFormat f)
  {
    super(columns);
    setDocument(new FormattedDocument(f));
    format = f;
    setValue(value);
  }

  public double getValue()
  {
    double retVal = 0.0;

    try
    {
      retVal = format.parse(getText()).doubleValue();
    }
    catch (ParseException e)
    {
      Toolkit.getDefaultToolkit().beep();
      System.err.println("getValue: could not parse: " + getText());
    }
    return retVal;
  }

  public void setValue(double value)
  {
    setText(format.format(value));
  }
}
