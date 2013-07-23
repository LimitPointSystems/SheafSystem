
/**
 * Classname: PropertiesDialog
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:02 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import tools.common.gui.*;
import tools.viewer.render.*;

import java.awt.event.*;
import javax.swing.*;
import java.util.*;

/**
 *  A non modal dialog for actor properties editing.
 */
public class PropertiesDialog extends LPSDialog
{
  /**
   * The properties panel
   */
  public PropertiesPanel panel;

  /**
   * Default constructor
   */
  public PropertiesDialog(JFrame xowner, String xtitle, PropertiesPanel xpanel)
  {
    super(xowner, xtitle);

    setModal(true);

    panel = xpanel;
    this.add(panel);

    panel.setDialog(this);

    pack();
    setLocationRelativeTo(xowner);

    // Use a WindowListener to handle hiding this dialog.

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(
      new WindowAdapter()
      {
        public void windowClosing(WindowEvent e)
        {
          setVisible(false);
        }
      }
    );
  }

  /**
   * Accessor for the properties panel.
   */
  public PropertiesPanel getPropertiesPanel()
  {
    return panel;
  }
}
