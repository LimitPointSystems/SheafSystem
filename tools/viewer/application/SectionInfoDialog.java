
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

package com.limitpoint.tools.viewer.application;

import bindings.java.*;
import com.limitpoimt.tools.common.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Class SectionInfoDialog is used for displaying basic information
 * about field instances in a popup window.
 */
public class SectionInfoDialog extends JDialog
{
  private JTextArea textArea;

  /**
   * Constructor.
   *
   * @param title The title to appear on the window title bar.
   */
  public SectionInfoDialog(String title)
  {
    setTitle(title);

    JPanel content = new JPanel();
    content.setLayout(new BorderLayout());

    textArea = new JTextArea(12, 32);  // Just a guess at what to use.
    textArea.setEditable(false);

    JScrollPane scrollPane = new JScrollPane(textArea);
    content.add(scrollPane, BorderLayout.CENTER);

    setContentPane(content);

    pack();
  }

  public void setSection(sec_vd section)
  {
    try
    {
      sec_rep_space secRepSpace = (sec_rep_space) section.host();
      namespace_poset namespacePoset = (namespace_poset) secRepSpace.host();

      abstract_poset_member base = secRepSpace.base();
      schema_poset_member fiberSchema = section.fiber().schema();

      int db = section.db();
      int df = section.df();
      int dofCt = section.dof_ct();

      StringBuffer sb = new StringBuffer();
      sb.append(" NamespacePoset = ")
      .append(namespacePoset.name()).append('\n')
      .append(" Base = ").append(base).append('\n')
      .append(" FiberSchema = ").append(fiberSchema.name()).append('\n')
      .append(" SecRepSpace = ").append(secRepSpace.name()).append('\n')
      .append(" Section = ").append(section.name()).append('\n')
      .append(" db = ").append(db).append('\n')
      .append(" df = ").append(df).append('\n')
      .append(" dofCt = ").append(dofCt).append('\n')
      .append(" DofNames:").append('\n');

      String[] names = SheafUtilities.getRowDofNames(section);

      for(int i=0; i<names.length; i++)
        sb.append("   ").append(names[i]).append('\n');

      sb.append('\n');

      textArea.setText(sb.toString());
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();

      textArea.setText("");
    }
  }
}
