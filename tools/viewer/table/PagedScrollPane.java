
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

package tools.viewer.table;

import tools.viewer.common.*;
import tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class PagedScrollPane extends JScrollPane
{
  Action upButtonAction;
  Action downButtonAction;

  JTable table;

  public PagedScrollPane(JTable xtable)
  {
    super(xtable);

    table = xtable;

    String imagePath = ViewerConstants.IMAGE_PATH;

    upButtonAction = new UpButtonAction();
    upButtonAction.setEnabled(false); // Starting at "top"

    ImageIcon upIcon = GuiUtilities.getImageIcon(imagePath + "PageUp16.png");
    JButton upButton = new JButton(upIcon);
    upButton.setBorder(new EmptyBorder(1, 1, 1, 1));
    upButton.addActionListener(upButtonAction);

    downButtonAction = new DownButtonAction();

    ImageIcon downIcon = GuiUtilities.getImageIcon(imagePath + "PageDown16.png");
    JButton downButton = new JButton(downIcon);
    downButton.setBorder(new EmptyBorder(1, 1, 1, 1));
    downButton.addActionListener(downButtonAction);

    // Add the corner buttons
    setCorner(ScrollPaneConstants.UPPER_RIGHT_CORNER, upButton);
    setCorner(ScrollPaneConstants.LOWER_RIGHT_CORNER, downButton);

    setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
    setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
  }

  /**
   *
   */
  class UpButtonAction extends AbstractAction
  {
    public void actionPerformed(ActionEvent evt)
    {
      if(table.getModel() instanceof PagedTableModel)
      {
        PagedTableModel model = (PagedTableModel) table.getModel();

        model.pageUp();

        // Disable up action if at top
        if(model.getPageIndex() == 0)
        {
          setEnabled(false);
        }
        downButtonAction.setEnabled(true);
      }
    }
  }

  /**
   *
   */
  class DownButtonAction extends AbstractAction
  {
    public void actionPerformed(ActionEvent evt)
    {
      if(table.getModel() instanceof PagedTableModel)
      {
        PagedTableModel model = (PagedTableModel) table.getModel();

        model.pageDown();

        // Disable up action if at bottom
        if(model.getPageIndex() == (model.getPageCount()-1))
        {
          setEnabled(false);
        }
        upButtonAction.setEnabled(true);
      }
    }
  }
}
