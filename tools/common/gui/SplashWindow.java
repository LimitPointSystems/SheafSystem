
/**
 *
 * Copyright (c) 2013 Limit Point Systems, Inc. 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

package tools.common.gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SplashWindow extends JWindow
{
  private boolean keepGoing = true;

  public SplashWindow(ImageIcon imageIcon, int millisecondsToShow)
  {
    JPanel panel  = new JPanel(new BorderLayout());
    JLabel label1 = new JLabel(imageIcon);
    label1.setBorder(BorderFactory.createRaisedBevelBorder());
    panel.add(label1, BorderLayout.CENTER);
    getContentPane().add(panel, BorderLayout.CENTER);

    // Add a mouse listener to allow closing the window by clicking
    // it with mouse.

    addMouseListener(new MouseAdapter()
                     {
                       public void mousePressed(MouseEvent e)
                       {
                         keepGoing = false;
                       }
                     }
                    );

    pack();
    centerWindow(panel);

    setVisible(true);

    // Do the thread voodoo required to keep the window in view
    // and to dispose of it after the specified time duration.

    doThreadStuff(millisecondsToShow);
  }

  private void doThreadStuff(int millisecondsToShow)
  {
    final int milliseconds = millisecondsToShow;

    // Anonymous runnable class/object to do the dispose and force garbage collection.
    // (Defined before showRunner because it is used there).

    final Runnable disposeRunner = new Runnable()
                                   {
                                     public void run()
                                     {
                                       //                 long mem1 = Runtime.getRuntime().freeMemory();
                                       //                 System.out.println("SplashWindow: free memory before dispose = " + mem1);

                                       setVisible(false);
                                       dispose();

                                       //                 long mem2 = Runtime.getRuntime().freeMemory();
                                       //                 System.out.println("SplashWindow: free memory after dispose = " + mem2);

                                       // Explicitly invoke the garbage collector

                                       System.gc();

                                       //                 long mem3 = Runtime.getRuntime().freeMemory();
                                       //                 System.out.println("SplashWindow: free memory after garbage collection = " + mem3);

                                       //                 long diff = mem3 - mem1;
                                       //                 System.out.println("SplashWindow: total memory recovered (bytes) = " + diff);
                                     }
                                   };

    // Anonymous runnable class to show the window and keep it in front.

    Runnable showRunner = new Runnable()
                          {
                            public void run()
                            {
                              // The following while loop keeps this window in front
                              // of other windows for the time that the window is visible.
                              // Without the repeated calls to toFront, other windows can
                              // cover it up.

                              int sleepTime = 10; // milliseconds (tune this value accordingly)

                              int totalTimeShown = 0;
                              while(keepGoing)
                              {
                                // Force this window to the front.

                                toFront();

                                // Sleep for "sleepTime"

                                try
                                {
                                  Thread.sleep(sleepTime);
                                }
                                catch(Exception e)
                                {}

                                // Increment the total time the window has been shown
                                // and exit the loop if the desired time has elapsed.

                                totalTimeShown += sleepTime;
                                if(totalTimeShown >= milliseconds)
                                  break;
                              }

                              // Use SwingUtilities.invokeAndWait to queue the disposeRunner
                              // object on the event dispatch thread.

                              try
                              {
                                SwingUtilities.invokeAndWait(disposeRunner);
                              }
                              catch(Exception e)
                              {}
                            }
                          }
                          ;

    // Create the thread to control the window and fire it up.

    Thread showThread = new Thread(showRunner);
    showThread.start();
  }

  // Convenience method to center the window on the screen.

  private void centerWindow(JPanel panel)
  {
    Toolkit   toolkit     = Toolkit.getDefaultToolkit();
    Dimension scrnSize    = toolkit.getScreenSize();
    Dimension labelSize   = panel.getPreferredSize();
    int       labelWidth  = labelSize.width,
                            labelHeight = labelSize.height;

    setLocation(scrnSize.width/2  - (labelWidth/2),
                scrnSize.height/2 - (labelHeight/2));
  }
}
