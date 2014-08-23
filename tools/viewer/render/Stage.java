
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

package com.limitpoint.tools.viewer.render;

import com.limitpoimt.tools.viewer.animation.*;
import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.viewer.common.ViewerConstants.ImageFormat;
import com.limitpoimt.tools.viewer.user.*;
import com.limitpoimt.tools.viewer.event.*;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Enumeration;
import vtk.*;

/**
 *
 * The <code>Stage</code> is the interface between java and VTK.  This class
 * contains and updates the cameras, lights, and actors.
 *
 */



public class Stage implements ActionListener
{
  // RENDER FACET

  //
  // $$ISSUE: Should be using a vtkPropAssembly for the field representations.
  //          A bug in vtkPropAssembly does not allow a vtkPropAssembly
  //          to have a vtkPropAssembly as one of it's parts.  Since, a
  //          field representation is a vtkPropAssembly the stage must add
  //          the field representation directly to the vtkRenderer.
  //

  /**
   * The <code>vtkPropAssembly</code> of <code>FieldActor</code>'s
   */
  //protected vtkPropAssembly actorAssembly = new vtkPropAssembly();

  /**
   * The <code>vtkRenderWindow</code>
   */
  protected vtkRenderWindow renderWindow = new vtkRenderWindow();

  /**
   * The <code>vtkRenderer</code>
   */
  protected vtkRenderer renderer = new vtkRenderer();


  /**
   * A LightKit consists of three lights, a key light, a fill light, and a 
   * headlight. The main light is the key light. It is usually positioned
   * so that it appears like an overhead light
   * (like the sun, or a ceiling light). It is generally positioned to
   * shine down on the scene from about a 45 degree angle vertically 
   * and at least a little offset side to side. The key light usually at
   * least about twice as bright as the total of all other lights in the
   * scene to provide good modeling of object features.The other lights in
   * the kit (the fill light, headlight, and a pair of back lights) are
   * weaker sources that provide extra illumination to fill in the spots
   * that the key light misses. The fill light is usually positioned
   * across from or opposite from the key light (though still on the 
   * same side of the object as the camera) in order to simulate diffuse
   * reflections from other objects in the scene. The headlight, always
   * located at the position of the camera, reduces the contrast between
   * areas lit by the key and fill light. The two back lights, one on 
   * the left of the object as seen from the observer and one on the 
   * right, fill on the high-contrast areas behind the object. 
   * To enforce the relationship between the different lights, 
   * the intensity of the fill, back and headlights are set as a ratio 
   * to the key light brightness. Thus, the brightness of all the 
   * lights in the scene can be changed by changing the key light intensity.
   * All lights are directional lights (infinitely far away with no falloff). 
   * Lights move with the camera.
   */
  protected vtkLightKit lightkit = new vtkLightKit();
  
  /**
   * The <code>vtkGenericRenderWindowInteractor</code>
   */
  protected vtkGenericRenderWindowInteractor interactor
  = new vtkGenericRenderWindowInteractor();

  /**
   * The <code>Timer</code> used by the window interactor.
   */
  protected Timer timer = null;

  /**
   * The last x position of a mouse event.
   */
  protected int lastX;

  /**
   * The last y position of a mouse event.
   */
  protected int lastY;

  // PICKER FACET

  /**
   * The <code>vtkPropPicker</code> for the probe
   */
  protected vtkPropPicker picker = null;

  // IMAGE FACET

  /**
   * The <code>vtkWindowToImageFiler</code>
   */
  protected vtkWindowToImageFilter win2img = new vtkWindowToImageFilter();

  /**
   * The <code>vtkJPEGWriter</code>
   */
  protected vtkJPEGWriter imageWriter = new vtkJPEGWriter();

  // SCENE FACET

  /**
   * The descriptors to cameras map
   */
  protected Hashtable<CameraDescriptor, vtkCamera> cameraMap =
      new Hashtable<CameraDescriptor, vtkCamera>();

  /**
   * The cameras to descriptors map
   */
  protected Hashtable<vtkCamera, CameraDescriptor> cameraDescriptorMap =
      new Hashtable<vtkCamera, CameraDescriptor>();

  /**
   * The lights
   */
  protected Hashtable<LightDescriptor, vtkLight> lightMap =
      new Hashtable<LightDescriptor, vtkLight>();

  /**
   * The lights to descriptors map
   */
  protected Hashtable<vtkLight, LightDescriptor> lightDescriptorMap =
      new Hashtable<vtkLight, LightDescriptor>();

  /**
   * The actors
   */
  protected Hashtable<FieldActorDescriptor, FieldActor> actorMap =
      new Hashtable<FieldActorDescriptor, FieldActor>();
  // add an accessor here to getFieldActor(descriptor)
  // need to ultimately ask the render thread for the stage
  // call renderthread.getstage.getactor.

  /**
   * The actors to descriptors map
   */
  protected Hashtable<FieldActor, FieldActorDescriptor> actorDescriptorMap =
      new Hashtable<FieldActor, FieldActorDescriptor>();

  /**
   * The current time of the actors
   */
  protected double time = 0.0;

  /**
   * The current interactor style
   */
  protected int[] interactorStyle = null;

  /**
   * The <code>RenderThread</code>
   */
  protected RenderThread renderThread;

  /**
   * The user thread's <code>Screen</code>
   */
  protected Screen screen;

  /**
   * Constructor
   */
  public Stage(RenderThread xrenderThread)
  {
    renderThread = xrenderThread;

    // RENDER FACET

    renderWindow.SetAAFrames(6);
    renderWindow.LineSmoothingOn();
    renderWindow.PolygonSmoothingOn();
    renderWindow.AddRenderer(renderer);
    interactor.SetRenderWindow(renderWindow);
    
    // Add lighting to the scene.
    lightkit.AddLightsToRenderer(renderer);
    
    // The "this" below is for the actionListener.

    int delay = 10; //milliseconds
    timer = new Timer(delay, this);

    // Create the picker

    picker = new vtkPropPicker();
    interactor.SetPicker(picker);

    interactor.AddObserver("CreateTimerEvent", this, "startTimer");
    interactor.AddObserver("DestroyTimerEvent", this, "destroyTimer");
    
    interactor.ConfigureEvent();

    // IMAGE FACET

    win2img.SetInput(renderWindow);
    win2img.ReleaseDataFlagOn();
    imageWriter.SetInput(win2img.GetOutput());
  }

  /**
   * Initialize this <code>Stage</code>
   */
  public void initialize(Screen xscreen)
  {
    screen = xscreen;

    long display = screen.getDisplay();
    long drawable = screen.getDrawable();

    // Set the size of the render window

    int width = screen.getSize().width;
    int height = screen.getSize().height;

    renderWindow.SetSize(width, height);
    interactor.SetSize(width, height);
    interactor.ConfigureEvent();

    // Attach the screen canvas to the renderer.

    RenderCreate(renderWindow, display, drawable);
  }

  /**
   * Detach the sections for all the actions on the stage.
   */
  public void detachStates()
  {
    Iterator<FieldActor> itr = actorMap.values().iterator();
    while(itr.hasNext())
    {
      itr.next().detachStates();
    }
  }

  // CLIENT FACET

  /**
   * Return true if the Actor has vector data.
   */
  public boolean isVector(FieldActorDescriptor xactor)
  {
    vtkUnstructuredGrid grid = (vtkUnstructuredGrid) actorMap.get(xactor).getDataSet();

    return(grid.GetPointData().GetVectors() != null);
  }

  /**
   * Return true if the Actor has tensor data.
   */
  public boolean isTensor(FieldActorDescriptor xactor)
  {
    vtkUnstructuredGrid grid = (vtkUnstructuredGrid) actorMap.get(xactor).getDataSet();

    return(grid.GetPointData().GetTensors() != null);
  }

  /**
   * The bounds for the Actor.
   */
  public void getBounds(G3DFieldActorDescriptor xactor, double[] xbounds)
  {
    ((G3DFieldActor) actorMap.get(xactor)).getBounds(xbounds);
  }

  // RENDER FACET

  /**
   *  Method used by the timer.
   */
  public void actionPerformed(ActionEvent e)
  {
    synchronized (this)
    {
      lock();
      interactor.TimerEvent();
      unlock();
    }
  }

  /**
   * Start the timer
   */
  public void startTimer()
  {
    if(timer.isRunning())
      timer.stop();

    timer.setRepeats(false);
    timer.start();
  }

  /**
   * Stop the timer
   */
  public void destroyTimer()
  {
    if(timer.isRunning())
      timer.stop();
  }

  /**
   * Make the <code>vtkRenderWindow</code> current.
   */
  public void makeCurrent()
  {
    renderWindow.SetForceMakeCurrent();
  }

  /**
   * Set the size of the <code>vtkRenderWindow</code> and
   * <code>vtkInteractor<code>.
   */
  public void setSize(int xWidth, int xHeight)
  {
    lock();
    renderWindow.SetSize(xWidth, xHeight);
    interactor.SetSize(xWidth, xHeight);
    interactor.ConfigureEvent();
    unlock();
  }

  /**
   * Set the offscreen rendering mode of this <code>Stage</code>
   */
  public void setOffScreenRendering(boolean xmode)
  {
    lock();
    renderWindow.SetOffScreenRendering(xmode ? ViewerConstants.TRUE :
                                       ViewerConstants.FALSE);
    unlock();
  }

  /**
   * Register a mouse pressed event
   */
  public void mousePressed(MouseEvent e)
  {
    if(visibleActorCount() == 0)
      return;

    renderWindow.SetAAFrames(0);
    interactor.SetDesiredUpdateRate(1000000000.0);

    lastX = e.getX();
    lastY = e.getY();

    interactor.SetEventInformationFlipY(e.getX(), e.getY(),
                                        ctrlPressed(e), shiftPressed(e),
                                        '0', 0, "0");

    lock();

    if(SwingUtilities.isLeftMouseButton(e))
    {
      interactor.LeftButtonPressEvent();
    }
    else if(SwingUtilities.isMiddleMouseButton(e))
    {
      interactor.MiddleButtonPressEvent();
    }
    else if(SwingUtilities.isRightMouseButton(e))
    {
      interactor.RightButtonPressEvent();
    }

    unlock();
  }

  /**
   * Register a mouse released event
   */
  public void mouseReleased(MouseEvent e)
  {
    if(visibleActorCount() == 0)
      return;

    renderWindow.SetAAFrames(6);
    interactor.SetDesiredUpdateRate(0.01);

    interactor.SetEventInformationFlipY(e.getX(), e.getY(),
                                        ctrlPressed(e), shiftPressed(e), '0', 0, "0");

    lock();

    if(SwingUtilities.isLeftMouseButton(e))
    {
      interactor.LeftButtonReleaseEvent();
    }
    else if(SwingUtilities.isMiddleMouseButton(e))
    {
      interactor.MiddleButtonReleaseEvent();
    }
    else if(SwingUtilities.isRightMouseButton(e))
    {
      interactor.RightButtonReleaseEvent();
    }

    unlock();

    updateMouseMotion();
  }

  /**
   * Update the scenes based on the mouse motion.
   */
  public void updateMouseMotion()
  {
    //
    // $$ISSUE: This method should probably be combined with
    //          the updateView() method.
    //

    // Update the mouse movement.

    SceneDescriptor scene = renderThread.getCurrentScene().clone();

    if(scene.interactorStyle[1] == ViewerConstants.ACTOR_INTERACTOR)
    {
      vtkActor actor;
      FieldActorDescriptor descriptor;

      Iterator<FieldActorDescriptor> itr = scene.actors.iterator();
      while(itr.hasNext())
      {
        descriptor = itr.next();
        if(descriptor instanceof G3DFieldActorDescriptor)
        {
          G3DFieldActor g3dActor = (G3DFieldActor) actorMap.get(descriptor);
          actor = g3dActor.getGridActor();

          G3DFieldActorDescriptor g3dDescriptor =
            (G3DFieldActorDescriptor) descriptor;

          g3dDescriptor.position = actor.GetPosition();
          g3dDescriptor.origin = actor.GetOrigin();
          g3dDescriptor.orientation = actor.GetOrientation();
          g3dDescriptor.scale = actor.GetScale();

          actorDescriptorMap.put(g3dActor, g3dDescriptor);
        }
      }
    }
    else // Camera Interactor
    {
      vtkCamera camera;
      CameraDescriptor descriptor;

      Iterator<CameraDescriptor> itr = scene.cameras.iterator();
      while(itr.hasNext())
      {
        descriptor = itr.next();

        if(descriptor.selected)
        {
          // Update the selected camera in the scene.

          camera = cameraMap.get(descriptor);
          descriptor.position = camera.GetPosition();
          descriptor.focalPoint = camera.GetFocalPoint();
          descriptor.viewUp = camera.GetViewUp();

          cameraDescriptorMap.put(camera, descriptor);
        }
      }
    }

    // Update the clients of the render thread

    renderThread.updateClients(scene);
  }

  /**
   * Register a mouse entered event
   */
  public void mouseEntered(MouseEvent e)
  {
    interactor.SetEventInformationFlipY(e.getX(), e.getY(), 0, 0, '0', 0, "0");
    interactor.EnterEvent();
  }

  /**
   * Register a mouse exited event
   */
  public void mouseExited(MouseEvent e)
  {
    interactor.SetEventInformationFlipY(e.getX(), e.getY(), 0, 0, '0', 0, "0");
    interactor.LeaveEvent();
  }

  /**
   * Register a mouse moved event
   */
  public void mouseMoved(MouseEvent e)
  {
    if(visibleActorCount() == 0)
      return;

    lastX = e.getX();
    lastY = e.getY();

    interactor.SetEventInformationFlipY(e.getX(), e.getY(),
                                        ctrlPressed(e), shiftPressed(e),
                                        '0', 0, "0");

    lock();

    interactor.MouseMoveEvent();

    unlock();
  }

  /**
   * Register a mouse dragged event
   */
  public void mouseDragged(MouseEvent e)
  {
    if(visibleActorCount() == 0)
      return;

    interactor.SetEventInformationFlipY(e.getX(), e.getY(),
                                        ctrlPressed(e), shiftPressed(e),
                                        '0', 0, "0");

    lock();

    interactor.MouseMoveEvent();

    unlock();
  }

  /**
   * Register a key pressed event
   */
  public void keyPressed(KeyEvent e)
  {
    char keyChar = e.getKeyChar();

    if(keyChar == 'p')
    {
      lock();
      picker.PickProp(lastX, renderWindow.GetSize()[1] - lastY, renderer);
      unlock();

      if(picker.GetPropAssembly() != null)
        renderThread.pick(picker.GetPickPosition());
      else
        renderThread.pick(null);
    }
  }

  /**
   * Reset the view
   */
  public void resetView()
  {
    // Reset the camera

    resetCamera();

    // Update the view of the selected camera

    updateView();
  }

  /**
   * Record this <code>Stage</code>
   */
  public void record(int xscene)
  {
    // Create the path to the recorded file.

    File file = new File(PlayThread.sceneDir,
                         Integer.toString(xscene) + ".jpg");

    // Write the image to disc.

    writeImage(file.getPath());
  }

  /**
   * Render this <code>Stage</code>
   */
  public void render()
  {
    lock();
    renderWindow.Render();
    unlock();
  }

  /**
   * Lock the drawable area.
   */
  public void lock()
  {
    screen.lock();
  }

  /**
   * Unlock the drawable area.
   */
  public void unlock()
  {
    screen.unlock();
  }

  /**
   *
   */
  protected int ctrlPressed(InputEvent e)
  {
    return (e.getModifiers() & InputEvent.CTRL_MASK) == InputEvent.CTRL_MASK ? 1 : 0;
  }


  /**
   *
   */
  protected int shiftPressed(InputEvent e)
  {
    return (e.getModifiers() & InputEvent.SHIFT_MASK) == InputEvent.SHIFT_MASK ? 1 : 0;
  }

  /**
   *
   */
  protected int visibleActorCount()
  {
    return renderer.VisibleActorCount();
  }

  // SCENE FACET

  /**
   * Add the field representation (<code>FieldActor</code>)
   *
   * @param xdescriptor The <code>FieldActorDescriptor</code>
   */
  public void addActor(FieldActorDescriptor xdescriptor)
  {
    FieldActor actor = xdescriptor.build();

    // Add the actor to the list of actors and renderer.

    actorMap.put(xdescriptor, actor);
    actorDescriptorMap.put(actor, xdescriptor);

    // Add to the renderer.

    actor.addTo(renderer);

    // Set the renderer for the actor.

    actor.setRenderer(renderer);
    
  }

  /**
   * Remove the actor with descriptor xdescriptor.
   */
  public void removeActor(FieldActorDescriptor xdescriptor)
  {
    FieldActor actor = actorMap.get(xdescriptor);

    // Remove the actor from the maps.

    actorDescriptorMap.remove(actor);
    actorMap.remove(xdescriptor);

    // Remove from the renderer.

    actor.removeFrom(renderer);

    // Request garbage collection

    System.gc();
  }

  /**
   * Update this <code>Stage</code> to xscene
   */
  public void update(SceneDescriptor xscene)
  {
    // The view changed when an actor is added or removed from
    // the stage or a camera is added.

    boolean viewChanged = false;

    // Update the cameras

    vtkCamera camera;
    CameraDescriptor cameraDescriptor;

    // Add new cameras and udpate existing cameras.

    Iterator<CameraDescriptor> citr = xscene.cameras.iterator();
    while(citr.hasNext())
    {
      cameraDescriptor = citr.next();
      camera = cameraMap.get(cameraDescriptor);

      if(camera == null)
      {
        camera = cameraDescriptor.build();
        cameraMap.put(cameraDescriptor, camera);
        cameraDescriptorMap.put(camera, cameraDescriptor);
      }
      else
      {
        cameraDescriptor.update(camera, cameraDescriptorMap.get(camera));
        cameraDescriptorMap.put(camera, cameraDescriptor);
      }

      if(cameraDescriptor.selected)
      {
        // The camera is selected, use it as the active camera
        // and use the camera background color.

        renderer.SetActiveCamera(camera);
        renderThread.setBackgroundColor(cameraDescriptor.background);

        // Force the camera to be reset if either the position, focal point,
        // or view up is undefined.

        if((cameraDescriptor.position == null ||
            cameraDescriptor.focalPoint == null ||
            cameraDescriptor.viewUp == null)
            && cameraDescriptor.selected)
        {
          viewChanged = true;
        }
      }
    }

    // Remove old cameras

    Enumeration<CameraDescriptor> cameraDescriptors = cameraMap.keys();
    while(cameraDescriptors.hasMoreElements())
    {
      cameraDescriptor = cameraDescriptors.nextElement();
      if(!xscene.cameras.contains(cameraDescriptor))
      {
        camera = cameraMap.get(cameraDescriptor);

        cameraMap.remove(cameraDescriptor);
        cameraDescriptorMap.remove(camera);
      }
    }

    // Update the lights

    vtkLight light;
    LightDescriptor lightDescriptor;
    float[] rgba = new float[4];

    // Add new lights and update existing lights

    Iterator<LightDescriptor> litr = xscene.lights.iterator();
    while(litr.hasNext())
    {
      lightDescriptor = litr.next();
      light = lightMap.get(lightDescriptor);

      if(light == null)
      {
        light = lightDescriptor.build();
        lightMap.put(lightDescriptor, light);
        lightDescriptorMap.put(light, lightDescriptor);

        renderer.AddLight(light);
        renderer.LightFollowCameraOn();
      }
      else
      {
        lightDescriptor.update(light, lightDescriptorMap.get(light));
        lightDescriptorMap.put(light, lightDescriptor);
      }
    }

    // Remove old ligths

    Enumeration<LightDescriptor> lightDescriptors = lightMap.keys();
    while(lightDescriptors.hasMoreElements())
    {
      lightDescriptor = lightDescriptors.nextElement();
      if(!xscene.lights.contains(lightDescriptor))
      {
        light = lightMap.get(lightDescriptor);

        lightMap.remove(lightDescriptor);
        lightDescriptorMap.remove(light);

        renderer.RemoveLight(light);
      }
    }

    // Update the actors

    FieldActor actor;
    FieldActorDescriptor actorDescriptor;

    // Add new actors and update existing actors

    Iterator<FieldActorDescriptor> aitr = xscene.actors.iterator();
    while(aitr.hasNext())
    {
      actorDescriptor = aitr.next();
      actor = actorMap.get(actorDescriptor);

      if(actor == null)
      {
        addActor(actorDescriptor);
      }
      else
      {
        actorDescriptor.update(actor, actorDescriptorMap.get(actor));
        actorDescriptorMap.put(actor, actorDescriptor);
      }
    }

    // Remove old actors

    Enumeration<FieldActorDescriptor> actorDescriptors = actorMap.keys();
    while(actorDescriptors.hasMoreElements())
    {
      actorDescriptor = actorDescriptors.nextElement();
      if(!xscene.actors.contains(actorDescriptor))
      {
        removeActor(actorDescriptor);
      }
    }

    // Modify actors

    Enumeration<FieldActor> actors = actorDescriptorMap.keys();
    while(actors.hasMoreElements())
    {
      actor = actors.nextElement();

      if(actor.isModified())
        actor.modify();
    }

    // Clear actor modified

    actors = actorDescriptorMap.keys();
    while(actors.hasMoreElements())
    {
      actors.nextElement().clearIsModified();
    }

    // Update the interactor style

    if(interactorStyle == null || interactorStyle[0] != xscene.interactorStyle[0] ||
        interactorStyle[1] != xscene.interactorStyle[1])
    {
      vtkInteractorStyle style =
        (vtkInteractorStyle) interactor.GetInteractorStyle();

      vtkInteractorStyleSwitch iswitch = (vtkInteractorStyleSwitch) style;

      if(xscene.interactorStyle[0] == ViewerConstants.TRACKBALL_INTERACTOR)
      {
        if(xscene.interactorStyle[1] == ViewerConstants.CAMERA_INTERACTOR)
          iswitch.SetCurrentStyleToTrackballCamera();
        else
          iswitch.SetCurrentStyleToTrackballActor();
      }
      else
      {
        if(xscene.interactorStyle[1] == ViewerConstants.CAMERA_INTERACTOR)
          iswitch.SetCurrentStyleToJoystickCamera();
        else
          iswitch.SetCurrentStyleToJoystickActor();
      }

      interactorStyle = xscene.interactorStyle;
    }

    if(viewChanged)
    {
      // Reset the camera when the view has changed.

      resetCamera();

      // Update the camera view of the next scene and
      // client scenes

      updateView();
    }
    else
    {
      // Reset the camera clipping range

      resetCameraClippingRange();
    }
  }

  /**
   * Updates the camera view.
   */
  private void updateView()
  {
    // Get the next scene of the renderThread.

    SceneDescriptor scene = renderThread.getCurrentScene().clone();

    // Update the camera position of the scene

    CameraDescriptor cameraDescriptor;
    vtkCamera camera;

    // Update each camera descriptor's position and focal point.

    Iterator<CameraDescriptor> citr = scene.cameras.iterator();
    while(citr.hasNext())
    {
      cameraDescriptor = citr.next();
      camera = cameraMap.get(cameraDescriptor);
      cameraDescriptor.position = camera.GetPosition();
      cameraDescriptor.focalPoint = camera.GetFocalPoint();
      cameraDescriptor.viewUp = camera.GetViewUp();

      cameraDescriptorMap.put(camera, cameraDescriptor);
    }

    // Update the client scenes.

    renderThread.updateClients(scene);
  }

  /**
   * Set the background color of the <code>vtkRenderer</code>
   */
  public void setBackgroundColor(Color xcolor)
  {
    float[] rgba = new float[4];
    xcolor.getRGBComponents(rgba);
    renderer.SetBackground(rgba[0], rgba[1], rgba[2]);
  }

  /**
   * Reset the clipping range of the <code>vtkCamera</code>
   */
  public void resetCameraClippingRange()
  {
    lock();
    renderer.ResetCameraClippingRange();
    unlock();
  }

  /**
   * Reset the <code>vtkCamera</code>
   */
  public void resetCamera()
  {
    lock();
    renderer.GetActiveCamera().OrthogonalizeViewUp();
    renderer.ResetCamera();
    unlock();
  }

  // IMAGE FACET

  /**
   * Write the Image to xfileName.
   */
  public void writeImage(String xfileName)
  {
    lock();
    win2img.Modified();
    imageWriter.SetFileName(xfileName);
    imageWriter.Write();
    unlock();
  }

  /**
   * Save the current scene to xfileName as an image of xformat
   */
  public void saveImage(String xfileName, ImageFormat xformat)
  {
    vtkImageWriter writer;
    switch(xformat)
    {
    case BMP:
      writer = new vtkBMPWriter();
      break;
    case JPEG:
      writer = new vtkJPEGWriter();
      break;
    case PNG:
      writer = new vtkPNGWriter();
      break;
    case PNM:
      writer = new vtkPNMWriter();
      break;
    case POSTSCRIPT:
      writer = new vtkPostScriptWriter();
      break;
    case TIFF:
      writer = new vtkTIFFWriter();
      break;
    default:
      return;
    }

    lock();
    win2img.Modified();
    writer.SetInput(win2img.GetOutput());
    writer.SetFileName(xfileName);
    writer.Write();
    unlock();
  }

  // NATIVE FACET

  protected native int RenderCreate(vtkRenderWindow xwindow,
                                    long xdisplay, long xdrawable);

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
