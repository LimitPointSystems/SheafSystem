
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


package com.limitpoint.tools.viewer.table;

import com.limitpoint.tools.common.gui.*;
import com.limitpoint.bindings.java.*;
import javax.swing.*;

/**
 * Viewer to display fields in table form.
 */
public class TableViewer extends LPSFrame
{
  /**
   * The <code>FieldTable</code>
   */
  protected FieldTable fieldTable;

  /**
   * Constructor
   */
  public TableViewer(FieldTableDescriptor xdescriptor)
  {
    super("Table Viewer");

    //     setDefaultLookAndFeelDecorated(true);

    fieldTable = new FieldTable(xdescriptor);
    getContentPane().add(fieldTable);

    pack();
    setVisible(true);

    setDefaultCloseOperation(DISPOSE_ON_CLOSE);
  }

  /**
   * Update the table
   */
  public void update()
  {
    fieldTable.update();
  }
}


