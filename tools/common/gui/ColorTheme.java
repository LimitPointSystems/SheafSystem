/**
 *  Classname: ColorTheme
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: ColorTheme.java,v $ $Revision: 1.11 $
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

public class ColorTheme extends DefaultMetalTheme
{
  private String name;
  private Color[] colors;

  private ColorUIResource[] primary;

  public ColorTheme(String name, Color[] colors)
  {
    this.name = name;
    this.colors = colors;

    primary = new ColorUIResource[3];
    for(int i=0; i<3; i++)
    {
      Color c = colors[i];
      primary[i] = new ColorUIResource(c.getRed(), c.getGreen(), c.getBlue());
    }
  }

  public String getName()
  {
    return name;
  }

  protected ColorUIResource getPrimary1()
  {
    return primary[0];
  }
  protected ColorUIResource getPrimary2()
  {
    return primary[1];
  }
  protected ColorUIResource getPrimary3()
  {
    return primary[2];
  }
}
