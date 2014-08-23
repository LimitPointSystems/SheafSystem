
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


package com.limitpoint.tools.viewer.animation;

import bindings.java.*;
import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.viewer.event.*;
import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.user.*;

import java.awt.*;
import java.util.*;
import java.util.concurrent.*;
import java.io.*;
import java.lang.reflect.*;
import javax.swing.event.*;
import javax.swing.*;
import javax.media.*;
import javax.media.control.*;
import javax.media.protocol.*;
import javax.media.datasink.*;
import javax.media.format.*;
import vtk.*;

/**
 *
 * Event queue for playing and recording a <code>Script</code>
 *
 */
public class PlayThread extends Thread implements ControllerListener, DataSinkListener
{
  /**
   * The temporary directory in which the jpgs of each sceen are stored.
   */
  public static final File sceneDir = new File("sceneDir");

  /**
   * The event queue
   */
  private LinkedBlockingQueue<PlayThreadEvent> events
  = new LinkedBlockingQueue<PlayThreadEvent>();

  /**
   * The event being handled
   */
  private PlayThreadEvent event = null;

  // INPUT FACET

  /**
   * Flag to abort the animation.
   */
  private boolean abort = false;

  // CLIENT FACET

  /**
   * The <code>Viewer</code>
   */
  private Viewer viewer;

  /**
   * The <code>RenderThread</code>
   */
  private RenderThread renderThread;

  // SCRIPT FACET

  /**
   * The current <code>Script</code>
   */
  private Script script;

  /**
   * The <code>AnimationToolBar</code>
   */
  private AnimationToolBar animationToolBar;

  /**
   * The <code>TimeSlider</code>
   */
  private TimeSlider timeSlider;

  /**
   * The scene in the animation
   */
  private int scene = 0;

  // MOVIE FACET

  /**
   * The record mode
   */
  private boolean recordMode;

  /**
   * The movie output file.
   */
  private File movieFile;

  /**
   * The constructor
   */
  public PlayThread()
  {}

  /**
   * Initialize this thread
   *
   * @param xrenderThread The rendering thread.
   */
  public void initialize(Viewer xviewer, RenderThread xrenderThread,
                         AnimationToolBar xanimationToolBar, Script xscript)
  {
    viewer = xviewer;
    renderThread = xrenderThread;
    animationToolBar = xanimationToolBar;

    timeSlider = animationToolBar.getTimeSlider();

    initScript(xscript);
  }

  /**
   * Queue up the <code>PlayThreadEvent</code>
   */
  public void addEvent(PlayThreadEvent xevent)
  {
    try
    {
      events.put(xevent);
    }
    catch(Exception e)
    {}
  }

  /**
   * Pause the animation
   */
  public synchronized void pause()
  {
    if(event != null)
      event.abort();

    abort = true;
    events.clear();
  }

  /**
   * Starts this <code>PlayThread</code>
   */
  public void run()
  {
    while(true)
    {
      try
      {
        // Pull an event off the queue and
        // handle it.

        event = events.take();
        event.handle(this);
      }
      catch(Exception e)
      {
        e.printStackTrace();
      }
    }
  }

  // SCRIPT FACET

  /**
   * The <code>AnimationToolBar</code>
   */
  public AnimationToolBar getAnimationToolBar()
  {
    return animationToolBar;
  }

  /**
   * Set the <code>Script</code>
   */
  public void initScript(Script xscript)
  {
    script = xscript;

    timeSlider.setScript(script);
    animationToolBar.setScript(script);
  }

  /**
   * Returns true, if the animation can increment to the next scene.
   */
  public boolean canIncrement()
  {
    if(scene+1 >= script.size())
    {
      // The next scene is not in the script, return false.

      return false;
    }
    else
    {
      double currentTime = script.get(scene+1).time;
      double lastTime = timeSlider.getEndTime();

      if(currentTime > lastTime)
      {
        // The next scene has an time greater than the time slider's
        // end time, return false.

        return false;
      }
    }

    return true;
  }

  /**
   * Returns true, if the animation can decrement to the previous scene.
   */
  public boolean canDecrement()
  {
    if(scene-1 < 0)
    {
      // The previous scene is not in the script, return false.

      return false;
    }
    else
    {
      double currentTime = script.get(scene-1).time;
      double firstTime = timeSlider.getStartTime();

      if(currentTime < firstTime)
      {
        // The previous scene has an time less than the time slider's
        // start time, return false.

        return false;
      }
    }

    return true;
  }

  /**
   * Get the first scene of the time slider.
   */
  private int getStartScene()
  {
    return script.getScene(timeSlider.getStartTime());
  }

  /**
   * Get the last scene of the time slider.
   */
  private int getEndScene()
  {
    return script.getScene(timeSlider.getEndTime());
  }

  // EVENT FACET

  /**
   * Set the current <code>Script</code>
   */
  public void setScript(Script xscript)
  {
    synchronized (xscript)
    {
      initScript(xscript);
    }
  }

  /**
   * Initialize this thread for scene rendering.
   */
  public void initScene()
  {
    // If the scene can not be incremented (at the end of animation)
    // then reset the animation to the beginning.

    if(!canIncrement())
      scene = getStartScene();
  }

  /**
   * Initialize this thread for movie rendering.
   */
  public boolean initMovie()
  {
    // Get the output file

    JFileChooser fileChooser = new JFileChooser();
    fileChooser.setDialogTitle("Save Animation as Movie File");

    String[] suffixes = {"mov"};
    SuffixFileFilter  filter = new SuffixFileFilter(suffixes);
    fileChooser.setFileFilter(filter);

    int returnVal = fileChooser.showSaveDialog(viewer);
    if(returnVal != JFileChooser.APPROVE_OPTION)
    {
      events.clear();
      invokeEvent(new SetPlayModeEvent(false));
      return false;
    }

    movieFile = fileChooser.getSelectedFile();

    if(!movieFile.getName().endsWith(".mov"))
    {
      movieFile = new File(movieFile.getParent(), movieFile.getName() + ".mov");
    }

    if(movieFile.exists())
    {
      int result = JOptionPane.showConfirmDialog(viewer,
                   "Movie file alread exists.\n\n" +
                   "Overwrite this file?");

      if(result != JOptionPane.YES_OPTION)
      {
        movieFile = null;
        events.clear();
        invokeEvent(new SetPlayModeEvent(false));
        return false;
      }
    }

    // Create the movie directory for dumping the animation to JPG images
    // Clear this directory if it already exists.

    if(sceneDir.exists())
    {
      // File already exists.

      if(sceneDir.isDirectory())
      {
        // File is a directory;
        // clear any existing files.

        clearSceneDir();
      }
      else
      {
        // File is not a directory; error

        JOptionPane.showMessageDialog(viewer,
                                      "Could not make the movie.\n" +
                                      "An ordinary file with the same name as the scene directory already exists.",
                                      "Movie Failure",
                                      JOptionPane.ERROR_MESSAGE);

        events.clear();
        invokeEvent(new SetPlayModeEvent(false));
        return false;
      }
    }
    else
    {
      // The file does not already exist; try to create it.

      if(!sceneDir.mkdir())
      {
        // Failed to create directory for scene files.

        JOptionPane.showMessageDialog(viewer,
                                      "Could not make the movie.\n" +
                                      "The scene directory could not be created.",
                                      "Movie Failure",
                                      JOptionPane.ERROR_MESSAGE);
        events.clear();
        invokeEvent(new SetPlayModeEvent(false));
        return false;
      }
    }

    // Turn-on off-screen rendering.

    recordMode = true;
    renderThread.addEvent(new SetOffScreenRenderingEvent(recordMode));

    // Set the scene to the first scene

    scene = getStartScene();

    return true;
  }

  /**
   * Play the <code>Script</code>
   */
  public void play()
  {
    while(!abort)
    {
      updateClients();

      // Pause between scenes

      try
      {
        sleep((int) ((1.0/script.rate)*1000.0));
      }
      catch(InterruptedException e)
      {
        e.printStackTrace();
      }

      // Increment to the next scene or exit if there is
      // no more scenes to increment to. Also if the
      // thread has been aborted during sleeping, exit.
      // Exiting here for abort will ensure that the
      // scene is not incremented.

      if(canIncrement() && !abort)
        scene++;
      else
        break;
    }

    // Finished animating, set play mode to false and
    // turn off record mode if needed.

    invokeEvent(new SetPlayModeEvent(false));
    if(recordMode)
    {
      recordMode = false;
      renderThread.addEvent(new SetOffScreenRenderingEvent(recordMode));
    }

    abort = false;
  }

  /**
   * Finialize the movie.  Save it to disk.
   */
  public void finalizeMovie()
  {
    //
    // Write the movie to disk.
    //

    // List and sort the files into the list.

    File[] ls = sceneDir.listFiles();
    File[] inFiles = new File[ls.length];
    for(int i=0; i<ls.length; i++)
    {
      String name = ls[i].getName();
      int idx = Integer.parseInt(name.substring(0, name.indexOf(".")));
      inFiles[idx] = ls[i];
    }

    // $$ISSUE: Do we want the user to set the width and height?

    // $$ISSUE: Need to handle errors better.  Should pop-up a dialog
    //          instead of just printing a message to std out.

    // Set the width and height to the canvas width and height

    int width = viewer.getScreen().getSize().width;
    int height = viewer.getScreen().getSize().height;

    // Generate the output media locators.

    MediaLocator outML;

    try
    {
      // In Java 6 File.toURL() is deprecate, so the next line was modified.
      // The change is backward compatible with previous version of Java.
      //outML = new MediaLocator(movieFile.toURL());
      outML = new MediaLocator((movieFile.toURI()).toURL());
    }
    catch (Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();

      return;
    }

    ImageDataSource ids = new ImageDataSource(width, height, script, inFiles);

    Processor p;

    try
    {
      p = Manager.createProcessor(ids);
    }
    catch (Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();

      return;
    }

    p.addControllerListener(this);

    // Put the Processor into configured state so we can set
    // some processing options on the processor.

    p.configure();
    if(!waitForState(p, p.Configured))
    {
      System.err.println("Failed to configure the processor.");
      return;
    }

    // Set the output content descriptor to QuickTime.

    p.setContentDescriptor(new ContentDescriptor(FileTypeDescriptor.QUICKTIME));

    // Query for the processor for supported formats.
    // Then set it on the processor.

    TrackControl tcs[] = p.getTrackControls();
    Format f[] = tcs[0].getSupportedFormats();
    if(f == null || f.length <= 0)
    {
      System.err.println("The mux does not support the input format: " + tcs[0].getFormat());
      return;
    }

    tcs[0].setFormat(f[0]);

    // We are done with programming the processor.  Let's just
    // realize it.

    p.realize();
    if(!waitForState(p, p.Realized))
    {
      System.err.println("Failed to realize the processor.");
      return;
    }

    // Now, we'll need to create a DataSink.
    DataSink dsink;
    if((dsink = createDataSink(p, outML)) == null)
    {
      System.err.println("Failed to create a DataSink for the given output MediaLocator: " + outML);
      return;
    }

    dsink.addDataSinkListener(this);
    fileDone = false;

    // OK, we can now start the actual transcoding.

    try
    {
      p.start();
      dsink.start();
    }
    catch(IOException e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
      return;
    }

    // Wait for EndOfStream event.

    waitForFileDone();

    // Cleanup.

    try
    {
      dsink.close();
    }
    catch(Exception e)
    {}

    p.removeControllerListener(this);


    //
    // Write out the movie header file
    //

    File headerFile = MovieHeader.getFile(movieFile);
    MovieHeader header = new MovieHeader(headerFile);
    try
    {
      header.write(timeSlider.getStartTime(), timeSlider.getEndTime(),
                   script.rate, script.size());
    }
    catch(IOException e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();

      return;
    }

    // Clean-up the construction debris

    clearSceneDir();
    sceneDir.delete();

    // Once finished open the movie file

    invokeEvent(new OpenMovieEvent(movieFile));

    return;
  }

  /**
   * Clear the scene directory
   */
  private void clearSceneDir()
  {
    File[] files = sceneDir.listFiles();

    for(int i=0; i<files.length; i++)
    {
      files[i].delete();
    }
  }

  /**
   * Render the first scene of the animation
   */
  public void first()
  {
    scene = getStartScene();
    updateClients();
  }

  /**
   * Render the previous scene of the animation
   */
  public void previous()
  {
    if(!canDecrement())
      return;

    scene--;
    updateClients();
  }

  /**
   * Render the next scene of the animation
   */
  public void next()
  {
    if(!canIncrement())
      return;

    scene++;
    updateClients();
  }

  /**
   * Render the last scene of the animation
   */
  public void last()
  {
    scene = getEndScene();
    updateClients();
  }

  /**
   * Render the animation scene at the time slider's time
   */
  public void updateTime(SceneDescriptor xscene)
  {
    //
    // $$ISSUE: This is kind of a hack to avoid potential threading problems.
    //          The current scene is passed in from the viewer but is only
    //          used if it's a one scene animation.
    //

    // One scene scripts used the current scene of the viewer.

    SceneDescriptor lscene = xscene;

    if(script.size() > 1)
    {
      // Multi scene scripts gets the scene in the script
      // closest to the time slider's time.

      scene = script.getScene(timeSlider.getTime());
      lscene = script.get(scene).clone();
    }

    // Set the time of the scene and its actors.

    lscene.setTime(timeSlider.getTime());

    updateClients(lscene);
  }

  /**
   * Load the next scene of the script
   */
  public void loadScene(SceneDescriptor xscene)
  {
    synchronized (xscene)
    {
      scene = script.indexOf(xscene);

      timeSlider.setTime(xscene.time);
    }
  }

  // RENDER FACET

  /**
   * Update the clients to the current scene.
   */
  protected synchronized void updateClients()
  {
    SceneDescriptor lscene = script.get(scene);

    updateClients(lscene);

    // Set the time.

    timeSlider.setTime(lscene.time);
  }

  /**
   * Update the clients to xscene
   */
  protected synchronized void updateClients(SceneDescriptor xscene)
  {
    // Render the next scene

    RenderThreadEvent event;
    event = new RenderEvent(xscene.clone(), false, recordMode);

    renderThread.addEvent(event);
    viewer.setAnimationScene(xscene.clone());

    // Wait for the render to complete

    try
    {
      wait();
    }
    catch(InterruptedException e)
    {}
  }

  // MOVIE FACET

  /**
   * Create the DataSink.
   */
  DataSink createDataSink(Processor p, MediaLocator outML)
  {
    DataSource ds;

    if((ds = p.getDataOutput()) == null)
    {
      return null;
    }

    DataSink dsink;

    try
    {
      dsink = Manager.createDataSink(ds, outML);
      dsink.open();
    }
    catch (Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
      return null;
    }

    return dsink;
  }


  Object waitSync = new Object();
  boolean stateTransitionOK = true;

  /**
   * Block until the processor has transitioned to the given state.
   * Return false if the transition failed.
   */
  boolean waitForState(Processor p, int state)
  {
    synchronized (waitSync)
    {
      try
      {
        while (p.getState() < state && stateTransitionOK)
          waitSync.wait();
      }
      catch (Exception e)
      {}
    }
    return stateTransitionOK;
  }

  /**
   * Controller Listener.
   */
  public void controllerUpdate(ControllerEvent evt)
  {
    if (evt instanceof ConfigureCompleteEvent ||
        evt instanceof RealizeCompleteEvent ||
        evt instanceof PrefetchCompleteEvent)
    {
      synchronized (waitSync)
      {
        stateTransitionOK = true;
        waitSync.notifyAll();
      }
    }
    else if (evt instanceof ResourceUnavailableEvent)
    {
      synchronized (waitSync)
      {
        stateTransitionOK = false;
        waitSync.notifyAll();
      }
    }
    else if (evt instanceof EndOfMediaEvent)
    {
      evt.getSourceController().stop();
      evt.getSourceController().close();
    }
  }

  Object waitFileSync = new Object();
  boolean fileDone = false;
  boolean fileSuccess = true;

  /**
   * Block until file writing is done. 
   */
  boolean waitForFileDone()
  {
    synchronized (waitFileSync)
    {
      try
      {
        while (!fileDone)
          waitFileSync.wait();
      }
      catch (Exception e)
      {}
    }
    return fileSuccess;
  }

  /**
   * Event handler for the file writer.
   */
  public void dataSinkUpdate(DataSinkEvent evt)
  {
    if(evt instanceof EndOfStreamEvent)
    {
      synchronized (waitFileSync)
      {
        fileDone = true;
        waitFileSync.notifyAll();
      }
    }
    else if (evt instanceof DataSinkErrorEvent)
    {
      synchronized (waitFileSync)
      {
        fileDone = true;
        fileSuccess = false;
        waitFileSync.notifyAll();
      }
    }
  }

  /**
   * A DataSource to read from a list of JPEG image files and
   * turn that into a stream of JMF buffers.
   * The DataSource is not seekable or positionable.
   */
  class ImageDataSource extends PullBufferDataSource
  {
    ImageSourceStream streams[];

    ImageDataSource(int width, int height, Script script, File[] images)
    {
      streams = new ImageSourceStream[1];
      streams[0] = new ImageSourceStream(width, height, script, images);
    }

    public void setLocator(MediaLocator source)
    {}

    public MediaLocator getLocator()
    {
      return null;
    }

    /**
     * Content type is of RAW since we are sending buffers of video
     * frames without a container format.
     */
    public String getContentType()
    {
      return ContentDescriptor.RAW;
    }

    public void connect()
    {}

    public void disconnect()
    {}

    public void start()
    {}

    public void stop()
    {}

    /**
     * Return the ImageSourceStreams.
     */
    public PullBufferStream[] getStreams()
    {
      return streams;
    }

    /**
     * We could have derived the duration from the number of
     * frames and frame rate.  But for the purpose of this program,
     * it's not necessary.
     */
    public Time getDuration()
    {
      return DURATION_UNKNOWN;
    }

    public Object[] getControls()
    {
      return new Object[0];
    }

    public Object getControl(String type)
    {
      return null;
    }
  }

  /**
   * The source stream to go along with ImageDataSource.
   */
  class ImageSourceStream implements PullBufferStream
  {
    File[] images;
    int width, height;
    Script script;
    VideoFormat format;

    int nextImage = 0; // index of the next image to be read.
    boolean ended = false;

    public ImageSourceStream(int width, int height, Script script, File[] images)
    {
      this.width = width;
      this.height = height;
      this.images = images;
      this.script = script;

      // Create a default format.

      format = new VideoFormat(VideoFormat.JPEG,
                               new Dimension(width, height),
                               Format.NOT_SPECIFIED,
                               Format.byteArray,
                               (float)script.rate);
    }

    /**
     * We should never need to block assuming data are read from files.
     */
    public boolean willReadBlock()
    {
      return false;
    }

    /**
     * This is called from the Processor to read a frame worth
     * of video data.
     */
    public void read(Buffer buf) throws IOException
    {
      // Check if we've finished all the frames.

      if(nextImage >= images.length)
      {
        // We are done.  Set EndOfMedia.

        buf.setEOM(true);
        buf.setOffset(0);
        buf.setLength(0);
        ended = true;
        return;
      }

      File imageFile = images[nextImage];
      nextImage++;

      // Open a random access file for the next image.

      RandomAccessFile raFile;
      raFile = new RandomAccessFile(imageFile, "r");

      byte data[] = null;

      // Check the input buffer type & size.

      if (buf.getData() instanceof byte[])
        data = (byte[])buf.getData();

      // Check to see the given buffer is big enough for the frame.

      if(data == null || data.length < raFile.length())
      {
        data = new byte[(int)raFile.length()];
        buf.setData(data);
      }

      buf.setHeader("junk");

      // Read the entire JPEG image from the file.

      raFile.readFully(data, 0, (int)raFile.length());

      // Create a VideoFormat with the correct frameRate

      buf.setOffset(0);
      buf.setLength((int)raFile.length());
      buf.setFormat(format);
      buf.setFlags(buf.getFlags() | buf.FLAG_KEY_FRAME);

      // Close the random access file.

      raFile.close();
    }

    /**
     * Return the format of each video frame.  That will be JPEG.
     */
    public Format getFormat()
    {
      return format;
    }

    public ContentDescriptor getContentDescriptor()
    {
      return new ContentDescriptor(ContentDescriptor.RAW);
    }

    public long getContentLength()
    {
      return 0;
    }

    public boolean endOfStream()
    {
      return ended;
    }

    public Object[] getControls()
    {
      return new Object[0];
    }

    public Object getControl(String type)
    {
      return null;
    }
  }

  // VIEWER FACET

  /**
   * Invoke a viewer event
   */
  public void invokeEvent(ViewerEvent xevent)
  {
    InvokeViewerEventRunnable runnable =
      new InvokeViewerEventRunnable(viewer, xevent);

    try
    {
      SwingUtilities.invokeLater(runnable);
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }
  }
}
