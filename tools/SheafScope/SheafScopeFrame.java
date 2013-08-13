
/**
 *  Classname: SheafScopeFrame
 *
 *  @author $Author: dmbutler $
 *
 *  $Date: 2013/03/13 00:59:08 $
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;
import tools.common.gui.*;
import tools.viewer.application.*;
import tools.viewer.animation.*;
import tools.viewer.common.*;
import tools.viewer.render.*;
import tools.viewer.user.*;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import javax.swing.plaf.metal.*;

/**
 * LPSFrame that contains SheafScopeMainPane.  This class handles wrapping
 * a <code>SheafScopeMainPane</code> in a LPSFrame.  It also
 * takes care of window sizing, positioning and  closing events,
 * sets the frame icon and displays the splash window for the application.
 * SheafScopeFrame is to be used for standalone applications.
  */
public class SheafScopeFrame extends LPSFrame
      implements FieldActorToolBarApplication
{
  protected JFileChooser fileChooser = new JFileChooser();

  protected HelpFrame helpFrame;
  protected SheafScopeMainPane mainPane;

  //$$TODO: Put into HashMap?

  protected Action openFileAction;
  protected Action exitAppAction;
  protected Action restartAction;
  protected Action delTabAction;
  protected Action delAllTabsAction;
  protected Action dofSettingsAction;
  protected Action createViewAction;
  protected Action openViewerAction;
  protected Action openScriptAction;
  protected Action aboutAction;
  protected Action helpAction;

  //   JMenuItem themeMenuItem;

  protected String startupFileName = null;
  protected String scriptFileName = null;
  protected boolean showStdNamespace = false;
  protected boolean  enableRemoteX = false;
  protected namespace_poset namespace = null;
  protected FieldActorDialog actorDialog;
  protected ViewerDialog viewerDialog;

  protected JPanel toolBarPanel;
  protected JToolBar actionToolBar;

  /**
   * Default constructor
   */
  public SheafScopeFrame()
  {
    this(false, false, null, null);
  }

  /**
   * Public constructor
   *
   * @param xenableRemoteX true, if remote X is enabled.
   * @param xshowStdNamespace true, if panel should show the standard namespace
   * @param xstartupFileName name of a namespace file to open
   */
  public SheafScopeFrame(boolean xenableRemoteX,
                         boolean xshowStdNamespace,
                         String xstartupFileName,
			 String xscriptFileName)
  {
    enableRemoteX = xenableRemoteX;
    showStdNamespace = xshowStdNamespace;
    startupFileName = xstartupFileName;
    scriptFileName = xscriptFileName;

    // Get the namespace from the file given.

    if(xstartupFileName != null)
    {
      namespace = readNamespace(startupFileName);
    }

    // Initialize the gui in the event queue to allow the namespace
    // to finish loading.

    SwingUtilities.invokeLater(new InitGUIThread());

    // Open the startup script in the event queue to allow the
    // gui to finish initializing.

    if(scriptFileName != null)
    {
      SwingUtilities.invokeLater(new OpenScriptThread());
    }
  }

  /**
   *
   */
  protected namespace_poset readNamespace(String startupFileName)
  {
    namespace_poset result = null;
    File file = new File(startupFileName);
    if(file != null && file.exists())
    {
      try
      {
        String lname = startupFileName.substring(startupFileName.lastIndexOf("/")+1);
        result = new namespace_poset(lname);
        result.get_read_write_access(true);

        storage_agent sa = new storage_agent(startupFileName,
                                             sheaf_file.access_mode.READ_ONLY,
                                             true, false);
        sa.put_member_record_buffer_ub(15);
        sa.put_dof_tuple_record_buffer_ub(15);
        sa.read_entire(result);
      }
      catch(Exception ex)
      {
        // $$HACK: Need better error handling.

        ex.printStackTrace();
      }
    }
    return result;
  }

  /**
   *
   */
  protected void createGUI()
  {
    // Layout the frame.

    setLayout(new BorderLayout());

    //     setLookAndFeel();

    createActions();  // Must do before toolbars and menus.

    setJMenuBar(createMenuBar());

    createFieldActorDialog();

    createViewerDialog();

    createActionToolBar();
    toolBarPanel = new JPanel(new BorderLayout());
    toolBarPanel.setBorder(BorderFactory.createRaisedBevelBorder());
    toolBarPanel.add(actionToolBar, BorderLayout.CENTER);

    setTitle(SheafScopeApplication.APPLICATION_NAME);


    mainPane = new SheafScopeMainPane(this,
                                      enableRemoteX,
                                      showStdNamespace,
                                      namespace);

    // Create a splash window a show it while we load the rest.
    // have to place the call to splash following the mainpane creation
    // or splash page shows up when we invoke the scope with --help

    //    splash(); // Turned off temporarily

    this.add(toolBarPanel, BorderLayout.NORTH);

    this.add(mainPane, BorderLayout.CENTER);

    // Center on screen

    Dimension screen = GuiUtilities.getScreenSize();
    int margin = 100;

    // Deal with dual monitors (keep window on just one monitor).

    int width  = screen.width -  2*margin;
    int height = screen.height - 2*margin;
    if(width > (5*height)/4)
      width = (5*height)/4; // 5:4 ratio

    setBounds(margin, margin, width, height);

    setDefaultCloseOperation(LPSFrame.DO_NOTHING_ON_CLOSE);

    addWindowListener(new WindowAdapter()
                      {
                        public void windowClosing(WindowEvent e)
                        {
                          exitApplication();
                        }
                      }
                     );

    setGlassPane(new GlassComponent(this));
  }

  /**
   * Create the <code>FieldActorDialog</code>.
   */
  public void createFieldActorDialog()
  {
    actorDialog = new SheafScopeFieldActorDialog(this);
  }

  /**
   * Create the <code>ViewerDialog</code>
   */
  public void createViewerDialog()
  {
    viewerDialog = new ViewerDialog(this);
  }

  /**
   * Creates the actions for this pane.
   *
   * 
   */
  protected void createActions()
  {
    String iconPath;
    String tip;

    // Establish an actionListener for open file events,
    // e.g, file menu(open), open button.

    openFileAction = new SheafScopeOpenFileCommand(this);

    // Establish an actionListener for exitapp events,
    // e.g, file menu(exit), exit button.

    iconPath = SheafScopeConstants.IMAGE_PATH + "Stop16.png";

    tip = "Exit " + SheafScopeApplication.APPLICATION_NAME;
    exitAppAction
    = new GenericAction(this,              //target
                        "exitApplication", //method
                        "Exit",            //action name
                        "Exit",            //label
                        iconPath,          //icon
                        tip);              //tooltip

    // Establish an actionListener for restarting the application.
    // e.g. edit menu(restart).

    iconPath = SheafScopeConstants.IMAGE_PATH + "Restart16.png";
    tip = "Restart " + SheafScopeApplication.APPLICATION_NAME;
    restartAction = new GenericAction(this,      //target
				      "restart", //method
				      "Restart", //action name
				      "Restart", //label
				      iconPath,  //icon
				      tip);      //tooltip

    // Establish an actionListener for delete tab events,
    // e.g, edit menu(delete tab).

    iconPath = SheafScopeConstants.IMAGE_PATH + "Delete16.png";
    delTabAction = new GenericAction(this,                  //target
                                     "deleteTab",           //method
                                     "Delete Tab",          //action name
                                     "Delete Tab",          //label
                                     iconPath,              //icon
                                     "Delete current tab"); //tooltip

    // Establish an actionListener for delete all tabs events,
    // e.g, edit menu(delete all tabs).

    //delAllTabsAction = new SheafScopeDeleteAllTabsCommand(this);

    iconPath = SheafScopeConstants.IMAGE_PATH + "Delete16.png";
    delAllTabsAction
    = new GenericAction(this,                  //target
                        "deleteAllTabs",       //method
                        "Delete All Tabs",     //action name
                        "Delete All Tabs",     //label
                        iconPath,              //icon
                        "Delete current tab"); //tooltip

    // Dof Action

    iconPath = SheafScopeConstants.IMAGE_PATH + "col_filter.png";
    tip = "Edit default column filter.";
    dofSettingsAction
    = new GenericAction(this,                //target
                        "editDofSettings",   //method
                        "Column Filter",     //action name
                        "Column Filter",     //label
                        iconPath,            //icon
                        tip);                //tooltip

    // Create View Action

    iconPath = null;
    tip = "Create Graphic Representation.";
    createViewAction
    = new GenericAction(this,                //target
                        "createView",        //method
                        "Create View",       //action name
                        "Create View",       //label
                        iconPath,            //icon
                        tip);                //tooltip

    // Open Viewer Action

    iconPath = null;
    tip = "Open an existing viewer.";
    openViewerAction
    = new GenericAction(this,                //target
                        "openViewer",        //method
                        "Open Viewer",       //action name
                        "Open Viewer",       //label
                        iconPath,            //icon
                        tip);                //tooltip
    openViewerAction.setEnabled(false);

    // Open Script

    iconPath = null;
    tip = "Open a Script.";
    openScriptAction
    = new GenericAction(this,                //target
                        "openScript",        //method
                        "Open Script",       //action name
                        "Open Script",       //label
                        iconPath,            //icon
                        tip);                //tooltip

    // Help action.

    iconPath = SheafScopeConstants.IMAGE_PATH + "About16.png";
    tip = "Display user's guide for " + SheafScopeApplication.APPLICATION_NAME;
    helpAction
    = new GenericAction(this,              //target
                        "showHelp",        //method
                        "Help",            //action name
                        "User's Guide",    //label
                        iconPath,          //icon
                        tip);              //tooltip

    // About action.

    iconPath = SheafScopeConstants.IMAGE_PATH + "Help16.png";
    tip = "About " + SheafScopeApplication.APPLICATION_NAME;
    aboutAction
    = new GenericAction(this,              //target
                        "showAbout",       //method
                        "About",           //action name
                        "About",           //label
                        iconPath,          //icon
                        tip);              //tooltip

  }

  /**
   * Creates the menuBar for this pane.
   *
   * @return  The menuBar for this pane.
   */
  protected JMenuBar createMenuBar()
  {
    //$$TODO: Write a SheafScopeMenuBar class
    JMenuBar bar = new JMenuBar();
    bar.setBorder(new BevelBorder(BevelBorder.RAISED));

    bar.add(createFileMenu());
    bar.add(createEditMenu());
    bar.add(createOptionsMenu());
    bar.add(createVisualizeMenu());
    bar.add(Box.createHorizontalGlue());
    bar.add(createHelpMenu());
    return bar;
  }

  /**
   * Creates the "file" menu item for this pane.
   *
   * @return The "file" <code>JMenu</code> item.
   */
  protected JMenu createFileMenu()
  {
    JMenu menu = new JMenu("File");
    menu.setMnemonic('F');

    menu.add(openFileAction);
    menu.addSeparator();
    menu.add(exitAppAction);
    return menu;
  }

  /**
   * Creates the "edit" menu item for this pane.
   *
   * @return The "edit" <code>JMenu</code> item.
   */
  protected JMenu createEditMenu()
  {
    JMenu menu = new JMenu("Edit");
    menu.setMnemonic('E');

    menu.add(restartAction);
    menu.addSeparator();
    menu.add(delTabAction);
    menu.add(delAllTabsAction);

    return menu;
  }

  /**
   * Creates the "options" menu item for this pane.
   *
   * @return The "options" <code>JMenu</code> item.
   */
  protected JMenu createOptionsMenu()
  {
    JMenu menu = new JMenu("Options");
    menu.setMnemonic('O');

    //     menu.add(new LookAndFeelMenu(mainPane));
    //     themeMenuItem = menu.add(new ThemeMenu());
    menu.add(dofSettingsAction);
    return menu;
  }

  /**
   * Creates the "visualize" menu item for this pane.
   *
   * @return The "visualize" <code>JMenu</code> item.
   */
  protected JMenu createVisualizeMenu()
  {
    JMenu menu = new JMenu("Visualize");
    menu.setMnemonic('V');

    menu.add(createViewAction);
    menu.add(openViewerAction);
    menu.addSeparator();
    menu.add(openScriptAction);

    return menu;
  }

  /**
   * Creates the "help" menu item for this pane.
   *
   * @return The "help" <code>JMenu</code> item..
   */
  protected JMenu createHelpMenu()
  {
    JMenu menu = new JMenu("Help");
    menu.setMnemonic('H');

    menu.add(aboutAction);
    menu.add(helpAction);
    return menu;
  }


  /**
   * Creates the tool bar for the actions of this pane.
   */
  protected void createActionToolBar()
  {
    actionToolBar = new JToolBar();
    actionToolBar.add(openFileAction);
    actionToolBar.addSeparator();
    actionToolBar.add(restartAction);
    actionToolBar.addSeparator();
    actionToolBar.add(helpAction);
    actionToolBar.addSeparator();
    actionToolBar.add(Box.createHorizontalGlue());
  }

  /**
   * Exits the application.
   */
  public void exitApplication()
  {
    try
    {
      // Beep.

      Toolkit.getDefaultToolkit().beep();

      // Show a confirmation dialog.

      int reply =
        JOptionPane.showConfirmDialog(this,
				      "Do you really want to exit?",
				      SheafScopeApplication.APPLICATION_NAME + " - Exit",
				      JOptionPane.YES_NO_OPTION,
				      JOptionPane.QUESTION_MESSAGE);

      // If the confirmation was affirmative, handle exiting.

      if(reply == JOptionPane.YES_OPTION)
      {
        System.exit(0);            // close the application
      }
    }
    catch(Exception e)
    {}
  }

  /**
   * Restart the application with the initial values.
   */
  public void restart()
  {
    int result =
      JOptionPane.showConfirmDialog(this,
				    SheafScopeApplication.APPLICATION_NAME +
				    " will be reset to it's startup state.\n" +
				    "Do you really want to restart?",
				    SheafScopeApplication.APPLICATION_NAME + " - Restart",
				    JOptionPane.YES_NO_OPTION,
				    JOptionPane.QUESTION_MESSAGE);

    if(result == JOptionPane.NO_OPTION)
      return;

    setWaitState(true);

    // Clear the viewer dialog.

    viewerDialog.clearViewers();

    // Re-read the startup namespace.

    if(startupFileName != null)
    {
      namespace = readNamespace(startupFileName);
    }

    // Delete all the tabs and reopen the namespace.

    mainPane.reopen(namespace);

    // Clear the field actor tool bar.

    mainPane.setFieldActorToolBar(null);
    toolBarPanel.removeAll();
    toolBarPanel.add(actionToolBar, BorderLayout.CENTER);

    // Repaint.

    validate();
    repaint();

    // Reopen the script in the event quet to allow the the namespace
    // to finish loading.

    if(scriptFileName != null)
      SwingUtilities.invokeLater(new OpenScriptThread());

    setWaitState(false);
  }

  /**
   * Deletes the currently selected tab.
   */
  public void deleteTab()
  {
    SheafScopeDisplayPanel displayPanel = getMainPane().getDisplayPanel();

    // Delete the tab.

    displayPanel.deleteTab();

    // Mark the node as not displayed.

    SheafScopeTreeNode node = displayPanel.getSelectedNode();

    if(node != null)
      node.setIsDisplayed(false);
  }

  /**
   * Deletes all displayed tabs.
   */
  public void deleteAllTabs()
  {
    getMainPane().getDisplayPanel().deleteAllTabs();
  }

  /**
   * Show dialog for editing Dof Settings
   */
  public void editDofSettings()
  {
    SheafScopeDofSettingsDialog dofs =
      new SheafScopeDofSettingsDialog(this);
    dofs.setVisible(true);

    String dofDisplay = dofs.getDofDisplay();
    if(dofDisplay != null)
    {
      SheafScopeApplication.dofDisplay = dofDisplay;

      if(SheafScopeApplication.dofDisplay.equals(SheafScopeApplication.DISPLAY_LIMITED_DOFS))
      {
        SheafScopeApplication.dofLimit = dofs.getDofLimit();
      }
    }
  }

  /**
   * Show the <code>FieldActorDialog</code> and embed the
   * appropriate <code>FieldActorToolBar</code>
   */
  public void createView()
  {
    // Get the toolbar from the dialog.

    actorDialog.setVisible(true);

    FieldActorToolBar toolBar = actorDialog.getSelectedRep();
    if(toolBar == null)
      return;

    // Reset the values of the toolbar

    toolBar.reset();

    // Insert the toolbar into the toolbar panel.

    setFieldActorToolBar(toolBar);
  }

  /**
   * Display a <code>FieldActorToolBar</code>
   */
  public void setFieldActorToolBar(FieldActorToolBar toolBar)
  {
    setWaitState(true);

    toolBarPanel.removeAll();
    toolBarPanel.add(toolBar, BorderLayout.CENTER);
    mainPane.setFieldActorToolBar(toolBar);    

    validate();
    repaint();

    setWaitState(false);
  }

  /**
   * Show the <code>ViewerDialog</code>
   */
  public void openViewer()
  {
    viewerDialog.open();
  }

  /**
   * Open a <code>Script</code> in a new viewer.
   */
  public void openScript()
  {
    File file = Script.getScriptFile(fileChooser, this, "Open");
    if(file == null || !file.exists())
      return;

    openScript(file);
  }

  /**
   * Open a <code>Script</code> from xfile in a new viewer.
   */
  public void openScript(File xfile)
  {
    try
    {
      Class viewerClass = Script.readViewerType(xfile);
      Viewer viewer = viewerDialog.createViewer(viewerClass, File.class, xfile);
      if(viewer == null)
        return;

      viewerDialog.addViewer(viewer);
      openViewerAction.setEnabled(true);
    }
    catch(ClassNotFoundException ex)
    {
      JOptionPane.showMessageDialog(this,
                                    "Invalid Script File!\n" +
                                    "Viewer Class was not recognized.",
                                    "Invalid Script",
                                    JOptionPane.ERROR_MESSAGE);
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
   * Show the about dialog
   *
   * 
   */
  public void showAbout()
  {
    String path = SheafScopeConstants.DOC_PATH + SheafScopeConstants.ABOUT;

    openHelp(path);
  }

  /**
   * Show the help dialog
  */
  public void showHelp()
  {
    String path = SheafScopeConstants.DOC_PATH + SheafScopeConstants.USERS_GUIDE;

    openHelp(path);
  }

  /**
   *
   */
  protected void openHelp(String path)
  {
    try
    {
      URL helpURL = getClass().getResource(path);

      if(helpURL == null)
      {
        System.out.println("Couldn't find file: " + path);
        return;
      }

      String iconPath = ViewerConstants.IMAGE_PATH
                        + ViewerConstants.MAIN_ICON;
      URL iconURL = getClass().getResource(iconPath);

      if(helpFrame == null)
        helpFrame = new HelpFrame(helpURL, iconURL);
      else
        helpFrame.setPage(helpURL);
    }
    catch(IOException e)
    {
      System.out.println(e);
      return;
    }

    helpFrame.setVisible(true);
  }

  /**
   * Public accessor for the <i>fileChooser/i> data member.
   *
   * @return This pane's <code>JFileChooser</code>.
   */
  public JFileChooser getFileChooser()
  {
    return fileChooser;
  }

  /**
   * Public accessor for the <i>enableRemoteX</i> data member.
   *
   * @return true if "-r" was specified on the SheahScope command line.
   */
  public boolean getEnableRemoteX()
  {
    return enableRemoteX;
  }


  /**
   * Displays the SheafScope splash window.<p>
   *
   * 
   */
  protected void splash()
  {
    String imagePath = SheafScopeConstants.IMAGE_PATH + "splash.png";
    ImageIcon imageIcon = GuiUtilities.getImageIcon(imagePath);

    SplashWindow splashWindow = new SplashWindow(imageIcon, 6000); // 6000 => 6 seconds
  }

  //   /**
  //    * Sets the initial look and feel of the interface.
  //    *
  //    *
  //    */
  //   protected void setLookAndFeel()
  //   {
  //     try
  //     {
  //       //MetalLookAndFeel.setCurrentTheme(new DefaultMetalTheme());
  //       //UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");

  //       UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
  //     }
  //     catch(Exception e)
  //     {
  //       System.out.println("Error: " + e);
  //     }

  //     // Register theme change listener

  //     UIManager.addPropertyChangeListener(new UISwitchListener(mainPane));
  //   }

  /**
   * The <i>SheafScopeMainPane</i>.
   *
   * @return The <code>SheafScopeMainPane</code>.
   */
  public SheafScopeMainPane getMainPane()
  {
    return mainPane;
  }

  /**
   * Open a namespace.
   *
   * @param xnamespace The namespace to open
   * @param xfileName The filename of the namespace
   */
  public void openNamespace(namespace_poset xnamespace, String xfileName)
  {
    mainPane.getDisplayPanel().createTab(xnamespace, xfileName);
  }

  // VIEWER CLIENT APPLICATION FACET

  /**
   * The <code>namespace_poset</code> with name, xname.
   */
  public namespace_poset getNamespace(String xname)
  {
    return mainPane.getNamespace(xname);
  }

  /**
   * Set the selected viewer
   */
  public void setSelectedViewer(Viewer xviewer)
  {
    viewerDialog.setSelectedViewer(xviewer);
  }

  // FIELD ACTOR TOOLBAR APPLICATION FACET

  /**
   * Open up a 3d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG3DViewer(FieldActorDescriptor xactor)
  {
    openViewer(G3DViewer.class, xactor);
  }

  /**
   * Open up a 2d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG2DViewer(FieldActorDescriptor xactor)
  {
    openViewer(G2DViewer.class, xactor);
  }

  /**
   * Open up a viewer of type, xviewerClass, for the
   * <code>FieldActorDescriptor</code>, xactor
   */
  protected void openViewer(Class xviewerClass, FieldActorDescriptor xactor)
  {
    viewerDialog.open(xviewerClass, xactor);

    if(viewerDialog.hasOpenViewer())
      openViewerAction.setEnabled(true);
  }

  /**
   * Cancel the current <code>FieldActorToolBar</code>
   */
  public void cancelFieldActorToolBar()
  {
    setWaitState(true);  

    toolBarPanel.removeAll();
    toolBarPanel.add(actionToolBar, BorderLayout.CENTER);

    validate();
    repaint();

    setWaitState(false);
  }

  // STARTUP THREADS

  /**
   * Thread for creating the used interface.
   */
  protected class InitGUIThread extends Thread
  {
    public InitGUIThread()
    {
    }

    public void run()
    {
      createGUI();
      setVisible(true);
    }
  }

  /**
   * Thread for opening the startup script.
   */
  protected class OpenScriptThread extends Thread
  {
    public void run()
    {
      openScript(new File(scriptFileName));
    }
  }
}
