
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

import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.common.gui.*;

import javax.swing.*;
import java.awt.*;

public class SceneCellRenderer extends DescriptorCellRenderer
{
  // Default values.

  static final ImageIcon keyIcon =
    GuiUtilities.getImageIcon(ViewerConstants.IMAGE_PATH + "Key.png");
  static final ImageIcon defaultIcon =
    GuiUtilities.getImageIcon(ViewerConstants.IMAGE_PATH + "Dot.png");

  /**
   * Constructor
   */
  public SceneCellRenderer()
  {
    super();
  }

  public Component getListCellRendererComponent(JList list,
      Object value,
      int index,
      boolean isSelected,
      boolean cellHasFocus)
  {
    JLabel result = (JLabel) super.getListCellRendererComponent(list, value, index,
                    isSelected, cellHasFocus);

    SceneDescriptor scene = (SceneDescriptor) value;
    if(scene.keyFrame)
      result.setIcon(keyIcon);
    else
      result.setIcon(defaultIcon);

    return result;
  }
}
