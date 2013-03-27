/**
 *  Classname: DemoTheme
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: DemoTheme.java,v $ $Revision: 1.11 $
 *
 *  $Date: 2013/01/12 17:17:55 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.gui;

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
