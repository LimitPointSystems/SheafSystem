
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

package com.limitpoint.tools.common.gui;

import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.plaf.metal.*;
import javax.swing.border.*;

public class DemoTheme extends DefaultMetalTheme
{
  public String getName()
  {
    return "Demo";
  }

  private final FontUIResource controlFont
  = new FontUIResource("Dialog", Font.BOLD, 18);

  private final FontUIResource systemFont
  = new FontUIResource("Dialog", Font.PLAIN, 18);

  private final FontUIResource userFont
  = new FontUIResource("SansSerif", Font.PLAIN, 18);

  private final FontUIResource smallFont
  = new FontUIResource("Dialog", Font.PLAIN, 14);

  public FontUIResource getControlTextFont()
  {
    return controlFont;
  }
  public FontUIResource getSystemTextFont()
  {
    return systemFont;
  }
  public FontUIResource getUserTextFont()
  {
    return userFont;
  }
  public FontUIResource getMenuTextFont()
  {
    return controlFont;
  }
  public FontUIResource getWindowTitleFont()
  {
    return controlFont;
  }
  public FontUIResource getSubTextFont()
  {
    return smallFont;
  }

  public void addCustomEntriesToTable(UIDefaults table)
  {
    super.addCustomEntriesToTable(table);

    final int internalFrameIconSize = 16;

    table.put("InternalFrameTitlePane.closeIcon",
              MetalIconFactory.getInternalFrameCloseIcon(
                internalFrameIconSize));

    table.put("InternalFrameTitlePane.maximizeIcon",
              MetalIconFactory.getInternalFrameMaximizeIcon(
                internalFrameIconSize));

    table.put("InternalFrameTitlePane.iconizeIcon",
              MetalIconFactory.getInternalFrameMinimizeIcon(
                internalFrameIconSize));

    table.put("InternalFrameTitlePane.altMaximizeIcon",
              MetalIconFactory.getInternalFrameAltMaximizeIcon(
                internalFrameIconSize));

    table.put( "ScrollBar.width", new Integer(21) );
  }
}
