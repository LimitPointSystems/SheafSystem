
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


package tools.viewer.animation;

import bindings.java.*;
import tools.viewer.user.*;
import tools.common.gui.*;

import java.awt.*;
import java.util.*;
import java.io.*;
import java.lang.reflect.*;
import javax.swing.event.*;
import javax.swing.*;
import javax.media.*;
import javax.media.protocol.*;

/**
 *
 * Class for playing a movie file.
 *
 */
public class MoviePlayer extends LPSFrame
{
  /**
   * The movie file
   */
  private File file;

  /**
   * The media player
   */
  private Player player;

  /**
   * The movie start time
   */
  private double start;

  /**
   * The movie end time
   */
  private double end;

  /**
   * The control component
   */
  private Component controlComponent = null;

  /**
   * The visualization component
   */
  private Component visualComponent = null;

  /**
   * Label for displaying the real time
   */
  private JLabel timeLabel;

  /**
   * The movie header file
   */
  private MovieHeader header;

  /**
   * The constructor
   *
   * @param viewer The viewer 
   * @param xfile The file
   */
  public MoviePlayer(Viewer viewer, File xfile)
  {
    file = xfile;

    setLayout(new BorderLayout());

    if(file == null)
    {
      // Get the movie file from the user

      JFileChooser fileChooser = new JFileChooser();
      fileChooser.setDialogTitle("Open Movie File");

      String[] suffixes = {"mov"};
      SuffixFileFilter  filter = new SuffixFileFilter(suffixes);
      fileChooser.setFileFilter(filter);

      int returnVal = fileChooser.showOpenDialog(viewer);
      if(returnVal != JFileChooser.APPROVE_OPTION)
        return;

      file = fileChooser.getSelectedFile();
    }

    setTitle("Movie: " + file.getName());

    // Get the movie header file and set the start and end times.

    File headerFile = MovieHeader.getFile(file);
    header = new MovieHeader(headerFile);

    try
    {
      header.read();
    }
    catch(Exception e)
    {
      JOptionPane.showMessageDialog(viewer,
                                    "Movie Header file not found!\n" +
                                    "Real time can not be displayed.",
                                    "No Header",
                                    JOptionPane.WARNING_MESSAGE);
    }

    start = header.getStartTime();
    end = header.getEndTime();

    try
    {
      // In Java 6 File.toURL() is deprecate, so the next line was modified.
      // The change is backward compatible with previous version of Java.
      //MediaLocator mrl = new MediaLocator(file.toURL());
      MediaLocator mrl = new MediaLocator((file.toURI()).toURL());
      player = Manager.createRealizedPlayer(mrl);
    }
    catch(Exception e)
    {
      e.printStackTrace();

      JOptionPane.showMessageDialog(viewer,
                                    "Could not create player for " + file.getPath(),
                                    "Invalid Movie File",
                                    JOptionPane.ERROR_MESSAGE);

      return;
    }

    controlComponent = player.getControlPanelComponent();
    int height = controlComponent.getPreferredSize().height;
    visualComponent = player.getVisualComponent();
    Dimension videoSize = visualComponent.getPreferredSize();
    int width = videoSize.width;
    height += videoSize.height;
    timeLabel = new JLabel();
    setTimeLabel();
    height += timeLabel.getPreferredSize().height;

    JPanel content = new JPanel();
    content.setLayout(new BorderLayout());
    content.add(timeLabel, BorderLayout.NORTH);
    content.add(visualComponent, BorderLayout.CENTER);
    content.add(controlComponent, BorderLayout.SOUTH);

    content.setPreferredSize(new Dimension(width, height));
    setContentPane(content);

    pack();

    player.start();

    setVisible(true);

    (new TimeThread()).start();
  }

  /**
   * Thread for displaying the real time of the player
   */
  private class TimeThread extends Thread
  {
    public void run()
    {
      while(true)
      {
        setTimeLabel();

        try
        {
          sleep(100);
        }
        catch(Exception e)
        {}
      }
    }
  }

  /**
   * Set the text of the time label
   */
  public void setTimeLabel()
  {
    // Convert from media time to real time

    String time = header.calculate(player.getMediaTime());

    timeLabel.setText("Time: " + time);
  }
}
