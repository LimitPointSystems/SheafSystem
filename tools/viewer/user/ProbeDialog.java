
//
// Copyright (c) 2013 Limit Point Systems, Inc.
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


package tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;

/**
 *  A non modal dialog for probe interaction.
 */
public class ProbeDialog extends JDialog
{
  /**
   * The <code>ProbePanel</code>
   */
  protected ProbePanel probePanel;

  /**
   * Default constructor
   */
  public ProbeDialog(JFrame xowner, G3DViewer xviewer)
  {
    super(xowner, "Probe Dialog");

    //     setDefaultLookAndFeelDecorated(true);

    probePanel = new ProbePanel(xviewer);
    this.add(probePanel);
    setSize(500, 300);

    // Use a WindowListener to handle hiding this dialog and turning off
    // probing (if active) on close.

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(
      new WindowAdapter()
      {
        public void windowClosing(WindowEvent e)
        {
          probePanel.endProbe();
          setVisible(false);
        }
      }
    );
  }

  /**
   * The <code>ProbePanel</code>
   */
  protected ProbePanel getProbePanel()
  {
    return probePanel;
  }
}
