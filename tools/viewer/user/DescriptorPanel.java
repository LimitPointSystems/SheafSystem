
/**
 * Classname:DescriptorPanel
 *
 * @author $Author: jebutler $
 *
 * $Date: 2013/01/12 17:18:01 $
 *
 * Copyright (c) 2013 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import tools.common.gui.*;
import tools.viewer.render.*;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 * Specialization of <code>JPanel</code> which contains a
 * <code>JList</code> of <code>Descriptors</code>
 *
 */
public abstract class DescriptorPanel extends JPanel
      implements ListSelectionListener
{
  // DATA FACET

  /**
   * The viewer.
   */
  protected Viewer viewer;

  /**
   * The descriptor list data
   */
  protected Object[] data;

  /**
   * The descriptor name
   */
  protected String name;

  /**
   * The selected descriptor
   */
  protected Descriptor selectedDescriptor = null;

  // GUI FACET

  //
  // Default values
  //

  static final int DEFAULT_WIDTH = 150;
  static final int DEFAULT_HEIGHT = 200;

  /**
   * The descriptor list.
   */
  protected JList list;

  /**
   * Constructor
   *
   */
  protected DescriptorPanel(Viewer xviewer, Object[] xdata, String xname,
                            int xwidth, int xheight)
  {
    viewer = xviewer;
    data = xdata;
    name = xname;

    // Set up the look and feel

    setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
    setPreferredSize(new Dimension(xwidth, xheight));

    // Create the list.

    list = new JList();
    list.setCellRenderer(createListCellRenderer());
    list.addMouseListener(createMouseListener());

    // Initialize the list

    init(data);

    // Create popup menu

    ViewerPopupMenu menu = createPopupMenu();

    // Attach popup menu to the list.

    list.setComponentPopupMenu(menu);

    // Register keystrokes

    registerKeyStrokes();

    // Add the list to this panel

    JScrollPane scroller = new JScrollPane(list);
    add
      (scroller);


    // Add list selection listener.

    list.addListSelectionListener(this);
  }

  /**
   * Constructor
   *
   */
  protected DescriptorPanel(Viewer xviewer, Object[] xdata, String xname)
  {
    this(xviewer, xdata, xname, DEFAULT_WIDTH, DEFAULT_HEIGHT);
  }

  /**
   * Create the double click mouse listener
   */
  protected abstract MouseListener createMouseListener();

  /**
   * Create the descriptor list cell renderer.
   */
  protected abstract DescriptorCellRenderer createListCellRenderer();

  /**
   * Create the popup menu and actions
   */
  protected abstract ViewerPopupMenu createPopupMenu();

  /**
   * Register keystrokes
   */
  protected abstract void registerKeyStrokes();

  /**
   * Force the update of the list and reselect the objects in the list.
   */
  public void refresh()
  {
    //
    // $$ISSUE: What happens if the animation changes the number
    //          of components and the selected indices don't match.
    //

    int[] selected = list.getSelectedIndices();

    update();

    list.setSelectedIndices(selected);
  }

  /**
   * Force an update of the list
   */
  protected abstract void update();

  /**
   * Reinitialize the list
   */
  protected void reinit(Object[] xdata)
  {
    selectedDescriptor = null;
    init(xdata);
  }

  /**
   * Initialize the list
   */
  protected void init(Object[] xdata)
  {
    synchronized (viewer.getScript())
    {
      synchronized (viewer.getScene())
      {
        data = xdata;

        // Set the selected descriptor if it is not
        // selected.

        if(selectedDescriptor == null)
        {
          Descriptor descriptor;
          for(int i=0; i<data.length; i++)
          {
            descriptor = (Descriptor) data[i];
            if(descriptor.selected)
            {
              selectedDescriptor = descriptor;
            }
          }

          // If no descriptor was selected and
          // there is a descriptor to select, select
          // the first descriptor.

          if(selectedDescriptor == null && data.length > 0)
          {
            selectedDescriptor = (Descriptor) data[0];
            selectedDescriptor.selected = true;
          }
        }
      }
    }

    list.setListData(data);
  }

  // THE ACTIONS

  /**
   * Implementation of ListSelectionListener.
   */
  public void valueChanged(ListSelectionEvent e)
  {
    if(e.getValueIsAdjusting() == false)
    {
      enablePopupMenu();
    }
  }

  /**
   * Invoked when the script edit mode has changed
   */
  public abstract void editScriptModeChanged();

  /**
   * Enable the popup menu items.
   */
  protected abstract void enablePopupMenu();

  /**
   * Override setEnabled
   */
  public void setEnabled(boolean xenabled)
  {
    list.setEnabled(xenabled);
  }

  /**
   * The Select Action
   */
  public void select()
  {
    // Deselect the selected descriptor

    deselect();

    // Select the highlighted descriptor.

    selectedDescriptor = getHighlightedDescriptor();
    if(selectedDescriptor != null)
      selectedDescriptor.selected = true;

    // Update the clients.

    viewer.updateClients();

    repaint();
  }

  /**
   * Deselect all the descriptors
   */
  protected void deselect()
  {
    if(selectedDescriptor == null)
      return;

    selectedDescriptor.selected = false;
    selectedDescriptor = null;
  }

  /**
   * Return the selected object as a <code>Descriptor</code>
   */
  public Descriptor getHighlightedDescriptor()
  {
    return (Descriptor) list.getSelectedValue();
  }

}
