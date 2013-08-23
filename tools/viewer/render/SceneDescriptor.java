
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

package tools.viewer.render;

import tools.viewer.animation.*;
import tools.viewer.common.*;
import bindings.java.*;

import java.awt.*;
import java.io.*;
import java.util.*;

/**
 *
 * Contains all data needed to describe a <code>Scene</code>.
 *
 */
public class SceneDescriptor extends Descriptor
{
  // SCENE DESCRIPTOR FACET

  /**
   * The scene number
   */
  public int scene = 0;

  /**
   * The key frame flag
   */
  public boolean keyFrame = false;

  /**
   * The interactor style
   */
  public int[] interactorStyle = {ViewerConstants.TRACKBALL_INTERACTOR,
                                  ViewerConstants.CAMERA_INTERACTOR};

  /**
   * The CameraDescriptors.
   */
  public LinkedHashSet<CameraDescriptor> cameras =
      new LinkedHashSet<CameraDescriptor>();

  /**
   * The LightDescriptors.
   */
  public LinkedHashSet<LightDescriptor> lights =
      new LinkedHashSet<LightDescriptor>();

  /**
   * The ActorDescriptors
   */
  public LinkedHashSet<FieldActorDescriptor> actors =
      new LinkedHashSet<FieldActorDescriptor>();

  /**
   * Default constructor
   */
  public SceneDescriptor()
  {}

  /**
   * Constructor
   */
  public SceneDescriptor(int xscene, double xtime)
  {
    scene = xscene;
    time = xtime;
  }

  /**
   * Copy values of the <code>CameraDescriptor</code>'s if the corrisponding
   * <code>CameraDescriptor</code>'s in this scene exists.
   */
  public synchronized void copyTo(CameraDescriptor[] cameras)
  {
    for(int i=0; i<cameras.length; i++)
    {
      copyTo(cameras[i]);
    }
  }

  /**
   * Copy values of the <code>CameraDescriptor</code> if a corrisponding
   * <code>CameraDescriptor</code> in this scene exists.
   */
  public synchronized void copyTo(CameraDescriptor camera)
  {
    Iterator<CameraDescriptor> itr = cameras.iterator();
    CameraDescriptor lcamera;
    while(itr.hasNext())
    {
      lcamera = itr.next();
      if(lcamera.equals(camera))
      {
        camera.copy(lcamera);
      }
    }
  }

  /**
   * Copy values of the <code>LightDescriptor</code>'s if the corrisponding
   * <code>LightDescriptor</code>'s in this scene exists.
   */
  public synchronized void copyTo(LightDescriptor[] lights)
  {
    for(int i=0; i<lights.length; i++)
    {
      copyTo(lights[i]);
    }
  }

  /**
   * Copy values of the <code>LightDescriptor</code> if a corrisponding
   * <code>LightDescriptor</code> in this scene exists.
   */
  public synchronized void copyTo(LightDescriptor light)
  {
    Iterator<LightDescriptor> itr = lights.iterator();
    LightDescriptor llight;
    while(itr.hasNext())
    {
      llight = itr.next();
      if(llight.equals(light))
      {
        light.copy(llight);
      }
    }
  }

  /**
   * Copy values of the <code>FieldActorDescriptor</code>'s if the corrisponding
   * <code>FieldActorDescriptor</code>'s in this scene exists.
   */
  public synchronized void copyTo(FieldActorDescriptor[] actors)
  {
    for(int i=0; i<actors.length; i++)
    {
      copyTo(actors[i]);
    }
  }

  /**
   * Copy values of the <code>FieldActorDescriptor</code> if a corrisponding
   * <code>FieldActorDescriptor</code> in this scene exists.
   */
  public synchronized void copyTo(FieldActorDescriptor actor)
  {
    Iterator<FieldActorDescriptor> itr = actors.iterator();
    FieldActorDescriptor lactor;
    while(itr.hasNext())
    {
      lactor = itr.next();
      if(lactor.equals(actor))
      {
        actor.copy(lactor);
      }
    }
  }

  /**
   * Returns the camera set as an array of objects.
   */
  public synchronized Object[] getCameras()
  {
    return cameras.toArray();
  }

  /**
   * Returns the light set as an array of objects.
   */
  public synchronized Object[] getLights()
  {
    return lights.toArray();
  }

  /**
   * Returns the actor set as an array of objects.
   */
  public synchronized Object[] getActors()
  {
    return actors.toArray();
  }

  /**
   * Clone this <code>SceneDescriptor</code>.
   */
  public synchronized SceneDescriptor clone()
  {
    SceneDescriptor result = new SceneDescriptor();

    result.selected = selected;

    result.time = time;
    result.scene = scene;
    result.keyFrame = keyFrame;

    result.interactorStyle[0] = interactorStyle[0];
    result.interactorStyle[1] = interactorStyle[1];

    // Create the cameras

    Iterator<CameraDescriptor> citr = cameras.iterator();
    while(citr.hasNext())
    {
      result.cameras.add(citr.next().clone());
    }

    // Create the lights

    Iterator<LightDescriptor> litr = lights.iterator();
    while(litr.hasNext())
    {
      result.lights.add(litr.next().clone());
    }

    // Create the actors

    Iterator<FieldActorDescriptor> aitr = actors.iterator();
    while(aitr.hasNext())
    {
      result.actors.add(aitr.next().clone());
    }

    return result;
  }

  /**
   * Copy the values of xscene into this
   * <code>SceneDescriptor</code>.  Assumes the same
   * number of lights, cameras, and actors.
   */
  public synchronized void copy(SceneDescriptor xscene)
  {
    // DESCRIPTOR FACET

    selected = xscene.selected;
    time = xscene.time;

    // SCENE DESCRIPTOR FACET

    scene = xscene.scene;
    keyFrame = xscene.keyFrame;

    interactorStyle[0] = xscene.interactorStyle[0];
    interactorStyle[1] = xscene.interactorStyle[1];

    // Copy the cameras

    Iterator<CameraDescriptor> citr = cameras.iterator();
    Iterator<CameraDescriptor> xcitr = xscene.cameras.iterator();
    while(citr.hasNext())
    {
      citr.next().copy(xcitr.next());
    }

    // Copy the lights

    Iterator<LightDescriptor> litr = lights.iterator();
    Iterator<LightDescriptor> xlitr = xscene.lights.iterator();
    while(litr.hasNext())
    {
      litr.next().copy(xlitr.next());
    }

    // Copy the actors

    Iterator<FieldActorDescriptor> aitr = actors.iterator();
    Iterator<FieldActorDescriptor> xaitr = xscene.actors.iterator();
    while(aitr.hasNext())
    {
      aitr.next().copy(xaitr.next());
    }
  }

  /**
   * The name of this descriptor, used by the <code>ScenePanel</code>
   */
  public String toString()
  {
    return "Scene " + Integer.toString(scene);
  }

  // DESCRIPTOR FACET

  /**
   * Set the time
   */
  public void setTime(double xtime)
  {
    super.setTime(xtime);

    Iterator<CameraDescriptor> citr = cameras.iterator();
    while(citr.hasNext())
    {
      citr.next().setTime(xtime);
    }

    Iterator<LightDescriptor> litr = lights.iterator();
    while(litr.hasNext())
    {
      litr.next().setTime(xtime);
    }

    Iterator<FieldActorDescriptor> aitr = actors.iterator();
    while(aitr.hasNext())
    {
      aitr.next().setTime(xtime);
    }
  }

  /**
   * Read the values of this <code>SceneDescriptor</code> from xinput
   */
  public synchronized void read(InputStream xinput) throws IOException
  {
    super.read(xinput);

    scene = Script.readInt(xinput);
    keyFrame = Script.readBoolean(xinput);
    interactorStyle[0] = Script.readInt(xinput);
    interactorStyle[1] = Script.readInt(xinput);

    while(true)
    {
      // Get the type of the next descriptor to read.

      String type;
      try
      {
        type = Script.readCell(xinput);
      }
      catch(EOFException ex)
      {
        // End of file reached, this scene is done.

        break;
      }

      // Done reading the scene when the next scene identifier is found.

      if(type.equals(SceneDescriptor.class.getName()))
        break;

      // Construct the descriptor using the factory.

      Descriptor descriptor = null;
      try
      {
        descriptor = (Descriptor) Class.forName(type).newInstance();
      }
      catch(Exception e)
      {}

      if(descriptor == null)
        throw new IOException("Unknown Descriptor: " + type);

      // Read the descriptor from the input stream.

      descriptor.read(xinput);

      // Add the descriptor into the sets.

      if(descriptor instanceof CameraDescriptor)
        cameras.add((CameraDescriptor) descriptor);
      else if(descriptor instanceof LightDescriptor)
        lights.add((LightDescriptor) descriptor);
      else if(descriptor instanceof FieldActorDescriptor)
        actors.add((FieldActorDescriptor) descriptor);
      else
        throw new IOException("Invalid Descriptor: " + type);
    }
  }

  /**
   * Write this <code>SceneDescriptor</code> to xout.
   */
  public synchronized void write(OutputStream xout)
  throws IOException
  {
    super.write(xout);

    Script.writeSeparator(xout);
    Script.write(scene, xout);
    Script.writeSeparator(xout);
    Script.write(keyFrame, xout);
    Script.writeSeparator(xout);
    Script.write(interactorStyle[0], xout);
    Script.writeSeparator(xout);
    Script.write(interactorStyle[1], xout);

    Iterator<CameraDescriptor> citr = cameras.iterator();
    CameraDescriptor camera;
    while(citr.hasNext())
    {
      camera = citr.next();
      Script.writeSeparator(xout);
      Script.write(camera.getClass().getName(), xout);
      Script.writeSeparator(xout);
      camera.write(xout);
    }

    Iterator<LightDescriptor> litr = lights.iterator();
    LightDescriptor light;
    while(litr.hasNext())
    {
      light = litr.next();
      Script.writeSeparator(xout);
      Script.write(light.getClass().getName(), xout);
      Script.writeSeparator(xout);
      light.write(xout);
    }

    Iterator<FieldActorDescriptor> aitr = actors.iterator();
    FieldActorDescriptor actor;
    while(aitr.hasNext())
    {
      actor = aitr.next();
      Script.writeSeparator(xout);
      Script.write(actor.getClass().getName(), xout);
      Script.writeSeparator(xout);
      actor.write(xout);
    }
  }

  /**
   * Override the hashCode method.  Same as the scene number.
   */
  public int hashCode()
  {
    return scene;
  }

  /**
   * Override the equals method.  True, if the scene numbers
   * are the same.
   */
  public boolean equals(Object obj)
  {
    if(!(obj instanceof SceneDescriptor))
      return false;

    SceneDescriptor input = (SceneDescriptor) obj;

    return (input.scene == scene);
  }
}
