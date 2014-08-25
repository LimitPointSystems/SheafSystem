
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

import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.user.*;
import com.limitpoint.bindings.java.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 * Specialization of <code>JPanel</code> for displaying a
 * <code>FieldTableDescriptor</code>
 */
public class FieldTable extends JPanel
{
  /**
   * The <code>FieldTableDescriptor</code>
   */
  protected FieldTableDescriptor descriptor;

  /**
   * The list of <code>SectionTable</code>'s
   */
  protected ArrayList<SectionTable> sections =
    new ArrayList<SectionTable>();

  /**
   * The <code>JPanel</code> containing the <code>SectionTable</code>'s
   */
  protected JPanel tablePanel;

  /**
   * Constructor
   */
  public FieldTable(FieldTableDescriptor xdescriptor)
  {
    descriptor = xdescriptor;

    setLayout(new BorderLayout());

    //$$ISSUE: Probably should use a JSplitPane here.  The logic
    //         might be more complex in order to distinguish between
    //         the one viewer and two viewer cases though.

    tablePanel = new JPanel();
    tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.X_AXIS));

    // Construct the section tables

    namespace_poset ns = Viewer.APPLICATION.getNamespace(descriptor.namespace);

    Iterator<SectionDescriptor> itr = descriptor.sections.iterator();
    SectionTable table;
    while(itr.hasNext())
    {
      table = new SectionTable(itr.next().build(ns));
      sections.add(table);
      tablePanel.add(table);
    }

    add
      (tablePanel, BorderLayout.CENTER);
  }

  /**
   * Update the <code>SectionTable</code>'s
   */
  public void update()
  {
    Iterator<SectionTable> itr = sections.iterator();
    while(itr.hasNext())
    {
      itr.next().update();
    }
  }
}


