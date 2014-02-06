
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


package tools.viewer.user;

import bindings.java.*;
import tools.common.gui.*;
import tools.viewer.animation.*;
import tools.viewer.application.*;
import tools.viewer.event.*;
import tools.viewer.render.*;
import tools.viewer.common.ViewerConstants.ImageFormat;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import javax.swing.plaf.metal.*;

import vtk.*;

/**
 *
 * Abstract class for providing a user interface to the <code>Stage</code>
 *
 */
public abstract class Viewer extends LPSFrame
{
  // CLIENT FACET

  /**
   * The <code>ViewerClientApplication</code>. This is a static variable
   * that needs to be set by the client.  It only needs set once when
   * the client is initialized.
   */
  public static ViewerClientApplication APPLICATION;

  // DEFAULT VALUE FACET
  // Center on screen


  /**
   * The width of the screen
   */
  protected static final int SCREEN_WIDTH = 800;


  /**
   * The height of the screen
   */
  protected static final int SCREEN_HEIGHT = 800;


  /**
   * Default status of this <code>Viewer</code>
   */
  protected static final String DEFAULT_STATUS = "Running the Viewer";

  // GUI FACET

  /**
   * The <code>ViewerMenuBar</code>
   */
  protected ViewerMenuBar menuBar;

  /**
   * The split panel
   */
  protected JSplitPane splitPane;

  /**
   * The <code>ScreenPanel</code>
   */
  protected ScreenPanel screenPanel;

  /**
   * The <code>Screen</code>
   */
  protected Screen screen;

  /**
   * The status bar.
   */
  protected JLabel statusBar;

  /**
   * The <code>DescriptorsTabbedPane</code>
   */
  protected DescriptorsTabbedPane tabbedPane;

  /**
   * The <code>JFileChooser</code> for this viewer.
   */
  protected JFileChooser chooser = new JFileChooser();

  // RENDER FACET

  /**
   * The <code>RenderThread</code>
   */
  protected RenderThread renderThread;

  /**
   * The current <code>SceneDescriptor</code>
   */
  protected SceneDescriptor scene = new SceneDescriptor();

  // ANIMATION FACET

  /**
   * The <code>PlayThread</code>
   */
  protected PlayThread playThread;

  /**
   * The <code>AnimationToolBar</code>
   */
  protected AnimationToolBar animationToolBar;

  /**
   * The <code>Script</code>
   */
  protected Script script;

  /**
   * The edit script mode
   */
  protected boolean editScriptMode = false;

  /**
   * Constructor
   */
  protected Viewer(String xtitle, FieldActorDescriptor xactor)
  {
    init(xtitle, createDefaultScript(xactor));
  }

  /**
   * Constructor
   */
  protected Viewer(String xtitle, Script xscript)
  {
    init(xtitle, xscript);
  }

  /**
   * Constructor
   */
  protected Viewer(String xtitle, File xscriptFile) throws IOException
  {
    init(xtitle, new Script(this, xscriptFile));
  }

  protected void init(String xtitle, Script xscript)
  {
    script = xscript;

    setTitle(xtitle);
    //     setDefaultLookAndFeelDecorated(true);

    // ANIMATION FACET

    // Create the animation controls

    animationToolBar = new AnimationToolBar(this);

    // Create the play thread

    playThread = new PlayThread();

    // RENDER FACET

    // Create the render thread

    renderThread = new RenderThread();

    // GUI FACET

    // Create the menu bar

    menuBar = createMenuBar();
    setJMenuBar(menuBar);

    // Create the Screen.

    screenPanel = new ScreenPanel();
    screenPanel.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    screen = screenPanel.getScreen();

    // Create the tabbed panel

    tabbedPane = createTabbedPane();

    // Create the status bar.

    statusBar = new JLabel(DEFAULT_STATUS);
    statusBar.setForeground(Color.black);
    statusBar.setBorder(BorderFactory.createLoweredBevelBorder());

    // Layout the viewer

    splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                               tabbedPane,
                               screenPanel);
    splitPane.setDividerLocation(150);

    JPanel content = new JPanel();
    content.setLayout(new BorderLayout());
    content.add(animationToolBar, BorderLayout.NORTH);
    content.add(splitPane, BorderLayout.CENTER);
    content.add(statusBar, BorderLayout.SOUTH);

    setContentPane(content);
    pack();

    screen.requestFocus();

    // INITIALIZE FACET

    screen.initialize(renderThread);
    renderThread.initialize(this, playThread, screen);
    renderThread.start();
    playThread.initialize(this, renderThread, animationToolBar, script);
    playThread.start();
    // Set the current scene to the selected scene in the script.

    for(int i=0; i<script.size(); i++)
    {
      if(script.get(i).selected)
      {
        setScriptScene(script.get(i).clone());
        break;
      }
    }
  }

  /**
   * Detach the sections on the stage.
   */
  public void detachStates()
  {
    renderThread.detachStates();
  }      

  /**
   * Make a clone of this <code>Viewer</code> and display it.
   */
  public abstract void cloneViewer();

  /**
   * Create a default <code>Script</code>
   */
  protected abstract Script createDefaultScript(FieldActorDescriptor xactor);

  /**
   * Create the <code>ViewerMenuBar</code>
   */
  protected abstract ViewerMenuBar createMenuBar();

  /**
   * Create the <code>DescriptorsTabbedPane</code>.
   */
  protected abstract DescriptorsTabbedPane createTabbedPane();

  /**
   * Add a <code>FieldActorDescriptor</code>.
   */
  public abstract boolean addFieldActor(FieldActorDescriptor xactor);

  /**
   * Pick xposition
   */
  public abstract void pick(double[] xposition);

  // GUI FACET

  /**
   * The <code>ScreenPanel</code>
   */
  public ScreenPanel getScreenPanel()
  {
    return screenPanel;
  }

  /**
   * The <code>Screen</code>
   */
  public Screen getScreen()
  {
    return screen;
  }

  /**
   * Set the description in the status bar.
   */
  public void setStatus(String status)
  {
    statusBar.setText(status);
  }

  /**
   * Set the default description in the status bar.
   */
  public void defaultStatus()
  {
    statusBar.setText(DEFAULT_STATUS);
  }

  // ANIMATION FACET

  /**
   * Set the <code>Script</code>
   */
  public void setScript(Script xscript)
  {
    synchronized (script)
    {
      synchronized (scene)
      {
        script = xscript;
      }
    }

    // Set the edit mode to false

    editScriptMode = false;
    animationToolBar.setEditMode(editScriptMode);

    // Queue up the script in the play thread.

    playThread.addEvent(new SetScriptEvent(script));

    // Refresh the scene in the descriptor panel

    tabbedPane.refreshScene();
  }

  /**
   * The <code>Script</code>
   */
  public Script getScript()
  {
    return script;
  }

  /**
   * Toggle the edit script mode
   */
  public void editScript()
  {
    editScriptMode = !editScriptMode;

    animationToolBar.setEditMode(editScriptMode);
    tabbedPane.editScriptModeChanged();
    menuBar.setEditMode(editScriptMode);
  }

  /**
   * The edit script mode
   */
  public boolean getEditScriptMode()
  {
    return editScriptMode;
  }

  /**
   * Start the <code>Animation</code>
   */
  public void play()
  {
    playThread.addEvent(new PlayEvent());

    setPlayMode(true);
  }

  /**
   * Record the <code>Animation</code>
   */
  public void record()
  {
    playThread.addEvent(new RecordEvent());

    setPlayMode(true);
  }

  /**
   * Pause the <code>Animation</code>
   */
  public void pause()
  {
    playThread.pause();
  }

  /**
   * Sets scene to the first scene
   */
  public void startScene()
  {
    playThread.addEvent(new FirstSceneEvent());
  }

  /**
   * Sets scene to the previous scene
   */
  public void previousScene()
  {
    playThread.addEvent(new PreviousSceneEvent());
  }

  /**
   * Sets scene to the last scene
   */
  public void endScene()
  {
    playThread.addEvent(new LastSceneEvent());
  }

  /**
   * Sets scene to the next scene
   */
  public void nextScene()
  {
    playThread.addEvent(new NextSceneEvent());
  }

  /**
   * Update the time of the <code>Animation</code>
   */
  public void updateAnimationTime()
  {
    playThread.addEvent(new UpdateTimeEvent(scene.clone()));
  }

  /**
   * Save the <code>Script</code> to a user specified file.
   */
  public void saveScript()
  {
    // Get the file from the user.

    File file = getScriptFile();
    if(file == null)
      return;

    // Write the script to a file

    writeScript(script, file);
  }

  /**
   * Save the current <code>SceneDescriptor</code> to a user specified file.
   */
  public void saveScene()
  {
    // Get the file from the user.

    File file = getScriptFile();
    if(file == null)
      return;

    // Create a new script from the current scene.
    // Clone the current script without scenes, then
    // add the current scene.

    Script lscript = script.clone(false);
    lscript.add(scene.clone());

    // Write the script to a file

    writeScript(lscript, file);
  }

  /**
   * Get a script file from the user
   */
  public File getScriptFile()
  {
    File file = Script.getScriptFile(chooser, this, "Save");
    if(file == null)
      return null;

    String name = file.getName();
    if(!name.endsWith(".csv"))
      file = new File(file.getParent(), name + ".csv");

    if(file.exists())
    {
      int result = JOptionPane.showConfirmDialog(this,
                   "File already exists!\n\n" +
                   "Overwrite the file?");

      if(result != JOptionPane.YES_OPTION)
        return null;
    }

    return file;
  }

  /**
   * Write xscript to xfile
   */
  public void writeScript(Script xscript, File xfile)
  {
    try
    {
      xscript.write(xfile);
    }
    catch(IOException ex)
    {
      JOptionPane.showMessageDialog(this,
                                    "File Output Error!\n\n" +
                                    "Could not write CSV file.",
                                    "Error",
                                    JOptionPane.ERROR_MESSAGE);
    }
  }

  /**
   * Open the <code>Script</code> from a user specified file.
   */
  public void openScript()
  {
    File file = Script.getScriptFile(chooser, this, "Open");
    if(file == null || !file.exists())
      return;

    try
    {
      Script lscript = new Script(this, file);
      setScript(lscript);
    }
    catch(IOException ex)
    {
      JOptionPane.showMessageDialog(this,
                                    "File Open Error!\n" +
                                    "Could not read CSV file.\n\n" +
                                    ex.getMessage(),
                                    "Error",
                                    JOptionPane.ERROR_MESSAGE);
    }
  }

  /**
   * Open a user specified movie file
   */
  public void openMovie()
  {
    openMovie(null);
  }

  /**
   * Open a movie file, xfile
   */
  public void openMovie(File xfile)
  {
    setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
    new MoviePlayer(this, xfile);
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
  }

  /**
   * Set the play mode
   */
  public void setPlayMode(boolean xmode)
  {
    animationToolBar.setPlayMode(xmode);

    screen.setEnabled(!xmode);
    tabbedPane.setEnabled(!xmode);
    menuBar.setEnabled(!xmode);
  }

  // RENDER FACET

  /**
   * Save scene to image
   */
  public void saveImage(String xfileName, ImageFormat xformat)
  {
    renderThread.addEvent(new SaveImageEvent(xfileName, xformat));
  }

  /**
   * Update the properties panel.
   */
  public void updatePropertiesPanel(PropertiesPanel xpanel)
  {
    renderThread.addEvent(new UpdatePropertiesPanelEvent(xpanel));
  }

  // SCENE

  /**
   * Update <code>SceneDescriptor</code> of the client threads of this
   * class without resetting the view.
   */
  public void updateClients()
  {
    updateClients(false);
  }

  /**
   * Update <code>SceneDescriptor</code> of the client threads of this class
   * with resetting the view defined by xresetView.
   */
  public void updateClients(boolean xresetView)
  {
    // Add render event to render thread queue.

    RenderEvent event = new RenderEvent(scene.clone(), xresetView, false);
    renderThread.addEvent(event);

    // Update the menu bar

    menuBar.update();
  }

  /**
   * Set the <code>SceneDescriptor</code> from the
   * <code>ScenePanel</code>
   */
  public void setScriptScene(SceneDescriptor xscene)
  {
    scene = xscene;

    // Render the scene

    RenderEvent event = new RenderEvent(scene.clone(), false, false);
    renderThread.addEvent(event);

    // Update the play thread

    playThread.addEvent(new LoadSceneEvent(scene.clone()));

    // Update the descriptor panels

    tabbedPane.update();

    // Update the menu bar

    menuBar.update();
  }

  /**
   * Set the <code>SceneDescriptor</code> from the
   * <code>AnimationToolBar</code>
   */
  public void setAnimationScene(SceneDescriptor xscene)
  {
    scene = xscene;

    // Update the scene in the descriptor panels

    tabbedPane.setScene(scene);

    // Update the menu bar

    menuBar.update();
  }

  /**
   * Set th <code>SceneDescriptor</code> from the
   * <code>RenderThread</code>
   */
  public void setRenderScene(SceneDescriptor xscene)
  {
    // Copy the scene instead of assigning the scene.  This
    // will ensure that the script is updated if the a key
    // frame is being edited and will ensure that the descriptor
    // panels list items are the same objects.

    scene.copy(xscene);
  }

  /**
   * Reset the scene to the selected scene.
   */
  public void resetScene()
  {
    // Record the time of the current scene.

    double time = scene.time;

    // Set the scene to the selected script scene.

    scene = tabbedPane.getSelectedScene().clone();

    // Make sure the new scene has the same time as
    // the old scene.

    scene.setTime(time);

    // Update the clients

    updateClients();
  }

  /**
   * The current <code>SceneDescriptor</code>.
   */
  public SceneDescriptor getScene()
  {
    return scene;
  }

  /**
   * Reset the camera view
   */
  public void resetView()
  {
    renderThread.addEvent(new ResetViewEvent());
  }

  /**
   * Overwrite toString().  Return the title.
   */
  public String toString()
  {
    return getTitle();
  }

  // EVENT FACET

  /**
   * Handle a <code>ViewerEvent</code>
   */
  public void handleEvent(ViewerEvent event)
  {
    event.handle(this);
  }
}
