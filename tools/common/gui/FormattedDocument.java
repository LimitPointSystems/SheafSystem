
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
