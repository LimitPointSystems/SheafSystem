
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

package tools.SheafScope;

import bindings.java.*;
import tools.common.gui.*;
import tools.viewer.application.*;

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
 * SheafScopeMainPane is the controlling class for the libsheaf
 * poset display mechanism. It creates an instance of SheafScopeDisplayPanel
 * and sets up the various user interface mechanisms required to
 * display and browse posets, poset members, and their associated data.
 *
 */
public class SheafScopeMainPane extends JPanel
{

  private SheafScopeDisplayPanel displayPanel;

  private JLabel dofStatusBar;
  private JLabel waitStatusBar;
  protected JLabel errorStatusBar;
  private JPanel statusBarPanel;

  private boolean enableRemoteX = false;
  private boolean showStdNamespace = false;
  private namespace_poset namespace = null;

  private FieldActorToolBar actorToolBar = null;
  private LPSFrame parentFrame;

  /**
   * Public Constructor
   *
   * @param xparentFrame Frame that contains this panel
   */
  public SheafScopeMainPane(LPSFrame xparentFrame)
  {
    this(xparentFrame, false, false);
  }

  /**
   * Public Constructor
   *
   * @param xparentFrame Frame that contains this panel
   * @param xenableRemoteX true, if remote X is enabled.
   * @param xshowStdNamespace true, if panel should show the standard namespace
   */
  public SheafScopeMainPane(LPSFrame xparentFrame,
                            boolean xenableRemoteX,
                            boolean xshowStdNamespace)
  {
    this(xparentFrame, xenableRemoteX, xshowStdNamespace, null);
  }

  /**
   * Public Constructor
   *
   * @param xparentFrame Frame that contains this panel
   * @param xenableRemoteX true, if remote X is enabled.
   * @param xshowStdNamespace true, if panel should show the standard namespace
   * @param xnamespace The namespace to open 
   */
  public SheafScopeMainPane(LPSFrame xparentFrame,
                            boolean xenableRemoteX,
                            boolean xshowStdNamespace,
                            namespace_poset xnamespace)
  {
    parentFrame = xparentFrame;

    enableRemoteX = xenableRemoteX;
    showStdNamespace = xshowStdNamespace;
    namespace = xnamespace;

    // Defeat swing double buffering to improve remote X performance.

    if(enableRemoteX)
    {
      RepaintManager.currentManager(null).setDoubleBufferingEnabled(false);
    }

    makePane();
  }

  /**
   * Reopen this main pane for xnamespace.
   */
  public void reopen(namespace_poset xnamespace)
  {
    namespace = xnamespace;

    displayPanel.reopen();

    if(namespace != null)
    {
      displayPanel.createTab(namespace, namespace.name());
    }
  }

  /**
   *
   */
  protected void makePane()
  {
    setLayout(new BorderLayout());

    displayPanel = createDisplayPanel();
    this.add(displayPanel, BorderLayout.CENTER);

    statusBarPanel = createStatusBar();
    this.add(statusBarPanel, BorderLayout.SOUTH);

    try
    {
      if(showStdNamespace)
      {
        namespace_poset lns = new namespace_poset("standard_namespace");
        displayPanel.createTab(lns, "standard namespace");
        //displayPanel.createTab(new namespace_poset(), "standard namespace");
      }
      else if(namespace != null)
      {
        displayPanel.createTab(namespace, namespace.name());
      }
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }
  }

  /**
   * Creates the status bar for this pane.
   *
   * @return The status bar for this pane.
   *
   */
  protected JPanel createStatusBar()
  {
    //$$TODO: Write a SheafScopeStatusBar class.

    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());
    panel.setBorder(new BevelBorder(BevelBorder.RAISED));
    errorStatusBar = new JLabel();
    errorStatusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));
    errorStatusBar.setText("Error status area");

    // Add the bars to the panel.

    panel.add(errorStatusBar, BorderLayout.EAST);

    return panel;
  }

  /**
   * Create a new instance of SheafScopeDisplayPanel --
   * this gets the whole show underway.
   *
   * @return The newly created <code>SheafScopeDisplayPanel</code> associated with this pane.
   */
  protected SheafScopeDisplayPanel createDisplayPanel()
  {
    return (new SheafScopeDisplayPanel(this));
  }

  // Public wrappers for private data members.

  /**
   * The <code>namespace_poset</code> with name, xname.
   */
  public namespace_poset getNamespace(String xname)
  {
    return displayPanel.getNamespace(xname);
  }

  /**
   * Public accessor for the private <i>dofStatusBar</i> data member.
   *
   * @return This pane's <code>dofStatusBar</code>.
   */
  public JLabel getDofStatusBar()
  {
    return dofStatusBar;
  }

  /**
   * Public accessor for the private <i>errorStatusBar</i> data member.
   *
   * @return This pane's <code>errorStatusBar</code>.
   */
  public JLabel getErrorStatusBar()
  {
    return errorStatusBar;
  }

  /**
   * Displays the error status in the status bar.
   *
   * @param xmessage The error message to be displayed.
   * @param xbeep true if you want to hear a beep.
   *
   * 
   */
  public void showErrorStatus(String xmessage, boolean xbeep)
  {
    errorStatusBar.setText(xmessage);
    System.out.println("ERROR: " + xmessage); // for testing

    if(xbeep)
      Toolkit.getDefaultToolkit().beep();
  }

  /**
   * Clears the error staus bar.
   *
   * 
   */
  public void clearErrorStatus()
  {
    //$$TODO: Find a more elegant mechanism for status bar display.
    // Clear the error status bar.

    errorStatusBar.setText(
      "                                                       ");
  }

  /**
   * Displays the dof staus on stdout.
   *
   * @param xmessage The dof status.
   *
   * 
   */
  public void showDofStatus(String xmessage)
  {
    //dofStatusBar.setText(message);
    System.out.println("DOF STATUS: " + xmessage); // for testing
  }

  /**
   * Public accessor for the <i>displayPanel</i> data member.
   *
   * @return This pane's <code>SheafScopeDisplayPanel</code>.
   */
  public SheafScopeDisplayPanel getDisplayPanel()
  {
    return displayPanel;
  }

  /**
   * Return if a jrm can be displayed in the graphic rep panel
   */
  public boolean canSelectJrm(sec_vd jrm)
  {
    // $$HACK: Fix
    //return actorPanel.canSelectJrm(jrm);

    return false;
  }

  /**
   * Default finalize method
   *
   * 
   */
  public void finalize() throws Throwable
  {
    // No specific action required, just call the superclass finalizer

    super.finalize();
  }

  /**
   * The parent frame.
   *
   * @return The parent frame.
   */
  public LPSFrame getParentFrame()
  {
    return parentFrame;
  }

  /**
   * Set the <code>FieldActorToolBar</code>
   */
  public void setFieldActorToolBar(FieldActorToolBar xactorToolBar)
  {
    actorToolBar = xactorToolBar;
  }

  /**
   * Set the section
   */
  public void setSection(sec_vd xsection)
  {
    if(actorToolBar != null)
      actorToolBar.setSection(xsection);
  }

  /**
   * Reset the actor tool bar.
   */
  public void resetActorToolBar()
  {
    if(actorToolBar != null)
      actorToolBar.reset();
  }

  /**
   * Public accessor for the <i>enableRemoteX</i> data member.
   *
   * @return true if "-r" was specified on the command line.
   */
  public boolean getEnableRemoteX()
  {
    return enableRemoteX;
  }
}
