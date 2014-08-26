
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


package com.limitpoint.tools.viewer.user;

import com.limitpoint.tools.viewer.render.*;

import javax.swing.*;
import java.awt.*;

public class DescriptorCellRenderer extends JLabel implements ListCellRenderer
{
  // Default values.

  static final Color DEFAULT_FOREGROUND  = Color.black;
  static final Color SELECTED_FOREGROUND = Color.red;

  /**
   * Constructor
   */
  public DescriptorCellRenderer()
  {
    super();
  }

  public Component getListCellRendererComponent(JList list,
      Object value,
      int index,
      boolean isSelected,
      boolean cellHasFocus)
  {
    String s = value.toString();
    setText(s);

    Descriptor descriptor = (Descriptor) value;

    if(descriptor.selected)
      setForeground(SELECTED_FOREGROUND);
    else
      setForeground(DEFAULT_FOREGROUND);

    if(isSelected)
      setBackground(list.getSelectionBackground());
    else
      setBackground(list.getBackground());

    setEnabled(list.isEnabled());
    setFont(list.getFont());
    setOpaque(true);
    return this;
  }
}
