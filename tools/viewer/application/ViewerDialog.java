
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

package com.limitpoint.tools.viewer.application;

import bindings.java.*;
import com.limitpoimt.tools.common.gui.*;
import com.limitpoimt.tools.common.util.*;
import com.limitpoimt.tools.viewer.user.*;
import com.limitpoimt.tools.viewer.render.*;
import com.limitpoimt.tools.viewer.common.*;
import com.limitpoimt.tools.viewer.table.*;

import java.awt.*;
import java.awt.event.*;
import java.lang.reflect.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * Dialog for choicing the viewer to open up a FieldActor in.
 */
public class ViewerDialog extends GenericDialog
{
  protected JComboBox viewersComboBox;

  protected Hashtable<Class, Vector<Viewer> > viewersMap;

  protected Viewer selectedViewer = null;

  protected Class viewerClass = null;
  protected FieldActorDescriptor actor = null;

  /**
   * Constructor
   */
  public ViewerDialog(Frame xowner)
  {
    super(xowner, "Open Viewer");

    setModal(true);

    viewersMap = new Hashtable<Class, Vector<Viewer> >();

    addPane(createContentPane(), 0);
  }

  /**
   * Create the content panel.
   */
  protected JPanel createContentPane()
  {
    // Layout the content panel.

    viewersComboBox = new JComboBox();
    viewersComboBox.setPreferredSize(new Dimension(200, 20));
    viewersComboBox.setMaximumSize(new Dimension(200, 20));
    viewersComboBox.setMinimumSize(new Dimension(200, 20));
    viewersComboBox.setToolTipText("Select Viewer");

    JPanel result = new JPanel();
    result.setLayout(new BoxLayout(result, BoxLayout.Y_AXIS));

    Box box = Box.createHorizontalBox();
    box.add(Box.createHorizontalStrut(10));
    box.add(viewersComboBox);
    box.add(Box.createHorizontalStrut(10));

    result.add(Box.createVerticalStrut(10));
    result.add(box);
    result.add(Box.createVerticalStrut(10));

    return result;
  }

  /**
   * Clear the opened viewers.
   */
  public void clearViewers()
  {
    // Hide all viewers.

    Enumeration<Class> keys = viewersMap.keys();
    Vector<Viewer> viewers;

    while(keys.hasMoreElements())
    {
      viewers = viewersMap.get(keys.nextElement());
      for(int i=0; i<viewers.size(); i++)
      {
        Viewer viewer = viewers.get(i);
	  
        viewer.setVisible(false);
	viewer.detachStates();
      }
    }

    // Clear the viewer map.

    viewersMap.clear();
    viewersComboBox.removeAllItems();
  }

  /**
   * True, if there is at least one viewer open.
   */
  public boolean hasOpenViewer()
  {
    return (viewersMap.size() > 0);
  }

  /**
   * Open existing viewer.
   */
  public void open()
  {
    viewerClass = null;
    actor = null;

    Enumeration<Class> keys = viewersMap.keys();
    Vector<Viewer> viewers;

    viewersComboBox.removeAllItems();
    while(keys.hasMoreElements())
    {
      viewers = viewersMap.get(keys.nextElement());
      for(int i=0; i<viewers.size(); i++)
      {
        viewersComboBox.addItem(viewers.get(i));
      }
    }

    setVisible(true);
  }

  /**
   * Open this <code>ViewerDialog</code> for viewer type, xviewerClass
   * with the <code>FieldActorDescriptor</code>, xactor.  If xviewerClass
   * is null, give the user a choice to open any existing viewer.
   */
  public void open(Class xviewerClass, FieldActorDescriptor xactor)
  {
    viewerClass = xviewerClass;
    actor = xactor;

    // Get the viewer vector and initialize the combo box.

    Vector<Viewer> viewers = viewersMap.get(viewerClass);

    int selected = -1;

    viewersComboBox.removeAllItems();
    if(viewers != null)
    {
      Viewer viewer;
      for(int i=0; i<viewers.size(); i++)
      {
        viewer = viewers.get(i);
        viewersComboBox.addItem(viewer);

        if(viewer == selectedViewer)
          selected = i;
      }
    }

    viewersComboBox.addItem("New Viewer");

    // Set the selected viewer.

    if(selected >= 0)
      viewersComboBox.setSelectedIndex(selected);
    else
      viewersComboBox.setSelectedIndex(viewersComboBox.getItemCount()-1);

    setVisible(true);
  }

  /**
   * Set the selected viewer
   */
  public void setSelectedViewer(Viewer xselectedViewer)
  {
    selectedViewer = xselectedViewer;
  }

  /**
   * Cancels the dialog.
   */
  public void cancelPressed()
  {
    setVisible(false);
  }

  /**
   * Accepts the selected filter.
   */
  public void okPressed()
  {
    setVisible(false);

    Object item = viewersComboBox.getSelectedItem();
    if(item instanceof Viewer)
    {
      // An existing viewer has been selected.

      Viewer viewer = (Viewer) item;

      if(actor != null)
      {
        // Add the field actor

        if(!viewer.addFieldActor(actor))
        {
          toFront();
          return;
        }
      }

      viewer.setVisible(true);
      viewer.setExtendedState(JFrame.NORMAL);
      viewer.toFront();
    }
    else
    {
      try
      {
        // Create a new viewer.

        Viewer viewer = createViewer(viewerClass,
                                     FieldActorDescriptor.class,
                                     actor);
        if(viewer == null)
          return;

        // Add viewer to the list

        addViewer(viewer);
      }
      catch(Exception e)
      {
        // $$HACK: Need better error handling.

        e.printStackTrace();
      }
    }
  }

  /**
   * Create and return a <code>Viewer</code>
   */
  public Viewer createViewer(Class xviewerClass,
                             Class xinputClass,
                             Object xinput) throws IOException
  {
    try
    {
      // Create a new viewer.

      Vector<Viewer> viewers = viewersMap.get(xviewerClass);

      // Get the title constructor.

      Constructor constructor =
        xviewerClass.getConstructor(Integer.class, xinputClass);

      // Instantiate the viewer

      int index = 1;
      if(viewers != null)
        index = viewers.size() + 1;

      Integer id = new Integer(index);
      Viewer viewer = (Viewer) constructor.newInstance(id, xinput);

      return viewer;
    }
    catch(InvocationTargetException e)
    {
      // Throw the cause of an invocation exception to
      // the client if it is an IOException.  This will allow
      // the user interface to catch Script reading problems
      // and report them to the user.  Otherwise, the
      // invocation exception is an error in the code
      // and should be dumped.

      if(e.getCause() instanceof IOException)
        throw (IOException) e.getCause();

      // $$HACK: Need better error handling

      e.printStackTrace();
    }
    catch(Exception e)
    {
      // $$HACK: Need better error handling.

      e.printStackTrace();
    }

    return null;
  }

  /**
   * Add a viewer to this dialog
   */
  public void addViewer(Viewer xviewer)
  {
    // Show viewer

    xviewer.setVisible(true);

    // Add viewer to the list

    Vector<Viewer> viewers = viewersMap.get(xviewer.getClass());
    if(viewers == null)
    {
      // Viewer list is not available for the class type.  Make
      // such a list.

      viewers = new Vector<Viewer>();
      viewersMap.put(xviewer.getClass(), viewers);
    }

    viewers.add(xviewer);
  }
}

