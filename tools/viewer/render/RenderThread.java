
/**
 * Classname: RenderThread
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:00 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.render;

import bindings.java.*;
import tools.viewer.animation.*;
import tools.viewer.common.*;
import tools.viewer.event.*;
import tools.viewer.user.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.concurrent.*;
import java.io.*;
import java.lang.reflect.*;
import javax.swing.event.*;
import javax.swing.*;
import vtk.*;

/**
 *
 * Event queue for rendering through the <code>Stage</code>.
 *
 */
public class RenderThread extends Thread
{
  /**
   * The event queue
   */
  private LinkedBlockingQueue<RenderThreadEvent> events =
    new LinkedBlockingQueue<RenderThreadEvent>();

  /**
   * The viewer
   */
  private Viewer viewer;

  /**
   * The <code>PlayThread</code>
   */
  private PlayThread playThread;

  /**
   * The <code>Stage</code>
   */
  private Stage stage;

  /**
   * The <code>Screen</code>
   */
  private Screen screen;

  /**
   * The current <code>SceneDescriptor</code> to render.
   */
  private SceneDescriptor currentScene;

  /**
   * The constructor
   */
  public RenderThread()
  {
    // Construct the stage

    stage = new Stage(this);
  }

  /**
   * Initalize this thread.
   *
   * @param xviewer The viewer
   * @param xplayThread The play thread
   * @param xscreen The screen canvas
   */
  public void initialize(Viewer xviewer,
                         PlayThread xplayThread,
                         Screen xscreen)
  {
    viewer = xviewer;
    playThread = xplayThread;
    screen = xscreen;

    // Initialize the stage

    stage.initialize(screen);
  }

  /**
   * Queue up the <code>RenderThreadEvent</code>
   */
  public void addEvent(RenderThreadEvent xevent)
  {
    try
    {
      events.put(xevent);
    }
    catch(Exception e)
    {}
  }

  /**
   * Start the rendering thread
   */
  public void run()
  {
    RenderThreadEvent event;

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

  /**
   * Detach the sections on the stage.
   */
  public void detachStates()
  {
    stage.detachStates();
  }      

  /**
   * Set the background color of the renderer.
   */
  public void setBackgroundColor(Color xcolor)
  {
    stage.setBackgroundColor(xcolor);
  }

  /**
   * Pick xposition
   */
  public void pick(double[] xposition)
  {
    invokeEvent(new PickEvent(xposition));
  }

  /**
   * Return true if the Actor has vector data.
   */
  public boolean isVector(G3DFieldActorDescriptor xactor)
  {
    return stage.isVector(xactor);
  }

  /**
   * Return true if the Actor has tensor data.
   */
  public boolean isTensor(G3DFieldActorDescriptor xactor)
  {
    return stage.isTensor(xactor);
  }

  /**
   * The bounds for the Actor.
   */
  public void getBounds(G3DFieldActorDescriptor xactor, double[] xbounds)
  {
    stage.getBounds(xactor, xbounds);
  }

  /**
   * Accessor method for the current <code>Stage</code>
   */
  public Stage getStage()
  {
    return stage;
  }

  /**
   * Accessor method for the current <code>SceneDescriptor</code>
   */
  public SceneDescriptor getCurrentScene()
  {
    return currentScene;
  }
  /**
   * Update the client scenes of this class
   */
  public void updateClients(SceneDescriptor xscene)
  {
    invokeEvent(new SetRenderSceneEvent(xscene));
  }

  // EVENT FACET

  /**
   * Abort the render.
   */
  public synchronized void abort()
  {
    // $$HACK: Abort current event

    events.clear();
  }

  /**
   * Make the <code>Stage</code> current
   */
  public void makeCurrent()
  {
    stage.makeCurrent();
  }

  /**
   * Set the size of the <code>Stage</code>
   */
  public void setSize(int xwidth, int xheight)
  {
    stage.setSize(xwidth, xheight);
  }

  /**
   * Register a mouse pressed event
   */
  public void mousePressed(MouseEvent xmouseEvent)
  {
    stage.mousePressed(xmouseEvent);
  }

  /**
   * Register a mouse released event
   */
  public void mouseReleased(MouseEvent xmouseEvent)
  {
    stage.mouseReleased(xmouseEvent);
  }

  /**
   * Register a mouse entered event
   */
  public void mouseEntered(MouseEvent xmouseEvent)
  {
    stage.mouseEntered(xmouseEvent);
  }

  /**
   * Register a mouse exited event
   */
  public void mouseExited(MouseEvent xmouseEvent)
  {
    stage.mouseExited(xmouseEvent);
  }

  /**
   * Register a mouse moved event
   */
  public void mouseMoved(MouseEvent xmouseEvent)
  {
    stage.mouseMoved(xmouseEvent);
  }

  /**
   * Register a mouse dragged event
   */
  public void mouseDragged(MouseEvent xmouseEvent)
  {
    stage.mouseDragged(xmouseEvent);
  }

  /**
   * Register a key pressed event
   */
  public void keyPressed(KeyEvent xkeyEvent)
  {
    stage.keyPressed(xkeyEvent);
  }

  /**
   * Reset the view
   */
  public void resetView()
  {
    stage.resetView();
  }

  /**
   * Save the scene to an image
   */
  public void saveImage(String xfileName,
                        ViewerConstants.ImageFormat xformat)
  {
    stage.saveImage(xfileName, xformat);
  }

  /**
   * Copy the next scene to the current scene.
   */
  public void copy(SceneDescriptor xscene)
  {
    currentScene = xscene.clone();
  }

  /**
   * Update the current scene
   */
  public void update()
  {
    // This method is invoked from the RenderEvent.  It updates the
    // scene descriptor causing the sheaf sections to be accessed.
    // To ensure concurrent access to the sheaf library, this method
    // must be executed from the "java event dispatching thread".
    // However, the update needs to finish before the scene can
    // be rendered via the RenderEvent.  Thus, invokeAndWait must
    // be called.

    UpdateStageRunnable runnable =
      new UpdateStageRunnable(stage, currentScene);

    try
    {
      SwingUtilities.invokeAndWait(runnable);
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }
  }

  /**
   * Render the current scene.
   */
  public void render()
  {
    try
    {
      // Render on the Stage.

      stage.render();

      // Notify the clients that the render is complete.

      synchronized (playThread)
      {
        playThread.notify();
      }

      // $$TODO: Notify the Viewer
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }
  }

  /**
   * Set the off screen rendering mode
   */
  public void setOffScreenRendering(boolean xmode)
  {
    stage.setOffScreenRendering(xmode);
  }

  /**
   * Record the current scene
   */
  public void record(int xidx)
  {
    stage.record(xidx);

    // Notify the clients that the render is complete.

    synchronized (playThread)
    {
      playThread.notify();
    }

    // $$TODO: Notify the Viewer
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
