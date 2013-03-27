
/**
 * Classname: FormattedDocument
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: FormattedDocument.java,v $ $Revision: 1.10 $
 *
 * $Date: 2013/01/12 17:17:55 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.gui;

import javax.swing.*;
import javax.swing.text.*;

import java.awt.Toolkit;
import java.text.*;
import java.util.Locale;

public class FormattedDocument extends PlainDocument
{
  private Format format;

  public FormattedDocument(Format f)
  {
    format = f;
  }

  public Format getFormat()
  {
    return format;
  }

  public void insertString(int offs, String str, AttributeSet a) throws BadLocationException
  {
    if (str == null)
      return;
    String oldString = getText(0, getLength());
    String newString = oldString.substring(0, offs) + str + oldString.substring(offs);
    try
    {
      Double.parseDouble(newString + "0");
      super.insertString(offs, str, a);
    }
    catch(NumberFormatException e)
    {}
  }
}
