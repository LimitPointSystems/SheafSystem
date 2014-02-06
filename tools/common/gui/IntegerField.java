
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

//$$TODO: Maybe add option to have only positive integers.

package tools.common.gui;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.Toolkit;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;

public class IntegerField extends JTextField
{
  private Toolkit toolkit;
  private NumberFormat integerFormatter;

  public IntegerField(int value, int columns)
  {
    super(columns);
    toolkit = Toolkit.getDefaultToolkit();
    integerFormatter = NumberFormat.getNumberInstance(Locale.US);
    integerFormatter.setParseIntegerOnly(true);
    setValue(value);
  }

  public int getValue()
  {
    int retVal = 0;
    try
    {
      retVal = integerFormatter.parse(getText()).intValue();
    }
    catch(ParseException e)
    {
      // This should never happen because insertString allows
      // only properly formatted data to get in the field.
      toolkit.beep();
    }
    return retVal;
  }

  public void setValue(int value)
  {
    setText(integerFormatter.format(value));
  }

  protected Document createDefaultModel()
  {
    return new IntegerDocument();
  }

  protected class IntegerDocument extends PlainDocument
  {
    public void insertString(int offs,
                             String str,
                             AttributeSet a)
    throws BadLocationException
    {
      char[] source = str.toCharArray();
      char[] result = new char[source.length];
      int j = 0;

      for (int i = 0; i < result.length; i++)
      {
        if (Character.isDigit(source[i]))
          result[j++] = source[i];
        else
        {
          toolkit.beep();
          System.err.println("insertString: " + source[i]);
        }
      }
      super.insertString(offs, new String(result, 0, j), a);
    }
  }
}
