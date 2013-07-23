
/**
 *  Classname: IntegerField
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

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
