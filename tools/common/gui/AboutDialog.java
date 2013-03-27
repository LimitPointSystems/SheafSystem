/**
 * Classname: AboutDialog.java
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: AboutDialog.java,v $ $Revision: 1.9 $
 *
 * $Date: 2013/01/12 17:17:54 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.common.gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


/**
 * AboutDialog is a generic class for constructing
 * "about" boxes for your app.
 * 
 */
public class AboutDialog extends JWindow implements Runnable
{
  private int milliseconds;
  private boolean keepGoing = true;

  JPanel panel = new JPanel(new BorderLayout());
  Toolkit toolkit = Toolkit.getDefaultToolkit();

  /**
   * Constructor
   *
   */
  public AboutDialog(ImageIcon imageIcon, String text)
  {
    JLabel label1 = new JLabel(imageIcon);
    JLabel label2 = new JLabel(text, JLabel.CENTER);

    label1.setBorder(BorderFactory.createRaisedBevelBorder());
    label2.setBorder(BorderFactory.createRaisedBevelBorder());
    label2.setOpaque(false);
    label2.setForeground(Color.black);

    panel.add(label1, BorderLayout.CENTER);
    getContentPane().add(panel, BorderLayout.CENTER);

    addMouseListener(new MouseAdapter()
                     {
                       public void mousePressed(MouseEvent e)
                       {
                         goAway();
                       }
                     }
                    );

    pack();
    centerWindow();
  }

  private void centerWindow()
  {
    Dimension scrnSize    = toolkit.getScreenSize();
    Dimension labelSize   = panel.getPreferredSize();
    int       labelWidth  = labelSize.width,
                            labelHeight = labelSize.height;

    setLocation(scrnSize.width/2  - (labelWidth/2),
                scrnSize.height/2 - (labelHeight/2));
  }

  public void showAbout(int millisecondsToShow)
  {
    milliseconds = millisecondsToShow;
    Thread t = new Thread(this);
    t.start();
  }

  public void goAway()
  {
    keepGoing = false;
  }

  public void run()
  {
    setVisible(true);

    int sleepTime = milliseconds/10;
    for(int i=0; i<10; i++)
    {
      if(!keepGoing)
        break;

      toFront();

      try
      {
        Thread.sleep(sleepTime);
      }
      catch(java.lang.InterruptedException e)
      {}
    }

    setVisible(false);
  }

}

