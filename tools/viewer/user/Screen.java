/**
 *  Classname: Screen
 *
 *  @author $Author: jebutler $
 *
 *  $Date: 2013/01/12 17:18:02 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import tools.viewer.event.*;
import tools.viewer.render.*;

import java.awt.*;
import java.util.ArrayList;
import java.util.ListIterator;
import java.awt.event.*;
import javax.swing.*;
import vtk.*;

/**
 *
 * This <code>Canvas</code> handles the java events by interacting with the
 * <code>RenderThread</code>.
 *
 */
public class Screen extends Canvas
      implements MouseListener, MouseMotionListener, ComponentListener
{
  /**
   * The <code>RenderThread</code>
   */
  protected RenderThread renderThread;

  /**
   * The display id of this <code>Screen</code>
   */
  protected long display;

  /**
   * The drawable id of this <code>Screen</code>
   */
  protected long drawable;

  /**
   * The enabled mode of this <code>Screen</code>
   */
  protected boolean enabled = true;

  /**
   * Constructor
   */
  public Screen()
  {
    super();

    addMouseListener(this);
    addMouseMotionListener(this);
    addComponentListener(this);
  }

  /**
   * Initialize this screen
   */
  public void initialize(RenderThread xrenderThread)
  {
    renderThread = xrenderThread;

    // Get the display id and drawable id

    display = GetDisplay();
    drawable = GetDrawable();
  }

  /**
   * Set the enabled mode of this <code>Screen</code>
   */
  public void setEnabled(boolean xenabled)
  {
    enabled = xenabled;
  }

  /**
   * Paint this canvas
   */
  public void paint(Graphics xgraphics)
  {
    if(!enabled)
      return;

    renderThread.addEvent(new RepaintEvent());
  }

  /**
   *
   */
  public void addNotify()
  {
    super.addNotify();

    if(renderThread != null)
    {
      renderThread.addEvent(new MakeCurrentEvent());
    }
  }

  /**
   * $$HACK: Override this function so this canvas can be contained in
   *         a JSplitPane.
   */
  public Dimension getMinimumSize()
  {
    return new Dimension(1,1);
  }

  //===========================================================================
  // MouseListener Methods
  //===========================================================================

  /**
   *
   */
  public void mouseClicked(MouseEvent e)
  {}

  /**
   *
   */
  public void mousePressed(MouseEvent e)
  {
    if(!enabled)
      return;

    renderThread.addEvent(new MousePressedEvent(e));
  }

  /**
   *
   */
  public void mouseReleased(MouseEvent e)
  {
    if(!enabled)
      return;

    // Clear all events from the queue in the render thread.

    renderThread.abort();

    // Add the mouse released event.

    renderThread.addEvent(new MouseReleasedEvent(e));
  }

  //===========================================================================
  // MouseMotionListener Methods
  //===========================================================================

  /**
   *
   */
  public void mouseEntered(MouseEvent e)
  {
    if(!enabled)
      return;

    requestFocus();

    renderThread.addEvent(new MouseEnteredEvent(e));
  }

  /**
   *
   */
  public void mouseExited(MouseEvent e)
  {
    if(!enabled)
      return;

    renderThread.addEvent(new MouseExitedEvent(e));
  }

  /**
   *
   */
  public void mouseMoved(MouseEvent e)
  {
    if(!enabled)
      return;

    renderThread.addEvent(new MouseMovedEvent(e));
  }


  /**
   *
   */
  public void mouseDragged(MouseEvent e)
  {
    if(!enabled)
      return;

    renderThread.addEvent(new MouseDraggedEvent(e));
  }

  //===========================================================================
  // KeyListener Methods
  //===========================================================================

  /**
   *
   */
  public void keyPressed(KeyEvent e)
  {
    if(!enabled)
      return;

    // This class is not a key listener.  It forwards key events
    // from the ProbePanel to the render thread.

    renderThread.addEvent(new KeyPressedEvent(e));
  }

  //===========================================================================
  // ComponentListener Methods
  //===========================================================================

  public void componentResized(ComponentEvent event)
  {
    super.setSize(getWidth(), getHeight());

    if(!enabled)
      return;

    renderThread.addEvent(new SetSizeEvent(getWidth(), getHeight()));
  }

  public void componentHidden(ComponentEvent event)
{}

  public void componentMoved(ComponentEvent event)
  {}

  public void componentShown(ComponentEvent event)
  {}

  // NATIVE FACET

  /**
   * The display id of this <code>Screen</code>
   */
  public synchronized long getDisplay()
  {
    return display;
  }

  /**
   * The drawable id of this <code>Screen</code>
   */
  public synchronized long getDrawable()
  {
    return drawable;
  }

  /**
   * Lock this <code>Screen</code>
   */
  public synchronized void lock()
  {
    Lock();
  }

  /**
   * Unlock this <code>Screen</code>
   */
  public synchronized void unlock()
  {
    UnLock();
  }

  protected native long GetDisplay();
  protected native long GetDrawable();
  protected native int Lock();
  protected native int UnLock();

  //
  // Load libraries statically.
  //
  static
  {
    System.loadLibrary("tools_java_binding");
    System.loadLibrary("tools");
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
    try
    {
      System.loadLibrary("vtkHybridJava");
    }
    catch (Throwable e)
    {
      System.out.println("Cannot load vtkHybrid");
    }
  }
}
