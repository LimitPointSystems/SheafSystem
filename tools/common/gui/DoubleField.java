
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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
