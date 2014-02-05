
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
