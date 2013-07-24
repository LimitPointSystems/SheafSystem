
/**
 * Classname: GenericDialog
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:17:55 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.common.gui;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.*;

public abstract class GenericDialog extends JDialog
{
  JPanel panel;

  //$$TODO: Fix to use url!!!
  //   static ImageIcon okIcon = new ImageIcon("resources/green-ball.png");
  //   static ImageIcon cancelIcon = new ImageIcon("resources/red-ball.png");

  GenericDialog(Frame f, String title, Component c)
  {
    super(f, title, true);  // true implies modal

    panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

    if(c != null)
      panel.add(c);
    panel.add(new ButtonPanel());

    getContentPane().add(panel);
    pack();
    //GuiUtilities.centerOnScreen(this);
  }

  public void setVisible(boolean xvisible)
  {
    if(xvisible)
      GuiUtilities.centerOnOwner(this);

    super.setVisible(xvisible);
  }

  public GenericDialog(Frame f, String title)
  {
    this(f, title, null);
  }

  public abstract void cancelPressed();

  public abstract void okPressed();

  public void addPane(Component c, int index)
  {
    panel.add(c, index);
    pack();
  }

  class ButtonPanel extends JPanel
  {
    public ButtonPanel()
    {
      super(new FlowLayout(FlowLayout.CENTER));

      //JButton ok     = new JButton("OK", okIcon);
      //JButton cancel = new JButton("Cancel", cancelIcon);
      JButton ok     = new JButton("OK");
      JButton cancel = new JButton("Cancel");

      //ok.setToolTipText("Accept selection(s) and proceed");
      //cancel.setToolTipText("Discard selection(s)");

      ok.addActionListener(new ActionListener()
                           {
                             public void actionPerformed(ActionEvent e)
                             {
                               okPressed();
                             }
                           }
                          );

      cancel.addActionListener(new ActionListener()
                               {
                                 public void actionPerformed(ActionEvent e)
                                 {
                                   cancelPressed();
                                 }
                               }
                              );

      this.add(ok);
      this.add(cancel);

      //getRootPane().setDefaultButton(ok);
    }
  }
}
